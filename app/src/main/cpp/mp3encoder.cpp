#include <jni.h>
#include <string>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include "lame/include/lame.h"
//#include "mp3_encoder.h"

//static Mp3Encoder *encoder = NULL;
FILE *pcmFile;
FILE *mp3File;
lame_t lameClient;

JNIEXPORT jstring JNICALL
Java_com_cjj_mp3encoder_JniManager_stringFromJNI(JNIEnv *env, jobject instance) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_cjj_mp3encoder_JniManager_getLameVersion(JNIEnv *env, jobject instance) {
    return env->NewStringUTF(get_lame_version());
}


int init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channel, int bitRate) {
    int ret = -1;
    if (access(pcmFilePath, F_OK) != 0||access(pcmFilePath, R_OK) != 0){
        return ret;
    }

    pcmFile = fopen(pcmFilePath, "rb");//读方式打开PCM文件
    if (pcmFile) {//pcmFile是否存在
        mp3File = fopen(mp3FilePath, "wb");//写方式打开MP3文件
        if (mp3File) {//mp3File是否存在
            lameClient = lame_init();//初始化lame
            //初始化输出文件的资源
            lame_set_in_samplerate(lameClient, sampleRate);
            lame_set_out_samplerate(lameClient, sampleRate);
            lame_set_num_channels(lameClient, channel);
            lame_set_brate(lameClient, bitRate / 1000);
            lame_init_params(lameClient);
            ret = 0;//成功初始化
        }
    }
    return ret;
}

void encode() {
    //读取PCM数据
    int bufferSize = 1024 * 256;
    short *buffer = new short[bufferSize / 2];
    short *leftBuffer = new short[bufferSize / 4];
    short *rightBuffer = new short[bufferSize / 4];
    unsigned char *mp3_buffer = new unsigned char[bufferSize];
    size_t readBufferSize = 0;
    while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0) {//读取一段bufferSize大小的PCM数据BUFFER
        for (int i = 0; i < readBufferSize; i++) {//拆分左右声道
            if (i % 2 == 0) {
                leftBuffer[i / 2] = buffer[i];
            } else {
                rightBuffer[i / 2] = buffer[i];
            }
        }
        // 调用LAME编码这段BUFFER
        size_t wroteSize = lame_encode_buffer(lameClient, (short int *) leftBuffer, (short int *) rightBuffer,
                                              (int) (readBufferSize / 2), mp3_buffer, bufferSize);
        fwrite(mp3_buffer, 1, wroteSize, mp3File);//把编码数据写入MP3文件
    }
    delete[] buffer;
    delete[] leftBuffer;
    delete[] rightBuffer;
    delete[] mp3_buffer;
}

void destroy() {
    if (pcmFile) {
        fclose(pcmFile);//关闭PCM文件
    }
    if (mp3File) {
        fclose(mp3File);//关闭MP3文件
        lame_close(lameClient);//销毁LAME
    }
}

JNIEXPORT jint JNICALL
Java_com_cjj_mp3encoder_JniManager_init(JNIEnv *env, jobject instance, jstring pcmPath_, jint audioChannels,
                                        jint bitRate, jint sampleRate, jstring mp3Path_) {
    const char *pcmPath = env->GetStringUTFChars(pcmPath_, 0);
    const char *mp3Path = env->GetStringUTFChars(mp3Path_, 0);

    int suc = init(pcmPath, mp3Path, sampleRate, audioChannels, bitRate);

    env->ReleaseStringUTFChars(pcmPath_, pcmPath);
    env->ReleaseStringUTFChars(mp3Path_, mp3Path);
    return (jint) suc;
}

JNIEXPORT void JNICALL
Java_com_cjj_mp3encoder_JniManager_encode(JNIEnv *env, jobject instance) {
    encode();
}

JNIEXPORT void JNICALL
Java_com_cjj_mp3encoder_JniManager_destroy(JNIEnv *env, jobject instance) {
    destroy();
}

#ifdef __cplusplus
}
#endif
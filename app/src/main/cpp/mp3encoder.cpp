#include <jni.h>
#include <string>

#ifdef __cplusplus
extern "C"
{
#include "lame/include/lame.h"

JNIEXPORT jstring JNICALL
Java_com_cjj_mp3encoder_JniManager_stringFromJNI(JNIEnv *env, jobject instance) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_cjj_mp3encoder_JniManager_getLameVersion(JNIEnv *env, jobject instance) {
    return env->NewStringUTF(get_lame_version());
}

}
#endif
//
// Created by chenjianjun on 2019/3/19.
//

#include "lame/include/lame.h"

#ifndef MP3ENCODER_MP3_ENCODER_H
#define MP3ENCODER_MP3_ENCODER_H

#endif //MP3ENCODER_MP3_ENCODER_H
#ifdef __cplusplus
extern "C"
{
#endif
class Mp3Encoder {
private:
    FILE *pcmFile;
    FILE *mp3File;
    lame_t lameClient;
public:
    Mp3Encoder();

    ~Mp3Encoder();

    int Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channel, int bitRate);

    void Encode();

    void Destroy();
};

#ifdef __cplusplus
}
#endif
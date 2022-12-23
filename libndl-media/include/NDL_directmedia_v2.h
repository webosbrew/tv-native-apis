#pragma once

#include <stddef.h>

#include "NDL_directmedia_common.h"


typedef void (*NDLMediaLoadCallback)(int, long long, const char *);

#define NDL_DIRECTMEDIA_AUDIO_PCM_FORMAT_S16LE "S16LE"
#define NDL_DIRECTMEDIA_AUDIO_PCM_MODE_STEREO "stereo"

typedef enum NDL_VIDEO_TYPE {
    NDL_VIDEO_TYPE_H264 = 1,
    NDL_VIDEO_TYPE_H265 = 2,
    NDL_VIDEO_TYPE_VP9 = 3,
    NDL_VIDEO_TYPE_AV1 = 4,
    NDL_VIDEO_TYPE_MAX = 0x7FFFFFFF,
} NDL_VIDEO_TYPE;

typedef enum NDL_AUDIO_TYPE {
    NDL_AUDIO_TYPE_PCM = 1,
    NDL_AUDIO_TYPE_MP3 = 2,
    NDL_AUDIO_TYPE_OPUS = 3,
    NDL_AUDIO_TYPE_MAX = 0x7FFFFFFF,
} NDL_AUDIO_TYPE;

typedef enum NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE {
    /* I'm pretty sure the app will crash on this value */
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_NONE = 0,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_48KHZ = 1,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_44KHZ = 2,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_32KHZ = 3,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_24KHZ = 4,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_22KHZ = 5,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_16KHZ = 6,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_12KHZ = 7,
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_8KHZ = 8,
} NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE;

static NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_OF(int hertz) {
    switch (hertz) {
        case 48000:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_48KHZ;
        case 44100:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_44KHZ;
        case 32000:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_32KHZ;
        case 24000:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_24KHZ;
        case 22050:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_22KHZ;
        case 16000:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_16KHZ;
        case 12000:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_12KHZ;
        case 8000:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_8KHZ;
        default:
            return NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE_NONE;
    }
}

typedef struct NDL_DIRECTMEDIA_AUDIO_PCM_INFO_T {
    NDL_AUDIO_TYPE type;
    int unknown1;
    const char *format;
    const char *layout;
    const char *channelMode;
    NDL_DIRECTMEDIA_AUDIO_PCM_SAMPLE_RATE sampleRate;
} NDL_DIRECTMEDIA_AUDIO_PCM_INFO;

typedef struct NDL_DIRECTMEDIA_AUDIO_OPUS_INFO_T {
    NDL_AUDIO_TYPE type;
    int unknown1;
    int channels;
    int unknown2;
    double sampleRate;
    const char *streamHeader;
} NDL_DIRECTMEDIA_AUDIO_OPUS_INFO;

typedef struct NDL_DIRECTMEDIA_DATA_INFO_T {
    struct NDL_DIRECTMEDIA_VIDEO_INFO_T {
        int width;
        int height;
        NDL_VIDEO_TYPE type;
        int unknown1;
    } video;
    union {
        NDL_AUDIO_TYPE type;
        NDL_DIRECTMEDIA_AUDIO_PCM_INFO pcm;
        NDL_DIRECTMEDIA_AUDIO_OPUS_INFO opus;
        char padding[32];
    } audio;
} NDL_DIRECTMEDIA_DATA_INFO;

typedef struct NDL_DIRECTVIDEO_HDR_INFO_T {
    int displayPrimariesX0;
    int displayPrimariesY0;
    int displayPrimariesX1;
    int displayPrimariesY1;
    int displayPrimariesX2;
    int displayPrimariesY2;
    int whitePointX;
    int whitePointY;
    int maxDisplayMasteringLuminance;
    int minDisplayMasteringLuminance;
    int maxContentLightLevel;
    int maxPicAverageLightLevel;
} NDL_DIRECTVIDEO_HDR_INFO;

/**
 *
 * @param info
 * @param callback
 * @return 0 if loaded successfully
 */
int NDL_DirectMediaLoad(NDL_DIRECTMEDIA_DATA_INFO *info, NDLMediaLoadCallback callback);

int NDL_DirectMediaUnload();


int NDL_DirectAudioGetAvailableBufferSize(int *available);

int NDL_DirectAudioGetTotalBufferSize(int *total);

int NDL_DirectAudioSupportMultiChannel(int *value);


int NDL_DirectVideoGetRenderBufferLength(int *length);

int NDL_DirectVideoSetHDRInfo(int displayPrimariesX0, int displayPrimariesY0, int displayPrimariesX1,
                              int displayPrimariesY1, int displayPrimariesX2, int displayPrimariesY2,
                              int whitePointX, int whitePointY,
                              int maxDisplayMasteringLuminance, int minDisplayMasteringLuminance,
                              int maxContentLightLevel, int maxPicAverageLightLevel);

int NDL_DirectVideoSetFrameDropThreshold(int threshold);

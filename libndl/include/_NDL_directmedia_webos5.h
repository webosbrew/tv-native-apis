#pragma once

#include <_NDL_directmedia_types.h>

typedef void (*NDLMediaLoadCallback)(int, long long, const char *);

typedef enum NDL_VIDEO_TYPE
{
    NDL_VIDEO_TYPE_H264 = 1,
    NDL_VIDEO_TYPE_H265 = 2,
    NDL_VIDEO_TYPE_VP9 = 3,
    NDL_VIDEO_TYPE_AV1 = 4,
} NDL_VIDEO_TYPE;

typedef enum NDL_AUDIO_TYPE
{
    NDL_AUDIO_TYPE_PCM = 1,
    NDL_AUDIO_TYPE_MP3 = 2,
    NDL_AUDIO_TYPE_OPUS = 3,
} NDL_AUDIO_TYPE;

typedef struct NDL_DIRECTMEDIA_AUDIO_PCM_INFO_T
{
    NDL_AUDIO_TYPE type;
    int unknown1;
    const char *format;
    const char *layout;
    const char *channelMode;
    NDL_DIRECTAUDIO_SAMPLING_FREQ_T sampleRate;
} NDL_DIRECTMEDIA_AUDIO_PCM_INFO;

typedef struct NDL_DIRECTMEDIA_AUDIO_OPUS_INFO_T
{
    NDL_AUDIO_TYPE type;
    int unknown1;
    int channels;
    int unknown2;
    double sampleRate;
    const char *streamHeader;
} NDL_DIRECTMEDIA_AUDIO_OPUS_INFO;

typedef struct NDL_DIRECTMEDIA_DATA_INFO_T
{
    struct NDL_DIRECTMEDIA_VIDEO_INFO_T
    {
        int width;
        int height;
        NDL_VIDEO_TYPE type;
        int unknown1;
    } video;
    union
    {
        NDL_AUDIO_TYPE type;
        NDL_DIRECTMEDIA_AUDIO_PCM_INFO pcm;
        NDL_DIRECTMEDIA_AUDIO_OPUS_INFO opus;
        char padding[32];
    } audio;
} NDL_DIRECTMEDIA_DATA_INFO;

typedef struct NDL_DIRECTVIDEO_HDR_INFO_T
{
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

int NDL_DirectMediaLoad(NDL_DIRECTMEDIA_DATA_INFO *info, NDLMediaLoadCallback callback);

int NDL_DirectMediaUnload();

/**
 * @param pts for webOS 5 only
 * @return 0 if succeeded
 */
int NDL_DirectAudioPlay(void *data, size_t size, unsigned long long pts);

int NDL_DirectAudioGetAvailableBufferSize(int *available);

int NDL_DirectAudioGetTotalBufferSize(int *total);

int NDL_DirectAudioSupportMultiChannel(int *value);

/**
 * @param pts for webOS 5 only
 * @return 0 if succeeded
 */
int NDL_DirectVideoPlay(void *data, size_t size, unsigned long long pts);

int NDL_DirectVideoGetRenderBufferLength(int *length);

int NDL_DirectVideoSetHDRInfo(NDL_DIRECTVIDEO_HDR_INFO info);

int NDL_DirectVideoSetFrameDropThreshold(int threshold);
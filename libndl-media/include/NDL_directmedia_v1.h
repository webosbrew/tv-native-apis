/* NDL DirectMedia API 1 (pre-webOS 5) */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDL_DIRECTMEDIA_API_VERSION
# define NDL_DIRECTMEDIA_API_VERSION 1
#elif (NDL_DIRECTMEDIA_API_VERSION != 1)
# error "this header requires NDL_DIRECTMEDIA_API_VERSION 1"
#endif

#include "NDL_directmedia_common.h"

static inline __attribute__((__const__)) NDL_DIRECTAUDIO_SAMPLING_FREQ NDL_DIRECTAUDIO_SAMPLING_FREQ_OF(int hertz) {
    switch (hertz) {
        case 4000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_4_KHZ;
        case 8000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_8_KHZ;
        case 11025:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_11_025KHZ;
        case 12000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_12_KHZ;
        case 16000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_16_KHZ;
        case 22050:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_22_05KHZ;
        case 24000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_24_KHZ;
        case 32000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_32_KHZ;
        case 44100:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_44_1KHZ;
        case 48000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_48_KHZ;
        case 64000:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_64_KHZ;
        default:
            return NDL_DIRECTAUDIO_SAMPLING_FREQ_NONE;
    }
}

typedef void (*NDLVideoPlayCallback)(unsigned long long);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioOpen(NDL_DIRECTAUDIO_DATA_INFO_T *data);

/**
 * @return 0 on success, -1 on failur
 *
 */
int NDL_DirectAudioClose(void);

/**
 * Play audio stream
 *
 * @param buffer Data buffer
 * @param size Buffer size
 * @return 0 if succeeded
 */
int NDL_DirectAudioPlay(void *buffer, unsigned int size);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioResume(void);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioPause(void);

/**
 * Check remaining space in audio buffer
 *
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioCheckBufferSize(unsigned int *remain);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoOpen(NDL_DIRECTVIDEO_DATA_INFO_T *data);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoClose(void);

/**
 * Play video stream
 *
 * @param buffer Data buffer
 * @param size Buffer size
 * @return 0 if succeeded
 */
int NDL_DirectVideoPlay(void *buffer, unsigned int size);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoStop(void);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoSetCallback(NDLVideoPlayCallback cb);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoPlayWithCallback(const void *buffer, unsigned int size, unsigned long long userdata);

#ifdef __cplusplus
}
#endif

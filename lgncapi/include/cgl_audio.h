/**
 * @ingroup cgl
 * @file cgl_audio.h
 * @brief Audio playback functions
 */
#pragma once

#include <stddef.h>

enum CGL_AUDIO_FMT_T {
    CGL_AUDIO_FMT_PCM = 1,
    CGL_AUDIO_FMT_AC3 = 2,
    CGL_AUDIO_FMT_AAC = 3,
    CGL_AUDIO_FMT_MP3 = 4,
};

typedef enum CGL_AUDIO_FMT_T CGL_AUDIO_FMT_T;

typedef enum CGL_AUDIO_CHANNEL_T {
    CGL_AUDIO_CH_INDEX_MAIN = 0,
    CGL_AUDIO_CH_INDEX_SUB = 1,
} CGL_AUDIO_CHANNEL_T;

/**
 * @brief Sampling frequency enum definitions
 */
typedef enum CGL_AUDIO_SAMPLING_FREQ_T {
    CGL_AUDIO_SAMPLING_FREQ_NONE = 0,
    CGL_AUDIO_SAMPLING_FREQ_4KHZ = 1,
    CGL_AUDIO_SAMPLING_FREQ_8KHZ = 2,
    CGL_AUDIO_SAMPLING_FREQ_11KHZ = 3,
    CGL_AUDIO_SAMPLING_FREQ_12KHZ = 4,
    CGL_AUDIO_SAMPLING_FREQ_16KHZ = 5,
    CGL_AUDIO_SAMPLING_FREQ_22KHZ = 6,
    CGL_AUDIO_SAMPLING_FREQ_24KHZ = 7,
    CGL_AUDIO_SAMPLING_FREQ_32KHZ = 8,
    CGL_AUDIO_SAMPLING_FREQ_44KHZ = 9,
    CGL_AUDIO_SAMPLING_FREQ_48KHZ = 10,
} CGL_AUDIO_SAMPLING_FREQ_T;

/**
 * @brief Helper function to get enum for certain sampling frequency
 * @param hertz Sampling frequency
 * @return Sampling frequency enum value
 */
static inline CGL_AUDIO_SAMPLING_FREQ_T CGL_AUDIO_SAMPLING_FREQ_OF(int hertz) {
    switch (hertz) {
        case 4000:
            return CGL_AUDIO_SAMPLING_FREQ_4KHZ;
        case 8000:
            return CGL_AUDIO_SAMPLING_FREQ_8KHZ;
        case 11025:
            return CGL_AUDIO_SAMPLING_FREQ_11KHZ;
        case 12000:
            return CGL_AUDIO_SAMPLING_FREQ_12KHZ;
        case 16000:
            return CGL_AUDIO_SAMPLING_FREQ_16KHZ;
        case 22050:
            return CGL_AUDIO_SAMPLING_FREQ_22KHZ;
        case 24000:
            return CGL_AUDIO_SAMPLING_FREQ_24KHZ;
        case 32000:
            return CGL_AUDIO_SAMPLING_FREQ_32KHZ;
        case 44100:
            return CGL_AUDIO_SAMPLING_FREQ_44KHZ;
        case 48000:
            return CGL_AUDIO_SAMPLING_FREQ_48KHZ;
        default:
            return CGL_AUDIO_SAMPLING_FREQ_NONE;
    }
}

/**
 * @brief Audio information
 */
typedef struct CGL_AUDIO_INFO_T {
    CGL_AUDIO_FMT_T codec;
    /**
     * @brief Usually set to CGL_AUDIO_CH_INDEX_MAIN
     */
    CGL_AUDIO_CHANNEL_T channel;
    CGL_AUDIO_SAMPLING_FREQ_T samplingFreq;
    unsigned int numberOfChannel;
    unsigned int bitPerSample;
} CGL_AUDIO_INFO_T;

/**
 * @brief Opens audio playback
 * @param info Audio information
 * @return 0 if succeeded
 */
int CGL_OpenAudio(const CGL_AUDIO_INFO_T *info);

/**
 * @brief Feed and play audio data
 * @param data Audio stream buffer
 * @param size Size of buffer
 * @return 0 if succeeded
 */
int CGL_PlayAudio(const void *data, size_t size);

/**
 * @brief Closes audio playback
 * @return 0 if succeeded
 */
int CGL_CloseAudio();

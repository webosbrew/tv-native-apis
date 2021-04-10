#pragma once
#include <stddef.h>

enum DILE_AUDIO_DIRECT_SRCTYPE_T
{
    DILE_AUDIO_DIRECT_SRCTYPE_PCM = 1
};
typedef enum DILE_AUDIO_DIRECT_SRCTYPE_T DILE_AUDIO_DIRECT_SRCTYPE_T;

enum DILE_AUDIO_DIRECT_SAMPFREQ_T
{
    DILE_AUDIO_DIRECT_SAMPFREQ_NONE = 0,
    DILE_AUDIO_DIRECT_SAMPFREQ_4KHZ = 1,
    DILE_AUDIO_DIRECT_SAMPFREQ_8KHZ = 2,
    DILE_AUDIO_DIRECT_SAMPFREQ_11KHZ = 3,
    DILE_AUDIO_DIRECT_SAMPFREQ_12KHZ = 4,
    DILE_AUDIO_DIRECT_SAMPFREQ_16KHZ = 5,
    DILE_AUDIO_DIRECT_SAMPFREQ_22KHZ = 6,
    DILE_AUDIO_DIRECT_SAMPFREQ_24KHZ = 7,
    DILE_AUDIO_DIRECT_SAMPFREQ_32KHZ = 8,
    DILE_AUDIO_DIRECT_SAMPFREQ_44KHZ = 9,
    DILE_AUDIO_DIRECT_SAMPFREQ_48KHZ = 10,
};
typedef enum DILE_AUDIO_DIRECT_SAMPFREQ_T DILE_AUDIO_DIRECT_SAMPFREQ_T;

static DILE_AUDIO_DIRECT_SAMPFREQ_T DILE_AUDIO_DIRECT_SAMPFREQ_OF(int hertz)
{
    switch (hertz)
    {
    case 4000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_4KHZ;
    case 8000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_8KHZ;
    case 11025:
        return DILE_AUDIO_DIRECT_SAMPFREQ_11KHZ;
    case 12000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_12KHZ;
    case 16000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_16KHZ;
    case 22050:
        return DILE_AUDIO_DIRECT_SAMPFREQ_22KHZ;
    case 24000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_24KHZ;
    case 32000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_32KHZ;
    case 44100:
        return DILE_AUDIO_DIRECT_SAMPFREQ_44KHZ;
    case 48000:
        return DILE_AUDIO_DIRECT_SAMPFREQ_48KHZ;
    default:
        return DILE_AUDIO_DIRECT_SAMPFREQ_NONE;
    }
}

int DILE_AUDIO_DIRECT_Open(unsigned int ch, unsigned int audioIndex);
int DILE_AUDIO_DIRECT_Start(unsigned int ch, DILE_AUDIO_DIRECT_SRCTYPE_T srcType, DILE_AUDIO_DIRECT_SAMPFREQ_T sampFreq, unsigned int numberofChannel, unsigned int bitPerSample);
int DILE_AUDIO_DIRECT_GetBufferInfo(unsigned int ch, unsigned int *param_2, void *param_3);
int DILE_AUDIO_DIRECT_SetNoDelayParam(unsigned int ch);
int DILE_AUDIO_DIRECT_Write(unsigned int ch, void *buf, size_t bufSize);
int DILE_AUDIO_DIRECT_Pause(unsigned int ch);
int DILE_AUDIO_DIRECT_Resume(unsigned int ch);
int DILE_AUDIO_DIRECT_Stop(unsigned int ch);
int DILE_AUDIO_DIRECT_Close(unsigned int ch);
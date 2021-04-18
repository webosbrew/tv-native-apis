#pragma once
#include <stddef.h>

enum NDL_DIRECTMEDIA_APP_STATE_
{
    NDL_DIRECTMEDIA_APP_STATE_FOREGROUND,
    NDL_DIRECTMEDIA_APP_STATE_BACKGROUND,
};
typedef enum NDL_DIRECTMEDIA_APP_STATE_ NDL_DIRECTMEDIA_APP_STATE_T;

enum NDL_DIRECTAUDIO_SAMPLING_FREQ_
{
    NDL_DIRECTAUDIO_SAMPLING_FREQ_NONE = 0,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_4KHZ = 1,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_8KHZ = 2,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_11KHZ = 3,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_12KHZ = 4,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_16KHZ = 5,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_22KHZ = 6,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_24KHZ = 7,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_32KHZ = 8,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_44KHZ = 9,
    NDL_DIRECTAUDIO_SAMPLING_FREQ_48KHZ = 10,
};
typedef enum NDL_DIRECTAUDIO_SAMPLING_FREQ_ NDL_DIRECTAUDIO_SAMPLING_FREQ_T;

static NDL_DIRECTAUDIO_SAMPLING_FREQ_T NDL_DIRECTAUDIO_SAMPLING_FREQ_OF(int hertz)
{
    switch (hertz)
    {
    case 4000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_4KHZ;
    case 8000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_8KHZ;
    case 11025:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_11KHZ;
    case 12000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_12KHZ;
    case 16000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_16KHZ;
    case 22050:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_22KHZ;
    case 24000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_24KHZ;
    case 32000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_32KHZ;
    case 44100:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_44KHZ;
    case 48000:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_48KHZ;
    default:
        return NDL_DIRECTAUDIO_SAMPLING_FREQ_NONE;
    }
}

typedef void (*NDLInitCallback)(char *type);

#if NDL_WEBOS5
#include "_NDL_directmedia_webos5.h"
#else
#include "_NDL_directmedia_webos4.h"
#endif

/**
 * I guess that's initializing NDL?
 * 
 * @return 0 if succeeded, -1 otherwise.
 */
int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb);
char *NDL_DirectMediaGetError();
int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state);
void NDL_DirectMediaQuit();

int NDL_DirectVideoSetArea(int x, int y, int w, int h);

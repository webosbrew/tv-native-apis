#include <stddef.h>

enum NDL_DIRECTAUDIO_CH_
{
    NDL_DIRECTAUDIO_CH_MAIN = 0,
    NDL_DIRECTAUDIO_CH_SUB = 1
};
typedef enum NDL_DIRECTAUDIO_CH_ NDL_DIRECTAUDIO_CH_T;

enum NDL_DIRECTAUDIO_SRC_TYPE_
{
    /** PCM Mix Channel */
    NDL_DIRECTAUDIO_SRC_TYPE_PCM = 1,
    NDL_DIRECTAUDIO_SRC_TYPE_AC3 = 2,
    /** AAC. audio/mpeg,mpegversion=4,stream-format=adts */
    NDL_DIRECTAUDIO_SRC_TYPE_AAC = 3,
    NDL_DIRECTAUDIO_SRC_TYPE_WTF = 4
};
typedef enum NDL_DIRECTAUDIO_SRC_TYPE_ NDL_DIRECTAUDIO_SRC_TYPE_T;

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

enum NDL_DIRECTMEDIA_APP_STATE_
{
    NDL_DIRECTMEDIA_APP_STATE_FOREGROUND,
    NDL_DIRECTMEDIA_APP_STATE_BACKGROUND,
};
typedef enum NDL_DIRECTMEDIA_APP_STATE_ NDL_DIRECTMEDIA_APP_STATE_T;

typedef void (*NDLInitCallback)(char *type);

typedef struct
{
    unsigned int numChannel;
    unsigned int bitPerSample;
    /**
     * @brief Nodelay setting - On(1)/Off(0)
     */
    unsigned int nodelay;
    unsigned int upperThreshold;
    unsigned int lowerThreshold;
    NDL_DIRECTAUDIO_CH_T channel;
    NDL_DIRECTAUDIO_SRC_TYPE_T srcType;
    NDL_DIRECTAUDIO_SAMPLING_FREQ_T samplingFreq;
} NDL_DIRECTAUDIO_DATA_INFO;

typedef struct
{
    int width;
    int height;
} NDL_DIRECTVIDEO_DATA_INFO;

/**
 * I guess that's initializing NDL?
 * 
 * @return 0 if succeeded, -1 otherwise.
 */
int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb);
char *NDL_DirectMediaGetError();
int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state);
void NDL_DirectMediaQuit();

int NDL_DirectAudioOpen(NDL_DIRECTAUDIO_DATA_INFO *info);
/**
 * @return 0 if succeeded, -1 otherwise.
 */
int NDL_DirectAudioClose();
/**
 * @return 0 if succeeded, -1 otherwise.
 */
int NDL_DirectAudioPause();
/**
 * @return maybe -1 is failed?
 */
int NDL_DirectAudioPlay(void *data, size_t size);
/**
 * @return 0 if succeeded, -1 otherwise.
 */
int NDL_DirectAudioResume();
/**
 * @return maybe -1 is failed?
 */
int NDL_DirectAudioCheckBufferSize(unsigned int *size);

int NDL_DirectVideoOpen(NDL_DIRECTVIDEO_DATA_INFO *info);
/**
 * @return maybe -1 is failed?
 */
int NDL_DirectVideoClose();
/**
 * @return maybe -1 is failed?
 */
int NDL_DirectVideoPlay(void *data, size_t size);
/**
 * @return maybe -1 is failed?
 */
int NDL_DirectVideoPlayWithCallback(void *data, size_t size, void *param_3, void *param_4);
int NDL_DirectVideoStop();
int NDL_DirectVideoSetArea(int x, int y, int w, int h);
int NDL_DirectVideoSetCallback(void (*cb)(void *));

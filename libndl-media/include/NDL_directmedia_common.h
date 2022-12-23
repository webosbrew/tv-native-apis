#pragma once

#include <stddef.h>

enum NDL_DIRECTMEDIA_APP_STATE_ {
    NDL_DIRECTMEDIA_APP_STATE_FOREGROUND,
    NDL_DIRECTMEDIA_APP_STATE_BACKGROUND,
};
typedef enum NDL_DIRECTMEDIA_APP_STATE_ NDL_DIRECTMEDIA_APP_STATE_T;

typedef void (*NDLInitCallback)(char *type);


/**
 * Initialize NDL library
 * @param appId Application ID
 * @return 0 if succeeded
 */
int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb);

/**
 * De-initialize NDL library
 */
void NDL_DirectMediaQuit();

/**
 * Get last error message
 * @return
 */
const char *NDL_DirectMediaGetError();

int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state);


int NDL_DirectVideoSetArea(int x, int y, int w, int h);

/**
 * Play audio stream
 *
 * @param data Data buffer
 * @param size Buffer size
 * @param pts Ignored under webOS 5
 * @return 0 if succeeded
 */
int NDL_DirectVideoPlay(const void *data, size_t size, unsigned long long pts);

/**
 * Play video stream
 *
 * @param data Data buffer
 * @param size Buffer size
 * @param pts Ignored under webOS 5
 * @return 0 if succeeded
 */
int NDL_DirectAudioPlay(const void *data, size_t size, unsigned long long pts);
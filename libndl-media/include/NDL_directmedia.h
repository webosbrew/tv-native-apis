#pragma once
#include <stddef.h>

#include "_NDL_directmedia_types.h"
#if NDL_WEBOS5
#include "_NDL_directmedia_webos5.h"
#else
#include "_NDL_directmedia_webos4.h"
#endif

/**
 * I guess that's initializing NDL?
 * @param appId Application ID
 * @return 0 if succeeded, -1 otherwise.
 */
int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb);
char *NDL_DirectMediaGetError();
int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state);
void NDL_DirectMediaQuit();

int NDL_DirectVideoSetArea(int x, int y, int w, int h);

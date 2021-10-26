#pragma once
#include <stddef.h>

#include "_NDL_directmedia_types.h"
#ifndef WEBOS_TARGET_VERSION_MAJOR
#error "WEBOS_TARGET_VERSION_MAJOR is not defined"
#elif WEBOS_TARGET_VERSION_MAJOR >= 5
#include "_NDL_directmedia_v2.h"
#elif WEBOS_TARGET_VERSION_MAJOR >= 4
#include "_NDL_directmedia_v1.h"
#else
#error "NDL_DirectMedia is only available on webOS 4 and above"
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

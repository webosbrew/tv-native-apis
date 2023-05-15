#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* default to API version 1 (pre-webOS 5) */
#ifndef NDL_DIRECTMEDIA_API_VERSION
# define NDL_DIRECTMEDIA_API_VERSION 1
#endif

#include "NDL_directmedia_types.h"

/**
 * Get last error message
 *
 * @return Last error message
 */
const char *NDL_DirectMediaGetError(void);

/**
 * Initialize NDL library
 * @param appId Application ID
 * @return 0 on success, -1 on failure
 */
int NDL_DirectMediaInit(const char *app_id, ResourceReleased cb);

/**
 * De-initialize NDL library
 *
 * @return 0 on success, -1 on failure
 */
int NDL_DirectMediaQuit(void);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE state);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoSetArea(int left, int top, int width, int height);

#ifdef __cplusplus
}
#endif

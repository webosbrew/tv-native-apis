/* NDL DirectMedia API 2 (webOS 5+) */

#pragma once

#ifdef __cplusplus
extern "C" {
#else
/* needed for bool in C */
# include <stdbool.h>
#endif

#ifndef NDL_DIRECTMEDIA_API_VERSION
# define NDL_DIRECTMEDIA_API_VERSION 2
#elif (NDL_DIRECTMEDIA_API_VERSION != 2)
# error "this header requires NDL_DIRECTMEDIA_API_VERSION 2"
#endif

#include "NDL_directmedia_common.h"

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioGetAvailableBufferSize(int *available);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioGetTotalBufferSize(int *total);

/**
 * Play audio stream
 *
 * @param buffer Data buffer
 * @param size Buffer size
 * @param pts
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioPlay(void *buffer, unsigned int size, long long pts);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectAudioSupportMultiChannel(int *isSuppored);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectEffectGetAvailableBufferSize(unsigned int *avail);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectEffectLoad(NDL_DIRECTAUDIO_PCM_INFO_T *info, unsigned int *preferredSize);

/**
 * Plays PCM audio using ALSA
 *
 * @param buffer Data buffer
 * @param size Buffer size
 * @return 0 on success, -1 on failure
 */
int NDL_DirectEffectPlay(void *buffer, unsigned int size);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectEffectUnload(void);

/**
 *
 * @param info
 * @param callback
 * @return 0 on success, -1 on failure
 */
int NDL_DirectMediaLoad(NDL_DIRECTMEDIA_DATA_INFO_T *data, NDLMediaLoadCallback callback);

/**
 * Unloads SMP and cleans up DA/DV/DE.
 *
 * @return 0 on success, -1 on failure
 */
int NDL_DirectMediaUnload(void);

/**
 * Unload NDL DirectMedia implementation library
 */
void NDL_DirectMedia_DL_Finalize(void);

/**
 * Load NDL DirectMedia implementation library
 *
 * @return true on success, false on failure
 */
bool NDL_DirectMedia_DL_Initialize(void);

/**
 * Load NDL DirectMedia implementation library
 *
 * @return Whether impl library has been loaded
 */
bool NDL_DirectMedia_DL_IsInitialized(void);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoFlushRenderBuffer(void);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoGetRenderBufferLength(int *length);

/**
 * Play video stream
 *
 * @param buffer Data buffer
 * @param size Buffer size
 * @param pts
 * @return 0 on success, -1 on failiure
 */
int NDL_DirectVideoPlay(void *buffer, unsigned int size, long long pts);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoSetFrameDropThreshold(int threshold);

/**
 * @return 0 on success, -1 on failure
 */
int NDL_DirectVideoSetHDRInfo(int displayPrimariesX0, int displayPrimariesY0, int displayPrimariesX1,
                              int displayPrimariesY1, int displayPrimariesX2, int displayPrimariesY2,
                              int whitePointX, int whitePointY,
                              int maxDisplayMasteringLuminance, int minDisplayMasteringLuminance,
                              int maxContentLightLevel, int maxPicAverageLightLevel);



#ifdef __cplusplus
}
#endif

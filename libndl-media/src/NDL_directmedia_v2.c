#include "NDL_directmedia_v2.h"

/* common */
const char *NDL_DirectMediaGetError(void) { return 0; }

int NDL_DirectMediaInit(const char *app_id, ResourceReleased cb) { return -1; }

int NDL_DirectMediaQuit(void) { return -1; }

int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE state) { return -1; }

int NDL_DirectVideoSetArea(int left, int top, int width, int height) { return -1; }

/* API version 2 */
int NDL_DirectAudioGetAvailableBufferSize(int *available) { return -1; }

int NDL_DirectAudioGetTotalBufferSize(int *total) { return -1; }

int NDL_DirectAudioSupportMultiChannel(int *isSupported) { return -1; }

int NDL_DirectEffectGetAvailableBufferSize(unsigned int *avail) { return -1; }

int NDL_DirectEffectLoad(NDL_DIRECTAUDIO_PCM_INFO_T *info, unsigned int *preferredSize) { return -1; }

int NDL_DirectEffectPlay(void *buffer, unsigned int size) { return -1; }

int NDL_DirectEffectUnload(void) { return -1; }

int NDL_DirectMediaLoad(NDL_DIRECTMEDIA_DATA_INFO_T *info, NDLMediaLoadCallback callback) { return -1; }

int NDL_DirectMediaUnload(void) { return -1; }

void NDL_DirectMedia_DL_Finalize(void) { return; }

bool NDL_DirectMedia_DL_Initialize(void) { return false; }

bool NDL_DirectMedia_DL_IsInitialized(void) { return false; }

int NDL_DirectVideoFlushRenderBuffer(void) { return -1; }

int NDL_DirectVideoGetRenderBufferLength(int *length) { return -1; }

int NDL_DirectVideoSetFrameDropThreshold(int threshold) { return -1; }

int NDL_DirectVideoSetHDRInfo(int displayPrimariesX0, int displayPrimariesY0, int displayPrimariesX1,
                              int displayPrimariesY1, int displayPrimariesX2, int displayPrimariesY2,
                              int whitePointX, int whitePointY,
                              int maxDisplayMasteringLuminance, int minDisplayMasteringLuminance,
                              int maxContentLightLevel, int maxPicAverageLightLevel) { return -1; }

/* both API versions (different signatures) */
int NDL_DirectAudioPlay(void *buffer, unsigned int size, long long pts) { return -1; }

int NDL_DirectVideoPlay(void *buffer, unsigned int size, long long pts) { return -1; }


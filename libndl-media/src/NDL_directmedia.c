#include "NDL_directmedia.h"

int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb) { return -1; }
char *NDL_DirectMediaGetError() { return NULL; }
int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state) { return -1; }
void NDL_DirectMediaQuit() {}

int NDL_DirectVideoSetArea(int x, int y, int w, int h) { return -1; }

#if NDL_DIRECTMEDIA_API_VERSION >= 2
int NDL_DirectMediaLoad(NDL_DIRECTMEDIA_DATA_INFO *info, NDLMediaLoadCallback callback) { return -1; }
int NDL_DirectMediaUnload() { return -1; }

int NDL_DirectAudioPlay(const void *data, size_t size, unsigned long long pts) { return -1; }
int NDL_DirectAudioGetAvailableBufferSize(int *available) { return -1; }
int NDL_DirectAudioGetTotalBufferSize(int *total) { return -1; }
int NDL_DirectAudioSupportMultiChannel(int *value) { return -1; }

int NDL_DirectVideoPlay(const void *data, size_t size, unsigned long long pts) { return -1; }
int NDL_DirectVideoGetRenderBufferLength(int *length) { return -1; }
int NDL_DirectVideoSetHDRInfo(int displayPrimariesX0, int displayPrimariesY0, int displayPrimariesX1,
                              int displayPrimariesY1, int displayPrimariesX2, int displayPrimariesY2,
                              int whitePointX, int whitePointY,
                              int maxDisplayMasteringLuminance, int minDisplayMasteringLuminance,
                              int maxContentLightLevel, int maxPicAverageLightLevel) { return -1; }
int NDL_DirectVideoSetFrameDropThreshold(int threshold) { return -1; }
#else
int NDL_DirectAudioOpen(NDL_DIRECTAUDIO_DATA_INFO *info) { return -1; }
int NDL_DirectAudioClose() { return -1; }
int NDL_DirectAudioCheckBufferSize(unsigned int *size) { return -1; }
int NDL_DirectAudioPlay(const void *data, size_t size) { return -1; }
int NDL_DirectAudioPause() { return -1; }
int NDL_DirectAudioResume() { return -1; }

int NDL_DirectVideoOpen(NDL_DIRECTVIDEO_DATA_INFO *info) { return -1; }
int NDL_DirectVideoClose() { return -1; }
int NDL_DirectVideoSetCallback(NDLVideoPlayCallback cb) { return -1; }
int NDL_DirectVideoPlay(const void *data, size_t size) { return -1; }
int NDL_DirectVideoStop() { return -1; }
int NDL_DirectVideoPlayWithCallback(const void *data, size_t size, unsigned long long userdata) { return -1; }
#endif
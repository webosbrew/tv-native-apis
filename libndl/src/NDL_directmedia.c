#include "NDL_directmedia.h"

int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb) { return -1; }

char *NDL_DirectMediaGetError() { return NULL; }

int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state) { return -1; }

void NDL_DirectMediaQuit() {}

int NDL_DirectAudioOpen(NDL_DIRECTAUDIO_DATA_INFO *info) { return -1; }

int NDL_DirectAudioClose() { return -1; }

int NDL_DirectAudioPause() { return -1; }

int NDL_DirectAudioPlay(void *data, size_t size) { return -1; }

int NDL_DirectAudioResume() { return -1; }

int NDL_DirectAudioCheckBufferSize(unsigned int *size) { return -1; }

int NDL_DirectVideoOpen(NDL_DIRECTVIDEO_DATA_INFO *info) { return -1; }

int NDL_DirectVideoClose() { return -1; }

int NDL_DirectVideoPlay(void *data, size_t size) { return -1; }

int NDL_DirectVideoPlayWithCallback(void *data, size_t size, void *param_3, void *param_4) { return -1; }

int NDL_DirectVideoStop() { return -1; }

int NDL_DirectVideoSetArea(int x, int y, int w, int h) { return -1; }

int NDL_DirectVideoSetCallback(void (*cb)(void *)) { return -1; }
#include "NDL_directmedia_v1.h"

int NDL_DirectAudioOpen(NDL_DIRECTAUDIO_DATA_INFO_T *data) { return -1; }

int NDL_DirectAudioClose(void) { return -1; }

int NDL_DirectAudioResume(void) { return -1; }

int NDL_DirectAudioPause(void) { return -1; }

int NDL_DirectAudioCheckBufferSize(unsigned int *remain) { return -1; }

int NDL_DirectVideoOpen(NDL_DIRECTVIDEO_DATA_INFO_T *data) { return -1; }

int NDL_DirectVideoClose(void) { return -1; }

int NDL_DirectVideoStop(void) { return -1; }

int NDL_DirectVideoSetCallback(NDLVideoPlayCallback cb) { return -1; }

int NDL_DirectVideoPlayWithCallback(const void *data, unsigned int size, unsigned long long userdata) { return -1; }

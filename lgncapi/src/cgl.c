#include "cgl.h"
#include <pthread.h>
#include <PmLogLib.h>
#include <json-c/json.h>
#include <dile_boardinfo.h>
#include <dile_audio_direct.h>
#include <dile_vdec_direct.h>
#include <AcbAPI.h>
#include <glib.h>
#include <luna-service2/lunaservice.h>
#include <ResourceManagerClient_c.h>
#include <unistd.h>

int CGL_Initialize(const char *appid) {
    (void) PmLogGetLibContext();
    (void) json_c_version();
    (void) pthread_testcancel();
    (void) DILE_BOARDINFO_Initialze();
    (void) DILE_AUDIO_DIRECT_Open(0, 0);
    (void) DILE_VDEC_DIRECT_Open(0, 0, 0, 0, 0);
    (void) AcbAPI_create();
    (void) glib_check_version(2, 0, 0);
    (void) LSRegister(NULL, NULL, NULL);
    (void) ResourceManagerClientCreate(NULL, NULL);
    return -1;
}

int CGL_Finalize() { return -1; }

int CGL_OpenAudio(const CGL_AUDIO_INFO_T *info) { return -1; }

int CGL_PlayAudio(const void *data, unsigned int size) { return -1; }

int CGL_CloseAudio() { return -1; }

int CGL_OpenVideo(const CGL_VIDEO_INFO_T *info) { return -1; }

int CGL_PlayVideo(const void *data, unsigned int size) { return -1; }

int CGL_CloseVideo() { return -1; }
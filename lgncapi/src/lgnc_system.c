#include "lgnc_wrapper.h"
#include "lgnc_system.h"

#include <dlfcn.h>

static void *_lgncopenapi_so = NULL;

wrapper_func _LGNC_SYSTEM_Initialize;
wrapper_func _LGNC_SYSTEM_Finalize;
wrapper_func _LGNC_SYSTEM_GetDisplayId;

wrapper_func _LGNC_DIRECTAUDIO_CheckBuffer;
wrapper_func _LGNC_DIRECTAUDIO_Close;
wrapper_func _LGNC_DIRECTAUDIO_Open;
wrapper_func _LGNC_DIRECTAUDIO_Play;

wrapper_func _LGNC_DIRECTVIDEO_Close;
wrapper_func _LGNC_DIRECTVIDEO_Open;
wrapper_func _LGNC_DIRECTVIDEO_Play;

wrapper_func _LGNC_eglGetDisplay;
wrapper_func _LGNC_eglInitialize;
wrapper_func _LGNC_eglTerminate;
wrapper_func _LGNC_eglGetConfigs;
wrapper_func _LGNC_eglChooseConfig;
wrapper_func _LGNC_eglGetConfigAttrib;
wrapper_func _LGNC_eglCreateWindowSurface;
wrapper_func _LGNC_eglDestroySurface;
wrapper_func _LGNC_eglSwapInterval;
wrapper_func _LGNC_eglCreateContext;
wrapper_func _LGNC_eglDestroyContext;
wrapper_func _LGNC_eglMakeCurrent;
wrapper_func _LGNC_eglSwapBuffers;

int LGNC_SYSTEM_Initialize(int argc, char **argv, LGNC_SYSTEM_CALLBACKS_T *callbacks)
{
    if (!_lgncopenapi_so)
    {
        _lgncopenapi_so = dlopen("liblgncopenapi.so", RTLD_NOW);
        if (!_lgncopenapi_so)
        {
            return -1;
        }
        _LGNC_SYSTEM_Initialize = dlsym(_lgncopenapi_so, "LGNC_SYSTEM_Initialize");
        _LGNC_SYSTEM_Finalize = dlsym(_lgncopenapi_so, "LGNC_SYSTEM_Finalize");
        _LGNC_SYSTEM_GetDisplayId = dlsym(_lgncopenapi_so, "LGNC_SYSTEM_GetDisplayId");

        _LGNC_DIRECTAUDIO_CheckBuffer = dlsym(_lgncopenapi_so, "LGNC_DIRECTAUDIO_CheckBuffer");
        _LGNC_DIRECTAUDIO_Close = dlsym(_lgncopenapi_so, "LGNC_DIRECTAUDIO_Close");
        _LGNC_DIRECTAUDIO_Open = dlsym(_lgncopenapi_so, "LGNC_DIRECTAUDIO_Open");
        _LGNC_DIRECTAUDIO_Play = dlsym(_lgncopenapi_so, "LGNC_DIRECTAUDIO_Play");

        _LGNC_DIRECTVIDEO_Close = dlsym(_lgncopenapi_so, "LGNC_DIRECTVIDEO_Close");
        _LGNC_DIRECTVIDEO_Open = dlsym(_lgncopenapi_so, "LGNC_DIRECTVIDEO_Open");
        _LGNC_DIRECTVIDEO_Play = dlsym(_lgncopenapi_so, "LGNC_DIRECTVIDEO_Play");

        _LGNC_eglGetDisplay = dlsym(_lgncopenapi_so, "LGNC_eglGetDisplay");
        _LGNC_eglInitialize = dlsym(_lgncopenapi_so, "LGNC_eglInitialize");
        _LGNC_eglTerminate = dlsym(_lgncopenapi_so, "LGNC_eglTerminate");
        _LGNC_eglGetConfigs = dlsym(_lgncopenapi_so, "LGNC_eglGetConfigs");
        _LGNC_eglChooseConfig = dlsym(_lgncopenapi_so, "LGNC_eglChooseConfig");
        _LGNC_eglGetConfigAttrib = dlsym(_lgncopenapi_so, "LGNC_eglGetConfigAttrib");
        _LGNC_eglCreateWindowSurface = dlsym(_lgncopenapi_so, "LGNC_eglCreateWindowSurface");
        _LGNC_eglDestroySurface = dlsym(_lgncopenapi_so, "LGNC_eglDestroySurface");
        _LGNC_eglSwapInterval = dlsym(_lgncopenapi_so, "LGNC_eglSwapInterval");
        _LGNC_eglCreateContext = dlsym(_lgncopenapi_so, "LGNC_eglCreateContext");
        _LGNC_eglDestroyContext = dlsym(_lgncopenapi_so, "LGNC_eglDestroyContext");
        _LGNC_eglMakeCurrent = dlsym(_lgncopenapi_so, "LGNC_eglMakeCurrent");
        _LGNC_eglSwapBuffers = dlsym(_lgncopenapi_so, "LGNC_eglSwapBuffers");
    }
    return (int)_LGNC_SYSTEM_Initialize(argc, argv, callbacks);
}

int LGNC_SYSTEM_Finalize(void)
{
    if (!_lgncopenapi_so)
    {
        return -1;
    }
    int ret = (int)_LGNC_SYSTEM_Finalize();
    dlclose(_lgncopenapi_so);
    return ret;
}

int LGNC_SYSTEM_GetDisplayId(int *displayId)
{
    return (int) _LGNC_SYSTEM_GetDisplayId(displayId);
}
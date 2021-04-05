#pragma once

typedef void *(*wrapper_func)();

extern wrapper_func _LGNC_SYSTEM_Initialize;
extern wrapper_func _LGNC_SYSTEM_Finalize;
extern wrapper_func _LGNC_SYSTEM_GetDisplayId;

extern wrapper_func _LGNC_DIRECTAUDIO_CheckBuffer;
extern wrapper_func _LGNC_DIRECTAUDIO_Close;
extern wrapper_func _LGNC_DIRECTAUDIO_Open;
extern wrapper_func _LGNC_DIRECTAUDIO_Play;

extern wrapper_func _LGNC_DIRECTVIDEO_Close;
extern wrapper_func _LGNC_DIRECTVIDEO_Open;
extern wrapper_func _LGNC_DIRECTVIDEO_Play;

extern wrapper_func _LGNC_eglGetDisplay;
extern wrapper_func _LGNC_eglInitialize;
extern wrapper_func _LGNC_eglTerminate;
extern wrapper_func _LGNC_eglGetConfigs;
extern wrapper_func _LGNC_eglChooseConfig;
extern wrapper_func _LGNC_eglGetConfigAttrib;
extern wrapper_func _LGNC_eglCreateWindowSurface;
extern wrapper_func _LGNC_eglDestroySurface;
extern wrapper_func _LGNC_eglSwapInterval;
extern wrapper_func _LGNC_eglCreateContext;
extern wrapper_func _LGNC_eglDestroyContext;
extern wrapper_func _LGNC_eglMakeCurrent;
extern wrapper_func _LGNC_eglSwapBuffers;
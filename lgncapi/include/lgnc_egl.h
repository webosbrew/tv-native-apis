#pragma once

#include <EGL/egl.h>

EGLDisplay LGNC_eglGetDisplay();
EGLBoolean LGNC_eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLBoolean LGNC_eglTerminate(EGLDisplay dpy);

EGLBoolean LGNC_eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);
EGLBoolean LGNC_eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
EGLBoolean LGNC_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);

EGLSurface LGNC_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
EGLBoolean LGNC_eglDestroySurface(EGLDisplay dpy, EGLSurface surface);

/* EGL 1.1 swap control API */
EGLBoolean LGNC_eglSwapInterval(EGLDisplay dpy, EGLint interval);

EGLContext LGNC_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list);
EGLBoolean LGNC_eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
EGLBoolean LGNC_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);

EGLBoolean LGNC_eglSwapBuffers(EGLDisplay dpy, EGLSurface draw);
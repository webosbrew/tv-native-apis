#include "lgnc_egl.h"

EGLDisplay LGNC_eglGetDisplay() { return 0; }
EGLBoolean LGNC_eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor) { return 0; }
EGLBoolean LGNC_eglTerminate(EGLDisplay dpy) { return 0; }
EGLBoolean LGNC_eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config) { return 0; }
EGLBoolean LGNC_eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config) { return 0; }
EGLBoolean LGNC_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value) { return 0; }
EGLSurface LGNC_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list) { return 0; }
EGLBoolean LGNC_eglDestroySurface(EGLDisplay dpy, EGLSurface surface) { return 0; }
EGLBoolean LGNC_eglSwapInterval(EGLDisplay dpy, EGLint interval) { return 0; }
EGLContext LGNC_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list) { return 0; }
EGLBoolean LGNC_eglDestroyContext(EGLDisplay dpy, EGLContext ctx) { return 0; }
EGLBoolean LGNC_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx) { return 0; }
EGLBoolean LGNC_eglSwapBuffers(EGLDisplay dpy, EGLSurface draw) { return 0; }
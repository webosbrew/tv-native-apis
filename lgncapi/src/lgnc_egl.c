#include "lgnc_egl.h"
#include "lgnc_wrapper.h"

EGLDisplay LGNC_eglGetDisplay()
{
    return (EGLDisplay)_LGNC_eglGetDisplay();
}
EGLBoolean LGNC_eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    return (EGLBoolean)_LGNC_eglInitialize(dpy, major, minor);
}
EGLBoolean LGNC_eglTerminate(EGLDisplay dpy)
{
    return (EGLBoolean)_LGNC_eglTerminate(dpy);
}
EGLBoolean LGNC_eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    return (EGLBoolean)_LGNC_eglGetConfigs(dpy, configs, config_size, num_config);
}
EGLBoolean LGNC_eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    return (EGLBoolean)_LGNC_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
}
EGLBoolean LGNC_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
    return (EGLBoolean)_LGNC_eglGetConfigAttrib(dpy, config, attribute, value);
}
EGLSurface LGNC_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
    return (EGLSurface)_LGNC_eglCreateWindowSurface(dpy, config, win, attrib_list);
}
EGLBoolean LGNC_eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    return (EGLBoolean)_LGNC_eglDestroySurface(dpy, surface);
}
EGLBoolean LGNC_eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
    return (EGLBoolean)_LGNC_eglSwapInterval(dpy, interval);
}
EGLContext LGNC_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list)
{
    return (EGLContext)_LGNC_eglCreateContext(dpy, config, share_list, attrib_list);
}
EGLBoolean LGNC_eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    return (EGLBoolean)_LGNC_eglDestroyContext(dpy, ctx);
}
EGLBoolean LGNC_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    return (EGLBoolean)_LGNC_eglMakeCurrent(dpy, draw, read, ctx);
}
EGLBoolean LGNC_eglSwapBuffers(EGLDisplay dpy, EGLSurface draw)
{
    return (EGLBoolean)_LGNC_eglSwapBuffers(dpy, draw);
}
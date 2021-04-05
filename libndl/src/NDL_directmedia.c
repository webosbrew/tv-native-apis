#include "NDL_directmedia.h"

#include <dlfcn.h>

typedef void *(*wrapper_func)();

static void *_NDL_directmedia_so = NULL;
static char *_NDL_directmedia_so_dlerr = NULL;

static wrapper_func _NDL_DirectMediaInit;
static wrapper_func _NDL_DirectMediaGetError;
static wrapper_func _NDL_DirectMediaSetAppState;
static wrapper_func _NDL_DirectMediaQuit;

static wrapper_func _NDL_DirectAudioOpen;
static wrapper_func _NDL_DirectAudioClose;
static wrapper_func _NDL_DirectAudioPause;
static wrapper_func _NDL_DirectAudioPlay;
static wrapper_func _NDL_DirectAudioResume;
static wrapper_func _NDL_DirectAudioCheckBufferSize;

static wrapper_func _NDL_DirectVideoOpen;
static wrapper_func _NDL_DirectVideoClose;
static wrapper_func _NDL_DirectVideoPlay;
static wrapper_func _NDL_DirectVideoPlayWithCallback;
static wrapper_func _NDL_DirectVideoStop;
static wrapper_func _NDL_DirectVideoSetArea;
static wrapper_func _NDL_DirectVideoSetCallback;

int NDL_DirectMediaInit(const char *appid, NDLInitCallback cb)
{
    if (!_NDL_directmedia_so)
    {
        _NDL_directmedia_so = dlopen("libNDL_directmedia.so.1", RTLD_NOW);
        if (!_NDL_directmedia_so)
        {
            _NDL_directmedia_so_dlerr = dlerror();
            return -1;
        }
        _NDL_DirectMediaInit = dlsym(_NDL_directmedia_so, "NDL_DirectMediaInit");
        _NDL_DirectMediaGetError = dlsym(_NDL_directmedia_so, "NDL_DirectMediaGetError");
        _NDL_DirectMediaSetAppState = dlsym(_NDL_directmedia_so, "NDL_DirectMediaSetAppState");
        _NDL_DirectMediaQuit = dlsym(_NDL_directmedia_so, "NDL_DirectMediaQuit");
        _NDL_DirectAudioOpen = dlsym(_NDL_directmedia_so, "NDL_DirectAudioOpen");
        _NDL_DirectAudioClose = dlsym(_NDL_directmedia_so, "NDL_DirectAudioClose");
        _NDL_DirectAudioPause = dlsym(_NDL_directmedia_so, "NDL_DirectAudioPause");
        _NDL_DirectAudioPlay = dlsym(_NDL_directmedia_so, "NDL_DirectAudioPlay");
        _NDL_DirectAudioResume = dlsym(_NDL_directmedia_so, "NDL_DirectAudioResume");
        _NDL_DirectAudioCheckBufferSize = dlsym(_NDL_directmedia_so, "NDL_DirectAudioCheckBufferSize");
        _NDL_DirectVideoOpen = dlsym(_NDL_directmedia_so, "NDL_DirectVideoOpen");
        _NDL_DirectVideoClose = dlsym(_NDL_directmedia_so, "NDL_DirectVideoClose");
        _NDL_DirectVideoPlay = dlsym(_NDL_directmedia_so, "NDL_DirectVideoPlay");
        _NDL_DirectVideoPlayWithCallback = dlsym(_NDL_directmedia_so, "NDL_DirectVideoPlayWithCallback");
        _NDL_DirectVideoStop = dlsym(_NDL_directmedia_so, "NDL_DirectVideoStop");
        _NDL_DirectVideoSetArea = dlsym(_NDL_directmedia_so, "NDL_DirectVideoSetArea");
        _NDL_DirectVideoSetCallback = dlsym(_NDL_directmedia_so, "NDL_DirectVideoSetCallback");
    }
    return (int)_NDL_DirectMediaInit(appid, cb);
}

char *NDL_DirectMediaGetError()
{
    if (!_NDL_directmedia_so)
    {
        return _NDL_directmedia_so_dlerr;
    }
    return _NDL_DirectMediaGetError();
}

int NDL_DirectMediaSetAppState(NDL_DIRECTMEDIA_APP_STATE_T state)
{
    return (int)_NDL_DirectMediaSetAppState(state);
}

void NDL_DirectMediaQuit()
{
    if (!_NDL_directmedia_so)
    {
        return;
    }
    _NDL_DirectMediaQuit();
    dlclose(_NDL_directmedia_so);
}

int NDL_DirectAudioOpen(NDL_DIRECTAUDIO_DATA_INFO *info)
{
    return (int)_NDL_DirectAudioOpen(info);
}

int NDL_DirectAudioClose()
{
    return (int)_NDL_DirectAudioClose();
}

int NDL_DirectAudioPause()
{
    return (int)_NDL_DirectAudioPause();
}

int NDL_DirectAudioPlay(void *data, size_t size)
{
    return (int)_NDL_DirectAudioPlay(data, size);
}

int NDL_DirectAudioResume()
{
    return (int)_NDL_DirectAudioResume();
}

int NDL_DirectAudioCheckBufferSize(unsigned int *size)
{
    return (int)_NDL_DirectAudioCheckBufferSize(size);
}

int NDL_DirectVideoOpen(NDL_DIRECTVIDEO_DATA_INFO *info)
{
    return (int)_NDL_DirectVideoOpen(info);
}

int NDL_DirectVideoClose()
{
    return (int)_NDL_DirectVideoClose();
}

int NDL_DirectVideoPlay(void *data, size_t size)
{
    return (int)_NDL_DirectVideoPlay(data, size);
}

int NDL_DirectVideoPlayWithCallback(void *data, size_t size, void *param_3, void *param_4)
{
    return (int)_NDL_DirectVideoPlayWithCallback(data, size, param_3, param_4);
}

int NDL_DirectVideoStop()
{
    return (int)_NDL_DirectVideoStop();
}

int NDL_DirectVideoSetArea(int x, int y, int w, int h)
{
    return (int)_NDL_DirectVideoSetArea(x, y, w, h);
}

int NDL_DirectVideoSetCallback(void (*cb)(void *))
{
    return (int)_NDL_DirectVideoSetCallback(cb);
}
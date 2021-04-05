#include <dlfcn.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

#include <sys/syscall.h>

static FILE *logout = NULL;
static int refcount = 0;

// StarfishMediaAPIs(const char *appId)
void *_ZN17StarfishMediaAPIsC1EPKc(void *this, const char *appId)
{
    refcount++;
    if (!logout)
    {
        char fname[256];
        snprintf(fname, 256, "/tmp/smp_%d.log", getpid());
        logout = fopen(fname, "a");
        setvbuf(logout, NULL, _IONBF, 0);
    }

    typedef void *(*OrigFunction)(void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIsC1EPKc");
    }
    void *ret = fn(this, appId);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::(%s) = %p\n", syscall(__NR_gettid), appId, ret);
    return ret;
}

// ~StarfishMediaAPIs()
void _ZN17StarfishMediaAPIsD1Ev(void *this)
{

    typedef void (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIsD1Ev");
        assert(fn);
    }
    fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::~()\n");
}
static void print_bytes(void *ptr, int size)
{
    unsigned char *p = ptr;
    int i;
    for (i = 0; i < size; i++)
    {
        fprintf(logout, "%02hhX ", p[i]);
    }
    fprintf(logout, "\n");
}
// const std::string StarfishMediaAPIs::Feed(const char *payload)
void *_ZN17StarfishMediaAPIs4FeedB5cxx11EPKc(void *this, void *unk, const char *payload)
{

    typedef void *(*OrigFunction)(void *, void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs4FeedB5cxx11EPKc");
        assert(fn);
    }
    void *ret = fn(this, unk, payload);
    // strtol(payl)
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Feed(%s) = %p\n", syscall(__NR_gettid), payload, ret);
    void *ptr = (void *)strtol(&payload[17], NULL, 16);
    print_bytes(ptr, 4);
    return ret;
}

// uint StarfishMediaAPIs::flush()
unsigned int _ZN17StarfishMediaAPIs5flushEv(void *this)
{
    typedef unsigned int (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs5flushEv");
        assert(fn);
    }
    unsigned int ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::flush() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// unsigned int flush(const char *payload)
unsigned int _ZN17StarfishMediaAPIs5flushEPKc(void *this, const char *payload)
{
    typedef unsigned int (*OrigFunction)(void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs5flushEPKc");
        assert(fn);
    }
    unsigned int ret = fn(this, payload);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::flush() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// void StarfishMediaAPIs::getCurrentPlaytime()
// {
// }

// const char *StarfishMediaAPIs::getMediaID()
const char *_ZN17StarfishMediaAPIs10getMediaIDEv(void *this)
{
    typedef const char *(*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs10getMediaIDEv");
        assert(fn);
    }
    const char *ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::getMediaID() = %s\n", syscall(__NR_gettid), ret);
    return ret;
}

// const char *StarfishMediaAPIs::getVolume()
// {
//     return nullptr;
// }

// bool Load(const char *payload, void(callback)(gint type, gint64 numValue, const gchar *strValue))
bool _ZN17StarfishMediaAPIs4LoadEPKcPFvixS1_E(void *this, const char *payload, void(callback)(int type, long long numValue, const char *strValue))
{
    typedef bool (*OrigFunction)(void *, const char *, void (*)(int, long long, const char *));

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs4LoadEPKcPFvixS1_E");
        assert(fn);
    }
    bool ret = fn(this, payload, callback);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Load(%s) = %d\n", syscall(__NR_gettid), payload, ret);
    return ret;
}

// bool Load(const char *payload, void(callback)(gint type, gint64 numValue, const gchar *strValue, void *data), void *data)
bool _ZN17StarfishMediaAPIs4LoadEPKcPFvixS1_PvES2_(void *this, const char *payload, void(callback)(int type, long long numValue, const char *strValue, void *data), void *data)
{
    typedef bool (*OrigFunction)(void *, const char *, void (*)(int, long long, const char *, void *), void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs4LoadEPKcPFvixS1_PvES2_");
        assert(fn);
    }
    bool ret = fn(this, payload, callback, data);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Load(%s) = %d\n", syscall(__NR_gettid), payload, ret);
    return ret;
}

// bool notifyBackground()
bool _ZN17StarfishMediaAPIs16notifyBackgroundEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs16notifyBackgroundEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::notifyBackground() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// bool notifyForeground()
bool _ZN17StarfishMediaAPIs16notifyForegroundEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs16notifyForegroundEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::notifyForeground() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// bool Pause()
bool _ZN17StarfishMediaAPIs5PauseEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs5PauseEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Pause() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// bool Play()
bool _ZN17StarfishMediaAPIs4PlayEv(void *this)
{

    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs4PlayEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Play() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// bool StarfishMediaAPIs::pushEOS()
bool _ZN17StarfishMediaAPIs7pushEOSEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs7pushEOSEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::pushEOS() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// bool StarfishMediaAPIs::renderPrerolledFrame()
bool _ZN17StarfishMediaAPIs20renderPrerolledFrameEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs20renderPrerolledFrameEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::renderPrerolledFrame() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// bool StarfishMediaAPIs::Seek(const char *millis)
bool _ZN17StarfishMediaAPIs4SeekEPKc(void *this, const char *millis)
{
    typedef bool (*OrigFunction)(void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs4SeekEPKc");
        assert(fn);
    }
    bool ret = fn(this, millis);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Seek(%s) = %d\n", syscall(__NR_gettid), millis, ret);
    return ret;
}

// bool StarfishMediaAPIs::setTimeToDecode(const char *)
bool _ZN17StarfishMediaAPIs15setTimeToDecodeEPKc(void *this, const char *payload)
{
    typedef bool (*OrigFunction)(void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs15setTimeToDecodeEPKc");
        assert(fn);
    }
    bool ret = fn(this, payload);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::setTimeToDecode(%s) = %d\n", syscall(__NR_gettid), payload, ret);
    return ret;
}

// bool StarfishMediaAPIs::setVolume(const char *)
bool _ZN17StarfishMediaAPIs9setVolumeEPKc(void *this, const char *payload)
{
    typedef bool (*OrigFunction)(void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs9setVolumeEPKc");
        assert(fn);
    }
    bool ret = fn(this, payload);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::setVolume(%s) = %d\n", syscall(__NR_gettid), payload, ret);
    return ret;
}

// bool StarfishMediaAPIs::Unload()
bool _ZN17StarfishMediaAPIs6UnloadEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs6UnloadEv");
        assert(fn);
    }
    bool ret = fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::Unload() = %d\n", syscall(__NR_gettid), ret);
    return ret;
}

// void StarfishMediaAPIs::setExternalContext(GMainContext *)
void _ZN17StarfishMediaAPIs18setExternalContextEP13_GMainContext(void *this, void *context)
{
    typedef bool (*OrigFunction)(void *, void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs18setExternalContextEP13_GMainContext");
        assert(fn);
    }
    fn(this, context);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::setExternalContext()\n", syscall(__NR_gettid));
}

// bool StarfishMediaAPIs::unsetExternalContext()
void _ZN17StarfishMediaAPIs20unsetExternalContextEv(void *this)
{
    typedef bool (*OrigFunction)(void *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs20unsetExternalContextEv");
        assert(fn);
    }
    fn(this);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::unsetExternalContext()\n", syscall(__NR_gettid));
}

// bool StarfishMediaAPIs::setHdrInfo(const char*)
bool _ZN17StarfishMediaAPIs10setHdrInfoEPKc(void *this, const char *payload)
{
    typedef bool (*OrigFunction)(void *, const char *);

    static OrigFunction fn = NULL;
    if (fn == NULL)
    {
        fn = dlsym(RTLD_NEXT, "_ZN17StarfishMediaAPIs10setHdrInfoEPKc");
        assert(fn);
    }
    bool ret = fn(this, payload);
    fprintf(logout, "[thread:%d] StarfishMediaAPIs::setHdrInfo(%s) = %d\n", syscall(__NR_gettid), payload, ret);
    return ret;
}
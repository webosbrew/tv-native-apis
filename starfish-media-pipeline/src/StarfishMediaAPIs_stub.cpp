#include <glib-2.0/glib.h>
#include <StarfishMediaAPIs.h>

StarfishMediaAPIs::StarfishMediaAPIs(const char *uid)
{
}

StarfishMediaAPIs::~StarfishMediaAPIs()
{
}

std::string StarfishMediaAPIs::Feed(const char *payload)
{
    return "";
}

uint StarfishMediaAPIs::flush()
{
    return 0;
}

uint StarfishMediaAPIs::flush(const char *payload)
{
    return 0;
}

void StarfishMediaAPIs::getCurrentPlaytime()
{
}

const char *StarfishMediaAPIs::getMediaID()
{
    return nullptr;
}

const char *StarfishMediaAPIs::getVolume()
{
    return nullptr;
}

bool StarfishMediaAPIs::Load(const char *payload, void(callback)(int type, int64_t numValue, const char *strValue))
{
    return false;
}

bool StarfishMediaAPIs::Load(const char *payload, void(callback)(int type, int64_t numValue, const char *strValue, void *data), void *data)
{
    return false;
}

bool StarfishMediaAPIs::notifyBackground()
{
    return false;
}

bool StarfishMediaAPIs::notifyForeground()
{
    return false;
}

bool StarfishMediaAPIs::Pause()
{
    return false;
}

bool StarfishMediaAPIs::Play()
{
    return false;
}

bool StarfishMediaAPIs::pushEOS()
{
    return false;
}

bool StarfishMediaAPIs::Seek(const char *millis)
{
    return false;
}

bool StarfishMediaAPIs::setTimeToDecode(const char *)
{
    return false;
}

bool StarfishMediaAPIs::setVolume(const char *)
{
    return false;
}

bool StarfishMediaAPIs::Unload()
{
    return false;
}

void StarfishMediaAPIs::setExternalContext(GMainContext *)
{
}

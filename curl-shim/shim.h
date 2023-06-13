#pragma

void *curl_shim_dlsym(const char *name);

#define CURL_SHIM_FN(ret, ...)            \
static ret (*fn) (__VA_ARGS__) = NULL;    \
if (!fn) fn = curl_shim_dlsym(__func__)

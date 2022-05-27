#pragma

void curl_shim_init();

void *curl_shim_dlsym(const char *name);

#define CURL_SHIM_FN(ret, ...)            \
curl_shim_init();                         \
static ret (*fn) (__VA_ARGS__) = NULL;    \
if (!fn) fn = curl_shim_dlsym(__func__)

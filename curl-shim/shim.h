#pragma

void curl_shim_init();

void *curl_shim_dlsym(const char *name);

#define CURL_SHIM_FN(sym, var, ret, ...) \
curl_shim_init();                         \
static ret (*var) (__VA_ARGS__) = NULL;  \
if (!var) var = curl_shim_dlsym(sym)
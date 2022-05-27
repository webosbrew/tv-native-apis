#include <stddef.h>
#include <stdarg.h>

#include "types.h"
#include "shim.h"

CURL *curl_easy_init(void) {
    CURL_SHIM_FN("curl_easy_init", fn, CURL*, void);
    return fn();
}

CURLcode curl_easy_setopt(CURL *curl, CURLoption option, ...) {
    CURL_SHIM_FN("curl_easy_setopt", fn, CURLcode, CURL *curl, CURLoption option, ...);

    CURLcode ret;
    va_list args;
    va_start(args, option);
    switch (option & CURLINFO_TYPEMASK) {
        case CURLINFO_DOUBLE:
            ret = fn(curl, option, va_arg(args, double));
            break;
        case CURLINFO_LONG:
            ret = fn(curl, option, va_arg(args, long));
            break;
        case CURLINFO_STRING:
            ret = fn(curl, option, va_arg(args, char*));
            break;
        default:
            ret = fn(curl, option, va_arg(args, void*));
            break;
    }
    va_end(args);
    return ret;
}

CURLcode curl_easy_perform(CURL *curl) {
    CURL_SHIM_FN("curl_easy_perform", fn, CURLcode, CURL *curl);
    return fn(curl);
}

void curl_easy_cleanup(CURL *curl) {
    CURL_SHIM_FN("curl_easy_cleanup", fn, void, CURL *curl);
    fn(curl);
}

CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ...) {
    CURL_SHIM_FN("curl_easy_getinfo", fn, CURLcode, CURL *curl, CURLINFO option, ...);

    CURLcode ret;
    va_list args;
    va_start(args, info);
    switch (info & CURLINFO_TYPEMASK) {
        case CURLINFO_DOUBLE:
            ret = fn(curl, info, va_arg(args, double*));
            break;
        case CURLINFO_LONG:
            ret = fn(curl, info, va_arg(args, long*));
            break;
        default:
            ret = fn(curl, info, va_arg(args, void*));
            break;
    }
    va_end(args);
    return ret;
}

CURL *curl_easy_duphandle(CURL *curl);

void curl_easy_reset(CURL *curl);

CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen, size_t *n);

CURLcode curl_easy_send(CURL *curl, const void *buffer, size_t buflen, size_t *n);

const char *curl_easy_strerror(CURLcode code) {
    CURL_SHIM_FN("curl_easy_perform", fn, const char*, CURLcode);
    return fn(code);
}
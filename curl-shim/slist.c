#include <stddef.h>

#include "shim.h"

struct curl_slist;

struct curl_slist *curl_slist_append(struct curl_slist *slist, const char *value) {
    CURL_SHIM_FN("curl_slist_append", fn, struct curl_slist *, struct curl_slist *, const char *);
    fn(slist, value);
}

void curl_slist_free_all(struct curl_slist *slist) {
    CURL_SHIM_FN("curl_slist_free_all", fn, void, struct curl_slist *);
    fn(slist);
}
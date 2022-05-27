#include <stddef.h>

#include "shim.h"
#include "types.h"

struct curl_slist;

CURL_EXTERN struct curl_slist *curl_slist_append(struct curl_slist *slist, const char *value) {
    CURL_SHIM_FN(struct curl_slist *, struct curl_slist *, const char *);
    return fn(slist, value);
}

CURL_EXTERN void curl_slist_free_all(struct curl_slist *slist) {
    CURL_SHIM_FN(void, struct curl_slist *);
    fn(slist);
}
#include <stddef.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <assert.h>

static const char *const LIBS[] = {
        "libcurl.so.4",
        "libcurl.so.5",
        NULL,
};

static void *lib_handle = NULL;

__attribute__((unused)) static void curl_shim_init() __attribute__((constructor));

__attribute__((unused)) void curl_shim_init() {
    for (int i = 0; lib_handle == NULL; ++i) {
        const char *lib = LIBS[i];
        if (lib == NULL) {
            fprintf(stderr, "Failed to load all CURL libs\n");
            abort();
        }
        lib_handle = dlopen(lib, RTLD_NOW | RTLD_LOCAL);
    }
}

void *curl_shim_dlsym(const char *name) {
    assert(lib_handle != NULL);
    return dlsym(lib_handle, name);
}
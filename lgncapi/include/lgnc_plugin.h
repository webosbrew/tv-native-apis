#pragma once
#include "lgnc_openapi_types.h"

int LGNC_PLUGIN_Initialize(LGNC_CALLBACKS_T *callbacks);

int LGNC_PLUGIN_SetAppId(const char *appId);

int LGNC_PLUGIN_Finalize();
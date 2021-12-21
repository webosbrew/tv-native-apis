#pragma once

typedef struct LGNC_PLUGIN_INIT_PARAM_T {
    int a;
    int b;
    int c;
    int d;
} LGNC_PLUGIN_INIT_PARAM_T;

int LGNC_PLUGIN_Initialize(LGNC_PLUGIN_INIT_PARAM_T *param);

int LGNC_PLUGIN_SetAppId(const char *appId);

int LGNC_PLUGIN_Finalize();
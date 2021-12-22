#pragma once

#include "lgnc_openapi_types.h"

/**
 * @brief Initializes as plugin
 * @param callbacks Event callbacks, must not be NULL.
 * @return 0 if succeeded
 */
int LGNC_PLUGIN_Initialize(LGNC_CALLBACKS_T *callbacks);

/**
 * @brief Set application ID
 *
 * Must be called AFTER LGNC_PLUGIN_Initialize.
 *
 * @param appId Application ID, e.g. "com.example.application"
 * @return 0 if succeeded
 *
 */
int LGNC_PLUGIN_SetAppId(const char *appId);

int LGNC_PLUGIN_Finalize();
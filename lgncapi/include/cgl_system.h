/**
 * @ingroup cgl
 * @file cgl_system.h
 * @brief Library initialization functions
 */
#pragma once

/**
 * @brief Initializes library
 * @param appid Application ID
 * @return 0 if succeeded
 */
int CGL_Initialize(const char *appid);

/**
 * @brief Uninitializes library
 * @return 0 if succeeded
 */
int CGL_Finalize();
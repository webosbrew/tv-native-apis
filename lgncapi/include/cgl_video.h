/**
 * @ingroup cgl
 * @file cgl_video.h
 * @brief Video playback functions
 * @hidecallgraph
 */
#pragma once

#include <stddef.h>

typedef enum CGL_VIDEO_SOURCE_T {
    CGL_VIDEO_SOURCE_MAIN = 0,
} CGL_VIDEO_SOURCE_T;

typedef enum CGL_VIDEO_3D_TYPE_T {
    CGL_VIDEO_3D_TYPE_NONE = 0,
    CGL_VIDEO_3D_TYPE_2DTO3D = 1,
    CGL_VIDEO_3D_TYPE_LR_HALF = 2,
    CGL_VIDEO_3D_TYPE_TB_HALF = 3,
    CGL_VIDEO_3D_TYPE_MAX = 4,
} CGL_VIDEO_3D_TYPE_T;

typedef struct CGL_VIDEO_INFO_T {
    int width;
    int height;
    CGL_VIDEO_SOURCE_T source;
    CGL_VIDEO_3D_TYPE_T tridType;
} CGL_VIDEO_INFO_T;

/**
 * @brief Opens video playback
 * @param info Pointer to video information
 * @return 0 if succeeded
 */
int CGL_OpenVideo(const CGL_VIDEO_INFO_T *info);

/**
 * @brief Feed and play video data
 * @param data Video stream buffer
 * @param size Size of buffer
 * @return 0 if succeeded
 */
int CGL_PlayVideo(const void *data, size_t size);

/**
 * @brief Closes video playback
 * @return 0 if succeeded
 */
int CGL_CloseVideo();

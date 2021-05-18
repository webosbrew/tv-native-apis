#pragma once

#include <stddef.h>
#include <stdint.h>

#define VT_OK 0
#define VT_SOURCE_REGION_MAX 1

typedef int32_t VT_VIDEO_WINDOW_ID;
typedef int32_t VT_RESOURCE_ID;
typedef int32_t VT_CONTEXT_ID;
typedef int32_t VT_VIDEO_PATH;
typedef int32_t VT_STATUS_T;

typedef enum VT_EVENT_TYPE_T
{
    VT_AVAILABLE = 0,
    VT_UNAVAILABLE = 1,
    VT_RESOURCE_BUSY = 2,
} VT_EVENT_TYPE_T;
typedef struct VT_REGION_T
{
    uint16_t x, y, w, h;
} VT_REGION_T;

typedef struct VT_RESOLUTION_T
{
    uint16_t w, h;
} VT_RESOLUTION_T;

typedef struct VT_OUTPUT_INFO_T
{
    uint8_t a, b, c, d;
    VT_REGION_T activeRegion;
    VT_REGION_T maxRegion;
} VT_OUTPUT_INFO_T;

typedef void (*VT_EVENT_HANDLER)(VT_EVENT_TYPE_T type, void *data, void *user_data);

VT_VIDEO_WINDOW_ID VT_CreateVideoWindow(VT_VIDEO_PATH videoPath);
VT_STATUS_T VT_AcquireVideoWindowResource(VT_VIDEO_WINDOW_ID windowId, VT_RESOURCE_ID *resourceId);
VT_STATUS_T VT_ReleaseVideoWindowResource(VT_RESOURCE_ID resourceId);
VT_CONTEXT_ID VT_CreateContext(VT_RESOURCE_ID resourceId, int textureBufferSize);
VT_STATUS_T VT_DeleteContext(VT_CONTEXT_ID contextId);
VT_STATUS_T VT_SetTextureSourceRegion(VT_CONTEXT_ID contextId, int param2);
VT_STATUS_T VT_RegisterEventHandler(VT_CONTEXT_ID contextId, VT_EVENT_HANDLER handler, void *user_data);
VT_STATUS_T VT_UnRegisterEventHandler(VT_CONTEXT_ID contextId);
VT_STATUS_T VT_GenerateTexture(VT_RESOURCE_ID resourceId, VT_CONTEXT_ID contextId, uint32_t *textureId, VT_OUTPUT_INFO_T *outputInfo);
VT_STATUS_T VT_DeleteTexture(VT_CONTEXT_ID contextId, uint32_t textureId);
VT_STATUS_T VT_GetTextureResolution(VT_CONTEXT_ID contextId, VT_RESOLUTION_T *resolution);
VT_STATUS_T VT_SetTextureResolution(VT_CONTEXT_ID contextId, VT_RESOLUTION_T *resolution);
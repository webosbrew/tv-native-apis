#pragma once

#include <stddef.h>
#include <stdint.h>

#define VT_OK 0
#define VT_SOURCE_REGION_MAX 1

typedef int32_t VT_VIDEO_WINDOW_ID;
typedef int32_t VT_RESOURCE_ID;
typedef int32_t VT_CONTEXT_ID;
typedef int32_t VT_VIDEO_PATH;

typedef enum VT_EVENT_TYPE_T
{
    VT_AVAILABLE = 0,
    VT_UNAVAILABLE = 1,
    VT_RESOURCE_BUSY = 2,
} VT_EVENT_TYPE_T;

typedef void (*VT_EVENT_HANDLER)(VT_EVENT_TYPE_T type, void *data, void *user_data);

VT_VIDEO_WINDOW_ID VT_CreateVideoWindow(VT_VIDEO_PATH videoPath);
int VT_AcquireVideoWindowResource(VT_VIDEO_WINDOW_ID windowId, VT_RESOURCE_ID *resourceId);
int VT_ReleaseVideoWindowResource(VT_RESOURCE_ID resourceId);
VT_CONTEXT_ID VT_CreateContext(VT_RESOURCE_ID resourceId, int param2);
int VT_DeleteContext(VT_CONTEXT_ID contextId);
int VT_SetTextureSourceRegion(VT_CONTEXT_ID contextId, int param2);
int VT_RegisterEventHandler(VT_CONTEXT_ID contextId, VT_EVENT_HANDLER handler, void *user_data);
int VT_UnRegisterEventHandler(VT_CONTEXT_ID contextId);
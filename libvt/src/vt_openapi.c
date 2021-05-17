#include "vt/vt_openapi.h"

VT_VIDEO_WINDOW_ID VT_CreateVideoWindow(VT_VIDEO_PATH videoPath) { return -1; }
int VT_AcquireVideoWindowResource(VT_VIDEO_WINDOW_ID windowId, VT_RESOURCE_ID *resourceId) { return -1; }
int VT_ReleaseVideoWindowResource(VT_RESOURCE_ID resourceId) { return -1; }
VT_CONTEXT_ID VT_CreateContext(VT_RESOURCE_ID resourceId, int param2) { return -1; }
int VT_DeleteContext(VT_CONTEXT_ID contextId) { return -1; }
int VT_SetTextureSourceRegion(VT_CONTEXT_ID contextId, int param2) { return -1; }
int VT_RegisterEventHandler(VT_CONTEXT_ID contextId, VT_EVENT_HANDLER handler, void *user_data) { return -1; }
int VT_UnRegisterEventHandler(VT_CONTEXT_ID contextId) { return -1; }
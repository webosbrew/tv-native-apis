#include "vt/vt_openapi.h"

VT_VIDEO_WINDOW_ID VT_CreateVideoWindow(VT_VIDEO_PATH videoPath) { return -1; }
VT_STATUS_T VT_AcquireVideoWindowResource(VT_VIDEO_WINDOW_ID windowId, VT_RESOURCE_ID *resourceId) { return -1; }
VT_STATUS_T VT_ReleaseVideoWindowResource(VT_RESOURCE_ID resourceId) { return -1; }
VT_CONTEXT_ID VT_CreateContext(VT_RESOURCE_ID resourceId, int textureBufferSize) { return -1; }
VT_STATUS_T VT_DeleteContext(VT_CONTEXT_ID contextId) { return -1; }
VT_STATUS_T VT_SetTextureSourceRegion(VT_CONTEXT_ID contextId, int param2) { return -1; }
VT_STATUS_T VT_RegisterEventHandler(VT_CONTEXT_ID contextId, VT_EVENT_HANDLER handler, void *user_data) { return -1; }
VT_STATUS_T VT_UnRegisterEventHandler(VT_CONTEXT_ID contextId) { return -1; }
VT_STATUS_T VT_GenerateTexture(VT_RESOURCE_ID resourceId, VT_CONTEXT_ID contextId, uint32_t *textureId, VT_OUTPUT_INFO_T *outputInfo) { return -1; }
VT_STATUS_T VT_DeleteTexture(VT_CONTEXT_ID contextId, uint32_t textureId) { return -1; }
VT_STATUS_T VT_GetTextureResolution(VT_CONTEXT_ID contextId, VT_RESOLUTION_T *resolution) { return -1; }
VT_STATUS_T VT_SetTextureResolution(VT_CONTEXT_ID contextId, VT_RESOLUTION_T *resolution) { return -1; }
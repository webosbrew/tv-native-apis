#include "dile_vt.h"

DILE_VT_HANDLE DILE_VT_Create(unsigned int videoWindowId) { return NULL; }
DILE_VT_HANDLE DILE_VT_CreateEx(unsigned int videoWindowId, int bufferNum) { return NULL; }
int DILE_VT_GetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE handle, int *pDumpLocation) { return -1; }
int DILE_VT_SetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE handle, int pDumpLocation) { return -1; }
int DILE_VT_SetVideoFrameOutputDeviceState(DILE_VT_HANDLE handle, uint32_t stateFlags, DILE_OUTPUTDEVICE_STATE *state) { return -1; }
int DILE_VT_GetCurrentVideoFrameBufferProperty(DILE_VT_HANDLE handle, DILE_VT_FRAMEBUFFER_PROPERTY *param_2, uint32_t *pIndexOfCurrentVideoFrameBuffer) { return -1; }
void DILE_VT_Destroy(DILE_VT_HANDLE handle) {}
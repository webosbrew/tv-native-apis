#include "dile_vt.h"

DILE_VT_HANDLE DILE_VT_Create(unsigned int videoWindowId) { return NULL; }
DILE_VT_HANDLE DILE_VT_CreateEx(unsigned int videoWindowId, int bufferNum) { return NULL; }
int DILE_VT_GetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE handle, int *pDumpLocation) { return -1; }
int DILE_VT_SetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE handle, int pDumpLocation) { return -1; }
int DILE_VT_SetVideoFrameOutputDeviceState(DILE_VT_HANDLE handle, uint32_t stateFlags, DILE_OUTPUTDEVICE_STATE *state) { return -1; }
int DILE_VT_GetCurrentVideoFrameBufferProperty(DILE_VT_HANDLE handle, DILE_VT_FRAMEBUFFER_PROPERTY *param_2, uint32_t *pIndexOfCurrentVideoFrameBuffer) { return -1; }
void DILE_VT_Destroy(DILE_VT_HANDLE handle) {}
int DILE_VT_SetVideoFrameOutputDeviceOutputRegion(DILE_VT_HANDLE handle, int pDumpLocation, DILE_VT_RECT* rect) { return -1; }
int DILE_VT_WaitVsync(DILE_VT_HANDLE handle, int unk1, int unk2) { return -1; }

int DILE_VT_GetVideoFrameBufferCapability(DILE_VT_HANDLE handle, DILE_VT_FRAMEBUFFER_CAPABILITY* cap) { return -1; }
int DILE_VT_GetAllVideoFrameBufferProperty(DILE_VT_HANDLE handle, DILE_VT_FRAMEBUFFER_CAPABILITY* cap, DILE_VT_FRAMEBUFFER_PROPERTY* vfbProp) { return -1; }
int DILE_VT_GetVideoFrameOutputDeviceLimitation(DILE_VT_HANDLE vth, DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_LIMITATION* limitation) { return -1; }

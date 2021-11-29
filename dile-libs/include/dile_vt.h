#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct DILE_VT_T *DILE_VT_HANDLE;

typedef struct DILE_OUTPUTDEVICE_STATE_T
{
    uint8_t enabled;
    uint8_t freezed;
    uint8_t appliedPQ;
    uint8_t unknown;
    uint32_t framerate;
} DILE_OUTPUTDEVICE_STATE;

typedef struct DILE_VT_FRAMEBUFFER_PROPERTY_T
{
    uint32_t pixelFormat, stride, width, height;
    void *ptr;
} DILE_VT_FRAMEBUFFER_PROPERTY;

typedef struct DILE_VT_REGION_T {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} DILE_VT_REGION;

DILE_VT_HANDLE DILE_VT_Create(unsigned int videoWindowId);
DILE_VT_HANDLE DILE_VT_CreateEx(unsigned int videoWindowId, int bufferNum);
int DILE_VT_GetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE, int *pDumpLocation);
int DILE_VT_SetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE, int pDumpLocation);
int DILE_VT_SetVideoFrameOutputDeviceState(DILE_VT_HANDLE, uint32_t stateFlags, DILE_OUTPUTDEVICE_STATE *state);
int DILE_VT_GetCurrentVideoFrameBufferProperty(DILE_VT_HANDLE, DILE_VT_FRAMEBUFFER_PROPERTY *param_2, uint32_t *pIndexOfCurrentVideoFrameBuffer);
void DILE_VT_Destroy(DILE_VT_HANDLE);
int DILE_VT_SetVideoFrameOutputDeviceOutputRegion(DILE_VT_HANDLE, int pDumpLocation, DILE_VT_REGION* region);
int DILE_VT_WaitVsync(DILE_VT_HANDLE, int unk1, int unk2);

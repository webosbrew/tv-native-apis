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

DILE_VT_HANDLE DILE_VT_Create(unsigned int videoWindowId);
DILE_VT_HANDLE DILE_VT_CreateEx(unsigned int videoWindowId, int bufferNum);
int DILE_VT_GetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE, int *pDumpLocation);
int DILE_VT_SetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE, int pDumpLocation);
int DILE_VT_SetVideoFrameOutputDeviceState(DILE_VT_HANDLE, uint32_t stateFlags, DILE_OUTPUTDEVICE_STATE *state);
int DILE_VT_GetCurrentVideoFrameBufferProperty(DILE_VT_HANDLE, DILE_VT_FRAMEBUFFER_PROPERTY *param_2, uint32_t *pIndexOfCurrentVideoFrameBuffer);
void DILE_VT_Destroy(DILE_VT_HANDLE);
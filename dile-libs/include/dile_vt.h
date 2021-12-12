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

typedef enum DILE_VT_DUMP_LOCATION_TYPE_T
{
    DILE_VT_SCALER_OUTPUT = 0,
    DILE_VT_DISPLAY_OUTPUT = 1,
} DILE_VT_DUMP_LOCATION_TYPE_T;

typedef enum DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_T
{
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_PLANAR = 0,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_SEMI_PLANAR = 1,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_INTERLEAVED = 2,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_PLANAR = 3,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_SEMI_PLANAR = 4,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_INTERLEAVED = 5,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_PLANAR = 6,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_SEMI_PLANAR = 7,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_INTERLEAVED = 8,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_RGB = 9,
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_ARGB = 10,
} DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_T;

typedef struct DILE_VT_FRAMEBUFFER_PROPERTY_T
{
    DILE_VT_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_T pixelFormat;
    uint32_t stride;
    uint32_t width;
    uint32_t height;

    // List (per vfb) of lists (per plane) of physical memory offsets
    uint32_t **ptr;
} DILE_VT_FRAMEBUFFER_PROPERTY;

typedef struct DILE_VT_RECT_T
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} DILE_VT_RECT;

typedef struct DILE_VT_FRAMEBUFFER_CAPABILITY_T
{
    uint32_t numVfbs;
    uint32_t numPlanes;
} DILE_VT_FRAMEBUFFER_CAPABILITY;

typedef struct DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_LIMITATION_T
{
    DILE_VT_RECT maxResolution;
    uint8_t unk;
    uint8_t supportInputVideoDeInterlacing;
    uint8_t supportDisplayVideoDeInterlacing;
    uint8_t supportScaleUp;
    uint32_t scaleUpLimitWidth;
    uint32_t scaleUpLimitHeight;
    uint8_t supportScaleDown;
    uint8_t unk2;
    uint8_t unk3;
    uint8_t unk4;
    uint32_t scaleDownLimitWidth;
    uint32_t scaleDownLimitHeight;
} DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_LIMITATION;

typedef enum DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_FLAGS_T
{
    DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_NOFX = 0x00,
    DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_ENABLED = 0x01,
    DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_FREEZED = 0x02,
    DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_APPLIED_PQ = 0x04,
    DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_FRAMERATE_DIVIDE = 0x10,
} DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_STATE_FLAGS_T;

DILE_VT_HANDLE DILE_VT_Create(unsigned int videoWindowId);
DILE_VT_HANDLE DILE_VT_CreateEx(unsigned int videoWindowId, int bufferNum);
int DILE_VT_GetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE, int *pDumpLocation);
int DILE_VT_SetVideoFrameOutputDeviceDumpLocation(DILE_VT_HANDLE, int pDumpLocation);
int DILE_VT_SetVideoFrameOutputDeviceState(DILE_VT_HANDLE, uint32_t stateFlags, DILE_OUTPUTDEVICE_STATE *state);
int DILE_VT_GetCurrentVideoFrameBufferProperty(DILE_VT_HANDLE, DILE_VT_FRAMEBUFFER_PROPERTY *param_2, uint32_t *pIndexOfCurrentVideoFrameBuffer);
void DILE_VT_Destroy(DILE_VT_HANDLE);
int DILE_VT_SetVideoFrameOutputDeviceOutputRegion(DILE_VT_HANDLE, int pDumpLocation, DILE_VT_RECT* rect);
int DILE_VT_WaitVsync(DILE_VT_HANDLE, int unk1, int unk2);

int DILE_VT_GetVideoFrameBufferCapability(DILE_VT_HANDLE, DILE_VT_FRAMEBUFFER_CAPABILITY*);
int DILE_VT_GetAllVideoFrameBufferProperty(DILE_VT_HANDLE, DILE_VT_FRAMEBUFFER_CAPABILITY*, DILE_VT_FRAMEBUFFER_PROPERTY*);
int DILE_VT_GetVideoFrameOutputDeviceLimitation(DILE_VT_HANDLE, DILE_VT_VIDEO_FRAME_OUTPUT_DEVICE_LIMITATION*);

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct HAL_GAL_SURFACE_T
{
    uint32_t offset;
    uint32_t *physicalAddress;
    uint16_t pitch;
    uint16_t bpp;
    uint16_t width;
    uint16_t height;
    uint16_t pixelFormat;
    uint32_t paletteInfo[257];
    uint32_t property;
    uint32_t vendorData;
} HAL_GAL_SURFACE;

typedef struct HAL_GAL_RECT_T
{
    uint16_t x,y,w,h;
} HAL_GAL_RECT;

typedef struct HAL_GAL_DRAW_FLAGS_T
{
    uint32_t pflag;
} HAL_GAL_DRAW_FLAGS;

typedef struct HAL_GAL_DRAW_SETTINGS_T
{
    uint32_t srcblending1;
    uint32_t dstblending2;
    uint32_t dstcolor;
} HAL_GAL_DRAW_SETTINGS;

int HAL_GAL_CreateSurface(uint32_t width, uint32_t height, uint32_t pixelFormat, HAL_GAL_SURFACE *surface_info);
int HAL_GAL_DestroySurface(HAL_GAL_SURFACE *surface_info);
int HAL_GAL_CaptureFrameBuffer(HAL_GAL_SURFACE *surface_info);
int HAL_GAL_FillRectangle(HAL_GAL_SURFACE *surface_info, HAL_GAL_RECT *rect, uint32_t color, HAL_GAL_DRAW_FLAGS *flags, HAL_GAL_DRAW_SETTINGS *settings);
int HAL_GAL_Init();
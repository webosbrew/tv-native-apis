#pragma once

#include <stddef.h>
#include <stdint.h>

typedef int32_t HAL_GAL_PIXEL_FORMAT_T;
typedef int32_t HAL_GAL_RECT_T; //Pointer of Exitcode from createSurface() 
typedef int32_t HAL_GAL_DRAW_FLAGS_T;
typedef int32_t HAL_GAL_DRAW_SETTINGS_T;

typedef struct HAL_GAL_SURFACE_INFO
{
    int32_t offset;
    int32_t physicalAddress;
    int16_t pitch;
    int16_t bpp;
    int16_t width;
    int16_t hight;
    int32_t pixelFormat;
    int32_t paletteInfo;
    int32_t property;
    int32_t vendorData;
} HAL_GAL_SURFACE_INFO_T;


int HAL_GAL_CreateSurface(int16_t width, int16_t height, HAL_GAL_PIXEL_FORMAT_T pixfmt, HAL_GAL_SURFACE_INFO_T *info); //defaultcall pixfmt = 0
int HAL_GAL_FillRectangle(HAL_GAL_SURFACE_INFO_T *info, HAL_GAL_RECT_T *surfacereturn, int dummy, HAL_GAL_DRAW_FLAGS_T *drawflags, HAL_GAL_DRAW_SETTINGS_T *settings); //defaultcalls int dummy = 0, drawflags = 0, settings = 2(1-10 possible)-blending parameters?

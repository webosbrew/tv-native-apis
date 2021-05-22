#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct GM_SURFACE_T
{
    uint32_t dummy0;
    uint8_t* framebuffer;
    uint32_t dummy1[4 + 0x101];
    uint32_t surfaceID;
    uint32_t dummy3[2];
} GM_SURFACE;

int GM_CreateSurface(uint32_t width, uint32_t height, uint32_t dummy, GM_SURFACE* surface_info);
int GM_DestroySurface(uint32_t surfaceID);
int GM_CaptureGraphicScreen(uint32_t surfaceID, uint32_t* width, uint32_t* height);

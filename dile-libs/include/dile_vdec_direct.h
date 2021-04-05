#pragma once
#include <stddef.h>

int DILE_VDEC_DIRECT_Open(unsigned int fourcc, int width, int height, int tridType, int videoIndex);

int DILE_VDEC_DIRECT_SetCallback(void (*cb)(unsigned long long buffID));

int DILE_VDEC_DIRECT_Play(const void *data, size_t size);

int DILE_VDEC_DIRECT_PlayWithCallback(const void *data, size_t size, unsigned long long buffID);

int DILE_VDEC_DIRECT_Stop();

void DILE_VDEC_DIRECT_Close();
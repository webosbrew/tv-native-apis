#include "dile_vdec_direct.h"

int DILE_VDEC_DIRECT_Open(unsigned int fourcc, int width, int height, int tridType, int videoIndex) { return 0; }

int DILE_VDEC_DIRECT_SetCallback(void (*cb)(unsigned long long buffID)) { return 0; }

int DILE_VDEC_DIRECT_Play(const void *data, size_t size) { return 0; }

int DILE_VDEC_DIRECT_PlayWithCallback(const void *data, size_t size, unsigned long long buffID) { return 0; }

int DILE_VDEC_DIRECT_Stop() { return 0; }

void DILE_VDEC_DIRECT_Close() {}
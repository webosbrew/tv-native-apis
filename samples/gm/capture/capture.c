#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <gm.h>

GM_SURFACE surfaceInfo;

unsigned short nativeWidth = 0;
unsigned short nativeHeight = 0;
int captureWidth = 1920;
int captureHeight = 1080;
int framerate = 0;

int main(int argc, char *argv[])
{
    int res;

    // Usage: ./gm-capture [width height]
    if (argc >= 3) {
        captureWidth = atoi(argv[1]);
        captureHeight = atoi(argv[2]);
    }

    if (argc >= 4) {
        framerate = atoi(argv[3]);
    }

    if ((res = GM_GetGraphicResolution(&nativeWidth, &nativeHeight)) != 0) {
        fprintf(stderr, "[GM Capture Sample] GM_GetGraphicResolution Failed: %x\n", res);
        return 5;
    }

    fprintf(stderr, "[GM Capture Sample] Native resolution: %dx%d\n", nativeWidth, nativeHeight);
    fprintf(stderr, "[GM Capture Sample] Capture resolution: %dx%d\n", captureWidth, captureHeight);

    if (captureWidth > nativeWidth || captureHeight > nativeHeight) {
        fprintf(stderr, "[GM Capture Sample] Capture resolution can't exceed native resolution...\n");
        return 6;
    }

    if ((res = GM_CreateSurface(captureWidth, captureHeight, 0, &surfaceInfo)) != 0) {
        fprintf(stderr, "[GM Capture Sample] GM_CreateSurface Failed: %x\n", res);
        return 1;
    }

    do {
        if ((res = GM_CaptureGraphicScreen(surfaceInfo.surfaceID, &captureWidth, &captureHeight)) != 0) {
            fprintf(stderr, "[GM Capture Sample] GM_CaptureGraphicScreen Failed: %x\n", res);
            return 2;
        }

        if (write(1, surfaceInfo.framebuffer, captureWidth * captureHeight * 4) == -1) {
            perror("write failed");
            return 3;
        }

        if (framerate > 0) {
            usleep (1000000 / framerate);
        }
    } while (framerate > 0);

    fprintf(stderr, "[GM Capture Sample] Capture successful! (%dx%d)\n", captureWidth, captureHeight);

    if ((res = GM_DestroySurface(surfaceInfo.surfaceID)) != 0) {
        fprintf(stderr, "[GM Capture Sample] Surface destroy failed: %d\n", res);
        return 4;
    }

    return 0;
}

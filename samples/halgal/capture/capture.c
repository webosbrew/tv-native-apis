#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>

#include <halgal.h>
 
HAL_GAL_SURFACE surfaceInfo;
HAL_GAL_RECT rect;
HAL_GAL_DRAW_FLAGS flags;
HAL_GAL_DRAW_SETTINGS settings;

uint32_t color = 0;

bool app_quit = false;
int isrunning = 0;
int done;
int file;

int stop();
void sighandle(int sig);
int blend(unsigned char *result, unsigned char *fg, unsigned char *bg, int leng);

void sighandle(int signal)
{
    switch (signal)
    {
    case SIGINT:
        app_quit = true;
        done = stop();
        exit(done);
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    if (getenv("XDG_RUNTIME_DIR") == NULL)
    {
        setenv("XDG_RUNTIME_DIR", "/tmp/xdg", 1);
    }
    signal(SIGINT, sighandle);

    int captureWidth = 960;
    int captureHeight = 540;
    int framerate = 30;

    if ((done = HAL_GAL_Init()) != 0) {
        fprintf(stderr, "HAL_GAL_Init failed: %x\n", done);
        done = stop();
        return done;
    }
    fprintf(stderr, "HAL_GAL_Init done! Exit: %d\n", done);   

    if ((done = HAL_GAL_CreateSurface(captureWidth, captureHeight, 0, &surfaceInfo)) != 0) {
        fprintf(stderr, "HAL_GAL_CreateSurface failed: %x\n", done);
        done = stop();
        return done;
    }
    fprintf(stderr, "HAL_GAL_CreateSurface done! SurfaceID: %d\n", surfaceInfo.vendorData);
    fprintf(stderr, "offset: %p\n", surfaceInfo.offset);
    fprintf(stderr, "physicalAddress: %p\n", surfaceInfo.physicalAddress);
    fprintf(stderr, "pitch: %d\n", surfaceInfo.pitch);
    fprintf(stderr, "bpp: %d\n", surfaceInfo.bpp);
    fprintf(stderr, "width: %d\n", surfaceInfo.width);
    fprintf(stderr, "height: %d\n", surfaceInfo.height);
    fprintf(stderr, "pixelFormat: %d\n", surfaceInfo.pixelFormat);
    fprintf(stderr, "paletteInfo: %d\n", surfaceInfo.paletteInfo);
    fprintf(stderr, "property: %d\n", surfaceInfo.property);

    settings.srcblending1 = 2; //default = 2(1-10 possible) - blend? setting
    settings.dstblending2 = 0;
    settings.dstcolor = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = captureWidth;
    rect.h = captureHeight;

    flags.pflag = 0;

    if ((done = HAL_GAL_CaptureFrameBuffer(&surfaceInfo)) != 0) {
        fprintf(stderr, "HAL_GAL_CaptureFrameBuffer failed: %x\n", done);
        done = stop();
        return done;
    }
    fprintf(stderr, "HAL_GAL_CaptureFrameBuffer done! %x\n", done);

    isrunning = 1;

    size_t len; 
    char *addr;
    int fd;

    fd = open("/dev/gfx",2);
    if (fd < 0){
        fprintf(stderr, "gfx open fail result: %d\n", fd);
        done = stop();
        return done;

    }else{
        fprintf(stderr, "gfx open ok result: %d\n", fd);
    }
    
    len = surfaceInfo.property;
    if (len == 0){
        len = surfaceInfo.height * surfaceInfo.pitch;
    }

    addr = (char *) mmap(0, len, 3, 1, fd, surfaceInfo.offset);
    fprintf(stderr, "Surface length: %d || Virtual address: %p\nWriting to file..\n", len, &addr);

    FILE * pFile;
    pFile = fopen ("/tmp/myfile.bin","wb");
    if (pFile!=NULL)
    {
        fwrite(addr, len, sizeof(addr), pFile);
        fclose (pFile);
    }

    munmap(addr, len);
    done = close(fd);


    if (done != 0){
        fprintf(stderr, "gfx close fail result: %d\n", done);
        done = stop();
        return done;

    }else{
        fprintf(stderr, "gfx close ok result: %d\n", done);
    }

    fprintf(stderr, "Capture ended! (%dx%d)\n", captureWidth, captureHeight);

    done = stop();
    return done;
}

int stop()
{
    int done = 0;

    isrunning = 0;
    if ((done = HAL_GAL_DestroySurface(&surfaceInfo)) != 0) {
        fprintf(stderr, "HAL_GAL_DestroySurface failed: %d\n", done);
        return done;
    }
    fprintf(stderr, "HAL_GAL_DestroySurface done! %d\n", done);
    return done;
}

int blend(unsigned char *result, unsigned char *fg, unsigned char *bg, int leng)
{
    unsigned int alpha,iAlpha;
    int rIndex, gIndex, bIndex, aIndex;

    for (int i = 0; i < leng; i += 4){
        bIndex = i;
        gIndex = i + 1;
        rIndex = i + 2;
        aIndex = i + 3;

        alpha = fg[aIndex] + 1;
        iAlpha = 256 - fg[aIndex];
        
        result[bIndex] = (unsigned char)((alpha * fg[bIndex] + iAlpha * bg[bIndex]) >> 8);;
        result[gIndex] = (unsigned char)((alpha * fg[gIndex] + iAlpha * bg[gIndex]) >> 8);;
        result[rIndex] = (unsigned char)((alpha * fg[rIndex] + iAlpha * bg[rIndex]) >> 8);;
        result[aIndex] = 0xff;
    }
}
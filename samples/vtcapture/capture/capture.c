#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <vtcapture/vtCaptureApi_c.h>

//GM_SURFACE surfaceInfo;
VT_DRIVER driver;
VT_CALLER* callerid;
char* clientid;

int captureWidth = 1920;
int captureHeight = 1080;
int framerate = 0;


int main(int argc, char *argv[])
{
    int done;
    callerid = "testcall";
    clientid = "testclient";
    _LibVtCaptureProperties props = {0,0,0,0,0,0,0};
    fprintf(stderr, "Test (%dx%d)\n", captureWidth, captureHeight);

    driver = vtCapture_create();
    fprintf(stderr, "Driver created\n");

    done = vtCapture_init(driver, callerid, clientid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_init failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_init done!\n");

    done = vtCapture_preprocess(driver, callerid, props);
    if (done != 0) {
        fprintf(stderr, "vtCapture_preprocess failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_preprocess done!\n");


    do{
        done = vtCapture_process(driver, callerid);
        if (done != 0) {
            fprintf(stderr, "vtCapture_process failed: %x\n", done);
            return 1;
        }

        if (write(1, driver.ms_currentBuffIndex, captureWidth * captureHeight * 4) == -1) {
                perror("write failed");
                return 3;
        }
    }while(1==1);


    done = vtCapture_stop(driver, callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_stop failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_stop done!\n");

    done = vtCapture_postprocess(driver, callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_postprocess failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_postprocess done!\n");

    done = vtCapture_finalize(driver, callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_finalize failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_finalize done!\n");

    done = vtCapture_postprocess(driver, callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_postprocess failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_postprocess done!\n");
}
/* 
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
 */
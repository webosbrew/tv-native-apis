#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <vtcapture/vtCaptureApi_c.h>


const VT_CALLER_T caller[24] = "com.webos.tbtest.cap";

VT_DRIVER *driver;
VT_CLIENTID_T client[128] = "00";

_LibVtCaptureProperties props;

_LibVtCapturePlaneInfo plane;
int stride, x, y, w, h, xa, ya, wa, ha;
VT_REGION_T region;
VT_REGION_T activeregion;

_LibVtCaptureBufferInfo buff;
int addr0, addr1, size0, size1;

int isrunning = 0;

int stop();
int finalize();

int main(int argc, char *argv[])
{
    int done;
    int ex;
    //Capture properties for vtCapture_preprocess - _LibVtCaptureProperties
    int dumping = 1;
    int capturex = 0;
    int capturey = 0;
    int captureWidth = 1900;
    int captureHeight = 200;
    int framerate = 30;
    int buffer_count = 3;

    VT_DUMP_T dump = dumping;
    VT_LOC_T loc = {capturex, capturey};
    VT_RESOLUTION_T reg = {captureWidth, captureHeight};
    VT_FRAMERATE_T frm = framerate;
    VT_BUF_T buf_cnt = buffer_count;

    props.dump = dump;
    props.loc = loc;
    props.reg = reg;
    props.buf_cnt = buf_cnt;
    props.frm = framerate;
    //End of capture properties for vtCapture_preprocess - _LibVtCaptureProperties


    fprintf(stderr, "Starting vtCapture using API: %dx%d @%dFPS\n", captureWidth, captureHeight,framerate);
    fprintf(stderr, "Used settings: dump location: %d, x: %d, y: %d, w: %d, h: %d, buf_cnt: %d, framerate: %d\n", dumping, capturex, capturey, captureWidth, captureHeight, framerate, buffer_count);

    driver = vtCapture_create();
    fprintf(stderr, "Driver created!\n");

    done = vtCapture_init(driver, caller, client);
    if (done != 0) {
        fprintf(stderr, "vtCapture_init failed: %x\nQuitting...\n", done);
        ex = finalize();
        return ex;
    }
    fprintf(stderr, "vtCapture_init done!\nCaller_ID: %s Client ID: %s \n", caller, client);

    done = vtCapture_preprocess(driver, client, &props);
    if (done != 0) {
        fprintf(stderr, "vtCapture_preprocess failed: %x\nQuitting...\n", done);
        ex = finalize();
        return ex;
    }
    fprintf(stderr, "vtCapture_preprocess done!\n");

    //_LibVtCaptureCapabilityInfo *test;
    //done = vtCapture_capabilityInfo(driver, client, test);

    done = vtCapture_planeInfo(driver, client, &plane);
    if (done == 0 ) {
        stride = plane.stride;

        region = plane.planeregion;
        x = region.a, y = region.b, w = region.c, h = region.d;

        activeregion = plane.activeregion;
        xa = activeregion.a, ya = activeregion.b, wa = activeregion.c, ha = activeregion.d;
    }else{
        fprintf(stderr, "vtCapture_planeInfo failed: %x\nQuitting...\n", done);
        ex = finalize();
        return ex;
    }
    fprintf(stderr, "vtCapture_planeInfo done!\nstride: %d\nRegion: x: %d, y: %d, w: %d, h: %d\nActive Region: x: %d, y: %d w: %d h: %d\n", stride, x, y, w, h, xa, ya, wa, ha);

    done = vtCapture_process(driver, client);
    if (done == 0){
        isrunning = 1;
    }else{
        isrunning = 0;
        fprintf(stderr, "vtCapture_process failed: %x\nQuitting...\n", done);
        ex = finalize();
        return ex;
    }
    fprintf(stderr, "vtCapture_process done!\n");

    done = vtCapture_currentCaptureBuffInfo(driver, &buff);
    if (done == 0 ) {
        addr0 = buff.start_addr0;
        addr1 = buff.start_addr1;
        size0 = buff.size0;
        size1 = buff.size1;
    }else{
        fprintf(stderr, "vtCapture_currentCaptureBuffInfo failed: %x\nQuitting...\n", done);
        ex = finalize();
        return ex;
    }
    fprintf(stderr, "vtCapture_currentCaptureBuffInfo done!\naddr0: %p addr1: %p size0: %d size1: %d\n", addr0, addr1, size0, size1);
    //ToDo: Image processing

    done = stop();
    return done;
}

int stop()
{
    int done;

    isrunning = 0;
    done = vtCapture_stop(driver, client);
    if (done != 0)
    {
        fprintf(stderr, "vtCapture_stop failed: %x\nQuitting...\n", done);
        return done;
    }
    fprintf(stderr, "vtCapture_stop done!\n");
    done = finalize();
    return done;
}

int finalize()
{
    fprintf(stderr, "-- Quit called! --\n");
    int done;
    done = vtCapture_postprocess(driver, client);
        if (done == 0){
            fprintf(stderr, "Quitting: vtCapture_postprocess done!\n");
            done = vtCapture_finalize(driver, client);
            if (done == 0) {
                fprintf(stderr, "Quitting: vtCapture_finalize done!\n");
                vtCapture_release(driver);
                fprintf(stderr, "Quitting: Driver released!\n");
                memset(&client,0,127);
                fprintf(stderr, "Quitting!\n");
                return -1;
            }
            fprintf(stderr, "Quitting: vtCapture_finalize failed: %x\n", done);
        }
    vtCapture_finalize(driver, client);
    vtCapture_release(driver);
    fprintf(stderr, "Quitting with errors: %x!\n", done);
    return 0;
}
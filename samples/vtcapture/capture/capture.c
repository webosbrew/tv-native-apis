#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <vtcapture/vtCaptureApi_c.h>

//GM_SURFACE surfaceInfo;
VT_DRIVER driver;
_LibVtCaptureProperties props;

int captureWidth = 1920;
int captureHeight = 1080;
int capturex = 0;
int capturey = 0;
//char* framerate = "0";
//char* dump = "0";

int main(int argc, char *argv[])
{
    int done;
 //   VT_CALLER_T callerid = "testcall";
 //   VT_CLIENTID_T clientid = "testclient";
    VT_CALLER_T callerid;
    VT_CLIENTID_T clientid;
    VT_REGION_T reg = {capturex, capturey, captureWidth, captureHeight};
 //   VT_DUMP_T dum = dump;
 //   VT_FRAMERATE_T fra = framerate;
    props.reg = reg;
 //   props.framerate = framerate;
 //   props.dump = dum;
    fprintf(stderr, "Test (%dx%d)\n", captureWidth, captureHeight);

    driver = vtCapture_create();
    fprintf(stderr, "Driver created\n");

    done = vtCapture_init(driver, &callerid, &clientid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_init failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_init done!\n");

    done = vtCapture_preprocess(driver, &callerid, &props);
    if (done != 0) {
        fprintf(stderr, "vtCapture_preprocess failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_preprocess done!\n");


    do{
        done = vtCapture_process(driver, &callerid);
        if (done != 0) {
            fprintf(stderr, "vtCapture_process failed: %x\n", done);
            return 1;
        }

        if (write(1, driver.ms_currentBuffIndex, captureWidth * captureHeight * 4) == -1) {
                perror("write failed");
                return 3;
        }
    }while(1==1);


    done = vtCapture_stop(driver, &callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_stop failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_stop done!\n");

    done = vtCapture_postprocess(driver, &callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_postprocess failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_postprocess done!\n");

    done = vtCapture_finalize(driver, &callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_finalize failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_finalize done!\n");

    done = vtCapture_postprocess(driver, &callerid);
    if (done != 0) {
        fprintf(stderr, "vtCapture_postprocess failed: %x\n", done);
        return 1;
    }
    fprintf(stderr, "vtCapture_postprocess done!\n");
}
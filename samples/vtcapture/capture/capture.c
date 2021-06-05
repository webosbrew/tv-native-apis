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
char *addr0, *addr1;
int size0, size1;

int isrunning = 0;

void NV21_TO_RGB24(unsigned char *yuyv, unsigned char *rgb, int width, int height);
int stop();
int finalize();

int main(int argc, char *argv[])
{
    int done;
    int ex;
    //Capture properties for vtCapture_preprocess - _LibVtCaptureProperties
    int dumping = 2;
    int capturex = 0;
    int capturey = 0;
    int captureWidth = 1280;
    int captureHeight = 720;
    int framerate = 30;
    int buffer_count = 1;

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

    sleep(2);
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

 //   char *rgb1;
//    char *rgb2;

  //  char *yuyv1 = addr0;
 //   char *yuyv2 = addr1;

 //   NV21_TO_RGB24(yuyv1, rgb1, w, h);
 //   NV21_TO_RGB24(yuyv2, rgb2, w, h);

    fprintf(stderr, "addr0: %p buff.addr0: %p sizeaddr0: %d sizebuff.addr0: %d\n", addr0, buff.start_addr0, sizeof(*addr0), sizeof(*buff.start_addr0));
 //   fprintf(stderr, "rgb1: %p addr0: %p sizergb1: %d sizeaddr0: %d\n", rgb1, addr0, sizeof(*rgb1), sizeof(*addr0));
    FILE * pFile;
    pFile = fopen ("/tmp/myfile.bin","wb");
    if (pFile!=NULL)
    {
        fwrite(addr0, size0, sizeof(addr0), pFile);
        fwrite(addr1, size1, sizeof(addr0), pFile);
        fclose (pFile);
    }

    done = stop();
    return done;
}

//Credits: https://www.programmersought.com/article/18954751423/
void NV21_TO_RGB24(unsigned char *yuyv, unsigned char *rgb, int width, int height)
{
        const int nv_start = width * height ;
        int  index = 0, rgb_index = 0;
        uint8_t y, u, v;
        int r, g, b, nv_index = 0,i, j;
 
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j ++){
                //nv_index = (rgb_index / 2 - width / 2 * ((i + 1) / 2)) * 2;
                nv_index = i / 2  * width + j - j % 2;
 
                y = yuyv[rgb_index];
                u = yuyv[nv_start + nv_index ];
                v = yuyv[nv_start + nv_index + 1];
 
                r = y + (140 * (v-128))/100;  //r
                g = y - (34 * (u-128))/100 - (71 * (v-128))/100; //g
                b = y + (177 * (u-128))/100; //b
 
                if(r > 255)   r = 255;
                if(g > 255)   g = 255;
                if(b > 255)   b = 255;
                if(r < 0)     r = 0;
                if(g < 0)     g = 0;
                if(b < 0)     b = 0;
 
                index = rgb_index % width + (height - i - 1) * width;
                //rgb[index * 3+0] = b;
                //rgb[index * 3+1] = g;
                //rgb[index * 3+2] = r;
 
                                 //Invert the image
                //rgb[height * width * 3 - i * width * 3 - 3 * j - 1] = b;
                //rgb[height * width * 3 - i * width * 3 - 3 * j - 2] = g;
                //rgb[height * width * 3 - i * width * 3 - 3 * j - 3] = r;
 
                                 //Front image
                rgb[i * width * 3 + 3 * j + 0] = b;
                rgb[i * width * 3 + 3 * j + 1] = g;
                rgb[i * width * 3 + 3 * j + 2] = r;
 
                rgb_index++;
            }
        }
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
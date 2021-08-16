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
#include <vtcapture/vtCaptureApi_c.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>
 

//HAL_GAL 
HAL_GAL_SURFACE surfaceInfo;
HAL_GAL_RECT rect;
HAL_GAL_DRAW_FLAGS flags;
HAL_GAL_DRAW_SETTINGS settings;

uint32_t color = 0;

//vtCapture
const VT_CALLER_T caller[24] = "com.webos.tbtest.cap";

VT_DRIVER *driver;
VT_CLIENTID_T client[128] = "00";

_LibVtCaptureProperties props;
_LibVtCapturePlaneInfo plane;

VT_REGION_T region;
VT_REGION_T activeregion;

_LibVtCaptureBufferInfo buff;
char *addr0, *addr1;
int size0, size1;
char *rgbout;

//All
int stride, x, y, w, h, xa, ya, wa, ha;
bool app_quit = false;
int isrunning = 0;
int done;
int ex;
int file;


int stop();
int stop_hal();
int stop_vt();
int finalize();
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
//    if (getenv("XDG_RUNTIME_DIR") == NULL)
//    {
//        setenv("XDG_RUNTIME_DIR", "/tmp/xdg", 1);
//   }
    signal(SIGINT, sighandle);

    int dumping = 2;
    int capturex = 0;
    int capturey = 0;
    int captureWidth = 960; //both
    int captureHeight = 540; //both
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

    if ((done = HAL_GAL_Init()) != 0) {
        fprintf(stderr, "HAL_GAL_Init failed: %x\n", done);
        done = stop();
        return done;
    }
    fprintf(stderr, "HAL_GAL_Init done! Exit: %d\n", done);   

  //  memset(&surfaceInfo,0,1096);

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
        fprintf(stderr, "HAL_GAL: gfx open fail result: %d\n", fd);
        done = stop();
        return done;

    }else{
        fprintf(stderr, "HAL_GAL: gfx open ok result: %d\n", fd);
    }

    len = surfaceInfo.property;
    if (len == 0){
        len = surfaceInfo.height * surfaceInfo.pitch;
    }

    fprintf(stderr, "HAL_GAL: Surface length: %d || Virtual address: %p\n", len, &addr);


    fprintf(stderr, "Starting vtCapture using API: %dx%d @%dFPS\n", captureWidth, captureHeight,framerate);
    fprintf(stderr, "Used settings: dump location: %d, x: %d, y: %d, w: %d, h: %d, framerate: %d,  buf_cnt: %d\n", dumping, capturex, capturey, captureWidth, captureHeight, framerate, buffer_count);

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
        ex += stop_hal();
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
        ex += stop_hal();
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


    int comsize;  
    comsize = size0+size1;
    char *combined = (char *) malloc(comsize);

    IplImage *halImg = cvCreateImage(cvSize(captureWidth,captureHeight),IPL_DEPTH_8U,4);
    IplImage *combImg = cvCreateImage(cvSize(captureWidth,captureHeight),IPL_DEPTH_8U,4);

    IplImage *vtYuv = cvCreateImage(cvSize(w,(h+h/2)),IPL_DEPTH_8U,1);
    IplImage *vtRgba = cvCreateImage(cvSize(w,h),IPL_DEPTH_8U,4);

    do {
        memcpy(combined, addr0, size0);
        memcpy(combined+size0, addr1, size1);
        if(vtYuv){
            memcpy(vtYuv->imageData,combined,comsize);
            cvCvtColor(vtYuv, vtRgba, CV_YUV2RGBA_NV21);
        }else{
            fprintf(stderr, "ERROR: Create vtYuv IplImage failed!\n");
        }

        if ((done = HAL_GAL_CaptureFrameBuffer(&surfaceInfo)) != 0) {
            fprintf(stderr, "HAL_GAL_CaptureFrameBuffer failed: %x\n", done);
            done = stop();
            return done;
        }
        addr = (char *) mmap(0, len, 3, 1, fd, surfaceInfo.offset);

        if(halImg){
            memcpy(halImg->imageData,addr,len);
        }else{
            fprintf(stderr, "ERROR: Create halImg IplImage failed!\n");
        }
        munmap(addr, len);

        if(combImg){
            blend(combImg->imageData, halImg->imageData, vtRgba->imageData, len);
        }else{
            fprintf(stderr, "ERROR: Create combImg IplImage failed!\n");
        }
        cvEncodeImage(".jpg", combImg, 0);
    //    cvSaveImage("/tmp/comb.png", combImg, 0);



        if (write(1, combImg->imageData, 1996800) == -1) {
                perror("write failed");
                done = stop();
                return done;
        }
     
    } while (framerate > 0 || app_quit == false);


    cvReleaseImage(&halImg);
    cvReleaseImage(&combImg);
    cvReleaseImage(&vtYuv);
    cvReleaseImage(&vtRgba);
    free(combined);
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
//    do {

    
/*     char *addr1 = (char *) malloc(surfaceInfo.property); 
    addr1 = mmap(0, surfaceInfo.property, file, 3, 1, surfaceInfo.offset);

    char *dst = (char *) malloc(surfaceInfo.property);

    memcpy(&dst, &addr1, len);



    memcpy(dst, addr1, len); */

/*         if (write(1, &addr, surfaceInfo.property) == -1) {
            perror("write failed");
            done = stop();
            return done;
        } */




//        if (framerate > 0) {
//            usleep (1000000 / framerate);
//        }
//    } while (framerate > 0 || app_quit == false);

/*     fprintf(stderr, "Capture ended! (%dx%d)\n", captureWidth, captureHeight);
    close(file);
    fprintf(stderr, "1Capture ended! (%dx%d)\n", captureWidth, captureHeight);
    free(dst);
    //free(addr1);
    fprintf(stderr, "2Capture ended! (%dx%d)\n", captureWidth, captureHeight); */
}

int stop(){
    fprintf(stderr, "-- Quit called! --\n");
    int done = 0;
    done = stop_vt();
    done += stop_hal();
    return done;
}

int stop_vt(){
    
    int done;

    isrunning = 0;
    done = vtCapture_stop(driver, client);
    if (done != 0)
    {
        fprintf(stderr, "vtCapture_stop failed: %x\nQuitting...\n", done);
        done = finalize();
        return done;
    }
    fprintf(stderr, "vtCapture_stop done!\n");
    done = finalize();
    return done;
}

int stop_hal()
{
    int done = 0;

//    close(file);
    isrunning = 0;
    if ((done = HAL_GAL_DestroySurface(&surfaceInfo)) != 0) {
        fprintf(stderr, "Quitting: HAL_GAL_DestroySurface failed: %d\n", done);
        return done;
    }
    fprintf(stderr, "Quitting: HAL_GAL_DestroySurface done! %d\n", done);
    return done;
}

int finalize()
{
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
                return 0;
            }
            fprintf(stderr, "Quitting: vtCapture_finalize failed: %x\n", done);
        }
    vtCapture_finalize(driver, client);
    vtCapture_release(driver);
    fprintf(stderr, "Quitting with errors: %x!\n", done);
    return 1;
}

int blend(unsigned char *result, unsigned char *fg, unsigned char *bg, int leng)
{
    int rIndex, gIndex, bIndex, aIndex;
    unsigned int alpha,iAlpha;
    int end;

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
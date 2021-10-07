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
#include <jpeglib.h>
#include <halgal.h>
#include <vtcapture/vtCaptureApi_c.h>

#define CRLF() fwrite("\r\n", 1, 2, stdout)

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
char *gesamt;
int comsize;  
char *combined;
int rgbasize;
int rgbsize;   
char *rgbout;   
char *hal;

//All
int stride, x, y, w, h, xa, ya, wa, ha;
bool app_quit = false;
int isrunning = 0;
int done;
int ex;
int file;

int rIndex, gIndex, bIndex, aIndex;
unsigned int alpha,iAlpha;

size_t len; 
char *addr;
int fd;

int stop();
int stop_hal();
int stop_vt();
int finalize();
void sighandle(int sig);
int blend(unsigned char *result, unsigned char *fg, unsigned char *bg, int leng);
void NV21_TO_RGBA(unsigned char *yuyv, unsigned char *rgba, int width, int height);
void write_JPEG_stdout(int quality);

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

    int dumping = 2;
    int capturex = 0;
    int capturey = 0;
    int captureWidth = 360; //both
    int captureHeight = 180; //both
    int framerate = 15;
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
        ex += stop_hal();
        return ex;
    }
    fprintf(stderr, "vtCapture_init done!\nCaller_ID: %s Client ID: %s \n", caller, client);

    done = vtCapture_preprocess(driver, client, &props);
    if (done != 0) {
        fprintf(stderr, "vtCapture_preprocess failed: %x\nQuitting...\n", done);
        ex = finalize();
        ex += stop_hal();
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
        ex += stop_hal();
        return ex;
    }
    fprintf(stderr, "vtCapture_currentCaptureBuffInfo done!\naddr0: %p addr1: %p size0: %d size1: %d\n", addr0, addr1, size0, size1);


    comsize = size0+size1;
    combined = (char *) malloc(comsize);

    rgbasize = sizeof(combined)*stride*h*4;
    rgbsize = sizeof(combined)*stride*h*3;   
    rgbout = (char *) malloc(rgbasize);   
    gesamt = (char *) malloc(len);
    hal = (char *) malloc(len);

    addr = (char *) mmap(0, len, 3, 1, fd, surfaceInfo.offset);
    int framecount = 0;

    do {
        
        memcpy(combined, addr0, size0);
        memcpy(combined+size0, addr1, size1);

        NV21_TO_RGBA(combined, rgbout, stride, h);

        if ((done = HAL_GAL_CaptureFrameBuffer(&surfaceInfo)) != 0) {
            fprintf(stderr, "HAL_GAL_CaptureFrameBuffer failed: %x\n", done);
            done = stop();
            return done;
        }

        memcpy(hal,addr,len);

        blend(gesamt, hal, rgbout, len);

        write_JPEG_stdout(85);
        
        if (framerate > 0) {
            usleep (1000000 / framerate);
        } 

    } while (framerate > 0 || app_quit == false);

    done = stop();
    return done;

}

int stop(){
    fprintf(stderr, "-- Quit called! --\n");

    int done;
    if(isrunning == 1){
        munmap(addr, len);
        free(combined);
        free(rgbout);
        free(gesamt);
        done = close(fd);
        if (done != 0){
            fprintf(stderr, "gfx close fail result: %d\n", done);
        }else{
            fprintf(stderr, "gfx close ok result: %d\n", done);
        }
    }
    done = 0;
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

int stop_hal(){
    int done = 0;
    isrunning = 0;

    if ((done = HAL_GAL_DestroySurface(&surfaceInfo)) != 0) {
        fprintf(stderr, "Quitting: HAL_GAL_DestroySurface failed: %d\n", done);
        return done;
    }
    fprintf(stderr, "Quitting: HAL_GAL_DestroySurface done! %d\n", done);
    return done;
}

int finalize(){
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

int blend(unsigned char *result, unsigned char *fg, unsigned char *bg, int leng){
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

//Credits: https://www.programmersought.com/article/18954751423/
void NV21_TO_RGBA(unsigned char *yuyv, unsigned char *rgba, int width, int height){
        const int nv_start = width * height ;
        int  index = 0, rgb_index = 0;
        uint8_t y, u, v;
        int r, g, b, nv_index = 0, i, j;
        int a = 255;
 
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j ++){

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
 
                rgba[i * width * 4 + 4 * j + 0] = b;
                rgba[i * width * 4 + 4 * j + 1] = g;
                rgba[i * width * 4 + 4 * j + 2] = r;   
                rgba[i * width * 4 + 4 * j + 3] = a;               
                rgb_index++;

            }
        }
}

//Credits: https://github.com/webosbrew/tv-native-apis/blob/main/samples/vt/capture/capture.c
void write_JPEG_stdout(int quality){

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
    int row_stride;          /* physical row width in image buffer */

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = NULL;

    jpeg_mem_dest(&cinfo, &jpegBuf, &jpegSize);

    cinfo.image_width = w; /* image width and height, in pixels */
    cinfo.image_height = h;
    cinfo.input_components = 4;          /* # of color components per pixel */
    cinfo.in_color_space = JCS_EXT_BGRX; /* colorspace of input image */

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

    jpeg_start_compress(&cinfo, TRUE);

    row_stride = stride * 4; /* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &gesamt[cinfo.next_scanline * row_stride];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);

    printf("--myboundary");
    CRLF();
    printf("Content-Type: image/jpeg");
    CRLF();
    printf("Content-Length: %d", jpegSize);
    CRLF();
    CRLF();
    fwrite(jpegBuf, 1, jpegSize, stdout);
    CRLF();

    jpeg_destroy_compress(&cinfo);
    free(jpegBuf);
}
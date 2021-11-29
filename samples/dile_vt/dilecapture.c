#include <dile_vt.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <fcntl.h>

#include <jpeglib.h>

#define LOG(fmt, ...) fprintf(stderr, "[DILE_VT Capture] " fmt "\n", ##__VA_ARGS__)
enum CAPTURE_VT_DUMP_LOCATION_TYPE_T {
    CAPTURE_VT_SCALER_OUTPUT = 0x0,
    CAPTURE_VT_DISPLAY_OUTPUT = 0x1,
};

void dump_state(DILE_OUTPUTDEVICE_STATE* state) {
    LOG("=== Dumping state (%08x) ===", state);
    LOG("enabled:   %d", state->enabled);
    LOG("freezed:   %d", state->freezed);
    LOG("appliedPQ: %d", state->appliedPQ);
    LOG("unknown:   %d", state->unknown);
    LOG("framerate: %d", state->framerate);
}

void dump_fvbprop(DILE_VT_FRAMEBUFFER_PROPERTY* vfb) {
    LOG("=== Dumping VFB props (%08x) ===", vfb);
    LOG("pixelFormat: %d", vfb->pixelFormat);
    LOG("stride:      %d", vfb->stride);
    LOG("width:       %d", vfb->width);
    LOG("height:      %d", vfb->height);
    LOG("ptr:         %08x", vfb->ptr);

}

void write_JPEG_stdout(uint8_t* buffer, uint32_t width, uint32_t height, int quality)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    int row_stride;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = NULL;

    jpeg_mem_dest(&cinfo, &jpegBuf, &jpegSize);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_EXT_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    row_stride = width * 3;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &buffer[(cinfo.next_scanline) * row_stride];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    printf("--myboundary\r\n");
    printf("Content-Type: image/jpeg\r\n");
    printf("Content-Length: %d\r\n\r\n", jpegSize);
    fwrite(jpegBuf, 1, jpegSize, stdout);
    printf("\r\n");
    jpeg_destroy_compress(&cinfo);

    free(jpegBuf);
}

double millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
}

int main(int argc, char** argv) {
    LOG("Hello there!");

    DILE_VT_HANDLE vth = DILE_VT_Create(0);
    if (vth == NULL) {
        LOG("vth init failed");
        return 1;
    }

    LOG(" -> SetVFODDumpLocation(): %d", DILE_VT_SetVideoFrameOutputDeviceDumpLocation(vth, CAPTURE_VT_DISPLAY_OUTPUT));

    DILE_VT_REGION region = {0, 0, 2880/3/4, 560/4};
    LOG(" -> SetVFODOutputRegion(): %d", DILE_VT_SetVideoFrameOutputDeviceOutputRegion(vth, CAPTURE_VT_DISPLAY_OUTPUT, &region));

    DILE_OUTPUTDEVICE_STATE output_state;
    output_state.enabled = 0;
    output_state.freezed = 0;
    output_state.appliedPQ = 0;
    output_state.framerate = 1;
    dump_state(&output_state);
    LOG(" -> SetVFODState(): %d", DILE_VT_SetVideoFrameOutputDeviceState(vth, 0x10, &output_state));
    LOG(" -> SetVFODState(): %d", DILE_VT_SetVideoFrameOutputDeviceState(vth, 0x02, &output_state));

    dump_state(&output_state);

    uint32_t idx = 0;
    DILE_VT_FRAMEBUFFER_PROPERTY vfbprop;
    uint32_t* ptrs[32] = {0};
    uint32_t** p1 = &ptrs;

    vfbprop.ptr = &p1;
    LOG(" -> GetCurrentVFBProperty(): %d", DILE_VT_GetCurrentVideoFrameBufferProperty(vth, &vfbprop, &idx));
    LOG("idx: %d", idx);
    dump_fvbprop(&vfbprop);

    int fd = 0;
    fd = open("/dev/mem", O_RDWR|O_SYNC);
    uint8_t* vfbs[16] = {0, 0,0,0,0,0,0,0,0,0,0,0,0,0};


    int frame = 0;
    double start = millis();
    while (1) {
        /*
        FILE* pFile = fopen("/tmp/dump.bin","wb");
        fwrite(memory, vfbprop.stride * vfbprop.height, 1, pFile);
        fclose(pFile);
        */

        DILE_VT_WaitVsync(vth, 0, 0);

        output_state.freezed = 1;
        DILE_VT_SetVideoFrameOutputDeviceState(vth, 2, &output_state);

        DILE_VT_GetCurrentVideoFrameBufferProperty(vth, &vfbprop, &idx);

        if (vfbs[idx] == 0)
            vfbs[idx] = (uint32_t *)mmap(0, vfbprop.stride * vfbprop.height, PROT_READ, MAP_SHARED, fd, ptrs[0]);

        write_JPEG_stdout(vfbs[idx], vfbprop.stride/3, vfbprop.height, 80);
        output_state.freezed = 0;
        DILE_VT_SetVideoFrameOutputDeviceState(vth, 2, &output_state);
        frame += 1;
        if (frame % 30 == 0) {
            LOG("DONE! %.5f", 1000 * frame / (millis() - start));
        }
    }

    DILE_VT_Destroy(vth);
    return 0;
}

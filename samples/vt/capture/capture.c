#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL.h>
#include <SDL_opengles2.h>
#include <jpeglib.h>
#include <vt/vt_openapi.h>

SDL_Window *sdl_window;
SDL_GLContext egl;
VT_VIDEO_WINDOW_ID window_id;
VT_RESOURCE_ID resource_id;
VT_CONTEXT_ID context_id;
GLuint texture_id = 0;
GLuint offscreen_fb = 0;

GLubyte *pixels = NULL;

bool app_quit = false;
bool capture_initialized = false;
bool vt_available = false;

VT_RESOLUTION_T resolution = {192, 108};

void write_JPEG_stdout(int quality);

int capture_initialize();
void capture_terminate();
void capture_onevent(VT_EVENT_TYPE_T type, void *data, void *user_data);

int main(int argc, char *argv[])
{
    // Create an SDL Window
    sdl_window = SDL_CreateWindow("Capture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

    if (sdl_window == NULL)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create an EGL context. VT will use EGL so this is important
    egl = SDL_GL_CreateContext(sdl_window);
    glGenFramebuffers(1, &offscreen_fb);
    SDL_assert(offscreen_fb);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: multipart/x-mixed-replace; boundary=myboundary\r\n");
    printf("Cache-Control: no-cache\r\n");
    printf("Connection: close\r\n");
    printf("Pragma: no-cache\r\n");
    printf("\r\n");

    int ret;
    if ((ret = capture_initialize()) != 0)
    {
        return ret;
    }
    pixels = (GLubyte *)calloc(resolution.w * resolution.h, 4 * sizeof(GLubyte));

    while (!app_quit)
    {

        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_QUIT:
                app_quit = true;
                break;
            case SDL_KEYUP:
                switch (evt.key.keysym.scancode)
                {
                case SDL_WEBOS_SCANCODE_BACK:
                    app_quit = true;
                    break;
                }
            }
        }
    }

    capture_terminate();
    glDeleteFramebuffers(1, &offscreen_fb);
    free(pixels);

    SDL_GL_DeleteContext(egl);
    SDL_DestroyWindow(sdl_window);
    return 0;
}

int capture_initialize()
{
    window_id = VT_CreateVideoWindow(0);
    if (window_id == -1)
    {
        fprintf(stderr, "[Capture Sample] VT_CreateVideoWindow Failed\n");
        return -1;
    }
    fprintf(stderr, "[Capture Sample] window_id=%d\n", window_id);

    if (VT_AcquireVideoWindowResource(window_id, &resource_id) != VT_OK)
    {
        fprintf(stderr, "[Capture Sample] VT_AcquireVideoWindowResource Failed\n");
        return -1;
    }
    fprintf(stderr, "[Capture Sample] resource_id=%d\n", resource_id);

    context_id = VT_CreateContext(resource_id, 2);
    if (context_id == -1)
    {
        fprintf(stderr, "[Capture Sample] VT_CreateContext Failed\n");
        VT_ReleaseVideoWindowResource(resource_id);
        return -1;
    }
    fprintf(stderr, "[Capture Sample] context_id=%d\n", context_id);

    VT_SetTextureResolution(context_id, &resolution);
    // VT_GetTextureResolution(context_id, &resolution);

    if (VT_SetTextureSourceRegion(context_id, VT_SOURCE_REGION_MAX) != VT_OK)
    {
        fprintf(stderr, "[Capture Sample] VT_SetTextureSourceRegion Failed\n");
        VT_DeleteContext(context_id);
        VT_ReleaseVideoWindowResource(resource_id);
        return -1;
    }

    if (VT_RegisterEventHandler(context_id, &capture_onevent, NULL) != VT_OK)
    {
        fprintf(stderr, "[Capture Sample] VT_RegisterEventHandler Failed\n");
        VT_DeleteContext(context_id);
        VT_ReleaseVideoWindowResource(resource_id);
        return -1;
    }
    capture_initialized = true;
    return 0;
}

void capture_terminate()
{
    capture_initialized = false;

    if (texture_id != 0 && glIsTexture(texture_id))
    {
        VT_DeleteTexture(context_id, texture_id);
    }

    if (VT_UnRegisterEventHandler(context_id) != VT_OK)
    {
        fprintf(stderr, "[Capture Sample] VT_UnRegisterEventHandler error!\n");
    }
    VT_DeleteContext(context_id);
    VT_ReleaseVideoWindowResource(resource_id);
}

void capture_acquire()
{
    static Uint32 fps_ticks = 0, framecount = 0;
    VT_OUTPUT_INFO_T output_info;
    if (vt_available)
    {
        if (capture_initialized)
        {

            if (texture_id != 0 && glIsTexture(texture_id))
            {
                VT_DeleteTexture(context_id, texture_id);
            }

            VT_STATUS_T vtStatus = VT_GenerateTexture(resource_id, context_id, &texture_id, &output_info);
            if (vtStatus == VT_OK)
            {
                int width = resolution.w, height = resolution.h;

                glBindFramebuffer(GL_FRAMEBUFFER, offscreen_fb);

                glBindTexture(GL_TEXTURE_2D, texture_id);

                //Bind the texture to your FBO
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

                //Test if everything failed
                GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
                if (status != GL_FRAMEBUFFER_COMPLETE)
                {
                    fprintf(stderr, "failed to make complete framebuffer object %x", status);
                }

                glViewport(0, 0, width, height);
                if (pixels)
                {
                    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
                    write_JPEG_stdout(95);
                }

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
            else
            {
                texture_id = 0;
            }
        }
        vt_available = false;
    }

    Uint32 end_ticks = SDL_GetTicks();
    if ((end_ticks - fps_ticks) >= 1000)
    {
        fprintf(stderr, "capture speed %d FPS\n", (int)(framecount * 1000.0 / (end_ticks - fps_ticks)));
        fps_ticks = end_ticks;
        framecount = 0;
    }
    else
    {
        framecount++;
    }
}

void capture_onevent(VT_EVENT_TYPE_T type, void *data, void *user_data)
{
    switch (type)
    {
    case VT_AVAILABLE:
        fprintf(stderr, "VT_AVAILABLE received: data=%p\n", data);
        vt_available = true;
        capture_acquire();
        break;
    case VT_UNAVAILABLE:
        fprintf(stderr, "VT_UNAVAILABLE received\n");
        break;
    case VT_RESOURCE_BUSY:
        fprintf(stderr, "VT_RESOURCE_BUSY received\n");
        break;
    default:
        fprintf(stderr, "UNKNOWN event received\n");
        break;
    }
}

void write_JPEG_stdout(int quality)
{
    /* This struct contains the JPEG compression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   * It is possible to have several such structures, representing multiple
   * compression/decompression processes, in existence at once.  We refer
   * to any one struct (and its associated working data) as a "JPEG object".
   */
    struct jpeg_compress_struct cinfo;
    /* This struct represents a JPEG error handler.  It is declared separately
   * because applications often want to supply a specialized error handler
   * (see the second half of this file for an example).  But here we just
   * take the easy way out and use the standard error handler, which will
   * print a message on stderr and call exit() if compression fails.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
    struct jpeg_error_mgr jerr;
    /* More stuff */

    JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
    int row_stride;          /* physical row width in image buffer */

    /* Step 1: allocate and initialize JPEG compression object */

    /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
    cinfo.err = jpeg_std_error(&jerr);
    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = NULL;

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */

    /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
    jpeg_mem_dest(&cinfo, &jpegBuf, &jpegSize);

    /* Step 3: set parameters for compression */

    /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
    cinfo.image_width = resolution.w; /* image width and height, in pixels */
    cinfo.image_height = resolution.h;
    cinfo.input_components = 4;          /* # of color components per pixel */
    cinfo.in_color_space = JCS_EXT_RGBX; /* colorspace of input image */
    /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
    jpeg_set_defaults(&cinfo);
    /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

    /* Step 4: Start compressor */

    /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
    jpeg_start_compress(&cinfo, TRUE);

    /* Step 5: while (scan lines remain to be written) */
    /*           jpeg_write_scanlines(...); */

    /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
    row_stride = resolution.w * 4; /* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height)
    {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
        row_pointer[0] = &pixels[(resolution.h - cinfo.next_scanline - 1) * row_stride];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    /* Step 6: Finish compression */

    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */

    printf("--myboundary\r\n");
    printf("Content-Type: image/jpeg\r\n");
    printf("Content-Length: %d\r\n", jpegSize);
    printf("\r\n");
    fwrite(jpegBuf, 1, jpegSize, stdout);
    printf("\r\n");

    /* Step 7: release JPEG compression object */

    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(&cinfo);

    /* And we're done! */
    // Free jpeg memory
    free(jpegBuf);
}
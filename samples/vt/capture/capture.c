#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <vt/vt_openapi.h>

SDL_Window *sdl_window;
SDL_GLContext egl;
VT_VIDEO_WINDOW_ID window_id;
VT_RESOURCE_ID resource_id;
VT_CONTEXT_ID context_id;

int app_quit = 0;

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

    egl = SDL_GL_CreateContext(sdl_window);

    int ret;
    if ((ret = capture_initialize()) != 0)
    {
        return ret;
    }

    while (!app_quit)
    {

        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_QUIT:
                app_quit = 1;
                break;
            case SDL_KEYUP:
                switch (evt.key.keysym.scancode)
                {
                case SDL_WEBOS_SCANCODE_BACK:
                    app_quit = 1;
                    break;
                }
            }
        }
    }

    capture_terminate();
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
    printf("[Capture Sample] window_id=%d\n", window_id);

    if (VT_AcquireVideoWindowResource(window_id, &resource_id) != VT_OK)
    {
        fprintf(stderr, "[Capture Sample] VT_AcquireVideoWindowResource Failed\n");
        return -1;
    }
    printf("[Capture Sample] resource_id=%d\n", resource_id);

    context_id = VT_CreateContext(resource_id, 2);
    if (context_id == -1)
    {
        fprintf(stderr, "[Capture Sample] VT_CreateContext Failed\n");
        VT_ReleaseVideoWindowResource(resource_id);
        return -1;
    }
    printf("[Capture Sample] context_id=%d\n", context_id);

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

    return 0;
}

void capture_terminate()
{
    if (VT_UnRegisterEventHandler(context_id) != VT_OK)
    {
        fprintf(stderr, "[Capture Sample] VT_UnRegisterEventHandler error!\n");
    }
    VT_DeleteContext(context_id);
    VT_ReleaseVideoWindowResource(resource_id);
}

void capture_onevent(VT_EVENT_TYPE_T type, void *data, void *user_data)
{
    switch (type)
    {
    case VT_AVAILABLE:
        printf("VT_AVAILABLE received: data=%p\n", data);
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
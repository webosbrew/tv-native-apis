#include <assert.h>
#include <NDL_directmedia.h>
#include <SDL.h>
#include "esplayer-datasrc.h"

#define TICKS_FOR_NEXT_FRAME (1000 / 60)

static SDL_Window *window = NULL;
static int app_quit = 0;

int videoPreroll(int width, int height, int framerate)
{
    NDL_DIRECTVIDEO_DATA_INFO_T info = {
        .width = width,
        .height = height,
    };
    return NDL_DirectVideoOpen(&info);
}

int videoSample(const void *data, size_t size)
{
    return NDL_DirectVideoPlay((void *) data, size);
}

void videoEos()
{
    NDL_DirectVideoClose();
}

int audioPreroll(int channels, int sampleFreq)
{
    NDL_DIRECTAUDIO_DATA_INFO_T info = {
        .number_of_channel = channels,
        .bit_per_sample = 16,
        .no_delay_mode = 1,
        .no_delay_upper_time = 48,
        .no_delay_lower_time = 16,
        .channel = NDL_DIRECTAUDIO_CH_MAIN,
        .source = NDL_DIRECTAUDIO_SRC_TYPE_AAC,
        .frequency = NDL_DIRECTAUDIO_SAMPLING_FREQ_OF(sampleFreq),
    };
    return NDL_DirectAudioOpen(&info);
}

int audioSample(const void *data, size_t size)
{
    return NDL_DirectAudioPlay((void *) data, size);
}

void audioEos()
{
    NDL_DirectAudioClose();
}

void pipelineQuit(int error)
{
    app_quit = 1;
}

int main(int argc, char *argv[])
{
    datasrc_init(argc, argv);
    int ndlerr;
    ndlerr = NDL_DirectMediaInit(APPID, NULL);
    assert(ndlerr == 0);

    SDL_SetHint(SDL_HINT_WEBOS_ACCESS_POLICY_KEYS_BACK, "true");
    // Create an SDL Window
    window = SDL_CreateWindow("NDL Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    // Setup renderer
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to transparent
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Clear winow
    SDL_RenderClear(renderer);
    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    // Start data source
    struct DATASRC_CALLBACKS dscb = {
        .videoPreroll = videoPreroll,
        .videoSample = videoSample,
        .videoEos = videoEos,
        .audioPreroll = audioPreroll,
        .audioSample = audioSample,
        .audioEos = audioEos,
        .pipelineQuit = pipelineQuit,
    };
    // Start the pipeline and let media callbacks roll in the background
    datasrc_start(&dscb);

    int lastTime = 0;
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
    datasrc_stop();
    SDL_DestroyWindow(window);
    SDL_Quit();
    // Unload all NDL resources before application quits
    NDL_DirectMediaQuit();
    return 0;
}

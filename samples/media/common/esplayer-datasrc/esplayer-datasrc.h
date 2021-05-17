#pragma
#include <stddef.h>

struct DATASRC_CALLBACKS
{
    int (*videoPreroll)(int width, int height, int framerate);
    int (*videoSample)(const void *data, size_t size);
    void (*videoEos)();
    int (*audioPreroll)(int channels, int sampleFreq);
    int (*audioSample)(const void *data, size_t size);
    void (*audioEos)();
    void (*pipelineQuit)(int error);
};

void datasrc_init(int argc, char *argv[]);
int datasrc_start(struct DATASRC_CALLBACKS *callbacks);
int datasrc_stop();
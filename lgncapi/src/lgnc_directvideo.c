#include "lgnc_directvideo.h"
#include "lgnc_wrapper.h"

int LGNC_DIRECTVIDEO_Close()
{
    return (int)_LGNC_DIRECTVIDEO_Close();
}

int LGNC_DIRECTVIDEO_Open(LGNC_VDEC_DATA_INFO_T *info)
{
    return (int)_LGNC_DIRECTVIDEO_Open(info);
}

int LGNC_DIRECTVIDEO_Play(void *data, unsigned int size)
{
    return (int)_LGNC_DIRECTVIDEO_Play(data, size);
}
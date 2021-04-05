#pragma once

enum LGNC_VDEC_FMT_T
{
    LGNC_VDEC_FMT_MAX = 10,
    LGNC_VDEC_FMT_H264 = 2
};

enum LGNC_VDEC_3D_TYPE_T
{
    LGNC_VDEC_3D_TYPE_LR_HALF = 2,
    LGNC_VDEC_3D_TYPE_NONE = 0,
    LGNC_VDEC_3D_TYPE_TB_HALF = 3,
    LGNC_VDEC_3D_TYPE_2DTO3D = 1,
    LGNC_VDEC_3D_TYPE_MAX = 4
};

typedef enum LGNC_VDEC_3D_TYPE_T LGNC_VDEC_3D_TYPE_T;

typedef struct LGNC_VDEC_DATA_INFO LGNC_VDEC_DATA_INFO_T;

typedef enum LGNC_VDEC_FMT_T LGNC_VDEC_FMT_T;

struct LGNC_VDEC_DATA_INFO
{
    int width;
    int height;
    LGNC_VDEC_FMT_T vdecFmt;
    LGNC_VDEC_3D_TYPE_T trid_type;
};

typedef struct LGNC_VDEC_DATA_INFO LGNC_VDEC_DATA_INFO_T;

int LGNC_DIRECTVIDEO_Close();
int LGNC_DIRECTVIDEO_Open(LGNC_VDEC_DATA_INFO_T *info);
int LGNC_DIRECTVIDEO_Play(void *data, unsigned int size);
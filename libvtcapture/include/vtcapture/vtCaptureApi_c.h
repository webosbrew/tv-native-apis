#pragma once

#include <stddef.h>
#include <stdint.h>

typedef char VT_CALLER_T;
typedef char VT_CLIENTID_T;
typedef int32_t VT_STATUS_T;

typedef int32_t VT_DUMP_T;
typedef int32_t VT_BUF_T;
typedef int32_t VT_FRAMERATE_T;

typedef struct VT_DRIVER_T
{
    uint32_t *ms_currentBuffIndex;
    int *ms_mutex; //p_thread_mutex_t in C = ??, should be wayne anyway 
} VT_DRIVER;

typedef struct VT_LOC
{
    int16_t x, y;
} VT_LOC_T;

typedef struct VT_RESOLUTION
{
    int16_t w, h;
} VT_RESOLUTION_T;

typedef struct VT_REGION
{
    int16_t a,b,c,d;
} VT_REGION_T;

typedef struct _LibVtCaptureProperties
{
    VT_DUMP_T dump;
    VT_LOC_T loc;
    VT_RESOLUTION_T reg;
    VT_BUF_T buf_cnt;
    VT_FRAMERATE_T frm;
} _LibVtCaptureProperties;


typedef struct _LibVtCaptureCapabilityInfo
{
    VT_DRIVER *driver;
    int32_t *dummy1;
    int16_t *dummy2;
    int16_t *dummy3;
    int16_t *dummy4;
    int16_t *dummy5; //0x14
    int16_t *dummy6;
    int16_t *dummy7;
    int16_t *dummy8;
    int16_t *dummy9;
    int16_t *dummy10;
} _LibVtCaptureCapabilityInfo;

typedef struct _LibVtCapturePlaneInfo
{
    int32_t stride;
    VT_REGION_T planeregion;
    VT_REGION_T activeregion;
} _LibVtCapturePlaneInfo;

typedef struct _LibVtCaptureBufferInfo
{
    int32_t start_addr0;
    int32_t start_addr1;
    int32_t size0;
    int32_t size1;
} _LibVtCaptureBufferInfo;


VT_DRIVER *vtCapture_create();
int vtCapture_init(VT_DRIVER *driver, const VT_CALLER_T *caller_id, VT_CLIENTID_T *clientid);
int vtCapture_preprocess(VT_DRIVER *driver, VT_CLIENTID_T *clientid, _LibVtCaptureProperties *props);
int vtCapture_capabilityInfo(VT_DRIVER *driver, VT_CLIENTID_T *clientid, _LibVtCaptureCapabilityInfo *capinf);
int vtCapture_planeInfo(VT_DRIVER *driver, VT_CLIENTID_T *clientid, _LibVtCapturePlaneInfo *planeinf);
int vtCapture_process(VT_DRIVER *driver, VT_CLIENTID_T *clientid);
int vtCapture_currentCaptureBuffInfo(VT_DRIVER *driver, _LibVtCaptureBufferInfo *buff);
int vtCapture_stop(VT_DRIVER *driver, VT_CLIENTID_T *clientid);
int vtCapture_postprocess(VT_DRIVER *driver, VT_CLIENTID_T *clientid);
int vtCapture_finalize(VT_DRIVER *driver, VT_CLIENTID_T *clientid);
int vtCapture_release(VT_DRIVER *driver);

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef char* VT_CALLER_T;
typedef char* VT_CLIENTID_T;
typedef int32_t VT_STATUS_T;
typedef char* VT_FRAMERATE_T;
typedef char* VT_DUMP_T;

typedef struct VT_DRIVER_T
{
    uint32_t* ms_currentBuffIndex;
    int* ms_mutex;
} VT_DRIVER;

typedef struct VT_REGION
{
    uint16_t x, y, w, h;
} VT_REGION_T;

typedef struct _LibVtCaptureProperties
{
    VT_DUMP_T dump;
    VT_REGION_T reg;
    VT_FRAMERATE_T framerate;
} _LibVtCaptureProperties;

VT_DRIVER vtCapture_create();
int vtCapture_init(VT_DRIVER driver, VT_CALLER_T *caller_id, VT_CLIENTID_T *client_id);
int vtCapture_preprocess(VT_DRIVER driver, VT_CALLER_T *caller_id, _LibVtCaptureProperties *props);
int vtCapture_process(VT_DRIVER driver, VT_CALLER_T *caller_id);
int vtCapture_stop(VT_DRIVER driver, VT_CALLER_T *caller_id);
int vtCapture_postprocess(VT_DRIVER driver, VT_CALLER_T *caller_id);
int vtCapture_finalize(VT_DRIVER driver, VT_CALLER_T *caller_id);

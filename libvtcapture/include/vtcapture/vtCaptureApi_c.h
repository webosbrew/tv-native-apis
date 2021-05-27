#pragma once

#include <stddef.h>
#include <stdint.h>

typedef char VT_CALLER;
typedef int32_t VT_STATUS_T;

typedef struct VT_DRIVER_T
{
    uint32_t ms_currentBuffIndex;
    int* ms_mutex;
} VT_DRIVER;

typedef struct _LibVtCaptureProperties
{
    char dump,
    int x,
    int y,
    int width,
    int height,
    int buf_cnt,
    char framerate;
} _LibVtCaptureProperties;

int vtCapture_create();
int vtCapture_init(VT_DRIVER driver, VT_CALLER *caller_id, char *client_id);
int vtCapture_preprocess(VT_DRIVER driver, VT_CALLER *caller_id, _LibVtCaptureProperties *props);
int vtCapture_process(VT_DRIVER driver, VT_CALLER *caller_id);
int vtCapture_stop(VT_DRIVER driver, VT_CALLER *caller_id);
int vtCapture_postprocess(VT_DRIVER driver, VT_CALLER *caller_id);
int vtCapture_finalize(VT_DRIVER driver, VT_CALLER *caller_id);

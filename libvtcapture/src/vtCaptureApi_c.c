#include "vtcapture/vtCaptureApi_c.h"

VT_DRIVER vtCapture_create() { 
    VT_DRIVER thi;
    thi.ms_mutex = 0;
    thi.ms_currentBuffIndex = 0;
    return thi; }
int vtCapture_init(VT_DRIVER driver, VT_CALLER_T *caller_id, VT_CLIENTID_T *client_id) { return -1; }
int vtCapture_preprocess(VT_DRIVER driver, VT_CALLER_T *caller_id, _LibVtCaptureProperties *props) { return -1; }
int vtCapture_process(VT_DRIVER driver, VT_CALLER_T *caller_id) { return -1; }
int vtCapture_stop(VT_DRIVER driver, VT_CALLER_T *caller_id) { return -1; }
int vtCapture_postprocess(VT_DRIVER driver, VT_CALLER_T *caller_id) { return -1; }
int vtCapture_finalize(VT_DRIVER driver, VT_CALLER_T *caller_id) { return -1; }

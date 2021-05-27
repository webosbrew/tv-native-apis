#include "vtcapture/vtCaptureApi_c.h"

int vtCapture_create() { return -1; }
int vtCapture_init(VT_DRIVER driver, VT_CALLER *caller_id, char *client_id) { return -1; }
int vtCapture_preprocess(VT_DRIVER driver, VT_CALLER *caller_id, _LibVtCaptureProperties *props) { return -1; }
int vtCapture_process(VT_DRIVER driver, VT_CALLER *caller_id) { return -1; }
int vtCapture_stop(VT_DRIVER driver, VT_CALLER *caller_id) { return -1; }
int vtCapture_postprocess(VT_DRIVER driver, VT_CALLER *caller_id) { return -1; }
int vtCapture_finalize(VT_DRIVER driver, VT_CALLER *caller_id) { return -1; }

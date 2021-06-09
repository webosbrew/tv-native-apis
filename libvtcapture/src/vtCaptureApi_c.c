#include "vtcapture/vtCaptureApi_c.h"

VT_DRIVER *vtCapture_create() { 
    VT_DRIVER *thi;
    return thi; }
int vtCapture_init(VT_DRIVER *driver, const VT_CALLER_T *caller_id, VT_CLIENTID_T *clientid) { return -1; }
int vtCapture_preprocess(VT_DRIVER *driver, VT_CLIENTID_T *clientid, _LibVtCaptureProperties *props) { return -1; }
int vtCapture_capabilityInfo(VT_DRIVER *driver, VT_CLIENTID_T *clientid, _LibVtCaptureCapabilityInfo *capinf) { return -1; }
int vtCapture_planeInfo(VT_DRIVER *driver, VT_CLIENTID_T *clientid, _LibVtCapturePlaneInfo *planeinf) { return -1; }
int vtCapture_process(VT_DRIVER *driver, VT_CLIENTID_T *clientid) { return -1; }
int vtCapture_stop(VT_DRIVER *driver, VT_CLIENTID_T *clientid) { return -1; }
int vtCapture_currentCaptureBuffInfo(VT_DRIVER *driver, _LibVtCaptureBufferInfo *buff) { return -1; }
int vtCapture_postprocess(VT_DRIVER *driver, VT_CLIENTID_T *clientid) { return -1; }
int vtCapture_finalize(VT_DRIVER *driver, VT_CLIENTID_T *client_id) { return -1; }
int vtCapture_release(VT_DRIVER *driver) { return -1; }

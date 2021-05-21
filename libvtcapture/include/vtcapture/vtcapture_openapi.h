#pragma once

#include <stddef.h>
#include <stdint.h>

typedef int32_t VTDRIVER;
typedef char VT_IDK;
typedef int32_t VT_CAPTURE_PROPERTIES;

VT_STATUS_T vtCapture_init(VTDRIVER *this);
VT_STATUS_T vtCapture_preprocess(VTDRIVER *this, VT_IDK *idk, VT_CAPTURE_PROPERTIES *props);
VT_STATUS_T vtCapture_process(VTDRIVER *this, VT_IDK *idk);
VT_STATUS_T vtCapture_postprocess(VTDRIVER *this, VT_IDK *idk);
VT_STATUS_T vtCapture_finalize(VTDRIVER *this, VT_IDK *idk);

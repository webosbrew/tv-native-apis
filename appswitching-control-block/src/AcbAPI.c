#include "AcbAPI.h"

long AcbAPI_create(void) { return -1; }

bool AcbAPI_initialize(long acbId, AcbAPI_PlayerType playerType, const char *appId, AcbAPI_Callback callback) { return false; }

int AcbAPI_setMediaVideoData(long acbId, const char *payload) { return -1; }

int AcbAPI_setState(long acbId, AcbAPI_AppState appState, AcbAPI_PlayState playState, long *taskId) { return -1; }

bool AcbAPI_setMediaId(long acbId, const char *connId) { return false; }

bool AcbAPI_setSinkType(long acbId, AcbAPI_SinkType sinkType) { return false; }

int AcbAPI_setDisplayWindow(long acbId, long x, long y, long w, long h, bool fullScreen, long *taskId) { return -1; }

int AcbAPI_setCustomDisplayWindow(long acbId, long in_x, long in_y, long in_w, long in_h, long out_x, long out_y, long out_w, long out_h, bool fullScreen, long *taskId) { return -1; }

int AcbAPI_finalize(long acbId) { return -1; }

void AcbAPI_destroy(long acbId) { return; }
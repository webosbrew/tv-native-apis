#pragma once

#include <stdbool.h>

typedef void (*AcbAPI_Callback)(long acbId, long taskId, long eventType, long appState, long playState, const char *reply);

typedef enum AcbAPI_PlayerType
{
    PLAYER_TYPE_GROUP = 0L,
    PLAYER_TYPE_VIDEO,
    PLAYER_TYPE_VIDEO_UNMUTED_AFTER_PLAYING,
    PLAYER_TYPE_AUDIO,
    PLAYER_TYPE_HTML5_AUDIO,
    PLAYER_TYPE_TV,
    PLAYER_TYPE_EXT_INPUT,
    PLAYER_TYPE_DVR,
    PLAYER_TYPE_VCS,
    PLAYER_TYPE_DIRECT_VIDEO,
    PLAYER_TYPE_DIRECT_AUDIO,
    PLAYER_TYPE_MSE,
    PLAYER_TYPE_QT_DVR,
    PLAYER_TYPE_PHOTO,
} AcbAPI_PlayerType;

typedef enum AcbAPI_SinkType
{
    SINK_TYPE_AUTO = 0L,
    SINK_TYPE_MAIN = 1L,
    SINK_TYPE_SUB = 2L,
} AcbAPI_SinkType;

typedef enum AcbAPI_AppState
{
    APPSTATE_INITIALIZED = 0,
    APPSTATE_FOREGROUND = 1,
    APPSTATE_BACKGROUND = 2,
} AcbAPI_AppState;

typedef enum AcbAPI_PlayState
{
    PLAYSTATE_UNLOADED = 0,
    PLAYSTATE_LOADED = 1,
    PLAYSTATE_SEAMLESS_LOADED = 2,
    PLAYSTATE_PLAYING = 3,
    PLAYSTATE_PAUSED = 4,
    PLAYSTATE_AUDIO_ONLY_PLAYING = 5,
    PLAYSTATE_FROZEN = 6,
} AcbAPI_PlayState;

long AcbAPI_create(void);

bool AcbAPI_initialize(long acbId, AcbAPI_PlayerType playerType, const char *appId, AcbAPI_Callback callback);

int AcbAPI_setMediaVideoData(long acbId, const char *payload);

int AcbAPI_setState(long acbId, AcbAPI_AppState appState, AcbAPI_PlayState playState, long *taskId);

bool AcbAPI_setMediaId(long acbId, const char *connId);

bool AcbAPI_setSinkType(long acbId, AcbAPI_SinkType sinkType);

int AcbAPI_setDisplayWindow(long acbId, long x, long y, long w, long h, bool fullScreen, long *taskId);

int AcbAPI_setCustomDisplayWindow(long acbId, long in_x, long in_y, long in_w, long in_h, long out_x, long out_y, long out_w, long out_h, bool fullScreen, long *taskId);

int AcbAPI_finalize(long acbId);

void AcbAPI_destroy(long acbId);
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "lgnc_openapi_types.h"

enum {
    LGNC_REMOTE_PRESS = 272,
    LGNC_REMOTE_RED = 398,
    LGNC_REMOTE_GREEN = 399,
    LGNC_REMOTE_YELLOW = 400,
    LGNC_REMOTE_BLUE = 401,
    LGNC_REMOTE_CH_UP = 402,
    LGNC_REMOTE_CH_DOWN = 403,
    LGNC_REMOTE_BACK = 412,
    LGNC_REMOTE_NUM_1 = 872,
    LGNC_REMOTE_NUM_2 = 873,
    LGNC_REMOTE_NUM_3 = 874,
    LGNC_REMOTE_NUM_4 = 875,
    LGNC_REMOTE_NUM_5 = 876,
    LGNC_REMOTE_NUM_6 = 877,
    LGNC_REMOTE_NUM_7 = 878,
    LGNC_REMOTE_NUM_8 = 879,
    LGNC_REMOTE_NUM_9 = 880,
    LGNC_REMOTE_NUM_10 = 881,
    LGNC_REMOTE_NUM_11 = 882,
    LGNC_REMOTE_NUM_12 = 883,
    LGNC_REMOTE_DATA_HOSO = 885,
};

enum LGNC_CURSOR_SIZE_T {
    LGNC_CURSOR_SIZE_L = 0,
    LGNC_CURSOR_SIZE_M = 1,
    LGNC_CURSOR_SIZE_S = 2,
    LGNC_CURSOR_SIZE_LASTEST = 3,
    LGNC_CURSOR_SIZE_LAST = 4
};

typedef enum LGNC_CURSOR_SIZE_T LGNC_CURSOR_SIZE_T;

enum LGNC_CURSOR_TYPE_T {
    LGNC_CURSOR_TYPE_A = 0,
    LGNC_CURSOR_TYPE_B = 1,
    LGNC_CURSOR_TYPE_C = 2,
    LGNC_CURSOR_TYPE_D = 3,
    LGNC_CURSOR_TYPE_DRAG = 4,
    LGNC_CURSOR_TYPE_POINT = 5,
    LGNC_CURSOR_TYPE_HOLD = 6,
    LGNC_CURSOR_TYPE_GESTURE_POINT = 7,
    LGNC_CURSOR_TYPE_DISABLE = 8,
    LGNC_CURSOR_TYPE_CUSTOM_A = 9,
    LGNC_CURSOR_TYPE_CUSTOM_B = 10,
    LGNC_CURSOR_TYPE_CUSTOM_C = 11,
    LGNC_CURSOR_TYPE_CUSTOM_D = 12,
    LGNC_CURSOR_TYPE_CUSTOM_E = 13,
    LGNC_CURSOR_TYPE_LASTEST = 14,
    LGNC_CURSOR_TYPE_EXTERNAL = 15,
    LGNC_CURSOR_TYPE_LAST = 16
};

enum LGNC_CURSOR_STATE_T {
    LGNC_CURSOR_STATE_NORMAL = 0,
    LGNC_CURSOR_STATE_PRESS = 1,
    LGNC_CURSOR_STATE_LASTEST = 2,
    LGNC_CURSOR_STATE_LAST = 3,
};

enum LGNC_CURSOR_HOTSPOT_T {
    LGNC_CURSOR_HOTSPOT_LEFTTOP = 0,
    LGNC_CURSOR_HOTSPOT_USERSETTING = 1,
    LGNC_CURSOR_HOTSPOT_LAST = 2,
};


typedef struct LGNC_CTRL_INFO LGNC_CTRL_INFO, *PLGNC_CTRL_INFO;

struct LGNC_CTRL_INFO {
    char projectName[32];
    char modelName[32];
    char hwVer[32];
    char swVer[32];
    char ESN[32];
    char toolTypeName[32];
    char serialNumber[32];
    char modelInch[8];
    char countryGroup[8];
    char szDdrRam[8];
};

typedef struct LGNC_CTRL_INFO LGNC_CTRL_INFO_T;

typedef enum LGNC_CURSOR_HOTSPOT_T LGNC_CURSOR_HOTSPOT_T;

typedef enum LGNC_CURSOR_SIZE_T LGNC_CURSOR_SIZE_T;

typedef enum LGNC_CURSOR_STATE_T LGNC_CURSOR_STATE_T;

typedef enum LGNC_CURSOR_TYPE_T LGNC_CURSOR_TYPE_T;

typedef struct LGNC_CUSTOM_CURSOR {
    char fileInfo[256];
    LGNC_CURSOR_TYPE_T cursorType;
    LGNC_CURSOR_SIZE_T cursorSize;
    LGNC_CURSOR_STATE_T cursorState;
    LGNC_CURSOR_HOTSPOT_T cursorHotSpot;
    unsigned short gapX;
    unsigned short gapY;
} LGNC_CUSTOM_CURSOR_T;

int LGNC_SYSTEM_Initialize(int argc, char **argv, LGNC_CALLBACKS_T *callbacks);

int LGNC_SYSTEM_Finalize(void);

int LGNC_SYSTEM_GetDisplayId(int *displayId /* very likely to be wl_egl_window */);

int LGNC_SYSTEM_GetDisplayResolution(int *width, int *height);

int LGNC_SYSTEM_GetLanguage(char *language);

int LGNC_SYSTEM_GetSaveDirectory(char *directory);

int LGNC_SYSTEM_GetSystemInfo(LGNC_CTRL_INFO *info);

int LGNC_SYSTEM_GetVersion(int *major, int *minor, int *patch);

int LGNC_SYSTEM_SetCursorShape(void);

int LGNC_SYSTEM_SetCustomCursor(void);

#ifdef __cplusplus
}
#endif

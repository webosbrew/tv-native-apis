#pragma once

#include <stddef.h>
#include <linux/input.h>

#include "lgnc_openapi_types.h"

enum LGNC_KEY_COND_T
{
    LGNC_KEY_PRESS = 0,
    LGNC_KEY_RELEASE = 1,
    LGNC_KEY_REPEAT = 2,
    LGNC_KEY_DRAG = 3,
    LGNC_KEY_POWER = 4,
    LGNC_KEY_GESTURE = 5,
    LGNC_KEY_COND_LAST = 6,
};

typedef enum LGNC_KEY_COND_T LGNC_KEY_COND_T;

enum LGNC_MSG_TYPE_T
{
    LGNC_MSG_NONE = 0,
    LGNC_MSG_FOCUS_IN = 1,
    LGNC_MSG_FOCUS_OUT = 2,
    LGNC_MSG_TERMINATE = 3,
    LGNC_MSG_HOST_EVENT = 4,
    LGNC_MSG_PAUSE = 5,
    LGNC_MSG_RESUME = 6,
    LGNC_MSG_LAST = -1
};

typedef enum LGNC_MSG_TYPE_T LGNC_MSG_TYPE_T;

enum LGNC_CURSOR_SIZE_T
{
    LGNC_CURSOR_SIZE_L = 0,
    LGNC_CURSOR_SIZE_M = 1,
    LGNC_CURSOR_SIZE_S = 2,
    LGNC_CURSOR_SIZE_LASTEST = 3,
    LGNC_CURSOR_SIZE_LAST = 4
};

typedef enum LGNC_CURSOR_SIZE_T LGNC_CURSOR_SIZE_T;

enum LGNC_CURSOR_TYPE_T
{
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

enum LGNC_CURSOR_STATE_T
{
    LGNC_CURSOR_STATE_NORMAL = 0,
    LGNC_CURSOR_STATE_PRESS = 1,
    LGNC_CURSOR_STATE_LASTEST = 2,
    LGNC_CURSOR_STATE_LAST = 3,
};

enum LGNC_CURSOR_HOTSPOT_T
{
    LGNC_CURSOR_HOTSPOT_LEFTTOP = 0,
    LGNC_CURSOR_HOTSPOT_USERSETTING = 1,
    LGNC_CURSOR_HOTSPOT_LAST = 2,
};

enum LGNC_INPUT_DEV_TYPE_T
{
    LGNC_INPUT_TYPE_KEYBOARD = 1,
    LGNC_INPUT_TYPE_MOUSE = 2,
    LGNC_INPUT_TYPE_JOYSTICK = 4,
    LGNC_INPUT_TYPE_REMOTE = 8,
    LGNC_INPUT_TYPE_PS3 = 32768,
    LGNC_INPUT_TYPE_VIRTUAL = 16,
    LGNC_INPUT_TYPE_KEY_RETURN = 32,
    LGNC_INPUT_TYPE_CURSOR_RETURN = 64,
    LGNC_INPUT_LGE = 128,
    LGNC_INPUT_TYPE_NLP = 1024,
    LGNC_INPUT_TYPE_SMARTREMOTE = 2048,
    LGNC_INPUT_TYPE_XPAD = 4096,
    LGNC_INPUT_TYPE_HIDPAD = 8192,
    LGNC_INPUT_TYPE_WIDI = 16384,
    LGNC_INPUT_TYPE_ALL = 65023,
    LGNC_INPUT_TYPE_NONE = 0,
};

typedef enum LGNC_INPUT_DEV_TYPE_T LGNC_INPUT_DEV_TYPE_T;

struct LGNC_ADDITIONAL_INPUT_INFO_T
{
    struct input_event event;
    int deviceID;
    LGNC_INPUT_DEV_TYPE_T deviceType;
};
typedef struct LGNC_ADDITIONAL_INPUT_INFO_T LGNC_ADDITIONAL_INPUT_INFO_T;

struct LGNC_SYSTEM_CALLBACKS_T
{
    LGNC_STATUS_T(*pfnMsgHandler)
    (LGNC_MSG_TYPE_T msg, unsigned int submsg, char *pData, unsigned short dataSize);
    unsigned int (*pfnKeyEventCallback)(unsigned int key, LGNC_KEY_COND_T keyCond, LGNC_ADDITIONAL_INPUT_INFO_T *keyInput);
    unsigned int (*pfnMouseEventCallback)(int posX, int posY, unsigned int key, LGNC_KEY_COND_T keyCond, LGNC_ADDITIONAL_INPUT_INFO_T *keyInput);
    void (*pfnJoystickEventCallback)(LGNC_ADDITIONAL_INPUT_INFO_T *e);
};

typedef struct LGNC_CTRL_INFO LGNC_CTRL_INFO, *PLGNC_CTRL_INFO;

struct LGNC_CTRL_INFO
{
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

typedef struct LGNC_CUSTOM_CURSOR LGNC_CUSTOM_CURSOR, *PLGNC_CUSTOM_CURSOR;

struct LGNC_CUSTOM_CURSOR
{
    char fileInfo[256];
    LGNC_CURSOR_TYPE_T cursorType;
    LGNC_CURSOR_SIZE_T cursorSize;
    LGNC_CURSOR_STATE_T cursorState;
    LGNC_CURSOR_HOTSPOT_T cursorHotSpot;
    unsigned short gapX;
    unsigned short gapY;
};

typedef struct LGNC_CUSTOM_CURSOR LGNC_CUSTOM_CURSOR_T;

typedef struct LGNC_SYSTEM_CALLBACKS_T LGNC_SYSTEM_CALLBACKS_T;

int LGNC_SYSTEM_Initialize(int argc, char **argv, LGNC_SYSTEM_CALLBACKS_T *callbacks);
int LGNC_SYSTEM_Finalize(void);

int LGNC_SYSTEM_GetDisplayId(int *displayId /* very likely to be wl_egl_window */);
int LGNC_SYSTEM_GetLanguage(void);
int LGNC_SYSTEM_GetSaveDirectory(void);
int LGNC_SYSTEM_GetSystemInfo(void);
int LGNC_SYSTEM_SetCursorShape(void);
int LGNC_SYSTEM_SetCustomCursor(void);
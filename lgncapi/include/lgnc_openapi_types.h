#pragma once

#include <linux/input.h>

typedef enum LGNC_STATUS_T {
    LGNC_OK = 0,
    LGNC_HANDLED = 0,
    LGNC_NOT_HANDLED = -1,
    LGNC_ERROR = -1,
    LGNC_BLOCKED = -2,
    LGNC_INVALID_PARAMS = -3,
    LGNC_NOT_ENOUGH_MEMORY = -4,
    LGNC_TIMEOUT = -5,
    LGNC_NOT_SUPPORTED = -6,
    LGNC_BUFFER_FULL = -7,
    LGNC_HOST_NOT_CONNECTED = -8,
    LGNC_VERSION_MISMATCH = -9,
    LGNC_ALREADY_REGISTERED = -10,
    LGNC_LAST = -10,
    LGNC_NOT_INITIALIZED = -11,
} LGNC_STATUS_T;

typedef enum LGNC_MSG_TYPE_T {
    LGNC_MSG_NONE = 0,
    LGNC_MSG_FOCUS_IN = 1,
    LGNC_MSG_FOCUS_OUT = 2,
    LGNC_MSG_TERMINATE = 3,
    LGNC_MSG_HOST_EVENT = 4,
    LGNC_MSG_PAUSE = 5,
    LGNC_MSG_RESUME = 6,
    LGNC_MSG_LAST = -1
} LGNC_MSG_TYPE_T;

typedef enum LGNC_KEY_COND_T {
    LGNC_KEY_PRESS = 0,
    LGNC_KEY_RELEASE = 1,
    LGNC_KEY_REPEAT = 2,
    LGNC_KEY_DRAG = 3,
    LGNC_KEY_POWER = 4,
    LGNC_KEY_GESTURE = 5,
    LGNC_KEY_COND_LAST = 6,
} LGNC_KEY_COND_T;

typedef enum LGNC_INPUT_DEV_TYPE_T {
    LGNC_INPUT_TYPE_NONE = 0,
    LGNC_INPUT_TYPE_KEYBOARD = 1,
    LGNC_INPUT_TYPE_MOUSE = 2,
    LGNC_INPUT_TYPE_JOYSTICK = 4,
    LGNC_INPUT_TYPE_REMOTE = 8,
    LGNC_INPUT_TYPE_VIRTUAL = 16,
    LGNC_INPUT_TYPE_KEY_RETURN = 32,
    LGNC_INPUT_TYPE_CURSOR_RETURN = 64,
    LGNC_INPUT_LGE = 128,
    LGNC_INPUT_TYPE_NLP = 1024,
    LGNC_INPUT_TYPE_SMARTREMOTE = 2048,
    LGNC_INPUT_TYPE_XPAD = 4096,
    LGNC_INPUT_TYPE_HIDPAD = 8192,
    LGNC_INPUT_TYPE_WIDI = 16384,
    LGNC_INPUT_TYPE_PS3 = 32768,
    LGNC_INPUT_TYPE_ALL = 65023,
} LGNC_INPUT_DEV_TYPE_T;

typedef struct LGNC_ADDITIONAL_INPUT_INFO_T {
    struct input_event event;
    int deviceID;
    LGNC_INPUT_DEV_TYPE_T deviceType;
} LGNC_ADDITIONAL_INPUT_INFO_T;

typedef struct LGNC_CALLBACKS_T {
    LGNC_STATUS_T (*msgHandler)(LGNC_MSG_TYPE_T msg, unsigned int submsg, char *pData, unsigned short dataSize);

    unsigned int (*keyEventCallback)(unsigned int key, LGNC_KEY_COND_T keyCond, LGNC_ADDITIONAL_INPUT_INFO_T *keyInput);

    unsigned int (*mouseEventCallback)(int posX, int posY, unsigned int key, LGNC_KEY_COND_T keyCond,
                                       LGNC_ADDITIONAL_INPUT_INFO_T *keyInput);

    void (*joystickEventCallback)(LGNC_ADDITIONAL_INPUT_INFO_T *e);
} LGNC_CALLBACKS_T;
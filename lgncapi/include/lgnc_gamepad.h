#pragma once
#include "lgnc_system.h"

struct LGNC_GAMEPAD_INFO_T
{
    int id;
    int type;
};

typedef struct LGNC_GAMEPAD_INFO_T LGNC_GAMEPAD_INFO;

typedef void(GamePadEventCallback)(LGNC_ADDITIONAL_INPUT_INFO_T *e);
typedef void(GamePadHotPlugCallback)(LGNC_GAMEPAD_INFO *gamepad, int count);

int LGNC_GAMEPAD_RegisterCallback(GamePadEventCallback *, GamePadHotPlugCallback *);
int LGNC_GAMEPAD_UnregisterCallback();
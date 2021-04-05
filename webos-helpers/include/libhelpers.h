#pragma once
#include <lunaservice.h>

typedef struct __HContext
{
    LSFilterFunc callback;
    int unknown1;
    int unknown2;
    int multiple;
    int public;
    LSMessageToken ret_token;
} HContext;

int HLunaServiceCall(const char *uri, const char *payload, HContext *context);
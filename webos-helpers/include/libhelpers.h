#pragma once

#include <luna-service2/lunaservice.h>

typedef struct __HContext {
    LSFilterFunc callback;
    int unknown1;
    int unknown2;
    int multiple;
    int public;
    LSMessageToken ret_token;
} HContext;

int HLunaServiceCall(const char *uri, const char *payload, HContext *context);

int HUnregisterServiceCallback(HContext *context);

const char *HLunaServiceMessage(LSMessage *msg);
/**
 * @defgroup helpers libhelpers
 * @brief webOS common helper
 */

/**
 * @ingroup helpers
 * @file libhelpers.h
 */
#pragma once

#include <luna-service2/lunaservice.h>

/**
 * @brief Context for luna service calls
 */
typedef struct HContext {
    /**
     * @brief Callback function called on incoming message.
     */
    LSFilterFunc callback;
    int unknown1;
    int unknown2;
    /**
     * @brief Whether the call is multiple (like subscription), or one-shot.
     */
    int multiple;
    /**
     * @brief Whether the call is a public call or private call
     */
    int public;
    LSMessageToken ret_token;
} HContext;

/**
 * @brief Send luna call
 * @param uri
 * @param payload
 * @param context
 * @return 0 if succeeded
 */
int HLunaServiceCall(const char *uri, const char *payload, HContext *context);

/**
 * @brief Unregister a service callback
 * @param context Same context used in HLunaServiceCall
 * @return 0 if succeeded
 */
int HUnregisterServiceCallback(HContext *context);

/**
 * @brief Get payload message from luna call response
 * @param msg
 * @return Payload message (JSON string)
 */
const char *HLunaServiceMessage(LSMessage *msg);
#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifndef STATIC
#define STATIC static
#endif

#define CANIF_OK                    (0u)
#define CANIF_ERR_INVALID_CONFIG    (1u)
#define CANIF_ERR_INVALID_OBJECT    (2u)
#define CANIF_ERR_INVALID_LENGTH    (3u)
#define CANIF_ERR_BUS_OFF           (4u)
#define CANIF_ERR_CONTROLLER_FULL   (5u)
#define CANIF_ERR_ROUTE_REF         (6u)
#define CANIF_ERR_INTERNAL          (7u)

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t CanIf_ControllerId_t;
typedef uint16_t CanIf_ChannelId_t;
typedef uint16_t CanIf_ObjectId_t;
typedef uint16_t CanIf_PduId_t;

typedef enum
{
    CANIF_STATE_RESET = 0u,
    CANIF_STATE_INITIALIZED = 1u,
    CANIF_STATE_CONFIG_VALIDATED = 2u,
    CANIF_STATE_STOPPED = 3u,
    CANIF_STATE_ACTIVE = 4u,
    CANIF_STATE_DEGRADED = 5u
} CanIf_StateType_t;

typedef struct
{
    CanIf_ControllerId_t controllerId;
    CanIf_ChannelId_t channelId;
    CanIf_PduId_t pduId;
    uint8_t direction;
    uint8_t payloadLength;
    uint8_t *data;
    uint8_t status;
} CanIf_PduInfo_t;

typedef struct
{
    CanIf_ControllerId_t controllerId;
    CanIf_ChannelId_t channelId;
    uint8_t active;
    uint8_t busOff;
    uint8_t ready;
    uint8_t errorCounter;
    uint8_t queueFull;
    uint8_t state;
} CanIf_ControllerStatus_t;

typedef struct
{
    CanIf_ObjectId_t objectId;
    CanIf_PduId_t pduId;
    uint32_t canId;
    uint8_t direction;
    uint8_t length;
    uint8_t enabled;
    uint16_t routeId;
} CanIf_ObjectConfig_t;

typedef struct
{
    CanIf_ChannelId_t channelId;
    CanIf_ControllerId_t controllerId;
    uint8_t transmitEnabled;
    uint8_t receiveEnabled;
    uint8_t objectCount;
    const CanIf_ObjectConfig_t *objects;
} CanIf_ChannelConfig_t;

typedef struct
{
    CanIf_ControllerId_t controllerId;
    uint8_t channelCount;
    const CanIf_ChannelConfig_t *channels;
    uint8_t enabled;
    uint8_t errorPolicy;
} CanIf_ControllerConfig_t;

typedef struct
{
    uint16_t controllerCount;
    uint16_t channelCount;
    uint16_t objectCount;
    const CanIf_ControllerConfig_t *controllers;
    const CanIf_ChannelConfig_t *channels;
    const CanIf_ObjectConfig_t *objects;
    uint8_t enableState;
} CanIf_Config_t;

#ifdef __cplusplus
}
#endif

#endif

#ifndef COM_TYPES_H
#define COM_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include "Com_Cfg.h"

#define COM_OK                  (0u)
#define COM_ERR_INVALID_SIGNAL  (1u)
#define COM_ERR_INVALID_PDU     (2u)
#define COM_ERR_INVALID_CONFIG  (3u)
#define COM_ERR_DIRECTION       (4u)
#define COM_ERR_TIMEOUT         (5u)
#define COM_ERR_QUEUE_FULL      (6u)
#define COM_ERR_INTERNAL        (7u)

#define COM_TRUE                (1u)
#define COM_FALSE               (0u)

#define COM_CODE

#ifndef STATIC
#define STATIC static
#endif
#ifndef FUNC
#define FUNC(rettype, memclass) rettype
#endif
#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t Com_SignalId_t;
typedef uint16_t Com_PduId_t;
typedef uint16_t Com_NotificationId_t;

typedef enum
{
    COM_STATUS_OK = 0u,
    COM_STATUS_INVALID_SIGNAL = 1u,
    COM_STATUS_INVALID_PDU = 2u,
    COM_STATUS_INVALID_CONFIG = 3u,
    COM_STATUS_DIRECTION = 4u,
    COM_STATUS_TIMEOUT = 5u,
    COM_STATUS_QUEUE_FULL = 6u,
    COM_STATUS_INTERNAL = 7u
} Com_Status_t;

typedef enum
{
    COM_SIGNAL_DIRECTION_TX = 0u,
    COM_SIGNAL_DIRECTION_RX = 1u,
    COM_SIGNAL_DIRECTION_LOCAL = 2u
} Com_SignalDirectionType;

typedef enum
{
    COM_NOTIFY_NONE = 0u,
    COM_NOTIFY_ON_CHANGE = 1u,
    COM_NOTIFY_ON_TIMEOUT = 2u
} Com_NotificationType_t;

typedef struct
{
    Com_SignalId_t signalId;
    Com_PduId_t pduId;
    Com_SignalDirectionType direction;
    uint8_t bitStart;
    uint8_t bitLength;
    uint32_t defaultValue;
    uint32_t timeoutMs;
    uint8_t valid;
    uint8_t enabled;
    Com_NotificationType_t notificationPolicy;
} Com_SignalMeta_t;

typedef struct
{
    Com_PduId_t pduId;
    uint8_t direction;
    uint8_t length;
    uint8_t txRouteEnabled;
    uint8_t rxRouteEnabled;
    uint32_t generationCounter;
    uint8_t periodTicks;
} Com_PduMeta_t;

typedef struct
{
    uint8_t valid;
    uint8_t stale;
    uint8_t timeout;
    uint8_t invalid;
    uint32_t updateCount;
    uint32_t lastUpdateTick;
    uint32_t statusFlags;
} Com_SignalStatus_t;

typedef struct
{
    uint32_t value;
    Com_SignalStatus_t status;
} Com_SignalRuntime_t;

typedef struct
{
    Com_SignalId_t signalId;
    Com_NotificationType_t type;
    uint32_t timestamp;
    Com_SignalStatus_t statusSnapshot;
    uint32_t reasonCode;
} Com_Notification_t;

typedef struct
{
    uint8_t count;
    uint8_t head;
    uint8_t tail;
    Com_Notification_t entries[COM_MAX_NOTIFICATIONS];
} Com_NotificationQueue_t;

typedef struct
{
    uint8_t length;
    uint8_t *data;
    uint8_t ownership;
    uint8_t status;
} Com_PduBuffer_t;

typedef struct
{
    uint16_t signalCount;
    const Com_SignalMeta_t *signalTable;
    Com_SignalRuntime_t *runtimeTable;
    uint16_t pduCount;
    Com_PduMeta_t *pduTable;
    uint8_t featureMask;
    Com_NotificationQueue_t *notificationQueue;
} Com_Config_t;

#ifdef __cplusplus
}
#endif

#endif

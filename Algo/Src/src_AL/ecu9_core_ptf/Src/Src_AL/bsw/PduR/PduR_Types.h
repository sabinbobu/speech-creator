#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include "PduR_Cfg.h"

#ifndef STATIC
#define STATIC static
#endif

#define PDUR_OK                     (0u)
#define PDUR_ERR_INVALID_ROUTE      (1u)
#define PDUR_ERR_INVALID_LENGTH     (2u)
#define PDUR_ERR_INVALID_DIRECTION  (3u)
#define PDUR_ERR_BUFFER_OWNERSHIP   (4u)
#define PDUR_ERR_ROUTE_DISABLED     (5u)
#define PDUR_ERR_DEST_UNAVAILABLE   (6u)
#define PDUR_ERR_INTERNAL           (7u)

#define PDUR_TRUE                   (1u)
#define PDUR_FALSE                  (0u)

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t PduR_RouteId_t;
typedef uint16_t PduR_PduId_t;
typedef uint16_t PduR_EndpointId_t;

typedef enum
{
    PDUR_DIRECTION_TX = 0u,
    PDUR_DIRECTION_RX = 1u,
    PDUR_DIRECTION_BOTH = 2u
} PduR_DirectionType_t;

typedef enum
{
    PDUR_OWNERSHIP_NONE = 0u,
    PDUR_OWNERSHIP_EXCLUSIVE = 1u,
    PDUR_OWNERSHIP_SHARED_READ = 2u,
    PDUR_OWNERSHIP_TRANSIENT = 3u
} PduR_OwnershipMode_t;

typedef struct
{
    uint8_t valid;
    uint8_t enabled;
    uint8_t lastResult;
    uint8_t lastReceiveResult;
    uint32_t errorSnapshot;
    uint32_t counter;
} PduR_RouteStatus_t;

typedef struct
{
    PduR_RouteId_t routeId;
    PduR_PduId_t sourcePduId;
    PduR_PduId_t destinationPduId;
    PduR_EndpointId_t sourceEndpoint;
    PduR_EndpointId_t destinationEndpoint;
    PduR_DirectionType_t direction;
    uint8_t allowedLength;
    PduR_OwnershipMode_t ownershipMode;
    uint8_t enabled;
    uint8_t routeCompatibility;
} PduR_RouteConfig_t;

typedef struct
{
    PduR_EndpointId_t endpointId;
    uint8_t moduleType;
    uint8_t capabilityMask;
    uint8_t routeCount;
    PduR_OwnershipMode_t bufferPolicy;
    uint8_t enabled;
} PduR_EndpointConfig_t;

typedef struct
{
    uint8_t length;
    uint8_t data[PDUR_MAX_BUFFER_SIZE];
    PduR_OwnershipMode_t ownershipMode;
    uint8_t isValid;
} PduR_BufferInfo_t;

typedef struct
{
    PduR_EndpointId_t sourceEndpoint;
    PduR_EndpointId_t destinationEndpoint;
    PduR_DirectionType_t direction;
    PduR_PduId_t pduId;
    uint8_t *buffer;
    uint8_t length;
    uint8_t confirmationCallbackConfigured;
    uint32_t statusCode;
} PduR_RouteContext_t;

typedef struct
{
    uint16_t routeCount;
    const PduR_RouteConfig_t *routes;
    PduR_RouteStatus_t *status;
    uint16_t endpointCount;
    const PduR_EndpointConfig_t *endpoints;
} PduR_RouteTable_t;

#ifdef __cplusplus
}
#endif

#endif

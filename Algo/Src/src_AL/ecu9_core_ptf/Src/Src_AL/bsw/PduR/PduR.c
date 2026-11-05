#include "PduR.h"
#include "CanIf.h"
#include "Com.h"

#define PDUR_STATE_IDLE     (0u)
#define PDUR_STATE_READY    (1u)
#define PDUR_STATE_ACTIVE   (2u)

typedef struct
{
    uint8_t state;
    const PduR_RouteTable_t *routeTable;
    uint32_t enabledMask;
} PduR_ModuleState_t;

STATIC PduR_ModuleState_t g_PduRModuleState = {PDUR_STATE_IDLE, NULL, 0u};

STATIC uint8_t PduR_IsRouteValid(const PduR_RouteTable_t *routeTable, PduR_RouteId_t routeId)
{
    if (routeTable == NULL || routeTable->routes == NULL)
    {
        return 0u;
    }

    if (routeId >= routeTable->routeCount)
    {
        return 0u;
    }

    return routeTable->routes[routeId].enabled ? 1u : 0u;
}

int PduR_Init(const PduR_RouteTable_t *routeTable)
{
    if (PduR_ValidateRoutes(routeTable) != PDUR_OK)
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    g_PduRModuleState.state = PDUR_STATE_READY;
    g_PduRModuleState.routeTable = routeTable;
    g_PduRModuleState.enabledMask = 0u;
    return PDUR_OK;
}

int PduR_Start(uint8_t startMode, uint32_t routeEnableMask)
{
    (void)startMode;
    if (g_PduRModuleState.state != PDUR_STATE_READY)
    {
        return PDUR_ERR_ROUTE_DISABLED;
    }

    g_PduRModuleState.enabledMask = routeEnableMask;
    g_PduRModuleState.state = PDUR_STATE_ACTIVE;
    return PDUR_OK;
}

int PduR_Stop(uint8_t stopMode)
{
    (void)stopMode;
    g_PduRModuleState.state = PDUR_STATE_READY;
    g_PduRModuleState.enabledMask = 0u;
    return PDUR_OK;
}

int PduR_Deinit(void)
{
    g_PduRModuleState.state = PDUR_STATE_IDLE;
    g_PduRModuleState.routeTable = NULL;
    g_PduRModuleState.enabledMask = 0u;
    return PDUR_OK;
}

int PduR_ValidateRoutes(const PduR_RouteTable_t *routeTable)
{
    uint16_t i;

    if ((routeTable == NULL) || (routeTable->routes == NULL) ||
        (routeTable->routeCount == 0u) ||
        (routeTable->routeCount > PDUR_MAX_ROUTES))
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    for (i = 0u; i < routeTable->routeCount; ++i)
    {
        const PduR_RouteConfig_t *route = &routeTable->routes[i];
        if ((route->routeId != i) ||
            (route->sourceEndpoint >= PDUR_MAX_ENDPOINTS) ||
            (route->destinationEndpoint >= PDUR_MAX_ENDPOINTS) ||
            ((route->direction != PDUR_DIRECTION_TX) &&
             (route->direction != PDUR_DIRECTION_RX) &&
             (route->direction != PDUR_DIRECTION_BOTH)))
        {
            return PDUR_ERR_INVALID_ROUTE;
        }
        if (routeTable->routes[i].sourceEndpoint == routeTable->routes[i].destinationEndpoint)
        {
            return PDUR_ERR_INVALID_ROUTE;
        }
        if (routeTable->routes[i].direction == PDUR_DIRECTION_BOTH)
        {
            continue;
        }
        if (routeTable->routes[i].allowedLength == 0u)
        {
            return PDUR_ERR_INVALID_LENGTH;
        }
    }

    return PDUR_OK;
}

int PduR_Transmit(PduR_EndpointId_t sourceEndpoint,
                 PduR_PduId_t pduId,
                 const uint8_t *payload,
                 uint8_t payloadLength,
                 PduR_RouteContext_t *routeContext)
{
    const PduR_RouteTable_t *routeTable = g_PduRModuleState.routeTable;
    uint16_t i;

    if ((routeTable == NULL) || (routeTable->routes == NULL) ||
        (g_PduRModuleState.state != PDUR_STATE_ACTIVE))
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    for (i = 0u; i < routeTable->routeCount; ++i)
    {
        const PduR_RouteConfig_t *route = &routeTable->routes[i];
        if ((route->sourceEndpoint == sourceEndpoint) &&
            (route->sourcePduId == pduId) &&
            (route->direction == PDUR_DIRECTION_TX))
        {
            if ((route->enabled == 0u) ||
                ((g_PduRModuleState.enabledMask &
                  ((uint32_t)1u << route->routeId)) == 0u))
            {
                return PDUR_ERR_ROUTE_DISABLED;
            }
            if ((payloadLength > route->allowedLength) ||
                ((payload == NULL) && (payloadLength > 0u)))
            {
                return PDUR_ERR_INVALID_LENGTH;
            }

            if (CanIf_Transmit(CANIF_CONTROLLER_ID, CANIF_CHANNEL_ID,
                               route->destinationPduId, payload,
                               payloadLength, 0u) != CANIF_OK)
            {
                return PDUR_ERR_DEST_UNAVAILABLE;
            }

            if (routeContext != NULL)
            {
                routeContext->sourceEndpoint = sourceEndpoint;
                routeContext->destinationEndpoint = route->destinationEndpoint;
                routeContext->direction = route->direction;
                routeContext->pduId = pduId;
                routeContext->buffer = (uint8_t *)payload;
                routeContext->length = payloadLength;
                routeContext->confirmationCallbackConfigured = route->routeCompatibility;
                routeContext->statusCode = PDUR_OK;
            }
            return PDUR_OK;
        }
    }

    return PDUR_ERR_INVALID_ROUTE;
}

int PduR_ReceiveIndication(PduR_EndpointId_t sourceEndpoint,
                          PduR_PduId_t pduId,
                          const uint8_t *payload,
                          uint8_t payloadLength)
{
    const PduR_RouteTable_t *routeTable = g_PduRModuleState.routeTable;
    uint16_t i;

    if ((routeTable == NULL) || (routeTable->routes == NULL) ||
        (g_PduRModuleState.state != PDUR_STATE_ACTIVE))
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    for (i = 0u; i < routeTable->routeCount; ++i)
    {
        const PduR_RouteConfig_t *route = &routeTable->routes[i];
        if ((route->sourceEndpoint == sourceEndpoint) &&
            (route->sourcePduId == pduId) &&
            (route->direction == PDUR_DIRECTION_RX))
        {
            if ((route->enabled == 0u) ||
                ((g_PduRModuleState.enabledMask &
                  ((uint32_t)1u << route->routeId)) == 0u))
            {
                return PDUR_ERR_ROUTE_DISABLED;
            }
            if (payloadLength > route->allowedLength)
            {
                return PDUR_ERR_INVALID_LENGTH;
            }
            if (payload == NULL && payloadLength > 0u)
            {
                return PDUR_ERR_INVALID_LENGTH;
            }
            if (Com_ProcessRx(route->destinationPduId, payload,
                              payloadLength) != COM_STATUS_OK)
            {
                return PDUR_ERR_DEST_UNAVAILABLE;
            }
            if (routeTable->status != NULL)
            {
                routeTable->status[route->routeId].valid = PDUR_TRUE;
                routeTable->status[route->routeId].lastReceiveResult = PDUR_OK;
                routeTable->status[route->routeId].counter += 1u;
            }
            return PDUR_OK;
        }
    }

    return PDUR_ERR_INVALID_ROUTE;
}

int PduR_ConfirmTx(PduR_RouteId_t routeId,
                  PduR_PduId_t pduId,
                  uint8_t result,
                  uint8_t confirmationStatus)
{
    const PduR_RouteTable_t *routeTable = g_PduRModuleState.routeTable;
    PduR_RouteStatus_t *routeStatus;

    if (routeTable == NULL || routeTable->status == NULL)
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    if (!PduR_IsRouteValid(routeTable, routeId))
    {
        return PDUR_ERR_INVALID_ROUTE;
    }
    if ((routeTable->routes[routeId].direction != PDUR_DIRECTION_TX) ||
        (routeTable->routes[routeId].sourcePduId != pduId))
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    routeStatus = &routeTable->status[routeId];
    routeStatus->valid = PDUR_TRUE;
    routeStatus->lastResult = result;
    routeStatus->errorSnapshot = confirmationStatus;
    routeStatus->counter += 1u;
    return PDUR_OK;
}

int PduR_GetRouteStatus(PduR_RouteId_t routeId, PduR_RouteStatus_t *status)
{
    const PduR_RouteTable_t *routeTable = g_PduRModuleState.routeTable;

    if (routeTable == NULL || routeTable->status == NULL || status == NULL)
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    if (!PduR_IsRouteValid(routeTable, routeId))
    {
        return PDUR_ERR_INVALID_ROUTE;
    }

    *status = routeTable->status[routeId];
    return PDUR_OK;
}

int PduR_RegisterDiagEndpoint(PduR_EndpointId_t endpointId,
                             const PduR_EndpointConfig_t *endpointConfig,
                             uint8_t routeCount)
{
    (void)endpointId;
    (void)endpointConfig;
    (void)routeCount;
    return PDUR_OK;
}

int PduR_RegisterLinEndpoint(PduR_EndpointId_t endpointId,
                            const PduR_EndpointConfig_t *endpointConfig,
                            uint8_t routeCount)
{
    (void)endpointId;
    (void)endpointConfig;
    (void)routeCount;
    return PDUR_OK;
}

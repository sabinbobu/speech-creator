#ifndef PDUR_H
#define PDUR_H

#include "PduR_Types.h"
#include "PduR_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const PduR_RouteTable_t PduR_Config;

extern int PduR_Init(const PduR_RouteTable_t *routeTable);
extern int PduR_Start(uint8_t startMode, uint32_t routeEnableMask);
extern int PduR_Stop(uint8_t stopMode);
extern int PduR_Deinit(void);
extern int PduR_ValidateRoutes(const PduR_RouteTable_t *routeTable);

extern int PduR_Transmit(PduR_EndpointId_t sourceEndpoint,
                         PduR_PduId_t pduId,
                         const uint8_t *payload,
                         uint8_t payloadLength,
                         PduR_RouteContext_t *routeContext);
extern int PduR_ReceiveIndication(PduR_EndpointId_t sourceEndpoint,
                                 PduR_PduId_t pduId,
                                 const uint8_t *payload,
                                 uint8_t payloadLength);
extern int PduR_ConfirmTx(PduR_RouteId_t routeId,
                         PduR_PduId_t pduId,
                         uint8_t result,
                         uint8_t confirmationStatus);
extern int PduR_GetRouteStatus(PduR_RouteId_t routeId, PduR_RouteStatus_t *status);

extern int PduR_RegisterDiagEndpoint(PduR_EndpointId_t endpointId,
                                     const PduR_EndpointConfig_t *endpointConfig,
                                     uint8_t routeCount);
extern int PduR_RegisterLinEndpoint(PduR_EndpointId_t endpointId,
                                    const PduR_EndpointConfig_t *endpointConfig,
                                    uint8_t routeCount);

#ifdef __cplusplus
}
#endif

#endif

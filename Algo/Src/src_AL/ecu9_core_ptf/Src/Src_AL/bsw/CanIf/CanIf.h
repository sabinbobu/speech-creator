#ifndef CANIF_H
#define CANIF_H

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const CanIf_Config_t CanIf_Config;

extern volatile uint32_t CanIf_TxRequestCount;
extern volatile uint32_t CanIf_TxAcceptedCount;
extern volatile uint32_t CanIf_TxConfirmationCount;
extern volatile uint32_t CanIf_RxIndicationCount;
extern volatile uint32_t CanIf_RxMatchedCount;
extern volatile uint32_t CanIf_RxUnmatchedCount;
extern volatile uint32_t CanIf_RxForwardedCount;
extern volatile uint32_t CanIf_LastRxCanId;
extern volatile uint16_t CanIf_LastRxHoh;
extern volatile int CanIf_LastTxResult;
extern volatile int CanIf_LastRxResult;

extern int CanIf_Init(const CanIf_Config_t *config);
extern int CanIf_Start(uint8_t channelEnableMask, uint8_t controllerEnableMask);
extern int CanIf_Stop(uint8_t channelMask);
extern int CanIf_Deinit(void);
extern int CanIf_ValidateConfig(const CanIf_Config_t *config);

extern int CanIf_Transmit(CanIf_ControllerId_t controllerId,
                          CanIf_ChannelId_t channelId,
                          CanIf_PduId_t pduId,
                          const uint8_t *payload,
                          uint8_t payloadLength,
                          uint8_t requestMetadata);
extern int CanIf_ReceiveIndication(CanIf_ControllerId_t controllerId,
                                  CanIf_ChannelId_t channelId,
                                  CanIf_PduId_t pduId,
                                  const uint8_t *payload,
                                  uint8_t payloadLength);
extern int CanIf_ReportTxConfirmation(CanIf_ControllerId_t controllerId,
                                     CanIf_ChannelId_t channelId,
                                     CanIf_PduId_t pduId,
                                     uint8_t confirmationResult);
extern int CanIf_RxIndicationStatus(CanIf_ControllerId_t controllerId,
                                   CanIf_ChannelId_t channelId,
                                   CanIf_PduId_t pduId,
                                   uint8_t *statusOut);

extern int CanIf_GetControllerStatus(CanIf_ControllerId_t controllerId,
                                    CanIf_ControllerStatus_t *statusOut);
extern int CanIf_SetControllerState(CanIf_ControllerId_t controllerId,
                                   uint8_t targetState,
                                   uint8_t reasonCode);
extern int CanIf_ReportBusError(CanIf_ControllerId_t controllerId,
                               uint8_t errorCode,
                               uint8_t severity,
                               uint32_t context);
extern int CanIf_ResetController(CanIf_ControllerId_t controllerId, uint8_t recoveryMode);

#ifdef __cplusplus
}
#endif

#endif

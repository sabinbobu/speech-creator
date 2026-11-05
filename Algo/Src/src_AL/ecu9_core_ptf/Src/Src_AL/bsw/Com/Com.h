#ifndef COM_H
#define COM_H

#include "Com_Types.h"
#include "Com_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const Com_Config_t Com_Config;

extern FUNC(Com_Status_t, COM_CODE) Com_Init(const Com_Config_t *config);
extern FUNC(Com_Status_t, COM_CODE) Com_Start(void);
extern FUNC(Com_Status_t, COM_CODE) Com_Stop(void);
extern FUNC(Com_Status_t, COM_CODE) Com_Deinit(void);
extern FUNC(Com_Status_t, COM_CODE) Com_ValidateConfig(const Com_Config_t *config);
extern FUNC(void, COM_CODE) Com_MainFunctionTx(void);

extern FUNC(Com_Status_t, COM_CODE) Com_ReadSignal(Com_SignalId_t signalId,
                                                  uint32_t *outValue,
                                                  Com_SignalStatus_t *outStatus);
extern FUNC(Com_Status_t, COM_CODE) Com_WriteSignal(Com_SignalId_t signalId,
                                                   uint32_t value,
                                                   uint8_t writeContext);
extern FUNC(Com_Status_t, COM_CODE) Com_GetSignalStatus(Com_SignalId_t signalId,
                                                        Com_SignalStatus_t *status);
extern FUNC(Com_Status_t, COM_CODE) Com_SetSignalStatus(Com_SignalId_t signalId,
                                                        uint8_t valid,
                                                        uint8_t stale,
                                                        uint8_t timeout,
                                                        uint8_t invalid);
extern FUNC(Com_Status_t, COM_CODE) Com_NotifySignalChanged(Com_SignalId_t signalId,
                                                            Com_NotificationType_t policy);

extern FUNC(Com_Status_t, COM_CODE) Com_ProcessTx(uint32_t tick,
                                                 const Com_PduMeta_t *pduList,
                                                 uint16_t pduCount,
                                                 uint8_t *outputBuffer,
                                                 uint16_t outputBufferLength,
                                                 uint16_t *writtenLength);
extern FUNC(Com_Status_t, COM_CODE) Com_ProcessRx(Com_PduId_t pduId,
                                                 const uint8_t *payload,
                                                 uint16_t payloadLength);
extern FUNC(Com_Status_t, COM_CODE) Com_EncodePdu(Com_PduId_t pduId,
                                                uint8_t *payload,
                                                uint16_t payloadCapacity,
                                                uint16_t *payloadLength);
extern FUNC(Com_Status_t, COM_CODE) Com_DecodePdu(Com_PduId_t pduId,
                                                const uint8_t *payload,
                                                uint16_t payloadLength);

extern FUNC(Com_Status_t, COM_CODE) Com_CheckTimeouts(uint32_t nowTick);
extern FUNC(Com_Status_t, COM_CODE) Com_UpdateAliveCounter(Com_PduId_t pduId,
                                                          uint32_t aliveValue);
extern FUNC(Com_Status_t, COM_CODE) Com_ValidateE2E(Com_PduId_t pduId,
                                                  const uint8_t *payload,
                                                  uint16_t payloadLength);

#ifdef __cplusplus
}
#endif

#endif

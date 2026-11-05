#include "CanIf.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "PduR.h"

#define CANIF_STATE_IDLE       (0u)
#define CANIF_STATE_READY      (1u)
#define CANIF_STATE_ACTIVE     (2u)

typedef struct
{
    uint8_t state;
    const CanIf_Config_t *config;
    uint8_t channelMask;
    uint8_t controllerMask;
    uint8_t busOff;
} CanIf_ModuleState_t;

STATIC CanIf_ModuleState_t g_CanIfModuleState =
    {CANIF_STATE_IDLE, NULL, 0u, 0u, 0u};

STATIC uint8_t g_CanIfControllerStarted = 0u;

volatile uint32_t CanIf_TxRequestCount;
volatile uint32_t CanIf_TxAcceptedCount;
volatile uint32_t CanIf_TxConfirmationCount;
volatile uint32_t CanIf_RxIndicationCount;
volatile uint32_t CanIf_RxMatchedCount;
volatile uint32_t CanIf_RxUnmatchedCount;
volatile uint32_t CanIf_RxForwardedCount;
volatile uint32_t CanIf_LastRxCanId;
volatile uint16_t CanIf_LastRxHoh;
volatile int CanIf_LastTxResult;
volatile int CanIf_LastRxResult;

STATIC const CanIf_ObjectConfig_t *CanIf_FindObject(
    CanIf_PduId_t pduId,
    uint8_t direction,
    CanIf_ControllerId_t controllerId,
    CanIf_ChannelId_t channelId)
{
    uint16_t i;
    const CanIf_Config_t *config = g_CanIfModuleState.config;

    if (config == NULL)
    {
        return NULL;
    }

    for (i = 0u; i < config->objectCount; ++i)
    {
        const CanIf_ObjectConfig_t *object = &config->objects[i];
        if ((object->pduId == pduId) && (object->direction == direction) &&
            (object->enabled != 0u))
        {
            uint16_t channelIndex;
            for (channelIndex = 0u; channelIndex < config->channelCount;
                 ++channelIndex)
            {
                const CanIf_ChannelConfig_t *channel =
                    &config->channels[channelIndex];
                if ((channel->channelId == channelId) &&
                    (channel->controllerId == controllerId) &&
                    (((direction == CANIF_OBJECT_TX) &&
                      (channel->transmitEnabled != 0u)) ||
                     ((direction == CANIF_OBJECT_RX) &&
                      (channel->receiveEnabled != 0u))))
                {
                    return object;
                }
            }
        }
    }

    return NULL;
}

int CanIf_Init(const CanIf_Config_t *config)
{
    if (CanIf_ValidateConfig(config) != CANIF_OK)
    {
        return CANIF_ERR_INVALID_CONFIG;
    }

    g_CanIfModuleState.config = config;
    g_CanIfModuleState.state = CANIF_STATE_READY;
    g_CanIfControllerStarted = 0u;
    CanIf_TxRequestCount = 0u;
    CanIf_TxAcceptedCount = 0u;
    CanIf_TxConfirmationCount = 0u;
    CanIf_RxIndicationCount = 0u;
    CanIf_RxMatchedCount = 0u;
    CanIf_RxUnmatchedCount = 0u;
    CanIf_RxForwardedCount = 0u;
    CanIf_LastRxCanId = 0u;
    CanIf_LastRxHoh = 0u;
    CanIf_LastTxResult = CANIF_OK;
    CanIf_LastRxResult = CANIF_OK;
    return CANIF_OK;
}

int CanIf_Start(uint8_t channelEnableMask, uint8_t controllerEnableMask)
{
    if (g_CanIfModuleState.state != CANIF_STATE_READY)
    {
        return CANIF_ERR_INVALID_CONFIG;
    }

    g_CanIfModuleState.channelMask = channelEnableMask;
    g_CanIfModuleState.controllerMask = controllerEnableMask;
    g_CanIfModuleState.busOff = 0u;
    g_CanIfModuleState.state = CANIF_STATE_ACTIVE;
    return CANIF_OK;
}

int CanIf_Stop(uint8_t channelMask)
{
    (void)channelMask;
    g_CanIfModuleState.state = CANIF_STATE_READY;
    g_CanIfModuleState.channelMask = 0u;
    return CANIF_OK;
}

int CanIf_Deinit(void)
{
    g_CanIfModuleState.state = CANIF_STATE_IDLE;
    g_CanIfModuleState.config = NULL;
    g_CanIfModuleState.channelMask = 0u;
    g_CanIfModuleState.controllerMask = 0u;
    return CANIF_OK;
}

int CanIf_ValidateConfig(const CanIf_Config_t *config)
{
    uint16_t i;

    if ((config == NULL) || (config->controllers == NULL) ||
        (config->channels == NULL) || (config->objects == NULL) ||
        (config->controllerCount == 0u) ||
        (config->controllerCount > CANIF_MAX_CONTROLLERS) ||
        (config->channelCount == 0u) ||
        (config->channelCount > CANIF_MAX_CHANNELS) ||
        (config->objectCount == 0u) ||
        (config->objectCount > CANIF_MAX_OBJECTS))
    {
        return CANIF_ERR_INVALID_CONFIG;
    }

    for (i = 0u; i < config->controllerCount; ++i)
    {
        if (config->controllers[i].controllerId >= CANIF_MAX_CONTROLLERS)
        {
            return CANIF_ERR_INVALID_CONFIG;
        }
    }

    for (i = 0u; i < config->objectCount; ++i)
    {
        const CanIf_ObjectConfig_t *object = &config->objects[i];
        if ((object->objectId >= CANIF_MAX_OBJECTS) ||
            (object->pduId >= CANIF_MAX_OBJECTS) ||
            (object->canId > 0x7FFu) ||
            (object->length == 0u) ||
            (object->length > CANIF_MAX_PAYLOAD) ||
            ((object->direction != CANIF_OBJECT_TX) &&
             (object->direction != CANIF_OBJECT_RX)))
        {
            return CANIF_ERR_INVALID_CONFIG;
        }
    }

    return CANIF_OK;
}

int CanIf_Transmit(CanIf_ControllerId_t controllerId,
                  CanIf_ChannelId_t channelId,
                  CanIf_PduId_t pduId,
                  const uint8_t *payload,
                  uint8_t payloadLength,
                  uint8_t requestMetadata)
{
    const CanIf_ObjectConfig_t *object;
    Can_PduType canPdu;
    Std_ReturnType canResult;

    (void)requestMetadata;
    CanIf_TxRequestCount++;

    if ((g_CanIfModuleState.state != CANIF_STATE_ACTIVE) ||
        (g_CanIfControllerStarted == 0u) ||
        (g_CanIfModuleState.busOff != 0u))
    {
        CanIf_LastTxResult = CANIF_ERR_BUS_OFF;
        return CANIF_ERR_BUS_OFF;
    }

    object = CanIf_FindObject(pduId, CANIF_OBJECT_TX, controllerId, channelId);
    if (object == NULL)
    {
        CanIf_LastTxResult = CANIF_ERR_INVALID_OBJECT;
        return CANIF_ERR_INVALID_OBJECT;
    }

    if ((payload == NULL) || (payloadLength != object->length))
    {
        CanIf_LastTxResult = CANIF_ERR_INVALID_LENGTH;
        return CANIF_ERR_INVALID_LENGTH;
    }

    canPdu.swPduHandle = pduId;
    canPdu.length = payloadLength;
    canPdu.id = object->canId;
    canPdu.sdu = (uint8_t *)payload;

    canResult = Can_Write(object->objectId, &canPdu);
    if (canResult == E_OK)
    {
        CanIf_TxAcceptedCount++;
        CanIf_LastTxResult = CANIF_OK;
        return CANIF_OK;
    }
    CanIf_LastTxResult = (canResult == CAN_BUSY) ?
                         CANIF_ERR_CONTROLLER_FULL : CANIF_ERR_INTERNAL;
    return CanIf_LastTxResult;
}

int CanIf_ReceiveIndication(CanIf_ControllerId_t controllerId,
                          CanIf_ChannelId_t channelId,
                          CanIf_PduId_t pduId,
                          const uint8_t *payload,
                          uint8_t payloadLength)
{
    if ((payload == NULL) || (payloadLength == 0u) ||
        (payloadLength > CANIF_MAX_PAYLOAD))
    {
        return CANIF_ERR_INVALID_LENGTH;
    }

    if ((g_CanIfModuleState.state != CANIF_STATE_ACTIVE) ||
        (g_CanIfModuleState.busOff != 0u))
    {
        return CANIF_ERR_BUS_OFF;
    }

    if (CanIf_FindObject(pduId, CANIF_OBJECT_RX, controllerId, channelId) == NULL)
    {
        return CANIF_ERR_INVALID_OBJECT;
    }

    if (PduR_ReceiveIndication(CANIF_ENDPOINT_ID, pduId, payload,
                               payloadLength) == PDUR_OK)
    {
        CanIf_RxForwardedCount++;
        CanIf_LastRxResult = CANIF_OK;
        return CANIF_OK;
    }
    CanIf_LastRxResult = CANIF_ERR_ROUTE_REF;
    return CANIF_ERR_ROUTE_REF;
}

int CanIf_ReportTxConfirmation(CanIf_ControllerId_t controllerId,
                               CanIf_ChannelId_t channelId,
                               CanIf_PduId_t pduId,
                               uint8_t confirmationResult)
{
    const CanIf_ObjectConfig_t *object =
        CanIf_FindObject(pduId, CANIF_OBJECT_TX, controllerId, channelId);
    if (object == NULL)
    {
        return CANIF_ERR_INVALID_OBJECT;
    }
    return PduR_ConfirmTx(object->routeId, pduId, confirmationResult,
                          confirmationResult);
}

int CanIf_RxIndicationStatus(CanIf_ControllerId_t controllerId,
                           CanIf_ChannelId_t channelId,
                           CanIf_PduId_t pduId,
                           uint8_t *statusOut)
{
    (void)controllerId;
    (void)channelId;
    (void)pduId;
    if (statusOut == NULL)
    {
        return CANIF_ERR_INVALID_CONFIG;
    }
    *statusOut = CANIF_OK;
    return CANIF_OK;
}

int CanIf_GetControllerStatus(CanIf_ControllerId_t controllerId,
                            CanIf_ControllerStatus_t *statusOut)
{
    if (statusOut == NULL)
    {
        return CANIF_ERR_INVALID_CONFIG;
    }

    statusOut->controllerId = controllerId;
    statusOut->state = g_CanIfModuleState.state;
    statusOut->active = (g_CanIfModuleState.state == CANIF_STATE_ACTIVE) ?
                        1u : 0u;
    statusOut->ready = (g_CanIfModuleState.config != NULL) ? 1u : 0u;
    statusOut->busOff = g_CanIfModuleState.busOff;
    statusOut->errorCounter = 0u;
    statusOut->queueFull = 0u;
    return CANIF_OK;
}

int CanIf_SetControllerState(CanIf_ControllerId_t controllerId,
                           uint8_t targetState,
                           uint8_t reasonCode)
{
    (void)controllerId;
    (void)targetState;
    (void)reasonCode;
    return CANIF_OK;
}

int CanIf_ReportBusError(CanIf_ControllerId_t controllerId,
                       uint8_t errorCode,
                       uint8_t severity,
                       uint32_t context)
{
    (void)controllerId;
    (void)errorCode;
    (void)severity;
    (void)context;
    return CANIF_OK;
}

int CanIf_ResetController(CanIf_ControllerId_t controllerId, uint8_t recoveryMode)
{
    (void)controllerId;
    (void)recoveryMode;
    return CANIF_OK;
}

void CanIf_ControllerBusOff(uint8 Controller)
{
    (void)Controller;
    g_CanIfModuleState.busOff = 1u;
    g_CanIfModuleState.state = CANIF_STATE_DEGRADED;
}

void CanIf_RxIndication(const Can_HwType *Mailbox,
                        const PduInfoType *PduInfoPtr)
{
    uint16_t i;
    const CanIf_Config_t *config = g_CanIfModuleState.config;

    CanIf_RxIndicationCount++;
    if ((config == NULL) || (Mailbox == NULL) || (PduInfoPtr == NULL) ||
        (PduInfoPtr->SduDataPtr == NULL))
    {
        CanIf_LastRxResult = CANIF_ERR_INVALID_CONFIG;
        return;
    }

    CanIf_LastRxCanId = Mailbox->CanId;
    CanIf_LastRxHoh = Mailbox->Hoh;
    for (i = 0u; i < config->objectCount; ++i)
    {
        const CanIf_ObjectConfig_t *object = &config->objects[i];
        if ((object->direction == CANIF_OBJECT_RX) &&
            (object->objectId == Mailbox->Hoh) &&
            (object->canId == Mailbox->CanId) &&
            (object->enabled != 0u))
        {
            CanIf_RxMatchedCount++;
            CanIf_LastRxResult =
                CanIf_ReceiveIndication(Mailbox->ControllerId,
                    CANIF_CHANNEL_ID, object->pduId,
                    PduInfoPtr->SduDataPtr,
                    (uint8_t)PduInfoPtr->SduLength);
            return;
        }
    }
    CanIf_RxUnmatchedCount++;
    CanIf_LastRxResult = CANIF_ERR_INVALID_OBJECT;
}

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    CanIf_TxConfirmationCount++;
    (void)CanIf_ReportTxConfirmation(CANIF_CONTROLLER_ID, CANIF_CHANNEL_ID,
                                    (CanIf_PduId_t)CanTxPduId, E_OK);
}

void CanIf_ControllerModeIndication(uint8 ControllerId,
                                    Can_ControllerStateType ControllerMode)
{
    (void)ControllerId;
    g_CanIfControllerStarted = (ControllerMode == CAN_CS_STARTED) ? 1u : 0u;
    if (ControllerMode == CAN_CS_STARTED)
    {
        g_CanIfModuleState.state = CANIF_STATE_ACTIVE;
    }
    else if (ControllerMode == CAN_CS_STOPPED)
    {
        g_CanIfModuleState.state = CANIF_STATE_READY;
    }
    else
    {
        g_CanIfModuleState.state = CANIF_STATE_DEGRADED;
    }
}

Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId,
                                     PduInfoType *PduInfoPtr)
{
    (void)TxPduId;
    (void)PduInfoPtr;
    return E_NOT_OK;
}

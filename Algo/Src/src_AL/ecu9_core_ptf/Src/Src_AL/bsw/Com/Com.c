#include "Com.h"
#include "PduR.h"

#define COM_INIT_STATE_IDLE      (0u)
#define COM_INIT_STATE_READY     (1u)
#define COM_INIT_STATE_ACTIVE    (2u)

typedef struct
{
    uint8_t initialized;
    uint8_t active;
    uint32_t tick;
    const Com_Config_t *config;
    Com_NotificationQueue_t notifications;
} Com_ModuleState_t;

STATIC Com_ModuleState_t g_ComModuleState = {0u};
STATIC uint32_t g_ComLastTxTick[COM_MAX_PDUS] = {0u};
STATIC uint32_t g_ComTxTick;

STATIC uint8_t Com_IsSignalValid(const Com_Config_t *config, Com_SignalId_t signalId)
{
    uint16_t i;

    if ((config == NULL) || (config->signalTable == NULL) || (config->runtimeTable == NULL))
    {
        return 0u;
    }

    if (signalId >= config->signalCount)
    {
        return 0u;
    }

    for (i = 0u; i < config->signalCount; ++i)
    {
        if (config->signalTable[i].signalId == signalId)
        {
            return (config->signalTable[i].enabled != 0u) ? 1u : 0u;
        }
    }

    return 0u;
}

STATIC const Com_SignalMeta_t *Com_FindSignalMeta(const Com_Config_t *config, Com_SignalId_t signalId)
{
    uint16_t i;

    if (config == NULL || config->signalTable == NULL)
    {
        return NULL;
    }

    for (i = 0u; i < config->signalCount; ++i)
    {
        if (config->signalTable[i].signalId == signalId)
        {
            return &config->signalTable[i];
        }
    }

    return NULL;
}

STATIC uint8_t Com_QueuePush(Com_NotificationQueue_t *queue, const Com_Notification_t *item)
{
    uint8_t next;

    if ((queue == NULL) || (item == NULL))
    {
        return 0u;
    }

    if (queue->count >= COM_MAX_NOTIFICATIONS)
    {
        return 0u;
    }

    next = (uint8_t)((queue->head + queue->count) % COM_MAX_NOTIFICATIONS);
    queue->entries[next] = *item;
    queue->count += 1u;
    if (queue->count == 1u)
    {
        queue->head = next;
    }
    queue->tail = next;
    return 1u;
}

FUNC(Com_Status_t, COM_CODE) Com_Init(const Com_Config_t *config)
{
    uint16_t i;

    if ((config == NULL) || (config->signalTable == NULL) || (config->pduTable == NULL))
    {
        return COM_STATUS_INVALID_CONFIG;
    }

    if (Com_ValidateConfig(config) != COM_STATUS_OK)
    {
        return COM_STATUS_INVALID_CONFIG;
    }

    g_ComModuleState.config = config;
    g_ComModuleState.initialized = COM_INIT_STATE_READY;
    g_ComModuleState.active = COM_INIT_STATE_IDLE;
    g_ComModuleState.tick = 0u;
    g_ComModuleState.notifications.count = 0u;
    g_ComModuleState.notifications.head = 0u;
    g_ComModuleState.notifications.tail = 0u;
    for (i = 0u; i < config->signalCount; ++i)
    {
        config->runtimeTable[i].value = config->signalTable[i].defaultValue;
        config->runtimeTable[i].status.valid = config->signalTable[i].valid;
        config->runtimeTable[i].status.stale = COM_FALSE;
        config->runtimeTable[i].status.timeout = COM_FALSE;
        config->runtimeTable[i].status.invalid = COM_FALSE;
        config->runtimeTable[i].status.updateCount = 0u;
        config->runtimeTable[i].status.lastUpdateTick = 0u;
        config->runtimeTable[i].status.statusFlags = 0u;
    }
    for (i = 0u; i < COM_MAX_PDUS; ++i)
    {
        g_ComLastTxTick[i] = 0u;
    }
    g_ComTxTick = 0u;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_Start(void)
{
    if (g_ComModuleState.initialized != COM_INIT_STATE_READY)
    {
        return COM_STATUS_INVALID_CONFIG;
    }

    g_ComModuleState.active = COM_INIT_STATE_ACTIVE;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_Stop(void)
{
    g_ComModuleState.active = COM_INIT_STATE_IDLE;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_Deinit(void)
{
    g_ComModuleState.initialized = COM_INIT_STATE_IDLE;
    g_ComModuleState.active = COM_INIT_STATE_IDLE;
    g_ComModuleState.config = NULL;
    g_ComModuleState.notifications.count = 0u;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_ValidateConfig(const Com_Config_t *config)
{
    uint16_t i;

    if ((config == NULL) || (config->signalTable == NULL) ||
        (config->runtimeTable == NULL) || (config->pduTable == NULL) ||
        (config->signalCount == 0u) || (config->signalCount > COM_MAX_SIGNALS) ||
        (config->pduCount == 0u) || (config->pduCount > COM_MAX_PDUS))
    {
        return COM_STATUS_INVALID_CONFIG;
    }

    for (i = 0u; i < config->signalCount; ++i)
    {
        const Com_SignalMeta_t *signal = &config->signalTable[i];
        if ((signal->signalId >= config->signalCount) ||
            (signal->pduId >= config->pduCount) ||
            (signal->bitLength == 0u) || (signal->bitLength > 32u) ||
            (((uint16_t)signal->bitStart + signal->bitLength) >
             ((uint16_t)config->pduTable[signal->pduId].length * 8u)))
        {
            return COM_STATUS_INVALID_CONFIG;
        }
    }

    for (i = 0u; i < config->pduCount; ++i)
    {
        if ((config->pduTable[i].pduId >= config->pduCount) ||
            (config->pduTable[i].length == 0u) ||
            (config->pduTable[i].length > COM_MAX_PDU_LENGTH))
        {
            return COM_STATUS_INVALID_CONFIG;
        }
    }

    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_ReadSignal(Com_SignalId_t signalId,
                                            uint32_t *outValue,
                                            Com_SignalStatus_t *outStatus)
{
    const Com_SignalMeta_t *meta;
    const Com_Config_t *config = g_ComModuleState.config;
    uint16_t index;

    if (!Com_IsSignalValid(config, signalId))
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    meta = Com_FindSignalMeta(config, signalId);
    if (meta == NULL)
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    index = (uint16_t)signalId;
    if (index >= config->signalCount)
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    if (outValue != NULL)
    {
        *outValue = config->runtimeTable[index].value;
    }

    if (outStatus != NULL)
    {
        *outStatus = config->runtimeTable[index].status;
    }

    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_WriteSignal(Com_SignalId_t signalId,
                                             uint32_t value,
                                             uint8_t writeContext)
{
    const Com_Config_t *config = g_ComModuleState.config;
    const Com_SignalMeta_t *meta;
    uint16_t index;

    (void)writeContext;

    if (!Com_IsSignalValid(config, signalId))
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    meta = Com_FindSignalMeta(config, signalId);
    if (meta == NULL)
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    if (meta->direction == COM_SIGNAL_DIRECTION_RX)
    {
        return COM_STATUS_DIRECTION;
    }

    index = (uint16_t)signalId;
    config->runtimeTable[index].value = value;
    config->runtimeTable[index].status.valid = COM_TRUE;
    config->runtimeTable[index].status.updateCount += 1u;
    config->runtimeTable[index].status.lastUpdateTick = ++g_ComModuleState.tick;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_GetSignalStatus(Com_SignalId_t signalId,
                                                Com_SignalStatus_t *status)
{
    const Com_Config_t *config = g_ComModuleState.config;
    uint16_t index;

    if (!Com_IsSignalValid(config, signalId) || (status == NULL))
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    index = (uint16_t)signalId;
    *status = config->runtimeTable[index].status;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_SetSignalStatus(Com_SignalId_t signalId,
                                                uint8_t valid,
                                                uint8_t stale,
                                                uint8_t timeout,
                                                uint8_t invalid)
{
    const Com_Config_t *config = g_ComModuleState.config;
    uint16_t index;

    if (!Com_IsSignalValid(config, signalId))
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    index = (uint16_t)signalId;
    config->runtimeTable[index].status.valid = valid;
    config->runtimeTable[index].status.stale = stale;
    config->runtimeTable[index].status.timeout = timeout;
    config->runtimeTable[index].status.invalid = invalid;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_NotifySignalChanged(Com_SignalId_t signalId,
                                                    Com_NotificationType_t policy)
{
    Com_Notification_t notification;
    const Com_Config_t *config = g_ComModuleState.config;

    if (!Com_IsSignalValid(config, signalId))
    {
        return COM_STATUS_INVALID_SIGNAL;
    }

    notification.signalId = signalId;
    notification.type = policy;
    notification.timestamp = ++g_ComModuleState.tick;
    notification.reasonCode = COM_OK;
    notification.statusSnapshot = config->runtimeTable[signalId].status;

    if (!Com_QueuePush(&g_ComModuleState.notifications, &notification))
    {
        return COM_STATUS_QUEUE_FULL;
    }

    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_ProcessTx(uint32_t tick,
                                         const Com_PduMeta_t *pduList,
                                         uint16_t pduCount,
                                         uint8_t *outputBuffer,
                                         uint16_t outputBufferLength,
                                         uint16_t *writtenLength)
{
    uint16_t i;
    uint16_t totalLength = 0u;

    (void)tick;

    if ((pduList == NULL) || (outputBuffer == NULL) || (writtenLength == NULL))
    {
        return COM_STATUS_INVALID_PDU;
    }

    for (i = 0u; i < pduCount; ++i)
    {
        if (pduList[i].length > outputBufferLength)
        {
            return COM_STATUS_INVALID_PDU;
        }
        totalLength += pduList[i].length;
    }

    if (totalLength > outputBufferLength)
    {
        return COM_STATUS_INVALID_PDU;
    }

    *writtenLength = totalLength;
    for (i = 0u; i < totalLength; ++i)
    {
        outputBuffer[i] = (uint8_t)(i & 0xFFu);
    }

    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_ProcessRx(Com_PduId_t pduId,
                                         const uint8_t *payload,
                                         uint16_t payloadLength)
{
    return Com_DecodePdu(pduId, payload, payloadLength);
}

FUNC(Com_Status_t, COM_CODE) Com_EncodePdu(Com_PduId_t pduId,
                                        uint8_t *payload,
                                        uint16_t payloadCapacity,
                                        uint16_t *payloadLength)
{
    const Com_Config_t *config = g_ComModuleState.config;

    if (payload == NULL || payloadLength == NULL)
    {
        return COM_STATUS_INVALID_PDU;
    }

    if (config == NULL || pduId >= config->pduCount)
    {
        return COM_STATUS_INVALID_PDU;
    }

    if (payloadCapacity < config->pduTable[pduId].length)
    {
        return COM_STATUS_INVALID_PDU;
    }

    *payloadLength = config->pduTable[pduId].length;
    for (uint16_t i = 0u; i < *payloadLength; ++i)
    {
        payload[i] = 0u;
    }

    for (uint16_t i = 0u; i < config->signalCount; ++i)
    {
        const Com_SignalMeta_t *signal = &config->signalTable[i];
        uint32_t value;
        uint8_t bit;

        if ((signal->pduId != pduId) ||
            (signal->direction != COM_SIGNAL_DIRECTION_TX))
        {
            continue;
        }

        value = config->runtimeTable[signal->signalId].value;
        for (bit = 0u; bit < signal->bitLength; ++bit)
        {
            uint16_t payloadBit = (uint16_t)signal->bitStart + bit;
            if ((value & ((uint32_t)1u << bit)) != 0u)
            {
                payload[payloadBit / 8u] |= (uint8_t)(1u << (payloadBit % 8u));
            }
        }
    }

    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_DecodePdu(Com_PduId_t pduId,
                                        const uint8_t *payload,
                                        uint16_t payloadLength)
{
    const Com_Config_t *config = g_ComModuleState.config;

    if (payload == NULL)
    {
        return COM_STATUS_INVALID_PDU;
    }

    if (config == NULL || pduId >= config->pduCount)
    {
        return COM_STATUS_INVALID_PDU;
    }

    if ((payloadLength != config->pduTable[pduId].length) ||
        (payload == NULL))
    {
        return COM_STATUS_INVALID_PDU;
    }

    for (uint16_t i = 0u; i < config->signalCount; ++i)
    {
        const Com_SignalMeta_t *signal = &config->signalTable[i];
        uint32_t value = 0u;
        uint8_t bit;

        if ((signal->pduId != pduId) ||
            (signal->direction != COM_SIGNAL_DIRECTION_RX))
        {
            continue;
        }

        for (bit = 0u; bit < signal->bitLength; ++bit)
        {
            uint16_t payloadBit = (uint16_t)signal->bitStart + bit;
            if ((payload[payloadBit / 8u] &
                 (uint8_t)(1u << (payloadBit % 8u))) != 0u)
            {
                value |= (uint32_t)1u << bit;
            }
        }

        config->runtimeTable[signal->signalId].value = value;
        config->runtimeTable[signal->signalId].status.valid = COM_TRUE;
        config->runtimeTable[signal->signalId].status.stale = COM_FALSE;
        config->runtimeTable[signal->signalId].status.timeout = COM_FALSE;
        config->runtimeTable[signal->signalId].status.invalid = COM_FALSE;
        config->runtimeTable[signal->signalId].status.updateCount += 1u;
        config->runtimeTable[signal->signalId].status.lastUpdateTick =
            ++g_ComModuleState.tick;
    }

    return COM_STATUS_OK;
}

FUNC(void, COM_CODE) Com_MainFunctionTx(void)
{
    const Com_Config_t *config = g_ComModuleState.config;
    uint16_t i;
    uint8_t payload[COM_MAX_PDU_LENGTH];
    uint32_t nowTick = g_ComTxTick++;

    if ((config == NULL) || (g_ComModuleState.active != COM_INIT_STATE_ACTIVE))
    {
        return;
    }

    for (i = 0u; i < config->pduCount; ++i)
    {
        const Com_PduMeta_t *pdu = &config->pduTable[i];
        uint16_t payloadLength = 0u;
        uint8_t periodTicks;

        if (pdu->txRouteEnabled == 0u)
        {
            continue;
        }

        periodTicks = pdu->periodTicks;
        if ((periodTicks != 0u) &&
            ((uint32_t)(nowTick - g_ComLastTxTick[pdu->pduId]) < periodTicks))
        {
            continue;
        }

        if (Com_EncodePdu(pdu->pduId, payload, sizeof(payload),
                          &payloadLength) != COM_STATUS_OK)
        {
            return;
        }

        if (PduR_Transmit(COM_PDUR_ENDPOINT_ID, pdu->pduId, payload,
                          (uint8_t)payloadLength, NULL) != PDUR_OK)
        {
            return;
        }
        g_ComLastTxTick[pdu->pduId] = nowTick;
    }
}

FUNC(Com_Status_t, COM_CODE) Com_CheckTimeouts(uint32_t nowTick)
{
    const Com_Config_t *config = g_ComModuleState.config;
    uint16_t i;

    if (config == NULL)
    {
        return COM_STATUS_INVALID_CONFIG;
    }

    for (i = 0u; i < config->signalCount; ++i)
    {
        if (config->runtimeTable[i].status.timeout != 0u)
        {
            config->runtimeTable[i].status.stale = COM_TRUE;
        }
        if (config->signalTable[i].timeoutMs != 0u)
        {
            if ((nowTick - config->runtimeTable[i].status.lastUpdateTick) > config->signalTable[i].timeoutMs)
            {
                config->runtimeTable[i].status.timeout = COM_TRUE;
            }
        }
    }

    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_UpdateAliveCounter(Com_PduId_t pduId,
                                                  uint32_t aliveValue)
{
    const Com_Config_t *config = g_ComModuleState.config;

    if (config == NULL || pduId >= config->pduCount)
    {
        return COM_STATUS_INVALID_PDU;
    }

    config->pduTable[pduId].generationCounter = aliveValue;
    return COM_STATUS_OK;
}

FUNC(Com_Status_t, COM_CODE) Com_ValidateE2E(Com_PduId_t pduId,
                                          const uint8_t *payload,
                                          uint16_t payloadLength)
{
    const Com_Config_t *config = g_ComModuleState.config;

    (void)payload;
    (void)payloadLength;

    if (config == NULL || pduId >= config->pduCount)
    {
        return COM_STATUS_INVALID_PDU;
    }

    return COM_STATUS_OK;
}

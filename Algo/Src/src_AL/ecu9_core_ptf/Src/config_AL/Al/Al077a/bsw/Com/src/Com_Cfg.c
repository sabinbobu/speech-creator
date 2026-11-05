#include "Com.h"

static const Com_SignalMeta_t Com_SignalTable[] =
{
    {
        COM_SIGNAL_ID_SAMPLE_TX_COUNTER, COM_PDU_ID_SAMPLE_TX,
        COM_SIGNAL_DIRECTION_TX, 0u, 8u, 0u, 0u, 1u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_SAMPLE_TX_VALUE, COM_PDU_ID_SAMPLE_TX,
        COM_SIGNAL_DIRECTION_TX, 8u, 16u, 0u, 0u, 1u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_SAMPLE_RX_COUNTER, COM_PDU_ID_SAMPLE_RX,
        COM_SIGNAL_DIRECTION_RX, 0u, 8u, 0u, 100u, 0u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_SAMPLE_RX_VALUE, COM_PDU_ID_SAMPLE_RX,
        COM_SIGNAL_DIRECTION_RX, 8u, 16u, 0u, 100u, 0u, 1u,
        COM_NOTIFY_NONE
    }
};

static Com_SignalRuntime_t Com_SignalRuntime[4];

static Com_PduMeta_t Com_PduTable[] =
{
    {
        COM_PDU_ID_SAMPLE_TX, COM_PDU_DIRECTION_TX, 8u, 1u, 0u, 0u, 2u
    },
    {
        COM_PDU_ID_SAMPLE_RX, COM_PDU_DIRECTION_RX, 8u, 0u, 1u, 0u, 0u
    }
};

static Com_NotificationQueue_t Com_NotificationQueue;

const Com_Config_t Com_Config =
{
    4u,
    Com_SignalTable,
    Com_SignalRuntime,
    2u,
    Com_PduTable,
    0u,
    &Com_NotificationQueue
};

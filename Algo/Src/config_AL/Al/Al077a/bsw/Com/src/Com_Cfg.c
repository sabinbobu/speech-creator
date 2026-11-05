#include "Com.h"

static const Com_SignalMeta_t Com_SignalTable[] =
{
    {
        COM_SIGNAL_ID_ROLL_ANGLE, COM_PDU_ID_IMU_STATUS,
        COM_SIGNAL_DIRECTION_TX, 0u, 16u, 0u, 0u, 1u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_PITCH_ANGLE, COM_PDU_ID_IMU_STATUS,
        COM_SIGNAL_DIRECTION_TX, 16u, 16u, 0u, 0u, 1u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_YAW_ANGLE, COM_PDU_ID_IMU_STATUS,
        COM_SIGNAL_DIRECTION_TX, 32u, 16u, 0u, 0u, 1u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_VEHICLE_SPEED, COM_PDU_ID_BCM_STATUS,
        COM_SIGNAL_DIRECTION_RX, 0u, 16u, 0u, 100u, 0u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_IGNITION_STATUS, COM_PDU_ID_BCM_STATUS,
        COM_SIGNAL_DIRECTION_RX, 16u, 2u, 0u, 100u, 0u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_DRIVER_DOOR_OPEN, COM_PDU_ID_BCM_STATUS,
        COM_SIGNAL_DIRECTION_RX, 18u, 1u, 0u, 100u, 0u, 1u,
        COM_NOTIFY_NONE
    },
    {
        COM_SIGNAL_ID_OTHER_DOORS_OPEN, COM_PDU_ID_BCM_STATUS,
        COM_SIGNAL_DIRECTION_RX, 19u, 1u, 0u, 100u, 0u, 1u,
        COM_NOTIFY_NONE
    }
};

static Com_SignalRuntime_t Com_SignalRuntime[7];

static Com_PduMeta_t Com_PduTable[] =
{
    {
        COM_PDU_ID_IMU_STATUS, COM_PDU_DIRECTION_TX, 8u, 1u, 0u, 0u, 2u
    },
    {
        COM_PDU_ID_BCM_STATUS, COM_PDU_DIRECTION_RX, 8u, 0u, 1u, 0u, 0u
    }
};

static Com_NotificationQueue_t Com_NotificationQueue;

const Com_Config_t Com_Config =
{
    7u,
    Com_SignalTable,
    Com_SignalRuntime,
    2u,
    Com_PduTable,
    0u,
    &Com_NotificationQueue
};

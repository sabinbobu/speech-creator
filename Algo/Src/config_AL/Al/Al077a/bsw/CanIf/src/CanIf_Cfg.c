#include "CanIf.h"
#include "Can_Cfg.h"
#include "Com_Cfg.h"
#include "PduR_Cfg.h"

static const CanIf_ObjectConfig_t CanIf_Objects[] =
{
    {0u, COM_PDU_ID_IMU_STATUS, CANIF_CAN_ID_IMU_STATUS, CANIF_OBJECT_TX, 8u, 1u, PDUR_IMU_STATUS_TX_ROUTE_ID},
    {2u, COM_PDU_ID_BCM_STATUS, CANIF_CAN_ID_BCM_STATUS, CANIF_OBJECT_RX, 8u, 1u, PDUR_BCM_STATUS_RX_ROUTE_ID},
    {1u, COM_PDU_ID_FILTERED_PITCH, CANIF_CAN_ID_FILTERED_PITCH, CANIF_OBJECT_TX, 8u, 1u, PDUR_FILTERED_PITCH_TX_ROUTE_ID}
};

static const CanIf_ChannelConfig_t CanIf_Channels[] =
{
    {CANIF_CHANNEL_ID, CANIF_CONTROLLER_ID, 1u, 1u, 3u, CanIf_Objects}
};

static const CanIf_ControllerConfig_t CanIf_Controllers[] =
{
    {CANIF_CONTROLLER_ID, 1u, CanIf_Channels, 1u, 0u}
};

const CanIf_Config_t CanIf_Config =
{
    1u,
    1u,
    3u,
    CanIf_Controllers,
    CanIf_Channels,
    CanIf_Objects,
    1u
};

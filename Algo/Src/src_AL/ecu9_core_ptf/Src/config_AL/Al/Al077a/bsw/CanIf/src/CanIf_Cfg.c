#include "CanIf.h"
#include "Can_Cfg.h"
#include "Com_Cfg.h"
#include "PduR_Cfg.h"

static const CanIf_ObjectConfig_t CanIf_Objects[] =
{
    {0u, COM_PDU_ID_SAMPLE_TX, CANIF_CAN_ID_SAMPLE_TX, CANIF_OBJECT_TX, 8u, 1u, PDUR_SAMPLE_TX_ROUTE_ID},
    {2u, COM_PDU_ID_SAMPLE_RX, CANIF_CAN_ID_SAMPLE_RX, CANIF_OBJECT_RX, 8u, 1u, 1u}
};

static const CanIf_ChannelConfig_t CanIf_Channels[] =
{
    {CANIF_CHANNEL_ID, CANIF_CONTROLLER_ID, 1u, 1u, 2u, CanIf_Objects}
};

static const CanIf_ControllerConfig_t CanIf_Controllers[] =
{
    {CANIF_CONTROLLER_ID, 1u, CanIf_Channels, 1u, 0u}
};

const CanIf_Config_t CanIf_Config =
{
    1u,
    1u,
    2u,
    CanIf_Controllers,
    CanIf_Channels,
    CanIf_Objects,
    1u
};

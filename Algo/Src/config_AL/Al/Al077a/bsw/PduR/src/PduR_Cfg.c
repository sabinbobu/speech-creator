#include "PduR.h"
#include "Com_Cfg.h"
#include "PduR_Cfg.h"

static const PduR_RouteConfig_t PduR_Routes[] =
{
    {
        PDUR_IMU_STATUS_TX_ROUTE_ID,
        COM_PDU_ID_IMU_STATUS,
        COM_PDU_ID_IMU_STATUS,
        PDUR_ENDPOINT_COM,
        PDUR_ENDPOINT_CANIF,
        PDUR_DIRECTION_TX,
        8u,
        PDUR_OWNERSHIP_TRANSIENT,
        1u,
        0u
    },
    {
        PDUR_BCM_STATUS_RX_ROUTE_ID,
        COM_PDU_ID_BCM_STATUS,
        COM_PDU_ID_BCM_STATUS,
        PDUR_ENDPOINT_CANIF,
        PDUR_ENDPOINT_COM,
        PDUR_DIRECTION_RX,
        8u,
        PDUR_OWNERSHIP_TRANSIENT,
        PDUR_BCM_STATUS_RX_ROUTE_ID,
        0u
    }
};

static PduR_RouteStatus_t PduR_RouteStatus[2];

static const PduR_EndpointConfig_t PduR_Endpoints[] =
{
    {PDUR_ENDPOINT_COM, 0u, 1u, 2u, PDUR_OWNERSHIP_TRANSIENT, 1u},
    {PDUR_ENDPOINT_CANIF, 1u, 1u, 2u, PDUR_OWNERSHIP_TRANSIENT, 1u}
};

const PduR_RouteTable_t PduR_Config =
{
    2u,
    PduR_Routes,
    PduR_RouteStatus,
    2u,
    PduR_Endpoints
};

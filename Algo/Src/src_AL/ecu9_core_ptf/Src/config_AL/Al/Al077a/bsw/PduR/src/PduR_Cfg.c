#include "PduR.h"
#include "Com_Cfg.h"
#include "PduR_Cfg.h"

static const PduR_RouteConfig_t PduR_Routes[] =
{
    {
        PDUR_SAMPLE_TX_ROUTE_ID,
        COM_PDU_ID_SAMPLE_TX,
        COM_PDU_ID_SAMPLE_TX,
        PDUR_ENDPOINT_COM,
        PDUR_ENDPOINT_CANIF,
        PDUR_DIRECTION_TX,
        8u,
        PDUR_OWNERSHIP_TRANSIENT,
        1u,
        0u
    },
    {
        1u,
        COM_PDU_ID_SAMPLE_RX,
        COM_PDU_ID_SAMPLE_RX,
        PDUR_ENDPOINT_CANIF,
        PDUR_ENDPOINT_COM,
        PDUR_DIRECTION_RX,
        8u,
        PDUR_OWNERSHIP_TRANSIENT,
        1u,
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

#ifndef COM_CFG_H
#define COM_CFG_H

#define COM_MAX_SIGNALS          (32u)
#define COM_MAX_PDUS             (16u)
#define COM_MAX_NOTIFICATIONS    (8u)
#define COM_MAX_PDU_LENGTH       (8u)

#define COM_FEATURE_TIMEOUT      (0x01u)
#define COM_FEATURE_ALIVE        (0x02u)
#define COM_FEATURE_E2E          (0x04u)

#define COM_PDU_DIRECTION_TX     (0u)
#define COM_PDU_DIRECTION_RX     (1u)
#define COM_PDUR_ENDPOINT_ID     (1u)

#define COM_PDU_ID_SAMPLE_TX     (0u)
#define COM_PDU_ID_SAMPLE_RX     (1u)

#define COM_SIGNAL_ID_SAMPLE_TX_COUNTER (0u)
#define COM_SIGNAL_ID_SAMPLE_TX_VALUE   (1u)
#define COM_SIGNAL_ID_SAMPLE_RX_COUNTER (2u)
#define COM_SIGNAL_ID_SAMPLE_RX_VALUE   (3u)

#endif

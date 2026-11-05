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

#define COM_PDU_ID_IMU_STATUS    (0u)
#define COM_PDU_ID_BCM_STATUS    (1u)

#define COM_SIGNAL_ID_ROLL_ANGLE       (0u)
#define COM_SIGNAL_ID_PITCH_ANGLE      (1u)
#define COM_SIGNAL_ID_YAW_ANGLE        (2u)
#define COM_SIGNAL_ID_VEHICLE_SPEED    (3u)
#define COM_SIGNAL_ID_IGNITION_STATUS  (4u)
#define COM_SIGNAL_ID_DRIVER_DOOR_OPEN (5u)
#define COM_SIGNAL_ID_OTHER_DOORS_OPEN (6u)

#endif

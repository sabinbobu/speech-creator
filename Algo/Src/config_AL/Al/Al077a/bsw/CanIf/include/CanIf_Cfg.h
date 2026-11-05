#ifndef CANIF_CFG_H
#define CANIF_CFG_H

#define CANIF_MAX_CONTROLLERS   (4u)
#define CANIF_MAX_CHANNELS      (8u)
#define CANIF_MAX_OBJECTS       (32u)
#define CANIF_MAX_PAYLOAD       (8u)

#define CANIF_ENDPOINT_ID       (2u)
#define CANIF_CONTROLLER_ID     (0u)
#define CANIF_CHANNEL_ID        (0u)
#define CANIF_CAN_ID_IMU_STATUS (0x200u)
#define CANIF_CAN_ID_BCM_STATUS (0x100u)

#define CANIF_OBJECT_TX         (0u)
#define CANIF_OBJECT_RX         (1u)

#endif

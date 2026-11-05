#ifndef SWC_CAN_DEMO_H
#define SWC_CAN_DEMO_H

#include "Std_Types.h"

#define SWC_CAN_DEMO_STATUS_ACTIVE (0U)
#define SWC_CAN_DEMO_STATUS_ERROR  (1U)

extern volatile uint8 SwcCanDemo_Status;
extern volatile uint8 SwcCanDemo_TxCounter;
extern volatile uint16 SwcCanDemo_TxValue;
extern volatile uint32 SwcCanDemo_TxErrorCount;
extern volatile uint32 SwcCanDemo_RxFrameCount;
extern volatile uint8 SwcCanDemo_RxCounter;
extern volatile uint16 SwcCanDemo_RxValue;

void swc_can_demo_init(void);
void swc_can_demo_MainFunction(void);

#endif

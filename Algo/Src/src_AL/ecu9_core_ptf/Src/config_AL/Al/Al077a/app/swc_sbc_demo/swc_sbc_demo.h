#ifndef SWC_SBC_DEMO_H
#define SWC_SBC_DEMO_H

#include "Std_Types.h"

#define SWC_SBC_DEMO_INIT_PENDING (0U)
#define SWC_SBC_DEMO_INIT_READY   (1U)
#define SWC_SBC_DEMO_INIT_ERROR   (2U)

extern volatile uint8 SwcSbcDemo_InitState;

void swc_sbc_demo_init(void);
void swc_sbc_demo_MainFunction(void);
void swc_sbc_demo_SpiSequenceEndNotification(void);

#endif /* SWC_SBC_DEMO_H */

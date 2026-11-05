#ifndef CDD_SBC_CFG_2019_08_14_H_
  #define CDD_SBC_CFG_2019_08_14_H_

#include <CddTle94x1_Types.h>
#include <AL_Helper.h>

//===============================================================
//                   User Configuration
//===============================================================
#define CDDSBC_CFG_INIT_OPERATION                         STD_ON
#define CDDSBC_CFG_STORE_RESETREASON                      STD_ON
#define CDDSBC_CFG_SLEEPMODE                              STD_ON
#define CDDSBC_CFG_WATCHDOG                               STD_ON
#define CDDSBC_CFG_CYCLIC_OPERATION                       STD_ON
#define CDDSBC_CFG_CAN_OPERATION                          STD_ON
#define CDDSBC_CFG_WK_INPUT                               STD_OFF
#define CDDSBC_CFG_VCC2_OPERATION                         STD_ON
#define CDDSBC_CFG_GPIO                                   STD_ON


//===============================================================
//                    CAN CONFIGURATION
//===============================================================
#define CDDSBC_CFG_CAN_CHANNEL_0_INIT_CFG           CDDTLE94X1_CFG_CAN_NORMAL

#define CDDSBC_CFG_CAN_CH0                          0u // only CAN0 is used

//===============================================================
//              SEQUENCE ERROR CONFIGURATION
//===============================================================
// The error will be reported if the SPI Cyclic communication 
// fails multiple 500 times in a row.
// 
// The SPI cyclic is called every 1ms => 500ms SPI timeout
//===============================================================
#define CDDSBC_CFG_MAX_CYCLIC_SEQ_ERRORS                    500u

#define CDDSBC_CFG_MAX_READ_ATTEMPTS                         10u
#define CDDSBC_CFG_MAX_WRITE_ATTEMPTS                        10u

#define CDDSBC_CFG_MAX_SPI_SCHED_QUEUE                       20u

//===============================================================
//                VCC2 ERROR THRESHOLD
//===============================================================
#define CDDTLE94X1_CFG_VCC2_SHORT2VBAT_THRESHOLD            5820u
#define CDDTLE94X1_CFG_VCC2_SHORT2VGND_THRESHOLD            4000u

#endif /* CDD_SBC_CFG_2019_08_14_H_ */

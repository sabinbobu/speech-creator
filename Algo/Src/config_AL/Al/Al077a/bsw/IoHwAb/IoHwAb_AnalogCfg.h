/******************************************************************************/
/*
| (C) Marelli Automotive Lighting - ALIT-TO                                    |
|     Strada del Drosso 29, 10135 Torino (IT)                                  |
|                                                                              |
| Marelli Automotive Lighting owns all the rights to this work.                |
| This work shall not be copied, reproduced, used, modified, transferred       |
| or its information shall not be disclosed without the prior written          |
| authorization of Marelli Automotive Lighting.                                |
*/
/******************************************************************************/
/*!
* \file     IoHwAb_AnalogCfg.h
*
* \brief    IoHwAb analog configuration header
*
* \descr    Static configuration interface for IoHwAb analog channels.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef IOHWAB_ANALOG_CFG_H
#define IOHWAB_ANALOG_CFG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/
#define IOHWAB_ADC_NUM_OF_GROUPS                                            (2U)
#define IOHWAB_ADC_NUM_OF_CHS                                              (12U)

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef enum
{
  IOHWAB_CHID_EXT_4 = 0U,
  IOHWAB_CHID_ADIN_3,
  IOHWAB_CHID_EXT_6,
  IOHWAB_CHID_EXT_1,
  IOHWAB_CHID_LED3,
  IOHWAB_CHID_ADIN_2,
  IOHWAB_CHID_LED2,
  IOHWAB_CHID_EXT_5,
  IOHWAB_CHID_LED4,
  IOHWAB_CHID_HSS_SENSE_1_2,
  IOHWAB_CHID_EXT_2,
  IOHWAB_CHID_EXT_3,
  IOHWAB_CHID_ADIN_1,
  IOHWAB_CHID_PCB_NTC,
  IOHWAB_CHID_EXT_7,
  IOHWAB_CHID_LED5,
  IOHWAB_CHID_LED1,
  IOHWAB_CHID_VBAT,
  IOHWAB_CHID_LR_DETECTION,
  IOHWAB_CHID_VBOOST,
  IOHWAB_NUM_OF_ANALOG_CHS
} IoHwAb_AnalogChannelIdType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/
extern CONST(IoHwAb_AdcCfgType, IOHWAB_CONST) IoHwAb_AdcCfg[IOHWAB_ADC_NUM_OF_GROUPS];
extern CONST(IoHwAb_AnalogChannelCfgType, IOHWAB_CONST) IoHwAb_AnalogChannelCfg[IOHWAB_NUM_OF_ANALOG_CHS];

/*______ L O C A L - D A T A _________________________________________________*/
  
/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/

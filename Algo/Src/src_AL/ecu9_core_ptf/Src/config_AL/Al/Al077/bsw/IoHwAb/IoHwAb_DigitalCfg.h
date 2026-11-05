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
* \file     IoHwAb_DigitalCfg.h
*
* \brief    IoHwAb digital configuration header
*
* \descr    Static configuration interface for IoHwAb digital channels.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef IOHWAB_DIGITAL_CFG_H
#define IOHWAB_DIGITAL_CFG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef enum
{
  IOHWAB_CHID_HSS_1_EN = 0U,
  IOHWAB_CHID_HSS_SEL_1,
  IOHWAB_CHID_EN_LWR,
  IOHWAB_CHID_HSS_2_EN,
  IOHWAB_CHID_HSS_SEN,
  IOHWAB_CHID_5V0_EN,
  IOHWAB_CHID_5V0_PG,
  IOHWAB_NUM_OF_DIGITAL_CHS
} IoHwAb_DigitalChannelIdType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/
extern CONST(IoHwAb_DigitalChannelCfgType, IOHWAB_CONST) IoHwAb_DigitalChannelCfg[IOHWAB_NUM_OF_DIGITAL_CHS];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/

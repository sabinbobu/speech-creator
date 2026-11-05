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
* \file     IoHwAb_TimingCfg.h
*
* \brief    IoHwAb timing configuration header
*
* \descr    Static configuration interface for IoHwAb timing channels.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#ifndef IOHWAB_TIMING_CFG_H
#define IOHWAB_TIMING_CFG_H

#include "IoHwAb_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef enum
{
  IOHWAB_CHID_CTRL_LWR = 0U,
  IOHWAB_CHID_GPIO_SENS_2,
  IOHWAB_CHID_LEDCTRL3,
  IOHWAB_CHID_LEDCTRL5,
  IOHWAB_CHID_LEDCTRL2,
  IOHWAB_CHID_LEDCTRL1,
  IOHWAB_CHID_LEDCTRL4,
  IOHWAB_CHID_LEDCTRL6,
  IOHWAB_CHID_GPIO_SENS_1,
  IOHWAB_CHID_BSTSYNC,
  IOHWAB_NUM_OF_TIMING_CHS
} IoHwAb_TimingChannelIdType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/
extern CONST(IoHwAb_TimingChannelCfgType, IOHWAB_CONST) IoHwAb_TimingChannelCfg[IOHWAB_NUM_OF_TIMING_CHS];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/
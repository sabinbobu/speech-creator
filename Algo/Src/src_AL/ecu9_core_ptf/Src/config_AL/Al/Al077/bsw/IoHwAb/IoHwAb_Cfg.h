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
* \file     IoHwAb_Cfg.h
*
* \brief    IoHwAb general configuration header
*
* \descr    Static configuration interface for the IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#ifndef IOHWAB_CFG_H
#define IOHWAB_CFG_H

#include "IoHwAb_AnalogCfg.h"
#include "IoHwAb_DigitalCfg.h"
#include "IoHwAb_TimingCfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef uint32 IoHwAb_VoltageType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_VoltageKL30_Read
(
  P2VAR(IoHwAb_VoltageType, AUTOMATIC, IOHWAB_APPL_DATA) VoltagePtr
);

extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_Discrete5V0_PG_Read
(
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) LevelPtr
);

extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DiscreteEN_LWR_Write
(
  VAR(IoHwAb_LevelType, AUTOMATIC) Level
);

extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_PwmLEDCTRL1_SetDutyCycle
(
  P2VAR(IoHwAb_DutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCycle
);

extern FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_PwmLEDCTRL1_SetOutputToIdle
(
  void
);

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/

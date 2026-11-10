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
* \file     IoHwAb_Cfg.c
*
* \brief    IoHwAb general configuration source file
*
* \descr    Static configuration for the IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_Cfg.h"
#include "IoHwAb_Internals.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_VoltageKL30_Read
(
  P2VAR(IoHwAb_VoltageType, AUTOMATIC, IOHWAB_APPL_DATA) VoltagePtr
)
{
  /* Init local variables */
  Std_ReturnType RetVal;

  RetVal = IoHwAb_AnalogReadConverted(IOHWAB_CHID_VBAT, VoltagePtr);

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DiscreteEN_LWR_Write
(
  VAR(IoHwAb_LevelType, AUTOMATIC) Level
)
{
  /* Init local variables */
  Std_ReturnType RetVal;

  RetVal = IoHwAb_DigitalWrite(IOHWAB_CHID_EN_LWR, Level);

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_PwmCTRL_LWR_SetDutyCycle
(
  VAR(IoHwAb_DutyCycleType, AUTOMATIC) DutyCycle
)
{
  return IoHwAb_TimingSetDutyCycle(IOHWAB_CHID_CTRL_LWR, DutyCycle);
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_PwmLEDCTRL1_SetDutyCycle
(
  P2VAR(IoHwAb_DutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCycle
)
{
  /* Init local variables */
  Std_ReturnType RetVal;

  RetVal = IoHwAb_TimingSetDutyCycle(IOHWAB_CHID_LEDCTRL1, DutyCycle);

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_PwmLEDCTRL1_SetOutputToIdle
(
  void
)
{
  /* Init local variables */
  Std_ReturnType RetVal;

  RetVal = IoHwAb_TimingStopActuation(IOHWAB_CHID_LEDCTRL1);

  return RetVal;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/

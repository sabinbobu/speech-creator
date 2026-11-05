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
* \file     IoHwAb_Timing.c
*
* \brief    BSW IoHwAb timing
*
* \descr    Timing signals support for IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb.h"
#include "IoHwAb_Internals.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/
#define IOHWAB_DUTYCYCLE_100 1000

/* PWM duty cycle range is 0..0x8000 */
/* Input duty range is 0..1000 */
/* PWM duty = input duty / 1000 * 0x8000 = duty * 0x8000 * 1024 / 1000 / 1024 */
#define PWM_DUTY(DutyCycle)                        (((DutyCycle) * 33554) >> 10)
/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
FUNC(void, IOHWAB_CODE) IoHwAb_TimingInit(void)
{
  /* Init local variables */
  uint8 ChId;

  for(ChId = 0U; ChId < IOHWAB_NUM_OF_TIMING_CHS; ChId++)
  {
    if ((IoHwAb_TimingChannelCfg[ChId].SourceType == IOHWAB_SOURCE_TYPE_MCAL_ICU) && (IOHWAB_ICU_GET_STARTUP(IoHwAb_TimingChannelCfg[ChId].SourceId) == STD_ON))
    {
      switch (IOHWAB_ICU_GET_MODE(IoHwAb_TimingChannelCfg[ChId].SourceId))
      {
        case ICU_MODE_SIGNAL_EDGE_DETECT:
          Icu_EnableEdgeDetection((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_SIGNAL_MEASUREMENT:
          Icu_StartSignalMeasurement((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_EDGE_COUNTER:
          Icu_EnableEdgeCount((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_TIMESTAMP:
        default:
          break;
      }
    }
  }
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingSetDutyCycle
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId,
  VAR(IoHwAb_DutyCycleType, AUTOMATIC) DutyCycle
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;

  if ((ChId < IOHWAB_NUM_OF_TIMING_CHS) && (IoHwAb_TimingChannelCfg[ChId].Interaction == IOHWAB_INTERACTION_ACTUATION))
  {
    switch (IoHwAb_TimingChannelCfg[ChId].SourceType)
    {
      case IOHWAB_SOURCE_TYPE_MCAL_PWM:
        Pwm_SetDutyCycle((Pwm_ChannelType)IoHwAb_TimingChannelCfg[ChId].SourceId, PWM_DUTY(DutyCycle));

        RetVal = E_OK;

        break;

      case IOHWAB_SOURCE_TYPE_EXTERNAL:
        IoHwAb_SetDutyCycleExternal(IoHwAb_TimingChannelCfg[ChId].SourceId, DutyCycle);

        RetVal = E_OK;

        break;

      default:
        break;
    }
  }

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingStopActuation
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;

  if (ChId < IOHWAB_NUM_OF_TIMING_CHS)
  {
    if(IoHwAb_TimingChannelCfg[ChId].SourceType == IOHWAB_SOURCE_TYPE_MCAL_PWM)
    {
      Pwm_SetOutputToIdle((Pwm_ChannelType)IoHwAb_TimingChannelCfg[ChId].SourceId);

      RetVal = E_OK;
    }
  }

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingGetDutyCycle
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_DutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCyclePtr
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;
  Icu_DutyCycleType IcuDutyCycle;

  if ((DutyCyclePtr != NULL_PTR) && (ChId < IOHWAB_NUM_OF_TIMING_CHS) && (IoHwAb_TimingChannelCfg[ChId].Interaction == IOHWAB_INTERACTION_MEASUREMENT))
  {
    switch (IoHwAb_TimingChannelCfg[ChId].SourceType)
    {
      case IOHWAB_SOURCE_TYPE_MCAL_ICU:
        Icu_GetDutyCycleValues((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId), &IcuDutyCycle);

        if (IcuDutyCycle.PeriodTime > 0U)
        {
          *DutyCyclePtr = (IoHwAb_DutyCycleType)(IcuDutyCycle.ActiveTime*IOHWAB_DUTYCYCLE_100/IcuDutyCycle.PeriodTime);

          RetVal = E_OK;
        }

        break;

      case IOHWAB_SOURCE_TYPE_EXTERNAL:
        IoHwAb_GetDutyCycleExternal(IoHwAb_TimingChannelCfg[ChId].SourceId, DutyCyclePtr);

        RetVal = E_OK;

        break;

      default:
        break;
    }
  }

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingStartMeasurement
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;

  if (ChId < IOHWAB_NUM_OF_TIMING_CHS)
  {
    if(IoHwAb_TimingChannelCfg[ChId].SourceType == IOHWAB_SOURCE_TYPE_MCAL_ICU)
    {
      switch (IOHWAB_ICU_GET_MODE(IoHwAb_TimingChannelCfg[ChId].SourceId))
      {
        case ICU_MODE_SIGNAL_EDGE_DETECT:
          Icu_EnableEdgeDetection((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_SIGNAL_MEASUREMENT:
          Icu_StartSignalMeasurement((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_EDGE_COUNTER:
          Icu_EnableEdgeCount((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_TIMESTAMP:
        default:
          break;
      }
    }
  }

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_TimingStopMeasurement
(
  VAR(IoHwAb_TimingChannelIdType, AUTOMATIC) ChId
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;

  if (ChId < IOHWAB_NUM_OF_TIMING_CHS)
  {
    if(IoHwAb_TimingChannelCfg[ChId].SourceType == IOHWAB_SOURCE_TYPE_MCAL_ICU)
    {
      switch (IOHWAB_ICU_GET_MODE(IoHwAb_TimingChannelCfg[ChId].SourceId))
      {
        case ICU_MODE_SIGNAL_EDGE_DETECT:
          Icu_DisableEdgeDetection((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_SIGNAL_MEASUREMENT:
          Icu_StopSignalMeasurement((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_EDGE_COUNTER:
          Icu_DisableEdgeCount((Icu_ChannelType)IOHWAB_ICU_GET_CHANNEL(IoHwAb_TimingChannelCfg[ChId].SourceId));
          break;
        case ICU_MODE_TIMESTAMP:
        default:
          break;
      }
    }
  }

  return RetVal;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/

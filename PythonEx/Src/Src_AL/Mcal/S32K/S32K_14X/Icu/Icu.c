//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Icu.c
///
/// \brief Public interface declarations of the input capture unit module.
///
/// \descr  initialise the reading of PWm from sensors
///
/// \author Tanase Alexandru-Anton (F58375C)
///         mailTo:alexandru-anton.tanase[at]marelli.com
///
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================

#include <Icu.h>

#ifndef UNIT_TEST
#include <ftm_ic_driver.h>
#include <ftm_hw_access.h>
#endif

#include <UtilUtility.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

//=============================================================================
// Functions
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief Icu_Init
///
/// \descr Initialise the reading of PWM from sensors using given configuration
///
/// \param  ConfigPtr: Configuration of ICU
///
/// \return void
//-----------------------------------------------------------------------------
void Icu_Init(CONST_AL sIcu_ConfigType* ConfigPtr)
{
  uint8 ucIdx = 0u;
  tsIcu_ConfigInstanceMap* sCfgChar = &ConfigPtr->sCfgCharacteristics[0];
  // PRQA S 316 3 // referencing void pointer to requested type
  uint32* ulInstance = (uint32*)sCfgChar->icu_instance;
  ftm_input_param_t* sIcuCfg = (ftm_input_param_t*)sCfgChar->icu_global_config;
  const ftm_user_config_t * sInfo = (ftm_user_config_t*)sCfgChar->icu_info_config;
  for (ucIdx = 0u; ucIdx < ConfigPtr->ucCountOfIcuInstances; ++ucIdx) 
  {
    ftmStatePtr[ulInstance[ucIdx]]->ftmMode = FTM_MODE_NOT_INITIALIZED;
    ftmStatePtr[ulInstance[ucIdx]]->ftmClockSource = FTM_CLOCK_SOURCE_SYSTEMCLK;

    // only works if the prescaler is 16
    (void)FTM_DRV_Init(ulInstance[ucIdx], &sInfo[ucIdx], ftmStatePtr[ulInstance[ucIdx]]);
    
    (void)FTM_DRV_InitInputCapture(ulInstance[ucIdx], &sIcuCfg[ucIdx]);
    
    FTM_RMW_SC(g_ftmBase[ulInstance[ucIdx]], (uint32)FTM_SC_PWMEN0_MASK, FTM_SC_PWMEN0(0u));
    FTM_RMW_SC(g_ftmBase[ulInstance[ucIdx]], (uint32)FTM_SC_PWMEN4_MASK, FTM_SC_PWMEN4(0u));
    FTM_RMW_SC(g_ftmBase[ulInstance[ucIdx]], (uint32)FTM_SC_PS_MASK,     FTM_SC_PS(FTM_CLOCK_DIVID_BY_16)); // 4 = FTM_CLOCK_DIVID_BY_16 
  }
}


//-----------------------------------------------------------------------------
/// \brief Icu_ChangeMeasurementMode
///
/// \descr Setting Measurement Mode of the leveling sensor's PWM
///
/// \param  ucIndex:   PWM index for Leveling sensor 
/// \param  ucMesMode: Measurement Mode flag
///
/// \return void
//-----------------------------------------------------------------------------
void Icu_ChangeMeasurementMode(uint8 ucIndex, uint8 ucMesMode)
{
  uint32_t         ulInstance;
  uint8_t          ucChannel;
  ftm_ic_op_mode_t inputMode;

  // Config instance and channel for Sensor PWM 0
  if (ucIndex == CFG_SENS_PWM0)
  {
    ulInstance = FTM_SENS_PWM0;
    ucChannel  = FTM_CHANNEL_SENS_PWM0;
  }
  // Config instance and channel for Sensor PWM 1
  else
  {
    ulInstance = FTM_SENS_PWM1;
    ucChannel  = FTM_CHANNEL_SENS_PWM1;
  }

  // Config measurement mode
  if (ucMesMode == ICU_MEASURE_MODE_DUTY)
  {
    inputMode = FTM_MEASURE_PULSE_HIGH;
  }
  else
  {
    inputMode = FTM_MEASURE_RISING_EDGE_PERIOD;
  }

  // Change the channel mode
  (void)FTM_IC_DRV_SetChannelMode(ulInstance, ucChannel, inputMode, true);
}


//-----------------------------------------------------------------------------
/// \brief Icu_GetMeasurementSens
///
/// \descr Get time stamps values of Period or Duty Cycle of the Leveling Sensor's PWM
///        depending on measurment configuration
///
/// \param  ucIdx: Leveling sensor index
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 Icu_GetMeasurementSens(uint8 ucIdx)
{
  uint16 unSensMeasurement = 0u;

  switch (ucIdx)
  {
  case CFG_SENS_PWM0:
  {
    // Get PWM Measurement from Sensor 0
    unSensMeasurement = FTM_DRV_GetInputCaptureMeasurement(FTM_SENS_PWM0, FTM_CHANNEL_SENS_PWM0);
  }
  break;

  case CFG_SENS_PWM1:
  {
    // Get PWM Measurement from Sensor 1
    unSensMeasurement = FTM_DRV_GetInputCaptureMeasurement(FTM_SENS_PWM1, FTM_CHANNEL_SENS_PWM1);
  }
  break;
  default:
    unSensMeasurement = 0u;
  break;
  }

  return unSensMeasurement;
}

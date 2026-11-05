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
/// \file   SysMonCheck_LedCtrl.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for SysMonCheck_LedCtrl
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMonCheck_LedCtrl.h>
#include <SysMonCheck_Data.h>
#include <SysMonRx_ASIL.h>
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
// Static variable declarations
//-----------------------------------------------------------------------------
STATIC_AL CONST_AL tsRte_TgtLedSig0*       SysMonCheck_LedCtrl_pTargetLed       = NULL_PTR; // Pointer of an array in reality
STATIC_AL          tsRte_TgtLedSig0_ASIL*  SysMonCheck_LedCtrl_pTargetLed_ASIL  = NULL_PTR;

STATIC_AL CONST_AL tSysMonCheck_Data_LedChParam* SysMonCheck_LedtCtrl_pLedChParam = NULL_PTR; //Pointer to LED channels parameters

//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_LedCtrl_EvaluateLightSourceReq(void);

//-----------------------------------------------------------------------------
/// \brief SysMonCheck_LedCtrl_Init
///
/// \descr Initialization function for TargetLed structure
///
/// \param  tsRte_TgtLedSig0*: Pointer to a structure containing LED channels Duty Cycle and Current values
///         tsRte_TgtLedSig0_ASIL: Pointer to a structure that will be sent to CddLed
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_LedCtrl_Init(CONST_AL tsRte_TgtLedSig0* CONST_AL paTargetLed, tsRte_TgtLedSig0_ASIL* CONST_AL paTargetLed_ASIL)
{
  SysMonCheck_LedtCtrl_pLedChParam = SysMonCheck_Data_GetaLEDChParamPtr();

  if (paTargetLed_ASIL != NULL_PTR)
  {
    SysMonCheck_LedCtrl_pTargetLed      = paTargetLed;
    SysMonCheck_LedCtrl_pTargetLed_ASIL = paTargetLed_ASIL;

    // Initialize Current and PWM duty to 0
    SysMonCheck_LedCtrl_TargetLedDefaultValues();
  }
  else
  {
    // do nothing
  }
}



//-----------------------------------------------------------------------------
/// \brief SysMonCheck_LedCtrl_Cycle
///
/// \descr Cyclic function that verifies and populates the structure to be sent to CddLed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_LedCtrl_Cycle(void)
{
  if ((SysMonCheck_Data_IsCodingDataValid() != FALSE) && (SysMonCheck_LedCtrl_pTargetLed_ASIL != NULL_PTR))
  {
    if (SysMonCheck_Data_AreFuSaParamValid() == SysMonCheck_Data_FuSaParamValid)
    {
      SysMonCheck_LedCtrl_EvaluateLightSourceReq();
    }
    else
    {
      // Set Current and PWM duty to 0
      SysMonCheck_LedCtrl_TargetLedDefaultValues();
    }
  }
  else
  {
    // Set Current and PWM duty to 0
    SysMonCheck_LedCtrl_TargetLedDefaultValues();
  }
}



//-----------------------------------------------------------------------------
/// \brief SysMonCheck_LedCtrl_TargetLedDefaultValues
///
/// \descr  Function that sets Current and Duty Cycle values to 0
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_LedCtrl_TargetLedDefaultValues(void)
{
  for (uint8 ucLedIdx = 0u; ucLedIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucLedIdx++)
  {
    // Removed after allignment with CABA Ionut
    //SysMonCheck_LedCtrl_pTargetLed_ASIL->asTgtVal[ucLedIdx].unCurrent   = SYSMON_ZERO_VALUE;
    SysMonCheck_LedCtrl_pTargetLed_ASIL->asTgtVal[ucLedIdx].unDutyCycle = SYSMON_ZERO_VALUE;
  }
}



//-----------------------------------------------------------------------------
/// \brief SysMon_LedCtrl_EvaluateLightSourceReq
///
/// \descr  Evaluate Light source request coming from CtrlLed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_LedCtrl_EvaluateLightSourceReq(void)
{
  boolean boIsTiFuSa = FALSE;

  boolean boEmergencyOperationTurnIndicator = SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationTurnIndicator();

  // Go trough all channels
  for (uint8 ucLedIdx = 0u; ucLedIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucLedIdx++)
  {
    // Check if we have TI channel
    boIsTiFuSa = SysMonCheck_Data_IsTurnIndicatorFuSa(ucLedIdx);

    // Check if we have TI channels that are in Emergency Operation Mode
    if ((boEmergencyOperationTurnIndicator != FALSE) && (boIsTiFuSa != FALSE))
    {
      // do nothing , channel is handled in SysMonRx_ASIL
    }
    else
    {
      // Bypass PWM and current values for other channels
      SysMonCheck_LedCtrl_pTargetLed_ASIL->asTgtVal[ucLedIdx].unCurrent   = SysMonCheck_LedCtrl_pTargetLed[ucLedIdx].unCurrent;
      SysMonCheck_LedCtrl_pTargetLed_ASIL->asTgtVal[ucLedIdx].unDutyCycle = SysMonCheck_LedCtrl_pTargetLed[ucLedIdx].unDutyCycle;
    }
  }
}


// EOF

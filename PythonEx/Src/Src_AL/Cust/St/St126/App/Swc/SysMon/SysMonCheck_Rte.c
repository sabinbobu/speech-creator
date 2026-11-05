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
/// \file   CtrlLed_Rte.c
///
/// \brief  RteAccess for CtrlLed
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include "SysMonCheck_Rte.h"
#include "SysMonCheck_InternalCom.h"

//=============================================================================
// Local globals
//=============================================================================

//=============================================================================
// functions prototype
//=============================================================================

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_LedDiag_RteAccess_Get_ChannelState
///
/// \descr  This function get channel states via RTE
///
/// \param  *sChannelState
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_RteAccess_Get_ChannelState(uint8_fast ucIdx, tsSysMon_aChannelState *psChannelState)
{
  tsRte_LedStates           sRte_LedStates;
  tsRte_BoostState          sRte_BoostState;
  STATIC_AL tsRte_LedStates sRte_sLedStates_ASIL;
  //read led state 
  (void)Rte_Read_CddLed_LedState(&sRte_LedStates);
  (void)Rte_Read_CddBoost_BoostState(&sRte_BoostState);
  // Check CRC8 of Internal Communication Rte port
  if (SysMonCheck_InternalCom_LedState_CheckCrc(&sRte_LedStates) != FALSE)
  {
    // Data can be used by SysMon because the CRC matches with the one sent from CddLed
    sRte_sLedStates_ASIL = sRte_LedStates;
  }
  else
  {
    // nothing to do, last valid data is still used
  }

  //PRQA S 310 1 //cust needed
  psChannelState->asChannelState[ucIdx].ucChannelStatus = (uint8)sRte_sLedStates_ASIL.aLedStates[ucIdx].eLedErrStatus;
  if ((psChannelState->asChannelState[ucIdx].ucChannelStatus <= (uint8)eRteCddLed_StatusOk) && ((sRte_sLedStates_ASIL.aLedStates[ucIdx].boVinBoostOk == FALSE) || (sRte_BoostState.aboBoostDefect[0] != FALSE)))
  {
     psChannelState->asChannelState[ucIdx].ucChannelStatus = (uint8)eRteCddLed_ErrcBoost;
  }
  psChannelState->asChannelState[ucIdx].boVinOk = sRte_sLedStates_ASIL.aLedStates[ucIdx].boVinBoostOk;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_RteAccess_Set_ChannelState
///
/// \descr  This function sets channel states via RTE
///
/// \param  *sChannelState
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_RteAccess_Set_ChannelState(tsSysMon_ErrorHandler  sChannelState[12])
{
  tsRte_SysMon_LedStates sRte_SysMon_LedStates;

  for (uint8_fast ucChannelIdx = 0u; ucChannelIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucChannelIdx++)
  {
    sRte_SysMon_LedStates.aLedStates[ucChannelIdx]    = sChannelState[ucChannelIdx].ucLedState;
    sRte_SysMon_LedStates.boVinBoostOk[ucChannelIdx]  = sChannelState[ucChannelIdx].boVinBoostOk;
  }

  // Write led state to Ctrl Led
  (void)Rte_Write_SysMon_LedState(&sRte_SysMon_LedStates);
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_RteAccess_Get_TiFailureStatus
///
/// \descr  This function get TI failure status via RTE
///
/// \param  *pboStatus
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_RteAccess_Get_TiFailureStatus(boolean *pboStatus)
{
  //read RTE port
  (void)Rte_Read_FctR_TiFailureStatus(pboStatus);
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_RteAccess_Get_ElecSupState
///
/// \descr  This function get STT Phase via RTE 
///
/// \param  *pData
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_RteAccess_Get_ElecSupState(teSysMon_EngineState *pData)
{
  tsRte_SigPrep_ElecSupState  sElecSupState;
  //read RTE port
  (void)Rte_Read_SigPrep_ElecSupState(&sElecSupState);

  switch (sElecSupState.eElectrSupplyState)
  {
  case eEtatFee_4_1:
    *pData = eEngineRunning;
    break;
  case eEtatFee_3c_1:
  case eEtatFee_3r_1:
    *pData = eSTT_Phase;
    break;
  default:
    *pData = eInvalid_State;
    break;
  }
}



//-----------------------------------------------------------------------------
/// \brief SysMonCheck_RteAccess_Get_VoltageRange
///
/// \descr Read voltage range via Rte call wrapper
///
/// \param  void
///
/// \return uint8 - batery voltage range
//-----------------------------------------------------------------------------
uint8 SysMonCheck_RteAccess_Get_VoltageRange(void)
{
  teRte_SysVolt_Results eSetVoltageState;

  // Rte call for Vbat voltage
  (void)Rte_Read_SysVolt_LedVoltRng0_sVoltRng(&eSetVoltageState);

  // Set voltage ranges
  uint8 ucSetVoltageState = (eSetVoltageState == SysVolt_eNormal) ? SYSMON_NORMAL_VOLT : \
    (eSetVoltageState == SysVolt_eLow2) ? SYSMON_LOW2_VOLT : \
    (eSetVoltageState == SysVolt_eLow1) ? SYSMON_LOW1_VOLT : \
    SYSMON_UNKNOWN_VOLT;

  return ucSetVoltageState;
}


// EOF

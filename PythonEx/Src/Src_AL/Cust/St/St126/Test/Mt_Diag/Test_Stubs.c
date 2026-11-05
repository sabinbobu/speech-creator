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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehicleSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehicleSpeed_Param1;
  Rte_Read_SysMon_VehicleSpeed_HitCount++;

  return Rte_Read_SysMon_VehicleSpeed_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehNetState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehNetState_Param1;
  Rte_Read_SysMon_VehNetState_HitCount++;

  return Rte_Read_SysMon_VehNetState_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_OS_CPULoadPeak
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_OS_CPULoadPeak
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_OS_CPULoadPeak(uint8* ppara1)
{
  *ppara1 = Rte_Read_OS_CPULoadPeak_Param1;
  Rte_Read_OS_CPULoadPeak_HitCount++;

  return Rte_Read_OS_CPULoadPeak_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal(tauRte_CtrlPxl_Mtx_bErr* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1;
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount++;

  return Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_StatusErr
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_StatusErr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_StatusErr(tisHssStatusError* ppara1)
{
  *ppara1 = Rte_Read_CtrlSwi_StatusErr_Param1;
  Rte_Read_CtrlSwi_StatusErr_HitCount++;

  return Rte_Read_CtrlSwi_StatusErr_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(teRte_SateliteStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1;
  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount++;

  return Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddLed_Status
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddLed_Status
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddLed_Status(tCddLedStatus* ppara1)
{
  *ppara1 = Rte_Read_CddLed_Status_Param1;
  Rte_Read_CddLed_Status_HitCount++;

  return Rte_Read_CddLed_Status_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_FctR_LgtDistStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_FctR_LgtDistStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_LgtDistStatus(uint32* ppara1)
{
  *ppara1 = Rte_Read_FctR_LgtDistStatus_Param1;
  Rte_Read_FctR_LgtDistStatus_HitCount++;

  return Rte_Read_FctR_LgtDistStatus_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(tasRte_MlcAdcResult* ppara1)
{

  for (uint32 ulIdx = 0u; ulIdx < sizeof(tasRte_MlcAdcResult); ulIdx++)
  {
    *((uint8*)(void*)ppara1 + ulIdx) = *((uint8*)(void*)&Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_Param1 + ulIdx);
  }
  Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_HitCount++;
  return Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Cpm_PowFact_Temp
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Cpm_PowFact_Temp
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Cpm_PowFact_Temp(tsRtePowFactTemp* ppara1)
{
  *ppara1 = Rte_Read_Cpm_PowFact_Temp_Param1;
  Rte_Read_Cpm_PowFact_Temp_HitCount++;

  return Rte_Read_Cpm_PowFact_Temp_RetVal;
}




//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LedState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LedState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LedState(tsRte_SysMon_LedStates* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LedState_Param1;
  Rte_Read_SysMon_LedState_HitCount++;

  return Rte_Read_SysMon_LedState_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;

  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Diag_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Diag_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_RoutineControl(tsRte_AfsRoutineControl* ppara1)
{
  *ppara1 = Rte_Read_Diag_RoutineControl_Param1;
  Rte_Read_Diag_RoutineControl_HitCount++;

  return Rte_Read_Diag_RoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LowBeamCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LowBeamCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LowBeamCmd_Req_Param1;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount++;

  return Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppCddStpActual0_sStpActualValues
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppCddStpActual0_sStpActualValues
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1)
{
  *ppara1 = Rte_Read_ppCddStpActual0_sStpActualValues_Param1;
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount++;

  return Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddSwi_ScrollingOn_Stat
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddSwi_ScrollingOn_Stat(boolean* ppara1)
{
  *ppara1 = Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount++;

  return Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;

  return Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_OS_CPULoadAvg
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_OS_CPULoadAvg
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_OS_CPULoadAvg(uint8* ppara1)
{
  *ppara1 = Rte_Read_OS_CPULoadAvg_Param1;
  Rte_Read_OS_CPULoadAvg_HitCount++;

  return Rte_Read_OS_CPULoadAvg_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1)
{
  *ppara1 = Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1;
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount++;

  return Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Cpm_TgtLedSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Cpm_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{
  ppara1 = &Rte_Read_Cpm_TgtLedSig_sVal_Param1;
  Rte_Read_Cpm_TgtLedSig_sVal_HitCount++;

  return Rte_Read_Cpm_TgtLedSig_sVal_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehicleConfigSig
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehicleConfigSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehicleConfigSig_Param1;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount++;

  return Rte_Read_SigPrep_VehicleConfigSig_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;

  return Rte_Read_SysMon_LifePhases_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_AppM_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_AppM_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_AppM_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_AppM_Para_Param1;
  Rte_Read_CodM_AppM_Para_HitCount++;

  return Rte_Read_CodM_AppM_Para_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_GetVoltage_NTCs
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_GetVoltage_NTCs
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_GetVoltage_NTCs(tsRte_Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetVoltage_NTCs_Param1;
  Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount++;

  return Rte_Read_IoHwAb_GetVoltage_NTCs_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_StatM_StackUsage
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_StatM_StackUsage
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_StatM_StackUsage(uint8* ppara1)
{
  *ppara1 = Rte_Read_StatM_StackUsage_Param1;
  Rte_Read_StatM_StackUsage_HitCount++;

  return Rte_Read_StatM_StackUsage_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_GetSens_Raw
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_GetSens_Raw
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetSens_Raw_Param1;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount++;

  return Rte_Read_IoHwAb_GetSens_Raw_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_Hss3StatusErr
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlSwi_Hss3StatusErr
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlSwi_Hss3StatusErr(tsRte_Hss3Status* ppara1)
{
  *ppara1 = Rte_Read_CtrlSwi_Hss3StatusErr_Param1;
  Rte_Read_CtrlSwi_Hss3StatusErr_HitCount++;

  return Rte_Read_CtrlSwi_Hss3StatusErr_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal(tasRte_CtrlPxl_BinEEprom* ppara1)
{
  ppara1 = &Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1;
  Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_HitCount++;

  return Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Stp_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Stp_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Stp_RoutineControl(tsRte_StepperRoutineControl* ppara1)
{
  *ppara1 = Rte_Read_Stp_RoutineControl_Param1;
  Rte_Read_Stp_RoutineControl_HitCount++;

  return Rte_Read_Stp_RoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Dcm_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Dcm_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1)
{
  *ppara1 = Rte_Read_Dcm_RoutineControl_Param1;
  Rte_Read_Dcm_RoutineControl_HitCount++;

  return Rte_Read_Dcm_RoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehiclePitchAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehiclePitchAngle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehiclePitchAngle_Param1;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount++;

  return Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Pitch_Angle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Pitch_Angle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1)
{
  *ppara1 = Rte_Read_Pitch_Angle_Param1;
  Rte_Read_Pitch_Angle_HitCount++;

  return Rte_Read_Pitch_Angle_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppsAvacOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppsAvacOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppsAvacOut(tsPositionOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAvacOut_Param1;
  Rte_Read_ppsAvacOut_HitCount++;

  return Rte_Read_ppsAvacOut_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_ThermzoneTemperatures
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_ThermzoneTemperatures
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1)
{
  *ppara1 = Rte_Read_RSens_ThermzoneTemperatures_Param1;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount++;

  return Rte_Read_RSens_ThermzoneTemperatures_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_ResetStatistics
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_ResetStatistics
///
/// \param  para1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_ResetStatistics(boolean para1)
{
  Rte_Write_Diag_ResetStatistics_Param1 = para1;
  Rte_Write_Diag_ResetStatistics_HitCount++;

  return Rte_Write_Diag_ResetStatistics_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_RoutineControl(const tsRte_AfsRoutineControl* ppara1)
{
  Rte_Write_Diag_RoutineControl_Param1 = *ppara1;
  Rte_Write_Diag_RoutineControl_HitCount++;

  return Rte_Write_Diag_RoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Dcm_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Dcm_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Dcm_RoutineControl(const tsRte_DcMotorRoutineControl* ppara1)
{
  Rte_Write_Dcm_RoutineControl_Param1 = *ppara1;
  Rte_Write_Dcm_RoutineControl_HitCount++;

  return Rte_Write_Dcm_RoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_TiScrollingTakeOver
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_TiScrollingTakeOver
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_TiScrollingTakeOver(const boolean* ppara1)
{
  Rte_Write_Diag_TiScrollingTakeOver_Param1 = *ppara1;
  Rte_Write_Diag_TiScrollingTakeOver_HitCount++;

  return Rte_Write_Diag_TiScrollingTakeOver_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddSwi_ScrollingOn_Stat
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CddSwi_ScrollingOn_Stat
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddSwi_ScrollingOn_Stat(const boolean* ppara1)
{
  Rte_Write_CddSwi_ScrollingOn_Stat_Param1 = *ppara1;
  Rte_Write_CddSwi_ScrollingOn_Stat_HitCount++;

  return Rte_Write_CddSwi_ScrollingOn_Stat_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(const teRte_SateliteStatus* ppara1)
{
  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1 = *ppara1;
  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_HitCount++;

  return Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Stp_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Stp_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Stp_RoutineControl(const tsRte_StepperRoutineControl* ppara1)
{
  Rte_Write_Stp_RoutineControl_Param1 = *ppara1;
  Rte_Write_Stp_RoutineControl_HitCount++;

  return Rte_Write_Stp_RoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_LdActivationRoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_LdActivationRoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_LdActivationRoutineControl(const tsRte_Ld_ActivationRoutineControl* ppara1)
{
  Rte_Write_Diag_LdActivationRoutineControl_Param1 = *ppara1;
  Rte_Write_Diag_LdActivationRoutineControl_HitCount++;

  return Rte_Write_Diag_LdActivationRoutineControl_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_StatM_StackUsage
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_StatM_StackUsage
///
/// \param  para1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_StatM_StackUsage(uint8 para1)
{
  Rte_Write_StatM_StackUsage_Param1 = para1;
  Rte_Write_StatM_StackUsage_HitCount++;

  return Rte_Write_StatM_StackUsage_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_OS_CPULoadPeak
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_OS_CPULoadPeak
///
/// \param  para1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_OS_CPULoadPeak(uint8 para1)
{
  Rte_Write_OS_CPULoadPeak_Param1 = para1;
  Rte_Write_OS_CPULoadPeak_HitCount++;

  return Rte_Write_OS_CPULoadPeak_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_DD01_Activation
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_DD01_Activation
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_DD01_Activation(const boolean* ppara1)
{
  Rte_Write_Diag_DD01_Activation_Param1 = *ppara1;
  Rte_Write_Diag_DD01_Activation_HitCount++;

  return Rte_Write_Diag_DD01_Activation_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_DD01_PixelActivation
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_DD01_PixelActivation
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_DD01_PixelActivation(const tsRte_DIDPixelActivation* ppara1)
{
  Rte_Write_Diag_DD01_PixelActivation_Param1 = *ppara1;
  Rte_Write_Diag_DD01_PixelActivation_HitCount++;

  return Rte_Write_Diag_DD01_PixelActivation_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_DiagResetRequest
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_DiagResetRequest
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_DiagResetRequest(const boolean* ppara1)
{
  Rte_Write_Diag_DiagResetRequest_Param1 = *ppara1;
  Rte_Write_Diag_DiagResetRequest_HitCount++;

  return Rte_Write_Diag_DiagResetRequest_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ElecInt_ReleaseRUN
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_ElecInt_ReleaseRUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ElecInt_ReleaseRUN(const uint8* ppara1)
{
  Rte_Write_ElecInt_ReleaseRUN_Param1 = *ppara1;
  Rte_Write_ElecInt_ReleaseRUN_HitCount++;

  return Rte_Write_ElecInt_ReleaseRUN_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_RequestPOST_RUN
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_RequestPOST_RUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_RequestPOST_RUN(const uint8* ppara1)
{
  Rte_Write_Diag_RequestPOST_RUN_Param1 = *ppara1;
  Rte_Write_Diag_RequestPOST_RUN_HitCount++;

  return Rte_Write_Diag_RequestPOST_RUN_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  BlockId
///         NvM_SrcPtr
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
  NvM_WriteBlock_Param1 = BlockId;
  NvM_WriteBlock_Param2 = NvM_SrcPtr;
  NvM_WriteBlock_HitCount++;

  return NvM_WriteBlock_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  EAPI_GetCurrentEIMode
///
/// \descr  Stub function created to simulate the behaviour of EAPI_GetCurrentEIMode
///
/// \param  void
///
/// \return LEIM_TE_CurrentEIMode
//-----------------------------------------------------------------------------
LEIM_TE_CurrentEIMode EAPI_GetCurrentEIMode(void)
{
  EAPI_GetCurrentEIMode_HitCount++;

  return EAPI_GetCurrentEIMode_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  DAPI_ClearDTCInfo
///
/// \descr  Stub function created to simulate the behaviour of DAPI_ClearDTCInfo
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_ClearDTCInfo(void)
{
  DAPI_ClearDTCInfo_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  DIAG_Send_Diag_Response
///
/// \descr  Stub function created to simulate the behaviour of DIAG_Send_Diag_Response
///
/// \param  p_ui8_Data
///         Length
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status DIAG_Send_Diag_Response(const UINT8* p_ui8_Data, Diag_Length_Type Length)
{
  for (uint16 i = 0; i < Length; i++)
  {
    DIAG_Send_Diag_Response_Param1[i] = p_ui8_Data[i];
  }

  DIAG_Send_Diag_Response_Param2 = Length;
  DIAG_Send_Diag_Response_HitCount++;

  return DIAG_Send_Diag_Response_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  DIAG_Send_Diag_Response
///
/// \descr  Stub function created to simulate the behaviour of DIAG_Send_Diag_Response
///
/// \param  Error
///
/// \return DIAG_status
//-----------------------------------------------------------------------------
DIAG_status DIAG_Send_Diag_Error(DIAG_status Error)
{
  DIAG_Send_Diag_Error_Param1 = Error;
  DIAG_Send_Diag_Error_HitCount++;

  return DIAG_Send_Diag_Error_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  DIAG_GetActiveSession
///
/// \descr  Stub function created to simulate the behaviour of DIAG_GetActiveSession
///
/// \param  void
///
/// \return UINT8
//-----------------------------------------------------------------------------
UINT8 DIAG_GetActiveSession(void)
{
  DIAG_GetActiveSession_HitCount++;

  return DIAG_GetActiveSession_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_GetVoltage_NTCs
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_GetVoltage_NTCs
///
/// \param  ucIdx
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_GetVoltage_NTCs(uint8 ucIdx)
{
  IoHwAbUser_GetVoltage_NTCs_Param1 = ucIdx;
  IoHwAbUser_GetVoltage_NTCs_HitCount++;

  return IoHwAbUser_GetVoltage_NTCs_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  CddSbc_GetPWM
///
/// \descr  Stub function created to simulate the behaviour of CddSbc_GetPWM
///
/// \param  ucMode
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CddSbc_GetPWM(uint8 ucMode)
{
  CddSbc_GetPWM_Param1 = ucMode;
  CddSbc_GetPWM_HitCount++;

  return CddSbc_GetPWM_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Dem_Diag_LockDTC
///
/// \descr  Stub function created to simulate the behaviour of Dem_Diag_LockDTC
///
/// \param  boEnableDTC
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Diag_LockDTC(boolean boEnableDTC)
{
  Dem_Diag_LockDTC_Param1 = boEnableDTC;
  Dem_Diag_LockDTC_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ClearMemory
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ClearMemory
///
/// \param  pucDtcCode
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean ErrCust_ClearMemory(uint8* pucDtcCode)
{
  ErrCust_ClearMemory_Param1 = *pucDtcCode;
  ErrCust_ClearMemory_HitCount++;

  return ErrCust_ClearMemory_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ulGetDtcCode
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ulGetDtcCode
///
/// \param  ucDtcIndex
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 ErrCust_ulGetDtcCode(uint8 ucDtcIndex)
{
  ErrCust_ulGetDtcCode_Param1 = ucDtcIndex;
  ErrCust_ulGetDtcCode_HitCount++;

  return ErrCust_ulGetDtcCode_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ucGetErrorCount
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ucGetErrorCount
///
/// \param  ucDTCStatusMask
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 ErrCust_ucGetErrorCount(uint8 ucDTCStatusMask)
{
  ErrCust_ucGetErrorCount_Param1 = ucDTCStatusMask;
  ErrCust_ucGetErrorCount_HitCount++;

  return ErrCust_ucGetErrorCount_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ResetDtcIndex
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ResetDtcIndex
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void  ErrCust_ResetDtcIndex(void)
{
  ErrCust_ResetDtcIndex_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ucGetStatusOfDTC
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ucGetStatusOfDTC
///
/// \param  ucDtcIndex
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 ErrCust_ucGetStatusOfDTC(uint8 ucDtcIndex)
{
  ErrCust_ucGetStatusOfDTC_Param1 = ucDtcIndex;
  ErrCust_ucGetStatusOfDTC_HitCount++;

  return ErrCust_ucGetStatusOfDTC_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_SetAvailableDtc
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_SetAvailableDtc
///
/// \param  pucBuf
///         ucDTCStatusMask
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_SetAvailableDtc(uint8* pucBuf, uint8 ucDTCStatusMask)
{
  ErrCust_SetAvailableDtc_Param1 = pucBuf;
  ErrCust_SetAvailableDtc_Param2 = ucDTCStatusMask;
  ErrCust_SetAvailableDtc_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ConvertValueSint2Int
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ConvertValueSint2Int
///
/// \param  slInValue
///         ucbitLength
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 ErrCust_ConvertValueSint2Int(sint32 slInValue, uint8 ucbitLength)
{
  ErrCust_ConvertValueSint2Int_Param1 = slInValue;
  ErrCust_ConvertValueSint2Int_Param2 = ucbitLength;
  ErrCust_ConvertValueSint2Int_HitCount++;

  return ErrCust_ConvertValueSint2Int_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_ConvertValueInt2Sint
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_ConvertValueInt2Sint
///
/// \param  ulInValue
///         ucbitLength
///
/// \return sint32
//-----------------------------------------------------------------------------
sint32 ErrCust_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength)
{
  ErrCust_ConvertValueInt2Sint_Param1 = ulInValue;
  ErrCust_ConvertValueInt2Sint_Param2 = ucbitLength;
  ErrCust_ConvertValueInt2Sint_HitCount++;

  return ErrCust_ConvertValueInt2Sint_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_FctR_LgtFctErrState
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_RteAccess_Read_FctR_LgtFctErrState
///
/// \param  psErrCust_RteAccess_LgtFctState
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_FctR_LgtFctErrState(tsErrCust_LgtFctState *psErrCust_RteAccess_LgtFctState)
{
  *psErrCust_RteAccess_LgtFctState = ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide
///
/// \param  peEcuSide
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(teErrCust_Types_MountingSide *peEcuSide)
{
  *peEcuSide = ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1;
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_CtrlStp_ActStatStp
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_RteAccess_Read_CtrlStp_ActStatStp
///
/// \param  psActStatStp
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_CtrlStp_ActStatStp(tsErrCust_TypesActStatStp *psActStatStp)
{
  *psActStatStp = ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_FctR_LgtFctStatus
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_RteAccess_Read_FctR_LgtFctStatus
///
/// \param  psErrCust_RteAccess_LgtFctStatus
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_FctR_LgtFctStatus(tsErrCust_LgtFctStatus *psErrCust_RteAccess_LgtFctStatus)
{
  *psErrCust_RteAccess_LgtFctStatus = ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_FctR_TI_FctErrState
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_RteAccess_Read_FctR_TI_FctErrState
///
/// \param  boErrCust_RteAccess_Lgt_TI_State
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_FctR_TI_FctErrState(boolean *boErrCust_RteAccess_Lgt_TI_State)
{
  *boErrCust_RteAccess_Lgt_TI_State = ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1;
  ErrCust_RteAccess_Read_FctR_TI_FctErrState_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketAttitudeEcuData
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_CaptureAftermarketAttitudeEcuData
///
/// \param  psOutputData
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketAttitudeEcuData(tsErrCust_AftermarketAttitudeEcuData* psOutputData)
{
  *psOutputData = ErrCust_CaptureAftermarketAttitudeEcuData_Param1;
  ErrCust_CaptureAftermarketAttitudeEcuData_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketLvlEcuData
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_CaptureAftermarketLvlEcuData
///
/// \param  psOutputData
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketLvlEcuData(tsErrCust_AftermarketLvlEcuData* psOutputData)
{
  *psOutputData = ErrCust_CaptureAftermarketLvlEcuData_Param1;
  ErrCust_CaptureAftermarketLvlEcuData_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketContextEcuData
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_CaptureAftermarketContextEcuData
///
/// \param  psOutputData
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketContextEcuData(tsErrCust_AftermarketContextEcuData* psOutputData)
{
  *psOutputData = ErrCust_CaptureAftermarketContextEcuData_Param1;
  ErrCust_CaptureAftermarketContextEcuData_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketRbinEepromLmmEcuData
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_CaptureAftermarketRbinEepromLmmEcuData
///
/// \param  psOutputData
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketRbinEepromLmmEcuData(tsErrCust_AftermarketRbinEepromLmmData* psOutputData)
{
  *psOutputData = ErrCust_CaptureAftermarketRbinEepromLmmEcuData_Param1;
  ErrCust_CaptureAftermarketRbinEepromLmmEcuData_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketLedOutputFailEcuData
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_CaptureAftermarketRbinEepromLmmEcuData
///
/// \param  psOutputData
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketLedOutputFailEcuData(tsErrCust_AftermarketLedChnlOutData* psOutputData)
{
  *psOutputData = ErrCust_CaptureAftermarketLedOutputFailEcuData_Param1;
  ErrCust_CaptureAftermarketLedOutputFailEcuData_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_CaptureAftermarketLedOutputFailEcuData
///
/// \descr  Stub function created to simulate the behaviour of ErrCust_CaptureAftermarketRbinEepromLmmEcuData
///
/// \param  psOutputData
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_CaptureAftermarketRbinNtcFailureEcuData(tsErrCust_AftermarketRbinNtcFailureData* psOutputData)
{
  *psOutputData = ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1;
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam(void)
{
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount++;

  return SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetLowBeamState
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_GetLowBeamState
///
/// \param  void
///
/// \return SysMon_EnumLowBeamState
//-----------------------------------------------------------------------------
SysMon_EnumLowBeamState SysMonRx_ASIL_GetLowBeamState(void)
{
  SysMonRx_ASIL_GetLowBeamState_HitCount++;

  return SysMonRx_ASIL_GetLowBeamState_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetSpeedState
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_GetSpeedState
///
/// \param  void
///
/// \return SysMon_EnumSpeedState
//-----------------------------------------------------------------------------
SysMon_EnumSpeedState SysMonRx_ASIL_GetSpeedState(void)
{
  SysMonRx_ASIL_GetSpeedState_HitCount++;

  return SysMonRx_ASIL_GetSpeedState_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetTurnIndicatorState
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_GetTurnIndicatorState
///
/// \param  void
///
/// \return SysMon_EnumTurnIndicatorState
//-----------------------------------------------------------------------------
SysMon_EnumTurnIndicatorState SysMonRx_ASIL_GetTurnIndicatorState(void)
{
  SysMonRx_ASIL_GetTurnIndicatorState_HitCount++;

  return SysMonRx_ASIL_GetTurnIndicatorState_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_GetTurnIndicatorCommandValue
///
/// \descr  Stub function created to simulate the behaviour of SysMonCheck_GetTurnIndicatorCommandValue
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_GetTurnIndicatorCommandValue(void)
{
  SysMonCheck_GetTurnIndicatorCommandValue_HitCount++;

  return SysMonCheck_GetTurnIndicatorCommandValue_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start
///
/// \descr  Stub function created to simulate the behaviour of roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start
///
/// \param  ucChannelNo
///         ucSwitchOutput
///
/// \return void
//-----------------------------------------------------------------------------
void roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(uint8 ucChannelNo, uint8 ucSwitchOutput)
{
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param1 = ucChannelNo;
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param2 = ucSwitchOutput;
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop
///
/// \descr  Stub function created to simulate the behaviour of roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop
///
/// \param  ucChannelNo
///
/// \return void
//-----------------------------------------------------------------------------
void roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(uint8 ucChannelNo)
{
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_Param1 = ucChannelNo;
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  Mcu_PerformReset
///
/// \descr  Stub function created to simulate the behaviour of Mcu_PerformReset
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Mcu_PerformReset(void)
{
  Mcu_PerformReset_HitCount++;
}



//-----------------------------------------------------------------------------
/// \brief  DiagControl_ProgrammingSesion_Request
///
/// \descr  Stub function created to simulate the behaviour of DiagControl_ProgrammingSesion_Request
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void  DiagControl_ProgrammingSesion_Request(void)
{
  DiagControl_ProgrammingSesion_Request_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  CddEft_DataValid
///
/// \descr  Stub function created to simulate the behaviour of CddEft_DataValid
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddEft_DataValid(void)
{
  CddEft_DataValid_HitCount++;

  return CddEft_DataValid_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_ChState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlLed_ChState
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------

Std_ReturnType Rte_Read_CtrlLed_ChState(tsRte_CtrlLed_ChStatesDiag* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_ChState_Param1;
  Rte_Read_CtrlLed_ChState_HitCount++;
  return Rte_Read_CtrlLed_ChState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_PcbTemperature
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_PcbTemperature
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------

void Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1)
{
  *ppara1 = Rte_Read_RSens_PcbTemperature_Param1;
  Rte_Read_RSens_PcbTemperature_HitCount++;
  return Rte_Read_RSens_PcbTemperature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Deh_ClearAndInitDehLogTab
///
/// \descr  Stub function created to simulate the behaviour of Deh_ClearAndInitDehLogTab
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
void Deh_ClearAndInitDehLogTab(void)
{
  Deh_ClearAndInitDehLogTab_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_Diag_TiScrollingTakeOver
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_Diag_TiScrollingTakeOver
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_TiScrollingTakeOver(boolean* ppara1)
{
  *ppara1 = Rte_Read_Diag_TiScrollingTakeOver_Param1;
  Rte_Read_Diag_TiScrollingTakeOver_HitCount++;
  return Rte_Read_Diag_TiScrollingTakeOver_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddMlc_GetEEPROMAddressId
/// 
/// \descr  Stub function to simulate the behavoiur of CddMlc_GetEEPROMAddressId
///
/// \param 
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddMlc_GetEEPROMAddressId(void)
{
  CddMlc_GetEEPROMAddressId_HitCount++;
  return CddMlc_GetEEPROMAddressId_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningDataDiag
///
/// \descr  Stub function created to simulate the behavior of Rte_Read_RSens_BinningDataDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningDataDiag(tsRte_D409Binning* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningDataDiag_Param1;
  Rte_Read_RSens_BinningDataDiag_HitCount++;
  return Rte_Read_RSens_BinningDataDiag_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Diag_Scrolling_TgtValue
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Diag_Scrolling_TgtValue
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Diag_Scrolling_TgtValue(const teRte_ScrollingTgt* ppara1)
{
  Rte_Write_Diag_Scrolling_TgtValue_Param1 = *ppara1;
  Rte_Write_Diag_Scrolling_TgtValue_HitCount++;

  return Rte_Write_Diag_Scrolling_TgtValue_RetVal;
}


// EOF

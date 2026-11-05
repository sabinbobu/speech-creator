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
// Stub function parameter stubs
//=============================================================================
tLinearPoint                     UtilMath_LinearInterpolate_Param1[2];
sint32                           UtilMath_LinearInterpolate_Param2;
sint32                           UtilMath_LinearInterpolate_Param3;
tsRteCodingParameters            Rte_Read_CodM_AppM_Para_Param1;
tsRte_SysMon_LifePhases          Rte_Read_SysMon_LifePhases_Param1;
teRte_MountingSide               Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_SysMonLgtFctsReq           Rte_Read_SysMon_StdLgtFcts_Req_Param1;
tiu32Voltage_mV                  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
tsRte_NTCTemperature             Rte_Read_RSens_ThermzoneTemperatures_Param1;
tsRte_PcbTemperatureMsg          Rte_Read_RSens_PcbTemperature_Param1;
tsRte_TgtLedSig0Arr              Rte_Read_CtrlLed_TgtLedSig_sVal_Param1;
tsRte_TgtPxlSig0Arr              Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1;
tsRte_TgtPxlSig0Arr              Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_Param1;
tsRte_TgtLedSig0Arr*             Rte_Write_Cpm_TgtLedSig_sVal_Param1;
tsRteHssTarget*                  Rte_Write_CpmHssTarget0_sSetting_Param1;
uint32                           LPTMR0_GetTimeElapsed_Param1;
tsRtePowFactTemp                 Rte_Write_Cpm_PowFact_Temp_Param1;
tsRte_PowerFactor                Rte_Write_Cpm_SigPrepTx_PowerFactor_Param1;
tunPercent_1_328                 FanM_Gen_Param1[12];
tunPercent_1_328                 FanM_Gen_Param2[8][16];
boolean                          FanM_Gen_Param3[2];
tsTemperatureArr14               FanM_Gen_Param4;
tsTemperatureArr8                FanM_Gen_Param5;
tunPercent_1_328                 CPM_Gen_Param1[8][16];
tunPercent_1_328                 CPM_Gen_Param2[8][16];
tsLsTargetPercArr13              CPM_Gen_Param3;
tsLsTargetPercArr13              CPM_Gen_Param4;
tsVoltage                        CPM_Gen_Param5;
tsTemperature                    CPM_Gen_Param6;
tsTemperatureArr14               CPM_Gen_Param7;
tsTemperatureArr8                CPM_Gen_Param8;
tsRte_TgtLedSig0                 Rte_Read_CtrlLed_TgtHssSig_sVal_Param1;
tsRte_CpmHSS3Duty                Rte_Write_Cpm_CtrlSwi_HSS3Target_Param1;
NM_ModeType                      NM_GetMode_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint8                            UtilMath_LinearInterpolate_RetVal;
uint8                            Rte_Read_CodM_AppM_Para_RetVal;
uint8                            Rte_Read_SysMon_LifePhases_RetVal;
uint8                            Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
uint8                            Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
uint8                            Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
uint8                            Rte_Read_RSens_ThermzoneTemperatures_RetVal;
uint8                            Rte_Read_RSens_PcbTemperature_RetVal;
uint8                            Rte_Read_CtrlLed_TgtLedSig_sVal_RetVal;
uint8                            Rte_Read_CtrlLed_Cpm_TgtPxlSig_RetVal;
uint8                            Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;
uint8                            Rte_Write_Cpm_TgtLedSig_sVal_RetVal;
uint8                            Rte_Write_CpmHssTarget0_sSetting_RetVal;
uint8                            LPTMR0_GetTimeElapsed_RetVal;
uint8                            Rte_Write_Cpm_PowFact_Temp_RetVal;
uint8                            Rte_Write_Cpm_SigPrepTx_PowerFactor_RetVal;
uint8                            CPM_Gen_RetVal;
uint8                            FanM_Gen_RetVal;
Std_ReturnType                   Rte_Read_CtrlLed_TgtHssSig_sVal_RetVal;
Std_ReturnType                   Rte_Write_Cpm_CtrlSwi_HSS3Target_RetVal;
NM_ErrorCodeType                 NM_GetMode_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8                            UtilMath_LinearInterpolate_HitCount;
uint8                            Rte_Read_CodM_AppM_Para_HitCount;
uint8                            Rte_Read_SysMon_LifePhases_HitCount;
uint8                            Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8                            Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8                            Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint8                            Rte_Read_RSens_ThermzoneTemperatures_HitCount;
uint8                            Rte_Read_RSens_PcbTemperature_HitCount;
uint8                            Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount;
uint8                            Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount;
uint8                            Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_HitCount;
uint8                            Rte_Write_Cpm_TgtLedSig_sVal_HitCount;
uint8                            Rte_Write_CpmHssTarget0_sSetting_HitCount;
uint8                            LPTMR0_GetTimeElapsed_HitCount;
uint8                            Rte_Write_Cpm_PowFact_Temp_HitCount;
uint8                            Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount;
uint8                            CPM_Gen_HitCount;
uint8                            FanM_Gen_HitCount;
uint8                            Rte_Read_CtrlLed_TgtHssSig_sVal_HitCount;
uint8                            Rte_Write_Cpm_CtrlSwi_HSS3Target_HitCount;
uint8                            NM_GetMode_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  NM_GetMode
///
/// \descr  Stub function created to simulate the behaviour of NM_GetMode
///
/// \param  p_NMMode
///
/// \return NM_ErrorCodeType
//-----------------------------------------------------------------------------
NM_ErrorCodeType NM_GetMode(NM_ModeType * p_NMMode)
{
  *p_NMMode = NM_GetMode_Param1;
  NM_GetMode_HitCount++;

  return NM_GetMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  UtilMath_LinearInterpolate
/// 
/// \descr  Stub function to simulate the behavoiur of UtilMath_LinearInterpolate
///
/// \param  pPoints
/// \param  nLinPairs
/// \param  lX
///
/// \return sint32
//----------------------------------------------------------------------------
sint32 UtilMath_LinearInterpolate(const tLinearPoint* pPoints, sint32 nLinPairs, sint32 lX)
{
  UtilMath_LinearInterpolate_Param1[2] = *pPoints;
  UtilMath_LinearInterpolate_Param2 = nLinPairs;
  UtilMath_LinearInterpolate_Param3 = lX;
  UtilMath_LinearInterpolate_HitCount++;
  return UtilMath_LinearInterpolate_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_AppM_Para
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CodM_AppM_Para
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_AppM_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_AppM_Para_Param1;
  Rte_Read_CodM_AppM_Para_HitCount++;
  return Rte_Read_CodM_AppM_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_TgtHssSig_sVal
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CtrlLed_TgtHssSig_sVal
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_TgtHssSig_sVal(tsRte_TgtLedSig0* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_TgtHssSig_sVal_Param1;
  Rte_Read_CtrlLed_TgtHssSig_sVal_HitCount++;
  return Rte_Read_CtrlLed_TgtHssSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_SysMon_LifePhases
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;
  return Rte_Read_SysMon_LifePhases_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;
  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtFcts_Req
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_SysMon_StdLgtFcts_Req
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1)
{
  *ppara1 = Rte_Read_SysMon_StdLgtFcts_Req_Param1;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount++;
  Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;
  return Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_ThermzoneTemperatures
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_RSens_ThermzoneTemperatures
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1)
{
  *ppara1 = Rte_Read_RSens_ThermzoneTemperatures_Param1;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount++;
  return Rte_Read_RSens_ThermzoneTemperatures_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_PcbTemperature
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_RSens_PcbTemperature
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1)
{
  ppara1 = &Rte_Read_RSens_PcbTemperature_Param1;
  Rte_Read_RSens_PcbTemperature_HitCount++;
  return Rte_Read_RSens_PcbTemperature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_TgtLedSig_sVal
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CtrlLed_TgtLedSig_sVal
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{
  ppara1 = Rte_Read_CtrlLed_TgtLedSig_sVal_Param1;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount++;
  return Rte_Read_CtrlLed_TgtLedSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_Cpm_TgtPxlSig
/// 
/// \descr  Stub function to simulate the behaviour of Rte_Read_CtrlLed_Cpm_TgtPxlSig
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_Cpm_TgtPxlSig(tsRte_TgtPxlSig0Arr* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount++;
  return Rte_Read_CtrlLed_Cpm_TgtPxlSig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1)
{
  Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_Param1 = *ppara1;
  Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_HitCount++;
  return Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Cpm_CtrlSwi_HSS3Target
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_Cpm_CtrlSwi_HSS3Target
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Cpm_CtrlSwi_HSS3Target(const tsRte_CpmHSS3Duty* ppara1)
{
  Rte_Write_Cpm_CtrlSwi_HSS3Target_Param1 = *ppara1;
  Rte_Write_Cpm_CtrlSwi_HSS3Target_HitCount++;
  return Rte_Write_Cpm_CtrlSwi_HSS3Target_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Cpm_TgtLedSig_sVal
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_Cpm_TgtLedSig_sVal
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{
  Rte_Write_Cpm_TgtLedSig_sVal_Param1 = ppara1;
  Rte_Write_Cpm_TgtLedSig_sVal_HitCount++;
  return Rte_Write_Cpm_TgtLedSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CpmHssTarget0_sSetting
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_CpmHssTarget0_sSetting
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CpmHssTarget0_sSetting(tsRteHssTarget* ppara1)
{
  Rte_Write_CpmHssTarget0_sSetting_Param1 = ppara1;
  Rte_Write_CpmHssTarget0_sSetting_HitCount++;
  return Rte_Write_CpmHssTarget0_sSetting_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR0_GetTimeElapsed
/// 
/// \descr  Stub function to simulate the behavoiur of LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;
  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Cpm_PowFact_Temp
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_Cpm_PowFact_Temp
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Cpm_PowFact_Temp(tsRtePowFactTemp* ppara1)
{
  Rte_Write_Cpm_PowFact_Temp_Param1 = *ppara1;
  Rte_Write_Cpm_PowFact_Temp_HitCount++;
  return Rte_Write_Cpm_PowFact_Temp_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Cpm_SigPrepTx_PowerFactor
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Write_Cpm_SigPrepTx_PowerFactor
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Cpm_SigPrepTx_PowerFactor(const tsRte_PowerFactor* ppara1)
{
  Rte_Write_Cpm_SigPrepTx_PowerFactor_Param1 = *ppara1;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount++;
  return Rte_Write_Cpm_SigPrepTx_PowerFactor_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FanM_Gen
/// 
/// \descr  Stub function to simulate the behavoiur of FanM_Gen
///
/// \param  asLsTargetSetting0[12]
/// \param  aunExtSwitchSetting0[8][16]
/// \param  abFanRequest1[2]
/// \param  sIoTemp0
/// \param  sLmmTemp0
///
/// \return void
//-----------------------------------------------------------------------------
void FanM_Gen(tunPercent_1_328 asLsTargetSetting0[12], tunPercent_1_328 aunExtSwitchSetting0[8][16],
  boolean abFanRequest1[2], tsTemperatureArr14 * sIoTemp0, tsTemperatureArr8 * sLmmTemp0)
{
  for (uint8 ucIdx = 0u; ucIdx < 12u; ucIdx++)

    FanM_Gen_Param1[ucIdx] = asLsTargetSetting0[ucIdx];

  for (uint8 ucIdx = 0u; ucIdx < 8u; ucIdx++)
  {
    for (uint8 ucJdx = 0u; ucJdx < 16u; ucJdx++)
    {
      FanM_Gen_Param2[ucIdx][ucJdx] = aunExtSwitchSetting0[ucIdx][ucJdx];
    }
  }

  FanM_Gen_Param3[2] = abFanRequest1[2];
  FanM_Gen_Param4 = *sIoTemp0;
  FanM_Gen_Param5 = *sLmmTemp0;
  FanM_Gen_HitCount++;

  return FanM_Gen_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CPM_Gen
/// 
/// \descr  Stub function to simulate the behavoiur of CPM_Gen
///
/// \param  aunExtSwitchSetting0[8][16]
/// \param  aunExtSwitchSetting1[8][16]
/// \param  asLsTargetSetting0
/// \param  asLsTargetSetting1
/// \param  sActVoltage0
/// \param  sEcuTemp0
/// \param  sIoTemp0
/// \param  sLmmTemp0
///
/// \return void
//-----------------------------------------------------------------------------
void CPM_Gen(tunPercent_1_328 aunExtSwitchSetting0[8][16], tunPercent_1_328
  aunExtSwitchSetting1[8][16], tsLsTargetPercArr13 * asLsTargetSetting0, tsLsTargetPercArr13 *
  asLsTargetSetting1, tsVoltage * sActVoltage0, tsTemperature * sEcuTemp0, tsTemperatureArr14 *
  sIoTemp0, tsTemperatureArr8 * sLmmTemp0)
{
  for (uint8 ucIdx = 0u; ucIdx < 8u; ucIdx++)
  {
    for (uint8 ucJdx = 0u; ucJdx < 16u; ucJdx++)
    {
      CPM_Gen_Param1[ucIdx][ucJdx] = aunExtSwitchSetting0[ucIdx][ucJdx];
      CPM_Gen_Param2[ucIdx][ucJdx] = aunExtSwitchSetting1[ucIdx][ucJdx];
    }
  }

  *asLsTargetSetting0 = CPM_Gen_Param3;
  *asLsTargetSetting1 = CPM_Gen_Param4;
  *sActVoltage0 = CPM_Gen_Param5;
  *sEcuTemp0 = CPM_Gen_Param6;
  *sIoTemp0 = CPM_Gen_Param7;
  *sLmmTemp0 = CPM_Gen_Param8;

  CPM_Gen_HitCount++;
  return CPM_Gen_RetVal;
}

// EOF
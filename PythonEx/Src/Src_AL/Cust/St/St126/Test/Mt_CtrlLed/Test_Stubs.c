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
// Global variable stubs
//=============================================================================

tNvmPara_CodingArea           Coding_Dummy = { 0u };
tParaFct0_Cmd                 Coding_State = eParaFct0_CodingDataInvalid;

//=============================================================================
// Stub function parameter stubs
//=============================================================================

tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_00_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_01_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_02_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_03_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_04_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_05_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_06_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_07_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_08_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_09_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_10_Param1;
tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_11_Param1;
tsRte_MtxEeprom_ErrStatus   Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
tisHssStatusError           Rte_Read_CtrlSwi_StatusErr_Param1;
tsRte_Hss3Status            Rte_Read_CtrlSwi_Hss3StatusErr_Param1;

tsRte_PxaIntensityMatrix    Rte_Read_AdbPxa_IntensityMatrix_Param1;
teRte_MountingSide          Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRteCodingParameters       Rte_Read_CodM_CtrlLed_Para_Param1;
tsRte_SysMon_LedStates      Rte_Read_SysMon_LedState_Param1;
tauRte_CtrlPxl_Mtx_bErr     Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1;
tsRte_MatrixFaultStates     Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1;
teRte_CddMlc_SystemMode     Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1;
tsRte_TgtLedVal0Arr         Rte_Read_FctR_TgtLed_sVal_Param1;
tiu32Voltage_mV             Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
teRte_SysVolt_Results       Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
boolean                     Rte_Read_Diag_DD01_Activation_Param1;
tsRte_DIDPixelActivation    Rte_Read_Diag_DD01_PixelActivation_Param1;

tsRte_ChLedSettings         Rte_Write_CtrlLed_LedSettings_sVal_Param1;
tsRte_CtrlLed_ChStatesDiag  Rte_Write_CtrlLed_ChState_Param1;
tsRte_LedErrStateArr        Rte_Write_CtrlLed_ActLed_sState_Param1;
tsRte_TgtPxlSig0Arr         Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1;
tsRte_TgtLedSig0Arr         Rte_Write_CtrlLed_TgtLedSig_sVal_Param1;
tsRte_ucBinningSelect       Rte_Write_CtrlLed_BinningClass_Param1;
tsRte_TgtLedSig0            Rte_Write_CtrlLed_TgtHssSig_sVal_Param1;
tsRte_LedChFbit             Rte_Write_CtrlLed_LedChFbit_Param1;

tLinearPoint                UtilMath_LinearInterpolate_Param1[2];
sint32                      UtilMath_LinearInterpolate_Param2;
sint32                      UtilMath_LinearInterpolate_Param3;
uint16*                     UtilMath_FastInterpolateU16_Param1;
sint32                      UtilMath_FastInterpolateU16_Param2;
uint16                      UtilMath_FastInterpolateU16_Param3;
uint32                      LPTMR0_GetTimeElapsed_Param1;
uint16                      Dem_SetEventStatus_Param1;
uint8                       Dem_SetEventStatus_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_00_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_01_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_02_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_03_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_04_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_05_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_06_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_07_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_08_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_09_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_10_RetVal;
Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_11_RetVal;

Std_ReturnType  Rte_Read_AdbPxa_IntensityMatrix_RetVal;
Std_ReturnType  Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType  Rte_Read_CodM_CtrlLed_Para_RetVal;
Std_ReturnType  Rte_Read_SysMon_LedState_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_RetVal;
Std_ReturnType  Rte_Read_FctR_TgtLed_sVal_RetVal;
tiu32Voltage_mV Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
Std_ReturnType  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
Std_ReturnType  Rte_Read_Diag_DD01_Activation_RetVal;
Std_ReturnType  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
Std_ReturnType  Rte_Read_CtrlSwi_StatusErr_RetVal;
Std_ReturnType  Rte_Read_CtrlSwi_Hss3StatusErr_RetVal;
Std_ReturnType  Rte_Read_Diag_DD01_PixelActivation_RetVal;

Std_ReturnType  Rte_Write_CtrlLed_LedSettings_sVal_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_ChState_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_ActLed_sState_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_Cpm_TgtPxlSig_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_TgtLedSig_sVal_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_BinningClass_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_TgtHssSig_sVal_RetVal;
Std_ReturnType  Rte_Write_CtrlLed_LedChFbit_RetVal;

sint32              UtilMath_LinearInterpolate_RetVal;
uint16              UtilMath_FastInterpolateU16_RetVal;
uint32              LPTMR0_GetTimeElapsed_RetVal;
tsRte_TgtAniArr     Anima_Tgt_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8  Rte_Read_RSens_BinningClass_sVal_00_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_01_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_02_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_03_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_04_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_05_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_06_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_07_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_08_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_09_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_10_HitCount;
uint8  Rte_Read_RSens_BinningClass_sVal_11_HitCount;

uint8  Rte_Read_AdbPxa_IntensityMatrix_HitCount;
uint8  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8  Rte_Read_CodM_CtrlLed_Para_HitCount;
uint8  Rte_Read_SysMon_LedState_HitCount;
uint8  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount;
uint8  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_HitCount;
uint8  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_HitCount;
uint8  Rte_Read_FctR_TgtLed_sVal_HitCount;
uint8  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint8  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount;
uint8  Rte_Read_Diag_DD01_Activation_HitCount;
uint8  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount;
uint8  Rte_Read_CtrlSwi_StatusErr_HitCount;
uint8  Rte_Read_CtrlSwi_Hss3StatusErr_HitCount;
uint8  Rte_Read_Diag_DD01_PixelActivation_HitCount;

uint8  Rte_Write_CtrlLed_LedSettings_sVal_HitCount;
uint8  Rte_Write_CtrlLed_ChState_HitCount;
uint8  Rte_Write_CtrlLed_ActLed_sState_HitCount;
uint8  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount;
uint8  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount;
uint8  Rte_Write_CtrlLed_BinningClass_HitCount;
uint8  Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount;
uint8  Rte_Write_CtrlLed_LedChFbit_HitCount;

uint8  UtilMath_LinearInterpolate_HitCount;
uint8  UtilMath_FastInterpolateU16_HitCount;
uint8  LPTMR0_GetTimeElapsed_HitCount;
uint8  Anima_Tgt_HitCount;
uint8  Anima_Cycle10_HitCount;
uint8  Anima_Init_HitCount;
uint8  Anima_TgtPrep_Init_HitCount;
uint8  Dem_SetEventStatus_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;
  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief UtilMath_LinearInterpolate
///
/// \descr Stub function to simulate the behavior of UtilMath_LinearInterpolate
///
/// \param  pPoints
/// \param  nLinPairs
/// \param  lX
///
/// \return sint32
//-----------------------------------------------------------------------------
sint32 UtilMath_LinearInterpolate(const tLinearPoint* pPoints, sint32 nLinPairs, sint32 lX)
{
  UtilMath_LinearInterpolate_Param1[2] = *pPoints;
  UtilMath_LinearInterpolate_Param2 = nLinPairs;
  UtilMath_LinearInterpolate_Param3 = lX;

  UtilMath_LinearInterpolate_HitCount++;
  return UtilMath_LinearInterpolate_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief UtilMath_FastInterpolateU16
///
/// \descr Stub function to simulate the behavor of UtilMath_FastInterpolateU16
///
/// \param  punY
/// \param  lShift
/// \param  unX
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 UtilMath_FastInterpolateU16(const uint16* punY, sint32 lShift, uint16 unX)
{
  UtilMath_FastInterpolateU16_Param1 = punY;
  UtilMath_FastInterpolateU16_Param2 = lShift;
  UtilMath_FastInterpolateU16_Param3 = unX;

  UtilMath_FastInterpolateU16_HitCount++;
  return UtilMath_FastInterpolateU16_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_Tgt
///
/// \descr  Stub function to simulate the behavior of Anima_Tgt
///
/// \param  
///
/// \return tsRte_TgtAniArr
//-----------------------------------------------------------------------------
tsRte_TgtAniArr* Anima_Tgt(void)
{
  Anima_Tgt_HitCount++;
  return &Anima_Tgt_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_Init
///
/// \descr  Stub function to simulate the behavior of Anima_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_Init(void)
{
  Anima_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_TgtPrep_Init
///
/// \descr  Stub function to simulate the behavior of Anima_TgtPrep_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_TgtPrep_Init(void)
{
	Anima_TgtPrep_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_Cycle10
///
/// \descr  Stub function to simulate the behavior of Anima_Cycle10
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_Cycle10(void)
{
  Anima_Cycle10_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Param1 = unAlecId;
  Dem_SetEventStatus_Param2 = ucTestStatus;
  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_AdbPxa_IntensityMatrix
///
/// \descr  Stub function to simulate the behavior of Rte_Read_AdbPxa_IntensityMatrix
///
/// \param  pTarget
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_AdbPxa_IntensityMatrix(tsRte_PxaIntensityMatrix* pTarget)
{
  *pTarget = Rte_Read_AdbPxa_IntensityMatrix_Param1;
  Rte_Read_AdbPxa_IntensityMatrix_HitCount++;
  return Rte_Read_AdbPxa_IntensityMatrix_RetVal;
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
/// \brief  Rte_Read_CodM_CtrlLed_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_CtrlLed_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CtrlLed_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CtrlLed_Para_Param1;
  Rte_Read_CodM_CtrlLed_Para_HitCount++;

  return Rte_Read_CodM_CtrlLed_Para_RetVal;
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
  tuRte_CtrlPxl_bErr* pTest = (tuRte_CtrlPxl_bErr*)ppara1;

  for (uint32 ulIdx = 0u; ulIdx < CFG_LOGICAL_UNITS; ulIdx++)
  {
    *((uint8*)(void*)pTest++) = *((uint8*)(void*)&Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[ulIdx]);
  }
  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount++;

  return Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState(tsRte_MatrixFaultStates* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1;
  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_HitCount++;
  return Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal(teRte_CddMlc_SystemMode* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1;
  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_HitCount++;
  return Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_00
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_00_Param1;
  Rte_Read_RSens_BinningClass_sVal_00_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_01
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_01_Param1;
  Rte_Read_RSens_BinningClass_sVal_01_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_02
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_02_Param1;
  Rte_Read_RSens_BinningClass_sVal_02_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_03
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_03_Param1;
  Rte_Read_RSens_BinningClass_sVal_03_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_03_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_04
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_04_Param1;
  Rte_Read_RSens_BinningClass_sVal_04_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_04_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_05
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_05
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_05_Param1;
  Rte_Read_RSens_BinningClass_sVal_05_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_05_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_06
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_06
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_06_Param1;
  Rte_Read_RSens_BinningClass_sVal_06_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_06_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_07
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_07
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_07_Param1;
  Rte_Read_RSens_BinningClass_sVal_07_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_07_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_08
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_08
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_08_Param1;
  Rte_Read_RSens_BinningClass_sVal_08_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_08_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_09
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_09
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_09_Param1;
  Rte_Read_RSens_BinningClass_sVal_09_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_09_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_10
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_10
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_10_Param1;
  Rte_Read_RSens_BinningClass_sVal_10_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_10_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_11
/// 
/// \descr  Stub function to simulate the behavoiur of  Rte_Read_RSens_BinningClass_sVal_11
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_11_Param1;
  Rte_Read_RSens_BinningClass_sVal_11_HitCount++;
  return Rte_Read_RSens_BinningClass_sVal_11_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr Stub function to simulate the behavior of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
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
/// \brief  Rte_Read_FctR_TgtLed_sVal
///
/// \descr  Stub function to simulate the behavior of Rte_Read_FctR_TgtLed_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_TgtLed_sVal(tsRte_TgtLedVal0Arr* ppara1)
{
  *ppara1 = Rte_Read_FctR_TgtLed_sVal_Param1;
  Rte_Read_FctR_TgtLed_sVal_HitCount++;
  return Rte_Read_FctR_TgtLed_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysVolt_LedVoltRng0_sVoltRng
///
/// \descr Stub function to simulate the behavior of Rte_Read_SysVolt_LedVoltRng0_sVoltRng
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1)
{
  *ppara1 = Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount++;
  return Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Diag_DD01_Activation
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_Diag_DD01_Activation
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_DD01_Activation(boolean* ppara1)
{
  *ppara1 = Rte_Read_Diag_DD01_Activation_Param1;
  Rte_Read_Diag_DD01_Activation_HitCount++;
  return Rte_Read_Diag_DD01_Activation_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus(tsRte_MtxEeprom_ErrStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount++;
  return Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlSwi_StatusErr
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CtrlSwi_StatusErr
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
/// \brief  Rte_Read_CtrlSwi_Hss3StatusErr
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CtrlSwi_Hss3StatusErr
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
/// \brief  Rte_Write_CtrlLed_LedSettings_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_LedSettings_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_LedSettings_sVal(const tsRte_ChLedSettings* ppara1)
{
  Rte_Write_CtrlLed_LedSettings_sVal_Param1 = *ppara1;
  Rte_Write_CtrlLed_LedSettings_sVal_HitCount++;
  return Rte_Write_CtrlLed_LedSettings_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_ChState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_ChState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_ChState(const tsRte_CtrlLed_ChStatesDiag* ppara1)
{
    Rte_Write_CtrlLed_ChState_Param1 = *ppara1;
    Rte_Write_CtrlLed_ChState_HitCount++;
    return Rte_Write_CtrlLed_ChState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_ActLed_sState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_ActLed_sState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_ActLed_sState(const tsRte_LedErrStateArr* ppara1)
{
  for (uint32 ulIdx = 0u; ulIdx < CFG_LSM_LED_ILLUMINANT_NR; ulIdx++)
  {
    Rte_Write_CtrlLed_ActLed_sState_Param1.uIlluminantState[ulIdx] = ppara1->uIlluminantState[ulIdx];
    Rte_Write_CtrlLed_ActLed_sState_Param1.boIlluminantStatus[ulIdx] = ppara1->boIlluminantStatus[ulIdx];
  }
  Rte_Write_CtrlLed_ActLed_sState_HitCount++;

  return Rte_Write_CtrlLed_ActLed_sState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_TgtLedSig_sVal
///
/// \descr  Stub function to simulate the behavior of Rte_Write_CtrlLed_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_TgtLedSig_sVal(const tsRte_TgtLedSig0Arr* ppara1)
{
  for (uint32 ulIdx = 0u; ulIdx < sizeof(tsRte_TgtLedSig0Arr); ulIdx++)
  {
    *((uint8*)(void*)&Rte_Write_CtrlLed_TgtLedSig_sVal_Param1 + ulIdx) = *((uint8*)(void*)ppara1 + ulIdx);
  }

  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount++;

  return Rte_Write_CtrlLed_TgtLedSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_Cpm_TgtPxlSig
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_Cpm_TgtPxlSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_Cpm_TgtPxlSig(const tsRte_TgtPxlSig0Arr* ppara1)
{
  for (uint32 ulIdx = 0u; ulIdx < CFG_LOGICAL_UNITS; ulIdx++)
  {
    Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ulIdx] = ppara1->unPxl_Int[ulIdx];
  }
  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount++;
  return Rte_Write_CtrlLed_Cpm_TgtPxlSig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_BinningClass
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_BinningClass
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_BinningClass(const tsRte_ucBinningSelect* ppara1)
{
  Rte_Write_CtrlLed_BinningClass_Param1 = *ppara1;
  Rte_Write_CtrlLed_BinningClass_HitCount++;
  return Rte_Write_CtrlLed_BinningClass_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_TgtHssSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_TgtHssSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_TgtHssSig_sVal(const tsRte_TgtLedSig0* ppara1)
{
  Rte_Write_CtrlLed_TgtHssSig_sVal_Param1 = *ppara1;
  Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount++;
  return Rte_Write_CtrlLed_TgtHssSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlLed_LedChFbit
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlLed_LedChFbit
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlLed_LedChFbit(const tsRte_LedChFbit* ppara1)
{
  Rte_Write_CtrlLed_LedChFbit_Param1 = *ppara1;
  Rte_Write_CtrlLed_LedChFbit_HitCount++;
  return Rte_Write_CtrlLed_LedChFbit_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Diag_DD01_PixelActivation
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Diag_DD01_PixelActivation
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_DD01_PixelActivation(tsRte_DIDPixelActivation* ppara1)
{
  *ppara1 = Rte_Read_Diag_DD01_PixelActivation_Param1;
  Rte_Read_Diag_DD01_PixelActivation_HitCount++;
  return Rte_Read_Diag_DD01_PixelActivation_RetVal;
}

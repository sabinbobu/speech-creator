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
uint32                     LPTMR0_GetTimeElapsed_Param1;
tLinearPoint               UtilMath_LinearInterpolate_Param1[];
sint32                     UtilMath_LinearInterpolate_Param2;
sint32                     UtilMath_LinearInterpolate_Param3;
uint16                     Dem_SetEventStatus_Param1;
uint8                      Dem_SetEventStatus_Param2;
tsRteCodingParameters      Rte_Read_CodM_Rsens_Para_Param1;
tsRte_Voltage_mV           Rte_Read_IoHwAb_GetVoltage_NTCs_Param1;
tiu16Voltage_mV            Rte_Read_IoHwAb_GetPCB_Param1;
tsRte_MtxEeprom_ErrStatus  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
tasRte_CtrlPxl_BinEEprom   Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1;
tasRte_MlcAdcResult        Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_Param1;
tsRte_ucBinningSelect      Rte_Read_CtrlLed_BinningClass_Param1;
tsRte_TgtLedSig0Arr        Rte_Read_CtrlLed_TgtLedSig_sVal_Param1;
tsRte_PcbTemperatureMsg    Rte_Write_RSens_PcbTemperature_Param1;
tsRte_NTCTemperature       Rte_Write_RSens_ThermzoneTemperatures_Param1;
tsRteNTCBinInData          Rte_Write_RSens_NTC_BIN_Input_Errors_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_00_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_01_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_02_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_03_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_04_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_05_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_06_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_07_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_08_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_09_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_10_Param1;
tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_11_Param1;
tsRte_D409Binning          Rte_Write_RSens_BinningDataDiag_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint32         LPTMR0_GetTimeElapsed_RetVal;
sint32         UtilMath_LinearInterpolate_RetVal;

Std_ReturnType Rte_Read_CodM_Rsens_Para_RetVal;
Std_ReturnType Rte_Read_IoHwAb_GetVoltage_NTCs_RetVal;
Std_ReturnType Rte_Read_IoHwAb_GetPCB_RetVal;
Std_ReturnType Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_RetVal;
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
Std_ReturnType Rte_Read_CtrlLed_BinningClass_RetVal;
Std_ReturnType Rte_Read_CtrlLed_TgtLedSig_sVal_RetVal;

Std_ReturnType Rte_Write_RSens_PcbTemperature_RetVal;
Std_ReturnType Rte_Write_RSens_ThermzoneTemperatures_RetVal;
Std_ReturnType Rte_Write_RSens_NTC_BIN_Input_Errors_RetVal;

Std_ReturnType Rte_Write_RSens_BinningClass_sVal_00_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_01_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_02_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_03_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_04_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_05_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_06_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_07_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_08_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_09_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_10_RetVal;
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_11_RetVal;
Std_ReturnType Rte_Write_RSens_BinningDataDiag_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 LPTMR0_GetTimeElapsed_HitCount;
uint8 UtilMath_LinearInterpolate_HitCount;
uint8 Dem_SetEventStatus_HitCount;

uint8 Rte_Read_CodM_Rsens_Para_HitCount;
uint8 Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount;
uint8 Rte_Read_IoHwAb_GetPCB_HitCount;
uint8 Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount;
uint8 Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_HitCount;
uint8 Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_HitCount;
uint8 Rte_Read_CtrlLed_BinningClass_HitCount;
uint8 Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount;

uint8 Rte_Write_RSens_PcbTemperature_HitCount;
uint8 Rte_Write_RSens_ThermzoneTemperatures_HitCount;
uint8 Rte_Write_RSens_NTC_BIN_Input_Errors_HitCount;

uint8 Rte_Write_RSens_BinningClass_sVal_00_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_01_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_02_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_03_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_04_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_05_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_06_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_07_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_08_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_09_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_10_HitCount;
uint8 Rte_Write_RSens_BinningClass_sVal_11_HitCount;
uint8 Rte_Write_RSens_BinningDataDiag_HitCount;


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
/// \brief  Rte_Write_RSens_BinningClass_sVal_00
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_00(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_00_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_00_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_00_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_01
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_01(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_01_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_01_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_01_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_02
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_02(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_02_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_02_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_02_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_03
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_03(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_03_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_03_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_03_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_04
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_04(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_04_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_04_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_04_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_05
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_05
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_05(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_05_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_05_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_05_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_06
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_06
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_06(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_06_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_06_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_06_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_07
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_07
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_07(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_07_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_07_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_07_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_08
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_08
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_08(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_08_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_08_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_08_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_09
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_09
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_09(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_09_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_09_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_09_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_10
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_10
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_10(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_10_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_10_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_10_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningClass_sVal_11
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_RSens_BinningClass_sVal_11
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_11(const tsRte_Binning0* ppara1)
{
  Rte_Write_RSens_BinningClass_sVal_11_Param1 = *ppara1;
  Rte_Write_RSens_BinningClass_sVal_11_HitCount++;
  return Rte_Write_RSens_BinningClass_sVal_11_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal
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
  ppara1 = &Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_Param1;
  Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_HitCount++;
  return Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_Rsens_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_Rsens_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_Rsens_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_Rsens_Para_Param1;
  Rte_Read_CodM_Rsens_Para_HitCount++;

  return Rte_Read_CodM_Rsens_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_PcbTemperature
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_RSens_PcbTemperature
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_PcbTemperature(const tsRte_PcbTemperatureMsg* ppara1)
{
  Rte_Write_RSens_PcbTemperature_Param1 = *ppara1;
  Rte_Write_RSens_PcbTemperature_HitCount++;

  return Rte_Write_RSens_PcbTemperature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_ThermzoneTemperatures
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_RSens_ThermzoneTemperatures
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_ThermzoneTemperatures(const tsRte_NTCTemperature* ppara1)
{
  Rte_Write_RSens_ThermzoneTemperatures_Param1 = *ppara1;
  Rte_Write_RSens_ThermzoneTemperatures_HitCount++;

  return Rte_Write_RSens_ThermzoneTemperatures_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_NTC_BIN_Input_Errors
///
/// \descr  Stub function created to simulate the behavior of Rte_Write_RSens_NTC_BIN_Input_Errors
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_NTC_BIN_Input_Errors(const tsRteNTCBinInData* ppara1)
{
  Rte_Write_RSens_NTC_BIN_Input_Errors_Param1 = *ppara1;
  Rte_Write_RSens_NTC_BIN_Input_Errors_HitCount++;

  return Rte_Write_RSens_NTC_BIN_Input_Errors_RetVal;
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
/// \brief  Rte_Read_IoHwAb_GetPCB
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_GetPCB
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_GetPCB(tiu16Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetPCB_Param1;
  Rte_Read_IoHwAb_GetPCB_HitCount++;

  return Rte_Read_IoHwAb_GetPCB_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_BinningClass
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlLed_BinningClass
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_BinningClass(tsRte_ucBinningSelect* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_BinningClass_Param1;
  Rte_Read_CtrlLed_BinningClass_HitCount++;

  return Rte_Read_CtrlLed_BinningClass_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_RSens_BinningDataDiag
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_RSens_BinningDataDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_RSens_BinningDataDiag(tsRte_D409Binning* ppara1)
{
  for (uint8 ucIdx = 0u; ucIdx < 14; ucIdx++)
  {
    //*((uint8*)(void*)&Rte_Write_RSens_BinningDataDiag_Param1 + ucIdx) = *((uint8*)(void*)ppara1 + ucIdx);
    Rte_Write_RSens_BinningDataDiag_Param1.aucBinClass[ucIdx] = ppara1->aucBinClass[ucIdx];
    Rte_Write_RSens_BinningDataDiag_Param1.aunBinCurrent[ucIdx] = ppara1->aunBinCurrent[ucIdx];


  }
  Rte_Write_RSens_BinningDataDiag_HitCount++;

  return Rte_Write_RSens_BinningDataDiag_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_TgtLedSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlLed_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{

  for (uint32 ulIdx = 0u; ulIdx < sizeof(tsRte_TgtLedSig0Arr); ulIdx++)
  {
    *((uint8*)(void*)ppara1 + ulIdx) = *((uint8*)(void*)&Rte_Read_CtrlLed_TgtLedSig_sVal_Param1 + ulIdx);
  }

  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount++;

  return Rte_Read_CtrlLed_TgtLedSig_sVal_RetVal;
}


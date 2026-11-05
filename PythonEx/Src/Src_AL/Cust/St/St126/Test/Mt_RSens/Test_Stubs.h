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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <RteCommonTypes.h>

//=============================================================================
// Typedefs
//=============================================================================
typedef struct
{
  sint32 X;
  sint32 Y;
} tLinearPoint;

//=============================================================================
// Stub function declarations
//=============================================================================
uint32         LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
sint32         UtilMath_LinearInterpolate(const tLinearPoint* pPoints, sint32 nLinPairs, sint32 lX);
void           Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);

Std_ReturnType Rte_Read_CodM_Rsens_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetVoltage_NTCs(tsRte_Voltage_mV* ppara1);
Std_ReturnType Rte_Read_IoHwAb_GetPCB(tiu16Voltage_mV* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus(tsRte_MtxEeprom_ErrStatus* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal(tasRte_CtrlPxl_BinEEprom* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(tasRte_MlcAdcResult* ppara1);
Std_ReturnType Rte_Read_CtrlLed_BinningClass(tsRte_ucBinningSelect* ppara1);
Std_ReturnType Rte_Read_CtrlLed_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);

Std_ReturnType Rte_Write_RSens_PcbTemperature(const tsRte_PcbTemperatureMsg* ppara1);
Std_ReturnType Rte_Write_RSens_ThermzoneTemperatures(const tsRte_NTCTemperature* ppara1);
Std_ReturnType Rte_Write_RSens_NTC_BIN_Input_Errors(const tsRteNTCBinInData* ppara1);

Std_ReturnType Rte_Write_RSens_BinningClass_sVal_00(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_01(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_02(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_03(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_04(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_05(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_06(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_07(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_08(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_09(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_10(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_11(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningDataDiag(tsRte_D409Binning* ppara1);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint16                     Dem_SetEventStatus_Param1;
extern uint8                      Dem_SetEventStatus_Param2;
extern tsRteCodingParameters      Rte_Read_CodM_Rsens_Para_Param1;
extern tsRte_Voltage_mV           Rte_Read_IoHwAb_GetVoltage_NTCs_Param1;
extern tiu16Voltage_mV            Rte_Read_IoHwAb_GetPCB_Param1;
extern tsRte_MtxEeprom_ErrStatus  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
extern tsRte_ucBinningSelect      Rte_Read_CtrlLed_BinningClass_Param1;
extern tsRte_TgtLedSig0Arr        Rte_Read_CtrlLed_TgtLedSig_sVal_Param1;
extern tsRteNTCBinInData          Rte_Write_RSens_NTC_BIN_Input_Errors_Param1;
extern tsRte_Binning0             Rte_Write_RSens_BinningClass_sVal_01_Param1;
extern tsRte_D409Binning          Rte_Write_RSens_BinningDataDiag_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern sint32         UtilMath_LinearInterpolate_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount;
extern uint8 Rte_Read_IoHwAb_GetPCB_HitCount;
extern uint8 Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

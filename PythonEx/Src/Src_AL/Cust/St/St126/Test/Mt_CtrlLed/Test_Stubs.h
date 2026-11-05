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
#include <Rte/RteCommonTypes.h>

//=============================================================================
// Typedef
//=============================================================================

typedef struct
{
  sint32 X;
  sint32 Y;
} tLinearPoint;

//=============================================================================
// Global variable stubs
//=============================================================================

extern tNvmPara_CodingArea  Coding_Dummy;
extern tParaFct0_Cmd        Coding_State;

//=============================================================================
// Stub function declarations
//=============================================================================

Std_ReturnType Rte_Read_AdbPxa_IntensityMatrix(tsRte_PxaIntensityMatrix* pTarget);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1);
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType Rte_Read_CodM_CtrlLed_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_SysMon_LedState(tsRte_SysMon_LedStates* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal(tauRte_CtrlPxl_Mtx_bErr* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState(tsRte_MatrixFaultStates* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal(teRte_CddMlc_SystemMode* ppara1);
Std_ReturnType Rte_Read_CtrlLed_Cpm_TgtPxlSig(tsRte_TgtPxlSig0Arr* ppara1);
Std_ReturnType Rte_Read_FctR_TgtLed_sVal(tsRte_TgtLedVal0Arr* ppara1);
Std_ReturnType Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1);
Std_ReturnType Rte_Read_Diag_DD01_Activation(boolean* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus(tsRte_MtxEeprom_ErrStatus* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_StatusErr(tisHssStatusError* ppara1);
Std_ReturnType Rte_Read_CtrlSwi_Hss3StatusErr(tsRte_Hss3Status* ppara1);
Std_ReturnType Rte_Read_Diag_DD01_PixelActivation(tsRte_DIDPixelActivation* ppara1);

Std_ReturnType Rte_Write_CtrlLed_TgtLedSig_sVal(const tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType Rte_Write_CtrlLed_LedSettings_sVal(const tsRte_ChLedSettings* ppara1);
Std_ReturnType Rte_Write_CtrlLed_ChState(const tsRte_CtrlLed_ChStatesDiag* ppara1);
Std_ReturnType Rte_Write_CtrlLed_ActLed_sState(const tsRte_LedErrStateArr* ppara1);
Std_ReturnType Rte_Write_CtrlLed_Cpm_TgtPxlSig(const tsRte_TgtPxlSig0Arr* ppara1);
Std_ReturnType Rte_Write_CtrlLed_BinningClass(const tsRte_ucBinningSelect* ppara1);
Std_ReturnType Rte_Write_CtrlLed_TgtHssSig_sVal(const tsRte_TgtLedSig0* ppara1);
Std_ReturnType Rte_Write_CtrlLed_LedChFbit(const tsRte_LedChFbit* ppara1);

sint32            UtilMath_LinearInterpolate(const tLinearPoint* pPoints, sint32 nLinPairs, sint32 lX);
uint16            UtilMath_FastInterpolateU16(const uint16* punY, sint32 lShift, uint16 unX);
tsRte_TgtAniArr*  Anima_Tgt(void);
void              Anima_Cycle10(void);
void              Anima_Init(void);
void              Anima_TgtPrep_Init(void);
void              Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_00_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_01_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_02_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_03_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_04_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_05_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_06_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_07_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_08_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_09_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_10_Param1;
extern tsRte_Binning0              Rte_Read_RSens_BinningClass_sVal_11_Param1;
extern tsRte_MtxEeprom_ErrStatus   Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
extern tisHssStatusError           Rte_Read_CtrlSwi_StatusErr_Param1;
extern tsRte_Hss3Status            Rte_Read_CtrlSwi_Hss3StatusErr_Param1;

extern tsRte_PxaIntensityMatrix    Rte_Read_AdbPxa_IntensityMatrix_Param1;
extern teRte_MountingSide          Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRteCodingParameters       Rte_Read_CodM_CtrlLed_Para_Param1;
extern tsRte_SysMon_LedStates      Rte_Read_SysMon_LedState_Param1;
extern tauRte_CtrlPxl_Mtx_bErr     Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1;
extern tsRte_MatrixFaultStates     Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_Param1;
extern teRte_CddMlc_SystemMode     Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_Param1;
extern tsRte_TgtLedVal0Arr         Rte_Read_FctR_TgtLed_sVal_Param1;
extern tiu32Voltage_mV             Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
extern teRte_SysVolt_Results       Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
extern boolean                     Rte_Read_Diag_DD01_Activation_Param1;
extern tsRte_DIDPixelActivation    Rte_Read_Diag_DD01_PixelActivation_Param1;

extern tsRte_ChLedSettings         Rte_Write_CtrlLed_LedSettings_sVal_Param1;
extern tsRte_CtrlLed_ChStatesDiag  Rte_Write_CtrlLed_ChState_Param1;
extern tsRte_LedErrStateArr        Rte_Write_CtrlLed_ActLed_sState_Param1;
extern tsRte_TgtPxlSig0Arr         Rte_Write_CtrlLed_Cpm_TgtPxlSig_Param1;
extern tsRte_TgtLedSig0Arr         Rte_Write_CtrlLed_TgtLedSig_sVal_Param1;
extern tsRte_ucBinningSelect       Rte_Write_CtrlLed_BinningClass_Param1;
extern tsRte_TgtLedSig0            Rte_Write_CtrlLed_TgtHssSig_sVal_Param1;
extern tsRte_LedChFbit             Rte_Write_CtrlLed_LedChFbit_Param1;

extern tLinearPoint                UtilMath_LinearInterpolate_Param1[2];
extern sint32                      UtilMath_LinearInterpolate_Param2;
extern sint32                      UtilMath_LinearInterpolate_Param3;
extern uint16*                     UtilMath_FastInterpolateU16_Param1;
extern sint32                      UtilMath_FastInterpolateU16_Param2;
extern uint16                      UtilMath_FastInterpolateU16_Param3;
extern uint32                      LPTMR0_GetTimeElapsed_Param1;
extern uint16                      Dem_SetEventStatus_Param1;
extern uint8                       Dem_SetEventStatus_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_00_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_01_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_02_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_03_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_04_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_05_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_06_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_07_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_08_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_09_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_10_RetVal;
extern Std_ReturnType  Rte_Read_RSens_BinningClass_sVal_11_RetVal;

extern Std_ReturnType  Rte_Read_AdbPxa_IntensityMatrix_RetVal;
extern Std_ReturnType  Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType  Rte_Read_CodM_CtrlLed_Para_RetVal;
extern Std_ReturnType  Rte_Read_SysMon_LedState_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_RetVal;
extern Std_ReturnType  Rte_Read_FctR_TgtLed_sVal_RetVal;
extern tiu32Voltage_mV Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
extern Std_ReturnType  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
extern Std_ReturnType  Rte_Read_Diag_DD01_Activation_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
extern Std_ReturnType  Rte_Read_CtrlSwi_StatusErr_RetVal;
extern Std_ReturnType  Rte_Read_CtrlSwi_Hss3StatusErr_RetVal;
extern Std_ReturnType  Rte_Read_Diag_DD01_PixelActivation_RetVal;

extern Std_ReturnType  Rte_Write_CtrlLed_LedSettings_sVal_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_ChState_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_ActLed_sState_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_Cpm_TgtPxlSig_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_TgtLedSig_sVal_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_BinningClass_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_TgtHssSig_sVal_RetVal;
extern Std_ReturnType  Rte_Write_CtrlLed_LedChFbit_RetVal;

extern sint32              UtilMath_LinearInterpolate_RetVal;
extern uint16              UtilMath_FastInterpolateU16_RetVal;
extern uint32              LPTMR0_GetTimeElapsed_RetVal;
extern tsRte_TgtAniArr     Anima_Tgt_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8  Rte_Read_RSens_BinningClass_sVal_00_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_01_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_02_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_03_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_04_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_05_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_06_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_07_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_08_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_09_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_10_HitCount;
extern uint8  Rte_Read_RSens_BinningClass_sVal_11_HitCount;

extern uint8  Rte_Read_AdbPxa_IntensityMatrix_HitCount;
extern uint8  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8  Rte_Read_CodM_CtrlLed_Para_HitCount;
extern uint8  Rte_Read_SysMon_LedState_HitCount;
extern uint8  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount;
extern uint8  Rte_Read_CtrlPxl_CtrLed_MatrixFault_sState_HitCount;
extern uint8  Rte_Read_CtrlPxl_CddMlc_SystemMode_eVal_HitCount;
extern uint8  Rte_Read_FctR_TgtLed_sVal_HitCount;
extern uint8  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint8  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount;
extern uint8  Rte_Read_Diag_DD01_Activation_HitCount;
extern uint8  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount;
extern uint8  Rte_Read_CtrlSwi_StatusErr_HitCount;
extern uint8  Rte_Read_CtrlSwi_Hss3StatusErr_HitCount;
extern uint8  Rte_Read_Diag_DD01_PixelActivation_HitCount;

extern uint8  Rte_Write_CtrlLed_LedSettings_sVal_HitCount;
extern uint8  Rte_Write_CtrlLed_ChState_HitCount;
extern uint8  Rte_Write_CtrlLed_ActLed_sState_HitCount;
extern uint8  Rte_Write_CtrlLed_Cpm_TgtPxlSig_HitCount;
extern uint8  Rte_Write_CtrlLed_TgtLedSig_sVal_HitCount;
extern uint8  Rte_Write_CtrlLed_BinningClass_HitCount;
extern uint8  Rte_Write_CtrlLed_TgtHssSig_sVal_HitCount;
extern uint8  Rte_Write_CtrlLed_LedChFbit_HitCount;

extern uint8  UtilMath_LinearInterpolate_HitCount;
extern uint8  UtilMath_FastInterpolateU16_HitCount;
extern uint8  LPTMR0_GetTimeElapsed_HitCount;
extern uint8  Anima_Tgt_HitCount;
extern uint8  Anima_Cycle10_HitCount;
extern uint8  Anima_Init_HitCount;
extern uint8  Anima_TgtPrep_Init_HitCount;
extern uint8  Dem_SetEventStatus_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

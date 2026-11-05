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
#include <../App/Swc/Cpm/Api/Cpm_Adapter.h>
#include <_NM_Types.h>
#include <UtilMath.h>
#include "CPM_GenTypes.h"

//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType                          Rte_Read_CodM_AppM_Para(tsRteCodingParameters* ppara1);
Std_ReturnType                          Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType                          Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType                          Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType                          Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);
Std_ReturnType                          Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1);
Std_ReturnType                          Rte_Read_CtrlLed_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType                          Rte_Read_CtrlLed_Cpm_TgtPxlSig(tsRte_TgtPxlSig0Arr* ppara1);
Std_ReturnType                          Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1);
Std_ReturnType                          Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1);
Std_ReturnType                          Rte_Write_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType                          Rte_Write_CpmHssTarget0_sSetting(tsRteHssTarget* ppara1);
Std_ReturnType                          Rte_Write_Cpm_SigPrepTx_PowerFactor(const tsRte_PowerFactor* ppara1);
Std_ReturnType                          Rte_Read_CtrlLed_TgtHssSig_sVal(tsRte_TgtLedSig0* ppara1);
Std_ReturnType                          Rte_Write_Cpm_CtrlSwi_HSS3Target(const tsRte_CpmHSS3Duty* ppara1);
NM_ErrorCodeType                        NM_GetMode(NM_ModeType * p_NMMode);
void                                    CPM_Gen(tunPercent_1_328 aunExtSwitchSetting0[8][16], tunPercent_1_328
                                        aunExtSwitchSetting1[8][16], tsLsTargetPercArr13 * asLsTargetSetting0, tsLsTargetPercArr13 *
                                        asLsTargetSetting1, tsVoltage * sActVoltage0, tsTemperature * sEcuTemp0, tsTemperatureArr14 *
                                        sIoTemp0, tsTemperatureArr8 * sLmmTemp0);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tLinearPoint                     UtilMath_LinearInterpolate_Param1[2];
extern sint32                           UtilMath_LinearInterpolate_Param2;
extern sint32                           UtilMath_LinearInterpolate_Param3;
extern tsRteCodingParameters            Rte_Read_CodM_AppM_Para_Param1;
extern tsRte_SysMon_LifePhases          Rte_Read_SysMon_LifePhases_Param1;
extern teRte_MountingSide               Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_SysMonLgtFctsReq           Rte_Read_SysMon_StdLgtFcts_Req_Param1;
extern tiu32Voltage_mV                  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
extern tsRte_NTCTemperature             Rte_Read_RSens_ThermzoneTemperatures_Param1;
extern tsRte_PcbTemperatureMsg          Rte_Read_RSens_PcbTemperature_Param1;
extern tsRte_TgtLedSig0Arr              Rte_Read_CtrlLed_TgtLedSig_sVal_Param1;
extern tsRte_TgtPxlSig0Arr              Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1;
extern tsRte_TgtPxlSig0Arr              Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_Param1;
extern tsRte_TgtLedSig0Arr*             Rte_Write_Cpm_TgtLedSig_sVal_Param1;
extern tsRteHssTarget*                  Rte_Write_CpmHssTarget0_sSetting_Param1;
extern uint32                           LPTMR0_GetTimeElapsed_Param1;
extern tsRtePowFactTemp                 Rte_Write_Cpm_PowFact_Temp_Param1;
extern tsRte_PowerFactor                Rte_Write_Cpm_SigPrepTx_PowerFactor_Param1;
extern tunPercent_1_328                 FanM_Gen_Param1[12];
extern tunPercent_1_328                 FanM_Gen_Param2[8][16];
extern boolean                          FanM_Gen_Param3[2];
extern tsTemperatureArr14               FanM_Gen_Param4;
extern tsTemperatureArr8                FanM_Gen_Param5;
extern tunPercent_1_328                 CPM_Gen_Param1[8][16];
extern tunPercent_1_328                 CPM_Gen_Param2[8][16];
extern tsLsTargetPercArr13              CPM_Gen_Param3;
extern tsLsTargetPercArr13              CPM_Gen_Param4;
extern tsVoltage                        CPM_Gen_Param5;
extern tsTemperature                    CPM_Gen_Param6;
extern tsTemperatureArr14               CPM_Gen_Param7;
extern tsTemperatureArr8                CPM_Gen_Param8;
extern tsRte_TgtLedSig0                 Rte_Read_CtrlLed_TgtHssSig_sVal_Param1;
extern tsRte_CpmHSS3Duty                Rte_Write_Cpm_CtrlSwi_HSS3Target_Param1;
extern NM_ModeType                      NM_GetMode_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint8                            UtilMath_LinearInterpolate_RetVal;
extern uint8                            Rte_Read_CodM_AppM_Para_RetVal;
extern uint8                            Rte_Read_SysMon_LifePhases_RetVal;
extern uint8                            Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern uint8                            Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
extern uint8                            Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
extern uint8                            Rte_Read_RSens_ThermzoneTemperatures_RetVal;
extern uint8                            Rte_Read_RSens_PcbTemperature_RetVal;
extern uint8                            Rte_Read_CtrlLed_TgtLedSig_sVal_RetVal;
extern uint8                            Rte_Read_CtrlLed_Cpm_TgtPxlSig_RetVal;
extern uint8                            Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;
extern uint8                            Rte_Write_Cpm_TgtLedSig_sVal_RetVal;
extern uint8                            Rte_Write_CpmHssTarget0_sSetting_RetVal;
extern uint8                            LPTMR0_GetTimeElapsed_RetVal;
extern uint8                            Rte_Write_Cpm_PowFact_Temp_RetVal;
extern uint8                            Rte_Write_Cpm_SigPrepTx_PowerFactor_RetVal;
extern uint8                            CPM_Gen_RetVal;
extern uint8                            FanM_Gen_RetVal;
extern Std_ReturnType                   Rte_Read_CtrlLed_TgtHssSig_sVal_RetVal;
extern Std_ReturnType                   Rte_Write_Cpm_CtrlSwi_HSS3Target_RetVal;
extern NM_ErrorCodeType                 NM_GetMode_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8                            UtilMath_LinearInterpolate_HitCount;
extern uint8                            Rte_Read_CodM_AppM_Para_HitCount;
extern uint8                            Rte_Read_SysMon_LifePhases_HitCount;
extern uint8                            Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8                            Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
extern uint8                            Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint8                            Rte_Read_RSens_ThermzoneTemperatures_HitCount;
extern uint8                            Rte_Read_RSens_PcbTemperature_HitCount;
extern uint8                            Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount;
extern uint8                            Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount;
extern uint8                            Rte_Write_Cpm_CtrlPxl_DeratedMtxPixels_HitCount;
extern uint8                            Rte_Write_Cpm_TgtLedSig_sVal_HitCount;
extern uint8                            Rte_Write_CpmHssTarget0_sSetting_HitCount;
extern uint8                            LPTMR0_GetTimeElapsed_HitCount;
extern uint8                            Rte_Write_Cpm_PowFact_Temp_HitCount;
extern uint8                            Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount;
extern uint8                            CPM_Gen_HitCount;
extern uint8                            FanM_Gen_HitCount;
extern uint8                            Rte_Read_CtrlLed_TgtHssSig_sVal_HitCount;
extern uint8                            Rte_Write_Cpm_CtrlSwi_HSS3Target_HitCount;
extern uint8                            NM_GetMode_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

// EOF
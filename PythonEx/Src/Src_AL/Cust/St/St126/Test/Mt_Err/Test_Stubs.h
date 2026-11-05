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
#include <RteCommonTypes.h>
#include <Nvm.h>

//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType                         Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType                         Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType                         Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1);
Std_ReturnType                         Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType                         Rte_Read_SigPrep_OdometerTotal(tsRte_OdometerTotal* ppara1);
Std_ReturnType                         Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1);
Std_ReturnType                         Rte_Read_CtrlStp_ActStatStp_sVal_0(tsRte_ActStatStp0* ppara1);
Std_ReturnType                         Rte_Read_FctR_LgtFctState(tsRte_LgtFctState* ppara1);
Std_ReturnType                         Rte_Read_FctR_TiFailureStatus(boolean* ppara1);
Std_ReturnType                         Rte_Read_FctR_LgtFctStatus(tsRte_LgtFctStatus* ppara1);
Std_ReturnType                         Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);
Std_ReturnType                         NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
void                                   Dem_ClearAlec(boolean boAllAlecs, uint16 unDemIndex);
boolean                                Dem_boEventPassed(uint16 unEventIdx);
void*                                  EcuM_Get_Mpu_Test_Hook_Address(void);
uint32                                 LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1);
Std_ReturnType                         Rte_Read_RSens_NTC_BIN_Input_Errors(tsRteNTCBinInData* ppara1);
Std_ReturnType                         Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern MemIf_JobResultType                    Fee_JobResult;
extern tieFeeState                            Fee_State;
extern tsRte_SigPrep_VehiclePitchAngle        sVehPitchAngle;
extern tDem_aEventStatus_type                 Dem_astEventStatus[DEM_CONFIG_ENTRY_MAX];
extern tsRte_SysMon_VehNetState               Rte_Read_SysMon_VehNetState_Param1;
extern teRte_MountingSide                     Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_SigPrep_VehiclePitchAngle        Rte_Read_SigPrep_VehiclePitchAngle_Param1;
extern tiu32Voltage_mV                        Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
extern tsRte_SysMon_VehicleSpeed              Rte_Read_SysMon_VehicleSpeed_Param1;
extern tsRte_OdometerTotal                    Rte_Read_SigPrep_OdometerTotal_Param1;
extern tsRte_SensorRaw                        Rte_Read_IoHwAb_GetSens_Raw_Param1;
extern boolean                                Dem_ClearAlec_Param1;
extern uint16                                 Dem_ClearAlec_Param2;
extern tsRte_ActStatStp0                      Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
extern tsRte_LgtFctState                      Rte_Read_FctR_LgtFctState_Param1;
extern boolean                                Rte_Read_FctR_TiFailureStatus_Param1;
extern tsRte_LgtFctStatus                     Rte_Read_FctR_LgtFctStatus_Param1;
extern uint16                                 Dem_boEventPassed_Param1;
extern uint32                                 LPTMR0_GetTimeElapsed_Param1;
extern NvM_BlockIdType                        NvM_WriteBlock_Param1;
extern void*                                  NvM_WriteBlock_Param2;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_00_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_01_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_02_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_03_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_04_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_05_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_06_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_07_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_08_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_09_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_10_Param1;
extern tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_11_Param1;
extern tsRte_NTCTemperature                   Rte_Read_RSens_ThermzoneTemperatures_Param1;
extern tsRteCodingParameters                  Rte_Read_CodM_Err_Para_Param1;
extern tsRte_CtrlLed_ChStatesDiag             Rte_Read_CtrlLed_ChState_Param1;
extern tsRteNTCBinInData                      Rte_Read_RSens_NTC_BIN_Input_Errors_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType                         Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType                         Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
extern Std_ReturnType                         Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType                         Rte_Read_SigPrep_OdometerTotal_RetVal;
extern Std_ReturnType                         Rte_Read_IoHwAb_GetSens_Raw_RetVal;
extern Std_ReturnType                         Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
extern Std_ReturnType                         Rte_Read_FctR_LgtFctState_RetVal;
extern Std_ReturnType                         Rte_Read_FctR_TiFailureStatus_RetVal;
extern Std_ReturnType                         Rte_Read_FctR_LgtFctStatus_RetVal;
extern Std_ReturnType                         NvM_WriteBlock_RetVal;
extern uint32                                 LPTMR0_GetTimeElapsed_RetVal;
extern uint8                                  Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern boolean                                Dem_boEventPassed_RetVal;
extern uint8                                  Rte_Read_RSens_ThermzoneTemperatures_RetVal;
extern uint8                                  Rte_Read_CodM_Err_Para_RetVal;
extern uint8                                  Rte_Read_CtrlLed_ChState_RetVal;
extern uint8                                  Rte_Read_RSens_NTC_BIN_Input_Errors_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8                                  EcuM_Get_Mpu_Test_Hook_Address_HitCount;
extern uint8                                  Rte_Read_SysMon_VehNetState_HitCount;
extern uint8                                  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8                                  Rte_Read_SigPrep_VehiclePitchAngle_HitCount;
extern uint8                                  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
extern uint8                                  Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8                                  Rte_Read_SigPrep_OdometerTotal_HitCount;
extern uint8                                  Rte_Read_IoHwAb_GetSens_Raw_HitCount;
extern uint8                                  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount;
extern uint8                                  Rte_Read_FctR_LgtFctState_HitCount;
extern uint8                                  Rte_Read_FctR_TiFailureStatus_HitCount;
extern uint8                                  Rte_Read_FctR_LgtFctStatus_HitCount;
extern uint8                                  Dem_ClearAlec_HitCount;
extern uint8                                  Dem_boEventPassed_HitCount;
extern uint8                                  LPTMR0_GetTimeElapsed_HitCount;
extern uint8                                  NvM_WriteBlock_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_00_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_01_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_02_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_03_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_04_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_05_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_06_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_07_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_08_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_09_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_10_HitCount;
extern uint8                                  Rte_Read_RSens_BinningClass_sVal_11_HitCount;
extern uint8                                  Rte_Read_RSens_ThermzoneTemperatures_HitCount;
extern uint8                                  Rte_Read_CodM_Err_Para_HitCount;
extern uint8                                  Rte_Read_CtrlLed_ChState_HitCount;
extern uint8                                  Rte_Read_RSens_NTC_BIN_Input_Errors_HitCount;


#endif // TEST_STUBS_2023_08_25_H_

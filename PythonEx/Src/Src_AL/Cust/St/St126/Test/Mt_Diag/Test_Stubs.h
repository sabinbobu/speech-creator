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
#include <CddEft.h>
#include "CddLed.h""
#include <Nvm.h>
#include <Rte/RteCommonTypes.h>
#include <SysMon_Types.h>
#include <Cfg/CfgId.h>
#include <_DIAG_types.h>

//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType                 Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType                 Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType                 Rte_Read_OS_CPULoadPeak(uint8* ppara1);
Std_ReturnType                 Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal(tauRte_CtrlPxl_Mtx_bErr* ppara1);
Std_ReturnType                 Rte_Read_CtrlSwi_StatusErr(tisHssStatusError* ppara1);
Std_ReturnType                 Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite(teRte_SateliteStatus* ppara1);
Std_ReturnType                 Rte_Read_CddLed_Status(tCddLedStatus* ppara1);
Std_ReturnType                 Rte_Read_FctR_LgtDistStatus(uint32* ppara1);
Std_ReturnType                 Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal(tasRte_MlcAdcResult* ppara1);
Std_ReturnType                 Rte_Read_Cpm_PowFact_Temp(tsRtePowFactTemp* ppara1);
Std_ReturnType                 Rte_Read_SysMon_LedState(tsRte_SysMon_LedStates* ppara1);
Std_ReturnType                 Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType                 Rte_Read_Diag_RoutineControl(tsRte_AfsRoutineControl* ppara1);
Std_ReturnType                 Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType                 Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1);
Std_ReturnType                 Rte_Read_CddSwi_ScrollingOn_Stat(boolean* ppara1);
Std_ReturnType                 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);
Std_ReturnType                 Rte_Read_OS_CPULoadAvg(uint8* ppara1);
Std_ReturnType                 Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1);
Std_ReturnType                 Rte_Read_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1);
Std_ReturnType                 Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType                 Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType                 Rte_Read_CodM_AppM_Para(tsRteCodingParameters* ppara1);
Std_ReturnType                 Rte_Read_IoHwAb_GetVoltage_NTCs(tsRte_Voltage_mV* ppara1);
Std_ReturnType                 Rte_Read_StatM_StackUsage(uint8* ppara1);
Std_ReturnType                 Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1);
Std_ReturnType                 Rte_Read_CtrlSwi_Hss3StatusErr(tsRte_Hss3Status* ppara1);
Std_ReturnType                 Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal(tasRte_CtrlPxl_BinEEprom* ppara1);
Std_ReturnType                 Rte_Read_Stp_RoutineControl(tsRte_StepperRoutineControl* ppara1);
Std_ReturnType                 Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType                 Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1);
Std_ReturnType                 Rte_Read_Pitch_Angle(tPitch0* ppara1);
Std_ReturnType                 Rte_Read_ppsAvacOut(tsPositionOut* ppara1);
Std_ReturnType                 Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1);
Std_ReturnType                 Rte_Read_RSens_BinningDataDiag(tsRte_D409Binning* ppara1);
Std_ReturnType                 Rte_Write_Diag_ResetStatistics(boolean para1);
Std_ReturnType                 Rte_Write_Diag_RoutineControl(const tsRte_AfsRoutineControl* ppara1);
Std_ReturnType                 Rte_Write_Dcm_RoutineControl(const tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType                 Rte_Write_Diag_TiScrollingTakeOver(const boolean* ppara1);
Std_ReturnType                 Rte_Write_CddSwi_ScrollingOn_Stat(const boolean* ppara1);
Std_ReturnType                 Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(const teRte_SateliteStatus* ppara1);
Std_ReturnType                 Rte_Write_Stp_RoutineControl(const tsRte_StepperRoutineControl* ppara1);
Std_ReturnType                 Rte_Write_Diag_LdActivationRoutineControl(const tsRte_Ld_ActivationRoutineControl* ppara1);
Std_ReturnType                 Rte_Write_StatM_StackUsage(uint8 para1);
Std_ReturnType                 Rte_Write_OS_CPULoadPeak(uint8 para1);
Std_ReturnType                 Rte_Write_Diag_DD01_Activation(const boolean* ppara1);
Std_ReturnType                 Rte_Write_Diag_DD01_PixelActivation(const tsRte_DIDPixelActivation* ppara1);
Std_ReturnType                 Rte_Write_Diag_DiagResetRequest(const boolean* ppara1);
Std_ReturnType                 Rte_Write_ElecInt_ReleaseRUN(const uint8* ppara1);
Std_ReturnType                 Rte_Write_Diag_RequestPOST_RUN(const uint8* ppara1);
Std_ReturnType                 NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
LEIM_TE_CurrentEIMode          EAPI_GetCurrentEIMode(void);
void                           DAPI_ClearDTCInfo(void);
DIAG_status                    DIAG_Send_Diag_Response(const UINT8* p_ui8_Data, Diag_Length_Type Length);
DIAG_status                    DIAG_Send_Diag_Error(DIAG_status Error);
UINT8                          DIAG_GetActiveSession(void);
tiu16Voltage_mV                IoHwAbUser_GetVoltage_NTCs(uint8 ucIdx);
uint16                         CddSbc_GetPWM(uint8 ucMode);
void                           Dem_Diag_LockDTC(boolean boEnableDTC);
boolean                        ErrCust_ClearMemory(uint8* pucDtcCode);
uint32                         ErrCust_ulGetDtcCode(uint8 ucDtcIndex);
uint8                          ErrCust_ucGetErrorCount(uint8 ucDTCStatusMask);
void                           ErrCust_ResetDtcIndex(void);
uint8                          ErrCust_ucGetStatusOfDTC(uint8 ucDtcIndex);
void                           ErrCust_SetAvailableDtc(uint8* pucBuf, uint8 ucDTCStatusMask);
uint32                         ErrCust_ConvertValueSint2Int(sint32 slInValue, uint8 ucbitLength);
sint32                         ErrCust_ConvertValueInt2Sint(uint32 ulInValue, uint8 ucbitLength);
void                           ErrCust_RteAccess_Read_FctR_LgtFctErrState(tsErrCust_LgtFctState *psErrCust_RteAccess_LgtFctState);
void                           ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(teErrCust_Types_MountingSide *peEcuSide);
void                           ErrCust_RteAccess_Read_CtrlStp_ActStatStp(tsErrCust_TypesActStatStp *psActStatStp);
void                           ErrCust_RteAccess_Read_FctR_LgtFctStatus(tsErrCust_LgtFctStatus *psErrCust_RteAccess_LgtFctStatus);
void                           ErrCust_RteAccess_Read_FctR_TI_FctErrState(boolean *boErrCust_RteAccess_Lgt_TI_State);
void                           ErrCust_CaptureAftermarketAttitudeEcuData(tsErrCust_AftermarketAttitudeEcuData* psOutputData);
void                           ErrCust_CaptureAftermarketLvlEcuData(tsErrCust_AftermarketLvlEcuData* psOutputData);
void                           ErrCust_CaptureAftermarketContextEcuData(tsErrCust_AftermarketContextEcuData* psOutputData);
void                           ErrCust_CaptureAftermarketRbinEepromLmmEcuData(tsErrCust_AftermarketRbinEepromLmmData* psOutputData);
void                           ErrCust_CaptureAftermarketRbinNtcFailureEcuData(tsErrCust_AftermarketRbinNtcFailureData* psOutputData);
void                           ErrCust_CaptureAftermarketLedOutputFailEcuData(tsErrCust_AftermarketLedChnlOutData* psOutputData);
boolean                        SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam(void);
SysMon_EnumLowBeamState        SysMonRx_ASIL_GetLowBeamState(void);
SysMon_EnumSpeedState          SysMonRx_ASIL_GetSpeedState(void);
SysMon_EnumTurnIndicatorState  SysMonRx_ASIL_GetTurnIndicatorState(void);
boolean                        SysMonCheck_GetTurnIndicatorCommandValue(void);
void                           roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(uint8 ucChannelNo, uint8 ucSwitchOutput);
void                           roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(uint8 ucChannelNo);
void                           Mcu_PerformReset(void);
void                           DiagControl_ProgrammingSesion_Request(void);
boolean                        CddEft_DataValid(void);
Std_ReturnType                 Rte_Read_CtrlLed_ChState(tsRte_CtrlLed_ChStatesDiag* ppara1);
void                           Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg *ppara1);
void                           Deh_ClearAndInitDehLogTab(void);
Std_ReturnType                 Rte_Read_Diag_TiScrollingTakeOver(boolean* ppara1);
uint8                          CddMlc_GetEEPROMAddressId(void);
Std_ReturnType                 Rte_Write_Diag_Scrolling_TgtValue(const teRte_ScrollingTgt* ppara1);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
tsRte_SysMon_VehicleSpeed               Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SysMon_VehNetState                Rte_Read_SysMon_VehNetState_Param1;
uint8                                   Rte_Read_OS_CPULoadPeak_Param1;
tauRte_CtrlPxl_Mtx_bErr                 Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1;
tisHssStatusError                       Rte_Read_CtrlSwi_StatusErr_Param1;
teRte_SateliteStatus                    Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1;
tCddLedStatus                           Rte_Read_CddLed_Status_Param1;
uint32                                  Rte_Read_FctR_LgtDistStatus_Param1;
tasRte_MlcAdcResult                     Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_Param1;
tsRtePowFactTemp                        Rte_Read_Cpm_PowFact_Temp_Param1;
tsRte_SysMon_LedStates                  Rte_Read_SysMon_LedState_Param1;
teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_AfsRoutineControl                 Rte_Read_Diag_RoutineControl_Param1;
teRte_ReqLightState                     Rte_Read_SysMon_LowBeamCmd_Req_Param1;
tsRte_CddStpActual                      Rte_Read_ppCddStpActual0_sStpActualValues_Param1;
boolean                                 Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
tiu32Voltage_mV                         Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
uint8                                   Rte_Read_OS_CPULoadAvg_Param1;
tsRte_TgtPxlSig0Arr                     Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1;
tsRte_TgtLedSig0Arr                     Rte_Read_Cpm_TgtLedSig_sVal_Param1;
tsRte_SigPrep_VehicleConfigSig          Rte_Read_SigPrep_VehicleConfigSig_Param1;
tsRte_SysMon_LifePhases                 Rte_Read_SysMon_LifePhases_Param1;
tsRteCodingParameters                   Rte_Read_CodM_AppM_Para_Param1;
tsRte_Voltage_mV                        Rte_Read_IoHwAb_GetVoltage_NTCs_Param1;
uint8                                   Rte_Read_StatM_StackUsage_Param1;
tsRte_SensorRaw                         Rte_Read_IoHwAb_GetSens_Raw_Param1;
tsRte_Hss3Status                        Rte_Read_CtrlSwi_Hss3StatusErr_Param1;
tasRte_CtrlPxl_BinEEprom                Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1;
tsRte_StepperRoutineControl             Rte_Read_Stp_RoutineControl_Param1;
tsRte_DcMotorRoutineControl             Rte_Read_Dcm_RoutineControl_Param1;
tsRte_SigPrep_VehiclePitchAngle         Rte_Read_SigPrep_VehiclePitchAngle_Param1;
tPitch0                                 Rte_Read_Pitch_Angle_Param1;
tsPositionOut                           Rte_Read_ppsAvacOut_Param1;
tsRte_NTCTemperature                    Rte_Read_RSens_ThermzoneTemperatures_Param1;
tsRte_D409Binning                       Rte_Read_RSens_BinningDataDiag_Param1;
boolean                                 Rte_Write_Diag_ResetStatistics_Param1;
tsRte_AfsRoutineControl                 Rte_Write_Diag_RoutineControl_Param1;
tsRte_DcMotorRoutineControl             Rte_Write_Dcm_RoutineControl_Param1;
boolean                                 Rte_Write_Diag_TiScrollingTakeOver_Param1;
boolean                                 Rte_Write_CddSwi_ScrollingOn_Stat_Param1;
teRte_SateliteStatus                    Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1;
tsRte_StepperRoutineControl             Rte_Write_Stp_RoutineControl_Param1;
tsRte_Ld_ActivationRoutineControl       Rte_Write_Diag_LdActivationRoutineControl_Param1;
uint8                                   Rte_Write_StatM_StackUsage_Param1;
uint8                                   Rte_Write_OS_CPULoadPeak_Param1;
boolean                                 Rte_Write_Diag_DD01_Activation_Param1;
tsRte_DIDPixelActivation                Rte_Write_Diag_DD01_PixelActivation_Param1;
boolean                                 Rte_Write_Diag_DiagResetRequest_Param1;
uint8                                   Rte_Write_ElecInt_ReleaseRUN_Param1;
uint8                                   Rte_Write_Diag_RequestPOST_RUN_Param1;
NvM_BlockIdType                         NvM_WriteBlock_Param1;
void*                                   NvM_WriteBlock_Param2;
UINT8                                   DIAG_Send_Diag_Response_Param1[600];
Diag_Length_Type                        DIAG_Send_Diag_Response_Param2;
DIAG_status                             DIAG_Send_Diag_Error_Param1;
uint8                                   IoHwAbUser_GetVoltage_NTCs_Param1;
uint8                                   CddSbc_GetPWM_Param1;
boolean                                 Dem_Diag_LockDTC_Param1;
uint8                                   ErrCust_ClearMemory_Param1;
uint8                                   ErrCust_ulGetDtcCode_Param1;
uint8                                   ErrCust_ucGetErrorCount_Param1;
uint8                                   ErrCust_ucGetStatusOfDTC_Param1;
uint8*                                  ErrCust_SetAvailableDtc_Param1;
uint8                                   ErrCust_SetAvailableDtc_Param2;
sint32                                  ErrCust_ConvertValueSint2Int_Param1;
uint8                                   ErrCust_ConvertValueSint2Int_Param2;
uint32                                  ErrCust_ConvertValueInt2Sint_Param1;
uint8                                   ErrCust_ConvertValueInt2Sint_Param2;
tsErrCust_LgtFctState                   ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1;
teErrCust_Types_MountingSide            ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1;
tsErrCust_TypesActStatStp               ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1;
tsErrCust_LgtFctStatus                  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1;
boolean                                 ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1;
tsErrCust_AftermarketAttitudeEcuData    ErrCust_CaptureAftermarketAttitudeEcuData_Param1;
tsErrCust_AftermarketLvlEcuData         ErrCust_CaptureAftermarketLvlEcuData_Param1;
tsErrCust_AftermarketContextEcuData     ErrCust_CaptureAftermarketContextEcuData_Param1;
tsErrCust_AftermarketRbinEepromLmmData  ErrCust_CaptureAftermarketRbinEepromLmmEcuData_Param1;
tsErrCust_AftermarketRbinNtcFailureData ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1;
tsErrCust_AftermarketLedChnlOutData     ErrCust_CaptureAftermarketLedOutputFailEcuData_Param1;
uint8                                   roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param1;
uint8                                   roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param2;
uint8                                   roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_Param1;
tsRte_CtrlLed_ChStatesDiag              Rte_Read_CtrlLed_ChState_Param1;
tsRte_PcbTemperatureMsg                 Rte_Read_RSens_PcbTemperature_Param1;
boolean                                 Rte_Read_Diag_TiScrollingTakeOver_Param1;
teRte_ScrollingTgt                      Rte_Write_Diag_Scrolling_TgtValue_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType                 Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType                 Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType                 Rte_Read_OS_CPULoadPeak_RetVal;
Std_ReturnType                 Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
Std_ReturnType                 Rte_Read_CtrlSwi_StatusErr_RetVal;
Std_ReturnType                 Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
Std_ReturnType                 Rte_Read_CddLed_Status_RetVal;
Std_ReturnType                 Rte_Read_FctR_LgtDistStatus_RetVal;
Std_ReturnType                 Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
Std_ReturnType                 Rte_Read_Cpm_PowFact_Temp_RetVal;
Std_ReturnType                 Rte_Read_SysMon_LedState_RetVal;
Std_ReturnType                 Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType                 Rte_Read_Diag_RoutineControl_RetVal;
Std_ReturnType                 Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
Std_ReturnType                 Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;
Std_ReturnType                 Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
Std_ReturnType                 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
Std_ReturnType                 Rte_Read_OS_CPULoadAvg_RetVal;
Std_ReturnType                 Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;
Std_ReturnType                 Rte_Read_Cpm_TgtLedSig_sVal_RetVal;
Std_ReturnType                 Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType                 Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType                 Rte_Read_CodM_AppM_Para_RetVal;
Std_ReturnType                 Rte_Read_IoHwAb_GetVoltage_NTCs_RetVal;
Std_ReturnType                 Rte_Read_StatM_StackUsage_RetVal;
Std_ReturnType                 Rte_Read_IoHwAb_GetSens_Raw_RetVal;
Std_ReturnType                 Rte_Read_CtrlSwi_Hss3StatusErr_RetVal;
Std_ReturnType                 Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_RetVal;
Std_ReturnType                 Rte_Read_Stp_RoutineControl_RetVal;
Std_ReturnType                 Rte_Read_Dcm_RoutineControl_RetVal;
Std_ReturnType                 Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
Std_ReturnType                 Rte_Read_Pitch_Angle_RetVal;
Std_ReturnType                 Rte_Read_ppsAvacOut_RetVal;
Std_ReturnType                 Rte_Read_RSens_ThermzoneTemperatures_RetVal;
Std_ReturnType                 Rte_Read_RSens_BinningDataDiag_RetVal;
Std_ReturnType                 Rte_Write_Diag_ResetStatistics_RetVal;
Std_ReturnType                 Rte_Write_Diag_RoutineControl_RetVal;
Std_ReturnType                 Rte_Write_Dcm_RoutineControl_RetVal;
Std_ReturnType                 Rte_Write_Diag_TiScrollingTakeOver_RetVal;
Std_ReturnType                 Rte_Write_CddSwi_ScrollingOn_Stat_RetVal;
Std_ReturnType                 Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
Std_ReturnType                 Rte_Write_Stp_RoutineControl_RetVal;
Std_ReturnType                 Rte_Write_Diag_LdActivationRoutineControl_RetVal;
Std_ReturnType                 Rte_Write_StatM_StackUsage_RetVal;
Std_ReturnType                 Rte_Write_OS_CPULoadPeak_RetVal;
Std_ReturnType                 Rte_Write_Diag_DD01_Activation_RetVal;
Std_ReturnType                 Rte_Write_Diag_DD01_PixelActivation_RetVal;
Std_ReturnType                 Rte_Write_Diag_DiagResetRequest_RetVal;
Std_ReturnType                 Rte_Write_ElecInt_ReleaseRUN_RetVal;
Std_ReturnType                 Rte_Write_Diag_RequestPOST_RUN_RetVal;
Std_ReturnType                 NvM_WriteBlock_RetVal;
LEIM_TE_CurrentEIMode          EAPI_GetCurrentEIMode_RetVal;
DIAG_status                    DIAG_Send_Diag_Response_RetVal;
DIAG_status                    DIAG_Send_Diag_Error_RetVal;
UINT8                          DIAG_GetActiveSession_RetVal;
tiu16Voltage_mV                IoHwAbUser_GetVoltage_NTCs_RetVal;
uint16                         CddSbc_GetPWM_RetVal;
uint32                         ErrCust_ConvertValueSint2Int_RetVal;
sint32                         ErrCust_ConvertValueInt2Sint_RetVal;
boolean                        ErrCust_ClearMemory_RetVal;
uint32                         ErrCust_ulGetDtcCode_RetVal;
uint8                          ErrCust_ucGetErrorCount_RetVal;
uint8                          ErrCust_ucGetStatusOfDTC_RetVal;
boolean                        SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal;
SysMon_EnumLowBeamState        SysMonRx_ASIL_GetLowBeamState_RetVal;
SysMon_EnumSpeedState          SysMonRx_ASIL_GetSpeedState_RetVal;
SysMon_EnumTurnIndicatorState  SysMonRx_ASIL_GetTurnIndicatorState_RetVal;
boolean                        SysMonCheck_GetTurnIndicatorCommandValue_RetVal;
boolean                        CddEft_DataValid_RetVal;
Std_ReturnType                 Rte_Read_CtrlLed_ChState_RetVal;
Std_ReturnType                 Rte_Read_RSens_PcbTemperature_RetVal;
Std_ReturnType                 Rte_Read_Diag_TiScrollingTakeOver_RetVal;
uint8                          CddMlc_GetEEPROMAddressId_RetVal;
Std_ReturnType                 Rte_Write_Diag_Scrolling_TgtValue_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8  Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8  Rte_Read_SysMon_VehNetState_HitCount;
uint8  Rte_Read_OS_CPULoadPeak_HitCount;
uint8  Rte_Read_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount;
uint8  Rte_Read_CtrlSwi_StatusErr_HitCount;
uint8  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount;
uint8  Rte_Read_CddLed_Status_HitCount;
uint8  Rte_Read_FctR_LgtDistStatus_HitCount;
uint8  Rte_Read_CtrlPxl_CddMlc_AdcResult_aVal_HitCount;
uint8  Rte_Read_Cpm_PowFact_Temp_HitCount;
uint8  Rte_Read_SysMon_LedState_HitCount;
uint8  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8  Rte_Read_Diag_RoutineControl_HitCount;
uint8  Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
uint8  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount;
uint8  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;
uint8  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint8  Rte_Read_OS_CPULoadAvg_HitCount;
uint8  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount;
uint8  Rte_Read_Cpm_TgtLedSig_sVal_HitCount;
uint8  Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint8  Rte_Read_SysMon_LifePhases_HitCount;
uint8  Rte_Read_CodM_AppM_Para_HitCount;
uint8  Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount;
uint8  Rte_Read_StatM_StackUsage_HitCount;
uint8  Rte_Read_IoHwAb_GetSens_Raw_HitCount;
uint8  Rte_Read_CtrlSwi_Hss3StatusErr_HitCount;
uint8  Rte_Read_CtrlPxl_CtrlLed_EepromBinningClass_aVal_HitCount;
uint8  Rte_Read_Stp_RoutineControl_HitCount;
uint8  Rte_Read_Dcm_RoutineControl_HitCount;
uint8  Rte_Read_SigPrep_VehiclePitchAngle_HitCount;
uint8  Rte_Read_Pitch_Angle_HitCount;
uint8  Rte_Read_ppsAvacOut_HitCount;
uint8  Rte_Read_RSens_ThermzoneTemperatures_HitCount;
uint8  Rte_Read_RSens_BinningDataDiag_HitCount;
uint8  Rte_Write_Diag_ResetStatistics_HitCount;
uint8  Rte_Write_Diag_RoutineControl_HitCount;
uint8  Rte_Write_Dcm_RoutineControl_HitCount;
uint8  Rte_Write_Diag_TiScrollingTakeOver_HitCount;
uint8  Rte_Write_CddSwi_ScrollingOn_Stat_HitCount;
uint8  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_HitCount;
uint8  Rte_Write_Stp_RoutineControl_HitCount;
uint8  Rte_Write_Diag_LdActivationRoutineControl_HitCount;
uint8  Rte_Write_StatM_StackUsage_HitCount;
uint8  Rte_Write_OS_CPULoadPeak_HitCount;
uint8  Rte_Write_Diag_DD01_Activation_HitCount;
uint8  Rte_Write_Diag_DD01_PixelActivation_HitCount;
uint8  Rte_Write_Stp_RoutineControl_HitCount;
uint8  Rte_Write_Diag_DiagResetRequest_HitCount;
uint8  Rte_Write_ElecInt_ReleaseRUN_HitCount;
uint8  Rte_Write_Diag_RequestPOST_RUN_HitCount;
uint8  NvM_WriteBlock_HitCount;
uint8  EAPI_GetCurrentEIMode_HitCount;
uint8  DAPI_ClearDTCInfo_HitCount;
uint8  DIAG_Send_Diag_Response_HitCount;
uint8  DIAG_Send_Diag_Error_HitCount;
uint8  DIAG_GetActiveSession_HitCount;
uint8  IoHwAbUser_GetVoltage_NTCs_HitCount;
uint8  CddSbc_GetPWM_HitCount;
uint8  Dem_Diag_LockDTC_HitCount;
uint8  ErrCust_ConvertValueSint2Int_HitCount;
uint8  ErrCust_ConvertValueInt2Sint_HitCount;
uint8  ErrCust_RteAccess_Read_FctR_LgtFctErrState_HitCount;
uint8  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_HitCount;
uint8  ErrCust_RteAccess_Read_FctR_LgtFctStatus_HitCount;
uint8  ErrCust_RteAccess_Read_FctR_TI_FctErrState_HitCount;
uint8  ErrCust_CaptureAftermarketAttitudeEcuData_HitCount;
uint8  ErrCust_CaptureAftermarketLvlEcuData_HitCount;
uint8  ErrCust_CaptureAftermarketContextEcuData_HitCount;
uint8  ErrCust_CaptureAftermarketRbinEepromLmmEcuData_HitCount;
uint8  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_HitCount;
uint8  ErrCust_CaptureAftermarketLedOutputFailEcuData_HitCount;
uint8  ErrCust_ClearMemory_HitCount;
uint8  ErrCust_ulGetDtcCode_HitCount;
uint8  ErrCust_ucGetErrorCount_HitCount;
uint8  ErrCust_ResetDtcIndex_HitCount;
uint8  ErrCust_ucGetStatusOfDTC_HitCount;
uint8  ErrCust_SetAvailableDtc_HitCount;
uint8  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount;
uint8  SysMonRx_ASIL_GetLowBeamState_HitCount;
uint8  SysMonRx_ASIL_GetSpeedState_HitCount;
uint8  SysMonRx_ASIL_GetTurnIndicatorState_HitCount;
uint8  SysMonCheck_GetTurnIndicatorCommandValue_HitCount;
uint8  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_HitCount;
uint8  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_HitCount;
uint8  Mcu_PerformReset_HitCount;
uint8  DiagControl_ProgrammingSesion_Request_HitCount;
uint8  CddEft_DataValid_HitCount;
uint8  Rte_Read_CtrlLed_ChState_HitCount;
uint8  Rte_Read_RSens_PcbTemperature_HitCount;
uint8  Deh_ClearAndInitDehLogTab_HitCount;
uint8  Rte_Read_Diag_TiScrollingTakeOver_HitCount;
uint8  CddMlc_GetEEPROMAddressId_HitCount;
uint8  Rte_Write_Diag_Scrolling_TgtValue_HitCount;


#endif // TEST_STUBS_2023_08_25_H_

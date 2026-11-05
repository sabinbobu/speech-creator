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
#include <UtilDebounce.h>
#include <FctR_Types.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Defines
//=============================================================================
#define RTE_E_OK                    (uint8)0x00u

//=============================================================================
// Global variable stubs
//=============================================================================

extern tNvmPara_CodingArea  Coding_Dummy;
extern tParaFct0_Cmd        Coding_State;

//=============================================================================
// Stub function declarations
//=============================================================================

/*Read*/
Std_ReturnType    Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType    Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1);
Std_ReturnType    Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1);
Std_ReturnType    Rte_Read_SigPrep_StdLgtClSbl_Req(tsRte_SigPrepLgtClSblReq* ppara1);
Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType    Rte_Read_CodM_FctR_Para(tsRteCodingParameters* ppara1);
Std_ReturnType    Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1);
Std_ReturnType    Rte_Read_CtrlLed_ActLed_sState(tsRte_LedErrStateArr* ppara1);
Std_ReturnType    Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType    Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType    Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType    Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1);
Std_ReturnType    Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1);
Std_ReturnType    Rte_Read_DEM_OV_NotifyStatus(boolean* ppara1);
Std_ReturnType    Rte_Read_DEM_UV_NotifyStatus(boolean* ppara1);
Std_ReturnType    Rte_Read_AdbMxb_Gfhb_Diag(boolean* ppara1);
Std_ReturnType    Rte_Read_Diag_LdActivationRoutineControl(tsRte_Ld_ActivationRoutineControl* ppara1);
Std_ReturnType    Rte_Read_Adb_StatusOut(tAdbStatus* ppara1);
Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_0(tAdbOut* ppara1);

/*Write*/
Std_ReturnType    Rte_Write_FctR_TgtLed_sVal(const tsRte_TgtLedVal0Arr* ppara1);
Std_ReturnType    Rte_Write_FctR_GfHbCmd(const teRte_GfHb_Cmd* ppara1);
Std_ReturnType    Rte_Write_FctR_AfsDblCmd(const tsRte_AfsDblCmd* ppara1);
Std_ReturnType    Rte_Write_FctR_AfsModeSig_sVal(const teRte_AfsModeSig_sVal* ppara1);
Std_ReturnType    Rte_Write_FctR_LgtFctState(const tsRte_LgtFctState* ppara1);
Std_ReturnType    Rte_Write_FctR_LgtFctStatus(const tsRte_LgtFctStatus* ppara1);
Std_ReturnType    Rte_Write_FctR_TiWarningMode(const teRte_WarningMode* ppara1);
Std_ReturnType    Rte_Write_FctR_TiFailureStatus(const boolean* ppara1);
Std_ReturnType    Rte_Write_FctR_LgtDistStatus(tuFctR_LgtFct ppara1);
Std_ReturnType    Rte_Write_FctR_PXALightDistr_Fbit(const boolean* ppara1);
Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_4(tAdbOut* ppara1);

void              UtilDebounceInit(tUtilDebounceControl* const pCtrl, tieDigState eStateInit, TIMER tOnDelay, TIMER tOffDelay);
void              UtilDebounce(tUtilDebounceControl* const pCtrl, boolean boVal);
uint32            LPTMR0_GetTimeElapsed(const uint32 ulStartValue);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

/*Read*/
extern tsRte_SysMonLgtFctsReq              Rte_Read_SysMon_StdLgtFcts_Req_Param1;
extern tsRte_SysMonAfsSignals              Rte_Read_SysMon_Afs_Signals_Param1;
extern tsRte_SysMonLgtTiReq                Rte_Read_SysMon_StdLgtTi_Req_Param1;
extern tsRte_SigPrepLgtClSblReq            Rte_Read_SigPrep_StdLgtClSbl_Req_Param1;
extern teRte_MountingSide                  Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern teRte_SysVolt_Results               Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
extern tsRteCodingParameters               Rte_Read_CodM_FctR_Para_Param1;
extern tsRte_LedErrStateArr                Rte_Read_CtrlLed_ActLed_sState_Param1;
extern tsRte_SysMon_VehNetState            Rte_Read_SysMon_VehNetState_Param1;
extern teRte_ReqLightState                 Rte_Read_SysMon_LowBeamCmd_Req_Param1;
extern tsRte_SigPrep_VehicleConfigSig      Rte_Read_SigPrep_VehicleConfigSig_Param1;
extern tsRte_SysMon_LifePhases             Rte_Read_SysMon_LifePhases_Param1;
extern tsRte_SigPrep_ElecSupState          Rte_Read_SigPrep_ElecSupState_Param1;
extern teRte_ReqLightState                 Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1;
extern boolean                             Rte_Read_DEM_OV_NotifyStatus_Param1;
extern boolean                             Rte_Read_DEM_UV_NotifyStatus_Param1;
extern boolean                             Rte_Read_AdbMxb_Gfhb_Diag_Param1;
extern tsRte_Ld_ActivationRoutineControl   Rte_Read_Diag_LdActivationRoutineControl_Param1;
extern tAdbOut                             Rte_Read_ppsAdb_Out_sVal_4_Param1;
extern tAdbStatus                          Rte_Read_Adb_StatusOut_Param1;
extern tAdbOut                             Rte_Read_ppsAdb_Out_sVal_0_Param1;

/*Write*/
extern teRte_GfHb_Cmd                      Rte_Write_FctR_GfHbCmd_Param1;
extern tsRte_TgtLedVal0Arr                 Rte_Write_FctR_TgtLed_sVal_Param1;
extern tsRte_AfsDblCmd                     Rte_Write_FctR_AfsDblCmd_Param1;
extern teRte_AfsModeSig_sVal               Rte_Write_FctR_AfsModeSig_sVal_Param1;
extern tsRte_LgtFctState                   Rte_Write_FctR_LgtFctState_Param1;
extern tsRte_LgtFctStatus                  Rte_Write_FctR_LgtFctStatus_Param1;
extern teRte_WarningMode                   Rte_Write_FctR_TiWarningMode_Param1;
extern boolean                             Rte_Write_FctR_TiFailureStatus_Param1;
extern tuFctR_LgtFct                       Rte_Write_FctR_LgtDistStatus_Param1;
extern boolean                             Rte_Write_FctR_PXALightDistr_Fbit_Param1;

extern tUtilDebounceControl                UtilDebounceInit_Param1;
extern tieDigState                         UtilDebounceInit_Param2;
extern TIMER                               UtilDebounceInit_Param3;
extern TIMER                               UtilDebounceInit_Param4;

extern tUtilDebounceControl                UtilDebounce_Param1;
extern boolean                             UtilDebounce_Param2;
extern uint32                              LPTMR0_GetTimeElapsed_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

/*Read*/
extern Std_ReturnType    Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_Afs_Signals_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_StdLgtTi_Req_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_StdLgtClSbl_Req_RetVal;
extern Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType    Rte_Read_CodM_FctR_Para_RetVal;
extern Std_ReturnType    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
extern Std_ReturnType    Rte_Read_CtrlLed_ActLed_sState_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_LifePhases_RetVal;
extern Std_ReturnType    Rte_Read_SigPrep_ElecSupState_RetVal;
extern Std_ReturnType    Rte_Read_SysMon_TurnIndicatorCmd_Req_RetVal;
extern Std_ReturnType    Rte_Read_DEM_OV_NotifyStatus_RetVal;
extern Std_ReturnType    Rte_Read_DEM_UV_NotifyStatus_RetVal;
extern Std_ReturnType    Rte_Read_AdbMxb_Gfhb_Diag_RetVal;
extern Std_ReturnType    Rte_Read_Diag_LdActivationRoutineControl_RetVal;
extern Std_ReturnType    Rte_Read_Adb_StatusOut_RetVal;
extern Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_0_RetVal;

/*Write*/
extern Std_ReturnType    Rte_Write_FctR_TgtLed_sVal_RetVal;
extern Std_ReturnType    Rte_Write_FctR_GfHbCmd_RetVal;
extern Std_ReturnType    Rte_Write_FctR_AfsDblCmd_RetVal;
extern Std_ReturnType    Rte_Write_FctR_AfsModeSig_sVal_RetVal;
extern Std_ReturnType    Rte_Write_FctR_LgtFctState_RetVal;
extern Std_ReturnType    Rte_Write_FctR_LgtFctStatus_RetVal;
extern Std_ReturnType    Rte_Write_FctR_TiWarningMode_RetVal;
extern Std_ReturnType    Rte_Write_FctR_TiFailureStatus_RetVal;
extern Std_ReturnType    Rte_Write_FctR_LgtDistStatus_RetVal;
extern Std_ReturnType    Rte_Write_FctR_PXALightDistr_Fbit_RetVal;
extern Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_4_RetVal;

extern uint32            LPTMR0_GetTimeElapsed_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

/*Read*/
extern uint8    Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
extern uint8    Rte_Read_SysMon_Afs_Signals_HitCount;
extern uint8    Rte_Read_SysMon_StdLgtTi_Req_HitCount;
extern uint8    Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount;
extern uint8    Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8    Rte_Read_CodM_FctR_Para_HitCount;
extern uint8    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount;
extern uint8    Rte_Read_CtrlLed_ActLed_sState_HitCount;
extern uint8    Rte_Read_SysMon_VehNetState_HitCount;
extern uint8    Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
extern uint8    Rte_Read_SigPrep_VehicleConfigSig_HitCount;
extern uint8    Rte_Read_SysMon_LifePhases_HitCount;
extern uint8    Rte_Read_SigPrep_ElecSupState_HitCount;
extern uint8    Rte_Read_SysMon_TurnIndicatorCmd_Req_HitCount;
extern uint8    Rte_Read_DEM_OV_NotifyStatus_HitCount;
extern uint8    Rte_Read_DEM_UV_NotifyStatus_HitCount;
extern uint8    Rte_Read_AdbMxb_Gfhb_Diag_HitCount;
extern uint8    Rte_Read_Diag_LdActivationRoutineControl_HitCount;
extern uint8    Rte_Read_Adb_StatusOut_HitCount;
extern uint8    Rte_Read_ppsAdb_Out_sVal_0_HitCount;

/*Write*/
extern uint8    Rte_Write_FctR_TgtLed_sVal_HitCount;
extern uint8    Rte_Write_FctR_GfHbCmd_HitCount;
extern uint8    Rte_Write_FctR_AfsDblCmd_HitCount;
extern uint8    Rte_Write_FctR_AfsModeSig_sVal_HitCount;
extern uint8    Rte_Write_FctR_LgtFctState_HitCount;
extern uint8    Rte_Write_FctR_LgtFctStatus_HitCount;
extern uint8    Rte_Write_FctR_TiWarningMode_HitCount;
extern uint8    Rte_Write_FctR_TiFailureStatus_HitCount;
extern uint8    Rte_Write_FctR_LgtDistStatus_HitCount;
extern uint8    Rte_Write_FctR_PXALightDistr_Fbit_HitCount;
extern uint8    Rte_Read_ppsAdb_Out_sVal_4_HitCount;

extern uint8    UtilDebounceInit_HitCount;
extern uint8    UtilDebounce_HitCount;
extern uint8    LPTMR0_GetTimeElapsed_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

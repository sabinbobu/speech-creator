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

#include <Rte/RteCommonTypes.h>

#include <../NvM/Nvm.h>
#include <LgmEIMMainAPI.h>
#include <_NM_Types.h>
#include <LgmEIMMainAPI.h>
#include <LgmDEHMainAPI.h>

//=============================================================================
// Stub function declarations
//=============================================================================

uint32                LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
Std_ReturnType        Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType        Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType        Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType        Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
Std_ReturnType        Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1);
Std_ReturnType        Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1);
Std_ReturnType        Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType        Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1);
Std_ReturnType        Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1);
Std_ReturnType        Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType        Rte_Read_ppsAvacOut(tsPositionOut* ppara1);
Std_ReturnType        Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1);
Std_ReturnType        Rte_Read_SigPrep_LevellingDiagStatus(tsRte_LevellingDiagStatus* ppara1);
Std_ReturnType        Rte_Read_SigPrep_LevellingFeedback(tsRte_LevellingFeedback* ppara1);
Std_ReturnType        Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType        Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType        Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType        Rte_Read_CtrlStp_SlaveDiagStatus(tsRte_LevellingDiagStatus* ppara1);
Std_ReturnType        Rte_Read_CodM_CtrlStp_Para(tsRteCodingParameters* ppara1);
Std_ReturnType        Rte_Read_CodM_CtrlStp_Para(tsRteCodingParameters* ppara1);
Std_ReturnType        Rte_Read_DEM_350Lost_NotifyStatus(boolean* ppara1);
Std_ReturnType        Rte_Write_Stp_RoutineControl(const tsRte_StepperRoutineControl* ppara1);
Std_ReturnType        Rte_Read_Stp_RoutineControl(tsRte_StepperRoutineControl* ppara1);
Std_ReturnType        Rte_Write_CtrlStp_Validation_Port(const tsRte_CtrlStpValidation* ppara1);
Std_ReturnType        Rte_Write_CtrlStp_ActStatStp_sVal_0(const tsRte_ActStatStp0* ppara1);
Std_ReturnType        Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront(const tsRte_CtrlStpStatusSpinFront* ppara1);
Std_ReturnType        Rte_Write_ppCtrlStpTarget0_StpTargetValues(const tsRte_CtrlStpTarget* ppara1);
Std_ReturnType        Rte_Write_CtrlStp_SlaveFeedback(const tsRte_LevellingFeedback* ppara1);
Std_ReturnType        Rte_Write_CtrlStp_SlaveDiagStatus(const tsRte_LevellingDiagStatus* ppara1);
Std_ReturnType        Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1);
Std_ReturnType        Rte_Read_DiagControl_AfsState(tsRte_AfsDiagControl* ppara1);
Std_ReturnType        Rte_Write_CtrlStp_MasterCommand(const tsRte_LevellingTgtPos* ppara1);
Std_ReturnType        Rte_Read_CtrlStp_ActStatStp_sVal_0(tsRte_ActStatStp0* ppara1);
NM_ErrorCodeType      NM_GetMode(NM_ModeType* p_NMMode);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tsRte_ActStatStp0                       Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
extern tsRte_LevellingTgtPos                   Rte_Write_CtrlStp_MasterCommand_Param1;
extern tsRte_AfsDiagControl                    Rte_Read_DiagControl_AfsState_Param1;
extern tsRte_CddStpActual                      Rte_Read_ppCddStpActual0_sStpActualValues_Param1;
extern tsRte_LevellingDiagStatus               Rte_Write_CtrlStp_SlaveDiagStatus_Param1;
extern tsRte_LevellingFeedback                 Rte_Write_CtrlStp_SlaveFeedback_Param1;
extern tsRte_CtrlStpStatusSpinFront            Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_Param1;
extern tsRte_ActStatStp0                       Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1;
extern tsRte_CtrlStpValidation                 Rte_Write_CtrlStp_Validation_Port_Param1;
extern tsRte_StepperRoutineControl             Rte_Write_Stp_RoutineControl_Param1;
extern tsRte_LevellingFeedback                 Rte_Read_CtrlStp_SlaveFeedback_Param1;
extern uint32                                  LPTMR0_GetTimeElapsed_Param1;
extern tieStepperIndex                         roCddStpStartRefRun_Param1;
extern ti16StepperPosition_halfsteps           roCddStpStartRefRun_Param2;
extern tsRte_SysMon_VehicleSpeed               Rte_Read_SysMon_VehicleSpeed_Param1;
extern tsRte_SysMon_VehNetState                Rte_Read_SysMon_VehNetState_Param1;
extern tsRte_SysMonLgtFctsReq                  Rte_Read_SysMon_StdLgtFcts_Req_Param1;
extern tsRte_SysMonAfsSignals                  Rte_Read_SysMon_Afs_Signals_Param1;
extern tsRte_SysMon_LifePhases                 Rte_Read_SysMon_LifePhases_Param1;
extern teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_SigPrep_DynamicSigs               Rte_Read_SigPrep_DynamicSigs_Param1;
extern tsRte_SigPrep_YawSpeed                  Rte_Read_SigPrep_YawSpeed_Param1;
extern tsRte_SigPrep_ElecSupState              Rte_Read_SigPrep_ElecSupState_Param1;
extern tsRte_SigPrep_VehicleConfigSig          Rte_Read_SigPrep_VehicleConfigSig_Param1;
extern tsRte_LevellingDiagStatus               Rte_Read_SigPrep_LevellingDiagStatus_Param1;
extern tsRte_LevellingFeedback                 Rte_Read_SigPrep_LevellingFeedback_Param1;
extern tsRte_LevellingTgtPos                   Rte_Read_SigPrep_LevellingTgtPos_Param1;
extern tsRte_LevellingTgtPos                   Rte_Read_CtrlStp_MasterCommand_Param1;
extern tsRte_Hs6_Diag_Drvled_L_457             Rte_Read_DrvLedDiag_Param1;
extern tsRte_Hs6_Diag_Drvled_L_457             Rte_Write_DrvLedDiag_Param1;
extern tsRte_LevellingDiagStatus               Rte_Read_CtrlStp_SlaveDiagStatus_Param1;
extern teRte_HlsSensorState                    Rte_Read_Pitch_PlausState_Param1;
extern tsPositionOut                           Rte_Read_ppsAvacOut_Param1;
extern tsRteCodingParameters                   Rte_Read_CodM_CtrlStp_Para_Param1;
extern boolean                                 Rte_Read_DEM_350Lost_NotifyStatus_Param1;
extern tsRte_StepperRoutineControl             Rte_Read_Stp_RoutineControl_Param1;
extern tsRte_CtrlStpTarget                     Rte_Write_ppCtrlStpTarget0_StpTargetValues_Param1;
extern NM_ModeType                             NM_GetMode_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType                   Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
extern uint32                           LPTMR0_GetTimeElapsed_RetVal;
extern Std_ReturnType                   roCddStpOff_RetVal;
extern Std_ReturnType                   roCddStpOn_RetVal;
extern LEIM_TE_CurrentEIMode            EAPI_GetCurrentEIMode_RetVal;
extern Std_ReturnType                   Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType                   Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType                   Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType                   Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
extern Std_ReturnType                   Rte_Read_SysMon_Afs_Signals_RetVal;
extern Std_ReturnType                   Rte_Read_SysMon_LifePhases_RetVal;
extern Std_ReturnType                   Rte_Read_SigPrep_YawSpeed_RetVal;
extern Std_ReturnType                   Rte_Read_SigPrep_ElecSupState_RetVal;
extern Std_ReturnType                   Rte_Read_SigPrep_VehicleConfigSig_RetVal;
extern Std_ReturnType                   Rte_Read_SigPrep_LevellingDiagStatus_RetVal;
extern Std_ReturnType                   Rte_Read_SigPrep_LevellingFeedback_RetVal;
extern Std_ReturnType                   Rte_Read_SigPrep_LevellingTgtPos_RetVal;
extern Std_ReturnType                   Rte_Read_CtrlStp_MasterCommand_RetVal;
extern Std_ReturnType                   Rte_Read_DrvLedDiag_RetVal;
extern Std_ReturnType                   Rte_Write_DrvLedDiag_RetVal;
extern Std_ReturnType                   Rte_Read_CtrlStp_SlaveDiagStatus_RetVal;
extern Std_ReturnType                   Rte_Read_CtrlStp_SlaveFeedback_RetVal;
extern Std_ReturnType                   Rte_Read_Pitch_PlausState_RetVal;
extern Std_ReturnType                   Rte_Read_ppsAvacOut_RetVal;
extern Std_ReturnType                   Rte_Read_CodM_CtrlStp_Para_RetVal;
extern Std_ReturnType                   Rte_Read_DEM_350Lost_NotifyStatus_RetVal;
extern Std_ReturnType                   Rte_Write_Stp_RoutineControl_RetVal;
extern Std_ReturnType                   Rte_Read_Stp_RoutineControl_RetVal;
extern Std_ReturnType                   Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;
extern Std_ReturnType                   Rte_Read_DiagControl_AfsState_RetVal;
extern NM_ErrorCodeType                 NM_GetMode_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount;
extern uint8  LPTMR0_GetTimeElapsed_HitCount;
extern uint8  Rte_Read_Pitch_PlausState_HitCount;
extern uint8  roCddStpOff_HitCount;
extern uint8  roCddStpOn_HitCount;
extern uint8  roCddStpStartRefRun_HitCount;
extern uint8  CtrlStp_RteAccess_ReadSensorStatus_HitCount;
extern uint8  EAPI_GetCurrentEIMode_HitCount;
extern uint8  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8  Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8  Rte_Read_SysMon_VehNetState_HitCount;
extern uint8  Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
extern uint8  Rte_Read_SysMon_Afs_Signals_HitCount;
extern uint8  Rte_Read_SysMon_LifePhases_HitCount;
extern uint8  Rte_Read_SigPrep_DynamicSigs_HitCount;
extern uint32 Rte_Read_SigPrep_YawSpeed_HitCount;
extern uint32 Rte_Read_SigPrep_ElecSupState_HitCount;
extern uint8  Rte_Read_SigPrep_VehicleConfigSig_HitCount;
extern uint32 Rte_Read_SigPrep_LevellingDiagStatus_HitCount;
extern uint32 Rte_Read_SigPrep_LevellingFeedback_HitCount;
extern uint32 Rte_Read_SigPrep_LevellingTgtPos_HitCount;
extern uint32 Rte_Read_CtrlStp_MasterCommand_HitCount;
extern uint8  Rte_Read_DrvLedDiag_HitCount;
extern uint8  Rte_Write_DrvLedDiag_HitCount;
extern uint32 Rte_Read_CtrlStp_SlaveDiagStatus_HitCount;
extern uint32 Rte_Read_CtrlStp_SlaveFeedback_HitCount;
extern uint32 Rte_Read_ppsAvacOut_HitCount;
extern uint32 Rte_Read_CodM_CtrlStp_Para_HitCount;
extern uint32 Rte_Read_DEM_350Lost_NotifyStatus_HitCount;
extern uint32 Rte_Write_Stp_RoutineControl_HitCount;
extern uint32 Rte_Read_Stp_RoutineControl_HitCount;
extern uint32 Rte_Write_CtrlStp_Validation_Port_HitCount;
extern uint32 Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount;
extern uint32 Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount;
extern uint32 Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount;
extern uint32 Rte_Write_CtrlStp_SlaveFeedback_HitCount;
extern uint32 Rte_Write_CtrlStp_SlaveDiagStatus_HitCount;
extern uint32 Rte_Read_ppCddStpActual0_sStpActualValues_HitCount;
extern uint32 Rte_Read_DiagControl_AfsState_HitCount;
extern uint32 Rte_Write_CtrlStp_MasterCommand_HitCount;
extern uint8  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_HitCount;
extern uint8  CtrlStp_RteAccess_WriteStpRoutineAck_HitCount;
extern uint32 NM_GetMode_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

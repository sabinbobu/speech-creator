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

tsRte_ActStatStp0                       Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
tsRte_LevellingTgtPos                   Rte_Write_CtrlStp_MasterCommand_Param1;
tsRte_AfsDiagControl                    Rte_Read_DiagControl_AfsState_Param1;
tsRte_CddStpActual                      Rte_Read_ppCddStpActual0_sStpActualValues_Param1;
tsRte_LevellingDiagStatus               Rte_Write_CtrlStp_SlaveDiagStatus_Param1;
tsRte_LevellingFeedback                 Rte_Write_CtrlStp_SlaveFeedback_Param1;
tsRte_CtrlStpStatusSpinFront            Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_Param1;
tsRte_ActStatStp0                       Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1;
tsRte_CtrlStpValidation                 Rte_Write_CtrlStp_Validation_Port_Param1;
tsRte_StepperRoutineControl             Rte_Write_Stp_RoutineControl_Param1;
tsRte_LevellingFeedback                 Rte_Read_CtrlStp_SlaveFeedback_Param1;
uint32                                  LPTMR0_GetTimeElapsed_Param1;
tieStepperIndex                         roCddStpStartRefRun_Param1;
ti16StepperPosition_halfsteps           roCddStpStartRefRun_Param2;
tsRte_SysMon_VehicleSpeed               Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SysMon_VehNetState                Rte_Read_SysMon_VehNetState_Param1;
tsRte_SysMonLgtFctsReq                  Rte_Read_SysMon_StdLgtFcts_Req_Param1;
tsRte_SysMonAfsSignals                  Rte_Read_SysMon_Afs_Signals_Param1;
tsRte_SysMon_LifePhases                 Rte_Read_SysMon_LifePhases_Param1;
teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_SigPrep_DynamicSigs               Rte_Read_SigPrep_DynamicSigs_Param1;
tsRte_SigPrep_YawSpeed                  Rte_Read_SigPrep_YawSpeed_Param1;
tsRte_SigPrep_ElecSupState              Rte_Read_SigPrep_ElecSupState_Param1;
tsRte_SigPrep_VehicleConfigSig          Rte_Read_SigPrep_VehicleConfigSig_Param1;
tsRte_LevellingDiagStatus               Rte_Read_SigPrep_LevellingDiagStatus_Param1;
tsRte_LevellingFeedback                 Rte_Read_SigPrep_LevellingFeedback_Param1;
tsRte_LevellingTgtPos                   Rte_Read_SigPrep_LevellingTgtPos_Param1;
tsRte_LevellingTgtPos                   Rte_Read_CtrlStp_MasterCommand_Param1;
tsRte_Hs6_Diag_Drvled_L_457             Rte_Read_DrvLedDiag_Param1;
tsRte_Hs6_Diag_Drvled_L_457             Rte_Write_DrvLedDiag_Param1;
tsRte_LevellingDiagStatus               Rte_Read_CtrlStp_SlaveDiagStatus_Param1;
teRte_HlsSensorState                    Rte_Read_Pitch_PlausState_Param1;
tsPositionOut                           Rte_Read_ppsAvacOut_Param1;
tsRteCodingParameters                   Rte_Read_CodM_CtrlStp_Para_Param1;
boolean                                 Rte_Read_DEM_350Lost_NotifyStatus_Param1;
tsRte_StepperRoutineControl             Rte_Read_Stp_RoutineControl_Param1;
tsRte_CtrlStpTarget                     Rte_Write_ppCtrlStpTarget0_StpTargetValues_Param1;
NM_ModeType                             NM_GetMode_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType                   Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
uint32                           LPTMR0_GetTimeElapsed_RetVal;
Std_ReturnType                   roCddStpOff_RetVal;
Std_ReturnType                   roCddStpOn_RetVal;
LEIM_TE_CurrentEIMode            EAPI_GetCurrentEIMode_RetVal;
Std_ReturnType                   Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType                   Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType                   Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType                   Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType                   Rte_Read_SysMon_Afs_Signals_RetVal;
Std_ReturnType                   Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType                   Rte_Read_SigPrep_YawSpeed_RetVal;
Std_ReturnType                   Rte_Read_SigPrep_ElecSupState_RetVal;
Std_ReturnType                   Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType                   Rte_Read_SigPrep_LevellingDiagStatus_RetVal;
Std_ReturnType                   Rte_Read_SigPrep_LevellingFeedback_RetVal;
Std_ReturnType                   Rte_Read_SigPrep_LevellingTgtPos_RetVal;
Std_ReturnType                   Rte_Read_CtrlStp_MasterCommand_RetVal;
Std_ReturnType                   Rte_Read_DrvLedDiag_RetVal;
Std_ReturnType                   Rte_Write_DrvLedDiag_RetVal;
Std_ReturnType                   Rte_Read_CtrlStp_SlaveDiagStatus_RetVal;
Std_ReturnType                   Rte_Read_CtrlStp_SlaveFeedback_RetVal;
Std_ReturnType                   Rte_Read_Pitch_PlausState_RetVal;
Std_ReturnType                   Rte_Read_ppsAvacOut_RetVal;
Std_ReturnType                   Rte_Read_CodM_CtrlStp_Para_RetVal;
Std_ReturnType                   Rte_Read_DEM_350Lost_NotifyStatus_RetVal;
Std_ReturnType                   Rte_Write_Stp_RoutineControl_RetVal;
Std_ReturnType                   Rte_Read_Stp_RoutineControl_RetVal;
Std_ReturnType                   Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;
Std_ReturnType                   Rte_Read_DiagControl_AfsState_RetVal;
NM_ErrorCodeType                 NM_GetMode_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount;
uint8  LPTMR0_GetTimeElapsed_HitCount;
uint8  Rte_Read_Pitch_PlausState_HitCount;
uint8  roCddStpOff_HitCount;
uint8  roCddStpOn_HitCount;
uint8  roCddStpStartRefRun_HitCount;
uint8  CtrlStp_RteAccess_ReadSensorStatus_HitCount;
uint8  EAPI_GetCurrentEIMode_HitCount;
uint8  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8  Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8  Rte_Read_SysMon_VehNetState_HitCount;
uint8  Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8  Rte_Read_SysMon_Afs_Signals_HitCount;
uint8  Rte_Read_SysMon_LifePhases_HitCount;
uint8  Rte_Read_SigPrep_DynamicSigs_HitCount;
uint32 Rte_Read_SigPrep_YawSpeed_HitCount;
uint32 Rte_Read_SigPrep_ElecSupState_HitCount;
uint8  Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint32 Rte_Read_SigPrep_LevellingDiagStatus_HitCount;
uint32 Rte_Read_SigPrep_LevellingFeedback_HitCount;
uint32 Rte_Read_SigPrep_LevellingTgtPos_HitCount;
uint32 Rte_Read_CtrlStp_MasterCommand_HitCount;
uint8  Rte_Read_DrvLedDiag_HitCount;
uint8  Rte_Write_DrvLedDiag_HitCount;
uint32 Rte_Read_CtrlStp_SlaveDiagStatus_HitCount;
uint32 Rte_Read_CtrlStp_SlaveFeedback_HitCount;
uint32 Rte_Read_ppsAvacOut_HitCount;
uint32 Rte_Read_CodM_CtrlStp_Para_HitCount;
uint32 Rte_Read_DEM_350Lost_NotifyStatus_HitCount;
uint32 Rte_Write_Stp_RoutineControl_HitCount;
uint32 Rte_Read_Stp_RoutineControl_HitCount;
uint32 Rte_Write_CtrlStp_Validation_Port_HitCount;
uint32 Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount;
uint32 Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount;
uint32 Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount;
uint32 Rte_Write_CtrlStp_SlaveFeedback_HitCount;
uint32 Rte_Write_CtrlStp_SlaveDiagStatus_HitCount;
uint32 Rte_Read_ppCddStpActual0_sStpActualValues_HitCount;
uint32 Rte_Read_DiagControl_AfsState_HitCount;
uint32 Rte_Write_CtrlStp_MasterCommand_HitCount;
uint8  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_HitCount;
uint8  CtrlStp_RteAccess_WriteStpRoutineAck_HitCount;
uint32 NM_GetMode_HitCount;


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
NM_ErrorCodeType NM_GetMode(NM_ModeType* p_NMMode)
{
  *p_NMMode = NM_GetMode_Param1;
  NM_GetMode_HitCount++;

  return NM_GetMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_ActStatStp_sVal_0
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlStp_ActStatStp_sVal_0
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_ActStatStp_sVal_0(tsRte_ActStatStp0* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount++;
  return Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlStp_MasterCommand
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlStp_MasterCommand
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlStp_MasterCommand(const tsRte_LevellingTgtPos* ppara1)
{
  Rte_Write_CtrlStp_MasterCommand_Param1 = *ppara1;
  Rte_Write_CtrlStp_MasterCommand_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DiagControl_AfsState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DiagControl_AfsState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DiagControl_AfsState(tsRte_AfsDiagControl* ppara1)
{
  *ppara1 = Rte_Read_DiagControl_AfsState_Param1;
  Rte_Read_DiagControl_AfsState_HitCount++;
  return Rte_Read_DiagControl_AfsState_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppCddStpActual0_sStpActualValues
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppCddStpActual0_sStpActualValues
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1)
{
  *ppara1 = Rte_Read_ppCddStpActual0_sStpActualValues_Param1;
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount++;
  return Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlStp_SlaveDiagStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlStp_SlaveDiagStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlStp_SlaveDiagStatus(const tsRte_LevellingDiagStatus* ppara1)
{
  Rte_Write_CtrlStp_SlaveDiagStatus_Param1 = *ppara1;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlStp_SlaveFeedback
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlStp_SlaveFeedback
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlStp_SlaveFeedback(const tsRte_LevellingFeedback* ppara1)
{
  Rte_Write_CtrlStp_SlaveFeedback_Param1 = *ppara1;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ppCtrlStpTarget0_StpTargetValues
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_ppCtrlStpTarget0_StpTargetValues
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ppCtrlStpTarget0_StpTargetValues(const tsRte_CtrlStpTarget* ppara1)
{
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_Param1 = *ppara1;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront(const tsRte_CtrlStpStatusSpinFront* ppara1)
{
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_Param1 = *ppara1;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlStp_ActStatStp_sVal_0
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlStp_ActStatStp_sVal_0
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlStp_ActStatStp_sVal_0(const tsRte_ActStatStp0* ppara1)
{
  Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1 = *ppara1;
  Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CtrlStp_Validation_Port
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_CtrlStp_Validation_Port
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CtrlStp_Validation_Port(const tsRte_CtrlStpValidation* ppara1)
{
  Rte_Write_CtrlStp_Validation_Port_Param1 = *ppara1;
  Rte_Write_CtrlStp_Validation_Port_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Stp_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Stp_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Stp_RoutineControl(tsRte_StepperRoutineControl* ppara1)
{
  *ppara1 = Rte_Read_Stp_RoutineControl_Param1;
  Rte_Read_Stp_RoutineControl_HitCount++;
  return Rte_Read_Stp_RoutineControl_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Write_Stp_RoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_Stp_RoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Stp_RoutineControl(const tsRte_StepperRoutineControl* ppara1)
{
  Rte_Write_Stp_RoutineControl_Param1 = *ppara1;
  Rte_Write_Stp_RoutineControl_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DEM_350Lost_NotifyStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DEM_350Lost_NotifyStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DEM_350Lost_NotifyStatus(boolean* ppara1)
{
  *ppara1 = Rte_Read_DEM_350Lost_NotifyStatus_Param1;
  Rte_Read_DEM_350Lost_NotifyStatus_HitCount++;
  return Rte_Read_DEM_350Lost_NotifyStatus_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppsAvacOut
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppsAvacOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppsAvacOut(tsPositionOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAvacOut_Param1;
  Rte_Read_ppsAvacOut_HitCount++;
  return Rte_Read_ppsAvacOut_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CtrlStp_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_CtrlStp_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CtrlStp_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CtrlStp_Para_Param1;
  Rte_Read_CodM_CtrlStp_Para_HitCount++;
  return Rte_Read_CodM_CtrlStp_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Pitch_PlausState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Pitch_PlausState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1)
{
  *ppara1 = Rte_Read_Pitch_PlausState_Param1;
  Rte_Read_Pitch_PlausState_HitCount++;
  return Rte_Read_Pitch_PlausState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_SlaveFeedback
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlStp_SlaveFeedback
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_SlaveFeedback(tsRte_LevellingFeedback* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_SlaveFeedback_Param1;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount++;
  return Rte_Read_CtrlStp_SlaveFeedback_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_SlaveDiagStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlStp_SlaveDiagStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_SlaveDiagStatus(tsRte_LevellingDiagStatus* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_SlaveDiagStatus_Param1;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount++;
  return Rte_Read_CtrlStp_SlaveDiagStatus_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief Rte_Write_DrvLedDiag
///
/// \descr Stub function for Rte_Write_DrvLedDiag
///
/// \param  tsRte_Hs6_Diag_Drvled_L_457
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  Rte_Write_DrvLedDiag_Param1 = *ppara1;
  Rte_Write_DrvLedDiag_HitCount++;
}
//-----------------------------------------------------------------------------
/// \brief Rte_Read_DrvLedDiag
///
/// \descr Stub function for Rte_Read_DrvLedDiag
///
/// \param  tsRte_Hs6_Diag_Drvled_L_457
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  *ppara1 = Rte_Read_DrvLedDiag_Param1;
  Rte_Read_DrvLedDiag_HitCount++;
  return Rte_Read_DrvLedDiag_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_MasterCommand
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_MasterCommand(tsRte_LevellingTgtPos* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_MasterCommand_Param1;
  Rte_Read_CtrlStp_MasterCommand_HitCount++;
  return Rte_Read_CtrlStp_MasterCommand_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_LevellingTgtPos
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_LevellingTgtPos
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_LevellingTgtPos_Param1;
  Rte_Read_SigPrep_LevellingTgtPos_HitCount++;
  return Rte_Read_SigPrep_LevellingTgtPos_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_LevellingFeedback
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_LevellingFeedback
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_LevellingFeedback(tsRte_LevellingFeedback* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_LevellingFeedback_Param1;
  Rte_Read_SigPrep_LevellingFeedback_HitCount++;
  return Rte_Read_SigPrep_LevellingFeedback_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_LevellingDiagStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_LevellingDiagStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_LevellingDiagStatus(tsRte_LevellingDiagStatus* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_LevellingDiagStatus_Param1;
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount++;
  return Rte_Read_SigPrep_LevellingDiagStatus_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehicleConfigSig
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehicleConfigSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehicleConfigSig_Param1;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount++;
  return Rte_Read_SigPrep_VehicleConfigSig_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ElecSupState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ElecSupState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ElecSupState_Param1;
  Rte_Read_SigPrep_ElecSupState_HitCount++;
  return Rte_Read_SigPrep_ElecSupState_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_YawSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_YawSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_YawSpeed(tsRte_SigPrep_YawSpeed* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_YawSpeed_Param1;
  Rte_Read_SigPrep_YawSpeed_HitCount++;
  return Rte_Read_SigPrep_YawSpeed_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrep_DynamicSigs
///
/// \descr Stub function for Rte_Read_SigPrep_DynamicSigs
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_DynamicSigs_Param1;
  Rte_Read_SigPrep_DynamicSigs_HitCount++;
  return E_OK;
}

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
/// \brief  roCddStpOff
///
/// \descr  Stub function to simulate the behaviour of roCddStpOff
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType roCddStpOff(void)
{
  roCddStpOff_HitCount++;

  return roCddStpOff_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  roCddStpOn
///
/// \descr  Stub function to simulate the behaviour of roCddStpOn
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType roCddStpOn(void)
{
  roCddStpOn_HitCount++;

  return roCddStpOn_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  roCddStpStartRefRun
///
/// \descr  Stub function to simulate the behaviour of roCddStpStartRefRun
///
/// \param  stepperIndex
/// \param  position
///
/// \return void
//-----------------------------------------------------------------------------
void roCddStpStartRefRun(tieStepperIndex stepperIndex, ti16StepperPosition_halfsteps position)
{
  roCddStpStartRefRun_Param1 = stepperIndex;
  roCddStpStartRefRun_Param2 = position;
  roCddStpStartRefRun_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  EAPI_GetCurrentEIMode
///
/// \descr  Stub function created to simulate the behaviour of EAPI_GetCurrentEIMode
///
/// \param  void
///
/// \return LEIM_TE_CurrentEIMode
//-----------------------------------------------------------------------------
LEIM_TE_CurrentEIMode EAPI_GetCurrentEIMode(void)
{
  EAPI_GetCurrentEIMode_HitCount++;

  return EAPI_GetCurrentEIMode_RetVal;
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
/// \brief  Rte_Read_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehicleSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehicleSpeed_Param1;
  Rte_Read_SysMon_VehicleSpeed_HitCount++;
  return Rte_Read_SysMon_VehicleSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehNetState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehNetState_Param1;
  Rte_Read_SysMon_VehNetState_HitCount++;
  return Rte_Read_SysMon_VehNetState_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtFcts_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_StdLgtFcts_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1)
{
  *ppara1 = Rte_Read_SysMon_StdLgtFcts_Req_Param1;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount++;

  return Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_Afs_Signals
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_Afs_Signals
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1)
{
  *ppara1 = Rte_Read_SysMon_Afs_Signals_Param1;
  Rte_Read_SysMon_Afs_Signals_HitCount++;

  return Rte_Read_SysMon_Afs_Signals_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;
  return Rte_Read_SysMon_LifePhases_RetVal;
}


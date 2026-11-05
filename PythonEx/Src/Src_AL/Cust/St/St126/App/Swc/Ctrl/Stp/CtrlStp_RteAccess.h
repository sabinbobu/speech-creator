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
/// \file   Dbl_RteAccess.h
///
/// \brief  encapsule RTE access
///
/// \descr  Functions used for the Dbl RTE wrapper, for input/output 
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Catuna Catalin-Lucian F37430C
///         mail to <catalin-lucian.catuna[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef __CTRLSTP_RTEACCESS_H__
#define __CTRLSTP_RTEACCESS_H__

//=============================================================================
// includes
//=============================================================================
#include <RteCommonTypes.h>
#include <Cfg/Cfg.h>
#include <Std_Types.h>
#include <Api/CtrlStp.h>
#include <CtrlStp_Data.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST

uint16 CtrlStp_RteAccess_ReadSpeed(boolean * boSpeedInvalid);
uint8 CtrlStp_RteAccess_ReadVehicleElectricState(void);
uint8 CtrlStp_RteAccess_ReadVESMainState(void);
uint8 CtrlStp_RteAccess_ReadAFSMode(void);
uint8 CtrlStp_RteAccess_ReadGfhbCmd(void);
uint8 CtrlStp_RteAccess_ReadHbCmd(void);
uint8 CtrlStp_RteAccess_ReadLbBoostAllowed(void);
uint8 CtrlStp_RteAccess_ReadVehicleModeConfig(void);
teCtrlStp_EtatFee CtrlStp_RteAccess_ReadElectricalSuppState(void);
Std_ReturnType CtrlStp_RteAccess_Read_EcuSide(teCtrlStp_MountingSide* eEcuSide);
void CtrlStp_RteAccess_Read_350Lost_Status(boolean* pboStatus);
void CtrlStp_RteAccess_ReadAvacCommand(sint16* snVerticalAngle, boolean* boVehAttitudeInvalid, uint8 ucMountingSide);
void CtrlStp_RteAccess_ReadSensorStatus(teCtrlStp_SensorState* eSensorState);
void CtrlStp_RteAccess_ReadLevellingDiagStatus(tsCtrlStp_LevellingDiagStatus* sLevellingDiagStatus);
void CtrlStp_RteAccess_ReadLevellingFeedback(tsCtrlStp_LevellingFeedback* sLevellingFeedback);
void CtrlStp_RteAccess_ReadLevellingTgtPos(tsCtrlStp_LevellingTgtPos* sLevellingTgtPos);
void CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues(tsRte_CddStpActual* CtrlStp_ActAll);
void CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(tsCtrlStp_LevellingTgtPos* tsLevellingSignals);
void CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port(tsCtrlStp_LevellingTgtPos* tsLevellingSignals);
void CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus);
void CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port(tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus);
void CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(tsCtrlStp_LevellingFeedback* tsLevellingFeedback);
void CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port(tsCtrlStp_LevellingFeedback* tsLevellingFeedback);
void CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(tsRte_CtrlStpTarget* CtrlStp_TgtAll);
void CtrlStp_RteAccess_Write_DrvLedDiag_Port(boolean boLvlError);
void CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(tsCtrlStp_DiagStatus* CtrlStp_ActStatStp);
void CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(tsCtrlStp_DiagStatus CtrlStp_ActStatStp);
void CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(tsCtrlStp_ValidationParameters* sValidationParams);
void CtrlStp_RteAccess_ReadDiagStpControlRoutine(tsCtrlStp_StepperRoutineControl* psRoutineInfo);
void CtrlStp_RteAccess_WriteStpRoutineAck(boolean boStatus);
void CtrlStp_RteAccess_MapParams(void);


#endif

//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CtrlDcm_RteAccess.h
///
/// \brief Functions used for the Dcm RTE wrapper, for input/output
///
//-----------------------------------------------------------------------------
#ifndef CTRL_DCM_RTE_ACCESS_2022_06_23_H
#define CTRL_DCM_RTE_ACCESS_2022_06_23_H

//=============================================================================
// includes
//=============================================================================

#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST
#include <RteCommonTypes.h>
#include <Cfg/Cfg.h>
#include <Std_Types.h>
#include "Api/CtrlDcm.h"
#include "CtrlDcm_Data.h"


uint16 CtrlDcm_RteAccess_ReadSpeed(boolean * boSpeedInvalid);
uint8 CtrlDcm_RteAccess_ReadVehicleElectricState(void);
uint8 CtrlDcm_RteAccess_ReadVESMainState(void);
uint8 CtrlDcm_RteAccess_ReadVehicleModeConfig(void);
Std_ReturnType CtrlDcm_RteAccess_Read_EcuSide(teCtrlDcm_MountingSide* eEcuSide);
void CtrlDcm_RteAccess_ReadAvacCommand(sint16* snVerticalAngle, boolean* boVehAttitudeInvalid, uint8 ucMountingSide);
void CtrlDcm_RteAccess_ReadSensorStatus(teCtrlDcm_SensorState* eSensorState);
void CtrlDcm_RteAccess_ReadDriverErrors(tsCtrlDcm_ErrorStatus* eErrorState);
void CtrlDcm_RteAccess_ReadLevellingTgtPos(tsCtrlDcm_LevellingTgtPos* sLevellingTgtPos);
void CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals);
void CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals);
void CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(tsCtrlDcm_TargetValues* CtrlDcm_TgtAll);
void CtrlDcm_RteAccess_Write_DrvLedDiag_Port(boolean boLvlError);
void CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(boolean boLvlError);
void CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(tsCtrlDcm_LevellingDiagStatus* sLvlError);
void CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0(tsCtrlDcm_DiagStatus* CtrlDcm_ActStatDcm);
void CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0(tsCtrlDcm_DiagStatus CtrlDcm_ActStatDcm);
void CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(tsCtrlDcm_DcmStatusParameters* sStatusParams);
void CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(tsCtrlDcm_DcMotorRoutineControl* psRoutineInfo);
void CtrlDcm_RteAccess_WriteDcmRoutineAck(boolean boStatus);
void CtrlDcm_RteAccess_MapParams(void);

#endif // CTRL_DCM_RTE_ACCESS_2022_06_23_H

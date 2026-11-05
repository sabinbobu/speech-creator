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
/// \file  CtrlDcmSm.h
///
/// \brief State machine control for CtrlDcm
///
//-----------------------------------------------------------------------------
#ifndef CTRL_DCM_SM_2022_06_23_H
#define CTRL_DCM_SM_2022_06_23_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>

//-----------------------------------------------------------------------------
// proptotypes
//-----------------------------------------------------------------------------
boolean CtrlDcm_CondEnabled                 (void);
boolean CtrlDcm_GetDiagLvl                  (void);
boolean CtrlDcm_RetPowerTrainActive         (void);
boolean CtrlDcm_ReturnboTrainingState       (void);
boolean CtrlDcm_ReturnboLvlAdjFuncFault     (void);
boolean CtrlDcm_ReturnboSlaveLvlAdjFuncFault(void);
boolean CtrlDcm_RetVehIgnition              (void);
boolean CtrlDcm_ReturnboExtTakeOver         (void);
void    CtrlDcm_DetectSide                  (void);
teCtrlDcm_MountingSide CtrlDcm_ReturnSide   (void);

boolean CtrlDcm_ReturnboLvlAdjHeadlampFault(void);
boolean CtrlDcm_ReturnboLvlAdjHeadlampFault_R(void);
teCtrlDcm_SensorState         CtrlDcm_ReturneSensorError(void);
                                    
void CtrlDcm_GetTgtPos              (void);
void CtrlDcm_DiagRoutineControl     (void);

void CtrlDcm_ReadMasterSignals      (void);
void CtrlDcm_ReadSlaveSignals       (void);
void CtrlDcm_WriteMasterSignals     (void);
void CtrlDcm_WriteSlaveSignals      (void);

void CtrlDcm_ReadCommonSignals(void);

void CtrlDcm_SetSignalMode(teCtrlDcm_SignalSrc eMode);
void CtrlDcm_SetDiagLvl(boolean boDiagLvl);
void CtrlDcm_SetSlaveStopRequest(boolean boStopReq);
void CtrlDcm_SetSlaveSafetyPosition(boolean boPosReq);
void CtrlDcm_SetFailIgnitionNeeded(boolean boIgnitionReq);

#endif // CTRL_DCM_SM_2022_06_23_H

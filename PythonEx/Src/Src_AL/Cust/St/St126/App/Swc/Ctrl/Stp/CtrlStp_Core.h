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
/// \file  CtrlStp_Core.h
///
/// \brief State transition control for CtrlStp
///
//-----------------------------------------------------------------------------
#ifndef CTRL_STP_TRANS_2020_07_02_H_
#define CTRL_STP_TRANS_2020_07_02_H_


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>

//-----------------------------------------------------------------------------
// proptotypes
//-----------------------------------------------------------------------------
boolean CtrlStp_CondEnabled                 (void);
boolean CtrlStp_CondIsReady                 (void);
boolean CtrlStp_CondIsOn                    (void);
boolean CtrlStp_CondOperationRequest        (void);
boolean CtrlStp_CondOperationStatus         (void);
boolean CtrlStp_CondParamReady              (void);
boolean CtrlStp_CondRefDelay                (void);
boolean CtrlStp_CondRefDnCompl              (void);
boolean CtrlStp_CondRefInProgress           (void);
boolean CtrlStp_CondRefUpCompl              (void);
boolean CtrlStp_RefRequest                  (void);
boolean CtrlStp_GetSubModeErr               (void);
boolean CtrlStp_RetPowerTrainActive         (void);
boolean CtrlStp_ReturnboTrainingState       (void);
boolean CtrlStp_ReturnboLvlAdjFuncFault     (void);
boolean CtrlStp_ReturnboSlaveLvlAdjFuncFault(void);
boolean CtrlStp_ReturnSteplossErr(void);
boolean CtrlStp_ReturnRightSteplossErr(void);
boolean CtrlStp_RetVehIgnition              (void);
boolean CtrlStp_ReturnboExtTakeOver         (void);
boolean CtrlStp_isSafetyPosReached          (void);
void    CtrlStp_DetectSide                  (void);
teCtrlStp_MountingSide CtrlStp_ReturnSide   (void);

teCtrlStp_HeadlampFaultStatus CtrlStp_ReturneLvlAdjHeadlampFault_L(void);
teCtrlStp_HeadlampFaultStatus CtrlStp_ReturneLvlAdjHeadlampFault_R(void);
teCtrlStp_SensorState         CtrlStp_ReturneSensorError(void);


boolean CtrlStp_DetectElecTransition(void);
boolean CtrlStp_DetectElecTransitionSttToAdj(void);
boolean CtrlStp_DetectElecTransitionSttToRef(void);

void CtrlStp_DoNorm                 (void);
                                    
void CtrlStp_EntryDis               (void);
void CtrlStp_EntryErr               (void);
void CtrlStp_EntryInit              (void);
void CtrlStp_EntryNorm              (void);
void CtrlStp_EntryOff               (void);
void CtrlStp_EntryRefDn             (void);
void CtrlStp_EntryRefUp             (void);
                                    
void CtrlStp_EvaluateOpReq          (void);
void CtrlStp_GetTgtPos              (void);
void CtrlStp_DiagRoutineControl     (void);

void CtrlStp_ReadParam              (void);
void CtrlStp_ReadMasterSignals      (void);
void CtrlStp_ReadSlaveSignals       (void);
void CtrlStp_WriteMasterSignals     (void);
void CtrlStp_WriteSlaveSignals      (void);

void CtrlStp_ReadCommonSignals(void);


void CtrlStp_SelectSource           (void);
void CtrlStp_StartRef               (void);
void CtrlStp_ElecDiagStat           (void);
void CtrlStp_PosDiagStat            (void);
void CtrlStp_LvlStatus              (void);
void CtrlStp_GetDiagStatus          (void);
void CtrlStp_WriteSignals           (void);

tsCtrlStp_ValidationParameters CtrlStp_ReturnValidationParams(void);

void CtrlStp_SetSignalMode(teCtrlStp_SignalSrc eMode);
void CtrlStp_SetRefRequest(boolean boRefRequst);
void CtrlStp_SetSubModeError(boolean boSubModeErr);
void CtrlStp_SetSlaveRefRequest(boolean boRefRequst);
void CtrlStp_SetSlaveStopRequest(boolean boStopReq);
void CtrlStp_SetSlaveSafetyPosition(boolean boPosReq);
void CtrlStp_SetIgnitionNeeded(boolean boIgnitionReq);

#endif // CTRL_STP_TRANS_2020_07_02_H_

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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

// Headers of the Module
#include <../App/Swc/Ctrl/Dcm/Api/CtrlDcm.h>
#include <CtrlDcmSm.h>
#include <../App/Swc/Ctrl/Dcm/CtrlDcm_Data.h>
#include <UtilUtility.h>

#include "CtrlDcm_RteAccess.h"
#include <Nvm.h>
#include "../Include/_NM_Types.h"

//=============================================================================
// Typedefs
//=============================================================================

// Transition function pointer
typedef boolean(*ptTransitionFctPtrCtrlDcm)(void);


// Transition function informations
typedef struct
{
  CONST_AL teCtrlDcm_eASLPhase       eNewState;
  CONST_AL ptTransitionFctPtrCtrlDcm ptTransitionFct;
} tsTransitionCtrlDcm;

typedef void(*tStateFctPtrCtrlDcm)(void);

typedef struct
{
  CONST_AL uint8                         ucCount;
  CONST_AL tsTransitionCtrlDcm *CONST_AL pTransition;
  CONST_AL tStateFctPtrCtrlDcm           pStateFct;
} tsCtrlDcm_StateMType;

//=============================================================================
// Defines
//=============================================================================

#define CTRLDCM_DIAG_SEQUENCE_TIME_MS 2000u // [ms] time between position commands during sequence
#define CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_NUMERATOR   10
#define CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_DENOMINATOR 6
#define CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_NUMERATOR   6
#define CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_DENOMINATOR 10
#define CTRLDCM_CONFIG_TIME_THRESHOLD 2000U // time needed to set the headlamp fault [ms]
#define CTRLDCM_ZERO_POS              800
#define CTRLDCM_POS_NOMINATOR         300
#define CTRLDCM_POS_DENOMINATOR       600
#define CDDBOOST_Cfg_NbOfChannels   1u

//=============================================================================
// Module global variables
//=============================================================================

extern  tsTransitionCtrlDcm CtrlDcm_asTransitionInit[2];
extern  tsTransitionCtrlDcm CtrlDcm_asTransitionAdj[1];
extern  tsTransitionCtrlDcm CtrlDcm_asTransitionFail[1];

// Transition tables for SLAVE mode
extern  tsTransitionCtrlDcm CtrlDcm_asTransitionInit_Slave[2];

extern  tsTransitionCtrlDcm CtrlDcm_asTransitionAdj_Slave[1];

extern  tsTransitionCtrlDcm CtrlDcm_asTransitionFail_Slave[1];


extern  tsCtrlDcm_StateMType CtrlDcm_atStateMachine_Master[3];


//// State machine table for SLAVE MODE 

extern  tsCtrlDcm_StateMType CtrlDcm_atStateMachine_Slave[3];

boolean boErrorCheck;
boolean boSlaveErrorCheck;
boolean boSlaveRecoveryCheck;
boolean boRecoveryCheck;
sint16 snPosMinASL;
sint16 snPosMaxASL;
NM_ModeType NMMode;
sint16 nSafetyPos;

extern teCtrlDcm_MountingSide    CtrlDcm_eMountingSide;

extern TIMER              CtrlDcm_ulTimeElapsed_us;              // elapsed time used for timer operations
extern TIMER              CtrlDcm_ulTimeElapsedSlave_us;              // elapsed time used for timer operations - slave
extern TIMER              CtrlDcm_ulRecoveryTimeElapsed_us;              // elapsed time used for timer operations
extern TIMER              CtrlDcm_ulRecoveryTimeElapsedSlave_us;              // elapsed time used for timer operations - slave

extern sint16             CtrlDcm_nDiagPos;                  // [0.01deg]  position for diagnostic access

extern uint32             CtrlDcm_ulDiagSequenceTimer;                 // Dcm Sequence Timer for routine control
extern boolean            CtrlDcm_boDiagDcmOn;              // Dcm status for takeover

extern teCtrlDcm_SignalSrc   CtrlDcm_SignalSrc;    // source for DC motor target values
extern boolean               CtrlDcm_boLvlAdjHeadlampFault;
extern boolean               CtrlDcm_boLvlAdjHeadlampFault_R;
extern teCtrlDcm_SensorState CtrlDcm_eSensorError; // pitch error 

extern volatile teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_eCurrentDiagStatep; // current state request in the routine control
// Dcm Sequence 1 for routine control
extern CONST_AL teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_aeDiagSequence1[];
// Dcm Sequence 2 for routine control
extern  CONST_AL teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_aeDiagSequence2[];

extern boolean CtrlDcm_boStop;  // [boolean] hold position
extern sint16  CtrlDcm_nTgtPos;     // [0.01 deg] commanded position
extern boolean CtrlDcm_boSlaveStop; // stop slave movement
extern boolean CtrlDcm_boSlaveSafetyPos; // set slave movement to safety position
extern boolean CtrlDcm_boIgnitionNeeded; // set flag for cases when new ignition is needed

// DC motor request
extern sint16             CtrlDcm_nPosReq;                      // position request
extern sint16             CtrlDcm_nLastPosReq;                      // previous position request

// DC motor operation request based on environmental conditions
extern boolean            CtrlDcm_boConVehIgnition;   // operation request by ConVeh in combination with Light request
extern boolean            CtrlDcm_boTrainingState;   // training state ok if valid value is received from pitch
extern boolean            CtrlDcm_boPowertrainActive;
extern boolean            CtrlDcm_boLvlAdjFuncFault;   // levelling adjust functional fault
extern boolean            CtrlDcm_boSlaveLvlAdjFuncFault;   // levelling adjust functional fault
extern boolean            CtrlDcm_boVehAttitudeInvalid;
extern boolean            CtrlDcm_boDiagLvl;   // DIAG_LVL
extern boolean            CtrlDcm_boStartSequence;    // Dcm Start Sequence Status for routine control


// target values for DC Motor
extern tsCtrlDcm_TargetValues CtrlDcm_TgtAll;

extern tsCtrlDcm_DiagStatus CtrlDcm_DiagStatus; // diagnostic status
extern tsCtrlDcm_ErrorStatus CtrlDcm_sErrorStatus; // Error status from driver
// DC motor control request for routine control
extern tsCtrlDcm_DcMotorRoutineControl CtrlDcm_sDcmControlRequest;

extern tsCtrlDcm_LevellingDiagStatus CtrlDcm_sLevellingDiagStatusFromRightToLeft;
extern tsCtrlDcm_LevellingTgtPos CtrlDcm_sLevellingSignalsFromLeftToRight;

//CtrlDcmSm.c
extern tsCtrlDcm_State CtrlDcm_State;
extern teCtrlDcm_eMainMode CtrlDcm_eMainMode;
extern teCtrlDcm_eASLMode  CtrlDcm_eASLMode;
extern tsCtrlDcm_DcmStatusParameters CtrlDcm_sDcmStatusParams;
boolean boExtTakeOver;
boolean boFirstEntry;
extern CONST_AL tsCtrlDcm_StateMType* CtrlDcm_atStateMachine;


//CtrlDcm_Data.c
extern tNvmPara_AvacStpBlock CtrlDcm_CodingData;
extern sint8 CtrlDcm_scSafety_Position;
extern sint16 CtrlDcm_snMin_ASL_Adjust;
extern sint16 CtrlDcm_snMax_ASL_Adjust;
extern sint8  CtrlDcm_scSafety_Position;
extern tNvmPara_AvacStp_DCMotorData     CtrlDcm_sDCMotorData;

//=============================================================================
// Module function declarations
//=============================================================================

//CtrlDcm.c
extern sint16  CtrlDcm_LimitAngle(uint16 unNegRange, uint16 unPosRange, sint16 nAngle);
extern void    CtrlDcm_ReadStatusSignals(void);
extern void    CtrlDcm_ReadLvlAdjFunctionalFaultStatus(void);
extern void    CtrlDcm_ReadLvlAdjHeadlampFaultStatus(void);
extern void    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery(void);
extern void    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R(void);
extern void    CtrlDcm_ReadEnvironmentSignals(void);
extern void    CtrlDcm_DiagDcmTakeOver(void);
extern void    CtrlDcm_SetDiagRequest(void);
extern void    CtrlDcm_SetDiagPos(void);
extern void    CtrlDcm_WriteValidationFrames(void);
extern teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_DiagSequenceMachine(CONST_AL teCtrlDcm_DcMotorRoutineControlRequest* psData, uint8_least ucLength);

//CtrlDcm_Data.c
extern boolean CtrlDcm_CodingDataReady(teCtrlDcm_MountingSide* pMountingSide);
extern void CtrlDcm_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* pData);
extern boolean Cod_DcmEnable();
extern sint16  Cod_DcmMinAdjASL(void);
extern sint16  Cod_DcmSp(void);

//CtrlDcmSm.c
extern boolean CtrlDcm_CondEnabled(void);
extern boolean CtrlDcm_GetDiagLvl(void);
extern boolean CtrlDcm_RetPowerTrainActive(void);
extern boolean CtrlDcm_ReturnboTrainingState(void);
extern boolean CtrlDcm_ReturnboLvlAdjFuncFault(void);
extern boolean CtrlDcm_ReturnboSlaveLvlAdjFuncFault(void);
extern boolean CtrlDcm_RetVehIgnition(void);
extern boolean CtrlDcm_ReturnboExtTakeOver(void);
extern void    CtrlDcm_DetectSide(void);
extern teCtrlDcm_MountingSide CtrlDcm_ReturnSide(void);
extern boolean CtrlDcm_ReturnboLvlAdjHeadlampFault(void);
extern boolean CtrlDcm_ReturnboLvlAdjHeadlampFault_R(void);
extern teCtrlDcm_SensorState         CtrlDcm_ReturneSensorError(void);
extern void CtrlDcm_GetTgtPos(void);
extern void CtrlDcm_DiagRoutineControl(void);
extern void CtrlDcm_ReadMasterSignals(void);
extern void CtrlDcm_ReadSlaveSignals(void);
extern void CtrlDcm_WriteMasterSignals(void);
extern void CtrlDcm_WriteSlaveSignals(void);
extern void CtrlDcm_ReadCommonSignals(void);
extern void CtrlDcm_SetSignalMode(teCtrlDcm_SignalSrc eMode);
extern void CtrlDcm_SetDiagLvl(boolean boDiagLvl);
extern void CtrlDcm_SetSlaveStopRequest(boolean boStopReq);
extern void CtrlDcm_SetSlaveSafetyPosition(boolean boPosReq);
extern void CtrlDcm_SetFailIgnitionNeeded(boolean boIgnitionReq);

// Transition functions MASTER
extern boolean CtrlDcm_Transition_Init_To_Adj(void);
extern boolean CtrlDcm_Transition_Init_To_Fail(void);
extern boolean CtrlDcm_Transition_Adj_To_Fail(void);
extern boolean CtrlDcm_Transition_Fail_To_Adj(void);

// Transition functions SLAVE
extern boolean CtrlDcm_Transition_Init_To_Adj_Slave(void);
extern boolean CtrlDcm_Transition_Init_To_Fail_Slave(void);
extern boolean CtrlDcm_Transition_Adj_To_Fail_Slave(void);
extern boolean CtrlDcm_Transition_Fail_To_Adj_Slave(void);

// transition functions for submodes
extern boolean CtrlDcm_Transition_Assembly_To_Frozen(void);
extern boolean CtrlDcm_Transition_Assembly_To_Factory(void);
extern boolean CtrlDcm_Transition_Assembly_To_Unavailable(void);
extern boolean CtrlDcm_Transition_Customer_To_Unavailable(void);
extern boolean CtrlDcm_Transition_Customer_To_Available(void);

// local functions
extern void CtrlDcm_DetectMode(void);
extern void CtrlDcm_UseMode(void);
extern void CtrlDcm_UseSubMode(void);
extern void CtrlDcm_ResetDcmState(void);
extern void CtrlDcm_WriteStatusParams(void);
extern void CtrlDcm_HandleFailState(void);
extern void CtrlDcm_HandleFailStateBehavior(teCtrlDcm_FailStateHandling eLeftState, teCtrlDcm_FailStateHandling eRightState);

// local functions SLAVE
extern void CtrlDcm_DetectSlaveSubMode(void);
extern void CtrlDcm_HandleFailState_Slave(void);
extern void CtrlDcm_HandleFailStateBehavior_Slave(teCtrlDcm_FailStateHandling eRightState);

// state machine functions
extern void CtrlDcm_StateMachine_PhaseInit(void);
extern void CtrlDcm_StateMachine_PhaseFail(void);
extern void CtrlDcm_StateMachine_PhaseAdj(void);

// state machine functions SLAVE
extern void CtrlDcm_StateMachine_PhaseInit_Slave(void);
extern void CtrlDcm_StateMachine_PhaseFail_Slave(void);

//CtrlDcm_RteAccess.c
extern uint16 CtrlDcm_RteAccess_ReadSpeed(boolean * boSpeedInvalid);
extern uint8 CtrlDcm_RteAccess_ReadVehicleElectricState(void);
extern uint8 CtrlDcm_RteAccess_ReadVESMainState(void);
extern uint8 CtrlDcm_RteAccess_ReadVehicleModeConfig(void);
extern Std_ReturnType CtrlDcm_RteAccess_Read_EcuSide(teCtrlDcm_MountingSide* eEcuSide);
extern void CtrlDcm_RteAccess_ReadAvacCommand(sint16* snVerticalAngle, boolean* boVehAttitudeInvalid, uint8 ucMountingSide);
extern void CtrlDcm_RteAccess_ReadSensorStatus(teCtrlDcm_SensorState* eSensorState);
extern void CtrlDcm_RteAccess_ReadDriverErrors(tsCtrlDcm_ErrorStatus* eErrorState);
extern void CtrlDcm_RteAccess_ReadLevellingTgtPos(tsCtrlDcm_LevellingTgtPos* sLevellingTgtPos);
extern void CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals);
extern void CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals);
extern void CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(tsCtrlDcm_TargetValues* CtrlDcm_TgtAll);
extern void CtrlDcm_RteAccess_Write_DrvLedDiag_Port(boolean boLvlError);
extern void CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(boolean boLvlError);
extern void CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(tsCtrlDcm_LevellingDiagStatus* sLvlError);
extern void CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0(tsCtrlDcm_DiagStatus* CtrlDcm_ActStatDcm);
extern void CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0(tsCtrlDcm_DiagStatus CtrlDcm_ActStatDcm);
extern void CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(tsCtrlDcm_DcmStatusParameters* sStatusParams);
extern void CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(tsCtrlDcm_DcMotorRoutineControl* psRoutineInfo);
extern void CtrlDcm_RteAccess_WriteDcmRoutineAck(boolean boStatus);
extern void CtrlDcm_RteAccess_MapParams(void);
extern void CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals);

//=============================================================================
// Module function parameter stubs
//=============================================================================

//CtrlDCm.c
boolean CtrlDcm_SetDiagLvl_Param1;
boolean CtrlDcm_SetSlaveStopRequest_Param1;
boolean CtrlDcm_SetSlaveSafetyPosition_Param1;
boolean CtrlDcm_SetFailIgnitionNeeded_Param1;
uint16 CtrlDcm_LimitAngle_Param1;
uint16 CtrlDcm_LimitAngle_Param2;
sint16 CtrlDcm_LimitAngle_Param3;
teCtrlDcm_SignalSrc CtrlDcm_SetSignalMode_Param1;
teCtrlDcm_FailStateHandling CtrlDcm_HandleFailStateBehavior_Slave_Param1;

//CtrlDcm_Data.c
teCtrlDcm_MountingSide CtrlDcm_CodingDataReady_Param1;
tParaFct0_Cmd CtrlDcm_ParaFct0_Param1;
tNvmPara_CodingArea CtrlDcm_ParaFct0_Param2;

//CtrlDcm_RteAccess.c
teCtrlDcm_MountingSide CtrlDcm_RteAccess_Read_EcuSide_Param1;
boolean CtrlDcm_RteAccess_ReadSpeed_Param1;
sint16 CtrlDcm_RteAccess_ReadAvacCommand_Param1;
boolean CtrlDcm_RteAccess_ReadAvacCommand_Param2;
uint8 CtrlDcm_RteAccess_ReadAvacCommand_Param3;
tsCtrlDcm_ErrorStatus CtrlDcm_RteAccess_ReadDriverErrors_Param1;
teCtrlDcm_SensorState CtrlDcm_RteAccess_ReadSensorStatus_Param1;
tsCtrlDcm_LevellingTgtPos CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1;
tsCtrlDcm_LevellingTgtPos CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1;
boolean CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1;
boolean CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1;
tsCtrlDcm_LevellingDiagStatus CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1;
tsCtrlDcm_LevellingTgtPos CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1;
tsCtrlDcm_TargetValues CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues_Param1;
boolean CtrlDcm_RteAccess_WriteDcmRoutineAck_Param1;
tsCtrlDcm_DcmStatusParameters* CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1;
tsCtrlDcm_DiagStatus CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0_Param1;
tsCtrlDcm_DiagStatus CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0_Param1;
tsCtrlDcm_DcMotorRoutineControl CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1;

//CtrlDcmSm.c
teCtrlDcm_FailStateHandling  CtrlDcm_HandleFailStateBehavior_Param1;
teCtrlDcm_FailStateHandling  CtrlDcm_HandleFailStateBehavior_Param2;

//=============================================================================
// Module function return value stubs
//=============================================================================

//CtrlDcm.c
boolean CtrlDcm_GetDiagLvl_RetVal;
sint16 CtrlDcm_LimitAngle_RetVal;
boolean CtrlDcm_CondEnabled_RetVal;
boolean CtrlDcm_RetVehIgnition_RetVal;
boolean CtrlDcm_ReturnboTrainingState_RetVal;
teCtrlDcm_SensorState CtrlDcm_ReturneSensorError_RetVal;
boolean CtrlDcm_ReturnboLvlAdjFuncFault_RetVal;
boolean CtrlDcm_ReturnboSlaveLvlAdjFuncFault_RetVal;
boolean CtrlDcm_ReturnboLvlAdjHeadlampFault_RetVal;
boolean CtrlDcm_ReturnboLvlAdjHeadlampFault_R_RetVal;
boolean CtrlDcm_ReturnboExtTakeOver_RetVal;
boolean CtrlDcm_Transition_Init_To_Fail_RetVal;

//CtrlDcm_Data.c
boolean CtrlDcm_CodingDataReady_RetVal;
sint8 Cod_DcmMinVehAtt_RetVal;
sint8 Cod_DcmMaxVehAtt_RetVal;
sint16 Cod_DcmMinAdjASL_RetVal;
sint16 Cod_DcmMaxAdjASL_RetVal;
sint16 Cod_DcmSp_RetVal;
uint8  Cod_DcmVehAttThrStill_RetVal;
uint8  Cod_DcmFrozenVehSpeedASL_RetVal;
boolean  Cod_DcmEnable_RetVal;
uint8  Cod_DcmVehAttThrMotion_RetVal;
uint8  Cod_DcmMotionDelayASL_RetVal;

//CtrlDcm_RteAccess.c
Std_ReturnType CtrlDcm_RteAccess_Read_EcuSide_RetVal;
uint16 CtrlDcm_RteAccess_ReadSpeed_RetVal;
uint8 CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal;
uint8 CtrlDcm_RteAccess_ReadVESMainState_RetVal;
uint8 CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal;

//CtrlDcmSm.c
boolean CtrlDcm_Transition_Assembly_To_Frozen_RetVal;
boolean CtrlDcm_Transition_Assembly_To_Factory_RetVal;
boolean CtrlDcm_Transition_Assembly_To_Unavailable_RetVal;
boolean CtrlDcm_Transition_Customer_To_Unavailable_RetVal;
boolean CtrlDcm_Transition_Customer_To_Available_RetVal;
boolean CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal;
boolean CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal;
boolean CtrlDcm_Transition_Init_To_Adj_Slave_RetVal;
boolean CtrlDcm_Transition_Init_To_Fail_Slave_RetVal;
boolean CtrlDcm_Transition_Init_To_Adj_RetVal;
boolean CtrlDcm_Transition_Adj_To_Fail_RetVal;
boolean CtrlDcm_Transition_Fail_To_Adj_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_

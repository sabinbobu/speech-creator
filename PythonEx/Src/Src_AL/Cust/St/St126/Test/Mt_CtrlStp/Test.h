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

#include <../Ctrl/Stp/Api/CtrlStp.h>
#include <../Ctrl/Stp/CtrlStp_Core.h>
#include <../Ctrl/Stp/CtrlStp_Data.h>


//=============================================================================
// Typedefs
//=============================================================================

typedef struct
{
  uint16  unLwrAnschlagMi;
  uint16  unLwrAnschlagPl;
  uint16  unLwrMaxWinkelMi;
  uint16  unLwrMaxWinkelPl;
  uint16  unLwrHsZeitAp;
  uint16  unLwrHsZeitSp;
  uint16  unLwrHsZeitMinTt;
  uint16  unLwrHsGrad;
  uint16  unLwrTestDlWeg;
  uint16  unLwrTestDlPeriode;
  sint16  nLwrAp;
  sint16  nLwrSp;
  uint8   ucLwrHsWertStart;
  boolean boLwrEnable;
  boolean boLwrTestDlAktiv;
  uint8   ucLwrWellRefTimeout;
  uint8   ucLwrAutorefZeitversatz;
} tCtrlStp_CodingData;

typedef struct
{
  uint32 ulSimActivated;
  sint16 nSimPosReq;
  uint16 unSimSpeedReq;
  uint8  ucSimCtrSpnEngReq;
} tsCtrlStp_SimData;


//=============================================================================
// Defines
//=============================================================================

#define UTILTIME_MSEC(x) ((TIMER) (   1000UL * UTILTIME_USEC((x))))
#define CTRLSTP_DIAG_SEQUENCE_TIME_MS 2000u 
#define CTRLSTP_TGT_ACT_POS_DIFF 300U 
#define CTRLSTP_AFSOFFSET_COEFFICIENT 1800 
#define CTRLSTP_PIVALUE 314
#define CTRLSTP_HsPosMin               12     
#define CTRLSTP_CONFIG_TIME_THRESHOLD 1000U 
#define CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_NUMERATOR   6
#define CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_DENOMINATOR 10
#define CTRLSTP_SIMULATION_PASSWORD     0xCAFEBABEu
#define CTRLSTP_HsPosInvalid            0

//=============================================================================
// Module global variables
//=============================================================================

extern TIMER              CtrlStp_ulTimeElapsed_us;
extern TIMER              CtrlStp_ulTimeElapsedSlave_us;

extern tsCtrlStp_LevellingDiagStatus CtrlStp_sLevellingDiagStatusFromRightToLeft;
extern tsCtrlStp_LevellingTgtPos CtrlStp_sLevellingSignalsFromLeftToRight;
extern tsCtrlStp_LevellingFeedback CtrlStp_sLevellingFeedbackFromRighToLeft;
extern tNvmPara_AvacStpBlock CtrlStp_CodingData;
extern sint16 CtrlStp_SafetyPos;
extern sint16 CtrlStp_ParkingPos;
extern tsRte_CddStpActual CtrlStp_ActAll;
extern tsCtrlStp_ValidationParameters CtrlStp_Core_sValidationParams;
extern volatile tsCtrlStp_SimData CtrlStp_Simulation_Data;
extern tsCtrlStp_ValidationParameters CtrlStp_sValidationParams;
extern teCtrlStp_eMainMode CtrlStp_eMainMode;
extern tsRte_CtrlStpTarget CtrlStp_TgtAll;
extern boolean CtrlStp_boIsRefDone;
extern boolean CtrlStp_boEntryUnavailable;
//CtrlStp_core.c
extern tieStpTempMode     CtrlStp_eTempMode;
extern boolean CtrlStp_boStop;
extern sint16  CtrlStp_nTgtPos;
extern teCtrlStp_HeadlampFaultStatus CtrlStp_eLvlAdjHeadlampFault_R;
extern teCtrlStp_HeadlampFaultStatus CtrlStp_eLvlAdjHeadlampFault_L;
extern boolean  CtrlStp_boOperationRequest;
extern boolean CtrlStp_boLvlAdjFuncFault;
extern volatile boolean   CtrlStp_boRefRequest;
extern boolean  CtrlStp_boPowertrainActive;
extern sint16   CtrlStp_nPosReq;
extern boolean  CtrlStp_boInscenReq;
extern uint16   CtrlStp_unInscenTimer;
extern sint16   CtrlStp_nInscenPos;
extern teCtrlStp_MountingSide    CtrlStp_eMountingSide;
extern teCtrlStp_SignalSrc CtrlStp_SignalSrc;
extern tsRte_CtrlStpStatusSpinFront CtrlStp_Status;
extern volatile boolean   CtrlStp_boSlaveRefRequest;
extern teCtrlStp_SensorState         CtrlStp_eSensorError;
extern CONST_AL teCtrlStp_StepperRoutineControlRequest CtrlStp_aeDiagSequence1;
extern CONST_AL teCtrlStp_StepperRoutineControlRequest CtrlStp_aeDiagSequence2;
extern boolean CtrlStp_boStartSequence;
extern uint16  CtrlStp_unTgtTmin;
extern boolean CtrlStp_boCurtainAct;
extern boolean CtrlStp_boDiagRefComplete;
extern boolean CtrlStp_boElecSC;
extern boolean CtrlStp_boIgnitionNeeded;
extern boolean CtrlStp_boElecOL;
extern tCtrlStp_AvacStp_SwGeo     CtrlStp_sHeadlampGeo;
extern boolean            CtrlStp_boStepLossCurrentSide;
extern boolean            CtrlStp_boStepLossRightSide;
extern boolean            CtrlStp_boCurtainDeAct;
extern boolean CtrlStp_boSlaveSafetyPos;
//CtrlStp_util.c
extern boolean CtrlStp_boConVehIgnition;
extern teCtrlStp_eSubMode  CtrlStp_eSubMode;
extern tsCtrlStp_State CtrlStp_State;
extern tsRte_CddStpActual CtrlStp_ActAll;
extern boolean  CtrlStp_boSlaveLvlAdjFuncFault;
extern volatile boolean   CtrlStp_boRefRequest;
extern boolean CtrlStp_boRefReady;
extern uint16  CtrlStp_unRefDelayCnt;
extern sint16  CtrlStp_snOffsetCorrection;
extern tsCtrlStp_DiagStatus CtrlStp_DiagStatus;
extern sint16  CtrlStp_nDiagPos;
extern boolean CtrlStp_boSlaveStop;
extern volatile teCtrlStp_StepperRoutineControlRequest CtrlStp_eCurrentDiagState;
extern tsCtrlStp_StepperRoutineControl CtrlStp_sStpControlRequest;
extern boolean  CtrlStp_boDiagStpOn;
extern boolean  CtrlStp_boOperationStatus;
extern boolean  CtrlStp_boSubModeError;
extern tsCtrlStp_ValidationParameters CtrlStp_Core_sValidationParams;
extern boolean CtrlStp_boTrainingState;
extern boolean CtrlStp_boOperationRequest;
extern sint16  CtrlStp_nOffset;
extern uint32  CtrlStp_ulDiagSequenceTimer;
extern boolean CtrlStp_boVehAttitudeInvalid;
extern boolean CtrlStp_StartDiagLvlTimer;
uint8_least ucIndx;
teCtrlStp_StepperRoutineControlRequest eReturnState;
boolean boErrorCheck;
boolean boSlaveErrorCheck;
uint16  CtrlStp_unCnt;
boolean         boLwrApVz;
boolean         boLwrSpVz;
teCtrlStp_EtatFee ePreviousValue;


//=============================================================================
// Module function declarations
//=============================================================================

/*CtrlStp_RteAccess.h*/
extern void CtrlStp_RteAccess_ReadSensorStatus(teCtrlStp_SensorState* eSensorState);
extern void CtrlStp_RteAccess_WriteStpRoutineAck(boolean boStatus);
extern void CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(tsRte_CtrlStpTarget* CtrlStp_TgtAll);
extern void CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port(tsCtrlStp_LevellingFeedback* tsLevellingFeedback);
extern void CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(tsCtrlStp_LevellingFeedback* tsLevellingFeedback);
extern void CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port(tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus);
extern void CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus);
extern void CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port(tsCtrlStp_LevellingTgtPos* tsLevellingSignals);
extern void CtrlStp_RteAccess_Write_DrvLedDiag_Port(boolean boLvlError);
extern void CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(tsCtrlStp_LevellingTgtPos* tsLevellingSignals);
extern void CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues(tsRte_CddStpActual* CtrlStp_ActAll);
extern void CtrlStp_RteAccess_MapParams(void);
extern Std_ReturnType CtrlStp_RteAccess_Read_EcuSide(teCtrlStp_MountingSide* eEcuSide);
extern void CtrlStp_RteAccess_ReadLevellingTgtPos(tsCtrlStp_LevellingTgtPos* sLevellingTgtPos);
extern uint8 CtrlStp_RteAccess_ReadAFSMode(void);
extern uint8 CtrlStp_RteAccess_ReadGfhbCmd(void);
extern uint8 CtrlStp_RteAccess_ReadHbCmd(void);
extern uint16 CtrlStp_RteAccess_ReadSpeed(boolean* boSpeedInvalid);
extern uint8 CtrlStp_RteAccess_ReadVehicleElectricState(void);
extern uint8 CtrlStp_RteAccess_ReadVESMainState(void);
extern void CtrlStp_RteAccess_ReadLevellingFeedback(tsCtrlStp_LevellingFeedback* sLevellingFeedback);
extern void CtrlStp_RteAccess_ReadAvacCommand(sint16* snVerticalAngle, boolean* boVehAttitudeInvalid, uint8 ucMountingSide);
extern uint8 CtrlStp_RteAccess_ReadVehicleModeConfig(void);
extern void CtrlStp_RteAccess_ReadLevellingDiagStatus(tsCtrlStp_LevellingDiagStatus* sLevellingDiagStatus);
extern uint8 CtrlStp_RteAccess_ReadLbBoostAllowed(void);
extern teCtrlStp_EtatFee CtrlStp_RteAccess_ReadElectricalSuppState(void);
extern void CtrlStp_RteAccess_ReadDiagStpControlRoutine(tsCtrlStp_StepperRoutineControl* psRoutineInfo);
extern void CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(tsCtrlStp_DiagStatus CtrlStp_ActStatStp);
extern void CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(tsCtrlStp_ValidationParameters* sValidationParams);

//CtrlStp_Data.c
extern boolean CtrlStp_CodingDataReady(teCtrlStp_MountingSide* pMountingSide);
extern void CtrlStp_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* pData);
extern uint16  Cod_LwrAnschlagMi(void);
extern uint16  Cod_LwrAnschlagPl(void);
extern uint16  Cod_LwrMaxWinkelMi(void);
extern uint16  Cod_LwrMaxWinkelPl(void);
extern sint16  Cod_LwrAp(void);
extern sint16  Cod_LwrSp(void);
extern uint16  Cod_LwrHsZeitAp(void);
extern uint16  Cod_LwrHsZeitMinTt(void);
extern boolean Cod_LwrEnable(void);
extern uint16  Cod_LwrHsGrad(void);
extern uint8   Cod_LwrHsWertStart(void);
extern boolean Cod_LwrTestDlAktiv(void);
extern uint16  Cod_LwrTestDlWeg(void);
extern uint16  Cod_LwrTestDlPeriode(void);
extern uint8   Cod_LwrWellRefTimeout(void);
extern uint8   Cod_LwrAutorefZeitversatz(void);

extern sint16  Cod_AfsLevellingHBOffset(void);
extern sint16  Cod_AfsLevellingTownPedOffset(void);
extern sint16  Cod_AfsLevellingMWBoostOffset(void);
extern sint16  Cod_AfsLevellingMWOffset(void);
extern sint16  Cod_AfsLevellingLeftBdwLhdOffset(void);
extern sint16  Cod_AfsLevellingLeftBdwRhdOffset(void);
extern sint16  Cod_AfsLevellingLeftFoggyLhdOffset(void);
extern sint16  Cod_AfsLevellingLeftFoggyRhdOffset(void);
extern sint16  Cod_AfsLevellingOffOffset(void);
extern uint8   Cod_AfsLevellingHBAperture(void);
extern uint8   Cod_AfsLevellingGFHBOffAngSpd(void);
extern uint8   Cod_AfsLevellingGFHBOffSgmDim(void);
extern uint8   Cod_AfsLevellingGFHBOnAngSpd(void);
extern uint8   Cod_AfsLevellingGFHBOnSgmDim(void);
extern uint16  Cod_AfsLevellingCorrectSpeed(void);
extern uint16  Cod_LwrMaxRefSpeed(void);
extern uint16  Cod_LwrSttDelay(void);


//CtrlStp_util.c
extern sint16 CtrlStp_Angle2StpPos(uint16 unTransmFactor, uint16 unOffset, sint16 nAngle);
extern sint16 CtrlStp_CheckForStart(uint8 ucThresh, boolean boMoving, sint16 nOldPos, sint16 nNewPos);
extern sint16 CtrlStp_LimitAngle(uint16 unNegRange, uint16 unPosRange, sint16 nAngle);
extern uint16 CtrlStp_Speed2Tmin(uint16 unTransmFactor, uint16 unSpeed);
extern uint16 CtrlStp_Tmin2Speed(uint16 unTransmFactor, uint16 unTmin);
extern sint16 CtrlStp_StpPos2Angle(uint16 unTransmFactor, uint16 unOffset, sint16 nStpPos);

//CtrlStp.c
extern teCtrlStp_StatMain CtrlStp_GetStateValue(void);
extern boolean CtrlStp_Transition_Init_To_Adj_Slave(void);
extern boolean CtrlStp_Transition_Ref_To_Adj_Slave(void);
extern boolean CtrlStp_Transition_Ref_To_Fail_Slave(void);
extern boolean CtrlStp_Transition_Fail_To_Ref_Slave(void);
extern boolean CtrlStp_Transition_Fail_To_Adj_Slave(void);
extern boolean CtrlStp_Transition_Adj_To_Ref_Slave(void);
extern boolean CtrlStp_Transition_Adj_To_Fail_Slave(void);
extern void CtrlStp_ResetStpState(void);
extern void CtrlStp_DetectMode(void);

extern void CtrlStp_Proccess_Reference(void);
extern void CtrlStp_StateMachine_StateRef(void);
extern void CtrlStp_StateMachine_StateAdj(void);
extern void CtrlStp_StateMachine_StateInit(void);
extern void CtrlStp_StateMachine_StateSTT(void);
extern void CtrlStp_StateMachine_StateFail(void);

extern void CtrlStp_StMch(void);

extern boolean CtrlStp_Transition_Customer_To_Aftersale(void);
extern boolean CtrlStp_Transition_Customer_To_Available(void);
extern boolean CtrlStp_Transition_Customer_To_Unavailable(void);
extern boolean CtrlStp_Transition_Assembly_To_Unavailable(void);
extern boolean CtrlStp_Transition_Assembly_To_Factory(void);
extern  boolean CtrlStp_Transition_Assembly_To_Frozen(void);
extern boolean CtrlStp_Transition_STT_To_Adj(void);
extern boolean CtrlStp_Transition_STT_To_Ref(void);
extern boolean CtrlStp_Transition_Fail_To_Adj(void);
extern boolean CtrlStp_Transition_Fail_To_Ref(void);
extern boolean CtrlStp_Transition_Ref_To_Fail(void);
extern boolean CtrlStp_Transition_Ref_To_Adj(void);
extern boolean CtrlStp_Transition_Adj_To_STT(void);
extern boolean CtrlStp_Transition_Adj_To_Fail(void);
extern boolean CtrlStp_Transition_Ref_To_STT(void);
extern boolean CtrlStp_Transition_Init_To_Fail(void);
extern boolean CtrlStp_Transition_Init_To_Ref(void);
extern void CtrlStp_ModeCustomer(void);
extern void CtrlStp_ModeAssembly(void);
extern  void CtrlStp_SubModeFrozen(void);
extern  void CtrlStp_SubModeFactory(void);
extern void CtrlStp_SubModeUnavailable(void);
extern void CtrlStp_SubModeAfterSale(void);
extern void CtrlStp_VerifyAndProcessRefRun(void);
extern void CtrlStp_WriteValidationParams(void);
extern void CtrlStp_UseMode(void);
extern void CtrlStp_Init(void);
extern void CtrlStp_UseSubMode(void);
extern void rpCtrlStp_Cycle(void);
extern void CtrlStp_HandleDiagLvl(boolean boStepLossErr);
extern void riCtrlStpInit(void);

//CddStp module
Std_ReturnType roCddStpOff(void);
Std_ReturnType roCddStpOn(void);
void roCddStpStartRefRun(tieStepperIndex stepperIndex, ti16StepperPosition_halfsteps position);
extern LEIM_TE_CurrentEIMode EAPI_GetCurrentEIMode(void);

//CtrlStp_core.c
extern tsCtrlStp_ValidationParameters CtrlStp_ReturnValidationParams(void);
extern boolean CtrlStp_GetDiagLvl(void);
extern teCtrlStp_CmdRefSiteD CtrlStp_GetCmdRef(void);
extern boolean CtrlStp_isSafetyPosReached(void);
extern void CtrlStp_SetIgnitionNeeded(boolean boIgnitionReq);
extern boolean CtrlStp_CondRefUpCompl(void);
extern teCtrlStp_HeadlampFaultStatus CtrlStp_ReturneLvlAdjHeadlampFault_R(void);
extern boolean CtrlStp_RefRequest(void);
extern boolean CtrlStp_ReturnboSlaveLvlAdjFuncFault(void);
extern boolean CtrlStp_RetPowerTrainActive(void);

extern void CtrlStp_InscenationStop(void);
extern void CtrlStp_InscenationStart(void);
extern boolean CtrlStp_CondIsReady(void);
extern void CtrlStp_SetSlaveRefRequest(boolean boRefRequst);
extern teCtrlStp_MountingSide CtrlStp_ReturnSide(void);
extern void CtrlStp_SetSignalMode(teCtrlStp_SignalSrc eMode);
extern void CtrlStp_EntryRefDn(void);
extern void CtrlStp_StartRef(void);
extern void CtrlStp_SetRefRequest(boolean boRefRequst);
extern void CtrlStp_SetSlaveRefRequest(boolean boRefRequst);
extern boolean CtrlStp_CondStepLoss(void);
extern void CtrlStp_EntryNorm(void);
extern void CtrlStp_SetSlaveStopRequest(boolean boStopReq);
extern void CtrlStp_DoNorm(void);
extern void CtrlStp_EntryInit(void);
extern void CtrlStp_SetSubModeError(boolean boSubModeErr);
extern void CtrlStp_EntryOff(void);
extern teCtrlStp_SensorState CtrlStp_ReturneSensorError(void);
extern boolean CtrlStp_ReturnboTrainingState(void);
extern boolean CtrlStp_ReturnboLvlAdjFuncFault(void);
extern boolean CtrlStp_IsMoving(void);
extern void CtrlStp_DetectSide(void);
extern void CtrlStp_ReadStatusSignals(void);
extern boolean CtrlStp_CondEnabled(void);
extern boolean CtrlStp_CondOperationRequest(void);
extern boolean CtrlStp_GetSubModeErr(void);
extern boolean CtrlStp_CondOperationStatus(void);
extern boolean CtrlStp_ReturnboExtTakeOver(void);
extern void CtrlStp_ReadParam(void);
extern void CtrlStp_DiagRoutineControl(void);
extern void CtrlStp_SetDiagPos(void);
extern void CtrlStp_SetDiagRequest(void);
extern void CtrlStp_ElecDiagStat(void);
extern boolean CtrlStp_DetectAfsOffsetCurtainActivation(uint8 ucGfhbCmd);
extern boolean CtrlStp_DetectAfsOffsetCurtainDeactivation(uint8 ucGfhbCmd, boolean boHighBeamCmd);
extern sint16 CtrlStp_GetContinMove(void);
extern uint16 CtrlStp_TempCheck(uint16 unTmin);
extern void CtrlStp_ReadCommonSignals(void);
extern void CtrlStp_PosDiagStat(void);
extern void CtrlStp_DiagStpTakeOver(void);
extern void CtrlStp_LvlStatus(void);
extern void CtrlStp_EntryDis(void);
extern 	void CtrlStp_EntryErr(void);
extern void CtrlStp_GetOffset(uint8 ucAfsModeCmd, boolean boLowBeamBoostAllowed, boolean boHighBeamCmd);
extern void CtrlStp_ApplyOffset(sint16 snLastOffset, sint16 snActualOffset, uint8 ucGfhbCmd, boolean boHighBeamCmd);
extern void CtrlStp_GetDiagStatus(void);
extern teCtrlStp_StepperRoutineControlRequest CtrlStp_DiagSequenceMachine(CONST_AL teCtrlStp_StepperRoutineControlRequest* psData, uint8_least ucLength);
extern void CtrlStp_CheckFrame350Recovery(void);
extern void CtrlStp_ReadEnvironmentSignals(void);
extern void CtrlStp_ReadLvlAdjFunctionalFaultStatus(void);
extern void CtrlStp_DetectSlaveSubMode(void);
extern void CtrlStp_ReadLvlAdjHeadlampFaultStatus(void);
extern void CtrlStp_ReadSlaveSignals(void);
extern void CtrlStp_ReadMasterSignals(void);
extern void CtrlStp_WriteSlaveSignals(void);
extern void CtrlStp_GetTgtPos(void);
extern void CtrlStp_WriteMasterSignals(void);
extern void CtrlStp_SetTgtTmin(void);
extern void CtrlStp_DetectOffset(void);
extern boolean CtrlStp_GetElecIntStopCondition(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

tsCtrlStp_ValidationParameters* CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_Param1;
tsCtrlStp_DiagStatus* CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1;
boolean                                              CtrlStp_SetRefRequest_Param1;
boolean                                              CtrlStp_SetSlaveRefRequest_Param1;
teCtrlStp_FailStateHandling                          CtrlStp_HandleFailStateBehavior_Slave_Param1;
teCtrlStp_FailStateHandling                          CtrlStp_HandleFailStateBehavior_Param1;
teCtrlStp_FailStateHandling                          CtrlStp_HandleFailStateBehavior_Param2;
teCtrlStp_SignalSrc                                  CtrlStp_SetSignalMode_Param1;
boolean                                              CtrlStp_SetSubModeError_Param1;
boolean                                              CtrlStp_SetSlaveSafetyPosition_Param1;
uint8                                                CtrlStp_CheckForStart_Param1;
boolean                                              CtrlStp_CheckForStart_Param2;
sint16                                               CtrlStp_CheckForStart_Param3;
sint16                                               CtrlStp_CheckForStart_Param4;
uint16                                               CtrlStp_Angle2StpPos_Param1;
uint16                                               CtrlStp_Angle2StpPos_Param2;
sint16                                               CtrlStp_Angle2StpPos_Param3;
sint16                                               CtrlStp_Angle2StpPos_Param4;
tsRte_CtrlStpTarget* CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues_Param1;
teCtrlStp_SensorState                                CtrlStp_RteAccess_ReadSensorStatus_Param1;
boolean* CtrlStp_RteAccess_Read_350Lost_Status_Param1;
boolean                                              CtrlStp_RteAccess_Read_350Lost_Status_Param2;
boolean                                              CtrlStp_RteAccess_WriteStpRoutineAck_Param1;
tsRte_SysMon_LifePhases                              CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1;
boolean* CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2;
tsCtrlStp_LevellingFeedback* CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param1;
tsRte_LevellingFeedback                              CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2;
tsCtrlStp_LevellingFeedback* CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param1;
tsRte_LevellingFeedback                              CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param2;
tsCtrlStp_LevellingDiagStatus* CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param1;
tsRte_LevellingDiagStatus                            CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2;
tsCtrlStp_LevellingDiagStatus* CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1;
tsRte_LevellingDiagStatus                            CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param2;
tsCtrlStp_LevellingTgtPos* CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param1;
tsRte_LevellingTgtPos                                CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2;
boolean                                              CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1;
tsRte_Hs6_Diag_Drvled_L_457                          CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2;
tsCtrlStp_LevellingTgtPos* CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1;
tsRte_LevellingTgtPos                                CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2;
tsRte_CddStpActual* CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues_Param1;
tsRteCodingParameters                                CtrlStp_RteAccess_MapParams_Param1;
teCtrlStp_MountingSide* CtrlStp_RteAccess_Read_EcuSide_Param1;
teRte_MountingSide                                   CtrlStp_RteAccess_Read_EcuSide_Param2;
tsCtrlStp_LevellingTgtPos* CtrlStp_RteAccess_ReadLevellingTgtPos_Param1;
tsRte_LevellingTgtPos                                CtrlStp_RteAccess_ReadLevellingTgtPos_Param2;
tsRte_SysMonAfsSignals                               CtrlStp_RteAccess_ReadAFSMode_Param1;
uint8                                                CtrlStp_RteAccess_ReadAFSMode_Param2;
tsRte_SysMonAfsSignals                               CtrlStp_RteAccess_ReadGfhbCmd_Param1;
uint8                                                CtrlStp_RteAccess_ReadGfhbCmd_Param2;
tsRte_SysMonLgtFctsReq                               CtrlStp_RteAccess_ReadHbCmd_Param1;
uint8                                                CtrlStp_RteAccess_ReadHbCmd_Param2;
tsRte_SigPrep_DynamicSigs                            CtrlStp_RteAccess_ReadPedalAccelerationd_Param1;
uint8                                                CtrlStp_RteAccess_ReadPedalAccelerationd_Param2;
tsRte_SigPrep_DynamicSigs                            CtrlStp_RteAccess_ReadDriverRequest_Param1;
uint8                                                CtrlStp_RteAccess_ReadDriverRequest_Param2;
tsRte_SigPrep_DynamicSigs                            CtrlStp_RteAccess_ReadBrakePressure_Param1;
uint8                                                CtrlStp_RteAccess_ReadBrakePressure_Param2;
tsRte_SigPrep_YawSpeed                               CtrlStp_RteAccess_ReadCylinderPressure_Param1;
uint16                                               CtrlStp_RteAccess_ReadCylinderPressure_Param2;
boolean                                              CtrlStp_RteAccess_ReadSpeed_Param1;
tsRte_SysMon_VehicleSpeed                            CtrlStp_RteAccess_ReadSpeed_Param2;
uint16                                               CtrlStp_RteAccess_ReadSpeed_Param3;
tsRte_SysMon_VehNetState                             CtrlStp_RteAccess_ReadVehicleElectricState_Param1;
uint8                                                CtrlStp_RteAccess_ReadVehicleElectricState_Param2;
tsRte_SysMon_VehNetState                             CtrlStp_RteAccess_ReadVESMainState_Param1;
uint8                                                CtrlStp_RteAccess_ReadVESMainState_Param2;
sint16* CtrlStp_RteAccess_ReadAvacCommand_Param1;
boolean* CtrlStp_RteAccess_ReadAvacCommand_Param2;
uint8                                                CtrlStp_RteAccess_ReadAvacCommand_Param3;
tsPositionOut                                        CtrlStp_RteAccess_ReadAvacCommand_Param4;
tsRte_SigPrep_VehicleConfigSig                       CtrlStp_RteAccess_ReadVehicleModeConfig_Param1;
uint8                                                CtrlStp_RteAccess_ReadVehicleModeConfig_Param2;
tsCtrlStp_LevellingFeedback                          CtrlStp_RteAccess_ReadLevellingFeedback_Param1;
tsRte_LevellingFeedback                              CtrlStp_RteAccess_ReadLevellingFeedback_Param2;
tsCtrlStp_LevellingDiagStatus* CtrlStp_RteAccess_ReadLevellingDiagStatus_Param1;
tsRte_LevellingDiagStatus                            CtrlStp_RteAccess_ReadLevellingDiagStatus_Param2;
tsRte_SysMonAfsSignals                               CtrlStp_RteAccess_ReadLbBoostAllowed_Param1;
uint8                                                CtrlStp_RteAccess_ReadLbBoostAllowed_Param2;
tsCtrlStp_StepperRoutineControl                      CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1;
tsCtrlStp_DiagStatus                                 CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1;
tsRte_ActStatStp0                                    CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param2;
tsRte_SigPrep_ElecSupState                           CtrlStp_RteAccess_ReadElectricalSuppState_Param1;
teCtrlStp_EtatFee                                    CtrlStp_RteAccess_ReadElectricalSuppState_Param2;
uint8_least                                          CtrlStp_DiagSequenceMachine_Param2;
teCtrlStp_StepperRoutineControlRequest* CtrlStp_DiagSequenceMachine_Param1;
//CtrlStp_Data.c
teCtrlStp_MountingSide                               CtrlStp_CodingDataReady_Param1;
tParaFct0_Cmd                                        CtrlStp_ParaFct0_Param1;
tNvmPara_CodingArea* CtrlStp_ParaFct0_Param2;
uint8                                                CtrlStp_ParaFct0_ucLwrTestDlPeriode;
uint8                                                CtrlStp_ParaFct0_ucLwrApWert;
uint8                                                CtrlStp_ParaFct0_ucLwrSpWert;
boolean                                              CtrlStp_ParaFct0_boLwrApVz;
boolean                                              CtrlStp_ParaFct0_boLwrSpVz;
sint16                                               CtrlStp_InscenationNextTarget_Param1;
uint16                                               CtrlStp_InscenationNextTarget_Param2;
sint16                                               CtrlStp_Angle2StpPos_Param3;
sint16                                               CtrlStp_Angle2StpPos_Param4;
uint8                                                CtrlStp_GetOffset_Param1;
uint8                                                CtrlStp_GetOffset_Param2;
boolean                                              CtrlStp_GetOffset_Param3;
sint16                                               CtrlStp_ApplyOffset_Param1;
sint16                                               CtrlStp_ApplyOffset_Param2;
uint8                                                CtrlStp_ApplyOffset_Param3;
boolean                                              CtrlStp_ApplyOffset_Param4;
sint16                                               snOffsetPercentage;
uint16                                               CtrlStp_TempCheck_Param1;
uint8                                                CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1;
boolean                                              CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2;
uint8                                                CtrlStp_DetectAfsOffsetCurtainActivation_Param1;
boolean                                              CtrlStp_CodingDataReady_Param2;//FALSE
boolean                                              CtrlStp_SetSlaveStopRequest_boStopReq_Param1;
teCtrlStp_MountingSide                               CtrlStp_StateMachine_StateInit_Param1;
sint16                                               roCtrlStp_LwrInscenation0NextTarget_Param1;
uint16                                               roCtrlStp_LwrInscenation0NextTarget_Param2;
boolean                                              CtrlStp_DetectSlaveSubMode_Param1;
uint16                                               CtrlStp_StpPos2Angle_Param1;
uint16                                               CtrlStp_StpPos2Angle_Param2;
sint16                                               CtrlStp_StpPos2Angle_Param3;
sint32                                               CtrlStp_StpPos2Angle_Param4;
uint16                                               CtrlStp_StpPos2Angle_Param5;
uint16                                               CtrlStp_Tmin2Speed_Param1;
uint16                                               CtrlStp_Tmin2Speed_Param2;
uint16                                               CtrlStp_Speed2Tmin_Param1;
uint16                                               CtrlStp_Speed2Tmin_Param2;
uint16                                               CtrlStp_LimitAngle_Param1;
uint16                                               CtrlStp_LimitAngle_Param2;
sint16                                               CtrlStp_LimitAngle_Param3;
sint16                                               CtrlStp_LimitAngle_Param4;
sint16                                               CtrlStp_LimitAngle_Param5;
boolean                                              CtrlStp_HandleDiagLvl_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean                                              CtrlStp_CodingDataReady_RetVal;
teCtrlStp_StepperRoutineControlRequest               CtrlStp_DiagSequenceMachine_RetVal;
teCtrlStp_MountingSide                               CtrlStp_ReturnSide_RetVal;
sint16                                               CtrlStp_Angle2StpPos_RetVal;
sint16                                               CtrlStp_StpPos2Angle_RetVal;
uint16                                               CtrlStp_Tmin2Speed_RetVal;
tsCtrlStp_ValidationParameters                       CtrlStp_ReturnValidationParams_RetVal;
boolean                                              CtrlStp_CondIsReady_RetVal;
boolean                                              CtrlStp_CondRefDnCompl_RetVal;
boolean                                              CtrlStp_CondRefInProgress_RetVal;
boolean                                              CtrlStp_RefRequest_RetVal;
boolean                                              CtrlStp_RetPowerTrainActive_RetVal;
boolean                                              CtrlStp_RetVehIgnition_RetVal;
boolean                                              CtrlStp_ReturnboTrainingState_RetVal;
boolean                                              CtrlStp_ReturnboLvlAdjFuncFault_RetVal;
boolean                                              CtrlStp_ReturnboSlaveLvlAdjFuncFault_RetVal;
teCtrlStp_HeadlampFaultStatus                        CtrlStp_ReturneLvlAdjHeadlampFault_L_RetVal;
teCtrlStp_HeadlampFaultStatus                        CtrlStp_ReturneLvlAdjHeadlampFault_R_RetVal;
teCtrlStp_SensorState                                CtrlStp_ReturneSensorError_RetVal;
boolean                                              CtrlStp_DetectElecTransition_RetVal;
boolean                                              CtrlStp_DetectElecTransitionSttToAdj_RetVal;
boolean                                              CtrlStp_DetectElecTransitionSttToRef_RetVal;
boolean                                              CtrlStp_isSafetyPosReached_RetVal;
boolean                                              CtrlStp_Transition_Init_To_Ref_RetVal1;
boolean                                              CtrlStp_Transition_Init_To_Fail_RetVal1;
boolean                                              CtrlStp_Transition_Ref_To_STT_RetVal1;
boolean                                              CtrlStp_Transition_Adj_To_Fail_RetVal1;
boolean                                              CtrlStp_Transition_Adj_To_STT_RetVal1;
boolean                                              CtrlStp_Transition_Ref_To_Adj_RetVal1;
boolean                                              CtrlStp_Transition_Ref_To_Fail_RetVal1;
boolean                                              CtrlStp_Transition_Fail_To_Ref_RetVal1;
boolean                                              CtrlStp_Transition_Fail_To_Adj_RetVal1;
boolean                                              CtrlStp_Transition_STT_To_Ref_RetVal1;
boolean                                              CtrlStp_Transition_STT_To_Adj_RetVal1;
boolean                                              CtrlStp_Transition_Assembly_To_Frozen_RetVal1;
boolean                                              CtrlStp_Transition_Assembly_To_Factory_RetVal1;
boolean                                              CtrlStp_Transition_Assembly_To_Unavailable_RetVal1;
boolean                                              CtrlStp_Transition_Customer_To_Unavailable_RetVal1;
boolean                                              CtrlStp_Transition_Customer_To_Available_RetVal1;
boolean                                              CtrlStp_Transition_Customer_To_Aftersale_RetVal1;
boolean                                              CtrlStp_Transition_Ref_To_Adj_Slave_boReturn;
boolean                                              CtrlStp_Transition_Init_To_Adj_Slave_RetVal;
boolean                                              CtrlStp_Detect_StepLoss_Recovery_RetVal;
boolean                                              CtrlStp_GetDiagLvl_RetVal;
teCtrlStp_CmdRefSiteD                                CtrlStp_GetCmdRef_RetVal;
boolean                                              CtrlStp_CondRefDelay_RetVal1;
uint8                                                CtrlStp_TempCheck_RetVal1;
uint8                                                CtrlStp_GetContinMove_RetVal1;
boolean                                              CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1;
boolean                                              CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1;
boolean                                              CtrlStp_CondParamReady_boCodingDataReady_RetVal1;
boolean                                              CtrlStp_CondEnabled_RetVal;
boolean                                              CtrlStp_CondOperationRequest_RetVal;
boolean                                              CtrlStp_GetSubModeErr_RetVal;
boolean                                              CtrlStp_CondOperationStatus_RetVal;
boolean                                              CtrlStp_ReturnboExtTakeOver_RetVal;
boolean                                              CtrlStp_IsMoving_RetVal1;
uint8                                                CtrlStp_RteAccess_ReadAFSMode_RetVal;
uint8                                                CtrlStp_RteAccess_ReadGfhbCmd_RetValue;
uint8                                                CtrlStp_RteAccess_ReadHbCmd_RetValue;
uint16                                               CtrlStp_Speed2Tmin_RetVal;
uint16                                               CtrlStp_Tmin2Speed_RetVal;
uint8                                                CtrlStp_RteAccess_ReadVehicleElectricState_Retval;
uint8                                                CtrlStp_RteAccess_ReadVESMainState_RetVal;
uint8                                                CtrlStp_RteAccess_ReadLbBoostAllowed_RetVal;
boolean                                              CtrlStp_Transition_Adj_To_Fail_Slave_boReturn;
boolean                                              CtrlStp_Transition_Adj_To_Ref_Slave_boReturn;
boolean                                              CtrlStp_Transition_Fail_To_Adj_Slave_boReturn;
boolean                                              CtrlStp_Transition_Fail_To_Ref_Slave_boReturn;
boolean                                              CtrlStp_Transition_Ref_To_Fail_Slave_boReturn;
Std_ReturnType                                       CtrlStp_RteAccess_Read_EcuSide_RetVal;
boolean                                              CtrlStp_GetElecIntStopCondition_RetVal;


//=============================================================================
// Module static variables inside functions 
//=============================================================================


#endif // TEST_2023_08_25_H_

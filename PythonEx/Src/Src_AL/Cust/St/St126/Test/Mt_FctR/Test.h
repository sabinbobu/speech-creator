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
#include <ctaaFctR.h>
#include <FctR.h>
#include <FctR_Data.h>
#include <FctR_RteAccess.h>
#include <FctR_Tgt.h>
#include <FctR_TgtPrep.h>

//=============================================================================
// Typedefs
//=============================================================================

//FctR_Tgt.c
// Two pairs of (Light Function, Priority).
typedef struct
{
  tAppLightFunction ucLgtFct1;  // light functions without Active bit
  tAppLightFunction ucLgtFct2;  // light functions with Active bit
  uint8 ucPrio1;                // light functions without Active bit
  uint8 ucPrio2;                // light functions with Active bit
}tPrioLgtFctPair;

typedef struct
{
  //input
  boolean boReq_Input;
  TIMER ulTimeMs_Input;
  //internal
  TIMER ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsFctR_TimerCfg;


typedef struct
{
  //input
  boolean boDiagEntryCmd; //status used for diag enable
  boolean boError; //status of electrical error or other errors like timeout to perform diag (OK/NOK)
  //timer settings
  TIMER   ulTime; //timer value
  sint8   cSelectTimer; //timer selection for different light function
  //store previous state of lightfunction
  boolean boPrvCmd;
}tsDiagFeedback_Cfg;

//=============================================================================
// Defines
//=============================================================================

// Fctr_Tgt.c
#define FCTR_LB_FAULT_DETECTION     0
#define FCTR_SBL_FAULT_DETECTION    1
#define FCTR_HB_FAULT_DETECTION     2
#define FCTR_TI_BLINKING_DETECTION  3
#define FCTR_POS_FAULT_DETECTION    4
#define FCTR_DRL_FAULT_DETECTION    5
#define FCTR_NUMBER_OF_TIMERS (FCTR_DRL_FAULT_DETECTION + 1) //number of timers

#define FCTR_AIM_COUNTER            10u  // counter for nb of blinks (ON/OFF) 
#define FCTR_INVALID_TIMER_CONFIG   0xFFU //invalid configuration for Timers

//=============================================================================
// Module global variables
//=============================================================================

// FctR_Data.c
extern tNvmPara_CodingArea*  FctR_pCodingArea;
extern tNvmPara_LmmABlock*   FctR_pLmmABlock;
extern uint8                 FctR_ucCodingState;
// LMM basic state
extern tsFctR_LmmInitBlock   FctR_LmmInit;
extern tuFctR_LgtFct         FctR_FailureIndicationLogLmpBDemMask;
extern tuFctR_LogLmp         FctR_DisableLogLmpLgtFctB[FCTR_CFG_LGTFCT_MAX];
extern tuFctR_LogLmp         FctR_FailureReactionLogLmpBTable[FCTR_CFG_LGTFCT_MAX];
extern tuFctR_LogLmp         FctR_UsageLogLmpBTable[FCTR_CFG_LGTFCT_MAX];
extern tuFctR_LogLmp         FctR_AccessLogLmpBTable[FCTR_CFG_LGTFCT_MAX];

// FctR_Tgt.c
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
extern tsFctR_ChLutType FctR_ChLut[FCTR_CFG_LGTFCT_MAX][FCTR_CFG_LOGLMP_MAX];
#else
extern tsFctR_ChLutType FctR_ChLut[FCTR_CFG_LGTFCT_MAX][FCTR_CFG_LOGLMP_MAX];
#endif

extern tsFctR_TgtLgtReq             FctR_TgtLgtReq;
extern tsFctR_TgtLgtReq             FctR_TgtLgtReq_Prv;
extern uint8                        FctR_ucTgtClSblLmpInt_Prv[FCTR_CFG_LOGLMP_MAX];
extern tsFctR_IlluminantStates      FctR_ActIlluminantStates[FCTR_CFG_LOGLMP_MAX];
extern tuFctR_LgtFct                FctR_LgtFctFailureFBit;
extern tsFctR_LgtFctState           FctR_Tgt_sLgtFctState;
extern tuFctR_LogLmp                FctR_UsageLogLmpTable[FCTR_CFG_LGTFCT_MAX];
extern tuFctR_LogLmp                FctR_AccessLogLmpTable[FCTR_CFG_LGTFCT_MAX];
extern uint8                        FctR_ucTgtLgtHighPrio[FCTR_CFG_LOGLMP_MAX];
extern uint8                        FctR_ucTgtLgtSustained[FCTR_CFG_LOGLMP_MAX];
extern uint8                        FctR_ucTgtLgtHighPrioPrevious[FCTR_CFG_LOGLMP_MAX];
extern uint32                       FctR_ulActLmpInt[FCTR_CFG_LOGLMP_MAX];
extern uint8                        FctR_ucActLmpInt[FCTR_CFG_LOGLMP_MAX];
extern uint8                        FctR_ucTgtLmpInt[FCTR_CFG_LOGLMP_MAX];
extern boolean                      FctR_boSwitchOffByFBit;
extern uint16                       FctR_unTgtLmpSpdInv[FCTR_CFG_LOGLMP_MAX];
extern uint16                       FctR_unTgtLmpSpdInv_sk[FCTR_CFG_LOGLMP_MAX];
extern tPrioLgtFctPair              FctR_PrioLgtFctPair[FCTR_CFG_LOGLMP_MAX];
extern uint32                       FctR_ulAimBlinkTime;
extern FctR_eAimingType             FctR_eAimingMode;
extern tsFctR_TimerCfg              FctR_sTimerCfg[FCTR_NUMBER_OF_TIMERS];
extern tsFctR_LightStatus           FctR_sLightStatus;
extern tsFctR_LightFailureStatus    FctR_sLightFailureStatus;
extern uint8                        FctR_ucTgtLgtHighPrioFbit[FCTR_CFG_LOGLMP_MAX];
extern uint16                       FctR_DRLIlluminantsErr;
extern uint16                       FctR_Cod_DRLIlluminantsFBit;

// FctR_TgtPrep.c
extern teFctR_EcuOperationgMode FctR_TgtPrep_eEcuOpMode;
extern teFctR_EcuSide           FctR_TgtPrep_eEcuSide;
extern teFctr_TiWarningMode     FctR_TgtPrep_eTiWarningMode;
extern tsFctR_AfsSignals        FctR_TgtPrep_sAfsSignals;
extern boolean                  FctR_TgtPrep_boTiStatus;
extern boolean                  FctR_TgtPrep_boTiAutoMode_On;
extern boolean                  FctR_TgtPrep_boTiCmd;
extern boolean                  FctR_TgtPrep_boHBCmd;
extern boolean                  FctR_TgtPrep_boLBCmd;
extern tUtilDebounceControl     FctR_TgtPrep_sTiAutoModeTimer;
extern tUtilDebounceControl     FctR_TgtPrep_TiDelayTimer;
extern tsFctR_TgtLgtReq         FctR_TgtLgtReqPrep;

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
extern boolean                  FctR_TgtPrep_boClSblTimeOut;
extern teFctR_LightFunctions    FctR_eActLgtClSbl;
extern uint8                    FctR_ucClSblTargetState;
#endif

//=============================================================================
// Module function declarations
//=============================================================================

// FctR_RteAccess.c
extern teFctR_AfsMode   FctR_RteAccess_MapAfsMode(teRte_Ctrl_AFS eAfsMode);
extern teFctR_GfHbCmd   FctR_RteAccess_MapGfHbSignals(teRte_GfHb_Cmd eGfHbCmd);
extern Std_ReturnType   FctR_RteAccess_Write_GfHbCmd(teRte_GfHb_Cmd eGfHbCmd);
extern teFctR_TiStatus  FctR_RteAccess_MapTiStatus(teRte_EtatClignotants eTiStatus);

// FctR_Tgt.c
extern void     FctR_ActLgt_Update                  (void);
extern void     FctR_TgtLgt_Prio                    (void);
extern void     FctR_TgtLgt_Sustain                 (void);
extern void     FctR_TgtLgt_Output                  (void);
extern void     FctR_Tgt_GetActLedState             (void);
extern void     FctR_Tgt_CheckLightFunctions_State  (void);
extern void     FctR_Tgt_HandleLgtFctFailure        (void);
extern void     FctR_Tgt_LgtFctFailureReaction      (void);
extern void     FctR_ProccessAimingMode             (void);
extern boolean  FctR_Get_UnderVoltageStatusDebounced(void);
extern boolean  FctR_Get_OverVoltageStatusDebounced (void);
extern uint8    FctR_CtrlDelayStatus(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel);
extern boolean  FctR_HandleDelayStatus(tsFctR_TimerCfg *sTimersCfg, const sint8 scTimerSel);
extern void     FctR_TgtDbl_Output                  (void);
extern boolean  FctR_CheckSblCl_LightStatus(void);

extern void     FctR_TgtLgt_StorePrep               (void);
extern void     FctR_TgtLgt_Prio_LgtFct             (void);
extern void     FctR_TgtLgt_Prio_LgtFct_FinalizePrio(void);

extern void     FctR_TgtLgt_Sustain_LogLamp    (tAppLogLamp ucLogLamp);
extern void     FctR_TgtLgt_Prio_LgtFctB_LogLmp(tAppLightFunction ucLgtFct);

extern boolean  FctR_GetActiveTgtLgtReq(tAppLightFunction ulLgtFct);
extern uint16   FctR_Percent_To_RteUnit(uint8 ucPercentVal);

extern uint8    FctR_GetPriority         (tAppLightFunction LgtFct, tAppLogLamp LogLmp);
extern uint8    FctR_GetIntensity        (tAppLightFunction LgtFct, tAppLogLamp LogLmp);
extern uint16   FctR_TgtLgt_GetLmpSpdInvB(tAppLightFunction LgtFct, tAppLogLamp LogLamp);
extern uint16   FctR_TgtLgt_GetLmpSpdInv (tAppLightFunction LgtFct, tAppLogLamp LogLamp);
extern uint16   FctR_TgtLgt_GetLmpSpdInvFromRampType(uint8 ucRampType, uint16 unTime, tAppLogLamp LogLamp);
extern void     FctR_CalculateUsageLogLmpTable(void);
extern tsFctR_TgtLgtReq FctR_SetLgtReq_VoltCond(tsFctR_TgtLgtReq sCurReq, uint8 ucVoltRange);

extern void     FctR_DiagFeedback(tsDiagFeedback_Cfg *psDiagSettings, boolean *pboDiagFeedback, boolean boForceErrReset);
extern void     FctR_KeepTiStatusOn(void);
extern void     FctR_StoreIlluminantFailureFunction(void);
extern void     FctR_StoreIlluminantStatusFunction(void);
extern boolean  FctR_SpecialBehaviorDrlPos(void);

// FctR_TgtPrep.c
extern void     FctR_TgtLgt_Prep_Ti(boolean boPosReq, boolean boTiReq, boolean boTiScrollingReq);
extern void     FctR_TgtLgt_Prep_StdLgtFcts(tsFctR_StdLgtFctsReq sStdLgtFcts);
extern boolean  FctR_TgtPrep_PklHandling(teFctR_PklReq ePklReq);
extern void     FctR_TgtPrep_DiagDD00_ResetCmd(boolean boCurrentStatusReq);

extern void     FctR_TgtPrep_SetTiWarningMode(teFctR_EcuOperationgMode eEcuOpMode, tsFctR_TiReq sTiReq);
extern void     FctR_TgtLgt_WarningMode_Handling(tsFctR_TiReq sTiReq, boolean* boTiCmd, boolean* boTiScrollingCmd);
extern void     FctR_TgtLgt_AutonomMode_Handling(boolean* boTiCmd);
extern void     FctR_TgtLgt_PilotedMode_Handling(tsFctR_TiReq sTiReq, boolean* boTiCmd, boolean* boTiScrollingCmd);
extern boolean  FctR_TgtPrep_LbLossHandling(boolean boLbReq);
extern boolean  FctR_TgtPrep_SetTiLgtStatus(boolean boTiReq);

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
extern void     FctR_TgtLgt_Prep_Aiming(boolean boAimReq, boolean boHbFlashReq);
extern void     FctR_TgtLgt_Prep_Lb_Full(boolean boLbReq);
extern void     FctR_TgtLgt_Prep_Hb_Full(tsFctR_StdLgtFctsReq sStdLgtFcts);
extern void     FctR_TgtLgt_Prep_ClSbl(boolean boClReq, boolean boSblReq);
#else
extern void     FctR_TgtLgt_Prep_Lb_Eco(tsFctR_StdLgtFctsReq sStdLgtFcts, boolean boLbReq);
extern void     FctR_TgtLgt_Prep_Hb_Eco(tsFctR_StdLgtFctsReq sStdLgtFcts);
#endif


//=============================================================================
// Module function parameter stubs
//=============================================================================

// FctR.c
tParaFct0_Cmd             FctR_ParaFct0_eCmd;
tNvmPara_CodingArea*      FctR_ParaFct0_pData;

// FctR_Tgt.c
tAppLightFunction         FctR_GetActiveTgtLgtReq_ulLgtFct;
uint8                     FctR_Percent_To_RteUnit_ucPercentVal;
tAppLightFunction         FctR_GetPriority_LgtFct;
tAppLogLamp               FctR_GetPriority_LogLmp;
tAppLightFunction         FctR_GetIntensity_LgtFct;
tAppLogLamp               FctR_GetIntensity_LogLmp;
tAppLightFunction         FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct;
uint8                     FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType;
uint16                    FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime;
tAppLogLamp               FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp;
tAppLightFunction         FctR_TgtLgt_GetLmpSpdInvB_LgtFct;
tAppLogLamp               FctR_TgtLgt_GetLmpSpdInvB_LogLamp;
tAppLightFunction         FctR_TgtLgt_GetLmpSpdInv_LgtFct;
tAppLogLamp               FctR_TgtLgt_GetLmpSpdInv_ucLogLamp;
tAppLogLamp               FctR_TgtLgt_Sustain_LogLamp_ucLogLamp;
tsFctR_TgtLgtReq          FctR_SetLgtReq_VoltCond_sCurReq;
uint8                     FctR_SetLgtReq_VoltCond_ucVoltRange;
tsDiagFeedback_Cfg*       FctR_DiagFeedback_psDiagSettings;
boolean*                  FctR_DiagFeedback_pboDiagFeedback;
boolean                   FctR_DiagFeedback_boForceErrReset;
boolean                   FctR_CtrlDelayStatus_boReqInput;
TIMER                     FctR_CtrlDelayStatus_ulTimeMs;
sint8                     FctR_CtrlDelayStatus_scTiTimerSel;
tsFctR_TimerCfg           FctR_HandleDelayStatus_sTimersCfg;
sint8                     FctR_HandleDelayStatus_scTimerSel;

// FctR_RteAccess.c
teRte_Ctrl_AFS            FctR_RteAccess_MapAfsMode_eAfsMode;
teRte_GfHb_Cmd            FctR_RteAccess_MapGfHbSignals_eGfHbCmd;
teRte_EtatClignotants     FctR_RteAccess_MapTiStatus_eTiStatus;

tsRte_TgtLedVal0Arr       FctR_RteAccess_Write_TgtLedsVal_pData;
tsFctR_LgtFctState        FctR_RteAccess_Write_LgtFctState_sState;
tuFctR_LgtFct             FctR_RteAccess_Write_LgtFctStatus_uStatus;
teFctr_TiWarningMode      FctR_RteAccess_Write_TiWarningMode_eTiWarningMode;
teRte_GfHb_Cmd            FctR_RteAccess_Write_GfHbCmd_eGfHbCmd;
teFctR_DblCommand         FctR_RteAccess_Write_DblCmd_eDblCmd;
tsFctR_TgtLgtReq          FctR_RteAccess_Write_AfsMode_sTgtLgt;
teFctR_AfsMode            FctR_RteAccess_Write_AfsMode_eAfsModeReceived;
FctR_eAimingType          FctR_RteAccess_Write_AfsMode_eAimingMode;

tsRte_LedErrStateArr      FctR_RteAccess_Read_ActLedState_pData;
tsFctR_VehState           FctR_RteAccess_Read_VehNetState_psData;
teFctR_EngineState        FctR_RteAccess_Read_EngineState_pData;
tsFctR_StdLgtFctsReq      FctR_RteAccess_Read_StdLgtFctReq_pData;
tsFctR_AfsSignals         FctR_RteAccess_Read_AfsSignals_pData;
tsFctR_TiReq*             FctR_RteAccess_Read_TiRequest_pData;
boolean*                  FctR_RteAccess_Read_ClSblRequest_pboClReq;
boolean*                  FctR_RteAccess_Read_ClSblRequest_pboSblReq;
boolean*                  FctR_RteAccess_Read_ClSblRequest_pboSblClSigQty;
teFctR_EcuSide            FctR_RteAccess_Read_EcuSide_eEcuSide;
uint8*                    FctR_RteAccess_Read_LedVoltRange_pucSetVoltageState;
teFctR_EcuOperationgMode  FctR_RteAccess_Read_PhaseVie_eEcuOpMode;
boolean*                  FctR_RteAccess_Read_OV_Status_pboStatus;
boolean*                  FctR_RteAccess_Read_UV_Status_pboStatus;

// FctR_TgtPrep.c
boolean                   FctR_TgtLgt_Prep_Ti_boPosReq;
boolean                   FctR_TgtLgt_Prep_Ti_boTiReq;
boolean                   FctR_TgtLgt_Prep_Ti_boTiScrollingReq;
boolean                   FctR_TgtPrep_SetTiLgtStatus_boTiReq;
tsFctR_StdLgtFctsReq      FctR_TgtLgt_Prep_StdLgtFcts_sStdLgtFcts;
teFctR_PklReq             FctR_TgtPrep_PklHandling_ePklReq;
teFctR_EcuOperationgMode  FctR_TgtPrep_SetTiWarningMode_eEcuOpMode;
tsFctR_TiReq              FctR_TgtPrep_SetTiWarningMode_sTiReq;
tsFctR_TiReq              FctR_TgtLgt_WarningMode_Handling_sTiReq;
boolean*                  FctR_TgtLgt_WarningMode_Handling_boTiCmd;
boolean*                  FctR_TgtLgt_WarningMode_Handling_boTiScrollingCmd;
boolean*                  FctR_TgtLgt_AutonomMode_Handling_boTiCmd;
tsFctR_TiReq              FctR_TgtLgt_PilotedMode_Handling_sTiReq;
boolean*                  FctR_TgtLgt_PilotedMode_Handling_boTiCmd;
boolean*                  FctR_TgtLgt_PilotedMode_Handling_boTiScrollingCmd;
boolean                   FctR_TgtPrep_LbLossHandling_boLbReq;
boolean                   FctR_TgtPrep_DiagDD00_ResetCmd_Param1;
boolean                   FctR_TgtLgt_Prep_Aiming_boAimReq;
boolean                   FctR_TgtLgt_Prep_Aiming_boHbFlashReq;
boolean                   FctR_TgtLgt_Prep_Lb_Full_boLbReq;
tsFctR_StdLgtFctsReq      FctR_TgtLgt_Prep_Hb_Full_sStdLgtFcts;
boolean                   FctR_TgtLgt_Prep_ClSbl_boClReq;
boolean                   FctR_TgtLgt_Prep_ClSbl_boSblReq;


#if(FCTR_CFG_FULL_VARIANT_SUPPORTED == 0)
tsFctR_StdLgtFctsReq  FctR_TgtLgt_Prep_Lb_Eco_sStdLgtFcts;
boolean               FctR_TgtLgt_Prep_Lb_Eco_boLbReq;
tsFctR_StdLgtFctsReq FctR_TgtLgt_Prep_Hb_Eco_sStdLgtFcts;
#endif

//=============================================================================
// Module function return value stubs
//=============================================================================
// FctR_Data.c
boolean FctR_Cod_Valid_RetVal;

// FctR_Tgt.c
boolean                   FctR_GetActiveTgtLgtReq_RetVal;
uint16                    FctR_Percent_To_RteUnit_RetVal;
uint8                     FctR_GetPriority_RetVal;
uint8                     FctR_GetIntensity_RetVal;
uint16                    FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal;
uint16                    FctR_TgtLgt_GetLmpSpdInvB_RetVal;
uint16                    FctR_TgtLgt_GetLmpSpdInv_RetVal;
boolean                   FctR_CheckSblCl_LightStatus_RetVal;
tsFctR_TgtLgtReq          FctR_SetLgtReq_VoltCond_RetVal;
boolean                   FctR_Get_UnderVoltageStatusDebounced_RetVal;
boolean                   FctR_Get_OverVoltageStatusDebounced_RetVal;
uint8                     FctR_CtrlDelayStatus_RetVal;
boolean                   FctR_HandleDelayStatus_RetVal;
boolean                   FctR_SpecialBehaviorDrlPos_RetVal;

//FctR_TgtPrep.c
boolean                   FctR_TgtPrep_SetTiLgtStatus_RetVal;
boolean                   FctR_TgtPrep_PklHandling_RetVal;
boolean                   FctR_TgtPrep_GetTiCmdReq_RetVal;
tsFctR_TgtLgtReq          FctR_TgtPrep_GetTgtLgtReq_RetVal;
boolean                   FctR_TgtPrep_LbLossHandling_RetVal;
boolean                   FctR_TgtPrep_GetAimingMode_RetVal;
boolean                   FctR_TgtPrep_Get_Hb_Cmd_RetVal;
boolean                   FctR_TgtPrep_Get_Lb_Cmd_RetVal;
uint8                     FctR_TgtPrep_GetClSblTargetState_RetVal;
teFctR_LightFunctions     FctR_TgtPrep_GetClSbl_AfsLight_RetVal;
teFctR_AfsMode            FctR_TgtPrep_GetAfsMode_RetVal;
boolean                   FctR_TgtPrep_GetAfsPedestrian_RetVal;
boolean                   FctR_TgtPrep_SblClTimeOutFrame_RetVal;

// FctR_RteAccess.c
teFctR_AfsMode           FctR_RteAccess_MapAfsMode_RetVal;
teFctR_GfHbCmd           FctR_RteAccess_MapGfHbSignals_RetVal;
teFctR_TiStatus          FctR_RteAccess_MapTiStatus_RetVal;
boolean                  FctR_RteAccess_Get_FailureGfHB_RetVal;

/* RTE Write */
Std_ReturnType           FctR_RteAccess_Write_TgtLedsVal_RetVal;
Std_ReturnType           FctR_RteAccess_Write_LgtFctState_RetVal;
Std_ReturnType           FctR_RteAccess_Write_LgtFctStatus_RetVal;
Std_ReturnType           FctR_RteAccess_Write_TiWarningMode_RetVal;
Std_ReturnType           FctR_RteAccess_Write_GfHbCmd_RetVal;
Std_ReturnType           FctR_RteAccess_Write_DblCmd_RetVal;
Std_ReturnType           FctR_RteAccess_Write_AfsMode_RetVal;

/* RTE Read */
Std_ReturnType           FctR_RteAccess_Read_ActLedState_RetVal;
Std_ReturnType           FctR_RteAccess_Read_VehNetState_RetVal;
Std_ReturnType           FctR_RteAccess_Read_EngineState_RetVal;
Std_ReturnType           FctR_RteAccess_Read_StdLgtFctReq_RetVal;
Std_ReturnType           FctR_RteAccess_Read_AfsSignals_RetVal;
teFctR_ModeConfigVehicle FctR_RteAccess_ReadVehicleModeConfig_RetVal;
Std_ReturnType           FctR_RteAccess_Read_TiRequest_RetVal;
boolean                  FctR_RteAccess_Read_HBB_RetVal;
Std_ReturnType           FctR_RteAccess_Read_ClSblRequest_RetVal;
Std_ReturnType           FctR_RteAccess_Read_EcuSide_RetVal;
Std_ReturnType           FctR_RteAccess_Read_LedVoltRange_RetVal;
Std_ReturnType           FctR_RteAccess_Read_PhaseVie_RetVal;
Std_ReturnType           FctR_RteAccess_Read_OV_Status_RetVal;
Std_ReturnType           FctR_RteAccess_Read_UV_Status_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

//FctR_Tgt.c
uint8   ucCounter     = 0u;
uint32  ulTimerStart  = 0u; 
uint32  ulTimeElapsed = 0u;
uint8   ucClSblDimOut;

//FctR_Tgt_HandleLgtFctFailure
boolean             boMxbFault;
tsFctR_LgtFctState  sDiagFeedback;
tsDiagFeedback_Cfg  asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS];
boolean             aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS];


//=============================================================================
// Global variable stubs
//=============================================================================
tNvmPara_LmmABlock      Mt_init = { 0u };

/*  These tables are configuration tables needed for generating the coding used by FctR Module*/
/*  !!! Important !!! : Keep the tables defined here, not in Test_Ext.c , otherwise coding is not initialized*/
const tNvmPara_LmmABlock    ConfigTable_LmmABlock_LghtFct_Ill[]     = FCTR_CFG_ILLUMINAT_LSM;
const tNvmPara_Lmm_Row      ConfigTable_LmmABlock_LghtFct_Ill_ROW[] = FCTR_CFG_ILLUMINAT_LSM;
const tNvmPara_Lmm_LutCell  ConfigTable[] = FCTR_CFG_LUT_LSM;


#endif // TEST_2023_08_25_H_

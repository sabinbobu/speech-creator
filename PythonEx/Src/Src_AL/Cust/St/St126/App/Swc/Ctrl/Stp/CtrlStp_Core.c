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
/// \file  CtrlStp_Core.c
///
/// \brief State transition control for CtrlStp
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <../Swc/Ctrl/Stp/Api/CtrlStp.h>
#include <../Swc/Ctrl/Stp/CtrlStp_Core.h>
#include "CtrlStp_Data.h"
#include "CtrlStp_Util.h" 
#include <UtilUtility.h>
#include <../Cdd/CddStp/ctscCddStp.h>
#include <../Cdd/CddStp/Api/CddStp.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST
#include <CtrlStp_RteAccess.h>
#include <Nvm.h>
#include <_NM_Types.h>
#include <LgmEIMMainAPI.h>

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define CTRLSTP_HsPosInvalid            0      // [HS] invalid HS position
#define CTRLSTP_HsPosMin                12     // [HS] min value needed for continous movement

#define CTRLSTP_MAX_MIN_POS_REQ         300U   // [0.01deg] upper and lower limit for position request (both are 3 degrees)

#define CTRLSTP_PostOpTimeout           300u   // [10ms]

#define CTRLSTP_MountingSideUndef       255u     // this definition is missing

#define CTRLSTP_SIMULATION_PASSWORD     0xCAFEBABEu
#define CTRLSTP_SIMULATION_DEACTIVATED  0xDEADC0DEu

#define CTRLSTP_LaMasterOffset          2000   // LA master offset for stepper positionning
#define CTRLSTP_InscenDelay             30u    // [ms] standardized value for acceleration and deceleration
#define CTRLSTP_InvalidInscenPos        -32768 // indicating invalid position (0x8000)

#define CTRLSTP_V_Ref                   (5u*64u)  // 5km/h [unit 1/64 km/h]
#define CTRLSTP_CycleTime               10u       // [us]

#define CTR_SLEEP_MODE_ABORT_SLEEP 1U

#define SUPPORT_NO 255U

#define SUPPORT_YES 1U

#define CTR_SLEEP_MODE_GOTO_SLEEP 0U

#define CTR_SLEEP_MODE_ABORT_SLEEP 1U

#define CTRLSTP_DIAG_SEQUENCE_TIME_MS 2000u // [ms] time between position commands during sequence

#define CTRLSTP_TGT_ACT_POS_DIFF 100U // indicates the threshold for the difference between target and actual position of the stepper (1 HS)
#define CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR   10
#define CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR 6
#define CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_NUMERATOR   6
#define CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_DENOMINATOR 10
#define CTRLSTP_AFSOFFSET_COEFFICIENT 1800 // coefficient used for offset calculation to approximate arctan operation
#define CTRLSTP_SCALING_10 10

#define CTRLSTP_PIVALUE 314

#define CTRLSTP_CONFIG_TIME_THRESHOLD 1000U // time needed to set the headlamp fault

#define CTRLSTP_ELEC_ZERO_POS 0


//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
typedef struct    // simulation for validation purposes
{
  uint32 ulSimActivated;     // simulation active (password)
  sint16 nSimPosReq;         // position    [0.01 deg]
  uint16 unSimSpeedReq;      // speed limit [0.1 deg/s]
  uint8  ucSimCtrSpnEngReq;  // control byte
} tsCtrlStp_SimData;


STATIC_AL volatile tsCtrlStp_SimData CtrlStp_Simulation_Data = { CTRLSTP_SIMULATION_DEACTIVATED, 0, 0u, 0u };



STATIC_AL teCtrlStp_MountingSide    CtrlStp_eMountingSide = CtrlStp_eMountedRight;

STATIC_AL TIMER              CtrlStp_ulTimeElapsed_us         = 0u;              // elapsed time used for timer operations
STATIC_AL TIMER              CtrlStp_ulTimeElapsedSlave_us    = 0u;              // elapsed time used for timer operations - slave

STATIC_AL boolean            CtrlStp_boDiagRefReq  = FALSE;              // storage for diag ref request
STATIC_AL boolean            CtrlStp_boDiagPosReq  = FALSE;              // flag for diag positionning request
STATIC_AL sint16             CtrlStp_nDiagPos      = 0;                  // [0.01deg]  position for diagnostic access
STATIC_AL uint16             CtrlStp_unDiagSpeed   = 0u;                 // [0.1deg/s] speed for diagnostic access

STATIC_AL boolean            CtrlStp_boInscenReq   = FALSE;              // Inscenation request
STATIC_AL sint16             CtrlStp_nInscenPos    = 0;                  // [HS]   position for inscenation
STATIC_AL uint16             CtrlStp_unInscenTmin  = 0u;                 // [usec] Tmin for inscenation
STATIC_AL uint16             CtrlStp_unInscenTimer = 0u;                 // for holding referenced condition after inscenation
STATIC_AL uint16             CtrlStp_unRefDelayCnt = 0u;                 // for asynchronous reference run L/R while vehicle is moving
STATIC_AL boolean            CtrlStp_boSpeedAbove5 = FALSE;              // vehicle speed >= 5km/h

STATIC_AL uint32             CtrlStp_ulDiagSequenceTimer = 0u;                 // Stp Sequence Timer for routine control
STATIC_AL boolean            CtrlStp_boDiagStpOn         = FALSE;              // Stp status for takeover
STATIC_AL boolean            CtrlStp_boDiagRefComplete   = FALSE;              // Referencing status for DF10

STATIC_AL teCtrlStp_SignalSrc CtrlStp_SignalSrc = eStpSrc_SleepPos;    // source for stepper target values
STATIC_AL teCtrlStp_HeadlampFaultStatus CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
STATIC_AL teCtrlStp_HeadlampFaultStatus CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
STATIC_AL teCtrlStp_SensorState         CtrlStp_eSensorError           = CtrlStp_eHLS_NO_FAILURE; // pitch error 

STATIC_AL volatile teCtrlStp_StepperRoutineControlRequest CtrlStp_eCurrentDiagState = CtrlStp_eStop; // current state request in the routine control
// Stp Sequence 1 for routine control
STATIC_AL CONST_AL teCtrlStp_StepperRoutineControlRequest CtrlStp_aeDiagSequence1[] = { CtrlStp_eMovementToBottom, CtrlStp_eMovementToTop, CtrlStp_eMovementToZero };
// Stp Sequence 2 for routine control
STATIC_AL CONST_AL teCtrlStp_StepperRoutineControlRequest CtrlStp_aeDiagSequence2[] = { CtrlStp_eMovementToBottom, CtrlStp_eMovementToZero };

STATIC_AL boolean CtrlStp_boStop             = TRUE;  // [boolean] hold position
STATIC_AL sint16  CtrlStp_nTgtPos            = 0;     // [HS] commanded position
STATIC_AL uint16  CtrlStp_unTgtTmin          = 0;     // [usec] commanded speed
STATIC_AL sint16  CtrlStp_nOffset            = 0;     // [0.01 deg]offset based on light request
STATIC_AL sint16  CtrlStp_snOffsetCorrection = 0;     // AFS offset correction value(distance between current offset and requested in 0.01 degree)
STATIC_AL boolean CtrlStp_boSlaveStop        = FALSE; // stop slave movement
STATIC_AL boolean CtrlStp_boSlaveSafetyPos   = FALSE; // set slave movement to safety position
STATIC_AL boolean CtrlStp_boIgnitionNeeded   = FALSE; // set flag for cases when new ignition is needed

STATIC_AL tsCtrlStp_ValidationParameters CtrlStp_Core_sValidationParams;

// stepper request
STATIC_AL sint16             CtrlStp_nPosReq         = 0;                      // LWR stepper position request
STATIC_AL uint16             CtrlStp_unSpeedReq      = 0u;                     // LWR stepper speed request

// stepper operation request based on environmental conditions
STATIC_AL boolean            CtrlStp_boConVehIgnition       = FALSE;   // operation request by ConVeh in combination with Light request
STATIC_AL boolean            CtrlStp_boOperationRequest     = FALSE;   // Overall operation request
STATIC_AL boolean            CtrlStp_boOperationStatus      = FALSE;   // Operation status (request plus post operation for driving to AP)
STATIC_AL boolean            CtrlStp_boTrainingState        = FALSE;   // training state ok if valid value is received from pitch
STATIC_AL volatile boolean   CtrlStp_boRefRequest           = FALSE;   // command for referencing
STATIC_AL volatile boolean   CtrlStp_boSlaveRefRequest      = FALSE;   // command for referencing for slave
STATIC_AL boolean            CtrlStp_boPowertrainActive     = FALSE;
STATIC_AL boolean            CtrlStp_boLvlAdjFuncFault      = FALSE;   // levelling adjust functional fault
STATIC_AL boolean            CtrlStp_boSlaveLvlAdjFuncFault = FALSE;   // levelling adjust functional fault
STATIC_AL boolean            CtrlStp_boVehAttitudeInvalid   = FALSE;
STATIC_AL boolean            CtrlStp_boSubModeError         = FALSE;
STATIC_AL boolean            CtrlStp_boCurtainAct           = FALSE;
STATIC_AL boolean            CtrlStp_boCurtainDeAct         = FALSE;
STATIC_AL boolean            CtrlStp_boStartSequence        = TRUE; // Stp Start Sequence Status for routine control
STATIC_AL boolean            CtrlStp_boElecOL               = FALSE;   // electrical error: open load
STATIC_AL boolean            CtrlStp_boElecSC               = FALSE;   // electrical error: short circuit
STATIC_AL boolean            CtrlStp_boStepLossCurrentSide  = FALSE;   // step loss status current side
STATIC_AL boolean            CtrlStp_boStepLossRightSide    = FALSE;   // step loss status Right side
STATIC_AL tieStpTempMode     CtrlStp_eTempMode              = (tieStpTempMode)0;   // electrical error: temperature mode status


// stepper status                                       pos                speed                 state
STATIC_AL tsRte_CtrlStpStatusSpinFront CtrlStp_Status = { CTRLSTP_SignalSna, CTRLSTP_SignalSna, (uint8)eStpSpnStatus_Sna};

// targets for all steppers                   pos stop speed
STATIC_AL tsRte_CtrlStpTarget CtrlStp_TgtAll = { { 0, TRUE, 0u } }; // LWR

// actual state of all steppers               pos speed     Support     Init   IsOn  IsReady IsMoving RefActive IsRef LowTemp TempMode IsFatalError boVoltNorm  boStepLoss boCommDefect boElecOL boElecSC boVoltUSSM  boVoltUVShtDwn boVoltOver boOverTempShtDwn
STATIC_AL tsRte_CddStpActual CtrlStp_ActAll = { { 0,  0u, { SUPPORT_NO, FALSE, FALSE, FALSE, FALSE,   FALSE,    FALSE, FALSE,     0,     FALSE,       FALSE,      FALSE,     FALSE,      FALSE,   FALSE,   FALSE,         FALSE,      FALSE,      FALSE   } } };
STATIC_AL tsCtrlStp_DiagStatus CtrlStp_DiagStatus;
// stepper control request for routine control
STATIC_AL tsCtrlStp_StepperRoutineControl CtrlStp_sStpControlRequest = { CtrlStp_eStpControl_Stop, CtrlStp_eBothActuators, CtrlStp_eStop, FALSE, FALSE, CtrlStp_eInvalid };

STATIC_AL tsCtrlStp_LevellingDiagStatus CtrlStp_sLevellingDiagStatusFromRightToLeft = 
{
  CtrlStp_eLvlElecR_NoDefect,                // Electric status of levelling stepper of Right LDM
  CtrlStp_eLvlTemperatureR_NoWarning,        // Temperature status of levelling stepper of Right LDM
  CtrlStp_eLvlSteplossR_NoSteploss,          // Step loss status of levelling stepper of Right LDM
  CtrlStp_eLvlRefStateR_WaitingForNewRefCmd, // Referencing status of levelling stepper of Right LDM
  CtrlStp_eLvlVoltR_NominalVoltage,          // Voltage status of Right levelling stepper
  CtrlStp_SIG_SNA                            // Signal quality
};
STATIC_AL tsCtrlStp_LevellingFeedback CtrlStp_sLevellingFeedbackFromRighToLeft = 
{
  CtrlStp_eSIGNPOSLVLR_Negative,       // SIGN_POS_LVL_R  - sign of the position feedback from right LDM
  { 0u },                              // POSITION_SITE_D - position value feedback from right LDM
  CtrlStp_eDynbendingBeamFaultR_False, // DBL fault feedback from right LDM
  CtrlStp_SIG_SNA                      // Signal quality
};
STATIC_AL tsCtrlStp_LevellingTgtPos CtrlStp_sLevellingSignalsFromLeftToRight = 
{
  CtrlStp_eSigneConsigneSiteD_Negativ, // SIGNE_CONSIGNE_SITE_D - sign of the position command to right LDM
  CtrlStp_eCmdRefSiteD_NoReferencing,  // CMD_REF_SITE_D        - ref command to right LDM
  { 0u },                              // CONSIGNE_SITE_D       - position command to right LDM
  eCtrlStpDynBendingBeamFaultL_False,  // DBL fault status sent to right LDM
  CtrlStp_SIG_SNA                      // Signal quality
};
//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
STATIC_AL  sint16  CtrlStp_GetContinMove(void);
STATIC_AL  boolean CtrlStp_IsMoving(void);
STATIC_AL  uint16  CtrlStp_TempCheck(uint16 unTmin);
STATIC_AL  void    CtrlStp_SetTgtTmin(void);
STATIC_AL  void    CtrlStp_DetectOffset(void);
STATIC_AL  void    CtrlStp_ReadStatusSignals(void);
STATIC_AL  void    CtrlStp_ReadLvlAdjFunctionalFaultStatus(void);
STATIC_AL  void    CtrlStp_ReadLvlAdjHeadlampFaultStatus(void);
STATIC_AL  void    CtrlStp_ReadStepLossRecovery(void);
STATIC_AL  void    CtrlStp_CheckFrame350Recovery(void);
STATIC_AL  void    CtrlStp_ReadEnvironmentSignals(void);
STATIC_AL  sint16  CtrlStp_GetOffset(uint8 ucAfsModeCmd, boolean boLowBeamBoostAllowed, boolean boHighBeamCmd);
STATIC_AL  void    CtrlStp_ApplyOffset(sint16 nLastOffset, sint16 nActualOffset, uint8 ucGfhbCmd, boolean boHighBeamCmd);
STATIC_AL  boolean CtrlStp_DetectAfsOffsetCurtainActivation(uint8 ucGfhbCmd);
STATIC_AL  boolean CtrlStp_DetectAfsOffsetCurtainDeactivation(uint8 ucGfhbCmd, boolean boHighBeamCmd);
STATIC_AL  boolean CtrlStp_GetDiagLvl(void);
STATIC_AL  boolean CtrlStp_GetElecIntStopCondition(void);
STATIC_AL  teCtrlStp_CmdRefSiteD CtrlStp_GetCmdRef(void);
STATIC_AL  void    CtrlStp_DiagStpTakeOver(void);
STATIC_AL  void    CtrlStp_SetDiagRequest(void);
STATIC_AL  void    CtrlStp_SetDiagPos(void);
STATIC_AL  void    CtrlStp_WriteValidationFrames(void);
STATIC_AL  teCtrlStp_StepperRoutineControlRequest CtrlStp_DiagSequenceMachine(CONST_AL teCtrlStp_StepperRoutineControlRequest* psData, uint8_least ucLength);


//-----------------------------------------------------------------------------
/// \brief  Get target value for continous movement
///
/// \descr  to be called at 10ms cycle
///
/// \param  none
///
/// \return sint16 position [HS]
//-----------------------------------------------------------------------------
STATIC_AL sint16 CtrlStp_GetContinMove(void)
{
  uint16 unPeriod;
  sint16 nTravel;
  sint16 nTgtPos;
  STATIC_UT(uint16, CtrlStp_unCnt, 0u);

  unPeriod = Cod_LwrTestDlPeriode();
  nTravel = (sint16)Cod_LwrTestDlWeg();

  if (CtrlStp_unCnt < (uint16)(unPeriod / 2u))
  {
    nTgtPos = CTRLSTP_HsPosMin + nTravel;
  }
  else
  {
    nTgtPos = CTRLSTP_HsPosMin;
  }

  if (++CtrlStp_unCnt >= unPeriod)
  {
    CtrlStp_unCnt = 0u;
  }
  else
  {
    // do nothing
  }

  return nTgtPos;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectOffset
///
/// \descr  detects offset based on light functions
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_DetectOffset(void)
{
  uint8    ucAfsMode = 0u, ucLBBoostAllowed = 0u, ucGFHB = 0u, ucHBCommand = 0u;
  boolean boLBBoost, boHBCmd;
  static sint16 nLastOffset = 0;
  sint16 nActualOffset = 0;
  // get all needed signals
  ucAfsMode = CtrlStp_RteAccess_ReadAFSMode();
  ucLBBoostAllowed = CtrlStp_RteAccess_ReadLbBoostAllowed();
  ucGFHB = CtrlStp_RteAccess_ReadGfhbCmd();
  boLBBoost = (ucLBBoostAllowed == 1u) ? TRUE : FALSE;
  ucHBCommand = CtrlStp_RteAccess_ReadHbCmd();
  boHBCmd = (ucHBCommand == 1u) ? TRUE : FALSE;

  // detect offset based on inputs
  nActualOffset = CtrlStp_GetOffset(ucAfsMode, boLBBoost, boHBCmd);
  CtrlStp_ApplyOffset(nLastOffset, nActualOffset, ucGFHB, boHBCmd);

  CtrlStp_snOffsetCorrection = CtrlStp_nOffset - nLastOffset;
  nLastOffset = CtrlStp_nOffset;

  // check for GFHB curtain effect transitions
  CtrlStp_boCurtainAct = CtrlStp_DetectAfsOffsetCurtainActivation(ucGFHB);
  CtrlStp_boCurtainDeAct = CtrlStp_DetectAfsOffsetCurtainDeactivation(ucGFHB, boHBCmd);
  //PRQA S 5324 1 // STCAL is exceeded due to software design
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_GetOffset
///
/// \descr  transition check function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL sint16 CtrlStp_GetOffset(uint8 ucAfsModeCmd, boolean boLowBeamBoostAllowed, boolean boHighBeamCmd)
{
  static sint16 nOffsetPercentage = 0; // offset from coding is given in 0.1%
  sint16 nOffsetCalculated = 0;

  if (boHighBeamCmd != FALSE)
  {
    // manual High Beam do not apply delay
    nOffsetPercentage = (sint16)Cod_AfsLevellingHBOffset();
  }
  else
  {
    switch (ucAfsModeCmd)
    {
    case(uint8)eCtrlAFS_Town:
      nOffsetPercentage = (sint16)Cod_AfsLevellingTownPedOffset();
      break;

    case(uint8)eCtrlAFS_Motorway:
      nOffsetPercentage = (boLowBeamBoostAllowed != FALSE) ? (sint16)Cod_AfsLevellingMWBoostOffset() : (sint16)Cod_AfsLevellingMWOffset();
      break;

    case(uint8)eCtrlAFS_BadWeatherLhd:
      nOffsetPercentage = (sint16)Cod_AfsLevellingLeftBdwLhdOffset();
      break;

    case(uint8)eCtrlAFS_BadWeatherRhd:
      nOffsetPercentage = (sint16)Cod_AfsLevellingLeftBdwRhdOffset();
      break;

    case(uint8)eCtrlAFS_FoggyLhd:
      nOffsetPercentage = (sint16)Cod_AfsLevellingLeftFoggyLhdOffset();
      break;

    case(uint8)eCtrlAFS_FoggyRhd:
      nOffsetPercentage = (sint16)Cod_AfsLevellingLeftFoggyRhdOffset();
      break;

    default:
      nOffsetPercentage = (sint16)Cod_AfsLevellingOffOffset();
      break;
    }
  }

  // convert offset to degrees according to the following formula:
  // Angle[Degrees] = 180 * arctan(AFS_OFFSET[%] / PI)
  nOffsetCalculated = (nOffsetPercentage * CTRLSTP_AFSOFFSET_COEFFICIENT) / CTRLSTP_PIVALUE;

  return nOffsetCalculated;

  //PRQA S 5324 1 // STCAL is exceeded due to software design
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_ApplyOffset
///
/// \descr Function used for applying the offset with a delay or not, depending on conditions
///
/// \param  snLastOffset
/// \param  snActualOffset
/// \param  ucGfhbCmd
/// \param  boHighBeamCmd
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_ApplyOffset(sint16 nLastOffset, sint16 nActualOffset, uint8 ucGfhbCmd, boolean boHighBeamCmd)
{
  STATIC_UT(boolean, boTimerStart, FALSE);
  STATIC_UT(uint32, ulHBTimer, 0u);

  if ((nActualOffset > nLastOffset) &&
    ((ucGfhbCmd == (uint8)eGfhbCmd_On || ucGfhbCmd == (uint8)eGfhbCmd_CurtainAct) && (boHighBeamCmd != FALSE)))
  {
    //delay the offset if we have a gfhb command on
    if (boTimerStart == FALSE)
    {
      ulHBTimer = TimerGetTick();
      boTimerStart = TRUE;
    }
    else if (TimerGetTimeSince(ulHBTimer) >= UTILTIME_MSEC(Cod_GFHBOffsetLevellingDelay()))
    {
      CtrlStp_nOffset = nActualOffset;
    }
    else
    {
      //go on timer not done
    }
  }
  else
  {
    boTimerStart = FALSE;
    CtrlStp_nOffset = nActualOffset;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectAfsOffsetCurtainActivation
///
/// \descr  Check if there is a transition to GFHB Curtain Activation and a correction of the offset is required
///
/// \param  uint8 ucGfhbCmd
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL  boolean CtrlStp_DetectAfsOffsetCurtainActivation(uint8 ucGfhbCmd)
{
  boolean boReturn = FALSE;

  if ((ucGfhbCmd == (uint8)eGfhbCmd_CurtainAct) && (CtrlStp_snOffsetCorrection != 0))
  {
    boReturn = TRUE;
  }
  else
  {
    boReturn = FALSE;
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectAfsOffsetCurtainDeactivation
///
/// \descr  Check if there is a transition to GFHB Curtain Deactivation and a correction of the offset is required from HB offset to any other offset
///
/// \param  uint8 ucGfhbCmd
/// \param  boolean boHighBeamCmd
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL  boolean CtrlStp_DetectAfsOffsetCurtainDeactivation(uint8 ucGfhbCmd, boolean boHighBeamCmd)
{
  boolean boReturn = FALSE;
  static boolean boLastHBCmd = FALSE;

  if ((ucGfhbCmd == (uint8)eGfhbCmd_CurtainDeAct) && (boLastHBCmd != FALSE)&& (boHighBeamCmd == FALSE))
  {
    boReturn = TRUE;
  }
  else
  {
    boReturn = FALSE;
  }

  boLastHBCmd = boHighBeamCmd;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  IsMoving()
///
/// \descr  Check if stepper is moving
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL  boolean CtrlStp_IsMoving(void)
{
  return CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectSide()
///
/// \descr  reads ecu side
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_DetectSide(void)
{
  (void)CtrlStp_RteAccess_Read_EcuSide(&CtrlStp_eMountingSide);
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnSide()
///
/// \descr  returns ecu side
///
/// \param  void
///
/// \return teCtrlStp_MountingSide
//-----------------------------------------------------------------------------
teCtrlStp_MountingSide CtrlStp_ReturnSide(void)
{
  return CtrlStp_eMountingSide;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadMasterSignals
///
/// \descr  reads master signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_ReadMasterSignals(void)
{
  sint16 nPosReq;

  (void)CtrlStp_RteAccess_ReadLevellingDiagStatus(&CtrlStp_sLevellingDiagStatusFromRightToLeft);
  (void)CtrlStp_RteAccess_ReadLevellingFeedback(&CtrlStp_sLevellingFeedbackFromRighToLeft);

  // read vehicle attitude from AVAC
  CtrlStp_RteAccess_ReadAvacCommand(&CtrlStp_nPosReq, &CtrlStp_boVehAttitudeInvalid, (uint8)CtrlStp_eMountingSide);
  
  CtrlStp_RteAccess_ReadSensorStatus(&CtrlStp_eSensorError); // read sensor error

  CtrlStp_boTrainingState = (NvmBlockDeltaPwmPara.ucZeroLevProg == 0xFFu) ? TRUE : FALSE;

  if (CtrlStp_Simulation_Data.ulSimActivated == CTRLSTP_SIMULATION_PASSWORD)
  {
    CtrlStp_nPosReq = CtrlStp_Simulation_Data.nSimPosReq;
    CtrlStp_unSpeedReq = CtrlStp_Simulation_Data.unSimSpeedReq;
  }
  else
  {
    // no simulation
  }

  //PRQA S 4342 1 // adaption of enum to RTE
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadSlaveSignals
///
/// \descr  read slave signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_ReadSlaveSignals(void)
{
  sint16          nPosReq;

  (void)CtrlStp_RteAccess_ReadLevellingTgtPos(&CtrlStp_sLevellingSignalsFromLeftToRight);

  if (CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl == CtrlStp_eSigneConsigneSiteD_Positive)
  {
    CtrlStp_nPosReq = (sint16)((sint16)CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl * CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_DENOMINATOR);
  }
  else
  {
    CtrlStp_nPosReq = -(sint16)((sint16)CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl * CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_DEG_RESOLUTION_DENOMINATOR);
  }

  // process slave reference request
  if (CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl == CtrlStp_eCmdRefSiteD_Referencing)
  {
    // store the request
    CtrlStp_boRefRequest = TRUE;
  }
  else
  {
    // stop reference request only after the current request has been proccessed
    if ((CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef != FALSE) || (CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive != FALSE))
    {
      CtrlStp_boRefRequest = FALSE;
    }
    else
    {
      // leave previous request
    }
  }
  
  if (CtrlStp_Simulation_Data.ulSimActivated == CTRLSTP_SIMULATION_PASSWORD)
  {
    CtrlStp_nPosReq    = CtrlStp_Simulation_Data.nSimPosReq;
    CtrlStp_unSpeedReq = CtrlStp_Simulation_Data.unSimSpeedReq;
  }
  else
  {
    // do nothing
  }

  //PRQA S 4342 1 // adaption of enum to RTE
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadEnvironmentSignals
///
/// \descr reads enviromental signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_ReadEnvironmentSignals(void)
{
  uint8    ucElectricNetworkState = (uint8)eInvalid;
  uint8    ucVESMainState        = (uint8)VESState_Invalid;

  ucVESMainState = CtrlStp_RteAccess_ReadVESMainState();
  ucElectricNetworkState = CtrlStp_RteAccess_ReadVehicleElectricState();

  // check if engine started 
  if ((ucVESMainState == (uint8)VESState_Ignition) ||
      (ucVESMainState == (uint8)VESState_Start))
  {
    CtrlStp_boConVehIgnition = TRUE;
  }
  else
  {
    CtrlStp_boConVehIgnition = FALSE;
    CtrlStp_boIgnitionNeeded = FALSE; // reset flag
  }


  // check if powertrain is activated
  if ((ucElectricNetworkState == (uint8)eTA_NOMINAL ||
       ucElectricNetworkState == (uint8)eTA_DEGRADE ||
       ucElectricNetworkState == (uint8)eTA_SECU    ||
       ucElectricNetworkState == (uint8)eREDEMARRAGE))
  {
    CtrlStp_boPowertrainActive = TRUE;
  }
  else
  {
    CtrlStp_boPowertrainActive = FALSE;
  }

  CtrlStp_DetectOffset();
  CtrlStp_CheckFrame350Recovery();

}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadStatusSignals
///
/// \descr  Read RTE signals from CddStp
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_ReadStatusSignals(void)
{
  CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues(&CtrlStp_ActAll);

  if (CtrlStp_boConVehIgnition != FALSE)
  {
    if (CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL != FALSE)
    {
      CtrlStp_boElecOL = TRUE;
    }
    else
    {
      // keep previous value
    }

    if (CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC != FALSE)
    {
      CtrlStp_boElecSC = TRUE;
    }
    else
    {
      // keep previous value
    }

    if (CtrlStp_ActAll.sLwrActual.sStatusError.boOverTempShtDwn != FALSE)
    {
      /* high temperature shutdown */
      CtrlStp_eTempMode = (tieStpTempMode)3;
    }
    else if (CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode == (tieStpTempMode)2)
    {
      /* high temperature warning */
      CtrlStp_eTempMode = (tieStpTempMode)2;
    }
    else if (CtrlStp_ActAll.sLwrActual.sStatusError.boLowTemp != FALSE)
    {
      /* cold temperature */
      CtrlStp_eTempMode = (tieStpTempMode)1;
    }
    else
    {
      // keep previous value
    }
  }
  else
  {
    CtrlStp_boElecOL  = FALSE;
    CtrlStp_boElecSC  = FALSE;
    CtrlStp_eTempMode = (tieStpTempMode)0; // no warning
  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadLvlAdjFunctionalFaultStatus
///
/// \descr  Read functional fault of levelling
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_ReadLvlAdjFunctionalFaultStatus(void)
{
  // collect adjustment errors
  if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
  {
    boolean boSpeedInvalid = FALSE, boPowertrainInvalid = FALSE, boLvlPosRInvalid = FALSE, boSTTPhaseInvalid = FALSE;

    (void)CtrlStp_RteAccess_ReadSpeed(&boSpeedInvalid);

    uint8    ucElectricNetworkState = (uint8)eInvalid;
    teCtrlStp_EtatFee eSTTPhase = CtrlStp_RteAccess_ReadElectricalSuppState();

    ucElectricNetworkState = CtrlStp_RteAccess_ReadVehicleElectricState();

    boPowertrainInvalid = (ucElectricNetworkState == (uint8)eInvalid) ? TRUE : FALSE;

    boLvlPosRInvalid = ((CtrlStp_sLevellingFeedbackFromRighToLeft.eSigQty == CtrlStp_SIG_INVALID) ||
                        (CtrlStp_sLevellingFeedbackFromRighToLeft.eSigQty == CtrlStp_SIG_TIMEOUT)) ? TRUE : FALSE;

    boSTTPhaseInvalid = (eSTTPhase == CtrlStp_eEtatFee_Invalid) ? TRUE : FALSE;

    if ((CtrlStp_boVehAttitudeInvalid != FALSE) ||
        (boSpeedInvalid               != FALSE) ||
        (boPowertrainInvalid          != FALSE) ||
        (boLvlPosRInvalid             != FALSE) ||
       ((boSTTPhaseInvalid            != FALSE) &&
       (NvmBlockDeltaPwmPara.eNVM_Function_STT == eOptionSTT_Present)))
    {
      CtrlStp_boLvlAdjFuncFault = TRUE;
    }
    else
    {
      CtrlStp_boLvlAdjFuncFault = FALSE;
    }
    CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_L = CtrlStp_boLvlAdjFuncFault;
  }
  else
  {
    if ((CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty == CtrlStp_SIG_INVALID) || (CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty == CtrlStp_SIG_TIMEOUT))
    {
      CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
    }
    else
    {
      CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
    }
    CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_R = CtrlStp_boSlaveLvlAdjFuncFault;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_CheckFrame350Recovery
///
/// \descr  Check if Frame 350 was lost and recovered from it
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_CheckFrame350Recovery(void)
{
  static boolean boLastFrameLost  = FALSE;
  static boolean boFrame350DTC    = FALSE;
  boolean boFrame350Lost          = FALSE;

  CtrlStp_RteAccess_Read_350Lost_Status(&boFrame350Lost);

  if (boFrame350Lost != FALSE) // check if DTC was set for Frame 350 lost, so we set ref request only in case of CAN error
  {
    boFrame350DTC = TRUE;
  }
  else
  {
    // leave previous value
  }

  if ((NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN) && (boFrame350DTC != FALSE) && (CtrlStp_boVehAttitudeInvalid == FALSE) && (boLastFrameLost != FALSE))
  {
    //CtrlStp_SetRefRequest(TRUE); // this ref request will be commented until the req regarding safety pos and frame 350 recovery are clarified with customer
  }
  else
  {
    // no behavior
  }

  boLastFrameLost = CtrlStp_boVehAttitudeInvalid;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadLvlAdjHeadlampFaultStatus
///
/// \descr  Check for levelling adjust headlamp fault
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL void CtrlStp_ReadLvlAdjHeadlampFaultStatus(void)
{
    STATIC_UT(boolean, boErrorCheck     , TRUE); // Check if 1000 ms have passed
    STATIC_UT(boolean, boSlaveErrorCheck, TRUE); // Check if 1000 ms have passed
 
  // collect current errors
  if ((CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError == FALSE)              &&
      (CtrlStp_boElecOL                                      == FALSE)              &&
      (CtrlStp_boElecSC                                      == FALSE)              &&
      (CtrlStp_boStepLossCurrentSide                         == FALSE)              &&
     ((CtrlStp_eTempMode                                     != (tieStpTempMode)2)  && // hot temperature warning
      (CtrlStp_eTempMode                                     != (tieStpTempMode)3)) && // hot temperature stop
      (CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm     != FALSE))
  {
    if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
    {
      CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
    }
    else
    {
      CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
    }

    // Validate flag so that the timer will be restarted at the next detection
    boErrorCheck = TRUE;
  }
  else if ((CtrlStp_boElecOL                                      != FALSE)             ||
           (CtrlStp_boElecSC                                      != FALSE)             ||
           (CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError != FALSE)             ||
          ((CtrlStp_eTempMode                                     == (tieStpTempMode)2) ||        // hot temperature warning
           (CtrlStp_eTempMode                                     == (tieStpTempMode)3)))         // hot temperature stop)
  {
    if (boErrorCheck != FALSE)
    {
      // Start timer
      CtrlStp_ulTimeElapsed_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boErrorCheck = FALSE;
    }
    else if ((TimerGetTimeSince(CtrlStp_ulTimeElapsed_us) >= UTILTIME_MSEC(CTRLSTP_CONFIG_TIME_THRESHOLD)))
    {
      if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
      {
        CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
      }
      else
      {
        CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
      }
    }
    else
    {
      // do nothing
    }
    
  }
  else if ((CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM != FALSE) ||
    (CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUVShtDwn != FALSE) ||
    (CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver != FALSE) ||
    (CtrlStp_boStepLossCurrentSide != FALSE))
  {
    if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
    {
      CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
    }
    else
    {
      CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
    }
  }
  else
  {
    // leave previous status
  }

  if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
  {
    // collect error from slave
    if ((CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR        == CtrlStp_eLvlElecR_NoDefect)                        &&
        (CtrlStp_boStepLossRightSide                                  == FALSE)                                             &&
       ((CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR != CtrlStp_eLvlTemperatureR_HighTemperatureWarning)   &&
        (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR != CtrlStp_eLvlTemperatureR_HighTemperatureShutdown)) &&
        (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR        == CtrlStp_eLvlVoltR_NominalVoltage))
    {
      CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
      boSlaveErrorCheck              = TRUE; // Validate flag so that the timer will be restarted at the next detection
    }
    else if ((CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR        == CtrlStp_eLvlElecR_OpenCircuit)                   ||
             (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR        == CtrlStp_eLvlElecR_ShortCircuit)                  ||
             (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR == CtrlStp_eLvlTemperatureR_HighTemperatureWarning) ||
             (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR == CtrlStp_eLvlTemperatureR_HighTemperatureShutdown))
    {
      if (boSlaveErrorCheck != FALSE)
      {
        // Start timer
        CtrlStp_ulTimeElapsedSlave_us = TimerGetTick();
        // Invalidate flag so that we do not restart the timer
        boSlaveErrorCheck = FALSE;
      }
      else if ((TimerGetTimeSince(CtrlStp_ulTimeElapsedSlave_us) >= UTILTIME_MSEC(CTRLSTP_CONFIG_TIME_THRESHOLD)))
      {
        CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
      }
      else
      {
        // do nothing
      }
    }
    else if ((CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR     == CtrlStp_eLvlVoltR_OverVoltage)  ||
             (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR     == CtrlStp_eLvlVoltR_UnderVoltage) ||
             (CtrlStp_boStepLossRightSide                               != FALSE))
    {
      if (boSlaveErrorCheck != FALSE)
      {
        // Start timer
        CtrlStp_ulTimeElapsedSlave_us = TimerGetTick();
        // Invalidate flag so that we do not restart the timer
        boSlaveErrorCheck = FALSE;
      }
      else if ((TimerGetTimeSince(CtrlStp_ulTimeElapsedSlave_us) >= UTILTIME_MSEC(CTRLSTP_CONFIG_TIME_THRESHOLD)))
      {
        CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      // leave previous status
    }

    CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_L = CtrlStp_eLvlAdjHeadlampFault_L;
  }
  else
  {
    // only left receives message from 4D7
  }
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eLvlAdjHeadlampFault_R;

  //PRQA S 5336 3 // STMIF exceeded due to program architecture and readability
  //PRQA S 5310 2 // STCPTH exceeded due to program architecture and readability
  //PRQA S 5316 1 // STCYC exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReadStepLossRecovery
///
/// \descr  Check for recovery of step loss
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_ReadStepLossRecovery(void)
{
  boolean boStepLoss = FALSE;

  boStepLoss = ((CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss         != FALSE) || 
                (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR == CtrlStp_eLvlSteplossR_SteplossRisk)) ? TRUE : FALSE;

  if (CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss != FALSE)
  {
    CtrlStp_boStepLossCurrentSide = TRUE;
  }
  else
  {
    // no behavior
  }

  if (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR == CtrlStp_eLvlSteplossR_SteplossRisk)
  {
    CtrlStp_boStepLossRightSide = TRUE;
  }
  else
  {
    // no behavior
  }

  // check if there was a recovery from steploss and set referencing request
  if (((CtrlStp_boStepLossCurrentSide != FALSE) || (CtrlStp_boStepLossRightSide != FALSE)) && (boStepLoss == FALSE))
  {
    CtrlStp_boRefRequest = TRUE;

    if ((CtrlStp_eLvlAdjHeadlampFault_L == CtrlStp_eTransition_Failure) || (CtrlStp_eLvlAdjHeadlampFault_R == CtrlStp_eTransition_Failure))
    {
      CtrlStp_boStepLossCurrentSide = FALSE;
      CtrlStp_boStepLossRightSide   = FALSE;
    }
    else
    {
      // no behavior
    }
  }
  else
  {
    // no behavior
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetTgtTmin
///
/// \descr  Set the minimum period for a halfstep
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_SetTgtTmin(void)
{
  //static boolean boMovementCompleted  = TRUE;
  uint16 unAfsCorrectSpeed            = Cod_AfsLevellingCorrectSpeed();

  if ((CtrlStp_snOffsetCorrection != 0) && (CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving == FALSE))
  {
    // OffsetAngle[0.01 deg] = (AFS_Offset[0.1 %] * 1800) / 314
    // OffsetAngularSpeed[0.01 deg/s] = (AFS_OffsetSpeed[0.1 %/s] * 1800) / 314
    // OffsetAngularSpeed[0.01 deg/s] = (AFS_OffsetSpeed[0.05 %/s] * 900) / 314
    // OffsetAngularSpeed[0.1  deg/s] = (AFS_OffsetSpeed[0.05 %/s] *  90) / 314
    CtrlStp_unSpeedReq = (unAfsCorrectSpeed * 90u) / (uint16)CTRLSTP_PIVALUE;
    CtrlStp_unTgtTmin = CtrlStp_Speed2Tmin(Cod_LwrHsGrad(), CtrlStp_unSpeedReq);
  }
  else if (CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving == FALSE)
  {
    CtrlStp_unTgtTmin = 0u;
  }
  else
  {
    // keep last value
  }

  CtrlStp_unTgtTmin = CtrlStp_TempCheck(CtrlStp_unTgtTmin);
  //PRQA S 5324 1 // STCAL is exceeded due to software design
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_TempCheck
///
/// \descr  Limit Tmin based on low temperature condition
///
/// \param  uint16 unTmin [us] : commanded Tmin
///
/// \return uint16 target Tmin [us]
//-----------------------------------------------------------------------------
STATIC_AL  uint16 CtrlStp_TempCheck(uint16 unTmin)
{
  uint16 unHsZeitMinTt = Cod_LwrHsZeitMinTt();

  if ( (CtrlStp_ActAll.sLwrActual.sStatusError.boLowTemp != FALSE        )
    && (unTmin                                            < unHsZeitMinTt) )
  {
    unTmin = unHsZeitMinTt;
  }
  else
  {
    // don t update
  }

  return unTmin;
}


//-----------------------------------------------------------------------------
// public functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectElecTransition
///
/// \descr  detects change of electric veh state for STT state
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_DetectElecTransition(void)
{
  STATIC_UT(teCtrlStp_EtatFee, ePreviousValue, CtrlStp_eEtatFee_1_1);
  teCtrlStp_EtatFee eCurrentValue = CtrlStp_RteAccess_ReadElectricalSuppState();
  boolean boReturn;

  if ((ePreviousValue == CtrlStp_eEtatFee_4_1)  &&
     ((eCurrentValue  == CtrlStp_eEtatFee_1_3c) ||
      (eCurrentValue  == CtrlStp_eEtatFee_1_3r) ||
      (eCurrentValue  == CtrlStp_eEtatFee_1_3vr)))
  {
    boReturn = TRUE;
  }
  else
  {
    boReturn = FALSE;
  }

  ePreviousValue = eCurrentValue;

  return boReturn;

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectElecTransitionSttToAdj
///
/// \descr  detects change of electric veh state
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_DetectElecTransitionSttToAdj(void)
{
  static teCtrlStp_EtatFee ePreviousValue;
  teCtrlStp_EtatFee eCurrentValue = CtrlStp_RteAccess_ReadElectricalSuppState();
  boolean boReturn;

  if ((ePreviousValue != eCurrentValue) && (eCurrentValue == CtrlStp_eEtatFee_4_1))
  {
    boReturn = TRUE;
  }
  else
  {
    boReturn = FALSE;
  }

  ePreviousValue = eCurrentValue;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectElecTransitionSttToRef
///
/// \descr  detects change of electric veh state
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_DetectElecTransitionSttToRef(void)
{
  static teCtrlStp_EtatFee ePreviousValue;
  teCtrlStp_EtatFee eCurrentValue = CtrlStp_RteAccess_ReadElectricalSuppState();
  boolean boReturn;

  if ((ePreviousValue == CtrlStp_eEtatFee_1_1) && (eCurrentValue == CtrlStp_eEtatFee_4_1))
  {
    boReturn = TRUE;
  }
  else
  {
    boReturn = FALSE;
  }

  ePreviousValue = eCurrentValue;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  Check if LWR stepper is enabled by coding data
///
/// \descr
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondEnabled(void)
{
  return Cod_LwrEnable();
}


//-----------------------------------------------------------------------------
/// \brief  Condition function to check if hardware is ready
///
/// \descr  Check if CddStp accepts new command
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondIsReady(void)
{
  return CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady;
}


//-----------------------------------------------------------------------------
/// \brief  Condition function to check if driver is on
///
/// \descr  
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondIsOn(void)
{
  return CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn;
}


//-----------------------------------------------------------------------------
/// \brief  Operation request
///
/// \descr  Operation requested from PWF, cont. movement or inscenation
///
/// \param  none
///
/// \return boolean - Reference run request active
//-----------------------------------------------------------------------------
boolean CtrlStp_CondOperationRequest(void)
{
  return CtrlStp_boOperationRequest;
}

//-----------------------------------------------------------------------------
/// \brief  Ref request
///
/// \descr  ref request active
///
/// \param  none
///
/// \return boolean - Reference run request active
//-----------------------------------------------------------------------------
boolean CtrlStp_RefRequest(void)
{
  return CtrlStp_boRefRequest;
}

//-----------------------------------------------------------------------------
/// \brief  Ref request
///
/// \descr  sets ref request only if stepper is in master mode
///
/// \param  boolean boRefRequst
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetRefRequest(boolean boRefRequst)
{
  // set ref request only if side is for master
  if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
  {
    CtrlStp_boRefRequest = boRefRequst;
  }
  else
  {
    // in slave mode request is only read
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetSlaveRefRequest
///
/// \descr  sets ref request for slave
///
/// \param  boolean boRefRequst
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetSlaveRefRequest(boolean boRefRequst)
{
  if (CtrlStp_ReturnSide() == CtrlStp_eMountedLeft)
  {
    CtrlStp_boSlaveRefRequest = boRefRequst;
  }
  else
  {
    //slave doesn't set reference request
  }
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_GetSubModeErr
///
/// \descr  get submode error
///
/// \param  none
///
/// \return boolean - submode error active
//-----------------------------------------------------------------------------
boolean CtrlStp_GetSubModeErr(void)
{
  return CtrlStp_boSubModeError;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetSubModeError
///
/// \descr  sets submode error only if stepper is in master mode
///
/// \param  boolean boSubModeErr
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetSubModeError(boolean boSubModeErr)
{
  // set ref request only if side is for master
  if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
  {
    CtrlStp_boSubModeError = boSubModeErr;
  }
  else
  {
    // in slave mode request is only read
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetSlaveStopRequest
///
/// \descr  sets stop request for slave
///
/// \param  boolean boSubModeErr
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetSlaveStopRequest(boolean boStopReq)
{
  // set ref request only if side is for master
  if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
  {
    CtrlStp_boSlaveStop = boStopReq;
  }
  else
  {
    // in slave mode request is only read
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetSlaveSafetyPosition
///
/// \descr  sets safety position command for slave
///
/// \param  boolean boPosReq
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetSlaveSafetyPosition(boolean boPosReq)
{
  // set pos request only if side is for master
  if (CtrlStp_eMountingSide == CtrlStp_eMountedLeft)
  {
    CtrlStp_boSlaveSafetyPos = boPosReq;
  }
  else
  {
    // in slave mode request is only read
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetIgnitionNeeded
///
/// \descr  sets ignition needed flag
///
/// \param  boolean boIgnitionReq
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetIgnitionNeeded(boolean boIgnitionReq)
{
  // set request for ignition
  CtrlStp_boIgnitionNeeded = boIgnitionReq;
}

//-----------------------------------------------------------------------------
/// \brief  Powertrain Active
///
/// \descr  powertrain active
///
/// \param  none
///
/// \return boolean - Powertrain Active
//-----------------------------------------------------------------------------
boolean CtrlStp_RetPowerTrainActive(void)
{
  return CtrlStp_boPowertrainActive;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RetVehIgnition
///
/// \descr  return ignition conditions fulfillment
///
/// \param  none
///
/// \return boolean - VehIgnition
//-----------------------------------------------------------------------------
boolean CtrlStp_RetVehIgnition(void)
{
  return CtrlStp_boConVehIgnition;
}

//-----------------------------------------------------------------------------
/// \brief  Operation request
///
/// \descr  Operation requested from PWF, cont. movement or inscenation
///
/// \param  none
///
/// \return boolean - Reference run request active
//-----------------------------------------------------------------------------
boolean CtrlStp_CondOperationStatus(void)
{
  return CtrlStp_boOperationStatus;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboTrainingState
///
/// \descr  Operation requested from PWF, cont. movement or inscenation
///
/// \param  none
///
/// \return boolean - Reference run request active
//-----------------------------------------------------------------------------
boolean CtrlStp_ReturnboTrainingState(void)
{
  return CtrlStp_boTrainingState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboSensorError
///
/// \descr  returns sensor error status
///
/// \param  none
///
/// \return teCtrlStp_SensorState
//-----------------------------------------------------------------------------
teCtrlStp_SensorState CtrlStp_ReturneSensorError(void)
{
  return CtrlStp_eSensorError;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboLvlAdjFuncFault
///
/// \descr  returns levelling adjust functional fault status
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_ReturnboLvlAdjFuncFault(void)
{
  return CtrlStp_boLvlAdjFuncFault;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboSlaveLvlAdjFuncFault
///
/// \descr  returns levelling adjust functional fault status for slave
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_ReturnboSlaveLvlAdjFuncFault(void)
{
  return CtrlStp_boSlaveLvlAdjFuncFault;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboLvlAdjHeadlampFault_L
///
/// \descr  returns levelling adjust headlamp fault status
///
/// \param  none
///
/// \return teCtrlStp_HeadlampFaultStatus
//-----------------------------------------------------------------------------
teCtrlStp_HeadlampFaultStatus CtrlStp_ReturneLvlAdjHeadlampFault_L(void)
{
  return CtrlStp_eLvlAdjHeadlampFault_L;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboLvlAdjHeadlampFault_R
///
/// \descr  returns levelling adjust headlamp fault status for slave
///
/// \param  none
///
/// \return teCtrlStp_HeadlampFaultStatus
//-----------------------------------------------------------------------------
teCtrlStp_HeadlampFaultStatus CtrlStp_ReturneLvlAdjHeadlampFault_R(void)
{
  return CtrlStp_eLvlAdjHeadlampFault_R;
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_ReturnSteplossErr
///
/// \descr returns steploss for current side
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_ReturnSteplossErr(void)
{
  return CtrlStp_boStepLossCurrentSide;
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_ReturnRightSteplossErr
///
/// \descr returns steploss for slave side
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_ReturnRightSteplossErr(void)
{
  return CtrlStp_boStepLossRightSide;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnboExtTakeOver
///
/// \descr  returns takeover status needed for diag takeover
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_ReturnboExtTakeOver(void)
{
  return CtrlStp_boDiagStpOn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_isSafetyPosReached
///
/// \descr  returns TRUE if safety position is reached or actual pos is less than safety pos
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_isSafetyPosReached(void)
{
  sint16 snSafetyPos    = CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), Cod_LwrSp());
  boolean boReturnValue = FALSE;

  if (CtrlStp_ActAll.sLwrActual.nPosition <= snSafetyPos)
  {
    boReturnValue = TRUE;
  }
  else
  {
    boReturnValue = FALSE;
  }
  return boReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  Check if coding parameter are available
///
/// \descr  Check also if stepper is supported by EFT data.
///         This can be checked in CddStp status
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondParamReady(void)
{
  boolean boCodingDataReady = CtrlStp_CodingDataReady(&CtrlStp_eMountingSide);

  if ((uint8)CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported != SUPPORT_YES)
  {
    boCodingDataReady = FALSE;  // EFT stepper configuration must be proved by CddStp
  }
  else
  {
    // do nothing
  }

  return boCodingDataReady;
}


//-----------------------------------------------------------------------------
/// \brief  Check for active referencing delay
///
/// \descr  Reference run delay is used for LH ECU only
///         if vehicle speed >= 5km/h
///
/// \param  none
///
/// \return boolean - Reference run delay active
//-----------------------------------------------------------------------------
boolean CtrlStp_CondRefDelay(void)
{
  boolean boRet = FALSE;  // default

  if (CtrlStp_eMountingSide  == CtrlStp_eMountedLeft)
  {
    if (CtrlStp_unRefDelayCnt > 0u)
    {
      CtrlStp_unRefDelayCnt--;
      boRet = TRUE;
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    // nothing for right ecu
  }

  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief  Condition function for reference run complete
///
/// \descr  Check if stepper is referenced
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondRefDnCompl(void)
{
  return CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef;
}

//-----------------------------------------------------------------------------
/// \brief  Condition function for reference run in progress
///
/// \descr  Check if stepper is referencing is in progress
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondRefInProgress(void)
{
  return CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive;
}


//-----------------------------------------------------------------------------
/// \brief  Condition function for referencing "movement up" complete
///
/// \descr  Check if stepper position is reached
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlStp_CondRefUpCompl(void)
{
  boolean boRet = FALSE;

  if (
    (CtrlStp_boStop != FALSE) // if no movement requested
    || (CtrlStp_nTgtPos == CtrlStp_ActAll.sLwrActual.nPosition))  // or target position reached
  {
    boRet = TRUE;
  }
  else
  {
    // leave request not true
  }

  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief  Do function of state Norm
///
/// \descr
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_DoNorm(void)
{
  // calculate actual angle in [0.1deg] (signed)
  sint32 lPosResp = CtrlStp_StpPos2Angle(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CtrlStp_ActAll.sLwrActual.nPosition);

  lPosResp = UTIL_MIN(lPosResp, CTRLSTP_SignalAngleMax);  // limit to range according to BMW messages
  lPosResp = UTIL_MAX(lPosResp, CTRLSTP_SignalAngleMin);

  CtrlStp_Status.ucLWRPosition = (uint8)(sint32)(lPosResp - CTRLSTP_SignalAngleMin);  // BMW format

  // calculate actual speed in [0.1deg/s]
  uint16 unSpeedResp = CtrlStp_Tmin2Speed(Cod_LwrHsGrad(), CtrlStp_unTgtTmin);  // use request instead of driver info

  unSpeedResp = UTIL_MIN(unSpeedResp, CTRLSTP_SignalSpeedMax);  // limit to range according to BMW messages

  CtrlStp_Status.ucLWRSpeed = (uint8)unSpeedResp;  // BMW format
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_EntryDis
///
/// \descr  Entry function of state Disabled
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_EntryDis(void)
{
  CtrlStp_Status.ucLWRState    = (uint8)eStpSpnStatus_Dis;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalDis;
  CtrlStp_Status.ucLWRSpeed    = CTRLSTP_SignalDis;

  (void)roCddStpOff();  // disable hardware
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_EntryErr
///
/// \descr  Entry function of state Error
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_EntryErr(void)
{
  CtrlStp_Status.ucLWRState    = (uint8)eStpSpnStatus_Err;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalErr;
  CtrlStp_Status.ucLWRSpeed    = CTRLSTP_SignalErr;

  (void)roCddStpOff();  // disable hardware
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_EntryInit
///
/// \descr  Entry function of state Init
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_EntryInit(void)
{
  CtrlStp_Status.ucLWRState    = (uint8)eStpSpnStatus_Sna;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalSna;
  CtrlStp_Status.ucLWRSpeed    = CTRLSTP_SignalSna;

  (void)roCddStpOff();  // disable hardware
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_EntryNorm
///
/// \descr  Entry function of state Norm
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_EntryNorm(void)
{
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
  // do not update speed and position here: this is done in "DoNorm"

  //CtrlStp_boDiagRefReq = FALSE;  // clear request-bit to avoid repetition of reference run
  //CtrlStp_boRefRequest = FALSE;  // clear request-bit to avoid repetition of reference run
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_EntryOff
///
/// \descr  Entry function of state Disabled
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_EntryOff(void)
{
  CtrlStp_Status.ucLWRState    = (uint8)eStpSpnStatus_NoInit;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalSna;
  CtrlStp_Status.ucLWRSpeed    = CTRLSTP_SignalSna;

  CtrlStp_unRefDelayCnt        = (uint16)((uint16)Cod_LwrAutorefZeitversatz() * (100u / CTRLSTP_CycleTime));  // [0.1s] --> [10ms]

  (void)roCddStpOff();  // disable hardware
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_EntryRefDn
///
/// \descr  Entry function of state RefDn
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_EntryRefDn(void)
{
  CtrlStp_Status.ucLWRState    = (uint8)eStpSpnStatus_Init;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalErr;
  CtrlStp_Status.ucLWRSpeed    = CTRLSTP_SignalErr;

  (void)roCddStpOn();  // enable hardware

  return;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetSignalMode
/// 
/// \descr  Sets CtrlStp mode
///
/// \param  teCtrlStp_SignalSrc eMode
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_SetSignalMode(teCtrlStp_SignalSrc eMode)
{
  CtrlStp_SignalSrc = eMode;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_GetTgtPos
///
/// \descr  Calculate Pos, Tmin and Stop based on selected source
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_GetTgtPos(void)
{
  sint16 nOffsetAngle;
  sint16 nAngle;
  sint16 nPos;
  uint16 unTmin;
  boolean boEIStop = FALSE;

  //get the stop condition
  boEIStop = CtrlStp_GetElecIntStopCondition();

  switch (CtrlStp_SignalSrc)
  {
    case eStpSrc_SleepPos:    // go to sleep mode
      //CtrlStp_nTgtPos   = CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), Cod_LwrAp());
      //CtrlStp_unTgtTmin = Cod_LwrHsZeitAp();
      // freeze levelling
      CtrlStp_boStop = TRUE;
      break;

    case eStpSrc_NormalPos:   // set values according to LA master request
      nOffsetAngle      = CtrlStp_LimitAngle(CTRLSTP_MAX_MIN_POS_REQ, CTRLSTP_MAX_MIN_POS_REQ, CtrlStp_nPosReq + CtrlStp_nOffset);
      nAngle            = CtrlStp_LimitAngle(Cod_LwrMaxWinkelMi(), Cod_LwrMaxWinkelPl(), nOffsetAngle);
      nPos              = CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), nAngle);
      CtrlStp_nTgtPos   = CtrlStp_CheckForStart(Cod_LwrHsWertStart(), CtrlStp_IsMoving(), CtrlStp_nTgtPos, nPos);
      CtrlStp_boStop    = boEIStop;
      CtrlStp_SetTgtTmin();
      break;

    case eStpSrc_DiagPos:     // goto position requested by diagnostic service "steuern_routine"
      nAngle            = CtrlStp_LimitAngle(Cod_LwrMaxWinkelMi(), Cod_LwrMaxWinkelPl(), CtrlStp_nDiagPos);
      CtrlStp_nTgtPos   = CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), nAngle);
      CtrlStp_unTgtTmin = CtrlStp_Speed2Tmin(Cod_LwrHsGrad(), CtrlStp_unDiagSpeed);
      CtrlStp_boStop    = (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF11) ? TRUE : FALSE; // move only the slave if DF11 routine is requested
      break;

    case eStpSrc_SafetyPos:   // goto safety position (so called SP)
      CtrlStp_nTgtPos   = CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), Cod_LwrSp());
      CtrlStp_unTgtTmin = 0u;
      CtrlStp_boStop    = (CtrlStp_ActAll.sLwrActual.nPosition < CtrlStp_nTgtPos) ? TRUE : FALSE;
      break;

    case eStpSrc_ContinPos:   // do continous movement according to coding parameters
      CtrlStp_nTgtPos   = CtrlStp_GetContinMove();
      CtrlStp_unTgtTmin = 0u;
      CtrlStp_boStop    = FALSE;
      break;

    case eStpSrc_ZeroPos:     //goto zero electrical position
      CtrlStp_nTgtPos = CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CTRLSTP_ELEC_ZERO_POS);
      CtrlStp_boStop  = boEIStop;
      CtrlStp_SetTgtTmin();
      break;

    default:
      break;
  }

  //PRQA S 5324 1 // STCAL >7 for a number of similar function calls
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_GetElecIntStopCondition
///
/// \descr returns the stop condition in electronic integration mode
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_GetElecIntStopCondition(void)
{
  boolean boRetVal = FALSE;
  NM_ModeType NMMode = NM_NORMAL;
  LEIM_TE_CurrentEIMode E_Ret = LEIM_E_INACTIVE;

  //Get Current Electronic Integration Mode
  E_Ret = EAPI_GetCurrentEIMode();
  // Get life phases from the NM
  (void)NM_GetMode(&NMMode);

  //Evaluate the stop condition in Electronic Integration Mode
  if ((E_Ret == LEIM_E_ACTIVE) && (NMMode == LIMP_HOME_MODE))
  {
    boRetVal = TRUE;
  }
  else
  {
    boRetVal = FALSE;
  }

  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Read coding parameter
///
/// \descr  read parameter based on mounting side
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
void CtrlStp_ReadParam(void)
{
  CtrlStp_RteAccess_MapParams();
}


//-----------------------------------------------------------------------------
/// \brief  Read RTE signals
///
/// \descr  read common signals for both slave and master ecu
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_ReadCommonSignals(void)
{
  CtrlStp_ReadEnvironmentSignals();  // PWF and LB/HB on/off conditions
  CtrlStp_ReadStatusSignals();       // status signals from CddStp
  CtrlStp_ReadLvlAdjFunctionalFaultStatus(); // read adjustment functional failure
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();   // read adjustment headlamp failure
  CtrlStp_ReadStepLossRecovery();   // read steploss status
  CtrlStp_DiagStpTakeOver(); // check if there is a request for exterior takeover
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_StartRef
///
/// \descr  Start reference run
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_StartRef(void)
{
  //CtrlStp_ucRefStartTimeoutCtr = CTRLSTP_REFSTART_TIMEOUT; // avoid hanging state machine if UV occurs immediately after starting reference run before it really has been started by CddStp

  // use internal summation of "CtrlStp_Angle2StpPos()"
  sint16 nRefPos = -CtrlStp_Angle2StpPos(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), (sint16)Cod_LwrAnschlagPl());

  roCddStpStartRefRun(0u, nRefPos);
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ElecDiagStat
///
/// \descr  Store electrical defect status
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_ElecDiagStat(void)
{
  if (CtrlStp_boElecOL != FALSE)
  {
    CtrlStp_DiagStatus.eStatStpElectricDefect = CtrlStp_eLvlElecR_OpenCircuit; // electrical defect for open load
  }
  else if (CtrlStp_boElecSC != FALSE)
  {
    CtrlStp_DiagStatus.eStatStpElectricDefect = CtrlStp_eLvlElecR_ShortCircuit; // electrical defect for short circuit
  }
  else
  {
    CtrlStp_DiagStatus.eStatStpElectricDefect = CtrlStp_eLvlElecR_NoDefect; // no electrical defect
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_PosDiagStat
///
/// \descr  Store position defect status
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_PosDiagStat(void)
{
  sint16 nPosDiff = CtrlStp_nTgtPos - CtrlStp_ActAll.sLwrActual.nPosition; // difference between target and actual position in halfsteps
  if (((uint16)UTIL_ABS(nPosDiff) > CTRLSTP_TGT_ACT_POS_DIFF) && (CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving == FALSE))
  {
    CtrlStp_DiagStatus.boStpPosDef = TRUE;
  }
  else
  {
    CtrlStp_DiagStatus.boStpPosDef = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_LvlStatus
///
/// \descr  Store automatic levelling status
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_LvlStatus(void)
{
  teCtrlStp_StatMain eStateValue = CtrlStp_GetStateValue();

  if (CtrlStp_CondEnabled() == 0u)
  {
    CtrlStp_DiagStatus.eStatStpLevelStatus = CtrlStp_eLvlStatus_NotImplemented; // status not implemented when stepper is disabled
  }
  else if (((eStateValue == CtrlStp_eState_Ref) || (eStateValue == CtrlStp_eState_Adj) || (eStateValue == CtrlStp_eState_STT)) && (CtrlStp_boPowertrainActive != FALSE))
  {
    CtrlStp_DiagStatus.eStatStpLevelStatus = CtrlStp_eLvlStatus_Active; // status is active when stepper is in available: ref or adjustment or STT state
  }
  else if (eStateValue == CtrlStp_eState_Fail)
  {
    CtrlStp_DiagStatus.eStatStpLevelStatus = CtrlStp_eLvlStatus_InDefect; // status in defect when stepper is in fail state
  }
  else
  {
    CtrlStp_DiagStatus.eStatStpLevelStatus = CtrlStp_eLvlStatus_Inhibited; // status inhibited when stepper is in other states
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_GetDiagStatus
///
/// \descr  Get values for levelling diagnosis
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_GetDiagStatus(void)
{
  sint16 snActPosDeg = CtrlStp_StpPos2Angle(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CtrlStp_ActAll.sLwrActual.nPosition); // store actual position in degrees [0.01 deg]

  if (snActPosDeg >= 0)
  {
    snActPosDeg = (snActPosDeg + 5) / 10;  // +5 /10 --> round and convert to 0.1deg
  }
  else
  {
    snActPosDeg = (snActPosDeg - 5) / 10;  // -5 /10 --> round and convert to 0.1deg
  }

  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&CtrlStp_DiagStatus);

  CtrlStp_DiagStatus.nStatStpPosVer         = CtrlStp_ActAll.sLwrActual.nPosition; // store actual position in halfsteps
  CtrlStp_DiagStatus.cStatStpPosDegree      = (sint8)snActPosDeg;
  CtrlStp_DiagStatus.eStatStpStepLoss       = (CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss != FALSE) ? CtrlStp_eLvlSteplossR_SteplossRisk : CtrlStp_eLvlSteplossR_NoSteploss; // store step loss status
  CtrlStp_DiagStatus.boStpIsMoving          = (CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving != FALSE) ? TRUE : FALSE; // store stepper movement status
  CtrlStp_DiagStatus.boStpCommDef           = (CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect != FALSE) ? TRUE : FALSE; // store communication defect status
  
  switch (CtrlStp_eTempMode)
  {
  case 0u: {CtrlStp_DiagStatus.eStatStpThermalState = CtrlStp_eLvlTemperatureR_NoWarning;               } break;
  case 1u: {CtrlStp_DiagStatus.eStatStpThermalState = CtrlStp_eLvlTemperatureR_ColdTemperature;         } break;
  case 2u: {CtrlStp_DiagStatus.eStatStpThermalState = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;  } break;
  case 3u: {CtrlStp_DiagStatus.eStatStpThermalState = CtrlStp_eLvlTemperatureR_HighTemperatureShutdown; } break;
  default: break;
  }

  CtrlStp_ElecDiagStat();  // store electrical defect status
  CtrlStp_PosDiagStat();   // store position defect status
  CtrlStp_LvlStatus();     // store automatic levelling status

  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(CtrlStp_DiagStatus);
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ReturnValidationParams
///
/// \descr  Return values for validation port
///
/// \param  none
///
/// \return tsCtrlStp_ValidationParameters
//-----------------------------------------------------------------------------
tsCtrlStp_ValidationParameters CtrlStp_ReturnValidationParams(void)
{
  return CtrlStp_Core_sValidationParams;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_GetDiagLvl
///
/// \descr  Get value of DIAG_LVL
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_GetDiagLvl(void)
{
  boolean boReturnValue  = FALSE;

  boReturnValue = ((CtrlStp_boIgnitionNeeded != FALSE) || 
                   (CtrlStp_boSubModeError   != FALSE)) ? TRUE : FALSE;

  return boReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_GetCmdRef
///
/// \descr  Get value of referencing command
///
/// \param  none
///
/// \return teCtrlStp_CmdRefSiteD
//-----------------------------------------------------------------------------
STATIC_AL teCtrlStp_CmdRefSiteD CtrlStp_GetCmdRef(void)
{
  teCtrlStp_CmdRefSiteD eReturnValue = CtrlStp_eCmdRefSiteD_NoReferencing;
  uint16 unMaxRefSpeed               = Cod_LwrMaxRefSpeed();
  boolean boSpeedInvalid             = FALSE;
  uint16 unVehicleSpeed              = CtrlStp_RteAccess_ReadSpeed(&boSpeedInvalid);

  // set referencing command only if conditions are met
  if ((CtrlStp_boSlaveRefRequest                           != FALSE)         &&
      (CtrlStp_boPowertrainActive                          != FALSE)         &&
      (unVehicleSpeed                                      <= unMaxRefSpeed) &&
      (CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty == CtrlStp_SIG_VALID))
  {
    eReturnValue = CtrlStp_eCmdRefSiteD_Referencing;
  }

  return eReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DiagStpTakeOver
///
/// \descr  Takeover of the stepper using the diag routine control
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_DiagStpTakeOver(void)
{
  uint8 ucVESMainState = (uint8)VESState_Invalid;
  static uint8 ucLastStartRequest = 0u;

  ucVESMainState = CtrlStp_RteAccess_ReadVESMainState();

  // Get Stp Control Routine
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_sStpControlRequest);

  // Reset takeover flag if engine is running
  if (ucVESMainState == (uint8)VESState_Start)
  {
    // Set Stp Status Off
    CtrlStp_boDiagStpOn = FALSE;
  }
  // Check the Diag Request status and Diagnostic Request (Start)
  else if ((CtrlStp_sStpControlRequest.boRequestStatus != FALSE) && (CtrlStp_sStpControlRequest.eStpControl == CtrlStp_eStpControl_Start))
  {
    // Set Stp Status On
    CtrlStp_boDiagStpOn = TRUE;
    // Set Acknowledge in order to handle the Diagnostic Result
    CtrlStp_RteAccess_WriteStpRoutineAck(TRUE);

    if (CtrlStp_sStpControlRequest.ucStartSequence != ucLastStartRequest)
    {
      // Prepare the flag for sequence start when the sequence start is requested
      CtrlStp_boStartSequence = TRUE;
    }
    else
    {
      // do nothing
    }
    ucLastStartRequest = CtrlStp_sStpControlRequest.ucStartSequence;
  }
  // Check the Diag Request status and Diagnostic Request (Stop)
  else if ((CtrlStp_sStpControlRequest.boRequestStatus != FALSE) && (CtrlStp_sStpControlRequest.eStpControl == CtrlStp_eStpControl_Stop))
  {
    // Set Stp Status Off
    CtrlStp_boDiagStpOn = FALSE;
    // Prepare the flag for sequence start when the sequence start is requested
    CtrlStp_boStartSequence = TRUE;
    // Clear Acknowledge in order to handle the Diagnostic Result
    CtrlStp_RteAccess_WriteStpRoutineAck(FALSE);
    // Reset side flag to make sure that no side will remain blocked
    CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eBothActuators;
    // Reset referencing flag for DF10
    CtrlStp_boDiagRefComplete = FALSE;
  }
  else
  {
    // None of the previous states (no Stp request or Request is Result)
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SetDiagRequest
///
/// \descr  Set the request needed for the takeover
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
 STATIC_AL void CtrlStp_SetDiagRequest(void)
{
  // Diagnostic Control over STP
  if ((CtrlStp_boDiagStpOn != FALSE) && ((CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF11) || (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF12) || (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF13)))
  {
    // Is request different than sequence
    if ((CtrlStp_sStpControlRequest.eStpRequest != CtrlStp_eSequence1) && (CtrlStp_sStpControlRequest.eStpRequest != CtrlStp_eSequence2))
    {
      // Set current state
      CtrlStp_eCurrentDiagState = CtrlStp_sStpControlRequest.eStpRequest;
    }
    // First sequence request
    else if (CtrlStp_sStpControlRequest.eStpRequest == CtrlStp_eSequence1)
    {
      // Run the sequence
      CtrlStp_eCurrentDiagState = CtrlStp_DiagSequenceMachine(CtrlStp_aeDiagSequence1, sizeof(CtrlStp_aeDiagSequence1) / sizeof(CtrlStp_aeDiagSequence1[0]));
    }
    // Second sequence request
    else
    {
      // Run the sequence
      CtrlStp_eCurrentDiagState = CtrlStp_DiagSequenceMachine(CtrlStp_aeDiagSequence2, sizeof(CtrlStp_aeDiagSequence2) / sizeof(CtrlStp_aeDiagSequence2[0]));
    }
  }
  else if ((CtrlStp_boDiagStpOn != FALSE) && (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF10))
  {
    if ((CtrlStp_boDiagRefComplete == FALSE) || (CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef == FALSE))
    {
      CtrlStp_SetSignalMode(eStpSrc_NormalPos);
      CtrlStp_StartRef();
      CtrlStp_boDiagRefComplete = TRUE;
    }
    else if (CtrlStp_CondRefUpCompl() != FALSE)
    {
      CtrlStp_SetSignalMode(eStpSrc_DiagPos);
    }
    else
    {
      // no behavior
    }
  }
  else
  {
    // No Diag request, set Stp stop == control using vehicle attitude
    CtrlStp_eCurrentDiagState = CtrlStp_eStop;
  }
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_DiagSequenceMachine
///
/// \descr STP sequence machine for routine control
///
/// \param  psData - sequence array
///
/// \return STATIC_AL teCtrlStp_StepperRoutineControlRequest
//-----------------------------------------------------------------------------
STATIC_AL teCtrlStp_StepperRoutineControlRequest CtrlStp_DiagSequenceMachine(CONST_AL teCtrlStp_StepperRoutineControlRequest* psData, uint8_least ucLength)
{
  // Stp Sequence Return
  STATIC_UT(teCtrlStp_StepperRoutineControlRequest, eReturnState, CtrlStp_eStop);
  // Sequence Index
  STATIC_UT(uint8_least, ucIndx, 0u);

  // Diag start is requested
  if (CtrlStp_boStartSequence == TRUE)
  {
    // return the first state of sequence
    eReturnState = psData[0];
    // Reset the sequence index
    ucIndx = 0u;
    // Get the time
    CtrlStp_ulDiagSequenceTimer = TimerGetTick();
    // Clear the sequence start flag
    CtrlStp_boStartSequence = FALSE;
  }
  else
  {
    // Time-Out on sequence step
    if (TimerGetTimeSince(CtrlStp_ulDiagSequenceTimer) >= UTILTIME_MSEC(CTRLSTP_DIAG_SEQUENCE_TIME_MS))
    {
      // Increment the step or stop at the end
      ucIndx = (ucIndx == ucLength - 1u) ? ucIndx : (ucIndx + 1u);
      // Get the time
      CtrlStp_ulDiagSequenceTimer = TimerGetTick();
      // return the current state of the input sequence
      eReturnState = psData[ucIndx];
    }
    else
    {
      // there is no time-out, skip
    }
  }
  // return current state of the Diag sequence
  return eReturnState;
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_SetDiagPos
///
/// \descr set stepper position for routine control
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_SetDiagPos(void)
{
  // Set diag target position according to the current request
  if ((CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF11) || (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF12) || (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDF13))
  {
    switch (CtrlStp_eCurrentDiagState)
    {
    case CtrlStp_eMovementToTop:
      CtrlStp_nDiagPos = (sint16)Cod_LwrMaxWinkelPl();
      break;
    case CtrlStp_eMovementToBottom:
      CtrlStp_nDiagPos = -(sint16)Cod_LwrMaxWinkelMi();
      break;
    case CtrlStp_eMovementToZero:
      CtrlStp_nDiagPos = 0;
      break;
    default:
      break;
    }
  }
  else if (CtrlStp_sStpControlRequest.eStpDID == CtrlStp_eDD05)
  {
    CtrlStp_nDiagPos = CtrlStp_sStpControlRequest.snPosRequest;
  }
  else
  {
    // no behavior
  }
  
  // set diag mode only for services besides DF10 - referencing needs normal mode
  if (CtrlStp_sStpControlRequest.eStpDID != CtrlStp_eDF10)
  {
    CtrlStp_SetSignalMode(eStpSrc_DiagPos);
  }
  else
  {
    // no behavior
  }
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_DiagRoutineControl
///
/// \descr set stepper position for routine control
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_DiagRoutineControl(void)
{
  // Turn on driver if it is switched off
  if (CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn == FALSE)
  {
    (void)roCddStpOn();  // enable hardware
  }
  else
  {
    // do nothing
  }
  // Get the request value from the routine control
  CtrlStp_SetDiagRequest();
  // Get diag target pos
  CtrlStp_SetDiagPos();
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_WriteValidationFrames
///
/// \descr write information needed for validation frames
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_WriteValidationFrames(void)
{
  tsCtrlStp_DiagStatus sLvlValidationFrames;

  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&sLvlValidationFrames);

  sint16 snTgtPosDegree = CtrlStp_StpPos2Angle(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CtrlStp_nTgtPos);
  sint16 snActPosDegree = CtrlStp_StpPos2Angle(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CtrlStp_ActAll.sLwrActual.nPosition);

  sLvlValidationFrames.sValidationFrames.boLvl_Elec_Defect  = (CtrlStp_DiagStatus.eStatStpElectricDefect         != CtrlStp_eLvlElecR_NoDefect        ) ? TRUE : FALSE;
  sLvlValidationFrames.sValidationFrames.boLvl_Temp_Defect  = (CtrlStp_DiagStatus.eStatStpThermalState           != CtrlStp_eLvlTemperatureR_NoWarning) ? TRUE : FALSE;
  sLvlValidationFrames.sValidationFrames.boLvl_StepLoss     = (CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss != FALSE                             ) ? TRUE : FALSE;
  sLvlValidationFrames.sValidationFrames.boLvl_Moving       = (CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving != FALSE                             ) ? TRUE : FALSE;
  sLvlValidationFrames.sValidationFrames.snLvl_Degree_Ctrl  = snTgtPosDegree * CTRLSTP_SCALING_10 * CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR;;
  sLvlValidationFrames.sValidationFrames.snLvl_Pos_Feedback = snActPosDegree * CTRLSTP_SCALING_10 * CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR;;

  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(sLvlValidationFrames);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_WriteMasterSignals
///
/// \descr  writes signals from master 
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_WriteMasterSignals(void)
{
  sint16 nPosReqRad = 0;
  sint16 nSafetyPos = Cod_LwrSp();
  uint16 unSafetyPosRad = (uint16)UTIL_ABS(nSafetyPos) * (uint16)CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR / (uint16)CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR;
  boolean boErrorDiag = CtrlStp_GetDiagLvl();
  boolean boSlaveStopRequest = ((CtrlStp_boTrainingState == FALSE) || (CtrlStp_boSlaveStop == TRUE)) ? TRUE : FALSE;

  // signals for CddStp
  CtrlStp_TgtAll.sLwrTarget.nPosition = CtrlStp_nTgtPos;

  if (CtrlStp_Status.ucLWRState == (uint8)eStpSpnStatus_Init)
  {
    CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
  }
  else
  {
    CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = CtrlStp_unTgtTmin;
  }

  if (CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef != FALSE)
  {
    CtrlStp_TgtAll.sLwrTarget.boStop = CtrlStp_boStop;
  }
  else
  {
    CtrlStp_TgtAll.sLwrTarget.boStop = FALSE;  // STOP allowed only if stepper is referenced
  }

  // write left signals
  (void)CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(&CtrlStp_sLevellingSignalsFromLeftToRight);

  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_GetCmdRef();

  // stop sending the referencing command if referencing is in progress
  if ((CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR == CtrlStp_eLvlRefStateR_RefInProgress) && //PRQA S 3415 // program architecture and readability
      (CtrlStp_boSlaveRefRequest                                 != FALSE))
  {
    CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
    CtrlStp_boSlaveRefRequest                            = FALSE;
  }
  else
  {
    // do nothing
  }

  nPosReqRad = CtrlStp_nPosReq * CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR;

  // set target value for slave if stop is not requested
 
  // set target value for slave if training is complete or diagnostic control is requested
  if ((CtrlStp_boDiagStpOn != FALSE) && (CtrlStp_sStpControlRequest.eStpSide != CtrlStp_eLeftActuator))
  {
    nPosReqRad = CtrlStp_nDiagPos * CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR;
    if (CtrlStp_nDiagPos > 0)
    {
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Positive;
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = (uint16)nPosReqRad;
    }
    else
    {
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = (uint16)(-nPosReqRad);
    }
  }
  else if (CtrlStp_boSlaveSafetyPos != FALSE) // set command to safety position
  {
    CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;

    if ((CtrlStp_sLevellingFeedbackFromRighToLeft.eRPosSignLvl == CtrlStp_eSIGNPOSLVLR_Positiv)        ||
       ((CtrlStp_sLevellingFeedbackFromRighToLeft.eRPosSignLvl == CtrlStp_eSIGNPOSLVLR_Negative) &&
        (CtrlStp_sLevellingFeedbackFromRighToLeft.ePositionSiteD.unRPosLvl < unSafetyPosRad)))
    {
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = unSafetyPosRad; // set safety position only if previous position was higher than safety position
    }
    else
    {
      // keep previous value
    }
  }
  else if ((boSlaveStopRequest == FALSE) && (CtrlStp_boIgnitionNeeded == FALSE))
  {
    if (CtrlStp_nPosReq > 0)
    {
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl             = CtrlStp_eSigneConsigneSiteD_Positive;
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = (uint16)nPosReqRad;
    }
    else
    {
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl             = CtrlStp_eSigneConsigneSiteD_Negativ;
      CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = (uint16)(-nPosReqRad);
    }
  }
  else
  {
    // keep previous value
  }

  CtrlStp_RteAccess_Write_DrvLedDiag_Port(boErrorDiag);

  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port(&CtrlStp_sLevellingSignalsFromLeftToRight);


  (void)CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(&CtrlStp_TgtAll);

  // write diagnostic status
  CtrlStp_GetDiagStatus();

  // write validation frames
  CtrlStp_WriteValidationFrames();
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_WriteSlaveSignals
///
/// \descr writes signals from slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_WriteSlaveSignals(void)
{
  sint16 nPosReqRad = 0;

  // signals for CddStp
  CtrlStp_TgtAll.sLwrTarget.nPosition = CtrlStp_nTgtPos;

  if (CtrlStp_Status.ucLWRState == (uint8)eStpSpnStatus_Init)
  {
    CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
  }
  else
  {
    CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = CtrlStp_unTgtTmin;
  }

  if (CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef != FALSE)
  {
    CtrlStp_TgtAll.sLwrTarget.boStop = CtrlStp_boStop;
  }
  else
  {
    CtrlStp_TgtAll.sLwrTarget.boStop = FALSE;  // STOP allowed only if stepper is referenced
  }

  (void)CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(&CtrlStp_TgtAll);

  // write right signals
  (void)CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(&CtrlStp_sLevellingDiagStatusFromRightToLeft);

  if ((CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError == FALSE) && 
      (CtrlStp_boElecOL                                      == FALSE) &&
      (CtrlStp_boElecSC                                      == FALSE))
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_NoDefect;
  }
  else if (CtrlStp_boElecOL != FALSE)
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
  }
  else if (CtrlStp_boElecSC != FALSE)
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_ShortCircuit;
  }
  else
  {
    // do nothing
  }
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eTempMode; //PRQA S 4442 // cast is needed
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = (CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss != FALSE) ? CtrlStp_eLvlSteplossR_SteplossRisk : CtrlStp_eLvlSteplossR_NoSteploss;

  if (CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef != FALSE)
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_SuccessfullyFinished;
  }
  else if (CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive != FALSE)
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_RefInProgress;
  }
  else
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_WaitingForNewRefCmd;
  }

  if (CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm != FALSE)
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_NominalVoltage;
  }
  else if (CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver != FALSE)
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
  }
  else if ((CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM != FALSE) || (CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUVShtDwn != FALSE))
  {
    CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_UnderVoltage;
  }
  else
  {
    // do nothing
  }

  (void)CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port(&CtrlStp_sLevellingDiagStatusFromRightToLeft);

  (void)CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(&CtrlStp_sLevellingFeedbackFromRighToLeft);
  nPosReqRad = CtrlStp_nPosReq * CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_NUMERATOR / CTRLSTP_ASSIETTE_VEHICULE_RAD_RESOLUTION_DENOMINATOR;
  // store position sign
  if ((CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty == CtrlStp_SIG_INVALID) || (CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty == CtrlStp_SIG_TIMEOUT)) // vehicle attitude is invalid
  {
    CtrlStp_sLevellingFeedbackFromRighToLeft.eRPosSignLvl             = CtrlStp_eSIGNPOSLVLR_Negative;
    CtrlStp_sLevellingFeedbackFromRighToLeft.ePositionSiteD.unRPosLvl = 0x3FFu;
  }
  else // store valid position
  {
    if (CtrlStp_nPosReq > 0)
    {
      CtrlStp_sLevellingFeedbackFromRighToLeft.eRPosSignLvl             = CtrlStp_eSIGNPOSLVLR_Positiv;
      CtrlStp_sLevellingFeedbackFromRighToLeft.ePositionSiteD.unRPosLvl = (uint16)nPosReqRad;
    }
    else
    {
      CtrlStp_sLevellingFeedbackFromRighToLeft.eRPosSignLvl             = CtrlStp_eSIGNPOSLVLR_Negative;
      CtrlStp_sLevellingFeedbackFromRighToLeft.ePositionSiteD.unRPosLvl = (uint16)(-nPosReqRad);
    }
  }

  (void)CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port(&CtrlStp_sLevellingFeedbackFromRighToLeft);

  // write diagnostic status
  CtrlStp_GetDiagStatus();

  // write validation frames
  CtrlStp_WriteValidationFrames();
  //PRQA S 5310 2 // STPTH exceeded and can't be simplified by design
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

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
/// \file  CtrlDcm.c
///
/// \brief Core module for CtrlDcm
///
/// \author Pop Sandor (F92597C)
///         mailTo:sandor.pop[at]marelli.com
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Rte.h>, <UtilUtility.h>, <Nvm.h>, <_NM_Types.h> */
#include "CtrlDcm.h"            /* ILCU_PORT: DPE include path <../App/Swc/Ctrl/Dcm/Api/CtrlDcm.h> flattened */
#include "CtrlDcm_Data.h"       /* ILCU_PORT: DPE include path <../App/Swc/Ctrl/Dcm/CtrlDcm_Data.h> flattened */
#include "CtrlDcmSm.h"          /* ILCU_PORT: DPE include path <../App/Swc/Ctrl/Dcm/CtrlDcmSm.h> flattened */
#include <CddDcm.h>
#include "CtrlDcm_RteAccess.h"  /* ILCU_PORT: DPE include path <../App/Swc/Ctrl/Dcm/CtrlDcm_RteAccess.h> flattened */

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

#define CTRLDCM_DIAG_SEQUENCE_TIME_MS 2000u // [ms] time between position commands during sequence

#define CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_NUMERATOR   10
#define CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_DENOMINATOR 6
#define CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_NUMERATOR   6
#define CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_DENOMINATOR 10
#define CTRLDCM_CONFIG_TIME_THRESHOLD 2000U // time needed to set the headlamp fault [ms]

#define CTRLDCM_ZERO_POS              800
#define CTRLDCM_POS_NOMINATOR         300
#define CTRLDCM_POS_DENOMINATOR       600

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------

STATIC_AL teCtrlDcm_MountingSide    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;

STATIC_AL TIMER              CtrlDcm_ulTimeElapsed_us              = 0u;              // elapsed time used for timer operations
STATIC_AL TIMER              CtrlDcm_ulTimeElapsedSlave_us         = 0u;              // elapsed time used for timer operations - slave
STATIC_AL TIMER              CtrlDcm_ulRecoveryTimeElapsed_us      = 0u;              // elapsed time used for timer operations
STATIC_AL TIMER              CtrlDcm_ulRecoveryTimeElapsedSlave_us = 0u;              // elapsed time used for timer operations - slave

STATIC_AL sint16             CtrlDcm_nDiagPos      = 0;                  // [0.01deg]  position for diagnostic access

STATIC_AL uint32             CtrlDcm_ulDiagSequenceTimer = 0u;                 // Dcm Sequence Timer for routine control
STATIC_AL boolean            CtrlDcm_boDiagDcmOn         = FALSE;              // Dcm status for takeover

STATIC_AL teCtrlDcm_SignalSrc   CtrlDcm_SignalSrc               = eDcmSrc_SleepPos;    // source for DC motor target values
STATIC_AL boolean               CtrlDcm_boLvlAdjHeadlampFault   = FALSE;
STATIC_AL boolean               CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
STATIC_AL teCtrlDcm_SensorState CtrlDcm_eSensorError            = CtrlDcm_eHLS_NO_FAILURE; // pitch error 

STATIC_AL volatile teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_eCurrentDiagState = CtrlDcm_eStop; // current state request in the routine control
// Dcm Sequence 1 for routine control
STATIC_AL CONST_AL teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_aeDiagSequence1[] = { CtrlDcm_eMovementToBottom, CtrlDcm_eMovementToTop, CtrlDcm_eMovementToZero };
// Dcm Sequence 2 for routine control
STATIC_AL CONST_AL teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_aeDiagSequence2[] = { CtrlDcm_eMovementToBottom, CtrlDcm_eMovementToZero };

STATIC_AL boolean CtrlDcm_boStop             = TRUE;  // [boolean] hold position
STATIC_AL sint16  CtrlDcm_nTgtPos            = 0;     // [0.01 deg] commanded position
STATIC_AL boolean CtrlDcm_boSlaveStop        = FALSE; // stop slave movement
STATIC_AL boolean CtrlDcm_boSlaveSafetyPos   = FALSE; // set slave movement to safety position
STATIC_AL boolean CtrlDcm_boIgnitionNeeded   = FALSE; // set flag for cases when new ignition is needed

// DC motor request
STATIC_AL sint16             CtrlDcm_nPosReq         = 0;                      // position request
STATIC_AL sint16             CtrlDcm_nLastPosReq     = 0;                      // previous position request

// DC motor operation request based on environmental conditions
STATIC_AL boolean            CtrlDcm_boConVehIgnition       = FALSE;   // operation request by ConVeh in combination with Light request
STATIC_AL boolean            CtrlDcm_boTrainingState        = FALSE;   // training state ok if valid value is received from pitch
STATIC_AL boolean            CtrlDcm_boPowertrainActive     = FALSE;
STATIC_AL boolean            CtrlDcm_boLvlAdjFuncFault      = FALSE;   // levelling adjust functional fault
STATIC_AL boolean            CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;   // levelling adjust functional fault
STATIC_AL boolean            CtrlDcm_boVehAttitudeInvalid   = FALSE;
STATIC_AL boolean            CtrlDcm_boDiagLvl              = FALSE;   // DIAG_LVL
STATIC_AL boolean            CtrlDcm_boStartSequence        = TRUE;    // Dcm Start Sequence Status for routine control


// target values for DC Motor
STATIC_AL tsCtrlDcm_TargetValues CtrlDcm_TgtAll = { { 0, TRUE } };

STATIC_AL tsCtrlDcm_DiagStatus CtrlDcm_DiagStatus; // diagnostic status
STATIC_AL tsCtrlDcm_ErrorStatus CtrlDcm_sErrorStatus; // Error status from driver
// DC motor control request for routine control
STATIC_AL tsCtrlDcm_DcMotorRoutineControl CtrlDcm_sDcmControlRequest = { CtrlDcm_eDcmControl_Stop, CtrlDcm_eBothActuators, CtrlDcm_eStop, FALSE, FALSE, CtrlDcm_eInvalid, 0u, 0u };

STATIC_AL tsCtrlDcm_LevellingDiagStatus CtrlDcm_sLevellingDiagStatusFromRightToLeft = 
{
  FALSE,                // DIAG_LVL_R
  CtrlDcm_SIG_SNA       // Signal quality
};
STATIC_AL tsCtrlDcm_LevellingTgtPos CtrlDcm_sLevellingSignalsFromLeftToRight = 
{
  CtrlDcm_eSigneConsigneSiteD_Negativ, // SIGNE_CONSIGNE_SITE_D - sign of the position command to right LDM
  { 0u },                              // CONSIGNE_SITE_D       - position command to right LDM
  CtrlDcm_SIG_SNA                      // Signal quality
};
//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
STATIC_AL  sint16  CtrlDcm_LimitAngle(uint16 unNegRange, uint16 unPosRange, sint16 nAngle);
STATIC_AL  void    CtrlDcm_ReadStatusSignals(void);
STATIC_AL  void    CtrlDcm_ReadLvlAdjFunctionalFaultStatus(void);
STATIC_AL  void    CtrlDcm_ReadLvlAdjHeadlampFaultStatus(void);
STATIC_AL  void    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery(void);
STATIC_AL  void    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R(void);
STATIC_AL  void    CtrlDcm_ReadEnvironmentSignals(void);
STATIC_AL  void    CtrlDcm_DiagDcmTakeOver(void);
STATIC_AL  void    CtrlDcm_SetDiagRequest(void);
STATIC_AL  void    CtrlDcm_SetDiagPos(void);
STATIC_AL  void    CtrlDcm_WriteValidationFrames(void);
STATIC_AL  teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_DiagSequenceMachine(CONST_AL teCtrlDcm_DcMotorRoutineControlRequest* psData, uint8_least ucLength);


//-----------------------------------------------------------------------------
/// \brief  Limit angle according to mechanical headlamp parameters
///
/// \descr  Limit input parameter Angle[0.01 deg] to
///           - upper limit: PosRange [0.01 deg]
///           - lower limit: NegRange [0.01 deg]
///
/// \param  uint16 unNegRange [0.01 deg] absolute value of negative range
///         uint16 unPosRange [0.01 deg] absolute value of positive range
///         sint16 nAngle     [0.01 deg]
///
/// \return sint16 nAngle with limitation
//-----------------------------------------------------------------------------
STATIC_AL sint16 CtrlDcm_LimitAngle(uint16 unNegRange, uint16 unPosRange, sint16 nAngle)
{
  sint16 nMinVal = -(sint16)unNegRange;
  sint16 nMaxVal =  (sint16)unPosRange;

  nAngle = UTIL_MAX(nAngle, nMinVal);  // lower limit
  nAngle = UTIL_MIN(nAngle, nMaxVal);  // upper limit

  return nAngle;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_DetectSide()
///
/// \descr  reads ecu side
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_DetectSide(void)
{
  (void)CtrlDcm_RteAccess_Read_EcuSide(&CtrlDcm_eMountingSide);
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnSide()
///
/// \descr  returns ecu side
///
/// \param  void
///
/// \return teCtrlDcm_MountingSide
//-----------------------------------------------------------------------------
teCtrlDcm_MountingSide CtrlDcm_ReturnSide(void)
{
  return CtrlDcm_eMountingSide;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReadMasterSignals
///
/// \descr  reads master signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_ReadMasterSignals(void)
{
  sint16 nPosReq = 0;

  CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(&CtrlDcm_sLevellingDiagStatusFromRightToLeft);

  // read vehicle attitude from sAVAC
  CtrlDcm_RteAccess_ReadAvacCommand(&CtrlDcm_nPosReq, &CtrlDcm_boVehAttitudeInvalid, (uint8)CtrlDcm_eMountingSide);
  
  CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_eSensorError); // read sensor error

  CtrlDcm_boTrainingState = (NvmBlockDeltaPwmPara.ucZeroLevProg == 0xFFu) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReadSlaveSignals
///
/// \descr  read slave signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_ReadSlaveSignals(void)
{
  sint16 nPosReq = 0;

  (void)CtrlDcm_RteAccess_ReadLevellingTgtPos(&CtrlDcm_sLevellingSignalsFromLeftToRight);

  if (CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl == CtrlDcm_eSigneConsigneSiteD_Positive)
  {
    CtrlDcm_nPosReq = (sint16)((sint16)CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl * CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_NUMERATOR / CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_DENOMINATOR);
  }
  else
  {
    CtrlDcm_nPosReq = -(sint16)((sint16)CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl * CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_NUMERATOR / CTRLDCM_VEHICLE_ATTITUDE_DEG_RESOLUTION_DENOMINATOR);
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReadEnvironmentSignals
///
/// \descr reads enviromental signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlDcm_ReadEnvironmentSignals(void)
{
  uint8 ucElectricNetworkState = (uint8)eInvalid;
  uint8 ucVESMainState         = (uint8)VESState_Invalid;

  ucVESMainState         = CtrlDcm_RteAccess_ReadVESMainState();
  ucElectricNetworkState = CtrlDcm_RteAccess_ReadVehicleElectricState();

  // check if engine started 
  if ((ucVESMainState == (uint8)VESState_Ignition) ||
      (ucVESMainState == (uint8)VESState_Start))
  {
    CtrlDcm_boConVehIgnition = TRUE;
  }
  else
  {
    CtrlDcm_boConVehIgnition = FALSE;
    CtrlDcm_boIgnitionNeeded = FALSE; // reset flag
  }


  // check if powertrain is activated
  if ((ucElectricNetworkState == (uint8)eTA_NOMINAL ||
       ucElectricNetworkState == (uint8)eTA_DEGRADE ||
       ucElectricNetworkState == (uint8)eTA_SECU    ||
       ucElectricNetworkState == (uint8)eDEMARRAGE  ||
       ucElectricNetworkState == (uint8)eREDEMARRAGE))
  {
    CtrlDcm_boPowertrainActive = TRUE;
  }
  else
  {
    CtrlDcm_boPowertrainActive = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReadStatusSignals
///
/// \descr  Read RTE signals from CddDcm
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlDcm_ReadStatusSignals(void)
{
  CtrlDcm_RteAccess_ReadDriverErrors(&CtrlDcm_sErrorStatus);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReadLvlAdjFunctionalFaultStatus
///
/// \descr  Read functional fault of levelling
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlDcm_ReadLvlAdjFunctionalFaultStatus(void)
{
  // collect adjustment errors
  if (CtrlDcm_eMountingSide == CtrlDcm_eMountedLeft)
  {
    boolean boSpeedInvalid = FALSE, boPowertrainInvalid = FALSE, boHeadlampFaultR = FALSE, boSTTPhaseInvalid = FALSE;
    uint8 ucElectricNetworkState = (uint8)eInvalid;

    (void)CtrlDcm_RteAccess_ReadSpeed(&boSpeedInvalid);
   

    ucElectricNetworkState = CtrlDcm_RteAccess_ReadVehicleElectricState();
 
    boPowertrainInvalid = (ucElectricNetworkState == (uint8)eInvalid) ? TRUE : FALSE;

    boHeadlampFaultR = ((CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty == CtrlDcm_SIG_INVALID) ||
                        (CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty == CtrlDcm_SIG_TIMEOUT)) ? TRUE : FALSE;

    if ((CtrlDcm_boVehAttitudeInvalid != FALSE) ||
        (boSpeedInvalid               != FALSE) ||
        (boPowertrainInvalid          != FALSE) ||
        (boHeadlampFaultR             != FALSE))
    {
      CtrlDcm_boLvlAdjFuncFault = TRUE;
    }
    else
    {
      CtrlDcm_boLvlAdjFuncFault = FALSE;
    }
  }
  else
  {
    if ((CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty == CtrlDcm_SIG_INVALID) || (CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty == CtrlDcm_SIG_TIMEOUT))
    {
      CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    }
    else
    {
      CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_CheckLvlAdjHeadlampFaultRecovery
///
/// \descr  Check for levelling adjust headlamp fault recovery
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_CheckLvlAdjHeadlampFaultRecovery(void)
{
  STATIC_UT(boolean, boRecoveryCheck, TRUE); // Check if 2000 ms have passed

  if (CtrlDcm_boLvlAdjHeadlampFault == FALSE)
  {
    // Validate flag so that the timer will be restarted at the next detection
    boRecoveryCheck = TRUE;
  }
  else
  {
    if (boRecoveryCheck != FALSE)
    {
      // Start timer
      CtrlDcm_ulRecoveryTimeElapsed_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boRecoveryCheck = FALSE;
    }
    else if ((TimerGetTimeSince(CtrlDcm_ulRecoveryTimeElapsed_us) >= UTILTIME_MSEC(CTRLDCM_CONFIG_TIME_THRESHOLD)))
    {
      CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    }
    else
    {
      // do nothing
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R
///
/// \descr  Check for levelling adjust headlamp fault recovery for right side
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R(void)
{
  STATIC_UT(boolean, boSlaveRecoveryCheck, TRUE); // Check if 2000 ms have passed

  if (CtrlDcm_boLvlAdjHeadlampFault_R == FALSE)
  {
    boSlaveRecoveryCheck = TRUE; // Validate flag so that the timer will be restarted at the next detection
  }
  else
  {
    if (boSlaveRecoveryCheck != FALSE)
    {
      // Start timer
      CtrlDcm_ulRecoveryTimeElapsedSlave_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boSlaveRecoveryCheck = FALSE;
    }
    else if ((TimerGetTimeSince(CtrlDcm_ulRecoveryTimeElapsedSlave_us) >= UTILTIME_MSEC(CTRLDCM_CONFIG_TIME_THRESHOLD)))
    {
      CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    }
    else
    {
      // do nothing
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReadLvlAdjHeadlampFaultStatus
///
/// \descr  Check for levelling adjust headlamp fault
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL void CtrlDcm_ReadLvlAdjHeadlampFaultStatus(void)
{
    STATIC_UT(boolean, boErrorCheck     , TRUE); // Check if 2000 ms have passed
    STATIC_UT(boolean, boSlaveErrorCheck, TRUE); // Check if 2000 ms have passed

    // collect current errors
  if ((CtrlDcm_sErrorStatus.boElecBAT == FALSE) && (CtrlDcm_sErrorStatus.boElecGND == FALSE))
  {
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery();

    // Validate flag so that the timer will be restarted at the next detection
    boErrorCheck = TRUE;
  }
  else
  {
    if (boErrorCheck != FALSE)
    {
      // Start timer
      CtrlDcm_ulTimeElapsed_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boErrorCheck = FALSE;
    }
    else if ((TimerGetTimeSince(CtrlDcm_ulTimeElapsed_us) >= UTILTIME_MSEC(CTRLDCM_CONFIG_TIME_THRESHOLD)))
    {
      CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    }
    else
    {
      // do nothing
    }
  }

  if (CtrlDcm_eMountingSide == CtrlDcm_eMountedLeft)
  {
    // collect error from slave
    if (CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR == FALSE)
    {
      CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R();

      boSlaveErrorCheck = TRUE; // Validate flag so that the timer will be restarted at the next detection
    }
    else
    {
      if (boSlaveErrorCheck != FALSE)
      {
        // Start timer
        CtrlDcm_ulTimeElapsedSlave_us = TimerGetTick();
        // Invalidate flag so that we do not restart the timer
        boSlaveErrorCheck = FALSE;
      }
      else if ((TimerGetTimeSince(CtrlDcm_ulTimeElapsedSlave_us) >= UTILTIME_MSEC(CTRLDCM_CONFIG_TIME_THRESHOLD)))
      {
        CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
      }
      else
      {
        // do nothing
      }
    }
  }
  else
  {
    // no behavior
  }
}

//-----------------------------------------------------------------------------
// public functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  Check if DC motor is enabled by coding data
///
/// \descr
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_CondEnabled(void)
{
  return Cod_DcmEnable();
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_GetDiagLvl
///
/// \descr  get DIAG_LVL
///
/// \param  none
///
/// \return boolean - DIAG_LVL error active
//-----------------------------------------------------------------------------
boolean CtrlDcm_GetDiagLvl(void)
{
  boolean boReturnValue = FALSE;

  boReturnValue = ((CtrlDcm_boDiagLvl != FALSE) || (CtrlDcm_boIgnitionNeeded != FALSE)) ? TRUE : FALSE;

  return boReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SetDiagLvl
///
/// \descr  sets DIAG_LVL error only if DC motor is in master mode
///
/// \param  boolean boDiagLvl
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_SetDiagLvl(boolean boDiagLvl)
{
  // set DIAG_LVL only if side is for master
  if (CtrlDcm_eMountingSide == CtrlDcm_eMountedLeft)
  {
    CtrlDcm_boDiagLvl = boDiagLvl;
  }
  else
  {
    // no behavior
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SetSlaveStopRequest
///
/// \descr  sets stop request for slave
///
/// \param  boolean boStopReq
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_SetSlaveStopRequest(boolean boStopReq)
{
  // set stop request only if side is for master
  if (CtrlDcm_eMountingSide == CtrlDcm_eMountedLeft)
  {
    CtrlDcm_boSlaveStop = boStopReq;
  }
  else
  {
    // in slave mode request is only read
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SetSlaveSafetyPosition
///
/// \descr  sets safety position command for slave
///
/// \param  boolean boPosReq
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_SetSlaveSafetyPosition(boolean boPosReq)
{
  // set pos request only if side is for master
  if (CtrlDcm_eMountingSide == CtrlDcm_eMountedLeft)
  {
    CtrlDcm_boSlaveSafetyPos = boPosReq;
  }
  else
  {
    // in slave mode request is only read
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SetFailIgnitionNeeded
///
/// \descr  sets ignition needed flag
///
/// \param  boolean boIgnitionReq
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_SetFailIgnitionNeeded(boolean boIgnitionReq)
{
  // set request for ignition
  CtrlDcm_boIgnitionNeeded = boIgnitionReq;
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
boolean CtrlDcm_RetPowerTrainActive(void)
{
  return CtrlDcm_boPowertrainActive;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RetVehIgnition
///
/// \descr  return ignition conditions fulfillment
///
/// \param  none
///
/// \return boolean - VehIgnition
//-----------------------------------------------------------------------------
boolean CtrlDcm_RetVehIgnition(void)
{
  return CtrlDcm_boConVehIgnition;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboTrainingState
///
/// \descr  Operation requested from PWF, cont. movement or inscenation
///
/// \param  none
///
/// \return boolean - Reference run request active
//-----------------------------------------------------------------------------
boolean CtrlDcm_ReturnboTrainingState(void)
{
  return CtrlDcm_boTrainingState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboSensorError
///
/// \descr  returns sensor error status
///
/// \param  none
///
/// \return teCtrlDcm_SensorState
//-----------------------------------------------------------------------------
teCtrlDcm_SensorState CtrlDcm_ReturneSensorError(void)
{
  return CtrlDcm_eSensorError;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboLvlAdjFuncFault
///
/// \descr  returns levelling adjust functional fault status
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_ReturnboLvlAdjFuncFault(void)
{
  return CtrlDcm_boLvlAdjFuncFault;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboSlaveLvlAdjFuncFault
///
/// \descr  returns levelling adjust functional fault status for slave
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_ReturnboSlaveLvlAdjFuncFault(void)
{
  return CtrlDcm_boSlaveLvlAdjFuncFault;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboLvlAdjHeadlampFault
///
/// \descr  returns levelling adjust headlamp fault status
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_ReturnboLvlAdjHeadlampFault(void)
{
  return CtrlDcm_boLvlAdjHeadlampFault;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboLvlAdjHeadlampFault_R
///
/// \descr  returns levelling adjust headlamp fault status for slave
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_ReturnboLvlAdjHeadlampFault_R(void)
{
  return CtrlDcm_boLvlAdjHeadlampFault_R;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ReturnboExtTakeOver
///
/// \descr  returns takeover status needed for diag takeover
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_ReturnboExtTakeOver(void)
{
  return CtrlDcm_boDiagDcmOn;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SetSignalMode
/// 
/// \descr  Sets CtrlDcm target source
///
/// \param  teCtrlDcm_SignalSrc eMode
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_SetSignalMode(teCtrlDcm_SignalSrc eMode)
{
  CtrlDcm_SignalSrc = eMode;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_GetTgtPos
///
/// \descr  Calculate Pos, Tmin and Stop based on selected source
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_GetTgtPos(void)
{
#ifdef UNIT_TEST
    extern  sint16 snPosMinASL;
    extern  sint16 snPosMaxASL;
    
#else
    sint16 snPosMinASL = Cod_DcmMinAdjASL();
    sint16 snPosMaxASL = Cod_DcmMaxAdjASL();
#endif 
    NM_ModeType NMMode = { 0 };
    uint16 unPosMinASL = (uint16)UTIL_ABS(snPosMinASL);
    uint16 unPosMaxASL = (uint16)UTIL_ABS(snPosMaxASL);
    sint16 snSafetyPos = Cod_DcmSp();
  

  // Get life phases from the NM
  (void)NM_GetMode(&NMMode);

  switch (CtrlDcm_SignalSrc)
  {
    case eDcmSrc_SleepPos:    // go to sleep mode
      CtrlDcm_boStop = TRUE;
      break;

    case eDcmSrc_NormalPos:   // set values according to vehicle attitude
      CtrlDcm_nTgtPos   = CtrlDcm_LimitAngle(unPosMinASL, unPosMaxASL, CtrlDcm_nPosReq);
      CtrlDcm_boStop    = (NMMode == LIMP_HOME_MODE) ? TRUE : FALSE;
      break;

    case eDcmSrc_DiagPos:     // goto position requested by diagnostic service "steuern_routine"
      CtrlDcm_nTgtPos   = CtrlDcm_nDiagPos;
      //CtrlDcm_boStop    = (CtrlDcm_sStpControlRequest.eStpDID == CtrlDcm_eDF11) ? TRUE : FALSE; // move only the slave if DF11 routine is requested
      CtrlDcm_boStop = FALSE;
      break;

    case eDcmSrc_SafetyPos:   // goto safety position (so called SP)
      CtrlDcm_boStop    = FALSE;
      if (snSafetyPos < CtrlDcm_nLastPosReq)
      {
        CtrlDcm_nTgtPos = snSafetyPos;
      }
      else
      {
        // keep previous value
      }
      break;


    default:
      break;
  }
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
void CtrlDcm_ReadCommonSignals(void)
{
  CtrlDcm_ReadEnvironmentSignals();  // PWF and LB/HB on/off conditions
  CtrlDcm_ReadStatusSignals();       // status signals from CddDcm
  CtrlDcm_ReadLvlAdjFunctionalFaultStatus(); // read adjustment functional failure
  CtrlDcm_ReadLvlAdjHeadlampFaultStatus();   // read adjustment headlamp failure
  CtrlDcm_DiagDcmTakeOver(); // check if there is a request for exterior takeover
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_DiagDcmTakeOver
///
/// \descr  Takeover of the DC motor using the diag routine control
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_DiagDcmTakeOver(void)
{
  uint8 ucVESMainState = (uint8)VESState_Invalid;
  static uint8 ucLastStartRequest = 0u;

  ucVESMainState = CtrlDcm_RteAccess_ReadVESMainState();

  // Get Dcm Control Routine
  CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_sDcmControlRequest);

  // Reset takeover flag if engine is running
  if (ucVESMainState == (uint8)VESState_Start)
  {
    // Set Dcm Status Off
    CtrlDcm_boDiagDcmOn = FALSE;
  }
  // Check the Diag Request status and Diagnostic Request (Start)
  else if ((CtrlDcm_sDcmControlRequest.boRequestStatus != FALSE) && (CtrlDcm_sDcmControlRequest.eDcmControl == CtrlDcm_eDcmControl_Start))
  {
    // Set Dcm Status On
    CtrlDcm_boDiagDcmOn = TRUE;
    // Set Acknowledge in order to handle the Diagnostic Result
    CtrlDcm_RteAccess_WriteDcmRoutineAck(TRUE);

    if (CtrlDcm_sDcmControlRequest.ucStartSequence != ucLastStartRequest)
    {
      // Prepare the flag for sequence start when the sequence start is requested
      CtrlDcm_boStartSequence = TRUE;
    }
    else
    {
      // do nothing
    }
    ucLastStartRequest = CtrlDcm_sDcmControlRequest.ucStartSequence;
  }
  // Check the Diag Request status and Diagnostic Request (Stop)
  else if ((CtrlDcm_sDcmControlRequest.boRequestStatus != FALSE) && (CtrlDcm_sDcmControlRequest.eDcmControl == CtrlDcm_eDcmControl_Stop))
  {
    // Set Dcm Status Off
    CtrlDcm_boDiagDcmOn = FALSE;
    // Prepare the flag for sequence start when the sequence start is requested
    CtrlDcm_boStartSequence = TRUE;
    // Clear Acknowledge in order to handle the Diagnostic Result
    CtrlDcm_RteAccess_WriteDcmRoutineAck(FALSE);
    // Reset side flag to make sure that no side will remain blocked
    CtrlDcm_sDcmControlRequest.eDcmSide = CtrlDcm_eBothActuators;
  }
  else
  {
    // None of the previous states (no Dcm request or Request is Result)
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SetDiagRequest
///
/// \descr  Set the request needed for the takeover
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
#if 0
 STATIC_AL void CtrlDcm_SetDiagRequest(void)
{
  // Diagnostic Control over Dcm
  if ((CtrlDcm_boDiagDcmOn != FALSE) && ((CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDF11) || (CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDF12) || (CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDF13)))
  {
    // Is request different than sequence
    if ((CtrlDcm_sDcmControlRequest.eDcmRequest != CtrlDcm_eSequence1) && (CtrlDcm_sDcmControlRequest.eDcmRequest != CtrlDcm_eSequence2))
    {
      // Set current state
      CtrlDcm_eCurrentDiagState = CtrlDcm_sDcmControlRequest.eDcmRequest;
    }
    // First sequence request
    else if (CtrlDcm_sDcmControlRequest.eDcmRequest == CtrlDcm_eSequence1)
    {
      // Run the sequence
      CtrlDcm_eCurrentDiagState = CtrlDcm_DiagSequenceMachine(CtrlDcm_aeDiagSequence1, sizeof(CtrlDcm_aeDiagSequence1) / sizeof(CtrlDcm_aeDiagSequence1[0]));
    }
    // Second sequence request
    else
    {
      // Run the sequence
      CtrlDcm_eCurrentDiagState = CtrlDcm_DiagSequenceMachine(CtrlDcm_aeDiagSequence2, sizeof(CtrlDcm_aeDiagSequence2) / sizeof(CtrlDcm_aeDiagSequence2[0]));
    }
  }
  else 
  {
    // No Diag request, set Dcm stop == control using vehicle attitude
    CtrlDcm_eCurrentDiagState = CtrlDcm_eStop;
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_DiagSequenceMachine
///
/// \descr Dcm sequence machine for routine control
///
/// \param  psData - sequence array
///
/// \return STATIC_AL teCtrlDcm_DcMotorRoutineControlRequest
//-----------------------------------------------------------------------------
#if 0
STATIC_AL teCtrlDcm_DcMotorRoutineControlRequest CtrlDcm_DiagSequenceMachine(CONST_AL teCtrlDcm_DcMotorRoutineControlRequest* psData, uint8_least ucLength)
{
  // Dcm Sequence Return
  STATIC_UT(teCtrlDcm_DcMotorRoutineControlRequest, eReturnState, CtrlDcm_eStop);
  // Sequence Index
  STATIC_UT(uint8_least, ucIndx, 0u);
  // Diag start is requested
  if (CtrlDcm_boStartSequence == TRUE)
  {
    // return the first state of sequence
    eReturnState = psData[0];
    // Reset the sequence index
    ucIndx = 0u;
    // Get the time
    CtrlDcm_ulDiagSequenceTimer = TimerGetTick();
    // Clear the sequence start flag
    CtrlDcm_boStartSequence = FALSE;
  }
  else
  {
    // Time-Out on sequence step
    if (TimerGetTimeSince(CtrlDcm_ulDiagSequenceTimer) >= UTILTIME_MSEC(CTRLDCM_DIAG_SEQUENCE_TIME_MS))
    {
      // Increment the step or stop at the end
      ucIndx = (ucIndx == ucLength - 1u) ? ucIndx : (ucIndx + 1u);
      // Get the time
      CtrlDcm_ulDiagSequenceTimer = TimerGetTick();
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
#endif

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_SetDiagPos
///
/// \descr set DC motor position for routine control
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_SetDiagPos(void)
{
  // Set diag target position according to the current request
#if 0
  if ((CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDF11) || (CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDF12) || (CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDF13))
  {
    switch (CtrlDcm_eCurrentDiagState)
    {
    case CtrlDcm_eMovementToTop:
      CtrlDcm_nDiagPos = 0;// (sint16)Cod_LwrMaxWinkelPl();
      break;
    case CtrlDcm_eMovementToBottom:
      CtrlDcm_nDiagPos = 0;// -(sint16)Cod_LwrMaxWinkelMi();
      break;
    case CtrlDcm_eMovementToZero:
      CtrlDcm_nDiagPos = 0;
      break;
    default:
      break;
    }
  }
  else 
#endif
    if (CtrlDcm_sDcmControlRequest.eDcmDID == CtrlDcm_eDD06)
  {
    CtrlDcm_nDiagPos = (sint16)((sint16)CtrlDcm_sDcmControlRequest.ucPosRequest * 10 - CTRLDCM_ZERO_POS) * CTRLDCM_POS_NOMINATOR / CTRLDCM_POS_DENOMINATOR; // %Vbat to [0.01 deg]
    CtrlDcm_SetSignalMode(eDcmSrc_DiagPos);
  }
  else
  {
    // no behavior
  }
}

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_DiagRoutineControl
///
/// \descr set DC motor position for routine control
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_DiagRoutineControl(void)
{
#if 0
  // Get the request value from the routine control
  CtrlDcm_SetDiagRequest();
#endif
  // Get diag target pos
  CtrlDcm_SetDiagPos();
}

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_WriteValidationFrames
///
/// \descr write information needed for validation frames
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if 0
STATIC_AL void CtrlDcm_WriteValidationFrames(void)
{
  tsCtrlDcm_DiagStatus sLvlValidationFrames;

  CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0(&sLvlValidationFrames);

  sint16 snTgtPosDegree = 0;// CtrlStp_StpPos2Angle(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CtrlStp_nTgtPos);
  sint16 snActPosDegree = 0;// CtrlStp_StpPos2Angle(Cod_LwrHsGrad(), Cod_LwrAnschlagMi(), CtrlStp_ActAll.sLwrActual.nPosition);

  /*sLvlValidationFrames.sValidationFrames.boLvl_Elec_Defect  = (CtrlDcm_DiagStatus.eStatDcmElectricDefect         != CtrlDcm_eLvlElecR_NoDefect        ) ? TRUE : FALSE;
  sLvlValidationFrames.sValidationFrames.boLvl_Temp_Defect  = (CtrlDcm_DiagStatus.eStatDcmThermalState           != CtrlDcm_eLvlTemperatureR_NoWarning) ? TRUE : FALSE;*/
  sLvlValidationFrames.sValidationFrames.boLvl_Moving = FALSE;// (CtrlDcm_ActAll.sLwrActual.sStatusError.boIsMoving != FALSE) ? TRUE : FALSE;
  sLvlValidationFrames.sValidationFrames.snLvl_Degree_Ctrl  = snTgtPosDegree * 10 * CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_NUMERATOR / CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_DENOMINATOR;;
  sLvlValidationFrames.sValidationFrames.snLvl_Pos_Feedback = snActPosDegree * 10 * CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_NUMERATOR / CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_DENOMINATOR;;

  CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0(sLvlValidationFrames);
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_WriteMasterSignals
///
/// \descr  writes signals from master 
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_WriteMasterSignals(void)
{
#ifdef UNIT_TEST
    extern sint16 nSafetyPos;
#else
    sint16 nSafetyPos = Cod_DcmSp();
#endif

  sint16 nPosReqRad = 0;
  uint16 unSafetyPosRad = (uint16)UTIL_ABS(nSafetyPos) * (uint16)CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_NUMERATOR / (uint16)CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_DENOMINATOR;
  boolean boErrorDiag = CtrlDcm_GetDiagLvl();
  boolean boSlaveStopRequest = ((CtrlDcm_boTrainingState == FALSE) || (CtrlDcm_boSlaveStop == TRUE)) ? TRUE : FALSE;

  // signals for CddDcm
  CtrlDcm_TgtAll.sDcmTarget.nPosition = CtrlDcm_nTgtPos;

  if ((CtrlDcm_boIgnitionNeeded != FALSE) && (CtrlDcm_SignalSrc != eDcmSrc_SafetyPos))
  {
    CtrlDcm_TgtAll.sDcmTarget.boStop = TRUE;
  }
  else
  {
    CtrlDcm_TgtAll.sDcmTarget.boStop = CtrlDcm_boStop;
  }

  CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(&CtrlDcm_TgtAll);

  // write left signals
  (void)CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(&CtrlDcm_sLevellingSignalsFromLeftToRight);
  nPosReqRad = CtrlDcm_nPosReq * CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_NUMERATOR / CTRLDCM_VEHICLE_ATTITUDE_RAD_RESOLUTION_DENOMINATOR;

  // set target value for slave if stop is not requested
  if (CtrlDcm_boSlaveSafetyPos != FALSE) // set command to safety position
  {
    CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;

    if (nSafetyPos < CtrlDcm_nLastPosReq)
    {
      CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = unSafetyPosRad; // set safety position only if previous position was higher than safety position
    }
    else
    {
      // keep previous value
    }
  }
  else if ((boSlaveStopRequest == FALSE) && (CtrlDcm_boIgnitionNeeded == FALSE))
  {
    if (CtrlDcm_nPosReq > 0)
    {
      CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl             = CtrlDcm_eSigneConsigneSiteD_Positive;
      CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = (uint16)nPosReqRad;
    }
    else
    {
      CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl             = CtrlDcm_eSigneConsigneSiteD_Negativ;
      CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = (uint16)(-nPosReqRad);
    }
  }
  else
  {
    // keep previous value
  }

  CtrlDcm_nLastPosReq = CtrlDcm_TgtAll.sDcmTarget.nPosition;

  CtrlDcm_RteAccess_Write_DrvLedDiag_Port(boErrorDiag);

  CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_VALID;

  CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(&CtrlDcm_sLevellingSignalsFromLeftToRight);


  // write diagnostic status
  //CtrlDcm_GetDiagStatus(); tbd

  // write validation frames
  //CtrlDcm_WriteValidationFrames(); tbd
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_WriteSlaveSignals
///
/// \descr writes signals from slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_WriteSlaveSignals(void)
{
  boolean boDiagLvlR = FALSE;

  // signals for CddDcm
  CtrlDcm_TgtAll.sDcmTarget.nPosition = CtrlDcm_nTgtPos;

  if ((CtrlDcm_boIgnitionNeeded != FALSE) && (CtrlDcm_SignalSrc != eDcmSrc_SafetyPos))
  {
    CtrlDcm_TgtAll.sDcmTarget.boStop = TRUE;
  }
  else
  {
    CtrlDcm_TgtAll.sDcmTarget.boStop = CtrlDcm_boStop;
  }

  (void)CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(&CtrlDcm_TgtAll);

  CtrlDcm_nLastPosReq = CtrlDcm_TgtAll.sDcmTarget.nPosition;

  if (((CtrlDcm_sErrorStatus.boElecBAT != FALSE)   ||
       (CtrlDcm_sErrorStatus.boElecGND  != FALSE)  ||
       (CtrlDcm_boSlaveLvlAdjFuncFault  != FALSE)) && (CtrlDcm_boConVehIgnition != FALSE))
  {
    boDiagLvlR = TRUE; // set DIAG_LVL_R to be sent immediately to L_LDM
  }
  else
  {
    boDiagLvlR = FALSE;
  }

  CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = (boDiagLvlR != FALSE) ? TRUE : FALSE;

  // write diagnostic status
  //CtrlDcm_GetDiagStatus(); tbd

  // write DIAG_LVL_R
  CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR);

  // write validation frames
  //CtrlDcm_WriteValidationFrames(); tbd
}

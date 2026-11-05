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
/// \file  DblCrSm.c
///
/// \brief  Calculate curvature:
///
/// \desc   This module is a state machine for Vehicle Path Curvature
///
///  \author  CALUGAR Radu - ALRO-CJ (M01472A)
///           mailTo:radusilviu.calugar[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <Cfg/Cfg.h>
#include "DblData.h"
#include "Dbl_RteAccess.h"
#include "DblCrCalc.h"
#include "DblCrState.h"
#include <ClAlg.h>

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version

//=============================================================================
// defines
//=============================================================================

#define DBLCRSTATE_NUMBER_OF_TIMERS                                    1u
#define DBLCRSTATE_SIG_QTY_INVALID_TIMER_SEL                           0u


//=============================================================================
// function prototype
//=============================================================================
STATIC_AL boolean               DblCrState_Transition_CalculationPhase_Nominal_to_Invalid(void);
STATIC_AL boolean               DblCrState_Transition_CalculationPhase_Invalid_to_Nominal(void);
STATIC_AL boolean               DblCrState_Transition_CalculationMode_Available_to_Unavailable(void);
STATIC_AL boolean               DblCrState_Transition_CalculationMode_Unavailable_to_Available(void);
STATIC_AL boolean               DblCrState_PowerTrain_State(void);
STATIC_AL boolean               DblCrState_HandleDelayStatus(tsDblCrState_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel);
STATIC_AL boolean               DblCrState_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel);

//=============================================================================
// global variables
//=============================================================================
STATIC_AL tsDblCrState_TimerCfg DblCrState_sTimerCfg[DBLCRSTATE_NUMBER_OF_TIMERS];
STATIC_AL uint16                DblCrState_unEgoVehicleMotionConfirmation = 0;
STATIC_AL boolean               DblCrState_boSigQty_TimeoutFlag = FALSE;

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief DblCrState_State_Machine
///
/// \descr This function sets curvature state machine and gets curvature value
///
/// \param  void
///
/// \return  slVehPathCurvature
//-----------------------------------------------------------------------------
sint32 DblCrState_State_Machine(void)
{
  static sint32 slVehPathCurvature = 0;

  if (DblCrState_Transition_CalculationMode_Unavailable_to_Available() != FALSE)
  {
    Dbl_sCurvatureData.sCurvatureState.eCalculationMode = eDbl_Available;

    if (DblCrState_Transition_CalculationPhase_Nominal_to_Invalid() != FALSE)
    {
      Dbl_sCurvatureData.sCurvatureState.eCalculationPhase = eDbl_Invalid;
      slVehPathCurvature = DBL_CURVATURE_INVALID_VALUE;
    }
    else
    {
      // do nothing
    }

    if (DblCrState_Transition_CalculationPhase_Invalid_to_Nominal() != FALSE)
    {
      Dbl_sCurvatureData.sCurvatureState.eCalculationPhase = eDbl_Nominal;
      slVehPathCurvature = DblCrvCalc_getCurvatureValue();

    }
    else
    {
      // do nothing
    }
  }
  else
  {
    if (DblCrState_Transition_CalculationMode_Available_to_Unavailable() != FALSE)
    {
      Dbl_sCurvatureData.sCurvatureState.eCalculationMode = eDbl_Unavailable;
      slVehPathCurvature = 0;
    }
  }

  return slVehPathCurvature;
}

//-----------------------------------------------------------------------------
/// \brief DblCrState_Init
///
/// \descr  Curvature state machine init phase
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
void DblCrState_Init(void)
{
  Dbl_sCurvatureData.sCurvatureState.eCalculationMode = eDbl_Unavailable;
  Dbl_sCurvatureData.sCurvatureState.eCalculationPhase = eDbl_Nominal;
  Dbl_sCurvatureData.slCurvatureRawValue = 0;
  Dbl_sCurvatureData.slCurvatureProcessedValue = 0;
  Dbl_sCurvatureData.slCurveRadiusValue = 0;
  Dbl_sCurvatureData.slCrcRadiusYaw = 0;
  Dbl_sCurvatureData.slCrcRadiusSteering = 0;
  Dbl_sCurvatureData.ucWf = 0u;
  DblCrState_unEgoVehicleMotionConfirmation = CodEgo_Vehicle_Motion_Confirmation_Time();
}

//-----------------------------------------------------------------------------
/// \brief DblCrState_Transition_CalculationMode_Available_to_Unavailable
///
/// \descr Curvature state machine transition
///
/// \param  void
///
/// \return boolean boRet
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_Transition_CalculationMode_Available_to_Unavailable(void)
{
  boolean boPowerTrain = FALSE, boRet = FALSE;
  tsDbl_SteeringWheelAngle sSteeringWheelAngle = { 0 };
  boPowerTrain         = DblCrState_PowerTrain_State();
  sSteeringWheelAngle  = Dbl_RteAccess_ReadSteeringWheelAngle();

  if ((boPowerTrain == FALSE) ||                                                 //powertrain is not running
      (sSteeringWheelAngle.nSteeringWheelAngle == DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE))  // Curvature init in progress value
  {
    boRet = TRUE;
  }
  else
  {
    boRet = FALSE;
  }
  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief DblCrState_Transition_CalculationMode_Unavailable_to_Available
///
/// \descr Curvature state machine transition
///
/// \param  void
///
/// \return boolean boRet
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_Transition_CalculationMode_Unavailable_to_Available(void)
{
  boolean boPowerTrain = FALSE, boRet = FALSE;
  tsDbl_SteeringWheelAngle sSteeringWheelAngle = { 0 };
  boPowerTrain = DblCrState_PowerTrain_State();
  sSteeringWheelAngle = Dbl_RteAccess_ReadSteeringWheelAngle();

  if ((boPowerTrain != FALSE) && //powertrain is running
      (sSteeringWheelAngle.nSteeringWheelAngle != DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE)) // Curvature init in progress value
  {
    boRet = TRUE;
  }
  else
  {
    boRet = FALSE;
  }
  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief  DblCrState_Transition_CalculationPhase_Invalid_to_Nominal
///
/// \descr Curvature state machine transition
///
/// \param  void
///
/// \return boolean boRet
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_Transition_CalculationPhase_Invalid_to_Nominal(void)
{
  boolean boRet                                = FALSE;
  tsDbl_VehicleSpeed  sDblSpeed                = { 0 };
  tsDbl_YawSpeed sYawSpeed                     = { 0 };
  tsDbl_SteeringWheelAngle sSteeringWheelAngle = { 0 };

  teDbl_SigQty eElecSigQty = Dbl_RteAccess_ReadEtatReseauElec();
  sDblSpeed                = Dbl_RteAccess_ReadVehicleSpeed();
  sYawSpeed                = Dbl_RteAccess_ReadYawSpeed();
  sSteeringWheelAngle      = Dbl_RteAccess_ReadSteeringWheelAngle();

  if ((eElecSigQty                 != Dbl_SIG_INVALID)   && // elec state is valid
      (sDblSpeed.eSigQty           != Dbl_SIG_INVALID)   && // vehicle speed is known
      (sYawSpeed.eSigQty           != Dbl_SIG_INVALID)   && // yaw rate is available
      (sSteeringWheelAngle.eSigQty != Dbl_SIG_INVALID))     // steering wheel angle is available
  {
    boRet = TRUE;
  }
  else
  {
    boRet = FALSE;
  }
  return boRet;
}

//-----------------------------------------------------------------------------
/// \brief DblCrState_Transition_CalculationPhase_Nominal_to_Invalid
///
/// \descr Curvature state machine transition
///
/// \param  void
///
/// \return boolean boRet
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_Transition_CalculationPhase_Nominal_to_Invalid(void) 
{

  boolean                  boRet                                     = FALSE;
  tsDbl_VehicleSpeed       sDblSpeed                                 = { 0 };
  tsDbl_YawSpeed           sYawSpeed                                 = { 0 };
  tsDbl_SteeringWheelAngle sSteeringWheelAngle                       = { 0 };

  uint32 ulSignalInvalidTimeout = DblCrState_unEgoVehicleMotionConfirmation;
  sDblSpeed              = Dbl_RteAccess_ReadVehicleSpeed();
  sYawSpeed              = Dbl_RteAccess_ReadYawSpeed();
  sSteeringWheelAngle    = Dbl_RteAccess_ReadSteeringWheelAngle();
  teDbl_SigQty eElecSigQty = Dbl_RteAccess_ReadEtatReseauElec();

  if ((eElecSigQty                  != Dbl_SIG_VALID)    || // elec state is not valid
      (sDblSpeed.eSigQty            != Dbl_SIG_VALID)    || // speed is unknown
      (sYawSpeed.eSigQty            != Dbl_SIG_VALID)    || // yaw rate is invalid
      (sSteeringWheelAngle.eSigQty  != Dbl_SIG_VALID))      // steering wheel angle is invalid
  {
    // wait EGO_VEHICLE_MOTION_CONFIRMATION_TIME ms
    DblCrState_boSigQty_TimeoutFlag = DblCrState_Timeout(TRUE, ulSignalInvalidTimeout, DBLCRSTATE_SIG_QTY_INVALID_TIMER_SEL);
  }
  else
  {
    boRet = FALSE;
    DblCrState_boSigQty_TimeoutFlag = DblCrState_Timeout(FALSE, ulSignalInvalidTimeout, DBLCRSTATE_SIG_QTY_INVALID_TIMER_SEL);
  }

  // check timers
  if (DblCrState_boSigQty_TimeoutFlag != FALSE) 
  {
    boRet = TRUE;
    DblCrState_boSigQty_TimeoutFlag = FALSE;
  }
  else
  {
    boRet = FALSE;
  }

  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief DblCrState_PowerTrain_State
///
/// \descr store powertrain state
///
/// \param  void
///
/// \return boRet
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_PowerTrain_State(void)
{
  tsDbl_VehNetState    sElectricNetworkState = { 0 };
  static boolean  boRet = FALSE;
  sElectricNetworkState = Dbl_RteAccess_ReadVehicleElectricState();
  if ((sElectricNetworkState.eSigQty == DBL_VNS_SIG_VALID) && (sElectricNetworkState.eElectricNetworkState != eDblInvalid))
  {
    switch (sElectricNetworkState.eElectricNetworkState)
    {
    case eDblTA_NOMINAL: 
    case eDblTA_DEGRADE:
    case eDblTA_SECU:
    case eDblREDEMARRAGE:
      boRet = TRUE;
      break;
    case eDblTI_NOMINAL:
    case eDblTI_DEGRADE:
    case eDblTI_DISPO_DEM:
    case eDblDEMARRAGE:
      boRet = FALSE;
      break;
    default:
      break;
    }
  }
  return boRet;
}

//-----------------------------------------------------------------------------
/// \brief  DblCrState_Timeout
///
/// \descr  This function returns timer status
///
/// \param  boReqInput, ulTimeMs, scTiTimerSel
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel)
{
  boolean boTimerTimeoutStatus = FALSE;
  if (ucTiTimerSel < DBLCRSTATE_NUMBER_OF_TIMERS)
  {
    DblCrState_sTimerCfg[ucTiTimerSel].ulTimeMs_Input = ulTimeMs;
    DblCrState_sTimerCfg[ucTiTimerSel].boReq_Input = boReqInput;
    boTimerTimeoutStatus = DblCrState_HandleDelayStatus(DblCrState_sTimerCfg, ucTiTimerSel);
  }
  return boTimerTimeoutStatus;
}

//-----------------------------------------------------------------------------
/// \brief  DblCrState_HandleDelayStatus
///
/// \descr  This function return TimeOut = TRUE based on sTimersCfg Configurations
///
/// \param  *sTimersCfg, scTimerSel
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean DblCrState_HandleDelayStatus(tsDblCrState_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel)
{
  // Input request (start timer or reset)
  if (psTimersCfg[ucTimerSel].boReq_Input != FALSE)
  {
    // Start Timer
    if (psTimersCfg[ucTimerSel].boStartStopTimer == FALSE)
    {
      psTimersCfg[ucTimerSel].ulCommandStart = UTILTIME_TIMER_START(UTILTIME_MSEC(psTimersCfg[ucTimerSel].ulTimeMs_Input));
      psTimersCfg[ucTimerSel].boStartStopTimer = TRUE;
    }
  }
  else
  {
    // Reset timer and reinit all timers values
    psTimersCfg[ucTimerSel].boTimeOut = FALSE;
    psTimersCfg[ucTimerSel].boStartStopTimer = FALSE;
    psTimersCfg[ucTimerSel].ulCommandStart = 0u;
  }

  // Timer still running ?
  if (psTimersCfg[ucTimerSel].boStartStopTimer != FALSE)
  {
    // Let it run
    psTimersCfg[ucTimerSel].boTimeOut = UTILTIME_TIMER_TIMEOUT(psTimersCfg[ucTimerSel].ulCommandStart);
  }
  else
  {
    // do nothing
  }


  return psTimersCfg[ucTimerSel].boTimeOut;
}


#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// ---------------------------------------------------------------------------
///
///  \file    DblcSm.c
///
///  \author  FUTO Henrietta - EEG-PM4 (F31185D)
///           mailTo:henrietta-helena.futo[at]marelli.com
///
///  \owner   FUTO Henrietta - EEG-PM4 (F31185D)
///           mailTo:henrietta-helena.futo[at]marelli.com
///
///  \date    05.05.2017
///
///  \brief   dynamic bending light control
///
///  \descr   dynamic bending light control
///
/// ---------------------------------------------------------------------------

#include <Cfg/Cfg.h>
#include "ClAlg.h"
#include "ClLrRelation.h"
#include "DblSwiveling.h"
#include "DblIdle.h"
#include "DblData.h"
#include "DblcSm.h"
#include <UtilMath.h>
#include <DblCrCalc.h>
#include <UtilUtility.h>
#include <UtilDebounce.h>
#include <Util_Time.h>
#include "Dbl_RteAccess.h"
#include <Swc/FctR/FctR_Types.h>
#include <CodM.h>
#include "DblCrState.h"
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version


//****************************************************************************
// Defines
//****************************************************************************

#define DBL_NUMBER_OF_TIMERS                            2u
#define DBL_SIG_QTY_INVALID_TIMER_SEL                   0u
#define DBL_SIG_QTY_UNAVAILABLE_TIMER_SEL               1u

//****************************************************************************
// GLOBAL VARIABLES
//****************************************************************************

//Coding Data
tsRteCodingParameters                                   Dbl_sCodingParam;  // pointer to const data
boolean                                                 Dbl_boIsCodingValid = TRUE; 
// State machine
STATIC_AL tDbl_State                                    Dbl_sState = { Dbl_eState_Init, TRUE };
STATIC_AL teDbl_eMainMode                               Dbl_eMainMode = Dbl_eModeAssembly;
STATIC_AL teDbl_eSubMode                                Dbl_eSubMode = Dbl_eSubModeUnavailable;

STATIC_AL tUtilDebounceControl                          Dbl_sSwivelBckTimer;
STATIC_AL tuDblDriveSituation                           Dbl_sDriveSituation;

STATIC_AL boolean                                       Dbl_boPowertrainActive = FALSE;
STATIC_AL boolean                                       Dbl_boSwivelingFunctionalFault_LR;
STATIC_AL boolean                                       Dbl_boDYN_BENDING_BEAM_FAULT;
STATIC_AL teDbl_MountingSide                            Dbl_eMountingSide = { 0 };
STATIC_AL boolean                                       Dbl_boErrorFromOtherHL;
STATIC_AL tsDbl_SwivellingOut                           Dbl_sMsgOut; // Output swivel angle 
STATIC_AL boolean                                       Dbl_boCurvature_SigQty_ERR = FALSE;
STATIC_AL boolean                                       Dbl_boCurvature_UNAV = FALSE;
STATIC_AL TIMER                                         Dbl_ulTimerSigQty_Inv = 0u;
STATIC_AL TIMER                                         Dbl_ulTimerSigQty_Unav = 0u;
STATIC_AL sint32                                        Dbl_slanHLAFilter[DBLC_HLAFILTERSIZE];  ///< head light angle filter 
STATIC_AL sint32                                        Dbl_slnHlaOut;                          ///< current swivelling angle
STATIC_AL tDblcSignal                                   Dbl_sSignal = { 0 };
STATIC_AL sint16                                        Dbl_snSwivelAngleLeft = 0;
STATIC_AL sint16                                        Dbl_snSwivelAngleRight = 0;
STATIC_AL tUtilDebounceControl                          Dbl_HighSpeedTimer;
STATIC_AL tUtilDebounceControl                          Dbl_SwivelBckTimer;
STATIC_AL tuDblDriveSituation                           Dbl_DriveSituation;
STATIC_AL boolean                                       Dbl_boHB = FALSE;
STATIC_AL teTraffic                                     Dbl_eTrafficSide;
STATIC_AL teDbl_DynBendingBeamFault                     Dbl_eErrorStatus;
STATIC_AL boolean                                       Dbl_boL_Internal_Failure;
STATIC_AL boolean                                       Dbl_boR_Internal_Failure;
STATIC_AL boolean                                       Dbl_boEtatMar = FALSE;
STATIC_AL boolean                                       Dbl_boFailureTimerFlag_Inv = FALSE;
STATIC_AL boolean                                       Dbl_boFailureTimerFlag_Unav = FALSE;
STATIC_AL tsDbl_TimerCfg                                Dbl_sTimerCfg[DBL_NUMBER_OF_TIMERS];
STATIC_AL tsDbl_FilteredCalculatedCurvatureData         Dbl_sCrCalcFilterData = {0};
STATIC_AL uint16                                        Dbl_unEgoMotionTime = 0u;
//****************************************************************************
// Prototypes
//****************************************************************************

STATIC_AL  void    Dbl_ConstHighSpeed_Detect(sint32 snSpeed);
STATIC_AL  void    Dbl_ModeAssembly(void);
STATIC_AL  void    Dbl_ModeCustomer(void);
 
STATIC_AL  void    Dbl_StateMachine_StateInit(void);
STATIC_AL  void    Dbl_StateMachine_StateFail(void);
STATIC_AL  void    Dbl_StateMachine_StateNominal(void);
STATIC_AL  void    Dbl_StateMachine_StateAdj(void);

STATIC_AL  void    Dbl_Call_StateOff(void);
STATIC_AL  void    Dbl_Call_StateHold(void);
STATIC_AL  void    Dbl_Call_StateNormal(void);

STATIC_AL  void    Dbl_SubModeFrozen(void);
STATIC_AL  void    Dbl_SubModeUnavailable(void);
STATIC_AL  void    Dbl_Reset_Flags(void);
STATIC_AL  void    Dbl_StMch(void);

STATIC_AL boolean  Dbl_Transition_Init_To_Nominal(void);
STATIC_AL boolean  Dbl_Transition_Init_To_Fail(void);
STATIC_AL boolean  Dbl_Transition_Nominal_To_Adj(void);
STATIC_AL boolean  Dbl_Transition_Nominal_To_Fail(void);
STATIC_AL boolean  Dbl_Transition_Adj_To_Nominal(void);
STATIC_AL boolean  Dbl_Transition_Adj_To_Fail(void);
STATIC_AL boolean Dbl_Transition_Adj_To_Init(void);
STATIC_AL boolean Dbl_Transition_Nominal_To_Init(void);
STATIC_AL boolean  Dbl_Transition_Fail_To_Init(void);
STATIC_AL boolean  Dbl_Transition_Fail_To_Adj(void);
STATIC_AL boolean  Dbl_Transition_Fail_To_Nominal(void);
STATIC_AL boolean  Dbl_Transition_Init_To_Adj(void);
STATIC_AL boolean  Dbl_Transition_Assembly_To_Frozen(void);
STATIC_AL boolean  Dbl_Transition_Customer_To_Unavailable(void);
STATIC_AL boolean  Dbl_Transition_Customer_To_Available(void);

STATIC_AL teDbl_DynBendingBeamFault  Dbl_ReadFault(teDbl_MountingSide eSide);
STATIC_AL boolean  Dbl_RetDigitalSwivelingFunctionalFault_LR(void);
STATIC_AL boolean  Dbl_RetPowerTrainActive(void);

STATIC_AL void     Dbl_DetectSide(void);
STATIC_AL void     Dbl_Call_StateFailure(void);

STATIC_AL boolean Dbl_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel);
STATIC_AL boolean Dbl_HandleDelayStatus(tsDbl_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel);

STATIC_AL sint32 Dbl_Get_Filtered_Calculated_Curvature_Value(sint32 lCurvatureCalculated);
STATIC_AL sint32 Dbl_FilterIIR_Input(sint32 nNewSample);
STATIC_AL void Dbl_Get_Calculated_Curvature_Coding_Parameters(void);
STATIC_AL teRte_SigQty Dbl_Curvature_SigQty(void);

// ---------------------------------------------------------------------------
// Transition function table for ucIx state Dbl_eStateInit
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tTransitionDbl Dbl_atTransitionInit[3] =
{
  //  new state                  transition function
  { Dbl_eState_Nominal,       Dbl_Transition_Init_To_Nominal     },
  { Dbl_eState_Adj,           Dbl_Transition_Init_To_Adj         },
  { Dbl_eState_Fail,          Dbl_Transition_Init_To_Fail        },
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state Dbl_eStateNominal
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tTransitionDbl Dbl_atTransitionNominal[3] =
{
  //  new state                  transition function
  { Dbl_eState_Adj,        Dbl_Transition_Nominal_To_Adj     },
  { Dbl_eState_Fail,       Dbl_Transition_Nominal_To_Fail    },
  { Dbl_eState_Init,       Dbl_Transition_Nominal_To_Init    },
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state Dbl_eStateAdjustment
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tTransitionDbl Dbl_atTransitionAdj[3] =
{
  //  new state                  transition function
  { Dbl_eState_Nominal,       Dbl_Transition_Adj_To_Nominal    },
  { Dbl_eState_Fail,          Dbl_Transition_Adj_To_Fail       },
  { Dbl_eState_Init,          Dbl_Transition_Adj_To_Init       },
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state Dbl_eStateFailure
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tTransitionDbl Dbl_atTransitionFail[3] =
{
  //  new state                  transition function
  { Dbl_eState_Init,       Dbl_Transition_Fail_To_Init       },
  { Dbl_eState_Nominal,    Dbl_Transition_Fail_To_Nominal    },
  { Dbl_eState_Adj,        Dbl_Transition_Fail_To_Adj        },
};

// ---------------------------------------------------------------------------
// State machine table for ucIx 
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tsDbl_StateMType Dbl_atStateMachine[4] =
{ //   state name              transition count (of tr-table) [ucCount]    transition table [tTransitionDbl] state function [tStateFctPtrDbl]
  { /* Dbl_eState_Init,    */  UTIL_COUNTOF(Dbl_atTransitionInit),         Dbl_atTransitionInit,                    Dbl_StateMachine_StateInit        },
  { /* Dbl_eState_Nominal, */  UTIL_COUNTOF(Dbl_atTransitionNominal),      Dbl_atTransitionNominal,                 Dbl_StateMachine_StateNominal     },
  { /* Dbl_eState_Adj,     */  UTIL_COUNTOF(Dbl_atTransitionAdj),          Dbl_atTransitionAdj,                     Dbl_StateMachine_StateAdj         },
  { /* Dbl_eState_Fail,    */  UTIL_COUNTOF(Dbl_atTransitionFail),         Dbl_atTransitionFail,                    Dbl_StateMachine_StateFail        }
};

//****************************************************************************
// Functions
//****************************************************************************
//-----------------------------------------------------------------------------
/// ---------------------------------------------------------------------------
/// \brief Dbl_Curvature_SigQty_INV
/// 
/// \descr SRead the curvature from rte and check if the signal is invalid
///
/// \param  none
///
/// \return void
/// ---------------------------------------------------------------------------
void Dbl_Curvature_SigQty_INV(void)
{
  teRte_SigQty eCurvSigQty = Dbl_Curvature_SigQty();
 
  switch (eCurvSigQty)
  {
  case SIG_INVALID:
    //reset Unavailable timer
    Dbl_boFailureTimerFlag_Unav = Dbl_Timeout(FALSE, Dbl_unEgoMotionTime, DBL_SIG_QTY_UNAVAILABLE_TIMER_SEL);

    // wait unEgoMotionTime ms to set the error
    Dbl_boFailureTimerFlag_Inv = Dbl_Timeout(TRUE, Dbl_unEgoMotionTime, DBL_SIG_QTY_INVALID_TIMER_SEL);
    if (Dbl_boFailureTimerFlag_Inv != FALSE)
    {
      // set error flags for invalid
      Dbl_boCurvature_SigQty_ERR = TRUE;
      Dbl_boCurvature_UNAV       = FALSE;
    }
    else
    {
      // do nothing
    }
    break;

  case SIG_UNAVAILABLE:
    //reset invalid timer
    Dbl_boFailureTimerFlag_Inv = Dbl_Timeout(FALSE, Dbl_unEgoMotionTime, DBL_SIG_QTY_INVALID_TIMER_SEL);

    // wait unEgoMotionTime ms to set the error
    Dbl_boFailureTimerFlag_Unav = Dbl_Timeout(TRUE, Dbl_unEgoMotionTime, DBL_SIG_QTY_UNAVAILABLE_TIMER_SEL);
    if (Dbl_boFailureTimerFlag_Unav != FALSE)
    {
      // set error flags for unavailable
      Dbl_boCurvature_UNAV       = TRUE;
      Dbl_boCurvature_SigQty_ERR = FALSE;
    }
    else
    {
      // do nothing
    }
    break;

  case SIG_VALID:
    // set timers
    Dbl_boFailureTimerFlag_Unav = Dbl_Timeout(FALSE, Dbl_unEgoMotionTime, DBL_SIG_QTY_UNAVAILABLE_TIMER_SEL);
    Dbl_boFailureTimerFlag_Inv  = Dbl_Timeout(FALSE, Dbl_unEgoMotionTime, DBL_SIG_QTY_INVALID_TIMER_SEL);
    Dbl_boCurvature_SigQty_ERR  = FALSE;
    Dbl_boCurvature_UNAV        = FALSE;
    Dbl_sSignal.slCurvature     = Dbl_sCurvatureData.slCurvatureProcessedValue;
    break;

  case SIG_TIMEOUT:
    // reset timeres
    Dbl_boFailureTimerFlag_Unav = Dbl_Timeout(FALSE, Dbl_unEgoMotionTime, DBL_SIG_QTY_UNAVAILABLE_TIMER_SEL);
    Dbl_boFailureTimerFlag_Inv  = Dbl_Timeout(FALSE, Dbl_unEgoMotionTime, DBL_SIG_QTY_INVALID_TIMER_SEL);
    Dbl_boCurvature_SigQty_ERR  = TRUE;
    Dbl_boCurvature_UNAV        = FALSE;
    break;

  default:
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_ProcessCurvature
///
/// \descr This function return signal quality for curvature-computed internally or via CAN
///
/// \param void
///
/// \return -teRte_SigQty - signal quality
//-----------------------------------------------------------------------------
STATIC_AL teRte_SigQty Dbl_Curvature_SigQty(void)
{
  teRte_SigQty eCurvSigQty = SIG_VALID; 
  sint32 slCurvature = 0;

  // switch between VehPathCurvature source: from CAN or calculated internally
  if (Dbl_sCurvatureData.ucCurvatureMode == DBLSM_CURVATURE_RECEIVED_ON_CAN)
  {
    eCurvSigQty = Dbl_RteAccess_ReadCurvature(&slCurvature); // READ CURVATURE
  }
  else
  {
    slCurvature = DblCrState_State_Machine();
    // enforce sigQty to valid if curvature state machine allows it.
    if (slCurvature == DBL_CURVATURE_INVALID_VALUE) 
    {
      eCurvSigQty = SIG_INVALID;
    }
    else
    {
      eCurvSigQty = SIG_VALID;
      slCurvature = Dbl_Get_Filtered_Calculated_Curvature_Value(slCurvature);
    }
  }
  Dbl_sCurvatureData.slCurvatureProcessedValue = slCurvature;

  return eCurvSigQty;
}
//-----------------------------------------------------------------------------
/// \brief  Dbl_Get_Filtered_Calculated_Curvature_Value
///
/// \descr This function process the filtred curvature 
///
/// \param lCurvatureCalculated - curvature calculated
///
/// \return -sint32 - filtered curvature
//-----------------------------------------------------------------------------
STATIC_AL sint32 Dbl_Get_Filtered_Calculated_Curvature_Value(sint32 lCurvatureCalculated)
{
  static ORDER1_Filter32 Filter_Curvature;
  sint32 nCurvature = 0;
  sint32 lCurvatureRaw;
  sint32 lCurvatureOut = 0;

  lCurvatureRaw = lCurvatureCalculated;

  register sint32 slRegOut = Dbl_FilterIIR_Input(lCurvatureRaw);

  // filter curvature signal
  // 1. IIR
  nCurvature = slRegOut;
  // 2. tracking filer, tracking range +-31 [0.000025 1/m]
  if (Dbl_sCrCalcFilterData.ucFilterTracking != 0u)
  {
    uint8 ucFilterTime;

    ucFilterTime = (uint8)Dbl_sCrCalcFilterData.ucFilterTimePrio;

    nCurvature = Order1TrackingFilter32(&Filter_Curvature, ucFilterTime, nCurvature, (uint32)Dbl_sCrCalcFilterData.ucFilterTracking);
  }
  else
  {
    // do nothing
  }

  // copy curvature to output variable
  lCurvatureOut = nCurvature;

  //return filtered curvature
  return lCurvatureOut;
}


//-----------------------------------------------------------------------------
/// \brief  Dbl_FilterIIR_Input
///
/// \descr This function is an infinite impulse response filter that is 
///        stable and does not produce ripples.
///
/// \param nNewSample - new filter input 
///
/// \return -sint32 - filtered curvature
//-----------------------------------------------------------------------------
STATIC_AL sint32 Dbl_FilterIIR_Input(sint32 nNewSample)
{
  sint32 nOutput;
  uint8 ucFilterTime;
  static ORDER1_Filter32 IIR_SWA_Filter1;
  static ORDER1_Filter32 IIR_SWA_Filter2;

  ucFilterTime = (uint8)Dbl_sCrCalcFilterData.ucFilterTimePrio;

  nOutput = Order1TrackingFilter32(&IIR_SWA_Filter1,
    ucFilterTime,
    nNewSample,
    (uint32)Dbl_sCrCalcFilterData.ucFilterTrackingRange);

  nOutput = Order1Filter32(&IIR_SWA_Filter2,
    ucFilterTime,
    nOutput);

  return nOutput;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RetPowerTrainActive
///
/// \descr  return the status of the PowerTrain condition
///
/// \param  none
///
/// \return boolean - Dbl_boPowertrainActive
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_RetPowerTrainActive(void)
{
  return Dbl_boPowertrainActive;
}


//-----------------------------------------------------------------------------
/// \brief  Dbl_GetHBStatus
///
/// \descr  return the status of the high beam command
///
/// \param  none
///
/// \return boolean - Dbl_boHB
//-----------------------------------------------------------------------------
boolean Dbl_GetHBStatus(void)
{
  return Dbl_boHB;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_ReadFault
///
/// \descr  return the fault status of the other headlamp
///
/// \param  none
///
/// \return teRte_MountingSide ucSide
//-----------------------------------------------------------------------------
STATIC_AL teDbl_DynBendingBeamFault Dbl_ReadFault(teDbl_MountingSide eSide)
{
  teDbl_DynBendingBeamFault eDynBendingBeamFaultLR = eDbl_DynBendingBeamFault_False;

  if (eSide == Dbl_eMountedLeft)
  {
    // read right fault
    eDynBendingBeamFaultLR = Dbl_RteAccess_ReadDynBendingBeamFaultR();
  }
  else
  {
    //read left fault
    eDynBendingBeamFaultLR = Dbl_RteAccess_ReadDynBendingBeamFaultL();
  }
  return eDynBendingBeamFaultLR;
}

//-----------------------------------------------------------------------------
/// \brief Dbl_DefOfFailure
///
/// \descr definition of failure flow 
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
void Dbl_DefOfFailure(void)
{
  uint32 ulDblSpeed = Dbl_RteAccess_ReadSpeed();

  if (Dbl_eMountingSide == Dbl_eMountedLeft)
  {
    if ((ulDblSpeed == DBL_MAX_SPEED) || // speed is invalid or indisp or unavailable
      (Dbl_boCurvature_SigQty_ERR != FALSE)) // curvature is invalid or loss of communication is confirmed
    {
      Dbl_boSwivelingFunctionalFault_LR = TRUE;
      Dbl_boL_Internal_Failure = TRUE;
    }
    else if (Dbl_eErrorStatus == eDbl_DynBendingBeamFault_True) // error from the other headlamp is received
    {
      Dbl_boSwivelingFunctionalFault_LR = TRUE;
      Dbl_boL_Internal_Failure = FALSE;
    }
    else
    {
      // do nothing
    }
  }
  else if (Dbl_eMountingSide == Dbl_eMountedRight)
  {
    if ((ulDblSpeed == DBL_MAX_SPEED) || // speed is invalid or indisp or unavailable
      (Dbl_boCurvature_SigQty_ERR != FALSE)) // curvature is invalid or loss of communication is confirmed
    {
      Dbl_boSwivelingFunctionalFault_LR = TRUE;
      Dbl_boR_Internal_Failure = TRUE;
    }
    else if (Dbl_eErrorStatus == eDbl_DynBendingBeamFault_True) // error from the other headlamp is received
    {
      Dbl_boSwivelingFunctionalFault_LR = TRUE;
      Dbl_boR_Internal_Failure = FALSE;
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    // do nothing
  }

  // The functional failure is deset when ( the speed is known and the vehicle path curvature is different of Invalid and the internal failure trigger is true) OR (there is no failure received from the right LDM and the internal failure trigger is fale)
  if (Dbl_eMountingSide == Dbl_eMountedLeft)
  {
    if (((ulDblSpeed < DBL_MAX_SPEED) && // speed is known
        (Dbl_boCurvature_SigQty_ERR == FALSE) && // curvature is different than invalid 
        (Dbl_boL_Internal_Failure != FALSE)) || // internal failure is present
       ((Dbl_eErrorStatus == eDbl_DynBendingBeamFault_False) && // error from the other headlamp
        (Dbl_boL_Internal_Failure == FALSE)))
    {
      Dbl_boSwivelingFunctionalFault_LR = FALSE;
      Dbl_boL_Internal_Failure = FALSE;
    }
    else
    {
    }
  }
  // The functional failure is deset when ( the speed is known and the vehicle path curvature is different of Invalid and the internal failure trigger is true) OR (there is no failure received from the left LDM and the internal failure trigger is fale)
    else if (Dbl_eMountingSide == Dbl_eMountedRight)
    {
      if (((ulDblSpeed < DBL_MAX_SPEED) && // speed is known
        (Dbl_boCurvature_SigQty_ERR == FALSE) && // curvature is different than invalid 
        (Dbl_boR_Internal_Failure != FALSE)) || // internal failure is present
        ((Dbl_eErrorStatus == eDbl_DynBendingBeamFault_False) && (Dbl_boR_Internal_Failure == FALSE))) // error from the other headlamp and no internal failure
      {
        Dbl_boSwivelingFunctionalFault_LR = FALSE;
        Dbl_boR_Internal_Failure = FALSE;
      }
    }
    else
    {
      // do nothing
    }
  }

//-----------------------------------------------------------------------------
/// \brief  Dbl_RetDigitalSwivelingFunctionalFault_LR
///
/// \descr  return the status of the digital swiveling functional fault 
///
/// \param  none
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_RetDigitalSwivelingFunctionalFault_LR(void)
{
  return Dbl_boSwivelingFunctionalFault_LR;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_DetectMode
///
/// \descr  Detect the mode 
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_DetectMode(void)
{
  uint8 ucModeConfigVhl = Dbl_RteAccess_ReadVehicleModeConfig();

  if ((ucModeConfigVhl == (uint8)eModeConfigVehicle_Client) || (ucModeConfigVhl == (uint8)eModeConfigVehicle_Showroom) || (ucModeConfigVhl == (uint8)eModeConfigVehicle_Stockage))
  {
    Dbl_eMainMode = Dbl_eModeCustomer;
  }
  else
  {
    Dbl_eMainMode = Dbl_eModeAssembly;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_UseMode
///
/// \descr Detect the submode
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
void Dbl_UseMode(void)
{
  switch (Dbl_eMainMode)
  {
  case Dbl_eModeAssembly:
  {
    Dbl_ModeAssembly();
    break;
  }
  case Dbl_eModeCustomer:
  {
    Dbl_ModeCustomer();
    break;
  }
  default: break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_UseSubMode
///
/// \descr Detects the mode
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
void Dbl_UseSubMode(void)
{
  switch (Dbl_eSubMode)
  {
  case Dbl_eSubModeUnavailable:
  {
    Dbl_SubModeUnavailable();
    break;
  }
  case Dbl_eSubModeAvailable:
  {
    Dbl_StMch();
    break;
  }
  case Dbl_eSubModeFrozen:
  {
    Dbl_SubModeFrozen();
    break;
  }
  default: break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_ModeAssembly
///
/// \descr Detects the submode for assembly mode
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void Dbl_ModeAssembly(void)
{
  // check transitions
  if (Dbl_Transition_Assembly_To_Frozen() != FALSE)
  {
    Dbl_eSubMode = Dbl_eSubModeFrozen;
  }
  else
  {
    // leave current state
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_ModeCustomer
///
/// \descr Detects the submodes for customer mode
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void Dbl_ModeCustomer(void)
{
  if (Dbl_Transition_Customer_To_Available() != FALSE)
  {
    Dbl_eSubMode = Dbl_eSubModeAvailable;
  }
  else if (Dbl_Transition_Customer_To_Unavailable() != FALSE)
  {
    Dbl_eSubMode = Dbl_eSubModeUnavailable;
  }
  else
  {
    // remain in current state
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Assembly_To_Frozen
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Assembly_To_Frozen(void)
{
  boolean boReturn = FALSE;

  uint8 ucModeConfigVhl = Dbl_RteAccess_ReadVehicleModeConfig();

  if ((ucModeConfigVhl == (uint8)eModeConfigVehicle_Montage) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Invalid2) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Controle) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_AfterMarket))
  {
    boReturn = TRUE;
  }
  else
  {
    // do nothing
  }
  return boReturn;
} 

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Customer_To_Unavailable
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Customer_To_Unavailable(void)
{
  boolean boReturn         = FALSE;
  uint8   ucModeConfigVhl  = Dbl_RteAccess_ReadVehicleModeConfig();
  teDbl_EtatPrincipSEV   eEtatPrincipSev = Dbl_RteAccess_ReadVESMainState();

  if (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Client) ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Showroom) ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Stockage)) &&
       (eEtatPrincipSev == eDBL_VESState_Stop))  
  {
    boReturn = TRUE;
  }
  else
  {
    // do nothing
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Customer_To_Available
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Customer_To_Available(void)
{
  boolean boReturn = FALSE;
  uint8 ucModeConfigVhl = Dbl_RteAccess_ReadVehicleModeConfig();
  teDbl_EtatPrincipSEV eEtatPrincipSev = Dbl_RteAccess_ReadVESMainState();

  if (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Client) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Showroom) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Stockage)) &&
      ((eEtatPrincipSev == eDBL_VESState_Ignition) || 
      (eEtatPrincipSev == eDBL_VESState_Start)))
  {
    boReturn = TRUE;
  }
  else
  {
    // do nothing
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Fail_To_Init
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Fail_To_Init(void)
{
  boolean boReturn = TRUE;
  boolean boDigitalSwivelFunctFault_LR = 0u;
  boolean boPowerTrain = Dbl_RetPowerTrainActive();
  boolean boCondition = FALSE;

  Dbl_DefOfFailure(); // check the actual state of the error
  boDigitalSwivelFunctFault_LR = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  boCondition = ((boPowerTrain == FALSE) && (boDigitalSwivelFunctFault_LR == FALSE)) ? TRUE : FALSE;
 
  if (boCondition != FALSE)
  {
    Dbl_boDYN_BENDING_BEAM_FAULT = FALSE;
    Dbl_boErrorFromOtherHL = FALSE;
  }
  else
  {
    boReturn = FALSE;
  }



  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Init_To_Nominal
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Init_To_Nominal(void)
{
  boolean boReturn = FALSE;
  boolean boPowerTrain = Dbl_RetPowerTrainActive();
  boolean boDigitalSwivelFunctFault = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  uint32  ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  uint8   CodAFSPolySolver2_V0_Local = CodAFSPolySolver2_V0();
  uint8   CodAFSPolySolver2_V4_Local = CodAFSPolySolver2_V4();



  boolean boCondition = (((boDigitalSwivelFunctFault == FALSE) ||
                         (Dbl_boCurvature_UNAV != FALSE)) &&
                         (boPowerTrain != FALSE) &&
                        ((ulDblSpeed < CodAFSPolySolver2_V0_Local) || (ulDblSpeed > CodAFSPolySolver2_V4_Local))) ? TRUE : FALSE;

  if (boCondition != FALSE)
  {
    boReturn = TRUE;
  }
  else
  {
   // do nothing
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Fail_To_Nominal
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Fail_To_Nominal(void)
{
  boolean boReturn = TRUE;
  boolean boPowerTrain = Dbl_RetPowerTrainActive();
  boolean boDigitalSwivelFunctFault= Dbl_RetDigitalSwivelingFunctionalFault_LR();
  uint32  ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  uint8   CodAFSPolySolver2_V0_Local = CodAFSPolySolver2_V0();
  uint8   CodAFSPolySolver2_V4_Local = CodAFSPolySolver2_V4();

  boolean boCondition = ((boDigitalSwivelFunctFault == FALSE) &&
                        ((Dbl_boCurvature_UNAV != FALSE) || ((Dbl_boCurvature_UNAV == FALSE) && (Dbl_boCurvature_SigQty_ERR == FALSE))) &&
                         (boPowerTrain != FALSE) &&
                        (((ulDblSpeed < CodAFSPolySolver2_V0_Local) || ulDblSpeed > CodAFSPolySolver2_V4_Local) && (ulDblSpeed != DBL_MAX_SPEED))) ? TRUE : FALSE;

  if (boCondition != FALSE)
  {
    Dbl_boDYN_BENDING_BEAM_FAULT = FALSE;
    Dbl_boErrorFromOtherHL = FALSE;
  }
  else
  {
    boReturn = FALSE;
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Adj_To_Nominal
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Adj_To_Nominal(void)
{
  boolean boReturn = FALSE;
  boolean boCondition = FALSE;
  boolean boDblInhibitionCmd = Dbl_RteAccess_ReadEnvCondition();
  uint32  ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  boolean ucLowBeamCmd = Dbl_RteAccess_ReadDblCmd();
  uint8   CodAFSPolySolver2_V0_Local = CodAFSPolySolver2_V0();
  uint8   CodAFSPolySolver2_V4_Local = CodAFSPolySolver2_V4();

  boCondition = (((ucLowBeamCmd == (uint8)STOP_DBL) &&
                  (Dbl_boHB == FALSE)) || 
                  (Dbl_boEtatMar != FALSE) ||
                  (boDblInhibitionCmd != FALSE) || 
                  (Dbl_boCurvature_UNAV != FALSE) || 
                 ((ulDblSpeed < CodAFSPolySolver2_V0_Local) || (ulDblSpeed > CodAFSPolySolver2_V4_Local) && (ulDblSpeed != DBL_MAX_SPEED))) ? TRUE : FALSE;
   
  if (boCondition != FALSE)
  {
    boReturn = TRUE;
  }
  else
  {
   // do nothing
  }

  return boReturn;
} // PRQA S 5324 // STCAL = 8 exceeds threshold

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Nominal_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Nominal_To_Adj(void)
{
  boolean boReturn = FALSE;
  boolean boPowerTrain = Dbl_RetPowerTrainActive();
  boolean boDigitalSwivelFunctFault= Dbl_RetDigitalSwivelingFunctionalFault_LR();
  boolean boDblInhibitionCmd = Dbl_RteAccess_ReadEnvCondition();
  uint32  ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  uint8   ucLowBeamCmd = Dbl_RteAccess_ReadDblCmd();
  uint8   CodAFSPolySolver2_V0_Local = CodAFSPolySolver2_V0();
  uint8   CodAFSPolySolver2_V4_Local = CodAFSPolySolver2_V4();

  boolean boCondition = ((boDigitalSwivelFunctFault == FALSE) &&
                         (boPowerTrain != FALSE) &&
                         ((ulDblSpeed >= CodAFSPolySolver2_V0_Local) && (ulDblSpeed <= CodAFSPolySolver2_V4_Local)) &&
                         (Dbl_boEtatMar == FALSE) &&
                        ((ucLowBeamCmd == (uint8)PLAY_DBL) ||
                         (Dbl_boHB != FALSE)) &&
                         (boDblInhibitionCmd == FALSE) &&
                        ((Dbl_boCurvature_UNAV == FALSE) && (Dbl_boCurvature_SigQty_ERR == FALSE))) ? TRUE : FALSE;
  
  if (boCondition != FALSE)
  {
    boReturn = TRUE;
  }
  else
  {
    // do nothing
  }

  return boReturn;
}  // PRQA S 5324  // HIS metrics violation suppressed (STCAL = 8)


//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Init_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Init_To_Adj(void)
{
  boolean boReturn = FALSE;
  boolean boPowerTrain = Dbl_RetPowerTrainActive();
  boolean boDigitalSwivelFunctFault = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  boolean boDblInhibitionCmd = Dbl_RteAccess_ReadEnvCondition();
  uint32  ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  uint8   ucLowBeamCmd = Dbl_RteAccess_ReadDblCmd();
  uint8   CodAFSPolySolver2_V0_Local = CodAFSPolySolver2_V0();
  uint8   CodAFSPolySolver2_V4_Local = CodAFSPolySolver2_V4();

  boolean boCondition = ((boDigitalSwivelFunctFault == FALSE) &&
                          (boPowerTrain != FALSE) &&
                         ((ulDblSpeed >= CodAFSPolySolver2_V0_Local) || (ulDblSpeed <= CodAFSPolySolver2_V4_Local)) &&
                          (Dbl_boEtatMar == FALSE) &&
                         ((ucLowBeamCmd == (uint8)PLAY_DBL) ||
                          (Dbl_boHB != FALSE)) &&
                         ((Dbl_boCurvature_UNAV == FALSE) && (Dbl_boCurvature_SigQty_ERR == FALSE)) &&
                          (boDblInhibitionCmd == (uint8)eInhEclairageVirageDyn_NoInhibition)) ? TRUE : FALSE; 
  
  if (boCondition != FALSE)
  {
    boReturn = TRUE;
  }
  else
  {
   // do nothing
  }

  return boReturn;
} // PRQA S 5324  // HIS metrics violation suppressed (STCAL = 8)

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Fail_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Fail_To_Adj(void)
{
  boolean boReturn = FALSE;
  boolean boPowerTrain = Dbl_RetPowerTrainActive();
  boolean boDigitalSwivelFunctFault = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  uint32  ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  uint8   CodAFSPolySolver2_V0_Local = CodAFSPolySolver2_V0();
  uint8   CodAFSPolySolver2_V4_Local = CodAFSPolySolver2_V4();
  boolean boDblInhibitionCmd = Dbl_RteAccess_ReadEnvCondition();
  uint8   ucLowBeamCmd = Dbl_RteAccess_ReadDblCmd();

  boolean boCondition = ((boDigitalSwivelFunctFault == FALSE) &&
                         (boPowerTrain != FALSE) &&
                        ((ulDblSpeed >= CodAFSPolySolver2_V0_Local) || (ulDblSpeed <= CodAFSPolySolver2_V4_Local)) &&
                        ((Dbl_boCurvature_UNAV == FALSE) && (Dbl_boCurvature_SigQty_ERR == FALSE)) &&
                         (boDblInhibitionCmd == (uint8)eInhEclairageVirageDyn_NoInhibition) &&
                         (Dbl_boEtatMar == FALSE) &&
                        ((ucLowBeamCmd == (uint8)PLAY_DBL) ||
                        (Dbl_boHB != FALSE))) ? TRUE : FALSE;

  if (boCondition != FALSE)
  {
    boReturn = TRUE;
    Dbl_boDYN_BENDING_BEAM_FAULT = FALSE;
    Dbl_boErrorFromOtherHL = FALSE;
  }
  else
  {
    // do nothing
  }

  return boReturn;
} // PRQA S 5324 // STCAL = 8

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Init_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Init_To_Fail(void)
{
  boolean boReturn = FALSE;
  boolean boDigitalSwivelFunctFault = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  boolean boCondition = (boDigitalSwivelFunctFault != FALSE) ? TRUE : FALSE;

  if (boCondition != FALSE)
  {
    boReturn = TRUE;
    Dbl_boDYN_BENDING_BEAM_FAULT = TRUE;
  }
  else
  {
    //do nothing
  }
  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Nominal_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Nominal_To_Fail(void)
{
  boolean boReturn = FALSE;
  boolean boDigitalSwivelFunctFault = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  boolean boCondition = (boDigitalSwivelFunctFault != FALSE) ? TRUE : FALSE;

  if (boCondition != FALSE)
  {
    boReturn = TRUE;
    Dbl_boDYN_BENDING_BEAM_FAULT = TRUE;
  }
  else
  {
  // do nothing
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Adj_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Adj_To_Fail(void)
{
  boolean boReturn = FALSE;
  boolean boDigitalSwivelFunctFault = Dbl_RetDigitalSwivelingFunctionalFault_LR();
  boolean boCondition = (boDigitalSwivelFunctFault != FALSE) ? TRUE : FALSE;

  if (boCondition != FALSE)
  {
    boReturn = TRUE;
    Dbl_boDYN_BENDING_BEAM_FAULT = TRUE;
  }
  else
  {
    //do nothing
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Adj_To_Init
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Adj_To_Init(void)
{
	boolean boReturn = FALSE;

	if (Dbl_boPowertrainActive == FALSE)
	{
		boReturn = TRUE;
	}
	else
	{
		//do nothing
	}
	return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Transition_Nominal_To_Init
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Transition_Nominal_To_Init(void)
{
  boolean boReturn = FALSE;

  if (Dbl_boPowertrainActive == FALSE)
  {
    boReturn = TRUE;
  }
  else
  {
    //do nothing
  }
  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_ReadEnvironmentSignals
///
/// \descr Read the RTE environmental signals
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_ReadEnvironmentSignals(void)
{
  tsDbl_VehNetState    sElectricNetworkState = { 0 };

  sElectricNetworkState = Dbl_RteAccess_ReadVehicleElectricState();
  // check if powertrain is activated
  if ((sElectricNetworkState.eElectricNetworkState == eDblTA_NOMINAL) ||
      (sElectricNetworkState.eElectricNetworkState == eDblTA_DEGRADE) ||
      (sElectricNetworkState.eElectricNetworkState == eDblTA_SECU)    ||
      (sElectricNetworkState.eElectricNetworkState == eDblREDEMARRAGE))
  {
    Dbl_boPowertrainActive = TRUE;
  }
  else
  {
    Dbl_boPowertrainActive = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief   DblcSm_ParaFct0
///
/// \descr  Initialize coding data
///
/// \param  eCmd: coding data valid, coding data invalid 
/// \param  pData 
///
/// \return void 
//-----------------------------------------------------------------------------
void DblcSm_ParaFct0(void)
{
  tParaFct0_Cmd sCodingStatus = eParaFct0_CodingDataInvalid;

  (void)Rte_Read_CodM_Dbl_Para(&Dbl_sCodingParam);

  sCodingStatus = Dbl_sCodingParam.eCodingState;

  if (sCodingStatus == eParaFct0_CodingDataValid)
  {
    Dbl_boIsCodingValid = TRUE;

    Dbl_sCurvatureData.ucCurvatureMode = CodDisableFuncs_Curvature_Mode();// LVM option from STO
    Dbl_sCurvatureData.ucDblEnable = CodSysConfigurability_Dbl_Enable();// CRP option from STO

    DblCrvCalc_Get_WfCodingParameters();
    DblCrvCalc_Get_CurvatureCodingParameters();
    Dbl_Get_Calculated_Curvature_Coding_Parameters();
    Dbl_unEgoMotionTime = CodEgo_Vehicle_Motion_Confirmation_Time();
  }
  else
  {
    Dbl_boIsCodingValid = FALSE;
  }
}

// ---------------------------------------------------------------------------
//  \func     Dbl_Get_Calculated_Curvature_Coding_Parameters
//
//  \brief    get filter parameters from coding
//
//  \param    void
//
//  \return   void
// ---------------------------------------------------------------------------
STATIC_AL void Dbl_Get_Calculated_Curvature_Coding_Parameters(void)
{
  Dbl_sCrCalcFilterData.ucFilterTimePrio      = CodDblCurvatureCalculation_getFilterTimePrio();
  Dbl_sCrCalcFilterData.ucFilterTracking      = CodDblCurvatureCalculation_getFilterTracking();
  Dbl_sCrCalcFilterData.ucFilterTrackingRange = CodDblCurvatureCalculation_getFilterTrackingRange();
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_DetectSide
///
/// \descr  reads ecu side
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Dbl_DetectSide(void)
{
  (void)Dbl_RteAccess_Read_EcuSide(&Dbl_eMountingSide);
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_GetSide
///
/// \descr  returns ecu side
///
/// \param  void
///
/// \return teRte_MountingSide
//-----------------------------------------------------------------------------
teDbl_MountingSide Dbl_GetSide(void)
{
  return Dbl_eMountingSide;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_GetTrafficSide
///
/// \descr  returns hand traffic side
///
/// \param  void
///
/// \return teTraffic
//-----------------------------------------------------------------------------
teTraffic Dbl_GetTrafficSide(void)
{
  Dbl_eTrafficSide = Dbl_RteAccess_ReadDblTrafficSide();
  return Dbl_eTrafficSide;
}

//-----------------------------------------------------------------------------
/// \brief  DblcSm_Init
///
/// \descr  Initialize dbl internal data 
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void DblcSm_Init(void)
{
  DblcSm_ParaFct0();
  DblCrState_Init();
  Dbl_DetectSide();
}

/// ---------------------------------------------------------------------------
/// \brief       DblcCl
///
/// \descr       dynamic bending light control, calls the poly solver algorithm and 
///              limits the swiveling ranges
///
/// \param       nC             curvature             [0.0000025 1/m]
/// \param       nCG            curvature gradient    [0.0000025 1/m]
/// \param       nV             vehicle speed         [0.1km/h]
/// \param       ucStreetClass  Street Class          [%]
///
/// \return      head light angle 
///
/// \callgraph 
/// 
/// ---------------------------------------------------------------------------
STATIC_AL sint32 DblcCl(sint32 nC, sint32 nCG, sint32 nV, uint8 ucStreetClass)
{
  tsDbl_SwiRateLimMsg SwiRateLim; // max. allowed swivelling step
  volatile sint32 nHla;                // head light angle
  sint32 nHlaDiff;            // head light angle gradient

  // calculate head light angle

  // 0            traffic not defined
  // 1 right hand traffic (Rechtsverkehr) | continent    | default
  // 2 left  hand traffic (Linksverkehr)  | GB, Ireland  

  switch (Dbl_RteAccess_ReadDblTrafficSide())
  {
  case RightHandTraffic:
  {
    // calculate head light angle
    //   for right hand traffic
    nHla = ClPolySolver(nC, nV);
  }
  break;

  case LeftHandTraffic:
  {
    // calculate head light angle
    //   for left hand traffic, inverse curvature and inverse result
    nHla = -ClPolySolver(-nC, nV);
  }
  break;

  default:
  {
    nHla = 0;
  }
  break;
  }

  //-------------------------------------------------------------------------
  // adaptive rate limiter

  //Dbl_slnHlaOut = DblcLimitSwiveling(nC, nCG, nHla, Dbl_slnHlaOut, ucStreetClass);

  // calculate swiveling rates/steps     
  DblcCalculateSwiveling(nC, nCG, ucStreetClass);

  // read back limits from black board
  SwiRateLim = Dbl_RteAccess_ReadSwimRate();

  // detect swiveling direction 
  //   > 0 => swivelling right
  //   < 0 => swivelling left
  nHlaDiff = nHla - Dbl_slnHlaOut;

  // swiveling right
  if (nHlaDiff > 0)
  {
    // if new calculated head light angle is less 
    //   than the old head light angle + new allowed swivelling range
    //   use the new calculate head light angle
    //   otherwise use the old head light angle + the new allowed swivelling step
    if (nHla <= (Dbl_slnHlaOut + SwiRateLim.nLimit[eRight]))
    {
      Dbl_slnHlaOut = nHla;
    }
    else
    {
      Dbl_slnHlaOut += SwiRateLim.nLimit[eRight];
    }
  }
  // swiveling left
  else if (nHlaDiff < 0)
  {
    // nSwiLeft negative value !!!!!
    if (nHla >= (Dbl_slnHlaOut + SwiRateLim.nLimit[eLeft]))
    {
      Dbl_slnHlaOut = nHla;
    }
    else
    {
      Dbl_slnHlaOut += SwiRateLim.nLimit[eLeft];
    }
  }
  else
  {
    // not intended to be reached
  }

  return Dbl_slnHlaOut;
}

/// ---------------------------------------------------------------------------
/// \brief       DblcOutputControl
///
/// \descr       dynamic bending light output controls,\n
///              if the system starts the function increases slowly the signal output
///              form 1 -> 100%
///
/// \param       nHla              head light angle
/// \param       nReqPercentage    required/requested output percentage 0-1000 [0.1%]
///
/// \return      reduced or normal head light angle 
///
/// \callgraph 
/// 
/// ---------------------------------------------------------------------------
STATIC_AL sint32 DblcOutputControl(sint32 nHla, sint32 nReqPercentage)
{
  return (nHla * nReqPercentage) / 1000;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_SetSteerbackDetection
///
/// \descr  functino that sets steerback detection
///
/// \param  boolean - boState
///
/// \return 
//-----------------------------------------------------------------------------
void Dbl_SetSteerbackDetection(boolean boState)
{
  //set steerback bit
  Dbl_sDriveSituation.Bit.bSteerBack = boState;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_Mrad2MDeg
///
/// \descr  converts angle in 0.1 rad to 0.05 degrees
///
/// \param  [nSwvMrad] - angle in 0.1 rad
///
/// \return [sint16] - angle in 0.05 degrees
//-----------------------------------------------------------------------------
sint16 Dbl_Mrad2MDeg(sint16 nSwvMrad)
{
  sint16 snSwivelAngle;

  //PRQA S 4390 ++  // cast to wider signed type is needed
  // first convert to 0.1 degrees
  snSwivelAngle = (sint16)((sint32)((nSwvMrad)* DBL_FULLANGLE) / DBL_PIVALUE);

  //map to 0.05 degrees
  snSwivelAngle = snSwivelAngle / 5;

  return snSwivelAngle;
}


#if ((CFG_OPT_CL & CFG_Cl_ActivateWithZeroCurvature) || (CFG_OPT_CL & CFG_Cl_DeactivateWithZeroCurvature))
#if (CFG_TYP_AM == CFG_Am_None)
/// Is there currently a zero curvature or a crossing of zero curvature?
typedef enum
{
  False = 0,   ///< No
  True = 1,   ///< Yes
  Unknown = 2    ///< Could not detect due to errorneous signal states
} ZeroCurvatureType;

/// was there a zero curvature or a crossing of the zero curvature?
static uint8 _bZeroCurvature = (uint8)Unknown;

/// ---------------------------------------------------------------------------
///
/// \brief       check if the current curvature is zero or has crossed zero
///
/// \return      TRUE   curvature is assumed to be zero <BR>
///              FALSE  curvature is not assumed to be zero            
///
/// ---------------------------------------------------------------------------
void _DetectZeroCurvature()
{
  static sint32  prevC = 0;
  static uint16 prevstate = SIG_INVALID;

  register uint8        d = 0x00;
  register tLitSigState currentstate = Dbl_sSignalState.Curvature;

  if (prevstate != SIG_VALID) d |= 0x01;
  if (currentstate != SIG_VALID) d |= 0x02;

  switch (d)
  {
  case 0x00:
  {
    // prev OK, new OK
    _bZeroCurvature = (prevC*Dbl_sSignal.nCurvature <= 0) ? (uint8)True : (uint8)False;
    prevC = Dbl_sSignal.nCurvature;
    prevstate = currentstate;
    break;
  }
  case 0x01:
  {
    // prev ERR/WARN, new OK
    _bZeroCurvature = (uint8)Unknown;
    prevC = Dbl_sSignal.nCurvature;
    prevstate = currentstate;
    break;
  }
  case 0x02:
  case 0x03:
  {
    // prev OK/ERR/WARN, new ERR/WARN
    _bZeroCurvature = (uint8)Unknown;
    prevC = 0;
    prevstate = currentstate;
    break;
  }
  default:
    // never reached, satisfy LINT
    break;
  }
}

/// ---------------------------------------------------------------------------
///
/// \brief       check if the current curvature is zero or has crossed zero
///
/// \return      True   curvature is assumed to be zero <BR>
///              False  curvature is not assumed to be zero <BR>
///              Unknown no valid detection possible
///
/// ---------------------------------------------------------------------------
INLINE ZeroCurvatureType _IsZeroCurvature(void)
{
  return (ZeroCurvatureType)_bZeroCurvature;
}
#endif
#endif

#if (CFG_TYP_AM != CFG_Am_None)
/// ---------------------------------------------------------------------------
/// \brief Dbl_Call_StateNormal
/// 
/// \descr Front swiveling angle left and right shall be calculated according to vehicle trajectory curvature 
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_Call_StateNormal(void)
{
  tsDbl_SwivellingOut sDblSwivelAndState;

  sint32 slIdledC;
  sint32 slCG = Dbl_sSignal.nCurvatureGrad;
  uint32 ulV = Dbl_sSignal.nSpeed;
  uint8  ucSC = Dbl_sSignal.ucStreetClass;
  
  
  sint32 slHlaTmp;                // 0.1 mRad
  sint32 slIdleRange;             // Idle Range 
  sint32 slAFactor;               // attenuation factor 
  
  sint32 slAngleRight = 0;
  sint32 slAngleLeft = 0;
  uint8 ucCodAfsHld_HlaFilterSize_Local = CodAfsHld_HlaFilterSize();
    // calculate idle range
#if ( CFG_OPT_CL & CFG_Cl_IdleRangeAlg2 )

      // extended idle range detection
    slIdleRange = ClIdleRange(ulV, Dbl_sSignal.slCurvature, 0x00, ucSC);  // PRQA S 4446  // program architecture and readability - intentionally no modification of existing code 

#else
      // default idle range detection
    slIdleRange = ClIdleRange(Dbl_sSignal.slCurvature, 0x00);
#endif

    // idle steering wheel angle
    slCG = ClIdleSignal(Dbl_sSignal.slCurvature, slIdleRange);

    // calculate head light angle
    //   copy calculated value to tmp variable
    //
    slHlaTmp = DblcCl(slCG, slCG, ulV, ucSC); // PRQA S 4446  // program architecture and readability - intentionally no modification of existing code 


    // filter head light angle   
  if ((ucCodAfsHld_HlaFilterSize_Local > 0u) &&
    (ucCodAfsHld_HlaFilterSize_Local < DBLC_HLAFILTERSIZE)
    )

  {
    slHlaTmp = FirFilter32(Dbl_slanHLAFilter, (sint32)ucCodAfsHld_HlaFilterSize_Local, slHlaTmp);
  }

  // calculate idle position -> mid
  slHlaTmp = ClHlaIdlePosition(slHlaTmp, ulV); // PRQA S 4446  // program architecture and readability - intentionally no modification of existing code 


  // calculate hla attenuation factor for hight speed signal attenuation  
  slAFactor = ClHlaAttenuationFactor(slCG, ulV); // PRQA S 4446  // program architecture and readability - intentionally no modification of existing code 


  // start control algorith
  slHlaTmp = DblcOutputControl(slHlaTmp, slAFactor);

  CL_LRRELATION(slHlaTmp, &slAngleLeft, &slAngleRight);


  sDblSwivelAndState.SwivellingAngle[eLeft].Hor = (sint16)slAngleLeft;
  sDblSwivelAndState.SwivellingAngle[eRight].Hor = (sint16)slAngleRight;

  // convert output to desired resolution
  Dbl_snSwivelAngleLeft = Dbl_Mrad2MDeg(sDblSwivelAndState.SwivellingAngle[eLeft].Hor);
  Dbl_snSwivelAngleRight = Dbl_Mrad2MDeg(sDblSwivelAndState.SwivellingAngle[eRight].Hor);
 
  if (Dbl_snSwivelAngleRight < 0)
  {
	  Dbl_snSwivelAngleRight = (sint16)((sint32)(Dbl_snSwivelAngleRight * (sint32)CodDblCurveFactor()) / DBL_FACTOR_RESOLUTION); // if the curvature is positive apply a factor for right swiveling angle
  }
  if (Dbl_snSwivelAngleLeft > 0)
  {
	  Dbl_snSwivelAngleLeft = (sint16)((sint32)(Dbl_snSwivelAngleLeft * (sint32)CodDblCurveFactor()) / DBL_FACTOR_RESOLUTION); // if the curvature is negative apply a factor for left swiveling angle
  }

  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = Dbl_snSwivelAngleLeft;
  Dbl_sMsgOut.SwivellingAngle[eRight].Hor = Dbl_snSwivelAngleRight;
}   // PRQA S 5324  // HIS metrics violation suppressed (STCAL = 10)


/// ---------------------------------------------------------------------------
/// \brief Dbl_Call_StateOff
/// 
/// \descr The system shall command the Lowbeam Digital Swiveling to 0 degrees
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_Call_StateOff(void)
{
  tsDbl_SwivellingOut sDblSwivelAndState;
  uint8       ucCounter;

  // reset global variables
  Dbl_slnHlaOut = 0;

  sDblSwivelAndState.SwivellingAngle[eLeft].Hor = 0;
  sDblSwivelAndState.SwivellingAngle[eRight].Hor = 0;
 
  Dbl_snSwivelAngleLeft= Dbl_Mrad2MDeg(sDblSwivelAndState.SwivellingAngle[eLeft].Hor);
  Dbl_snSwivelAngleRight= Dbl_Mrad2MDeg(sDblSwivelAndState.SwivellingAngle[eRight].Hor);
  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = Dbl_snSwivelAngleLeft;
  Dbl_sMsgOut.SwivellingAngle[eRight].Hor = Dbl_snSwivelAngleRight;

  // reset FIR filter
  for (ucCounter = 0u; ucCounter < DBLC_HLAFILTERSIZE; ucCounter++)
  {
    Dbl_slanHLAFilter[ucCounter] = 0;
  }

  ClResetSpeedFilter();
}

/// ---------------------------------------------------------------------------
/// \brief Dbl_Call_StateFailure
/// 
/// \descr The system shall command the Lowbeam Digital Swiveling to 0 degrees
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_Call_StateFailure(void)
{
  tsDbl_SwivellingOut sDblSwivelAndState = { 0 };
  uint8       ucCounter;

  // reset global variables
  Dbl_slnHlaOut = 0;

  if (Dbl_eMountingSide == Dbl_eMountedLeft)
  {
    sDblSwivelAndState.SwivellingAngle[eLeft].Hor = 0;
  }
  else if (Dbl_eMountingSide == Dbl_eMountedRight)
  {
    sDblSwivelAndState.SwivellingAngle[eRight].Hor = 0;
  }
  else
  {
    // do nothing
  }

  Dbl_snSwivelAngleLeft = Dbl_Mrad2MDeg(sDblSwivelAndState.SwivellingAngle[eLeft].Hor);
  Dbl_snSwivelAngleRight = Dbl_Mrad2MDeg(sDblSwivelAndState.SwivellingAngle[eRight].Hor);
  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = Dbl_snSwivelAngleLeft;
  Dbl_sMsgOut.SwivellingAngle[eRight].Hor = Dbl_snSwivelAngleRight;

  // reset FIR filter
  for (ucCounter = 0u; ucCounter < DBLC_HLAFILTERSIZE; ucCounter++)
  {
    Dbl_slanHLAFilter[ucCounter] = 0;
  }

  ClResetSpeedFilter();
}

/// ---------------------------------------------------------------------------
/// \brief Dbl_Reset_Flags
/// 
/// \descr The System shall reset error flag in unavailable mode in order 
/// to retrrigger the unEgoMotionTime
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_Reset_Flags(void)
{
  Dbl_boFailureTimerFlag_Unav = FALSE;
  Dbl_boFailureTimerFlag_Inv = FALSE;
}

/// ---------------------------------------------------------------------------
/// \brief Dbl_Call_StateHold
/// 
/// \descr The System shall freeze the swiveling angle of left and right headlamp 
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_Call_StateHold(void)
{
  tsDbl_SwivellingOut sDblOut = { 0 };

  sDblOut = Dbl_RteAccess_ReadDblOutput();

  Dbl_sMsgOut.SwivellingAngle[eLeft].Hor = sDblOut.SwivellingAngle[0].Hor;
  Dbl_sMsgOut.SwivellingAngle[eRight].Hor = sDblOut.SwivellingAngle[1].Hor;
}


/// ---------------------------------------------------------------------------
/// \brief Dbl_StateMachine_StateInit
/// 
/// \descr The System shall freeze the swiveling angle of left and right headlamp 
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_StateMachine_StateInit(void)
{
  Dbl_boErrorFromOtherHL = FALSE;
  Dbl_boDYN_BENDING_BEAM_FAULT = FALSE;
  Dbl_Call_StateHold();

}

/// ---------------------------------------------------------------------------
/// \brief Dblc State Machine: State Nominal
/// 
/// \descr The system shall command the Lowbeam Digital Swiveling to 0 degrees
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_StateMachine_StateNominal(void)
{
  Dbl_Call_StateOff();
}

/// ---------------------------------------------------------------------------
/// \brief Dbl_StateMachine_StateFail
/// 
/// \descr The system shall command the Lowbeam Digital Swiveling to 0 degrees
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_StateMachine_StateFail(void)
{
  teDbl_MountingSide eMountingSide_Local = Dbl_GetSide();

  // set DBL error state
  Dbl_Call_StateFailure();

  if (eMountingSide_Local == Dbl_eMountedLeft)
  {
    // get side error
    Dbl_boErrorFromOtherHL = Dbl_boL_Internal_Failure;
    // general fault is set only by left side
    Dbl_boDYN_BENDING_BEAM_FAULT = TRUE;
  }
  else if (eMountingSide_Local == Dbl_eMountedRight)
  {
    // get side error
    Dbl_boErrorFromOtherHL = Dbl_boR_Internal_Failure;
  }
  else
  {
    // do nothing 
  }

}

/// ---------------------------------------------------------------------------
/// \brief Dbl_HbActive
/// 
/// \descr The system shall check if high beam command, glare free high beam command is on
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
void Dbl_HbActive(void)
{
  uint8 ucHbCmd = Dbl_RteAccess_ReadHbCmd();
  uint8 ucFlashBeamCmd = Dbl_RteAccess_ReadFlashBeamCmd();
  uint8 ucGfHbCmd = Dbl_RteAccess_ReadGfhbCmd();
  uint8 ucHbDiversity = CodDblDiversityParam();

  if (((ucHbCmd != FALSE) || (ucFlashBeamCmd != FALSE) || (ucHbCmd != FALSE && ucGfHbCmd != FALSE)) &&
      ((ucHbDiversity == (uint8)Dbl_eAUC_02) || (ucHbDiversity == (uint8)Dbl_eAUC_03)))
  {
    Dbl_boHB = TRUE;
  }
  else
  {
    Dbl_boHB = FALSE;
  }
}

/// ---------------------------------------------------------------------------
/// \brief Dbl_Write_OutputValues
/// 
/// \descr Produced flowsL bending beam fault, front swiveling angle
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
void Dbl_Write_OutputValues(void)
{

  Dbl_sMsgOut.State = Dbl_sState.eMain;

  if (Dbl_sCurvatureData.ucDblEnable == DBLSM_DBL_DISABLED) //  DBL feature is not active, then send 0 deg swivelling angle. 
  {
    Dbl_sMsgOut.SwivellingAngle[0].Hor = 0;
    Dbl_sMsgOut.SwivellingAngle[1].Hor = 0;
  }
  else
  {
    // do nothing. DBL feature is active
  }

  Dbl_RteAccess_WriteDblOutput(Dbl_sMsgOut, Dbl_sMsgOut.State, Dbl_eSubMode); // PRQA S 4424 // Cast is needed

    if (Dbl_eMountingSide == Dbl_eMountedLeft)
    {
      Dbl_RteAccess_WriteDblSysMonTx_FullStatus(Dbl_boDYN_BENDING_BEAM_FAULT);
    }

    Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(Dbl_eMountingSide, Dbl_boErrorFromOtherHL);
}

/// ---------------------------------------------------------------------------
/// \brief Dbl_StateMachine_StateAdj
/// 
/// \descr Front swiveling angle left and right shall be calculated according to vehicle trajectory curvature 
/// 
/// \param  -
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void Dbl_StateMachine_StateAdj(void)
{
  Dbl_Call_StateNormal();
 }

// -----------------------------------------------------------------------------
/// \brief  Dbl_SubModeFrozen
///
/// \descr  The system shall freeze the swiveling angle of left headlamp 
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void Dbl_SubModeFrozen(void)
{
  Dbl_Call_StateHold();
}

// ---------------------------------------------------------------------------
///  \func     Dbl_StMch
///
///  \brief    state machine for Dbl(Available mode)
///
///  \param    void
///
///  \return   void
// ---------------------------------------------------------------------------
STATIC_AL void Dbl_StMch(void)
{
  uint8 ucIx;

  // call current state
  Dbl_atStateMachine[(uint8)Dbl_sState.eMain].pStateFct();

  // go through all transitions for current state
  for (ucIx = 0; ucIx < Dbl_atStateMachine[(uint8)Dbl_sState.eMain].ucCount; ucIx++)
  {
    if (Dbl_atStateMachine[(uint8)Dbl_sState.eMain].pTransition[ucIx].ptTransitionFct() != FALSE)
    {
      // change current state 
      Dbl_sState.eMain = Dbl_atStateMachine[(uint8)Dbl_sState.eMain].pTransition[ucIx].eNewState;
      // mark new state as entered
      Dbl_sState.boEntry = TRUE;

      break;
    }
    else
    {
      // don t change state
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_SubModeUnavailable
///
/// \descr The system shall set the swiveling angle of left headlamp to 0 degree
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void Dbl_SubModeUnavailable(void)
{
  Dbl_Call_StateOff();
  Dbl_Reset_Flags();
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_GetTimer
///
/// \descr  This function is returning the address of the  timer
///
/// \param  void
///
/// \return tUtilDebounceControl
//-----------------------------------------------------------------------------
tUtilDebounceControl* Dbl_GetTimer(void)
{
  return &Dbl_sSwivelBckTimer;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_ConstHighSpeed_Detect
///
/// \descr  functino that checks if vehicle is in constant speed interval
///
/// \param  [unS] - speed in km/h
///
/// \return 
//-----------------------------------------------------------------------------
STATIC_AL void Dbl_ConstHighSpeed_Detect(sint32 snSpeed)
{
  //PRQA S 3415 ++  // side effects considered and are not a problem
  if (((uint16)snSpeed > CodDriveSit_ConstSpeedThr()) && ((uint16)snSpeed <= CodDriveSit_ConstMaxThr()))
  {
    UtilDebounce(&Dbl_HighSpeedTimer, TRUE);

    if (Dbl_HighSpeedTimer.eState == Di_On)
    {
      Dbl_DriveSituation.Bit.bHighSpeed = TRUE;
    }
  }
  else
  {
    Dbl_DriveSituation.Bit.bHighSpeed = FALSE;
    Dbl_HighSpeedTimer.eState = Di_Sna;
  }

}


//-----------------------------------------------------------------------------
/// \brief  Dbl_ReadInputSignals
///
/// \descr  This function read all input signals for dbl input
///
/// \param  void
///
/// \return tUtilDebounceControl
//-----------------------------------------------------------------------------
void Dbl_ReadInputSignals(void)
{
  uint32 ulDblSpeed = Dbl_RteAccess_ReadSpeed();
  
  Dbl_eErrorStatus = Dbl_ReadFault(Dbl_eMountingSide);

  (void)Dbl_GetTrafficSide();
  Dbl_sSignal.nSpeed = Dbl_RteAccess_ReadSpeed() * DBL_SPEED_RESOLUTION10;
  Dbl_boEtatMar = Dbl_RteAccess_ReadReverseGearStatus();
  Dbl_sSignal.ucStreetClass = 0u;
  // detect driving situation
  Dbl_ConstHighSpeed_Detect(Dbl_sSignal.nSpeed / 10); // PRQA S 4446, 1840 // Division is needed
}


//-----------------------------------------------------------------------------
/// \brief  Dbl_Timeout
///
/// \descr  This function returns timer status
///
/// \param  boReqInput, ulTimeMs, scTiTimerSel
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel)
{
  boolean boTimerTimeoutStatus = FALSE;
  if (ucTiTimerSel < DBL_NUMBER_OF_TIMERS)
  {
    Dbl_sTimerCfg[ucTiTimerSel].ulTimeMs_Input = ulTimeMs;
    Dbl_sTimerCfg[ucTiTimerSel].boReq_Input = boReqInput;
    boTimerTimeoutStatus = Dbl_HandleDelayStatus(Dbl_sTimerCfg, ucTiTimerSel);
  }
  return boTimerTimeoutStatus;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_HandleDelayStatus
///
/// \descr  This function return TimeOut = TRUE based on sTimersCfg Configurations
///
/// \param  *sTimersCfg, scTimerSel
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Dbl_HandleDelayStatus(tsDbl_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel)
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

#endif 
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

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
/// \file  CtrlDcmSm.c
///
/// \brief State Machine for Control of DC Motor
///
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include "CtrlDcm.h" /* ILCU_PORT: DPE include path <../Ctrl/Dcm/Api/CtrlDcm.h> flattened */
#include "CtrlDcmSm.h"
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <UtilUtility.h>, <Util_Time.h> */
#include "CtrlDcm_RteAccess.h"


//-----------------------------------------------------------------------------
// local types
//-----------------------------------------------------------------------------

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
//---------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------

  STATIC_AL tsCtrlDcm_State CtrlDcm_State = { CtrlDcm_ePhase_Init, TRUE };
  STATIC_AL teCtrlDcm_eMainMode CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
  STATIC_AL teCtrlDcm_eASLMode  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;
  STATIC_AL tsCtrlDcm_DcmStatusParameters CtrlDcm_sDcmStatusParams = { 0 };
  STATIC_AL CONST_AL tsCtrlDcm_StateMType* CtrlDcm_atStateMachine;


//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------

// local functions
 STATIC_AL void CtrlDcm_DetectMode            (void);
 STATIC_AL void CtrlDcm_UseMode               (void);
 STATIC_AL void CtrlDcm_UseSubMode(void);
 STATIC_AL void CtrlDcm_ResetDcmState(void);
 STATIC_AL void CtrlDcm_WriteStatusParams(void);
 STATIC_AL void CtrlDcm_HandleFailState(void);
 STATIC_AL void CtrlDcm_HandleFailStateBehavior(teCtrlDcm_FailStateHandling eLeftState, teCtrlDcm_FailStateHandling eRightState);

 // local functions SLAVE
 STATIC_AL void CtrlDcm_DetectSlaveSubMode(void);
 STATIC_AL void CtrlDcm_HandleFailState_Slave(void);
 STATIC_AL void CtrlDcm_HandleFailStateBehavior_Slave(teCtrlDcm_FailStateHandling eRightState);

 // state machine functions
 STATIC_AL void CtrlDcm_StateMachine_PhaseInit(void);
 STATIC_AL void CtrlDcm_StateMachine_PhaseFail(void);
 STATIC_AL void CtrlDcm_StateMachine_PhaseAdj(void);

 // state machine functions SLAVE
 STATIC_AL void CtrlDcm_StateMachine_PhaseInit_Slave(void);
 STATIC_AL void CtrlDcm_StateMachine_PhaseFail_Slave(void);

 //submode functions
 STATIC_AL void CtrlDcm_SubModeFactory(void);
 STATIC_AL void CtrlDcm_SubModeFrozen(void);
 STATIC_AL void CtrlDcm_SubModeUnavailable(void);

 STATIC_AL void CtrlDcm_ModeAssembly(void);
 STATIC_AL void CtrlDcm_ModeCustomer(void);


 // Transition functions MASTER
 STATIC_AL boolean CtrlDcm_Transition_Init_To_Adj(void);
 STATIC_AL boolean CtrlDcm_Transition_Init_To_Fail(void);
 STATIC_AL boolean CtrlDcm_Transition_Adj_To_Fail(void);
 STATIC_AL boolean CtrlDcm_Transition_Fail_To_Adj(void);


 // Transition functions SLAVE
 STATIC_AL boolean CtrlDcm_Transition_Init_To_Adj_Slave(void);
 STATIC_AL boolean CtrlDcm_Transition_Init_To_Fail_Slave(void);
 STATIC_AL boolean CtrlDcm_Transition_Adj_To_Fail_Slave(void);
 STATIC_AL boolean CtrlDcm_Transition_Fail_To_Adj_Slave(void);


//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------

 // state machine calls

 STATIC_AL void CtrlDcm_StMch(void);

 // transition functions for submodes
 STATIC_AL boolean CtrlDcm_Transition_Assembly_To_Frozen(void);
 STATIC_AL boolean CtrlDcm_Transition_Assembly_To_Factory(void);
 STATIC_AL  boolean CtrlDcm_Transition_Assembly_To_Unavailable(void);
 STATIC_AL boolean CtrlDcm_Transition_Customer_To_Unavailable(void);
 STATIC_AL boolean CtrlDcm_Transition_Customer_To_Available(void);


 // Transition tables for MASTER mode

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlDcm_asTransitionInit
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlDcm CtrlDcm_asTransitionInit[2] =
{
  //  new state                  transition function
  { CtrlDcm_ePhase_Fail ,      CtrlDcm_Transition_Init_To_Fail    },
  { CtrlDcm_ePhase_Adj ,       CtrlDcm_Transition_Init_To_Adj     }
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlDcm_asTransitionAdj
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlDcm CtrlDcm_asTransitionAdj[1] =
{
  //  new state                  transition function
  { CtrlDcm_ePhase_Fail,       CtrlDcm_Transition_Adj_To_Fail}
};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlDcm_asTransitionFail
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlDcm CtrlDcm_asTransitionFail[1] =
{
  //  new state                  transition function
  { CtrlDcm_ePhase_Adj ,       CtrlDcm_Transition_Fail_To_Adj    }

};

// Transition tables for SLAVE mode

// ---------------------------------------------------------------------------
// Transition function table for ucIx state  CtrlDcm_asTransitionInit_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlDcm CtrlDcm_asTransitionInit_Slave[2] =
{
  //  new state                  transition function
  { CtrlDcm_ePhase_Fail,       CtrlDcm_Transition_Init_To_Fail_Slave   },
  { CtrlDcm_ePhase_Adj ,       CtrlDcm_Transition_Init_To_Adj_Slave    }
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlDcm_asTransitionAdj_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlDcm CtrlDcm_asTransitionAdj_Slave[1] =
{
  //  new state                  transition function
  { CtrlDcm_ePhase_Fail,       CtrlDcm_Transition_Adj_To_Fail_Slave    }
};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlDcm_asTransitionFail_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlDcm CtrlDcm_asTransitionFail_Slave[1] =
{
  //  new state                  transition function
  { CtrlDcm_ePhase_Adj ,       CtrlDcm_Transition_Fail_To_Adj_Slave    }

};

// ---------------------------------------------------------------------------
// State machine table for Master mode
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tsCtrlDcm_StateMType CtrlDcm_atStateMachine_Master[3] =
{ //   state name                transition count (of tr-table) [ucCount]        transition table                              state function 
  { /* CtrlDcm_ePhase_Init,    */  UTIL_COUNTOF(CtrlDcm_asTransitionInit),     CtrlDcm_asTransitionInit,                CtrlDcm_StateMachine_PhaseInit    },
  { /* CtrlDcm_ePhase_Adj,     */  UTIL_COUNTOF(CtrlDcm_asTransitionAdj),      CtrlDcm_asTransitionAdj,                 CtrlDcm_StateMachine_PhaseAdj     },
  { /* CtrlDcm_ePhase_Fail,    */  UTIL_COUNTOF(CtrlDcm_asTransitionFail),     CtrlDcm_asTransitionFail,                CtrlDcm_StateMachine_PhaseFail    }
};



//// State machine table for SLAVE MODE 

STATIC_AL CONST_AL tsCtrlDcm_StateMType CtrlDcm_atStateMachine_Slave[3] =
{ //   state name                     transition count (of tr-table) [ucCount]        transition table                                state function 
  { /* CtrlDcm_ePhase_Init,     */ UTIL_COUNTOF(CtrlDcm_asTransitionInit_Slave),     CtrlDcm_asTransitionInit_Slave,                CtrlDcm_StateMachine_PhaseInit_Slave     },
  { /* CtrlDcm_ePhase_Adj,     */  UTIL_COUNTOF(CtrlDcm_asTransitionAdj_Slave),      CtrlDcm_asTransitionAdj_Slave,                 CtrlDcm_StateMachine_PhaseAdj            },
  { /* CtrlDcm_ePhase_Fail,    */  UTIL_COUNTOF(CtrlDcm_asTransitionFail_Slave),     CtrlDcm_asTransitionFail_Slave,                CtrlDcm_StateMachine_PhaseFail_Slave     }

};

//-----------------------------------------------------------------------------
/// \brief  cyclic function for CtrlDcm master
///
/// \descr reads singals , detects mode and submode and writes tg pos
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_Master_Cycle20ms(void)
{
  // exterior takeover status
    STATIC_UT(boolean, boExtTakeOver, FALSE);
  
  // get all input signals
  CtrlDcm_ReadMasterSignals();  
  CtrlDcm_ReadCommonSignals();

  boExtTakeOver = CtrlDcm_ReturnboExtTakeOver();

  if (boExtTakeOver == FALSE)
  {
    // detect functionality mode
    CtrlDcm_DetectMode();
    CtrlDcm_UseMode();
    CtrlDcm_UseSubMode();
  }
  else
  {
    // run the routine control
    CtrlDcm_DiagRoutineControl();
    CtrlDcm_State.boEntry = TRUE; // mark as a new state so ASL will recover when takeover is stopped
  }
  
  // calculate target position based on selected source
  CtrlDcm_GetTgtPos();
  // write parameters for validation team
  CtrlDcm_WriteStatusParams();
  // writw all output signals
  CtrlDcm_WriteMasterSignals();
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}
  
//-----------------------------------------------------------------------------
/// \brief  cyclic function for CtrlDcm Slave mode
///
/// \descr  reads singals , detects mode and submode and writes tg pos
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_Slave_Cycle20ms(void)
{ 
  // exterior takeover status
  STATIC_UT(boolean, boExtTakeOver,FALSE);
  // get all input signals
  CtrlDcm_ReadSlaveSignals();  
  CtrlDcm_ReadCommonSignals();

  boExtTakeOver = CtrlDcm_ReturnboExtTakeOver();

  if (boExtTakeOver == FALSE)
  {
    // detect mode and submode of functionality
    CtrlDcm_DetectSlaveSubMode();
    CtrlDcm_UseSubMode();
  }
  else
  {
    // run the routine control
    CtrlDcm_DiagRoutineControl();
    CtrlDcm_State.boEntry = TRUE; // mark as a new state so ASL will recover when takeover is stopped
  }
  
  // calculate target position based on selected source
  CtrlDcm_GetTgtPos();
  // write parameters for validation team
  CtrlDcm_WriteStatusParams();
  // writw all output signals
  CtrlDcm_WriteSlaveSignals();
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  initialisation function for CtrlDcm
///
/// \descr
///
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_Init(void)
{

    // detect side and initialize mode
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;
    CtrlDcm_DetectSide();
    if (CtrlDcm_ReturnSide() == CtrlDcm_eMountedLeft)
    {
      CtrlDcm_atStateMachine = CtrlDcm_atStateMachine_Master;
    }
    else 
    {
      CtrlDcm_atStateMachine = CtrlDcm_atStateMachine_Slave;
    }

    // map coding parameters
    CtrlDcm_RteAccess_MapParams();
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_UseMode
///
/// \descr  calls main mode function
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_UseMode(void)
{
  switch (CtrlDcm_eMainMode)
  {
  case CtrlDcm_eModeAssembly:
  {
    CtrlDcm_ModeAssembly();
    break;
  }

  case CtrlDcm_eModeCustomer:
  {
    CtrlDcm_ModeCustomer();
    break;
  }

  default: break;

  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_UseSubMode
///
/// \descr  calls submode function
///
/// \param   void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_UseSubMode(void)
{
  switch (CtrlDcm_eASLMode)
  {

  case CtrlDcm_eModeUnavailable:
  {
    // reset DC motor state if it was previously in available mode
    CtrlDcm_ResetDcmState();
    // call submode function
    CtrlDcm_SubModeUnavailable();
    break;
  }
  case CtrlDcm_eModeAvailable:
  {
    CtrlDcm_StMch();
    break;
  }
  case CtrlDcm_eModeFrozen:
  {
    // reset DC motor state if it was previously in available mode
    CtrlDcm_ResetDcmState();
    // call submode function
    CtrlDcm_SubModeFrozen();
    break;
  }
  case CtrlDcm_eModeFactory:
  {
    // reset DC motor state if it was previously in available mode
    CtrlDcm_ResetDcmState();
    // call submode function
    CtrlDcm_SubModeFactory();
    break;
  }

  default: break;
  }

  
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_WriteStatusParams
///
/// \descr  write status parameters in rte port
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL   void CtrlDcm_WriteStatusParams(void)
{
  CtrlDcm_sDcmStatusParams.eASL_MODE  = CtrlDcm_eASLMode;
  CtrlDcm_sDcmStatusParams.eASL_PHASE = CtrlDcm_State.ePhase;

  CtrlDcm_sDcmStatusParams.boLvlAdjFunctionalFault_L = CtrlDcm_ReturnboLvlAdjFuncFault();
  CtrlDcm_sDcmStatusParams.boLvlAdjFunctionalFault_R = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();
  CtrlDcm_sDcmStatusParams.boLvlAdjHeadlampFault     = CtrlDcm_ReturnboLvlAdjHeadlampFault();

  CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(&CtrlDcm_sDcmStatusParams);
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SubModeUnavailable
///
/// \descr  submode function for unavailable mode
///
/// \param    void
///
/// \return   void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_SubModeUnavailable(void)
{
  // set Dcm to sleep position
  CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
  CtrlDcm_SetDiagLvl(FALSE);
  CtrlDcm_SetSlaveStopRequest(TRUE);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SubModeFactory
///
/// \descr  submode function for factory mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_SubModeFactory(void)
{
    CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
    CtrlDcm_SetDiagLvl(TRUE);
    CtrlDcm_SetSlaveStopRequest(TRUE);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_SubModeFrozen
///
/// \descr submode function for frozen state
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_SubModeFrozen(void)
{
  // set Dcm to sleep position
  CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
  CtrlDcm_SetDiagLvl(TRUE);
  CtrlDcm_SetSlaveStopRequest(TRUE);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ModeAssembly
///
/// \descr  detects submode of assembly mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_ModeAssembly(void)
{

  // check transitions
  if (CtrlDcm_Transition_Assembly_To_Frozen() != FALSE)
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
  }
  else if (CtrlDcm_Transition_Assembly_To_Factory() != FALSE)
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeFactory;
  }
  else if (CtrlDcm_Transition_Assembly_To_Unavailable() != FALSE)
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;
  }
  else
  {
    // remain in current submode
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_ModeAssembly
///
/// \descr  detects submode of assembly mode
///
/// \param  - void
///
/// \return   void
//-----------------------------------------------------------------------------
  STATIC_AL  void CtrlDcm_ModeCustomer(void)
{

  if (CtrlDcm_Transition_Customer_To_Available() != FALSE)
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
  }
  else if (CtrlDcm_Transition_Customer_To_Unavailable() != FALSE)
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;

  }
  else
  {
    // remain in current submode
  }
}

  //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Init_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlDcm_Transition_Init_To_Adj(void)
{
  boolean boLvlFuncHeadlampFaultL = CtrlDcm_ReturnboLvlAdjHeadlampFault();
  boolean boLvlFuncHeadlampFaultR = CtrlDcm_ReturnboLvlAdjHeadlampFault_R();
  boolean boReturnValue           = FALSE;
  boolean boPowertrainActive      = CtrlDcm_RetPowerTrainActive();
  boolean boLvlAdjFuncFault       = CtrlDcm_ReturnboLvlAdjFuncFault();
  teCtrlDcm_MountingSide eMountingSide = CtrlDcm_ReturnSide();
  boolean boParamReady            = CtrlDcm_CodingDataReady(&eMountingSide);
  boolean boCondEnabled           = CtrlDcm_CondEnabled();
  boolean boAslEnabled            = ((boParamReady != FALSE) && (boCondEnabled != FALSE)) ? TRUE : FALSE;

  boReturnValue = ((boPowertrainActive      != FALSE) &&
                   (boAslEnabled            != FALSE) &&
                   (boLvlAdjFuncFault       == FALSE) &&
                   (boLvlFuncHeadlampFaultL == FALSE) &&
                   (boLvlFuncHeadlampFaultR == FALSE)) ? TRUE : FALSE;

  return boReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Init_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlDcm_Transition_Init_To_Fail(void)
{
  boolean boLvlFuncHeadlampFaultL    = CtrlDcm_ReturnboLvlAdjHeadlampFault();
  boolean boLvlFuncHeadlampFaultR    = CtrlDcm_ReturnboLvlAdjHeadlampFault_R();
  teCtrlDcm_SensorState eSensorError = CtrlDcm_ReturneSensorError();
  boolean boLvlAdjFuncFault          = CtrlDcm_ReturnboLvlAdjFuncFault();

  boolean boReturn = ((boLvlAdjFuncFault       != FALSE) ||
                      (boLvlFuncHeadlampFaultL != FALSE) ||
                      (boLvlFuncHeadlampFaultR != FALSE) ||
                      (eSensorError            == CtrlDcm_eHLS_STORED_FAILURE)) ? TRUE : FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Adj_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlDcm_Transition_Adj_To_Fail(void)
{
  boolean boReturn                   = FALSE;
  teCtrlDcm_SensorState eSensorError = CtrlDcm_ReturneSensorError();
  boolean boLvlAdjFuncFault          = CtrlDcm_ReturnboLvlAdjFuncFault();
  boolean boLvlFuncHeadlampFaultL    = CtrlDcm_ReturnboLvlAdjHeadlampFault();
  boolean boLvlFuncHeadlampFaultR    = CtrlDcm_ReturnboLvlAdjHeadlampFault_R();

  boReturn = ((boLvlFuncHeadlampFaultL != FALSE)                       ||
              (boLvlFuncHeadlampFaultR != FALSE)                       ||
              (eSensorError            == CtrlDcm_eHLS_SENSOR_FAILURE) ||
              (eSensorError            == CtrlDcm_eHLS_FROZEN_FAILURE) ||
              (boLvlAdjFuncFault       != FALSE)) ? TRUE:FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Fail_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlDcm_Transition_Fail_To_Adj(void)
{
  boolean boReturn = FALSE;
  boolean boPowerTrainActive         = CtrlDcm_RetPowerTrainActive();
  teCtrlDcm_SensorState eSensorError = CtrlDcm_ReturneSensorError();
  boolean boLvlAdjFuncFault          = CtrlDcm_ReturnboLvlAdjFuncFault();
  boolean boLvlFuncHeadlampFaultL    = CtrlDcm_ReturnboLvlAdjHeadlampFault();
  boolean boLvlFuncHeadlampFaultR    = CtrlDcm_ReturnboLvlAdjHeadlampFault_R();

  boolean boFailure = ((boLvlFuncHeadlampFaultL == FALSE)                   &&
                       (boLvlFuncHeadlampFaultR == FALSE)                   &&
                       (eSensorError            == CtrlDcm_eHLS_NO_FAILURE) &&
                       (boLvlAdjFuncFault       == FALSE)) ? FALSE:TRUE;

  boReturn = ((boPowerTrainActive != FALSE) &&
              (boFailure          == FALSE)) ? TRUE:FALSE;


  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Assembly_To_Frozen
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlDcm_Transition_Assembly_To_Frozen(void)
{
  boolean boReturn      = FALSE;  
  uint8 ucModeConfigVhl = CtrlDcm_RteAccess_ReadVehicleModeConfig();

  if ((ucModeConfigVhl == (uint8)eModeConfigVehicle_Montage)  || 
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Invalid2) ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Controle))
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
/// \brief  CtrlDcm_Transition_Assembly_To_Factory
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlDcm_Transition_Assembly_To_Factory(void)
{
  boolean boReturn        = FALSE;
  uint8 ucModeConfigVhl   = CtrlDcm_RteAccess_ReadVehicleModeConfig();
  boolean boTrainingState = CtrlDcm_ReturnboTrainingState();

  if (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine)        ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Client)       ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Showroom)     ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Stockage)     ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_AfterMarket)) &&
       (boTrainingState == FALSE))
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
/// \brief  CtrlDcm_Transition_Assembly_To_Unavailable
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlDcm_Transition_Assembly_To_Unavailable(void)
{
  boolean boReturn        = FALSE;
  uint8   ucModeConfigVhl = CtrlDcm_RteAccess_ReadVehicleModeConfig();
  boolean boTrainingState = CtrlDcm_ReturnboTrainingState();
  boolean boIgnition      = CtrlDcm_RetVehIgnition();

  if (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine)        ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_AfterMarket)) &&
       (boTrainingState != FALSE)                                  &&
       (boIgnition      == FALSE))
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
/// \brief  CtrlDcm_Transition_Customer_To_Unavailable
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlDcm_Transition_Customer_To_Unavailable(void)
{
  boolean boReturn;
  boolean boIgnition = CtrlDcm_RetVehIgnition();

  if (boIgnition == FALSE)
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
/// \brief  CtrlDcm_Transition_Customer_To_Available
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlDcm_Transition_Customer_To_Available(void)
{
  boolean boReturn         = FALSE;
  boolean boTrainingStatus = CtrlDcm_ReturnboTrainingState();
  boolean boIgnition       = CtrlDcm_RetVehIgnition();

  if  ((boTrainingStatus != FALSE) &&
       (boIgnition       != FALSE))
  {
    boReturn = TRUE;
  }
  else
  {
    boReturn = FALSE;
  }

  return boReturn; 
}


// ---------------------------------------------------------------------------
//  \func     CtrlDcm_StMch
//
//  \brief    state machine for DC Motor. Calls state function and goes through each state transition check
//
//  \param    void
//
//  \return   void
// ---------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_StMch(void)
  {
    uint8 ucIx;

    // call current state
    CtrlDcm_atStateMachine[(uint8)CtrlDcm_State.ePhase].pStateFct();

    // go through all transitions for current state
    for (ucIx = 0u; ucIx < CtrlDcm_atStateMachine[(uint8)CtrlDcm_State.ePhase].ucCount; ucIx++)
    {
      if (CtrlDcm_atStateMachine[(uint8)CtrlDcm_State.ePhase].pTransition[ucIx].ptTransitionFct() != FALSE)
      {
        // change current state 
        CtrlDcm_State.ePhase = CtrlDcm_atStateMachine[(uint8)CtrlDcm_State.ePhase].pTransition[ucIx].eNewState;
        // mark new state as entered
        CtrlDcm_State.boEntry = TRUE;
        break;
      }
      else
      {
        // don t change state
      }
    }
  }


  //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_StateMachine_PhaseFail
///
/// \descr  State Machine: behavior in case of state Err
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_StateMachine_PhaseFail(void)
  {
    // first check if we are in the initial phase of the state
    if (CtrlDcm_State.boEntry != FALSE)
    {
      CtrlDcm_State.boEntry = FALSE;
    }
    else  // we have passed sub state "entry"
    {
      // handle fail state
    }
    CtrlDcm_HandleFailState();
  }

  //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_HandleFailState
///
/// \descr  Handle fail state behavior
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_HandleFailState(void)
  {
    static teCtrlDcm_FailStateHandling eFailStateLeft  = CtrlDcm_eFreeze; /* ILCU_PORT: was read uninitialised on the keep-previous path (UB) */
    static teCtrlDcm_FailStateHandling eFailStateRight = CtrlDcm_eFreeze; /* ILCU_PORT: was read uninitialised on the keep-previous path (UB) */
    boolean boLvlFuncHeadlampFaultL;
    boolean boLvlFuncHeadlampFaultR;
    boolean boPowertrainActive         = CtrlDcm_RetPowerTrainActive();
    boolean boLvlAdjFuncFault          = CtrlDcm_ReturnboLvlAdjFuncFault();
    teCtrlDcm_SensorState eSensorError = CtrlDcm_ReturneSensorError();

    boLvlFuncHeadlampFaultL = CtrlDcm_ReturnboLvlAdjHeadlampFault();
    boLvlFuncHeadlampFaultR = CtrlDcm_ReturnboLvlAdjHeadlampFault_R();

    if (boPowertrainActive == FALSE)
    {
      eFailStateLeft  = CtrlDcm_eFreeze;
      eFailStateRight = CtrlDcm_eFreeze;
    }
    else if (boLvlAdjFuncFault != FALSE)
    {
      eFailStateLeft  = CtrlDcm_eSafety_IgnitionNeeded;
      eFailStateRight = CtrlDcm_eSafety_IgnitionNeeded;
    }
    else if ((boLvlFuncHeadlampFaultL != FALSE) && (boLvlFuncHeadlampFaultR == FALSE))
    {
      eFailStateLeft  = CtrlDcm_eFreeze;
      eFailStateRight = CtrlDcm_eContinue;
    }
    else if ((boLvlFuncHeadlampFaultL == FALSE) && (boLvlFuncHeadlampFaultR != FALSE))
    {
      eFailStateLeft  = CtrlDcm_eContinue;
      eFailStateRight = CtrlDcm_eFreeze;
    }
    else if ((boLvlFuncHeadlampFaultL != FALSE) && (boLvlFuncHeadlampFaultR != FALSE))
    {
      eFailStateLeft  = CtrlDcm_eFreeze;
      eFailStateRight = CtrlDcm_eFreeze;
    }
    else if (eSensorError != CtrlDcm_eHLS_NO_FAILURE)
    {
      eFailStateLeft  = CtrlDcm_eSafety;
      eFailStateRight = CtrlDcm_eSafety;
    }
    else
    {
      // keep previous values
    }

    CtrlDcm_SetDiagLvl(TRUE); // set DIAG_LVL to NOK
    CtrlDcm_HandleFailStateBehavior(eFailStateLeft, eFailStateRight);
    //PRQA S 5336 1 // STMIF is exceeded due to program architecture and readability
  }

  //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_HandleFailStateBehavior
///
/// \descr  Handle Fail state behavior for Master and Slave control
///
/// \param  teCtrlDcm_FailStateHandling eLeftState - state for Master
/// \param  teCtrlDcm_FailStateHandling eRightState - state for Slave
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_HandleFailStateBehavior(teCtrlDcm_FailStateHandling eLeftState, teCtrlDcm_FailStateHandling eRightState)
  {
    switch (eLeftState)
    {
      case CtrlDcm_eFreeze:
      {
        CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
        break;
      }
      case CtrlDcm_eSafety:
      {
        CtrlDcm_SetSignalMode(eDcmSrc_SafetyPos);
        break;
      }
      case CtrlDcm_eSafety_IgnitionNeeded:
      {
        CtrlDcm_SetSignalMode(eDcmSrc_SafetyPos);
        CtrlDcm_SetFailIgnitionNeeded(TRUE);
        break;
      }
      case CtrlDcm_eContinue:
      {
        CtrlDcm_SetSignalMode(eDcmSrc_NormalPos);
        break;
      }
      default:
        break;
    }

    switch (eRightState)
    {
    case CtrlDcm_eFreeze:
    {
      CtrlDcm_SetSlaveStopRequest(TRUE);
      CtrlDcm_SetSlaveSafetyPosition(FALSE);
      break;
    }
    case CtrlDcm_eSafety:
    {
      CtrlDcm_SetSlaveStopRequest(FALSE);
      CtrlDcm_SetSlaveSafetyPosition(TRUE);
      break;
    }
    case CtrlDcm_eSafety_IgnitionNeeded:
    {
      CtrlDcm_SetSlaveStopRequest(FALSE);
      CtrlDcm_SetSlaveSafetyPosition(TRUE);
      CtrlDcm_SetFailIgnitionNeeded(TRUE);
      break;
    }
    case CtrlDcm_eContinue:
    {
      CtrlDcm_SetSlaveStopRequest(FALSE);
      CtrlDcm_SetSlaveSafetyPosition(FALSE);
      break;
    }
    default:
      break;
    }
  }


//-----------------------------------------------------------------------------
/// \brief CtrlDcm_StateMachine_PhaseInit
///
/// \descr  State Machine: behavior in case of state Init
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_StateMachine_PhaseInit(void)
  {
    if (CtrlDcm_State.boEntry != FALSE)
    {
      CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
      CtrlDcm_SetDiagLvl(FALSE);
      CtrlDcm_SetSlaveStopRequest(TRUE);
      CtrlDcm_State.boEntry = FALSE;
    }
    else
    {
      // do nothing
    }
  }

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_StateMachine_PhaseAdj
///
/// \descr  State Machine: behavior in case of adjustment state
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL  void CtrlDcm_StateMachine_PhaseAdj(void)
{
  if (CtrlDcm_State.boEntry != FALSE)
  {
    // do normal behavior according to sAVAC
    CtrlDcm_SetSignalMode(eDcmSrc_NormalPos);
    CtrlDcm_State.boEntry = FALSE; // reset state machine entry flag
    CtrlDcm_SetSlaveStopRequest(FALSE); // make sure not to keep slave movement blocked
    CtrlDcm_SetSlaveSafetyPosition(FALSE); // clear slave safety position flag
    CtrlDcm_SetDiagLvl(FALSE);  // set DIAG_LVL to OK
  }
  else
  {
    // keep executing adjusment phase according to vehicle attitude
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_DetectMode
///
/// \descr  detects main mode of DC motor control
///
/// \param  -void
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlDcm_DetectMode(void)
{
  uint8 ucModeConfigVhl = CtrlDcm_RteAccess_ReadVehicleModeConfig();
  boolean boTrainingState = CtrlDcm_ReturnboTrainingState();

  if (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Client)       ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Showroom)     ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Stockage)     ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine)        ||
       (ucModeConfigVhl == (uint8)eModeConfigVehicle_AfterMarket)) &&
       (boTrainingState != FALSE))
  {
    CtrlDcm_eMainMode = CtrlDcm_eModeCustomer;
  }
  else
  {
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
  }
}
//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_DetectMode
///
/// \descr  checks if DC motor was previously activated and it resets the state if so
///
/// \param  -void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlDcm_ResetDcmState(void)
{
    STATIC_UT(boolean, boFirstEntry, TRUE);

  if (boFirstEntry != FALSE)
  {
    boFirstEntry = FALSE;
  }
  else
  {
    // keep current values
  }

  if (CtrlDcm_State.ePhase != CtrlDcm_ePhase_Init)  // check if command is called too early
  {
    CtrlDcm_State.ePhase  = CtrlDcm_ePhase_Init;
    CtrlDcm_State.boEntry = TRUE;
    boFirstEntry          = TRUE;
  }
  else
  {
    // DC motor is already in init state
  }
}



/////////////////////////////////////////
/////// SLAVE MODE FUNCTIONS
/////////////////////////////////////////


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Adj_To_Fail_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlDcm_Transition_Adj_To_Fail_Slave(void)
{
  boolean boLvlAdjFuncFault       = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();
  boolean boLvlFuncHeadlampFaultR = CtrlDcm_ReturnboLvlAdjHeadlampFault();

  boolean boReturn = ((boLvlFuncHeadlampFaultR != FALSE) || (boLvlAdjFuncFault != FALSE)) ? TRUE : FALSE;

  return boReturn;

}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Fail_To_Adj_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlDcm_Transition_Fail_To_Adj_Slave(void)
{
  boolean boLvlAdjFuncFault = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();
  boolean boLvlFuncHeadlampFaultR = CtrlDcm_ReturnboLvlAdjHeadlampFault();

  boolean boReturn = (
    (boLvlFuncHeadlampFaultR == FALSE) &&
    (boLvlAdjFuncFault       == FALSE)) ? TRUE : FALSE;

    return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Init_To_Adj_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlDcm_Transition_Init_To_Adj_Slave(void)
{
  teCtrlDcm_MountingSide eMountingSide = CtrlDcm_ReturnSide();
  boolean boLvlAdjFuncFault       = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();
  boolean boLvlFuncHeadlampFaultR = CtrlDcm_ReturnboLvlAdjHeadlampFault();
  boolean boPowertrainActive      = CtrlDcm_RetPowerTrainActive();
  boolean boParamReady            = CtrlDcm_CodingDataReady(&eMountingSide);
  boolean boCondEnabled           = CtrlDcm_CondEnabled();
  boolean boAslEnabled            = ((boParamReady != FALSE) && (boCondEnabled != FALSE)) ? TRUE : FALSE;

  boolean boReturn = ((boLvlFuncHeadlampFaultR == FALSE) && 
                      (boLvlAdjFuncFault       == FALSE) &&
                      (boAslEnabled            != FALSE) &&
                      (boPowertrainActive      != FALSE)) ? TRUE : FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_Transition_Init_To_Fail_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlDcm_Transition_Init_To_Fail_Slave(void)
{
  boolean boLvlAdjFuncFault = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();
  boolean boLvlFuncHeadlampFaultR = CtrlDcm_ReturnboLvlAdjHeadlampFault();

  boolean boReturn = ((boLvlFuncHeadlampFaultR != FALSE) || (boLvlAdjFuncFault != FALSE)) ? TRUE : FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_DetectSlaveSubMode
///
/// \descr  detect submode of slave mode
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlDcm_DetectSlaveSubMode(void)
{
  boolean boIgnition = CtrlDcm_RetVehIgnition();


  if (boIgnition == FALSE)
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;
  }
  else
  {
    CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
  }
}

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_StateMachine_PhaseInit_Slave
///
/// \descr  State Machine: behavior in case of state Init for Slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_StateMachine_PhaseInit_Slave(void)
  {
    if (CtrlDcm_State.boEntry != FALSE)
    {
      CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
      CtrlDcm_State.boEntry = FALSE;
    }
    else
    {
      // do nothing
    }
  }

    //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_StateMachine_PhaseFail_Slave
///
/// \descr  State Machine: behavior in case of state Err for Slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_StateMachine_PhaseFail_Slave(void)
  {
    // first check if we are in the initial phase of the state
    if (CtrlDcm_State.boEntry != FALSE)
    {
      CtrlDcm_State.boEntry = FALSE;
    }
    else  // we have passed sub state "entry"
    {
      // handle fail state
    }
    CtrlDcm_HandleFailState_Slave();
  }

  //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_HandleFailState_Slave
///
/// \descr  Handle fail state behavior for Slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_HandleFailState_Slave(void)
  {
    static teCtrlDcm_FailStateHandling eFailState = CtrlDcm_eFreeze; /* ILCU_PORT: was read uninitialised on the keep-previous path (UB) */
    boolean boLvlFuncHeadlampFault;
    boolean boPowertrainActive = CtrlDcm_RetPowerTrainActive();
    boolean boLvlAdjFuncFault  = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();

    boLvlFuncHeadlampFault = CtrlDcm_ReturnboLvlAdjHeadlampFault();

    if ((boPowertrainActive == FALSE) && (boLvlAdjFuncFault != FALSE))
    {
      eFailState  = CtrlDcm_eFreeze;
    }
    else if ((boPowertrainActive != FALSE) && (boLvlAdjFuncFault != FALSE))
    {
      eFailState  = CtrlDcm_eSafety;
    }
    else if (boLvlFuncHeadlampFault != FALSE)
    {
      eFailState  = CtrlDcm_eFreeze_IgnitionNeeded;
    }
    else
    {
      // keep previous values
    }

    CtrlDcm_HandleFailStateBehavior_Slave(eFailState);
  }

    //-----------------------------------------------------------------------------
/// \brief  CtrlDcm_HandleFailStateBehavior_Slave
///
/// \descr  Handle Fail state behavior for Slave control
///
/// \param  teCtrlDcm_FailStateHandling eRightState - state for Slave
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlDcm_HandleFailStateBehavior_Slave(teCtrlDcm_FailStateHandling eRightState)
  {
    switch (eRightState)
    {
    case CtrlDcm_eFreeze:
    {
      CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
      break;
    }
    case CtrlDcm_eSafety:
    {
      CtrlDcm_SetSignalMode(eDcmSrc_SafetyPos);
      break;
    }
    case CtrlDcm_eFreeze_IgnitionNeeded:
    {
      CtrlDcm_SetSignalMode(eDcmSrc_SleepPos);
      CtrlDcm_SetFailIgnitionNeeded(TRUE);
      break;
    }
    default:
      break;
    }
  }



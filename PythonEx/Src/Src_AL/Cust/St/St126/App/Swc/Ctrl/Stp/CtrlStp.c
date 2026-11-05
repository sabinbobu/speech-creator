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
/// \file  CtrlStp.c
///
/// \brief	The software component CtrlStp can be initialized from the RTE.
///			All monitor counters, values and timers will be initialized during initialization.
///			The RTE call CtrlStp cyclicaly. In each cycle call CtrlStp performs tbd for each stepper
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <../Ctrl/Stp/Api/CtrlStp.h>
#include <CtrlStp_Core.h>
#include <UtilUtility.h>
#include <CtrlStp_RteAccess.h>
#include <Util_Time.h>
#include <Bsw/Sys/Load/SysLoad.h>


#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCtrlStpInit)
SYS_LOAD_MEAS_VAR_DEC(rpCtrlStp_Cycle)
#endif

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define CTRLSTP_DIAG_AP_INDICATION     0xFFFFu  //indication of sleep position request
#define CTRLSTP_SLAVE_NB_OF_PHASES          3u  // nb of phases in slave mode
#define CTRLSTP_SLAVE_MAX_STATES            4u  // nb of states in slave mode


//-----------------------------------------------------------------------------
// local types
//-----------------------------------------------------------------------------

#ifdef UNIT_TEST
typedef enum {
  VEILLE = (uint8)0x00,
  NM_NORMAL = (uint8)0x01,
  MISE_EN_VEILLE = (uint8)0x02,
  REVEIL = (uint8)0x03,
  COM_OFF = (uint8)0x04
  , LIMP_HOME_MODE = (uint8)0x05
} NM_ModeType;
#endif


// Transition function pointer
typedef boolean(*ptTransitionFctPtrCtrlStp)(void);


// Transition function informations
typedef struct
{
  CONST_AL teCtrlStp_StatMain             eNewState;
  CONST_AL ptTransitionFctPtrCtrlStp ptTransitionFct;
} tsTransitionCtrlStp ;



typedef void(*tStateFctPtrCtrlStp)(void);

typedef struct
{
  CONST_AL uint8                        ucCount;
  CONST_AL tsTransitionCtrlStp *CONST_AL pTransition;
  CONST_AL tStateFctPtrCtrlStp      pStateFct;
} tsCtrlStp_StateMType;
//---------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------

  STATIC_AL volatile tsCtrlStp_State CtrlStp_State = { CtrlStp_eState_Init, TRUE };
  STATIC_AL volatile teCtrlStp_eMainMode CtrlStp_eMainMode = CtrlStp_eModeAssembly;
  STATIC_AL teCtrlStp_eSubMode  CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
  STATIC_AL tsCtrlStp_ValidationParameters CtrlStp_sValidationParams;
  STATIC_AL CONST_AL tsCtrlStp_StateMType* CtrlStp_atStateMachine;
  STATIC_AL boolean CtrlStp_boRefReady         = FALSE;
  STATIC_AL boolean CtrlStp_boIsRefDone        = FALSE; // reference status used for aftersale mode and factory mode
  STATIC_AL boolean CtrlStp_boEntryUnavailable = FALSE; // reference status used for aftersale mode and factory mode
  STATIC_AL boolean CtrlStp_StartDiagLvlTimer = FALSE;

//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------
  STATIC_AL void CtrlStp_Init      (void);

// local functions
 STATIC_AL void CtrlStp_DetectMode            (void);
 STATIC_AL void CtrlStp_UseMode               (void);
 STATIC_AL void CtrlStp_UseSubMode(void);
 STATIC_AL void CtrlStp_Proccess_Reference(void);
 STATIC_AL void CtrlStp_ResetStpState(void);
 STATIC_AL void CtrlStp_VerifyAndProcessRefRun(void);
 STATIC_AL void CtrlStp_WriteValidationParams(void);
 STATIC_AL void CtrlStp_HandleFailState(void);
 STATIC_AL void CtrlStp_HandleFailStateBehavior(teCtrlStp_FailStateHandling eLeftState, teCtrlStp_FailStateHandling eRightState);
 STATIC_AL void CtrlStp_HandleDiagLvl(boolean boStepLossErr);

 // local functions SLAVE
 STATIC_AL void CtrlStp_DetectSlaveSubMode(void);
 STATIC_AL void CtrlStp_HandleFailState_Slave(void);
 STATIC_AL void CtrlStp_HandleFailStateBehavior_Slave(teCtrlStp_FailStateHandling eRightState);

 // state machine functions
 STATIC_AL void CtrlStp_StateMachine_StateInit(void);
 STATIC_AL void CtrlStp_StateMachine_StateFail(void);
 STATIC_AL void CtrlStp_StateMachine_StateRef(void);
 STATIC_AL void CtrlStp_StateMachine_StateAdj(void);
 STATIC_AL void CtrlStp_StateMachine_StateSTT(void);

 // state machine functions SLAVE
 STATIC_AL void CtrlStp_StateMachine_StateInit_Slave(void);
 STATIC_AL void CtrlStp_StateMachine_StateFail_Slave(void);

 //submode functions
 STATIC_AL void CtrlStp_SubModeFactory(void);
 STATIC_AL void CtrlStp_SubModeFrozen(void);
 STATIC_AL void CtrlStp_SubModeAfterSale(void);
 STATIC_AL void CtrlStp_SubModeUnavailable(void);

 STATIC_AL void CtrlStp_ModeAssembly(void);
 STATIC_AL void CtrlStp_ModeCustomer(void);


 // Transition functions MASTER
 STATIC_AL boolean CtrlStp_Transition_Init_To_Ref(void);
 STATIC_AL boolean CtrlStp_Transition_Init_To_Fail(void);
 STATIC_AL boolean CtrlStp_Transition_Ref_To_Adj(void);
 STATIC_AL boolean CtrlStp_Transition_Ref_To_Fail(void);
 STATIC_AL boolean CtrlStp_Transition_Ref_To_STT(void);
 STATIC_AL boolean CtrlStp_Transition_Adj_To_Fail(void);
 STATIC_AL boolean CtrlStp_Transition_Adj_To_STT(void);
 STATIC_AL boolean CtrlStp_Transition_Fail_To_Ref(void);
 STATIC_AL boolean CtrlStp_Transition_Fail_To_Adj(void);
 STATIC_AL boolean CtrlStp_Transition_STT_To_Ref(void);
 STATIC_AL boolean CtrlStp_Transition_STT_To_Adj(void);


 // Transition functions SLAVE
 STATIC_AL boolean CtrlStp_Transition_Init_To_Adj_Slave(void);
 STATIC_AL boolean CtrlStp_Transition_Adj_To_Fail_Slave(void);
 STATIC_AL boolean CtrlStp_Transition_Adj_To_Ref_Slave(void);
 STATIC_AL boolean CtrlStp_Transition_Fail_To_Adj_Slave(void);
 STATIC_AL boolean CtrlStp_Transition_Fail_To_Ref_Slave(void);
 STATIC_AL boolean CtrlStp_Transition_Ref_To_Fail_Slave(void);
 STATIC_AL boolean CtrlStp_Transition_Ref_To_Adj_Slave(void);



//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------
 STATIC_AL  void CtrlStp_Master_Cycle20ms(void);
 STATIC_AL  void CtrlStp_Slave_Cycle20ms(void);

 STATIC_AL  void CtrlStp_Init(void);

 // state machine calls

 STATIC_AL void CtrlStp_StMch(void);

 // transition functions for submodes
 STATIC_AL boolean CtrlStp_Transition_Assembly_To_Frozen(void);
 STATIC_AL boolean CtrlStp_Transition_Assembly_To_Factory(void);
 STATIC_AL  boolean CtrlStp_Transition_Assembly_To_Unavailable(void);
 STATIC_AL boolean CtrlStp_Transition_Customer_To_Unavailable(void);
 STATIC_AL boolean CtrlStp_Transition_Customer_To_Available(void);
 STATIC_AL boolean CtrlStp_Transition_Customer_To_Aftersale(void);


 // Transition tables for MASTER mode

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionInit
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionInit[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Ref ,       CtrlStp_Transition_Init_To_Ref     },
  { CtrlStp_eState_Fail ,      CtrlStp_Transition_Init_To_Fail    }
};

// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionRef
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionRef[3] =
{
  //  new state                  transition function
  { CtrlStp_eState_Adj ,       CtrlStp_Transition_Ref_To_Adj     },
  { CtrlStp_eState_Fail ,      CtrlStp_Transition_Ref_To_Fail    },
  { CtrlStp_eState_STT ,       CtrlStp_Transition_Ref_To_STT     }

};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionAdj
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionAdj[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Fail,       CtrlStp_Transition_Adj_To_Fail    },
  { CtrlStp_eState_STT ,       CtrlStp_Transition_Adj_To_STT     }

};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionFail
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionFail[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Ref ,       CtrlStp_Transition_Fail_To_Ref    },
  { CtrlStp_eState_Adj ,       CtrlStp_Transition_Fail_To_Adj    }

};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionSTT
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionSTT[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Ref ,      CtrlStp_Transition_STT_To_Ref    },
  { CtrlStp_eState_Adj,       CtrlStp_Transition_STT_To_Adj    }

};



// Transition tables for SLAVE mode

// ---------------------------------------------------------------------------
// Transition function table for ucIx state  CtrlStp_asTransitionInit_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionInit_Slave[1] =
{
  //  new state                  transition function
  { CtrlStp_eState_Adj ,       CtrlStp_Transition_Init_To_Adj_Slave    }
};
// -
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionRef_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionRef_Slave[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Adj ,       CtrlStp_Transition_Ref_To_Adj_Slave     },
  { CtrlStp_eState_Fail ,      CtrlStp_Transition_Ref_To_Fail_Slave    }
};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionAdj_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionAdj_Slave[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Fail,       CtrlStp_Transition_Adj_To_Fail_Slave    },
  { CtrlStp_eState_Ref ,       CtrlStp_Transition_Adj_To_Ref_Slave     }

};
// ---------------------------------------------------------------------------
// Transition function table for ucIx state CtrlStp_asTransitionFail_Slave
// ---------------------------------------------------------------------------
STATIC_AL CONST_AL tsTransitionCtrlStp CtrlStp_asTransitionFail_Slave[2] =
{
  //  new state                  transition function
  { CtrlStp_eState_Ref ,       CtrlStp_Transition_Fail_To_Ref_Slave    },
  { CtrlStp_eState_Adj ,       CtrlStp_Transition_Fail_To_Adj_Slave    }

};

// ---------------------------------------------------------------------------
// State machine table for Master mode
// ---------------------------------------------------------------------------

STATIC_AL CONST_AL tsCtrlStp_StateMType CtrlStp_atStateMachine_Master[CtrlStp_eState_Maxsize] =
{ //   state name                transition count (of tr-table) [ucCount]        transition table                              state function 
  { /* CtrlStp_eState_Init,    */  UTIL_COUNTOF(CtrlStp_asTransitionInit),     CtrlStp_asTransitionInit,                CtrlStp_StateMachine_StateInit    },
  { /* CtrlStp_eState_Ref,     */  UTIL_COUNTOF(CtrlStp_asTransitionRef),      CtrlStp_asTransitionRef,                 CtrlStp_StateMachine_StateRef     },
  { /* CtrlStp_eState_Adj,     */  UTIL_COUNTOF(CtrlStp_asTransitionAdj),      CtrlStp_asTransitionAdj,                 CtrlStp_StateMachine_StateAdj     },
  { /* CtrlStp_eState_Fail,    */  UTIL_COUNTOF(CtrlStp_asTransitionFail),     CtrlStp_asTransitionFail,                CtrlStp_StateMachine_StateFail    },
  { /* CtrlStp_eState_STT,     */  UTIL_COUNTOF(CtrlStp_asTransitionSTT),      CtrlStp_asTransitionSTT,                 CtrlStp_StateMachine_StateSTT     }

};



//// State machine table for SLAVE MODE 

STATIC_AL CONST_AL tsCtrlStp_StateMType CtrlStp_atStateMachine_Slave[CTRLSTP_SLAVE_MAX_STATES] =
{ //   state name                     transition count (of tr-table) [ucCount]        transition table [tTransitionCddStp88XX]   state function [tStateFctPtrCddStp88XX]
  { /* CtrlStp_eState_Init,     */ UTIL_COUNTOF(CtrlStp_asTransitionInit_Slave),     CtrlStp_asTransitionInit_Slave,                CtrlStp_StateMachine_StateInit_Slave     },
  { /* CtrlStp_eState_Ref,     */  UTIL_COUNTOF(CtrlStp_asTransitionRef_Slave),      CtrlStp_asTransitionRef_Slave,                 CtrlStp_StateMachine_StateRef            },
  { /* CtrlStp_eState_Adj,     */  UTIL_COUNTOF(CtrlStp_asTransitionAdj_Slave),      CtrlStp_asTransitionAdj_Slave,                 CtrlStp_StateMachine_StateAdj            },
  { /* CtrlStp_eState_Fail,    */  UTIL_COUNTOF(CtrlStp_asTransitionFail_Slave),     CtrlStp_asTransitionFail_Slave,                CtrlStp_StateMachine_StateFail_Slave     }

};

//-----------------------------------------------------------------------------
/// \brief  cyclic function for CtrlStp master
///
/// \descr reads singals , detects mode and submode and writes tg pos
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_Master_Cycle20ms(void)
{
  // exterior takeover status
  static boolean boExtTakeOver = FALSE;
  // get all input signals
  CtrlStp_ReadMasterSignals();  
  CtrlStp_ReadCommonSignals();

  boExtTakeOver = CtrlStp_ReturnboExtTakeOver();

  if (boExtTakeOver == FALSE)
  {
    // detect functionality mode
    CtrlStp_DetectMode();
    CtrlStp_UseMode();
    CtrlStp_UseSubMode();
  }
  else
  {
    // run the routine control
    CtrlStp_DiagRoutineControl();
  }
  
  // calculate halfstep position based on selected source
  CtrlStp_GetTgtPos();    
  // write parameters for validation team
  CtrlStp_WriteValidationParams();
  // writw all output signals
  CtrlStp_WriteMasterSignals();  
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}
  
//-----------------------------------------------------------------------------
/// \brief  cyclic function for CtrlStp Slave mode
///
/// \descr  reads singals , detects mode and submode and writes tg pos
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_Slave_Cycle20ms(void)
{ 
  // exterior takeover status
  static boolean boExtTakeOver = FALSE;

  // get all input signals
  CtrlStp_ReadSlaveSignals();  
  CtrlStp_ReadCommonSignals();

  boExtTakeOver = CtrlStp_ReturnboExtTakeOver();

  if (boExtTakeOver == FALSE)
  {
    // detect mode and submode of functionality
    CtrlStp_DetectSlaveSubMode();
    CtrlStp_UseSubMode();
  }
  else
  {
    // run the routine control
    CtrlStp_DiagRoutineControl();
  }
  
  // calculate halfspep position based on selected source
  CtrlStp_GetTgtPos(); 
  // write parameters for validation team
  CtrlStp_WriteValidationParams();
  // writw all output signals
  CtrlStp_WriteSlaveSignals(); 
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  initialisation function for CtrlStp
///
/// \descr
///
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL void CtrlStp_Init(void)
{

    // detect side and initialize mode
    CtrlStp_eMainMode = CtrlStp_eModeAssembly;
    CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
    CtrlStp_DetectSide();
    if (CtrlStp_ReturnSide() == CtrlStp_eMountedLeft)
    {
      CtrlStp_atStateMachine = CtrlStp_atStateMachine_Master;
    }
    else 
    {
      CtrlStp_atStateMachine = CtrlStp_atStateMachine_Slave;
    }
    // map coding param
    CtrlStp_RteAccess_MapParams();
    CtrlStp_EntryInit();
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_UseMode
///
/// \descr  calls main mode function
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_UseMode(void)
{
  switch (CtrlStp_eMainMode)
  {
  case CtrlStp_eModeAssembly:
  {
    CtrlStp_ModeAssembly();
    break;
  }

  case CtrlStp_eModeCustomer:
  {
    CtrlStp_ModeCustomer();
    break;
  }

  default: break;

  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_UseSubMode
///
/// \descr  calls submode function
///
/// \param   void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_UseSubMode(void)
{
  switch (CtrlStp_eSubMode)
  {

  case CtrlStp_eSubModeUnavailable:
  {
    // reset stepper state if it was previously in available mode
    CtrlStp_ResetStpState();
    // call submode function
    CtrlStp_SubModeUnavailable();
    break;
  }
  case CtrlStp_eSubModeAvailable:
  {
    CtrlStp_StMch();
    CtrlStp_boEntryUnavailable = TRUE; // reset entry flag for unavailable mode
    break;
  }
  case CtrlStp_eSubModeFrozen:
  {
    // reset stepper state if it was previously in available mode
    CtrlStp_ResetStpState();
    // call submode function
    CtrlStp_SubModeFrozen();
    CtrlStp_boEntryUnavailable = TRUE; // reset entry flag for unavailable mode
    break;
  }
  case CtrlStp_eSubModeFactory:
  {
    // reset stepper state if it was previously in available mode
    CtrlStp_ResetStpState();
    // call submode function
    CtrlStp_SubModeFactory();
    CtrlStp_boEntryUnavailable = TRUE; // reset entry flag for unavailable mode
    break;
  }
  case CtrlStp_eSubModeAftersale:
  {
    // reset stepper state if it was previously in available mode
    CtrlStp_ResetStpState();
    // call submode function
    CtrlStp_SubModeAfterSale();
    CtrlStp_boEntryUnavailable = TRUE; // reset entry flag for unavailable mode
    break;
  }

  default: break;
  }

  
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_WriteValidationParams
///
/// \descr  write validation parameters in rte port
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL   void CtrlStp_WriteValidationParams(void)
{
  tsCtrlStp_ValidationParameters sValidationParamsFromCore = CtrlStp_ReturnValidationParams();

  CtrlStp_sValidationParams.eADL_MODE = CtrlStp_eSubMode;
  CtrlStp_sValidationParams.eADL_PHASE = CtrlStp_GetStateValue();

  CtrlStp_sValidationParams.boLvlAdjFunctionalFault_L = sValidationParamsFromCore.boLvlAdjFunctionalFault_L;
  CtrlStp_sValidationParams.boLvlAdjFunctionalFault_R = sValidationParamsFromCore.boLvlAdjFunctionalFault_R;
  CtrlStp_sValidationParams.eLvlAdjHeadlampFault_L    = sValidationParamsFromCore.eLvlAdjHeadlampFault_L;
  CtrlStp_sValidationParams.eLvlAdjHeadlampFault_R    = sValidationParamsFromCore.eLvlAdjHeadlampFault_R;

  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&CtrlStp_sValidationParams);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_VerifyAndProcessRefRun
///
/// \descr  submode behavior function for processing reference run
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL   void CtrlStp_VerifyAndProcessRefRun(void)
{
  boolean boIgnition = CtrlStp_RetVehIgnition();
  boolean boPowerTrain = CtrlStp_RetPowerTrainActive();
  boolean boIsRefDn = CtrlStp_CondRefDnCompl();
  boolean boIsRefUp = CtrlStp_CondRefUpCompl();
  boolean boIsFullyReferenced = ((boIsRefDn != FALSE) && (boIsRefUp != FALSE)) ? TRUE : FALSE;

  // start reference run if powertrain is active and ignition active
  // only when not already referenced
  if ((boPowerTrain != FALSE) && (boIgnition != FALSE) && (boIsFullyReferenced == FALSE))
  {
    CtrlStp_EntryRefDn(); // turn on driver

    if (CtrlStp_boIsRefDone == FALSE)
    {
      // make ref request 
      CtrlStp_SetRefRequest(TRUE);
      CtrlStp_boIsRefDone = TRUE;
    }
    else
    {
      // leave previous value
    }

    CtrlStp_Proccess_Reference();
  }
  else
  {
    // set stp to sleep position
    CtrlStp_SetSignalMode(eStpSrc_SleepPos);
  }
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SubModeAfterSale
///
/// \descr submode function for aftersale functionality
///
/// \param   void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL   void CtrlStp_SubModeAfterSale(void)
{
  boolean boPowerTrainActive  = CtrlStp_RetPowerTrainActive();

  if (boPowerTrainActive == FALSE)
  {
    CtrlStp_SetSubModeError(TRUE);
  }

  if (CtrlStp_CondParamReady() != FALSE)
  {
    CtrlStp_VerifyAndProcessRefRun();
  }
  else
  {
    // nothing to do
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SubModeUnavailable
///
/// \descr  submode function for unavailable mode
///
/// \param    void
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL   void CtrlStp_SubModeUnavailable(void)
{
  // set stp to sleep position
  CtrlStp_SetSignalMode(eStpSrc_SleepPos);
  CtrlStp_SetSubModeError(FALSE);
  CtrlStp_boIsRefDone = FALSE;
  CtrlStp_SetSlaveStopRequest(TRUE);
  CtrlStp_State.boEntry = TRUE;

  if (CtrlStp_boEntryUnavailable != FALSE)
  {
    CtrlStp_EntryOff(); // turn off driver
    CtrlStp_boEntryUnavailable = FALSE;
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SubModeFactory
///
/// \descr  submode function for factory mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_SubModeFactory(void)
{
    boolean boTrainingState     = CtrlStp_ReturnboTrainingState();
    boolean boPowerTrainActive  = CtrlStp_RetPowerTrainActive();
    boolean boIgnition          = CtrlStp_RetVehIgnition();

    if (boIgnition == FALSE)
    {
      if (CtrlStp_State.boEntry == FALSE)
      {
        CtrlStp_EntryOff(); // turn off driver when ignition is off
      }
      else
      {
        // do nothing
      }
      CtrlStp_boIsRefDone   = FALSE;
      CtrlStp_State.boEntry = TRUE;
    }
    else
    {
      // do nothing
    }

    if (CtrlStp_CondParamReady() != FALSE)
    {
      CtrlStp_VerifyAndProcessRefRun();
    }
    else
    {
      // nothing to do
    }
    

    if ((boTrainingState == FALSE) && (boPowerTrainActive == FALSE))
    {
      CtrlStp_SetSubModeError(TRUE);
    }
    else if (boTrainingState != FALSE)
    {
      CtrlStp_SetSubModeError(FALSE);
    }
    else
    {
      // keep current values
    }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_SubModeFrozen
///
/// \descr submode function for frozen state
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_SubModeFrozen(void)
{
  // set stp to sleep position
  CtrlStp_SetSignalMode(eStpSrc_SleepPos);
  CtrlStp_SetSubModeError(TRUE);
  CtrlStp_SetSlaveStopRequest(TRUE);
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ModeAssembly
///
/// \descr  detects submode of assembly mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_ModeAssembly(void)
{

  // check transitions
  if (CtrlStp_Transition_Assembly_To_Frozen() != FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeFrozen;
  }
  else if (CtrlStp_Transition_Assembly_To_Factory() != FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeFactory;
  }
  else if (CtrlStp_Transition_Assembly_To_Unavailable() != FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
  }
  else
  {
    // remain in current submode
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_ModeAssembly
///
/// \descr  detects submode of assembly mode
///
/// \param  - void
///
/// \return   void
//-----------------------------------------------------------------------------
  STATIC_AL  void CtrlStp_ModeCustomer(void)
{

  if (CtrlStp_Transition_Customer_To_Available() != FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeAvailable;
  }
  else if (CtrlStp_Transition_Customer_To_Aftersale() != FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeAftersale;

  }
  else if (CtrlStp_Transition_Customer_To_Unavailable() != FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;

  }
  else
  {
    // remain in current submode
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Init_To_Ref
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Init_To_Ref(void)
{
  boolean boSpeedInvalid;
  uint16 unVehicleSpeed = CtrlStp_RteAccess_ReadSpeed(&boSpeedInvalid);
  uint16 unMaxRefSpeed = Cod_LwrMaxRefSpeed();
  boolean boAdlReferencingRequest  = CtrlStp_RefRequest();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  boolean boPowerTrainActive       = CtrlStp_RetPowerTrainActive();


  boolean boReturn = ((boPowerTrainActive      != FALSE)               &&
                      (boAdlReferencingRequest != FALSE)               &&
                      (eLvlFuncHeadlampFaultL  == CtrlStp_eNo_Failure) &&
                      (eLvlFuncHeadlampFaultR  == CtrlStp_eNo_Failure) &&
                      (unVehicleSpeed          <= unMaxRefSpeed)       &&
                      (CtrlStp_boRefReady      != FALSE)) ? TRUE:FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Init_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_Init_To_Fail(void)
{
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  teCtrlStp_SensorState eSensorError                   = CtrlStp_ReturneSensorError();

  boolean boReturn = ((eLvlFuncHeadlampFaultL != CtrlStp_eNo_Failure) ||
                      (eLvlFuncHeadlampFaultR != CtrlStp_eNo_Failure) ||
                      (eSensorError           == CtrlStp_eHLS_STORED_FAILURE)) ? TRUE : FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Ref_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Ref_To_Adj(void)
{
  static boolean boRefStarted = FALSE;
  boolean boReturn = FALSE;
  boolean boRefComplete = CtrlStp_CondRefUpCompl();
  boolean boRefDnComplete = CtrlStp_CondRefDnCompl();
  boolean boRefInProgress = CtrlStp_CondRefInProgress();
  boolean boRefRequest = CtrlStp_RefRequest();
  
  if (boRefInProgress != FALSE)
  {
    boRefStarted = TRUE;
  }
  else
  {
    // no behavior
  }

  if (boRefStarted != FALSE)
  {
    if ((boRefComplete != FALSE) && (boRefRequest == FALSE) && (boRefDnComplete != FALSE))
    {
      boReturn     = TRUE;
      boRefStarted = FALSE;
    }
    else
    {
      boReturn = FALSE;
    }
  }

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Ref_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Ref_To_Fail(void)
{
  boolean boReturn;

  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  boReturn = ((eLvlFuncHeadlampFaultL != CtrlStp_eNo_Failure) ||
              (eLvlFuncHeadlampFaultR != CtrlStp_eNo_Failure)) ? TRUE : FALSE;

  return boReturn;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Ref_To_STT
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Ref_To_STT(void)
{
  boolean boReturn;

  // to implement checking of finished delay
  boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
  boolean boElectricTransition = FALSE;

  STATIC_UT(uint32, ulTimerStart, 0u);
  STATIC_UT(uint32, ulTimeElapsed, 0u);
  ulTimerStart = (ulTimerStart == 0u) ? TimerStart(ulTimerStart) : ulTimerStart;

  ulTimeElapsed = UTILTIME_MSEC(TimerGetTimeSince(ulTimerStart));

  if (CtrlStp_DetectElecTransition() != FALSE)
  {
    boElectricTransition = TRUE;
  }
  else
  {
    // leave previous value
  }

  boReturn = ((boPowerTrainActive   != FALSE)     &&
              (ulTimeElapsed > UTILTIME_MSEC(Cod_LwrSttDelay())) && //PRQA S 3415 // program architecture and readability
              (boElectricTransition != FALSE))? TRUE:FALSE;


  return boReturn;
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Adj_To_Fail
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Adj_To_Fail(void)
{
  boolean boReturn;
  teCtrlStp_SensorState eSensorError                   = CtrlStp_ReturneSensorError();
  boolean boLvlAdjFuncFault                            = CtrlStp_ReturnboLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  // to check sensor failure
  boReturn = ((eLvlFuncHeadlampFaultL != CtrlStp_eNo_Failure)         ||
              (eLvlFuncHeadlampFaultR != CtrlStp_eNo_Failure)         ||
              (eSensorError           == CtrlStp_eHLS_SENSOR_FAILURE) ||
              (eSensorError           == CtrlStp_eHLS_FROZEN_FAILURE) ||
              (boLvlAdjFuncFault      != FALSE)) ? TRUE:FALSE;

  return boReturn;
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Adj_To_STT
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_Adj_To_STT(void)
  {
    boolean boReturn;
    boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
    //static uint32 ulTimerStart = 0u, ulTimeElapsed = 0u;
    STATIC_UT(uint32, ulTimerStart, 0u);
    STATIC_UT(uint32, ulTimeElapsed, 0u);

    ulTimerStart = (ulTimerStart == 0u) ? TimerStart(ulTimerStart) : ulTimerStart;

    ulTimeElapsed = UTILTIME_MSEC(TimerGetTimeSince(ulTimerStart));


    boolean boElectricTransition = FALSE;

    if (CtrlStp_DetectElecTransition() != FALSE)
    {
      boElectricTransition = TRUE;
    }
    else
    {
      // leave previous value
    }
    boReturn = ((boPowerTrainActive != FALSE) &&
               (ulTimeElapsed > UTILTIME_MSEC(Cod_LwrSttDelay())) && //PRQA S 3415 // program architecture and readability
               (boElectricTransition != FALSE)) ? TRUE : FALSE;


    return boReturn;

  }
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Fail_To_Ref
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Fail_To_Ref(void)
{
  boolean boReturn;
  boolean boSpeedInvalid;


  uint16 unVehicleSpeed                                = CtrlStp_RteAccess_ReadSpeed(&boSpeedInvalid);
  uint16 unMaxRefSpeed                                 = Cod_LwrMaxRefSpeed();
  boolean boPowerTrainActive                           = CtrlStp_RetPowerTrainActive();
  boolean boRefRequest                                 = CtrlStp_RefRequest();
  teCtrlStp_SensorState eSensorError                   = CtrlStp_ReturneSensorError();
  boolean boLvlAdjFuncFault                            = CtrlStp_ReturnboLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
                             
                             
  boolean boFailure          = ((eLvlFuncHeadlampFaultL == CtrlStp_eNo_Failure) &&
                               (eLvlFuncHeadlampFaultR == CtrlStp_eNo_Failure)  &&
                               (eSensorError       == CtrlStp_eHLS_NO_FAILURE)  &&
                               (boLvlAdjFuncFault == FALSE)) ? FALSE:TRUE ;
                             
  boReturn                  = ((boPowerTrainActive != FALSE)                           &&
                               (boFailure == FALSE)                                    &&
                               (boRefRequest != FALSE)                                 &&
                               ( unVehicleSpeed <= unMaxRefSpeed)) ? TRUE:FALSE;

  return boReturn;
  //PRQA S 5324 1 // STCAL exceeded and can't be simplified for this requirement
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Fail_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Fail_To_Adj(void)
{
  boolean boReturn;

  boolean boAdlReferencingRequest                      = CtrlStp_RefRequest();
  boolean boPowerTrainActive                           = CtrlStp_RetPowerTrainActive();
  boolean boRefComplete                                = CtrlStp_CondRefUpCompl();
  teCtrlStp_SensorState eSensorError                   = CtrlStp_ReturneSensorError();
  boolean boLvlAdjFuncFault                            = CtrlStp_ReturnboLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  boolean boFailure = ((eLvlFuncHeadlampFaultL == CtrlStp_eNo_Failure) &&
                       (eLvlFuncHeadlampFaultR == CtrlStp_eNo_Failure) &&
                       (eSensorError       == CtrlStp_eHLS_NO_FAILURE) &&
                       (boLvlAdjFuncFault      == FALSE)) ? FALSE:TRUE;

  boReturn = ((boAdlReferencingRequest == FALSE) &&
                         (boPowerTrainActive != FALSE) &&
                         (boRefComplete      != FALSE) &&
                         (boFailure == FALSE)) ? TRUE:FALSE;


  return boReturn;
  //PRQA S 5324 1 // STCAL exceeded and can't be simplified for this requirement
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_STT_To_Ref
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_STT_To_Ref(void)
{
  boolean boReturn;

  boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
  boolean boAdlReferencingRequest = CtrlStp_RefRequest();
  boolean boElectricTransition = FALSE;

  if (CtrlStp_DetectElecTransitionSttToRef() != FALSE)
  {
    boElectricTransition = TRUE;
  }
  else
  {
    // leave previous value
  }

  boReturn = ((boAdlReferencingRequest != FALSE) &&
                         (boPowerTrainActive != FALSE)      &&
                         (boElectricTransition != FALSE)) ? TRUE:FALSE;

  return boReturn;
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_STT_To_Adj
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_STT_To_Adj(void)
{
  boolean boReturn;

  boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
  boolean boAdlReferencingRequest = CtrlStp_RefRequest();

  boolean boElectricTransition = FALSE;

  if (CtrlStp_DetectElecTransitionSttToAdj() != FALSE)
  {
    boElectricTransition = TRUE;
  }
  else
  {
    // leave previous value
  }

  if ((boAdlReferencingRequest == FALSE) && (boPowerTrainActive != FALSE) && (boElectricTransition != FALSE))
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
/// \brief  CtrlStp_Transition_Assembly_To_Frozen
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Assembly_To_Frozen(void)
{
  boolean boReturn;
  
  uint8 ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();

  if ((ucModeConfigVhl == (uint8)eModeConfigVehicle_Montage)    || 
    (ucModeConfigVhl == (uint8)eModeConfigVehicle_Invalid2)     ||
    ((ucModeConfigVhl == (uint8)eModeConfigVehicle_AfterMarket) &&
     (CtrlStp_ReturnboTrainingState() != FALSE))                || //PRQA S 3415 1 // program architecture and readability
    (ucModeConfigVhl == (uint8)eModeConfigVehicle_Controle) )
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
/// \brief  CtrlStp_Transition_Assembly_To_Factory
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_Assembly_To_Factory(void)
{
  boolean boReturn;

  uint8 ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  boolean boTrainingState = CtrlStp_ReturnboTrainingState();

  if (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine) ||
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
/// \brief  CtrlStp_Transition_Assembly_To_Unavailable
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_Assembly_To_Unavailable(void)
{
  boolean boReturn;

  uint8 ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  boolean boTrainingState = CtrlStp_ReturnboTrainingState();
  boolean boIgnition = CtrlStp_RetVehIgnition();

  if ((ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine) &&
      (boTrainingState != FALSE) &&
      (boIgnition == FALSE))
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
/// \brief  CtrlStp_Transition_Customer_To_Unavailable
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL   boolean CtrlStp_Transition_Customer_To_Unavailable(void)
{
  boolean boReturn;
  boolean boIgnition = CtrlStp_RetVehIgnition();

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
/// \brief  CtrlStp_Transition_Customer_To_Available
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_Customer_To_Available(void)
{
  boolean boReturn;

  boolean boIgnition = CtrlStp_RetVehIgnition();

  if  ((CtrlStp_ReturnboTrainingState() != FALSE)
       && (boIgnition != FALSE))
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
/// \brief  CtrlStp_Transition_Customer_To_Aftersale
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
  STATIC_AL  boolean CtrlStp_Transition_Customer_To_Aftersale(void)
{
  boolean boReturn;

  boolean boIgnition = CtrlStp_RetVehIgnition();

  if (    (CtrlStp_ReturnboTrainingState() == FALSE)
       && (boIgnition != FALSE))
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
//  \func     CtrlStp_StMch
//
//  \brief    state machine for CtrlStepper. Calls state function and goes through each state transition check
//
//  \param    void
//
//  \return   void
// ---------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_StMch(void)
  {
    uint8 ucIx;

    // call current state
    CtrlStp_atStateMachine[(uint8)CtrlStp_State.eMain].pStateFct();

    // go through all transitions for current state
    for (ucIx = 0u; ucIx < CtrlStp_atStateMachine[(uint8)CtrlStp_State.eMain].ucCount; ucIx++)
    {
      if (CtrlStp_atStateMachine[(uint8)CtrlStp_State.eMain].pTransition[ucIx].ptTransitionFct() != FALSE)
      {
        // change current state 
        CtrlStp_State.eMain = CtrlStp_atStateMachine[(uint8)CtrlStp_State.eMain].pTransition[ucIx].eNewState;
        // mark new state as entered
        CtrlStp_State.boEntry = TRUE;
        break;
      }
      else
      {
        // don t change state
      }
    }
  }


  //-----------------------------------------------------------------------------
/// \brief  CtrlStp_StateMachine_StateFail
///
/// \descr  State Machine: behavior in case of state Err
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_StateMachine_StateFail(void)
  {
    if (CtrlStp_State.boEntry != FALSE)
    {
      CtrlStp_StartDiagLvlTimer = TRUE;
      CtrlStp_State.boEntry = FALSE;
    }
    else
    {
      // handle fail state behavior depending on the fault status
      CtrlStp_HandleFailState();
    }
  }

  //-----------------------------------------------------------------------------
/// \brief  CtrlStp_HandleFailState
///
/// \descr  Handle fail state behavior
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_HandleFailState(void)
  {
    CONST_AL boolean boLeftSteploss = CtrlStp_ReturnSteplossErr();
    CONST_AL boolean boRightSteploss = CtrlStp_ReturnRightSteplossErr();

    teCtrlStp_FailStateHandling eFailStateLeft  = CtrlStp_eContinue;
    teCtrlStp_FailStateHandling eFailStateRight = CtrlStp_eContinue;
    teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultL = CtrlStp_eNo_Failure;
    teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_eNo_Failure;
    boolean boPowertrainActive         = CtrlStp_RetPowerTrainActive();
    boolean boLvlAdjFuncFault          = CtrlStp_ReturnboLvlAdjFuncFault();
    teCtrlStp_SensorState eSensorError = CtrlStp_ReturneSensorError();
    boolean boStepLossError = FALSE;

    eLvlFuncHeadlampFaultL = CtrlStp_ReturneLvlAdjHeadlampFault_L();
    eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

    boStepLossError = ((boLeftSteploss != FALSE) ||
                       (boRightSteploss != FALSE)) ? TRUE : FALSE;

    if (boPowertrainActive == FALSE)
    {
      eFailStateLeft  = CtrlStp_eFreeze;
      eFailStateRight = CtrlStp_eFreeze;
    }
    else if (eLvlFuncHeadlampFaultL == CtrlStp_eFrozen_Failure)
    {
      eFailStateLeft  = CtrlStp_eFreeze_IgnitionNeeded;
      eFailStateRight = CtrlStp_eContinue;
    }
    else if (eLvlFuncHeadlampFaultL == CtrlStp_eTransition_Failure)
    {
      eFailStateLeft  = CtrlStp_eFreeze;
      eFailStateRight = CtrlStp_eContinue;
    }
    else if (boLvlAdjFuncFault != FALSE)
    {
      eFailStateLeft  = CtrlStp_eSafety_IgnitionNeeded;
      eFailStateRight = CtrlStp_eSafety_IgnitionNeeded;
    }
    else if (eLvlFuncHeadlampFaultR == CtrlStp_eFrozen_Failure)
    {
      eFailStateLeft  = CtrlStp_eContinue;
      eFailStateRight = CtrlStp_eContinue;
    }
    else if (eLvlFuncHeadlampFaultR == CtrlStp_eTransition_Failure)
    {
      eFailStateLeft  = CtrlStp_eContinue;
      eFailStateRight = CtrlStp_eContinue;
    }
    else if (eSensorError != CtrlStp_eHLS_NO_FAILURE)
    {
      eFailStateLeft  = CtrlStp_eSafety;
      eFailStateRight = CtrlStp_eSafety;
    }
    else
    {
      // keep previous values
    }

    CtrlStp_HandleDiagLvl(boStepLossError);
    CtrlStp_HandleFailStateBehavior(eFailStateLeft, eFailStateRight);
    //PRQA S 5336 2 // STMIF is exceeded due to program architecture and readability
    //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
  }

//-----------------------------------------------------------------------------
/// \brief CtrlStp_HandleDiagLvl
///
/// \descr Function used to delay the appearance of the HMI (DIAG_LVL)
///
/// \param  boStepLossErr
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
  STATIC_AL void CtrlStp_HandleDiagLvl(boolean boStepLossErr)
  {
    STATIC_UT(uint32, ulDelayTimer, 0u);
    boolean boIsError = FALSE;

    //start the delay timer
    if (CtrlStp_StartDiagLvlTimer != FALSE)
    {
      ulDelayTimer = TimerGetTick();
      CtrlStp_StartDiagLvlTimer = FALSE;
    }
    else if (TimerGetTimeSince(ulDelayTimer) >= UTILTIME_MSEC(Cod_LevellingStepperFailureReportTime()))
    {
      //check for steploss error, if not present set DIAG_LVL
      boIsError = (boStepLossErr != FALSE) ? FALSE : TRUE;
    }
    else
    {
      //go on timer not done
    }

    CtrlStp_SetSubModeError(boIsError);

  }

  //-----------------------------------------------------------------------------
/// \brief  CtrlStp_HandleFailStateBehavior
///
/// \descr  Handle Fail state behavior for Master and Slave control
///
/// \param  teCtrlStp_FailStateHandling eLeftState - state for Master
/// \param  teCtrlStp_FailStateHandling eRightState - state for Slave
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_HandleFailStateBehavior(teCtrlStp_FailStateHandling eLeftState, teCtrlStp_FailStateHandling eRightState)
  {
    switch (eLeftState)
    {
      case CtrlStp_eFreeze:
      {
        CtrlStp_SetSignalMode(eStpSrc_SleepPos);
        break;
      }
      case CtrlStp_eFreeze_IgnitionNeeded:
      {
        CtrlStp_SetSignalMode(eStpSrc_SleepPos);
        CtrlStp_EntryErr();
        break;
      }
      case CtrlStp_eSafety:
      {
        CtrlStp_SetSignalMode(eStpSrc_SafetyPos);
        break;
      }
      case CtrlStp_eSafety_IgnitionNeeded:
      {
        CtrlStp_SetSignalMode(eStpSrc_SafetyPos);
        if (CtrlStp_isSafetyPosReached() != FALSE)
        {
          CtrlStp_EntryErr(); // turn off driver
        }
        else
        {
          // do nothing
        }
        break;
      }
      case CtrlStp_eContinue:
      {
        CtrlStp_SetSignalMode(eStpSrc_NormalPos);
        break;
      }
      default:
        break;
    }

    switch (eRightState)
    {
    case CtrlStp_eFreeze:
    {
      CtrlStp_SetSlaveStopRequest(TRUE);
      CtrlStp_SetSlaveSafetyPosition(FALSE);
      break;
    }
    case CtrlStp_eSafety:
    {
      CtrlStp_SetSlaveStopRequest(FALSE);
      CtrlStp_SetSlaveSafetyPosition(TRUE);
      break;
    }
    case CtrlStp_eSafety_IgnitionNeeded:
    {
      CtrlStp_SetSlaveStopRequest(FALSE);
      CtrlStp_SetSlaveSafetyPosition(TRUE);
      CtrlStp_SetIgnitionNeeded(TRUE);
      break;
    }
    case CtrlStp_eContinue:
    {
      CtrlStp_SetSlaveStopRequest(FALSE);
      CtrlStp_SetSlaveSafetyPosition(FALSE);
      break;
    }
    default:
      break;
    }
  }


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_StateMachine_StateSTT
///
/// \descr  State Machine: behavior in case of stt state
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_StateMachine_StateSTT(void)
{
  CtrlStp_SetSignalMode(eStpSrc_SleepPos);
  CtrlStp_SetSlaveStopRequest(TRUE);
}


//-----------------------------------------------------------------------------
/// \brief CtrlStp_StateMachine_StateInit
///
/// \descr  State Machine: behavior in case of state Init
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_StateMachine_StateInit(void)
  {
   boolean boCondIsReady      = FALSE; // if driver is ready

   // make ref request for slave when we enter init state
   CtrlStp_SetSlaveRefRequest(TRUE);

   if (CtrlStp_State.boEntry != FALSE)
   {
     CtrlStp_SetRefRequest(FALSE);

     CtrlStp_SetSlaveStopRequest(TRUE);

     CtrlStp_EntryInit();
     
     CtrlStp_boRefReady = FALSE;
     
     CtrlStp_State.boEntry = FALSE;
     
     CtrlStp_SetSubModeError(FALSE);
   }
   else
   {
     boCondIsReady = CtrlStp_CondIsReady();

     if ((CtrlStp_CondParamReady() != FALSE) && (boCondIsReady != FALSE))
     {
       // set errors to false
       CtrlStp_SetSignalMode(eStpSrc_SleepPos);
       CtrlStp_boRefReady = TRUE;
       CtrlStp_EntryRefDn(); // turn on driver
       CtrlStp_SetRefRequest(TRUE);
     }
   }
   //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
  }

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_StateMachine_StateAdj
///
/// \descr  State Machine: behavior in case of adjustment state
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL  void CtrlStp_StateMachine_StateAdj(void)
{
  boolean boRefRequest = CtrlStp_RefRequest();


  if (CtrlStp_State.boEntry != FALSE)
  {
    CtrlStp_EntryNorm();
    CtrlStp_State.boEntry = FALSE;
    CtrlStp_SetRefRequest(FALSE);

  }
  else
  {

    // do normal behavior
    CtrlStp_SetSignalMode(eStpSrc_NormalPos);
    CtrlStp_DoNorm();
  }
  CtrlStp_SetSlaveStopRequest(FALSE);
  CtrlStp_SetSlaveSafetyPosition(FALSE);
  CtrlStp_SetSubModeError(FALSE); // set DIAG_LVL to OK
  //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_StateMachine_StateRef
///
/// \descr  State Machine: behavior in case of state Ref
///         (Reference run including initializing)
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL  void CtrlStp_StateMachine_StateRef(void)
{
    CtrlStp_Proccess_Reference();
}

  //-----------------------------------------------------------------------------
/// \brief  CtrlStp_Proccess_Reference
///
/// \descr  handles refference request 
///         
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL  void CtrlStp_Proccess_Reference(void)
  {
    boolean boRefRequest;
    boolean boCondIsReady;
    NM_ModeType NMMode;

    // Get life phases from the NM
    (void)NM_GetMode(&NMMode);

    if (CtrlStp_State.boEntry != FALSE) // handle the initial phase of the state
    {

      if (CtrlStp_CondIsOn() == FALSE)
      {
        //turn on driver
        CtrlStp_EntryRefDn();
      }
      
      if (CtrlStp_CondIsReady() != FALSE)  // hardware is ready
      {
        CtrlStp_SetSlaveRefRequest(TRUE);
        if (CtrlStp_ReturnboTrainingState() == FALSE)
        {
          CtrlStp_SetSignalMode(eStpSrc_ZeroPos);
        }
        else
        {
          CtrlStp_SetSignalMode(eStpSrc_NormalPos);
        }
        CtrlStp_State.boEntry = FALSE;
      }
      else
      {
        // not ready
      }
    }
    else  // we have passed sub state "entry"
    {
      boRefRequest = CtrlStp_RefRequest();
      boCondIsReady = CtrlStp_CondIsReady();

      if ((boRefRequest != FALSE) && (boCondIsReady != FALSE) && (NMMode != LIMP_HOME_MODE)) // use ref condition delay if needed
      {

        CtrlStp_StartRef();
        CtrlStp_SetRefRequest(FALSE);
      }
      else
      {
        // nothing to do
      }

    }
    //PRQA S 5324 1 // STCAL is exceeded due to program architecture and readability
  }

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectMode
///
/// \descr  detects main mode of stepper control
///
/// \param  -void
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_DetectMode(void)
{
  uint8 ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  boolean boTrainingState = CtrlStp_ReturnboTrainingState();

  if ((ucModeConfigVhl == (uint8)eModeConfigVehicle_Client)       ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Showroom)     ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_Stockage)     ||
    (((ucModeConfigVhl == (uint8)eModeConfigVehicle_Usine)        ||
      (ucModeConfigVhl == (uint8)eModeConfigVehicle_AfterMarket)) &&
      (boTrainingState != FALSE)))
  {
    CtrlStp_eMainMode = CtrlStp_eModeCustomer;
  }
  else
  {
    CtrlStp_eMainMode = CtrlStp_eModeAssembly;
  }
}
//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectMode
///
/// \descr  checks if stepper was previously activated and it resets the state if so
///
/// \param  -void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL  void CtrlStp_ResetStpState(void)
{
  static boolean boFirstEntry = TRUE;

  if (boFirstEntry != FALSE)
  {
    CtrlStp_SetRefRequest(FALSE);
    CtrlStp_SetSlaveRefRequest(FALSE);
    boFirstEntry = FALSE;
  }
  else
  {
    // keep current values
  }

  if (CtrlStp_State.eMain != CtrlStp_eState_Init)  // check if command is called too early
  {
    CtrlStp_State.eMain = CtrlStp_eState_Init;
    CtrlStp_State.boEntry = TRUE;
    boFirstEntry = TRUE;
  }
  else
  {
    // stepper is already in init state
  }
}


//-----------------------------------------------------------------------------
/// \brief  riCtrlStpInit
///
/// \descr   init function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCtrlStpInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCtrlStpInit)
#endif

    CtrlStp_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCtrlStpInit)
#endif
}
//-----------------------------------------------------------------------------
/// \brief  rpCtrlStp_Cycle
///
/// \descr   20ms cycle function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpCtrlStp_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCtrlStp_Cycle)
#endif

  if (CtrlStp_ReturnSide() == CtrlStp_eMountedRight)
  {
    CtrlStp_Slave_Cycle20ms();
  }
  else
  {
    CtrlStp_Master_Cycle20ms();
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCtrlStp_Cycle)
#endif
}

/////////////////////////////////////////
/////// SLAVE MODE FUNCTIONS
/////////////////////////////////////////


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Adj_To_Fail_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Adj_To_Fail_Slave(void)
{
  boolean boLvlAdjFuncFault                            = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  boolean boReturn = ((eLvlFuncHeadlampFaultR != CtrlStp_eNo_Failure) || (boLvlAdjFuncFault != FALSE)) ? TRUE : FALSE;

  return boReturn;

}



//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Adj_To_Ref_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Adj_To_Ref_Slave(void)
{
  boolean boAdlReferencingRequest                      = CtrlStp_RefRequest();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  boolean boPowerTrainActive                           = CtrlStp_RetPowerTrainActive();

  boolean boReturn = ( (boPowerTrainActive != FALSE) &&
    (boAdlReferencingRequest != FALSE) &&
    (eLvlFuncHeadlampFaultR  == CtrlStp_eNo_Failure)) ? TRUE : FALSE;

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Fail_To_Adj_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Fail_To_Adj_Slave(void)
{
  boolean boRefRequest = CtrlStp_RefRequest();
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  boolean boReturn = (
    (eLvlFuncHeadlampFaultR == CtrlStp_eNo_Failure) &&
    (boRefRequest           == FALSE)               &&
    (boLvlAdjFuncFault      == FALSE)) ? TRUE : FALSE;

    return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Fail_To_Ref_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Fail_To_Ref_Slave(void)
{

  boolean boRefRequest                                 = CtrlStp_RefRequest();
  boolean boLvlAdjFuncFault                            = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  boolean boReturn = (
                            (eLvlFuncHeadlampFaultR == CtrlStp_eNo_Failure) &&
                            (boLvlAdjFuncFault      == FALSE)               &&
                            (boRefRequest != FALSE))?TRUE:FALSE;


    return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Ref_To_Fail_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Ref_To_Fail_Slave(void)
{
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();

  boolean boReturn = (eLvlFuncHeadlampFaultR != CtrlStp_eNo_Failure) ? TRUE : FALSE;

  return boReturn;
}



//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Ref_To_Adj_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Ref_To_Adj_Slave(void)
{
  static boolean boRefStarted = FALSE;
  boolean boReturn = FALSE;
  boolean boRefComplete = CtrlStp_CondRefDnCompl();
  boolean boRefUpComplete = CtrlStp_CondRefUpCompl();
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  boolean boRefRequest = CtrlStp_RefRequest();
  boolean boRefInProgress = CtrlStp_CondRefInProgress();

  if (boRefInProgress != FALSE)
  {
    boRefStarted = TRUE;
  }
  else
  {
    // no behavior
  }

  if (boRefStarted != FALSE)
  {
    if ((boRefComplete != FALSE) && (boRefRequest == FALSE) && (boRefUpComplete != FALSE) && (boLvlAdjFuncFault == FALSE))
    {
      boReturn     = TRUE;
      boRefStarted = FALSE;
    }
    else
    {
      boReturn = FALSE;
    }
  }

  return boReturn;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_Transition_Init_To_Adj_Slave
///
/// \descr  transition check function
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlStp_Transition_Init_To_Adj_Slave(void)
{
  boolean boReturn  = FALSE;
  boolean boIsDrvOn = CtrlStp_CondIsOn();

  if (boIsDrvOn != FALSE)
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
/// \brief  CtrlStp_GetStateValue
///
/// \descr  return stepper state
///
/// \param  void
///
/// \return teCtrlStp_StatMain
//-----------------------------------------------------------------------------
teCtrlStp_StatMain CtrlStp_GetStateValue(void)
{
  return CtrlStp_State.eMain;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_DetectSlaveSubMode
///
/// \descr  detect submode of slave mode
///
/// \param  -
///
/// \return   void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlStp_DetectSlaveSubMode(void)
{
  boolean boIgnition = CtrlStp_RetVehIgnition();


  if (boIgnition == FALSE)
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
  }
  else
  {
    CtrlStp_eSubMode = CtrlStp_eSubModeAvailable;
  }
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_StateMachine_StateInit_Slave
///
/// \descr  State Machine: behavior in case of state Init for Slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_StateMachine_StateInit_Slave(void)
  {
    boolean boIsParamReady = CtrlStp_CondParamReady();

    CtrlStp_SetSignalMode(eStpSrc_SleepPos);

    if (boIsParamReady != FALSE)
    {
      CtrlStp_EntryRefDn(); // turn on driver
    }
    else
    {
      // leave driver off
    }
  }

    //-----------------------------------------------------------------------------
/// \brief  CtrlStp_StateMachine_StateFail_Slave
///
/// \descr  State Machine: behavior in case of state Err for Slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_StateMachine_StateFail_Slave(void)
  {
    // first check if we are in the initial phase of the state
    if (CtrlStp_State.boEntry != FALSE)
    {
      CtrlStp_State.boEntry = FALSE;
    }
    else  // we have passed sub state "entry"
    {
      CtrlStp_HandleFailState_Slave();
    }
  }

  //-----------------------------------------------------------------------------
/// \brief  CtrlStp_HandleFailState_Slave
///
/// \descr  Handle fail state behavior for Slave
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_HandleFailState_Slave(void)
  {
    teCtrlStp_FailStateHandling eFailState = CtrlStp_eContinue;
    teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
    boolean boPowertrainActive = CtrlStp_RetPowerTrainActive();
    boolean boLvlAdjFuncFault  = CtrlStp_ReturnboSlaveLvlAdjFuncFault();

    eLvlFuncHeadlampFault = CtrlStp_ReturneLvlAdjHeadlampFault_R();

    if ((boPowertrainActive == FALSE) && (boLvlAdjFuncFault != FALSE))
    {
      eFailState  = CtrlStp_eFreeze;
    }
    else if ((boPowertrainActive != FALSE) && (boLvlAdjFuncFault != FALSE))
    {
      eFailState  = CtrlStp_eSafety_IgnitionNeeded;
    }
    else if (eLvlFuncHeadlampFault == CtrlStp_eTransition_Failure)
    {
      eFailState  = CtrlStp_eFreeze;
    }
    else if (eLvlFuncHeadlampFault == CtrlStp_eFrozen_Failure)
    {
      eFailState  = CtrlStp_eFreeze_IgnitionNeeded;
    }
    else
    {
      // keep previous values
    }

    CtrlStp_HandleFailStateBehavior_Slave(eFailState);
  }

    //-----------------------------------------------------------------------------
/// \brief  CtrlStp_HandleFailStateBehavior_Slave
///
/// \descr  Handle Fail state behavior for Slave control
///
/// \param  teCtrlStp_FailStateHandling eRightState - state for Slave
///
/// \return void
//-----------------------------------------------------------------------------
  STATIC_AL   void CtrlStp_HandleFailStateBehavior_Slave(teCtrlStp_FailStateHandling eRightState)
  {
    switch (eRightState)
    {
    case CtrlStp_eFreeze:
    {
      CtrlStp_SetSignalMode(eStpSrc_SleepPos);
      break;
    }
    case CtrlStp_eSafety:
    {
      CtrlStp_SetSignalMode(eStpSrc_SafetyPos);
      break;
    }
    case CtrlStp_eSafety_IgnitionNeeded:
    {
      CtrlStp_SetSignalMode(eStpSrc_SafetyPos);
      if (CtrlStp_isSafetyPosReached() != FALSE)
      {
        CtrlStp_EntryErr(); // turn off driver
      }
      else
      {
        // do nothing
      }
      break;
    }
    case CtrlStp_eFreeze_IgnitionNeeded:
    {
      CtrlStp_SetSignalMode(eStpSrc_SleepPos);
      CtrlStp_EntryErr();
      break;
    }
    default:
      break;
    }
  }



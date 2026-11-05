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
/// \file  FctRTgt.c
///
/// \brief Defines the target path for Function Router (FctR).
///        Map CAN signals to (an internal representation of) light functions
///        Resolve priorities for light functions
///        Compute target values for logical lamps
///        Calculate ramps for logical lamps
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "FctR.h"
#include "FctR_TgtPrep.h"
#include "FctR_RteAccess.h"
#include "FctR_Cfg.h"
#include "FctR_Tgt.h"
#include "FctR_Data.h"
#include "FctR_Types.h"

//=============================================================================
// defines
//=============================================================================

// Stuff for module test on Win32
#ifdef WIN32
// warning C4244: '=' : conversion from 'uint32' to 'boolean', possible loss of data
#pragma warning(disable: 4244)
#endif

// Cycle time of runable FctR_TgtCycle0 [ms]
#define FCTR_CYCLE_FCTR_TGTCYCLE0      20u
/// Resolution for values of actual logical lamps
/// <P>
/// Longest ramp: 10 min = 600 s = 6000 [100 ms] <BR>
/// t : Time for 100% [100 ms] (inverse of speed)<BR>
/// tc: Cycle time [20 ms]                       <BR>
/// i:  increment                                <BR>
/// With t = 6000 (10 min)                       <BR>
/// i = tc * 100% / (100 * t)                    <BR>
///    = 20 ms * 100% / (100 * 6000) ms          <BR>
///    = 0.0033...%                              <BR>
/// => Resolution min. 10000 such that 10000*i = 33<BR>
/// Choose power of 2: 16384                       <BR>
/// i = 16384 * tc * 100% / (100*t)                <BR>
///   = 16384 * tc * 100% / (100*6000)             <BR>
///   = 54.61333...%                               <BR>
/// How to compute the smallest resolution R necessary for a given maximal error e [s]:<BR>
/// With div(R*i) = R*i - eps    where eps < 1:                     <BR>
/// error  = 100%*R*tc / (div(R*i)*1000) - 100%*R*tc / (R*i*1000)   <BR>
///       <= 100%*R*tc / (R*i*1000-1000) - 100%*R*tc / (R*i*1000)   <BR>
///        = R*tc / (10*(R*R * i*i - R*i))                          <BR>
///       !< e                                                      <BR>
/// <=>   R > (10*i*e + tc) / (10 * i*i * e)                        <BR>
/// With e = 1, i = 20/6000, tc = 20: R > 180300.                   <BR>
/// With R = 16384, i = 20/6000, tc = 20: error = 11.1912...s       <BR>
#define FCTR_RES_ACTLMP              16384u
// Used to scale from [%] to [0.1%] for RTE representation
#define FCTR_RTE_UNIT_SCALER  10u
#define FCTR_FREQUENCY_RESOLUTION_FACTOR      1000u  // value in order to get the frequency value
#define FCTR_DUTY_DIVIDER                        2u  // value for getting 50% duty 
#define FCTR_AIM_BLINK_FREQ                      3u  // frequency in Hz for blinking 
#define FCTR_AIM_BLINK_FREQ_TOLERANCE            10u  // blinking time calculation tolerance 
#define FCTR_AIM_COUNTER                         10u  // counter for nb of blinks (ON/OFF) 
#define FCTR_RAMP_RESOLUTION                     20u  //Dim up / Dim down resolution factor
 
#define FCTR_TIMEOUT_NOT_OCCURED 0x00U //no timeout
#define FCTR_IS_TIMEOUT 0x01U //timeout

#define FCTR_INVALID_TIMER_CONFIG 0xFFU //invalid configuration for Timers

#define FCTR_LB_FAULT_DETECTION 0
#define FCTR_SBL_FAULT_DETECTION 1
#define FCTR_HB_FAULT_DETECTION 2
#define FCTR_TI_BLINKING_DETECTION 3
#define FCTR_POS_FAULT_DETECTION 4
#define FCTR_DRL_FAULT_DETECTION 5
#define FCTR_NUMBER_OF_TIMERS (FCTR_DRL_FAULT_DETECTION + 1) //number of timers
         
#define FCTR_LB_FAULT_DETECTION_TIME_MS 200UL //(fault detection) //???? for MATRIX recovery this time is ok???
#define FCTR_SBL_FAULT_DETECTION_TIME_MS 200UL //(fault detection)
#define FCTR_HB_FAULT_DETECTION_TIME_MS 200UL //(fault detection)
#define FCTR_TI_BLINKING_DETECTION_TIME_MS FCTR_DELAY_TI_NOT_REQUESTED
#define FCTR_POS_FAULT_DETECTION_TIME_MS 200UL //(fault detection)
#define FCTR_DRL_FAULT_DETECTION_TIME_MS 200UL //(fault detection)

#define FCTR_ERASE_LB_FCTS          0xFFFFFE00U
#define FCTR_ERASE_CL_SBL_FCTS      0x6000000U
#define FCTR_SET_SBL_FCTS           0x2000000U
#define FCTR_SET_CL_FCTS            0x4000000U
#define FCTR_KEEP_LB_FCTS           0x1FFU
#define FCTR_SET_FAILURE_LB_HB_FCTS 221695UL

//=============================================================================
// data types
//=============================================================================

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
  TIMER ulTime; //timer value
  sint8 cSelectTimer; //timer selection for different light function
  //store previous state of lightfunction
  boolean boPrvCmd;
}tsDiagFeedback_Cfg;

//=============================================================================
// function prototypes
//=============================================================================
STATIC_AL void    FctR_ActLgt_Update                  (void);
STATIC_AL void    FctR_TgtLgt_Prio                    (void);
STATIC_AL void    FctR_TgtLgt_Sustain                 (void);
STATIC_AL void    FctR_TgtLgt_Output                  (void);
STATIC_AL void    FctR_Tgt_GetActLedState             (void);
STATIC_AL void    FctR_Tgt_CheckLightFunctions_State  (void);
STATIC_AL void    FctR_Tgt_HandleLgtFctFailure        (void);
STATIC_AL void    FctR_Tgt_LgtFctFailureReaction      (void);
STATIC_AL void    FctR_ProccessAimingMode             (void);
STATIC_AL boolean FctR_Get_UnderVoltageStatusDebounced(void);
STATIC_AL boolean FctR_Get_OverVoltageStatusDebounced (void);
STATIC_AL uint8 FctR_CtrlDelayStatus(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel);
STATIC_AL boolean FctR_HandleDelayStatus(tsFctR_TimerCfg *sTimersCfg, const sint8 scTimerSel);
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  STATIC_AL void    FctR_TgtDbl_Output                  (void);
  STATIC_AL boolean FctR_CheckSblCl_LightStatus(void);
#endif

STATIC_AL void    FctR_TgtLgt_StorePrep               (void);
STATIC_AL void    FctR_TgtLgt_Prio_LgtFct             (void);
STATIC_AL void    FctR_TgtLgt_Prio_LgtFct_FinalizePrio(void);

STATIC_AL void    FctR_TgtLgt_Sustain_LogLamp    (tAppLogLamp ucLogLamp);
STATIC_AL void    FctR_TgtLgt_Prio_LgtFctB_LogLmp(tAppLightFunction ucLgtFct);

STATIC_AL boolean FctR_GetActiveTgtLgtReq(tAppLightFunction ulLgtFct);
STATIC_AL uint16  FctR_Percent_To_RteUnit(uint8 ucPercentVal);

STATIC_AL uint8   FctR_GetPriority         (tAppLightFunction LgtFct, tAppLogLamp LogLmp);
STATIC_AL uint8   FctR_GetIntensity        (tAppLightFunction LgtFct, tAppLogLamp LogLmp);
STATIC_AL uint16  FctR_TgtLgt_GetLmpSpdInvB(tAppLightFunction LgtFct, tAppLogLamp LogLamp);
STATIC_AL uint16  FctR_TgtLgt_GetLmpSpdInv (tAppLightFunction LgtFct, tAppLogLamp LogLamp);

STATIC_AL uint16  FctR_TgtLgt_GetLmpSpdInvFromRampType(uint8 ucRampType, uint16 unTime, tAppLogLamp LogLamp);

STATIC_AL void FctR_CalculateUsageLogLmpTable(void);

STATIC_AL tsFctR_TgtLgtReq FctR_SetLgtReq_VoltCond(tsFctR_TgtLgtReq sCurReq, uint8 ucVoltRange);

STATIC_AL void FctR_DiagFeedback(tsDiagFeedback_Cfg *psDiagSettings, boolean *pboDiagFeedback, boolean boForceErrReset);
STATIC_AL void FctR_KeepTiStatusOn(void);
STATIC_AL void FctR_StoreIlluminantFailureFunction(void);
STATIC_AL void FctR_StoreIlluminantStatusFunction(void);
//=============================================================================
// variables
//=============================================================================

//Stores the LED channels intensities from Look-up table
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
//previous values for CL/SBL intensities
STATIC_AL uint8 FctR_ucTgtClSblLmpInt_Prv[FCTR_CFG_LOGLMP_MAX];
#endif

// Requests for Light Functions
STATIC_AL tsFctR_TgtLgtReq FctR_TgtLgtReq;
// Previous requests for Light Functions
STATIC_AL tsFctR_TgtLgtReq FctR_TgtLgtReq_Prv;
// Actual leds error state
STATIC_AL tsFctR_IlluminantStates FctR_ActIlluminantStates[FCTR_CFG_LOGLMP_MAX];
// Failure indication of light functions
//STATIC_AL tuFctR_LgtFct FctR_LgtFctFailure;
// F-Bit Failure indication of light functions8
STATIC_AL tuFctR_LgtFct FctR_LgtFctFailureFBit;

// Status of light functions (0 = OFF; 1 = ON)
//STATIC_AL tuFctR_LgtFct FctR_LgtFctStatus;
// Mark reaction to switch off illuminant if F-Bit = 1
// 1 = LogLmp is used by this light function (Lmm[LgtFct].ucIntensity > 0), 0 = LogLmp is not used by this light function (Lmm[LgtFct].ucIntensity == 0)
tuFctR_LogLmp FctR_UsageLogLmpTable[FCTR_CFG_LGTFCT_MAX];
// 1 = LogLmp is configured to be accessed by the LgtFct (intensity > 0 OR prio < 15 OR F = 1 OR A = 1), 0 = LogLmp is not configured to be accessed by the LgtFct
tuFctR_LogLmp FctR_AccessLogLmpTable[FCTR_CFG_LGTFCT_MAX];

// For each logical lamp the light function with the highest priority (LF_xxx)
STATIC_AL uint8 FctR_ucTgtLgtHighPrio[FCTR_CFG_LOGLMP_MAX];
// For each logical lamp the light function which is sustained (LF_xxx)
STATIC_AL uint8 FctR_ucTgtLgtSustained[FCTR_CFG_LOGLMP_MAX];
// For each logical lamp the light function with highest priority of previous call (LF_xxx)
STATIC_AL uint8 FctR_ucTgtLgtHighPrioPrevious[FCTR_CFG_LOGLMP_MAX];
// For each logical lamp the light function with highest priority with Fbit (LF_xxx)
STATIC_AL uint8 FctR_ucTgtLgtHighPrioFbit[FCTR_CFG_LOGLMP_MAX];

// [1/FCTR_RES_ACTLMP %] For each logical lamp the actual value (calculated by an internal ramp)
STATIC_AL uint32 FctR_ulActLmpInt[FCTR_CFG_LOGLMP_MAX];
// [%] For each logical lamp the actual value (calculated by an internal ramp)
STATIC_AL uint8 FctR_ucActLmpInt[FCTR_CFG_LOGLMP_MAX];
// [%] For each logical lamp the target intensity
STATIC_AL uint8 FctR_ucTgtLmpInt[FCTR_CFG_LOGLMP_MAX];
STATIC_AL boolean FctR_boSwitchOffByFBit = FALSE;
// [20 ms] For each logical lamp the speed to reach its target intensity
STATIC_AL uint16 FctR_unTgtLmpSpdInv[FCTR_CFG_LOGLMP_MAX];
// [100 ms/100%] For each logical lamp the speed to reach its target intensity
STATIC_AL uint16 FctR_unTgtLmpSpdInv_sk[FCTR_CFG_LOGLMP_MAX];

// Contains two pairs of (light function, priority) for each logical lamp. 
// One pair for light functions with Active Bit = 0 (Pair 1) and
// another pair for light functions with Active Bit = 1 (Pair 2).
STATIC_AL tPrioLgtFctPair FctR_PrioLgtFctPair[FCTR_CFG_LOGLMP_MAX];

STATIC_AL tsFctR_TimerCfg FctR_sTimerCfg[FCTR_NUMBER_OF_TIMERS];

STATIC_AL uint32 FctR_ulAimBlinkTime;           // time in ms for aiming blinking phases
STATIC_AL FctR_eAimingType FctR_eAimingMode;    // aiming mode state variable

STATIC_AL tsFctR_LightStatus FctR_sLightStatus;
STATIC_AL tsFctR_LightFailureStatus FctR_sLightFailureStatus;

STATIC_AL uint16 FctR_DRLIlluminantsErr; //store failure on DRL
STATIC_AL uint16 FctR_Cod_DRLIlluminantsFBit; //store Fbit for DRL
//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  FctR_CalculateUsageLogLmpTable
///
/// \descr  Calculates usage tables for FctR_UsageLogLmpTable and FctR_AccessLogLmpTable
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_CalculateUsageLogLmpTable(void)
{
  if (FctR_Cod_Valid() != FALSE)
  {
    tAppLightFunction ucLgtFct;
    tAppLogLamp       ucLogLamp;
    uint8             ucIdx, ucIntensity, ucPriority, ucErrBit, ucActiveBit;

    for (ucLgtFct = 0; ucLgtFct < FCTR_CFG_LGTFCT_MAX; ucLgtFct++)
    {
      // Optimize
      ucIdx = ucLgtFct;

      for (ucLogLamp = (uint8)LL1; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
      {
        // Get the coding values
        //ucIntensity = FctR_ChLut[ucLgtFct][ucLogLamp].ucIntensity; //Cod_IntensityB  (ucLgtFct, ucLogLamp);
        ucIntensity = Cod_IntensityB(ucLgtFct, ucLogLamp);
        //ucPriority  = FctR_ChLut[ucLgtFct][ucLogLamp].ucPriority;  //Cod_PriorityB   (ucLgtFct, ucLogLamp);
        ucPriority = Cod_PriorityB(ucLgtFct, ucLogLamp);
        ucErrBit    = Cod_ErrorImpactB(ucLgtFct, ucLogLamp);
        //ucActiveBit = FctR_ChLut[ucLgtFct][ucLogLamp].ucActiveBit; //Cod_ActiveB     (ucLgtFct, ucLogLamp);
        ucActiveBit = Cod_ActiveB(ucLgtFct, ucLogLamp);

        // Check the usage of logical lamp
        if (ucIntensity > 0u)
        {
          FCTR_SET_LOG_LMP_BIT(ucLogLamp, FctR_UsageLogLmpTable[ucIdx].Raw);
        }
        else
        {
          FCTR_CLR_LOG_LMP_BIT(ucLogLamp, FctR_UsageLogLmpTable[ucIdx].Raw);
        }

        // Check the accessibility of logical lamp
        if ( (ucIntensity >  0u)
          || (ucPriority  < FCTR_CFG_LGTFCT_NOT_USED)
          //|| (ucErrBit    >  0u)
          || (ucActiveBit >  0u) )
        {
          FCTR_SET_LOG_LMP_BIT(ucLogLamp, FctR_AccessLogLmpTable[ucIdx].Raw);
        }
        else
        {
          FCTR_CLR_LOG_LMP_BIT(ucLogLamp, FctR_AccessLogLmpTable[ucIdx].Raw);
        }
        if ((ucErrBit > 0u)
          && (ucLgtFct == (uint8)DRL_DaytimeRunningLight))
        {
          FCTR_SET_LOG_LMP_BIT(ucLogLamp, FctR_Cod_DRLIlluminantsFBit);
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_GetActiveTgtLgtReq
/// 
/// \descr  Get the request status of the specific light function 
///
/// \param  ulLgtFct - light function index
///
/// \return TRUE = active request; FALSE = no request
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_GetActiveTgtLgtReq(tAppLightFunction ulLgtFct)
{
  return ((FCTR_GET_LGT_FCT_BIT(ulLgtFct, FctR_TgtLgtReq.Req.ulRaw) != 0u) ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Percent_To_RteUnit
///
/// \descr  Transform [%] to [0.1%] in uint16 (parameter unit to RTE unit)
///
/// \param  ucPercentVal - value in percentage [%]
///
/// \return Value in Rte unit ( [0.1%] of ucPercentVal )
//-----------------------------------------------------------------------------
STATIC_AL uint16 FctR_Percent_To_RteUnit(uint8 ucPercentVal)
{
  return (uint16) (FCTR_RTE_UNIT_SCALER * (uint32)ucPercentVal);
}

//-----------------------------------------------------------------------------
/// \brief  FctR_SpecialBehaviorDrlPos
/// 
/// \descr  This function return the activation of special behavior for POS and DRL
///         It's TRUE when POS+DRL are requested and one of the illuminants related to
///         DRL has a failure bit set and an error occur then force DRL request to OFF
///
/// \param  ulLgtFct - light function index
///
/// \return TRUE = force off DRL request; FALSE = do nothing
//-----------------------------------------------------------------------------
boolean FctR_SpecialBehaviorDrlPos(void)
{
  boolean boForceOffDrlRequest = FALSE;

    if(((FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight != 0u) && (FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight != 0u)) && // POS and DRL are requested
      ((FctR_DRLIlluminantsErr & FctR_Cod_DRLIlluminantsFBit) != 0u))  //at init phase of FctR, the code set the DRL's illuminants which contain F-bit Present (bit representation for each illuminant) and should match with actual DRL illuminant's error
    {
      boForceOffDrlRequest = TRUE;
    }
    else
    {
      //do nothing
    }

  return boForceOffDrlRequest;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtInit
///
/// \descr  Initialize FctRTgt
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_TgtInit(void)
{
  uint8 ucLogLmp;
  
  FctR_TgtLgtReq.Req.ulRaw                    = 0u;
  FctR_TgtLgtReq_Prv.Req.ulRaw                = 0u;

  for (ucLogLmp = 0; ucLogLmp < FCTR_CFG_LOGLMP_MAX; ucLogLmp++)
  {
    FctR_ucTgtLgtSustained[ucLogLmp]        = (uint8)LF_INIT;
    FctR_ucTgtLgtHighPrio[ucLogLmp]         = (uint8)LF_INIT;
    FctR_ucTgtLgtHighPrioPrevious[ucLogLmp] = (uint8)LF_INIT;
    FctR_ucTgtLgtHighPrioFbit[ucLogLmp]     = (uint8)LF_INIT;
    FctR_ulActLmpInt[ucLogLmp]              = 0u;
    FctR_ucActLmpInt[ucLogLmp]              = 0u;
    FctR_ucTgtLmpInt[ucLogLmp]              = 0u;
    FctR_unTgtLmpSpdInv[ucLogLmp]           = 0u;
    FctR_unTgtLmpSpdInv_sk[ucLogLmp]        = 0u;
  }
  // Maps the coding parameters to FctR
  FctR_MapParams();
  FctR_CalculateUsageLogLmpTable();

  FctR_TgtPrep_Init();

  // Send initial values on Rte at start up.
  FctR_TgtLgt_Output();


  // blink time for each side(50%ON - 50%OFF) will be 1/frequency and divided by 2 for 50% duty
  // added tolerance because of the 10 ms resolution of the FctR cyclic time
  FctR_ulAimBlinkTime = ((FCTR_FREQUENCY_RESOLUTION_FACTOR / FCTR_AIM_BLINK_FREQ) / FCTR_DUTY_DIVIDER)- FCTR_AIM_BLINK_FREQ_TOLERANCE;

  FctR_eAimingMode = eAimingOff;

}

//-----------------------------------------------------------------------------
/// \brief  FctR_GetPriority
///
/// \descr  Return the priority of light function LgtFct for logical lamp LogLmp.
///
/// \param  LgtFct - index of light function
///         LogLmp - index of logical lamp
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 FctR_GetPriority(tAppLightFunction LgtFct, tAppLogLamp LogLmp)
{
  uint8 ucPrio;
  boolean boLgtFctIdxValid;

  boLgtFctIdxValid = FctR_LgtFctIndexCheck(LgtFct);

  if (boLgtFctIdxValid != FALSE)
  {
    //ucPrio = FctR_ChLut[LgtFct][LogLmp].ucPriority; //Cod_PriorityB(LgtFct, LogLmp);
    ucPrio = Cod_PriorityB(LgtFct, LogLmp);
  }
  else
  {
    ucPrio = Fix_PriorityI(LogLmp);
  }

  return ucPrio;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_GetIntensity
///
/// \descr  Get the intensity of the light function LgtFct for the logical lamp LogLmp
///
/// \param  LgtFct - light function index
///         LogLmp - logical lamp index
///
/// \return The intensity to be set for the specific logical lamp
//-----------------------------------------------------------------------------
STATIC_AL uint8 FctR_GetIntensity(tAppLightFunction LgtFct, tAppLogLamp LogLmp)
{
  uint8   ucIntensity;
  boolean boLgtFctIdxValid;
  
  boLgtFctIdxValid = FctR_LgtFctIndexCheck(LgtFct);

  if (boLgtFctIdxValid != FALSE)
  {
    //ucIntensity = FctR_ChLut[LgtFct][LogLmp].ucIntensity; //Cod_IntensityB(LgtFct, LogLmp);
    ucIntensity = Cod_IntensityB(LgtFct, LogLmp);
  }
  else
  {
    ucIntensity = Fix_IntensityI(LogLmp);
  }

  return ucIntensity;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_ActLgt_Update
///
/// \descr  Update all actual intensities of logical lamps in order to reach FctR_ucTgtLmpInt.
///         Therefore, the (internal) high-res registers of all logical lamp intensities
///         are updated using the speeds stored in FctR_unTgtLmpSpdInv_sk.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_ActLgt_Update(void)
{
  uint8  ucLogLmp;
  uint32 ulInc;
  uint32 ulTgtInt;

  for (ucLogLmp = 0; ucLogLmp < FCTR_CFG_LOGLMP_MAX; ucLogLmp++)
  {
    if (FctR_unTgtLmpSpdInv_sk[ucLogLmp] == 0u)
    {
      FctR_ucActLmpInt[ucLogLmp] = FctR_ucTgtLmpInt[ucLogLmp];
      FctR_ulActLmpInt[ucLogLmp] = (uint32)(FCTR_RES_ACTLMP * (uint32)FctR_ucTgtLmpInt[ucLogLmp]);
    }
    else
    {
      // t : Time for 100% [100 ms] (inverse of speed)
      // tc: Cycle time [20 ms]
      // i: increment
      //
      // 100% / (100 * t) = i / tc
      // <=>
      // i = tc * 100% / (100 * t)
      //   = tc / t
      ulInc = (FCTR_RES_ACTLMP * FCTR_CYCLE_FCTR_TGTCYCLE0) / FctR_unTgtLmpSpdInv_sk[ucLogLmp];
      ulTgtInt = (uint32)(FCTR_RES_ACTLMP * (uint32)FctR_ucTgtLmpInt[ucLogLmp]);

      if (FctR_ulActLmpInt[ucLogLmp] > ulTgtInt)
      {
        if ((FctR_ulActLmpInt[ucLogLmp] - ulTgtInt) > ulInc)
        {
          FctR_ulActLmpInt[ucLogLmp] -= ulInc;
        }
        else
        {
          FctR_ulActLmpInt[ucLogLmp] = ulTgtInt;
        }
      }
      else
      {
        if ((ulTgtInt - FctR_ulActLmpInt[ucLogLmp]) > ulInc)
        {
          FctR_ulActLmpInt[ucLogLmp] += ulInc;
        }
        else
        {
          FctR_ulActLmpInt[ucLogLmp] = ulTgtInt;
        }
      }

      FctR_ucActLmpInt[ucLogLmp] = (uint8) (FctR_ulActLmpInt[ucLogLmp] / FCTR_RES_ACTLMP);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prio_LgtFctB_LogLmp
///
/// \descr  Compute FctR_PrioLgtFctPair for a light function.
///
/// \param  ucLgtFct - index of light function
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prio_LgtFctB_LogLmp(tAppLightFunction ucLgtFct)
{
  tAppLogLamp ucLogLamp;
  boolean     boLogLmpAccess;

  for (ucLogLamp = (uint8)LL1; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {
    // Handle logical lamps with active bit
    if (Cod_ActiveB(ucLgtFct, ucLogLamp) != 0u)
    {
      if (FctR_HigherPrio(Cod_PriorityB(ucLgtFct, ucLogLamp), FctR_PrioLgtFctPair[ucLogLamp].ucPrio2) != FALSE)
      {
        // Update FctR_PrioLgtFctPair with the highest priority function
        FctR_PrioLgtFctPair[ucLogLamp].ucPrio2 = Cod_PriorityB(ucLgtFct, ucLogLamp);
        FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct2 = ucLgtFct;
      }
      else
      {
        // Do not update FctR_PrioLgtFctPair
      }
    }
    // Handle logical lamps without active bit
    else
    {
      boLogLmpAccess = FctR_AccessLogLmp(ucLgtFct, ucLogLamp);

      if ((FctR_HigherPrio(Cod_PriorityB(ucLgtFct, ucLogLamp), FctR_PrioLgtFctPair[ucLogLamp].ucPrio1) != FALSE) && (boLogLmpAccess != FALSE))
      {
        // Update FctR_PrioLgtFctPair with the highest priority function
        FctR_PrioLgtFctPair[ucLogLamp].ucPrio1 = Cod_PriorityB(ucLgtFct, ucLogLamp);
        FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1 = ucLgtFct;
      }
      else
      {
        // Do not update FctR_PrioLgtFctPair
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prio_LgtFct
///
/// \descr  Compute FctR_PrioLgtFctPair for light functions based on request,
///         fail/safe modes due to hardware errors, timing conditions.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prio_LgtFct(void)
{
  tAppLightFunction ulLgtFct;

  for (ulLgtFct = 0; ulLgtFct < FCTR_CFG_LGTFCT_MAX; ulLgtFct++)
  {
    // Check only mandatory lamps
    if (FctR_GetActiveTgtLgtReq(ulLgtFct) != FALSE)
    {
        // Fill FctR_PrioLgtFctPair[LogLmp]
        FctR_TgtLgt_Prio_LgtFctB_LogLmp(ulLgtFct);
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prio_LgtFct_FinalizePrio
///
/// \descr  Given valid FctR_PrioLgtFctPair, determine the light function which
///         has access to a logical lamp.
///         FctR_PrioLgtFctPair contains two pairs of (light function, priority) 
///         for each logical lamp. One pair for light functions with Active Bit = 0 (Pair 1)
///         and another pair for light functions with Active Bit = 1 (Pair 2).
///         This function decides whether Pair 1 or Pair 2 has access to a logical lamp.
///         That is, this function ensures the proper treatment of the Active Bit.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prio_LgtFct_FinalizePrio(void)
{
  tAppLogLamp ucLogLamp;
  
  for (ucLogLamp = (uint8)LL1; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {  
    // Check for light functions with Active Bit
    if (FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct2 == (uint8)LF_INIT)
    {
      // No light function with Active Bit => set as high prio the light function without Active Bit
      FctR_ucTgtLgtHighPrio[ucLogLamp] = (uint8) FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1;
    }
    else
    {
      if (FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1 == (uint8)LF_INIT)
      {
        // Light function with Active Bit but no light function without Active Bit
        // Ignore the light function with Active Bit
        FctR_ucTgtLgtHighPrio[ucLogLamp] = (uint8)LF_INIT;
      }
      else
      {
        // Light function with Active Bit and light function without Active Bit
        if (FctR_HigherPrio(FctR_PrioLgtFctPair[ucLogLamp].ucPrio1, FctR_PrioLgtFctPair[ucLogLamp].ucPrio2) != FALSE)
        {
          // Light function without Active Bit has higher priority and wins
          FctR_ucTgtLgtHighPrio[ucLogLamp] = (uint8) FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1;
        }
        else
        {
          // Light function with Active Bit has higher priority and wins if the other light function has
          // an intensity greater than 0.
          if (FctR_UsageLogLmp(FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1, ucLogLamp) != FALSE)
          {
            FctR_ucTgtLgtHighPrio[ucLogLamp] = (uint8) FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct2;
          }
          else
          {
            FctR_ucTgtLgtHighPrio[ucLogLamp] = (uint8) FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1;
          }
        }
      }
    }
  }

  // PRQA S 5336 1     // Function is maintainable and well-structured
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prio
///
/// \descr  Priorize light functions based on request flags and parameters (LSM).
///         If coding data is invalid, LF_INIT has highest priority for all Logical Lamps.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prio(void)
{
  tAppLogLamp ulLogLamp;

  // Set init values for all Logical Lamps
  for (ulLogLamp = 0; ulLogLamp < FCTR_CFG_LOGLMP_MAX; ulLogLamp++)
  {
    FctR_ucTgtLgtHighPrio[ulLogLamp]           = (uint8)LF_INIT;
    FctR_PrioLgtFctPair  [ulLogLamp].ucPrio1   = Fix_PriorityI(ulLogLamp);
    FctR_PrioLgtFctPair  [ulLogLamp].ucPrio2   = Fix_PriorityI(ulLogLamp);
    FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct1 = (uint8)LF_INIT;
    FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct2 = (uint8)LF_INIT;
  }
  
  if (FctR_Cod_Valid() != FALSE)
  {
    FctR_TgtLgt_Prio_LgtFct();
    FctR_TgtLgt_Prio_LgtFct_FinalizePrio();
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_GetLmpSpdInvFromRampType
///
/// \descr  Compute the speed of the light function based on its target intensity
///         FctR_ucTgtLmpInt and the actual intensity FctR_ucActLmpInt.
///
/// \param  ucRampType - ramp type from LMM
///         unTime     - Ton/Toff time from LMMM
///         LogLamp    - index of logical lamp
///
/// \return The speed of light function [100 ms/ 100%]
//-----------------------------------------------------------------------------
STATIC_AL uint16 FctR_TgtLgt_GetLmpSpdInvFromRampType(uint8 ucRampType, uint16 unTime, tAppLogLamp LogLamp)
{
  uint16 unSpd;

  // these lines are needed for internal ramp calculation
  uint8 ucDelta = (FctR_ucTgtLmpInt[LogLamp] > FctR_ucActLmpInt[LogLamp]) ? 
                  (FctR_ucTgtLmpInt[LogLamp] - FctR_ucActLmpInt[LogLamp]) :
                  (FctR_ucActLmpInt[LogLamp] - FctR_ucTgtLmpInt[LogLamp]);

  if (ucDelta > 0u)
  {
    FctR_unTgtLmpSpdInv_sk[LogLamp] = (uint16) (((uint32) unTime * 20u) / (uint32) ucDelta);
  }
  else
  {
    FctR_unTgtLmpSpdInv_sk[LogLamp] = 0;
  }

  if (ucRampType == FCTR_RAMP_ZK)
  {
    // ZK
    unSpd = unTime;
  }
  else
  {
    // HART
    unSpd = 0;
  }
  
  return unSpd;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_GetLmpSpdInvB
///
/// \descr  Compute the speed of the light function based on its actual intensity 
///         FctR_ucActLmpInt and its target intensity FctR_ucTgtLmpInt.
///         Needs a valid pointer to coding data.
///
/// \param  LgtFct  - light function index
///         LogLamp - logical lamp index
///
/// \return Speed of the light function [100 ms/100%]
//-----------------------------------------------------------------------------
STATIC_AL uint16 FctR_TgtLgt_GetLmpSpdInvB(tAppLightFunction LgtFct, tAppLogLamp LogLamp)
{
  uint16 unTime = 0u;
  uint16 unSpd = 0u;
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  const tsFctR_ClSblDimState sClSblDimState[] = FCTR_CFG_SBL_CL_DIM_SEL;
  static uint8 ucCurrentClSblState = FCTR_CFG_SBL_CL_OFF;
  STATIC_UT(uint8, ucClSblDimOut, 255U);
  uint8 ucClSblTargetState = FCTR_CFG_SBL_CL_OFF;

  //special case for SBL/CL
  if (((FctR_ucTgtLgtHighPrio[LogLamp] == (uint8)SBL_StaticBendingLight) || (FctR_ucTgtLgtHighPrio[LogLamp] == (uint8)CL_CorneringLight)) ||
      ((FctR_ucTgtLgtSustained[LogLamp] == (uint8)SBL_StaticBendingLight) || (FctR_ucTgtLgtSustained[LogLamp] == (uint8)CL_CorneringLight)))
  {
    ucClSblTargetState = FctR_TgtPrep_GetClSblTargetState();
    const uint8 ucSizeTable = (sizeof(sClSblDimState) / sizeof(sClSblDimState[0]));
    for (uint8_fast ucIdx = 0U; ucIdx < ucSizeTable; ucIdx++)
    {
      if ((ucClSblTargetState == sClSblDimState[ucIdx].ucTargetState) && (ucCurrentClSblState == sClSblDimState[ucIdx].ucCurrentState))
      {
        ucClSblDimOut = sClSblDimState[ucIdx].ucDimOut;
        break;
      }
    }

    switch (ucClSblDimOut)
    {
    case FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT:
      unTime = (uint16)Cod_TimeOnB((tAppLightFunction)FctR_ucTgtLgtHighPrio[LogLamp], LogLamp);
      unTime = (((uint16)((uint16)FctR_ucTgtLmpInt[LogLamp] - (uint16)FctR_ucTgtClSblLmpInt_Prv[LogLamp]) * unTime) / (uint16)100u);
      break;
    case FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT:
      unTime = Cod_TimeOffB(((ucClSblTargetState == FCTR_CFG_SBL_CL_OFF) && (ucCurrentClSblState == FCTR_CFG_SBL_CL_NOMINAL)) ? (tAppLightFunction)FctR_ucTgtLgtSustained[LogLamp] :(tAppLightFunction)FctR_ucTgtLgtHighPrio[LogLamp], LogLamp);
      unTime = (((uint16)FctR_ucTgtClSblLmpInt_Prv[LogLamp] - (uint16)FctR_ucTgtLmpInt[LogLamp]) * unTime) / 100u;
      break;
    case FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME:
      unTime = Cod_AfsTransitionDim();
      break;
    default:
      unTime = 0u;
      break;
    }
  }
  //default path
  else
#endif
  {
    if (FctR_GetActiveTgtLgtReq(LgtFct) != FALSE)
    {
      unTime = Cod_TimeOnB(LgtFct, LogLamp);
    }
    else
    {
      unTime = Cod_TimeOffB(LgtFct, LogLamp);
    }
  }

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)

  //should be here because when SBL is OFF (see the special code of checking SBL/CL request) current state should be updated also.
  ucCurrentClSblState = ucClSblTargetState;

  FctR_ucTgtClSblLmpInt_Prv[LogLamp] = FctR_ucTgtLmpInt[LogLamp];
#endif
  unSpd = FctR_TgtLgt_GetLmpSpdInvFromRampType(Cod_RampTypeB(LgtFct, LogLamp), unTime, LogLamp);
  
  return unSpd;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_GetLmpSpdInv
///
/// \descr  Compute the speed of the light function based on its actual 
///         intensity FctR_ucActLmpInt and its target intensity FctR_ucTgtLmpInt.
///         Needs a valid pointer to coding data.
///
/// \param  LgtFct  - light function index
///         LogLamp - logical lamp index
///
/// \return The speed of the light function [100 ms/100%]
//-----------------------------------------------------------------------------
STATIC_AL uint16 FctR_TgtLgt_GetLmpSpdInv(tAppLightFunction LgtFct, tAppLogLamp LogLamp)
{
  uint16 unSpd;

  if (FctR_LgtFctIndexCheck(LgtFct) != FALSE)
  {
    unSpd = FctR_TgtLgt_GetLmpSpdInvB(LgtFct, LogLamp);
  }
  else
  {
    // LF_INIT
    unSpd = Fix_TimeOffI(LogLamp);
  }

  return unSpd;
// PRQA S 5106 1   // Function is maintainable and well-structured
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Sustain_LogLamp
///
/// \descr  Sustain light functions for a single logical lamp.
///
/// \param  ucLogLamp - logical lamp index
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Sustain_LogLamp(tAppLogLamp ucLogLamp)
{
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  static uint8 ucCntChanges[FCTR_CFG_LOGLMP_MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  boolean boSblInAfsMode_status = FALSE;
  tAppLightFunction ucClSblInAfsModeLight = 255U;
#else
  static uint8 ucCntChanges[FCTR_CFG_LOGLMP_MAX] = { 0, 0, 0, 0, 0, 0 };
#endif

        tAppLightFunction Actual    = (tAppLightFunction) FctR_ucTgtLgtHighPrio[ucLogLamp];
  const tAppLightFunction Sustained = (tAppLightFunction) FctR_ucTgtLgtSustained[ucLogLamp];
  const tAppLightFunction Previous  = (tAppLightFunction) FctR_ucTgtLgtHighPrioPrevious[ucLogLamp];
  boolean boTiCmd;
  boolean boClSblIntChanged = FALSE;

  // Commented code will be used after coding integration
  if (FctR_Cod_Valid() != FALSE)
  {
    boTiCmd = FctR_TgtPrep_GetTiCmdReq();
    // Get target intensity
    // Special handling for TI channel to blink while TI light function is active and DRL/POS channel to stay ON
    const boolean boTI_POS_Act = ((Actual == (tAppLightFunction)TI_TurnIndicator) || (Actual == (tAppLightFunction)TI_POS_TurnIndicatorPos)) ? TRUE : FALSE;
    const boolean boCod_Active = (Cod_ActiveB(Actual, ucLogLamp) == 0u) ? TRUE : FALSE;
    if ((boTI_POS_Act != FALSE) && (boCod_Active != FALSE) && (boTiCmd == FALSE))
    {
      FctR_ucTgtLmpInt[ucLogLamp] = 0u;
    }
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
    else if((FctR_ucTgtLgtHighPrio[ucLogLamp] == (uint8)SBL_StaticBendingLight) || (FctR_ucTgtLgtHighPrio[ucLogLamp] == (uint8)CL_CorneringLight))
    {
      ucClSblInAfsModeLight = (tAppLightFunction)FctR_TgtPrep_GetClSbl_AfsLight();
      //priority is done in FctR_ucTgtLgtSustained, overwrite the corect priority
      ucClSblInAfsModeLight = ((ucClSblInAfsModeLight == (tAppLightFunction)SBL_StaticBendingLight) || (ucClSblInAfsModeLight == (tAppLightFunction)CL_CorneringLight)) ? FctR_ucTgtLgtHighPrio[ucLogLamp] : ucClSblInAfsModeLight;
      FctR_ucTgtLmpInt[ucLogLamp] = FctR_GetIntensity(ucClSblInAfsModeLight, ucLogLamp);

      boClSblIntChanged = (FctR_ucTgtClSblLmpInt_Prv[ucLogLamp] != FctR_ucTgtLmpInt[ucLogLamp]) ? TRUE : boClSblIntChanged;
    }
#endif
    else
    {
      FctR_ucTgtLmpInt[ucLogLamp] = FctR_GetIntensity(Actual, ucLogLamp);
    }

    if (Sustained != Actual)
    {
      if (FctR_HigherPrio(FctR_GetPriority(Actual, ucLogLamp), FctR_GetPriority(Sustained, ucLogLamp)) != FALSE)
      {
        // Prio(Actual) higher than Prio(Sustained)
        FctR_ucTgtLgtSustained[ucLogLamp] = (uint8) Actual;
        FctR_unTgtLmpSpdInv[ucLogLamp] = FctR_TgtLgt_GetLmpSpdInv(Actual, ucLogLamp);
      }
      else
      {
        if (Previous != Actual)
        {
          // 1st change --> start of Toff ramp
          if(ucCntChanges[ucLogLamp] == 0u)
          {
            // Set speed once
            FctR_unTgtLmpSpdInv[ucLogLamp] = FctR_TgtLgt_GetLmpSpdInv(Sustained, ucLogLamp);
          }
          // This is a new request that cancels the active ramp
          else
          {
          FctR_ucTgtLgtSustained[ucLogLamp] = (uint8)Actual;
          FctR_unTgtLmpSpdInv[ucLogLamp] = FctR_TgtLgt_GetLmpSpdInv(Actual, ucLogLamp);
          }

          ucCntChanges[ucLogLamp]++;
        }

        // Check if target value is reached
        if (FctR_ucTgtLmpInt[ucLogLamp] == FctR_ucActLmpInt[ucLogLamp])
        {
          // Target value reached
          FctR_ucTgtLgtSustained[ucLogLamp] = (uint8)Actual;
        }
        else
        {
          // Do not updated sustained function
        }
      }
    }
    else if ((Previous != Actual) || (boClSblIntChanged != FALSE))
    {
    // Set speed once
      FctR_unTgtLmpSpdInv[ucLogLamp] = FctR_TgtLgt_GetLmpSpdInv(Sustained, ucLogLamp);
      ucCntChanges[ucLogLamp] = 0;
    }
    else
    {
      ucCntChanges[ucLogLamp] = 0;
    }
  }
  else
  {
    // Use init values if the pointer to the coding area is invalid
    FctR_ucTgtLgtHighPrio[ucLogLamp] = (uint8)LF_INIT;
    FctR_ucTgtLgtSustained[ucLogLamp] = (uint8)LF_INIT;
    FctR_ucTgtLmpInt[ucLogLamp] = Fix_IntensityI(ucLogLamp);
    FctR_unTgtLmpSpdInv[ucLogLamp] = Fix_TimeOffI(ucLogLamp);
  }

  // PRQA S 5324,5336 1     // Function is maintainable and well-structured
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Sustain
///
/// \descr  Sustain light functions based on request flags and parameters (LSM).
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Sustain(void)
{
  uint8 ucLogLamp;

  for (ucLogLamp = 0u; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {
    FctR_TgtLgt_Sustain_LogLamp(ucLogLamp);
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Output
///
/// \descr  Write output values of light functions
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Output(void)
{
  uint8_fast         ucLogLamp;
  tsRte_TgtLedVal0Arr sTgtLampVal;
  boolean boPxaFbit = FALSE;
  
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  static teFctR_LightFunctions eClSblPrv = LF_INIT;
  teFctR_AfsMode      eAfsMode_Received;
#endif
  // Write target LED values
  for (ucLogLamp = 0U; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {
    //f bit failre is still present AND (actual f bit for high prio light is present AND high prio light is OFF) => reset fbit failure for the affected light distribution
    if ((FctR_LgtFctFailureFBit.ulRaw != 0U) && ((FCTR_GET_LGT_FCT_BIT(FctR_ucTgtLgtHighPrioFbit[ucLogLamp], FctR_LgtFctFailureFBit.ulRaw) != 0u) && (FCTR_GET_LGT_FCT_BIT(FctR_ucTgtLgtHighPrio[ucLogLamp], FctR_LgtFctFailureFBit.ulRaw) == 0u)))  
    {
      FctR_LgtFctFailureFBit.ulRaw &= (uint32)~(uint32)((uint32)1u << (uint32)FctR_ucTgtLgtHighPrioFbit[ucLogLamp]);
    }

    //based on light distribution present with Fbit set, force to OFF the affected illuminants
    if (FCTR_GET_LGT_FCT_BIT(FctR_ucTgtLgtHighPrio[ucLogLamp], FctR_LgtFctFailureFBit.ulRaw) != 0u)
    {
      sTgtLampVal.asTgtLedVal[ucLogLamp].unTgtIntensity = 0U;
      sTgtLampVal.asTgtLedVal[ucLogLamp].boFBit = TRUE;
      sTgtLampVal.asTgtLedVal[ucLogLamp].unRampTime = 0U;
      FctR_ucTgtLgtHighPrioFbit[ucLogLamp] = FctR_ucTgtLgtHighPrio[ucLogLamp];
    }
    else
    {
      FctR_ucTgtLgtHighPrioFbit[ucLogLamp] = (uint8)LF_INIT;
      sTgtLampVal.asTgtLedVal[ucLogLamp].unTgtIntensity = FctR_Percent_To_RteUnit(FctR_ucTgtLmpInt[ucLogLamp]);
      sTgtLampVal.asTgtLedVal[ucLogLamp].boFBit = FALSE;
      sTgtLampVal.asTgtLedVal[ucLogLamp].unRampTime = FCTR_RAMP_RESOLUTION * FctR_unTgtLmpSpdInv[ucLogLamp];                  // [200ms] - LSM coding resolution to [100ms] - speed of RTE
    }

    // Update previous high prio light function
    FctR_ucTgtLgtHighPrioPrevious[ucLogLamp] = FctR_ucTgtLgtHighPrio[ucLogLamp];
  }
    
  uint32 ulLDraw = FctR_TgtLgtReq.Req.ulRaw;

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  // Write Afs Dbl command
  FctR_TgtDbl_Output();
  // Get Afs Mode received on CAN
  eAfsMode_Received = FctR_TgtPrep_GetAfsMode();

  if ((FctR_LgtFctFailureFBit.ulRaw & FctR_TgtLgtReq.Req.ulRaw & (uint32)FCTR_SET_FAILURE_LB_HB_FCTS) != 0U)
  {
    boPxaFbit = TRUE;
  }

  (void)Rte_Write_FctR_PXALightDistr_Fbit(&boPxaFbit);
  // Write Afs Mode signal
  (void)FctR_RteAccess_Write_AfsMode(FctR_TgtLgtReq, eAfsMode_Received, FctR_eAimingMode);
  
  if (FctR_TgtPrep_GetClSbl_AfsLight() == CL_CorneringLight)
  {
    ulLDraw |= FCTR_SET_CL_FCTS;
  }
  else if (FctR_TgtPrep_GetClSbl_AfsLight() == SBL_StaticBendingLight)
  {
    ulLDraw |= FCTR_SET_SBL_FCTS;
  }
  else
  {
    ulLDraw &= ((uint32)~FCTR_ERASE_CL_SBL_FCTS); //will never work when CL or SBL is requested via AFS (customer request)
  }

#endif

  (void)Rte_Write_FctR_LgtDistStatus(&ulLDraw);
  // Write light functions status (ON/OFF)
  (void)FctR_RteAccess_Write_LgtFctStatus(FctR_TgtLgtReq.Req);
  //write ramps and intensities
  (void)FctR_RteAccess_Write_TgtLedsVal(sTgtLampVal);
  // PRQA S 5324 1     // Function is maintainable and well-structured
}

//-----------------------------------------------------------------------------
/// \brief  FctR_KeepTiStatusOn
///
/// \descr   this function keeps the status of TI active while TI is requested
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_KeepTiStatusOn(void)
{
  uint8 ucTimersDelayStatus = FCTR_TIMEOUT_NOT_OCCURED;
  static boolean boTiStatus = FALSE;
  static boolean boTiReq = 0U;
  //TI status ON
  if (FctR_sLightStatus.boTiBlink_Status != FALSE)
  {
    //TI is on road
    boTiStatus = TRUE;
    //store TI request
    boTiReq = FctR_sLightStatus.boTiBlink_Status;
    //reset timer
    (void)FctR_CtrlDelayStatus(FALSE, FCTR_TI_BLINKING_DETECTION_TIME_MS, FCTR_TI_BLINKING_DETECTION);
  }
  else
  {
    //TI is no more active (falling edge)
    if (boTiStatus != FALSE)
    {
      //start timer
      ucTimersDelayStatus = FctR_CtrlDelayStatus(TRUE, FCTR_TI_BLINKING_DETECTION_TIME_MS, FCTR_TI_BLINKING_DETECTION);
      if (ucTimersDelayStatus == FCTR_IS_TIMEOUT)
      {
        //reset TI status
        boTiStatus = FALSE;
      }
      else
      {
        //keep TI status 
      }
    }
  }
  FctR_sLightStatus.boTi_Status = boTiStatus;
}


#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
//-----------------------------------------------------------------------------
/// \brief  FctR_TgtDbl_Output
///
/// \descr  Write output value for Dbl activation
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtDbl_Output(void)
{
  teFctR_DblCommand eTgtDblCmd;
  boolean boLB_CONDITIONS;
  boolean boHB_CONDITIONS;
  // Create mask containing all LowBeam and HighBeam light distributions
  const  tuFctR_LgtFct uMask = { .Bits.biLB_TownLight = 1u,
                                 .Bits.biLB_Pedestrian = 1u,
                                 .Bits.biLB_CountryLight = 1u,
                                 .Bits.biLB_MotorwayLight = 1u,
                                 .Bits.biLB_Boost       = 1u,
                                 .Bits.biLB_AdverseWeather_RHD = 1u,
                                 .Bits.biFoggyWeather_RHD = 0u,
                                 .Bits.biLB_AdverseWeather_LHD = 1u,
                                 .Bits.biFoggyWeather_LHD = 0u,
                                 .Bits.biHB_HighBeam = 0u
  };

  const  tuFctR_LgtFct uMask2 = { .Bits.biLB_TownLight = 0u,
                             .Bits.biLB_Pedestrian = 0u,
                             .Bits.biLB_CountryLight = 0u,
                             .Bits.biLB_MotorwayLight = 0u,
                             .Bits.biLB_Boost = 0u,
                             .Bits.biLB_AdverseWeather_RHD = 0u,
                             .Bits.biFoggyWeather_RHD = 0u,
                             .Bits.biLB_AdverseWeather_LHD = 0u,
                             .Bits.biFoggyWeather_LHD = 0u,
                             .Bits.biHB_HighBeam = 1u
  };

  boLB_CONDITIONS = (((FctR_TgtLgtReq.Req.ulRaw & uMask.ulRaw) != 0u) && ((FctR_TgtLgtReq.Req.ulRaw & (uint32)FCTR_DBLMASK_FOGGY) != 1u)) ? TRUE : FALSE;
  boHB_CONDITIONS = ((FctR_TgtLgtReq.Req.ulRaw & uMask2.ulRaw) != 0u) ? TRUE : FALSE;

  eTgtDblCmd = ((boLB_CONDITIONS != FALSE) || (boHB_CONDITIONS != FALSE)) ? PLAY_DBL : STOP_DBL;

  (void)FctR_RteAccess_Write_DblCmd(eTgtDblCmd); // Update function or Foggy
}

//-----------------------------------------------------------------------------
/// \brief FctR_CheckSblCl_LightStatus 
///
/// \descr This function get lighting status for SBL/CL
///         
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_CheckSblCl_LightStatus(void)
{
  boolean boStatus = FALSE;
  for (uint8 ucLogLamp = 0u; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {
    if ((FctR_ucTgtLgtSustained[ucLogLamp] == (uint8)SBL_StaticBendingLight) || (FctR_ucTgtLgtSustained[ucLogLamp] == (uint8)CL_CorneringLight))
    {
      boStatus = TRUE;
      break;
    }
  }
  return boStatus;
}

#endif

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_StorePrep
///
/// \descr  Store prep variables for light function requests
///
/// \param  -void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_StorePrep(void)
{
  uint8 ucLedVoltRng = FCTR_UNKNOWN_VOLT;
  tsFctR_TgtLgtReq sCurLgtFctReq;
  //get led volt state
  (void)FctR_RteAccess_Read_LedVoltRange(&ucLedVoltRng);
  //get current light functions request
  sCurLgtFctReq = FctR_TgtPrep_GetTgtLgtReq();
  //prepare target lights beased on voltage conditions
  FctR_TgtLgtReq = FctR_SetLgtReq_VoltCond(sCurLgtFctReq, ucLedVoltRng);
}

//-----------------------------------------------------------------------------
/// \brief  FctR_SetLgtReq_VoltCond
///
/// \descr  -this function decides the light function request output based on 
///          voltage state for led
///
/// \param  sCurReq       : current light functions requests
/// \param  ucVoltRange   : LED voltage state
///
/// \return  tsFctR_TgtLgtReq : light fct request
//-----------------------------------------------------------------------------
STATIC_AL tsFctR_TgtLgtReq FctR_SetLgtReq_VoltCond(tsFctR_TgtLgtReq sCurReq, uint8 ucVoltRange)
{
  static tsFctR_TgtLgtReq sOutReq;
  switch (ucVoltRange)
  {
  case FCTR_NORMAL_VOLT:
    sOutReq = sCurReq;
    break;
  case FCTR_LOW1_VOLT:
    //avoid to switch on other light function
    sOutReq.Req.ulRaw &= sCurReq.Req.ulRaw;
    break;
  case FCTR_LOW2_VOLT:
    sOutReq.Req.ulRaw = 0;
    break;
  default:
    break;
  }
  return sOutReq;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Tgt_GetActLedState
///
/// \descr  Get actual LED states
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_Tgt_GetActLedState(void)
{
  tsRte_LedErrStateArr sLedState;
  // Read Leds state from Rte
  FctR_DRLIlluminantsErr = 0u;
  (void)FctR_RteAccess_Read_ActLedState(&sLedState);
 
  for (uint8_fast ucIdx = 0u; ucIdx < FCTR_CFG_LOGLMP_MAX; ucIdx++)
  {
    FctR_ActIlluminantStates[ucIdx].boIlFailureStatus = FALSE;
    // Store actual led state
    FctR_ActIlluminantStates[ucIdx].unIlluminantErrState = sLedState.uIlluminantState[ucIdx].unRaw;
    FctR_ActIlluminantStates[ucIdx].boIlluminantStatus = sLedState.boIlluminantStatus[ucIdx];
    FctR_ActIlluminantStates[ucIdx].ucIlluminantName = sLedState.ucIlluminantFctName[ucIdx];
    if (FctR_ActIlluminantStates[ucIdx].unIlluminantErrState > 0U)
    {
      FctR_ActIlluminantStates[ucIdx].boIlFailureStatus = TRUE;
      if (FctR_ActIlluminantStates[ucIdx].ucIlluminantName == FCTR_CH_NAME_DRL_POS)
      {
        FctR_DRLIlluminantsErr |= (uint16)((uint16)1u << (uint16)(ucIdx));
      }
    }
  }

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  if ((FctR_ActIlluminantStates[14].boIlFailureStatus != FALSE) && ((FctR_TgtLgtReq.Req.Bits.biHB_Boost != 0U) || (FctR_TgtLgtReq.Req.Bits.biHB_FlashToPass != 0U) || (FctR_TgtLgtReq.Req.Bits.biHB_HighBeam != 0U)))
  {
    FctR_ActIlluminantStates[15].boIlFailureStatus = FctR_ActIlluminantStates[14].boIlFailureStatus;
    FctR_ActIlluminantStates[15].unIlluminantErrState = FctR_ActIlluminantStates[14].unIlluminantErrState;
  }
#endif
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Tgt_CheckLightFunctions_State
///
/// \descr  Check light functions failure based on the led channels failure
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_Tgt_CheckLightFunctions_State(void)
{
  FctR_StoreIlluminantFailureFunction();
  FctR_StoreIlluminantStatusFunction();
  //mentain TI status to active on falling edge
  FctR_KeepTiStatusOn();
}

//-----------------------------------------------------------------------------
/// \brief  FctR_StoreIlluminantFailureFunction
///
/// \descr  This function checks each Illuminant for failure and stores the 
///         failure status for the standard light functions
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_StoreIlluminantFailureFunction(void)
{
  //always start without failure
  uint32 ulFailureFunctionIlluminant = 0U; //bits representation

  for (uint8_fast ucIdxIl = 0U; ucIdxIl < FCTR_CFG_LOGLMP_MAX; ucIdxIl++)
  {
    if (FctR_ActIlluminantStates[ucIdxIl].ucIlluminantName != FCTR_CH_UNKNOWN_NAME)
    {
      if (FctR_ActIlluminantStates[ucIdxIl].boIlFailureStatus != FALSE)
      {
        FCTR_SET_BIT_U32(ulFailureFunctionIlluminant, FctR_ActIlluminantStates[ucIdxIl].ucIlluminantName);
      }
    }
  }

  FctR_sLightFailureStatus.boLb_State = (FCTR_CHECK_BIT_FCT_U32(ulFailureFunctionIlluminant, FCTR_LOW_BEAM_FUNCTION));
  FctR_sLightFailureStatus.boSbl_State= (FCTR_CHECK_BIT_FCT_U32(ulFailureFunctionIlluminant, FCTR_STATIC_BENDING_FUNCTION));
  FctR_sLightFailureStatus.boTi_State = (FCTR_CHECK_BIT_FCT_U32(ulFailureFunctionIlluminant, FCTR_TURN_INDICATOR_FUNCTION));
  FctR_sLightFailureStatus.boHb_State = (FCTR_CHECK_BIT_FCT_U32(ulFailureFunctionIlluminant, FCTR_HIGH_BEAM_FUNCTION));
  FctR_sLightFailureStatus.boGfHb_State = FctR_sLightFailureStatus.boHb_State;
  FctR_sLightFailureStatus.boDrl_State = (FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight != 0U) ? (FCTR_CHECK_BIT_FCT_U32(ulFailureFunctionIlluminant, FCTR_DAYTIME_RUNNING_AND_POSITION_FUNCTION)) : FALSE;
  FctR_sLightFailureStatus.boPos_State = (FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight != 0U) ? (FCTR_CHECK_BIT_FCT_U32(ulFailureFunctionIlluminant, FCTR_DAYTIME_RUNNING_AND_POSITION_FUNCTION)) : FALSE;;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_StoreIlluminantStatusFunction
///
/// \descr  This function checks the status of each Illuminant stores the 
///         light status for the standard light functions from the
///         assigned illuminant
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_StoreIlluminantStatusFunction(void)
{
  //always start without status
  uint32 ulStatusFunctionIlluminant = 0U; //bits representation

  for (uint8_fast ucIdxIl = 0U; ucIdxIl < FCTR_CFG_LOGLMP_MAX; ucIdxIl++)
  {
    //check for illuminant usage
    if (FctR_ActIlluminantStates[ucIdxIl].ucIlluminantName != FCTR_CH_UNKNOWN_NAME)
    {
      //check illuminant status
      if (FctR_ActIlluminantStates[ucIdxIl].boIlluminantStatus != FALSE)
      {
        //set light status
        FCTR_SET_BIT_U32(ulStatusFunctionIlluminant, FctR_ActIlluminantStates[ucIdxIl].ucIlluminantName);
      }
    }
  }

  //fillout light status
  FctR_sLightStatus.boLb_Status = (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_LOW_BEAM_FUNCTION));
  FctR_sLightStatus.boSbl_Status = (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_STATIC_BENDING_FUNCTION));
  FctR_sLightStatus.boTiBlink_Status = (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_TURN_INDICATOR_FUNCTION));
  FctR_sLightStatus.boHb_Status = (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_HIGH_BEAM_FUNCTION));
  FctR_sLightStatus.boGfHb_Status = FctR_sLightStatus.boHb_Status;
  FctR_sLightStatus.boDrl_Status = (FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight != 0U) ? (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_DAYTIME_RUNNING_AND_POSITION_FUNCTION)) : FALSE;
  FctR_sLightStatus.boPos_Status = (FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight != 0U) ? (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_DAYTIME_RUNNING_AND_POSITION_FUNCTION)) : FALSE;
  FctR_sLightStatus.boSM_Status = (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_SIDE_MARKER_FUNCTION));
  FctR_sLightStatus.boFog_Status = (FCTR_CHECK_BIT_FCT_U32(ulStatusFunctionIlluminant, FCTR_FOG_FUNCTION));
}
 
//-----------------------------------------------------------------------------
/// \brief  FctR_Tgt_HandleLgtFctFailure
///
/// \descr  Store the state of light functions that need to be sent as feedback
///         and turn off the light if failure is active. All constant vars are used as inputs
///         for Diag Window
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_Tgt_HandleLgtFctFailure(void) //check for FULL and ECO
{
  tsFctR_VehState     sVehState;
  tAdbOut             PxaModeMsg;
  boolean boAdbGfhb_Diag = FALSE; //check for camera faulty, invalid or loss of frame
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  STATIC_UT(boolean, boMxbFault, FALSE);
#endif
  STATIC_UT(tsFctR_LgtFctState, sDiagFeedback, { 0U });
  STATIC_UT_NOINIT(tsDiagFeedback_Cfg, asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS]);
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  STATIC_UT(boolean, aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS], { 0u });
#else
  STATIC_UT(boolean, aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS], { 0u });
#endif
  //check each light function which has a diag feeback
  for (uint8_fast ucDiag_Xx = 0u; ucDiag_Xx < FCTR_CFG_DIAG_FEEDBACK_MAX_LIGHTS; ucDiag_Xx++)
  {
    switch (ucDiag_Xx)
    {
    case FCTR_CFG_DIAG_FEEDBACK_LB:
    {
      const boolean boLbCmd = FctR_TgtPrep_Get_Lb_Cmd();
      const boolean boUnderVoltStatus = ((FctR_Get_UnderVoltageStatusDebounced() != FALSE) && (boLbCmd != FALSE)) ? TRUE : FALSE;
      const boolean boOverVoltStatus = ((FctR_Get_OverVoltageStatusDebounced() != FALSE) && (boLbCmd != FALSE)) ? TRUE : FALSE;
      //configuration
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_LB].boDiagEntryCmd = FctR_TgtPrep_Get_Lb_Cmd();
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_LB].boError = FctR_sLightFailureStatus.boLb_State;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_LB].cSelectTimer = FCTR_LB_FAULT_DETECTION;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_LB].ulTime = FCTR_LB_FAULT_DETECTION_TIME_MS;

      FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_LB], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_LB], FALSE);

      //store diag feedback
      if ((boUnderVoltStatus != FALSE) || (boOverVoltStatus != FALSE) || (aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_LB] != FALSE))
      {
        sDiagFeedback.bLb_Diag = 1u;
      }
      else
      {
        sDiagFeedback.bLb_Diag = 0u;
      }
    }
    break;
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
    case FCTR_CFG_DIAG_FEEDBACK_SBL:
    {
      const boolean boSblCmd = FctR_CheckSblCl_LightStatus();
      const boolean boUnderVoltStatus = ((FctR_Get_UnderVoltageStatusDebounced() != FALSE) && (boSblCmd != FALSE)) ? TRUE : FALSE;
      const boolean boOverVoltStatus = ((FctR_Get_OverVoltageStatusDebounced() != FALSE) && (boSblCmd != FALSE)) ? TRUE : FALSE;
      const boolean boSblClTimeoutStatus = FctR_TgtPrep_SblClTimeOutFrame();
      //configuration
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_SBL].boDiagEntryCmd = FctR_CheckSblCl_LightStatus();
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_SBL].boError = ((FctR_sLightFailureStatus.boSbl_State != FALSE) || (boSblClTimeoutStatus != FALSE)) ? TRUE : FALSE;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_SBL].cSelectTimer = FCTR_SBL_FAULT_DETECTION;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_SBL].ulTime = FCTR_SBL_FAULT_DETECTION_TIME_MS;
      //handle diag feedback
      FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_SBL], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_SBL], FALSE);

      //store diag feedback
      if ((boUnderVoltStatus != FALSE) || (boOverVoltStatus != FALSE) || (aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_SBL] != FALSE))
      {
        sDiagFeedback.bSbl_Diag = 1u;
      }
      else
      {
        sDiagFeedback.bSbl_Diag = 0u;
      }
    }
    break;

    case FCTR_CFG_DIAG_FEEDBACK_GFHB:
    {
      {
        // Get GFHB state
        (void)Rte_Read_ppsAdb_Out_sVal_0(&PxaModeMsg);
        // Get vehicle state
        (void)FctR_RteAccess_Read_VehNetState(&sVehState);
        const boolean boGfhbCmd = ((PxaModeMsg.State == FCTR_GFHB_STATE_ACTIVE || PxaModeMsg.State == FCTR_GFHB_STATE_CURTAIN_ON) && ((FctR_TgtLgtReq.Req.Bits.biHB_Boost != 0U) || (FctR_TgtLgtReq.Req.Bits.biHB_FlashToPass != 0U) || (FctR_TgtLgtReq.Req.Bits.biHB_HighBeam != 0U))) ? TRUE : FALSE;

        // Get Diagnostic Status from AdbMxb
        (void)Rte_Read_AdbMxb_Gfhb_Diag(&boAdbGfhb_Diag);
        //store mxb fault for TA_XX request
        switch (sVehState.eFctR_EtatReseauElec)
        {
        case eState_TA_NOMINAL:
        case eState_TA_DEGRADE:
        case eState_TA_SECU:
          boMxbFault = boAdbGfhb_Diag;
          break;
        default:
          break;
        }

        const boolean boArretGfHb_Status = (sVehState.eFctR_EtatPrincipSEV == eState_Stop) ? TRUE : FALSE;
        const boolean boGfhbFault = FctR_sLightFailureStatus.boGfHb_State;
        //configuration
        asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_GFHB].boDiagEntryCmd = (boGfhbCmd != FALSE) ? TRUE : FALSE;
        asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_GFHB].boError = boGfhbFault;
        asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_GFHB].cSelectTimer = FCTR_HB_FAULT_DETECTION;
        asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_GFHB].ulTime = FCTR_HB_FAULT_DETECTION_TIME_MS;
        if (FctR_sLightStatus.boGfHb_Status == FALSE/*(FctR_ucTgtLmpInt[15] == 0U && FctR_ucTgtLmpInt[14] == 0U)*/ && (boArretGfHb_Status != FALSE))
        {
          FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_GFHB], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_GFHB], TRUE);
          sDiagFeedback.bGfHb_Diag = 0U;
        }
        else
        {
          FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_GFHB], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_GFHB], FALSE);
          sDiagFeedback.bGfHb_Diag = (boMxbFault != FALSE) ? 1U : aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_GFHB];
        }
      }
    }
      break;
#endif
    case FCTR_CFG_DIAG_FEEDBACK_HB:
    {
      const boolean boHbCmd = ((FctR_TgtLgtReq.Req.Bits.biHB_Boost != 0U) || (FctR_TgtLgtReq.Req.Bits.biHB_FlashToPass != 0U) || (FctR_TgtLgtReq.Req.Bits.biHB_HighBeam != 0U)) ? TRUE : FALSE;

      //configuration
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_HB].boDiagEntryCmd = (boHbCmd != FALSE) ? TRUE : FALSE;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_HB].boError = FctR_sLightFailureStatus.boHb_State;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_HB].cSelectTimer = FCTR_HB_FAULT_DETECTION;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_HB].ulTime = FCTR_HB_FAULT_DETECTION_TIME_MS;

      //handle diag feedback
      FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_HB], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_HB], FALSE);
      //store diag feedback
      sDiagFeedback.bHb_Diag = aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_HB];
    }
    break;
    case FCTR_CFG_DIAG_FEEDBACK_POS:
    {
      const boolean boPosCmd = FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight != 0U ? TRUE : FALSE;
      //configuration
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_POS].boDiagEntryCmd = boPosCmd;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_POS].boError = FctR_sLightFailureStatus.boPos_State;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_POS].cSelectTimer = FCTR_POS_FAULT_DETECTION;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_POS].ulTime = FCTR_POS_FAULT_DETECTION_TIME_MS;
      //handle diag feedback
      FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_POS], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_POS], FALSE);
      //store diag feedback
      sDiagFeedback.bPos_Diag = aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_POS];
    }
    break;
    case FCTR_CFG_DIAG_FEEDBACK_DRL:
    {
      const boolean boDrlCmd = (FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight != 0U) ? TRUE : FALSE;
      //configuration
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_DRL].boDiagEntryCmd = boDrlCmd;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_DRL].boError = FctR_sLightFailureStatus.boDrl_State;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_DRL].cSelectTimer = FCTR_DRL_FAULT_DETECTION;
      asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_DRL].ulTime = FCTR_DRL_FAULT_DETECTION_TIME_MS;
      //handle diag feedback
      FctR_DiagFeedback(&asDiagFeedback_Cfg[FCTR_CFG_DIAG_FEEDBACK_DRL], &aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_DRL], FALSE);
      //store diag feedback
      sDiagFeedback.bDrl_Diag = aboDiagFeedback[FCTR_CFG_DIAG_FEEDBACK_DRL];
    }
    break;
    default:
      break;
    }

    // Turn off the affected light functions
    FctR_Tgt_LgtFctFailureReaction(); //only Fbit
    //set ti state failure
    sDiagFeedback.bTi_Diag = FctR_sLightFailureStatus.boTi_State;
    //write TI failure status
    (void)Rte_Write_FctR_TiFailureStatus(&FctR_sLightFailureStatus.boTi_State);
    // Write light functions state (OK/NOK)
    (void)FctR_RteAccess_Write_LgtFctState(sDiagFeedback);
  }
}// PRQA S 5324,5330 1     // Function is maintainable and well-structured

//-----------------------------------------------------------------------------
/// \brief Matrix FctR_DiagFeedback distribution with ramp 
///
/// \descr This function handle diag feedback based on cfg inputs
///         
/// \param  *psDiagSettings, *pboDiagFeedback, boForceErrReset - force error reset should be applicable only for 
///  GFHB function when few precondition are met (Arret status = true and last 2 illuminats are off)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_DiagFeedback(tsDiagFeedback_Cfg *psDiagSettings, boolean *pboDiagFeedback, boolean boForceErrReset)
{
  TIMER ulTmrTimeOut = 0U;

  //check for entry command
  if (psDiagSettings->boDiagEntryCmd != FALSE)
  {
    //in case the previous state has been OFF (psDiagSettings->boPrvCmd = TRUE), wait 200ms to confirm the failure and reset psDiagSettings->boPrvCmd to FALSE
    if (psDiagSettings->boPrvCmd != FALSE)
    {
      //start timer
      ulTmrTimeOut = FctR_CtrlDelayStatus(TRUE, psDiagSettings->ulTime, psDiagSettings->cSelectTimer);
      psDiagSettings->boPrvCmd = (ulTmrTimeOut == FCTR_IS_TIMEOUT) ? FALSE : psDiagSettings->boPrvCmd;
      if (psDiagSettings->boPrvCmd == FALSE)
      {
        //reset timer
        ulTmrTimeOut = FctR_CtrlDelayStatus(FALSE, psDiagSettings->ulTime, psDiagSettings->cSelectTimer);
        //store electrical error or other errors (as TRUE)
        *pboDiagFeedback = (psDiagSettings->boError == FALSE) ? FALSE : *pboDiagFeedback;
      }
    }
    else
    {
      //store electrical error or other errors (as TRUE)
      *pboDiagFeedback |= (psDiagSettings->boError != FALSE) ? TRUE : *pboDiagFeedback;
    }
  }
  else
  {
    //store the current state of this lightfunction
    psDiagSettings->boPrvCmd = TRUE;
    *pboDiagFeedback = (boForceErrReset != FALSE) ? FALSE : *pboDiagFeedback;
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Get_UnderVoltageStatusDebounced
///
/// \descr  This function return under voltage status for more than 12s (TRUE) and
///         2s for healing (FALSE)
///
/// \param  void
///
/// \return boolean : TRUE = undervoltage detected; FALSE = no UV
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_Get_UnderVoltageStatusDebounced(void)
{
  boolean boUvStatus = FALSE;
  (void)FctR_RteAccess_Read_UV_Status(&boUvStatus);
  return boUvStatus;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Get_OverVoltageStatusDebounced
///
/// \descr  This function return over voltage status for more than 12s (TRUE) and
///         2s for healing (FALSE)
///
/// \param  void
///
/// \return boolean : TRUE = overvoltage detected; FALSE = no OV
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_Get_OverVoltageStatusDebounced(void)
{
	boolean boOvStatus = FALSE;
	(void)FctR_RteAccess_Read_OV_Status(&boOvStatus);
	return boOvStatus;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_Tgt_LgtFctFailureReaction
///
/// \descr  Apply failure reaction for affected light functions
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_Tgt_LgtFctFailureReaction(void)
{
  uint8_fast   ucLogLmpIdx;
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  static boolean aboIlLightStatus[FCTR_CFG_LOGLMP_MAX] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
#else
  static boolean aboIlLightStatus[FCTR_CFG_LOGLMP_MAX] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
#endif

  for (ucLogLmpIdx = 0u; ucLogLmpIdx < FCTR_CFG_LOGLMP_MAX; ucLogLmpIdx++)
  {
    if ((Cod_ErrorImpactB(FctR_ucTgtLgtHighPrio[ucLogLmpIdx], (uint8)ucLogLmpIdx) != 0u) && (FctR_ActIlluminantStates[ucLogLmpIdx].boIlFailureStatus != FALSE))//(FCTR_GET_LGT_FCT_BIT(FctR_ucTgtLgtHighPrio[ucLogLmpIdx], FctR_LgtFctFailure.ulRaw) != 0u))
    {
      if ((aboIlLightStatus[ucLogLmpIdx] != FctR_ActIlluminantStates[ucLogLmpIdx].boIlluminantStatus) && (FCTR_GET_LGT_FCT_BIT(FctR_ucTgtLgtHighPrio[ucLogLmpIdx], FctR_LgtFctFailureFBit.ulRaw) == 0u) && (FctR_ucTgtLgtHighPrio[ucLogLmpIdx] < FCTR_CFG_LGTFCT_MAX))
      {
        //store the affected light function
        FctR_LgtFctFailureFBit.ulRaw |= (uint32)((uint32)1u << (uint32)FctR_ucTgtLgtHighPrio[ucLogLmpIdx]);
      }
    }

    aboIlLightStatus[ucLogLmpIdx] = FctR_ActIlluminantStates[ucLogLmpIdx].boIlluminantStatus;
  }
}

//-----------------------------------------------------------------------------
/// \brief FctR_ProccessAimingMode - Matrix pixel distribution with ramp 
///
/// \descr This function will go thorugh each state of aiming mode , start by blinking 
///        and then keep function active
///         
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_ProccessAimingMode(void)
{
 STATIC_UT(uint8, ucCounter, 0u);
 STATIC_UT(uint32, ulTimerStart, 0u); STATIC_UT(uint32, ulTimeElapsed, 0u);
 boolean boAimingStatus = FctR_TgtPrep_GetAimingMode();


 // call current state 
 switch (FctR_eAimingMode)
 {
  //default case when aiming mode is turned off
 case eAimingOff:
 {

  if (boAimingStatus != FALSE)
  {
   FctR_eAimingMode = eBlinkOn;
   // start timer
   ulTimerStart = 0u;

  }
  else
  {
   // do nothing
  }
  break;
 }

 case eBlinkOn:
 {
  ulTimerStart = (ulTimerStart == 0u) ? TimerGetTick() : ulTimerStart;

  if (boAimingStatus == FALSE)
  {
   // reset variables
   FctR_eAimingMode = eAimingOff;
   ucCounter = 0u;
   ulTimerStart = 0u;
  }
  else
  {
   ulTimeElapsed = TimerGetTimeSince(ulTimerStart);

   // if timer expired go back to blink off or post blink state if counter is bigger than threshold
   if (ulTimeElapsed > FT_MSEC(FctR_ulAimBlinkTime))
   {
    ucCounter++;
    FctR_eAimingMode = (ucCounter >= FCTR_AIM_COUNTER) ? eAimOn : eBlinkOff;
    // restart timer
    ulTimerStart = 0u; 
   }
   else
   {
    // don t reset
   }
  }
  break;
 }

 case eBlinkOff:
 {

  ulTimerStart = (ulTimerStart == 0u) ? TimerGetTick() : ulTimerStart;


  if (boAimingStatus == FALSE)
  {
   FctR_eAimingMode = eAimingOff;
   ucCounter = 0u;
   // restart timer
   ulTimerStart = 0u;
  }
  else
  {
   ulTimeElapsed = TimerGetTimeSince(ulTimerStart);

   if (ulTimeElapsed > FT_MSEC(FctR_ulAimBlinkTime))
   {
    FctR_eAimingMode = (ucCounter >= FCTR_AIM_COUNTER) ? eAimOn : eBlinkOn;
    // restart timer
    ulTimerStart = 0u;
   }
   else
   {
    // don t reset
   }
  }
  break;
 }
 case eAimOn:
 {
  if (boAimingStatus == FALSE)
  {
   FctR_eAimingMode = eAimingOff;
   ucCounter = 0u;
  }
  else
  {
    // leave current distribution
  }
  break;

 }
 default:
  break;

 }

}
//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt
///
/// \descr  New target values for light functions received.
///         Read RTE input values and compute RTE output values.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_TgtLgt(void)
{
  // Update actual intensities
  FctR_ActLgt_Update();
  // Get actual Leds state
  FctR_Tgt_GetActLedState();
  // Read light function requests
#if (FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  FctR_TgtLgt_Prep_Full();
#else
  FctR_TgtLgt_Prep_Eco();
#endif
  // Store light requests locally
  FctR_TgtLgt_StorePrep();
  // Priorize light functions
  FctR_TgtLgt_Prio();
  // Check light functions state
  FctR_Tgt_CheckLightFunctions_State();
  // Sustain light functions
  FctR_TgtLgt_Sustain();
  // Handle light functions failure
  FctR_Tgt_HandleLgtFctFailure();
  // proccess aiming mode request
  FctR_ProccessAimingMode();
  // Write output values
  FctR_TgtLgt_Output();

  // PRQA S 5324 1     // Function is maintainable and well-structured
}

//-----------------------------------------------------------------------------
/// \brief  FctR_CtrlDelayStatus
///
/// \descr  This function configures the selected timer with the request and timeout
///         detection time  
///
/// \param  boReqInput      : input request (start/reset timer)
/// \param  ulTimeMs        : timer configuration ( timeout detection)
/// \param  scTiTimerSel    : timer selection
///
/// \return  uint8 : timer timeout status (TRUE : timeout occured)
//-----------------------------------------------------------------------------
STATIC_AL uint8 FctR_CtrlDelayStatus(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel)
{
  uint8 ucTimersDelayStatus = FCTR_INVALID_TIMER_CONFIG;
  if (scTiTimerSel < FCTR_NUMBER_OF_TIMERS)
  {
    FctR_sTimerCfg[scTiTimerSel].ulTimeMs_Input = ulTimeMs;
    FctR_sTimerCfg[scTiTimerSel].boReq_Input = boReqInput;
    ucTimersDelayStatus = FctR_HandleDelayStatus(FctR_sTimerCfg, scTiTimerSel);
  }
  return ucTimersDelayStatus;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_HandleDelayStatus
///
/// \descr  This function return TimeOut = TRUE based on sTimersCfg Configurations
///
/// \param   *sTimersCfg, scTimerSel
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_HandleDelayStatus(tsFctR_TimerCfg *sTimersCfg, const sint8 scTimerSel)
{
  // Input request (start timer or reset)
  if (sTimersCfg[scTimerSel].boReq_Input != FALSE)
  {
    // Start Timer
    if (sTimersCfg[scTimerSel].boStartStopTimer == FALSE)
    {
      sTimersCfg[scTimerSel].ulCommandStart = UTILTIME_TIMER_START(UTILTIME_MSEC(sTimersCfg[scTimerSel].ulTimeMs_Input));
      sTimersCfg[scTimerSel].boStartStopTimer = TRUE;
    }
  }
  else
  {
    // Reset timer and reinit all timers values
    sTimersCfg[scTimerSel].boTimeOut = FALSE;
    sTimersCfg[scTimerSel].boStartStopTimer = FALSE;
    sTimersCfg[scTimerSel].ulCommandStart = 0U;
  }

  // Timer still running ?
  if (sTimersCfg[scTimerSel].boStartStopTimer != FALSE)
  {
    // Let it run
    sTimersCfg[scTimerSel].boTimeOut = UTILTIME_TIMER_TIMEOUT(sTimersCfg[scTimerSel].ulCommandStart);
  }

  return sTimersCfg[scTimerSel].boTimeOut;
}

// EOF

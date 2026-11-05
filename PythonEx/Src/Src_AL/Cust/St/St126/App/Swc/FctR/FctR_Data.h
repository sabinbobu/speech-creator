#ifndef __FCTRDATA_H__
#define __FCTRDATA_H__

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
/// \file  FctR_Data.h
///
/// \brief  
///
/// \descr  
///
/// \author Ralf Sondershaus  (sor2rt)
///         mailTo:ralf.sondershaus@al-lighting.com       
//-----------------------------------------------------------------------------

#include "FctR_Types.h"
#include <Rte/RteCommonTypes.h>
//#include <Util/UtilTime.h>
#include <CodM.h>

//=============================================================================
// extern variables
//=============================================================================

// LMM basic state
extern CONST_AL tsFctR_LmmInitBlock FctR_LmmInit;

// NVM Parameter
extern CONST_AL tNvmPara_CodingArea* FctR_pCodingArea;
extern CONST_AL tNvmPara_LmmABlock*  FctR_pLmmABlock;
extern uint8 FctR_ucCodingState;

// 1 = LogLmp is used by this light function (Lmm[LgtFct].ucIntensity > 0), 0 = LogLmp is not used by this light function (Lmm[LgtFct].ucIntensity == 0)
extern tuFctR_LogLmp FctR_UsageLogLmpTable[FCTR_CFG_LGTFCT_MAX];
// 1 = LogLmp is configured to be accessed by the LgtFct (intensity > 0 OR prio < 15 OR F = 1 OR A = 1), 0 = LogLmp is not configured to be accessed by the LgtFct
extern tuFctR_LogLmp FctR_AccessLogLmpTable[FCTR_CFG_LGTFCT_MAX];

//=============================================================================
// defines
//=============================================================================
/// UNQUALIFIED after startup until VALID or INVALID is received
#define FCTR_CODING_UNQUALIFIED   0U
#define FCTR_CODING_VALID         1U
#define FCTR_CODING_INVALID       2U

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0U)
#define FCTR_AFS_TRANSITION_TIME_RESOLUTION        5U
#endif

// ----------------------------------------------------------------------------
/// Get the bit pattern for a Light Functions
// ----------------------------------------------------------------------------
#define FCTR_GET_TGT_LGT_BIT_PTRN(LgtFct)    (((LgtFct) < 32U) ? ((uint32)1u << (uint32)(LgtFct)) : 0U)

#define FCTR_GET_LGT_FCT_BIT(LgtFct,Raw)    ((Raw) & (uint32)FCTR_GET_TGT_LGT_BIT_PTRN(LgtFct))
#define FCTR_SET_LGT_FCT_BIT(LgtFct,Raw)    ((Raw) = (Raw) |  FCTR_GET_TGT_LGT_BIT_PTRN(LgtFct))
#define FCTR_CLR_LGT_FCT_BIT(LgtFct,Raw)    ((Raw) = (Raw) & (uint32)~FCTR_GET_TGT_LGT_BIT_PTRN(LgtFct))

// ----------------------------------------------------------------------------
/// Get the target request for Light Function given the raw value of all requests (e.g. tuFctR_LgtFct::ulRaw)
// ----------------------------------------------------------------------------
#define FCTR_GET_TGT_LGT_REQ(LgtFct,Raw)    FCTR_GET_LGT_FCT_BIT(LgtFct,Raw)
#define FCTR_SET_TGT_LGT_REQ(LgtFct,Raw)    FCTR_SET_LGT_FCT_BIT(LgtFct,Raw)
#define FCTR_CLR_TGT_LGT_REQ(LgtFct,Raw)    FCTR_CLR_LGT_FCT_BIT(LgtFct,Raw)

// ----------------------------------------------------------------------------
/// Get the bit pattern for a Logical Lamp
// ----------------------------------------------------------------------------
#define FCTR_GET_LOG_LMP_BIT_PTRN(LogLmp)    (uint16)((uint16)1u << (uint16)(LogLmp))

#define FCTR_GET_LOG_LMP_BIT(LogLmp,Raw)    ((Raw) & FCTR_GET_LOG_LMP_BIT_PTRN(LogLmp))
#define FCTR_SET_LOG_LMP_BIT(LogLmp,Raw)    ((Raw) = (tLogLmpStg) ((Raw) |  FCTR_GET_LOG_LMP_BIT_PTRN(LogLmp)))
#define FCTR_CLR_LOG_LMP_BIT(LogLmp,Raw)    ((Raw) = (tLogLmpStg) ((Raw) & (uint16)~FCTR_GET_LOG_LMP_BIT_PTRN(LogLmp)))

// ----------------------------------------------------------------------------
/// Get the basic state of an LMM cell
// ----------------------------------------------------------------------------
#define FIX_CELL(LogLmp)   FctR_LmmInit.sLmmCell[LogLmp]

static inline uint8 Fix_IntensityI(tAppLogLamp LogLmp)   { return FIX_CELL(LogLmp).ucPower; }
static inline uint8 Fix_PriorityI(tAppLogLamp LogLmp)    { return FIX_CELL(LogLmp).biPriority; }
//static inline uint8 Fix_RampTypeI(tAppLogLamp LogLmp)  { return Fix_CellI(LogLmp).biRampType; }
static inline uint8 Fix_TimeOnI(tAppLogLamp LogLmp)      { return FIX_CELL(LogLmp).ucTimeOn; }
static inline uint8 Fix_TimeOffI(tAppLogLamp LogLmp)     { return FIX_CELL(LogLmp).ucTimeOff; }
static inline uint8 Fix_ErrorImpactI(tAppLogLamp LogLmp) { return FIX_CELL(LogLmp).biErrorImpact; }
static inline uint8 Fix_ActiveI(tAppLogLamp LogLmp)      { return FIX_CELL(LogLmp).biActive; }

// ----------------------------------------------------------------------------
/// Get the coding values of an LMM cell
// ----------------------------------------------------------------------------
#define Cod_CellB(LgtFct, LogLmp)  FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[LgtFct].cell[LogLmp].ucIdx]
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
#define Cod_AfsTransitionTime(void) FctR_pCodingArea->PXA.DimmingTimes.ucCOUNTRY_TO_ADVERSEW
static inline uint8 Cod_AfsTransitionDim(void) { return (Cod_AfsTransitionTime() * FCTR_AFS_TRANSITION_TIME_RESOLUTION); } //rescale from 100ms resolution to 20ms. See coding param. tools
#endif

static inline uint8 Cod_IntensityB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)   { return Cod_CellB(LgtFct, LogLmp).ucPower; }
static inline uint8 Cod_PriorityB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)    { return Cod_CellB(LgtFct, LogLmp).biPriority; }
static inline uint8 Cod_RampTypeB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)    { return Cod_CellB(LgtFct, LogLmp).biRampType; }
static inline uint8 Cod_TimeOnB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)      { return Cod_CellB(LgtFct, LogLmp).ucTimeOn; }
static inline uint8 Cod_TimeOffB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)     { return Cod_CellB(LgtFct, LogLmp).ucTimeOff; }
static inline uint8 Cod_ErrorImpactB(tAppLightFunction LgtFct, tAppLogLamp LogLmp) { return Cod_CellB(LgtFct, LogLmp).biErrorImpact; }
static inline uint8 Cod_ActiveB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)      { return Cod_CellB(LgtFct, LogLmp).biActive; }

//=============================================================================
// inline functions
//=============================================================================

// Return TRUE if priority ucPrio1 is higher than priority ucPrio2.
static inline boolean FctR_HigherPrio(uint8 ucPrio1, uint8 ucPrio2)
{
  return (ucPrio1 < ucPrio2 ? TRUE : FALSE);
}

// Return TRUE if ucLgtFct is a valid index
static inline boolean FctR_LgtFctIndexCheck(tAppLightFunction ucLgtFct)
{
  return (ucLgtFct < FCTR_CFG_LGTFCT_MAX);
}

// Return TRUE if the LogLmp is configured to be accessed by the LgtFct (intensity > 0 OR prio < 15 OR F = 1 OR A = 1)
static inline boolean FctR_AccessLogLmp(tAppLightFunction LgtFct, tAppLogLamp LogLmp)
{
  return FCTR_GET_LOG_LMP_BIT(LogLmp, FctR_AccessLogLmpTable[LgtFct].Raw) != 0;
}

// Return TRUE if the LogLmp is used by the LgtFct
static inline boolean FctR_UsageLogLmpB(tAppLightFunction LgtFct, tAppLogLamp LogLmp)
{
  return FCTR_GET_LOG_LMP_BIT(LogLmp, FctR_UsageLogLmpTable[LgtFct].Raw) != 0;
}

// Return TRUE if the LogLmp is used by the LgtFct
static inline boolean FctR_UsageLogLmp(tAppLightFunction LgtFct, tAppLogLamp LogLmp)
{
  boolean boRet;

  if (FctR_LgtFctIndexCheck(LgtFct))
  {
    boRet = FctR_UsageLogLmpB(LgtFct, LogLmp);
  }
  else
  {
    boRet = FALSE;
  }
  return boRet;
}

// Return DELAY_TI_NOT_REQUESTED time
static inline uint16 FctR_GetDelayTiNotRequested(void)
{
  return FctR_pCodingArea->Led1.BasicFunctions.unDELAY_TI_NOT_REQUESTED;
}

///// UNQUALIFIED after startup until VALID or INVALID is received
//#define FCTR_CODING_UNQUALIFIED   0
//#define FCTR_CODING_VALID         1
//#define FCTR_CODING_INVALID       2
//
//INLINE uint8 FctR_VehicleType     (void)       { return FctR_pCodingArea->Sys.VariantSelection.ucVehicleType; }
//
///// Access to NVM Parameters (coding parameters)
//INLINE uint8 Cod_WL_OffDelay      (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_OffDelay;            }
//INLINE uint8 Cod_WL_FadeTime      (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_FadeTime;            }
//INLINE uint8 Cod_WL_WakeupDelay   (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_WakeupDelay;         }
//INLINE uint8 Cod_WL_DrlTimeOn     (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_DrlTimeOn;           }
//INLINE uint8 Cod_WL_DrlDuration   (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_DrlDuration;         }
//INLINE uint8 Cod_WL_DrlTimeOff    (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_DrlTimeOff;          }
//INLINE uint8 Cod_WL_ShutdownDelay (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_ShutdownDelay;       }
//INLINE uint8 Cod_WL_PosTimeOff    (void)       { return FctR_pCodingArea->LmmX.WL.ucWL_PosTimeOff;          }
//INLINE uint8 Cod_WL_DrlPos_Channel(uint32 ul)  { return FctR_pCodingArea->LmmX.WL.aucWL_DrlPos_Channel[ul]; }
//INLINE uint8 Cod_WL_Drl_Power     (uint32 ul)  { return FctR_pCodingArea->LmmX.WL.aucWL_Drl_Power     [ul]; }
//INLINE uint8 Cod_WL_Pos_Power     (uint32 ul)  { return FctR_pCodingArea->LmmX.WL.aucWL_Pos_Power     [ul]; }
//
//// LM name mapping
//INLINE tCfgOutputName Cod_NameMapping(uint32 ul)  { return (tCfgOutputName)(FctR_pCodingArea->Led1.LedLMNameMapping.LM_Name[ul]); }

boolean FctR_Cod_Valid(void);

//INLINE uint8   Cod_Led1_LogLmpName(tAppLogLamp LogLamp)   { return ((const uint8 *) &(FctR_pCodingArea->Led1.LedLMNameMapping.LM1_Name))[LogLamp]; }

//INLINE bool Cod_Afs123Error(void)  { return ((FctR_pCodingArea->CarConfigNvM.ucAfs123Fitted == 0)  /* not supported */
//                                          || (FctR_pCodingArea->CarConfigNvM.ucAfs123Fitted == 3)  /* Error         */ ) ? true : false; }

///// Failure indication bits
//extern tFctRStateBits FctR_FailureIndication;
//
///// =1 if a logical lamp must be switched off due to a failure indication of logical lamps
//extern tuFctR_LogLmp FctR_FailureReactionLogLmp;
//
///// =1 if light function must be switched off due to failure indications of mandatory logical lamps. 
///// Possibly locked until environmental conditions have changed or a new request has been made.
//extern tuFctR_LgtFct FctR_FailureReactionLogLmpBTgtLgt;
///// =1 if state information (via CAN) must be set to ERROR. 
///// Possibly locked until environmental conditions have changed or a new request has been made.
//extern tuFctR_LgtFct FctR_FailureReactionLogLmpBActLgt;
///// =1 if DTC must be set to FAILED.
///// =0 if DTC is not to be set to FAILED (but it could still be set to PASSED).
///// Possibly locked until environmental conditions have changed or a new request has been made.
//extern tuFctR_LgtFct FctR_FailureReactionLogLmpBDemFailed;
//extern tuFctR_LgtFct FctR_FailureReactionLogLmpBDemFailedPrev;
///// =1 if DTC must be set to PASSED.
///// =0 if DTC is not to be set to PASSED (but it could still be set to FAILED).
///// Possibly locked until environmental conditions have changed or a new request has been made.
//extern tuFctR_LgtFct FctR_FailureReactionLogLmpBDemPassed;
//extern tuFctR_LgtFct FctR_FailureReactionLogLmpBDemPassedPrev;
///// =0 if DTC is set because a mandatory logical lamp fails.
///// =1 if DTC is set because a used logical lamp fails.
///// Depending on CCM parameters.
//extern tuFctR_LgtFct FctR_FailureIndicationLogLmpBDemMask;
//
///// =0 if Cod_ActiveA/B(LgtFct, LogLamp) = 0
///// =1 if Cod_ActiveA/B(LgtFct, LogLamp) = 1
///// Depending on LMM.
///// Calculated from coding data via #FctR_CalculateActiveLogLmpAMask, #FctR_CalculateActiveLogLmpBMask.
////extern tuFctR_LgtFct FctR_ActiveLogLmpBMask[FCTR_CFG_LOGLMP_MAX];
//
///// A bit for each light function indicating if a light function was switched on
///// 1 = light function is switched on
///// 0 = light function is not switched on (is either on or off or switched off)
//extern tuFctR_LgtFct FctR_TgtLgtReqBChangeToActive;
//extern tuFctR_LgtFct FctR_TgtLgtReqBChangeToActiveTgtLgt;
//extern tuFctR_LgtFct FctR_TgtLgtReqBChangeToActiveTgtLgtMand;
//extern tuFctR_LgtFct FctR_TgtLgtReqBChangeToActiveActLgt;
//extern tuFctR_LgtFct FctR_TgtLgtReqBChangeToActiveDisableLogLmpLgtFct;
//
///// A bit for each light function indicating if a light function has higher priority than POLI1, POLI2, POLI3
///// for a channel which is used by POLI and BLINKEN2
///// 1 = light function has higher (or equal) priority
///// 0 = light function has lower priority
//extern tuFctR_LgtFct FctR_HigherPrioPoliB[3];
//
///// =0 if no logical lamp has ramp RAMP_HART
///// =1 if at least one logical lamp has ramp RAMP_HART
///// Depending on LMM.
///// Calculated from coding data via #FctR_CheckRampHartA, #FctR_CheckRampHartB.
//extern tuFctR_LgtFct FctR_RampHartB;
//
///// Return TRUE if the light function must be switched off due to a failure of a (mandatory) logical lamp
//INLINE boolean FctR_FailureReactionLogLmpBTgtLgt_(tAppLightFunction LgtFct) { return FctR_GetLgtFctBit(LgtFct, FctR_FailureReactionLogLmpBTgtLgt.ulRaw) != 0; }
//
//INLINE boolean FctR_FailureReactionLogLmpBActLgt_(tAppLightFunction LgtFct) { return FctR_GetLgtFctBit(LgtFct, FctR_FailureReactionLogLmpBActLgt.ulRaw) != 0; }
//INLINE boolean FctR_FailureReactionLogLmpBActLgts(tuFctR_LgtFct      LgtFctMask) { return (LgtFctMask.ulRaw        & FctR_FailureReactionLogLmpBActLgt.ulRaw) != 0; }
//
///// A logical lamp can be disabled while a light function is requested (delayed switch on, vehicle speed thresholds, ...)
///// - 1 = Logical lamp is disabled for light function (due to delayed switch on, vehicle speed thresholds, ...)
///// - 0 = Logical lamp is enabled for light function 
//extern tuFctR_LogLmp FctR_DisableLogLmpLgtFctB[FCTR_CFG_LGTFCT_MAX];
//
///// A logical lamp can be disabled while a light function is requested (delayed switch on, vehicle speed thresholds, ...)
///// - TRUE  = Logical lamp is disabled for light function (due to delayed switch on, vehicle speed thresholds, ...)
///// - FALSE = Logical lamp is enabled for light function 
//INLINE boolean FctR_DisableLogLmpLgtFctB_(tAppLightFunction LgtFct, tAppLogLamp LogLamp)  { return FctR_GetLogLmpBit(LogLamp, FctR_DisableLogLmpLgtFctB[LgtFct].Raw) != 0; }
//
///// Reaction tables for light functions A/B: must a light function be switched off due to a failure of a logical lamp?
///// The reaction tables must be calculated once when new parameters are received (ErrorImpact bit of LMM)
//extern tuFctR_LogLmp FctR_FailureReactionLogLmpBTable[FCTR_CFG_LGTFCT_MAX];
//
///// Initialize internal variables if a (new) valid coding has been received
//void FctR_InitValidCoding(void);
//
///// A bit for each light function indicating if at least one mandatory logical lamp is defective
///// - 1 = at least one mandatory logical lamp is certainly defective
///// - 0 = for each mandatory logical lamp holds: either the logical lamp is working properly or its state is unknown
//extern tuFctR_LgtFct FctR_FailureIndicationLogLmpMandB;
///// A bit for each light function indicating if at least one used logical lamp is defective
///// - 1 = at least one used logical lamp is certainly defective
///// - 0 = for each used logical lamp holds: either the logical lamp is working properly or its state is unknown
//extern tuFctR_LgtFct FctR_FailureIndicationLogLmpUsedB;
///// A bit for each light function indicating if all logical lamps used by this light function are defective
///// - 1 = all used logical lamps are certainly defective
///// - 0 = for at least one used logical lamp holds: either the logical lamp is working properly or its state is unknown
//extern tuFctR_LgtFct FctR_FailureIndicationLogLmpAllB;
//
///// A bit for each light function indicating if the state of all mandatory logical lamps is known
///// - 1 = the state of all mandatory logical lamps is known certainly
///// - 0 = the state of at least one mandatory logical lamp is unknown
//extern tuFctR_LgtFct FctR_FailureIndicationLogLmpStateMandB;
///// A bit for each light function indicating if the state of all used logical lamps is known
///// - 1 = the state of all used logical lamps is known certainly
///// - 0 = the state of at least one used logical lamp is unknown
//extern tuFctR_LgtFct FctR_FailureIndicationLogLmpStateAllB;
//
///// [Counter] If the bit 'error reset' is set to 1, the actual state of the LED drivers must not be evaluated for this time
//extern uint8 FctR_ucTgtErrorReset[FCTR_CFG_LOGLMP_MAX];
//
///// 1 = LogLmp is switched on (intensity > 0), 0 = LogLmp is switched off (intensity == 0).
///// Relies on actual values of LED drivers (received via actual path).
//extern tuFctR_LogLmp FctR_ActiveLogLmp;
//
///// 1 = LogLmp is used by this light function (Lmm[LgtFct].ucIntensity > 0), 0 = LogLmp is not used by this light function (Lmm[LgtFct].ucIntensity == 0)
extern tuFctR_LogLmp FctR_UsageLogLmpBTable[FCTR_CFG_LGTFCT_MAX];
///// 1 = LogLmp is configured to be accessed by the LgtFct (intensity > 0 OR prio < 15 OR F = 1 OR A = 1), 0 = LogLmp is not configured to be accessed by the LgtFct
//extern tuFctR_LogLmp FctR_AccessLogLmpBTable[FCTR_CFG_LGTFCT_MAX];

#endif // __FCTRDATA_H__

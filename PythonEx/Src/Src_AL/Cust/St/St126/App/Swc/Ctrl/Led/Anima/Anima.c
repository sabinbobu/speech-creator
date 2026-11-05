/// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Anima.c
///
/// \brief core module for Animations
///
/// \author Georgiana Sevastre (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <AL_Helper.h>
#include <RteCommonTypes.h>
#include "Anima.h"
#include "Anima_RteAccess.h"
#include "AnimMa_Cod.h"
#include "Anima_CodPrj.h"
#include "Anima_Cfg.h"
#include "AnimMa_Types.h"
#include "UtilDebounce.h"

#ifndef UNIT_TEST
#include <Rte.h>
#endif

//=============================================================================
// defines
//=============================================================================

/// Priority if an animation is running
#define PRIORITY_ANIMATION_RUNNING                  TRUE
/// Priority if animations are not running
#define PRIORITY_ANIMATION_NONE                     FALSE
#define TI_SCROLLING                                0U
#define TI_SCROLLING_ANIMMA                         27U
#define MASK1                                       1u
#define MASK2                                       2u
#define MASKSHIFT                                   8u
//=============================================================================
// variables
//=============================================================================

/// Timer for delay TI not requested
STATIC_AL tUtilDebounceControl Anima_TgtPrep_TiDelayTimer;

//=============================================================================
// functions prototypes
//=============================================================================
STATIC_AL teRte_ExtLightingAnimationReq Anima_CheckInputs(void);
STATIC_AL uint8                         Anima_GetInputs(void);
STATIC_AL tsRte_TgtAniArr               Anima_TgtAniArr;
STATIC_AL tsRte_TgtAniArrScr            Anima_Scrolling = { 0 };
STATIC_AL void                          Anima_TgtPrep_Init(void);
STATIC_AL boolean                       Anima_ReadFrontTurnIndicatorCmd(void);

//-----------------------------------------------------------------------------
/// link to animation target intensities
/// unTgtAni: [1/32768 %] 0 = 0%, 0x8000 = 100%, Array of intensities for the 103 animation intensities
/// boPriority: [0 - 15] 0...14: animation is active, PRIORITY_ANIMATION_NONE (FALSE): animation is not active
//-----------------------------------------------------------------------------
tsRte_TgtAniArr* Anima_Tgt(void)
{
  return &Anima_TgtAniArr;
}

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// Cacluate 16 bit intensity value [1/32768 %] from 8 bit intensity value [%]
//-----------------------------------------------------------------------------
STATIC_AL inline uint16 Anima_Percent8_to_Percent16(uint8 ucInt)
{
  return (ucInt > 0u) ? ((uint16)((32768u * (uint32)ucInt) / 100u)) : (0u);
}

//-----------------------------------------------------------------------------
/// Read animation request from RTE and start or stop animations accordingly.
/// Return true if an animation is started or if an animation is stopped.
//-----------------------------------------------------------------------------
STATIC_AL bool Anima_StartStopAnimation(void)
{
  static teRte_ExtLightingAnimationReq eReqPrev = eExtLightingAnimationReq_None;
  teRte_ExtLightingAnimationReq eReq;
  bool                          bRet = false;
  //check all anima inputs
  eReq = Anima_CheckInputs();
  //check valid animation
  if ((eReq != eExtLightingAnimationReq_None) && (eReq != eExtLightingAnimationReq_Invalid))
  {
    // an animation is requested: start the animation if it hasn't been started before
    if (eReq != eReqPrev)
    {
      // switch between animations: stop previous animation (if any) and start new animation
      if ((eReqPrev != eExtLightingAnimationReq_None) && (eReqPrev != eExtLightingAnimationReq_Invalid))
      {
        AnimMa_stopSequence(CodPrj_GetAnimMaSequenceId(eReqPrev));
      }
      // start the animation
      AnimMa_startSequence(CodPrj_GetAnimMaSequenceId(eReq));
      bRet = true;
    }
  }
  else if (eReq == eExtLightingAnimationReq_None) //off
  {
    // animation is not requested: stop previous animation (if any)
    if (eExtLightingAnimationReq_None != eReqPrev)
    {
      AnimMa_stopSequence(CodPrj_GetAnimMaSequenceId(eReqPrev));
      bRet = true;
    }
  }
  else //invalid
  {
    //stay here untill new valid animation is coming
  }
  // store the last animation
  eReqPrev = eReq;
  return bRet;
}

//-----------------------------------------------------------------------------
/// Return the sequence id for eReq that can be used to start (or stop) sequences in the animation engine.
//-----------------------------------------------------------------------------
STATIC_AL void Anima_DoRamps(void)
{
  int i;
  ///AnimMa_GetPxlTgt contains the output intensity for each pixel and for each block used in a sequence
  const uint8 * paucPxlTgt = AnimMa_GetPxlTgt();
  const uint8 * paucPxlInc = AnimMa_GetPxlInc();
  const uint8 * paucPxlDec = AnimMa_GetPxlDec();

  for (i = 0; i < ANIMMA_NR_PIXELS; i++)
  {
    int nNewTgt = 0;
    const uint16 unPxlTgt = Anima_Percent8_to_Percent16(paucPxlTgt[i]);

    if (unPxlTgt == Anima_TgtAniArr.unTgtAni[i])
    {
      // intentionally left blank; nothing to do: actual value is at target value
    }
    else if (unPxlTgt < Anima_TgtAniArr.unTgtAni[i])
    {

      if (paucPxlDec[i] == 0u)
      {
        nNewTgt = (int)unPxlTgt;
      }
      else
      {
        // decrease
        nNewTgt = (int)Anima_TgtAniArr.unTgtAni[i] - (int)Anima_Percent8_to_Percent16(paucPxlDec[i]);
      }
      Anima_TgtAniArr.unTgtAni[i] = (nNewTgt > (int)unPxlTgt) ? ((uint16)nNewTgt) : (unPxlTgt);
    }
    else
    {
      // increase
      nNewTgt = (int)Anima_TgtAniArr.unTgtAni[i] + (int)Anima_Percent8_to_Percent16(paucPxlInc[i]);
      Anima_TgtAniArr.unTgtAni[i] = (nNewTgt < (int)unPxlTgt) ? ((uint16)nNewTgt) : (unPxlTgt);
    }
  }
}

//-----------------------------------------------------------------------------
/// Clear all the intensities for the 103 pixels
//-----------------------------------------------------------------------------
STATIC_AL void Clear_Intensities(void)
{
  int i;
  ///AnimMa_GetPxlTgt contains the output intensity for each pixel and for each block used in a sequence

  for (i = 0; i < ANIMMA_NR_PIXELS; i++)
  {
    Anima_TgtAniArr.unTgtAni[i] = 0u;
    Anima_Scrolling.unTgtAniScr[TI_SCROLLING] = 0u;
  }

}

//-----------------------------------------------------------------------------
/// \Check Table of inputs and set priority to CtrlLED
///
/// \descr
///
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL teRte_ExtLightingAnimationReq Anima_CheckInputs(void)
{
  static teRte_ExtLightingAnimationReq eRetExtAnim = eExtLightingAnimationReq_None;
  teRte_ExtLightingAnimationReq AnimaReq;
  teRte_DelayFmh DelayFMH;
  uInputsCheck uInputScenario;

  AnimaReq = Anima_RteAccess_Read_ExtLightingAnimationReq();
  DelayFMH = Anima_RteAccess_ReadDelayFmh();

  if (AnimaReq == eExtLightingAnimationReq_Fmh)
  {
    switch (DelayFMH)
    {
    case eDelayFmh_15Seconds:
      eRetExtAnim = eExtLightingAnimationReq_Fmh15;
      break;
    case eDelayFmh_30Seconds:
      eRetExtAnim = eExtLightingAnimationReq_Fmh30;
      break;
    case eDelayFmh_60Seconds:
      eRetExtAnim = eExtLightingAnimationReq_Fmh60;
      break;
    default:
      break;

    }
  }
  else
  {
    eRetExtAnim = AnimaReq;
  }

  uInputScenario.unRaw = Anima_GetInputs();
  //animation is requested and valid
  if ((eRetExtAnim != eExtLightingAnimationReq_None) && (eRetExtAnim != eExtLightingAnimationReq_Invalid))
  {
    Anima_TgtAniArr.boPriority = ((uInputScenario.unRaw & ANIMA_CFG_SWITCH_OFF_ANIMA_VALID) != 0U) ? PRIORITY_ANIMATION_NONE : PRIORITY_ANIMATION_RUNNING;
  }
  //animation is requested and invalid
  else if (eRetExtAnim == eExtLightingAnimationReq_Invalid)
  {
    Anima_TgtAniArr.boPriority = ((uInputScenario.unRaw & ANIMA_CFG_SWITCH_OFF_ANIMA_INVALID) != 0U) ? PRIORITY_ANIMATION_NONE : Anima_TgtAniArr.boPriority;
  }
  //off
  else
  {
    Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE;
  }

  return (Anima_TgtAniArr.boPriority == PRIORITY_ANIMATION_NONE) ? eExtLightingAnimationReq_None : eRetExtAnim;
}

//-----------------------------------------------------------------------------
/// \Anima_GetInputs
///
/// \descr Get the inputs used in Anima.c to inhibit the animations
///
///
/// \param  
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 Anima_GetInputs(void)
{
  uInputsCheck uInputs;
  const uint8 ucElNetState = Anima_RteAccess_ReadElectricNetworkState();

  uInputs.bBit.bLB = (Anima_RteAccess_ReadLowBeamCtrl() != FALSE) ? 1U : 0U;

  switch (ucElNetState)
  {
  case (uint8)eTA_NOMINAL:
  case (uint8)eTA_DEGRADE:
  case (uint8)eREDEMARRAGE:
  case (uint8)eTI_DISPO_DEM:
  case (uint8)eDEMARRAGE:
    uInputs.bBit.bEtat = 1U;
    break;
  default:
    uInputs.bBit.bEtat = 0U;
    break;
  }

  uInputs.bBit.bGFHBAvailability = 0U;
  uInputs.bBit.bF2P = (Anima_RteAccess_ReadHeadlampFlashBeamCmd() != FALSE) ? 1U : 0U;
  uInputs.bBit.bHB = (Anima_RteAccess_ReadHighBeamCtrl() != FALSE) ? 1U : 0U;
  uInputs.bBit.bDRL = (Anima_RteAccess_ReadDRLRequest() != FALSE) ? 1U : 0U;
  uInputs.bBit.bFP = (Anima_RteAccess_ReadFPRequest() != FALSE) ? 1U : 0U;
  uInputs.bBit.bTI = (Anima_ReadFrontTurnIndicatorCmd() != FALSE) ? 1U : 0U;

  return uInputs.unRaw;
} // PRQA S 5324 1 // Anima_GetInputs is an interface function and it exceeds the treshold 7 of distinct function calls ( 8 in total)

//-----------------------------------------------------------------------------
/// \brief  initialisation function for Anima
///
/// \descr
///
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_Init(void)
{
  teRte_MountingSide eSide;

  (void)rcAnimMaInit();

  eSide = Anima_RteAccess_Read_MountingSide();

  if (eSide == eMountedLeft)
  {
    (void)AnimMa_setMountingSide(ANIMMA_MOUNTINGSIDE_LEFT);
  }
  else if (eSide == eMountedRight)
  {
    (void)AnimMa_setMountingSide(ANIMMA_MOUNTINGSIDE_RIGHT);
  }
  else
  {
    (void)AnimMa_setMountingSide(ANIMMA_MOUNTINGSIDE_UNKNOWN);
  }

  Anima_MapParams();

  Anima_TgtPrep_Init();

  Anima_TgtAniArr.boPriority = PRIORITY_ANIMATION_NONE;


}

//-----------------------------------------------------------------------------
/// \brief  Anima main function call, called every 10 ms.
///
/// \descr  Start and stop animations as per CAN signal request. 
///         Call animation engine every 50 ms. 
///         Calculate dim ramps every 10 ms.
///
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_Cycle10(void)
{
  static uint32 counter = 0U; //counter scheduler, for the AnimMa50

  if (Anima_StartStopAnimation())
  {
    // ensure that animation engine is called immediately if an animation is started and/or stopped
    counter = 0U;
  }

  // Update the animation engine every 50 ms
  if ((counter % ANIMMA_CYCLE) == 0u)
  {
    (void)rcAnimMa50();
  }
  if (Anima_TgtAniArr.boPriority == PRIORITY_ANIMATION_NONE)
  {
    Clear_Intensities();
    Anima_Scrolling.boPriorityScr = Anima_TgtAniArr.boPriority;
  }
  else
  {
    Anima_DoRamps();
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
    if (((Anima_TgtAniArr.unTgtAni[TI_SCROLLING_ANIMMA] >> MASKSHIFT) & MASK1) != 0u)
    {
      Anima_Scrolling.unTgtAniScr[TI_SCROLLING] = (uint16)eRte_eScrollingSatelite_On_Scrolling_Off;
    }
    else if (((Anima_TgtAniArr.unTgtAni[TI_SCROLLING_ANIMMA] >> MASKSHIFT) & MASK2) != 0u)
    {
      Anima_Scrolling.unTgtAniScr[TI_SCROLLING] = (uint16)eRte_eScrollingSatelite_On_Scrolling_On;
    }
    else
    {
      Anima_Scrolling.unTgtAniScr[TI_SCROLLING] = (uint16)eRte_ScrollingSatelite_Off;
    }

    (void)Rte_Write_AnimaScrollingActivation(&Anima_Scrolling);
#endif 
  }
  counter += 1U;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_TgtPrep_Init
///
/// \descr  Initialize variables used in Anima_RteAccess_ReadFrontTurnIndicatorCmd
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Anima_TgtPrep_Init(void)
{
  // Init TI Delay timer and reset the init state to Di_Sna to not start the timer
  UtilDebounceInit(&Anima_TgtPrep_TiDelayTimer, Di_Sna, UTILTIME_MSEC(AnimMa_Cod_GetDelayTiNotRequested()), 0u);
  Anima_TgtPrep_TiDelayTimer.eState = Di_Sna;

}

//-----------------------------------------------------------------------------
/// \brief  Anima_ReadFrontTurnIndicatorCmd
///
/// \descr  get Ti status
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean Anima_ReadFrontTurnIndicatorCmd(void)
{
  static boolean boTiRetStatus = FALSE;
  const boolean boTiReq = Anima_RteAccess_ReadFrontTurnIndicatorCmd();

  if (boTiReq != FALSE)
  {
    // Set TI light function status to active
    boTiRetStatus = TRUE;
    // Reset TI delay timer
    Anima_TgtPrep_TiDelayTimer.eState = Di_Sna;
  }
  else
  {
    // Check timer status
   // When TI request is not active wait for FCTR_DELAY_TI_NOT_REQUESTED ms 
   // to confirm that TI is no more requested
    UtilDebounce(&Anima_TgtPrep_TiDelayTimer, TRUE);
  }

  // Check for timer timout
  if (Anima_TgtPrep_TiDelayTimer.eState == Di_On)
  {
    // Set TI light function status to inactive
    boTiRetStatus = FALSE;
  }
  else
  {
    // Keep the TI light function status
  }

  return boTiRetStatus;
}

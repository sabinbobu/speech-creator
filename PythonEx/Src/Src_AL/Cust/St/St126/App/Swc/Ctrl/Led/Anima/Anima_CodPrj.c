/// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Anima_CodPrj.c
///
/// \brief Project specific definition for coding data (if any)
///
/// \author Georgiana Sevastre (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <AL_Helper.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#include <RteCommonTypes.h>
#include "Anima.h"
#include "Anima_CodPrj.h"
#include "AnimMa.h"

//=============================================================================
// function prototypes
//=============================================================================
#ifdef UNIT_TEST
extern Std_ReturnType   Rte_Read_CodM_Anima_Para(tsRteCodingParameters* ppara1);
#endif

//=============================================================================
// defines
//=============================================================================

//=============================================================================
// variables
//=============================================================================
STATIC_AL boolean                 Anima_boCodingValid;
CONST_AL  tNvmPara_CodingArea*    AnimMa_pCodingData;
/// This array defines a sequence id per animation. Each animation has a sequence id which defines the sequence
/// that is to be started if the animation is requested.
/// The sequences are defined in the Windows tool. Each sequence has an ID in the Windows tool.

STATIC_AL const teRte_ExtLightingAnimationReq Anima_CodPrj_aucLutAnimations[] =
{
  eExtLightingAnimationReq_None                 , // =  0u 
  eExtLightingAnimationReq_WelcomeDay           , // =  1u 
  eExtLightingAnimationReq_WelcomeNight         , // =  2u 
  eExtLightingAnimationReq_ByeByeDay            , // =  3u 
  eExtLightingAnimationReq_ByeByeNight          , // =  4u 
  eExtLightingAnimationReq_ByeByeNightFmh       , // =  5u  not present on ECO/FULL
  eExtLightingAnimationReq_UnlockDay            , // =  6u 
  eExtLightingAnimationReq_UnlockNight          , // =  7u 
  eExtLightingAnimationReq_UnlockDayExtension   , // =  8u 
  eExtLightingAnimationReq_UnlockNightExtension , // =  9u 
  eExtLightingAnimationReq_Fmh                  , // =  10u 
  eExtLightingAnimationReq_RemoteLighting       , // =  11u not present on ECO/FULL
  eExtLightingAnimationReq_LockDay              , // =  12u 
  eExtLightingAnimationReq_LockNight            , // =  13u 
  eExtLightingAnimationReq_LockNightExtension   , // =  14u 
  eExtLightingAnimationReq_Autorelock           , // =  15u not present on ECO
  eExtLightingAnimationReq_LocalizationDay      , // =  16u 
  eExtLightingAnimationReq_LocalizationNight    , // =  17u 
  eExtLightingAnimationReq_ShowroomEvent        , // =  18u not present on ECO
  eExtLightingAnimationReq_ShowroomContinu      , // =  19u not present on ECO
  eExtLightingAnimationReq_EndNightByeBye       , // =  20u 
  eExtLightingAnimationReq_SwitchOff            , // =  21u not present on ECO/FULL
  eExtLightingAnimationReq_LockDayExtension     , // =  22u 
  eExtLightingAnimationReq_Fmh15                , // =  23u
  eExtLightingAnimationReq_Fmh30                , // =  24u
  eExtLightingAnimationReq_Fmh60                , // =  25u
  eExtLightingAnimationReq_Invalid                // =  255u
};

//=============================================================================
// variables
//=============================================================================


//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// Return sequence ID for given PSA animation
//-----------------------------------------------------------------------------
teRte_ExtLightingAnimationReq CodPrj_GetAnimMaSequenceId(teRte_ExtLightingAnimationReq eReq)
{
  return Anima_CodPrj_aucLutAnimations[(int)eReq];
}

//-----------------------------------------------------------------------------
/// \func   Cpm_ParaFct0
///
/// \brief  Thermo coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  // set pointer to Coding Data
  AnimMa_pCodingData = pData;
  Anima_boCodingValid = (eCmd == eParaFct0_CodingDataValid) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  Cpm_MapParams
///
/// \descr  Maps the coding parameter in order to acces them in Anima
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Anima_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;

  (void)Rte_Read_CodM_Anima_Para(&sCodingParameters);

  Anima_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
}

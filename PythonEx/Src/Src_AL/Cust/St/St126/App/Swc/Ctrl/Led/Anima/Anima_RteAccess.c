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
/// \file  Anima_RteAccess.c
///
/// \brief
///
/// \author Georgiana Sevastre (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#include <Std_Types.h>
#include "Anima_RteAccess.h"
#include <Cfg/Cfg.h>
#include "Anima.h"
#include "Anima_Cfg.h"

//=============================================================================
// variables
//=============================================================================


//=============================================================================
// functions
//=============================================================================
#ifdef UNIT_TEST
extern Std_ReturnType   Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1); 
extern Std_ReturnType   Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1);
extern Std_ReturnType   Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
extern Std_ReturnType   Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1);
extern Std_ReturnType   Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1);
extern Std_ReturnType   Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1);
extern Std_ReturnType   Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
extern Std_ReturnType   Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
extern Std_ReturnType   Rte_Read_SigPrep_AnimationReq(tsRte_AnimationReq* ppara1);
#endif
//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_Read_MountingSide
///
/// \descr  Mount side
///
/// \param  void
///
/// \return 
//-----------------------------------------------------------------------------
teRte_MountingSide Anima_RteAccess_Read_MountingSide(void)
{
  teRte_MountingSide eMountingSide;
  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);
  return eMountingSide;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_Read_ExtLightingAnimationReq
///
/// \descr  gets the L/R animation request
///
/// \param  void
///
/// \return teRte_ExtLightingAnimationReq
//-----------------------------------------------------------------------------
// PRQA S 5316 ++
// QAC(Prio2) Msg: 5316(HIS metrics violation: 'Anima_RteAccess_Read_ExtLightingAnimationReq() : STCYC = 16' exceeds threshold 15 for Cyclomatic complexity (STCYC).) Depth: 0 Ref:  
// Rationale: code is maintainable, testable and well structured.
teRte_ExtLightingAnimationReq Anima_RteAccess_Read_ExtLightingAnimationReq(void)
{
  tsRte_AnimationReq            sExtLightingAnimationReq;
  teRte_ExtLightingAnimationReq eRet_ExtLightingAnimationReq;

  (void)Rte_Read_SigPrep_AnimationReq(&sExtLightingAnimationReq);

  if (sExtLightingAnimationReq.eSigQty == SIG_VALID)
  {
      switch (sExtLightingAnimationReq.eFrontLightingAnimationCtrl)
      {
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
          case eExtLightingAnimationReq_WelcomeDay:
          case eExtLightingAnimationReq_WelcomeNight:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_WelcomeDay;
              break;
          case eExtLightingAnimationReq_ByeByeDay:
          case eExtLightingAnimationReq_ByeByeNight:
          case eExtLightingAnimationReq_EndNightByeBye:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ByeByeDay;
              break;
          case eExtLightingAnimationReq_ByeByeNightFmh:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ByeByeNightFmh;
              break;
          case eExtLightingAnimationReq_UnlockDay:
          case eExtLightingAnimationReq_UnlockNight:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_UnlockDay;
              break;
          case eExtLightingAnimationReq_UnlockDayExtension:
          case eExtLightingAnimationReq_UnlockNightExtension:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_UnlockDayExtension;
              break;
          case eExtLightingAnimationReq_RemoteLighting:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_RemoteLighting;
              break;
          case eExtLightingAnimationReq_LockDay:
          case eExtLightingAnimationReq_LockNight:
          case eExtLightingAnimationReq_Autorelock:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_LockDay;
              break;
          case eExtLightingAnimationReq_LocalizationDay:
          case eExtLightingAnimationReq_LocalizationNight:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_LocalizationDay;
              break;
          case eExtLightingAnimationReq_ShowroomEvent:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ShowroomEvent;
              break;
          case eExtLightingAnimationReq_ShowroomContinu:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ShowroomContinu;
              break;
          case eExtLightingAnimationReq_SwitchOff:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_SwitchOff;
              break;
          case eExtLightingAnimationReq_LockDayExtension:
          case eExtLightingAnimationReq_LockNightExtension:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_LockDayExtension;
              break;
          case eExtLightingAnimationReq_None:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_None;
              break;
          case eExtLightingAnimationReq_Fmh:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_Fmh;
              break;
          default:
              eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_None;
              break;
#else 
      case eExtLightingAnimationReq_WelcomeDay:
      case eExtLightingAnimationReq_WelcomeNight:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_WelcomeDay;
          break;
      case eExtLightingAnimationReq_ByeByeDay:
      case eExtLightingAnimationReq_ByeByeNight:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ByeByeDay;
          break; 
      case eExtLightingAnimationReq_EndNightByeBye:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_EndNightByeBye;
          break;
      case eExtLightingAnimationReq_ByeByeNightFmh:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ByeByeNightFmh;
          break;
      case eExtLightingAnimationReq_UnlockDay:
      case eExtLightingAnimationReq_UnlockNight:
      case eExtLightingAnimationReq_UnlockDayExtension:
      case eExtLightingAnimationReq_UnlockNightExtension:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_UnlockDay;
          break;
          break;
      case eExtLightingAnimationReq_RemoteLighting:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_RemoteLighting;
          break;
      case eExtLightingAnimationReq_LockDay:
      case eExtLightingAnimationReq_LockNight:
      case eExtLightingAnimationReq_LockDayExtension:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_LockDay;
          break;
      case eExtLightingAnimationReq_LocalizationDay:
      case eExtLightingAnimationReq_LocalizationNight:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_LocalizationDay;
          break;
      case eExtLightingAnimationReq_ShowroomEvent:
      case eExtLightingAnimationReq_ShowroomContinu:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_ShowroomEvent;
          break;
      case eExtLightingAnimationReq_SwitchOff:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_SwitchOff;
          break;
      case eExtLightingAnimationReq_Autorelock:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_Autorelock;
          break;
      case eExtLightingAnimationReq_LockNightExtension:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_LockNightExtension;
          break;
      case eExtLightingAnimationReq_None:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_None;
          break;
      case eExtLightingAnimationReq_Fmh:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_Fmh;
          break;
      default:
          eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_None;
          break;
#endif
      }
  }
  else
  {
    eRet_ExtLightingAnimationReq = eExtLightingAnimationReq_Invalid;
  }
  return eRet_ExtLightingAnimationReq;
}// PRQA S 5316 compactness and readability,program architecture and readability - intentionally no modification of existing code

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadDelayFmh
///
/// \descr  gets the Follow me home animation Delay requested
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
teRte_DelayFmh Anima_RteAccess_ReadDelayFmh(void)
{
  tsRte_AnimationReq   sDelayFmh;
  teRte_DelayFmh       eReturnDelayFmh;

  (void)Rte_Read_SigPrep_AnimationReq(&sDelayFmh);

  if (sDelayFmh.eSigQty == SIG_VALID)
  {
	  eReturnDelayFmh = sDelayFmh.eDelayFmh;
  }
  else
  {
	  eReturnDelayFmh = eDelayFmh_NotUsed;
  }
  return eReturnDelayFmh;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadElectricNetworkState
///
/// \descr  gets the  vehicle electrical state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 Anima_RteAccess_ReadElectricNetworkState(void)
{
  tsRte_SysMon_VehNetState   sVehNetState;
  uint8                      ucElectricNetworkState;

  (void)Rte_Read_SysMon_VehNetState(&sVehNetState);

  if (sVehNetState.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucElectricNetworkState = (uint8)sVehNetState.eElectricNetworkState;
  }
  else
  {
    ucElectricNetworkState = (uint8)eInvalid;
  }
  return ucElectricNetworkState;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadFrontTurnIndicatorCmd
///
/// \descr  turn indicator control
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Anima_RteAccess_ReadFrontTurnIndicatorCmd(void)
{
  boolean boTiReq                 = FALSE;
  teRte_ReqLightState eTi_Request = ReqLighted_Off;
  (void)Rte_Read_SysMon_TurnIndicatorCmd_Req(&eTi_Request);

  if (eTi_Request != ReqLighted_Off)
  {
    boTiReq = TRUE;
  }

  return boTiReq;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadHeadlampFlashBeamCmd
///
/// \descr  HB flash request
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Anima_RteAccess_ReadHeadlampFlashBeamCmd(void)
{
  tsRte_SysMonLgtFctsReq   sdataLgtFctsReq;
  boolean                  boF2PReq = FALSE;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sdataLgtFctsReq);

  if (sdataLgtFctsReq.eSigQty == SIG_VALID)
  {
    boF2PReq = (sdataLgtFctsReq.eHbFlash_Request != ReqLighted_Off) ? TRUE : FALSE;
  }
  else
  {
    boF2PReq = FALSE;
  }
  return boF2PReq;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadDRLRequest
///
/// \descr  DRL request
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Anima_RteAccess_ReadDRLRequest(void)
{
  tsRte_SysMonLgtFctsReq      sdataLgtFctsReq;
  boolean                     boDRL_Request;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sdataLgtFctsReq);

  if (sdataLgtFctsReq.eSigQty == SIG_VALID)
  {
    boDRL_Request = (sdataLgtFctsReq.eDrl_Request != ReqLighted_Off) ? TRUE : FALSE;
  }
  else
  {
    boDRL_Request = FALSE; 
  }
  return boDRL_Request;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadFPRequest
///
/// \descr  Front Position request
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Anima_RteAccess_ReadFPRequest(void)
{
  tsRte_SysMonLgtFctsReq   sdataLgtFctsReq;
  boolean                  boFP_Request;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sdataLgtFctsReq);

  if (sdataLgtFctsReq.eSigQty == SIG_VALID)
  {
    boFP_Request = (sdataLgtFctsReq.ePos_Request != ReqLighted_Off) ? TRUE : FALSE;
  }
  else
  {
    boFP_Request = FALSE;
  }
  return boFP_Request;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadLowBeamCtrl
///
/// \descr  Low beam control
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Anima_RteAccess_ReadLowBeamCtrl(void)
{
  teRte_ReqLightState eLb = ReqLighted_Off;
  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLb);
  return (eLb != ReqLighted_Off) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ReadHighBeamCtrl
///
/// \descr  High beam control
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------

boolean Anima_RteAccess_ReadHighBeamCtrl(void)
{
  tsRte_SysMonLgtFctsReq   sdataLgtFctsReq;
  boolean                  boHbReq = FALSE;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sdataLgtFctsReq);

  if (sdataLgtFctsReq.eSigQty == SIG_VALID)
  {
    boHbReq = (sdataLgtFctsReq.eHb_Request != ReqLighted_Off) ? TRUE : FALSE;
  }
  else
  {
    boHbReq = FALSE;
  }
  return boHbReq;
}

//-----------------------------------------------------------------------------
/// \brief  Anima_RteAccess_ElectricNetworkState
///
/// \descr  status of the 12V electrical energy supply in by engine
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 Anima_RteAccess_ElectricNetworkState(void)
{
  tsRte_SysMon_VehNetState   sEtatFee;
  uint8                      ucElectricNetworkState;

  (void)Rte_Read_SysMon_VehNetState(&sEtatFee);

  if (sEtatFee.eSigQty == SIG_VALID)
  {
    ucElectricNetworkState = (uint8)sEtatFee.eElectricNetworkState;
  }
  else
  {
    ucElectricNetworkState = (uint8)eInvalid;
  }
  return ucElectricNetworkState;
}

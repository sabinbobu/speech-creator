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
/// \file  CodM_RteAccess.c
///
/// \brief Source files for the coding manager module wrappers
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <CodM_RteAccess.h>
#include <CodM.h>

//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// functions 
//=============================================================================
//read
//-----------------------------------------------------------------------------
/// \brief CodM_RteAccess_GetTouristMState
///
/// \descr returns tourist mode state
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
//teCodM_HandTraffic CodM_RteAccess_GetTouristMState(void)
//{
//  teRte_HandTraffic   eTouristModeState;
//  teCodM_HandTraffic  eHandTraffic;
//  (void)Rte_Read_AfsLgtFctMgr_TouristModeConfigState_Port(&eTouristModeState);
//
//  switch (eTouristModeState)
//  {
//  case eLeftHandTraffic:
//    eHandTraffic = eCodMHTrafficLeft;
//    break;
//  case eRightHandTraffic:
//    eHandTraffic = eCodMtHTrafficRght;
//    break;
//  default:
//    eHandTraffic = eInitialValue;
//    break;
//  }
//
//  return eHandTraffic;
//}

////-----------------------------------------------------------------------------
///// \brief roCodM_GetMinBrightnesParamValidity
/////
///// \descr Rte call runnable getter for minimum brightness parameters and their integrity
/////
///// \param  sMinBrParam - Minimum Brightness Parameters for Lb and Ti
/////
///// \return void
////-----------------------------------------------------------------------------
//void roCodM_RteAccess_GetMinBrightnessParamsValidity(tsRte_CodMinBrightness_Param* const sMinBrParam)
//{
//  sMinBrParam->eQty                 = (CodM_GetMinBrightness_Param()->boMinBrParamValidStatus != FALSE) ? SIG_VALID : SIG_INVALID;
//  sMinBrParam->unSafetyTiMin_Curent = CodM_GetMinBrightness_Param()->unTi_MinCurrent;
//  sMinBrParam->unSafetyTiMin_Pwm    = CodM_GetMinBrightness_Param()->unTi_MinPWM;
//  sMinBrParam->unSafetyLbMin_Curent = CodM_GetMinBrightness_Param()->unLb_MinCurrent;
//  sMinBrParam->unSafetyLbMin_Pwm    = CodM_GetMinBrightness_Param()->unLb_MinPWM;
//}

//-----------------------------------------------------------------------------
/// \brief CodM_RteAccess_CalculateCrc32
///
/// \descr Rte wrepper for SysRomSeg CRC32 calculation
///
/// \param  pucData:        Data Adress
/// \param  unLength:       Data Length
/// \param  ulCrc_StartVal: CRC32 Init Value
///
/// \return uint32: CRC32 Value returned
//-----------------------------------------------------------------------------
//uint32 CodM_RteAccess_CalculateCrc32(CONST_AL uint8* CONST_AL pucData, uint16 unLength, uint32 ulCrc_StartVal)
//{
//  return (Rte_Call_SysCrc_RomSegs_CalculateCrc32(pucData, unLength, ulCrc_StartVal));
//}

// EOF

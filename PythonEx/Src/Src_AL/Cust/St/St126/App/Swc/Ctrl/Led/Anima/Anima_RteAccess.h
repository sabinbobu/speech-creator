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
/// \file   Anima_RteAccess.h
///
/// \brief  encapsule RTE access
///
/// \descr  
///
/// \author 
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <RteCommonTypes.h>
#include <Cfg/Cfg.h>
#include "AnimMa_Types.h"
#include "Anima.h"

//=============================================================================
// functions prototype
//=============================================================================

teRte_ExtLightingAnimationReq Anima_RteAccess_Read_ExtLightingAnimationReq(void);
teRte_DelayFmh Anima_RteAccess_ReadDelayFmh(void);
uint8 Anima_RteAccess_ReadElectricNetworkState(void);
boolean Anima_RteAccess_ReadHeadlampFlashBeamCmd(void);
uint8 Anima_RteAccess_ElectricNetworkState(void);
boolean Anima_RteAccess_ReadLowBeamCtrl(void);
boolean Anima_RteAccess_ReadHighBeamCtrl(void);
boolean Anima_RteAccess_ReadDRLRequest(void);
boolean Anima_RteAccess_ReadFPRequest(void);
teRte_MountingSide Anima_RteAccess_Read_MountingSide(void);
boolean Anima_RteAccess_ReadFrontTurnIndicatorCmd(void);
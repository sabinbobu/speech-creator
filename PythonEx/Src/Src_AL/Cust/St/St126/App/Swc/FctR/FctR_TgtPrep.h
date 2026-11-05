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
/// \file  FctR_TgtPrep.h
///
/// \brief Defines the Signal Preparation functionality of Function Router (FctR).
///
//-----------------------------------------------------------------------------
#ifndef FCT_R_TGT_PREP_H_
#define FCT_R_TGT_PREP_H_

//=============================================================================
// includes
//=============================================================================

#include <UtilDebounce.h>

//=============================================================================
// function prototypes
//=============================================================================

void FctR_TgtPrep_Init(void);
boolean FctR_TgtPrep_GetTiCmdReq(void);
tsFctR_TgtLgtReq FctR_TgtPrep_GetTgtLgtReq(void);
boolean FctR_TgtPrep_GetAimingMode(void);
boolean FctR_TgtPrep_Get_Hb_Cmd(void);
boolean FctR_TgtPrep_Get_Lb_Cmd(void);

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
uint8 FctR_TgtPrep_GetClSblTargetState(void);
teFctR_LightFunctions FctR_TgtPrep_GetClSbl_AfsLight(void);
teFctR_AfsMode FctR_TgtPrep_GetAfsMode(void);
boolean FctR_TgtPrep_GetAfsPedestrian(void);
void FctR_TgtLgt_Prep_Full(void);
boolean FctR_TgtPrep_SblClTimeOutFrame(void);
#else
  void FctR_TgtLgt_Prep_Eco(void);
#endif

#endif // FCT_R_TGT_PREP_H_

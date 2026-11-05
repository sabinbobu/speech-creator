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
/// \file   SigPrepRx.h
///
/// \brief  
///
/// \descr  Input Rx Frame processing header file
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_RX_H__
#define __SIG_PREP_RX_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SigPrep_Types.h>

#ifdef UNIT_TEST
#include <CommonE2E.h>
#endif

//-----------------------------------------------------------------------------
// externs
//-----------------------------------------------------------------------------
extern CONST_AL  tNvmPara_CodingArea*     SigPrep_Data_pCodingArea;


//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void                SigPrepRx_Init                  (void);
void                SigPrepRx_Cycle0                (void);
void                SigPrepRx_ComM_DisableCallbacks (void);
void                SigPrepRx_ComM_EnableCallbacks  (void);
teRte_MountingSide  SigPrepRx_GetMountingSide       (void);
uint16              SigPrepRx_GetConfigTime         (void);

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
boolean  Cod_Dbl_Enable                             (void);
boolean  Cod_GFHB_Enable                            (void);
boolean  Cod_CurtainEffect_Enable                   (void);
boolean  Cod_TSAG_Enable                            (void);
boolean  Cod_Motorway_Enable                        (void);
boolean  Cod_CurvatureMode                          (void);
// Check if ADL option is present in Coding for FULL version
boolean  Cod_AvacStp_Enable                         (void);
#endif // (SAMPLE_FULL) || defined(UNIT_TEST)
#if defined (CFG_VARIANT_ECO) || (UNIT_TEST)
// Check if ASL option is present in Coding for ECO version
boolean  Cod_Asl_Enable                             (void);
#endif // (CFG_VARIANT_ECO) || (UNIT_TEST)

#endif // __SIG_PREP_RX_H__

// EOF

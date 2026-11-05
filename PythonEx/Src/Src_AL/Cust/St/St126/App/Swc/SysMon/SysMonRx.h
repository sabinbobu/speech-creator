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
/// \file   SysMonRx.h
///
/// \brief  
///
/// \descr  Input Rx Frame processing header file
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_RX_H__
#define __SYS_MON_RX_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#ifdef UNIT_TEST
#include <SigPrep_Types.h>
#include <CommonE2E.h>
#include <_NM_Types.h>
#else
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Rte.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#endif
//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------

extern EECO_TE_RxIndicator APPLI_ui32_Hs6DatVsm34eIndicator;        // variable that indicates the reception of HS6_DAT_VSM_34E message -> it is used by E2E protection

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SysMonRx_Init(void);
void SysMonRx_Cycle0(void);
void SysMonRx_ComM_DisableCallbacks (void);
void SysMonRx_ComM_EnableCallbacks  (void);
teRte_MountingSide SysMonRx_GetMountingSide(void);
NM_ModeType SysMonRx_getNMMode(void);

#endif // __SYS_MON_RX_H__

// EOF

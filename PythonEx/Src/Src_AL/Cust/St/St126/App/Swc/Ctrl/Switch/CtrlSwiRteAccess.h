#ifndef __CTRFANRTEACCESS_H__
#define __CTRFANRTEACCESS_H__
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
/// \file  CtrlFanRteAccess.h
///
/// \brief  
///
/// \descr  
///
///
/// \author Cretu Vladut-Ioan (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <CtrlSwi_Types.h>
#include <Cfg/Cfg.h>
#include <RteCommonTypes.h>
#include <Std_Types.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//=============================================================================
// functions prototype
//=============================================================================
// TBD
//teRte_DiagFeedback CtrlFanRteAccess_DiagFct0(teRte_CtrlFan_DiagFct0_FanCmd eCmd);
//void CtrlFanRteAccess_SetALEC(teCtrlFan_newALECsError eErrorType);

//=============================================================================
// inline functions
//=============================================================================

// Maps the coding parameters via RTE
void CtrlSwi_RteAccess_MapParams(void);
#endif /* CTRLFANRTEACCESS_H */
//EOF


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
/// \file   SysMonCheck_LedCtrl.h
///
/// \brief  
///
/// \descr  Cyclic and Init Function prototypes for SysMonCheck_LedCtrl
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_CHECK_LEDCTRL_H__
#define __SYS_MON_CHECK_LEDCTRL_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SysMonCheck_LedCtrl_Init(CONST_AL tsRte_TgtLedSig0* CONST_AL paTargetLed, tsRte_TgtLedSig0_ASIL* CONST_AL paTargetLed_ASIL);
void SysMonCheck_LedCtrl_Cycle(void);
void SysMonCheck_LedCtrl_TargetLedDefaultValues(void);

#endif // __SYS_MON_CHECK_LEDCTRL_H__

// EOF

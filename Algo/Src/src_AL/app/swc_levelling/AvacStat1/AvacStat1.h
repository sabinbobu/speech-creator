#ifndef __AVACSTAT1_H
  #define __AVACSTAT1_H

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
/// \file  AvacStat1.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen[at]al-lighting.com
//-----------------------------------------------------------------------------

#include <Std_Types.h>

#if (CFG_DEV_HOOK_EN == 1u) // tester hook
#define AVACSTAT1_RESET_ZLP_HOOK_KEY       0xADEE2323u
extern volatile uint32 AvacStat1_ulTesterHookActivation;
#endif


//=============================================================================
// Functions
//=============================================================================

void AvacStat1_Cycle0(void);
void AvacStat1_Init(void);


#endif //__AVACSTAT1_H

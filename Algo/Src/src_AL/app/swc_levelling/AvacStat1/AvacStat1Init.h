#ifndef __AVAC_INIT_H__
#define __AVAC_INIT_H__

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
/// \file  AvacInit.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Traulsen, Alf ALRT/EEG-CA * (taf2rt)
///         mailTo:Alf.Traulsen@al-lighting.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Nvm.h> */

//=============================================================================
// defines
//=============================================================================

#define AVAC_SAFETY_POS (-54) // Safety angle set to -5.4 mrad (-0,31°)

//=============================================================================
// init data for Nvm-Parameter
//=============================================================================
extern const tisStatAvacPrj1Para     NvmInit_StatAvacPrj1ParaDefault;
extern const tisStatAvac1Para        NvmInit_StatAvac1ParaDefault;
extern const tisStatAvacOp1Data      NvmInit_StatAvacOp1DataDefault;

#endif // __AVAC_INIT_H__

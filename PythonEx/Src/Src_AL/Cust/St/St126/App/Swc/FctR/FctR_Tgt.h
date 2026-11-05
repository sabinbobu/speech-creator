#ifndef __FCTRTGT_H__
#define __FCTRTGT_H__

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
/// \file  FctR_Tgt.h
///
/// \brief External variables and functions of target path.
///
/// \author Peter Ott  (otp2rt)
///         mailTo:peter.ott@al-lighting.com       
//-----------------------------------------------------------------------------

#include "FctR_Types.h"
#include "FctR_Data.h"

//=============================================================================
// functions prototypes
//=============================================================================

void FctR_TgtInit(void);

void FctR_TgtLgt(void);

boolean FctR_SpecialBehaviorDrlPos(void);


#endif // __FCTRTGT_H__

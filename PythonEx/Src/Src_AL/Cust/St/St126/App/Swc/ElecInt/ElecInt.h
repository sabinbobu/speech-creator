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
/// \file  ElecInt.h
///
/// \brief  Electronic Integration handling
///
/// \descr  
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __ELECINT_H__
#define __ELECINT_H__

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#ifndef UNIT_TEST
#include <RteCommonTypes.h>
#endif // UNIT_TEST


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
// Initialization of the ElecInt module
void  ElecInt_Init(void);
// ElecInt Cyclic function
void  ElecInt_Cycle(void);
void  ElecInt_EnterEIMMode(void);
void  ElecInt_ExitEIMMode(void);


#endif // __ELECINT_H__


// EOF

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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

//=============================================================================
// Stub function parameter stubs
//=============================================================================
uint8 Lpit_ClearInterruptFlag_Param1;
uint8 Lpit_ClearInterruptFlag_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 CddSbc_SetWdgWindowModeAnd200ms_HitCount;
uint8 Lpit_ClearInterruptFlag_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief CddSbc_SetWdgWindowModeAnd200ms
///
/// \descr Stub function for SetWdgWindowModeAnd200ms
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void  CddSbc_SetWdgWindowModeAnd200ms()
{
  CddSbc_SetWdgWindowModeAnd200ms_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Lpit_ClearInterruptFlag
///
/// \descr Stub function for Lpit_ClearInterruptFlag
///
/// \param  ucTimerInst,ucTimerCh
///
/// \return void
//-----------------------------------------------------------------------------
void  Lpit_ClearInterruptFlag(uint8 ucTimerInst, uint8 ucTimerCh)
{
  Lpit_ClearInterruptFlag_Param1 = ucTimerInst;
  Lpit_ClearInterruptFlag_Param2 = ucTimerCh;
  Lpit_ClearInterruptFlag_HitCount++;
}

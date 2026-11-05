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

//=============================================================================
// Stub function returned value stubs
//=============================================================================

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 CddDma_StartJob_Callback_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief CddDma_StartJob_Callback_Stub
///
/// \descr Stub function created to verify that the CddDma_StartJob function correctly
///        calls it's callback function
///
/// \param
///
/// \return void
//-----------------------------------------------------------------------------
void CddDma_StartJob_Callback_Stub(void)
{
  CddDma_StartJob_Callback_HitCount++;
}
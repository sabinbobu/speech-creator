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

//=============================================================================
// Stub function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief CddMlc_IsMlcPowered
///
/// \descr Stub function for CddMlc_IsMlcPowered
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddMlc_IsMlcPowered(void)
{
  CddMlc_IsMlcPowered_HitCount++;
  return CddMlc_IsMlcPowered_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief CddMlc_pfGetCodingData
///
/// \descr Stub function for CddMlc_pfGetCodingData
///
/// \param  void
///
/// \return tsCddMlc_CodingData
//-----------------------------------------------------------------------------
tsCddMlc_CodingData* CddMlc_pfGetCodingData(void)
{
  CddMlc_pfGetCodingData_HitCount++;
  return &CddMlc_pfGetCodingData_RetVal;
}




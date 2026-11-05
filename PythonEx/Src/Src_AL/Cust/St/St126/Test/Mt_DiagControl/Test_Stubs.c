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
#include <ALUnitTest_UserInterface.h>
#include "Test_Stubs.h"


//=============================================================================
// Stub function parameter stubs
//=============================================================================

tieFeeState          Fee_State;
MemIf_JobResultType  Fee_JobResult;
uint32               LPTMR0_GetTimeElapsed_Param1;
uint8                roDiag_Callbacks_NRC_Response_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint32   LPTMR0_GetTimeElapsed_RetVal;
boolean  roDiag_IntegrationMode_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8  LPTMR0_GetTimeElapsed_HitCount;
uint8  roDiag_IntegrationMode_HitCount;
uint8  roDiag_Callbacks_ProgramingSessionAccepted_HitCount;
uint8  roDiag_Callbacks_NRC_Response_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_HitCount++;
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  return (LPTMR0_GetTimeElapsed_RetVal);
}


//-----------------------------------------------------------------------------
/// \brief roDiag_IntegrationMode
///
/// \descr Stub function for roDiag_IntegrationMode
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean roDiag_IntegrationMode(void)
{
  roDiag_IntegrationMode_HitCount++;
  return (roDiag_IntegrationMode_RetVal);
}


//-----------------------------------------------------------------------------
/// \brief roDiag_Callbacks_ProgramingSessionAccepted
///
/// \descr Stub function for roDiag_Callbacks_ProgramingSessionAccepted
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void roDiag_Callbacks_ProgramingSessionAccepted(void)
{
  roDiag_Callbacks_ProgramingSessionAccepted_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief roDiag_Callbacks_NRC_Response
///
/// \descr Stub function for roDiag_Callbacks_NRC_Response
///
/// \param  uint8
///
/// \return void
//-----------------------------------------------------------------------------
void roDiag_Callbacks_NRC_Response(uint8 ucCode)
{
  roDiag_Callbacks_NRC_Response_HitCount++;
  roDiag_Callbacks_NRC_Response_Param1 = ucCode;
}



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
/// \file   Test.c
///
/// \brief  Unit Test Cases for DiagControl
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaDiagControl.c
//            - DiagControl.c
//==============================================================================
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
//  ctaaDiagControl.c
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_riDiagControl_Init
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the init runnable is called correctly.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  none
///
///   - Expectations:
/// \output There is no output, this test is performed only for code coverage.
///
//-----------------------------------------------------------------------------
void Mt_riDiagControl_Init(void)
{
  //Step 1: Set pre-conditions
  // none

  //Step 2) Assign Input values
  // none

  //Step 3) Call FUT
  riDiagControl_Init();

  //Step 4) Check expected output values
  // none, this test is performed only for test coverage
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpDiagControl_Cycle0_TestCase1
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the Programming Request Status remains to false in 
///                     case there is no Programming Session request.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  DiagControl_boProgramingReq_Status  = FALSE
///
///   - Expectations:
/// \output DiagControl_boProgramingReq_Status  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_rpDiagControl_Cycle0_TestCase1(void)
{
  //Step 1: Set pre-conditions
  // none

  //Step 2) Assign Input values
  DiagControl_boProgramingReq_Status  = FALSE;

  //Step 3) Call FUT
  rpDiagControl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DiagControl_boProgramingReq_Status,   FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpDiagControl_Cycle0_TestCase2
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the Programming Request Status is TRUE, but
///                     the Integration Mode is false, and the Timer for giving
///                     NRC 0x22 is started.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  DiagControl_boProgramingReq_Status      = TRUE
/// \input  roDiag_IntegrationMode_RetVal           = FALSE
/// \input  DiagControl_ulTmrProgSessison           = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal            = 0u
/// \input  LPTMR0_GetTimeElapsed_HitCount          = 0u
/// \input  roDiag_Callbacks_NRC_Response_HitCount  = 0u
/// \input  roDiag_Callbacks_NRC_Response_Param1    = 0u
///
///   - Expectations:
/// \output DiagControl_boProgramingReq_Status      = TRUE
/// \output roDiag_Callbacks_NRC_Response_HitCount  = 0u
/// \output roDiag_Callbacks_NRC_Response_Param1    = 0u
/// \output LPTMR0_GetTimeElapsed_HitCount          = 1u
/// \output LPTMR0_GetTimeElapsed_RetVal            = 0u
///
//-----------------------------------------------------------------------------
void Mt_rpDiagControl_Cycle0_TestCase2(void)
{
  //Step 1: Set pre-conditions
  // none

  //Step 2) Assign Input values
  DiagControl_boProgramingReq_Status      = TRUE;
  roDiag_IntegrationMode_RetVal           = FALSE;
  DiagControl_ulTmrProgSessison           = 0u;
  LPTMR0_GetTimeElapsed_RetVal            = 0u;
  roDiag_Callbacks_NRC_Response_HitCount  = 0u;
  roDiag_Callbacks_NRC_Response_Param1    = 0u;

  //Step 3) Call FUT
  rpDiagControl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DiagControl_boProgramingReq_Status,       TRUE, == );
  AL_UNITTEST_CHECK(roDiag_Callbacks_NRC_Response_HitCount,     0u, == );
  AL_UNITTEST_CHECK(roDiag_Callbacks_NRC_Response_Param1,       0u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpDiagControl_Cycle0_TestCase3
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the Programming Request Status is TRUE, but
///                     the Integration Mode is false, and the Timer for giving
///                     NRC 0x22 has expired and NRC is given out.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  DiagControl_boProgramingReq_Status      = TRUE
/// \input  roDiag_IntegrationMode_RetVal           = FALSE
/// \input  DiagControl_ulTmrProgSessison           = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal            = 1000001u
/// \input  LPTMR0_GetTimeElapsed_HitCount          = 0u
/// \input  roDiag_Callbacks_NRC_Response_HitCount  = 0u
/// \input  roDiag_Callbacks_NRC_Response_Param1    = 0u
///
///   - Expectations:
/// \output DiagControl_boProgramingReq_Status      = FALSE
/// \output roDiag_Callbacks_NRC_Response_HitCount  = 1u
/// \output roDiag_Callbacks_NRC_Response_Param1    = 0x22U
/// \output LPTMR0_GetTimeElapsed_HitCount          = 1u
/// \output LPTMR0_GetTimeElapsed_RetVal            = 1000001u
///
//-----------------------------------------------------------------------------
void Mt_rpDiagControl_Cycle0_TestCase3(void)
{
  //Step 1: Set pre-conditions
  // none

  //Step 2) Assign Input values
  DiagControl_boProgramingReq_Status      = TRUE;
  roDiag_IntegrationMode_RetVal           = FALSE;
  DiagControl_ulTmrProgSessison           = 0u;
  LPTMR0_GetTimeElapsed_RetVal            = 1000001u;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  roDiag_Callbacks_NRC_Response_HitCount  = 0u;
  roDiag_Callbacks_NRC_Response_Param1    = 0u;

  //Step 3) Call FUT
  rpDiagControl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DiagControl_boProgramingReq_Status,          FALSE, == );
  AL_UNITTEST_CHECK(roDiag_Callbacks_NRC_Response_HitCount,         1u, == );
  AL_UNITTEST_CHECK(roDiag_Callbacks_NRC_Response_Param1,        0x22U, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_RetVal,             1000001u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpDiagControl_Cycle0_TestCase4
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the Programming Request Status is TRUE and the
///                     Integration Mode is met and that the Programming Session 
///                     is accepted and the status is reset.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  roDiag_Callbacks_ProgramingSessionAccepted_HitCount  = 0u
/// \input  DiagControl_boProgramingReq_Status                   = TRUE
/// \input  roDiag_IntegrationMode_RetVal                        = TRUE
/// \input  DiagControl_ulTmrProgSessison                        = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                         = 0u
/// \input  LPTMR0_GetTimeElapsed_HitCount                       = 0u
/// \input  roDiag_Callbacks_NRC_Response_HitCount               = 0u
/// \input  roDiag_Callbacks_NRC_Response_Param1                 = 0u
///
///   - Expectations:
/// \output roDiag_Callbacks_ProgramingSessionAccepted_HitCount  = 1u
/// \output DiagControl_boProgramingReq_Status                   = FALSE
/// \output roDiag_Callbacks_NRC_Response_HitCount               = 0u
/// \output roDiag_Callbacks_NRC_Response_Param1                 = 0u
/// \output LPTMR0_GetTimeElapsed_HitCount                       = 0u
/// \output LPTMR0_GetTimeElapsed_RetVal                         = 0u
///
//-----------------------------------------------------------------------------
void Mt_rpDiagControl_Cycle0_TestCase4(void)
{
  //Step 1: Set pre-conditions
  // none

  //Step 2) Assign Input values
  roDiag_Callbacks_ProgramingSessionAccepted_HitCount  = 0u;
  DiagControl_boProgramingReq_Status                   = TRUE;
  roDiag_IntegrationMode_RetVal                        = TRUE;
  DiagControl_ulTmrProgSessison                        = 0u;
  LPTMR0_GetTimeElapsed_RetVal                         = 0u;
  LPTMR0_GetTimeElapsed_HitCount                       = 0u;
  roDiag_Callbacks_NRC_Response_HitCount               = 0u;
  roDiag_Callbacks_NRC_Response_Param1                 = 0u;

  //Step 3) Call FUT
  rpDiagControl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(roDiag_Callbacks_ProgramingSessionAccepted_HitCount,      1u, == );
  AL_UNITTEST_CHECK(DiagControl_boProgramingReq_Status,                    FALSE, == );
  AL_UNITTEST_CHECK(roDiag_Callbacks_NRC_Response_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(roDiag_Callbacks_NRC_Response_Param1,                     0u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                           0u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_RetVal,                             0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpDiagControl_Cycle0
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Test that the request to enter Programming Session is Accepted
///                     based on the Integration Mode, and if not , that the NRC 0x22
///                     is given out every 1 second.
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_rpDiagControl_Cycle0(void)
{
  Mt_rpDiagControl_Cycle0_TestCase1();
  Mt_rpDiagControl_Cycle0_TestCase2();
  Mt_rpDiagControl_Cycle0_TestCase3();
  Mt_rpDiagControl_Cycle0_TestCase4();
}


//-----------------------------------------------------------------------------
//  DiagControl.c
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_DiagControl_ProgrammingSesion_Request
///
/// \Functional Safety: QM
///
/// \Test Case Description
///    - Test subject:  Check that the Programming Session Request API is called
///                     and that the Status flag is set to TRUE and the timer is started.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  DiagControl_boProgramingReq_Status  = FALSE
/// \input  LPTMR0_GetTimeElapsed_RetVal        = 0u
/// \input    LPTMR0_GetTimeElapsed_HitCount    = 0u
///
///   - Expectations:
/// \output DiagControl_boProgramingReq_Status  = TRUE
/// \output DiagControl_ulTmrProgSessison       = 0u
/// \output LPTMR0_GetTimeElapsed_RetVal        = 0u
/// \output LPTMR0_GetTimeElapsed_HitCount      = 1u
///
//-----------------------------------------------------------------------------
void Mt_DiagControl_ProgrammingSesion_Request(void)
{
  //Step 1: Set pre-conditions
  // none

  //Step 2) Assign Input values
  DiagControl_boProgramingReq_Status  = FALSE;
  LPTMR0_GetTimeElapsed_RetVal        = 0u;
  LPTMR0_GetTimeElapsed_HitCount      = 0u;

  //Step 3) Call FUT
  DiagControl_ProgrammingSesion_Request();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DiagControl_boProgramingReq_Status,   TRUE, == );
  AL_UNITTEST_CHECK(DiagControl_ulTmrProgSessison,          0u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_RetVal,           0u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,         1u, == );
}


//-----------------------------------------------------------------------------
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
  /* ctaaDiagControl.c */
  ALUnitTest_AddFunction("Mt_riDiagControl_Init",     Mt_riDiagControl_Init);
  ALUnitTest_AddFunction("Mt_rpDiagControl_Cycle0",   Mt_rpDiagControl_Cycle0);

  /* DiagControl.c */
  ALUnitTest_AddFunction("Mt_DiagControl_ProgrammingSesion_Request",   Mt_DiagControl_ProgrammingSesion_Request);
}


// EOF

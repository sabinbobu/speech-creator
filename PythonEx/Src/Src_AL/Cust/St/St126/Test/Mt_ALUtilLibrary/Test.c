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
/// \file  Test.c
///
/// \brief Module test of ALUtilLibrary
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemClr
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if UtilMemClr Clear Memory with 0 values,
///                    using 16/32 Bit access.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemClr_Param1 = 0u
/// \input  UtilMemClr_Param2 = 0u
///
/// - Expectations:
///
/// \output UtilMemClr_Param1 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemClr(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemClr_Param1 = 0u;
  UtilMemClr_Param2 = 0u;

  //Step 3) Call FUT
  UtilMemClr(&UtilMemClr_Param1, UtilMemClr_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemClr_Param1, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemSet_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemSet sets the memory
///                        with the specified ucData byte.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemSet_Param1 = 0u
/// \input  UtilMemSet_Param2 = 0u
/// \input  UtilMemSet_Param3 = 0u
///
/// - Expectations:
///
/// \output UtilMemSet_Param1 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemSet_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemSet_Param1[0] = 0u;
  UtilMemSet_Param2 = 0u;
  UtilMemSet_Param3 = 0u;

  //Step 3) Call FUT
  UtilMemSet(UtilMemSet_Param1, UtilMemSet_Param2, UtilMemSet_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemSet_Param1[0], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemSet_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemSet sets the memory
///                        with the specified ucData byte.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemSet_Param1 = 1u
/// \input  UtilMemSet_Param2 = 0u
/// \input  UtilMemSet_Param3 = 3u
///
/// - Expectations:
///
/// \output UtilMemSet_Param1 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemSet_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  for (uint8 ucIx = 0; ucIx < 3; ucIx++)
  {
    UtilMemSet_Param1[ucIx] = 1u;
  }
  UtilMemSet_Param2 = 0u;
  UtilMemSet_Param3 = 3u;

  //Step 3) Call FUT
  UtilMemSet(&UtilMemSet_Param1[0], UtilMemSet_Param2, UtilMemSet_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemSet_Param1[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMemSet_Param1[1], 0u, == );
  AL_UNITTEST_CHECK(UtilMemSet_Param1[2], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemSet
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if UtilMemSet sets the memory
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemSet(void)
{
  Mt_ALUtilLibrary_UtilMemSet_TestCase_1();
  Mt_ALUtilLibrary_UtilMemSet_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCopy_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemCopy copies to memory.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemCopy_Param1 = 0u
/// \input  UtilMemCopy_Param2 = 0u
/// \input  UtilMemCopy_Param3 = 0u
///
/// - Expectations:
///
/// \output UtilMemCopy_Param1 = 0u
/// \output UtilMemCopy_Param2 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCopy_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemCopy_Param1[0] = 0u;
  UtilMemCopy_Param2[0] = 0u;
  UtilMemCopy_Param3    = 0u;

  //Step 3) Call FUT
  UtilMemCopy(UtilMemCopy_Param1, UtilMemCopy_Param2, UtilMemCopy_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_Param1[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_Param2[0], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCopy_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemCopy copies to memory.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemCopy_Param1 = 1u
/// \input  UtilMemCopy_Param2 = 0u
/// \input  UtilMemCopy_Param3 = 1u
///
/// - Expectations:
///
/// \output UtilMemCopy_Param1 = 0u
/// \output UtilMemCopy_Param2 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCopy_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  for (uint8 ucIx = 0; ucIx < 3; ucIx++)
  {
    UtilMemCopy_Param1[ucIx] = 1u;
  }
  for (uint8 ucIx = 0; ucIx < 3; ucIx++)
  {
    UtilMemCopy_Param2[ucIx] = 0u;
  }
  UtilMemCopy_Param3 = 3u;

  //Step 3) Call FUT
  UtilMemCopy(&UtilMemCopy_Param1[0], &UtilMemCopy_Param2[0], UtilMemCopy_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_Param1[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_Param1[1], 0u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_Param1[2], 0u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_Param2[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_Param2[1], 0u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_Param2[2], 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCopy
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if UtilMemCopy copies to memory
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCopy(void)
{
  Mt_ALUtilLibrary_UtilMemCopy_TestCase_1();
  Mt_ALUtilLibrary_UtilMemCopy_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCmp_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemCmp Compares  its  arguments.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemCmp_Param1 = 0u
/// \input  UtilMemCmp_Param2 = 0u
/// \input  UtilMemCmp_Param3 = 0u
///
/// - Expectations:
///
/// \output UtilMemCmp_RetVal = 0u
/// \output UtilMemCmp_Param1 = 0u
/// \output UtilMemCmp_Param2 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCmp_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemCmp_Param1 = 0u;
  UtilMemCmp_Param2 = 0u;
  UtilMemCmp_Param3 = 0u;

  //Step 3) Call FUT
  UtilMemCmp_RetVal = UtilMemCmp(&UtilMemCmp_Param1, &UtilMemCmp_Param2, UtilMemCmp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCmp_RetVal, 0u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param1, 0u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param2, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCmp_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemCmp Compares  its  arguments.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemCmp_Param1 = 0u
/// \input  UtilMemCmp_Param2 = 0u
/// \input  UtilMemCmp_Param3 = 1u
///
/// - Expectations:
///
/// \output UtilMemCmp_RetVal = 0u
/// \output UtilMemCmp_Param1 = 0u
/// \output UtilMemCmp_Param2 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCmp_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemCmp_Param1 = 0u;
  UtilMemCmp_Param2 = 0u;
  UtilMemCmp_Param3 = 1u;

  //Step 3) Call FUT
  UtilMemCmp_RetVal = UtilMemCmp(&UtilMemCmp_Param1, &UtilMemCmp_Param2, UtilMemCmp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCmp_RetVal, 0u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param1, 0u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param2, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCmp_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemCmp Compares  its  arguments.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemCmp_Param1 = 1u
/// \input  UtilMemCmp_Param2 = 0u
/// \input  UtilMemCmp_Param3 = 1u
///
/// - Expectations:
///
/// \output UtilMemCmp_RetVal = 1u
/// \output UtilMemCmp_Param1 = 1u
/// \output UtilMemCmp_Param2 = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCmp_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemCmp_Param1 = 1u;
  UtilMemCmp_Param2 = 0u;
  UtilMemCmp_Param3 = 1u;

  //Step 3) Call FUT
  UtilMemCmp_RetVal = UtilMemCmp(&UtilMemCmp_Param1, &UtilMemCmp_Param2, UtilMemCmp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCmp_RetVal, 1u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param1, 1u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param2, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCmp_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if UtilMemCmp Compares  its  arguments.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMemCmp_Param1 = 0u
/// \input  UtilMemCmp_Param2 = 1u
/// \input  UtilMemCmp_Param3 = 1u
///
/// - Expectations:
///
/// \output UtilMemCmp_RetVal = -1
/// \output UtilMemCmp_Param1 = 0u
/// \output UtilMemCmp_Param2 = 1u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCmp_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilMemCmp_Param1 = 0u;
  UtilMemCmp_Param2 = 1u;
  UtilMemCmp_Param3 = 1u;

  //Step 3) Call FUT
  UtilMemCmp_RetVal = UtilMemCmp(&UtilMemCmp_Param1, &UtilMemCmp_Param2, UtilMemCmp_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCmp_RetVal, -1, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param1, 0u, == );
  AL_UNITTEST_CHECK(UtilMemCmp_Param2, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMemCmp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if UtilMemCmp Compares  its  arguments
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMemCmp(void)
{
  Mt_ALUtilLibrary_UtilMemCmp_TestCase_1();
  Mt_ALUtilLibrary_UtilMemCmp_TestCase_2();
  Mt_ALUtilLibrary_UtilMemCmp_TestCase_3();
  Mt_ALUtilLibrary_UtilMemCmp_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_Off value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_Off
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_Off
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState         = Di_Off;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce     = 0u;
  UtilDebounce_Param2                = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_Off, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_Off
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_Off
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OnDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_Off;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OnDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_Sna
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_Sna
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OffDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = FALSE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_Sna;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OffDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, FALSE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_Sna
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_Sna
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OnDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = FALSE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_Sna;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OnDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, FALSE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for invalid state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = 5
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OnDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = FALSE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = 5;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OnDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, FALSE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works forDi_OnDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OnDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_Sna
/// \output UtilDebounce_Param1.sValFlt.bValid   = FALSE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_6(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OnDelay;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_Sna, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, FALSE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OnDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OnDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_Off
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_7(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OnDelay;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_Off, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OnDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OnDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_On
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_8(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OnDelay;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_On, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OnDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OnDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 1u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OnDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 1u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_9(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OnDelay;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 1u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OnDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_On state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_On
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 1u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OffDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_10(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_On;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 1u;
  UtilDebounce_Param2 = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OffDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_On state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_On
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 1u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_On
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 1u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_11(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_On;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 1u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_On, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_12
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OffDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OffDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 1u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_On
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 1u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_12(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OffDelay;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 1u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_On, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_13
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OffDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OffDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = TRUE
/// \input  UtilDebounce_Param1.tiDebounce     = 1u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_OffDelay
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 1u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_13(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OffDelay;
  UtilDebounce_Param1.sValFlt.bValid = TRUE;
  UtilDebounce_Param1.tiDebounce = 1u;
  UtilDebounce_Param2 = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_OffDelay, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_14
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OffDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OffDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 1u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_Sna
/// \output UtilDebounce_Param1.sValFlt.bValid   = FALSE
/// \output UtilDebounce_Param1.tiDebounce       = 1u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_14(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OffDelay;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 1u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_Sna, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, FALSE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_15
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OffDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OffDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = TRUE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_Sna
/// \output UtilDebounce_Param1.sValFlt.bValid   = FALSE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_15(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OffDelay;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = TRUE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_Sna, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, FALSE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce_TestCase_16
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if debounce function works for Di_OffDelay state
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounce_Param1.eState         = Di_OffDelay
/// \input  UtilDebounce_Param1.sValFlt.bValid = FALSE
/// \input  UtilDebounce_Param1.tiDebounce     = 0u
/// \input  UtilDebounce_Param2                = FALSE
///
/// - Expectations:
///
/// \output UtilDebounce_Param1.eState           = Di_Off
/// \output UtilDebounce_Param1.sValFlt.bValid   = TRUE
/// \output UtilDebounce_Param1.tiDebounce       = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce_TestCase_16(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  UtilDebounce_Param1.eState = Di_OffDelay;
  UtilDebounce_Param1.sValFlt.bValid = FALSE;
  UtilDebounce_Param1.tiDebounce = 0u;
  UtilDebounce_Param2 = FALSE;

  //Step 3) Call FUT
  UtilDebounce(&UtilDebounce_Param1, UtilDebounce_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounce_Param1.eState, Di_Off, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.sValFlt.bValid, TRUE, == );
  AL_UNITTEST_CHECK(UtilDebounce_Param1.tiDebounce, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounce
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if debounce function works for every state
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounce(void)
{
  Mt_ALUtilLibrary_UtilDebounce_TestCase_1();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_2();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_3();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_4();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_5();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_6();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_7();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_8();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_9();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_10();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_11();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_12();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_13();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_14();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_15();
  Mt_ALUtilLibrary_UtilDebounce_TestCase_16();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounceReset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function resets debounced signal
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounceReset_Param1.eState              = 0u
/// \input  UtilDebounceReset_Param1.tiDebounce          = 0u
/// \input  UtilDebounceReset_Param1.sValFlt.bVal        = 0u
/// \input  UtilDebounceReset_Param1.sValFlt.bPosEdge    = 0u
/// \input  UtilDebounceReset_Param1.sValFlt.bNegEdge    = 0u
/// \input  UtilDebounceReset_Param1.sValFlt.bValid      = 0u
/// \input  UtilDebounceReset_Param1.sValFlt.bValLatched = 0u
/// \input  UtilDebounceReset_Param1.tOnDelay            = 0u
/// \input  UtilDebounceReset_Param1.tOffDelay           = 0u
/// \input  UtilDebounceReset_Param2                     = 0u
///
/// - Expectations:
///
/// \output UtilDebounceReset_Param1.eState              = 0u
/// \output UtilDebounceReset_Param1.tiDebounce          = 0u
/// \output UtilDebounceReset_Param1.sValFlt.bVal        = 0u
/// \output UtilDebounceReset_Param1.sValFlt.bPosEdge    = 0u
/// \output UtilDebounceReset_Param1.sValFlt.bNegEdge    = 0u
/// \output UtilDebounceReset_Param1.sValFlt.bValid      = 1u
/// \output UtilDebounceReset_Param1.sValFlt.bValLatched = 0u
/// \output UtilDebounceReset_Param1.tOnDelay            = 0u
/// \output UtilDebounceReset_Param1.tOffDelay           = 0u
/// \output UtilDebounceReset_Param2                     = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounceReset(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilDebounceReset_Param1.eState              = 0u;
  UtilDebounceReset_Param1.tiDebounce          = 0u;
  UtilDebounceReset_Param1.sValFlt.bVal        = 0u;
  UtilDebounceReset_Param1.sValFlt.bPosEdge    = 0u;
  UtilDebounceReset_Param1.sValFlt.bNegEdge    = 0u;
  UtilDebounceReset_Param1.sValFlt.bValid      = 0u;
  UtilDebounceReset_Param1.sValFlt.bValLatched = 0u;
  UtilDebounceReset_Param1.tOnDelay            = 0u;
  UtilDebounceReset_Param1.tOffDelay           = 0u;
  UtilDebounceReset_Param2                     = 0u;

  //Step 3) Call FUT

  UtilDebounceReset(&UtilDebounceReset_Param1, UtilDebounceReset_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.eState, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.tiDebounce, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.sValFlt.bVal, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.sValFlt.bPosEdge, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.sValFlt.bNegEdge, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.sValFlt.bValid, 1u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.sValFlt.bValLatched, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.tOnDelay, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param1.tOffDelay, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceReset_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilDebounceInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function initializes debounced signal
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilDebounceInit_Param1.eState              = 0u
/// \input  UtilDebounceInit_Param1.tiDebounce          = 0u
/// \input  UtilDebounceInit_Param1.sValFlt.bVal        = 0u
/// \input  UtilDebounceInit_Param1.sValFlt.bPosEdge    = 0u
/// \input  UtilDebounceInit_Param1.sValFlt.bNegEdge    = 0u
/// \input  UtilDebounceInit_Param1.sValFlt.bValid      = 0u
/// \input  UtilDebounceInit_Param1.sValFlt.bValLatched = 0u
/// \input  UtilDebounceInit_Param1.tOnDelay            = 0u
/// \input  UtilDebounceInit_Param1.tOffDelay           = 0u
/// \input  UtilDebounceInit_Param2                     = 0u
/// \input  UtilDebounceInit_Param3                     = 0u
/// \input  UtilDebounceInit_Param4                     = 0u
///
/// - Expectations:
///
/// \output UtilDebounceInit_Param1.eState              = 0u
/// \output UtilDebounceInit_Param1.tiDebounce          = 0u
/// \output UtilDebounceInit_Param1.sValFlt.bVal        = 0u
/// \output UtilDebounceInit_Param1.sValFlt.bPosEdge    = 0u
/// \output UtilDebounceInit_Param1.sValFlt.bNegEdge    = 0u
/// \output UtilDebounceInit_Param1.sValFlt.bValid      = 1u
/// \output UtilDebounceInit_Param1.sValFlt.bValLatched = 0u
/// \output UtilDebounceInit_Param1.tOnDelay            = 0u
/// \output UtilDebounceInit_Param1.tOffDelay           = 0u
/// \output UtilDebounceInit_Param2                     = 0u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilDebounceInit(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values
  UtilDebounceInit_Param1.eState = 0u;
  UtilDebounceInit_Param1.tiDebounce = 0u;
  UtilDebounceInit_Param1.sValFlt.bVal = 0u;
  UtilDebounceInit_Param1.sValFlt.bPosEdge = 0u;
  UtilDebounceInit_Param1.sValFlt.bNegEdge = 0u;
  UtilDebounceInit_Param1.sValFlt.bValid = 0u;
  UtilDebounceInit_Param1.sValFlt.bValLatched = 0u;
  UtilDebounceInit_Param1.tOnDelay = 0u;
  UtilDebounceInit_Param1.tOffDelay = 0u;
  UtilDebounceInit_Param2 = 0u;
  UtilDebounceInit_Param3 = 0u;
  UtilDebounceInit_Param4 = 0u;

  //Step 3) Call FUT

  UtilDebounceInit(&UtilDebounceInit_Param1, UtilDebounceInit_Param2, UtilDebounceInit_Param3, UtilDebounceInit_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.eState, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.tiDebounce, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.sValFlt.bVal, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.sValFlt.bPosEdge, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.sValFlt.bNegEdge, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.sValFlt.bValid, 1u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.sValFlt.bValLatched, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.tOnDelay, 0u, == );
  AL_UNITTEST_CHECK(UtilDebounceInit_Param1.tOffDelay, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1Filter32
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Lowpass 1st order for external call
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1Filter32_Param1           = 0u
/// \input Order1Filter32_Param2           = 0u
/// \input Order1Filter32_Param3           = 0u
///
/// - Expectations:
///
/// \output Order1Filter32_Param1          = 0u
/// \output Order1Filter32_RetVal          = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1Filter32(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1Filter32_Param1 = 0u;
  Order1Filter32_Param2 = 0u;
  Order1Filter32_Param3 = 0u;

  //Step 3) Call FUT

  Order1Filter32_RetVal = Order1Filter32(&Order1Filter32_Param1, Order1Filter32_Param2, Order1Filter32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1Filter32_Param1, 0u, == );
  AL_UNITTEST_CHECK(Order1Filter32_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_LowPass1Filter32_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Lowpass 1st order for external call
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LowPass1Filter32_Param1           = 0u
/// \input LowPass1Filter32_Param2           = 0u
/// \input LowPass1Filter32_Param3           = 0u
///
/// - Expectations:
///
/// \output LowPass1Filter32_Param1          = 0u
/// \output LowPass1Filter32_RetVal          = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_LowPass1Filter32_TestCase_1(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LowPass1Filter32_Param1 = 0u;
  LowPass1Filter32_Param2 = 0u;
  LowPass1Filter32_Param3 = 0u;

  //Step 3) Call FUT

  LowPass1Filter32_RetVal = LowPass1Filter32(&LowPass1Filter32_Param1, LowPass1Filter32_Param2, LowPass1Filter32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LowPass1Filter32_Param1, 0u, == );
  AL_UNITTEST_CHECK(LowPass1Filter32_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_LowPass1Filter32_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Lowpass 1st order for external call
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LowPass1Filter32_Param1           = 0u
/// \input LowPass1Filter32_Param2           = 1u
/// \input LowPass1Filter32_Param3           = 1u
///
/// - Expectations:
///
/// \output LowPass1Filter32_Param1          = 508u
/// \output LowPass1Filter32_RetVal          = 1u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_LowPass1Filter32_TestCase_2(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LowPass1Filter32_Param1 = 0u;
  LowPass1Filter32_Param2 = 1u;
  LowPass1Filter32_Param3 = 1u;

  //Step 3) Call FUT

  LowPass1Filter32_RetVal = LowPass1Filter32(&LowPass1Filter32_Param1, LowPass1Filter32_Param2, LowPass1Filter32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LowPass1Filter32_Param1, 508u, == );
  AL_UNITTEST_CHECK(LowPass1Filter32_RetVal,   1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_LowPass1Filter32
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if this function Lowpass 1st order for external call
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_LowPass1Filter32(void)
{
  Mt_ALUtilLibrary_LowPass1Filter32_TestCase_1();
  Mt_ALUtilLibrary_LowPass1Filter32_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_LowPass1FilterInit32
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Initialize filter variable by 
///                        scaling input value, near function for internal use.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LowPass1FilterInit32_Param1           = 0u
/// \input LowPass1FilterInit32_Param2           = 0u
///
/// - Expectations:
///
/// \output Order1Filter32_Param1          = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_LowPass1FilterInit32(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LowPass1FilterInit32_Param1 = 0u;
  LowPass1FilterInit32_Param2 = 0;

  //Step 3) Call FUT
  
  LowPass1FilterInit32(&LowPass1FilterInit32_Param1, LowPass1FilterInit32_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LowPass1FilterInit32_Param1, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Get actual filter output 
///                        value without new filter calculation.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1TrackingFilter32_Param1          = 0
/// \input Order1TrackingFilter32_Param2          = 0u
/// \input Order1TrackingFilter32_Param3          = 0
/// \input Order1TrackingFilter32_Param4          = 0u
///
/// - Expectations:
///
/// \output Order1FilterInit32_Param1          = 0u
/// \output Order1TrackingFilter32_RetVal      = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_1(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1TrackingFilter32_Param1 = 0;
  Order1TrackingFilter32_Param2 = 0u;
  Order1TrackingFilter32_Param3 = 0;
  Order1TrackingFilter32_Param4 = 0u;

  //Step 3) Call FUT

  Order1TrackingFilter32_RetVal = Order1TrackingFilter32(&Order1TrackingFilter32_Param1, Order1TrackingFilter32_Param2, Order1TrackingFilter32_Param3, Order1TrackingFilter32_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param1, 0, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_RetVal, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Get actual filter output 
///                        value without new filter calculation.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1TrackingFilter32_Param1          = 0
/// \input Order1TrackingFilter32_Param2          = 0u
/// \input Order1TrackingFilter32_Param3          = 1
/// \input Order1TrackingFilter32_Param4          = 0u
///
/// - Expectations:
///
/// \output Order1FilterInit32_Param1          = 512u
/// \output Order1TrackingFilter32_RetVal      = 1u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_2(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1TrackingFilter32_Param1 = 0;
  Order1TrackingFilter32_Param2 = 0u;
  Order1TrackingFilter32_Param3 = 1;
  Order1TrackingFilter32_Param4 = 0u;

  //Step 3) Call FUT

  Order1TrackingFilter32_RetVal = Order1TrackingFilter32(&Order1TrackingFilter32_Param1, Order1TrackingFilter32_Param2, Order1TrackingFilter32_Param3, Order1TrackingFilter32_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param1, 512, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_RetVal, 1, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Get actual filter output 
///                        value without new filter calculation.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1TrackingFilter32_Param1          = 1u
/// \input Order1TrackingFilter32_Param2          = 500000u
/// \input Order1TrackingFilter32_Param3          = 0
/// \input Order1TrackingFilter32_Param4          = 1u
///
/// - Expectations:
///
/// \output Order1FilterInit32_Param1          = 512u
/// \output Order1TrackingFilter32_RetVal      = 1u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_3(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1TrackingFilter32_Param1 = 1;
  Order1TrackingFilter32_Param2 = 500000u;
  Order1TrackingFilter32_Param3 = 0;
  Order1TrackingFilter32_Param4 = 1u;

  //Step 3) Call FUT

  Order1TrackingFilter32_RetVal = Order1TrackingFilter32(&Order1TrackingFilter32_Param1, Order1TrackingFilter32_Param2, Order1TrackingFilter32_Param3, Order1TrackingFilter32_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1TrackingFilter32_Param1, 512, == );
  AL_UNITTEST_CHECK(Order1TrackingFilter32_RetVal, 1, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1TrackingFilter32
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if function gets actual filter output value without new filter calculation
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1TrackingFilter32(void)
{
  Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_1();
  Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_2();
  Mt_ALUtilLibrary_Order1TrackingFilter32_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_FirFilter32_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function FIR filter implementation,
///                        supports variable filter length, 32 bit code.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input FirFilter32_Param1          = 0
/// \input FirFilter32_Param2          = 0
/// \input FirFilter32_Param3          = 0
///
/// - Expectations:
///
/// \output FirFilter32_RetVal         = 0
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_FirFilter32_TestCase_1(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  FirFilter32_Param1[0] = 0;
  FirFilter32_Param2 = 0;
  FirFilter32_Param3 = 0;

  //Step 3) Call FUT

  FirFilter32_RetVal = FirFilter32(FirFilter32_Param1, FirFilter32_Param2, FirFilter32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FirFilter32_RetVal, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_FirFilter32_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function FIR filter implementation,
///                        supports variable filter length, 32 bit code.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   FirFilter32_Param1[0] = 0u
/// \input   FirFilter32_Param1[1] = 0u
/// \input   FirFilter32_Param2    = 2u
/// \input   FirFilter32_Param3    = 0u
///
/// - Expectations:
///
/// \output FirFilter32_RetVal         = 0
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_FirFilter32_TestCase_2(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  FirFilter32_Param1[0] = 0u;
  FirFilter32_Param1[1] = 0u;
  FirFilter32_Param2    = 2u;
  FirFilter32_Param3    = 0u;

  //Step 3) Call FUT

  FirFilter32_RetVal = FirFilter32(FirFilter32_Param1, FirFilter32_Param2, FirFilter32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FirFilter32_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_FirFilter32_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function FIR filter implementation,
///                        supports variable filter length, 32 bit code.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input FirFilter32_Param1          = 0
/// \input FirFilter32_Param2          = 0
/// \input FirFilter32_Param3          = 0
///
/// - Expectations:
///
/// \output FirFilter32_RetVal         = 0
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_FirFilter32_TestCase_3(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  FirFilter32_Param1[0] = 0;
  FirFilter32_Param1[1] = 0;
  FirFilter32_Param2 = 0;
  FirFilter32_Param3 = 0;

  //Step 3) Call FUT

  FirFilter32_RetVal = FirFilter32(FirFilter32_Param1, FirFilter32_Param2, FirFilter32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FirFilter32_RetVal, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_FirFilter32
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if filters correctly
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_FirFilter32(void)
{
  Mt_ALUtilLibrary_FirFilter32_TestCase_1();
  Mt_ALUtilLibrary_FirFilter32_TestCase_2();
  Mt_ALUtilLibrary_FirFilter32_TestCase_3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolateU16_Param1[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param3          = 0u
/// \input UtilMath_LinearInterpolateU16_Param4          = 0u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateU16_Param1[0]          = 0u
/// \output UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \output UtilMath_LinearInterpolateU16_RetVal         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_1(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

 UtilMath_LinearInterpolateU16_Param1[0] = 0u;
 UtilMath_LinearInterpolateU16_Param2[0] = 0u;
 UtilMath_LinearInterpolateU16_Param3 = 0u;
 UtilMath_LinearInterpolateU16_Param4 = 0u;

  //Step 3) Call FUT

 UtilMath_LinearInterpolateU16_RetVal = UtilMath_LinearInterpolateU16(&UtilMath_LinearInterpolateU16_Param1[0], &UtilMath_LinearInterpolateU16_Param2[0], UtilMath_LinearInterpolateU16_Param3, UtilMath_LinearInterpolateU16_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolateU16_Param1[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param3          = 3u
/// \input UtilMath_LinearInterpolateU16_Param4          = 1u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateU16_Param1[0]          = 0u
/// \output UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \output UtilMath_LinearInterpolateU16_RetVal         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_2(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolateU16_Param1[0] = 0u;
  UtilMath_LinearInterpolateU16_Param2[0] = 0u;
  UtilMath_LinearInterpolateU16_Param3 = 3u;
  UtilMath_LinearInterpolateU16_Param4 = 1u;

  //Step 3) Call FUT

  UtilMath_LinearInterpolateU16_RetVal = UtilMath_LinearInterpolateU16(&UtilMath_LinearInterpolateU16_Param1[0], &UtilMath_LinearInterpolateU16_Param2[0], UtilMath_LinearInterpolateU16_Param3, UtilMath_LinearInterpolateU16_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolateU16_Param1[8]          = 3u
/// \input UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param3          = 9u
/// \input UtilMath_LinearInterpolateU16_Param4          = 1u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateU16_Param1[8]          = 3u
/// \output UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \output UtilMath_LinearInterpolateU16_RetVal         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_3(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolateU16_Param1[8] = 3u;
  UtilMath_LinearInterpolateU16_Param2[0] = 0u;
  UtilMath_LinearInterpolateU16_Param3 = 9u;
  UtilMath_LinearInterpolateU16_Param4 = 1u;

  //Step 3) Call FUT

  UtilMath_LinearInterpolateU16_RetVal = UtilMath_LinearInterpolateU16(&UtilMath_LinearInterpolateU16_Param1[0], &UtilMath_LinearInterpolateU16_Param2[0], UtilMath_LinearInterpolateU16_Param3, UtilMath_LinearInterpolateU16_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[8], 3u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolateU16_Param1[8]          = 3u
/// \input UtilMath_LinearInterpolateU16_Param1[4]          = 3u
/// \input UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param3          = 9u
/// \input UtilMath_LinearInterpolateU16_Param4          = 1u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateU16_Param1[8]          = 3u
/// \output UtilMath_LinearInterpolateU16_Param1[4]          = 3u
/// \output UtilMath_LinearInterpolateU16_Param2[0]          = 0u
/// \output UtilMath_LinearInterpolateU16_RetVal         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_4(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolateU16_Param1[8] = 3u;
  UtilMath_LinearInterpolateU16_Param1[4] = 3u;
  UtilMath_LinearInterpolateU16_Param2[0] = 0u;
  UtilMath_LinearInterpolateU16_Param3 = 9u;
  UtilMath_LinearInterpolateU16_Param4 = 1u;

  //Step 3) Call FUT

  UtilMath_LinearInterpolateU16_RetVal = UtilMath_LinearInterpolateU16(&UtilMath_LinearInterpolateU16_Param1[0], &UtilMath_LinearInterpolateU16_Param2[0], UtilMath_LinearInterpolateU16_Param3, UtilMath_LinearInterpolateU16_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[8], 3u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[4], 3u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolateU16_Param1[0]          = 0u
/// \input UtilMath_LinearInterpolateU16_Param1[1]          = 1u
/// \input UtilMath_LinearInterpolateU16_Param1[2]          = 2u
/// \input UtilMath_LinearInterpolateU16_Param2[0]          = 4u
/// \input UtilMath_LinearInterpolateU16_Param2[1]          = 3u
/// \input UtilMath_LinearInterpolateU16_Param2[2]          = 2u
/// \input UtilMath_LinearInterpolateU16_Param3             = 3u
/// \input UtilMath_LinearInterpolateU16_Param4             = 1u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolateU16_Param1[0]         = 0u
/// \output UtilMath_LinearInterpolateU16_Param1[1]         = 1u
/// \output UtilMath_LinearInterpolateU16_Param1[2]         = 2u
/// \output UtilMath_LinearInterpolateU16_Param2[0]         = 4u
/// \output UtilMath_LinearInterpolateU16_Param2[1]         = 3u
/// \output UtilMath_LinearInterpolateU16_Param2[2]         = 2u
/// \output UtilMath_LinearInterpolateU16_RetVal            = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_5(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolateU16_Param1[0] = 0u;
  UtilMath_LinearInterpolateU16_Param1[1] = 1u;
  UtilMath_LinearInterpolateU16_Param1[2] = 2u;
  UtilMath_LinearInterpolateU16_Param2[0] = 4u;
  UtilMath_LinearInterpolateU16_Param2[1] = 3u;
  UtilMath_LinearInterpolateU16_Param2[2] = 2u;
  UtilMath_LinearInterpolateU16_Param3 = 3u;
  UtilMath_LinearInterpolateU16_Param4 = 1u;

  //Step 3) Call FUT

  UtilMath_LinearInterpolateU16_RetVal = UtilMath_LinearInterpolateU16(&UtilMath_LinearInterpolateU16_Param1[0], &UtilMath_LinearInterpolateU16_Param2[0], UtilMath_LinearInterpolateU16_Param3, UtilMath_LinearInterpolateU16_Param4);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[0], 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[1], 1u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param1[2], 2u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[0], 4u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[1], 3u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_Param2[2], 2u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolateU16_RetVal, 3u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if the function interpolates a table of points using linear interpolation rule
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16(void)
{
  Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_1();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_2();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_3();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_4();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolate_Param1[0].X          = 0
/// \input UtilMath_LinearInterpolate_Param1[0].Y          = 0
/// \input UtilMath_LinearInterpolate_Param2            = 0
/// \input UtilMath_LinearInterpolate_Param3            = 0
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolate_Param1[0].X         = 0u
/// \output UtilMath_LinearInterpolate_Param1[0].Y         = 0u
/// \output UtilMath_LinearInterpolate_RetVal           = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_1(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolate_Param1[0].X = 0;
  UtilMath_LinearInterpolate_Param1[0].Y = 0;
  UtilMath_LinearInterpolate_Param2   = 0;
  UtilMath_LinearInterpolate_Param3   = 0;

  //Step 3) Call FUT

  UtilMath_LinearInterpolate_RetVal = UtilMath_LinearInterpolate(&UtilMath_LinearInterpolate_Param1[0], UtilMath_LinearInterpolate_Param2, UtilMath_LinearInterpolate_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].X, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].Y, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_RetVal,   0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolate_Param1[0].X          = 0
/// \input UtilMath_LinearInterpolate_Param1[0].Y          = 0
/// \input UtilMath_LinearInterpolate_Param2            = 3
/// \input UtilMath_LinearInterpolate_Param3            = 1
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolate_Param1[0].X         = 0u
/// \output UtilMath_LinearInterpolate_Param1[0].Y         = 0u
/// \output UtilMath_LinearInterpolate_RetVal           = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_2(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolate_Param1[0].X = 0;
  UtilMath_LinearInterpolate_Param1[0].Y = 0;
  UtilMath_LinearInterpolate_Param2 = 3;
  UtilMath_LinearInterpolate_Param3 = 1;

  //Step 3) Call FUT

  UtilMath_LinearInterpolate_RetVal = UtilMath_LinearInterpolate(&UtilMath_LinearInterpolate_Param1[0], UtilMath_LinearInterpolate_Param2, UtilMath_LinearInterpolate_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].X, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].Y, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_RetVal, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolate_Param1[0].X          = 0
/// \input UtilMath_LinearInterpolate_Param1[2].X          = 2
/// \input UtilMath_LinearInterpolate_Param1[0].Y          = 0
/// \input UtilMath_LinearInterpolate_Param2            = 3
/// \input UtilMath_LinearInterpolate_Param3            = 1
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolate_Param1[0].X         = 0u
/// \output UtilMath_LinearInterpolate_Param1[0].Y         = 0u
/// \output UtilMath_LinearInterpolate_RetVal           = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_3(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolate_Param1[0].X = 0;
  UtilMath_LinearInterpolate_Param1[2].X = 2;
  UtilMath_LinearInterpolate_Param1[0].Y = 0;
  UtilMath_LinearInterpolate_Param2 = 3;
  UtilMath_LinearInterpolate_Param3 = 1;

  //Step 3) Call FUT

  UtilMath_LinearInterpolate_RetVal = UtilMath_LinearInterpolate(&UtilMath_LinearInterpolate_Param1[0], UtilMath_LinearInterpolate_Param2, UtilMath_LinearInterpolate_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].X, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[2].X, 2, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].Y, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_RetVal, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolate_Param1[0].X           = 0u
/// \input UtilMath_LinearInterpolate_Param1[1].X           = 2u
/// \input UtilMath_LinearInterpolate_Param1[2].X           = 2u
/// \input UtilMath_LinearInterpolate_Param1[0].Y           = 0u
/// \input UtilMath_LinearInterpolate_Param2                = 3u
/// \input UtilMath_LinearInterpolate_Param3                = 1u
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolate_Param1[0].X        = 0u
/// \output UtilMath_LinearInterpolate_Param1[1].X        = 2u
/// \output UtilMath_LinearInterpolate_Param1[2].X        = 2u
/// \output UtilMath_LinearInterpolate_Param1[0].Y        = 0u
/// \output UtilMath_LinearInterpolate_RetVal             = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_4(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolate_Param1[0].X = 0u;
  UtilMath_LinearInterpolate_Param1[1].X = 2u;
  UtilMath_LinearInterpolate_Param1[2].X = 2u;
  UtilMath_LinearInterpolate_Param1[0].Y = 0u;
  UtilMath_LinearInterpolate_Param2      = 3u;
  UtilMath_LinearInterpolate_Param3      = 1u;

  //Step 3) Call FUT

  UtilMath_LinearInterpolate_RetVal = UtilMath_LinearInterpolate(&UtilMath_LinearInterpolate_Param1[0], UtilMath_LinearInterpolate_Param2, UtilMath_LinearInterpolate_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].X, 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[1].X, 2u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[2].X, 2u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].Y, 0u, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_RetVal     , 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function interpolates a table of points using linear interpolation rule.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_LinearInterpolate_Param1[0].X          = 0
/// \input UtilMath_LinearInterpolate_Param1[1].X          = 2
/// \input UtilMath_LinearInterpolate_Param1[2].X          = 2
/// \input UtilMath_LinearInterpolate_Param1[3].X          = 2
/// \input UtilMath_LinearInterpolate_Param1[0].Y          = 3
/// \input UtilMath_LinearInterpolate_Param1[1].Y          = 2
/// \input UtilMath_LinearInterpolate_Param1[2].Y          = 1
/// \input UtilMath_LinearInterpolate_Param1[3].Y          = 0
/// \input UtilMath_LinearInterpolate_Param2            = 3
/// \input UtilMath_LinearInterpolate_Param3            = 1
///
/// - Expectations:
///
/// \output UtilMath_LinearInterpolate_Param1[0].X        = 0
/// \output UtilMath_LinearInterpolate_Param1[1].X        = 2
/// \output UtilMath_LinearInterpolate_Param1[2].X        = 2
/// \output UtilMath_LinearInterpolate_Param1[3].X        = 2
/// \output UtilMath_LinearInterpolate_Param1[0].Y        = 3
/// \output UtilMath_LinearInterpolate_Param1[1].Y        = 2
/// \output UtilMath_LinearInterpolate_Param1[2].Y        = 1
/// \output UtilMath_LinearInterpolate_Param1[3].Y        = 0
/// \output UtilMath_LinearInterpolate_RetVal             = 2
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_5(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_LinearInterpolate_Param1[0].X = 0;
  UtilMath_LinearInterpolate_Param1[1].X = 2;
  UtilMath_LinearInterpolate_Param1[2].X = 2;
  UtilMath_LinearInterpolate_Param1[3].X = 2;
  UtilMath_LinearInterpolate_Param1[0].Y = 3;
  UtilMath_LinearInterpolate_Param1[1].Y = 2;
  UtilMath_LinearInterpolate_Param1[2].Y = 1;
  UtilMath_LinearInterpolate_Param1[3].Y = 0;
  UtilMath_LinearInterpolate_Param2 = 3;
  UtilMath_LinearInterpolate_Param3 = 1;

  //Step 3) Call FUT

  UtilMath_LinearInterpolate_RetVal = UtilMath_LinearInterpolate(&UtilMath_LinearInterpolate_Param1[0], UtilMath_LinearInterpolate_Param2, UtilMath_LinearInterpolate_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].X, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[1].X, 2, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[2].X, 2, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[3].X, 2, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[0].Y, 3, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[1].Y, 2, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[2].Y, 1, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_Param1[3].Y, 0, == );
  AL_UNITTEST_CHECK(UtilMath_LinearInterpolate_RetVal, 2, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_LinearInterpolate
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if the function interpolates a table of points using linear interpolation rule
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_LinearInterpolate(void)
{
  Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_1();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_2();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_3();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_4();
  Mt_ALUtilLibrary_UtilMath_LinearInterpolate_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_ShiftValue
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function shift the value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      ShiftValue_Param1 = 0u
///
/// - Expectations:
///
/// \output ShiftValue_RetVal        = 17
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_ShiftValue(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  ShiftValue_Param1 = 0u;

  //Step 3) Call FUT

  ShiftValue_RetVal = ShiftValue(ShiftValue_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(ShiftValue_RetVal, 17u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_Log2_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function calculates.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_Log2_Param1          = 0u
///
/// - Expectations:
///
/// \output UtilMath_Log2_RetVal         = 2097158u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_Log2_TestCase_1(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_Log2_Param1 = 0u;

  //Step 3) Call FUT

  UtilMath_Log2_RetVal = UtilMath_Log2(UtilMath_Log2_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_Log2_RetVal, 1064250u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_Log2_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function calculates.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_Log2_Param1          = 65536u
///
/// - Expectations:
///
/// \output UtilMath_Log2_RetVal         = 2097158u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_Log2_TestCase_2(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_Log2_Param1 = 65536u;

  //Step 3) Call FUT

  UtilMath_Log2_RetVal = UtilMath_Log2(UtilMath_Log2_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_Log2_RetVal, 1064250u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_Log2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check if the function calculates log2
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_Log2(void)
{
  Mt_ALUtilLibrary_UtilMath_Log2_TestCase_1();
  Mt_ALUtilLibrary_UtilMath_Log2_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1Filter
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function Lowpasses 1st order.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1Filter_Param1           = 0u
/// \input Order1Filter_Param2           = 0u
/// \input Order1Filter_Param3           = 0u
///
/// - Expectations:
///
/// \output Order1Filter_Param1          = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1Filter(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1Filter_Param1 = 0u;
  Order1Filter_Param2 = 0u;
  Order1Filter_Param3 = 0u;

  //Step 3) Call FUT

  Order1Filter(&Order1Filter_Param1, Order1Filter_Param2, Order1Filter_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1Filter_Param1, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1FilterInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function initialises the lowpass 1st order.
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1FilterInit_Param1          = 0u
/// \input Order1FilterInit_Param2          = 0u
///
/// - Expectations:
///
/// \output Order1FilterInit_Param1         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1FilterInit(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1FilterInit_Param1 = 0u;
  Order1FilterInit_Param2 = 0u;

  //Step 3) Call FUT

  Order1FilterInit(&Order1FilterInit_Param1, Order1FilterInit_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1FilterInit_Param1, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1FilterValue
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function gets return value of lowpass 1st order
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1FilterValue_Param1          = 0u
///
/// - Expectations:
///
/// \output Order1FilterValue_Param1         = 0u
/// \output Order1FilterValue_RetVal         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1FilterValue(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1FilterValue_Param1 = 0u;

  //Step 3) Call FUT

  Order1FilterValue_RetVal = Order1FilterValue(&Order1FilterValue_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1FilterValue_Param1, 0u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Order1FilterGetCoef
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function calculates filter coefficient for lowpass 1st order
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Order1FilterGetCoef_Param1          = 1u
/// \input Order1FilterGetCoef_Param2          = 0u
///
/// - Expectations:
///
/// \output Order1FilterGetCoef_RetVal         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Order1FilterGetCoef(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  Order1FilterGetCoef_Param1 = 1u;
  Order1FilterGetCoef_Param2 = 0u;

  //Step 3) Call FUT

  Order1FilterGetCoef_RetVal = Order1FilterGetCoef(Order1FilterGetCoef_Param1, Order1FilterGetCoef_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1FilterGetCoef_RetVal, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_LinEquSolver
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function calculates filter coefficient for lowpass 1st order
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LinEquSolver_Param1.nX          = 1u
/// \input LinEquSolver_Param1.nY          = 0u
/// \input LinEquSolver_Param2.nX          = 0u
/// \input LinEquSolver_Param2.nY          = 0u
/// \input LinEquSolver_Param3.nM          = 0u
/// \input LinEquSolver_Param3.nB          = 0u
///
/// - Expectations:
///
/// \output Order1FilterGetCoef_RetVal       = 0u
/// \output LinEquSolver_Param3.nM           = 0u
/// \output LinEquSolver_Param3.nB           = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_LinEquSolver(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LinEquSolver_Param1.nX = 1u;
  LinEquSolver_Param1.nY = 0u;
  LinEquSolver_Param2.nX = 0u;
  LinEquSolver_Param2.nY = 0u;
  LinEquSolver_Param3.nM = 0u;
  LinEquSolver_Param3.nB = 0u;

  //Step 3) Call FUT

  LinEquSolver(LinEquSolver_Param1, LinEquSolver_Param2, &LinEquSolver_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Order1FilterGetCoef_RetVal, 0u, == );
  AL_UNITTEST_CHECK(LinEquSolver_Param3.nM, 0u, == );
  AL_UNITTEST_CHECK(LinEquSolver_Param3.nB, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_LinEquCalculator
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function does linear equation calculator: f(x) = mx + b
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LinEquCalculator_Param1             = 0u
/// \input LinEquCalculator_Param2.nM          = 0u
/// \input LinEquCalculator_Param2.nB          = 0u
/// - Expectations:
///
/// \output Order1FilterGetCoef_RetVal         = 0u
/// \output LinEquCalculator_Param2.nM         = 0u
/// \output LinEquCalculator_Param2.nB         = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_LinEquCalculator(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LinEquCalculator_Param1    = 0u;
  LinEquCalculator_Param2.nM = 0u;
  LinEquCalculator_Param2.nB = 0u;

  //Step 3) Call FUT

  LinEquCalculator_RetVal = LinEquCalculator(LinEquCalculator_Param1, &LinEquCalculator_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(LinEquCalculator_RetVal, 0u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_Param2.nM, 0u, == );
  AL_UNITTEST_CHECK(LinEquCalculator_Param2.nB, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_FastIir_u
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if function executes Lowpass 1st order, runtime optimized, for unsigned values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMath_FastIir_u_Param1 = 8u
/// \input  UtilMath_FastIir_u_Param2 = 1u
/// \input  UtilMath_FastIir_u_Param3 = 3u
///
/// - Expectations:
///
/// \output UtilMath_FastIir_u_Param1 = 8199u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_FastIir_u(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_FastIir_u_Param1 = 8u;
  UtilMath_FastIir_u_Param2 = 1u;
  UtilMath_FastIir_u_Param3 = 3u;

  //Step 3) Call FUT

  UtilMath_FastIir_u(&UtilMath_FastIir_u_Param1, UtilMath_FastIir_u_Param2, UtilMath_FastIir_u_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_FastIir_u_Param1, 8199u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_FastIir_u_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if function intializes filter value (scale it up to internal scale 2^16)
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  UtilMath_FastIir_u_Init_Param1 = 1u
/// \input  UtilMath_FastIir_u_Init_Param2 = 3u
///
/// - Expectations:
///
/// \output UtilMath_FastIir_u_Init_Param1 = 196608u
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_FastIir_u_Init(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_FastIir_u_Init_Param1 = 1u;
  UtilMath_FastIir_u_Init_Param2 = 3u;

  //Step 3) Call FUT

  UtilMath_FastIir_u_Init(&UtilMath_FastIir_u_Init_Param1, UtilMath_FastIir_u_Init_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_FastIir_u_Init_Param1, 196608u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UtilMath_FastIir_u_GetResult
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function returns result of lowpass 1st order, for unsigned values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UtilMath_FastIir_u_GetResult_Param1 = 1374205u
///
/// - Expectations:
///
/// \output UtilMath_FastIir_u_GetResult_RetVal = 21u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UtilMath_FastIir_u_GetResult(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UtilMath_FastIir_u_GetResult_Param1 = 1374205u;

  //Step 3) Call FUT

  UtilMath_FastIir_u_GetResult_RetVal = UtilMath_FastIir_u_GetResult(&UtilMath_FastIir_u_GetResult_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UtilMath_FastIir_u_GetResult_RetVal, 21u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Crc_CalculateCRC32P4
///
/// \Test Case Description
///        - Test subject: Check if this function calculates CRC32 following E2E Autosar Profile 4 polynomial 0xF4ACFB13
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.232,  LDM.MDRS_ALUTILLIBRARY.233
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Crc_CalculateCRC32P4_Param1[0...8] = [0...8] + 0x31u
/// \input Crc_CalculateCRC32P4_Param2        = 9u
/// \input Crc_CalculateCRC32P4_Param3        = 0xFFFFFFFFu
/// - Expectations:
///
/// \output Crc_CalculateCRC32P4_RetVal = 0x1697D06Au
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Crc_CalculateCRC32P4(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  for (uint8 ucIdx = 0u; ucIdx < 9u; ucIdx++)
  {
    Crc_CalculateCRC32P4_Param1[ucIdx] = ucIdx + 0x31u; // 0x31u = ASCII 1
  }

  Crc_CalculateCRC32P4_Param2 = 9u;
  Crc_CalculateCRC32P4_Param3 = 0xFFFFFFFFu;

  //Step 3) Call FUT

  Crc_CalculateCRC32P4_RetVal = Crc_CalculateCRC32P4(Crc_CalculateCRC32P4_Param1, Crc_CalculateCRC32P4_Param2, Crc_CalculateCRC32P4_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Crc_CalculateCRC32P4_RetVal, 0x1697D06Au, == ); // See AUTOSAR CRC Specification 4.3.1 Chapter 7.2.3.2 Check Value
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Crc_CalculateCRC32
///
/// \Test Case Description
///        - Test subject: Check if this function calculates CRC32
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.229,  LDM.MDRS_ALUTILLIBRARY.230
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Crc_CalculateCRC32_Param1[0...8] = [0...8] + 0x31u
/// \input Crc_CalculateCRC32_Param2        = 9u
/// \input Crc_CalculateCRC32_Param3        = 0xFFFFFFFFu
///
/// - Expectations:
///
/// \output Crc_CalculateCRC32_RetVal = 0xCBF43926u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Crc_CalculateCRC32(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  for (uint8 ucIdx = 0u; ucIdx < 9u; ucIdx++)
  {
    Crc_CalculateCRC32_Param1[ucIdx] = ucIdx + 0x31u; // 0x31u = ASCII 1
  }
  
  Crc_CalculateCRC32_Param2 = 9u;
  Crc_CalculateCRC32_Param3 = 0xFFFFFFFFu;

  //Step 3) Call FUT

  Crc_CalculateCRC32_RetVal = Crc_CalculateCRC32(Crc_CalculateCRC32_Param1, Crc_CalculateCRC32_Param2, Crc_CalculateCRC32_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Crc_CalculateCRC32_RetVal, 0x0376E6E7, == ); // AL CRC-32/MPEG-2 Check Value (crccalc.com)
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Crc_CalculateCRC16
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function calculates CRC16
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Crc_CalculateCRC16_Param1[0...8] = [0...8] + 0x31u
/// \input Crc_CalculateCRC16_Param2        = 9u
/// \input Crc_CalculateCRC16_Param3        = 0xFFFFu
///
/// - Expectations:
///
/// \output Crc_CalculateCRC16_RetVal = 0x29B1u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Crc_CalculateCRC16(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  for (uint8 ucIdx = 0u; ucIdx < 9; ucIdx++)
  {
    Crc_CalculateCRC16_Param1[ucIdx] = ucIdx + 0x31u; // 0x31u = ASCII 1
  }
  
  Crc_CalculateCRC16_Param2 = 9u;
  Crc_CalculateCRC16_Param3 = 0xFFFFu;

  //Step 3) Call FUT

  Crc_CalculateCRC16_RetVal = Crc_CalculateCRC16(Crc_CalculateCRC16_Param1, Crc_CalculateCRC16_Param2, Crc_CalculateCRC16_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Crc_CalculateCRC16_RetVal, 0x29B1u, == ); // See AUTOSAR CRC Specification 4.3.1 Chapter 7.2.2.1 Check Value
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Crc_CalculateCRC8H2F
///
/// \Test Case Description
///        - Test subject: Check if this function calculates CRC8 following Autosar E2E Profile 2 polynomial 0x2F
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.235,  LDM.MDRS_ALUTILLIBRARY.236
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Crc_CalculateCRC8H2F_Param1[0...8] = [0...8] + 0x31u
/// \input Crc_CalculateCRC8H2F_Param2        = 9u
/// \input Crc_CalculateCRC8H2F_Param3        = 0xFFu
///
/// - Expectations:
///
/// \output Crc_CalculateCRC8H2F_RetVal = 0xDFu
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Crc_CalculateCRC8H2F(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  for (uint8 ucIdx = 0u; ucIdx < 9; ucIdx++)
  {
    Crc_CalculateCRC8H2F_Param1[ucIdx] = ucIdx + 0x31u; // 0x31u = ASCII 1
  }
  
  Crc_CalculateCRC8H2F_Param2 = 9u;
  Crc_CalculateCRC8H2F_Param3 = 0xFFu;

  //Step 3) Call FUT

  Crc_CalculateCRC8H2F_RetVal = Crc_CalculateCRC8H2F(Crc_CalculateCRC8H2F_Param1, Crc_CalculateCRC8H2F_Param2, Crc_CalculateCRC8H2F_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Crc_CalculateCRC8H2F_RetVal, 0xDFu, == ); // See AUTOSAR CRC Specification 4.3.1 Chapter 7.2.1.2 Check Value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Crc_CalculateCRC8H1D
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function calculates CRC8 following Autosar E2E Profile 2 polynomial 0x2F
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Crc_CalculateCRC8H1D_Param1[0...8] = [0...8] + 0x31u
/// \input Crc_CalculateCRC8H1D_Param2        = 9u
/// \input Crc_CalculateCRC8H1D_Param3        = 0xFFu
///
/// - Expectations:
///
/// \output Crc_CalculateCRC8H1D_RetVal = 0x4Bu
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Crc_CalculateCRC8H1D(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  for (uint8 ucIdx = 0u; ucIdx < 9; ucIdx++)
  {
    Crc_CalculateCRC8H1D_Param1[ucIdx] = ucIdx + 0x31u; // 0x31u = ASCII 1
  }
  
  Crc_CalculateCRC8H1D_Param2 = 9u;
  Crc_CalculateCRC8H1D_Param3 = 0xFFu;

  //Step 3) Call FUT

  Crc_CalculateCRC8H1D_RetVal = Crc_CalculateCRC8H1D(Crc_CalculateCRC8H1D_Param1, Crc_CalculateCRC8H1D_Param2, Crc_CalculateCRC8H1D_Param3);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Crc_CalculateCRC8H1D_RetVal, 0x4Bu, == ); // Check sunshine2k.de/coding/javascript/crc/crc_js.html CRC8 with polynomial 0x1D
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_Crc_CalculateCRC32_4C11DB7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function calculate CRC with CRC32 (initial value is 0xFFFFFFFF;
///                        polynomial used is 0x04C11DB7; 
///                        input data is 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38)
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     CddEft_Crc32_Vector_AUTOSAR_Param1 = &ucArr[0]
/// \input     CddEft_Crc32_Vector_AUTOSAR_Param2 = 8u
/// \input     CddEft_Crc32_Vector_AUTOSAR_Param3 = EFT_CRC_START
///
/// - Expectations:
///
/// \output    CddEft_Crc32_Vector_AUTOSAR_RetVal = 0x9AE0DAAF
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_Crc_CalculateCRC32_4C11DB7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  uint8 ucArr[8] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };
  Crc_CalculateCRC32_4C11DB7_Param1 = &ucArr[0];
  Crc_CalculateCRC32_4C11DB7_Param2 = 8u;
  Crc_CalculateCRC32_4C11DB7_Param3 = 0xFFFFFFFFuL;

  //Step 3) Call FUT
  Crc_CalculateCRC32_4C11DB7_RetVal = Crc_CalculateCRC32_4C11DB7(Crc_CalculateCRC32_4C11DB7_Param1, Crc_CalculateCRC32_4C11DB7_Param2, Crc_CalculateCRC32_4C11DB7_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Crc_CalculateCRC32_4C11DB7_RetVal, 0x9AE0DAAF, == ); // this value verify with sunshine(http://www.sunshine2k.de/coding/javascript/crc/crc_js.html)
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UTILTIME_USEC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UTILTIME_USEC_Param1 = 100u
///
/// - Expectations:
///
/// \output UTILTIME_USEC_RetVal = 100u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UTILTIME_USEC(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UTILTIME_USEC_Param1 = 100u;

  //Step 3) Call FUT

  UTILTIME_USEC_RetVal = UTILTIME_USEC(UTILTIME_USEC_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UTILTIME_USEC_RetVal, 100u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UTILTIME_MSEC
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.163
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UTILTIME_MSEC_Param1 = 200u
///
/// - Expectations:
///
/// \output UTILTIME_MSEC_RetVal = 200000u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UTILTIME_MSEC(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UTILTIME_MSEC_Param1 = 200u;

  //Step 3) Call FUT

  UTILTIME_MSEC_RetVal = UTILTIME_MSEC(UTILTIME_MSEC_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UTILTIME_MSEC_RetVal, 200000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_UTILTIME_SEC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input UTILTIME_SEC_Param1 = 300u
///
/// - Expectations:
///
/// \output UTILTIME_SEC_RetVal = 300000000u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_UTILTIME_SEC(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  UTILTIME_SEC_Param1 = 300u;

  //Step 3) Call FUT

  UTILTIME_SEC_RetVal = UTILTIME_SEC(UTILTIME_SEC_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(UTILTIME_SEC_RetVal, 300000000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerShortStart
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerShortStart_Param1         = 5u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 2000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerShortStart_RetVal         = 0u
///
/// - Expectations:
///
/// \output TimerShortStart_RetVal         = 7u
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerShortStart(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerShortStart_Param1         = 5u;
  LPTMR0_GetTimeElapsed_RetVal   = 2000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerShortStart_RetVal         = 0u;

  //Step 3) Call FUT

  TimerShortStart_RetVal = TimerShortStart(TimerShortStart_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerShortStart_RetVal        , 7u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  , 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerShortTimeout
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerShortTimeout_Param1       = 2u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 3000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerShortTimeout_RetVal       = FALSE
///
/// - Expectations:
///
/// \output TimerShortTimeout_RetVal       = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerShortTimeout(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerShortTimeout_Param1       = 2u;
  LPTMR0_GetTimeElapsed_RetVal   = 3000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerShortTimeout_RetVal       = FALSE;

  //Step 3) Call FUT

  TimerShortTimeout_RetVal = TimerShortTimeout(TimerShortTimeout_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerShortTimeout_RetVal      , TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,   1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  ,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerShortTimeoutOfCustomTick
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerShortTimeoutOfCustomTick_Param1 = 2u
/// \input TimerShortTimeoutOfCustomTick_Param2 = 3u
/// \input TimerShortTimeoutOfCustomTick_RetVal = FALSE
///
/// - Expectations:
///
/// \output TimerShortTimeoutOfCustomTick_RetVal = TRUE
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerShortTimeoutOfCustomTick(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerShortTimeoutOfCustomTick_Param1 = 2u;
  TimerShortTimeoutOfCustomTick_Param2 = 3u;
  TimerShortTimeoutOfCustomTick_RetVal = FALSE;

  //Step 3) Call FUT

  TimerShortTimeoutOfCustomTick_RetVal = TimerShortTimeoutOfCustomTick(TimerShortTimeoutOfCustomTick_Param1, TimerShortTimeoutOfCustomTick_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerShortTimeoutOfCustomTick_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerShortGetTimeSince
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerShortGetTimeSince_Param1  = 5u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 8000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerShortGetTimeSince_RetVal  = 0u
///
/// - Expectations:
///
/// \output TimerShortGetTimeSince_RetVal  = 3u
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerShortGetTimeSince(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerShortGetTimeSince_Param1  = 5u;
  LPTMR0_GetTimeElapsed_RetVal   = 8000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerShortGetTimeSince_RetVal  = 0u;

  //Step 3) Call FUT

  TimerShortGetTimeSince_RetVal = TimerShortGetTimeSince(TimerShortGetTimeSince_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerShortGetTimeSince_RetVal , 3u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  , 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerShortGetTick
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LPTMR0_GetTimeElapsed_RetVal   = 4000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u;
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u;
/// \input TimerShortGetTick_RetVal       = 0u;
///
/// - Expectations:
///
/// \output TimerShortGetTick_RetVal       = 4u
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerShortGetTick(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LPTMR0_GetTimeElapsed_RetVal   = 4000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerShortGetTick_RetVal       = 0u;

  //Step 3) Call FUT

  TimerShortGetTick_RetVal = TimerShortGetTick();

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerShortGetTick_RetVal      , 4u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  , 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerStart
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.167
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerStart_Param1              = 10u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 2000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerStart_RetVal              = 0u
///
/// - Expectations:
///
/// \output TimerStart_RetVal              = 2010u
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerStart(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerStart_Param1              = 10u;
  LPTMR0_GetTimeElapsed_RetVal   = 2000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerStart_RetVal              = 0u;

  //Step 3) Call FUT

  TimerStart_RetVal = TimerStart(TimerStart_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerStart_RetVal             , 2010u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,    1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  ,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerTimeout
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.169
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerTimeout_Param1            = 10u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 10000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerTimeout_RetVal            = FALSE
///
/// - Expectations:
///
/// \output TimerTimeout_RetVal            = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerTimeout(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerTimeout_Param1            = 10u;
  LPTMR0_GetTimeElapsed_RetVal   = 10000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerTimeout_RetVal            = FALSE;

  //Step 3) Call FUT

  TimerTimeout_RetVal = TimerTimeout(TimerTimeout_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerTimeout_RetVal           , TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,   1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  ,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerTimeoutOfCustomTick
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerTimeoutOfCustomTick_Param1 = 2u
/// \input TimerTimeoutOfCustomTick_Param2 = 3u
/// \input TimerTimeoutOfCustomTick_RetVal = FALSE
///
/// - Expectations:
///
/// \output TimerTimeoutOfCustomTick_RetVal = TRUE
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerTimeoutOfCustomTick(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerTimeoutOfCustomTick_Param1 = 2u;
  TimerTimeoutOfCustomTick_Param2 = 3u;
  TimerTimeoutOfCustomTick_RetVal = FALSE;

  //Step 3) Call FUT

  TimerTimeoutOfCustomTick_RetVal = TimerTimeoutOfCustomTick(TimerTimeoutOfCustomTick_Param1, TimerTimeoutOfCustomTick_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerTimeoutOfCustomTick_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerGetTimeSince
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.171
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerGetTimeSince_Param1       = 5000u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 20000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerGetTimeSince_RetVal       = 0u
///
/// - Expectations:
///
/// \output TimerGetTimeSince_RetVal       = 15000u
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerGetTimeSince(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerGetTimeSince_Param1       = 5000u;
  LPTMR0_GetTimeElapsed_RetVal   = 20000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerGetTimeSince_RetVal       = 0u;

  //Step 3) Call FUT

  TimerGetTimeSince_RetVal = TimerGetTimeSince(TimerGetTimeSince_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerGetTimeSince_RetVal      , 15000u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,     1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  ,     0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerGetTick
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ALUTILLIBRARY Id Requirement(s) covered: 
///
/// LDM.MDRS_ALUTILLIBRARY.173
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LPTMR0_GetTimeElapsed_RetVal   = 0xABCDEFu
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerGetTick_RetVal            = 0u
///
/// - Expectations:
///
/// \output TimerGetTick_RetVal            = 0xABCDEFu
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerGetTick(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  LPTMR0_GetTimeElapsed_RetVal   = 0xABCDEFu;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerGetTick_RetVal            = 0u;

  //Step 3) Call FUT

  TimerGetTick_RetVal = TimerGetTick();

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerGetTick_RetVal           , 0xABCDEFu, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  ,        0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_TimerGetTimeSinceMs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this macro returns the correct TIMER value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input TimerGetTimeSinceMs_Param1     = 5000u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 20000u
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_Param1   = 1u
/// \input TimerGetTimeSinceMs_RetVal     = 0u
///
/// - Expectations:
///
/// \output TimerGetTimeSinceMs_RetVal     = 15u
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
/// \output LPTMR0_GetTimeElapsed_Param1   = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_TimerGetTimeSinceMs(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  TimerGetTimeSinceMs_Param1     = 5000u;
  LPTMR0_GetTimeElapsed_RetVal   = 20000u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_Param1   = 1u;
  TimerGetTimeSinceMs_RetVal     = 0u;

  //Step 3) Call FUT

  TimerGetTimeSinceMs_RetVal = TimerGetTimeSinceMs(TimerGetTimeSinceMs_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(TimerGetTimeSinceMs_RetVal    , 15u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_Param1  ,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ALUtilLibrary_ASHRI32
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if this function executes arithmetic right shift operation for signed values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ASHRI32_Param1 = 128
/// \input ASHRI32_Param2 = 2u
///
/// - Expectations:
///
/// \output ASHRI32_RetVal = 32
///
///
//-----------------------------------------------------------------------------
void Mt_ALUtilLibrary_ASHRI32(void)
{
  //Step 1: Set pre-conditions 
  //Step 2) Assign Input values

  ASHRI32_Param1 = 128;
  ASHRI32_Param2 = 2u;

  //Step 3) Call FUT

  ASHRI32_RetVal = ASHRI32(ASHRI32_Param1, ASHRI32_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(ASHRI32_RetVal, 32, == );
}

//-----------------------------------------------------------------------------
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMemClr", Mt_ALUtilLibrary_UtilMemClr);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMemSet", Mt_ALUtilLibrary_UtilMemSet);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMemCopy", Mt_ALUtilLibrary_UtilMemCopy);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMemCmp", Mt_ALUtilLibrary_UtilMemCmp);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilDebounce", Mt_ALUtilLibrary_UtilDebounce);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilDebounceReset", Mt_ALUtilLibrary_UtilDebounceReset);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilDebounceInit", Mt_ALUtilLibrary_UtilDebounceInit);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Order1Filter32", Mt_ALUtilLibrary_Order1Filter32);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_LowPass1Filter32", Mt_ALUtilLibrary_LowPass1Filter32);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_LowPass1FilterInit32", Mt_ALUtilLibrary_LowPass1FilterInit32);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Order1TrackingFilter32", Mt_ALUtilLibrary_Order1TrackingFilter32);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_FirFilter32", Mt_ALUtilLibrary_FirFilter32);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16", Mt_ALUtilLibrary_UtilMath_LinearInterpolateU16);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMath_LinearInterpolate", Mt_ALUtilLibrary_UtilMath_LinearInterpolate);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_ShiftValue", Mt_ALUtilLibrary_ShiftValue);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMath_Log2", Mt_ALUtilLibrary_UtilMath_Log2);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Order1Filter", Mt_ALUtilLibrary_Order1Filter);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Order1FilterInit", Mt_ALUtilLibrary_Order1FilterInit);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Order1FilterValue", Mt_ALUtilLibrary_Order1FilterValue);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Order1FilterGetCoef", Mt_ALUtilLibrary_Order1FilterGetCoef);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_LinEquSolver", Mt_ALUtilLibrary_LinEquSolver);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_LinEquCalculator", Mt_ALUtilLibrary_LinEquCalculator);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMath_FastIir_u", Mt_ALUtilLibrary_UtilMath_FastIir_u);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMath_FastIir_u_Init", Mt_ALUtilLibrary_UtilMath_FastIir_u_Init);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UtilMath_FastIir_u_GetResult", Mt_ALUtilLibrary_UtilMath_FastIir_u_GetResult);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Crc_CalculateCRC32P4", Mt_ALUtilLibrary_Crc_CalculateCRC32P4);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Crc_CalculateCRC32", Mt_ALUtilLibrary_Crc_CalculateCRC32);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Crc_CalculateCRC16", Mt_ALUtilLibrary_Crc_CalculateCRC16);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Crc_CalculateCRC8H2F", Mt_ALUtilLibrary_Crc_CalculateCRC8H2F);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Crc_CalculateCRC8H1D", Mt_ALUtilLibrary_Crc_CalculateCRC8H1D);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_Crc_CalculateCRC32_4C11DB7", Mt_ALUtilLibrary_Crc_CalculateCRC32_4C11DB7);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UTILTIME_USEC", Mt_ALUtilLibrary_UTILTIME_USEC);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UTILTIME_MSEC", Mt_ALUtilLibrary_UTILTIME_MSEC);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_UTILTIME_SEC", Mt_ALUtilLibrary_UTILTIME_SEC);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerShortStart", Mt_ALUtilLibrary_TimerShortStart);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerShortTimeout", Mt_ALUtilLibrary_TimerShortTimeout);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerShortTimeoutOfCustomTick", Mt_ALUtilLibrary_TimerShortTimeoutOfCustomTick);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerShortGetTimeSince", Mt_ALUtilLibrary_TimerShortGetTimeSince);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerShortGetTick", Mt_ALUtilLibrary_TimerShortGetTick);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerStart", Mt_ALUtilLibrary_TimerStart);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerTimeout", Mt_ALUtilLibrary_TimerTimeout);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerTimeoutOfCustomTick", Mt_ALUtilLibrary_TimerTimeoutOfCustomTick);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerGetTimeSince", Mt_ALUtilLibrary_TimerGetTimeSince);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerGetTick", Mt_ALUtilLibrary_TimerGetTick);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_TimerGetTimeSinceMs", Mt_ALUtilLibrary_TimerGetTimeSinceMs);
  ALUnitTest_AddFunction("Mt_ALUtilLibrary_ASHRI32", Mt_ALUtilLibrary_ASHRI32);
}

// EOF

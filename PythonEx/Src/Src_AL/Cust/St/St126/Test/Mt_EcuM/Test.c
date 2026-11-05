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
/// \brief Module test for EcuM
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_HandleNvmWrite_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the function handles NvM write
///                        and returns the status of write operation 
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  NvM_GetErrorStatus_Param1   = 1u
/// \input  NvM_GetErrorStatus_Param2   = 1u
/// \input  NvM_GetErrorStatus_HitCount = 0u
/// \input  EcuM_HandleNvmWrite_RetVal  = 0u
///
/// - Expectations:
///
/// \output NvM_GetErrorStatus_Param1                 = 0u
/// \output NvM_GetErrorStatus_HitCount               = 1u
/// \output EcuM_HandleNvmWrite_RetVal                = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_HandleNvmWrite_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  NvM_GetErrorStatus_Param1   = 1u;
  NvM_GetErrorStatus_Param2   = 1u;
  NvM_GetErrorStatus_HitCount = 0u;
  EcuM_HandleNvmWrite_RetVal  = 0u;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_HandleNvmWrite_RetVal = EcuM_HandleNvmWrite();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1,                 0u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount,               1u, == );
  AL_UNITTEST_CHECK(EcuM_HandleNvmWrite_RetVal,                1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_EnterPrep_Shutdown_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function transitions the EcuM into Prep_Shutdown state
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState            = eEcuM_Undefined
/// \input  EcuM_boTriggerNvmWrite = FALSE
/// \input  Nvm_WriteAll_HitCount  = 0u;
///
/// - Expectations:
///
/// \output EcuM_eState             = eEcuM_ShutDownPrep
/// \output EcuM_boTriggerNvmWrite  = FALSE
/// \output Nvm_WriteAll_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_EnterPrep_Shutdown_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eState            = eEcuM_Undefined;
  EcuM_boTriggerNvmWrite = FALSE;
  Nvm_WriteAll_HitCount = 0u;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_EnterPrep_Shutdown();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState,            eEcuM_ShutDownPrep, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite, FALSE, == );
  AL_UNITTEST_CHECK(Nvm_WriteAll_HitCount, 1u, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function prepares for Ecu Run mode
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulRunRequestCnt   = 0u
/// \input  EcuM_eState            = eEcuM_Undefined
/// \input  EcuM_boTriggerNvmWrite = FALSE
/// \input  Nvm_WriteAll_HitCount  = 0u;
///
/// - Expectations:
///
/// \output EcuM_eState             = eEcuM_ShutDownPrep
/// \output EcuM_boTriggerNvmWrite  = FALSE
/// \output Nvm_WriteAll_HitCount   = 1
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulRunRequestCnt   = 0u;
  EcuM_eState            = eEcuM_Undefined;
  EcuM_boTriggerNvmWrite = FALSE;
  Nvm_WriteAll_HitCount = 0u;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Up_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState,            eEcuM_ShutDownPrep, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite, FALSE, == );
  AL_UNITTEST_CHECK(Nvm_WriteAll_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function keeps Ecu Run mode
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulRunRequestCnt   = 0u
/// \input  EcuM_eState            = eEcuM_App_Run
/// \input  EcuM_boTriggerNvmWrite = FALSE
///
/// - Expectations:
///
/// \output EcuM_eState             = eEcuM_App_Run
/// \output EcuM_boTriggerNvmWrite  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulRunRequestCnt   = 1u;
  EcuM_eState            = eEcuM_App_Run;
  EcuM_boTriggerNvmWrite = FALSE;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Up_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState,            eEcuM_App_Run, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Enter_Shutdown_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Updates the EcuM Shut-Down state
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState = eEcuM_Undefined
///
/// - Expectations:
///
/// \output EcuM_eState  = eEcuM_ShutDown
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Enter_Shutdown_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eState = eEcuM_Undefined;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Enter_Shutdown();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState, eEcuM_ShutDown, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ExitPrep_Shutdown_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Updates the EcuM state
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState = eEcuM_ShutDown
///
/// - Expectations:
///
/// \output EcuM_eState  = eEcuM_Up
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ExitPrep_Shutdown_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eState = eEcuM_ShutDown;

  //Step 2) Assign Input values
  //-----

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ExitPrep_Shutdown();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState, eEcuM_Up, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_WaitNvMReady_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Waits for Nvm ready function
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_WaitNvMReady_WhileTestMode = 0u
/// \input  EcuM_WaitNvMReady_Param1        = 10u
/// \input  NvM_MainFunction_HitCount       = 0u
/// \input  NvM_GetErrorStatus_HitCount     = 0u
/// \input  NvM_GetErrorStatus_Param1       = 0u
/// \input  NvM_GetErrorStatus_Param2       = 1u
/// \input  NvM_GetErrorStatus_Param1       = TRUE
///
/// - Expectations:
///
/// \output NvM_MainFunction_HitCount       = 1u;
/// \output NvM_GetErrorStatus_HitCount     = 1u;
/// \output NvM_GetErrorStatus_Param1       = 10u;
/// \output EcuM_WaitNvMReady_RetVal        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_WaitNvMReady_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_WaitNvMReady_WhileTestMode = 0u;
  EcuM_WaitNvMReady_Param1        = 10u;
  NvM_MainFunction_HitCount       = 0u;
  NvM_GetErrorStatus_HitCount     = 0u;

  //Step 2) Assign Input values
  NvM_GetErrorStatus_Param1 = 0u;
  NvM_GetErrorStatus_Param2 = 1u;
  NvM_GetErrorStatus_Param1 = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_WaitNvMReady_RetVal = EcuM_WaitNvMReady(EcuM_WaitNvMReady_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_MainFunction_HitCount,         1u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount,       1u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1,        10u, == );
  AL_UNITTEST_CHECK(EcuM_WaitNvMReady_RetVal,       FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_WaitNvMReady_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Waits for Nvm ready function
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_WaitNvMReady_WhileTestMode = 0x55u
/// \input  EcuM_WaitNvMReady_Param1        = 10u
/// \input  NvM_MainFunction_HitCount       = 0u
/// \input  NvM_GetErrorStatus_HitCount     = 0u
///
/// - Expectations:
///
/// \output NvM_MainFunction_HitCount       = 1u;
/// \output NvM_GetErrorStatus_HitCount     = 1u;
/// \output NvM_GetErrorStatus_Param1       = 10u;
/// \output EcuM_WaitNvMReady_RetVal        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_WaitNvMReady_TestCase_2(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------
	
  //Step 1) Set pre-conditions
  EcuM_WaitNvMReady_WhileTestMode = 0x55;
	EcuM_WaitNvMReady_Param1 = 10u;
	NvM_MainFunction_HitCount = 0u;
	NvM_GetErrorStatus_HitCount = 0u;

  //Step 2) Assign Input values
  NvM_GetErrorStatus_Param1 = 0u;
  NvM_GetErrorStatus_Param2 = 1u;
  NvM_GetErrorStatus_Param1 = TRUE;

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_WaitNvMReady_RetVal = EcuM_WaitNvMReady(EcuM_WaitNvMReady_Param1);

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(NvM_MainFunction_HitCount, 1u, == );
	AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount, 1u, == );
	AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1, 10u, == );
	AL_UNITTEST_CHECK(EcuM_WaitNvMReady_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_WaitNvMReady_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Waits for Nvm ready function
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_WaitNvMReady_WhileTestMode = 0xAAu
/// \input  EcuM_WaitNvMReady_Param1        = 10u
/// \input  NvM_MainFunction_HitCount       = 0u
/// \input  NvM_GetErrorStatus_HitCount     = 0u
/// \input  NvM_GetErrorStatus_Param1       = 0u
/// \input  NvM_GetErrorStatus_Param2       = 1u
/// \input  NvM_GetErrorStatus_Param1       = TRUE
///
/// - Expectations:
///
/// \output NvM_MainFunction_HitCount       = 6u;
/// \output NvM_GetErrorStatus_HitCount     = 6u;
/// \output NvM_GetErrorStatus_Param1       = 10u;
/// \output EcuM_WaitNvMReady_RetVal        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_WaitNvMReady_TestCase_3(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------
	
  //Step 1) Set pre-conditions
  EcuM_WaitNvMReady_WhileTestMode = 0xAA;
	EcuM_WaitNvMReady_Param1 = 10u;
	NvM_MainFunction_HitCount = 0u;
	NvM_GetErrorStatus_HitCount = 0u;

  //Step 2) Assign Input values
  NvM_GetErrorStatus_Param1 = 0u;
  NvM_GetErrorStatus_Param2 = 1u;
  NvM_GetErrorStatus_Param1 = TRUE;

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_WaitNvMReady_RetVal = EcuM_WaitNvMReady(EcuM_WaitNvMReady_Param1);

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(NvM_MainFunction_HitCount, 6u, == );
	AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount, 6u, == );
	AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1, 10u, == );
	AL_UNITTEST_CHECK(EcuM_WaitNvMReady_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_WaitForNvMReadAllReady_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Waits for Nvm ready function
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_WaitNvMReady_WhileTestMode = 0u
/// \input  NvM_MainFunction_HitCount       = 0u
/// \input  NvM_GetErrorStatus_HitCount     = 0u
/// \input  NvM_GetErrorStatus_Param1       = 0u
/// \input  NvM_GetErrorStatus_Param2       = 10u
/// \input  NvM_GetErrorStatus_Param1       = FALSE
///
/// - Expectations:
///
/// \output NvM_MainFunction_HitCount       = 1u;
/// \output NvM_GetErrorStatus_HitCount     = 1u;
/// \output NvM_GetErrorStatus_Param1       = 0u;
/// \output EcuM_WaitNvMReady_RetVal        = TRUE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_WaitForNvMReadAllReady_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  EcuM_WaitNvMReady_WhileTestMode = 0;
  NvM_MainFunction_HitCount       = 0u;
  NvM_GetErrorStatus_HitCount     = 0u;

  //Step 2) Assign Input values
  NvM_GetErrorStatus_Param1 = 10u;
  NvM_GetErrorStatus_Param2 = 0u;
  NvM_GetErrorStatus_Param1 = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_WaitForNvMReadAllReady();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_MainFunction_HitCount,         1u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount,       1u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1,         0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Finishes the startup
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)

///
/// - Preconditions:
///
/// \input  EcuM_ulRunRequestCnt   = 1u
/// \input  EcuM_eState            = eEcuM_Undefined
///
/// - Expectations:
///
/// \output EcuM_eState             = eEcuM_Up
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulRunRequestCnt   = 1u;
  EcuM_eState            = eEcuM_Undefined;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_StartUp_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState,            eEcuM_Up, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Finishes the startup
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulRunRequestCnt   = 0u
/// \input  EcuM_eState            = eEcuM_App_Run
///
/// - Expectations:
///
/// \output EcuM_eState             = eEcuM_App_Run
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulRunRequestCnt   = 0u;
  EcuM_eState            = eEcuM_App_Run;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_StartUp_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState,            eEcuM_App_Run, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateStartup_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Finishes the startup
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulRunRequestCnt   = 1u
/// \input  EcuM_eState            = eEcuM_Undefined
///
/// - Expectations:
///
/// \output EcuM_eState             = eEcuM_Up
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateStartup_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulRunRequestCnt   = 1u;
  EcuM_eState            = eEcuM_Undefined;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_OnStateStartup();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState,            eEcuM_Up, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReportWgdReset_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reports watchdog defect error
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                  = 0u
/// \input  Dem_SetEventStatus_Param1                    = 0u
/// \input  Dem_SetEventStatus_Param2                    = 0u
/// \input  EcuM_sEcuInternalResetReason.eMcuResetReason = 1u
/// \input  Dem_Set_Init_Window_HitCount                 = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                  = 1u
/// \output Dem_SetEventStatus_Param1                    = WATCHDOG_DEFECT
/// \output Dem_SetEventStatus_Param2                    = 3u
/// \output Dem_Set_Init_Window_HitCount                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReportWgdReset_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Dem_SetEventStatus_HitCount   = 0u;
  Dem_SetEventStatus_Param1     = 0u;
  Dem_SetEventStatus_Param2     = 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason = 1u;
  Dem_Set_Init_Window_HitCount  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReportWgdReset();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             WATCHDOG_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,                          3u, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount,                       2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReportWgdReset_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function reports watchdog defect error
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                    = 0u
/// \input  Dem_SetEventStatus_Param1                     = 0u
/// \input  Dem_SetEventStatus_Param2                     = 0u
/// \input  EcuM_sEcuInternalResetReason.eMcuResetReason  = 1u
/// \input  Dem_Set_Init_Window_HitCount                  = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                  = 1u
/// \output Dem_SetEventStatus_Param1                    = WATCHDOG_DEFECT
/// \output Dem_SetEventStatus_Param2                    = 2u
/// \output Dem_Set_Init_Window_HitCount                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReportWgdReset_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Dem_SetEventStatus_HitCount   = 0u;
  Dem_SetEventStatus_Param1     = 0u;
  Dem_SetEventStatus_Param2     = 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason = 0u;
  Dem_Set_Init_Window_HitCount  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReportWgdReset();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------.
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             WATCHDOG_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,                          2u, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount,                       2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function reports APP CRC defect error
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                  = 0u
/// \input  Dem_SetEventStatus_Param1                    = 0u
/// \input  Dem_SetEventStatus_Param2                    = 0u
/// \input  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason = 1u
/// \input  Dem_Set_Init_Window_HitCount                 = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                  = 1u
/// \output Dem_SetEventStatus_Param1                    = CRC_APP_DEFECT
/// \output Dem_SetEventStatus_Param2                    = 3u
/// \output Dem_Set_Init_Window_HitCount                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Dem_SetEventStatus_HitCount   = 0u;
  Dem_SetEventStatus_Param1     = 0u;
  Dem_SetEventStatus_Param2     = 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason = 1u;
  Dem_Set_Init_Window_HitCount  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReportAppCrcReset();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              CRC_APP_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,                          3u, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount,                       2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function clears App CRC defect error
///
/// \FuSa Relevant: - 
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                   = 0u
/// \input  Dem_SetEventStatus_Param1                     = 0u
/// \input  Dem_SetEventStatus_Param2                     = 0u
/// \input  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason = 0u
/// \input  Dem_Set_Init_Window_HitCount                  = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                  = 1u
/// \output Dem_SetEventStatus_Param1                    = CRC_APP_DEFECT
/// \output Dem_SetEventStatus_Param2                    = 2u
/// \output Dem_Set_Init_Window_HitCount                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Dem_SetEventStatus_HitCount   = 0u;
  Dem_SetEventStatus_Param1     = 0u;
  Dem_SetEventStatus_Param2     = 0u;
  EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason = 0u;
  Dem_Set_Init_Window_HitCount  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReportAppCrcReset();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------.
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              CRC_APP_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,                          2u, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount,                       2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_AL_InterruptCfg_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function executes the initialization sequence for interrupt list 
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.487,  LDM.MDRS_ECUM.489, LDM.MDRS_ECUM.945
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  INT_SYS_SetPriority_HitCount           = 0u
/// \input  INT_SYS_SetPriority_Param1             = 0u
/// \input  INT_SYS_SetPriority_Param2             = 0u
/// \input  EcuM_InterruptCfg_List[6u].ucInterrupt = 23u
/// \input  EcuM_InterruptCfg_List[6u].ucPriority  = 13u
///
/// - Expectations:
///
/// \output INT_SYS_SetPriority_HitCount           = 10u
/// \output INT_SYS_SetPriority_Param1             = 21u
/// \output INT_SYS_SetPriority_Param2             = 4u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_AL_InterruptCfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  INT_SYS_SetPriority_HitCount           = 0u;
  INT_SYS_SetPriority_Param1             = 0u;
  INT_SYS_SetPriority_Param2             = 0u;
  EcuM_InterruptCfg_List[6u].ucInterrupt = 23u;
  EcuM_InterruptCfg_List[6u].ucPriority  = 13u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_AL_InterruptCfg();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(INT_SYS_SetPriority_HitCount,   11u, == );
  AL_UNITTEST_CHECK(INT_SYS_SetPriority_Param1,     58u, == );
  AL_UNITTEST_CHECK(INT_SYS_SetPriority_Param2,      4u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_AL_InterruptEnable_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function executes the enable sequence for interrupt
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.490, LDM.MDRS_ECUM.492, LDM.MDRS_ECUM.974, LDM.MDRS_ECUM.1015
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  INT_SYS_EnableIRQ_HitCount  = 0u
/// \input  INT_SYS_EnableIRQ_Param1    = 0u
/// \input  EcuM_InterruptEnbl_List[6u] = 23u
///
/// - Expectations:
///
/// \output INT_SYS_EnableIRQ_HitCount           = 10u
/// \output INT_SYS_EnableIRQ_Param1             = 21u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_AL_InterruptEnable_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  INT_SYS_EnableIRQ_HitCount  = 0u;
  INT_SYS_EnableIRQ_Param1    = 0u;
  EcuM_InterruptEnbl_List[6u] = 23u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_AL_InterruptEnable();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(INT_SYS_EnableIRQ_HitCount,   11u, == );
  AL_UNITTEST_CHECK(INT_SYS_EnableIRQ_Param1,     58u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_RequestRUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Gets Run Request status and
///                        Sets Run Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_RequestRUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]       = 0xF0u
/// \input  EcuM_ulRunRequestCnt   = 1u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 2u
/// \output EcuM_aucUser[1u]     = 0xFFu
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_RequestRUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]       = 0xF0u;
  EcuM_ulRunRequestCnt   = 1u;

  //Step 2) Assign Input values
  EcuM_RequestRUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_RequestRUN(EcuM_RequestRUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,     2u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],      0xFFu, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_RequestRUN_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Gets Run Request status and
///                        Sets Run Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_RequestRUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]       = 0xF0u
/// \input  EcuM_ulRunRequestCnt   = 0xFFFFFFFFu
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 0xFFFFFFFFu
/// \output EcuM_aucUser[1u]     = 0xFFu
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_RequestRUN_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]       = 0xF0u;
  EcuM_ulRunRequestCnt   = 0xFFFFFFFFu;

  //Step 2) Assign Input values
  EcuM_RequestRUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_RequestRUN(EcuM_RequestRUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt, 0xFFFFFFFFu, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],           0xFFu, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_RequestRUN_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Gets Run Request status and
///                        Sets Run Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_RequestRUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]       = 0x0Fu
/// \input  EcuM_ulRunRequestCnt   = 1u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 1u
/// \output EcuM_aucUser[1u]     = 0x0Fu
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_RequestRUN_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]       = 0x0Fu;
  EcuM_ulRunRequestCnt   = 1u;

  //Step 2) Assign Input values
  EcuM_RequestRUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_RequestRUN(EcuM_RequestRUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,     1u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],      0x0Fu, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Gets PostRun Request status and
///                        Sets PostRun Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_RequestPOST_RUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]            = 0x0Fu
/// \input  EcuM_ulPostRunRequestCnt    = 1u
///
/// - Expectations:
///
/// \output EcuM_ulPostRunRequestCnt = 2u
/// \output EcuM_aucUser[1u]         = 0xFFu
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]            = 0x0Fu;
  EcuM_ulPostRunRequestCnt    = 1u;

  //Step 2) Assign Input values
  EcuM_RequestPOST_RUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_RequestPOST_RUN(EcuM_RequestPOST_RUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulPostRunRequestCnt,     2u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],          0xFFu, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Gets PostRun Request status and
///                        Sets PostRun Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_RequestPOST_RUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]            = 0x0Fu
/// \input  EcuM_ulPostRunRequestCnt    = 0xFFFFFFFFu
///
/// - Expectations:
///
/// \output EcuM_ulPostRunRequestCnt = 0xFFFFFFFFu
/// \output EcuM_aucUser[1u]         = 0xFFu
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]            = 0x0Fu;
  EcuM_ulPostRunRequestCnt    = 0xFFFFFFFFu;

  //Step 2) Assign Input values
  EcuM_RequestPOST_RUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_RequestPOST_RUN(EcuM_RequestPOST_RUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulPostRunRequestCnt, 0xFFFFFFFFu, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],               0xFFu, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Gets PostRun Request status and
///                        Sets PostRun Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_RequestPOST_RUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]            = 0xF0u
/// \input  EcuM_ulPostRunRequestCnt    = 1u
///
/// - Expectations:
///
/// \output EcuM_ulPostRunRequestCnt = 1u
/// \output EcuM_aucUser[1u]         = 0xF0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]            = 0xF0u;
  EcuM_ulPostRunRequestCnt    = 1u;

  //Step 2) Assign Input values
  EcuM_RequestPOST_RUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_RequestPOST_RUN(EcuM_RequestPOST_RUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulPostRunRequestCnt,     1u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],          0xF0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReleaseRUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Gets Run Release status and
///                        Clears Run Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ReleaseRUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]       = 0x0Fu
/// \input  EcuM_ulRunRequestCnt   = 3u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 2u
/// \output EcuM_aucUser[1u]     = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReleaseRUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]       = 0x0Fu;
  EcuM_ulRunRequestCnt   = 3u;

  //Step 2) Assign Input values
  EcuM_ReleaseRUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  
  //Step 3) Call FUT
  EcuM_ReleaseRUN(EcuM_ReleaseRUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,     2u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],         0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReleaseRUN_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Gets Run Release status and
///                        Clears Run Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ReleaseRUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]       = 0x0Fu
/// \input  EcuM_ulRunRequestCnt   = 0u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 0u
/// \output EcuM_aucUser[1u]     = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReleaseRUN_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]       = 0x0Fu;
  EcuM_ulRunRequestCnt   = 0u;

  //Step 2) Assign Input values
  EcuM_ReleaseRUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReleaseRUN(EcuM_ReleaseRUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,          0u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],              0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReleaseRUN_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Gets Run Release status and
///                        Clears Run Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ReleaseRUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]       = 0x0Fu
/// \input  EcuM_ulRunRequestCnt   = 1u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 1u
/// \output EcuM_aucUser[1u]     = 0xF0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReleaseRUN_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]       = 0xF0u;
  EcuM_ulRunRequestCnt   = 1u;

  //Step 2) Assign Input values
  EcuM_ReleaseRUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReleaseRUN(EcuM_ReleaseRUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,     1u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],      0xF0u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Gets PostRun Release status and
///                        Clears PostRun Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ReleasePOST_RUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]            = 0xF0u
/// \input  EcuM_ulRunRequestCnt        = 3u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 2u
/// \output EcuM_aucUser[1u]     = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]            = 0xF0u;
  EcuM_ulPostRunRequestCnt    = 3u;

  //Step 2) Assign Input values
  EcuM_ReleasePOST_RUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReleasePOST_RUN(EcuM_ReleasePOST_RUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulPostRunRequestCnt,     2u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],             0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Gets PostRun Release status and
///                        Clears PostRun Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ReleasePOST_RUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]            = 0xF0u
/// \input  EcuM_ulRunRequestCnt        = 0u
///
/// - Expectations:
///
/// \output EcuM_ulRunRequestCnt = 0u
/// \output EcuM_aucUser[1u]     = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]            = 0xF0u;
  EcuM_ulPostRunRequestCnt    = 0u;

  //Step 2) Assign Input values
  EcuM_ReleasePOST_RUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReleasePOST_RUN(EcuM_ReleasePOST_RUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulPostRunRequestCnt,      0u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],              0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Gets PostRun Release status and
///                        Clears PostRun Request flag
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ReleasePOST_RUN_Param1 = 1u
/// \input  EcuM_aucUser[1u]            = 0x0Fu
/// \input  EcuM_ulRunRequestCnt        = 1u
///
/// - Expectations:
///
/// \output EcuM_ReleasePOST_RUN_Param1 = 1u
/// \output EcuM_aucUser[1u]            = 0x0Fu
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[1u]            = 0x0Fu;
  EcuM_ulRunRequestCnt        = 1u;

  //Step 2) Assign Input values
  EcuM_ReleasePOST_RUN_Param1 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ReleasePOST_RUN(EcuM_ReleasePOST_RUN_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ReleasePOST_RUN_Param1,     1u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[1u],             0x0Fu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_FlashCrcFailure_Indication_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Sets Flash CRC failure indication flag
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.460,  LDM.MDRS_ECUM.462, LDM.MDRS_ECUM.836
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_boFlashCrcFailure                   = FALSE
///
/// - Expectations:
///
/// \output EcuM_boFlashCrcFailure                   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_FlashCrcFailure_Indication_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boFlashCrcFailure = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_FlashCrcFailure_Indication();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_boFlashCrcFailure, TRUE, == );
}

#if 0
//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_Sleep_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Runs release by NM user and
///                        Disables SysMon and SigPrep Rx/Tx
///
/// - Preconditions:
///
/// \input  EcuM_aucUser[0u]                           = 0xF0u
/// \input  EcuM_ulRunRequestCnt                       = 1u
/// \input  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u
///
/// - Expectations:
///
/// \output EcuM_aucUser[0u]                           = 0xF0u
/// \output EcuM_ulRunRequestCnt                       = 1u
/// \output SysMonRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount   = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_Sleep_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  EcuM_aucUser[0u]                           = 0xF0u;
  EcuM_ulRunRequestCnt                       = 1u;
  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u;
  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Sleep_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,                       1u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[0u],                        0xF0u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_DisableCallbacks_HitCount,    1u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_DeactivateTxBuffer_HitCount,  1u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,   1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_Connected_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Runs NM Request and
///                        Enables SysMon and SigPrep Rx/Tx
///
/// - Preconditions:
///
/// \input  EcuM_aucUser[0u]                           = 0x0Fu
/// \input  EcuM_ulRunRequestCnt                       = 1u
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount     = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount     = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount    = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount    = 0u
///
/// - Expectations:
///
/// \output EcuM_aucUser[0u]                           = 0x0Fu
/// \output EcuM_ulRunRequestCnt                       = 1u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount     = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount     = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount    = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount    = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_Connected_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  EcuM_aucUser[0u]                           = 0x0Fu;
  EcuM_ulRunRequestCnt                       = 1u;
  SysMonRx_ComM_EnableCallbacks_HitCount     = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount     = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount    = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount    = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Connected_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRunRequestCnt,                       1u, == );
  AL_UNITTEST_CHECK(EcuM_aucUser[0u],                        0x0Fu, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,     0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,     0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,    0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,    0u, == );
}
#endif

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Releases PostRun request evaluation and
///                        Re-Enables SysMon and SigPrep Rx/Tx
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_On
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_AutonomWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_On
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Drive_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Valid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 1u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 1u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 1u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 1u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 1u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_On;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_AutonomWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_On;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Drive_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Valid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Evaluate_ReleasePostRun_Condtion();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Releases PostRun request evaluation and
///                        Skips release PostRun
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 1u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 1u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 1u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 1u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 1u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Evaluate_ReleasePostRun_Condtion();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetActiveApplication_TestCase_1
///
/// \Test Case Description
///        - Test subject: Empty Function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_aucUser[3u] = 3u
///
/// - Expectations:
///
/// \output EcuM_aucUser[3u] = 3u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetActiveApplication_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[3u] = 3u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_SetActiveApplication();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_aucUser[3u], 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Enables the charge pump
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eChargePumpState                    = eEcuM_ChargePump_NotEnabled
///
/// - Expectations:
///
/// \output EcuM_eChargePumpState                    = eEcuM_ChargePump_Enabled
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Enable_ChargePump_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eChargePumpState = eEcuM_ChargePump_NotEnabled;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Enable_ChargePump();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eChargePumpState, eEcuM_ChargePump_Enabled, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_NvmWrite_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the function handles NvM write command
///                        and returns the status of write operation  
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_boTriggerNvmWrite      = TRUE
/// \input  Nvm_WriteAll_HitCount       = 0u
/// \input  NvM_GetErrorStatus_Param1   = 1u
/// \input  NvM_GetErrorStatus_Param2   = 1u
/// \input  NvM_GetErrorStatus_HitCount = 0u
/// \input  EcuM_NvmWrite_RetVal        = 1u
///
/// - Expectations:
///
/// \output EcuM_boTriggerNvmWrite                    = FALSE
/// \output Nvm_WriteAll_HitCount                     = 1u
/// \output NvM_GetErrorStatus_Param1                 = 0u
/// \output NvM_GetErrorStatus_HitCount               = 1u
/// \output EcuM_NvmWrite_RetVal                      = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_NvmWrite_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boTriggerNvmWrite      = TRUE;
  Nvm_WriteAll_HitCount       = 0u;
  NvM_GetErrorStatus_Param1   = 1u;
  NvM_GetErrorStatus_Param2   = 1u;
  NvM_GetErrorStatus_HitCount = 0u;
  EcuM_NvmWrite_RetVal        = 1u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_NvmWrite_RetVal = EcuM_NvmWrite();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Nvm_WriteAll_HitCount,                     1u, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite,                 FALSE, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1,                 0u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount,               1u, == );
  AL_UNITTEST_CHECK(EcuM_NvmWrite_RetVal,                      0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_NvmWrite_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the function handles NvM write command
///                        and returns the status of write operation  
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_boTriggerNvmWrite      = FALSE
/// \input  Nvm_WriteAll_HitCount       = 0u
/// \input  NvM_GetErrorStatus_Param1   = 1u
/// \input  NvM_GetErrorStatus_Param2   = 0u
/// \input  NvM_GetErrorStatus_HitCount = 0u
/// \input  EcuM_NvmWrite_RetVal        = 0u
///
/// - Expectations:
///
/// \output EcuM_boTriggerNvmWrite                    = FALSE
/// \output Nvm_WriteAll_HitCount                     = 0u
/// \output NvM_GetErrorStatus_Param1                 = 0u
/// \output NvM_GetErrorStatus_HitCount               = 1u
/// \output EcuM_NvmWrite_RetVal                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_NvmWrite_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boTriggerNvmWrite      = FALSE;
  Nvm_WriteAll_HitCount       = 0u;
  NvM_GetErrorStatus_Param1   = 1u;
  NvM_GetErrorStatus_Param2   = 0u;
  NvM_GetErrorStatus_HitCount = 0u;
  EcuM_NvmWrite_RetVal        = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_NvmWrite_RetVal = EcuM_NvmWrite();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Nvm_WriteAll_HitCount,                     0u, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite,                 FALSE, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1,                 0u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount,               1u, == );
  AL_UNITTEST_CHECK(EcuM_NvmWrite_RetVal,                      1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Invalidate_Shutdown_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Updates the EcuM state
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState = eEcuM_WakeUp
///
/// - Expectations:
///
/// \output EcuM_eState = eEcuM_Up
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Invalidate_Shutdown_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eState = eEcuM_WakeUp;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Invalidate_Shutdown();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState, eEcuM_Up, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and handles PostRun Request
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
/// \input  CddSpi_Stop_HitCount                                                 = 0u
/// \input  CddBoost_Shutdown_HitCount                                           = 0u
/// \input  CddSbc_SetSleepMode_HitCount                                         = 0u
/// \input  EcuM_ulShutDownp_us                                                  = 6000u
/// \input  EcuM_ulPostRunRequestCnt                                             = 1u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 2u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 2u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 2u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 2u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 2u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
/// \output CddSpi_Stop_HitCount                                                   = 0u
/// \output CddBoost_Shutdown_HitCount                                             = 0u
/// \output CddSbc_SetSleepMode_HitCount                                           = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;
  CddSpi_Stop_HitCount                                                 = 0u;
  CddBoost_Shutdown_HitCount                                           = 0u;
  CddSbc_SetSleepMode_HitCount                                         = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // First Call - invalidate  SBC time-out flag
  EcuM_ShutDown_HandleTransitions();

  EcuM_ulShutDownp_us      = 6000u;
  EcuM_ulPostRunRequestCnt = 1u;

  //Step 3) Call FUT
  EcuM_ShutDown_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(CddSpi_Stop_HitCount,                                                      1u, == );
  AL_UNITTEST_CHECK(CddBoost_Shutdown_HitCount,                                                1u, == );
  AL_UNITTEST_CHECK(CddSbc_SetSleepMode_HitCount,                                              1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and Updates the EcuM state
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
/// \input  CddSpi_Stop_HitCount                                                 = 0u
/// \input  CddBoost_Shutdown_HitCount                                           = 0u
/// \input  CddSbc_SetSleepMode_HitCount                                         = 0u
/// \input  EcuM_eState                                                          = eEcuM_Up
/// \input  EcuM_ulShutDownp_us                                                  = 6000u
/// \input  EcuM_ulPostRunRequestCnt                                             = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 2u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 2u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 2u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 2u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 2u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
/// \output CddSpi_Stop_HitCount                                                   = 0u
/// \output CddBoost_Shutdown_HitCount                                             = 0u
/// \output CddSbc_SetSleepMode_HitCount                                           = 0u
/// \output EcuM_eState                                                            = eEcuM_Up
///
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;
  CddSpi_Stop_HitCount                                                 = 0u;
  CddBoost_Shutdown_HitCount                                           = 0u;
  CddSbc_SetSleepMode_HitCount                                         = 0u;
  EcuM_eState                                                          = eEcuM_Up;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // First Call - invalidate  SBC time-out flag
  EcuM_ShutDown_HandleTransitions();

  EcuM_ulShutDownp_us      = 6000u;
  EcuM_ulPostRunRequestCnt = 0u;

  //Step 3) Call FUT
  EcuM_ShutDown_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(CddSpi_Stop_HitCount,                                                      0u, == );
  AL_UNITTEST_CHECK(CddBoost_Shutdown_HitCount,                                                0u, == );
  AL_UNITTEST_CHECK(CddSbc_SetSleepMode_HitCount,                                              0u, == );
  AL_UNITTEST_CHECK(EcuM_eState,                                                         eEcuM_Up, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and does nothing while time-out did not expire
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
/// \input  CddSpi_Stop_HitCount                                                 = 0u
/// \input  CddBoost_Shutdown_HitCount                                           = 0u
/// \input  CddSbc_SetSleepMode_HitCount                                         = 0u
/// \input  EcuM_eState                                                          = eEcuM_WakeUp
/// \input  EcuM_ulShutDownp_us                                                  = 0u
/// \input  EcuM_ulPostRunRequestCnt                                             = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 2u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 2u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 2u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 2u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 2u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
/// \output CddSpi_Stop_HitCount                                                   = 0u
/// \output CddBoost_Shutdown_HitCount                                             = 0u
/// \output CddSbc_SetSleepMode_HitCount                                           = 0u
/// \output EcuM_eState                                                            = eEcuM_WakeUp
///
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;
  CddSpi_Stop_HitCount                                                 = 0u;
  CddBoost_Shutdown_HitCount                                           = 0u;
  CddSbc_SetSleepMode_HitCount                                         = 0u;
  EcuM_eState                                                          = eEcuM_WakeUp;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // First Call - invalidate  SBC time-out flag
  EcuM_ShutDown_HandleTransitions();

  EcuM_ulShutDownp_us      = 0u;
  EcuM_ulPostRunRequestCnt = 0u;

  //Step 3) Call FUT
  EcuM_ShutDown_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(CddSpi_Stop_HitCount,                                                      0u, == );
  AL_UNITTEST_CHECK(CddBoost_Shutdown_HitCount,                                                0u, == );
  AL_UNITTEST_CHECK(CddSbc_SetSleepMode_HitCount,                                              0u, == );
  AL_UNITTEST_CHECK(EcuM_eState,                                                     eEcuM_WakeUp, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and does nothing while time-out did not expire
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
/// \input  CddSpi_Stop_HitCount                                                 = 0u
/// \input  CddBoost_Shutdown_HitCount                                           = 0u
/// \input  CddSbc_SetSleepMode_HitCount                                         = 0u
/// \input  EcuM_eState                                                          = eEcuM_WakeUp
/// \input  EcuM_ulShutDownp_us                                                  = 0u
/// \input  EcuM_ulPostRunRequestCnt                                             = 0u
/// \input  EcuM_ulRunRequestCnt                                                 = 1u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 2u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 2u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 2u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 2u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 2u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
/// \output CddSpi_Stop_HitCount                                                   = 0u
/// \output CddBoost_Shutdown_HitCount                                             = 0u
/// \output CddSbc_SetSleepMode_HitCount                                           = 0u
/// \output EcuM_eState                                                            = eEcuM_WakeUp
///
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1 = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 10000u;
  EcuM_ulShutDownp_us = 0u;
  CddSpi_Stop_HitCount = 0u;
  CddBoost_Shutdown_HitCount = 0u;
  CddSbc_SetSleepMode_HitCount = 0u;
  EcuM_eState = eEcuM_WakeUp;
  boShutDownStatus = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // First Call - invalidate  SBC time-out flag
  EcuM_ShutDown_HandleTransitions();

  EcuM_ulShutDownp_us = 0u;
  //EcuM_ulPostRunRequestCnt = 0u;
  //EcuM_ulRunRequestCnt = 1u;

  //Step 3) Call FUT
  EcuM_ShutDown_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount, 2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount, 2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount, 2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount, 2u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount, 0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount, 0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount, 0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddSpi_Stop_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddBoost_Shutdown_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddSbc_SetSleepMode_HitCount, 0u, == );
  AL_UNITTEST_CHECK(EcuM_eState, eEcuM_WakeUp, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and does nothing while time-out did not expire
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
/// \input  CddSpi_Stop_HitCount                                                 = 0u
/// \input  CddBoost_Shutdown_HitCount                                           = 0u
/// \input  CddSbc_SetSleepMode_HitCount                                         = 0u
/// \input  EcuM_eState                                                          = eEcuM_WakeUp
/// \input  EcuM_ulShutDownp_us                                                  = 0u
/// \input  EcuM_ulPostRunRequestCnt                                             = 0u
/// \input  EcuM_ulRunRequestCnt                                                 = 1u
///
/// - Expectations:
///
/// \output CddSpi_Stop_HitCount                                                   = 0u
/// \output CddBoost_Shutdown_HitCount                                             = 0u
/// \output CddSbc_SetSleepMode_HitCount                                           = 0u
/// \output EcuM_eState                                                            = eEcuM_WakeUp
///
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode = eWarningMode_AutonomWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1 = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0u;
  EcuM_ulShutDownp_us = 0u;
  CddSpi_Stop_HitCount = 0u;
  CddBoost_Shutdown_HitCount = 0u;
  CddSbc_SetSleepMode_HitCount = 0u;
  EcuM_eState = eEcuM_WakeUp;
  boShutDownStatus = FALSE;
  EcuM_ulChangeSbcSleep_Timeout_Hook = ECUM_CHANGE_SLEEP_TIME_OUT_HOOK_ACTIVATION;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDown_HandleTransitions();


  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSpi_Stop_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddBoost_Shutdown_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddSbc_SetSleepMode_HitCount, 0u, == );
  AL_UNITTEST_CHECK(EcuM_eState, eEcuM_WakeUp, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_DiagResetRequest_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function resets diag request
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_boDiagReqReset = FALSE
///
/// - Expectations:
///
/// \output EcuM_boDiagReqReset = TRUE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_DiagResetRequest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_DiagResetRequest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_boDiagReqReset, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateShutDown_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and handles PostRun Request
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 1u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 1u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 1u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 1u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 1u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateShutDown_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_OnStateShutDown();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_StartOS_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization function EcuM_StartOS is called.
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_StartOS_Param1 = 23u
/// \input  StartOS_HitCount    = 0u
/// \input  StartOS_Param1      = 0u
///
/// - Expectations:
///
/// \output StartOS_HitCount = 1u
/// \output StartOS_Param1   = 23u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_StartOS_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  StartOS_HitCount    = 0u;
  StartOS_Param1      = 0u;

  //Step 2) Assign Input values
  EcuM_StartOS_Param1 = 23u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_StartOS(EcuM_StartOS_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(StartOS_HitCount,  1u, == );
  AL_UNITTEST_CHECK(StartOS_Param1,   23u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_AL_DriverInitOne_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization function EcuM_AL_DriverInitOne is called.
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1234,  LDM.MDRS_ECUM.1240, LDM.MDRS_ECUM.1246, LDM.MDRS_ECUM.1305,
/// LDM.MDRS_ECUM.1309,  LDM.MDRS_ECUM.493
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcu_InitClock_HitCount    = 0u
/// \input  Mcu_InitClock_Param1      = &ucClockType_Out
/// \input  ucClockType_Out           = 0xABu
/// \input  Mcu_InitClock_RetVal      = E_OK
///
/// - Expectations:
///
/// \output EcuM_DriverInitOne_FunctionList[ucIndex] != NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_AL_DriverInitOne_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mcu_ClockType ucClockType_Out;

  Mcu_InitClock_HitCount = 0u;
  Mcu_InitClock_Param1 = &ucClockType_Out;
  ucClockType_Out = 0xABu;
  Mcu_ClockData = 0xBAu;
  Mcu_InitClock_RetVal = E_OK;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_AL_DriverInitOne();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  for (uint8 ucIndex = 0u; ucIndex < (uint8)EcuM_DriverInitOne_Id_Count; ucIndex++)
  {
    AL_UNITTEST_CHECK(&EcuM_DriverInitOne_FunctionList[ucIndex], NULL_PTR, != );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_AL_DriverInitZero_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization function EcuM_AL_DriverInitZero is called.
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1204,  LDM.MDRS_ECUM.1208, LDM.MDRS_ECUM.1210, LDM.MDRS_ECUM.1310,
/// LDM.MDRS_ECUM.1216,  LDM.MDRS_ECUM.1222, LDM.MDRS_ECUM.1226, LDM.MDRS_ECUM.1228,
/// LDM.MDRS_ECUM.1232,  LDM.MDRS_ECUM.496
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
///
/// - Expectations:
///
/// \output EcuM_DriverInitZero_FunctionList[ucIndex] != NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_AL_DriverInitZero_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  //--

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_AL_DriverInitZero();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  for (uint8 ucIndex = 0u; ucIndex < (uint8)EcuM_DriverInitZero_Id_Count; ucIndex++)
  {
    AL_UNITTEST_CHECK(&EcuM_DriverInitZero_FunctionList[ucIndex], NULL_PTR, != );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_StartupTwo_Trusted_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization function EcuM_StartupTwo_Trusted is called.
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.442,  LDM.MDRS_ECUM.444, LDM.MDRS_ECUM.1252, LDM.MDRS_ECUM.1256
/// LDM.MDRS_ECUM.904
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  
///
/// - Expectations:
///
/// \output EcuM_StartupTwo_Trusted_FunctionList[ucIndex] != NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_StartupTwo_Trusted_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  //--

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_StartupTwo_Trusted();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  for (uint8 ucIndex = 0u; ucIndex < (uint8)EcuM_Startup_Two_Trusted_Id_Count; ucIndex++)
  {
    AL_UNITTEST_CHECK(EcuM_StartupTwo_Trusted_FunctionList[ucIndex], NULL_PTR, != );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_StartupTwo_NonTrusted_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization function EcuM_StartupTwo_NonTrusted is called.
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
///
/// - Expectations:
///
/// \output EcuM_StartupTwo_Trusted_FunctionList[ucIndex] != NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_StartupTwo_NonTrusted_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  //--

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_StartupTwo_NonTrusted();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  for (uint8 ucIndex = 0u; ucIndex < (uint8)EcuM_Startup_Two_NonTrusted_Id_Count; ucIndex++)
  {
    AL_UNITTEST_CHECK(EcuM_StartupTwo_NonTrusted_FunctionList[ucIndex], NULL_PTR, != );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_sEcuInternalResetReason.eMcuResetReason                           = MCU_RESET_UNDEFINED
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.eMcuResetReason                           = MCU_RESET_UNDEFINED
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_sEcuInternalResetReason.eMcuResetReason                           = MCU_RESET_UNDEFINED;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_SetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.eMcuResetReason, MCU_RESET_UNDEFINED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_sEcuInternalResetReason.eMcuResetReason                           = MCU_RESET_UNDEFINED
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.eMcuResetReason                           = MCU_WATCHDOG_RESET
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ShaDataMem[38] = 0x5A01u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_SetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (Clock configuration failed Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unClock_Cfg_Reset = 0x5A01u; // Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biClock_Cfg_ResetReason = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_3(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unClock_Cfg_Reset = 0x5A01u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biClock_Cfg_ResetReason, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (Clock configuration Pass)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unClock_Cfg_Reset = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biClock_Cfg_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_4(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unClock_Cfg_Reset = 0x5A00u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biClock_Cfg_ResetReason, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (SBC watchdog Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unSBC_Wdg_Reset = 0x5A01u; // Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_5(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unSBC_Wdg_Reset = 0x5A01u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (SBC Wdg ResetPass)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unSBC_Wdg_Reset = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_6(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unSBC_Wdg_Reset = 0x5A00u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biSBC_WDG_ResetReason, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (MPU self test failed Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unMpu_Self_Test_Reset = 0x5A01u; // Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biMPU_Self_Test_ResetReason = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_7(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unMpu_Self_Test_Reset = 0x5A01u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biMPU_Self_Test_ResetReason, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (MPU self test Pass)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unMpu_Self_Test_Reset = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biMPU_Self_Test_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_8(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unMpu_Self_Test_Reset = 0x5A00u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biMPU_Self_Test_ResetReason, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (ECC double bit error Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unEcc_DED_Reset = 0x5A01u; // Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biECC_DED_ResetReason = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_9(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unEcc_DED_Reset = 0x5A01u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biECC_DED_ResetReason, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_10
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (ECC double bit error No Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unEcc_DED_Reset = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biECC_DED_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_10(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unEcc_DED_Reset = 0x5A00u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biECC_DED_ResetReason, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_11
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (App Crc error Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unCRC_App_Reset = 0x5A01u; // Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_11(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unCRC_App_Reset = 0x5A01u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_12
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (App Crc No Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unCRC_App_Reset = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_12(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unCRC_App_Reset = 0x5A00u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biCRC_App_ResetReason, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_13
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (HardFault Sw Lock Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unHardFaultSwLock = 0x5A01u; // Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biHard_Fault_ResetReason = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_13(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unHardFaultSwLock = 0x5A01u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biHard_Fault_ResetReason, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_14
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (HardFault Sw Lock No Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unHardFaultSwLock = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biHard_Fault_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_14(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unHardFaultSwLock = 0x5A00u;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biHard_Fault_ResetReason, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_SetResetReason_TestCase_15
///
/// \Test Case Description
///        - Test subject: Test if function Reads the reset reason using Mcu_GetResetReason (HardFault Sw Lock No Reset)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32] // ShaData emulation
/// \input  psTestShaDataHwErr->unHardFaultSwLock = 0x5A00u; // No Reset event stored in ShaData
///
/// - Expectations:
///
/// \output EcuM_sEcuInternalResetReason.uEcuInternalResetReason.Bit.biHard_Fault_ResetReason = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_SetResetReason_TestCase_15(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
	tsEcuM_EcuInternalErrors *psTestShaDataHwErr = (tsEcuM_EcuInternalErrors *)&EcuM_ShaDataMem[32];
	psTestShaDataHwErr->unMPU_Bus_Fault_Cnt = 100u;
	EcuM_sEcuInternalResetReason.eMcuResetReason = MCU_LOSS_OF_LOCK_RESET;

	Mcu_GetResetReason_RetVal = MCU_POWER_ON_RESET;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

	Mcu_Init();

  //Step 3) Call FUT
	EcuM_SetResetReason();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
	AL_UNITTEST_CHECK(psTestShaDataHwErr->unMPU_Bus_Fault_Cnt, 0u, == );
	AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.eMcuResetReason, MCU_POWER_ON_RESET, == );
}

/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 8
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.634, LDM.MDRS_ECUM.636
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						  = TRUE
/// \input  EcuM_ulMcuPrivStatus						      = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						  = 0u
/// \input  EcuM_boTriggerHardFault_MPUST8				      = FALSE
/// \input  MPU->CESR									      = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST8 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 8
///          1) MCU in User
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.634, LDM.MDRS_ECUM.636
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST8				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_2(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST8 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 8
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags not set (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.634, LDM.MDRS_ECUM.636
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST8				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST8				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x0u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_3(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST8 = TRUE;
  EcuM_boUpdateMPUReg_MPUST8 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= (0u << 27u);
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 8
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Flags wrong (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.634, LDM.MDRS_ECUM.636
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST8				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST8				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x3u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_4(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST8 = TRUE;
  EcuM_boUpdateMPUReg_MPUST8 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x3u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x3u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 8
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Address Error (SELF TEST FAILED)
///			     5) Details Error (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.634, LDM.MDRS_ECUM.636
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST8				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST8				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 15u
/// \input  MPU->EDR                                    = (0x3u << 1u) | 0x0u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 3u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_5(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST8 = TRUE;
  EcuM_boUpdateMPUReg_MPUST8 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 15u;
  MPU->EAR_EDR[3].EDR = (0x3u << 1u) | 0x0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 3u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 8
///          1) MCU in USER
///			     2) Hard Fault is raised
///			     3) MPU Self-Test Passed
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.634, LDM.MDRS_ECUM.636
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST8				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST8				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 16u
/// \input  MPU->EDR                                    = (0x1u << 1u) | 0x1u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = ECUM_MPU_SELF_TEST_RESULT_PASS
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_6(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST8 = TRUE;
  EcuM_boUpdateMPUReg_MPUST8 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 16u;
  MPU->EAR_EDR[3].EDR = (0x1u << 1u) | 0x1u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_8();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest8_Res, 0x1u, == );
}


/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 7
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST PASSED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.631, LDM.MDRS_ECUM.633
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST7				      = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST7 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_7();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x00u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res, 0x1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 7
///          1) MCU in user
///			     2) Hard Fault is raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.631, LDM.MDRS_ECUM.633
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST7				      = TRUE
/// \input  MPU->CESR                                  |= 0x2u << 27us
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST7 = TRUE;
  MPU->CESR = 0x2u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_7();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 7
///          1) MCU in privilege
///			     2) Hard Fault is raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.631, LDM.MDRS_ECUM.633
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST7				      = TRUE
/// \input  MPU->CESR                                  |= 0x2u << 27us
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST7 = TRUE;
  MPU->CESR = 0x2u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_7();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest7_Res, 0x2u, == );
}


/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 6
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST PASSED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.628, LDM.MDRS_ECUM.630
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST6				      = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST6 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_6();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x00u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res, 0x1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 6
///          1) MCU in user
///			     2) Hard Fault is raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.628, LDM.MDRS_ECUM.630
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST6				      = TRUE
/// \input  MPU->CESR                                  |= 0x2u << 27us
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST6 = TRUE;
  MPU->CESR = 0x2u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res = 0x0u;

  //Step 2) Assign Input values
  //--


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_6();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest6_Res, 0x2u, == );
}

/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 5
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST PASSED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.625, LDM.MDRS_ECUM.627
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST5				      = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST5 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_5();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x00u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res, 0x1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 5
///          1) MCU in user
///			     2) Hard Fault is raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.625, LDM.MDRS_ECUM.627
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST5				      = TRUE
/// \input  MPU->CESR                                  |= 0x2u << 27us
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST5 = TRUE;
  MPU->CESR = 0x2u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_5();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest5_Res, 0x2u, == );
}


/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 4
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.622,  LDM.MDRS_ECUM.624
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST4				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST4 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 4
///          1) MCU in User
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.622,  LDM.MDRS_ECUM.624
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST4				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_2(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST4 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res, 0x2u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 4
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags not set (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.622,  LDM.MDRS_ECUM.624
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST4				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST4				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x0u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_3(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST4 = TRUE;
  EcuM_boUpdateMPUReg_MPUST4 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= (0u << 27u);
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 4
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Flags wrong (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.622,  LDM.MDRS_ECUM.624
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST4				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST4				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x3u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_4(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST4 = TRUE;
  EcuM_boUpdateMPUReg_MPUST4 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x3u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x3u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 4
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Address Error (SELF TEST FAILED)
///			     5) Details Error (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.622,  LDM.MDRS_ECUM.624
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST4				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST4				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 23u
/// \input  MPU->EDR                                    = (0x2u << 1u) | 0x0u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 3u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_5(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST4 = TRUE;
  EcuM_boUpdateMPUReg_MPUST4 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 23u;
  MPU->EAR_EDR[3].EDR = (0x2u << 1u) | 0x0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 3u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 4
///          1) MCU in USER
///			     2) Hard Fault is raised
///			     3) MPU Self-Test Passed
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.622,  LDM.MDRS_ECUM.624
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST4				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST4				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 24u
/// \input  MPU->EDR                                    = (0x1u << 1u) | 0x1u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = ECUM_MPU_SELF_TEST_RESULT_PASS
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_6(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST4 = TRUE;
  EcuM_boUpdateMPUReg_MPUST4 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 24u;
  MPU->EAR_EDR[3].EDR = (0x1u << 1u) | 0x1u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_4();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest4_Res, 0x1u, == );
}

/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 3
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.619, LDM.MDRS_ECUM.621
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST3				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST3 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 3
///          1) MCU in User
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.619, LDM.MDRS_ECUM.621
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST3				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_2(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST3 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 3
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags not set (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.619, LDM.MDRS_ECUM.621
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST3				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST3				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x0u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_3(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST3 = TRUE;
  EcuM_boUpdateMPUReg_MPUST3 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= (0u << 27u);
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 3
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Flags wrong (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.619, LDM.MDRS_ECUM.621
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST3				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST3				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x3u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_4(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST3 = TRUE;
  EcuM_boUpdateMPUReg_MPUST3 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x3u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x3u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 3
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Address Error (SELF TEST FAILED)
///			     5) Details Error (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.619, LDM.MDRS_ECUM.621
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST3				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST3				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 7u
/// \input  MPU->EDR                                    = (0x3u << 1u) | 0x1u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 3u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_5(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST3 = TRUE;
  EcuM_boUpdateMPUReg_MPUST3 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 7u;
  MPU->EAR_EDR[3].EDR = (0x3u << 1u) | 0x1u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 3u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 3
///          1) MCU in USER
///			     2) Hard Fault is raised
///			     3) MPU Self-Test Passed
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.619, LDM.MDRS_ECUM.621
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST3				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST3				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 8u
/// \input  MPU->EDR                                    = (0x1u << 1u) | 0x0u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = ECUM_MPU_SELF_TEST_RESULT_PASS
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_6(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST3 = TRUE;
  EcuM_boUpdateMPUReg_MPUST3 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 8u;
  MPU->EAR_EDR[3].EDR = (0x1u << 1u) | 0x0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_3();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest3_Res, 0x1u, == );
}


/////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 2
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.616,  LDM.MDRS_ECUM.618
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST2				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST2 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 2
///          1) MCU in User
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.616,  LDM.MDRS_ECUM.618
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST2				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_2(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST2 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res, 0x2u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 2
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags not set (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
////
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.616,  LDM.MDRS_ECUM.618
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST2				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST2				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x0u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_3(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST2 = TRUE;
  EcuM_boUpdateMPUReg_MPUST2 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= (0u << 27u);
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 2
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Flags wrong (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
////
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.616,  LDM.MDRS_ECUM.618
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST2				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST2				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x3u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_4(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST2 = TRUE;
  EcuM_boUpdateMPUReg_MPUST2 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x3u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x3u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 2
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Address Error (SELF TEST FAILED)
///			     5) Details Error (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.616,  LDM.MDRS_ECUM.618
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST2				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST2				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 15u
/// \input  MPU->EDR                                    = (0x2u << 1u) | 0x0u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 3u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest2Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_5(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST2 = TRUE;
  EcuM_boUpdateMPUReg_MPUST2 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 15u;
  MPU->EAR_EDR[3].EDR = (0x2u << 1u) | 0x0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 3u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 2
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU Self-Test Passed
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.616,  LDM.MDRS_ECUM.618
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST2				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST2				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 16u
/// \input  MPU->EDR                                    = (0x3u << 1u) | 0x1u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = ECUM_MPU_SELF_TEST_RESULT_PASS
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_6(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST2 = TRUE;
  EcuM_boUpdateMPUReg_MPUST2 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 16u;
  MPU->EAR_EDR[3].EDR = (0x3u << 1u) | 0x1u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest2_Res, 0x1u, == );
}

/////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 1
///          1) MCU in privilege
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.613,  LDM.MDRS_ECUM.615
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST1				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus                        = 1u;
  EcuM_ucMPUSelfTestErrCnt                    = 0u;
  EcuM_boTriggerHardFault_MPUST1              = FALSE;
  MPU->CESR                                   = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt,                     1u, == );
  AL_UNITTEST_CHECK(MPU->CESR,                                  0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 1
///          1) MCU in User
///			     2) Hard Fault is not raised (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.613,  LDM.MDRS_ECUM.615
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 0u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST1				      = FALSE
/// \input  MPU->CESR									                  = 0x0u
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_2(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 0u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST1 = FALSE;
  MPU->CESR = 0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt,                       1u, == );
  AL_UNITTEST_CHECK(MPU->CESR,                                   0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res,  0x2u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 1
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags not set (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.613,  LDM.MDRS_ECUM.615
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST1				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST1				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x0u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_3(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST1 = TRUE;
  EcuM_boUpdateMPUReg_MPUST1 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= (0u << 27u);
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, 0x01u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 1
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Flags wrong (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.613,  LDM.MDRS_ECUM.615
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST1				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST1				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x3u << 27s
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 1u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_4(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST1 = TRUE;
  EcuM_boUpdateMPUReg_MPUST1 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x3u << 27u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 1u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x3u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res, 0x2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 1
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU flags set
///			     4) Address Error (SELF TEST FAILED)
///			     5) Details Error (SELF TEST FAILED)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.613,  LDM.MDRS_ECUM.615
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST1				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST1				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 3u
/// \input  MPU->EDR                                    = (0x2u << 1u) | 0x1u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 3u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = ECUM_MPU_SELF_TEST_RESULT_FAIL
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_5(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST1 = TRUE;
  EcuM_boUpdateMPUReg_MPUST1 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 3u;
  MPU->EAR_EDR[3].EDR = (0x2u << 1u) | 0x1u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 3u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res, 0x2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test MPU seftest 1
///          1) MCU in Privilege
///			     2) Hard Fault is raised
///			     3) MPU Self-Test Passed
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.613,  LDM.MDRS_ECUM.615
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable						        = TRUE
/// \input  EcuM_ulMcuPrivStatus						            = 1u
/// \input  EcuM_ucMPUSelfTestErrCnt						        = 0u
/// \input  EcuM_boTriggerHardFault_MPUST1				      = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST1				          = FALSE
/// \input  MPU->CESR                                   = 0u
/// \input  MPU->CESR                                  |= 0x2u << 27s
/// \input  MPU->EAR                                    = (volatile uint32)&ulEcuM_Mpu_SelfTest[0] + 4u
/// \input  MPU->EDR                                    = (0x3u << 1u) | 0x0u;
/// \input  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u
///
/// - Expectations:
///
/// \output EcuM_ucMPUSelfTestErrCnt                    = 0u
/// \output MPU->CESR                                   = (0x2u << 27u) | 0x1u
/// \output EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = ECUM_MPU_SELF_TEST_RESULT_PASS
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_6(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable = TRUE;
  EcuM_ulMcuPrivStatus = 1u;
  EcuM_ucMPUSelfTestErrCnt = 0u;
  EcuM_boTriggerHardFault_MPUST1 = TRUE;
  EcuM_boUpdateMPUReg_MPUST1 = FALSE;
  MPU->CESR = 0u;
  MPU->CESR |= 0x2u << 27u;
  MPU->EAR_EDR[3].EAR = ((volatile uint32)&ulEcuM_Mpu_SelfTest[0]) + 4u;
  MPU->EAR_EDR[3].EDR = (0x3u << 1u) | 0x0u;
  EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res = 0x0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Test_1();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ucMPUSelfTestErrCnt, 0u, == );
  AL_UNITTEST_CHECK(MPU->CESR, (0x2u << 27u) | 0x1u, == );
  AL_UNITTEST_CHECK(EcuM_uMpu_SelfTest_State.Bit.biMpuTest1_Res, 0x1u, == );
}


///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_MPU_Config_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Function cofigures the registers
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.601,  LDM.MDRS_ECUM.603
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Mpu.CESR         = 0x00u
/// \input Mpu.RGD[1].WORD0 = 0x01u
/// \input Mpu.RGD[1].WORD1 = 0x00u
/// \input Mpu.RGD[1].WORD2 = 0x00u
/// \input Mpu.RGD[1].WORD3 = 0x00u
/// \input Mpu.RGD[2].WORD0 = 0x01u
/// \input Mpu.RGD[2].WORD1 = 0x00u
/// \input Mpu.RGD[2].WORD2 = 0x00u
/// \input Mpu.RGD[2].WORD3 = 0x00u
/// \input Mpu.RGD[3].WORD0 = 0x01u
/// \input Mpu.RGD[3].WORD1 = 0x00u
/// \input Mpu.RGD[3].WORD2 = 0x00u
/// \input Mpu.RGD[3].WORD3 = 0x00u
/// \input Mpu.RGD[4].WORD0 = 0x01u
/// \input Mpu.RGD[4].WORD1 = 0x00u
/// \input Mpu.RGD[4].WORD2 = 0x00u
/// \input Mpu.RGD[4].WORD3 = 0x00u
/// \input Mpu.RGDAAC[0]    = 0x00u
///
/// - Expectations:
///
/// \output Mpu.CESR         = 0x01u
/// \output Mpu.RGD[1].WORD0 = 0x00u
/// \output Mpu.RGD[1].WORD1 = &ulEcuM_Mpu_SelfTest-1
/// \output Mpu.RGD[1].WORD2 = 0x1C71C7u
/// \output Mpu.RGD[1].WORD3 = 0x01u
/// \output Mpu.RGD[2].WORD0 = &ulEcuM_Mpu_SelfTest
/// \output Mpu.RGD[2].WORD1 = &ulEcuM_Mpu_SelfTest
/// \output Mpu.RGD[2].WORD2 = 0x1C71D8u
/// \output Mpu.RGD[2].WORD3 = 0x01u
/// \output Mpu.RGD[3].WORD0 = &ulEcuM_Mpu_SelfTest
/// \output Mpu.RGD[3].WORD1 = &ulEcuM_Mpu_SelfTest
/// \output Mpu.RGD[3].WORD2 = 0x1C71C4u
/// \output Mpu.RGD[3].WORD3 = 0x01u
/// \output Mpu.RGD[4].WORD0 = &ulEcuM_Mpu_SelfTest + 1
/// \output Mpu.RGD[4].WORD1 = 0xFFFFFFFFu
/// \output Mpu.RGD[4].WORD2 = 0x1C71C7u
/// \output Mpu.RGD[4].WORD3 = 0x01u
/// \output Mpu.RGDAAC[0]    = 0x18u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_MPU_Config_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mpu.CESR         = 0x00u;
  Mpu.RGD[1].WORD0 = 0x01u;
  Mpu.RGD[1].WORD1 = 0x00u;
  Mpu.RGD[1].WORD2 = 0x00u;
  Mpu.RGD[1].WORD3 = 0x00u;
  Mpu.RGD[2].WORD0 = 0x01u;
  Mpu.RGD[2].WORD1 = 0x00u;
  Mpu.RGD[2].WORD2 = 0x00u;
  Mpu.RGD[2].WORD3 = 0x00u;
  Mpu.RGD[3].WORD0 = 0x01u;
  Mpu.RGD[3].WORD1 = 0x00u;
  Mpu.RGD[3].WORD2 = 0x00u;
  Mpu.RGD[3].WORD3 = 0x00u;
  Mpu.RGD[4].WORD0 = 0x01u;
  Mpu.RGD[4].WORD1 = 0x00u;
  Mpu.RGD[4].WORD2 = 0x00u;
  Mpu.RGD[4].WORD3 = 0x00u;
  Mpu.RGDAAC[0]    = 0x00u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_MPU_Config();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mpu.CESR,                                            0x01u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[1].WORD0,                                    0x00u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[1].WORD1,     ((uint32)&ulEcuM_Mpu_SelfTest[0])-1u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[1].WORD2,                                0x1C71C7u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[1].WORD3,                                    0x01u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[2].WORD0,          (uint32)&ulEcuM_Mpu_SelfTest[0], == );
  AL_UNITTEST_CHECK(Mpu.RGD[2].WORD1,          (uint32)&ulEcuM_Mpu_SelfTest[0], == );
  AL_UNITTEST_CHECK(Mpu.RGD[2].WORD2,                                0x1C71D8u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[2].WORD3,                                    0x01u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[3].WORD0,          (uint32)&ulEcuM_Mpu_SelfTest[0], == );
  AL_UNITTEST_CHECK(Mpu.RGD[3].WORD1,          (uint32)&ulEcuM_Mpu_SelfTest[0], == );
  AL_UNITTEST_CHECK(Mpu.RGD[3].WORD2,                                0x1C71C4u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[3].WORD3,                                    0x01u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[4].WORD0,    ((uint32)&ulEcuM_Mpu_SelfTest[0] + 1), == );
  AL_UNITTEST_CHECK(Mpu.RGD[4].WORD1,                              0xFFFFFFFFu, == );
  AL_UNITTEST_CHECK(Mpu.RGD[4].WORD2,                                0x1C71C7u, == );
  AL_UNITTEST_CHECK(Mpu.RGD[4].WORD3,                                    0x01u, == );
  AL_UNITTEST_CHECK(Mpu.RGDAAC[0],                                       0x18u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if funtion Gets MPU error status and error information
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.466,  LDM.MDRS_ECUM.468, LDM.MDRS_ECUM.610, LDM.MDRS_ECUM.612
/// LDM.MDRS_ECUM.857
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mpu.CESR                                                       = 0x10000000u
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus      = FALSE
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags       = 0x00u
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3]  = 0x00u
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3] = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                                             = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                                             = 0x03u
///
/// - Expectations:
///
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus      = TRUE
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags       = 0x02u
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3]  = 0x05u
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3] = 0x03u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mpu.CESR                                                       = 0x10000000u;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus      = FALSE;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags       = 0x00u;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3]  = 0x00u;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3] = 0x00u;
  Mpu.EAR_EDR[3].EAR                                             = 0x05u;
  Mpu.EAR_EDR[3].EDR                                             = 0x03u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_mpu_SelfTest_GestMpuHwStatus(&EcuM_mpu_SelfTest_GestMpuHwStatus_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus,              TRUE, == );
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags,              0x02u, == );
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3],         0x05u, == );
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3],        0x03u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if funtion Gets MPU error status and error information
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.466,  LDM.MDRS_ECUM.468, LDM.MDRS_ECUM.610, LDM.MDRS_ECUM.612
/// LDM.MDRS_ECUM.857
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mpu.CESR                                                       = 0x10000000u
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus      = TRUE
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags       = 0x00u
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3]  = 0x00u
/// \input  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3] = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                                             = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                                             = 0x03u
///
/// - Expectations:
///
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus      = FALSE
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags       = 0x00u
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3]  = 0x00u
/// \output EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3] = 0x00u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mpu.CESR                                                       = 0x00u;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus      = TRUE;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags       = 0x00u;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3]  = 0x00u;
  EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3] = 0x00u;
  Mpu.EAR_EDR[3].EAR                                             = 0x05u;
  Mpu.EAR_EDR[3].EDR                                             = 0x03u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_mpu_SelfTest_GestMpuHwStatus(&EcuM_mpu_SelfTest_GestMpuHwStatus_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.boMPUErrorStatus,             FALSE, == );
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ucMPUErrorFlags,              0x00u, == );
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUAddressError[3],         0x00u, == );
  AL_UNITTEST_CHECK(EcuM_mpu_SelfTest_GestMpuHwStatus_Param1.ulMPUDetailedError[3],        0x00u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_RestoreDefaultReg0W2_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if funtion restores default region
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.607, LDM.MDRS_ECUM.609, LDM.MDRS_ECUM.851
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mpu.RGDAAC[0]                    = 0x00u
/// \input  EcuM_ulRegion0Word2_DefaultValue = 0x01u
/// \input  Mpu.CESR                         = 0x05u
///
/// - Expectations:
///
/// \output Mpu.RGDAAC[0]                    = 0x01u
/// \output Mpu.CESR                         = 0x05u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_RestoreDefaultReg0W2_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mpu.RGDAAC[0]                    = 0x00u;
  EcuM_ulRegion0Word2_DefaultValue = 0x01u;
  Mpu.CESR                         = 0x05u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_RestoreDefaultReg0W2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mpu.RGDAAC[0], 0x01u, == );
  AL_UNITTEST_CHECK(Mpu.CESR,      0x05u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_GetDefaultReg0W2_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if funtion gets MPU default region 2 setup
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.604, LDM.MDRS_ECUM.606, LDM.MDRS_ECUM.851
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mpu.RGD[0].WORD2                 = 0x08u
/// \input  EcuM_ulRegion0Word2_DefaultValue = 0x00u
///
/// - Expectations:
///
/// \output EcuM_ulRegion0Word2_DefaultValue = 0x08u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_GetDefaultReg0W2_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mpu.RGD[0].WORD2                 = 0x08u;
  EcuM_ulRegion0Word2_DefaultValue = 0x00u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_GetDefaultReg0W2();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulRegion0Word2_DefaultValue, 0x08u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_PLL_Unlock_SelfTest_Fail_Reaction_TestCase_1
///
/// \Test Case Description
///        - Test subject: Empty Function
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.655, LDM.MDRS_ECUM.1277, LDM.MDRS_ECUM.1282, LDM.MDRS_ECUM.1292,
/// LDM.MDRS_ECUM.1296
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_aucUser[3u] = 3u
///
/// - Expectations:
///
/// \output EcuM_aucUser[3u] = 3u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_PLL_Unlock_SelfTest_Fail_Reaction_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[3u] = 3u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_PLL_Unlock_SelfTest_Fail_Reaction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_aucUser[3u], 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Unused_Opcode_SelfTest_Fail_Reaction_TestCase_1
///
/// \Test Case Description
///        - Test subject: Empty Function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_aucUser[3u] = 3u
///
/// - Expectations:
///
/// \output EcuM_aucUser[3u] = 3u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Unused_Opcode_SelfTest_Fail_Reaction_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[3u] = 3u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Unused_Opcode_SelfTest_Fail_Reaction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_aucUser[3u], 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ECC_SelfTest_Fail_Reaction_TestCase_1
///
/// \Test Case Description
///        - Test subject: Empty Function
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.643, LDM.MDRS_ECUM.645
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_aucUser[3u] = 3u
///
/// - Expectations:
///
/// \output EcuM_aucUser[3u] = 3u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ECC_SelfTest_Fail_Reaction_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_aucUser[3u] = 3u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ECC_SelfTest_Fail_Reaction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_aucUser[3u], 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_PLLUnlockSelfTest_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function returns ECUM_SELFTEST_PASS
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_PLLUnlockSelfTest_RetVal = 1u
///
/// - Expectations:
///
/// \output EcuM_PLLUnlockSelfTest_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_PLLUnlockSelfTest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_PLLUnlockSelfTest_RetVal = 1u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_PLLUnlockSelfTest_RetVal = EcuM_PLLUnlockSelfTest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_PLLUnlockSelfTest_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_UnusedOpcodeSelfTest_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function returns ECUM_SELFTEST_PASS
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_UnusedOpcodeSelfTest_RetVal = 1u
///
/// - Expectations:
///
/// \output EcuM_UnusedOpcodeSelfTest_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_UnusedOpcodeSelfTest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_UnusedOpcodeSelfTest_RetVal = 1u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_UnusedOpcodeSelfTest_RetVal = EcuM_UnusedOpcodeSelfTest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_UnusedOpcodeSelfTest_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ECCSelfTest_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function returns ECUM_SELFTEST_PASS
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.640, LDM.MDRS_ECUM.642
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ECCSelfTest_RetVal = 1u
///
/// - Expectations:
///
/// \output EcuM_ECCSelfTest_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ECCSelfTest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ECCSelfTest_RetVal = 1u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ECCSelfTest_RetVal = EcuM_ECCSelfTest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ECCSelfTest_RetVal, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPU_SelfTest_Fail_Reaction_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MPU Self Test Reaction
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.598, LDM.MDRS_ECUM.600
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcu_PerformReset_HitCount = 0u
/// \input  ulEcuM_Mpu_SelfTest       = 0u
///
/// - Expectations:
///
/// \output Mcu_PerformReset_HitCount = 1u
/// \output ulEcuM_Mpu_SelfTest       = 20u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPU_SelfTest_Fail_Reaction_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mcu_PerformReset_HitCount = 0u;
  ulEcuM_Mpu_SelfTest[98] = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPU_SelfTest_Fail_Reaction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount,          1u, == );
  AL_UNITTEST_CHECK(ulEcuM_Mpu_SelfTest[98],       0x5a01u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_HardFault_Handler_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test MCU Hard_Fault handler
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.469,  LDM.MDRS_ECUM.471, LDM.MDRS_ECUM.848, LDM.MDRS_ECUM.854
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable                = 1u
/// \input  EcuM_ulHardFaultErrCnt                  = 0u
/// \input  Mpu.CESR                                = 0x10000000u
/// \input  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE
/// \input  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                      = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                      = 0x03u
///
/// - Expectations:
///
/// \output EcuM_ulHardFaultErrCnt                  = 1u
/// \output EcuM_sMpuErrState.boMPUErrorStatus      = TRUE
/// \output EcuM_sMpuErrState.ucMPUErrorFlags       = 0x02u
/// \output EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x05u
/// \output EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x03u
/// \output Mpu.CESR                                = 0x10000000u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_HardFault_Handler_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable                = 1u;
  EcuM_ulHardFaultErrCnt                  = 0u;
  Mpu.CESR                                = 0x10000000u;
  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE;
  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u;
  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u;
  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u;
  Mpu.EAR_EDR[3].EAR                      = 0x05u;
  Mpu.EAR_EDR[3].EDR                      = 0x03u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  HardFault_Handler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulHardFaultErrCnt,                            1u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.boMPUErrorStatus,              TRUE, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ucMPUErrorFlags,              0x02u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUAddressError[3],         0x05u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUDetailedError[3],        0x03u, == );
  AL_UNITTEST_CHECK(Mpu.CESR,                                 0x10000000u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_HardFault_Handler_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test MCU Hard_Fault handler
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.469,  LDM.MDRS_ECUM.471, LDM.MDRS_ECUM.848, LDM.MDRS_ECUM.854
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMPUSelfTestEnable                = 1u
/// \input  EcuM_ulHardFaultErrCnt                  = 0u
/// \input  Mpu.CESR                                = 0x10000000u
/// \input  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE
/// \input  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                      = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                      = 0x03u
///
/// - Expectations:
///
/// \output EcuM_ulHardFaultErrCnt                  = 0u
/// \output EcuM_sMpuErrState.boMPUErrorStatus      = FALSE
/// \output EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u
/// \output EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u
/// \output EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u
/// \output Mpu.CESR                                = 0x10000000u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_HardFault_Handler_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMPUSelfTestEnable                = 0u;
  EcuM_ulHardFaultErrCnt                  = 0u;
  Mpu.CESR                                = 0x10000000u;
  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE;
  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u;
  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u;
  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u;
  Mpu.EAR_EDR[3].EAR                      = 0x05u;
  Mpu.EAR_EDR[3].EDR                      = 0x03u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  HardFault_Handler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ulHardFaultErrCnt,                            0u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.boMPUErrorStatus,             FALSE, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ucMPUErrorFlags,              0x00u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUAddressError[3],         0x00u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUDetailedError[3],        0x00u, == );
  AL_UNITTEST_CHECK(Mpu.CESR,                                 0x10000000u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPUSelfTest_TestCase_1
///
/// \Test Case Description
///        - Test subject: MPU self test performing
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.559,  LDM.MDRS_ECUM.561, LDM.MDRS_ECUM.562, LDM.MDRS_ECUM.564,
/// LDM.MDRS_ECUM.565,  LDM.MDRS_ECUM.567, LDM.MDRS_ECUM.637, LDM.MDRS_ECUM.639
/// LDM.MDRS_ECUM.845,  LDM.MDRS_ECUM.860, LDM.MDRS_ECUM.863
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulHardFaultErrCnt                  = 0u
/// \input  Mpu.CESR                                = 0x10000000u
/// \input  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE
/// \input  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                      = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                      = 0x03u
/// \input  EcuM_MPUSelfTest_RetVal                 = 0x00u
///
/// - Expectations:
///
/// \output EcuM_sMpuErrState.boMPUErrorStatus      = TRUE
/// \output EcuM_sMpuErrState.ucMPUErrorFlags       = 0x02u
/// \output EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x05u
/// \output EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x03u
/// \output EcuM_MPUSelfTest_RetVal                 = 0x01u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPUSelfTest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMcuPrivStatus                    = 0u;
  Mpu.CESR                                = 0x10000000u;
  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE;
  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u;
  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u;
  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u;
  Mpu.EAR_EDR[3].EAR                      = 0x05u;
  Mpu.EAR_EDR[3].EDR                      = 0x03u;
  EcuM_MPUSelfTest_RetVal                 = 0x00u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPUSelfTest_RetVal = EcuM_MPUSelfTest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.boMPUErrorStatus,              TRUE, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ucMPUErrorFlags,              0x02u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUAddressError[3],         0x05u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUDetailedError[3],        0x03u, == );
  AL_UNITTEST_CHECK(EcuM_MPUSelfTest_RetVal,                        0x01u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MPUSelfTest_TestCase_2
///
/// \Test Case Description
///        - Test subject: MPU self test performing
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.559,  LDM.MDRS_ECUM.561, LDM.MDRS_ECUM.562, LDM.MDRS_ECUM.564,
/// LDM.MDRS_ECUM.565,  LDM.MDRS_ECUM.567, LDM.MDRS_ECUM.637, LDM.MDRS_ECUM.639
/// LDM.MDRS_ECUM.845,  LDM.MDRS_ECUM.860, LDM.MDRS_ECUM.863
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulHardFaultErrCnt                  = 0u
/// \input  Mpu.CESR                                = 0x10000000u
/// \input  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE
/// \input  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                      = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                      = 0x03u
/// \input  EcuM_MPUSelfTest_RetVal                 = 0x01u
/// \input  EcuM_ulHardFaultErrCnt                  = 1u
///
/// - Expectations:
///
/// \output EcuM_sMpuErrState.boMPUErrorStatus      = TRUE
/// \output EcuM_sMpuErrState.ucMPUErrorFlags       = 0x02u
/// \output EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x05u
/// \output EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x03u
/// \output EcuM_MPUSelfTest_RetVal                 = 0x01u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MPUSelfTest_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMcuPrivStatus                    = 1u;
  Mpu.CESR                                = 0x0u;
  EcuM_sMpuErrState.boMPUErrorStatus      = FALSE;
  EcuM_sMpuErrState.ucMPUErrorFlags       = 0x00u;
  EcuM_sMpuErrState.ulMPUAddressError[3]  = 0x00u;
  EcuM_sMpuErrState.ulMPUDetailedError[3] = 0x00u;
  Mpu.EAR_EDR[3].EAR                      = 0x05u;
  Mpu.EAR_EDR[3].EDR                      = 0x03u;
  EcuM_MPUSelfTest_RetVal                 = 0x01u;
  EcuM_ulHardFaultErrCnt                  = 1u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MPUSelfTest_RetVal = EcuM_MPUSelfTest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.boMPUErrorStatus,             FALSE, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ucMPUErrorFlags,              0x00u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUAddressError[3],         0x00u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUDetailedError[3],        0x00u, == );
  AL_UNITTEST_CHECK(EcuM_MPUSelfTest_RetVal,                        0x01u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_McuSelfTest_TestCase_1
///
/// \Test Case Description
///        - Test subject: MCU self test performing (Test failed due the first MPU self test failed and RAM error)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.595, LDM.MDRS_ECUM.597, LDM.MDRS_ECUM.848
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  MPU->CESR                               = 0u
/// \input  EcuM_ulMcuPrivStatus                    = 1u
/// \input  EcuM_boTriggerHardFault_MPUST1          = FALSE
/// \input  EcuM_boUpdateMPUReg_MPUST1              = TRUE
/// \input  EcuM_boTriggerHardFault_MPUST2          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST2              = TRUE;
/// \input  EcuM_boTriggerHardFault_MPUST3          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST3              = TRUE;
/// \input  EcuM_boTriggerHardFault_MPUST4          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST4              = TRUE;
/// \input  EcuM_boTriggerHardFault_MPUST5          = FALSE;
/// \input  EcuM_boTriggerHardFault_MPUST6          = FALSE;
/// \input  EcuM_boTriggerHardFault_MPUST7          = FALSE;
/// \input  EcuM_boTriggerHardFault_MPUST8          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST8              = TRUE;
/// \input  EcuM_boTriggerSEC_ISR_Test              = TRUE;
/// \input  EcuM_boTriggerDED_ISR_Test              = TRUE;
/// \input  EcuM_boTriggerFNCE_ISR_Test             = TRUE;
///
/// - Expectations:
///
/// \output EcuM_McuSelfTest_RetVal                 = 0x01u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_McuSelfTest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  MPU->CESR                      = 0u;
  EcuM_ulMcuPrivStatus           = 1u;
	EcuM_boTriggerHardFault_MPUST1 = FALSE;   // Test failed
	EcuM_boUpdateMPUReg_MPUST1     = TRUE;
	EcuM_boTriggerHardFault_MPUST2 = TRUE;
  EcuM_boUpdateMPUReg_MPUST2     = TRUE;
	EcuM_boTriggerHardFault_MPUST3 = TRUE;
  EcuM_boUpdateMPUReg_MPUST3     = TRUE;
	EcuM_boTriggerHardFault_MPUST4 = TRUE;
  EcuM_boUpdateMPUReg_MPUST4     = TRUE;
	EcuM_boTriggerHardFault_MPUST5 = FALSE;
	EcuM_boTriggerHardFault_MPUST6 = FALSE;
	EcuM_boTriggerHardFault_MPUST7 = FALSE;
	EcuM_boTriggerHardFault_MPUST8 = TRUE;
  EcuM_boUpdateMPUReg_MPUST8     = TRUE;
	EcuM_boTriggerSEC_ISR_Test	   = FALSE; // Test Failed
	EcuM_boTriggerDED_ISR_Test     = TRUE;
	EcuM_boTriggerFNCE_ISR_Test    = TRUE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_McuSelfTest_RetVal = EcuM_McuSelfTest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_McuSelfTest_RetVal,                        0x01u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_McuSelfTest_TestCase_2
///
/// \Test Case Description
///        - Test subject: MCU self test performing (Self test Passed)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.595, LDM.MDRS_ECUM.597
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  MPU->CESR                               = 0u
/// \input  EcuM_ulMcuPrivStatus                    = 1u
/// \input  EcuM_boTriggerHardFault_MPUST1          = TRUE
/// \input  EcuM_boUpdateMPUReg_MPUST1              = TRUE
/// \input  EcuM_boTriggerHardFault_MPUST2          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST2              = TRUE;
/// \input  EcuM_boTriggerHardFault_MPUST3          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST3              = TRUE;
/// \input  EcuM_boTriggerHardFault_MPUST4          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST4              = TRUE;
/// \input  EcuM_boTriggerHardFault_MPUST5          = FALSE;
/// \input  EcuM_boTriggerHardFault_MPUST6          = FALSE;
/// \input  EcuM_boTriggerHardFault_MPUST7          = FALSE;
/// \input  EcuM_boTriggerHardFault_MPUST8          = TRUE;
/// \input  EcuM_boUpdateMPUReg_MPUST8              = TRUE;
/// \input  EcuM_boTriggerSEC_ISR_Test              = TRUE;
/// \input  EcuM_boTriggerDED_ISR_Test              = TRUE;
/// \input  EcuM_boTriggerFNCE_ISR_Test             = TRUE;
///
/// - Expectations:
///
/// \output EcuM_MPUSelfTest_RetVal                 = 0x00u (pass)
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_McuSelfTest_TestCase_2(void)
{

	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  MPU->CESR                      = 0u;
  EcuM_ulMcuPrivStatus           = 1u;
	EcuM_boTriggerHardFault_MPUST1 = TRUE;
	EcuM_boUpdateMPUReg_MPUST1     = TRUE;
	EcuM_boTriggerHardFault_MPUST2 = TRUE;
  EcuM_boUpdateMPUReg_MPUST2     = TRUE;
	EcuM_boTriggerHardFault_MPUST3 = TRUE;
  EcuM_boUpdateMPUReg_MPUST3     = TRUE;
	EcuM_boTriggerHardFault_MPUST4 = TRUE;
  EcuM_boUpdateMPUReg_MPUST4     = TRUE;
	EcuM_boTriggerHardFault_MPUST5 = FALSE;
	EcuM_boTriggerHardFault_MPUST6 = FALSE;
	EcuM_boTriggerHardFault_MPUST7 = FALSE;
	EcuM_boTriggerHardFault_MPUST8 = TRUE;
  EcuM_boUpdateMPUReg_MPUST8     = TRUE;
	EcuM_boTriggerSEC_ISR_Test	   = TRUE;
	EcuM_boTriggerDED_ISR_Test     = TRUE;
	EcuM_boTriggerFNCE_ISR_Test    = TRUE;

  //Step 2) Assign Input values
  //--

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

  //Step 3) Call FUT
	EcuM_McuSelfTest_RetVal = EcuM_McuSelfTest();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_McuSelfTest_RetVal,            0x00u, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Post Run request evaluation
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_SleepBSI_Param1 = ECUM_LGM_TRUE
/// \input boBsiInstantSleepStatus          = TRUE
/// \input NM_CAN_b_SleepBSIframe           = LGM_TRUE
/// \input Rte_Read_SigPrep_SleepBSI_HitCount = 0u
///
/// - Expectations:
///
/// \output boBsiInstantSleepStatus             = TRUE
/// \output Rte_Read_SigPrep_SleepBSI_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_SleepBSI_Param1 = ECUM_LGM_TRUE;
  boBsiInstantSleepStatus          = TRUE;
  NM_CAN_b_SleepBSIframe           = LGM_TRUE;
  Rte_Read_SigPrep_SleepBSI_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Evaluate_RequestPostRun_Condtion();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(boBsiInstantSleepStatus,          TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_SleepBSI_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test Post Run request evaluation
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boBsiInstantSleepStatus          = TRUE
/// \input Rte_Read_SigPrep_SleepBSI_Param1 = ECUM_LGM_FALSE
/// \input NM_CAN_b_SleepBSIframe           = LGM_FALSE
/// \input Rte_Read_SigPrep_SleepBSI_HitCount = 0u
///
/// - Expectations:
///
/// \output boBsiInstantSleepStatus             = TRUE
/// \output Rte_Read_SigPrep_SleepBSI_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_SleepBSI_Param1 = ECUM_LGM_FALSE;
  boBsiInstantSleepStatus = TRUE;
  NM_CAN_b_SleepBSIframe  = LGM_FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Evaluate_RequestPostRun_Condtion();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(boBsiInstantSleepStatus, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test Post Run request evaluation
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boBsiInstantSleepStatus          = FALSE
/// \input Rte_Read_SigPrep_SleepBSI_Param1 = ECUM_LGM_TRUE
/// \input NM_CAN_b_SleepBSIframe           = LGM_TRUE
/// \input Rte_Read_SigPrep_SleepBSI_HitCount = 0u
///
/// - Expectations:
///
/// \output boBsiInstantSleepStatus             = FALSE
/// \output Rte_Read_SigPrep_SleepBSI_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Rte_Read_SigPrep_SleepBSI_Param1 = ECUM_LGM_TRUE;
  boBsiInstantSleepStatus = FALSE;
  NM_CAN_b_SleepBSIframe  = LGM_TRUE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Evaluate_RequestPostRun_Condtion();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(boBsiInstantSleepStatus, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_boTriggerNvmWrite      = TRUE
/// \input boShutDownStartStatus       = FALSE
///
/// - Expectations:
///
/// \output EcuM_boTriggerNvmWrite      = TRUE
/// \output boShutDownStartStatus       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boTriggerNvmWrite      = TRUE;
  boShutDownStartStatus       = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite, TRUE, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
/// \input boNvmWriteStatus               = TRUE
/// \input boShutDownStartStatus          = FALSE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulRunRequestCnt           = 1u
/// \input EcuM_eState                    = eEcuM_App_Run
///
/// - Expectations:
///
/// \outputNvm_WriteAll_HitCount       = 1u
/// \output EcuM_eState                = eEcuM_Up
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
  boShutDownStartStatus          = FALSE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal   = 5000000u;
  EcuM_ulRunRequestCnt           = 1u;
  EcuM_eState                    = eEcuM_App_Run;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(EcuM_eState,                         eEcuM_Up, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
/// \input boShutDownStartStatus          = FALSE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulRunRequestCnt           = 0u
/// \input EcuM_ulPostRunRequestCnt       = 1u
/// \input EcuM_eState                    = eEcuM_App_Run
///
/// - Expectations:
///
/// \outputNvm_WriteAll_HitCount       = 1u
/// \output EcuM_eState                = eEcuM_ShutDown
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
  boShutDownStartStatus          = FALSE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal   = 5000000u;
  EcuM_ulRunRequestCnt           = 0u;
  EcuM_ulPostRunRequestCnt       = 1u;
  EcuM_eState                    = eEcuM_App_Run;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(EcuM_eState,                   eEcuM_ShutDown, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
/// \input boShutDownStartStatus          = FALSE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulRunRequestCnt           = 0u
/// \input EcuM_ulPostRunRequestCnt       = 0u
/// \input EcuM_eState                    = eEcuM_App_Run
///
/// - Expectations:
///
/// \outputNvm_WriteAll_HitCount       = 1u
/// \output EcuM_eState                = eEcuM_App_Run
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
  boShutDownStartStatus          = FALSE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal   = 5000000u;
  EcuM_ulRunRequestCnt           = 0u;
  EcuM_ulPostRunRequestCnt       = 0u;
  EcuM_eState                    = eEcuM_App_Run;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(EcuM_eState,                    eEcuM_App_Run, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
/// \input boShutDownStartStatus          = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulShutDownPrep_us         = 0u
///
/// - Expectations:
///
/// \output Nvm_WriteAll_HitCount       = 1u
/// \output EcuM_ulShutDownPrep_us      = 5000000u
/// \output boShutDownStartStatus       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  NvM_GetErrorStatus_Param2      = NVM_REQ_OK;
  boShutDownStartStatus          = TRUE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal   = 5000000u;
  EcuM_ulShutDownPrep_us         = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(EcuM_ulShutDownPrep_us,              5000000u, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus,                  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boShutDownStartStatus          = FALSE
/// \input NvM_GetErrorStatus_Param2      = NVM_REQ_NOT_OK;
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulShutDownPrep_us         = 0u
/// \input ucNvMWrRetryCnt                = 0u
/// \input EcuM_boTriggerNvmWrite         = FALSE
///
/// - Expectations:
///
/// \output Nvm_WriteAll_HitCount       = 1u
/// \output boShutDownStartStatus       = TRUE
/// \output ucNvMWrRetryCnt             = 1u
/// \output EcuM_boTriggerNvmWrite      = TRUE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  boShutDownStartStatus = FALSE;
  NvM_GetErrorStatus_Param2 = NVM_REQ_NOT_OK;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 5000000u;
  EcuM_ulShutDownPrep_us = 0u;
  ucNvMWrRetryCnt = 0u;
  EcuM_boTriggerNvmWrite = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus, TRUE, == );
  AL_UNITTEST_CHECK(ucNvMWrRetryCnt, 1u, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boShutDownStartStatus          = FALSE
/// \input NvM_GetErrorStatus_Param2      = NVM_REQ_NOT_OK;
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulShutDownPrep_us         = 0u
/// \input ucNvMWrRetryCnt                = 1u
/// \input EcuM_boTriggerNvmWrite         = FALSE
///
/// - Expectations:
///
/// \output Nvm_WriteAll_HitCount       = 1u
/// \output boShutDownStartStatus       = TRUE
/// \output ucNvMWrRetryCnt             = 2u
/// \output EcuM_boTriggerNvmWrite      = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  boShutDownStartStatus = FALSE;
  NvM_GetErrorStatus_Param2 = NVM_REQ_NOT_OK;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 5000000u;
  EcuM_ulShutDownPrep_us = 0u;
  ucNvMWrRetryCnt = 1u;
  EcuM_boTriggerNvmWrite = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ShutDownPrep_HandleTransitions();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus, TRUE, == );
  AL_UNITTEST_CHECK(ucNvMWrRetryCnt, 2u, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateShutDownPrep_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boNvmWriteStatus               = TRUE
/// \input boShutDownStartStatus          = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulShutDownPrep_us         = 0u
///
/// - Expectations:
///
/// \output Nvm_WriteAll_HitCount       = 1u
/// \output EcuM_ulShutDownPrep_us      = 5000000u
/// \output boShutDownStartStatus       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateShutDownPrep_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  boNvmWriteStatus               = TRUE;
  boShutDownStartStatus          = TRUE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal   = 5000000u;
  EcuM_ulShutDownPrep_us         = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_OnStateShutDownPrep();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(EcuM_ulShutDownPrep_us,              5000000u, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus,                  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateUp_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if functions waits for timer and performs Mcu reset
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boNvmWriteStatus               = TRUE
/// \input boShutDownStartStatus          = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input boNvmWriteStatus               = TRUE
/// \input Mcu_PerformReset_HitCount      = 0u
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount = 2u
/// \output Mcu_PerformReset_HitCount      = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateUp_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset               = TRUE;
  boResetTimerStatus                = TRUE;
  LPTMR0_GetTimeElapsed_HitCount    = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = 5000000u;
  boNvmWriteStatus                  = TRUE;
  Mcu_PerformReset_HitCount         = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  // Start Timer
  EcuM_OnStateUp();
  // Evaluate Timer
  EcuM_OnStateUp();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            2u, == );
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount,                 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateUp_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if functions waits for timer and does nothing
///                        while Nvm Write status is false
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_boDiagReqReset               = TRUE
/// \input boResetTimerStatus                = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount    = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal      = 5000000u
/// \input EcuM_boTriggerNvmWrite            = TRUE
/// \input Nvm_WriteAll_HitCount             = 0u
/// \input NvM_GetErrorStatus_Param1         = 1u
/// \input NvM_GetErrorStatus_Param2         = 1u
/// \input NvM_GetErrorStatus_HitCount       = 0u
/// \input boNvmWriteStatus                  = FALSE
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount = 2u
/// \output boShutDownStartStatus          = FALSE
/// \output Nvm_WriteAll_HitCount          = 1u
/// \output EcuM_boTriggerNvmWrite         = FALSE
/// \output NvM_GetErrorStatus_Param1      = 0u
/// \output NvM_GetErrorStatus_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateUp_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset               = TRUE;
  boResetTimerStatus                = TRUE;
  LPTMR0_GetTimeElapsed_HitCount    = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = 5000000u;
  EcuM_boTriggerNvmWrite            = TRUE;
  Nvm_WriteAll_HitCount             = 0u;
  NvM_GetErrorStatus_Param1         = 1u;
  NvM_GetErrorStatus_Param2         = 1u;
  NvM_GetErrorStatus_HitCount       = 0u;
  boNvmWriteStatus                  = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  // Start Timer
  EcuM_OnStateUp();
  // Evaluate Timer
  EcuM_OnStateUp();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            2u, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus,                  FALSE, == );
  AL_UNITTEST_CHECK(Nvm_WriteAll_HitCount,                     1u, == );
  AL_UNITTEST_CHECK(EcuM_boTriggerNvmWrite,                 FALSE, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param1,                 0u, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_HitCount,               1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateUp_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if functions does nothing if 50ms has not passed
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_boDiagReqReset               = TRUE
/// \input boResetTimerStatus                = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount    = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal      = 0u
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateUp_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset               = TRUE;
  boResetTimerStatus                = TRUE;
  LPTMR0_GetTimeElapsed_HitCount    = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  // Start Timer
  EcuM_OnStateUp();
  // Evaluate Timer
  EcuM_OnStateUp();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_OnStateUp_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if functions Calls EcuM handle transition procedure
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_boDiagReqReset               = FALSE
/// \input boResetTimerStatus                = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount    = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal      = 0u
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_OnStateUp_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset               = FALSE;
  boResetTimerStatus                = TRUE;
  LPTMR0_GetTimeElapsed_HitCount    = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_OnStateUp();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MainFunction_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Finishes the startup
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.439, LDM.MDRS_ECUM.441,  LDM.MDRS_ECUM.1379, LDM.MDRS_ECUM.1380,
/// LDM.MDRS_ECUM.818, LDM.MDRS_ECUM.867,  LDM.MDRS_ECUM.818,  LDM.MDRS_ECUM.870, 
/// LDM.MDRS_ECUM.873, LDM.MDRS_ECUM.891
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  WdgM_SetLocalCheckPoint_HitCount = 0u
/// \input  WdgM_SetLocalCheckPoint_Param1   = 0u
/// \input  EcuM_ulRunRequestCnt             = 1u
/// \input  EcuM_eState                      = eEcuM_Startup
///
/// - Expectations:
///
/// \output WdgM_SetLocalCheckPoint_HitCount = 1u
/// \output WdgM_SetLocalCheckPoint_Param1   = 1u
/// \output EcuM_eState                      = eEcuM_Up
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MainFunction_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  WdgM_SetLocalCheckPoint_HitCount = 0u;
  WdgM_SetLocalCheckPoint_Param1   = 0u;
  EcuM_ulRunRequestCnt             = 1u;
  EcuM_eState                      = eEcuM_Startup;
  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt  = 1u;
  EcuM_ulECC_RAM_SEC_TestEnable    = 20212022u;
  EcuM_ulECC_RAM_DED_TestEnable    = 20212022u;
  EcuM_ulECC_FLASH_DED_TestEnable  = 20212022u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MainFunction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_SetLocalCheckPoint_HitCount,       1u, == );
  AL_UNITTEST_CHECK(WdgM_SetLocalCheckPoint_Param1,         1u, == );
  AL_UNITTEST_CHECK(EcuM_eState,                      eEcuM_Up, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_SEC_TestEnable,          0u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_DED_TestEnable,          0u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_FLASH_DED_TestEnable,        0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MainFunction_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if functions does nothing if 50ms has not passed
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.439, LDM.MDRS_ECUM.441,  LDM.MDRS_ECUM.1379, LDM.MDRS_ECUM.1380,
/// LDM.MDRS_ECUM.818, LDM.MDRS_ECUM.867,  LDM.MDRS_ECUM.818,  LDM.MDRS_ECUM.870, 
/// LDM.MDRS_ECUM.873, LDM.MDRS_ECUM.891
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_boDiagReqReset               = TRUE
/// \input boResetTimerStatus                = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount    = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal      = 0u
/// \input EcuM_eState                       = eEcuM_Up
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MainFunction_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset               = TRUE;
  boResetTimerStatus                = TRUE;
  LPTMR0_GetTimeElapsed_HitCount    = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = 0u;
  EcuM_eState                       = eEcuM_Up;
  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt   = 1u;
  EcuM_ulMcuPrivStatus              = 0u;
  EcuM_ulECC_DED_Reset_Inhib_TestEnable = 20212022u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MainFunction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MainFunction_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test Shut-Down Prepare handling transition routine
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.439, LDM.MDRS_ECUM.441,  LDM.MDRS_ECUM.1379, LDM.MDRS_ECUM.1380
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input boNvmWriteStatus               = TRUE
/// \input boShutDownStartStatus          = TRUE
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u
/// \input LPTMR0_GetTimeElapsed_RetVal   = 5000000u
/// \input EcuM_ulShutDownPrep_us         = 0u
/// \input EcuM_eState                    = eEcuM_ShutDownPrep
///
/// - Expectations:
///
/// \output Nvm_WriteAll_HitCount       = 1u
/// \output EcuM_ulShutDownPrep_us      = 5000000u
/// \output boShutDownStartStatus       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MainFunction_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  boNvmWriteStatus               = TRUE;
  boShutDownStartStatus          = TRUE;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal   = 5000000u;
  EcuM_ulShutDownPrep_us         = 0u;
  EcuM_eState                    = eEcuM_ShutDownPrep;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MainFunction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(EcuM_ulShutDownPrep_us,              5000000u, == );
  AL_UNITTEST_CHECK(boShutDownStartStatus,                  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MainFunction_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and handles PostRun Request
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.439, LDM.MDRS_ECUM.441,  LDM.MDRS_ECUM.1379, LDM.MDRS_ECUM.1380,
/// LDM.MDRS_ECUM.544, LDM.MDRS_ECUM.546
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState                                                          = eEcuM_ShutDown
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 1u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 1u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 1u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 1u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 1u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MainFunction_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eState                                                          = eEcuM_ShutDown;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MainFunction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_MainFunction_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function goes into default mode
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.439, LDM.MDRS_ECUM.441,  LDM.MDRS_ECUM.1379, LDM.MDRS_ECUM.1380
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState                      = eEcuM_WakeUp
///
/// - Expectations:
///
/// \output EcuM_eState                      = eEcuM_Undefined
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_MainFunction_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  
  //Step 1) Set pre-conditions
  EcuM_eState                      = eEcuM_WakeUp;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_MainFunction();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_eState, eEcuM_Undefined, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function initializes EcuM module
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.435,  LDM.MDRS_ECUM.437, LDM.MDRS_ECUM.1378, LDM.MDRS_ECUM.1381
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  INT_SYS_SetPriority_HitCount                                = 0u
/// \input  INT_SYS_SetPriority_Param1                                  = 0u
/// \input  INT_SYS_SetPriority_Param2                                  = 0u
/// \input  EcuM_InterruptCfg_List[6u].ucInterrupt                      = 23u
/// \input  EcuM_InterruptCfg_List[6u].ucPriority                       = 13u
/// \input  INT_SYS_EnableIRQ_HitCount                                  = 0u
/// \input  INT_SYS_EnableIRQ_Param1                                    = 0u
/// \input  EcuM_InterruptEnbl_List[6u]                                 = 23u
/// \input  EcuM_sEcuInternalResetReason.eMcuResetReason                = MCU_RESET_UNDEFINED
/// \input  Dem_SetEventStatus_HitCount                                 = 0u
/// \input  Dem_SetEventStatus_Param1                                   = 0u
/// \input  Dem_SetEventStatus_Param2                                   = 0u
/// \input  EcuM_sEcuInternalResetReason.eMcuResetReason                = 1u
/// \input  EcuM_ulMcuPrivStatus                                        = 1u
/// \input  Mpu.CESR                                                    = 0x0u
/// \input  EcuM_sMpuErrState.boMPUErrorStatus                          = FALSE
/// \input  EcuM_sMpuErrState.ucMPUErrorFlags                           = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUAddressError[3]                      = 0x00u
/// \input  EcuM_sMpuErrState.ulMPUDetailedError[3]                     = 0x00u
/// \input  Mpu.EAR_EDR[3].EAR                                          = 0x05u
/// \input  Mpu.EAR_EDR[3].EDR                                          = 0x03u
/// \input  EcuM_MPUSelfTest_RetVal                                     = 0x01u
/// \input  EcuM_ulHardFaultErrCnt                                      = 1u
/// \input  StartOS_HitCount                                            = 0u
/// \input  StartOS_Param1                                              = 10u
/// \input  Dem_ClearStartUpStatus_HitCount                             = 0u
///
/// - Expectations:
///
/// \output INT_SYS_SetPriority_HitCount                              = 10u
/// \output INT_SYS_SetPriority_Param1                                = 21u
/// \output INT_SYS_SetPriority_Param2                                = 4u
/// \output INT_SYS_EnableIRQ_HitCount                                = 10u
/// \output INT_SYS_EnableIRQ_Param1                                  = 21u
/// \output EcuM_sEcuInternalResetReason.eMcuResetReason              = MCU_RESET_UNDEFINED
/// \output Dem_SetEventStatus_HitCount                               = 2u
/// \output Dem_SetEventStatus_Param1                                 = CRC_APP_DEFECT
/// \output Dem_SetEventStatus_Param2                                 = 2u
/// \output EcuM_sMpuErrState.boMPUErrorStatus                        = FALSE
/// \output EcuM_sMpuErrState.ucMPUErrorFlags                         = 0x00u
/// \output EcuM_sMpuErrState.ulMPUAddressError[3]                    = 0x00u
/// \output EcuM_sMpuErrState.ulMPUDetailedError[3]                   = 0x00u
/// \output EcuM_MPUSelfTest_RetVal                                   = 0x01u
/// \output StartOS_HitCount                                          = 1u
/// \output StartOS_Param1                                            = 0u
/// \output Dem_ClearStartUpStatus_HitCount                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  INT_SYS_SetPriority_HitCount                                = 0u;
  INT_SYS_SetPriority_Param1                                  = 0u;
  INT_SYS_SetPriority_Param2                                  = 0u;
  EcuM_InterruptCfg_List[6u].ucInterrupt                      = 23u;
  EcuM_InterruptCfg_List[6u].ucPriority                       = 13u;
  INT_SYS_EnableIRQ_HitCount                                  = 0u;
  INT_SYS_EnableIRQ_Param1                                    = 0u;
  EcuM_InterruptEnbl_List[6u]                                 = 23u;
  EcuM_sEcuInternalResetReason.eMcuResetReason                = MCU_RESET_UNDEFINED;
  Dem_SetEventStatus_HitCount                                 = 0u;
  Dem_SetEventStatus_Param1                                   = 0u;
  Dem_SetEventStatus_Param2                                   = 0u;
  EcuM_sEcuInternalResetReason.eMcuResetReason                = 1u;
  EcuM_ulMcuPrivStatus                                        = 1u;
  Mpu.CESR                                                    = 0x0u;
  EcuM_sMpuErrState.boMPUErrorStatus                          = FALSE;
  EcuM_sMpuErrState.ucMPUErrorFlags                           = 0x00u;
  EcuM_sMpuErrState.ulMPUAddressError[3]                      = 0x00u;
  EcuM_sMpuErrState.ulMPUDetailedError[3]                     = 0x00u;
  Mpu.EAR_EDR[3].EAR                                          = 0x05u;
  Mpu.EAR_EDR[3].EDR                                          = 0x03u;
  EcuM_MPUSelfTest_RetVal                                     = 0x01u;
  EcuM_ulHardFaultErrCnt                                      = 1u;
  StartOS_HitCount                                            = 0u;
  StartOS_Param1                                              = 10u;
  Dem_ClearStartUpStatus_HitCount                             = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(INT_SYS_SetPriority_HitCount,                                     11u, == );
  AL_UNITTEST_CHECK(INT_SYS_SetPriority_Param1,                                       58u, == );
  AL_UNITTEST_CHECK(INT_SYS_SetPriority_Param2,                                        4u, == );
  AL_UNITTEST_CHECK(INT_SYS_EnableIRQ_HitCount,                                       11u, == );
  AL_UNITTEST_CHECK(INT_SYS_EnableIRQ_Param1,                                         58u, == );
  AL_UNITTEST_CHECK(EcuM_sEcuInternalResetReason.eMcuResetReason,      MCU_POWER_ON_RESET, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                                       2u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                             CRC_APP_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,                                         2u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.boMPUErrorStatus,                             FALSE, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ucMPUErrorFlags,                              0x00u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUAddressError[3],                         0x00u, == );
  AL_UNITTEST_CHECK(EcuM_sMpuErrState.ulMPUDetailedError[3],                        0x00u, == );
  AL_UNITTEST_CHECK(EcuM_MPUSelfTest_RetVal,                                        0x01u, == );
  AL_UNITTEST_CHECK(StartOS_HitCount,                                                  1u, == );
  AL_UNITTEST_CHECK(StartOS_Param1,                                                    0u, == );
  AL_UNITTEST_CHECK(Dem_ClearStartUpStatus_HitCount,                                   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_rpEcuM_Cycle0_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Evaluates release port run condition
///                        and handles PostRun Request
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.481,  LDM.MDRS_ECUM.1003, LDM.MDRS_ECUM.1009, LDM.MDRS_ECUM.1013
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_eState                                                          = eEcuM_ShutDown
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off
/// \input  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u
/// \input  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u
/// \input  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off
/// \input  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u
/// \input  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State
/// \input  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u
/// \input  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u
/// \input  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = TRUE
/// \input  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u
/// \input  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_StdLgtFcts_Req_HitCount                                = 1u
/// \output Rte_Read_SysMon_StdLgtTi_Req_HitCount                                  = 0u
/// \output Rte_Read_SysMon_LowBeamCmd_Req_HitCount                                = 1u
/// \output SysMonRx_ASIL_GetSpeedState_HitCount                                   = 1u
/// \output SysMonRx_ASIL_GetLowBeamState_HitCount                                 = 1u
/// \output SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount   = 1u
/// \output SysMonRx_ComM_EnableCallbacks_HitCount                                 = 0u
/// \output SysMonTx_ComM_ActivateTxBufer_HitCount                                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount                                = 0u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount                                = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_rpEcuM_Cycle0_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_eState                                                          = eEcuM_ShutDown;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount                              = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request                   = ReqLighted_Off;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount                                = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eWarning_Mode                    = eWarningMode_PilotedWarningMode;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount                              = 0u;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1                                = ReqLighted_Off;
  SysMonRx_ASIL_GetSpeedState_HitCount                                 = 0u;
  SysMonRx_ASIL_GetSpeedState_RetVal                                   = SysMon_Speed_Invalid_State;
  SysMonRx_ASIL_GetLowBeamState_HitCount                               = 0u;
  SysMonRx_ASIL_GetLowBeamState_RetVal                                 = SysMon_LowBeam_Invalid_State;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount = 0u;
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal   = FALSE;
  SysMonRx_ComM_EnableCallbacks_HitCount                               = 0u;
  SysMonTx_ComM_ActivateTxBufer_HitCount                               = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount                              = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount                              = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  rpEcuM_Cycle0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,                                     0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LowBeamCmd_Req_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetSpeedState_HitCount,                                      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_GetLowBeamState_HitCount,                                    1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount,      1u, == );
  AL_UNITTEST_CHECK(SysMonRx_ComM_EnableCallbacks_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_ActivateTxBufer_HitCount,                                    0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,                                   0u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if Single Bit Coretable error injection in RAM_L, RAM_U
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.580, LDM.MDRS_ECUM.582
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMcuPrivStatus = 0u
/// \input  Eim.EICHDn[0].WORD1  = 0u
/// \input  Eim.EICHEN           = 0u
/// \input  Eim.EIMCR            = 0u
/// \input  Eim.EICHDn[1].WORD1  = 0u
///
/// - Expectations:
///
/// \output Eim.EICHDn[0].WORD1  = 1u
/// \output Eim.EICHEN           = 0u
/// \output Eim.EIMCR            = 0u
/// \output Eim.EICHDn[1].WORD1  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMcuPrivStatus = 0u;
  Eim.EICHDn[0].WORD1  = 0u;
  Eim.EICHEN           = 0u;
  Eim.EIMCR            = 0u;
  Eim.EICHDn[1].WORD1  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Inject_RAM_SEC_ECCError();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EICHDn[0].WORD1,   1u, == );
  AL_UNITTEST_CHECK(Eim.EICHEN,            0u, == );
  AL_UNITTEST_CHECK(Eim.EIMCR,             0u, == );
  AL_UNITTEST_CHECK(Eim.EICHDn[1].WORD1,   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if Single Bit Coretable error injection in RAM_L, RAM_U
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.580, LDM.MDRS_ECUM.582
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMcuPrivStatus = 1u
/// \input  Eim.EICHDn[0].WORD1  = 0u
/// \input  Eim.EICHEN           = 0u
/// \input  Eim.EIMCR            = 0u
/// \input  Eim.EICHDn[1].WORD1  = 0u
///
/// - Expectations:
///
/// \output Eim.EICHDn[0].WORD1  = 1u
/// \output Eim.EICHEN           = 0u
/// \output Eim.EIMCR            = 0u
/// \output Eim.EICHDn[1].WORD1  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMcuPrivStatus = 1u;
  Eim.EICHDn[0].WORD1  = 0u;
  Eim.EICHEN           = 0u;
  Eim.EIMCR            = 0u;
  Eim.EICHDn[1].WORD1  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Inject_RAM_SEC_ECCError();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EICHDn[0].WORD1,   1u, == );
  AL_UNITTEST_CHECK(Eim.EICHEN,            0u, == );
  AL_UNITTEST_CHECK(Eim.EIMCR,             0u, == );
  AL_UNITTEST_CHECK(Eim.EICHDn[1].WORD1,   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Double Bit Uncorectable error injection in RAM_L, RAM_U
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.583, LDM.MDRS_ECUM.585
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMcuPrivStatus = 0u
/// \input  Eim.EICHDn[0].WORD1  = 0u
/// \input  Eim.EICHEN           = 0u
/// \input  Eim.EIMCR            = 0u
/// \input  Eim.EICHDn[1].WORD1  = 0u
///
/// - Expectations:
///
/// \output Eim.EICHDn[0].WORD1  = 1u
/// \output Eim.EICHEN           = 0u
/// \output Eim.EIMCR            = 0u
/// \output Eim.EICHDn[1].WORD1  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMcuPrivStatus = 0u;
  Eim.EICHDn[0].WORD1  = 0u;
  Eim.EICHEN           = 0u;
  Eim.EIMCR            = 0u;
  Eim.EICHDn[1].WORD1  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Inject_RAM_DED_ECCError();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EICHDn[0].WORD1,   3u, == );
  AL_UNITTEST_CHECK(Eim.EICHEN,            0u, == );
  AL_UNITTEST_CHECK(Eim.EIMCR,             0u, == );
  AL_UNITTEST_CHECK(Eim.EICHDn[1].WORD1,   3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test Double Bit Uncorectable error injection in RAM_L, RAM_U
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.583, LDM.MDRS_ECUM.585
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_ulMcuPrivStatus = 1u
/// \input  Eim.EICHDn[0].WORD1  = 0u
/// \input  Eim.EICHEN           = 0u
/// \input  Eim.EIMCR            = 0u
/// \input  Eim.EICHDn[1].WORD1  = 0u
///
/// - Expectations:
///
/// \output Eim.EICHDn[0].WORD1  = 1u
/// \output Eim.EICHEN           = 0u
/// \output Eim.EIMCR            = 0u
/// \output Eim.EICHDn[1].WORD1  = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_ulMcuPrivStatus = 1u;
  Eim.EICHDn[0].WORD1  = 0u;
  Eim.EICHEN           = 0u;
  Eim.EIMCR            = 0u;
  Eim.EICHDn[1].WORD1  = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Inject_RAM_DED_ECCError();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EICHDn[0].WORD1,   3u, == );
  AL_UNITTEST_CHECK(Eim.EICHEN,            0u, == );
  AL_UNITTEST_CHECK(Eim.EIMCR,             0u, == );
  AL_UNITTEST_CHECK(Eim.EICHDn[1].WORD1,   3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Inject_FLASH_DED_ECCError_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Double Bit Uncorectable error injection in RAM_L, RAM_U
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.586, LDM.MDRS_ECUM.589, LDM.MDRS_ECUM.591, LDM.MDRS_ECUM.1317
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  FTFC_sReg.FERCNFG = 1u
///
/// - Expectations:
///
/// \output FTFC_sReg.FERCNFG = 33u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Inject_FLASH_DED_ECCError_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  FTFC_sReg.FERCNFG = 1u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Inject_FLASH_DED_ECCError();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FTFC_sReg.FERCNFG,   33u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Ram Single Bit Corectable Error Reporter Irq
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.478,  LDM.MDRS_ECUM.480, LDM.MDRS_ECUM.876, LDM.MDRS_ECUM.879
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Eim.EIMCR                       = 0x01
/// \input  Erm.SR0                         = 0x80000000u
/// \input  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u
/// \input  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u
///
/// - Expectations:
///
/// \output Eim.EIMCR                       = 0x0
/// \output Erm.SR0                         = 0x80000000u
/// \output EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 1u;
/// \output EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;
///
//-----------------------------------------------------------------------------
void Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Eim.EIMCR                       = 0x01;
  Erm.SR0                         = 0x80000000u;
  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  ERM_single_fault_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EIMCR,                         0u, == );
  AL_UNITTEST_CHECK(Erm.SR0,                  0x80000000u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt,   1u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt,   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test Ram Single Bit Corectable Error Reporter Irq
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.478,  LDM.MDRS_ECUM.480, LDM.MDRS_ECUM.876, LDM.MDRS_ECUM.879
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Eim.EIMCR                       = 0x00
/// \input  Erm.SR0                         = 0x08000000u
/// \input  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u
/// \input  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u
///
/// - Expectations:
///
/// \output Eim.EIMCR                       = 0x0
/// \output Erm.SR0                         = 0x08000000u
/// \output EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
/// \output EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 1u;
///
//-----------------------------------------------------------------------------
void Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Eim.EIMCR                       = 0x00;
  Erm.SR0                         = 0x08000000u;
  EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  ERM_single_fault_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EIMCR,                         0u, == );
  AL_UNITTEST_CHECK(Erm.SR0,                  0x08000000u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_L_SEC_Irq_ErrCnt,   0u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_U_SEC_Irq_ErrCnt,   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Ram Multi Bit Uncorectable Error Reporter Irq
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.475,  LDM.MDRS_ECUM.477, LDM.MDRS_ECUM.882, LDM.MDRS_ECUM.885,
/// LDM.MDRS_ECUM.888
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Eim.EIMCR                       = 0x01
/// \input  Erm.SR0                         = 0x40000000u
/// \input  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u
/// \input  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u
///
/// - Expectations:
///
/// \output Eim.EIMCR                       = 0x0
/// \output Erm.SR0                         = 0x40000000u
/// \output EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 1u
/// \output EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Eim.EIMCR                       = 0x01;
  Erm.SR0                         = 0x40000000u;
  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  ERM_double_fault_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EIMCR,                         0u, == );
  AL_UNITTEST_CHECK(Erm.SR0,                  0x40000000u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_L_DED_Irq_ErrCnt,   1u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_U_DED_Irq_ErrCnt,   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test Ram Single Bit Corectable Error Reporter Irq
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.475,  LDM.MDRS_ECUM.477, LDM.MDRS_ECUM.882, LDM.MDRS_ECUM.885,
/// LDM.MDRS_ECUM.888
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Eim.EIMCR                       = 0x00
/// \input  Erm.SR0                         = 0x04000000u
/// \input  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u
/// \input  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u
///
/// - Expectations:
///
/// \output Eim.EIMCR                       = 0x0
/// \output Erm.SR0                         = 0x04000000u
/// \output EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
/// \output EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 1u;
///
//-----------------------------------------------------------------------------
void Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Eim.EIMCR                       = 0x00;
  Erm.SR0                         = 0x04000000u;
  EcuM_ulECC_RAM_L_DED_Irq_ErrCnt = 0u;
  EcuM_ulECC_RAM_U_DED_Irq_ErrCnt = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  ERM_double_fault_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Eim.EIMCR,                         0u, == );
  AL_UNITTEST_CHECK(Erm.SR0,                  0x04000000u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_L_DED_Irq_ErrCnt,   0u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_RAM_U_DED_Irq_ErrCnt,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test Flash Double Bit Error Irq Handler
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.472,  LDM.MDRS_ECUM.474
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  FTFC_sReg.FERCNFG                    = 0x20u
/// \input  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u
///
/// - Expectations:
///
/// \output FTFC_sReg.FERCNFG                    = 0x0u
/// \output EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  FTFC_sReg.FERCNFG                    = 0x20u;
  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  FTFC_Fault_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FTFC_sReg.FERCNFG,                      0u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_Flash_NCE_Irq_ErrCnt,   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test Flash Double Bit Error Irq Handler
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.472,  LDM.MDRS_ECUM.474
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  FTFC_sReg.FERCNFG                    = 0x20u
/// \input  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u
///
/// - Expectations:
///
/// \output FTFC_sReg.FERCNFG                    = 0x0u
/// \output EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  FTFC_sReg.FERCNFG                    = 0x0u;
  EcuM_ulECC_Flash_NCE_Irq_ErrCnt = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  FTFC_Fault_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FTFC_sReg.FERCNFG,                      0u, == );
  AL_UNITTEST_CHECK(EcuM_ulECC_Flash_NCE_Irq_ErrCnt,   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_InvalidInterrupt_Reset_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if Mcu Perform Reset
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcu_PerformReset_HitCount = 0u
///
/// - Expectations:
///
/// \output Mcu_PerformReset_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_InvalidInterrupt_Reset_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Mcu_PerformReset_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_InvalidInterrupt_Reset();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount,   1u, == );
}


#if 0
//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_Wake_Up_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test NM callback for wake up network
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u
///
/// - Expectations:
///
/// \output SysMonRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount   = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_Wake_Up_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u;
  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Wake_Up_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(SysMonRx_ComM_DisableCallbacks_HitCount,    1u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_DeactivateTxBuffer_HitCount,  1u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,   1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_Sleep_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test NM callback for sleep  network
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u
///
/// - Expectations:
///
/// \output SysMonRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount   = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_Sleep_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u;
  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Sleep_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(SysMonRx_ComM_DisableCallbacks_HitCount,    1u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_DeactivateTxBuffer_HitCount,  1u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,   1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_Com_Off_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test NM callback for sleep  network
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u
///
/// - Expectations:
///
/// \output SysMonRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount   = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_Com_Off_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  SysMonRx_ComM_DisableCallbacks_HitCount    = 0u;
  SysMonTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  SigPrepRx_ComM_DisableCallbacks_HitCount   = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  Com_Off_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(SysMonRx_ComM_DisableCallbacks_HitCount,    1u, == );
  AL_UNITTEST_CHECK(SysMonTx_ComM_DeactivateTxBuffer_HitCount,  1u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,   1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount, 1u, == );
}
#endif

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ECCProtEnable_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test ECC protection enabling procedure over RAM and Flash memory
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.577,  LDM.MDRS_ECUM.579
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcm.LMDR[0] = 0x00010000u
/// \input  Mcm.LMDR2   = 0x00010000u
///
/// - Expectations:
///
/// \output Mcm.LMDR[0] = 0x10000u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ECCProtEnable_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Mcm.LMDR[0] = 0x00010000u;
  Mcm.LMDR2   = 0x00010000u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ECCProtEnable();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcm.LMDR[0],    0x10000u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ECCProtEnable_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test ECC protection enabling procedure over RAM and Flash memory
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.577,  LDM.MDRS_ECUM.579
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcm.LMDR[0] = 0x00010000u
/// \input  Mcm.LMDR2   = 0x000000A0u
///
/// - Expectations:
///
/// \output Mcm.LMDR[0] = 0x10000u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ECCProtEnable_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Mcm.LMDR[0] = 0x00010000u;
  Mcm.LMDR2   = 0x000000A0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ECCProtEnable();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcm.LMDR[0],    0x10000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_CheckAppCrc_TestCase_1
///
/// \Test Case Description
///        - Test subject: Application Crc checking function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ucCounter = 0u
/// \input  EcuM_boFlashCrcFailure = TRUE
/// \input  EcuM_ulShaDataCrcAppLocation = 50u
/// \input  Mcu_PerformReset_HitCount = 0u

///
/// - Expectations:
///
/// \output ucCounter = 1u
/// \output EcuM_boFlashCrcFailure = TRUE
/// \output Mcu_PerformReset_HitCount = 0u
/// \output EcuM_ulShaDataCrcAppLocation = 50u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_CheckAppCrc_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  ucCounter = 0u;
  EcuM_boFlashCrcFailure = TRUE;
  EcuM_ulShaDataCrcAppLocation = 50;
  Mcu_PerformReset_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_CheckAppCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter, 1u, == );
  AL_UNITTEST_CHECK(EcuM_boFlashCrcFailure, TRUE, == );
  AL_UNITTEST_CHECK(EcuM_ulShaDataCrcAppLocation, 50u, == );
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_CheckAppCrc_TestCase_2
///
/// \Test Case Description
///        - Test subject: Application Crc checking function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ucCounter = 50u
/// \input  EcuM_boFlashCrcFailure = TRUE
/// \input  EcuM_ulShaDataCrcAppLocation = 50u
/// \input  Mcu_PerformReset_HitCount = 0u

///
/// - Expectations:
///
/// \output ucCounter = 1u
/// \output EcuM_boFlashCrcFailure = TRUE
/// \output Mcu_PerformReset_HitCount = 1u
/// \output EcuM_ulShaDataCrcAppLocation = 0x5A01u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_CheckAppCrc_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  ucCounter = 50u;
  EcuM_boFlashCrcFailure = TRUE;
  EcuM_ulShaDataCrcAppLocation = 50;
  Mcu_PerformReset_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_CheckAppCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter, 1u, == );
  AL_UNITTEST_CHECK(EcuM_boFlashCrcFailure, TRUE, == );
  AL_UNITTEST_CHECK(EcuM_ulShaDataCrcAppLocation, 0x5A01u, == );
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_CheckAppCrc_TestCase3
///
/// \Test Case Description
///        - Test subject: Application Crc checking function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ucCounter = 50u
/// \input  EcuM_boFlashCrcFailure = FALSE
/// \input  EcuM_ulShaDataCrcAppLocation = 50u
/// \input  Mcu_PerformReset_HitCount = 0u
///
/// - Expectations:
///
/// \output ucCounter = 1u
/// \output EcuM_boFlashCrcFailure = FALSE
/// \output Mcu_PerformReset_HitCount = 0u
/// \output EcuM_ulShaDataCrcAppLocation = 50u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_CheckAppCrc_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  ucCounter = 50u;
  EcuM_boFlashCrcFailure = FALSE;
  EcuM_ulShaDataCrcAppLocation = 50;
  Mcu_PerformReset_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_CheckAppCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter, 1u, == );
  AL_UNITTEST_CHECK(EcuM_boFlashCrcFailure, FALSE, == );
  AL_UNITTEST_CHECK(EcuM_ulShaDataCrcAppLocation, 50U, == );
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Get_Mpu_Test_Hook_Address_1
///
/// \Test Case Description
///        - Test subject: MPU DTC Hook local MPU address getter test
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  EcuM_Get_Mpu_Test_Hook_Address_RetVal = NULL_PTR
///
/// - Expectations:
///
/// \output EcuM_Get_Mpu_Test_Hook_Address_RetVal = EcuM_ulMPU_Fault_Hook_Addr
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Get_Mpu_Test_Hook_Address_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  uint32* EcuM_Get_Mpu_Test_Hook_Address_RetVal = NULL_PTR;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Get_Mpu_Test_Hook_Address_RetVal = (uint32*)EcuM_Get_Mpu_Test_Hook_Address();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_Get_Mpu_Test_Hook_Address_RetVal, &EcuM_ulMPU_Fault_Hook_Addr, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_1
///
/// \Test Case Description
///        - Test subject: MPU Error Report function
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1267,  LDM.MDRS_ECUM.1271, LDM.MDRS_ECUM.1312
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ucCounter1 = 0u
/// \input  ulBusFaultCnt_Last = 0u
/// \input  Os_Get_BusFaultCnt_RetVal = 0u
/// \input  Rte_Write_MPU_ErrorCounter_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy
/// \input  Rte_Write_MPU_ErrorCounter_RetVal = 0u
/// \input  Dem_SetEventStatus_HitCount = 0u
/// \input  Dem_SetEventStatus_Param1 = 0u
/// \input  Dem_SetEventStatus_Param2 = 0u
///
/// - Expectations:
///
/// \output ucCounter = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  uint32 Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u;

  ucCounter1 = 0u;
  ulBusFaultCnt_Last = 0u;
  Os_Get_BusFaultCnt_RetVal = 0u;
  Rte_Write_MPU_ErrorCounter_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy;
  Rte_Write_MPU_ErrorCounter_RetVal = 0u;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Check_MPU_Errors();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter1, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_2
///
/// \Test Case Description
///        - Test subject: MPU Error Report function
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1272,  LDM.MDRS_ECUM.1276, LDM.MDRS_ECUM.1312
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u
/// \input  ucCounter1 = 100u
/// \input  ulBusFaultCnt_Last = 30u
/// \input  Os_Get_BusFaultCnt_RetVal = 30u
/// \input  Os_Get_BusFaultCnt_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy
/// \input  Rte_Write_MPU_ErrorCounter_RetVal = 0u
/// \input  Dem_SetEventStatus_HitCount = 0u
/// \input  Dem_SetEventStatus_Param1 = 0u
/// \input  Dem_SetEventStatus_Param2 = 0u
///
/// - Expectations:
///
/// \output ucCounter = 1u
/// \output  ulBusFaultCnt_Last = 30u
/// \output  Os_Get_BusFaultCnt_HitCount = 1u
/// \output  Rte_Write_MPU_ErrorCounter_HitCount = 1u
/// \output  Rte_Write_MPU_ErrorCounter_Param_Dummy = 30u
/// \output  Dem_SetEventStatus_HitCount = 0u
/// \output  Dem_SetEventStatus_Param1 = 0u
/// \output  Dem_SetEventStatus_Param2 = 0u
/// \output  Rte_Write_MPU_ErrorCounter_Param_Dummy = 30u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  uint32 Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u;

  ucCounter1 = 100u;
  ulBusFaultCnt_Last = 30u;
  Os_Get_BusFaultCnt_RetVal = 30u;
  Os_Get_BusFaultCnt_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy;
  Rte_Write_MPU_ErrorCounter_RetVal = 0u;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Check_MPU_Errors();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter1, 1u, == );
  AL_UNITTEST_CHECK(ulBusFaultCnt_Last, 30u, == );
  AL_UNITTEST_CHECK(Os_Get_BusFaultCnt_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_MPU_ErrorCounter_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_MPU_ErrorCounter_Param_Dummy, 30u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, 0u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_3
///
/// \Test Case Description
///        - Test subject: MPU Error Report function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u
/// \input  ucCounter1 = 100u
/// \input  ulBusFaultCnt_Last = 30u
/// \input  Os_Get_BusFaultCnt_RetVal = 31u
/// \input  Os_Get_BusFaultCnt_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy
/// \input  Rte_Write_MPU_ErrorCounter_RetVal = 0u
/// \input  Dem_SetEventStatus_HitCount = 0u
/// \input  Dem_SetEventStatus_Param1 = 0u
/// \input  Dem_SetEventStatus_Param2 = 0u
///
/// - Expectations:
///
/// \output ucCounter = 1u
/// \output  ulBusFaultCnt_Last = 31u
/// \output  Os_Get_BusFaultCnt_HitCount = 1u
/// \output  Rte_Write_MPU_ErrorCounter_HitCount = 1u
/// \output  Rte_Write_MPU_ErrorCounter_Param_Dummy = 30u
/// \output  Dem_SetEventStatus_HitCount = 1u
/// \output  Dem_SetEventStatus_Param1 = 69u
/// \output  Dem_SetEventStatus_Param2 = 3u
/// \output  Rte_Write_MPU_ErrorCounter_Param_Dummy = 31u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
   // Inputs
   //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  uint32 Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u;

  //Step 2) Assign Input values
  //--

  ucCounter1 = 100u;
  ulBusFaultCnt_Last = 30u;
  Os_Get_BusFaultCnt_RetVal = 31u;
  Os_Get_BusFaultCnt_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy;
  Rte_Write_MPU_ErrorCounter_RetVal = 0u;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Check_MPU_Errors();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter1, 1u, == );
  AL_UNITTEST_CHECK(ulBusFaultCnt_Last, 31u, == );
  AL_UNITTEST_CHECK(Os_Get_BusFaultCnt_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_MPU_ErrorCounter_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_MPU_ErrorCounter_Param_Dummy, 31u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, MPU_Error, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_4
///
/// \Test Case Description
///        - Test subject: MPU Error Report function
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u
/// \input  ucCounter1 = 100u
/// \input  ulBusFaultCnt_Last = 30u
/// \input  Os_Get_BusFaultCnt_RetVal = 65536u
/// \input  Os_Get_BusFaultCnt_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_HitCount = 0u
/// \input  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy
/// \input  Rte_Write_MPU_ErrorCounter_RetVal = 0u
/// \input  Dem_SetEventStatus_HitCount = 0u
/// \input  Dem_SetEventStatus_Param1 = 0u
/// \input  Dem_SetEventStatus_Param2 = 0u
///
/// - Expectations:
///
/// \output ucCounter = 1u
/// \output  ulBusFaultCnt_Last = 65536u
/// \output  Os_Get_BusFaultCnt_HitCount = 1u
/// \output  Rte_Write_MPU_ErrorCounter_HitCount = 1u
/// \output  Rte_Write_MPU_ErrorCounter_Param_Dummy = 30u
/// \output  Dem_SetEventStatus_HitCount = 1u
/// \output  Dem_SetEventStatus_Param1 = 69u
/// \output  Dem_SetEventStatus_Param2 = 3u
/// \output  Rte_Write_MPU_ErrorCounter_Param_Dummy = 65536u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
   // Inputs
   //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  uint32 Rte_Write_MPU_ErrorCounter_Param_Dummy = 100u;

  ucCounter1 = 100u;
  ulBusFaultCnt_Last = 30u;
  Os_Get_BusFaultCnt_RetVal = 65536u;
  Os_Get_BusFaultCnt_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_HitCount = 0u;
  Rte_Write_MPU_ErrorCounter_Param1 = &Rte_Write_MPU_ErrorCounter_Param_Dummy;
  Rte_Write_MPU_ErrorCounter_RetVal = 0u;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = 0u;
  Dem_SetEventStatus_Param2 = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_Check_MPU_Errors();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucCounter1, 1u, == );
  AL_UNITTEST_CHECK(ulBusFaultCnt_Last, 65536u, == );
  AL_UNITTEST_CHECK(Os_Get_BusFaultCnt_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_MPU_ErrorCounter_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_MPU_ErrorCounter_Param_Dummy, 65536u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, MPU_Error, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_McuInit_TestCase_1
///
/// \Test Case Description
///        - Test subject: MCU init function - clock check pass, no reset requested
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1198,  LDM.MDRS_ECUM.1202
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcu_InitClock_HitCount = 0u
/// \input  Mcu_InitClock_Param1 = &ucClockType_Out
/// \input  ucClockType_Out = 0xABu
/// \input  Mcu_ClockData = 0xBAu
/// \input  Mcu_InitClock_RetVal = E_OK
/// \input  Scg.SOSCCSR = 0u
/// \input  Scg.SIRCCSR = 0u
/// \input  Scg.SPLLCSR = 0u
/// \input  Mcu_PerformReset_HitCount = 0u
/// \input  cuM_unShaData_Clk_Cfg_Fail = 0u
///
/// - Expectations:
///
/// \output ucClockType_Out = 0xBAu
/// \output Mcu_InitClock_HitCount = 1u
/// \output EcuM_unShaData_Clk_Cfg_Fail = 0u
/// \output Mcu_PerformReset_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_McuInit_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
   // Inputs
   //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Mcu_ClockType ucClockType_Out;

  Mcu_InitClock_HitCount = 0u;
  Mcu_InitClock_Param1 = &ucClockType_Out;
  ucClockType_Out = 0xABu;
  Mcu_ClockData   = 0xBAu;
  Mcu_InitClock_RetVal = E_OK;
  Scg.SOSCCSR = 0u;
  Scg.SIRCCSR = 0u;
  Scg.SPLLCSR = 0u;
  Mcu_PerformReset_HitCount = 0u;
  EcuM_unShaData_Clk_Cfg_Fail = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_McuInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucClockType_Out, 0xBAu, == );
  AL_UNITTEST_CHECK(Mcu_InitClock_HitCount, 1u, == );
  AL_UNITTEST_CHECK(EcuM_unShaData_Clk_Cfg_Fail, 0u, == );
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_McuInit_TestCase_2
///
/// \Test Case Description
///        - Test subject: MCU init function - clock check fail, reset requested, shadata memory updated
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1198,  LDM.MDRS_ECUM.1202
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mcu_InitClock_HitCount = 0u
/// \input  Mcu_InitClock_Param1 = &ucClockType_Out
/// \input  ucClockType_Out = 0xABu
/// \input  Mcu_ClockData = 0xBAu
/// \input  Mcu_InitClock_RetVal = E_OK
/// \input  Scg.SOSCCSR = 0x04000000u
/// \input  Scg.SIRCCSR = 0x04000000u
/// \input  Scg.SPLLCSR = 0x04000000u
/// \input  Mcu_PerformReset_HitCount = 0u
/// \input  cuM_unShaData_Clk_Cfg_Fail = 0u
///
/// - Expectations:
///
/// \output ucClockType_Out = 0xBAu
/// \output Mcu_InitClock_HitCount = 1u
/// \output EcuM_unShaData_Clk_Cfg_Fail = 0x5A01u
/// \output Mcu_PerformReset_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_McuInit_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1) Set pre-conditions
  Mcu_ClockType ucClockType_Out;

  Mcu_InitClock_HitCount = 0u;
  Mcu_InitClock_Param1 = &ucClockType_Out;
  ucClockType_Out = 0xABu;
  Mcu_ClockData = 0xBAu;
  Mcu_InitClock_RetVal = E_OK;
  Scg.SOSCCSR = 0x04000000u;
  Scg.SIRCCSR = 0x04000000u;
  Scg.SPLLCSR = 0x04000000u;
  Mcu_PerformReset_HitCount = 0u;
  EcuM_unShaData_Clk_Cfg_Fail = 0u;

  //Step 2) Assign Input 
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_McuInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ucClockType_Out, 0xBAu, == );
  AL_UNITTEST_CHECK(Mcu_InitClock_HitCount, 1u, == );
  AL_UNITTEST_CHECK(EcuM_unShaData_Clk_Cfg_Fail, 0x5A01u, == );
  AL_UNITTEST_CHECK(Mcu_PerformReset_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test the Clock consistency and clock errors
///               1) Insert error in SOSC, FIRC and SPLL (function detects error and returns FALSE)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1287, LDM.MDRS_ECUM.1291
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  SCG->SOSCCSR = 0x04002000u
/// \input  SCG->FIRCCSR = 0x040700C0u
/// \input  SCG->SPLLCSR = 0x04350900u
///
/// - Expectations:
///
/// \output EcuM_ClockCfg_Consistency_Check_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_1(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  SCG->SOSCCSR = 0x04002000u;
  SCG->FIRCCSR = 0x040700C0u;
  SCG->SPLLCSR = 0x04350900u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ClockCfg_Consistency_Check_RetVal = EcuM_ClockCfg_Consistency_Check();

 //-----------------------------------------------------------------------------
 // Outputs
 //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ClockCfg_Consistency_Check_RetVal,     FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test the Clock consistency and clock errors
///               1) Remove error in SOSC, FIRC and SPLL (function detects no error and returns TRUE)
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_ECUM.1287, LDM.MDRS_ECUM.1291
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  SCG->SOSCCSR = 0x00002000u
/// \input  SCG->FIRCCSR = 0x000700C0u
/// \input  SCG->SPLLCSR = 0x00350900u
///
/// - Expectations:
///
/// \output EcuM_ClockCfg_Consistency_Check_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_2(void)
{

  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  SCG->SOSCCSR = 0x00002000u;
  SCG->FIRCCSR = 0x000700C0u;
  SCG->SPLLCSR = 0x00350900u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_ClockCfg_Consistency_Check_RetVal = EcuM_ClockCfg_Consistency_Check();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_ClockCfg_Consistency_Check_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_reEcuM_RequestRUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that the function reads the request RUN command
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_ElecInt_RequestRUN_Param1   = ECUM_LIFEPHASE_NM_USER
/// \input  Rte_Read_ElecInt_RequestRUN_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Read_ElecInt_RequestRUN_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_reEcuM_RequestRUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_ElecInt_RequestRUN_Param1   = ECUM_LIFEPHASE_NM_USER;
  Rte_Read_ElecInt_RequestRUN_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  reEcuM_RequestRUN();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_ElecInt_RequestRUN_HitCount,       1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_reEcuM_ReleaseRUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that the function reads the release RUN command
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_ElecInt_ReleaseRUN_Param1   = ECUM_LIFEPHASE_NM_USER
/// \input  Rte_Read_ElecInt_ReleaseRUN_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Read_ElecInt_ReleaseRUN_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_reEcuM_ReleaseRUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_ElecInt_ReleaseRUN_Param1   = ECUM_LIFEPHASE_NM_USER;
  Rte_Read_ElecInt_ReleaseRUN_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  reEcuM_ReleaseRUN();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_ElecInt_ReleaseRUN_HitCount,       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_reEcuM_ReleasePOST_RUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that the function reads the release POST RUN command
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_ElecInt_ReleasePOST_RUN_Param1   = ECUM_LIFEPHASE_NM_USER
/// \input  Rte_Read_ElecInt_ReleasePOST_RUN_HitCount = 0u

///
/// - Expectations:
///
/// \output Rte_Read_ElecInt_ReleasePOST_RUN_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_reEcuM_ReleasePOST_RUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_ElecInt_ReleasePOST_RUN_Param1   = ECUM_LIFEPHASE_NM_USER;
  Rte_Read_ElecInt_ReleasePOST_RUN_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  reEcuM_ReleasePOST_RUN();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_ElecInt_ReleasePOST_RUN_HitCount,       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_reEcuM_RequestPOST_RUN_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that the function reads the request POST RUN command
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_Diag_RequestPOST_RUN_Param1   = ECUM_LIFEPHASE_NM_USER
/// \input  Rte_Read_Diag_RequestPOST_RUN_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Read_Diag_RequestPOST_RUN_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_reEcuM_RequestPOST_RUN_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  Rte_Read_Diag_RequestPOST_RUN_Param1   = ECUM_LIFEPHASE_NM_USER;
  Rte_Read_Diag_RequestPOST_RUN_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  reEcuM_RequestPOST_RUN();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Diag_RequestPOST_RUN_HitCount,       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_rreEcuM_DiagResetRequest_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that the function activates the diag reset command
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_boDiagReqReset = FALSE
///
/// - Expectations:
///
/// \output EcuM_boDiagReqReset = TRUE
///
//-----------------------------------------------------------------------------
void Mt_EcuM_reEcuM_DiagResetRequest_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_boDiagReqReset = FALSE;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  reEcuM_DiagResetRequest();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(EcuM_boDiagReqReset,       TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_WdgInit_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test that the function activates init state of SBC watchdog based on developer hook (INACTIVE HOOK)
///
/// \FuSa Relevant: ASIL_B
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_unShaData_Wdg_Hook_Enbl = 0xABCDu
/// \input CddSbc_SetWdgTimeoutModeAnd200ms_HitCount = 0u
///
/// - Expectations:
///
/// \output CddSbc_SetWdgTimeoutModeAnd200ms_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_WdgInit_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_unShaData_Wdg_Hook_Enbl              = 0xABCDu;
  CddSbc_SetWdgTimeoutModeAnd200ms_HitCount = 0u;


  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_WdgInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSbc_SetWdgTimeoutModeAnd200ms_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_EcuM_EcuM_WdgInit_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test that the function deactivates init state of SBC watchdog based on developer hook (ACTIVE HOOK)
///
/// \FuSa Relevant: -
///
/// \Used Test Method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input EcuM_unShaData_Wdg_Hook_Enbl = 0x5A01u
/// \input CddSbc_SetWdgTimeoutModeAnd200ms_HitCount = 0u
///
/// - Expectations:
///
/// \output CddSbc_SetWdgTimeoutModeAnd200ms_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_EcuM_EcuM_WdgInit_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1) Set pre-conditions
  EcuM_unShaData_Wdg_Hook_Enbl              = 0x5A01u;
  CddSbc_SetWdgTimeoutModeAnd200ms_HitCount = 0u;


  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  EcuM_WdgInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSbc_SetWdgTimeoutModeAnd200ms_HitCount, 0u, == );
}


//=============================================================================
// Test Cases
//=============================================================================

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
#if 0
  ALUnitTest_AddFunction("Mt_EcuM_Com_Off_Request_Callback_TestCase_1",                               Mt_EcuM_Com_Off_Request_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_Sleep_Callback_TestCase_1",                                         Mt_EcuM_Sleep_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_Wake_Up_Request_Callback_TestCase_1",                               Mt_EcuM_Wake_Up_Request_Callback_TestCase_1);
#endif
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_InvalidInterrupt_Reset_TestCase_1",                            Mt_EcuM_EcuM_InvalidInterrupt_Reset_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_1",                            Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_2",                            Mt_EcuM_ERM_single_fault_IRQHandler_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Inject_FLASH_DED_ECCError_TestCase_1",                         Mt_EcuM_EcuM_Inject_FLASH_DED_ECCError_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_1",                           Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_2",                           Mt_EcuM_EcuM_Inject_RAM_DED_ECCError_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_1",                           Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_2",                           Mt_EcuM_EcuM_Inject_RAM_SEC_ECCError_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_HandleNvmWrite_TestCase_1",                                    Mt_EcuM_EcuM_HandleNvmWrite_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_EnterPrep_Shutdown_TestCase_1",                                Mt_EcuM_EcuM_EnterPrep_Shutdown_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_1",                              Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_2",                              Mt_EcuM_EcuM_Up_HandleTransitions_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Enter_Shutdown_TestCase_1",                                    Mt_EcuM_EcuM_Enter_Shutdown_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ExitPrep_Shutdown_TestCase_1",                                 Mt_EcuM_EcuM_ExitPrep_Shutdown_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_WaitNvMReady_TestCase_1",                                      Mt_EcuM_EcuM_WaitNvMReady_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_WaitNvMReady_TestCase_2",                                      Mt_EcuM_EcuM_WaitNvMReady_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_WaitNvMReady_TestCase_3",                                      Mt_EcuM_EcuM_WaitNvMReady_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_WaitForNvMReadAllReady_TestCase_1",                            Mt_EcuM_EcuM_WaitForNvMReadAllReady_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_1",                         Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_1",                         Mt_EcuM_EcuM_StartUp_HandleTransitions_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateStartup_TestCase_1",                                    Mt_EcuM_EcuM_OnStateStartup_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReportWgdReset_TestCase_1",                                    Mt_EcuM_EcuM_ReportWgdReset_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReportWgdReset_TestCase_2",                                    Mt_EcuM_EcuM_ReportWgdReset_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_1",                                 Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_2",                                 Mt_EcuM_EcuM_ReportAppCrcReset_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_AL_InterruptCfg_TestCase_1",                                   Mt_EcuM_EcuM_AL_InterruptCfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_AL_InterruptEnable_TestCase_1",                                Mt_EcuM_EcuM_AL_InterruptEnable_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_RequestRUN_TestCase_1",                                        Mt_EcuM_EcuM_RequestRUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_RequestRUN_TestCase_2",                                        Mt_EcuM_EcuM_RequestRUN_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_RequestRUN_TestCase_3",                                        Mt_EcuM_EcuM_RequestRUN_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_1",                                   Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_2",                                   Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_3",                                   Mt_EcuM_EcuM_RequestPOST_RUN_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReleaseRUN_TestCase_1",                                        Mt_EcuM_EcuM_ReleaseRUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReleaseRUN_TestCase_2",                                        Mt_EcuM_EcuM_ReleaseRUN_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReleaseRUN_TestCase_3",                                        Mt_EcuM_EcuM_ReleaseRUN_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_1",                                   Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_2",                                   Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_3",                                   Mt_EcuM_EcuM_ReleasePOST_RUN_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_FlashCrcFailure_Indication_TestCase_1",                        Mt_EcuM_EcuM_FlashCrcFailure_Indication_TestCase_1);
#if 0
  ALUnitTest_AddFunction("Mt_EcuM_Sleep_Request_Callback_TestCase_1",                                 Mt_EcuM_Sleep_Request_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_Connected_Callback_TestCase_1",                                     Mt_EcuM_Connected_Callback_TestCase_1);
#endif
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_1",                  Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_2",                  Mt_EcuM_EcuM_Evaluate_ReleasePostRun_Condtion_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetActiveApplication_TestCase_1",                              Mt_EcuM_EcuM_SetActiveApplication_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Enable_ChargePump_TestCase_1",                                 Mt_EcuM_EcuM_Enable_ChargePump_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_NvmWrite_TestCase_1",                                          Mt_EcuM_EcuM_NvmWrite_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_NvmWrite_TestCase_2",                                          Mt_EcuM_EcuM_NvmWrite_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Invalidate_Shutdown_TestCase_1",                               Mt_EcuM_EcuM_Invalidate_Shutdown_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_1",                        Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_2",                        Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_3",                        Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_4",                        Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_5",                        Mt_EcuM_EcuM_ShutDown_HandleTransitions_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_DiagResetRequest_TestCase_1",                                  Mt_EcuM_EcuM_DiagResetRequest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateShutDown_TestCase_1",                                   Mt_EcuM_EcuM_OnStateShutDown_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_StartOS_TestCase_1",                                           Mt_EcuM_EcuM_StartOS_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_AL_DriverInitOne_TestCase_1",                                  Mt_EcuM_EcuM_AL_DriverInitOne_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_AL_DriverInitZero_TestCase_1",                                 Mt_EcuM_EcuM_AL_DriverInitZero_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_StartupTwo_Trusted_TestCase_1",                                Mt_EcuM_EcuM_StartupTwo_Trusted_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_StartupTwo_NonTrusted_TestCase_1",                             Mt_EcuM_EcuM_StartupTwo_NonTrusted_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_1",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_2",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_3",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_4",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_5",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_6",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_7",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_7);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_8",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_8);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_9",                                    Mt_EcuM_EcuM_SetResetReason_TestCase_9);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_10",                                   Mt_EcuM_EcuM_SetResetReason_TestCase_10);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_11",                                   Mt_EcuM_EcuM_SetResetReason_TestCase_11);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_12",                                   Mt_EcuM_EcuM_SetResetReason_TestCase_12);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_13",                                   Mt_EcuM_EcuM_SetResetReason_TestCase_13);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_14",                                   Mt_EcuM_EcuM_SetResetReason_TestCase_14);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_SetResetReason_TestCase_15",                                   Mt_EcuM_EcuM_SetResetReason_TestCase_15);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_3",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_4",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_5",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_6",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_8_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_3",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_7_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_6_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_5_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_3",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_4",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_5",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_6",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_4_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_3",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_4",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_5",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_6",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_3_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_3",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_4",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_5",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_6",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_2_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_1",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_2",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_3",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_4",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_5",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_6",                               Mt_EcuM_EcuM_MPU_SelfTest_Test_1_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_MPU_Config_TestCase_1",                           Mt_EcuM_EcuM_MPU_SelfTest_MPU_Config_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_1",                      Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_2",                      Mt_EcuM_EcuM_mpu_SelfTest_GestMpuHwStatus_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_RestoreDefaultReg0W2_TestCase_1",                 Mt_EcuM_EcuM_MPU_SelfTest_RestoreDefaultReg0W2_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_GetDefaultReg0W2_TestCase_1",                     Mt_EcuM_EcuM_MPU_SelfTest_GetDefaultReg0W2_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_PLL_Unlock_SelfTest_Fail_Reaction_TestCase_1",                 Mt_EcuM_EcuM_PLL_Unlock_SelfTest_Fail_Reaction_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Unused_Opcode_SelfTest_Fail_Reaction_TestCase_1",              Mt_EcuM_EcuM_Unused_Opcode_SelfTest_Fail_Reaction_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ECC_SelfTest_Fail_Reaction_TestCase_1",                        Mt_EcuM_EcuM_ECC_SelfTest_Fail_Reaction_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_PLLUnlockSelfTest_TestCase_1",                                 Mt_EcuM_EcuM_PLLUnlockSelfTest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_UnusedOpcodeSelfTest_TestCase_1",                              Mt_EcuM_EcuM_UnusedOpcodeSelfTest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ECCSelfTest_TestCase_1",                                       Mt_EcuM_EcuM_ECCSelfTest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPU_SelfTest_Fail_Reaction_TestCase_1",                        Mt_EcuM_EcuM_MPU_SelfTest_Fail_Reaction_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_HardFault_Handler_TestCase_1",                                      Mt_EcuM_HardFault_Handler_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_HardFault_Handler_TestCase_2",                                      Mt_EcuM_HardFault_Handler_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPUSelfTest_TestCase_1",                                       Mt_EcuM_EcuM_MPUSelfTest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MPUSelfTest_TestCase_2",                                       Mt_EcuM_EcuM_MPUSelfTest_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_McuSelfTest_TestCase_1",                                       Mt_EcuM_EcuM_McuSelfTest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_McuSelfTest_TestCase_2",                                       Mt_EcuM_EcuM_McuSelfTest_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_1",                  Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_2",                  Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_3",                  Mt_EcuM_EcuM_Evaluate_RequestPostRun_Condtion_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_1",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_2",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_3",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_4",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_5",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_6",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_6);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_7",                    Mt_EcuM_EcuM_ShutDownPrep_HandleTransitions_TestCase_7);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateShutDownPrep_TestCase_1",                               Mt_EcuM_EcuM_OnStateShutDownPrep_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateUp_TestCase_1",                                         Mt_EcuM_EcuM_OnStateUp_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateUp_TestCase_2",                                         Mt_EcuM_EcuM_OnStateUp_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateUp_TestCase_3",                                         Mt_EcuM_EcuM_OnStateUp_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_OnStateUp_TestCase_4",                                         Mt_EcuM_EcuM_OnStateUp_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MainFunction_TestCase_1",                                      Mt_EcuM_EcuM_MainFunction_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MainFunction_TestCase_2",                                      Mt_EcuM_EcuM_MainFunction_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MainFunction_TestCase_3",                                      Mt_EcuM_EcuM_MainFunction_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MainFunction_TestCase_4",                                      Mt_EcuM_EcuM_MainFunction_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_MainFunction_TestCase_5",                                      Mt_EcuM_EcuM_MainFunction_TestCase_5);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Init_TestCase_1",                                              Mt_EcuM_EcuM_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_rpEcuM_Cycle0_TestCase_1",                                          Mt_EcuM_rpEcuM_Cycle0_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_1",                            Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_2",                            Mt_EcuM_ERM_double_fault_IRQHandler_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_1",                                  Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_2",                                  Mt_EcuM_FTFC_Fault_IRQHandler_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ECCProtEnable_TestCase_1",                                     Mt_EcuM_EcuM_ECCProtEnable_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ECCProtEnable_TestCase_2",                                     Mt_EcuM_EcuM_ECCProtEnable_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_CheckAppCrc_TestCase_1",                                       Mt_EcuM_EcuM_CheckAppCrc_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_CheckAppCrc_TestCase_2",                                       Mt_EcuM_EcuM_CheckAppCrc_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_CheckAppCrc_TestCase_3",                                       Mt_EcuM_EcuM_CheckAppCrc_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_1",                                  Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_2",                                  Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_3",                                  Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_3);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_4",                                  Mt_EcuM_EcuM_Check_MPU_Errors_TestCase_4);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_Get_Mpu_Test_Hook_Address_1",                                  Mt_EcuM_EcuM_Get_Mpu_Test_Hook_Address_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_McuInit_TestCase_1",                                           Mt_EcuM_EcuM_McuInit_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_McuInit_TestCase_2",                                           Mt_EcuM_EcuM_McuInit_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_1",                        Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_2",                        Mt_EcuM_EcuM_ClockCfg_Consistency_Check_TestCase_2);
  ALUnitTest_AddFunction("Mt_EcuM_reEcuM_RequestRUN_TestCase_1",                                      Mt_EcuM_reEcuM_RequestRUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_reEcuM_ReleaseRUN_TestCase_1",                                      Mt_EcuM_reEcuM_ReleaseRUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_reEcuM_ReleasePOST_RUN_TestCase_1",                                 Mt_EcuM_reEcuM_ReleasePOST_RUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_reEcuM_RequestPOST_RUN_TestCase_1",                                 Mt_EcuM_reEcuM_RequestPOST_RUN_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_reEcuM_DiagResetRequest_TestCase_1",                                Mt_EcuM_reEcuM_DiagResetRequest_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_WdgInit_TestCase_1",                                           Mt_EcuM_EcuM_WdgInit_TestCase_1);
  ALUnitTest_AddFunction("Mt_EcuM_EcuM_WdgInit_TestCase_2",                                           Mt_EcuM_EcuM_WdgInit_TestCase_2);
}

// EOF
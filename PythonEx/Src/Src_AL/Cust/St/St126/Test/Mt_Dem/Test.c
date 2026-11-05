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
/// \brief Module test of Dem
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
//  Files covered by this module unit test:
//        Cust/St/St126/App/Bsw/Dem:
//            - ctaaDem.c
//            - Dem.c
//=============================================================================
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
/// \Test Case : Mt_Dem_riDem_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized correctly after the call on the runnable is done
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone           = FALSE
/// \input   NvmBlockDemData.aucAgingCounter[0] = 0u
/// \input   Dem_ucSideModifier                 = 0u
///
/// - Expectations:
///
/// \output Dem_boInitializationDone                            = TRUE
/// \output Dem_asDiagFaultState[0].ucDiagFaultState            = 0x08u
/// \output Dem_asStatusTest[0].ucResult                        = DEM_EVENT_STATUS_PASSED
/// \output Dem_astEventStatus[0].unStatus                      = 192u 
/// \output NvmBlockDemData.aucAgingCounter[0]                  = 0u
/// \output Dem_ucSideModifier                                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_riDem_Init(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone            = FALSE;
  NvmBlockDemData.aucAgingCounter[0]  = 0u;
  Dem_ucSideModifier                  = 0u;

  // Step 3) Call FUT
  riDem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitializationDone,                  TRUE, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[0].ucDiagFaultState,  0x08u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[0].ucResult,              DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,            192u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[0],        0u, == );
  AL_UNITTEST_CHECK(Dem_ucSideModifier,                        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_rpDem_Cycle0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the runnable calll does nothing if the initialization hasn't been done
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone                     = FALSE
/// \input   Dem_astEventStatus[0].unStatus               = DEM_STATUS_TEST_PREPASSED
/// \input   Dem_astEventStatus[0].ulDebounceStartTime    = 1000u
///
/// - Expectations:
///
/// \output Dem_astEventStatus[0].ulDebounceStartTime    = 1000u
/// \output Dem_astEventStatus[0].unStatus               = DEM_STATUS_TEST_PREPASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_rpDem_Cycle0_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                   = FALSE;
  Dem_astEventStatus[0].unStatus             = DEM_STATUS_TEST_PREPASSED;
  Dem_astEventStatus[0].ulDebounceStartTime  = 1000u;

  // Step 3) Call FUT
  rpDem_Cycle0();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,             DEM_STATUS_TEST_PREPASSED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].ulDebounceStartTime,  1000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_rpDem_Cycle0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the the correct fault state is set
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boInitializationDone                    = TRUE
/// \input dem_config[0].debounce_cnt_max              = DEM_JDD_CUSTOM_FAULT_CNT_MAX
/// \input Dem_astEventStatus[0].unStatus              = DEM_STATUS_TEST_FAILED
/// \input Dem_astEventStatus[0].ulDebounceStartTime   = 0u
/// \input Gpt_GetTimeElapsed_RetVal                   = 0u
/// \input Gpt_GetTimeElapsed_HitCount                 = 0u
/// \input dem_config[0].debounce_time_failed          = 0u
/// \input Dem_asDiagFaultState[0].ucDiagFaultState    = DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[0].ucDiagFaultState     = 16u
///
//-----------------------------------------------------------------------------
void Mt_Dem_rpDem_Cycle0_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                   = TRUE;
  dem_config[0].debounce_cnt_max             = DEM_JDD_CUSTOM_FAULT_CNT_MAX;
  Dem_astEventStatus[0].unStatus             = DEM_STATUS_TEST_FAILED;
  Dem_astEventStatus[0].ulDebounceStartTime  = 0u;
  LPTMR0_GetTimeElapsed_RetVal               = 0u;
  LPTMR0_GetTimeElapsed_HitCount             = 0u;
  dem_config[0].debounce_time_failed         = 0u;
  Dem_asDiagFaultState[0].ucDiagFaultState   = DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC;
  SysMonRx_Callbacks_GetDiagMuxState_Param1  = FALSE;

  // Step 3) Call FUT
  rpDem_Cycle0();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[0].ucDiagFaultState,  16u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_rpDem_Cycle0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the the correct fault state is set
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boInitializationDone                     = TRUE
/// \input dem_config[42].debounce_cnt_max              = 10u
/// \input Dem_astEventStatus[42].unStatus              = DEM_STATUS_TEST_PREPASSED
/// \input Dem_astEventStatus[42].ulDebounceStartTime   = 0u
/// \input Gpt_GetTimeElapsed_RetVal                    = 0u
/// \input Gpt_GetTimeElapsed_HitCount                  = 0u
/// \input dem_config[42].debounce_time_passed          = 0u
/// \input Dem_asDiagFaultState[42].ucDiagFaultState    = DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[42].ucDiagFaultState   = 32u
///
//-----------------------------------------------------------------------------
void Mt_Dem_rpDem_Cycle0_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                    = TRUE;
  dem_config[42].debounce_cnt_max             = 10u;
  Dem_astEventStatus[42].unStatus             = DEM_STATUS_TEST_PREPASSED;
  Dem_astEventStatus[42].ulDebounceStartTime  = 0u;
  LPTMR0_GetTimeElapsed_RetVal                = 0u;
  LPTMR0_GetTimeElapsed_HitCount              = 0u;
  dem_config[42].debounce_time_passed         = 0u;
  Dem_asDiagFaultState[42].ucDiagFaultState   = DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC;

  // Step 3) Call FUT
  rpDem_Cycle0();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[42].ucDiagFaultState,  32u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_rpDem_Cycle0_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the the correct fault state is set
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boInitializationDone                     = TRUE
/// \input dem_config[83].debounce_cnt_max              = DEM_JDD_CUSTOM_FAULT_CNT_MAX
/// \input Dem_astEventStatus[83].unStatus              = DEM_STATUS_TEST_PREPASSED
/// \input Dem_astEventStatus[83].ulDebounceStartTime   = 0u
/// \input Gpt_GetTimeElapsed_RetVal                    = 0u
/// \input Gpt_GetTimeElapsed_HitCount                  = 0u
/// \input dem_config[83].debounce_time_passed          = 0u
/// \input Dem_asDiagFaultState[83].ucDiagFaultState    = DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[83].ucDiagFaultState   = 32u
///
//-----------------------------------------------------------------------------
void Mt_Dem_rpDem_Cycle0_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                    = TRUE;
  dem_config[83].debounce_cnt_max             = DEM_JDD_CUSTOM_FAULT_CNT_MAX;
  Dem_astEventStatus[83].unStatus             = DEM_STATUS_TEST_PREPASSED;
  Dem_astEventStatus[83].ulDebounceStartTime  = 0u;
  LPTMR0_GetTimeElapsed_RetVal                = 0u;
  LPTMR0_GetTimeElapsed_HitCount              = 0u;
  dem_config[83].debounce_time_passed         = 0u;
  Dem_asDiagFaultState[83].ucDiagFaultState   = DEM_JDD_FAULT_ABSENT_CONFIRMED_DTC;
  SysMonRx_Callbacks_GetDiagMuxState_Param1   = FALSE;

  // Step 3) Call FUT
  rpDem_Cycle0();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[83].ucDiagFaultState,  32u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_rpDem_Cycle0_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the the correct fault state is set
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boInitializationDone                    = TRUE
/// \input dem_config[130].debounce_cnt_max            = 122u
/// \input Dem_astEventStatus[130].unStatus            = DEM_STATUS_TEST_FAILED
/// \input Dem_astEventStatus[130].ulDebounceStartTime = 0u
/// \input Gpt_GetTimeElapsed_RetVal                   = 0u
/// \input Gpt_GetTimeElapsed_HitCount                 = 0u
/// \input dem_config[130].debounce_time_failed        = 0u
/// \input Dem_asDiagFaultState[130].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[130].ucDiagFaultState   = 16u
///
//-----------------------------------------------------------------------------
void Mt_Dem_rpDem_Cycle0_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                     = TRUE;
  dem_config[130].debounce_cnt_max             = 122u;
  Dem_astEventStatus[130].unStatus             = DEM_STATUS_TEST_FAILED;
  Dem_astEventStatus[130].ulDebounceStartTime  = 0u;
  LPTMR0_GetTimeElapsed_RetVal                 = 0u;
  LPTMR0_GetTimeElapsed_HitCount               = 0u;
  dem_config[130].debounce_time_failed         = 0u;
  Dem_asDiagFaultState[130].ucDiagFaultState   = DEM_JDD_FAULT_PRESENT_CONFIRMED_DTC;

  // Step 3) Call FUT
  rpDem_Cycle0();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[130].ucDiagFaultState,  16u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_rpDem_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the the correct fault state is set
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_rpDem_Cycle0(void)
{
  Mt_Dem_rpDem_Cycle0_TestCase_1();
  Mt_Dem_rpDem_Cycle0_TestCase_2();
  Mt_Dem_rpDem_Cycle0_TestCase_3();
  Mt_Dem_rpDem_Cycle0_TestCase_4();
  Mt_Dem_rpDem_Cycle0_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized correctly after the call on the init function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone                           = FALSE
/// \input   NvmBlockDemData.aucAgingCounter[0]                 = 0u
/// \input   Dem_ucSideModifier                                 = 0u
///
/// - Expectations:
///
/// \output Dem_boInitializationDone                            = TRUE
/// \output Dem_asDiagFaultState[0].ucDiagFaultState            = 0x08u
/// \output Dem_asStatusTest[0].ucResult                        = DEM_EVENT_STATUS_PASSED
/// \output Dem_astEventStatus[0].unStatus                      = 192u 
/// \output NvmBlockDemData.aucAgingCounter[0]                  = 0u
/// \output Dem_ucSideModifier                                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone            = FALSE;
  NvmBlockDemData.aucAgingCounter[0]  = 0u;
  Dem_ucSideModifier                  = 0u;

  // Step 3) Call FUT
  Dem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitializationDone,                  TRUE, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[0].ucDiagFaultState,  0x08u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[0].ucResult,              DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,            192u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[0],        0u, == );
  AL_UNITTEST_CHECK(Dem_ucSideModifier,                        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is decremented at initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone           = FALSE
/// \input   NvmBlockDemData.aucAgingCounter[1] = 10u
///
/// - Expectations:
///
/// \output Dem_boInitializationDone           = TRUE
/// \output NvmBlockDemData.aucAgingCounter[1] = 9u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone            = FALSE;
  NvmBlockDemData.aucAgingCounter[1]  = 10u;

  // Step 3) Call FUT
  Dem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitializationDone,            TRUE, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[1],  9u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is not decremented
///         when the ALEC failed in the previous operation cycle
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_boInitializationDone           = FALSE
/// \input    NvmBlockDemData.aucAgingCounter[1] = 10u
/// \input    NvmBlockDemData.aucStatus[1]       = 0x02
///
/// - Expectations:
///
/// \output Dem_boInitializationDone             = TRUE
/// \output NvmBlockDemData.aucAgingCounter[1]   = 10u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone            = FALSE;
  NvmBlockDemData.aucAgingCounter[1]  = 10u;
  NvmBlockDemData.aucStatus[1]        = 0x02;

  // Step 3) Call FUT
  Dem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitializationDone,            TRUE, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[1],  10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is not decremented
///         when the ALEC failed in the previous operation cycle
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_boInitializationDone                   = FALSE
/// \input    NvmBlockDemData.aucAgingCounter[1]         = 10u
/// \input    NvmBlockDemData.aucStatus[1]               = 0x02
/// \input    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = 255u
///
/// - Expectations:
///
/// \output Dem_boInitializationDone             = TRUE
/// \output NvmBlockDemData.aucAgingCounter[1]   = 10u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                    = FALSE;
  NvmBlockDemData.aucAgingCounter[1]          = 10u;
  NvmBlockDemData.aucStatus[1]                = 0x02;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1  = 255u;

  // Step 3) Call FUT
  Dem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitializationDone,            TRUE, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[1],  10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is decremented at initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone           = FALSE
/// \input   NvmBlockDemData.aucAgingCounter[1] = 10u
///
/// - Expectations:
///
/// \output Dem_boInitializationDone           = TRUE
/// \output NvmBlockDemData.aucAgingCounter[1] = 9u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone            = FALSE;
  NvmBlockDemData.aucAgingCounter[0]  = 10u;
  Dem_boNvmDirty                      = FALSE;
  NvM_WriteBlock_RetVal               = E_NOT_OK;

  // Step 3) Call FUT
  Dem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boNvmDirty,                      TRUE, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[0],  9u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is decremented at initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  NvmBlockDemData.aucStatus[2] = 0x11;
/// \input  Dem_asDiagFaultState[2].ucDiagFaultState = 0x08;
///
/// - Expectations:
///
/// \output  AL_UNITTEST_CHECK(Dem_asDiagFaultState[2].ucDiagFaultState, 0x1A, == );
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init_TestCase_6(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  NvmBlockDemData.aucStatus[2]              = 0x11;
  Dem_asDiagFaultState[2].ucDiagFaultState  = 0x08;

  // Step 3) Call FUT
  Dem_Init();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[2].ucDiagFaultState,  0x1A, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Dem module is intialized and the aging counter is not decremented
///                     when the ALEC failed in the previous operation cycle
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Init(void)
{
  Mt_Dem_Dem_Init_TestCase_1();
  Mt_Dem_Dem_Init_TestCase_2();
  Mt_Dem_Dem_Init_TestCase_3();
  Mt_Dem_Dem_Init_TestCase_4();
  Mt_Dem_Dem_Init_TestCase_5();
  Mt_Dem_Dem_Init_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Task_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function does nothing if the initialization of the module
///               hasn't been done
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone                     = FALSE
/// \input   Dem_astEventStatus[0].unStatus               = 0x033u
/// \input   Dem_astEventStatus[0].ulDebounceStartTime    = 1u
/// \input   LPTMR0_GetTimeElapsed_HitCount               = 0U
///
/// - Expectations:
///
/// \output Dem_astEventStatus[0].ulDebounceStartTime    = 1u
/// \output Dem_astEventStatus[0].unStatus               = 0x033u
/// \output LPTMR0_GetTimeElapsed_HitCount               = 0U
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Task_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                   = FALSE;
  LPTMR0_GetTimeElapsed_HitCount             = 0U;
  Dem_astEventStatus[0].unStatus             = 0x033u;
  Dem_astEventStatus[0].ulDebounceStartTime  = 1u;

  // Step 3) Call FUT
  Dem_Task();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].ulDebounceStartTime,  1u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,             0x033u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Task_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function clears Alec and Dtc flag
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_boInitializationDone                     = TRUE
/// \input   LPTMR0_GetTimeElapsed_HitCount               = 0U
/// \input   LPTMR0_GetTimeElapsed_RetVal                 = 500000u
/// \input   Dem_astEventStatus[0].unStatus               = 0x033u
/// \input   Dem_astEventStatus[0].ulDebounceStartTime    = 1u
/// \input   Dem_boNvmDirty                               = TRUE
///
/// - Expectations:
///
/// \output Dem_astEventStatus[0].ulDebounceStartTime    = 1u
/// \output Dem_astEventStatus[0].unStatus               = 0x033u
/// \output Gpt_GetTimeElapsed_HitCount                  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Task_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone                   = TRUE;
  LPTMR0_GetTimeElapsed_HitCount             = 0U;
  LPTMR0_GetTimeElapsed_RetVal               = 500000u;
  Dem_astEventStatus[0].unStatus             = 0x033u;
  Dem_astEventStatus[0].ulDebounceStartTime  = 1u;
  Dem_boNvmDirty                             = TRUE;

  // Step 3) Call FUT
  Dem_Task();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].ulDebounceStartTime,  1u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,             0x033u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Task_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is decremented at initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boInitializationDone            = TRUE;
/// \input Dem_astEventStatus[0u].unStatus     = DEM_STATUS_TEST_PREFAILED;
/// \input LPTMR0_GetTimeElapsed_RetVal        = 20000u;
/// \input dem_config[0u].debounce_time_failed = 1u;
/// \input Dem_boNvmDirty = FALSE;
///
/// - Expectations:
///
/// \output Dem_boNvmDirty                      = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Task_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boInitializationDone             = TRUE;
  Dem_astEventStatus[0u].unStatus      = DEM_STATUS_TEST_PREFAILED;
  LPTMR0_GetTimeElapsed_RetVal         = 20000u;
  dem_config[0u].debounce_time_failed  = 1u;
  Dem_boNvmDirty                       = FALSE;

  // Step 3) Call FUT
  Dem_Task();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boNvmDirty,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Task_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if Dem module is intialized and the aging counter is decremented at initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boInitializationDone         = TRUE;
/// \input Dem_astEventStatus[0u].unStatus  = DEM_STATUS_TEST_PREFAILED;
/// \input LPTMR0_GetTimeElapsed_RetVal     = 20000u;
/// \input Dem_boNvmDirty                   = TRUE;
/// \input NvM_WriteBlock_RetVal            = E_OK;
///
/// - Expectations:
///
/// \output Dem_boInitializationDone           = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Task_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values

  Dem_boInitializationDone         = TRUE;
  Dem_astEventStatus[0u].unStatus  = DEM_STATUS_TEST_PREFAILED;
  LPTMR0_GetTimeElapsed_RetVal     = 20000u;
  Dem_boNvmDirty                   = TRUE;
  NvM_WriteBlock_RetVal            = E_OK;

  // Step 3) Call FUT
  Dem_Task();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boNvmDirty,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Task
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function clears Alec and Dtc flag
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Task(void)
{
  Mt_Dem_Dem_Task_TestCase_3();
  Mt_Dem_Dem_Task_TestCase_1();
  Mt_Dem_Dem_Task_TestCase_2();
  Mt_Dem_Dem_Task_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the case of DEM_EVENT_STATUS_PASSED_IMMEDIATELY:
///       callback for passed is null, therefore stub function is not being called
///       callback for failed is null, therefore stub function is not being called
///       callback for custom is not null, therefore ErrCust_ErrHandling is being called
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_TriggerCallbackFunctions_Param1 = 1u
/// \input    Dem_astEventStatus[1].unStatus      = DEM_STATUS_TEST_PASSED
/// \input    dem_config[1].notify_passed         = NULL_PTR
/// \input    dem_config[1].notify_failed         = NULL_PTR
/// \input    dem_config[1].notify_custom         = ErrCust_ErrHandling
/// \input    ErrCust_ErrHandling_HitCount        = 0u
/// \input    Dem_UnitTest_NotifyPassed_HitCount  = 0u
/// \input    Dem_UnitTest_NotifyFailed_HitCount  = 0u
///
/// - Expectations:
///
/// \output ErrCust_ErrHandling_HitCount          = 1u
/// \output Dem_UnitTest_NotifyPassed_HitCount    = 0u
/// \output Dem_UnitTest_NotifyFailed_HitCount    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_TriggerCallbackFunctions_Param1  = 1u;
  Dem_astEventStatus[1].unStatus       = DEM_STATUS_TEST_PASSED;
  dem_config[1].notify_passed          = NULL_PTR;
  dem_config[1].notify_failed          = NULL_PTR;
  dem_config[1].notify_custom          = ErrCust_ErrHandling;
  Dem_UnitTest_NotifyFailed_HitCount   = 0u;
  Dem_UnitTest_NotifyPassed_HitCount   = 0u;
  ErrCust_ErrHandling_HitCount         = 0u;

  // Step 3) Call FUT
  Dem_TriggerCallbackFunctions(Dem_TriggerCallbackFunctions_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ErrHandling_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_HitCount,  0u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the case of DEM_EVENT_STATUS_FAILED_IMMEDIATELY:
///       callback for custom is null, therefore ErrCust_ErrHandling is not called
///       callback for failed is not null, therefore stub funtion is being called
///       callback for passed is null, therefore stub funtion is not being called
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_TriggerCallbackFunctions_Param1 = 1u
/// \input    Dem_astEventStatus[1].unStatus      = DEM_STATUS_TEST_FAILED
/// \input    dem_config[1].notify_custom         = NULL_PTR
/// \input    dem_config[1].notify_passed         = NULL_PTR
/// \input    dem_config[1].notify_failed         = Dem_UnitTest_NotifyFiled
/// \input    ErrCust_ErrHandling_HitCount        = 0u
/// \input    Dem_UnitTest_NotifyPassed_HitCount  = 0u
/// \input    Dem_UnitTest_NotifyFailed_HitCount  = 0u
/// \input    Dem_UnitTest_NotifyFailed_Param1    = 0u 
/// \input    Dem_UnitTest_NotifyFailed_Param2    = TRUE
///
/// - Expectations:
///
/// \output ErrCust_ErrHandling_HitCount          = 0u
/// \output Dem_UnitTest_NotifyFailed_HitCount    = 1u
/// \output Dem_UnitTest_NotifyFailed_Param1      = 2u
/// \output Dem_UnitTest_NotifyFailed_Param2      = FALSE
/// \output Dem_UnitTest_NotifyPassed_HitCount    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_TriggerCallbackFunctions_Param1  = 1u;
  Dem_astEventStatus[1].unStatus       = DEM_STATUS_TEST_FAILED;
  dem_config[1].notify_custom          = NULL_PTR;
  dem_config[1].notify_passed          = NULL_PTR;
  dem_config[1].notify_failed          = Dem_UnitTest_NotifyFailed;
  Dem_UnitTest_NotifyFailed_HitCount   = 0u;
  Dem_UnitTest_NotifyFailed_Param1     = 0u;
  Dem_UnitTest_NotifyFailed_Param2     = TRUE;
  Dem_UnitTest_NotifyPassed_HitCount   = 0u;
  ErrCust_ErrHandling_HitCount         = 0u;

  // Step 3) Call FUT
  Dem_TriggerCallbackFunctions(Dem_TriggerCallbackFunctions_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ErrHandling_HitCount,        0u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_Param1,    2u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_Param2,    FALSE, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the case of DEM_EVENT_STATUS_PASSED_IMMEDIATELY:
///       callback for passed is not null, stub funtion is being called
///       callback for custom is null, therefore ErrCust_ErrHandling is not called
///       callback for failed is not null, therefore stub funtion is being called
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   Dem_TriggerCallbackFunctions_Param1 = 1u;
/// \input   Dem_astEventStatus[1].unStatus = 0x080u;
/// \input   dem_config[1].notify_custom = NULL_PTR;
/// \input   dem_config[1].notify_failed = NULL_PTR;
/// \input   dem_config[1].notify_passed = Dem_UnitTest_NotifyPassed;
/// \input   Dem_UnitTest_NotifyFailed_HitCount = 0u;
/// \input   Dem_UnitTest_NotifyPassed_Param1 = 0u;
/// \input   Dem_UnitTest_NotifyPassed_Param2 = FALSE;
/// \input   Dem_UnitTest_NotifyPassed_HitCount = 0u;
/// \input   ErrCust_ErrHandling_HitCount = 0u;
///
/// - Expectations:
///
///   AL_UNITTEST_CHECK(ErrCust_ErrHandling_HitCount, 0u, == );
///   AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_HitCount, 1u, == );
///   AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_Param1, 2u, == );
///   AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_Param2, TRUE, == );
///   AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_HitCount, 0u, == );
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_TriggerCallbackFunctions_Param1  = 1u;
  Dem_astEventStatus[1].unStatus       = 0x080u;
  dem_config[1].notify_custom          = NULL_PTR;
  dem_config[1].notify_failed          = NULL_PTR;
  dem_config[1].notify_passed          = Dem_UnitTest_NotifyPassed;
  Dem_UnitTest_NotifyFailed_HitCount   = 0u;
  Dem_UnitTest_NotifyPassed_Param1     = 0u;
  Dem_UnitTest_NotifyPassed_Param2     = FALSE;
  Dem_UnitTest_NotifyPassed_HitCount   = 0u;
  ErrCust_ErrHandling_HitCount         = 0u;

  // Step 3) Call FUT
  Dem_TriggerCallbackFunctions(Dem_TriggerCallbackFunctions_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ErrHandling_HitCount,        0u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_Param1,    2u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_Param2,    TRUE, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the case of invalid dem event status:
///       callback for passed is not null, stub funtion is not called
///       callback for custom is not null, therefore ErrCust_ErrHandling is called
///       callback for failed is not null, stub function is not called
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_TriggerCallbackFunctions_Param1 = 1u
/// \input    Dem_astEventStatus[1].unStatus      = 0x010u
/// \input    dem_config[1].notify_custom         = ErrCust_ErrHandling
/// \input    dem_config[1].notify_passed         = Dem_UnitTest_NotifyPassed
/// \input    dem_config[1].notify_failed         = Dem_UnitTest_NotifyFailed
/// \input    ErrCust_ErrHandling_HitCount        = 0u
/// \input    Dem_UnitTest_NotifyPassed_HitCount  = 0u
/// \input    Dem_UnitTest_NotifyFailed_HitCount  = 0u
///
/// - Expectations:
///
/// \output ErrCust_ErrHandling_HitCount          = 1u
/// \output Dem_UnitTest_NotifyPassed_HitCount    = 0u
/// \output Dem_UnitTest_NotifyFailed_HitCount    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_TriggerCallbackFunctions_Param1  = 1u;
  Dem_astEventStatus[1].unStatus       = 0x010u;
  dem_config[1].notify_custom          = ErrCust_ErrHandling;
  dem_config[1].notify_failed          = Dem_UnitTest_NotifyFailed;
  dem_config[1].notify_passed          = Dem_UnitTest_NotifyPassed;
  Dem_UnitTest_NotifyFailed_HitCount   = 0u;
  Dem_UnitTest_NotifyPassed_HitCount   = 0u;
  ErrCust_ErrHandling_HitCount         = 0u;

  // Step 3) Call FUT
  Dem_TriggerCallbackFunctions(Dem_TriggerCallbackFunctions_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ErrHandling_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyPassed_HitCount,  0u, == );
  AL_UNITTEST_CHECK(Dem_UnitTest_NotifyFailed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_TriggerCallbackFunctions
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function  trigger the following callback functions: 
///                    notify_custom and (notify_passed  or notify_failed
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_TriggerCallbackFunctions(void)
{
  Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_1();
  Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_2();
  Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_3();
  Mt_Dem_Dem_TriggerCallbackFunctions_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ProcessEvent_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the correct event status is set for a given event
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_ProcessEvent_Param1                     = 41u
/// \input    Dem_ProcessEvent_Param2                     = DEM_EVENT_STATUS_PASSED_IMMEDIATELY
/// \input    Dem_astEventStatus[41].unStatus             = DEM_STATUS_TEST_PASSED
/// \input    Dem_astEventStatus[41].ulDebounceStartTime  = 100u 
///
/// - Expectations:
///
/// \output Dem_astEventStatus[41].unStatus               = 128u
/// \output Dem_astEventStatus[41].ulDebounceStartTime    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ProcessEvent_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ProcessEvent_Param1                     = 41u;
  Dem_ProcessEvent_Param2                     = DEM_EVENT_STATUS_PASSED_IMMEDIATELY;
  Dem_astEventStatus[41].unStatus             = DEM_STATUS_TEST_PASSED;
  Dem_astEventStatus[41].ulDebounceStartTime  = 100u;

  // Step 3) Call FUT
  Dem_ProcessEvent(Dem_ProcessEvent_Param1, Dem_ProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].unStatus,             128u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].ulDebounceStartTime,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ProcessEvent_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the event status and debounce time are not updated in case 
///           of an unknown event status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_ProcessEvent_Param1                     = 41u
/// \input    Dem_ProcessEvent_Param2                     = 4u (unknown event)
/// \input    Dem_astEventStatus[41].unStatus             = DEM_STATUS_TEST_PASSED
/// \input    Dem_astEventStatus[41].ulDebounceStartTime  = 100u 
///
/// - Expectations:
///
/// \output Dem_astEventStatus[41].unStatus               = DEM_STATUS_TEST_PASSED
/// \output Dem_astEventStatus[41].ulDebounceStartTime    = 100u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ProcessEvent_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ProcessEvent_Param1                     = 41u;
  Dem_ProcessEvent_Param2                     = 4u;
  Dem_astEventStatus[41].unStatus             = DEM_STATUS_TEST_PASSED;
  Dem_astEventStatus[41].ulDebounceStartTime  = 100u;

  // Step 3) Call FUT
  Dem_ProcessEvent(Dem_ProcessEvent_Param1, Dem_ProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].unStatus,             DEM_STATUS_TEST_PASSED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].ulDebounceStartTime,  100u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ProcessEvent_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the correct event status is set for a given event,
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///
/// - Preconditions:
///
/// \input    Dem_ProcessEvent_Param1                     = 41u
/// \input    Dem_ProcessEvent_Param2                     = DEM_EVENT_STATUS_PASSED_IMMEDIATELY
/// \input    Dem_astEventStatus[41].unStatus             = DEM_STATUS_CONFIRMED_DTC
/// \input    Dem_astEventStatus[41].ulDebounceStartTime  = 39u 
///
/// - Expectations:
///
/// \output Dem_astEventStatus[41].unStatus               = 136u
/// \output Dem_astEventStatus[41].ulDebounceStartTime    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ProcessEvent_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ProcessEvent_Param1              = 41u;
  Dem_ProcessEvent_Param2              = DEM_EVENT_STATUS_PASSED_IMMEDIATELY;
  Dem_astEventStatus[41].unStatus      = DEM_STATUS_CONFIRMED_DTC;
  NvmBlockDemData.aucAgingCounter[41]  = 39u;

  // Step 3) Call FUT
  Dem_ProcessEvent(Dem_ProcessEvent_Param1, Dem_ProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].unStatus,             136u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].ulDebounceStartTime,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ProcessEvent_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the correct event status is set for a given event and
///           the aging counter is set to max value          
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_ProcessEvent_Param1                     = 41u
/// \input    Dem_ProcessEvent_Param2                     = DEM_EVENT_STATUS_FAILED_IMMEDIATELY
/// \input    Dem_astEventStatus[41].unStatus             = DEM_STATUS_TEST_FAILED
/// \input    NvmBlockDemData.aucAgingCounter[41]         = 39u
///
/// - Expectations:
///
/// \output Dem_astEventStatus[41].unStatus               = 47u
/// \output Dem_astEventStatus[41].ulDebounceStartTime    = 0u
/// \output NvmBlockDemData.aucAgingCounter[41]           = 40u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ProcessEvent_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ProcessEvent_Param1              = 41u;
  Dem_ProcessEvent_Param2              = DEM_EVENT_STATUS_FAILED_IMMEDIATELY;
  Dem_astEventStatus[41].unStatus      = DEM_STATUS_TEST_FAILED;
  NvmBlockDemData.aucAgingCounter[41]  = 39u;

  // Step 3) Call FUT
  Dem_ProcessEvent(Dem_ProcessEvent_Param1, Dem_ProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].unStatus,             47u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[41].ulDebounceStartTime,  0u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[41],         40u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ProcessEvent
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the correct event status is set for a given event and
///                     the aging counter is set to max value
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ProcessEvent(void)
{
  Mt_Dem_Dem_ProcessEvent_TestCase_1();
  Mt_Dem_Dem_ProcessEvent_TestCase_2();
  Mt_Dem_Dem_ProcessEvent_TestCase_3();
  Mt_Dem_Dem_ProcessEvent_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_PreProcessEvent_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the debounce time is set correctly for DEM_EVENT_STATUS_PREPASSED
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_PreProcessEvent_Param1               = 73u
/// \input  Dem_PreProcessEvent_Param2               = DEM_EVENT_STATUS_PREPASSED
/// \input  Dem_astEventStatus[73].unStatus          = 0x00u
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 0u
/// \input  dem_config[73].debounce_time_passed      = 111u;
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 111u
///
/// - Expectations:
///
/// \output Dem_astEventStatus[73].ulDebounceStartTime = 111u
/// \output LPTMR0_GetTimeElapsed_HitCount             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_PreProcessEvent_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_PreProcessEvent_Param1           = 73u;
  Dem_PreProcessEvent_Param2           = DEM_EVENT_STATUS_PREPASSED;
  Dem_astEventStatus[73].unStatus      = 0x00u;
  LPTMR0_GetTimeElapsed_HitCount       = 0u;
  dem_config[73].debounce_time_passed  = 111u;
  LPTMR0_GetTimeElapsed_RetVal         = 111u;

  // Step 3) Call FUT
  Dem_PreProcessEvent(Dem_PreProcessEvent_Param1, Dem_PreProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[73].ulDebounceStartTime,  111u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_PreProcessEvent_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the debounce time is set correctly for DEM_EVENT_STATUS_PREFAILED
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_PreProcessEvent_Param1               = 15u
/// \input  Dem_PreProcessEvent_Param2               = DEM_EVENT_STATUS_PREFAILED
/// \input  Dem_astEventStatus[15u].unStatus         = 0x00u
/// \input  Gpt_GetTimeElapsed_HitCount              = 0u
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 999u
///
/// - Expectations:
///
/// \output Dem_astEventStatus[15u].ulDebounceStartTime = 999u
/// \output LPTMR0_GetTimeElapsed_HitCount              = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_PreProcessEvent_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_PreProcessEvent_Param1        = 15u;
  Dem_PreProcessEvent_Param2        = DEM_EVENT_STATUS_PREFAILED;
  Dem_astEventStatus[15u].unStatus  = 0x00u;
  LPTMR0_GetTimeElapsed_HitCount    = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = 999u;

  // Step 3) Call FUT
  Dem_PreProcessEvent(Dem_PreProcessEvent_Param1, Dem_PreProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[15u].ulDebounceStartTime,  999u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,               1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_PreProcessEvent_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the debounce time is not set for DEM_EVENT_STATUS_PREFAILED
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_PreProcessEvent_Param1               = 41u
/// \input  Dem_PreProcessEvent_Param2               = DEM_EVENT_STATUS_PREFAILED
/// \input  Dem_astEventStatus[41].unStatus          = DEM_EVENT_STATUS_FAILED_IMMEDIATELY
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 0u
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_PreProcessEvent_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_PreProcessEvent_Param1       = 41u;
  Dem_PreProcessEvent_Param2       = DEM_EVENT_STATUS_PREFAILED;
  Dem_astEventStatus[41].unStatus  = DEM_EVENT_STATUS_FAILED_IMMEDIATELY;
  LPTMR0_GetTimeElapsed_HitCount   = 0u;

  // Step 3) Call FUT
  Dem_PreProcessEvent(Dem_PreProcessEvent_Param1, Dem_PreProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_PreProcessEvent_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the debounce time is not set for DEM_EVENT_STATUS_PREPASSED
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_PreProcessEvent_Param1               = 41u
/// \input  Dem_PreProcessEvent_Param2               = DEM_EVENT_STATUS_PREPASSED
/// \input  Dem_astEventStatus[41].unStatus          = DEM_STATUS_TEST_PREPASSED
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 0u
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_PreProcessEvent_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_PreProcessEvent_Param1       = 41u;
  Dem_PreProcessEvent_Param2       = DEM_EVENT_STATUS_PREPASSED;
  Dem_astEventStatus[41].unStatus  = DEM_STATUS_TEST_PREPASSED;
  LPTMR0_GetTimeElapsed_HitCount   = 0u;

  // Step 3) Call FUT
  Dem_PreProcessEvent(Dem_PreProcessEvent_Param1, Dem_PreProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_PreProcessEvent_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if nothing is done in case of an unknown pre event status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_PreProcessEvent_Param1               = 41u
/// \input  Dem_PreProcessEvent_Param2               = 111u
/// \input  Dem_astEventStatus[41].unStatus          = DEM_STATUS_TEST_PREPASSED
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 0u
///
/// - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_PreProcessEvent_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_PreProcessEvent_Param1       = 41u;
  Dem_PreProcessEvent_Param2       = 111u;
  Dem_astEventStatus[41].unStatus  = DEM_STATUS_TEST_PREPASSED;
  LPTMR0_GetTimeElapsed_HitCount   = 0u;

  // Step 3) Call FUT
  Dem_PreProcessEvent(Dem_PreProcessEvent_Param1, Dem_PreProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_PreProcessEvent
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if This function starts the debounce timer and set/reset all 
///                     the flags for ALEC corresponding to unPreEventIndex
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_PreProcessEvent(void)
{
  Mt_Dem_Dem_PreProcessEvent_TestCase_1();
  Mt_Dem_Dem_PreProcessEvent_TestCase_2();
  Mt_Dem_Dem_PreProcessEvent_TestCase_3();
  Mt_Dem_Dem_PreProcessEvent_TestCase_4();
  Mt_Dem_Dem_PreProcessEvent_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if fault state is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Pass_TimeOut_Param1        = 327u
/// \input  Dem_asDiagFaultState[327u].ucDiagFaultState     = 0x02
/// \input  LPTMR0_GetTimeElapsed_RetVal                    = 1u
/// \input  LPTMR0_GetTimeElapsed_HitCount                  = 0u
/// \input  dem_config[327u].condition_confirmed_absent     = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[327u].ucDiagFaultState     = 6u
/// \output Dem_asDiagFaultState[327u].ulDiagConfirmedTimer = 1u
/// \output LPTMR0_GetTimeElapsed_HitCount                  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_TimeOut_Param1    = 327u;
  Dem_asDiagFaultState[327].ucDiagFaultState  = 0x02;
  LPTMR0_GetTimeElapsed_RetVal                = 1u;
  LPTMR0_GetTimeElapsed_HitCount              = 0u;
  dem_config[327].condition_confirmed_absent  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_TimeOut(Dem_DiagProcessEvent_Pass_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[327].ucDiagFaultState,      6u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[327].ulDiagConfirmedTimer,  1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if fault state is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Dem_DiagProcessEvent_Pass_TimeOut_Param1                    = 1u
/// \input    Dem_asDiagFaultState[1].ucDiagFaultState                    = 0x04u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState                      = 44u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_TimeOut_Param1                                         = 1u;
  Dem_asDiagFaultState[1].ucDiagFaultState                                         = 0x06u;
  dem_config[Dem_DiagProcessEvent_Pass_TimeOut_Param1].condition_confirmed_absent  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_TimeOut(Dem_DiagProcessEvent_Pass_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  44u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if fault state is not set if it doesn't match to the conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_TimeOut_Param1      = 41u
/// \input Dem_asDiagFaultState[41].ucDiagFaultState     = 0x02u
/// \input Dem_asDiagFaultState[41].ulDiagConfirmedTimer = 0u
/// \input Gpt_GetTimeElapsed_RetVal                     = 10u
/// \input Gpt_GetTimeElapsed_HitCount                   = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[41].ucDiagFaultState     = 44u
/// \output Dem_asDiagFaultState[41].ulDiagConfirmedTimer = 10u
/// \output Gpt_GetTimeElapsed_HitCount                   = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_TimeOut_Param1       = 41u;
  Dem_asDiagFaultState[41].ucDiagFaultState      = 0x02u;
  Dem_asDiagFaultState[41].ulDiagConfirmedTimer  = 0u;
  LPTMR0_GetTimeElapsed_RetVal                   = 10u;
  LPTMR0_GetTimeElapsed_HitCount                 = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_TimeOut(Dem_DiagProcessEvent_Pass_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[41].ucDiagFaultState,      44u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[41].ulDiagConfirmedTimer,  10u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if fault state is not set if it doesn't match to the conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_TimeOut_Param1        = 180u
/// \input Dem_asDiagFaultState[180u].ucDiagFaultState     = 0x02u
/// \input Dem_asDiagFaultState[180u].ulDiagConfirmedTimer = 0u
/// \input Gpt_GetTimeElapsed_RetVal                       = 10u
/// \input Gpt_GetTimeElapsed_HitCount                     = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[180u].ucDiagFaultState     = 44u
/// \output Dem_asDiagFaultState[180u].ulDiagConfirmedTimer = 10u
/// \output Gpt_GetTimeElapsed_HitCount                     = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_TimeOut_Param1         = 180u;
  Dem_asDiagFaultState[180u].ucDiagFaultState      = 0x02u;
  Dem_asDiagFaultState[180u].ulDiagConfirmedTimer  = 0u;
  LPTMR0_GetTimeElapsed_RetVal                     = 10u;
  LPTMR0_GetTimeElapsed_HitCount                   = 0u;
  dem_config[180u].debounce_time_passed            = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_TimeOut(Dem_DiagProcessEvent_Pass_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].ucDiagFaultState,      44u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].ulDiagConfirmedTimer,  10u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,                   2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if fault state is not set if it doesn't match to the conditions
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut(void)
{
  Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_1();
  Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_2();
  Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_3();
  Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour while fault is absent and confirmed absent
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_Cnt_Param1     = 1u
/// \input Dem_asDiagFaultState[1].ucDiagFaultState = DEM_JDD_FAULT_PRESENT_CONFIRMED
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState = 44u
/// \output Dem_asDiagFaultState[1].unDiagFaultCnt   = 0u  (dbnc_cnt_max -dbnc_cnt_dec)
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1      = 1u;
  Dem_asDiagFaultState[1].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT_CONFIRMED;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  44u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour while fault is absent and not confirmed absent and
///           its fault counter reaches minimum value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_Cnt_Param1              = 339u
/// \input Dem_asDiagFaultState[339u].ucDiagFaultState       = DEM_JDD_FAULT_PRESENT_CONFIRMED
/// \input Dem_asDiagFaultState[339u].unDiagFaultCnt         = 10u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[339u].ucDiagFaultState      = 44u
/// \output Dem_asDiagFaultState[339u].unDiagFaultCnt        = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1         = 339u;
  Dem_asDiagFaultState[339u].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT_CONFIRMED;
  Dem_asDiagFaultState[339u].unDiagFaultCnt    = 10u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[339u].ucDiagFaultState,  44u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[339u].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour when fault was present during DiagMuxOn
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_Cnt_Param1          = 4u
/// \input Dem_asDiagFaultState[4].ucDiagFaultState      = DEM_JDD_FAULT_PRESENT
/// \input Dem_asDiagFaultState[4].unDiagFaultCnt        = 100u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[4].ucDiagFaultState     = 0u
/// \output Dem_asDiagFaultState[4].unDiagFaultCnt       = 99u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1      = 4u;
  Dem_asDiagFaultState[4].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT;
  Dem_asDiagFaultState[4].unDiagFaultCnt    = 100u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[4].ucDiagFaultState,  0u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[4].unDiagFaultCnt,    99u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour when fault was present during DiagMuxOn and fault cnt is resetted
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_Cnt_Param1            = 145u
/// \input Dem_asDiagFaultState[145].ucDiagFaultState      = DEM_JDD_FAULT_PRESENT
/// \input Dem_asDiagFaultState[145].unDiagFaultCnt        = 100u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[145].ucDiagFaultState     = 0u
/// \output Dem_asDiagFaultState[145].unDiagFaultCnt       = 99u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1        = 145u;
  Dem_asDiagFaultState[145].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT;
  Dem_asDiagFaultState[145].unDiagFaultCnt    = 100u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[145].ucDiagFaultState,  0u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[145].unDiagFaultCnt,    99u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour while fault is absent and not confirmed absent and
///           its fault counter reaches minimum value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_Cnt_Param1     = 4u
/// \input Dem_asDiagFaultState[4].ucDiagFaultState = DEM_JDD_FAULT_PRESENT_CONFIRMED
/// \input dem_config[4].condition_confirmed_absent = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[4].ucDiagFaultState = 44u
/// \output Dem_asDiagFaultState[4].unDiagFaultCnt   = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1      = 4u;
  Dem_asDiagFaultState[4].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT_CONFIRMED;
  dem_config[4].condition_confirmed_absent  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[4].ucDiagFaultState,  44u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[4].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour while fault is absent and not confirmed absent and
///           its fault counter reaches minimum value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Pass_Cnt_Param1        = 180u
/// \input Dem_asDiagFaultState[180u].ucDiagFaultState = DEM_JDD_FAULT_PRESENT_CONFIRMED
/// \input dem_config[4].condition_confirmed_absent    = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[180u].ucDiagFaultState = 44u
/// \output Dem_asDiagFaultState[180u].unDiagFaultCnt   = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_6(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1         = 180u;
  Dem_asDiagFaultState[180u].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT_CONFIRMED;
  dem_config[4].condition_confirmed_absent     = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].ucDiagFaultState,  44u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].unDiagFaultCnt,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour while fault is absent and not confirmed absent and
///           its fault counter reaches minimum value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// input Dem_DiagProcessEvent_Pass_Cnt_Param1        = 180u;
/// input Dem_asDiagFaultState[180u].ucDiagFaultState = DEM_JDD_FAULT_PRESENT_CONFIRMED;
/// input dem_config[180u].debounce_cnt_max           = 2u;
/// input dem_config[180u].debounce_cnt_dec           = 1u;
/// input dem_config[180u].debounce_cnt_min           = 0u;
/// input Dem_asDiagFaultState[180u].unDiagFaultCnt   = 5u;

///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[180u].unDiagFaultCnt   = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_7(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Pass_Cnt_Param1       = 1u;
  Dem_asDiagFaultState[1u].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT_CONFIRMED;
  dem_config[1u].debounce_cnt_max            = 2u;
  dem_config[1u].debounce_cnt_dec            = 1u;
  dem_config[1u].debounce_cnt_min            = 0u;
  dem_config[1u].condition_absent            = NULL_PTR;
  Dem_asDiagFaultState[1u].unDiagFaultCnt    = 5u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Pass_Cnt(Dem_DiagProcessEvent_Pass_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1u].unDiagFaultCnt,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test behaviour while fault is absent and not confirmed absent and
///           its fault counter reaches minimum value
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt(void)
{
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_1();
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_2();
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_3();
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_7();
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_4();
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_5();
  Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the fault is marked present and timer is started
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_TimeOut_Param1     = 1u
/// \input  Dem_asDiagFaultState[1].ucDiagFaultState     = 1u
/// \input  Gpt_GetTimeElapsed_HitCount                  = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                 = 100000u
/// \input  Dem_asDiagFaultState[1].ulDiagConfirmedTimer = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[4].ucDiagFaultState = 1u
/// \output Gpt_GetTimeElapsed_HitCount              = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_TimeOut_Param1      = 1u;
  Dem_asDiagFaultState[1].ucDiagFaultState      = 1u;
  LPTMR0_GetTimeElapsed_HitCount                = 0u;
  LPTMR0_GetTimeElapsed_RetVal                  = 100000u;
  Dem_asDiagFaultState[1].ulDiagConfirmedTimer  = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_TimeOut(Dem_DiagProcessEvent_Fail_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test behaviour when fault is marked as present and not confirmed
///                 present and there is time-out on time failed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_TimeOut_Param1  = 4u
/// \input  Dem_asDiagFaultState[4].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT
/// \input  dem_config[4].condition_confirmed_present = NULL_PTR
/// \input  LPTMR0_GetTimeElapsed_HitCount            = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[4].ucDiagFaultState  = DEM_JDD_FAULT_PRESENT
/// \output LPTMR0_GetTimeElapsed_HitCount            = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_TimeOut_Param1   = 3u;
  Dem_asDiagFaultState[3].ucDiagFaultState   = DEM_JDD_FAULT_PRESENT;
  dem_config[3].condition_confirmed_present  = NULL_PTR;
  LPTMR0_GetTimeElapsed_HitCount             = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_TimeOut(Dem_DiagProcessEvent_Fail_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].ucDiagFaultState,  DEM_JDD_FAULT_PRESENT, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the fault is marked present and timer is started
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_TimeOut_Param1       = 1u
/// \input  Dem_asDiagFaultState[1].ulDiagConfirmedTimer   = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                   = 2100000u
/// \input  LPTMR0_GetTimeElapsed_HitCount                 = 0u
/// \input  Dem_asDiagFaultState[1].ucDiagFaultState       = DEM_JDD_FAULT_PRESENT
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState  = 19u
/// \output LPTMR0_GetTimeElapsed_HitCount            = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_TimeOut_Param1      = 1u;
  Dem_asDiagFaultState[1].ulDiagConfirmedTimer  = 0u;
  LPTMR0_GetTimeElapsed_RetVal                  = 2100000u;
  LPTMR0_GetTimeElapsed_HitCount                = 0u;
  Dem_asDiagFaultState[1].ucDiagFaultState      = DEM_JDD_FAULT_PRESENT;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_TimeOut(Dem_DiagProcessEvent_Fail_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  19u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the fault is marked present and timer is started
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_TimeOut_Param1 = 1u
/// \input  Dem_asDiagFaultState[1].ucDiagFaultState = DEM_EVENT_STATUS_PASSED
/// \input  LPTMR0_GetTimeElapsed_HitCount           = 0u
/// \input  dem_config[1].condition_present          = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState = 3u
/// \output LPTMR0_GetTimeElapsed_HitCount           = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_TimeOut_Param1  = 1u;
  Dem_asDiagFaultState[1].ucDiagFaultState  = DEM_EVENT_STATUS_PASSED;
  LPTMR0_GetTimeElapsed_HitCount            = 0u;
  dem_config[1].condition_present           = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_TimeOut(Dem_DiagProcessEvent_Fail_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  3u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the fault is marked present and timer is started
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_TimeOut_Param1        = 180u
/// \input  Dem_asDiagFaultState[180u].ucDiagFaultState     = 1u
/// \input  Gpt_GetTimeElapsed_HitCount                     = 0u
/// \input  LPTMR0_GetTimeElapsed_RetVal                    = 100000u
/// \input  Dem_asDiagFaultState[180u].ulDiagConfirmedTimer = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[180u].ucDiagFaultState = 19u
/// \output LPTMR0_GetTimeElapsed_HitCount              = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_TimeOut_Param1         = 180u;
  Dem_asDiagFaultState[180u].ucDiagFaultState      = 1u;
  LPTMR0_GetTimeElapsed_HitCount                   = 0u;
  LPTMR0_GetTimeElapsed_RetVal                     = 100000u;
  Dem_asDiagFaultState[180u].ulDiagConfirmedTimer  = 0u;
  dem_config[180u].condition_confirmed_present     = NULL_PTR;
  dem_config[180u].debounce_time_failed            = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_TimeOut(Dem_DiagProcessEvent_Fail_TimeOut_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].ucDiagFaultState,  19u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,               1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test if the fault is marked present and timer is started
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut(void)
{
  Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_1();
  Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_2();
  Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_3();
  Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_4();
  Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the fault is marked present and counter is incremented
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1      = 31
/// \input  Dem_asDiagFaultState[31].ucDiagFaultState = 0x08u
/// \input  Dem_asDiagFaultState[31].unDiagFaultCnt   = 10u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[31].ucDiagFaultState = 19u
/// \output Dem_asDiagFaultState[31].unDiagFaultCnt   = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1       = 31;
  Dem_asDiagFaultState[31].ucDiagFaultState  = 0x08u;
  Dem_asDiagFaultState[31].unDiagFaultCnt    = 10u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[31].ucDiagFaultState,  19u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[31].unDiagFaultCnt,     1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1             = 1u
/// \input  Dem_asDiagFaultState[1].ucDiagFaultState         = DEM_STATUS_CONFIRMED_DTC
/// \input  Dem_asDiagFaultState[1].unDiagFaultCnt           = 240u
/// \input  dem_config[1].condition_present                  = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState         = DEM_STATUS_TEST_FAILED
/// \output Dem_asDiagFaultState[1].unDiagFaultCnt           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1      = 1u;
  Dem_asDiagFaultState[1].ucDiagFaultState  = DEM_STATUS_CONFIRMED_DTC;
  Dem_asDiagFaultState[1].unDiagFaultCnt    = 240u;
  dem_config[1].condition_present           = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  DEM_STATUS_TEST_FAILED, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly when fault is present and
///             not confirmed present-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1             = 5u
/// \input  Dem_asDiagFaultState[5].ucDiagFaultState         = DEM_STATUS_CONFIRMED_DTC
/// \input  Dem_asDiagFaultState[5].unDiagFaultCnt           = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[5].ucDiagFaultState         = DEM_STATUS_TEST_FAILED
/// \output Dem_asDiagFaultState[5].unDiagFaultCnt           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1      = 3u;
  Dem_asDiagFaultState[3].ucDiagFaultState  = DEM_STATUS_CONFIRMED_DTC;
  Dem_asDiagFaultState[3].unDiagFaultCnt    = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].ucDiagFaultState,  DEM_STATUS_TEST_FAILED, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly when fault is present and
///             not confirmed present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1             = 5u
/// \input  Dem_asDiagFaultState[5].ucDiagFaultState         = DEM_STATUS_CONFIRMED_DTC
/// \input  Dem_asDiagFaultState[5].unDiagFaultCnt           = 0u
/// \input  dem_config[5].condition_confirmed_present        = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[5].ucDiagFaultState         = DEM_STATUS_TEST_FAILED
/// \output Dem_asDiagFaultState[5].unDiagFaultCnt           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1       = 3u;
  Dem_asDiagFaultState[3].ucDiagFaultState   = DEM_STATUS_CONFIRMED_DTC;
  Dem_asDiagFaultState[3].unDiagFaultCnt     = 0u;
  dem_config[3].condition_confirmed_present  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].ucDiagFaultState,  DEM_STATUS_TEST_FAILED, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly when fault is present and
///             not confirmed present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1             = 5u
/// \input  Dem_asDiagFaultState[5].ucDiagFaultState         = DEM_STATUS_PENDING_DTC
/// \input  Dem_asDiagFaultState[5].unDiagFaultCnt           = 240u
/// \input  dem_config[5].condition_confirmed_present        = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[5].ucDiagFaultState         = 5u
/// \output Dem_asDiagFaultState[5].unDiagFaultCnt           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1       = 5u;
  Dem_asDiagFaultState[5].ucDiagFaultState   = DEM_STATUS_PENDING_DTC;
  Dem_asDiagFaultState[5].unDiagFaultCnt     = 240u;
  dem_config[5].condition_confirmed_present  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[5].ucDiagFaultState,  5u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[5].unDiagFaultCnt,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly when fault is present and
///             not confirmed present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1             = 5u
/// \input  Dem_asDiagFaultState[5].ucDiagFaultState         = DEM_STATUS_PENDING_DTC
/// \input  Dem_asDiagFaultState[5].unDiagFaultCnt           = 240u
/// \input  dem_config[5].condition_confirmed_present        = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[5].ucDiagFaultState         = 5u
/// \output Dem_asDiagFaultState[5].unDiagFaultCnt           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_6(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1       = 3u;
  Dem_asDiagFaultState[3].ucDiagFaultState   = DEM_STATUS_PENDING_DTC;
  Dem_asDiagFaultState[3].unDiagFaultCnt     = 0u;
  dem_config[3].condition_confirmed_present  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].ucDiagFaultState,  5u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[3].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly when fault is present and
///             not confirmed present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Fail_Cnt_Param1                = 180u
/// \input  Dem_asDiagFaultState[180u].ucDiagFaultState         = 0x01u
/// \input  Dem_asDiagFaultState[180u].unDiagFaultCnt           = 240u
/// \input  dem_config[180u].condition_confirmed_present        = NULL_PTR
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[180u].ucDiagFaultState         = 19u
/// \output Dem_asDiagFaultState[180u].unDiagFaultCnt           = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_7(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1          = 180u;
  Dem_asDiagFaultState[180u].ucDiagFaultState   = 0x01u;
  dem_config[180u].debounce_cnt_max             = 0u;
  Dem_asDiagFaultState[180u].unDiagFaultCnt     = 0u;
  dem_config[180u].condition_confirmed_present  = NULL_PTR;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].ucDiagFaultState,  19u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the state is set correctly when fault is present and
///             not confirmed present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_DiagProcessEvent_Fail_Cnt_Param1        = 180u;
/// \input Dem_asDiagFaultState[180u].ucDiagFaultState = 0x08u;
/// \input dem_config[180u].debounce_cnt_max           = 0u;
/// \input dem_config[180u].debounce_cnt_min           = 1u;
/// \input dem_config[180u].debounce_cnt_inc           = 2u;
/// \input Dem_asDiagFaultState[180u].unDiagFaultCnt   = 1u;
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[180u].unDiagFaultCnt         = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_8(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Fail_Cnt_Param1         = 180u;
  Dem_asDiagFaultState[180u].ucDiagFaultState  = 0x08u;
  dem_config[180u].debounce_cnt_max            = 0u;
  dem_config[180u].debounce_cnt_min            = 1u;
  dem_config[180u].debounce_cnt_inc            = 2u;
  Dem_asDiagFaultState[180u].unDiagFaultCnt    = 1u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent_Fail_Cnt(Dem_DiagProcessEvent_Fail_Cnt_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[180u].unDiagFaultCnt,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test if the state is set correctly when fault is present and
///                     not confirmed present
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt(void)
{
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_1();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_2();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_3();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_4();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_5();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_6();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_7();
  Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt_TestCase_8();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the callbacks are set correctly, according to conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Param1               = 1u
/// \input  Dem_DiagProcessEvent_Param2               = DEM_EVENT_STATUS_PASSED
/// \input  Dem_asDiagFaultState[1].ucDiagFaultState  = DEM_STATUS_TEST_PASSED
/// \input  Dem_asDiagFaultState[1].unDiagFaultCnt    = 10u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState  = 132u
/// \output Dem_asDiagFaultState[1].unDiagFaultCnt    = 10u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Param1                                   = 1u;
  Dem_DiagProcessEvent_Param2                                   = DEM_EVENT_STATUS_PASSED;
  Dem_asDiagFaultState[1].ucDiagFaultState                      = DEM_STATUS_TEST_PASSED;
  Dem_asDiagFaultState[1].unDiagFaultCnt                        = 10u;
  dem_config[Dem_DiagProcessEvent_Param1].jdd_reporter          = TRUE;
  dem_config[Dem_DiagProcessEvent_Param1].debounce_time_passed  = 2000u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent(Dem_DiagProcessEvent_Param1, Dem_DiagProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  132u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].unDiagFaultCnt,    10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the callbacks are set correctly, according to conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Param1                = 41u
/// \input  Dem_DiagProcessEvent_Param2                = DEM_EVENT_STATUS_PASSED
/// \input  Dem_asDiagFaultState[41].ucDiagFaultState  = DEM_STATUS_TEST_PASSED
/// \input  Gpt_GetTimeElapsed_HitCount                = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[41].ucDiagFaultState  = DEM_STATUS_TEST_PASSED
/// \output Gpt_GetTimeElapsed_HitCount                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Param1                = 41u;
  Dem_DiagProcessEvent_Param2                = DEM_EVENT_STATUS_PASSED;
  Dem_asDiagFaultState[41].ucDiagFaultState  = DEM_STATUS_TEST_PASSED;
  LPTMR0_GetTimeElapsed_HitCount             = 0u;
  dem_config[41].debounce_time_passed        = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent(Dem_DiagProcessEvent_Param1, Dem_DiagProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[41].ucDiagFaultState,  DEM_STATUS_TEST_PASSED, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,             0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the callbacks are set correctly, according to conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Param1             = 1u
/// \input  Dem_DiagProcessEvent_Param2             = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asDiagFaultState[1].unDiagFaultCnt  = 0u
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[1].ucDiagFaultState = 129u
/// \output Dem_asDiagFaultState[1].unDiagFaultCnt   = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Param1             = 1u;
  Dem_DiagProcessEvent_Param2             = DEM_EVENT_STATUS_FAILED;
  Dem_asDiagFaultState[1].unDiagFaultCnt  = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent(Dem_DiagProcessEvent_Param1, Dem_DiagProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].ucDiagFaultState,  129u, == );
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[1].unDiagFaultCnt,    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the callbacks are set correctly, according to conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Param1               = 35u
/// \input  Dem_DiagProcessEvent_Param2               = DEM_EVENT_STATUS_FAILED
/// \input  LPTMR0_GetTimeElapsed_HitCount            = 0u
/// \input  dem_config[35].jdd_reporter = TRUE;
/// \input  Dem_asDiagFaultState[35].ucDiagFaultState = 0u;
/// 
/// - Expectations:
///
/// \output Dem_asDiagFaultState[35].ucDiagFaultState = 19u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Param1                = 35u;
  Dem_DiagProcessEvent_Param2                = DEM_EVENT_STATUS_FAILED;
  dem_config[35].jdd_reporter                = TRUE;
  Dem_asDiagFaultState[35].ucDiagFaultState  = 0u;

  // Step 3) Call FUT
  Dem_DiagProcessEvent(Dem_DiagProcessEvent_Param1, Dem_DiagProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[35u].ucDiagFaultState,  19u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the callbacks are set correctly, according to conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Param1                = 41u
/// \input  Dem_DiagProcessEvent_Param2                = DEM_EVENT_STATUS_PASSED
/// \input  Dem_asDiagFaultState[41].ucDiagFaultState  = DEM_STATUS_TEST_PASSED
/// \input  dem_config[41].jdd_reporter                = FALSE
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[41].ucDiagFaultState  = DEM_STATUS_TEST_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Param1                = 41u;
  Dem_DiagProcessEvent_Param2                = DEM_EVENT_STATUS_PASSED;
  Dem_asDiagFaultState[41].ucDiagFaultState  = DEM_STATUS_TEST_PASSED;
  dem_config[41].jdd_reporter                = FALSE;

  // Step 3) Call FUT
  Dem_DiagProcessEvent(Dem_DiagProcessEvent_Param1, Dem_DiagProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[41].ucDiagFaultState,  DEM_STATUS_TEST_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the callbacks are set correctly, according to conditions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_DiagProcessEvent_Param1                = 6u
/// \input  Dem_DiagProcessEvent_Param2                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asDiagFaultState[6].ucDiagFaultState   = DEM_STATUS_TEST_PASSED
/// \input  dem_config[6].jdd_reporter                 = FALSE
///
/// - Expectations:
///
/// \output Dem_asDiagFaultState[6].ucDiagFaultState   = DEM_STATUS_TEST_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent_TestCase_6(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_DiagProcessEvent_Param1               = 6u;
  Dem_DiagProcessEvent_Param2               = DEM_EVENT_STATUS_FAILED;
  Dem_asDiagFaultState[6].ucDiagFaultState  = DEM_STATUS_TEST_PASSED;
  dem_config[6].jdd_reporter                = FALSE;

  // Step 3) Call FUT
  Dem_DiagProcessEvent(Dem_DiagProcessEvent_Param1, Dem_DiagProcessEvent_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asDiagFaultState[6].ucDiagFaultState,  DEM_STATUS_TEST_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_DiagProcessEvent
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test if the callbacks are set correctly, according to conditions
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_DiagProcessEvent(void)
{
  Mt_Dem_Dem_DiagProcessEvent_TestCase_1();
  Mt_Dem_Dem_DiagProcessEvent_TestCase_2();
  Mt_Dem_Dem_DiagProcessEvent_TestCase_3();
  Mt_Dem_Dem_DiagProcessEvent_TestCase_4();
  Mt_Dem_Dem_DiagProcessEvent_TestCase_5();
  Mt_Dem_Dem_DiagProcessEvent_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_Param1                   = 1u
/// \input  Dem_SetEventStatus_Param2                   = 1u
/// \input  Dem_boInitializationDone                    = TRUE
/// \input  EAPI_GetCurrentEIMode_RetVal                = LEIM_E_INACTIVE
/// \input  Dem_ucSideModifier                          = 2u
/// \input  SysMon_RxCallbacks_GetDiagMuxState_HitCount = 0
/// \input  SysMon_RxCallbacks_GetDiagMuxState_Param1   = TRUE
/// \input  Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_PASSED
///
/// - Expectations:
///
/// \output SysMon_RxCallbacks_GetDiagMuxState_HitCount = 1u
/// \output Dem_asStatusTest[1].boDoneThisCycle         = 0u
/// \output Dem_asStatusTest[1].ucResult                = 0x02u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1                    = 1u;
  Dem_SetEventStatus_Param2                    = 1u;
  Dem_boInitializationDone                     = TRUE;
  EAPI_GetCurrentEIMode_RetVal                 = LEIM_E_INACTIVE;
  Dem_ucSideModifier                           = 2u;
  SysMonRx_Callbacks_GetDiagMuxState_HitCount  = 0;
  SysMonRx_Callbacks_GetDiagMuxState_Param1    = TRUE;
  Dem_asStatusTest[1].ucResult                 = DEM_EVENT_STATUS_PASSED;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(SysMonRx_Callbacks_GetDiagMuxState_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,          0u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].ucResult,                 0x02u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1                   = 1u
/// \input Dem_SetEventStatus_Param2                   = 1u
/// \input Dem_boInitializationDone                    = TRUE
/// \input EAPI_GetCurrentEIMode_RetVal                = LEIM_E_INACTIVE
/// \input Dem_ucSideModifier                          = 2u
/// \input SysMon_RxCallbacks_GetDiagMuxState_HitCount = 0
/// \input SysMon_RxCallbacks_GetDiagMuxState_Param1   = TRUE
/// \input Dem_asStatusTest[1].boDoneThisCycle         = FALSE
/// \input Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_PASSED
/// \input Dem_astEventStatus[1].unStatus              = 1u
/// \input NvmBlockDemData.aucStatus[1]                = 17u
///
/// - Expectations:
///
/// \output Dem_astEventStatus[1].unStatus       = 1u
/// \output Dem_asStatusTest[1].boDoneThisCycle  = 0u
/// \output NvmBlockDemData.aucStatus[1]         = 17u
/// \output Dem_boNvmDirty                       = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1                    = 1u;
  Dem_SetEventStatus_Param2                    = 1u;
  Dem_boInitializationDone                     = TRUE;
  EAPI_GetCurrentEIMode_RetVal                 = LEIM_E_INACTIVE;
  Dem_ucSideModifier                           = 2u;
  SysMonRx_Callbacks_GetDiagMuxState_HitCount  = 0;
  SysMonRx_Callbacks_GetDiagMuxState_Param1    = TRUE;
  Dem_asStatusTest[1].boDoneThisCycle          = FALSE;
  Dem_asStatusTest[1].ucResult                 = DEM_EVENT_STATUS_PASSED;
  Dem_astEventStatus[1].unStatus               = 1u;
  NvmBlockDemData.aucStatus[1]                 = 17u;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       1u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  0u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucStatus[1],         17u, == );
  AL_UNITTEST_CHECK(Dem_boNvmDirty,                       TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1             = 1u
/// \input Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_PASSED_IMMEDIATELY
/// \input Dem_boInitializationDone              = TRUE
/// \input Dem_ucSideModifier                    = 2u
/// \input Dem_asStatusTest[1].boDoneThisCycle   = FALSE
/// \input Dem_asStatusTest[1].ucResult          = DEM_EVENT_STATUS_PASSED_IMMEDIATELY
///
/// - Expectations:
///
/// \output Dem_astEventStatus[1].unStatus        = 1u
/// \output Dem_asStatusTest[1].boDoneThisCycle   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_3(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1            = 1u;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED_IMMEDIATELY;
  Dem_boInitializationDone             = TRUE;
  Dem_ucSideModifier                   = 2u;
  Dem_asStatusTest[1].boDoneThisCycle  = FALSE;
  Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED_IMMEDIATELY;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       1u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1             = 1u
/// \input Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_PASSED
/// \input Dem_boInitializationDone              = TRUE
/// \input Dem_ucSideModifier                    = 2u
/// \input Dem_asStatusTest[1].boDoneThisCycle   = FALSE
/// \input Dem_asStatusTest[1].ucResult          = DEM_EVENT_STATUS_PASSED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[1].unStatus        = 640u
/// \output Dem_asStatusTest[1].boDoneThisCycle   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_4(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1            = 1u;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Dem_boInitializationDone             = TRUE;
  Dem_ucSideModifier                   = 2u;
  Dem_asStatusTest[1].boDoneThisCycle  = FALSE;
  Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       640u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1            = 1u
/// \input Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED
/// \input Dem_boInitializationDone             = TRUE
/// \input Dem_ucSideModifier                   = 2u
/// \input Dem_asStatusTest[1].boDoneThisCycle  = TRUE
/// \input Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[1].unStatus      = 640u
/// \output Dem_asStatusTest[1].boDoneThisCycle = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_5(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1            = 1u;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Dem_boInitializationDone             = TRUE;
  Dem_ucSideModifier                   = 2u;
  Dem_asStatusTest[1].boDoneThisCycle  = TRUE;
  Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       640u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1             = 1u
/// \input Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_PASSED
/// \input Dem_boInitializationDone              = TRUE
/// \input Dem_ucSideModifier                    = 2u
/// \input Dem_asStatusTest[1].boDoneThisCycle   = FALSE
/// \input Dem_asStatusTest[1].ucResult          = DEM_EVENT_STATUS_PASSED
/// \input NvmBlockDemData.aucStatus[1]          = DEM_STATUS_TEST_PASSED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[1].unStatus        = 640u
/// \output Dem_asStatusTest[1].boDoneThisCycle   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_6(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1            = 1u;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Dem_boInitializationDone             = TRUE;
  Dem_ucSideModifier                   = 2u;
  Dem_asStatusTest[1].boDoneThisCycle  = FALSE;
  Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED;
  NvmBlockDemData.aucStatus[1]         = DEM_STATUS_TEST_PASSED;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       640u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1             = 1u
/// \input Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_PASSED
/// \input Dem_boInitializationDone              = TRUE
/// \input Dem_ucSideModifier                    = 2u
/// \input Dem_asStatusTest[1].boDoneThisCycle   = FALSE
/// \input Dem_asStatusTest[1].ucResult          = DEM_EVENT_STATUS_PASSED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[1].unStatus        = 640u
/// \output Dem_asStatusTest[1].boDoneThisCycle   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_7(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1            = 1u;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Dem_boInitializationDone             = TRUE;
  Dem_ucSideModifier                   = 2u;
  Dem_asStatusTest[1].boDoneThisCycle  = FALSE;
  Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED;
  EAPI_GetCurrentEIMode_RetVal         = 0u;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       640u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1            = 1u
/// \input Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED
/// \input Dem_boInitializationDone             = TRUE
/// \input Dem_ucSideModifier                   = 2u
/// \input Dem_asStatusTest[1].boDoneThisCycle  = TRUE
/// \input Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_PASSED
/// \input EAPI_GetCurrentEIMode_RetVal         = 1u
///
/// - Expectations:
///
/// \output Dem_asStatusTest[1].boDoneThisCycle = TRUE
/// \output Dem_asStatusTest[1].ucResult        = DEM_EVENT_STATUS_PASSED
/// \output Dem_astEventStatus[1].unStatus      = 640u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_8(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1            = 1u;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Dem_boInitializationDone             = TRUE;
  Dem_ucSideModifier                   = 2u;
  Dem_asStatusTest[1].boDoneThisCycle  = TRUE;
  Dem_asStatusTest[1].ucResult         = DEM_EVENT_STATUS_FAILED;
  EAPI_GetCurrentEIMode_RetVal         = 1u;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].boDoneThisCycle,  TRUE, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].ucResult,         DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,       640u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if event status is set correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1                                   = 1u
/// \input Dem_SetEventStatus_Param2                                   = DEM_EVENT_STATUS_PASSED
/// \input Dem_boInitializationDone                                    = TRUE
/// \input Dem_ucSideModifier                                          = 10u
/// \input Dem_asStatusTest[Dem_SetEventStatus_Param1].ucResult        = DEM_EVENT_STATUS_FAILED;
/// \input Dem_asStatusTest[Dem_SetEventStatus_Param1].boDoneThisCycle = FALSE;
/// \input NM_GetMode_HitCount                                         = 0u;
///
/// - Expectations:
///
/// \output NM_GetMode_HitCount                                         = 1u
/// \output Dem_asStatusTest[Dem_SetEventStatus_Param1].boDoneThisCycle = TRUE
/// \output Dem_asStatusTest[Dem_SetEventStatus_Param1].ucResult        = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus_TestCase_9(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_SetEventStatus_Param1                                    = HS6_COMMANDES_VSM_036_ID;
  Dem_SetEventStatus_Param2                                    = DEM_EVENT_STATUS_PASSED;
  NM_GetMode_Param1                                            = LIMP_HOME_MODE;
  Dem_ucSideModifier                                           = 10u;
  Dem_asStatusTest[Dem_SetEventStatus_Param1].ucResult         = DEM_EVENT_STATUS_FAILED;
  Dem_asStatusTest[Dem_SetEventStatus_Param1].boDoneThisCycle  = FALSE;
  NM_GetMode_HitCount                                          = 0u;

  // Step 3) Call FUT
  Dem_SetEventStatus(Dem_SetEventStatus_Param1, Dem_SetEventStatus_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(NM_GetMode_HitCount,                                          1u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[Dem_SetEventStatus_Param1].boDoneThisCycle,  TRUE, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[Dem_SetEventStatus_Param1].ucResult,         DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_SetEventStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test if event status is set correctly
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_SetEventStatus(void)
{
  Mt_Dem_Dem_SetEventStatus_TestCase_1();
  Mt_Dem_Dem_SetEventStatus_TestCase_2();
  Mt_Dem_Dem_SetEventStatus_TestCase_3();
  Mt_Dem_Dem_SetEventStatus_TestCase_4();
  Mt_Dem_Dem_SetEventStatus_TestCase_5();
  Mt_Dem_Dem_SetEventStatus_TestCase_6();
  Mt_Dem_Dem_SetEventStatus_TestCase_7();
  Mt_Dem_Dem_SetEventStatus_TestCase_8();
  Mt_Dem_Dem_SetEventStatus_TestCase_9();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_boEventPassed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks if the Alec Id (unEventIdx + 1) given as parameter was passed or not
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boEventPassed_Param1        = 1u
/// \input Dem_astEventStatus[1].unStatus  = 0xCA
/// \input Dem_boEventPassed_RetVal        = FALSE
///
/// - Expectations:
///
/// \output Dem_boEventPassed_RetVal        = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_boEventPassed_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boEventPassed_Param1        = 1u;
  Dem_astEventStatus[1].unStatus  = 0xCA;
  Dem_boEventPassed_RetVal        = FALSE;

  // Step 3) Call FUT
  Dem_boEventPassed_RetVal = Dem_boEventPassed(Dem_boEventPassed_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boEventPassed_RetVal,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_boEventPassed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function checks if the Alec Id (unEventIdx + 1) given as parameter was passed or not
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_boEventPassed_Param1        = 1u
/// \input Dem_astEventStatus[1].unStatus  = 0u
/// \input Dem_boEventPassed_RetVal        = TRUE
///
/// - Expectations:
///
/// \output Dem_boEventPassed_RetVal        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_boEventPassed_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boEventPassed_Param1        = 1u;
  Dem_astEventStatus[1].unStatus  = 0u;
  Dem_boEventPassed_RetVal        = TRUE;

  // Step 3) Call FUT
  Dem_boEventPassed_RetVal = Dem_boEventPassed(Dem_boEventPassed_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boEventPassed_RetVal,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_boEventPassed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test if function checks if the Alec Id (unEventIdx + 1) given as parameter was passed or not
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_boEventPassed(void)
{
  Mt_Dem_Dem_boEventPassed_TestCase_1();
  Mt_Dem_Dem_boEventPassed_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ClearAlec_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function clears all ALECs corresponding with dem
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_ClearAlec_Param1                        = TRUE
/// \input  Dem_ClearAlec_Param2                        = 1u
/// \input  Dem_astEventStatus[0].ulDebounceStartTime   = 6u
/// \input  Dem_astEventStatus[0].unStatus              = DEM_EVENT_STATUS_FAILED
/// \input  NvmBlockDemData.aucAgingCounter[0]          = 6u
/// \input  NvmBlockDemData.aucStatus[0]                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asStatusTest[0].ucResult                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_astEventStatus[1].ulDebounceStartTime   = 6u
/// \input  Dem_astEventStatus[1].unStatus              = DEM_EVENT_STATUS_FAILED
/// \input  NvmBlockDemData.aucAgingCounter[1]          = 6u
/// \input  NvmBlockDemData.aucStatus[1]                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_FAILED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[0].ulDebounceStartTime   = 0u
/// \output Dem_astEventStatus[0].unStatus              = 208u
/// \output NvmBlockDemData.aucAgingCounter[0]          = 0u
/// \output NvmBlockDemData.aucStatus[0]                = 208u
/// \output Dem_asStatusTest[0].ucResult                = DEM_EVENT_STATUS_PASSED
/// \output Dem_astEventStatus[1].ulDebounceStartTime   = 0u
/// \output Dem_astEventStatus[1].unStatus              = 208u
/// \output NvmBlockDemData.aucAgingCounter[1]          = 0u
/// \output NvmBlockDemData.aucStatus[1]                = 208u
/// \output Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ClearAlec_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ClearAlec_Param1                       = TRUE;
  Dem_ClearAlec_Param2                       = 1u;
  Dem_astEventStatus[0].ulDebounceStartTime  = 6u;
  Dem_astEventStatus[0].unStatus             = DEM_EVENT_STATUS_FAILED;
  NvmBlockDemData.aucAgingCounter[0]         = 6u;
  NvmBlockDemData.aucStatus[0]               = DEM_EVENT_STATUS_FAILED;
  Dem_asStatusTest[0].ucResult               = DEM_EVENT_STATUS_FAILED;
  Dem_astEventStatus[1].ulDebounceStartTime  = 6u;
  Dem_astEventStatus[1].unStatus             = DEM_EVENT_STATUS_FAILED;
  NvmBlockDemData.aucAgingCounter[1]         = 6u;
  NvmBlockDemData.aucStatus[1]               = DEM_EVENT_STATUS_FAILED;
  Dem_asStatusTest[1].ucResult               = DEM_EVENT_STATUS_FAILED;

  // Step 3) Call FUT
  Dem_ClearAlec(Dem_ClearAlec_Param1, Dem_ClearAlec_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].ulDebounceStartTime,  0, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,             208u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[0],         0u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucStatus[0],               208u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[0].ucResult,               DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].ulDebounceStartTime,  0, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,             208u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[1],         0u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucStatus[1],               208u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].ucResult,               DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ClearAlec_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function clears all ALECs corresponding with dem
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_ClearAlec_Param1                        = FALSE
/// \input  Dem_ClearAlec_Param2                        = 1u
/// \input  Dem_astEventStatus[0].ulDebounceStartTime   = 6u
/// \input  Dem_astEventStatus[0].unStatus              = DEM_EVENT_STATUS_FAILED
/// \input  NvmBlockDemData.aucAgingCounter[0]          = 6u
/// \input  NvmBlockDemData.aucStatus[0]                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asStatusTest[0].ucResult                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_astEventStatus[1].ulDebounceStartTime   = 6u
/// \input  Dem_astEventStatus[1].unStatus              = DEM_EVENT_STATUS_FAILED
/// \input  NvmBlockDemData.aucAgingCounter[1]          = 6u
/// \input  NvmBlockDemData.aucStatus[1]                = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_FAILED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[0].ulDebounceStartTime   = 6u
/// \output Dem_astEventStatus[0].unStatus              = DEM_EVENT_STATUS_FAILED
/// \output NvmBlockDemData.aucAgingCounter[0]          = 6u
/// \output NvmBlockDemData.aucStatus[0]                = DEM_EVENT_STATUS_FAILED
/// \output Dem_asStatusTest[0].ucResult                = DEM_EVENT_STATUS_FAILED
/// \output Dem_astEventStatus[1].ulDebounceStartTime   = 0u
/// \output Dem_astEventStatus[1].unStatus              = 208u
/// \output NvmBlockDemData.aucAgingCounter[1]          = 0u
/// \output NvmBlockDemData.aucStatus[1]                = 208u
/// \output Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ClearAlec_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ClearAlec_Param1                        = FALSE;
  Dem_ClearAlec_Param2                        = 1u;
  Dem_astEventStatus[0].ulDebounceStartTime   = 6u;
  Dem_astEventStatus[0].unStatus              = DEM_EVENT_STATUS_FAILED;
  NvmBlockDemData.aucAgingCounter[0]          = 6u;
  NvmBlockDemData.aucStatus[0]                = DEM_EVENT_STATUS_FAILED;
  Dem_asStatusTest[0].ucResult                = DEM_EVENT_STATUS_FAILED;
  Dem_astEventStatus[1].ulDebounceStartTime   = 6u;
  Dem_astEventStatus[1].unStatus              = DEM_EVENT_STATUS_FAILED;
  NvmBlockDemData.aucAgingCounter[1]          = 6u;
  NvmBlockDemData.aucStatus[1]                = DEM_EVENT_STATUS_FAILED;
  Dem_asStatusTest[1].ucResult                = DEM_EVENT_STATUS_FAILED;

  // Step 3) Call FUT
  Dem_ClearAlec(Dem_ClearAlec_Param1, Dem_ClearAlec_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].ulDebounceStartTime,  6u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,             DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[0],         6u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucStatus[0],               DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[0].ucResult,               DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].ulDebounceStartTime,  0, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[1].unStatus,             208u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[1],         0u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucStatus[1],               208u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[1].ucResult,               DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ClearAlec
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test if function checks if the Alec Id (unEventIdx + 1) given as parameter was passed or not
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ClearAlec(void)
{
  Mt_Dem_Dem_ClearAlec_TestCase_1();
  Mt_Dem_Dem_ClearAlec_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ResetArrays
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function resets all arrays which are used by Dem at their initial values
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_ResetArrays_Param1                    = 0u
/// \input  Dem_astEventStatus[0].ulDebounceStartTime = 6u
/// \input  Dem_astEventStatus[0].unStatus            = DEM_EVENT_STATUS_FAILED
/// \input  NvmBlockDemData.aucAgingCounter[0]        = 6u
/// \input  NvmBlockDemData.aucStatus[0]              = DEM_EVENT_STATUS_FAILED
/// \input  Dem_asStatusTest[0].ucResult              = DEM_EVENT_STATUS_FAILED
///
/// - Expectations:
///
/// \output Dem_astEventStatus[0].ulDebounceStartTime = 0u
/// \output Dem_astEventStatus[0].unStatus            = 208u
/// \output NvmBlockDemData.aucAgingCounter[0]        = 0u
/// \output NvmBlockDemData.aucStatus[0]              = 208u
/// \output Dem_asStatusTest[0].ucResult              = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ResetArrays(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_ResetArrays_Param1 = 0u;
  Dem_astEventStatus[0].ulDebounceStartTime  = 6u;
  Dem_astEventStatus[0].unStatus             = DEM_EVENT_STATUS_FAILED;
  NvmBlockDemData.aucAgingCounter[0]         = 6u;
  NvmBlockDemData.aucStatus[0]               = DEM_EVENT_STATUS_FAILED;
  Dem_asStatusTest[0].ucResult               = DEM_EVENT_STATUS_FAILED;

  // Step 3) Call FUT
  Dem_ResetArrays(Dem_ResetArrays_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].ulDebounceStartTime,  0u, == );
  AL_UNITTEST_CHECK(Dem_astEventStatus[0].unStatus,             208u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucAgingCounter[0],         0u, == );
  AL_UNITTEST_CHECK(NvmBlockDemData.aucStatus[0],               208u, == );
  AL_UNITTEST_CHECK(Dem_asStatusTest[0].ucResult,               DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_ClearStartUpStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if startup flag is cleared
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_boStartupStat = TRUE
///
/// - Expectations:
///
/// \output Dem_boStartupStat = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_ClearStartUpStatus(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_boStartupStat  = TRUE;

  // Step 3) Call FUT
  Dem_ClearStartUpStatus();

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boStartupStat,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_350Lost_NotifyPassed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if frame 350 is notified as not present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_DEM_350Lost_NotifyStatus_Param1   = TRUE
/// \input  Rte_Write_DEM_350Lost_NotifyStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Write_DEM_350Lost_NotifyStatus_Param1   = FALSE
/// \output Rte_Write_DEM_350Lost_NotifyStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Custom_350Lost_NotifyPassed(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Rte_Write_DEM_350Lost_NotifyStatus_Param1    = TRUE;
  Rte_Write_DEM_350Lost_NotifyStatus_HitCount  = 0u;

  // Step 3) Call FUT
  Dem_Custom_350Lost_NotifyPassed(Dem_Custom_350Lost_NotifyPassed_Param1, Dem_Custom_350Lost_NotifyPassed_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_DEM_350Lost_NotifyStatus_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_DEM_350Lost_NotifyStatus_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_350Lost_NotifyFailed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if frame 350 is notified as present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_DEM_350Lost_NotifyStatus_Param1   = FALSE
/// \input  Rte_Write_DEM_350Lost_NotifyStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Write_DEM_350Lost_NotifyStatus_Param1   = TRUE
/// \output Rte_Write_DEM_350Lost_NotifyStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Custom_350Lost_NotifyFailed(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Rte_Write_DEM_350Lost_NotifyStatus_Param1    = FALSE;
  Rte_Write_DEM_350Lost_NotifyStatus_HitCount  = 0u;

  // Step 3) Call FUT
  Dem_Custom_350Lost_NotifyFailed(Dem_Custom_350Lost_NotifyFailed_Param1, Dem_Custom_350Lost_NotifyFailed_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_DEM_350Lost_NotifyStatus_Param1,    TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_DEM_350Lost_NotifyStatus_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_OV_NotifyPassed
///
/// \Functional Safety: NA

/// \Test Case Description
///        - Test subject: Test if OV is notified as not present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_DEM_OV_NotifyStatus_Param1   = TRUE
/// \input  Rte_Write_DEM_OV_NotifyStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Write_DEM_OV_NotifyStatus_Param1   = FALSE
/// \output Rte_Write_DEM_OV_NotifyStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Custom_OV_NotifyPassed(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Rte_Write_DEM_OV_NotifyStatus_Param1    = TRUE;
  Rte_Write_DEM_OV_NotifyStatus_HitCount  = 0u;

  // Step 3) Call FUT
  Dem_Custom_OV_NotifyPassed(Dem_Custom_OV_NotifyPassed_Param1, Dem_Custom_OV_NotifyPassed_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_DEM_OV_NotifyStatus_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_DEM_OV_NotifyStatus_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_OV_NotifyFailed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if OV is notified as present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_DEM_OV_NotifyStatus_Param1   = FALSE
/// \input  Rte_Write_DEM_OV_NotifyStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Write_DEM_OV_NotifyStatus_Param1   = TRUE
/// \output Rte_Write_DEM_OV_NotifyStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Custom_OV_NotifyFailed(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Rte_Write_DEM_OV_NotifyStatus_Param1    = FALSE;
  Rte_Write_DEM_OV_NotifyStatus_HitCount  = 0u;

  // Step 3) Call FUT
  Dem_Custom_OV_NotifyFailed(Dem_Custom_OV_NotifyFailed_Param1, Dem_Custom_OV_NotifyFailed_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_DEM_OV_NotifyStatus_Param1,    TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_DEM_OV_NotifyStatus_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_UV_NotifyPassed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if UV is notified as not present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_DEM_UV_NotifyStatus_Param1   = TRUE
/// \input  Rte_Write_DEM_UV_NotifyStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Write_DEM_UV_NotifyStatus_Param1   = FALSE
/// \output Rte_Write_DEM_UV_NotifyStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Custom_UV_NotifyPassed(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Rte_Write_DEM_UV_NotifyStatus_Param1    = TRUE;
  Rte_Write_DEM_UV_NotifyStatus_HitCount  = 0u;

  // Step 3) Call FUT
  Dem_Custom_UV_NotifyPassed(Dem_Custom_UV_NotifyPassed_Param1, Dem_Custom_UV_NotifyPassed_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_DEM_UV_NotifyStatus_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_DEM_UV_NotifyStatus_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_UV_NotifyFailed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if UV is notified as present
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_DEM_UV_NotifyStatus_Param1   = FALSE
/// \input  Rte_Write_DEM_UV_NotifyStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output Rte_Write_DEM_UV_NotifyStatus_Param1   = TRUE
/// \output Rte_Write_DEM_UV_NotifyStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Custom_UV_NotifyFailed(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Rte_Write_DEM_UV_NotifyStatus_Param1    = FALSE;
  Rte_Write_DEM_UV_NotifyStatus_HitCount  = 0u;

  // Step 3) Call FUT
  Dem_Custom_UV_NotifyFailed(Dem_Custom_UV_NotifyFailed_Param1, Dem_Custom_UV_NotifyFailed_Param2);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_DEM_UV_NotifyStatus_Param1,    TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_DEM_UV_NotifyStatus_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_UV_NotifyFailed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function disables stroing DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_Diag_LockDTC_Param1 = FALSE
/// \input  LockDTC                 = TRUE
///
/// - Expectations:
///
/// \output LockDTC                 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Diag_LockDTC_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_Diag_LockDTC_Param1  = FALSE;
  LockDTC                  = TRUE;

  // Step 3) Call FUT
  Dem_Diag_LockDTC(Dem_Diag_LockDTC_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(LockDTC,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Custom_UV_NotifyFailed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function enables stroing DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_Diag_LockDTC_Param1 = TRUE
/// \input  LockDTC                 = FALSE
///
/// - Expectations:
///
/// \output LockDTC                 = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Diag_LockDTC_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_Diag_LockDTC_Param1  = TRUE;
  LockDTC                  = FALSE;

  // Step 3) Call FUT
  Dem_Diag_LockDTC(Dem_Diag_LockDTC_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(LockDTC,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Diag_LockDTC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function monitors the fault during DiagMuxOn and
///         set callbacks for first events of absent/present and for conditions of confirmed absent/present
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Diag_LockDTC(void)
{
  Mt_Dem_Dem_Diag_LockDTC_TestCase_1();
  Mt_Dem_Dem_Diag_LockDTC_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Set_Init_Window_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test Cycle function for open/close diagnostic window
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_Set_Init_Window_Param1  = FALSE
/// \input  Dem_boInitEvent             = TRUE
///
/// - Expectations:
///
/// \output   Dem_boInitEvent = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Set_Init_Window_TestCase_1(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_Set_Init_Window_Param1  = FALSE;
  Dem_boInitEvent             = TRUE;

  // Step 3) Call FUT
  Dem_Set_Init_Window(Dem_Set_Init_Window_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitEvent,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Set_Init_Window_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test Cycle function for open/close diagnostic window
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Dem_Set_Init_Window_Param1  = TRUE
/// \input  Dem_boInitEvent             = FALSE
///
/// - Expectations:
///
/// \output   Dem_boInitEvent = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Set_Init_Window_TestCase_2(void)
{
  // Step 1) Set Preconditions 
  // Step 2) Assign Input values
  Dem_Set_Init_Window_Param1  = TRUE;
  Dem_boInitEvent             = FALSE;

  // Step 3) Call FUT
  Dem_Set_Init_Window(Dem_Set_Init_Window_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_boInitEvent,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dem_Dem_Set_Init_Window
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test Cycle function for open/close diagnostic window
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Dem_Dem_Set_Init_Window(void)
{
  Mt_Dem_Dem_Set_Init_Window_TestCase_1();
  Mt_Dem_Dem_Set_Init_Window_TestCase_2();
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
  // ctaaDem.c 
  ALUnitTest_AddFunction("Mt_Dem_riDem_Init", Mt_Dem_riDem_Init);
  ALUnitTest_AddFunction("Mt_Dem_rpDem_Cycle0", Mt_Dem_rpDem_Cycle0);

  // Dem.c
  ALUnitTest_AddFunction("Mt_Dem_Dem_Init", Mt_Dem_Dem_Init);
  ALUnitTest_AddFunction("Mt_Dem_Dem_ClearStartUpStatus", Mt_Dem_Dem_ClearStartUpStatus);
  ALUnitTest_AddFunction("Mt_Dem_Dem_ResetArrays", Mt_Dem_Dem_ResetArrays);
  ALUnitTest_AddFunction("Mt_Dem_Dem_ClearAlec", Mt_Dem_Dem_ClearAlec);
  ALUnitTest_AddFunction("Mt_Dem_Dem_boEventPassed", Mt_Dem_Dem_boEventPassed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_SetEventStatus", Mt_Dem_Dem_SetEventStatus);
  ALUnitTest_AddFunction("Mt_Dem_Dem_DiagProcessEvent", Mt_Dem_Dem_DiagProcessEvent);
  ALUnitTest_AddFunction("Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt", Mt_Dem_Dem_DiagProcessEvent_Fail_Cnt);
  ALUnitTest_AddFunction("Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut", Mt_Dem_Dem_DiagProcessEvent_Fail_TimeOut);
  ALUnitTest_AddFunction("Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt", Mt_Dem_Dem_DiagProcessEvent_Pass_Cnt);
  ALUnitTest_AddFunction("Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut", Mt_Dem_Dem_DiagProcessEvent_Pass_TimeOut);
  ALUnitTest_AddFunction("Mt_Dem_Dem_PreProcessEvent", Mt_Dem_Dem_PreProcessEvent);
  ALUnitTest_AddFunction("Mt_Dem_Dem_ProcessEvent", Mt_Dem_Dem_ProcessEvent);
  ALUnitTest_AddFunction("Mt_Dem_Dem_TriggerCallbackFunctions", Mt_Dem_Dem_TriggerCallbackFunctions);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Task", Mt_Dem_Dem_Task);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Custom_350Lost_NotifyPassed", Mt_Dem_Dem_Custom_350Lost_NotifyPassed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Custom_350Lost_NotifyFailed", Mt_Dem_Dem_Custom_350Lost_NotifyFailed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Custom_OV_NotifyPassed", Mt_Dem_Dem_Custom_OV_NotifyPassed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Custom_OV_NotifyFailed", Mt_Dem_Dem_Custom_OV_NotifyFailed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Custom_UV_NotifyPassed", Mt_Dem_Dem_Custom_UV_NotifyPassed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Custom_UV_NotifyFailed", Mt_Dem_Dem_Custom_UV_NotifyFailed);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Diag_LockDTC", Mt_Dem_Dem_Diag_LockDTC);
  ALUnitTest_AddFunction("Mt_Dem_Dem_Set_Init_Window", Mt_Dem_Dem_Set_Init_Window);
}


// EOF

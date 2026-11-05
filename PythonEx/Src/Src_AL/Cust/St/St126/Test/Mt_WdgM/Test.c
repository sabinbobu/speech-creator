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
/// \brief  Unit Test Cases for WdgM module
///
/// \author 
///         
//-----------------------------------------------------------------------------

//=============================================================================
//  Files covered by this module unit test:
//            - ctscWdgm.c
//            - WdgM.c
//            
//=============================================================================

//=============================================================================
// Includes
//=============================================================================
// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"


//-----------------------------------------------------------------------------
//  Module Test Cases
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_riWdgM_Init
///
/// \Test Case Description
///    - Test subject:  Check the function initializing the watch dog timer
///
/// \FuSa Relevant: -
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// - Preconditions: 
///
/// \input: WdgM_ResetHookActivation = 20212022u
///
/// - Expectations:
///
/// \output: WdgM_ResetHookActivation = 20212022u (init does nothing)
///
//-----------------------------------------------------------------------------
void Mt_riWdgM_Init(void)
{
	//Step 1: Set pre-conditions
  boFirstCallWdgCycleStatus = TRUE;
  WdgM_ResetHookActivation = 20212022u;

	//Step 2) Assign Input values
  //--
	
	//Step 3) Call FUT
	riWdgM_Init();

	//Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_ResetHookActivation, 20212022u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpWdgM_Cycle0
///
/// \Test Case Description
///    - Test subject:  Check the function WdgM cyclic runnable
///
/// \FuSa Relevant: -
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// - Preconditions:
///
/// \input: WdgM_ResetHookActivation = 20212022u
///
/// - Expectations:
///
/// \output: WdgM_ResetHookActivation = 0u
///
//-----------------------------------------------------------------------------
void Mt_rpWdgM_Cycle0(void)
{
	//Step 1: Set pre-conditions
  WdgM_ResetHookActivation = 20212022;

	//Step 2) Assign Input values
  //--
	
	//Step 3) Call FUT
	rpWdgM_Cycle0();

	//Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_ResetHookActivation, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_SetLocalCheckPoint
///
/// \Test Case Description
///    - Test subject:  Check the function updating the checkpoint counter
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.519, LDM.MDRS_WDGM.605, LDM.MDRS_WDGM.610
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// - Preconditions:
///
/// \input ucId = 0u
/// \input WdgM_SetLocalCheckPoint_Param1 = 0u
/// \input WdgM_asCheckPointsList[ucId].uctHitCount = 1u
///
/// - Expectations:
/// \output WdgM_asCheckPointsList[ucId].uctHitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_SetLocalCheckPoint(void)
{
	//Step 1: Set pre-conditions
  WdgM_asCheckPointsList[0u].uctHitCount = 1u;
  
	//Step 2) Assign Input values
  WdgM_SetLocalCheckPoint_Param1 = 0u;

	//Step 3) Call FUT
	WdgM_SetLocalCheckPoint(WdgM_SetLocalCheckPoint_Param1);

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[0u].uctHitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Init
///
/// \Test Case Description
///    - Test subject:  Check the function Wdg manager init runnable
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.537, LDM.MDRS_WDGM.599
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// - Preconditions: 
///
/// \input: WdgM_ResetHookActivation = 20212022u
///
/// - Expectations:
///
/// \output: WdgM_ResetHookActivation = 20212022u (init does nothing)
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Init(void)
{
	//Step 1: Set pre-conditions
  WdgM_ResetHookActivation = 20212022u;

	//Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_Init();

	//Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_ResetHookActivation, 20212022u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Cycle0_TestCase1
///
/// \Test Case Description
///    - Test subject:  Check that the function does watch dog reset when the coding parameters are correct
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.533, LDM.MDRS_WDGM.600, LDM.MDRS_WDGM.625
///
/// - Preconditions:
///
/// \input: WdgM_ResetHookActivation  = 20212022u
/// \input: WdgM_boTriggerStatus      = TRUE
///
/// - Expectations:
///
/// \output: WdgM_ResetHookActivation = 0u
/// \output: WdgM_boTriggerStatus     = FALSE
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Cycle0_TestCase1(void)
{
	//Step 1: Set pre-conditions
  WdgM_ResetHookActivation = 20212022;
  WdgM_boTriggerStatus = TRUE;
	
	//Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_Cycle0();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_ResetHookActivation, 0, == );
  AL_UNITTEST_CHECK(WdgM_boTriggerStatus, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Cycle0_TestCase2
///
/// \Test Case Description
///    - Test subject:  Check that the function skips the watch dog reset when the coding parameters are Incorrect
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.533, LDM.MDRS_WDGM.600, LDM.MDRS_WDGM.625
///
/// - Preconditions:
///
/// \input: WdgM_ResetHookActivation  = 20212023u
/// \input: WdgM_boTriggerStatus      = TRUE
///
/// - Expectations:
///
/// \output: WdgM_ResetHookActivation = 20212023u
/// \output: WdgM_boTriggerStatus     = FALSE
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Cycle0_TestCase2(void)
{
	//Step 1: Set pre-conditions
  WdgM_ResetHookActivation = 20212023;
  WdgM_boTriggerStatus = TRUE;

	//Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_Cycle0();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_ResetHookActivation, 20212023, == );
  AL_UNITTEST_CHECK(WdgM_boTriggerStatus, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Cycle0_TestCase3
///
/// \Test Case Description
///    - Test subject:  Check that the functionality of special hook develop for watchdog reset testing (controlled via sw)
///
/// \FuSa Relevant: -
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// N.A.
///
/// - Preconditions:
///
/// \input: WdgM_unEmulate_SpecialHook_Enbl_Var  = 0x5A01u
/// \input: WdgM_unEmulate_SpecialHook_Cnt_Var   = 0u
///
/// - Expectations:
///
/// \output: WdgM_unEmulate_SpecialHook_Enbl_Var  = 0x5A501u
/// \output: WdgM_unEmulate_SpecialHook_Cnt_Var   = 1u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Cycle0_TestCase3(void)
{
  //Step 1: Set pre-conditions
  WdgM_unEmulate_SpecialHook_Enbl_Var = 0x5A01u;
  WdgM_unEmulate_SpecialHook_Cnt_Var  = 0u;

  //Step 2) Assign Input values
  //--

  //Step 3) Call FUT
  WdgM_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_unEmulate_SpecialHook_Enbl_Var, 0x5A01u, == );
  AL_UNITTEST_CHECK(WdgM_unEmulate_SpecialHook_Cnt_Var, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Cycle0_TestCase4
///
/// \Test Case Description
///    - Test subject:  Check that the functionality of special hook develop for watchdog reset testing (controlled via sw)
///
/// \FuSa Relevant: -
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// N.A.
///
/// - Preconditions:
///
/// \input: WdgM_unEmulate_SpecialHook_Enbl_Var  = 0x5A01u
/// \input: WdgM_unEmulate_SpecialHook_Cnt_Var   = 10u
///
/// - Expectations:
///
/// \output: WdgM_unEmulate_SpecialHook_Enbl_Var  = 0u
/// \output: WdgM_unEmulate_SpecialHook_Cnt_Var   = 0u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Cycle0_TestCase4(void)
{
  //Step 1: Set pre-conditions
  WdgM_unEmulate_SpecialHook_Enbl_Var = 0x5A01u;
  WdgM_unEmulate_SpecialHook_Cnt_Var = 10u;

  //Step 2) Assign Input values
  //--

  //Step 3) Call FUT
  WdgM_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_unEmulate_SpecialHook_Enbl_Var, 0u, == );
  AL_UNITTEST_CHECK(WdgM_unEmulate_SpecialHook_Cnt_Var, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Cycle0_TestCase5
///
/// \Test Case Description
///    - Test subject:  Check that the functionality of special hook develop for watchdog reset testing (controlled via sw)
///
/// \FuSa Relevant: -
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// N.A.
///
/// - Preconditions:
///
/// \input: WdgM_unEmulate_SpecialHook_Enbl_Var  = 0x5A02u
/// \input: WdgM_unEmulate_SpecialHook_Cnt_Var   = 7u
///
/// - Expectations:
///
/// \output: WdgM_unEmulate_SpecialHook_Enbl_Var  = 0x5A02u
/// \output: WdgM_unEmulate_SpecialHook_Cnt_Var   = 7u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Cycle0_TestCase5(void)
{
  //Step 1: Set pre-conditions
  WdgM_unEmulate_SpecialHook_Enbl_Var = 0x5A02u;
  WdgM_unEmulate_SpecialHook_Cnt_Var = 7u;

  //Step 2) Assign Input values
  //--

  //Step 3) Call FUT
  WdgM_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(WdgM_unEmulate_SpecialHook_Enbl_Var, 0x5A02u, == );
  AL_UNITTEST_CHECK(WdgM_unEmulate_SpecialHook_Cnt_Var, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Cycle0
///
/// \FuSa Relevant:ASIL-B
///
/// \Test Case Description
///    - Test subject:  Check the function Wdg manager cyclic runnable
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Cycle0(void)
{
  Mt_WdgM_Cycle0_TestCase1();
  Mt_WdgM_Cycle0_TestCase2();
  Mt_WdgM_Cycle0_TestCase3();
  Mt_WdgM_Cycle0_TestCase4();
  Mt_WdgM_Cycle0_TestCase5();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_Trigger
///
/// \Test Case Description
///    - Test subject:  Check that the function Trigger the SBC wathdog window mode
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.324, LDM.MDRS_WDGM.601, LDM.MDRS_WDGM.527, LDM.MDRS_WDGM.603,
/// LDM.MDRS_WDGM.628
///
/// - Preconditions:
///
/// \input: CddSbc_SetWdgWindowModeAnd200ms_HitCount = 0u
///
/// - Expectations:
///
/// \output: CddSbc_SetWdgWindowModeAnd200ms_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_Trigger(void)
{
	//Step 1: Set pre-conditions
  CddSbc_SetWdgWindowModeAnd200ms_HitCount = 0u;

	//Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_Trigger();

	//Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSbc_SetWdgWindowModeAnd200ms_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_LPIT0_Ch1_IRQHandler_TestCase1
///
/// \Test Case Description
///    - Test subject:  Check that the function Trigger the wathdog reset when the coding paramaters are correct
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.556, LDM.MDRS_WDGM.606
///
/// - Preconditions: 
///
/// \input: WdgM_boTriggerStatus             = FALSE
/// \input: WdgM_ulErrorStatus               = 15u
/// \input: Lpit_ClearInterruptFlag_HitCount = 0u
/// \input: Lpit_ClearInterruptFlag_Param1   = 5u
/// \input: Lpit_ClearInterruptFlag_Param2   = 5u
/// 
/// - Expectations:
///	\output: WdgM_boTriggerStatus = TRUE
/// \output: Lpit_ClearInterruptFlag_HitCount = 1u
/// \output: Lpit_ClearInterruptFlag_Param1   = 0u
/// \output: Lpit_ClearInterruptFlag_Param2   = 1u
///
//-----------------------------------------------------------------------------
void Mt_LPIT0_Ch1_IRQHandler_TestCase1(void)
{
	//Step 1: Set pre-conditions
	WdgM_boTriggerStatus = FALSE;
  WdgM_ulErrorStatus = 15u;
  Lpit_ClearInterruptFlag_HitCount = 0u;
	
	//Step 2) Assign Input values
  Lpit_ClearInterruptFlag_Param1   = 5u;
  Lpit_ClearInterruptFlag_Param2   = 5u;

	//Step 3) Call FUT
	LPIT0_Ch1_IRQHandler();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_boTriggerStatus, TRUE, == );
  AL_UNITTEST_CHECK(Lpit_ClearInterruptFlag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Lpit_ClearInterruptFlag_Param1,   0u, == );
  AL_UNITTEST_CHECK(Lpit_ClearInterruptFlag_Param2,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_LPIT0_Ch1_IRQHandler_TestCase2
///
/// \Test Case Description
///    - Test subject:  Check that the function Skips the wathdog reset when the coding paramaters are Incorrect
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.556, LDM.MDRS_WDGM.606
///
/// - Preconditions: 
///
/// \input: WdgM_boTriggerStatus                   = TRUE
/// \input: WdgM_ulErrorStatus                     = 0u
/// \input: ulWdgM_Sha_Data_address_Reset_Reason   = 15u
/// \input: Lpit_ClearInterruptFlag_HitCount       = 0u
/// \input: Lpit_ClearInterruptFlag_Param1         = 5u
/// \input: Lpit_ClearInterruptFlag_Param2         = 5u
/// 
/// - Expectations:
///	\output: ulWdgM_Sha_Data_address_Reset_Reason  = WDGM_SHA_DATA_WDG_RESET_REASON_VAL
///	\output: WdgM_boTriggerStatus                  = TRUE
/// \output: Lpit_ClearInterruptFlag_HitCount      = 1u
/// \output: Lpit_ClearInterruptFlag_Param1        = 0u
/// \output: Lpit_ClearInterruptFlag_Param2        = 1u
///
//-----------------------------------------------------------------------------
void Mt_LPIT0_Ch1_IRQHandler_TestCase2(void)
{
	//Step 1: Set pre-conditions
	WdgM_boTriggerStatus = TRUE;
  WdgM_ulErrorStatus = 15u;
  ulWdgM_Sha_Data_address_Reset_Reason = 0u;
  Lpit_ClearInterruptFlag_HitCount = 0u;

	//Step 2) Assign Input values
  Lpit_ClearInterruptFlag_Param1   = 5u;
  Lpit_ClearInterruptFlag_Param2   = 5u;

	//Step 3) Call FUT
	LPIT0_Ch1_IRQHandler();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(ulWdgM_Sha_Data_address_Reset_Reason, WDGM_SHA_DATA_WDG_RESET_REASON_VAL, == );
	AL_UNITTEST_CHECK(WdgM_boTriggerStatus, TRUE, == );
  AL_UNITTEST_CHECK(Lpit_ClearInterruptFlag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Lpit_ClearInterruptFlag_Param1,   0u, == );
  AL_UNITTEST_CHECK(Lpit_ClearInterruptFlag_Param2,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_LPIT0_Ch1_IRQHandler
///
/// \FuSa Relevant:ASIL-B
///
/// \Test Case Description
///    - Test subject:  Check the function LPIT0_Ch1_IRQHandler
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_LPIT0_Ch1_IRQHandler(void)
{
  Mt_LPIT0_Ch1_IRQHandler_TestCase1();
  Mt_LPIT0_Ch1_IRQHandler_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_ResetShaDataResetReason
///
/// \Test Case Description
///    - Test subject:  Check that the function store the no reset reason value to the controllers memory location
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.593, LDM.MDRS_WDGM.602
///
/// - Preconditions:
///
/// \input: ulWdgM_Sha_Data_address_Reset_Reason = 0u
///
/// - Expectations:
///
/// \output: ulWdgM_Sha_Data_address_Noreset = WDGM_SHA_DATA_WDG_NORESET_REASON_VAL
///
//-----------------------------------------------------------------------------
void Mt_WdgM_ResetShaDataResetReason(void)
{
	//Step 1: Set pre-conditions
  ulWdgM_Sha_Data_address_Reset_Reason = 0u;

	//Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_ResetShaDataResetReason();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(ulWdgM_Sha_Data_address_Reset_Reason, WDGM_SHA_DATA_WDG_NORESET_REASON_VAL, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_EntitySupervision_TestCase1
///
/// \Test Case Description
///    - Test subject:  Check that the function decrements the Wdgm error status and update the error status to zero
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.524, LDM.MDRS_WDGM.604, LDM.MDRS_WDGM.615
///
/// - Preconditions:
///
/// \input: boFirstCallWdgCycleStatus = FALSE;
/// \input: WdgM_asCheckPointsList[0].uctHitCount = 9u
/// \input: WdgM_asCheckPointsList[1].uctHitCount = 10u
/// \input: WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u
/// \input: WdgM_asCheckPointsList[1].ucEntityCycleMs = 11u
/// \input: WdgM_ulErrorStatus = 0u
///
/// - Expectations:
///
/// \output: WdgM_ulErrorStatus = 0u
/// \output: WdgM_asCheckPointsList[0].uctHitCount = 0u
/// \output: WdgM_asCheckPointsList[1].uctHitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_EntitySupervision_TestCase1(void)
{
	//Step 1: Set pre-conditions
	boFirstCallWdgCycleStatus = FALSE;
  WdgM_asCheckPointsList[0].uctHitCount = 9u;
  WdgM_asCheckPointsList[1].uctHitCount = 10u;
  WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u;
  WdgM_asCheckPointsList[1].ucEntityCycleMs = 11u;
  WdgM_ulErrorStatus = 0u;

	//Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_EntitySupervision();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_ulErrorStatus, 0u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[0].uctHitCount, 0u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[1].uctHitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_EntitySupervision_TestCase2
///
/// \Test Case Description
///    - Test subject:  Check that the function decrements the Wdgm error status and update the error status to Eight if 
///						          the coding parameter are incorrect
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.524, LDM.MDRS_WDGM.604, LDM.MDRS_WDGM.615
///
/// - Preconditions:
///
/// \input: WdgM_asCheckPointsList[0].uctHitCount = 9u
/// \input: WdgM_asCheckPointsList[1].uctHitCount = 10u
/// \input: WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u
/// \input: WdgM_asCheckPointsList[1].ucEntityCycleMs = 11u
/// \input: WdgM_ulErrorStatus = 10u
///
/// - Expectations:
///
/// \output: WdgM_ulErrorStatus = 0u
/// \output: WdgM_asCheckPointsList[0].uctHitCount = 0u
/// \output: WdgM_asCheckPointsList[1].uctHitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_EntitySupervision_TestCase2(void)
{
  //Step 1: Set pre-conditions
	WdgM_asCheckPointsList[0].uctHitCount = 9u;
	WdgM_asCheckPointsList[1].uctHitCount = 10u;
	WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u;
	WdgM_asCheckPointsList[1].ucEntityCycleMs = 11u;
	WdgM_ulErrorStatus = 10u;

  //Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_EntitySupervision();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_ulErrorStatus, 8u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[0].uctHitCount, 0u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[1].uctHitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_EntitySupervision_TestCase3
///
/// \Test Case Description
///    - Test subject:  Check that the function Increments the Wdgm error status if
///						          the coding parameter are correct
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.524, LDM.MDRS_WDGM.604, LDM.MDRS_WDGM.615
///
/// - Preconditions:
///
/// \input: WdgM_asCheckPointsList[0].uctHitCount = 2u
/// \input: WdgM_asCheckPointsList[1].uctHitCount = 3u
/// \input: WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u
/// \input: WdgM_asCheckPointsList[1].ucEntityCycleMs = 1u
/// \input: WdgM_ulErrorStatus = 0u
///
/// - Expectations:
///
/// \output: WdgM_ulErrorStatus = 20u
/// \output: WdgM_asCheckPointsList[0].uctHitCount = 0u
/// \output: WdgM_asCheckPointsList[1].uctHitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_EntitySupervision_TestCase3(void)
{
  //Step 1: Set pre-conditions
	WdgM_asCheckPointsList[0].uctHitCount = 2u;
	WdgM_asCheckPointsList[1].uctHitCount = 3u;
	WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u;
	WdgM_asCheckPointsList[1].ucEntityCycleMs = 10u;
	WdgM_ulErrorStatus = 0u;

  //Step 2) Assign Input values
  //--

	//Step 3) Call FUT
	WdgM_EntitySupervision();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_ulErrorStatus, 20u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[0].uctHitCount, 0u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[1].uctHitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_EntitySupervision_TestCase4
///
/// \Test Case Description
///    - Test subject:  Check that the function Increments the Wdgm error status if
///						          the coding parameter are correct
///
/// \FuSa Relevant: ASIL_B
///
/// \Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test Method: Requirements-based test
///
/// \MDRS WDGM Id Requirement(s) covered: 
///
/// LDM.MDRS_WDGM.524, LDM.MDRS_WDGM.604, LDM.MDRS_WDGM.615
///
/// - Preconditions:
///
/// \input: WdgM_asCheckPointsList[0].uctHitCount = 2u
/// \input: WdgM_asCheckPointsList[1].uctHitCount = 3u
/// \input: WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u
/// \input: WdgM_asCheckPointsList[1].ucEntityCycleMs = 10u
/// \input: WdgM_ulErrorStatus = 255u
///
/// - Expectations:
///
/// \output: WdgM_ulErrorStatus = 255u
/// \output: WdgM_asCheckPointsList[0].uctHitCount = 0u
/// \output: WdgM_asCheckPointsList[1].uctHitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_WdgM_EntitySupervision_TestCase4(void)
{
  //Step 1: Set pre-conditions
	WdgM_asCheckPointsList[0].uctHitCount = 2u;
	WdgM_asCheckPointsList[1].uctHitCount = 3u;
	WdgM_asCheckPointsList[0].ucEntityCycleMs = 10u;
	WdgM_asCheckPointsList[1].ucEntityCycleMs = 10u;
	WdgM_ulErrorStatus = 255u;

  //Step 2) Assign Input values
  //--

    //Step 3) Call FUT
	WdgM_EntitySupervision();

	//Step 4) Check expected output values
	AL_UNITTEST_CHECK(WdgM_ulErrorStatus, 255u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[0].uctHitCount, 0u, == );
	AL_UNITTEST_CHECK(WdgM_asCheckPointsList[1].uctHitCount, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_WdgM_EntitySupervision
///
/// \FuSa Relevant:ASIL-B
/// 
/// \Test Case Description
///    - Test subject:  check that the function decrements the Wdgm error status and update the error status to Eight if 
///						          the coding parameter are incorrect, also check that the function Increments the Wdgm error status if
///						          the coding parameter are correct 
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_WdgM_EntitySupervision(void)
{
  Mt_WdgM_EntitySupervision_TestCase1();
  Mt_WdgM_EntitySupervision_TestCase2();
  Mt_WdgM_EntitySupervision_TestCase3();
  Mt_WdgM_EntitySupervision_TestCase4();
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
  ALUnitTest_AddFunction("Mt_riWdgM_Init",                      Mt_riWdgM_Init);
  ALUnitTest_AddFunction("Mt_rpWdgM_Cycle0",                    Mt_rpWdgM_Cycle0);
  ALUnitTest_AddFunction("Mt_WdgM_SetLocalCheckPoint",          Mt_WdgM_SetLocalCheckPoint);
  ALUnitTest_AddFunction("Mt_WdgM_Init",                        Mt_WdgM_Init);
  ALUnitTest_AddFunction("Mt_WdgM_Cycle0",                      Mt_WdgM_Cycle0);
  ALUnitTest_AddFunction("Mt_WdgM_Trigger",                     Mt_WdgM_Trigger);
  ALUnitTest_AddFunction("Mt_LPIT0_Ch1_IRQHandler",             Mt_LPIT0_Ch1_IRQHandler);
  ALUnitTest_AddFunction("Mt_WdgM_ResetShaDataResetReason",     Mt_WdgM_ResetShaDataResetReason);
  ALUnitTest_AddFunction("Mt_WdgM_EntitySupervision",           Mt_WdgM_EntitySupervision);
}



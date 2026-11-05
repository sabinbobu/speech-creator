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
/// \brief  Unit Test Cases for CddSbc
///
/// \author Diana Ursan
///         elena-diana.ursan@marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - CddSbc.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================
#include <ALUnitTest_UserInterface.h>

#include "Test.h"
#include "Test_Stubs.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_rpCddSbc_Cycle0_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc periodic runnable is called correctly
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_Short_To_VBAT_HitCount       = 0u
/// \input: CddTle94x1_Reset_Short_To_VBAT_HitCount = 0u
/// \input: CddTle94x1_Short_To_GND_HitCount        = 0u
/// \input: CddTle94x1_Reset_Short_To_GND_HitCount  = 0u
/// \input: CddTle94x1_Thermal_Shutdown_HitCount    = 0u
///
/// - Expectations: 
///
/// \output: CddTle94x1_Short_To_VBAT_HitCount       = 1u
/// \output: CddTle94x1_Reset_Short_To_VBAT_HitCount = 1u
/// \output: CddTle94x1_Short_To_GND_HitCount        = 1u
/// \output: CddTle94x1_Reset_Short_To_GND_HitCount  = 1u
/// \output: CddTle94x1_Thermal_Shutdown_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_rpCddSbc_Cycle0_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_Short_To_VBAT_HitCount = 0;
  CddTle94x1_Reset_Short_To_VBAT_HitCount = 0;
  CddTle94x1_Short_To_GND_HitCount = 0;
  CddTle94x1_Reset_Short_To_GND_HitCount = 0;
  CddTle94x1_Thermal_Shutdown_HitCount = 0;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  rpCddSbc_Cycle0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_Short_To_VBAT_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Reset_Short_To_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Short_To_GND_HitCount,        1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Reset_Short_To_GND_HitCount,  1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Thermal_Shutdown_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_riCddSbc_Init_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if riCddSbc_Init is called correctly
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_Init_HitCount = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_Init_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_riCddSbc_Init_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_Init_HitCount = 0u;
  
  //Step 2) Assign Input values
  //--
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  riCddSbc_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_Init_HitCount, 0u,          == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_Init_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc is initialized correctly
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_CDDSBC.206, LDM.MDRS_CDDSBC.468
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_Init_HitCount = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_Init_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_Init_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //Step 1: Set pre-conditions
  CddTle94x1_Init_HitCount = 0u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_Init_HitCount, 1u,          == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_DeInit_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc is de-initialized correctly
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_DeInit_HitCount = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_DeInit_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_DeInit_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_DeInit_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_DeInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_DeInit_HitCount, 1u,        == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_Cycle0_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc cyclic function is called correctly.
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_CDDSBC.303, LDM.MDRS_CDDSBC.315, LDM.MDRS_CDDSBC.587, LDM.MDRS_CDDSBC.682
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:  
///
/// \input: CddTle94x1_Short_To_VBAT_HitCount       = 0u
/// \input: CddTle94x1_Reset_Short_To_VBAT_HitCount = 0u
/// \input: CddTle94x1_Short_To_GND_HitCount        = 0u
/// \input: CddTle94x1_Reset_Short_To_GND_HitCount  = 0u
/// \input: CddTle94x1_Thermal_Shutdown_HitCount    = 0u
///
/// - Expectations: 
///
/// \output: CddTle94x1_Short_To_VBAT_HitCount       = 1u
/// \output: CddTle94x1_Reset_Short_To_VBAT_HitCount = 1u
/// \output: CddTle94x1_Short_To_GND_HitCount        = 1u
/// \output: CddTle94x1_Reset_Short_To_GND_HitCount  = 1u
/// \output: CddTle94x1_Thermal_Shutdown_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_Cycle0_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_Short_To_VBAT_HitCount       = 0;
  CddTle94x1_Reset_Short_To_VBAT_HitCount = 0;
  CddTle94x1_Short_To_GND_HitCount        = 0;
  CddTle94x1_Reset_Short_To_GND_HitCount  = 0;
  CddTle94x1_Thermal_Shutdown_HitCount    = 0;
  CddTle94x1_SetWdgWindowModeAnd200ms_HitCount = 0;
  
  //Step 2) Assign Input values
  CddSbc_ucWdgTriggerStat                 = 0xBDu;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_Cycle0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_Short_To_VBAT_HitCount,       1u,    == );
  AL_UNITTEST_CHECK(CddTle94x1_Reset_Short_To_VBAT_HitCount, 1u,    == );
  AL_UNITTEST_CHECK(CddTle94x1_Short_To_GND_HitCount,        1u,    == );
  AL_UNITTEST_CHECK(CddTle94x1_Reset_Short_To_GND_HitCount,  1u,    == );
  AL_UNITTEST_CHECK(CddTle94x1_Thermal_Shutdown_HitCount,    1u,    == );
  AL_UNITTEST_CHECK(CddTle94x1_SetWdgWindowModeAnd200ms_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_Cycle0_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if Sbc cyclic function is called correctly.
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_CDDSBC.727, LDM.MDRS_CDDSBC.303, LDM.MDRS_CDDSBC.315, LDM.MDRS_CDDSBC.587,
/// LDM.MDRS_CDDSBC.682, LDM.MDRS_CDDSBC.611, LDM.MDRS_CDDSBC.615, LDM.MDRS_CDDSBC.618,
/// LDM.MDRS_CDDSBC.621, LDM.MDRS_CDDSBC.624, LDM.MDRS_CDDSBC.590
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:  
///
/// \input: CddTle94x1_Short_To_VBAT_HitCount         = 0u
/// \input: CddTle94x1_Reset_Short_To_VBAT_HitCount   = 0u
/// \input: CddTle94x1_Short_To_GND_HitCount          = 0u
/// \input: CddTle94x1_Reset_Short_To_GND_HitCount    = 0u
/// \input: CddTle94x1_Thermal_Shutdown_HitCount      = 0u
///
/// - Expectations: 
///
/// \output: CddTle94x1_Short_To_VBAT_HitCount       = 1u
/// \output: CddTle94x1_Reset_Short_To_VBAT_HitCount = 1u
/// \output: CddTle94x1_Short_To_GND_HitCount        = 1u
/// \output: CddTle94x1_Reset_Short_To_GND_HitCount  = 1u
/// \output: CddTle94x1_Thermal_Shutdown_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_Cycle0_TestCase2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-condition
  CddTle94x1_Short_To_VBAT_HitCount = 0;
  CddTle94x1_Reset_Short_To_VBAT_HitCount = 0;
  CddTle94x1_Short_To_GND_HitCount = 0;
  CddTle94x1_Reset_Short_To_GND_HitCount = 0;
  CddTle94x1_Thermal_Shutdown_HitCount = 0;
  CddTle94x1_SetWdgWindowModeAnd200ms_HitCount = 0;
  
  //Step 2) Assign Input values
  CddSbc_ucWdgTriggerStat = 0x00u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_Cycle0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_Short_To_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Reset_Short_To_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Short_To_GND_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Reset_Short_To_GND_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_Thermal_Shutdown_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddTle94x1_SetWdgWindowModeAnd200ms_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_SetSleepMode_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc Sleep Mode function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:   
///
/// \input: CddTle94x1_SetSleepMode_HitCount = 0u
///
/// - Expectations:    
///
/// \output: CddTle94x1_SetSleepMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_SetSleepMode_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_SetSleepMode_HitCount = 0u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_SetSleepMode();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_SetSleepMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_SetCanMode_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc Set Can Mode function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:   
///
/// \input: CddTle94x1_SetCanMode_HitCount  = 0U
/// \input: CddSbc_SetCanMode_Param1        = 0u
/// \input: CddSbc_SetCanMode_Param2        = 1u
///
///
/// - Expectations:
///
/// \output: CddTle94x1_SetCanMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_SetCanMode_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_SetCanMode_HitCount = 0u;
  
  //Step 2) Assign Input values
  CddSbc_SetCanMode_Param1       = 0u;
  CddSbc_SetCanMode_Param2       = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_SetCanMode(CddSbc_SetCanMode_Param1, CddSbc_SetCanMode_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_SetCanMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetCanMode_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Can Mode function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetCanMode_HitCount = 0u
/// \input: CddSbc_GetCanMode_Param1       = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_GetCanMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetCanMode_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetCanMode_HitCount = 0u;
  
  //Step 2) Assign Input values
  CddSbc_GetCanMode_Param1 = 0u;
  CddTle94x1_GetCanMode_RetVal = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetCanMode_RetVal = CddSbc_GetCanMode(CddSbc_GetCanMode_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetCanMode_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetCanMode_RetVal,       0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetCanUV_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Can Undervoltage function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetCanUV_HitCount = 0u
///
/// - Expectations:
///
/// \output:  CddTle94x1_GetCanUV_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetCanUV_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetCanUV_HitCount = 0u;
  CddTle94x1_GetCanUV_RetVal   = 4u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetCanUV_RetVal = CddSbc_GetCanUV();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetCanUV_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetCanUV_RetVal,       4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetResetReason_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Reset Reason function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetSBCResetReason_HitCount = 0u;
/// \input: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)ePowerOnResetSBC;
///
/// - Expectations:
///
/// \output: CddTle94x1_GetSBCResetReason_HitCount = 1u
/// \output: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eRESET_POWER_ON
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetResetReason_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetSBCResetReason_HitCount = 0u;
  CddTle94x1_GetSBCResetReason_RetVal   = (uint8)ePowerOnResetSBC; //1u
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetResetReason_RetVal = CddSbc_GetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetSBCResetReason_HitCount, 1u,       == );
  AL_UNITTEST_CHECK(CddSbc_GetResetReason_RetVal, (uint8)eRESET_POWER_ON, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetResetReason_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Reset Reason function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetSBCResetReason_HitCount = 0u;
/// \input: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eCANWakeUpReset
///
/// - Expectations: 
/// \output: CddTle94x1_GetSBCResetReason_HitCount = 1u;
/// \output: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eRESET_CAN_WAKEUP
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetResetReason_TestCase2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetSBCResetReason_HitCount = 0u;
  
  //Step 2) Assign Input values
  CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eCANWakeUpReset;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetResetReason_RetVal = CddSbc_GetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetSBCResetReason_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetResetReason_RetVal, (uint8)eRESET_CAN_WAKEUP, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetResetReason_TestCase3
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Reset Reason function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetSBCResetReason_HitCount = 0u
/// \input: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eWatchdogReset
///
/// - Expectations:
///
/// \output: CddTle94x1_GetSBCResetReason_HitCount = 1u
/// \output: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eRESET_WATCHDOG
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetResetReason_TestCase3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetSBCResetReason_HitCount = 0u;
  
  //Step 2) Assign Input values
  CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eWatchdogReset;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetResetReason_RetVal = CddSbc_GetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetSBCResetReason_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetResetReason_RetVal, (uint8)eRESET_WATCHDOG, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetResetReason_TestCase4
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Reset Reason function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetSBCResetReason_HitCount = 0u
/// \input: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eInputWakeUpReset
///
/// - Expectations:
///
/// \output: CddTle94x1_GetSBCResetReason_HitCount = 1u
/// \output: CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eRESET_INPUT_WAKEUP
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetResetReason_TestCase4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetSBCResetReason_HitCount = 0u;
  
  //Step 2) Assign Input values
  CddTle94x1_GetSBCResetReason_RetVal   = (uint8)eInputWakeUpReset;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetResetReason_RetVal = CddSbc_GetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetSBCResetReason_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetResetReason_RetVal, (uint8)eRESET_INPUT_WAKEUP, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetResetReason_TestCase5
///
/// \Test Case Description
///        - Test subject: Test if Sbc Get Reset Reason function is called correctly.
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_GetSBCResetReason_HitCount   = 0u
/// \input: CddTle94x1_GetSBCResetReason_RetVal     = 11u
///
/// - Expectations:
///
/// \output: CddTle94x1_GetSBCResetReason_HitCount  = 1u
/// \output: CddSbc_GetResetReason_RetVal           = (uint8)eRESET_SNA
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetResetReason_TestCase5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_GetSBCResetReason_HitCount = 0u;
  CddTle94x1_GetSBCResetReason_RetVal = 11u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetResetReason_RetVal = CddSbc_GetResetReason();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_GetSBCResetReason_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetResetReason_RetVal, (uint8)eRESET_SNA, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_SetWdgWindowModeAnd10ms_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if CddSbc_SetWdgWindowModeAnd10ms function is called correctly
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_SetWdgWindowModeAnd10ms_HitCount   = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_SetWdgWindowModeAnd10ms_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_SetWdgWindowModeAnd10ms_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_SetWdgWindowModeAnd10ms_HitCount = 0u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_SetWdgWindowModeAnd10ms();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_SetWdgWindowModeAnd10ms_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_SetWdgWindowModeAnd200ms_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if CddSbc_SetWdgWindowModeAnd200ms function is called correctly
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_CDDSBC.484, LDM.MDRS_CDDSBC.523
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input: CddTle94x1_SetWdgWindowModeAnd200ms_HitCount = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_SetWdgWindowModeAnd200ms_HitCount = 0u
/// \output: CddSbc_ucWdgTriggerStat                      = 0xBDu
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_SetWdgWindowModeAnd200ms_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_SetWdgWindowModeAnd200ms_HitCount = 0u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_SetWdgWindowModeAnd200ms();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_SetWdgWindowModeAnd200ms_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddSbc_ucWdgTriggerStat, 0xBDu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_SetWdgTimeoutModeAnd200ms_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if SetWdgTimeoutModeAnd200ms function is called correctly
///
/// \FuSa Relevant: ASIL_B
///
/// \MDRS ECUM Id Requirement(s) covered: 
///
/// LDM.MDRS_CDDSBC.486
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount = 0u
///
/// - Expectations:
///
/// \output: CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_SetWdgTimeoutModeAnd200ms_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount = 0u;
  
  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_SetWdgTimeoutModeAnd200ms();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddTle94x1_SetWdgTimeoutModeAnd200ms_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_SetPWM_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if function set and call the router function for PWM OUT_FCT
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddSbc_unPWM_Val            = 0u
/// \input: CddSbc_SetPWM_Param1        = 15000u
/// \input: CddTle94x1_SetPWM_Param1    = 0u
/// \input: CddTle94x1_SetPWM_HitCount  = 0u
///
/// - Expectations:
///
/// \output: CddSbc_unPWM_Val             = 15000u
/// \output: CddTle94x1_SetPWM_Param1     = 15000u
/// \output: CddTle94x1_SetPWM_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_SetPWM_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddSbc_unPWM_Val = 0u;
  CddTle94x1_SetPWM_Param1 = 0u;
  CddTle94x1_SetPWM_HitCount = 0u;

  //Step 2) Assign Input values
  CddSbc_SetPWM_Param1 = 15000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_SetPWM(CddSbc_SetPWM_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSbc_unPWM_Val, 15000u, == );
  AL_UNITTEST_CHECK(CddTle94x1_SetPWM_Param1, 15000u, == );
  AL_UNITTEST_CHECK(CddTle94x1_SetPWM_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetPWM_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if function set and call the router function for PWM OUT_FCT
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddSbc_unPWM_Val              = 1200u
/// \input: CddSbc_GetPWM_Param1          = 0u
/// \input: CddSbc_GetPWM_RetVal          = 0u
/// \input: CddTle94x1_GetPWM_RetVal      = 0u
/// \input: CddTle94x1_GetPWM_HitCount    = 0u
///
/// - Expectations:
///
/// \output: CddSbc_GetPWM_RetVal         = 1200u
/// \output: CddTle94x1_GetPWM_HitCount   = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetPWM_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddSbc_unPWM_Val = 1200u;
  CddSbc_GetPWM_Param1 = 0u;
  CddSbc_GetPWM_RetVal = 0u;
  CddTle94x1_GetPWM_RetVal = 0u;
  CddTle94x1_GetPWM_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetPWM_RetVal = CddSbc_GetPWM(CddSbc_GetPWM_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSbc_GetPWM_RetVal, 1200u, == );
  AL_UNITTEST_CHECK(CddTle94x1_GetPWM_HitCount, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_CddSbc_GetPWM_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if function set and call the router function for PWM OUT_FCT
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: CddSbc_unPWM_Val              = 1200u
/// \input: CddSbc_GetPWM_Param1          = 1u
/// \input: CddSbc_GetPWM_RetVal          = 0u
/// \input: CddTle94x1_GetPWM_RetVal      = 127u
/// \input: CddTle94x1_GetPWM_HitCount    = 0u
///
/// - Expectations:
///
/// \output: CddSbc_GetPWM_RetVal         = 4980u (~5000u = 50%)
/// \output: CddTle94x1_GetPWM_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_CddSbc_GetPWM_TestCase2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  CddSbc_unPWM_Val = 1200u;
  CddSbc_GetPWM_Param1 = 1u;
  CddSbc_GetPWM_RetVal = 0u;
  CddTle94x1_GetPWM_RetVal = 127u;
  CddTle94x1_GetPWM_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  CddSbc_GetPWM_RetVal = CddSbc_GetPWM(CddSbc_GetPWM_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CddSbc_GetPWM_RetVal, 4980u, == );
  AL_UNITTEST_CHECK(CddTle94x1_GetPWM_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSbc_reCddSbc_SetLssPwm_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if function simulates the event runnable reCddSbc_SetLssPwm stimulated by CddSwi_SetLssPwm_Req RTE port
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input: Rte_Read_CddSwi_SetLssPwm_Req_HitCount            = 0u
/// \input: Rte_Read_CddSwi_SetLssPwm_Req_RetVal              = E_OK
/// \input: Rte_Read_CddSwi_SetLssPwm_Req_Param1              = &temp
/// \input: temp                                              = 1000u
/// \input: CddSbc_unPWM_Val                                  = 0u
/// \input: CddTle94x1_SetPWM_Param1                          = 0u
/// \input: CddTle94x1_SetPWM_HitCount                        = 0u
///
/// - Expectations:
///
/// \output: Rte_Read_CddSwi_SetLssPwm_Req_HitCount          = 1u
/// \output: CddSbc_unPWM_Val                                = 1000u
/// \output: CddTle94x1_SetPWM_Param1                        = 1000u
/// \output: CddTle94x1_SetPWM_HitCount                      = 1
///
//-----------------------------------------------------------------------------
void Mt_CddSbc_reCddSbc_SetLssPwm_TestCase1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //Step 1: Set pre-conditions
  uint16 temp = 1000u;
  Rte_Read_CddSwi_SetLssPwm_Req_HitCount = 0u;
  Rte_Read_CddSwi_SetLssPwm_Req_RetVal = E_OK;
  Rte_Read_CddSwi_SetLssPwm_Req_Param1 = &temp;
  CddSbc_unPWM_Val = 0u;
  CddTle94x1_SetPWM_Param1 = 0u;
  CddTle94x1_SetPWM_HitCount = 0u;

  //Step 2) Assign Input values
  //--

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  //Step 3) Call FUT
  reCddSbc_SetLssPwm();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SetLssPwm_Req_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddSbc_unPWM_Val, 1000u, == );
  AL_UNITTEST_CHECK(CddTle94x1_SetPWM_Param1, 1000u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SetLssPwm_Req_HitCount, 1u, == );
}


void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_CddSbc_rpCddSbc_Cycle0_TestCase1",         Mt_CddSbc_rpCddSbc_Cycle0_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_riCddSbc_Init_TestCase1",           Mt_CddSbc_riCddSbc_Init_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_Init_TestCase1",             Mt_CddSbc_CddSbc_Init_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_DeInit_TestCase1",           Mt_CddSbc_CddSbc_DeInit_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_Cycle0_TestCase1",           Mt_CddSbc_CddSbc_Cycle0_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_Cycle0_TestCase2",           Mt_CddSbc_CddSbc_Cycle0_TestCase2);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_SetSleepMode_TestCase1",     Mt_CddSbc_CddSbc_SetSleepMode_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_SetCanMode_TestCase1",       Mt_CddSbc_CddSbc_SetCanMode_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetCanMode_TestCase1",       Mt_CddSbc_CddSbc_GetCanMode_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetCanUV_TestCase1",         Mt_CddSbc_CddSbc_GetCanUV_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetResetReason_TestCase1",   Mt_CddSbc_CddSbc_GetResetReason_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetResetReason_TestCase2",   Mt_CddSbc_CddSbc_GetResetReason_TestCase2);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetResetReason_TestCase3",   Mt_CddSbc_CddSbc_GetResetReason_TestCase3);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetResetReason_TestCase4",   Mt_CddSbc_CddSbc_GetResetReason_TestCase4);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetResetReason_TestCase5",   Mt_CddSbc_CddSbc_GetResetReason_TestCase5);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_SetWdgWindowModeAnd10ms_TestCase1",   Mt_CddSbc_CddSbc_SetWdgWindowModeAnd10ms_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_SetWdgWindowModeAnd200ms_TestCase1",  Mt_CddSbc_CddSbc_SetWdgWindowModeAnd200ms_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_SetWdgTimeoutModeAnd200ms_TestCase1", Mt_CddSbc_CddSbc_SetWdgTimeoutModeAnd200ms_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_SetPWM_TestCase1", Mt_CddSbc_CddSbc_SetPWM_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetPWM_TestCase1", Mt_CddSbc_CddSbc_GetPWM_TestCase1);
  ALUnitTest_AddFunction("Mt_CddSbc_CddSbc_GetPWM_TestCase2", Mt_CddSbc_CddSbc_GetPWM_TestCase2);
  ALUnitTest_AddFunction("Mt_CddSbc_reCddSbc_SetLssPwm_TestCase1", Mt_CddSbc_reCddSbc_SetLssPwm_TestCase1);
}

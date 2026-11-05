//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen AGmbH.
//*****************************************************************************
/// \file  Test.c
///
/// \brief  Unit Test Cases for Mcu module
///
/// \author Futo Henrietta Helena (F31185D)
///         mailTo:henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_Init
///
/// \Test Case Description: Test if the function is initializing the Mcu specific clocks and the
///                         peripheral clocks, following the configuration structure form ConfigPtr.
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Enable CP10 and CP11 coprocessors
///         Step2: Invalidate and enable code cache
///         Step3: Call Mcu_Init(Mcu_Init_Param1)
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input    Mcu_Init_Param1                     = 10u
/// \input    SCB_Register_Layout.CPACR           = 5u
/// \input    LMem_Register_Layout.PCCCR          = 10u
///
/// - Expectations: 
///
/// \output   CB_Register_Layout.CPACR            = 53u
/// \output   LMem_Register_Layout.PCCCR          = 1u
//-----------------------------------------------------------------------------
void Mt_Mcu_Init(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Mcu_Init_Param1            = 10u;
  SCB_Register_Layout.CPACR  = 5u;
  LMem_Register_Layout.PCCCR = 10U;

  //Step 3) Call FUT
  Mcu_Init(&Mcu_Init_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(SCB_Register_Layout.CPACR, 53u, == );
  AL_UNITTEST_CHECK(LMem_Register_Layout.PCCCR, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_InitClock_TestCase_1
///
/// \Test Case Description: Test if the function is initializing the Mcu specific clocks and the
///                         peripheral clocks, following the configuration structure form ConfigPtr.
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the parameters for clock system intialization
///         Step2: Set the parameters for clock system update configuration
///         Step3: Call Mcu_InitClock(Mcu_InitClock_Param1)
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input    Mcu_InitClock_Param1                        = 10u
/// \input    CLOCK_SYS_Init_Param1                       = 1u
/// \input    CLOCK_SYS_Init_Param2                       = 1u
/// \input    CLOCK_SYS_Init_Param3                       = 1u
/// \input    CLOCK_SYS_Init_Param4                       = 1u
/// \input    CLOCK_SYS_Init_HitCount                     = 0u
/// \input    CLOCK_SYS_UpdateConfiguration_Param1        = 100u
/// \input    CLOCK_SYS_UpdateConfiguration_Param2        = 10u
/// \input    CLOCK_SYS_UpdateConfiguration_HitCount      = 0u
/// \input    CLOCK_SYS_UpdateConfiguration_RetVal        = 1u
///
/// - Expectations: 
///
/// \output   Mcu_InitClock_RetVal                        = 1u
/// \output   CLOCK_SYS_Init_HitCount                     = 1u
/// \output   CLOCK_SYS_UpdateConfiguration_HitCount      = 1u
//-----------------------------------------------------------------------------
void Mt_Mcu_InitClock_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Mcu_InitClock_Param1                   = 10u;
  CLOCK_SYS_Init_Param1                  = 1u;
  CLOCK_SYS_Init_Param2                  = 1u;
  CLOCK_SYS_Init_Param3                  = 1u;
  CLOCK_SYS_Init_Param4                  = 1u;
  CLOCK_SYS_Init_HitCount                = 0u;
  CLOCK_SYS_UpdateConfiguration_Param1   = 100u;
  CLOCK_SYS_UpdateConfiguration_Param2   = 10u;
  CLOCK_SYS_UpdateConfiguration_HitCount = 0u;
  CLOCK_SYS_UpdateConfiguration_RetVal   = 1u;

  //Step 3) Call FUT
  Mcu_InitClock_RetVal = Mcu_InitClock(&Mcu_InitClock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_InitClock_RetVal,                   1u, == );
  AL_UNITTEST_CHECK(CLOCK_SYS_Init_HitCount,                1u, == );
  AL_UNITTEST_CHECK(CLOCK_SYS_UpdateConfiguration_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_InitClock_TestCase_2
///
/// \Test Case Description: Test if the function is initializing the Mcu specific clocks and the
///                         peripheral clocks, following the configuration structure form ConfigPtr.
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the parameters for clock system intialization
///         Step2: Set the parameters for clock system update configuration
///         Step3: Call Mcu_InitClock(Mcu_InitClock_Param1)
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input    Mcu_InitClock_Param1                        = 10u
/// \input    CLOCK_SYS_Init_Param1                       = 1u
/// \input    CLOCK_SYS_Init_Param2                       = 1u
/// \input    CLOCK_SYS_Init_Param3                       = 1u
/// \input    CLOCK_SYS_Init_Param4                       = 1u
/// \input    CLOCK_SYS_Init_HitCount                     = 0u
/// \input    CLOCK_SYS_UpdateConfiguration_Param1        = 100u
/// \input    CLOCK_SYS_UpdateConfiguration_Param2        = 10u
/// \input    CLOCK_SYS_UpdateConfiguration_HitCount      = 0u
/// \input    CLOCK_SYS_UpdateConfiguration_RetVal        = 0u
///
/// - Expectations: 
///
/// \output   Mcu_InitClock_RetVal                        = 0u
/// \output   CLOCK_SYS_Init_HitCount                     = 1u
/// \output   CLOCK_SYS_UpdateConfiguration_HitCount      = 1u
//-----------------------------------------------------------------------------
void Mt_Mcu_InitClock_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Mcu_InitClock_Param1                   = 10;
  CLOCK_SYS_Init_Param1                  = 1u;
  CLOCK_SYS_Init_Param2                  = 1u;
  CLOCK_SYS_Init_Param3                  = 1u;
  CLOCK_SYS_Init_Param4                  = 1u;
  CLOCK_SYS_Init_HitCount                = 0u;
  CLOCK_SYS_UpdateConfiguration_Param1   = 100u;
  CLOCK_SYS_UpdateConfiguration_Param2   = 10u;
  CLOCK_SYS_UpdateConfiguration_HitCount = 0u;
  CLOCK_SYS_UpdateConfiguration_RetVal   = 0u;

  //Step 3) Call FUT
  Mcu_InitClock_RetVal = Mcu_InitClock(&Mcu_InitClock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_InitClock_RetVal,                   0u, == );
  AL_UNITTEST_CHECK(CLOCK_SYS_Init_HitCount,                1u, == );
  AL_UNITTEST_CHECK(CLOCK_SYS_UpdateConfiguration_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_InitClock
///
/// \FuSa Relevant:ASIL-B
///
/// \Test Case Description
///    - Test subject:  Test if the function is initializing the Mcu specific clocks and the
///                     peripheral clocks, following the configuration structure form ConfigPtr.
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_Mcu_InitClock(void)
{
  Mt_Mcu_InitClock_TestCase_1();
  Mt_Mcu_InitClock_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_DistributePllClock
///
/// \Test Case Description: Function return E_OK (TBD)
///
/// - Preconditions:
///
/// \input -
///
/// - Expectations: 
///
/// \output   Mcu_DistributePllClock_RetVal         = 0u
//-----------------------------------------------------------------------------
void Mt_Mcu_DistributePllClock(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  //Step 3) Call FUT
  Mcu_DistributePllClock_RetVal = Mcu_DistributePllClock();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_DistributePllClock_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Port_Mcu_GetResetReason_TestCase_1
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_SACKERR_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_STOP_ACKNOWLEDGE_ERROR_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_SACKERR_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_STOP_ACKNOWLEDGE_ERROR_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_2
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_MDM_AP_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_MDM_AP_SYSTEM_RESET_REQUEST
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_MDM_AP_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_MDM_AP_SYSTEM_RESET_REQUEST, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_3
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_SW_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_SOFTWARE_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_SW_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_SOFTWARE_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_4
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_LOCKUP_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_CORE_LOCKUP
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_LOCKUP_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_CORE_LOCKUP, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_5
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_JTAG_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_JTAG_GENERATED_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_JTAG_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_JTAG_GENERATED_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_6
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_POR_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_POWER_ON_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_POR_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_POWER_ON_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_7
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_PIN_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_EXTERNAL_PIN_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_PIN_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_EXTERNAL_PIN_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_8
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_WDOG_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_WATCHDOG_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_WDOG_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_WATCHDOG_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_9
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_CMU_LOC_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_CMU_LOSS_OF_CLOCK_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_9(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_CMU_LOC_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_CMU_LOSS_OF_CLOCK_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_10
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_LOL_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_LOSS_OF_LOCK_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_10(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_LOL_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_LOSS_OF_LOCK_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_11
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_LOC_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_LOSS_OF_CLOCK_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_11(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_LOC_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_LOSS_OF_CLOCK_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_12
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_LVD_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_LOW_VOLTAGE_DETECT_OR_HIGH_VOLTAGE_DETECT_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_12(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_LVD_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_LOW_VOLTAGE_DETECT_OR_HIGH_VOLTAGE_DETECT_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_13
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = RCM_SRS_POR_MASK | RCM_SRS_LVD_MASK
/// \input    Mcu_GetResetReason_RetVal         = 255u
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_POWER_ON_RESET
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_13(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = RCM_SRS_POR_MASK | RCM_SRS_LVD_MASK;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_POWER_ON_RESET, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason_TestCase_14
///
/// \Test Case Description: Test if the function gets the reason for the reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// \Steps:
///         Step1: Set the value for System Reset Status Register
///         Step2: Decide what is the reason of the reset
///         Step3: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    RCM_Register_Layout.SRS           = 0u (fault injection)
///
/// - Expectations: 
///
/// \output   Mcu_GetResetReason_RetVal         = MCU_RESET_UNDEFINED
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason_TestCase_14(void)
{
  //Step 1 Set pre-conditions
  //Step 2) Assign Input values
  RCM_Register_Layout.SRS = 0u;
  Mcu_GetResetReason_RetVal = 255u;

  //Step 3) Call FUT
  Mcu_GetResetReason_RetVal = Mcu_GetResetReason();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Mcu_GetResetReason_RetVal, MCU_RESET_UNDEFINED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_GetResetReason
///
/// \FuSa Relevant:ASIL-B
///
/// \Test Case Description
///    - Test subject:  Test if the function gets the reason for the reset
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_Mcu_GetResetReason(void)
{
  Mt_Mcu_GetResetReason_TestCase_1();
  Mt_Mcu_GetResetReason_TestCase_2();
  Mt_Mcu_GetResetReason_TestCase_3();
  Mt_Mcu_GetResetReason_TestCase_4();
  Mt_Mcu_GetResetReason_TestCase_5();
  Mt_Mcu_GetResetReason_TestCase_6();
  Mt_Mcu_GetResetReason_TestCase_7();
  Mt_Mcu_GetResetReason_TestCase_8();
  Mt_Mcu_GetResetReason_TestCase_9();
  Mt_Mcu_GetResetReason_TestCase_10();
  Mt_Mcu_GetResetReason_TestCase_11();
  Mt_Mcu_GetResetReason_TestCase_12();
  Mt_Mcu_GetResetReason_TestCase_13();
  Mt_Mcu_GetResetReason_TestCase_14();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mcu_PerformReset
///
/// \Test Case Description: Test if the function performs software reset
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Indicate that it will not be a PowerOn Reset, in case application has not yet reset the flag
///         Step2: Set the access register parameters for SvcAccessReg32
///         Step3: Generating soft reset
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input    SvcAccessReg32_Param1           = 0u
/// \input    SvcAccessReg32_Param2           = 1u
/// \input    SvcAccessReg32_Param3           = 10u
/// \input    SvcAccessReg32_RetVal           = 5u
///
/// - Expectations: 
///
/// \output   SvcAccessReg32_RetVal           = 5u
//-----------------------------------------------------------------------------
void Mt_Mcu_PerformReset(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  SvcAccessReg32_Param1 = 0u;
  SvcAccessReg32_Param2 = 1u;
  SvcAccessReg32_Param3 = 10u;
  SvcAccessReg32_RetVal = 5u;

  //Step 3) Call FUT
  Mcu_PerformReset();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(SvcAccessReg32_RetVal, 5u, == );
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
  ALUnitTest_AddFunction("Mt_Mcu_Init", Mt_Mcu_Init);
  ALUnitTest_AddFunction("Mt_Mcu_InitClock", Mt_Mcu_InitClock);
  ALUnitTest_AddFunction("Mt_Mcu_DistributePllClock", Mt_Mcu_DistributePllClock);
  ALUnitTest_AddFunction("Mt_Mcu_GetResetReason", Mt_Mcu_GetResetReason);
  ALUnitTest_AddFunction("Mt_Mcu_PerformReset", Mt_Mcu_PerformReset);
}

//// EOF

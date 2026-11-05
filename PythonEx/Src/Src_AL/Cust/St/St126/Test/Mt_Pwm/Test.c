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
/// \brief Module test for McalPwm
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
/// \Test Case : Mt_McalPwm_Pwm_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if pwm channels are initialized
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: - 
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_Init_Param1                     = &Pwm_Config
/// \input  PWM_Init_Param1.instIdx             = 20u
/// \input  PWM_Init_Param1.instType            = 20u
/// \input  PWM_Init_Param2.numberOfPwmChannels = 20u
/// \input  PWM_Init_Param2.pwmChannels         = 20u
/// \input  PWM_Init_HitCount                   = 0u
/// \input  g_ftmBase[0]->CONF                  = 12u
/// \input  g_ftmBase[1]->CONF                  = 22u
/// \input  g_ftmBase[2]->CONF                  = 32u
/// \input  g_ftmBase[3]->CONF                  = 42u
///
/// - Expectations:
///
/// \output PWM_Init_Param1.instIdx             = 3u
/// \output PWM_Init_Param1.instType            = PWM_INST_TYPE_FTM (0u)
/// \output PWM_Init_Param2.numberOfPwmChannels = 2u
/// \output PWM_Init_Param2.pwmChannels         = &pwm_pal_configs_FTM3[0]
/// \output PWM_Init_HitCount                   = 4u
/// \output g_ftmBase[0]->CONF                  = 1578u
/// \output g_ftmBase[1]->CONF                  = 554u
/// \output g_ftmBase[2]->CONF                  = 554u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  PWM_Init_Param1.instIdx             = 20u;
  PWM_Init_Param1.instType            = 20u;
  PWM_Init_Param2.numberOfPwmChannels = 20u;
  PWM_Init_Param2.pwmChannels         = 20u;
  PWM_Init_HitCount                   = 0u;
  g_ftmBase[0]->CONF                  = 12u;
  g_ftmBase[1]->CONF                  = 22u;
  g_ftmBase[2]->CONF                  = 32u;
  g_ftmBase[3]->CONF                  = 42u;

  // Step 2: Assign Input values
  Pwm_Init_Param1                     = &Pwm_Config;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_Init(Pwm_Init_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(PWM_Init_Param1.instIdx,                                                 3u, == );
  AL_UNITTEST_CHECK(PWM_Init_Param1.instType,                                 PWM_INST_TYPE_FTM, == );
  AL_UNITTEST_CHECK(PWM_Init_Param2.numberOfPwmChannels,                                     2u, == );
  AL_UNITTEST_CHECK(PWM_Init_Param2.pwmChannels,                       &pwm_pal_configs_FTM3[0], == );
  AL_UNITTEST_CHECK(PWM_Init_HitCount,                                                       4u, == );
  AL_UNITTEST_CHECK(g_ftmBase[0]->CONF,                                                   1578u, == );
  AL_UNITTEST_CHECK(g_ftmBase[1]->CONF,                                                    554u, == );
  AL_UNITTEST_CHECK(g_ftmBase[2]->CONF,                                                    554u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is not set when channel number is invalid
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input  Pwm_SetPeriodAndDuty_Param1      = 14u
/// \input  Pwm_SetPeriodAndDuty_Param2      = 1u
/// \input  Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input  FTM_DRV_UpdatePwmPeriod_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_UpdatePwmPeriod_HitCount  = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_UpdatePwmPeriod_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1      = 14u; // invalid channel
  Pwm_SetPeriodAndDuty_Param2      = 1u;
  Pwm_SetPeriodAndDuty_Param3      = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is not set when channel number is out of range
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input  Pwm_SetPeriodAndDuty_Param1      = 15u
/// \input  Pwm_SetPeriodAndDuty_Param2      = 1u
/// \input  Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input  FTM_DRV_UpdatePwmPeriod_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_UpdatePwmPeriod_HitCount  = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_UpdatePwmPeriod_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1      = 15u; // out of range channel
  Pwm_SetPeriodAndDuty_Param2      = 1u;
  Pwm_SetPeriodAndDuty_Param3      = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is not set when periond is invalid
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input   Pwm_SetPeriodAndDuty_Param1      = 0u
/// \input   Pwm_SetPeriodAndDuty_Param2      = 0xFFFFu
/// \input   Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input   FTM_DRV_UpdatePwmPeriod_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_UpdatePwmPeriod_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_UpdatePwmPeriod_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1      = 0u;
  Pwm_SetPeriodAndDuty_Param2      = 0xFFFFu;
  Pwm_SetPeriodAndDuty_Param3      = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_HitCount, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if pwm period is not updated
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input  Pwm_SetPeriodAndDuty_Param1      = 0u
/// \input  Pwm_SetPeriodAndDuty_Param2      = 1u
/// \input  Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input  FTM_DRV_UpdatePwmPeriod_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_UpdatePwmPeriod_HitCount  = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_UpdatePwmPeriod_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1      = 0u;
  Pwm_SetPeriodAndDuty_Param2      = 1u;
  Pwm_SetPeriodAndDuty_Param3      = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_HitCount, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetPeriodAndDuty_Param1      = 0u
/// \input  Pwm_SetPeriodAndDuty_Param2      = 1u
/// \input  Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input  g_ftmBase[0]->CONF               = 23u
/// \input  FTM_DRV_GetMod_HitCount          = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF       = 0u
/// \input  FTM_DRV_GetMod_RetVal            = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount    = 2u
/// \output FTM_DRV_GetMod_Param1.CONF = 23u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF               = 23u;
  FTM_DRV_GetMod_HitCount          = 0u;
  FTM_DRV_GetMod_Param1.CONF       = 0u;
  FTM_DRV_GetMod_RetVal            = 0u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1      = 0u;
  Pwm_SetPeriodAndDuty_Param2      = 1u;
  Pwm_SetPeriodAndDuty_Param3      = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,            2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,        23u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetPeriodAndDuty_Param1      = 0u
/// \input  Pwm_SetPeriodAndDuty_Param2      = 0u
/// \input  Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input  g_ftmBase[0]->CONF               = 24u
/// \input  FTM_DRV_GetMod_HitCount          = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF       = 0u
/// \input  FTM_DRV_GetMod_RetVal            = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount    = 2u
/// \output FTM_DRV_GetMod_Param1.CONF = 24u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF               = 24u;
  FTM_DRV_GetMod_HitCount          = 0u;
  FTM_DRV_GetMod_Param1.CONF       = 0u;
  FTM_DRV_GetMod_RetVal            = 1u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1 = 0u;
  Pwm_SetPeriodAndDuty_Param2 = 0u;
  Pwm_SetPeriodAndDuty_Param3 = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,            2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,        24u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if pwm duty and period is updated
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetPeriodAndDuty_Param1      = 0u
/// \input  Pwm_SetPeriodAndDuty_Param2      = 0u
/// \input  Pwm_SetPeriodAndDuty_Param3      = 1u
/// \input  g_ftmBase[0]->CONF               = 24u
/// \input  FTM_DRV_GetMod_HitCount          = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF       = 0u
/// \input  FTM_DRV_GetMod_RetVal            = 10u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount          = 53u
/// \output FTM_DRV_GetMod_Param1.CONF       = 24u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF               = 24u;
  FTM_DRV_GetMod_HitCount          = 0u;
  FTM_DRV_GetMod_Param1.CONF       = 0u;
  FTM_DRV_GetMod_RetVal            = 10u;

  // Step 2: Assign Input values
  Pwm_SetPeriodAndDuty_Param1      = 0u;
  Pwm_SetPeriodAndDuty_Param2      = 0u;
  Pwm_SetPeriodAndDuty_Param3      = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetPeriodAndDuty(Pwm_SetPeriodAndDuty_Param1, Pwm_SetPeriodAndDuty_Param2, Pwm_SetPeriodAndDuty_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,           53u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,        24u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is not updated when channel number is invalid
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                = 14u
/// \input  Pwm_SetDutyCycle_Param2                = 1u
/// \input  FTM_DRV_SetChnCountVal_HitCount        = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_SetChnCountVal_HitCount        = 0u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_SetChnCountVal_HitCount        = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                = 14u; // invalid channel
  Pwm_SetDutyCycle_Param2                = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,          0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is not updated when channel number is out of range
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                = 15u
/// \input  Pwm_SetDutyCycle_Param2                = 1u
/// \input  FTM_DRV_SetChnCountVal_HitCount        = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_SetChnCountVal_HitCount        = 0u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_SetChnCountVal_HitCount        = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                = 15u; // out of range channel
  Pwm_SetDutyCycle_Param2                = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,        0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is not updated when channel number is invalid
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test, Fault injection
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                = 15u
/// \input  Pwm_SetDutyCycle_Param2                = 1u
/// \input  FTM_DRV_SetChnCountVal_HitCount        = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_SetChnCountVal_HitCount        = 0u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_SetChnCountVal_HitCount        = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                = 15u;
  Pwm_SetDutyCycle_Param2                = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,          0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated when complementary mode is active
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                   = 1u
/// \input  Pwm_SetDutyCycle_Param2                   = 1u
/// \input  g_ftmBase[0]->CONF                        = 23u
/// \input  FTM_DRV_SetChnCountVal_HitCount           = 0u
/// \input  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u
/// \input  FTM_DRV_SetChnCountVal_Param2             = 20u
/// \input  FTM_DRV_SetChnCountVal_Param3             = 10u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_SetChnCountVal_HitCount           = 2u
/// \output FTM_DRV_SetChnCountVal_Param1.CONF        = 23u
/// \output FTM_DRV_SetChnCountVal_Param2             = 7u
/// \output FTM_DRV_SetChnCountVal_Param3             = 0u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 23u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param2      = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF                        = 23u;
  FTM_DRV_SetChnCountVal_HitCount           = 0u;
  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u;
  FTM_DRV_SetChnCountVal_Param2             = 20u;
  FTM_DRV_SetChnCountVal_Param3             = 10u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                   = 1u;
  Pwm_SetDutyCycle_Param2                   = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,            2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param1.CONF,        23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param2,              7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param3,              0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF, 23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param2,       1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated when complementary mode is active
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                   = 2u
/// \input  Pwm_SetDutyCycle_Param2                   = 0x8000u
/// \input  g_ftmBase[0]->CONF                        = 23u
/// \input  FTM_DRV_GetMod_RetVal                     = 1u 
/// \input  FTM_DRV_GetMod_HitCount                   = 0u
/// \input  FTM_DRV_SetChnCountVal_HitCount           = 0u
/// \input  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u
/// \input  FTM_DRV_SetChnCountVal_Param2             = 20u
/// \input  FTM_DRV_SetChnCountVal_Param3             = 10u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                   = 1u
/// \output FTM_DRV_SetChnCountVal_HitCount           = 2u
/// \output FTM_DRV_SetChnCountVal_Param1.CONF        = 23u
/// \output FTM_DRV_SetChnCountVal_Param2             = 7u
/// \output FTM_DRV_SetChnCountVal_Param3             = 3u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 23u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param2      = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF                        = 23u;
  FTM_DRV_GetMod_RetVal                     = 1u; 
  FTM_DRV_GetMod_HitCount                   = 0u;
  FTM_DRV_SetChnCountVal_HitCount           = 0u;
  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u;
  FTM_DRV_SetChnCountVal_Param2             = 20u;
  FTM_DRV_SetChnCountVal_Param3             = 10u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                   = 2u;
  Pwm_SetDutyCycle_Param2                   = 0x8000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,            2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param1.CONF,        23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param2,              7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param3,              3u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF, 23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param2,       1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated when complementary mode is active
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                   = 2u
/// \input  Pwm_SetDutyCycle_Param2                   = 0x9000u
/// \input  g_ftmBase[0]->CONF                        = 23u
/// \input  FTM_DRV_GetMod_RetVal                     = 0u 
/// \input  FTM_DRV_GetMod_HitCount                   = 0u
/// \input  FTM_DRV_SetChnCountVal_HitCount           = 0u
/// \input  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u
/// \input  FTM_DRV_SetChnCountVal_Param2             = 20u
/// \input  FTM_DRV_SetChnCountVal_Param3             = 10u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                   = 1u
/// \output FTM_DRV_SetChnCountVal_HitCount           = 2u
/// \output FTM_DRV_SetChnCountVal_Param1.CONF        = 23u
/// \output FTM_DRV_SetChnCountVal_Param2             = 7u
/// \output FTM_DRV_SetChnCountVal_Param3             = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 23u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param2      = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF                        = 23u;
  FTM_DRV_GetMod_RetVal                     = 1u; 
  FTM_DRV_GetMod_HitCount                   = 0u;
  FTM_DRV_SetChnCountVal_HitCount           = 0u;
  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u;
  FTM_DRV_SetChnCountVal_Param2             = 20u;
  FTM_DRV_SetChnCountVal_Param3             = 10u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                   = 2u;
  Pwm_SetDutyCycle_Param2                   = 0x7900u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,            2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param1.CONF,        23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param2,              7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param3,              1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF, 23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param2,       1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated when complementary mode is active
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                   = 10u
/// \input  Pwm_SetDutyCycle_Param2                   = 0x7990u
/// \input  g_ftmBase[0]->CONF                        = 23u
/// \input  FTM_DRV_GetMod_RetVal                     = 1u
/// \input  FTM_DRV_GetMod_HitCount                   = 0u
/// \input  FTM_DRV_SetChnCountVal_HitCount           = 0u
/// \input  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u
/// \input  FTM_DRV_SetChnCountVal_Param2             = 20u
/// \input  FTM_DRV_SetChnCountVal_Param3             = 10u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                   = 1u
/// \output FTM_DRV_SetChnCountVal_HitCount           = 2u
/// \output FTM_DRV_SetChnCountVal_Param1.CONF        = 554u
/// \output FTM_DRV_SetChnCountVal_Param2             = 1u
/// \output FTM_DRV_SetChnCountVal_Param3             = 99u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 554u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param2      = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF                        = 23u;
  FTM_DRV_GetMod_RetVal                     = 1u; 
  FTM_DRV_GetMod_HitCount                   = 0u;
  FTM_DRV_SetChnCountVal_HitCount           = 0u;
  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u;
  FTM_DRV_SetChnCountVal_Param2             = 20u;
  FTM_DRV_SetChnCountVal_Param3             = 10u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                   = 10u;
  Pwm_SetDutyCycle_Param2                   = 0x7990u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,             2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param1.CONF,        554u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param2,               1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param3,              99u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,      1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF, 554u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param2,        1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetDutyCycle_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if pwm duty is updated when complementary mode is active
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant:  ASIL_B
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetDutyCycle_Param1                   = 9u
/// \input  Pwm_SetDutyCycle_Param2                   = 0x7990u
/// \input  g_ftmBase[0]->CONF                        = 23u
/// \input  FTM_DRV_GetMod_RetVal                     = 1u
/// \input  FTM_DRV_GetMod_HitCount                   = 0u
/// \input  FTM_DRV_SetChnCountVal_HitCount           = 0u
/// \input  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u
/// \input  FTM_DRV_SetChnCountVal_Param2             = 20u
/// \input  FTM_DRV_SetChnCountVal_Param3             = 10u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u
/// \input  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                   = 1u
/// \output FTM_DRV_SetChnCountVal_HitCount           = 2u
/// \output FTM_DRV_SetChnCountVal_Param1.CONF        = 554u
/// \output FTM_DRV_SetChnCountVal_Param2             = 1u
/// \output FTM_DRV_SetChnCountVal_Param3             = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 1u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 554u
/// \output FTM_DRV_SetSoftwareTriggerCmd_Param2      = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetDutyCycle_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF                        = 23u;
  FTM_DRV_GetMod_RetVal                     = 1u; 
  FTM_DRV_GetMod_HitCount                   = 0u;
  FTM_DRV_SetChnCountVal_HitCount           = 0u;
  FTM_DRV_SetChnCountVal_Param1.CONF        = 0u;
  FTM_DRV_SetChnCountVal_Param2             = 20u;
  FTM_DRV_SetChnCountVal_Param3             = 10u;
  FTM_DRV_SetSoftwareTriggerCmd_HitCount    = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF = 0u;
  FTM_DRV_SetSoftwareTriggerCmd_Param2      = 0u;

  // Step 2: Assign Input values
  Pwm_SetDutyCycle_Param1                   = 9u;
  Pwm_SetDutyCycle_Param2                   = 0x7990u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetDutyCycle(Pwm_SetDutyCycle_Param1, Pwm_SetDutyCycle_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_HitCount,             2u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param1.CONF,        554u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param2,               1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnCountVal_Param3,               1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_HitCount,      1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param1.CONF, 554u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetSoftwareTriggerCmd_Param2,        1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if duty is decreased by DUTY_ADJUSTMENT when duty is at 100%
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_CalculateChannelHwDuty_Param1 = 0x8000u
/// \input  Pwm_CalculateChannelHwDuty_Param2 = 0x8000u
///
/// - Expectations:
///
/// \output Pwm_CalculateChannelHwDuty_RetVal = 32763u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_CalculateChannelHwDuty_Param1 = 0x8000u;
  Pwm_CalculateChannelHwDuty_Param2 = 0x8000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_CalculateChannelHwDuty_RetVal = Pwm_CalculateChannelHwDuty(Pwm_CalculateChannelHwDuty_Param1, Pwm_CalculateChannelHwDuty_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_CalculateChannelHwDuty_RetVal, 32768u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if duty is kept when it is not at 100%
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_CalculateChannelHwDuty_Param1 = 0x4000u
/// \input  Pwm_CalculateChannelHwDuty_Param2 = 0x4000u
///
/// - Expectations:
///
/// \output Pwm_CalculateChannelHwDuty_RetVal = 32763u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_CalculateChannelHwDuty_Param1 = 0x4000u;
  Pwm_CalculateChannelHwDuty_Param2 = 0x4000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_CalculateChannelHwDuty_RetVal = Pwm_CalculateChannelHwDuty(Pwm_CalculateChannelHwDuty_Param1, Pwm_CalculateChannelHwDuty_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_CalculateChannelHwDuty_RetVal, 8192u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if duty is 0 when it exceeds maximum value
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_CalculateChannelHwDuty_Param1 = 0x9000u
///
/// - Expectations:
///
/// \output Pwm_CalculateChannelHwDuty_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_CalculateChannelHwDuty_Param1 = 0x9000u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_CalculateChannelHwDuty_RetVal = Pwm_CalculateChannelHwDuty(Pwm_CalculateChannelHwDuty_Param1, Pwm_CalculateChannelHwDuty_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_CalculateChannelHwDuty_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetChannelOutput_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if channel polarity is checked and output is set to high
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetChannelOutput_Param1.POL     = 1u
/// \input  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
/// \input  Pwm_SetChannelOutput_Param2         = 0u
/// \input  Pwm_SetChannelOutput_Param3         = PWM_HIGH
///
/// - Expectations:
///
/// \output Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetChannelOutput_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_SetChannelOutput_Param1.POL     = 1u;
  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u;
  Pwm_SetChannelOutput_Param2         = 0u;
  Pwm_SetChannelOutput_Param3         = PWM_HIGH; // 1U

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetChannelOutput(&Pwm_SetChannelOutput_Param1, Pwm_SetChannelOutput_Param2, Pwm_SetChannelOutput_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_SetChannelOutput_Param1.SWOCTRL, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetChannelOutput_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if channel polarity is checked and output is set to low
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetChannelOutput_Param1.POL     = 1u
/// \input  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
/// \input  Pwm_SetChannelOutput_Param2         = 0u
/// \input  Pwm_SetChannelOutput_Param3         = PWM_LOW
///
/// - Expectations:
///
/// \output Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetChannelOutput_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_SetChannelOutput_Param1.POL     = 1u;
  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u;
  Pwm_SetChannelOutput_Param2         = 0u;
  Pwm_SetChannelOutput_Param3         = PWM_LOW; // 0U

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetChannelOutput(&Pwm_SetChannelOutput_Param1, Pwm_SetChannelOutput_Param2, Pwm_SetChannelOutput_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_SetChannelOutput_Param1.SWOCTRL, 1u, == ); // 1 &= ~(1 << 8)
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetChannelOutput_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if channel polarity is checked and output is set to high
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetChannelOutput_Param1.POL     = 0u
/// \input  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
/// \input  Pwm_SetChannelOutput_Param2         = 0u
/// \input  Pwm_SetChannelOutput_Param3         = PWM_HIGH
///
/// - Expectations:
///
/// \output Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetChannelOutput_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_SetChannelOutput_Param1.POL     = 0u;
  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u;
  Pwm_SetChannelOutput_Param2         = 0u;
  Pwm_SetChannelOutput_Param3         = PWM_HIGH; // 1U

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetChannelOutput(&Pwm_SetChannelOutput_Param1, Pwm_SetChannelOutput_Param2, Pwm_SetChannelOutput_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_SetChannelOutput_Param1.SWOCTRL, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_SetChannelOutput_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if channel polarity is checked and output is set to low
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_SetChannelOutput_Param1.POL     = 0u
/// \input  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
/// \input  Pwm_SetChannelOutput_Param2         = 0u
/// \input  Pwm_SetChannelOutput_Param3         = PWM_LOW
///
/// - Expectations:
///
/// \output Pwm_SetChannelOutput_Param1.SWOCTRL = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_SetChannelOutput_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions

  // Step 2: Assign Input values
  Pwm_SetChannelOutput_Param1.POL     = 0u;
  Pwm_SetChannelOutput_Param1.SWOCTRL = 1u;
  Pwm_SetChannelOutput_Param2         = 0u;
  Pwm_SetChannelOutput_Param3         = PWM_LOW; // 0U

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_SetChannelOutput(&Pwm_SetChannelOutput_Param1, Pwm_SetChannelOutput_Param2, Pwm_SetChannelOutput_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_SetChannelOutput_Param1.SWOCTRL, 1u, == ); // 1 &= ~(1 << 8)
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_StartPwmChannel_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function finds the instance and the config indexes
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_StartPwmChannel_Param1                  = 0u
/// \input  g_ftmBase[0]->CONF                          = 61u
/// \input  FTM_DRV_ClearChnEventFlag_HitCount          = 0u
/// \input  FTM_DRV_ClearChnEventFlag_Param1.CONF       = 0u
/// \input  FTM_DRV_ClearChnEventFlag_Param2            = 15u
/// \input  FTM_DRV_EnablePwmChannelOutputs_HitCount    = 0u
/// \input  FTM_DRV_EnablePwmChannelOutputs_Param1.CONF = 0u
/// \input  FTM_DRV_EnablePwmChannelOutputs_Param2      = 15u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount      = 0u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF   = 0u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_Param2        = 15u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_Param3        = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_ClearChnEventFlag_HitCount          = 4u
/// \output FTM_DRV_ClearChnEventFlag_Param1.CONF       = 61u
/// \output FTM_DRV_ClearChnEventFlag_Param2            = 5u
/// \output FTM_DRV_EnablePwmChannelOutputs_HitCount    = 4u
/// \output FTM_DRV_EnablePwmChannelOutputs_Param1.CONF = 61u
/// \output FTM_DRV_EnablePwmChannelOutputs_Param2      = 5u
/// \output FTM_DRV_SetChnSoftwareCtrlCmd_HitCount      = 4u
/// \output FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF  = 61u
/// \output FTM_DRV_SetChnSoftwareCtrlCmd_Param2        = 5u
/// \output FTM_DRV_SetChnSoftwareCtrlCmd_Param3        = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_StartPwmChannel_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF                          = 61u;
  FTM_DRV_ClearChnEventFlag_HitCount          = 0u;
  FTM_DRV_ClearChnEventFlag_Param1.CONF       = 0u;
  FTM_DRV_ClearChnEventFlag_Param2            = 15u;
  FTM_DRV_EnablePwmChannelOutputs_HitCount    = 0u;
  FTM_DRV_EnablePwmChannelOutputs_Param1.CONF = 0u;
  FTM_DRV_EnablePwmChannelOutputs_Param2      = 15u;
  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount      = 0u;
  FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF   = 0u;
  FTM_DRV_SetChnSoftwareCtrlCmd_Param2        = 15u;
  FTM_DRV_SetChnSoftwareCtrlCmd_Param3        = 1u;

  // Step 2: Assign Input values
  Pwm_StartPwmChannel_Param1                  = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_StartPwmChannel(Pwm_StartPwmChannel_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_ClearChnEventFlag_HitCount,            1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_ClearChnEventFlag_Param1.CONF,        61u, == );
  AL_UNITTEST_CHECK(FTM_DRV_ClearChnEventFlag_Param2,              7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_EnablePwmChannelOutputs_HitCount,      1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_EnablePwmChannelOutputs_Param1.CONF,  61u, == );
  AL_UNITTEST_CHECK(FTM_DRV_EnablePwmChannelOutputs_Param2,        7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_HitCount,        1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF,    61u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_Param2,          7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_Param3,          0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_StartPwmChannel_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function finds the instance and the config indexes
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_StartPwmChannel_Param1                  = 15u
/// \input  FTM_DRV_ClearChnEventFlag_HitCount          = 0u
/// \input  FTM_DRV_EnablePwmChannelOutputs_HitCount    = 0u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount      = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_ClearChnEventFlag_HitCount          = 0u
/// \output FTM_DRV_EnablePwmChannelOutputs_HitCount    = 0u
/// \output FTM_DRV_SetChnSoftwareCtrlCmd_HitCount      = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_StartPwmChannel_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_ClearChnEventFlag_HitCount          = 0u;
  FTM_DRV_EnablePwmChannelOutputs_HitCount    = 0u;
  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount      = 0u;

  // Step 2: Assign Input values
  Pwm_StartPwmChannel_Param1                  = 15u; // only 14 channels configured in test

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_StartPwmChannel(Pwm_StartPwmChannel_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_ClearChnEventFlag_HitCount,            0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_EnablePwmChannelOutputs_HitCount,      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_HitCount,        0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function finds the instance and the config indexes
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_GetFreq_Param1                        = 0u
/// \input  Pwm_GetFreq_Param2                        = PWM_LOW
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount    = 0u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF = 0u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_Param2      = 15u
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_Param3      = 0u
/// \input  g_ftmBase[0]->CONF                        = 23u
///
/// - Expectations:
///
/// \output(FTM_DRV_SetChnSoftwareCtrlCmd_HitCount    = 4u
/// \output(FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF = 23u
/// \output(FTM_DRV_SetChnSoftwareCtrlCmd_Param2      = 5u
/// \output(FTM_DRV_SetChnSoftwareCtrlCmd_Param3      = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount    = 0u;
  FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF = 0u;
  FTM_DRV_SetChnSoftwareCtrlCmd_Param2      = 15u;
  FTM_DRV_SetChnSoftwareCtrlCmd_Param3      = 0u;
  g_ftmBase[0]->CONF                        = 23u;

  // Step 2: Assign Input values
  Pwm_GetFreq_Param1                        = 1u;
  Pwm_GetFreq_Param2                        = PWM_LOW;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_ClampPwmChannel(Pwm_GetFreq_Param1, Pwm_GetFreq_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_HitCount,          1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_Param1.CONF,      23u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_Param2,            7u, == );
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_Param3,            1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function finds the instance and the config indexes
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_GetFreq_Param1                     = 494967295u
/// \input  Pwm_GetFreq_Param2                     = PWM_LOW
/// \input  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount = 0u
///
/// - Expectations:
///
/// \output FTM_DRV_SetChnSoftwareCtrlCmd_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_SetChnSoftwareCtrlCmd_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_GetFreq_Param1                     = 494967295u;
  Pwm_GetFreq_Param2                     = PWM_LOW;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_ClampPwmChannel(Pwm_GetFreq_Param1, Pwm_GetFreq_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(FTM_DRV_SetChnSoftwareCtrlCmd_HitCount, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_GetFreq_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function gets counter initial value
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_GetFreq_Param1         = 1u
/// \input  Pwm_GetFreq_Param2         = 10u
/// \input  g_ftmBase[0]->CONF         = 11u
/// \input  FTM_DRV_GetMod_HitCount    = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF = 0u
/// \input  FTM_DRV_GetMod_RetVal      = 15u
///
/// - Expectations:
///
/// \output Pwm_GetFreq_Param2         = 15u
/// \output FTM_DRV_GetMod_HitCount    = 1u
/// \output FTM_DRV_GetMod_Param1.CONF = 11u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_GetFreq_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  g_ftmBase[0]->CONF         = 11u;
  FTM_DRV_GetMod_HitCount    = 0u;
  FTM_DRV_GetMod_Param1.CONF = 0u;
  FTM_DRV_GetMod_RetVal      = 15u;

  // Step 2: Assign Input values
  Pwm_GetFreq_Param1         = 1u;
  Pwm_GetFreq_Param2         = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_GetFreq(Pwm_GetFreq_Param1, &Pwm_GetFreq_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_GetFreq_Param2,             15u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,         1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,     11u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_Pwm_GetFreq_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function gets counter initial value
///
/// \Used Test Design Technique: ET (Exploratory Testing)
///
/// \FuSa Relevant: -
///
/// \Used Test method: Requirements-based test
///
/// - Preconditions:
///
/// \input  Pwm_GetFreq_Param1      = 100u
/// \input  Pwm_GetFreq_Param2      = 10u
/// \input  FTM_DRV_GetMod_HitCount = 0u
///
/// - Expectations:
///
/// \output Pwm_GetFreq_Param2      = 10u
/// \output FTM_DRV_GetMod_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_Pwm_GetFreq_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  // Step 1: Set pre-conditions
  FTM_DRV_GetMod_HitCount = 0u;

  // Step 2: Assign Input values
  Pwm_GetFreq_Param1      = 100u;
  Pwm_GetFreq_Param2      = 10u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Step 3: Call FUT
  Pwm_GetFreq(Pwm_GetFreq_Param1, &Pwm_GetFreq_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // Step 4: Check expected output values
  AL_UNITTEST_CHECK(Pwm_GetFreq_Param2,     10u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount, 0u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Enables the channel output
/// - Preconditions:
///
/// \input  FTM_DRV_ControlChannelOutput_Param1         = 1u
/// \input  FTM_DRV_ControlChannelOutput_Param2         = 10u
/// \input  FTM_DRV_ControlChannelOutput_Param3         = TRUE
/// \input  FTM_DRV_ControlChannelOutput_RetVal         = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_ControlChannelOutput_RetVal         = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_ControlChannelOutput_Param1         = 1u;
  FTM_DRV_ControlChannelOutput_Param2         = 10u;
  FTM_DRV_ControlChannelOutput_Param3         = TRUE;

  FTM_DRV_ControlChannelOutput_RetVal         = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_ControlChannelOutput_RetVal = FTM_DRV_ControlChannelOutput(FTM_DRV_ControlChannelOutput_Param1, FTM_DRV_ControlChannelOutput_Param2, FTM_DRV_ControlChannelOutput_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_ControlChannelOutput_RetVal,          0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Disables the channel output
/// - Preconditions:
///
/// \input  FTM_DRV_ControlChannelOutput_Param1         = 1u
/// \input  FTM_DRV_ControlChannelOutput_Param2         = 11u
/// \input  FTM_DRV_ControlChannelOutput_Param3         = TRUE
/// \input  FTM_DRV_ControlChannelOutput_RetVal         = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_ControlChannelOutput_RetVal         = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_ControlChannelOutput_Param1         = 1u;
  FTM_DRV_ControlChannelOutput_Param2         = 11u;
  FTM_DRV_ControlChannelOutput_Param3         = FALSE;

  FTM_DRV_ControlChannelOutput_RetVal         = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_ControlChannelOutput_RetVal = FTM_DRV_ControlChannelOutput(FTM_DRV_ControlChannelOutput_Param1, FTM_DRV_ControlChannelOutput_Param2, FTM_DRV_ControlChannelOutput_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_ControlChannelOutput_RetVal,          0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if -
/// - Preconditions:
///
/// \input  FTM_DRV_FastUpdatePwmChannels_Param1 = 1u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param2 = 1u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param3 = 1u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param4 = 50u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param5 = TRUE
/// \input  FTM_DRV_FastUpdatePwmChannels_RetVal = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_FastUpdatePwmChannels_RetVal  = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_FastUpdatePwmChannels_Param1 = 1u;
  FTM_DRV_FastUpdatePwmChannels_Param2 = 1u;
  FTM_DRV_FastUpdatePwmChannels_Param3 = 1u;
  FTM_DRV_FastUpdatePwmChannels_Param4 = 50u;
  FTM_DRV_FastUpdatePwmChannels_Param5 = TRUE;

  FTM_DRV_FastUpdatePwmChannels_RetVal = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_FastUpdatePwmChannels_RetVal = FTM_DRV_FastUpdatePwmChannels(FTM_DRV_FastUpdatePwmChannels_Param1, FTM_DRV_FastUpdatePwmChannels_Param2, &FTM_DRV_FastUpdatePwmChannels_Param3, &FTM_DRV_FastUpdatePwmChannels_Param4, FTM_DRV_FastUpdatePwmChannels_Param5);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_FastUpdatePwmChannels_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if -
/// - Preconditions:
///
/// \input  FTM_DRV_FastUpdatePwmChannels_Param1 = 1u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param2 = 1u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param3 = 1u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param4 = 50u
/// \input  FTM_DRV_FastUpdatePwmChannels_Param5 = FALSE
/// \input  FTM_DRV_FastUpdatePwmChannels_RetVal = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_FastUpdatePwmChannels_RetVal  = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_FastUpdatePwmChannels_Param1 = 1u;
  FTM_DRV_FastUpdatePwmChannels_Param2 = 1u;
  FTM_DRV_FastUpdatePwmChannels_Param3 = 1u;
  FTM_DRV_FastUpdatePwmChannels_Param4 = 50u;
  FTM_DRV_FastUpdatePwmChannels_Param5 = FALSE;

  FTM_DRV_FastUpdatePwmChannels_RetVal = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_FastUpdatePwmChannels_RetVal = FTM_DRV_FastUpdatePwmChannels(FTM_DRV_FastUpdatePwmChannels_Param1, FTM_DRV_FastUpdatePwmChannels_Param2, &FTM_DRV_FastUpdatePwmChannels_Param3, &FTM_DRV_FastUpdatePwmChannels_Param4, FTM_DRV_FastUpdatePwmChannels_Param5);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_FastUpdatePwmChannels_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function checks type of update,
///                        sets new modulo value and generate trigger
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmPeriod_Param1            = 1u
/// \input  FTM_DRV_UpdatePwmPeriod_Param2            = FTM_PWM_UPDATE_IN_TICKS
/// \input  FTM_DRV_UpdatePwmPeriod_Param3            = 128u
/// \input  FTM_DRV_UpdatePwmPeriod_Param4            = TRUE
/// \input  FTM_DRV_UpdatePwmPeriod_RetVal            = 1u
/// \input  ftmStatePtr[1u]->ftmMode                  = FTM_MODE_CEN_ALIGNED_PWM
/// \input  ftmStatePtr[1u]->ftmPeriod                = 0u
/// \input  g_ftmBase[1]->CONF                        = 22u
///
/// - Expectations:
///
/// \output FTM_DRV_UpdatePwmPeriod_RetVal            = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmPeriod_Param1            = 1u;
  FTM_DRV_UpdatePwmPeriod_Param2            = FTM_PWM_UPDATE_IN_TICKS;
  FTM_DRV_UpdatePwmPeriod_Param3            = 128u;
  FTM_DRV_UpdatePwmPeriod_Param4            = TRUE;
  FTM_DRV_UpdatePwmPeriod_RetVal            = 1u;

  ftmStatePtr[1u]->ftmMode                  = FTM_MODE_CEN_ALIGNED_PWM;
  ftmStatePtr[1u]->ftmPeriod                = 0u;
  g_ftmBase[1]->CONF                        = 22u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmPeriod_RetVal = FTM_DRV_UpdatePwmPeriod(FTM_DRV_UpdatePwmPeriod_Param1, FTM_DRV_UpdatePwmPeriod_Param2, FTM_DRV_UpdatePwmPeriod_Param3, FTM_DRV_UpdatePwmPeriod_Param4);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function checks type of update,
///                        sets new modulo value and generate trigger
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmPeriod_Param1            = 1u
/// \input  FTM_DRV_UpdatePwmPeriod_Param2            = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmPeriod_Param3            = 128u
/// \input  FTM_DRV_UpdatePwmPeriod_Param4            = TRUE
/// \input  FTM_DRV_UpdatePwmPeriod_RetVal            = 1u
/// \input  ftmStatePtr[1u]->ftmMode                  = FTM_MODE_QUADRATURE_DECODER
/// \input  ftmStatePtr[1u]->ftmPeriod                = 0u
/// \input  g_ftmBase[1]->CONF                        = 22u
/// \input  FTM_DRV_ConvertFreqToPeriodTicks_Param1   = 0u
/// \input  FTM_DRV_ConvertFreqToPeriodTicks_Param2   = 0u
/// \input  FTM_DRV_ConvertFreqToPeriodTicks_RetVal   = 128
///
/// - Expectations:
///
/// \output FTM_DRV_ConvertFreqToPeriodTicks_HitCount = 1u
/// \output FTM_DRV_ConvertFreqToPeriodTicks_Param1   = 1u
/// \output FTM_DRV_ConvertFreqToPeriodTicks_Param2   = 127u
/// \output FTM_DRV_UpdatePwmPeriod_RetVal            = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmPeriod_Param1            = 1u;
  FTM_DRV_UpdatePwmPeriod_Param2            = FTM_PWM_UPDATE_IN_DUTY_CYCLE;
  FTM_DRV_UpdatePwmPeriod_Param3            = 128u;
  FTM_DRV_UpdatePwmPeriod_Param4            = TRUE;
  FTM_DRV_UpdatePwmPeriod_RetVal            = 1u;

  ftmStatePtr[1u]->ftmMode                  = FTM_MODE_QUADRATURE_DECODER;
  ftmStatePtr[1u]->ftmPeriod                = 0u;
  ftmStatePtr[1u]->ftmSourceClockFrequency  = 130u;
  g_ftmBase[1]->CONF                        = 22u;

  FTM_DRV_ConvertFreqToPeriodTicks_HitCount = 0u;
  FTM_DRV_ConvertFreqToPeriodTicks_Param1   = 0u;
  FTM_DRV_ConvertFreqToPeriodTicks_Param2   = 0u;
  FTM_DRV_ConvertFreqToPeriodTicks_RetVal   = 128;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmPeriod_RetVal = FTM_DRV_UpdatePwmPeriod(FTM_DRV_UpdatePwmPeriod_Param1, FTM_DRV_UpdatePwmPeriod_Param2, FTM_DRV_UpdatePwmPeriod_Param3, FTM_DRV_UpdatePwmPeriod_Param4);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_ConvertFreqToPeriodTicks_HitCount,    1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_ConvertFreqToPeriodTicks_Param1,      1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_ConvertFreqToPeriodTicks_Param2,    128u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function checks type of update,
///                        and returns status error
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmPeriod_Param1            = 1u
/// \input  FTM_DRV_UpdatePwmPeriod_Param2            = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmPeriod_Param3            = 128u
/// \input  FTM_DRV_UpdatePwmPeriod_Param4            = TRUE
/// \input  FTM_DRV_UpdatePwmPeriod_RetVal            = 0u
/// \input  ftmStatePtr[1u]->ftmMode                  = FTM_MODE_QUADRATURE_DECODER
/// \input  ftmStatePtr[1u]->ftmPeriod                = 0u
/// \input  g_ftmBase[1]->CONF                        = 22u
/// \input  FTM_DRV_ConvertFreqToPeriodTicks_Param1   = 0u
/// \input  FTM_DRV_ConvertFreqToPeriodTicks_Param2   = 0u
/// \input  FTM_DRV_ConvertFreqToPeriodTicks_RetVal   = 128
///
/// - Expectations:
///
/// \output FTM_DRV_ConvertFreqToPeriodTicks_HitCount = 0u
/// \output FTM_DRV_ConvertFreqToPeriodTicks_Param1   = 0u
/// \output FTM_DRV_ConvertFreqToPeriodTicks_Param2   = 0u
/// \output FTM_DRV_UpdatePwmPeriod_RetVal            = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmPeriod_Param1            = 1u;
  FTM_DRV_UpdatePwmPeriod_Param2            = FTM_PWM_UPDATE_IN_DUTY_CYCLE;
  FTM_DRV_UpdatePwmPeriod_Param3            = 128u;
  FTM_DRV_UpdatePwmPeriod_Param4            = TRUE;
  FTM_DRV_UpdatePwmPeriod_RetVal            = 0u;

  ftmStatePtr[1u]->ftmMode                  = FTM_MODE_QUADRATURE_DECODER;
  ftmStatePtr[1u]->ftmPeriod                = 0u;
  ftmStatePtr[1u]->ftmSourceClockFrequency  = 120u;
  g_ftmBase[1]->CONF                        = 22u;

  FTM_DRV_ConvertFreqToPeriodTicks_HitCount = 0u;
  FTM_DRV_ConvertFreqToPeriodTicks_Param1   = 0u;
  FTM_DRV_ConvertFreqToPeriodTicks_Param2   = 0u;
  FTM_DRV_ConvertFreqToPeriodTicks_RetVal   = 128;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmPeriod_RetVal = FTM_DRV_UpdatePwmPeriod(FTM_DRV_UpdatePwmPeriod_Param1, FTM_DRV_UpdatePwmPeriod_Param2, FTM_DRV_UpdatePwmPeriod_Param3, FTM_DRV_UpdatePwmPeriod_Param4);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_ConvertFreqToPeriodTicks_HitCount,    0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_ConvertFreqToPeriodTicks_Param1,      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_ConvertFreqToPeriodTicks_Param2,      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmPeriod_RetVal,               1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 0x8000u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 0x4000u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_CEN_ALIGNED_PWM
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 2u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE;
  FTM_DRV_UpdatePwmChannel_Param4             = 0x8000u;
  FTM_DRV_UpdatePwmChannel_Param5             = 0x4000u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  g_ftmBase[2]->COMBINE                       = 0xFFFFu;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_CEN_ALIGNED_PWM;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 0x8000u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 0x4000u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_EDGE_ALIGNED_PWM
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 8u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE;
  FTM_DRV_UpdatePwmChannel_Param4             = 0x4000u;
  FTM_DRV_UpdatePwmChannel_Param5             = 0x4000u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  g_ftmBase[2]->SC                            = 18u;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_EDGE_ALIGNED_PWM;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 0x8000u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 0x4000u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_UP_DOWN_TIMER
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 8u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE;
  FTM_DRV_UpdatePwmChannel_Param4             = 0x9000u;
  FTM_DRV_UpdatePwmChannel_Param5             = 0x4000u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_UP_DOWN_TIMER;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_EDGE_ALIGNED_PWM
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 8u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_TICKS;
  FTM_DRV_UpdatePwmChannel_Param4             = 1u;
  FTM_DRV_UpdatePwmChannel_Param5             = 1u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  g_ftmBase[2]->COMBINE                       = 0x15u;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_CEN_ALIGNED_PWM;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_EDGE_ALIGNED_PWM
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 8u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_TICKS;
  FTM_DRV_UpdatePwmChannel_Param4             = 1u;
  FTM_DRV_UpdatePwmChannel_Param5             = 1u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  g_ftmBase[2]->SC                            = 0x200u;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_CEN_ALIGNED_PWM;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_EDGE_ALIGNED_PWM
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 8u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_TICKS;
  FTM_DRV_UpdatePwmChannel_Param4             = 1u;
  FTM_DRV_UpdatePwmChannel_Param5             = 1u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  g_ftmBase[2]->SC                            = 0u;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_CEN_ALIGNED_PWM;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle of PWM output
///
/// - Preconditions:
///
/// \input  FTM_DRV_UpdatePwmChannel_Param1             = 2u
/// \input  FTM_DRV_UpdatePwmChannel_Param2             = 8u
/// \input  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_DUTY_CYCLE
/// \input  FTM_DRV_UpdatePwmChannel_Param4             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = 1u
/// \input  FTM_DRV_UpdatePwmChannel_Param5             = TRUE
/// \input  g_ftmBase[2]->CONF                          = 22u
/// \input  ftmStatePtr[2]->ftmMode                     = FTM_MODE_EDGE_ALIGNED_PWM
/// \input  FTM_DRV_GetMod_HitCount                     = 0u
/// \input  FTM_DRV_GetMod_Param1.CONF                  = 0u
/// \input  FTM_DRV_GetMod_RetVal                       = 128u
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 1u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_UpdatePwmChannel_RetVal              = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_UpdatePwmChannel_Param1             = 2u;
  FTM_DRV_UpdatePwmChannel_Param2             = 8u;
  FTM_DRV_UpdatePwmChannel_Param3             = FTM_PWM_UPDATE_IN_TICKS;
  FTM_DRV_UpdatePwmChannel_Param4             = 0x8000u;
  FTM_DRV_UpdatePwmChannel_Param5             = 0x8000u;
  FTM_DRV_UpdatePwmChannel_Param5             = TRUE;
  FTM_DRV_UpdatePwmChannel_RetVal             = 10u;

  g_ftmBase[2]->CONF                          = 22u;
  ftmStatePtr[2]->ftmMode                     = FTM_MODE_CEN_ALIGNED_PWM;

  FTM_DRV_GetMod_HitCount                     = 0u;
  FTM_DRV_GetMod_Param1.CONF                  = 0u;
  FTM_DRV_GetMod_RetVal                       = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_UpdatePwmChannel_RetVal = FTM_DRV_UpdatePwmChannel(FTM_DRV_UpdatePwmChannel_Param1, FTM_DRV_UpdatePwmChannel_Param2, FTM_DRV_UpdatePwmChannel_Param3, FTM_DRV_UpdatePwmChannel_Param4, FTM_DRV_UpdatePwmChannel_Param5, FTM_DRV_UpdatePwmChannel_Param6);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_UpdatePwmChannel_RetVal,               1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_DeinitPwm_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Stops all PWM channels
///
/// - Preconditions:
///
/// \input  FTM_DRV_DeinitPwm_Param1                     = 2u
/// \input  g_ftmBase[2]->CONF                           = 22u
/// \input  FTM_DRV_DeinitPwm_RetVal                     = 1u
///
/// - Expectations:
///
/// \output FTM_DRV_DeinitPwm_RetVal,                    =  0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_DeinitPwm_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  FTM_DRV_DeinitPwm_Param1                     = 2u;
  g_ftmBase[2]->CONF                           = 22u;
  FTM_DRV_DeinitPwm_RetVal                     = 1u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_DeinitPwm_RetVal = FTM_DRV_DeinitPwm(FTM_DRV_DeinitPwm_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_DeinitPwm_RetVal,                       0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwm_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Configures duty cycle and frequency and starts outputting
///                        PWM on specified channels.
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 0x9000u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 0x9000u;
/// \input  FTM_DRV_InitPwm_Param1                                                                  = 3u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_INPUT_CAPTURE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_MAN_EVEN;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = TRUE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig[0].uDutyCyclePercent                 = 0x9000u;
/// \input  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig[1].uDutyCyclePercent                 = 0x9000u;
/// \input  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2u;
/// \input  FTM_DRV_InitPwm_Param2.nNumCombinedPwmChannels                                          = 2u;
/// \input  g_ftmBase[3]->CONF                                                                      = 22u;
/// \input  g_ftmBase[3]->FLTCTRL                                                                   = 22u;
/// \input  g_ftmBase[3]->FLTPOL                                                                    = 22u;
/// \input  ftmStatePtr[3]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;
/// \input  FTM_DRV_GetMod_HitCount                                                                 = 0u;
/// \input  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
/// \input  FTM_DRV_GetMod_RetVal                                                                   = 128u;
/// \input  FTM_DRV_InitPwm_RetVal                                                                  = 3u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_InitPwm_RetVal                       =  1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwm_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 0x9000u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 0x9000u;

  FTM_DRV_InitPwm_Param1                                                                  = 3u;
  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_INPUT_CAPTURE;
  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_MAN_EVEN;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = TRUE;
  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig[0].uDutyCyclePercent                 = 0x9000u;
  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig[1].uDutyCyclePercent                 = 0x9000u;
  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2u;
  FTM_DRV_InitPwm_Param2.nNumCombinedPwmChannels                                          = 2u;

  g_ftmBase[3]->CONF                                                                      = 22u;
  g_ftmBase[3]->FLTCTRL                                                                   = 22u;
  g_ftmBase[3]->FLTPOL                                                                    = 22u;
  ftmStatePtr[3]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;

  FTM_DRV_GetMod_HitCount                                                                 = 0u;
  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
  FTM_DRV_GetMod_RetVal                                                                   = 128u;
  FTM_DRV_InitPwm_RetVal                                                                  = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwm_RetVal = FTM_DRV_InitPwm(FTM_DRV_InitPwm_Param1, &FTM_DRV_InitPwm_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       4u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_InitPwm_RetVal,                        1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwm_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Configures duty cycle and frequency and starts outputting
///                        PWM on specified channels.
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwm_Param1                                                                  = 4u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_CEN_ALIGNED_PWM;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_MAN_EVEN;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = FALSE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmFaultInterrupt                                   = TRUE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2U;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;
/// \input  g_ftmBase[4]->CONF                                                                      = 22u;
/// \input  g_ftmBase[4]->FLTCTRL                                                                   = 22u;
/// \input  g_ftmBase[4]->FLTPOL                                                                    = 22u;
/// \input  ftmStatePtr[4]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;
/// \input  FTM_DRV_InitPwm_RetVal                                                                  = 3u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_InitPwm_RetVal                       =  1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwm_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;

  FTM_DRV_InitPwm_Param1                                                                  = 4u;
  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_CEN_ALIGNED_PWM;
  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_MAN_EVEN;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = FALSE;
  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmFaultInterrupt                                   = TRUE;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2U;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;

  g_ftmBase[4]->CONF                                                                      = 22u;
  g_ftmBase[4]->FLTCTRL                                                                   = 22u;
  g_ftmBase[4]->FLTPOL                                                                    = 22u;
  ftmStatePtr[4]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;
  FTM_DRV_InitPwm_RetVal                                                                  = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwm_RetVal = FTM_DRV_InitPwm(FTM_DRV_InitPwm_Param1, &FTM_DRV_InitPwm_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                       8u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_InitPwm_RetVal,                        0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwm_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Configures duty cycle and frequency and starts outputting
///                        PWM on specified channels.
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwm_Param1                                                                  = 4u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_CEN_ALIGNED_PWM;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_MAN_EVEN;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = FALSE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmFaultInterrupt                                   = TRUE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2U;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;
/// \input  g_ftmBase[4]->CONF                                                                      = 22u;
/// \input  g_ftmBase[4]->FLTCTRL                                                                   = 22u;
/// \input  g_ftmBase[4]->FLTPOL                                                                    = 22u;
/// \input  ftmStatePtr[4]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;
/// \input  FTM_DRV_InitPwm_RetVal                                                                  = 3u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_InitPwm_RetVal                       =  1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwm_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[0].secondChannelPolarity                                    = FTM_MAIN_INVERTED;
  pwmIndependentChannelConfig[1].secondChannelPolarity                                    = FTM_MAIN_INVERTED;

  FTM_DRV_InitPwm_Param1                                                                  = 4u;
  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_CEN_ALIGNED_PWM;
  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_DISABLED;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = FALSE;
  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmFaultInterrupt                                   = TRUE;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2U;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;

  g_ftmBase[4]->CONF                                                                      = 22u;
  g_ftmBase[4]->FLTCTRL                                                                   = 22u;
  g_ftmBase[4]->FLTPOL                                                                    = 22u;
  ftmStatePtr[4]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;
  FTM_DRV_InitPwm_RetVal                                                                  = 3u;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwm_RetVal = FTM_DRV_InitPwm(FTM_DRV_InitPwm_Param1, &FTM_DRV_InitPwm_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                      12u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_InitPwm_RetVal,                        0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwm_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if function Configures duty cycle and frequency and starts outputting
///                        PWM on specified channels.
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwm_Param1                                                                  = 4u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_CEN_ALIGNED_PWM;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_MAN_EVEN;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = FALSE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->pwmFaultInterrupt                                   = TRUE;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
/// \input  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
/// \input  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2U;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;
/// \input  g_ftmBase[4]->CONF                                                                      = 22u;
/// \input  g_ftmBase[4]->FLTCTRL                                                                   = 22u;
/// \input  g_ftmBase[4]->FLTPOL                                                                    = 22u;
/// \input  ftmStatePtr[4]->ftmMode                                                                 = FTM_MODE_NOT_INITIALIZED;
/// \input  FTM_DRV_InitPwm_RetVal                                                                  = 3u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_InitPwm_RetVal                       =  1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwm_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;

  FTM_DRV_InitPwm_Param1                                                                  = 4u;
  FTM_DRV_InitPwm_Param2.faultConfig                                                      = &faultConfig;
  FTM_DRV_InitPwm_Param2.pwmCombinedChannelConfig                                         = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwm_Param2.pwmIndependentChannelConfig                                      = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwm_Param2.mode                                                             = FTM_MODE_CEN_ALIGNED_PWM;
  FTM_DRV_InitPwm_Param2.faultConfig->faultMode                                           = FTM_FAULT_CONTROL_DISABLED;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmOutputStateOnFault                               = FALSE;
  FTM_DRV_InitPwm_Param2.faultConfig->faultFilterValue                                    = 32u;
  FTM_DRV_InitPwm_Param2.faultConfig->pwmFaultInterrupt                                   = TRUE;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultChannelEnabled        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[2u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[3u].faultChannelEnabled        = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].faultFilterEnabled         = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].faultFilterEnabled         = 0u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[0u].ftmFaultPinPolarity        = 1u;
  FTM_DRV_InitPwm_Param2.faultConfig->ftmFaultChannelParam[1u].ftmFaultPinPolarity        = 0u;
  FTM_DRV_InitPwm_Param2.nNumIndependentPwmChannels                                       = 2U;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;

  g_ftmBase[4]->CONF                                                                      = 22u;
  g_ftmBase[4]->FLTCTRL                                                                   = 22u;
  g_ftmBase[4]->FLTPOL                                                                    = 22u;
  ftmStatePtr[4]->ftmMode                                                                 = FTM_MODE_INPUT_CAPTURE;
  FTM_DRV_InitPwm_RetVal                                                                  = 3u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwm_RetVal = FTM_DRV_InitPwm(FTM_DRV_InitPwm_Param1, &FTM_DRV_InitPwm_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                      12u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                   22u, == );
  AL_UNITTEST_CHECK(FTM_DRV_InitPwm_RetVal,                        1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwmDutyCycleChannel_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function updates the duty cycle for the PWM signal
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param1                                                  = 2u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.faultConfig                                      = &faultConfig;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.pwmCombinedChannelConfig                         = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.pwmIndependentChannelConfig                      = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.deadTimePrescaler                                = 3u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.deadTimeValue                                    = 3u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.counterInitValue                                 = 32U;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.mode                                             = 4u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_Param2.uFrequencyHZ                                     = 20u;
/// \input  g_ftmBase[2]->CONF                                                                      = 22u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 3u;
/// \input  FTM_DRV_GetMod_HitCount                                                                 = 0u;
/// \input  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
/// \input  FTM_DRV_GetMod_RetVal                                                                   = 128u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 22u
/// \output FTM_DRV_InitPwmDutyCycleChannel_RetVal       =  1u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwmDutyCycleChannel_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;

  FTM_DRV_InitPwmDutyCycleChannel_Param1                                                  = 2u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumIndependentPwmChannels                       = 2u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.nNumCombinedPwmChannels                          = 2u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.faultConfig                                      = &faultConfig;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.pwmCombinedChannelConfig                         = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.pwmIndependentChannelConfig                      = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.deadTimePrescaler                                = 3u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.deadTimeValue                                    = 3u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.counterInitValue                                 = 32U;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.mode                                             = 4u;
  FTM_DRV_InitPwmDutyCycleChannel_Param2.uFrequencyHZ                                     = 20u;

  g_ftmBase[2]->CONF                                                                      = 22u;
  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 3u;
  FTM_DRV_GetMod_HitCount                                                                 = 0u;
  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
  FTM_DRV_GetMod_RetVal                                                                   = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwmDutyCycleChannel_RetVal = FTM_DRV_InitPwmDutyCycleChannel(FTM_DRV_InitPwmDutyCycleChannel_Param1, &FTM_DRV_InitPwmDutyCycleChannel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_InitPwmDutyCycleChannel_RetVal,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                                      4u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                                  22u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Configures the PWM signal for the combined channel
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].mainChannelSafeState                                        = 0u;
/// \input  pwmCombinedChannelConfig[0].mainChannelPolarity                                         = 1u;
/// \input  pwmCombinedChannelConfig[1].mainChannelSafeState                                        = 1u;
/// \input  pwmCombinedChannelConfig[1].mainChannelPolarity                                         = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param1                                                   = 1u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.nNumIndependentPwmChannels                        = 2u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.nNumCombinedPwmChannels                           = 2u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig                                       = &faultConfig;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.pwmCombinedChannelConfig                          = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.pwmIndependentChannelConfig                       = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimePrescaler                                 = 3u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimeValue                                     = 3u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.counterInitValue                                  = 32U;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.mode                                              = 4u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.uFrequencyHZ                                      = 20u;
/// \input  g_ftmBase[1]->CONF                                                                      = 22u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 3u;
/// \input  FTM_DRV_GetMod_HitCount                                                                 = 0u;
/// \input  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
/// \input  FTM_DRV_GetMod_RetVal                                                                   = 128u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 3u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 0u
/// \output FTM_DRV_InitPwmDutyCycleChannel_RetVal       = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 1u;
  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 1u;
  pwmCombinedChannelConfig[0].mainChannelSafeState                                        = 0u;
  pwmCombinedChannelConfig[0].mainChannelPolarity                                         = 1u;
  pwmCombinedChannelConfig[1].mainChannelSafeState                                        = 1u;
  pwmCombinedChannelConfig[1].mainChannelPolarity                                         = 1u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;

  FTM_DRV_InitPwmCombinedChannel_Param1                                                   = 1u;
  FTM_DRV_InitPwmCombinedChannel_Param2.nNumIndependentPwmChannels                        = 2u;
  FTM_DRV_InitPwmCombinedChannel_Param2.nNumCombinedPwmChannels                           = 2u;
  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig                                       = &faultConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.pwmCombinedChannelConfig                          = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.pwmIndependentChannelConfig                       = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimePrescaler                                 = 3u;
  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimeValue                                     = 3u;
  FTM_DRV_InitPwmCombinedChannel_Param2.counterInitValue                                  = 32U;
  FTM_DRV_InitPwmCombinedChannel_Param2.mode                                              = 4u;
  FTM_DRV_InitPwmCombinedChannel_Param2.uFrequencyHZ                                      = 20u;

  g_ftmBase[1]->CONF                                                                      = 22u;
  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 3u;
  FTM_DRV_GetMod_HitCount                                                                 = 0u;
  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
  FTM_DRV_GetMod_RetVal                                                                   = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwmCombinedChannel(FTM_DRV_InitPwmCombinedChannel_Param1, &FTM_DRV_InitPwmCombinedChannel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_InitPwmDutyCycleChannel_RetVal,                       3u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                                      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function Configures the PWM signal for the combined channel
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].mainChannelSafeState                                        = 0u;
/// \input  pwmCombinedChannelConfig[0].mainChannelPolarity                                         = 1u;
/// \input  pwmCombinedChannelConfig[1].mainChannelSafeState                                        = 1u;
/// \input  pwmCombinedChannelConfig[1].mainChannelPolarity                                         = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param1                                                   = 1u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.nNumIndependentPwmChannels                        = 2u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.nNumCombinedPwmChannels                           = 2u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig                                       = &faultConfig;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.pwmCombinedChannelConfig                          = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.pwmIndependentChannelConfig                       = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimePrescaler                                 = 3u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimeValue                                     = 3u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.counterInitValue                                  = 32U;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.mode                                              = 4u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.uFrequencyHZ                                      = 20u;
/// \input  g_ftmBase[1]->CONF                                                                      = 22u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 3u;
/// \input  FTM_DRV_GetMod_HitCount                                                                 = 0u;
/// \input  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
/// \input  FTM_DRV_GetMod_RetVal                                                                   = 128u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 0u
/// \output FTM_DRV_InitPwmDutyCycleChannel_RetVal       = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 1u;
  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 1u;
  pwmCombinedChannelConfig[0].mainChannelSafeState                                        = 1u;
  pwmCombinedChannelConfig[0].mainChannelPolarity                                         = 1u;
  pwmCombinedChannelConfig[1].mainChannelSafeState                                        = 1u;
  pwmCombinedChannelConfig[1].mainChannelPolarity                                         = 1u;
  pwmCombinedChannelConfig[0].secondChannelSafeState                                      = 0u;
  pwmCombinedChannelConfig[1].secondChannelSafeState                                      = 1u;
  pwmCombinedChannelConfig[1].secondChannelPolarity                                       = FTM_MAIN_DUPLICATED;
  pwmCombinedChannelConfig[0].secondChannelPolarity                                       = FTM_MAIN_INVERTED;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;

  FTM_DRV_InitPwmCombinedChannel_Param1                                                   = 1u;
  FTM_DRV_InitPwmCombinedChannel_Param2.nNumIndependentPwmChannels                        = 2u;
  FTM_DRV_InitPwmCombinedChannel_Param2.nNumCombinedPwmChannels                           = 2u;
  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig                                       = &faultConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.pwmCombinedChannelConfig                          = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.pwmIndependentChannelConfig                       = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimePrescaler                                 = 3u;
  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimeValue                                     = 3u;
  FTM_DRV_InitPwmCombinedChannel_Param2.counterInitValue                                  = 32U;
  FTM_DRV_InitPwmCombinedChannel_Param2.mode                                              = 4u;
  FTM_DRV_InitPwmCombinedChannel_Param2.uFrequencyHZ                                      = 20u;

  g_ftmBase[1]->CONF                                                                      = 22u;
  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 1u;
  FTM_DRV_GetMod_HitCount                                                                 = 0u;
  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
  FTM_DRV_GetMod_RetVal                                                                   = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwmCombinedChannel(FTM_DRV_InitPwmCombinedChannel_Param1, &FTM_DRV_InitPwmCombinedChannel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_InitPwmDutyCycleChannel_RetVal,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                                      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function Configures the PWM signal for the combined channel
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].mainChannelSafeState                                        = 0u;
/// \input  pwmCombinedChannelConfig[0].mainChannelPolarity                                         = 1u;
/// \input  pwmCombinedChannelConfig[1].mainChannelSafeState                                        = 1u;
/// \input  pwmCombinedChannelConfig[1].mainChannelPolarity                                         = 1u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param1                                                   = 1u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.nNumIndependentPwmChannels                        = 2u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.nNumCombinedPwmChannels                           = 2u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig                                       = &faultConfig;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.pwmCombinedChannelConfig                          = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.pwmIndependentChannelConfig                       = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimePrescaler                                 = 3u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimeValue                                     = 3u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.counterInitValue                                  = 32U;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.mode                                              = 4u;
/// \input  FTM_DRV_InitPwmCombinedChannel_Param2.uFrequencyHZ                                      = 20u;
/// \input  g_ftmBase[1]->CONF                                                                      = 22u;
/// \input  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 3u;
/// \input  FTM_DRV_GetMod_HitCount                                                                 = 0u;
/// \input  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
/// \input  FTM_DRV_GetMod_RetVal                                                                   = 128u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      =  4u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 0u
/// \output FTM_DRV_InitPwmDutyCycleChannel_RetVal       = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 0u;
  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 0u;
  pwmCombinedChannelConfig[0].mainChannelSafeState                                        = 1u;
  pwmCombinedChannelConfig[0].mainChannelPolarity                                         = 1u;
  pwmCombinedChannelConfig[1].mainChannelSafeState                                        = 1u;
  pwmCombinedChannelConfig[1].mainChannelPolarity                                         = 1u;
  pwmCombinedChannelConfig[0].secondChannelSafeState                                      = 0u;
  pwmCombinedChannelConfig[1].secondChannelSafeState                                      = 1u;
  pwmCombinedChannelConfig[1].secondChannelPolarity                                       = FTM_MAIN_DUPLICATED;
  pwmCombinedChannelConfig[0].secondChannelPolarity                                       = FTM_MAIN_INVERTED;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;

  FTM_DRV_InitPwmCombinedChannel_Param1                                                   = 1u;
  FTM_DRV_InitPwmCombinedChannel_Param2.nNumIndependentPwmChannels                        = 2u;
  FTM_DRV_InitPwmCombinedChannel_Param2.nNumCombinedPwmChannels                           = 2u;
  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig                                       = &faultConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.pwmCombinedChannelConfig                          = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.pwmIndependentChannelConfig                       = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwmCombinedChannel_Param2.faultConfig->faultMode                            = FTM_FAULT_CONTROL_MAN_EVEN;
  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimePrescaler                                 = 3u;
  FTM_DRV_InitPwmCombinedChannel_Param2.deadTimeValue                                     = 3u;
  FTM_DRV_InitPwmCombinedChannel_Param2.counterInitValue                                  = 32U;
  FTM_DRV_InitPwmCombinedChannel_Param2.mode                                              = 4u;
  FTM_DRV_InitPwmCombinedChannel_Param2.uFrequencyHZ                                      = 20u;

  g_ftmBase[1]->CONF                                                                      = 22u;
  FTM_DRV_InitPwmDutyCycleChannel_RetVal                                                  = 1u;
  FTM_DRV_GetMod_HitCount                                                                 = 0u;
  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
  FTM_DRV_GetMod_RetVal                                                                   = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwmCombinedChannel(FTM_DRV_InitPwmCombinedChannel_Param1, &FTM_DRV_InitPwmCombinedChannel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_InitPwmDutyCycleChannel_RetVal,                       1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                                      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalPwm_FTM_DRV_InitPwmIndependentChannel_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if function Configures the PWM signal for the independent channel
///
/// - Preconditions:
///
/// \input  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
/// \input  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
/// \input  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
/// \input  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 0u;
/// \input  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 0u;
/// \input  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
/// \input  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
/// \input  pwmIndependentChannelConfig[1].safeState                                                = 1u;
/// \input  pwmIndependentChannelConfig[1].polarity                                                 = 0u;
/// \input  pwmIndependentChannelConfig[1].enableSecondChannelOutput                                = 1u;
/// \input  pwmIndependentChannelConfig[0].enableSecondChannelOutput                                = 1u;
/// \input  pwmIndependentChannelConfig[0].secondChannelPolarity                                    = FTM_MAIN_INVERTED;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param1                                                = 1u;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.nNumIndependentPwmChannels                     = 2u;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.nNumCombinedPwmChannels                        = 2u;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.faultConfig                                    = &faultConfig;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.pwmCombinedChannelConfig                       = &pwmCombinedChannelConfig;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.pwmIndependentChannelConfig                    = &pwmIndependentChannelConfig
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.faultConfig->faultMode                         = FTM_FAULT_CONTROL_MAN_EVEN;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.deadTimePrescaler                              = 3u;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.deadTimeValue                                  = 3u;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.counterInitValue                               = 32U;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.mode                                           = 4u;
/// \input  FTM_DRV_InitPwmIndependentChannel_Param2.uFrequencyHZ                                   = 20u;
/// \input  g_ftmBase[1]->CONF                                                                      = 22u;
/// \input  FTM_DRV_GetMod_HitCount                                                                 = 0u;
/// \input  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
/// \input  FTM_DRV_GetMod_RetVal                                                                   = 128u;
///
/// - Expectations:
///
/// \output FTM_DRV_GetMod_HitCount                      = 0u
/// \output FTM_DRV_GetMod_Param1.CONF                   = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalPwm_FTM_DRV_InitPwmIndependentChannel_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  ftm_combined_ch_param_t    pwmCombinedChannelConfig[8U >> 1U];
  ftm_independent_ch_param_t pwmIndependentChannelConfig[8U];
  pwmCombinedChannelConfig[0].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[0].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[0].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[1].hwChannelId                                                 = 1u;
  pwmCombinedChannelConfig[1].firstEdge                                                   = 1u;
  pwmCombinedChannelConfig[1].secondEdge                                                  = 1u;
  pwmCombinedChannelConfig[0].enableSecondChannelOutput                                   = 0u;
  pwmCombinedChannelConfig[1].enableSecondChannelOutput                                   = 0u;
  pwmIndependentChannelConfig[0].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[0].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].hwChannelId                                              = 1u;
  pwmIndependentChannelConfig[1].uDutyCyclePercent                                        = 1u;
  pwmIndependentChannelConfig[1].safeState                                                = 1u;
  pwmIndependentChannelConfig[1].polarity                                                 = 0u;
  pwmIndependentChannelConfig[1].enableSecondChannelOutput                                = 1u;
  pwmIndependentChannelConfig[0].enableSecondChannelOutput                                = 1u;
  pwmIndependentChannelConfig[0].secondChannelPolarity                                    = FTM_MAIN_INVERTED;

  FTM_DRV_InitPwmIndependentChannel_Param1                                                = 1u;
  FTM_DRV_InitPwmIndependentChannel_Param2.nNumIndependentPwmChannels                     = 2u;
  FTM_DRV_InitPwmIndependentChannel_Param2.nNumCombinedPwmChannels                        = 2u;
  FTM_DRV_InitPwmIndependentChannel_Param2.faultConfig                                    = &faultConfig;
  FTM_DRV_InitPwmIndependentChannel_Param2.pwmCombinedChannelConfig                       = &pwmCombinedChannelConfig;
  FTM_DRV_InitPwmIndependentChannel_Param2.pwmIndependentChannelConfig                    = &pwmIndependentChannelConfig;
  FTM_DRV_InitPwmIndependentChannel_Param2.faultConfig->faultMode                         = FTM_FAULT_CONTROL_MAN_EVEN;
  FTM_DRV_InitPwmIndependentChannel_Param2.deadTimePrescaler                              = 3u;
  FTM_DRV_InitPwmIndependentChannel_Param2.deadTimeValue                                  = 3u;
  FTM_DRV_InitPwmIndependentChannel_Param2.counterInitValue                               = 32U;
  FTM_DRV_InitPwmIndependentChannel_Param2.mode                                           = 4u;
  FTM_DRV_InitPwmIndependentChannel_Param2.uFrequencyHZ                                   = 20u;

  g_ftmBase[1]->CONF                                                                      = 22u;
  FTM_DRV_GetMod_HitCount                                                                 = 0u;
  FTM_DRV_GetMod_Param1.CONF                                                              = 0u;
  FTM_DRV_GetMod_RetVal                                                                   = 128u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  FTM_DRV_InitPwmIndependentChannel(FTM_DRV_InitPwmIndependentChannel_Param1, &FTM_DRV_InitPwmIndependentChannel_Param2);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(FTM_DRV_GetMod_HitCount,                                      0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetMod_Param1.CONF,                                   0u, == );
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
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_Init_TestCase_1",                                Mt_McalPwm_Pwm_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_1",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_2",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_3",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_4",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_4);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_5",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_5);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_6",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_6);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_7",                    Mt_McalPwm_Pwm_SetPeriodAndDuty_TestCase_7);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_1",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_2",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_3",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_4",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_4);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_5",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_5);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_6",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_6);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_7",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_7);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetDutyCycle_TestCase_8",                        Mt_McalPwm_Pwm_SetDutyCycle_TestCase_8);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_1",              Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_2",              Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_3",              Mt_McalPwm_Pwm_CalculateChannelHwDuty_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetChannelOutput_TestCase_1",                    Mt_McalPwm_Pwm_SetChannelOutput_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetChannelOutput_TestCase_2",                    Mt_McalPwm_Pwm_SetChannelOutput_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetChannelOutput_TestCase_3",                    Mt_McalPwm_Pwm_SetChannelOutput_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_SetChannelOutput_TestCase_4",                    Mt_McalPwm_Pwm_SetChannelOutput_TestCase_4);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_StartPwmChannel_TestCase_1",                     Mt_McalPwm_Pwm_StartPwmChannel_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_StartPwmChannel_TestCase_2",                     Mt_McalPwm_Pwm_StartPwmChannel_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_1",                     Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_2",                     Mt_McalPwm_Pwm_ClampPwmChannel_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_GetFreq_TestCase_1",                             Mt_McalPwm_Pwm_GetFreq_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_Pwm_GetFreq_TestCase_2",                             Mt_McalPwm_Pwm_GetFreq_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwmIndependentChannel_TestCase_1",       Mt_McalPwm_FTM_DRV_InitPwmIndependentChannel_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_1",            Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_2",            Mt_McalPwm_FTM_DRV_ControlChannelOutput_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_1",           Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_2",           Mt_McalPwm_FTM_DRV_FastUpdatePwmChannels_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_1",                 Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_2",                 Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_3",                 Mt_McalPwm_FTM_DRV_UpdatePwmPeriod_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_1",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_2",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_3",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_4",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_4);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_5",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_5);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_6",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_6);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_7",                Mt_McalPwm_FTM_DRV_UpdatePwmChannel_TestCase_7);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_DeinitPwm_TestCase_1",                       Mt_McalPwm_FTM_DRV_DeinitPwm_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwm_TestCase_1",                         Mt_McalPwm_FTM_DRV_InitPwm_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwm_TestCase_2",                         Mt_McalPwm_FTM_DRV_InitPwm_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwm_TestCase_3",                         Mt_McalPwm_FTM_DRV_InitPwm_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwm_TestCase_4",                         Mt_McalPwm_FTM_DRV_InitPwm_TestCase_4);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwmDutyCycleChannel_TestCase_1",         Mt_McalPwm_FTM_DRV_InitPwmDutyCycleChannel_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_1",          Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_2",          Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_3",          Mt_McalPwm_FTM_DRV_InitPwmCombinedChannel_TestCase_3);
}
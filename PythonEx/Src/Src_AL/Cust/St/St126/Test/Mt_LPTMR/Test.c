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
///
/// \brief Module test for LPTMR
///
/// 
/// 
/// author 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_INIT_TestCase_1
///
/// \Test Case Description: Test the initialization of LPTMR
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Enable IRQ for LPTMR
///         Step2: Start LPTMR counter - Initialize the counter
///         Step3: Memorize init configuration for LPTMR instance
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
///input  LPTMR_INIT_Param1                    = &LPTMR_Config
///input  LPTMR_DRV_Init_Param1                = 33u
///input  LPTMR_DRV_Init_Param2                = NULL_PTR
///input  LPTMR_DRV_Init_Param3                = true
///input  LPTMR_DRV_Init_HitCount              = 0u
///input  LPTMR_DRV_StartCounter_Param1        = 33u
///input  LPTMR_DRV_StartCounter_HitCount      = 0u
///input  LPTMR_sTimerCfg_Init.bypassPrescaler = 33u
///
/// - Expectations:
///
///output LPTMR_DRV_Init_Param1                = INST_LPTMR_1
///output LPTMR_DRV_Init_Param2                = &lptmr_1_config0
///output LPTMR_DRV_Init_Param3                = false
///output LPTMR_DRV_Init_HitCount              = 1u
///output LPTMR_DRV_StartCounter_Param1        = INST_LPTMR_1
///output LPTMR_DRV_StartCounter_HitCount      = 1u
///output LPTMR_sTimerCfg_Init.bypassPrescaler = lptmr_1_config0.bypassPrescaler
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_INIT_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_INIT_Param1                    = &LPTMR_Config;
  LPTMR_DRV_Init_Param1                = 33u;
  LPTMR_DRV_Init_Param2                = NULL_PTR;
  LPTMR_DRV_Init_Param3                = true;
  LPTMR_DRV_Init_HitCount              = 0u;
  LPTMR_DRV_StartCounter_Param1        = 33u;
  LPTMR_DRV_StartCounter_HitCount      = 0u;
  LPTMR_sTimerCfg_Init.bypassPrescaler = 33u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_INIT(LPTMR_INIT_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_DRV_Init_Param1,                                   INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_Init_Param2,                               &lptmr_1_config0, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_Init_Param3,                                          false, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_Init_HitCount,                                           1u, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_StartCounter_Param1,                           INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_StartCounter_HitCount,                                   1u, == );
  AL_UNITTEST_CHECK(LPTMR_sTimerCfg_Init.bypassPrescaler, lptmr_1_config0.bypassPrescaler, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR0_IRQHandler_TestCase_1
///
/// \Test Case Description: Test if compare flag is cleared and timer is incremented
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the value for clear compare flag
///         Step2: Initialize the LP timer
///         Step3: Call the interruption
///         Step4: Check the value of the timer and check if the clear compare flag value is equal to instance timer 1
///
/// - Preconditions:
///
///input  LPTMR_DRV_ClearCompareFlag_Param1   = 33u
///input  LPTMR_DRV_ClearCompareFlag_HitCount = 0u
///input  ulLPTMR0_MicrosecondTimer           = 0u
///input  RTX_Timer_Notification_HitCount     = 1u
///
/// - Expectations:
///
///output LPTMR_DRV_ClearCompareFlag_Param1   = INST_LPTMR_1
///output LPTMR_DRV_ClearCompareFlag_HitCount = 1u
///output ulLPTMR0_MicrosecondTimer           = 1000u
///output RTX_Timer_Notification_HitCount     = 1u
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR0_IRQHandler_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_DRV_ClearCompareFlag_Param1   = 33u;
  LPTMR_DRV_ClearCompareFlag_HitCount = 0u;
  ulLPTMR0_MicrosecondTimer           = 0u;
  RTX_Timer_Notification_HitCount     = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR0_IRQHandler();

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_DRV_ClearCompareFlag_Param1,        INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_ClearCompareFlag_HitCount,                1u, == );
  AL_UNITTEST_CHECK(ulLPTMR0_MicrosecondTimer,                       1000u, == );
  AL_UNITTEST_CHECK(RTX_Timer_Notification_HitCount,                    1u, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR0_GetTimeElapsed_TestCase_1
///
/// \Test Case Description: Test if correct timer value is returned
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set the start value for timer
///         Step2: Initialize the counter
///         Step3: Call LPTMR0_GetTimeElapsed(LPTMR0_GetTimeElapsed_Param1) function 
///         Step4: Check if the returned value is calculated correctly ( the timer was calculating correctly the timing)
///
/// - Preconditions:
///
///input  LPTMR0_GetTimeElapsed_Param1              = 5u
///input  LPTMR0_GetTimeElapsed_RetVal              = 0u
///input  LPTMR_DRV_GetCounterValueByCount_Param1   = 33u
///input  LPTMR_DRV_GetCounterValueByCount_HitCount = 0u
///input  LPTMR_DRV_GetCounterValueByCount_RetVal   = 30u
///input  ulLPTMR0_MicrosecondTimer                 = 20u
///
/// - Expectations:
///
///output LPTMR_DRV_GetCounterValueByCount_Param1   = INST_LPTMR_1
///output LPTMR_DRV_GetCounterValueByCount_HitCount = 1u
///output LPTMR0_GetTimeElapsed_RetVal              = 45u
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR0_GetTimeElapsed_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR0_GetTimeElapsed_Param1              = 5u;
  LPTMR0_GetTimeElapsed_RetVal              = 0u;
  LPTMR_DRV_GetCounterValueByCount_Param1   = 33u;
  LPTMR_DRV_GetCounterValueByCount_HitCount = 0u;
  LPTMR_DRV_GetCounterValueByCount_RetVal   = 30u;
  ulLPTMR0_MicrosecondTimer                 = 20u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR0_GetTimeElapsed_RetVal = LPTMR0_GetTimeElapsed(LPTMR0_GetTimeElapsed_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_DRV_GetCounterValueByCount_Param1,   INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_GetCounterValueByCount_HitCount,           1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_RetVal,                       45u, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks prescaler cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.bypassPrescaler
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_ByPassPrescaler_Cfg_Param1.bypassPrescaler = 1u
///input  LPTMR_sTimerCfg_Init.bypassPrescaler                   = 0u
///input  LPTMR_Check_ByPassPrescaler_Cfg_RetVal                 = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_ByPassPrescaler_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_ByPassPrescaler_Cfg_Param1.bypassPrescaler = 1u;
  LPTMR_sTimerCfg_Init.bypassPrescaler                   = 0u;
  LPTMR_Check_ByPassPrescaler_Cfg_RetVal                 = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_ByPassPrescaler_Cfg_RetVal = LPTMR_Check_ByPassPrescaler_Cfg(&LPTMR_Check_ByPassPrescaler_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_ByPassPrescaler_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks prescaler cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.bypassPrescaler
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_ByPassPrescaler_Cfg_Param1.bypassPrescaler = 0u
///input  LPTMR_sTimerCfg_Init.bypassPrescaler                   = 0u
///input  LPTMR_Check_ByPassPrescaler_Cfg_RetVal                 = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_ByPassPrescaler_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_ByPassPrescaler_Cfg_Param1.bypassPrescaler = 0u;
  LPTMR_sTimerCfg_Init.bypassPrescaler                   = 0u;
  LPTMR_Check_ByPassPrescaler_Cfg_RetVal                 = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_ByPassPrescaler_Cfg_RetVal = LPTMR_Check_ByPassPrescaler_Cfg(&LPTMR_Check_ByPassPrescaler_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_ByPassPrescaler_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks clock selector cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.clockSelect
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_ClkSelect_Cfg_Param1.clockSelect       = 1u
///input  LPTMR_sTimerCfg_Init.clockSelect                   = 0u
///input  LPTMR_Check_ClkSelect_Cfg_RetVal                  = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_ClkSelect_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_ClkSelect_Cfg_Param1.clockSelect       = 1u;
  LPTMR_sTimerCfg_Init.clockSelect                   = 0u;
  LPTMR_Check_ClkSelect_Cfg_RetVal                   = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_ClkSelect_Cfg_RetVal = LPTMR_Check_ClkSelect_Cfg(&LPTMR_Check_ClkSelect_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_ClkSelect_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks clock selector cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.clockSelect
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_ClkSelect_Cfg_Param1.clockSelectr = 0u
///input  LPTMR_sTimerCfg_Init.clockSelect              = 0u
///input  LPTMR_Check_ClkSelect_Cfg_RetVal              = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_ClkSelect_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_ClkSelect_Cfg_Param1.clockSelect       = 0u;
  LPTMR_sTimerCfg_Init.clockSelect                   = 0u;
  LPTMR_Check_ClkSelect_Cfg_RetVal                   = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_ClkSelect_Cfg_RetVal = LPTMR_Check_ClkSelect_Cfg(&LPTMR_Check_ClkSelect_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_ClkSelect_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks compare value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.compareValue
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_CompVal_Cfg_Param1.compareValue = 1u
///input  LPTMR_sTimerCfg_Init.compareValue           = 0u
///input  LPTMR_Check_CompVal_Cfg_RetVal              = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_CompVal_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_CompVal_Cfg_Param1.compareValue      = 1u;
  LPTMR_sTimerCfg_Init.compareValue                = 0u;
  LPTMR_Check_CompVal_Cfg_RetVal                   = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_CompVal_Cfg_RetVal = LPTMR_Check_CompVal_Cfg(&LPTMR_Check_CompVal_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_CompVal_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks compare value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.compareValue
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_CompVal_Cfg_Param1.compareValue = 0u
///input  LPTMR_sTimerCfg_Init.compareValue           = 0u
///input  LPTMR_Check_CompVal_Cfg_RetVal              = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_CompVal_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_CompVal_Cfg_Param1.compareValue      = 0u;
  LPTMR_sTimerCfg_Init.compareValue                = 0u;
  LPTMR_Check_CompVal_Cfg_RetVal                   = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_CompVal_Cfg_RetVal = LPTMR_Check_CompVal_Cfg(&LPTMR_Check_CompVal_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_CompVal_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks counter unit value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.counterUnits
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_CntUnit_Cfg_Param1.counterUnits = 1u
///input  LPTMR_sTimerCfg_Init.counterUnits           = 0u
///input  LPTMR_Check_CntUnit_Cfg_RetVal              = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_CntUnit_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_CntUnit_Cfg_Param1.counterUnits      = 1u;
  LPTMR_sTimerCfg_Init.counterUnits                = 0u;
  LPTMR_Check_CntUnit_Cfg_RetVal                   = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_CntUnit_Cfg_RetVal = LPTMR_Check_CntUnit_Cfg(&LPTMR_Check_CntUnit_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_CntUnit_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks counter unit value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.counterUnits
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_CntUnit_Cfg_Param1.counterUnits = 0u
///input  LPTMR_sTimerCfg_Init.counterUnits           = 0u
///input  LPTMR_Check_CntUnit_Cfg_RetVal              = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_CntUnit_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_CntUnit_Cfg_Param1.counterUnits      = 0u;
  LPTMR_sTimerCfg_Init.counterUnits                = 0u;
  LPTMR_Check_CntUnit_Cfg_RetVal                   = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_CntUnit_Cfg_RetVal = LPTMR_Check_CntUnit_Cfg(&LPTMR_Check_CntUnit_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_CntUnit_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks dma request value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.dmaRequest
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_DmaReq_Cfg_Param1.dmaRequest = 1u
///input  LPTMR_sTimerCfg_Init.dmaRequest          = 0u
///input  LPTMR_Check_DmaReq_Cfg_RetVal            = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_DmaReq_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_DmaReq_Cfg_Param1.dmaRequest        = 1u;
  LPTMR_sTimerCfg_Init.dmaRequest                 = 0u;
  LPTMR_Check_DmaReq_Cfg_RetVal                   = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_DmaReq_Cfg_RetVal = LPTMR_Check_DmaReq_Cfg(&LPTMR_Check_DmaReq_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_DmaReq_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks dma request value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.dmaRequest
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_DmaReq_Cfg_Param1.dmaRequest = 0u
///input  LPTMR_sTimerCfg_Init.dmaRequest          = 0u
///input  LPTMR_Check_DmaReq_Cfg_RetVal            = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_DmaReq_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_DmaReq_Cfg_Param1.dmaRequest        = 0u;
  LPTMR_sTimerCfg_Init.dmaRequest                 = 0u;
  LPTMR_Check_DmaReq_Cfg_RetVal                   = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_DmaReq_Cfg_RetVal = LPTMR_Check_DmaReq_Cfg(&LPTMR_Check_DmaReq_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_DmaReq_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks Interrupt Enable value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.interruptEnable
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input LPTMR_Check_IntEnbl_Cfg_Param1.interruptEnable = 1u
///input LPTMR_sTimerCfg_Init.interruptEnable           = 0u
///input LPTMR_Check_IntEnbl_Cfg_RetVal                 = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_DmaReq_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_IntEnbl_Cfg_Param1.interruptEnable        = 1u;
  LPTMR_sTimerCfg_Init.interruptEnable                  = 0u;
  LPTMR_Check_IntEnbl_Cfg_RetVal                        = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_IntEnbl_Cfg_RetVal = LPTMR_Check_IntEnbl_Cfg(&LPTMR_Check_IntEnbl_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_IntEnbl_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks Interrupt Enable value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.interruptEnable
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_IntEnbl_Cfg_Param1.interruptEnable = 0u
///input  LPTMR_sTimerCfg_Init.interruptEnable           = 0u
///input  LPTMR_Check_IntEnbl_Cfg_RetVal                 = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_IntEnbl_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_IntEnbl_Cfg_Param1.interruptEnable        = 0u;
  LPTMR_sTimerCfg_Init.interruptEnable                  = 0u;
  LPTMR_Check_IntEnbl_Cfg_RetVal                        = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_IntEnbl_Cfg_RetVal = LPTMR_Check_IntEnbl_Cfg(&LPTMR_Check_IntEnbl_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_IntEnbl_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks Pin Select value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.pinSelect
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_PinSel_Cfg_Param1.pinSelect = 1u
///input  LPTMR_sTimerCfg_Init.pinSelect          = 0u
///input  LPTMR_Check_PinSel_Cfg_RetVal           = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_PinSel_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_PinSel_Cfg_Param1.pinSelect        = 1u;
  LPTMR_sTimerCfg_Init.pinSelect                 = 0u;
  LPTMR_Check_PinSel_Cfg_RetVal                  = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_PinSel_Cfg_RetVal = LPTMR_Check_PinSel_Cfg(&LPTMR_Check_PinSel_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_PinSel_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks Pin Select value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.pinSelect
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_PinSel_Cfg_Param1.pinSelect = 0u
///input  LPTMR_sTimerCfg_Init.pinSelect          = 0u
///input  LPTMR_Check_PinSel_Cfg_RetVal           = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_PinSel_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_PinSel_Cfg_Param1.pinSelect        = 0u;
  LPTMR_sTimerCfg_Init.pinSelect                 = 0u;
  LPTMR_Check_PinSel_Cfg_RetVal                  = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_PinSel_Cfg_RetVal = LPTMR_Check_PinSel_Cfg(&LPTMR_Check_PinSel_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_PinSel_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks pin polarity value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.pinPolarity
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_PinPol_Cfg_Param1.pinPolarity = 1u
///input  LPTMR_sTimerCfg_Init.pinPolarity          = 0u
///input  LPTMR_Check_PinPol_Cfg_RetVal             = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_PinPol_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_PinPol_Cfg_Param1.pinPolarity        = 1u;
  LPTMR_sTimerCfg_Init.pinPolarity                 = 0u;
  LPTMR_Check_PinPol_Cfg_RetVal                    = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_PinPol_Cfg_RetVal = LPTMR_Check_PinPol_Cfg(&LPTMR_Check_PinPol_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_PinPol_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks pin polarity value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.pinPolarity
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_PinPol_Cfg_Param1.pinPolarity = 0u
///input  LPTMR_sTimerCfg_Init.pinPolarity          = 0u
///input  LPTMR_Check_PinPol_Cfg_RetVal             = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_PinPol_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_PinPol_Cfg_Param1.pinPolarity        = 0u;
  LPTMR_sTimerCfg_Init.pinPolarity                 = 0u;
  LPTMR_Check_PinPol_Cfg_RetVal                    = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_PinPol_Cfg_RetVal = LPTMR_Check_PinPol_Cfg(&LPTMR_Check_PinPol_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_PinPol_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks prescaler value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.prescaler
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_Prescaler_Cfg_Param1.prescaler = 1u
///input  LPTMR_sTimerCfg_Init.prescaler             = 0u
///input  LPTMR_Check_Prescaler_Cfg_RetVal           = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_Prescaler_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_Prescaler_Cfg_Param1.prescaler          = 1u;
  LPTMR_sTimerCfg_Init.prescaler                      = 0u;
  LPTMR_Check_Prescaler_Cfg_RetVal                    = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_Prescaler_Cfg_RetVal = LPTMR_Check_Prescaler_Cfg(&LPTMR_Check_Prescaler_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_Prescaler_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks prescaler value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.prescaler
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_Prescaler_Cfg_Param1.prescaler = 0u
///input  LPTMR_sTimerCfg_Init.prescaler             = 0u
///input  LPTMR_Check_Prescaler_Cfg_RetVal           = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_Prescaler_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_Prescaler_Cfg_Param1.prescaler        = 0u;
  LPTMR_sTimerCfg_Init.prescaler                    = 0u;
  LPTMR_Check_Prescaler_Cfg_RetVal                  = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_Prescaler_Cfg_RetVal = LPTMR_Check_Prescaler_Cfg(&LPTMR_Check_Prescaler_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_Prescaler_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks work mode value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.workMode
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_WorkMode_Cfg_Param1.workMode = 1u
///input  LPTMR_sTimerCfg_Init.workMode            = 0u
///input  LPTMR_Check_WorkMode_Cfg_RetVal          = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_WorkMode_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_WorkMode_Cfg_Param1.workMode           = 1u;
  LPTMR_sTimerCfg_Init.workMode                      = 0u;
  LPTMR_Check_WorkMode_Cfg_RetVal                    = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_WorkMode_Cfg_RetVal = LPTMR_Check_WorkMode_Cfg(&LPTMR_Check_WorkMode_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_WorkMode_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks work mode value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.workMode
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_WorkMode_Cfg_Param1.workMode = 0u
///input  LPTMR_sTimerCfg_Init.workMode            = 0u
///input  LPTMR_Check_WorkMode_Cfg_RetVal          = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_WorkMode_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_WorkMode_Cfg_Param1.workMode        = 0u;
  LPTMR_sTimerCfg_Init.workMode                   = 0u;
  LPTMR_Check_WorkMode_Cfg_RetVal                 = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_WorkMode_Cfg_RetVal = LPTMR_Check_WorkMode_Cfg(&LPTMR_Check_WorkMode_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_WorkMode_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_1
///
/// \Test Case Description: Test if function checks work mode value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.freeRun
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_FreeRun_Cfg_Param1.freeRun = 1u
///input  LPTMR_sTimerCfg_Init.freeRun           = 0u
///input  LPTMR_Check_FreeRun_Cfg_RetVal         = FALSE
///
/// - Expectations:
///
///output LPTMR_Check_FreeRun_Cfg_RetVal   = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  LPTMR_Check_FreeRun_Cfg_Param1.freeRun            = 1u;
  LPTMR_sTimerCfg_Init.freeRun                      = 0u;
  LPTMR_Check_FreeRun_Cfg_RetVal                    = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_FreeRun_Cfg_RetVal = LPTMR_Check_FreeRun_Cfg(&LPTMR_Check_FreeRun_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_FreeRun_Cfg_RetVal, TRUE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_2
///
/// \Test Case Description: Test if function checks work mode value cinsistency
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the coressponding variables for the configuration
///         Step2: Check if the set value is different than LPTMR_sTimerCfg_Init.freeRun
///         Step3: Check that the value of the output variable if it is true or false 
///
/// - Preconditions:
///
///input  LPTMR_Check_FreeRun_Cfg_Param1.freeRun = 0u
///input  LPTMR_sTimerCfg_Init.freeRun           = 0u
///input  LPTMR_Check_FreeRun_Cfg_RetVal         = TRUE
///
/// - Expectations:
///
///output LPTMR_Check_FreeRun_Cfg_RetVal   = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_Check_FreeRun_Cfg_Param1.freeRun        = 0u;
  LPTMR_sTimerCfg_Init.freeRun                  = 0u;
  LPTMR_Check_FreeRun_Cfg_RetVal                = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_FreeRun_Cfg_RetVal = LPTMR_Check_FreeRun_Cfg(&LPTMR_Check_FreeRun_Cfg_Param1);

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_Check_FreeRun_Cfg_RetVal, FALSE, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_Config_TestCase_1
///
/// \Test Case Description: Test if function returns correct error status
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set LPTMR configuration
///         Step2: Check all config parameter
///         Step3: Check config parameter
///         Step4: Check if timer is running and configuration is kept
///         Step5: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
///input  LPTMR_DRV_GetConfig_Param1                 = 33u
///input  LPTMR_DRV_GetConfig_Param2.bypassPrescaler = 0u
///input  LPTMR_DRV_GetConfig_Param2.clockSelect     = 1u
///input  LPTMR_DRV_GetConfig_HitCount               = 0u
///input  LPTMR_sTimerCfg_Init.bypassPrescaler       = 0u
///input  LPTMR_sTimerCfg_Init.clockSelect           = 0u
///input  LPTMR_DRV_IsRunning_Param1                 = 33u
///input  LPTMR_DRV_IsRunning_HitCount               = 0u
///input  LPTMR_DRV_IsRunning_RetVal                 = false
///input  LPTMR_DRV_StopCounter_Param1               = 33u
///input  LPTMR_DRV_StopCounter_HitCount             = 0u
///input  LPTMR_Check_Config_RetVal                  = FALSE
///
/// - Expectations:
///
///output LPTMR_DRV_GetConfig_Param1     = INST_LPTMR_1
///output LPTMR_DRV_GetConfig_HitCount   = 1u
///output LPTMR_DRV_IsRunning_Param1     = INST_LPTMR_1
///output LPTMR_DRV_IsRunning_HitCount   = 1u
///output LPTMR_DRV_StopCounter_Param1   = INST_LPTMR_1
///output LPTMR_DRV_StopCounter_HitCount = 1u
///output LPTMR_Check_Config_RetVal      = TRUE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_Config_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_DRV_GetConfig_Param1                 = 33u;
  LPTMR_DRV_GetConfig_Param2.bypassPrescaler = 0u;
  LPTMR_DRV_GetConfig_Param2.clockSelect     = 1u;
  LPTMR_DRV_GetConfig_HitCount               = 0u;
  LPTMR_sTimerCfg_Init.bypassPrescaler       = 0u;
  LPTMR_sTimerCfg_Init.clockSelect           = 0u;
  LPTMR_DRV_IsRunning_Param1                 = 33u;
  LPTMR_DRV_IsRunning_HitCount               = 0u;
  LPTMR_DRV_IsRunning_RetVal                 = false;
  LPTMR_DRV_StopCounter_Param1               = 33u;
  LPTMR_DRV_StopCounter_HitCount             = 0u;
  LPTMR_Check_Config_RetVal                  = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_Config_RetVal = LPTMR_Check_Config();

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_DRV_GetConfig_Param1,         INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_GetConfig_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_IsRunning_Param1,         INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_IsRunning_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_StopCounter_Param1,       INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_StopCounter_HitCount,               1u, == );
  AL_UNITTEST_CHECK(LPTMR_Check_Config_RetVal,                  TRUE, == );
}



//--------------------------------------------------------------------------------
/// \Test Case : Mt_LPTMR_LPTMR_Check_Config_TestCase_2
///
/// \Test Case Description: Test if function returns correct error status
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set LPTMR configuration
///         Step2: Check all config parameter
///         Step3: Check config parameter
///         Step4: Check if timer is running and configuration is kept
///         Step5: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
///input  LPTMR_DRV_GetConfig_Param1                 = 33u
///input  LPTMR_DRV_GetConfig_Param2.bypassPrescaler = 0u
///input  LPTMR_DRV_GetConfig_Param2.clockSelect     = 0u
///input  LPTMR_DRV_GetConfig_Param2.compareValue    = 0u
///input  LPTMR_DRV_GetConfig_Param2.counterUnits    = 0u
///input  LPTMR_DRV_GetConfig_Param2.dmaRequest      = 0u
///input  LPTMR_DRV_GetConfig_Param2.freeRun         = 0u
///input  LPTMR_DRV_GetConfig_Param2.interruptEnable = 0u
///input  LPTMR_DRV_GetConfig_Param2.pinSelect       = 0u
///input  LPTMR_DRV_GetConfig_Param2.pinPolarity     = 0u
///input  LPTMR_DRV_GetConfig_Param2.prescaler       = 0u
///input  LPTMR_DRV_GetConfig_Param2.workMode        = 0u
///input  LPTMR_DRV_GetConfig_HitCount               = 0u
///input  LPTMR_sTimerCfg_Init.bypassPrescaler       = 0u
///input  LPTMR_sTimerCfg_Init.clockSelect           = 0u
///input  LPTMR_sTimerCfg_Init.compareValue          = 0u
///input  LPTMR_sTimerCfg_Init.counterUnits          = 0u
///input  LPTMR_sTimerCfg_Init.dmaRequest            = 0u
///input  LPTMR_sTimerCfg_Init.freeRun               = 0u
///input  LPTMR_sTimerCfg_Init.interruptEnable       = 0u
///input  LPTMR_sTimerCfg_Init.pinSelect             = 0u
///input  LPTMR_sTimerCfg_Init.pinPolarity           = 0u
///input  LPTMR_sTimerCfg_Init.prescaler             = 0u
///input  LPTMR_sTimerCfg_Init.workMode              = 0u
///input  LPTMR_DRV_IsRunning_Param1                 = 33u
///input  LPTMR_DRV_IsRunning_HitCount               = 0u
///input  LPTMR_DRV_IsRunning_RetVal                 = true
///input  LPTMR_DRV_StopCounter_HitCount             = 0u
///input  LPTMR_Check_Config_RetVal                  = TRUE
///
/// - Expectations:
///
///output LPTMR_DRV_GetConfig_Param1     = INST_LPTMR_1
///output LPTMR_DRV_GetConfig_HitCount   = 1u
///output LPTMR_DRV_IsRunning_Param1     = INST_LPTMR_1
///output LPTMR_DRV_IsRunning_HitCount   = 1u
///output LPTMR_DRV_StopCounter_HitCount = 0u
///output LPTMR_Check_Config_RetVal      = FALSE
///
//--------------------------------------------------------------------------------
void Mt_LPTMR_LPTMR_Check_Config_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  LPTMR_DRV_GetConfig_Param1                 = 33u;
  LPTMR_DRV_GetConfig_Param2.bypassPrescaler = 0u;
  LPTMR_DRV_GetConfig_Param2.clockSelect     = 0u;
  LPTMR_DRV_GetConfig_Param2.compareValue    = 0u;
  LPTMR_DRV_GetConfig_Param2.counterUnits    = 0u;
  LPTMR_DRV_GetConfig_Param2.dmaRequest      = 0u;
  LPTMR_DRV_GetConfig_Param2.freeRun         = 0u;
  LPTMR_DRV_GetConfig_Param2.interruptEnable = 0u;
  LPTMR_DRV_GetConfig_Param2.pinSelect       = 0u;
  LPTMR_DRV_GetConfig_Param2.pinPolarity     = 0u;
  LPTMR_DRV_GetConfig_Param2.prescaler       = 0u;
  LPTMR_DRV_GetConfig_Param2.workMode        = 0u;
  LPTMR_DRV_GetConfig_HitCount               = 0u;
  LPTMR_sTimerCfg_Init.bypassPrescaler       = 0u;
  LPTMR_sTimerCfg_Init.clockSelect           = 0u;
  LPTMR_sTimerCfg_Init.compareValue          = 0u;
  LPTMR_sTimerCfg_Init.counterUnits          = 0u;
  LPTMR_sTimerCfg_Init.dmaRequest            = 0u;
  LPTMR_sTimerCfg_Init.freeRun               = 0u;
  LPTMR_sTimerCfg_Init.interruptEnable       = 0u;
  LPTMR_sTimerCfg_Init.pinSelect             = 0u;
  LPTMR_sTimerCfg_Init.pinPolarity           = 0u;
  LPTMR_sTimerCfg_Init.prescaler             = 0u;
  LPTMR_sTimerCfg_Init.workMode              = 0u;
  LPTMR_DRV_IsRunning_Param1                 = 33u;
  LPTMR_DRV_IsRunning_HitCount               = 0u;
  LPTMR_DRV_IsRunning_RetVal                 = true;
  LPTMR_DRV_StopCounter_HitCount             = 0u;
  LPTMR_Check_Config_RetVal                  = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  LPTMR_Check_Config_RetVal = LPTMR_Check_Config();

  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(LPTMR_DRV_GetConfig_Param1,         INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_GetConfig_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_IsRunning_Param1,         INST_LPTMR_1, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_IsRunning_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(LPTMR_DRV_StopCounter_HitCount,               0u, == );
  AL_UNITTEST_CHECK(LPTMR_Check_Config_RetVal,                 FALSE, == );
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
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_INIT_TestCase_1",                           Mt_LPTMR_LPTMR_INIT_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR0_IRQHandler_TestCase_1",                    Mt_LPTMR_LPTMR0_IRQHandler_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR0_GetTimeElapsed_TestCase_1",                Mt_LPTMR_LPTMR0_GetTimeElapsed_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_1",      Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_2",      Mt_LPTMR_LPTMR_Check_ByPassPrescaler_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_1",            Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_2",            Mt_LPTMR_LPTMR_Check_ClkSelect_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_1",              Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_2",              Mt_LPTMR_LPTMR_Check_CompVal_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_1",              Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_2",              Mt_LPTMR_LPTMR_Check_CntUnit_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_1",               Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_2",               Mt_LPTMR_LPTMR_Check_DmaReq_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_1",              Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_2",              Mt_LPTMR_LPTMR_Check_IntEnbl_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_1",               Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_2",               Mt_LPTMR_LPTMR_Check_PinSel_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_1",               Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_2",               Mt_LPTMR_LPTMR_Check_PinPol_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_1",            Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_2",            Mt_LPTMR_LPTMR_Check_Prescaler_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_1",             Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_2",             Mt_LPTMR_LPTMR_Check_WorkMode_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_1",              Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_2",              Mt_LPTMR_LPTMR_Check_FreeRun_Cfg_TestCase_2);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_Config_TestCase_1",                   Mt_LPTMR_LPTMR_Check_Config_TestCase_1);
  ALUnitTest_AddFunction("Mt_LPTMR_LPTMR_Check_Config_TestCase_2",                   Mt_LPTMR_LPTMR_Check_Config_TestCase_2);
}

// EOF

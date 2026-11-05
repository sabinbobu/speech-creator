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
/// \brief Module test of SysVolt
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
/// \Test Case : Mt_SysVolt_SysVolt_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization values of configuration are set according to the voltage readed from Rte (7.6V)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount   = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1     = 7600u
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount   = 4u
/// \output SysVolt_asInStateResult[0].ePreviousVoltageRange = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[0].eVoltageRangeResult   = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[0].unDebounceValTo_Ms    = 0u
/// \output SysVolt_asInStateResult[1].ePreviousVoltageRange = 5u (eSysVolt_eLow1)
/// \output SysVolt_asInStateResult[1].eVoltageRangeResult   = 5u (eSysVolt_eLow1)
/// \output SysVolt_asInStateResult[1].unDebounceValTo_Ms    = 0u
/// \output SysVolt_asInStateResult[2].ePreviousVoltageRange = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[2].eVoltageRangeResult   = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[2].unDebounceValTo_Ms    = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 7600u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,               4u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ePreviousVoltageRange, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].eVoltageRangeResult,   eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].unDebounceValTo_Ms,                0u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ePreviousVoltageRange, eSysVolt_eLow1, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].eVoltageRangeResult,   eSysVolt_eLow1, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].unDebounceValTo_Ms,                0u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ePreviousVoltageRange, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].eVoltageRangeResult,   eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].unDebounceValTo_Ms,                0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Init_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the initialization values of configuration are set according to the voltage readed from Rte (SYSVOLT_GENERIC_LAST)
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount              = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                = 0xFFFFu (SYSVOLT_GENERIC_LAST)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 4u
/// \output SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
/// \output SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = 8u (eSysVolt_eHigh2)
/// \output SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms    = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Init_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = SYSVOLT_GENERIC_LAST;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount, 4u, == );

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) 
  {
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange, eSysVolt_eHigh2, == );
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult,   eSysVolt_eHigh2, == );
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms,                 0u, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if coding is not available if SysVolt_boCodingValidStatus = FALSE
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                           = FALSE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount        = 0u
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount        = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                    = FALSE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  SysVolt_boCodingValidStatus = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = SYSVOLT_GENERIC_LAST;


  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eSysVolt_eHigh2;
    SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us = 0u;
    SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms = 1u;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult = eSysVolt_eHigh1;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of SYSVOLT_GENERIC_LAST readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                        = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                       = 0xFFFFu (SYSVOLT_GENERIC_LAST)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange         = 8u (eSysVolt_eHigh2)
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult           = 8u (eSysVolt_eHigh2)
///
/// - Expectations:
///
/// \output  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                      = 4u
/// \output  SysVolt_boCodingValidStatus                                         = TRUE
/// \output  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange          = 8u (eSysVolt_eHigh2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                  = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount               = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                 = SYSVOLT_GENERIC_LAST;
  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) 
  {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eSysVolt_eHigh2;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = eSysVolt_eHigh2;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,                            4u, == );
  AL_UNITTEST_CHECK(SysVolt_boCodingValidStatus,                                             TRUE, == );

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) 
  {
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange, eSysVolt_eHigh2, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of 7.6V readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                              = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount           = 4u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1             = 7600u
/// \input  SysVolt_asInStateResult[0].ePreviousVoltageRange         = 4u (eSysVolt_eLow2)
/// \input  SysVolt_asInStateResult[0].eVoltageRangeResult           = 4u (eSysVolt_eLow2)
/// \input  SysVolt_asInStateResult[1].ePreviousVoltageRange         = 5u (eSysVolt_eLow1)
/// \input  SysVolt_asInStateResult[1].eVoltageRangeResult           = 5u (eSysVolt_eLow1)
/// \input  SysVolt_asInStateResult[2].ePreviousVoltageRange         = 4u (eSysVolt_eLow2)
/// \input  SysVolt_asInStateResult[2].eVoltageRangeResult           = 4u (eSysVolt_eLow2)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount           = 3u
/// \output SysVolt_asInStateResult[0].ePreviousVoltageRange         = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[1].ePreviousVoltageRange         = 5u (eSysVolt_eLow1)
/// \output SysVolt_asInStateResult[2].ePreviousVoltageRange         = 4u (eSysVolt_eLow2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                      = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount   = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1     = 7600u;
  SysVolt_asInStateResult[0].ePreviousVoltageRange = eSysVolt_eLow2;
  SysVolt_asInStateResult[0].eVoltageRangeResult   = eSysVolt_eLow2;
  SysVolt_asInStateResult[1].ePreviousVoltageRange = eSysVolt_eLow1;
  SysVolt_asInStateResult[1].eVoltageRangeResult   = eSysVolt_eLow1;
  SysVolt_asInStateResult[2].ePreviousVoltageRange = eSysVolt_eLow2;
  SysVolt_asInStateResult[2].eVoltageRangeResult   = eSysVolt_eLow2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,               4u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ePreviousVoltageRange, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ePreviousVoltageRange, eSysVolt_eLow1, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ePreviousVoltageRange, eSysVolt_eLow2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of 5V readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Gpt_GetTimeElapsed_HitCount                                        = 0
/// \input  Gpt_GetTimeElapsed_RetVal                                          = 1u
/// \input  SysVolt_boCodingValidStatus                                        = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                       = 5000u
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange         = 7u (eSysVolt_eHigh1)
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult           = 2u (eSysVolt_eLow4)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 4u
/// \output Gpt_GetTimeElapsed_HitCount                                        = 6u
/// \output SysVolt_asInStateResult[0].unDebounceValTo_Ms                      = 20u
/// \output SysVolt_asInStateResult[0].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[0].ePreviousVoltageRange                   = 3u (eSysVolt_eLow3)
/// \output SysVolt_asInStateResult[1].unDebounceValTo_Ms                      = 0u
/// \output SysVolt_asInStateResult[1].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[1].ePreviousVoltageRange                   = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[2].unDebounceValTo_Ms                      = 20u
/// \output SysVolt_asInStateResult[2].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[2].ePreviousVoltageRange                   = 4u (eSysVolt_eLow2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                   = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                  = 5000u;
  SysVolt_StMachine_Param1                                      = TRUE;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++)
  {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange  = eSysVolt_eHigh1;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult    = eSysVolt_eLow4;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,               4u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].unDebounceValTo_Ms,                20u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ulDebounceTmr_Us,               1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ePreviousVoltageRange, eSysVolt_eLow3, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].unDebounceValTo_Ms,                0u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ulDebounceTmr_Us,               1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ePreviousVoltageRange, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].unDebounceValTo_Ms,                20u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ulDebounceTmr_Us,               1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ePreviousVoltageRange,  eSysVolt_eLow2,== );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of 5V readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                        = TRUE;
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                       = 5000u
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange         = 7u (eSysVolt_eHigh1)
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult           = 8u (eSysVolt_eHigh2)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 4u
/// \output Gpt_GetTimeElapsed_HitCount                                        = 6u
/// \output SysVolt_asInStateResult[0].unDebounceValTo_Ms                      = 20u
/// \output SysVolt_asInStateResult[0].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[0].ePreviousVoltageRange                   = eSysVolt_eLow3
/// \output SysVolt_asInStateResult[1].unDebounceValTo_Ms                      = 0u
/// \output SysVolt_asInStateResult[1].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[1].ePreviousVoltageRange                   = eSysVolt_eLow2
/// \output SysVolt_asInStateResult[2].unDebounceValTo_Ms                      = 20u
/// \output SysVolt_asInStateResult[2].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[2].ePreviousVoltageRange                   = eSysVolt_eLow2
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                  = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount               = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                 = 5000u;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eSysVolt_eHigh1;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = eSysVolt_eHigh2;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,               4u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].unDebounceValTo_Ms,                20u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ulDebounceTmr_Us,               1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ePreviousVoltageRange, eSysVolt_eLow3, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].unDebounceValTo_Ms,                0u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ulDebounceTmr_Us,               1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ePreviousVoltageRange, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].unDebounceValTo_Ms,                20u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ulDebounceTmr_Us,               1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ePreviousVoltageRange, eSysVolt_eLow2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of SYSVOLT_GENERIC_LAST readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                        = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                       = 0xFFFFu (SYSVOLT_GENERIC_LAST)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange         = 8u (eSysVolt_eHigh2)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us              = 0u
/// \input  SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms            = 1u
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult           = 7u (eSysVolt_eHigh1)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                      = 4u
/// \output SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult            = 8u (eSysVolt_eHigh2)
/// \output SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange          = 8u (eSysVolt_eHigh2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                  = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount               = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                 = SYSVOLT_GENERIC_LAST;
  SysVolt_StMachine_Param1 = TRUE;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eSysVolt_eHigh2;
    SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us      = 0u;
    SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms    = 1u;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = eSysVolt_eHigh1;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,                            4u, == );

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) {
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult,   eSysVolt_eHigh2, == );
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange, eSysVolt_eHigh2, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of SYSVOLT_GENERIC_LAST readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount            = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount        = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1               = 0xFFFFu (SYSVOLT_GENERIC_LAST)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us      = 0u
/// \input  SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms    = 1u
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = 7u (eSysVolt_eHigh1)
/// \input  SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb            = NULL_PTR
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 4u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount        = 0u
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount            = 0u
/// \output SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = 8u (eSysVolt_eHigh2)
/// \output SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                  = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount               = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount              = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount          = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                 = SYSVOLT_GENERIC_LAST;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) 
  {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eSysVolt_eHigh2;
    SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us      = 0u;
    SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms    = 1u;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = eSysVolt_eHigh1;
    SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb            = NULL_PTR;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,                            4u, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,                           0u, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,                       0u, == );
 
  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) 
  {
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult,   eSysVolt_eHigh2, == );
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange, eSysVolt_eHigh2, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of SYSVOLT_GENERIC_LAST readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount            = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount        = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1               = 0xFFFFu (SYSVOLT_GENERIC_LAST)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us      = 0u
/// \input  SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms    = 1u
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = 7u (eSysVolt_eHigh1)
/// \input  SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb            = NULL_PTR
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 4u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount        = 0u
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount            = 0u
/// \output SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = 8u (eSysVolt_eHigh2)
/// \output SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                   = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount               = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount           = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                  = SYSVOLT_GENERIC_LAST;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++)
  {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange  = eSysVolt_eHigh2;
    SysVolt_asInStateResult[ucConfigIdx].ulDebounceTmr_Us       = 1u;
    SysVolt_asInStateResult[ucConfigIdx].unDebounceValTo_Ms     = 0u;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult    = eSysVolt_eHigh1;
    SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb             = NULL_PTR;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,                            4u, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,                           0u, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,                       0u, == );
  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++)
  {
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult,   eSysVolt_eHigh2, == );
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange, eSysVolt_eHigh2, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of 5V readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                        = TRUE;
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 0u
/// \input  SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb                    = NULL_PTR
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                       = 5000u
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange         = 7u (eSysVolt_eHigh1)
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult           = 8u (eSysVolt_eHigh2)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                     = 4u
/// \output SysVolt_asInStateResult[0].unDebounceValTo_Ms                      = 5u
/// \output SysVolt_asInStateResult[0].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[0].ePreviousVoltageRange                   = eSysVolt_eLow3
/// \output SysVolt_asInStateResult[1].unDebounceValTo_Ms                      = 0u
/// \output SysVolt_asInStateResult[1].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[1].ePreviousVoltageRange                   = eSysVolt_eLow2
/// \output SysVolt_asInStateResult[2].unDebounceValTo_Ms                      = 300u
/// \output SysVolt_asInStateResult[2].ulDebounceTmr_Us                        = 1000u
/// \output SysVolt_asInStateResult[2].ePreviousVoltageRange                   = eSysVolt_eLow2
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_9(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                                    = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount                 = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                   = 5000u;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange   = eSysVolt_eHigh1;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult     = eSysVolt_eHigh2;
    SysVolt_Configs[ucConfigIdx].pfRangeChangeIndCb              = NULL_PTR;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,                 4u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].unDebounceValTo_Ms,                  20u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ulDebounceTmr_Us,                 1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ePreviousVoltageRange,   eSysVolt_eLow3, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].unDebounceValTo_Ms,                  0u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ulDebounceTmr_Us,                 1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[1].ePreviousVoltageRange,   eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].unDebounceValTo_Ms,                  20u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ulDebounceTmr_Us,                 1000u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[2].ePreviousVoltageRange,   eSysVolt_eLow2, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_Cycle_TestCase_10
///
/// \Test Case Description
///        - Test subject: Test if SysVolt_asInStateResult parameters are set according 
///                         to voltage of 5V readed from Rte and input parameters
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                        = FALSE;
///
/// - Expectations:
///
/// \output -
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Cycle_TestCase_10(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus = FALSE;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Cycle();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_ParaFct0_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if voltage range limits are set correctly for Stp, Fan and Bat.
///                         if SysVolt_ParaFct0_Param1 = 0
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_SysVolt_Para_Param1.eCodingState     = eParaFct0_CodingDataInvalid
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1       = 5u;
///
/// - Expectations:
///
/// \output SysVolt_boIsCodingValid                            = FALSE;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount     = 4u;
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_ParaFct0_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_CodM_SysVolt_Para_Param1.eCodingState  = eParaFct0_CodingDataInvalid;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1    = 5u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_ParaFct0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_boIsCodingValid,                     FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_ParaFct0_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if voltage range limits are set correctly for Stp, Fan and Bat. if SysVolt_ParaFct0_Param1 = 1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                                                   = TRUE;
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                                                  = 5u
/// \input  Coding_State                                                                                  = eParaFct0_CodingDataValid
/// \input  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_V                                       = 10u
/// \input  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_V                                        = 5u
/// \input  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_T                                       = 1u
/// \input  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_T                                        = 3u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MIN                                         = 10u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MIN                                          = 20u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MAX                                          = 30u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MAX                                         = 40u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MIN                                         = 100u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN                                          = 100u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX                                         = 100u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN                                          = 100u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MAX                                          = 100u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MAX                                          = 100u
/// \input  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX                                         = 100u
/// \input  
///
/// - Expectations:
///
/// \output SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unRangeUpperLimit_mV                              = 1000
/// \output SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unRangeUpperLimit_mV                              = 500
/// \output SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsWorse_Ms                   = SYSVOLT_ZERO_DEBTIME
/// \output SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsWorse_Ms                   = 1u
/// \output SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsBetter_Ms                  = 1u
/// \output SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsBetter_Ms                  = 3u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unRangeUpperLimit_mV                              = 1000u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unRangeUpperLimit_mV                              = 2000u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unRangeUpperLimit_mV                              = 3000u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unRangeUpperLimit_mV                              = 4000u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsWorse_Ms                   = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsWorse_Ms                   = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unDebounceCnt_RangeGetsWorse_Ms                   = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unDebounceCnt_RangeGetsWorse_Ms                   = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsBetter_Ms                  = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsBetter_Ms                  = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unDebounceCnt_RangeGetsBetter_Ms                  = 0u
/// \output SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unDebounceCnt_RangeGetsBetter_Ms                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_ParaFct0_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
   SysVolt_sCodingParam.eCodingState = eParaFct0_CodingDataValid;


  SysVolt_boCodingValidStatus                                       = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                      = 5u;
  Coding_State                                                      = eParaFct0_CodingDataValid;
  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_V           = 10u;
  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_V            = 5u;
  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_OFF_T           = 1u;
  Coding_Dummy.Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_T            = 3u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MIN             = 10u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MIN              = 20u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MAX              = 30u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MAX             = 40u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MIN             = 100u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN              = 100u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX             = 100u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN              = 100u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MAX              = 100u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MAX              = 100u;
  Coding_Dummy.Fan1.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX             = 100u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_ParaFct0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unRangeUpperLimit_mV,                              1000, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unRangeUpperLimit_mV,                               500, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsWorse_Ms,   SYSVOLT_ZERO_DEBTIME, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsWorse_Ms,                     1u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsBetter_Ms,                    1u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Led_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsBetter_Ms,                    3u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unRangeUpperLimit_mV,                             1000u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unRangeUpperLimit_mV,                             2000u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unRangeUpperLimit_mV,                             3000u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unRangeUpperLimit_mV,                             4000u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsWorse_Ms,                     0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsWorse_Ms,                     0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unDebounceCnt_RangeGetsWorse_Ms,                     0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unDebounceCnt_RangeGetsWorse_Ms,                     0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[0].unDebounceCnt_RangeGetsBetter_Ms,                    0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[1].unDebounceCnt_RangeGetsBetter_Ms,                    0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[2].unDebounceCnt_RangeGetsBetter_Ms,                    0u, == );
  AL_UNITTEST_CHECK(SysVolt_Configs[eSysV_Fan_Idx].pRangeCfg[3].unDebounceCnt_RangeGetsBetter_Ms,                    0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eLow2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount  = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = 4u (eSysVolt_eLow2)
///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag                                  = eVbatLow
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_LocalDiagVbat_Param1                     = eSysVolt_eLow2;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatLow, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eLow1 and previous state was eSysVolt_eLow2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount  = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = 4u (eSysVolt_eLow2) - to obtain the previous state
///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag                                  = eVbatLow
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_LocalDiagVbat_Param1                     = eSysVolt_eLow2;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);
  SysVolt_LocalDiagVbat_Param1 = eSysVolt_eLow1;
  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatLow, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eLow1 and previous state was eSysVolt_eLow1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                       = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = 5u (eSysVolt_eLow1) 
///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag                                  = eVbatLow
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      =  0u;
  SysVolt_LocalDiagVbat_Param1                     = eSysVolt_eLow1;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, eVbatLow, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eNormal and previous state was eSysVolt_eLow1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                       = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = 6u (eSysVolt_eNormal) - to obtain the current state
///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag = eVbatNormal
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_LocalDiagVbat_Param1                     = eSysVolt_eHigh1;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatNormal, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eHigh3 and previous state was eSysVolt_eHigh1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                       = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = 9u (eSysVolt_eHigh3) - to obtain the current state
/// \input  SysVolt_LocalDiagVbat_Param1                      = 7u (eSysVolt_eHigh1) - to obtain the previous state 
///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag = eVbatHigh
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_LocalDiagVbat_Param1                     = eSysVolt_eHigh2;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatHigh, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eHigh3 and previous state was eSysVolt_eHigh1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                       = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = eSysVolt_eHigh1

///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag = eVbatHigh
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount = 0u;
  SysVolt_LocalDiagVbat_Param1 = eSysVolt_eNormal;
  SysVolt_RteAccess_ReadVESMainState_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatNormal, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eHigh3 and previous state was eSysVolt_eHigh1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                       = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = eSysVolt_eHigh3

///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag = eVbatHigh
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount = 0u;
  SysVolt_LocalDiagVbat_Param1 = eSysVolt_eHigh3;
  SysVolt_RteAccess_ReadVESMainState_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatNormal, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if LocalDiagVbat is calling ReportVbatDemError and if is reporting to Dem the correct Vbat state 
///                        when the current state is eSysVolt_eHigh3 and previous state was eSysVolt_eHigh1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                       = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                      = eSysVolt_eHigh3

///
/// - Expectations:
///
/// \output SysVolt_eVbatDiag = eVbatHigh
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount = 0u;
  SysVolt_LocalDiagVbat_Param1 = eSysVolt_eHigh2;
  SysVolt_RteAccess_ReadVESMainState_Param1 = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);
  SysVolt_LocalDiagVbat_Param1 = eSysVolt_eHigh1; 
  SysVolt_LocalDiagVbat(SysVolt_LocalDiagVbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_eVbatDiag, eVbatHigh, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if ReportVbatDemError is reporting to Dem the correct Vbat state when input is eVbatNormal
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_ReportVbatDemError_Param1 = 1u (eVbatNormal)
/// \input  Dem_SetEventStatus_HitCount       = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1   = 47u (UV_D)
/// \output Dem_SetEventStatus_Param2   = 0x02u (DEM_EVENT_STATUS_PASSED)
/// \output Dem_SetEventStatus_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError_Param1 = eVbatNormal;
  Dem_SetEventStatus_HitCount       = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError(SysVolt_ReportVbatDemError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                      UV_D, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,   DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                      2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if ReportVbatDemError is reporting to Dem the correct Vbat state when input is eVbatLow
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_ReportVbatDemError_Param1 = 0u (eVbatLow)
/// \input  Dem_SetEventStatus_HitCount       = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1   = 45u (OV_D)
/// \output Dem_SetEventStatus_Param2   = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError_Param1 = eVbatLow;
  Dem_SetEventStatus_HitCount       = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError(SysVolt_ReportVbatDemError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                      OV_D, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,   DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                      2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if ReportVbatDemError is reporting to Dem the correct Vbat state when input is eVbatHigh
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_ReportVbatDemError_Param1 = 2u (eVbatHigh)
/// \input  Dem_SetEventStatus_HitCount       = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1   = 47u (UV_D)
/// \output Dem_SetEventStatus_Param2   = 0x02u (DEM_EVENT_STATUS_PASSED)
/// \output Dem_SetEventStatus_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError_Param1 = eVbatHigh;
  Dem_SetEventStatus_HitCount       = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError(SysVolt_ReportVbatDemError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                      UV_D, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,   DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                      2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test If SysVolt avoid to call Dem in case of undefined VbatDemErrorState
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_ReportVbatDemError_Param1 = 3u (default value for coverage)
/// \input  Dem_SetEventStatus_HitCount       = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError_Param1 = 3u;
  Dem_SetEventStatus_HitCount       = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_ReportVbatDemError(SysVolt_ReportVbatDemError_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eLow3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount    = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1      = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1           = 3u (eSysVolt_eLow3) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount    = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1      = 3u (SysVolt_eLow3)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eLow3;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eLow3, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eLow2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 4u (eSysVolt_eLow2) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 4u (SysVolt_eLow2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eLow2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eLow2, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eLow1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions: 
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 5u (eSysVolt_eLow1) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 5u (SysVolt_eLow1)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eLow1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eLow1, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eNormal
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 6u (eSysVolt_eNormal) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 6u (SysVolt_eNormal)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eNormal;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eNormal, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eHigh1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 7u (eSysVolt_eHigh1) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 7u (SysVolt_eHigh1)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eHigh1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eHigh1, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eHigh2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 8u (eSysVolt_eHigh2) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 8u (SysVolt_eHigh2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eHigh2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eHigh2, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eHigh3
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 9u (eSysVolt_eHigh3) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 9u (eSysVolt_eHigh3)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eHigh3;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,   SysVolt_eHigh3, == );
  //AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if Stepper voltage wrapper is called and if voltage range is written correctly on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \input  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
/// \input  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = 10u (eSysVolt_eHigh4) 
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u
/// \output Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1   = 0u;
  SysVolt_RteAccess_Write_Stp_VoltState_Param1        = eSysVolt_eHigh4;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Stp_VoltState(SysVolt_RteAccess_Write_Stp_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1,              0u, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount,            0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eLow3 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions: 
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 3u (eSysVolt_eLow3)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 3u (SysVolt_eLow3)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_Rte_Write_SysVolt_FanVoltRng0_sVoltRng_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eLow3;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eLow3, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,            1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eLow2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 4u (eSysVolt_eLow2)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Port_Param1    = 4u (SysVolt_eLow2)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Port_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eLow2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eLow2, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eLow1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 5u (eSysVolt_eLow1)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 5u (SysVolt_eLow1)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eLow1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eLow1, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eNormal
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 6u (eSysVolt_eNormal)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 6u (SysVolt_eNormal)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eNormal;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eNormal, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eHigh1
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 7u (eSysVolt_eHigh1)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 7u (SysVolt_eHigh1)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eHigh1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eHigh1, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eHigh2
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 8u (eSysVolt_eHigh2)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 8u (SysVolt_eHigh2)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eHigh2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eHigh2, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written correctly on Rte when input is eSysVolt_eHigh3 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 9u (eSysVolt_eHigh3)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 9u (SysVolt_eHigh3)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eHigh3;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eHigh3, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,             1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if Fan voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 0u
/// \input  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 0u
/// \input  SysVolt_RteAccess_Write_Fan_VoltState_Param1          = 10u (eSysVolt_eHigh4)
///
/// - Expectations:
///
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1         = 255u (SysVolt_eUnknown)
/// \output Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount      = 0u;
  Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1        = 0u;
  SysVolt_RteAccess_Write_Fan_VoltState_Param1         = eSysVolt_eHigh4;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Fan_VoltState(SysVolt_RteAccess_Write_Fan_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1,   SysVolt_eUnknown, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,               1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eLow3
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eLow3
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eLow3;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1,    eSysVolt_eLow3, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,             1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eLow2
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eLow2
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eLow2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,          1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eLow2
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eLow2
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eLow2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1,    eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,             1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eNormal
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eNormal
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eNormal;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1, eSysVolt_eNormal, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,            1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eHigh1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eHigh1
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eHigh1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1, eSysVolt_eHigh1, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,           1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eHigh2
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eHigh2
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eHigh2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1, eSysVolt_eHigh2, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,           1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eHigh3
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = eSysVolt_eHigh3
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = eSysVolt_eHigh3;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1, eSysVolt_eHigh3, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,           1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if Led voltage wrapper is called and if voltage range is written on Rte according to input
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 0u
/// \input  SysVolt_RteAccess_Write_Led_VoltState_Param1          = SysVolt_eUnknown
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_Write_Led_VoltState_Param1          = SysVolt_eUnknown
/// \output Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount = 0u;
  SysVolt_RteAccess_Write_Led_VoltState_Param1    = SysVolt_eUnknown;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Write_Led_VoltState(SysVolt_RteAccess_Write_Led_VoltState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Write_Led_VoltState_Param1, SysVolt_eUnknown, == );
  AL_UNITTEST_CHECK(Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount,            1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if Vbat voltage Rte wrapper is reading the correct voltage 
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_VBatMeanValue_Hitcount                  = 0
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1            = 1000u
/// \input  SysVolt_RteAccess_Read_Vbat_Param1                      = 7200u
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_VBatMeanValue_Param1                    = 1000u
/// \output Rte_Read_IoHwAb_VBatMeanValue_Hitcount                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_Read_Vbat_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount    = 0;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1      = 1000u;
  SysVolt_RteAccess_Read_Vbat_Param1                = 7200u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_Read_Vbat(&SysVolt_RteAccess_Read_Vbat_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_Read_Vbat_Param1,          1000u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_riSysVolt_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if riSysVolt_Init is calling SysVolt_Init and if
///                         the initialization values of configuration are set according to voltage readed from Rte
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount           = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1             = 7600u
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount           = 4u
/// \output SysVolt_asInStateResult[0].ePreviousVoltageRange         = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[0].eVoltageRangeResult          = 4u (eSysVolt_eLow2)
/// \output SysVolt_asInStateResult[0].unDebounceValTo_Ms           = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_riSysVolt_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 7600u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  riSysVoltInit();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,               4u, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].ePreviousVoltageRange, eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].eVoltageRangeResult,   eSysVolt_eLow2, == );
  AL_UNITTEST_CHECK(SysVolt_asInStateResult[0].unDebounceValTo_Ms,                0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_rpSysVolt_Cycle0_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if rpSysVolt_Cycle0 is calling SysVolt_Cycle0 and
///                         if SysVolt_asInStateResult parameters are set according to voltage SYSVOLT_GENERIC_LAST readed from Rte
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_boCodingValidStatus                                = TRUE
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1               = 0xFFFFu (SYSVOLT_GENERIC_LAST)
/// \input  SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
/// \input  SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = 8u (eSysVolt_eHigh2)
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount             = 4u
/// \output SysVolt_boCodingValidStatus                                = TRUE
/// \output SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = 8u (eSysVolt_eHigh2)
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_rpSysVolt_Cycle0_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_boCodingValidStatus                   = TRUE;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1          = SYSVOLT_GENERIC_LAST;

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) 
  {
    SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange = eSysVolt_eHigh2;
    SysVolt_asInStateResult[ucConfigIdx].eVoltageRangeResult   = eSysVolt_eHigh2;
  }

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  rpSysVolt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount,                            4u, == );
  AL_UNITTEST_CHECK(SysVolt_boCodingValidStatus,                                             TRUE, == );

  for (uint8 ucConfigIdx = 0; ucConfigIdx < 3; ucConfigIdx++) {
    AL_UNITTEST_CHECK(SysVolt_asInStateResult[ucConfigIdx].ePreviousVoltageRange, eSysVolt_eHigh2, == );
  }
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if vehicle electric state is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1            = 0u
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadVESMainState_Param1            = eSysVolt_State_Stop
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Stop;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_RetVal = SysVolt_RteAccess_ReadVESMainState(&SysVolt_RteAccess_ReadVESMainState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadVESMainState_Param1, eSysVolt_State_Stop, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,                       1u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if vehicle electric state is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1            = 0u
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Stop
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadVESMainState_Param1            = eSysVolt_State_Stop
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Stop;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_RetVal = SysVolt_RteAccess_ReadVESMainState(&SysVolt_RteAccess_ReadVESMainState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadVESMainState_Param1, eSysVolt_State_Stop, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,                       1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if vehicle electric state is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1            = 0u
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Ignition
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadVESMainState_Param1            = eSysVolt_State_Contact
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_RetVal = SysVolt_RteAccess_ReadVESMainState(&SysVolt_RteAccess_ReadVESMainState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadVESMainState_Param1, eSysVolt_State_Contact, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,                       1u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if vehicle electric state is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1            = 0u
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Start
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadVESMainState_Param1            = eSysVolt_State_Start
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_RetVal = SysVolt_RteAccess_ReadVESMainState(&SysVolt_RteAccess_ReadVESMainState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadVESMainState_Param1, eSysVolt_State_Start, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,                        1u, == );
}


// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if vehicle electric state is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1            = 0u
/// \input  Rte_Read_SysMon_VehNetState_HitCount                 = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Invalid
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadVESMainState_Param1            = eSysVolt_State_InvalidSEV
/// \output Rte_Read_SysMon_VehNetState_HitCount                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Invalid;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_RetVal = SysVolt_RteAccess_ReadVESMainState(&SysVolt_RteAccess_ReadVESMainState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadVESMainState_Param1, eSysVolt_State_InvalidSEV, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,                             1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_1_1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_1_1
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_1_1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                             1u, == );
}


// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_1_2
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_1_2
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_2;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_1_2, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                             1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_1_3c
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_1_3c
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_3c;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_1_3c, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                              1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_1_3r
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_1_3r
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_3r;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_1_3r, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                              1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_2_1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_2_1
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_2_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_2_1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                             1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_6
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_3c_1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_3c_1
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_6(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_3c_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_3c_1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                              1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_7
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_3r_1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_3r_1
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_7(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_3r_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_3r_1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                              1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_8
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_4_1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_4_1
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_8(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_4_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_4_1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                             1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_9
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_5_5
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_5_5
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_9(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_5_5;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_5_5, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                             1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_10
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_1_3vr
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_1_3vr
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_10(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_3vr;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_1_3vr, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                               1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_11
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_3vr_1
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_3vr_1
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_11(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1                = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                   = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty             = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_3vr_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_3vr_1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                               1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_12
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_INVALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = 12u
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_Invalid
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_12(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_INVALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 12u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_Invalid, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                                 1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_13
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = eEtatFee_Invalid
///
/// - Expectations:
///
/// \output SysVolt_RteAccess_ReadElectricalSuppState_RetVal            = SysVolt_eEtatFee_Invalid
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_13(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_Invalid;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_RteAccess_ReadElectricalSuppState_RetVal, SysVolt_eEtatFee_Invalid, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                                 1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_14
///
/// \Test Case Description
///        - Test subject: Test if TMC pressure is read correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                   = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount                      = 0u
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState     = 13u
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount                      = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_14(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadVESMainState_Param1               = 0u;
  Rte_Read_SigPrep_ElecSupState_HitCount                  = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty            = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 13u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_RteAccess_ReadElectricalSuppState_RetVal = SysVolt_RteAccess_ReadElectricalSuppState();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount,                                 1u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if changes of electric veh state for STT state is detected
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                   = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState        = eEtatFee_4_1
///
/// - Expectations:
///
/// \output SysVolt_DetectElecTransition_RetVal                            = TRUE
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_4_1;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_DetectElecTransition_RetVal = SysVolt_DetectElecTransition();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_DetectElecTransition_RetVal, TRUE, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if changes of electric veh state for STT state is detected
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty                   = SIG_VALID
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState        = eEtatFee_Invalid
///
/// - Expectations:
///
/// \output SysVolt_DetectElecTransition_RetVal                            = FALSE
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_Invalid;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_DetectElecTransition_RetVal = SysVolt_DetectElecTransition();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysVolt_DetectElecTransition_RetVal, FALSE, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_StMachine_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the state machine for voltage behavior based on cfg file works correctly
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  SysVolt_StMachine_Param1                   = TRUE
///
/// - Expectations:
///
/// \output -
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_StMachine_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysVolt_StMachine_Param1 = TRUE;
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_StMachine(SysVolt_StMachine_Param1);
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_StMachine_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if if the requested condition are met for realizing the diagnoss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                              = 0u
/// \input  SysVolt_eVbatDiag                                        = 5u
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                = 0u
/// \input  NvmBlockDeltaPwmPara.eNVM_Function_STT                   = eOptionSTT_Absent
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = eSysVolt_State_Contact
/// \input  Rte_Read_SysMon_VehNetState_HitCount                     = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                              = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Diagnosis_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_eVbatDiag                                = 5u;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  NvmBlockDeltaPwmPara.eNVM_Function_STT           = eOptionSTT_Absent;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Diagnosis();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    0u, == );
}


// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_StMachine_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if if the requested condition are met for realizing the diagnoss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                              = 0u
/// \input  SysVolt_LocalDiagVbat_Param1                             = eVbatHigh
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                = 0u
/// \input  NvmBlockDeltaPwmPara.eNVM_Function_STT                   = eOptionSTT_Absent
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = VESState_Ignition
/// \input  Rte_Read_SysMon_VehNetState_HitCount                     = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1                                = UV_D
/// \output Dem_SetEventStatus_Param2                                = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount                              = 2u
/// \output Rte_Read_SysMon_VehNetState_HitCount                     = 2u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Diagnosis_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_eVbatDiag                                = eVbatHigh;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  NvmBlockDeltaPwmPara.eNVM_Function_STT           = eOptionSTT_Absent;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Diagnosis();
  SysVolt_eVbatDiag = eSysVolt_eLow1;
  SysVolt_Diagnosis();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    2u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                    UV_D, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,           2u, == );
}

// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_StMachine_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if if the requested condition are met for realizing the diagnoss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                              = 0u
/// \input  SysVolt_eVbatDiag                                        = eVbatLow
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                = 0u
/// \input  NvmBlockDeltaPwmPara.eNVM_Function_STT                   = eOptionSTT_Absent
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = VESState_Ignition
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1                                = OV_D
/// \output Dem_SetEventStatus_Param2                                = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount                              = 2u
/// \output Rte_Read_SysMon_VehNetState_HitCount                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Diagnosis_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_eVbatDiag                                = eVbatLow;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  NvmBlockDeltaPwmPara.eNVM_Function_STT           = eOptionSTT_Absent;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Diagnosis();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                    OV_D, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,           1u, == );
}


// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_StMachine_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if if the requested condition are met for realizing the diagnoss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                              = 0u
/// \input  SysVolt_eVbatDiag                                        = eVbatNormal
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                = 0u
/// \input  NvmBlockDeltaPwmPara.eNVM_Function_STT                   = eOptionSTT_Absent
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = VESState_Ignition
/// \input  Rte_Read_SysMon_VehNetState_HitCount                     = 0u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1                                = UV_D
/// \output Dem_SetEventStatus_Param2                                = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount                              = 2u
/// \output Rte_Read_SysMon_VehNetState_HitCount                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Diagnosis_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                       = 0u;
  SysVolt_eVbatDiag                                 = eVbatNormal;
  SysVolt_RteAccess_ReadVESMainState_Param1         = 0u;
  NvmBlockDeltaPwmPara.eNVM_Function_STT            = eOptionSTT_Absent;
  Rte_Read_SysMon_VehNetState_HitCount              = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState  = VESState_Ignition;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Diagnosis();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,                    UV_D, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,           1u, == );
}


// -----------------------------------------------------------------------------
/// \Test Case : Mt_SysVolt_SysVolt_StMachine_TestCase_5
///
/// \Test Case Description
///        - Test subject: Test if if the requested condition are met for realizing the diagnoss
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                              = 0u
/// \input  SysVolt_eVbatDiag                                        = eVbatNormal
/// \input  SysVolt_RteAccess_ReadVESMainState_Param1                = 0u
/// \input  NvmBlockDeltaPwmPara.eNVM_Function_STT                   = eOptionSTT_Present
/// \input  Rte_Read_SysMon_VehNetState_HitCount                     = 0u
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = VESState_Ignition
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                              = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysVolt_SysVolt_Diagnosis_TestCase_5(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Dem_SetEventStatus_HitCount                      = 0u;
  SysVolt_eVbatDiag                                = eVbatNormal;
  SysVolt_RteAccess_ReadVESMainState_Param1        = 0u;
  NvmBlockDeltaPwmPara.eNVM_Function_STT           = eOptionSTT_Present;
  Rte_Read_SysMon_VehNetState_HitCount             = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysVolt_Diagnosis();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );
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
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Init_TestCase_1", Mt_SysVolt_SysVolt_Init_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Init_TestCase_2", Mt_SysVolt_SysVolt_Init_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_1", Mt_SysVolt_SysVolt_Cycle_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_2", Mt_SysVolt_SysVolt_Cycle_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_3", Mt_SysVolt_SysVolt_Cycle_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_4", Mt_SysVolt_SysVolt_Cycle_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_5", Mt_SysVolt_SysVolt_Cycle_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_6", Mt_SysVolt_SysVolt_Cycle_TestCase_6);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_7", Mt_SysVolt_SysVolt_Cycle_TestCase_7);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_8", Mt_SysVolt_SysVolt_Cycle_TestCase_8);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_9", Mt_SysVolt_SysVolt_Cycle_TestCase_9);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Cycle_TestCase_10", Mt_SysVolt_SysVolt_Cycle_TestCase_10);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_ParaFct0_TestCase_1", Mt_SysVolt_SysVolt_ParaFct0_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_ParaFct0_TestCase_2", Mt_SysVolt_SysVolt_ParaFct0_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_1", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_2", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_3", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_4", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_5", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_6", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_6);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_7", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_7);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_8", Mt_SysVolt_SysVolt_LocalDiagVbat_TestCase_8);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_1", Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_2", Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_3", Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_4", Mt_SysVolt_SysVolt_ReportVbatDemError_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_1", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_2", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_3", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_4", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_5", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_6", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_6);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_7", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_7);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_8", Mt_SysVolt_SysVolt_RteAccess_Write_Stp_VoltState_TestCase_8);
 ALUnitTest_AddFunction("Mt_SysVolt_Rte_Write_SysVolt_FanVoltRng0_sVoltRng_TestCase_1", Mt_SysVolt_Rte_Write_SysVolt_FanVoltRng0_sVoltRng_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_2", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_3", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_4", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_5", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_6", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_6);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_7", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_7);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_8", Mt_SysVolt_SysVolt_RteAccess_Write_Fan_VoltState_TestCase_8);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Read_Vbat_TestCase_1", Mt_SysVolt_SysVolt_RteAccess_Read_Vbat_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_riSysVolt_Init_TestCase_1", Mt_SysVolt_riSysVolt_Init_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_rpSysVolt_Cycle0_TestCase_1", Mt_SysVolt_rpSysVolt_Cycle0_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_1", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_2", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_3", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_4", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_5", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_6", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_6);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_7", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_7);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_8", Mt_SysVolt_SysVolt_RteAccess_Write_Led_VoltState_TestCase_8);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_1", Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_2", Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_3", Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_4", Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_5", Mt_SysVolt_SysVolt_RteAccess_ReadVESMainState_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_1", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_2", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_3", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_4", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_5", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_5);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_6", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_6);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_7", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_7);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_8", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_8);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_9", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_9);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_10", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_10);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_11", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_11);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_12", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_12);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_13", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_13);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_14", Mt_SysVolt_SysVolt_RteAccess_ReadElectricalSuppState_TestCase_14);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_1", Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_2", Mt_SysVolt_SysVolt_DetectElecTransition_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_StMachine_TestCase_1", Mt_SysVolt_SysVolt_StMachine_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Diagnosis_TestCase_1", Mt_SysVolt_SysVolt_Diagnosis_TestCase_1);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Diagnosis_TestCase_2", Mt_SysVolt_SysVolt_Diagnosis_TestCase_2);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Diagnosis_TestCase_3", Mt_SysVolt_SysVolt_Diagnosis_TestCase_3);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Diagnosis_TestCase_4", Mt_SysVolt_SysVolt_Diagnosis_TestCase_4);
 ALUnitTest_AddFunction("Mt_SysVolt_SysVolt_Diagnosis_TestCase_5", Mt_SysVolt_SysVolt_Diagnosis_TestCase_5);
}

// EOF

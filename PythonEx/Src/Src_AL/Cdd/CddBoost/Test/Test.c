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
/// \brief  Unit Test Cases for software component module CddBoost
///
/// \author
///         mailTo:
//-----------------------------------------------------------------------------

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include <Test_Ext.h>
#include "Test_Stubs.h"

// Headers of the unit test Module
#include <Test.h>
#include <Test_Adapter.h>

//=============================================================================
//  Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_Init
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that booster pins are enabled/disabled based on EFT data.
///        This test case is done for coverage purpose (adapter function), 
///        actual CddBoost initialization is performed by Mt_CddNcv78702_Init
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results:
///        - High byte of data mirror must be different from 0
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_Init(void)
{
  //Step 1) Set pre - conditions
  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddBoost_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  //coverage only (adapter function), actual CddBoost initialization is performed by Mt_CddNcv78702_Init
  AL_UNITTEST_CHECK(0u, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_SetPara
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:
///      Check if the functions sets correctly the parameter validity
///       status
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results:
///        - CddBoost_boParaValid = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_SetPara(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_boParaValid = FALSE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddBoost_SetPara(TRUE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_boParaValid, TRUE, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_Cycle20ms
///
/// \Test Case Description
///    - Test subject:
///      Check if empty function is called (coverage only)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_Cycle20ms(void)
{
  //Step 1) Set pre - conditions
  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddBoost_Cycle20ms();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  // none: coverage only
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_SetTarget
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:
///       Set a new value for boost voltage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
/// \Steps:
///         Step1: Set target Booster Voltage
///         Step2: Set ECU voltage to 5,5V
///         Step3: Keep booster voltage as target 
///         Step4: Set ECU voltage to 13V
///         Step5: Keep booster voltage as target 
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost Voltage is updated (CddBoost_sTarget.aunBoostVolt_mV[0])
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_SetTarget(void)
{
  //Step 1) Set pre - conditions
  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddBoost_SetTarget_Param1.aunBoostVolt_mV[0] = 47000u;
  Test_SetECUSupply(5500u);

  //Step 3) Call the FUT
  CddBoost_SetTarget(&CddBoost_SetTarget_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0], 47000u, ==);

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_SetECUSupply(13000u);

  //Step 3) Call the FUT
  CddBoost_SetTarget(&CddBoost_SetTarget_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0], 47000u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_GetStatus
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:
///       Check Boost status is updated by checking different kind of errors
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Reset internal error and mark no booster driver available
///         Step2: Check Booster Status is eCddBoost_NoSupport
///         Step3: Set SPI error detected
///         Step4: Check Booster Status is eCddBoost_ErrSpi
///         Step5: Remove SPI error and set Reset detected
///         Step6: Check Booster Status is eCddBoost_Reset
///         Step7: Remove Reset error and set Thermal Shutdown
///         Step8: Check Booster Status is eCddBoost_ErrThermShutdn
///         Step9: Remove internal errors
///         Step10: Check Booster Status is eCddBoost_StatusOk
///
///    - Preconditions: none
///
///    - Expected test results:
///        -Read Boost status based on input errors given in previous steps
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_GetStatus(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  Test_SetThermalWarning (0u, FALSE);

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddBoost_GetStatus_Param1.aStatus[0] = eCddBoost_NoSupport;
  CddBoost_ulAvailMask = 0u;

  //Step 3) Call the FUT
  CddBoost_GetStatus(&CddBoost_GetStatus_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_GetStatus_Param1.aStatus[0], eCddBoost_NoSupport, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddBoost_GetStatus_Param1.aStatus[0] = eCddBoost_NoSupport;
  CddBoost_ulAvailMask = 1u;
  Test_SetSpiError       (0u, TRUE);

  //Step 3) Call the FUT
  CddBoost_GetStatus(&CddBoost_GetStatus_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_GetStatus_Param1.aStatus[0], eCddBoost_ErrSpi, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddBoost_GetStatus_Param1.aStatus[0] = eCddBoost_NoSupport;
  Test_SetSpiError       (0u, FALSE);
  Test_SetReset          (0u, TRUE);

  //Step 3) Call the FUT
  CddBoost_GetStatus(&CddBoost_GetStatus_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_GetStatus_Param1.aStatus[0], eCddBoost_Reset, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddBoost_GetStatus_Param1.aStatus[0] = eCddBoost_NoSupport;
  Test_SetReset          (0u, FALSE);
  Test_SetThermalShutDown(0u, TRUE);

  //Step 3) Call the FUT
  CddBoost_GetStatus(&CddBoost_GetStatus_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_GetStatus_Param1.aStatus[0], eCddBoost_ErrThermShutdn, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddBoost_GetStatus_Param1.aStatus[0] = eCddBoost_NoSupport;
  Test_SetThermalShutDown(0u, FALSE);  // reset condition

  //Step 3) Call the FUT
  CddBoost_GetStatus(&CddBoost_GetStatus_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_GetStatus_Param1.aStatus[0], eCddBoost_StatusOk, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_Shutdown
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        test needed for coverage. Function is an adapter and actual booster
///        shutdown is tested by Mt_CddNcv78702_Shutdown
///
///    - Test Design Technique: Requirements-based test
///                             ET (Exploratory Test)
///
///    - Preconditions:
///         - N/A
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_Shutdown(void)
{
  //Unit test just for coverage.

  //Step x: call FUT
  CddBoost_Shutdown();
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
  // CddBoost.c tests
  ALUnitTest_AddFunction("Mt_CddBoost_Init",             Mt_CddBoost_Init);
  ALUnitTest_AddFunction("Mt_CddBoost_SetPara",       Mt_CddBoost_SetPara);
  ALUnitTest_AddFunction("Mt_CddBoost_Cycle20ms",   Mt_CddBoost_Cycle20ms);
  ALUnitTest_AddFunction("Mt_CddBoost_SetTarget",   Mt_CddBoost_SetTarget);
  ALUnitTest_AddFunction("Mt_CddBoost_GetStatus",   Mt_CddBoost_GetStatus);
  ALUnitTest_AddFunction("Mt_CddBoost_Shutdown",     Mt_CddBoost_Shutdown);

  // project specific tests of adapter
  ALUnitTest_AddTests_Adapter();
}

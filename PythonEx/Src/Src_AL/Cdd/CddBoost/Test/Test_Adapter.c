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
/// \file  Test_Adapter.c
///
/// \brief  Unit Test Cases for software component module CddBoost_Adapter
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
#include <Test_Adapter.h>

//=============================================================================
//  Test cases
//=============================================================================
//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddBoostInit_TestCase1
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that the boost driver remains uninitialized if coding data is
///         not valid
///
///    - Test Design Technique:   Requirement based test
///                               ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - CddBoost_sStatus.aStatus[0] = eCddBoost_NoSupport
///
//-----------------------------------------------------------------------------
void Mt_riCddBoostInit_TestCase1(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_sStatus.aStatus[0] = eCddBoost_NoSupport;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  riCddBoostInit();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sStatus.aStatus[0], eCddBoost_NoSupport, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddBoostInit_TestCase2
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that the boost driver is initialized by the returned
///         boost status if coding data is valid
///
///    - Test Design Technique:   Requirement based test
///                               ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - CddBoost_sStatus.aStatus[0] = eCddBoost_StatusOk
///
//-----------------------------------------------------------------------------
void Mt_riCddBoostInit_TestCase2(void)
{
  //Step 1) Set pre - conditions
  tNvmPara_CodingArea sTestDataInit;

  // default initialization
  CddBoost_sStatus.aStatus[0] = eCddBoost_NoSupport;
  Rte_Read_CodM_CddBoost_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddBoost_Para_Param1.psCodingParameters_Blocks = &sTestDataInit;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  riCddBoostInit();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sStatus.aStatus[0], eCddBoost_StatusOk, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddBoostInit
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:  Check execution of the initialization function
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Expected test results: All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_riCddBoostInit(void)
{
  Mt_riCddBoostInit_TestCase1();
  Mt_riCddBoostInit_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddBoostNewTarget
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check write of a new target voltage
///
///    - Test Design Technique:   - Requirement based test
///                               - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost target voltage must take the value read from RTE port
///          CddBoost_sTarget.aunBoostVolt_mV[0] = 49000
///
//-----------------------------------------------------------------------------
void Mt_reCddBoostNewTarget(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_sTarget.aunBoostVolt_mV[0] = 0u;
  CddBoost_unV_Boost                  = 49000u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  reCddBoostNewTarget();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0], 49000, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddBoost_Cycle_TestCase1
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that the execution of the cyclic function sets the booster
///        as not supported and stops the cyclic behaviour when the booster
///        parameters are invalid
///
///    - Test Design Technique: - Requirement based test
///                             - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost target voltage must take the value read from RTE port
///          CddBoost_sTarget.aunBoostVolt_mV[0] = 49000u
///          CddBoost_sStatus.aStatus[0]         = eCddBoost_NoSupport
///
//-----------------------------------------------------------------------------
void Mt_rpCddBoost_Cycle_TestCase1(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_sTarget.aunBoostVolt_mV[0] = 0u;
  CddBoost_sStatus.aStatus[0] = eCddBoost_Reset;
  CddBoost_SetPara(FALSE);
  CddBoost_boCodingValidity = TRUE;
  CddBoost_unV_Boost  = 49000u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  rpCddBoost_Cycle();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0], 49000u, == );
  AL_UNITTEST_CHECK(CddBoost_sStatus.aStatus[0], eCddBoost_NoSupport, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddBoost_Cycle_TestCase2
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that the execution of the cyclic function updates the booster status
///        in case SPI error was found and keeps the target voltage from RTE
///
///    - Test Design Technique: - Requirement based test
///                             - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost target voltage must take the value read from RTE port
///          CddBoost_sTarget.aunBoostVolt_mV[0] = 49000u
///          CddBoost_sStatus.aStatus[0]         = eCddBoost_ErrSpi
///          Rte_Write_CddBoost_BoostState_Param1.aboBoostDefect[0] = TRUE
///
//-----------------------------------------------------------------------------
void Mt_rpCddBoost_Cycle_TestCase2(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_sTarget.aunBoostVolt_mV[0] = 0u;
  Rte_Write_CddBoost_BoostState_Param1.aboBoostDefect[0] = 0u;
  Test_SetSpiError(0U, TRUE);
  CddBoost_boCodingValidity = TRUE;
  CddBoost_boParaInit = FALSE;
  applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_OVER_VOLTAGE[11] = 235u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  rpCddBoost_Cycle();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0],      49000u, ==);
  AL_UNITTEST_CHECK(CddBoost_sStatus.aStatus[0],    eCddBoost_ErrSpi, ==);
  AL_UNITTEST_CHECK(Rte_Write_CddBoost_BoostState_Param1.aboBoostDefect[0], TRUE, ==);

  //restore value
  applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_OVER_VOLTAGE[11] = 0u;

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddBoost_Cycle_TestCase3
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that the execution of the cyclic function does not execute in case
///        of invalid coding data and keeps the last target voltage
///
///    - Test Design Technique: - Requirement based test
///                             - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost target voltage must take the value read from RTE port
///          CddBoost_sTarget.aunBoostVolt_mV[0] = 49000u
///          CddBoost_sStatus.aStatus[0]         = eCddBoost_StatusOk
///
//-----------------------------------------------------------------------------
void Mt_rpCddBoost_Cycle_TestCase3(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_sTarget.aunBoostVolt_mV[0] = 49000u;
  Rte_Write_CddBoost_BoostState_Param1.aboBoostDefect[0] = 0u;
  CddBoost_sStatus.aStatus[0] = eCddBoost_StatusOk;
  Test_SetSpiError(0U, TRUE);
  CddBoost_boCodingValidity = FALSE;
  Rte_Read_CodM_CddBoost_Para_Param1.eCodingState = 2u; //unknown command

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  rpCddBoost_Cycle();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0],     49000u, == );
  AL_UNITTEST_CHECK(CddBoost_sStatus.aStatus[0], eCddBoost_StatusOk, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddBoost_Cycle
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:  Check execution of the cyclic function
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Expected test results: The test cases : Mt_rpCddBoost_Cycle_TestCase1,
///                             Mt_rpCddBoost_Cycle_TestCase2 are both passed
///
//-----------------------------------------------------------------------------
void Mt_rpCddBoost_Cycle(void)
{
  Mt_rpCddBoost_Cycle_TestCase1();
  Mt_rpCddBoost_Cycle_TestCase2();
  Mt_rpCddBoost_Cycle_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddBoost_CalcTgtBoostVolt
///
/// \Functional Safety: ASIL-B
///
/// \Test Case Description
///    - Test subject:
///        Check that the booster undervoltage threshold for error detection is
///        no calculated when the booster coding parameters are invalid
///
///    - Test Design Technique: - Requirement based test
///                             - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results:
///        - Boost target voltage must take the value read from RTE port
///          CddBoost_sTarget.aunBoostVolt_mV[0] = 49000u
///          CddBoost_unV_Boost                  = 50000u
///
//-----------------------------------------------------------------------------
void Mt_CddBoost_CalcTgtBoostVolt(void)
{
  //Step 1) Set pre - conditions
  // default initialization
  CddBoost_sTarget.aunBoostVolt_mV[0] = 0u;
  CddBoost_unV_Boost = 50000u; // CDDBOOST_BoostVoltLimit +1000 (FULL)

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddBoost_CalcTgtBoostVolt(FALSE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CddBoost_sTarget.aunBoostVolt_mV[0],      0u, == );
  AL_UNITTEST_CHECK(CddBoost_unV_Boost,                   50000u, == ); // for normal operaion, it should have been limtied to 49000u

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
void ALUnitTest_AddTests_Adapter(void)
{
  ALUnitTest_AddFunction("Mt_riCddBoostInit"              , Mt_riCddBoostInit);
  ALUnitTest_AddFunction("Mt_reCddBoostNewTarget"         , Mt_reCddBoostNewTarget);
  ALUnitTest_AddFunction("Mt_rpCddBoost_Cycle"            , Mt_rpCddBoost_Cycle);
  ALUnitTest_AddFunction("Mt_CddBoost_CalcTgtBoostVolt"   , Mt_CddBoost_CalcTgtBoostVolt);
}

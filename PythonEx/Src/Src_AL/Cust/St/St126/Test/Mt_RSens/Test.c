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
/// \file   Test.c
///
/// \brief  Unit Test Cases for RSens
///
/// \author Braga Ionut-Cosmin (M01467A)
///         mailTo:ionutcosmin.braga[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaRSens.c
//            - RSens.c
//            - RSens_Data.c
//            - RSensRteAccess.c
//==============================================================================

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

//RSensRteAccess.c
//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Rte_Read_PCBNTC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the voltage of the PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input RSens_Rte_Read_PCBNTC_Param1     = 10u
/// \input Rte_Read_IoHwAb_GetPCB_HitCount  = 0u
///
///   - Expectations:
///
/// \output RSens_Rte_Read_PCBNTC_Param1    = 10u
/// \output Rte_Read_IoHwAb_GetPCB_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Rte_Read_PCBNTC(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_IoHwAb_GetPCB_Param1   = 10u;
  Rte_Read_IoHwAb_GetPCB_HitCount = 0u;
  //Step 3) Call the FUT
  RSens_Rte_Read_PCBNTC(&RSens_Rte_Read_PCBNTC_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_Rte_Read_PCBNTC_Param1, 10u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetPCB_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Rte_Read_ExtNTC_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the voltage from NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input   RSens_Rte_Read_ExtNTC_Param1             = 0u
/// \input   Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount = 0u
/// \input   Rte_Read_IoHwAb_GetVoltage_NTCs_Param1.aunNtcVoltage[0] = 10u
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount  = 1u
/// \output RSens_Rte_Read_ExtNTC_RetVal              = 10u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Rte_Read_ExtNTC_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Rte_Read_ExtNTC_Param1 = 0u;
  Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount = 0u;
  Rte_Read_IoHwAb_GetVoltage_NTCs_Param1.aunNtcVoltage[0] = 10u;

  //Step 3) Call the FUT
  RSens_Rte_Read_ExtNTC_RetVal = RSens_Rte_Read_ExtNTC(RSens_Rte_Read_ExtNTC_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount, 1u, == );
  AL_UNITTEST_CHECK(RSens_Rte_Read_ExtNTC_RetVal, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Rte_Read_ExtNTC_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the voltage
///                     from NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input RSens_Rte_Read_ExtNTC_Param1  = 1000u;
///
///   - Expectations:
///
/// \output RSens_Rte_Read_ExtNTC_RetVal = 0xFFFFU
///
//-----------------------------------------------------------------------------
void Mt_RSens_Rte_Read_ExtNTC_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Rte_Read_ExtNTC_Param1 = 1000u;

  //Step 3) Call the FUT
  RSens_Rte_Read_ExtNTC_RetVal = RSens_Rte_Read_ExtNTC(RSens_Rte_Read_ExtNTC_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_Rte_Read_ExtNTC_RetVal, 0xFFFFU, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Rte_Read_ExtNTC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the voltage
///                     from NTCs
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Rte_Read_ExtNTC(void)
{
  Mt_RSens_Rte_Read_ExtNTC_TestCase_1();
  Mt_RSens_Rte_Read_ExtNTC_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_RteAccess_Write_BinnigClasses
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function write actual binning classes
///                     for each led channel.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input tsRte_Binning0 sActParam = { 0x00 }
/// \input RSens_RteAccess_Write_BinnigClasses_Param1  = 0u
/// \input RSens_RteAccess_Write_BinnigClasses_Param2  = &sActParam
///
///   - Expectations:
///
/// \output RSens_RteAccess_Write_BinnigClasses_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_RSens_RteAccess_Write_BinnigClasses(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  tsRte_Binning0 sActParam = { 0x00 };
  RSens_RteAccess_Write_BinnigClasses_Param1 = 0u;
  RSens_RteAccess_Write_BinnigClasses_Param2 = &sActParam;

  //Step 3) Call the FUT
  RSens_RteAccess_Write_BinnigClasses_RetVal = RSens_RteAccess_Write_BinnigClasses(RSens_RteAccess_Write_BinnigClasses_Param1, RSens_RteAccess_Write_BinnigClasses_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_RteAccess_Write_BinnigClasses_RetVal, 0u, == );

}

//RSens.c
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_ParallelResistor_Exists_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function Rsens_ParallelResistor_Exists
///                     returns the presence of a parallel resistor for external NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input Rsens_ParallelResistor_Exists_Param1 = 1u;
/// \input RSens_boResistor_Para_Test = TRUE;
///
///   - Expectations:
///
/// \output Rsens_ParallelResistor_Exists_RetVal = TRUE;
///
//-----------------------------------------------------------------------------
void Mt_Rsens_ParallelResistor_Exists_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rsens_ParallelResistor_Exists_Param1 = 1u;
  RSens_boResistor_Para_Test = TRUE;

  //Step 3) Call the FUT
  Rsens_ParallelResistor_Exists_RetVal = Rsens_ParallelResistor_Exists(Rsens_ParallelResistor_Exists_Param1);
  
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rsens_ParallelResistor_Exists_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_ParallelResistor_Exists_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function Rsens_ParallelResistor_Exists
///                     returns the presence of a parallel resistor for external NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input RSens_boResistor_Para_Test = FALSE;
/// \input Rsens_ParallelResistor_Exists_Param1 = 2u;
///
///   - Expectations:
///
/// \output Rsens_ParallelResistor_Exists_RetVal = TRUE;
///
//-----------------------------------------------------------------------------
void Mt_Rsens_ParallelResistor_Exists_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boResistor_Para_Test = FALSE;
  Rsens_ParallelResistor_Exists_Param1 = 2u;

  //Step 3) Call the FUT
  Rsens_ParallelResistor_Exists_RetVal = Rsens_ParallelResistor_Exists(Rsens_ParallelResistor_Exists_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rsens_ParallelResistor_Exists_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_ParallelResistor_Exists
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function Rsens_ParallelResistor_Exists
///                     returns the presence of a parallel resistor for external NTCs
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Rsens_ParallelResistor_Exists(void)
{
  Mt_Rsens_ParallelResistor_Exists_TestCase_1();
  Mt_Rsens_ParallelResistor_Exists_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_ParaFct0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is called when coding data are
///                     available
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  RSens_pCodingArea     = RSens_ParaFct0_Param2
/// \input  RSens_ParaFct0_Param1 = eParaFct0_CodingDataInvalid
/// \input  RSens_eCodingMode     = RSENS_CODINGMODE_UNDEFINE
///
///   - Expectations:
///
/// \output RSens_eCodingMode     = RSENS_CODINGMODE_INVALID
///
//-----------------------------------------------------------------------------
void Mt_RSens_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_pCodingArea     = RSens_ParaFct0_Param2;
  RSens_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  RSens_eCodingMode     = RSENS_CODINGMODE_UNDEFINE;

  //Step 3) Call the FUT
  RSens_ParaFct0(RSens_ParaFct0_Param1, RSens_ParaFct0_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_eCodingMode, RSENS_CODINGMODE_INVALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_ParaFct0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is called when coding data are
///                     available
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_pCodingArea             = RSens_ParaFct0_Param2
/// \input  RSens_ParaFct0_Param1         = eParaFct0_CodingDataValid
/// \input  RSens_eCodingMode             = RSENS_CODINGMODE_UNDEFINE
///
///   - Expectations:
///
/// \output RSens_eCodingMode             = RSENS_CODINGMODE_VALID
///
//-----------------------------------------------------------------------------
void Mt_RSens_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_pCodingArea             = RSens_ParaFct0_Param2;
  RSens_ParaFct0_Param1         = eParaFct0_CodingDataValid;
  RSens_eCodingMode             = RSENS_CODINGMODE_UNDEFINE;

  //Step 3) Call the FUT
  RSens_ParaFct0(RSens_ParaFct0_Param1, RSens_ParaFct0_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_eCodingMode, RSENS_CODINGMODE_VALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is called when coding data are
///                     available
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_ParaFct0(void)
{
  Mt_RSens_ParaFct0_TestCase_1();
  Mt_RSens_ParaFct0_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_TempLimitation_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if the temperature is
///                    between the correct range and if not limit it
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_TempLimitation_Param1 = &snValueParam
///
///   - Expectations:
///
/// \output RSens_TempLimitation_Param1 = RSENS_MIN_LIMIT_TEMP
///
//-----------------------------------------------------------------------------
void Mt_RSens_TempLimitation_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  sint16 snValueParam = -440;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_TempLimitation_Param1 = &snValueParam;

  //Step 3) Call the FUT
  RSens_TempLimitation(RSens_TempLimitation_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(*RSens_TempLimitation_Param1, RSENS_MIN_LIMIT_TEMP, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_TempLimitation_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if the temperature is
///                    between the correct range and if not limit it
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_TempLimitation_Param1 = &snValueParam
///
///   - Expectations:
///
/// \output RSens_TempLimitation_Param1 = RSENS_MAX_LIMIT_TEMP
///
//-----------------------------------------------------------------------------
void Mt_RSens_TempLimitation_TestCase_2(void)
{
    //Step 1) Set pre - conditions
    sint16 snValueParam = 1600;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    RSens_TempLimitation_Param1 = &snValueParam;

    //Step 3) Call the FUT
    RSens_TempLimitation(RSens_TempLimitation_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(*RSens_TempLimitation_Param1, RSENS_MAX_LIMIT_TEMP, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_TempLimitation_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if the temperature is
///                     between the correct range and if not limit it
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input RSens_TempLimitation_Param1 = &snValueParam
///
///   - Expectations:
///
/// \output RSens_TempLimitation_Param1 = 0
///
//-----------------------------------------------------------------------------
void Mt_RSens_TempLimitation_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  sint16 snValueParam = 0;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_TempLimitation_Param1 = &snValueParam;

  //Step 3) Call the FUT
  RSens_TempLimitation(RSens_TempLimitation_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(*RSens_TempLimitation_Param1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_TempLimitation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if the temperature is
///                     between the correct range and if not limit it
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_TempLimitation(void)
{
  Mt_RSens_TempLimitation_TestCase_1();
  Mt_RSens_TempLimitation_TestCase_2();
  Mt_RSens_TempLimitation_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_CheckErrorBinning
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the voltage range for
///                     binning classes, set the specific error flag and return
///                     the error status
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_unCodShortGND                                                 = 134u;
/// \input  RSens_unCodShortBAT                                                 = 5100u;
/// \input  RSens_unCodOpenLoad                                                 = 4773u;
/// \input  Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Gnd   = TRUE;
/// \input  Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Vbat  = TRUE;
/// \input  Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boOpenload = TRUE;
/// \input  Rsens_CheckErrorBinning_Param1 = asTestCaseData[ucIdx].ucVoltage
/// \input  Rsens_CheckErrorBinning_Param2 = asTestCaseData[ucIdx].ucBinningIdx
/// \input  Rsens_CheckErrorBinning_Param3 = asTestCaseData[ucIdx].ucCodBinIdx
///
///   - Expectations:
///
/// \output Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Vbat  = asTestCaseData[ucIdx].boSh2Vbat
/// \output Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boOpenload = asTestCaseData[ucIdx].boOpenload
/// \output Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Gnd   = asTestCaseData[ucIdx].boSh2Gnd
/// \output Rsens_CheckErrorBinning_RetVal                                      = asTestCaseData[ucIdx].ucRetVal
///
//-----------------------------------------------------------------------------
void Mt_Rsens_CheckErrorBinning(void)
{
  //Step 1) Set pre - conditions
  RSens_unCodShortGND = 134u;
  RSens_unCodShortBAT = 5100u;
  RSens_unCodOpenLoad = 4773u;

  Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Gnd = TRUE;
  Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Vbat = TRUE;
  Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boOpenload = TRUE;

  struct { uint16  ucVoltage;  uint8 ucBinningIdx; uint8 ucCodBinIdx; boolean boSh2Vbat;  boolean boOpenload;  boolean boSh2Gnd;    uint8 ucRetVal
  } asTestCaseData[]
    = { {             130u,              1u,                 16u,             FALSE,               FALSE,              TRUE,               0u,         },
        {            5200u,              2u,                 13u,             TRUE,                FALSE,              FALSE,              0u,         },
        {            4800u,              3u,                 21u,             FALSE,               TRUE,               FALSE,              0u,         },
        {           65535u,              4u,                 5u,              FALSE,               FALSE,              FALSE,              0u,         },
        {            4500u,              5u,                 7u,              FALSE,               FALSE,              FALSE,              4u,         },
        {            4900u,              5u,                 5u,              FALSE,               TRUE,               FALSE,              0u,         },
    };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
    {
      //Step 2) Assign all input values to the corresponding input variables identified in the FUT
      Rsens_CheckErrorBinning_Param1 = asTestCaseData[ucIdx].ucVoltage;
      Rsens_CheckErrorBinning_Param2 = asTestCaseData[ucIdx].ucBinningIdx;
      Rsens_CheckErrorBinning_Param3 = asTestCaseData[ucIdx].ucCodBinIdx;

      //Step 3) Call the FUT
      Rsens_CheckErrorBinning_RetVal = Rsens_CheckErrorBinning(Rsens_CheckErrorBinning_Param1, Rsens_CheckErrorBinning_Param2, Rsens_CheckErrorBinning_Param3);

      //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
      AL_UNITTEST_CHECK(Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Vbat,   asTestCaseData[ucIdx].boSh2Vbat,  == );
      AL_UNITTEST_CHECK(Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boOpenload,  asTestCaseData[ucIdx].boOpenload, == );
      AL_UNITTEST_CHECK(Rsens_asRCODBin_ErrState[Rsens_CheckErrorBinning_Param2].boSh2Gnd,    asTestCaseData[ucIdx].boSh2Gnd,   == );
      AL_UNITTEST_CHECK(Rsens_CheckErrorBinning_RetVal, asTestCaseData[ucIdx].ucRetVal, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_GetTemperature
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates the correct value of
///                       the temperature
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rsens_GetTemperature_Param1 = 6
/// \input  Rsens_GetTemperature_Param2 = 5
/// \input  Rsens_GetTemperature_Param3 = 10
/// \input  Rsens_GetTemperature_Param4 = 15
/// \input  Rsens_GetTemperature_Param5 = 25
///
///   - Expectations:
///
/// \output Rsens_GetTemperature_RetVal = 17
///
//-----------------------------------------------------------------------------
void Mt_Rsens_GetTemperature(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rsens_GetTemperature_Param1 = 6;
  Rsens_GetTemperature_Param2 = 5;
  Rsens_GetTemperature_Param3 = 10;
  Rsens_GetTemperature_Param4 = 15;
  Rsens_GetTemperature_Param5 = 25;
  //Step 3) Call the FUT
  Rsens_GetTemperature_RetVal = Rsens_GetTemperature(Rsens_GetTemperature_Param1, Rsens_GetTemperature_Param2, Rsens_GetTemperature_Param3, Rsens_GetTemperature_Param4, Rsens_GetTemperature_Param5);
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rsens_GetTemperature_RetVal, 17, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CheckVoltageRange
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the voltage range to set 
///                     the corresponding error flag for DTC setting/desetting
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_unCodShortGND                                                = 134u;
/// \input  RSens_unCodShortBAT                                                = 5100u;
/// \input  RSens_unCodOpenLoad                                                = 4773u;
/// \input  Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boSh2Vbat  = TRUE;
/// \input  Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boOpenload = TRUE;
/// \input  Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boSh2Gnd   = TRUE;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CheckVoltageRange_Param2]   = SIG_VALID;
/// \input  RSens_CheckVoltageRange_Param1                                     = asTestCaseData[ucIdx].ucVoltage;
/// \input  RSens_CheckVoltageRange_Param2                                     = asTestCaseData[ucIdx].ucZoneID;
///
///   - Expectations:
///
/// \output 
///
//-----------------------------------------------------------------------------
void Mt_RSens_CheckVoltageRange(void)
{
  //Step 1) Set pre - conditions
  RSens_unCodShortGND = 134u;
  RSens_unCodShortBAT = 5100u;
  RSens_unCodOpenLoad = 4773u;

  Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boSh2Vbat = TRUE;
  Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boOpenload = TRUE;
  Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boSh2Gnd = TRUE;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CheckVoltageRange_Param2] = SIG_VALID;

  struct { uint16  ucVoltage;  uint8 ucZoneID;  boolean boSh2Vbat;  boolean boOpenload;  boolean boSh2Gnd;    teRte_SigQty eSigQty      } asTestCaseData[]
     =  { {             130u,              1u,              FALSE,               FALSE,              TRUE,             SIG_INVALID,       },
          {            5200u,              2u,               TRUE,               FALSE,             FALSE,             SIG_INVALID,       },
          {            4800u,              3u,              FALSE,                TRUE,             FALSE,             SIG_INVALID,       },
          {            4500u,              4u,              FALSE,               FALSE,             FALSE,             SIG_VALID,         },
        };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    RSens_CheckVoltageRange_Param1 = asTestCaseData[ucIdx].ucVoltage;
    RSens_CheckVoltageRange_Param2 = asTestCaseData[ucIdx].ucZoneID;
    //Step 3) Call the FUT
    RSens_CheckVoltageRange(RSens_CheckVoltageRange_Param1, RSens_CheckVoltageRange_Param2);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boSh2Vbat, asTestCaseData[ucIdx].boSh2Vbat, == );
    AL_UNITTEST_CHECK(Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boOpenload, asTestCaseData[ucIdx].boOpenload, == );
    AL_UNITTEST_CHECK(Rsens_asNtcThz_ErrState[RSens_CheckVoltageRange_Param2].boSh2Gnd, asTestCaseData[ucIdx].boSh2Gnd, == );
    AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CheckVoltageRange_Param2], asTestCaseData[ucIdx].eSigQty, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Pcb_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates correctly the
///                     temperature of the PCB
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_unPCBShortGND             = 180u;
/// \input  RSens_unPCBOpenLoad             = 4977u;
/// \input  Rte_Read_IoHwAb_GetPCB_Param1   = asTestCaseData[ucIdx].ucVoltage;
/// \input  RSens_Rte_Read_PCBNTC_Param1    = &Rte_Read_IoHwAb_GetPCB_Param1;
///
///   - Expectations:
///
/// \output Rsens_asPCB_ErrState.boSh2Vbat  = asTestCaseData[ucIdx].boSh2Vbat
/// \output Rsens_asPCB_ErrState.boOpenload = asTestCaseData[ucIdx].boOpenload
/// \output Rsens_asPCB_ErrState.boSh2Gnd   = asTestCaseData[ucIdx].boSh2Gnd
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Pcb_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  RSens_unPCBShortGND = 180u;
  RSens_unPCBOpenLoad = 4977u;

  struct {tiu16Voltage_mV  ucVoltage;   boolean boSh2Vbat;  boolean boOpenload;  boolean boSh2Gnd;    teRSens_SigQty eSigQty} asTestCaseData[]
      = { {             130u,              FALSE,               FALSE,              TRUE,      eRSENS_SIG_INVALID,        },
          {            6000u,              FALSE,                TRUE,             FALSE,      eRSENS_SIG_INVALID,        },
          {            4800u,              FALSE,               FALSE,             FALSE,        eRSENS_SIG_VALID,        },
        };

    for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucIdx++)
    {
      //Step 2) Assign all input values to the corresponding input variables identified in the FUT
      Rte_Read_IoHwAb_GetPCB_Param1 = asTestCaseData[ucIdx].ucVoltage;
      RSens_Rte_Read_PCBNTC_Param1 = &Rte_Read_IoHwAb_GetPCB_Param1;
      
      //Step 3) Call the FUT
      RSens_CalculateTemp_Pcb();

      //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
      AL_UNITTEST_CHECK(Rsens_asPCB_ErrState.boSh2Vbat, asTestCaseData[ucIdx].boSh2Vbat, == );
      AL_UNITTEST_CHECK(Rsens_asPCB_ErrState.boOpenload, asTestCaseData[ucIdx].boOpenload, == );
      AL_UNITTEST_CHECK(Rsens_asPCB_ErrState.boSh2Gnd, asTestCaseData[ucIdx].boSh2Gnd, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Pcb_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates correctly the
///                     temperature of the PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_GetPCB_Param1     = 4500u;
/// \input  RSens_Rte_Read_PCBNTC_Param1      = &Rte_Read_IoHwAb_GetPCB_Param1;
/// \input  UtilMath_LinearInterpolate_RetVal = -500;
///
///   - Expectations:
///
/// \output sPCBTemperatureVal.nVal           = -400
/// \output sPCBTemperatureVal.eQty           = SIG_VALID
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Pcb_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  RSens_unPCBShortGND               = 180u;
  RSens_unPCBOpenLoad               = 4977u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_IoHwAb_GetPCB_Param1     = 4500u;
  RSens_Rte_Read_PCBNTC_Param1      = &Rte_Read_IoHwAb_GetPCB_Param1;
  UtilMath_LinearInterpolate_RetVal = -500;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Pcb();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(sPCBTemperatureVal.nVal, -400, == );
  AL_UNITTEST_CHECK(sPCBTemperatureVal.eQty, SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Pcb_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates correctly the
///                     temperature of the PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_GetPCB_Param1     = 4500u
/// \input  RSens_Rte_Read_PCBNTC_Param1      = &Rte_Read_IoHwAb_GetPCB_Param1
/// \input  UtilMath_LinearInterpolate_RetVal = 1600
///
///   - Expectations:
///
/// \output sPCBTemperatureVal.nVal          = 1500
/// \output sPCBTemperatureVal.eQty          = SIG_VALID
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Pcb_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  RSens_unPCBShortGND               = 180u;
  RSens_unPCBOpenLoad               = 4977u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_IoHwAb_GetPCB_Param1     = 4500u;
  RSens_Rte_Read_PCBNTC_Param1      = &Rte_Read_IoHwAb_GetPCB_Param1;
  UtilMath_LinearInterpolate_RetVal = 1600;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Pcb();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(sPCBTemperatureVal.nVal, 1500, == );
  AL_UNITTEST_CHECK(sPCBTemperatureVal.eQty, SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Pcb
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates correctly the
///                     temperature of the PCB
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Pcb(void)
{
  Mt_RSens_CalculateTemp_Pcb_TestCase_1();
  Mt_RSens_CalculateTemp_Pcb_TestCase_2();
  Mt_RSens_CalculateTemp_Pcb_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_GetInterpolationNTCInputs_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates and interpolates correctly the
///                     temperature of the NTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rsens_GetInterpolationNTCInputs_Param1 = 5000u;
/// \input  Rsens_GetInterpolationNTCInputs_Param2 = &pasTestTable;
/// \input  Rsens_GetInterpolationNTCInputs_Param3 = TRUE;
///
///   - Expectations:
///
/// \output RSens_sInterpPoints.snTemp0    =-40
/// \output RSens_sInterpPoints.snVoltage0 = 5000
/// \output RSens_sInterpPoints.snTemp1    = -40
/// \output RSens_sInterpPoints.snVoltage1 = 3857
///
//-----------------------------------------------------------------------------
void Mt_Rsens_GetInterpolationNTCInputs_TestCase_1(void)
{

  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  NtcTables pasTestTable = 
  {
{-40, 3857, 3744},
{  0, 3470, 3296},
{ 25, 2872, 2792},
{ 60, 1782, 1550},
{ 80, 1252, 1060},
{100,  860,  714},
{120,  590,  484},
{150,  344,  279}
  };
  Rsens_GetInterpolationNTCInputs_Param1 = 5000u;
  Rsens_GetInterpolationNTCInputs_Param2 = &pasTestTable;
  Rsens_GetInterpolationNTCInputs_Param3 = TRUE;

  //Step 3) Call the FUT
  Rsens_GetInterpolationNTCInputs(Rsens_GetInterpolationNTCInputs_Param1, Rsens_GetInterpolationNTCInputs_Param2, Rsens_GetInterpolationNTCInputs_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snTemp0, -40, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snVoltage0, 5000, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snTemp1, -40, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snVoltage1, 3857, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_GetInterpolationNTCInputs_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates and interpolates correctly the
///                     temperature of the NTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rsens_GetInterpolationNTCInputs_Param1 = 1000u;
/// \input  Rsens_GetInterpolationNTCInputs_Param2 = &pasTestTable;
/// \input  Rsens_GetInterpolationNTCInputs_Param3 = FALSE;
///
///   - Expectations:
///
/// \output RSens_sInterpPoints.snTemp0    = 80
/// \output RSens_sInterpPoints.snVoltage0 = 1060
/// \output RSens_sInterpPoints.snTemp1    = 100
/// \output RSens_sInterpPoints.snVoltage1 = 714
///
//-----------------------------------------------------------------------------
void Mt_Rsens_GetInterpolationNTCInputs_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  NtcTables pasTestTable =
  {
{-40, 3857, 3744},
{  0, 3470, 3296},
{ 25, 2872, 2792},
{ 60, 1782, 1550},
{ 80, 1252, 1060},
{100,  860,  714},
{120,  590,  484},
{150,  344,  279}
  };
  Rsens_GetInterpolationNTCInputs_Param1 = 1000u;
  Rsens_GetInterpolationNTCInputs_Param2 = &pasTestTable;
  Rsens_GetInterpolationNTCInputs_Param3 = FALSE;

  //Step 3) Call the FUT
  Rsens_GetInterpolationNTCInputs(Rsens_GetInterpolationNTCInputs_Param1, Rsens_GetInterpolationNTCInputs_Param2, Rsens_GetInterpolationNTCInputs_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snTemp0, 80, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snVoltage0, 1060, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snTemp1, 100, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snVoltage1, 714, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_GetInterpolationNTCInputs_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates and interpolates correctly the
///                     temperature of the NTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input Rsens_GetInterpolationNTCInputs_Param1 = 100u;
/// \input Rsens_GetInterpolationNTCInputs_Param2 = &pasTestTable;
/// \input Rsens_GetInterpolationNTCInputs_Param3 = TRUE;
///
///   - Expectations:
///
/// \output RSens_sInterpPoints.snTemp0    = (*(Rsens_GetInterpolationNTCInputs_Param2))[RSENS_NUM_NTC_TEMP_PROFILE - 1u][0u]
/// \output RSens_sInterpPoints.snTemp1    = 150
/// \ouput  RSens_sInterpPoints.snVoltage0 = 344
/// \output RSens_sInterpPoints.snVoltage1 = 0
///
//-----------------------------------------------------------------------------
void Mt_Rsens_GetInterpolationNTCInputs_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  NtcTables pasTestTable =
  {
  {-40, 3857, 3744},
  {  0, 3470, 3296},
  { 25, 2872, 2792},
  { 60, 1782, 1550},
  { 80, 1252, 1060},
  {100,  860,  714},
  {120,  590,  484},
  {150,  344,  279}
  };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rsens_GetInterpolationNTCInputs_Param1 = 100u;
  Rsens_GetInterpolationNTCInputs_Param2 = &pasTestTable;
  Rsens_GetInterpolationNTCInputs_Param3 = TRUE;

  //Step 3) Call the FUT
  Rsens_GetInterpolationNTCInputs(Rsens_GetInterpolationNTCInputs_Param1, Rsens_GetInterpolationNTCInputs_Param2, Rsens_GetInterpolationNTCInputs_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snTemp0, (*(Rsens_GetInterpolationNTCInputs_Param2))[RSENS_NUM_NTC_TEMP_PROFILE - 1u][0u], == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snVoltage0, 344u, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snTemp1, 150u, == );
  AL_UNITTEST_CHECK(RSens_sInterpPoints.snVoltage1, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_GetInterpolationNTCInputs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Rsens_GetInterpolationNTCInputs(void)
{
  Mt_Rsens_GetInterpolationNTCInputs_TestCase_1();
  Mt_Rsens_GetInterpolationNTCInputs_TestCase_2();
  Mt_Rsens_GetInterpolationNTCInputs_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingNtcs_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to ground DTC for NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount = 0u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 1u
/// \output Dem_SetEventStatus_Param1   = NTCs_SC_GND
/// \output Dem_SetEventStatus_Param2   = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingNtcs_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asNtcThz_ErrState[ucIdx].boSh2Gnd = TRUE;
  }
  
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_Sh2GndHandlingNtcs();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTCs_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingNtcs_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to ground DTC for NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount             = 0u
/// \input  Rsens_asNtcThz_ErrState[ucIdx].boSh2Gnd = FALSE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount             = 1u
/// \output Dem_SetEventStatus_Param1               = NTCs_SC_GND
/// \output Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingNtcs_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asNtcThz_ErrState[ucIdx].boSh2Gnd = FALSE;
  }
  //Step 3) Call the FUT
  RSens_Sh2GndHandlingNtcs();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTCs_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingNtcs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingNtcs(void)
{
  Mt_RSens_Sh2GndHandlingNtcs_TestCase_1();
  Mt_RSens_Sh2GndHandlingNtcs_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingNtcs_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to voltage  battery DTC for NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount = 0u;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 1u
/// \output Dem_SetEventStatus_Param1   = NTCs_SC_BAT
/// \output Dem_SetEventStatus_Param2   = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingNtcs_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asNtcThz_ErrState[ucIdx].boSh2Vbat = TRUE;
  }
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_Sh2VbatHandlingNtcs();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTCs_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingNtcs_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to voltage  battery DTC for NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount              = 0u
/// \input  Rsens_asNtcThz_ErrState[ucIdx].boSh2Vbat = FALSE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount              = 1u
/// \output Dem_SetEventStatus_Param1                = NTCs_SC_BAT
/// \output Dem_SetEventStatus_Param2                = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingNtcs_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asNtcThz_ErrState[ucIdx].boSh2Vbat = FALSE;
  }
  //Step 3) Call the FUT
  RSens_Sh2VbatHandlingNtcs();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTCs_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingNtcs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingNtcs(void)
{
  Mt_RSens_Sh2VbatHandlingNtcs_TestCase_1();
  Mt_RSens_Sh2VbatHandlingNtcs_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenloadHandlingNtcs_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the open load DTC for NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount = 0u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 1u
/// \output Dem_SetEventStatus_Param1   = NTCs_OL
/// \output Dem_SetEventStatus_Param2   = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenloadHandlingNtcs_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asNtcThz_ErrState[ucIdx].boOpenload = TRUE;
  }
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_OpenloadHandlingNtcs();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTCs_OL, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenloadHandlingNtcs_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the open load DTC for NTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount               = 0u;
/// \input  Dsens_asNtcThz_ErrState[ucIdx].boOpenload = FALSE;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount               = 1u
/// \output Dem_SetEventStatus_Param1                 = NTCs_OL
/// \output Dem_SetEventStatus_Param2                 = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenloadHandlingNtcs_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asNtcThz_ErrState[ucIdx].boOpenload = FALSE;
  }

  //Step 3) Call the FUT
  RSens_OpenloadHandlingNtcs();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTCs_OL, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenloadHandlingNtcs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenloadHandlingNtcs(void)
{
  Mt_RSens_OpenloadHandlingNtcs_TestCase_1();
  Mt_RSens_OpenloadHandlingNtcs_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingPCB_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to ground DTC for PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Sh2GndHandlingPCB_Param1 = TRUE;
/// \input  Dem_SetEventStatus_HitCount    = 0u;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount    = 1u
/// \output Dem_SetEventStatus_Param1      = NTC_PCB_E_SC_GND
/// \output Dem_SetEventStatus_Param2      = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingPCB_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Sh2GndHandlingPCB_Param1 = TRUE;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_Sh2GndHandlingPCB(RSens_Sh2GndHandlingPCB_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingPCB_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to ground DTC for PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Sh2GndHandlingPCB_Param1 = FALSE
/// \input  Dem_SetEventStatus_HitCount    = 0u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount    = 1u
/// \output Dem_SetEventStatus_Param1      = NTC_PCB_E_SC_GND
/// \output Dem_SetEventStatus_Param2      = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingPCB_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Sh2GndHandlingPCB_Param1 = FALSE;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_Sh2GndHandlingPCB(RSens_Sh2GndHandlingPCB_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingPCB_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the short to ground DTC for PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Sh2GndHandlingPCB_Param1 = 3u;
/// \input  Dem_SetEventStatus_HitCount    = 0u;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount    = 1u
/// \output Dem_SetEventStatus_Param1      = NTC_PCB_E_SC_GND
/// \output Dem_SetEventStatus_Param2      = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingPCB_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Sh2GndHandlingPCB_Param1 = 3u;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_Sh2GndHandlingPCB(RSens_Sh2GndHandlingPCB_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingPCB
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingPCB(void)
{
  Mt_RSens_Sh2GndHandlingPCB_TestCase_1();
  Mt_RSens_Sh2GndHandlingPCB_TestCase_2();
  Mt_RSens_Sh2GndHandlingPCB_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenLoadHandlingPCB_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the open load DTC for PCB
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  RSens_OpenLoadHandlingPCB_Param1 = TRUE
/// \input  Dem_SetEventStatus_HitCount      = 0u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount      = 1u
/// \output Dem_SetEventStatus_Param1        = NTC_PCB_E_OPENLOAD
/// \output Dem_SetEventStatus_Param2        = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenLoadHandlingPCB_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_OpenLoadHandlingPCB_Param1 = TRUE;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_OpenLoadHandlingPCB(RSens_OpenLoadHandlingPCB_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_OPENLOAD, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenLoadHandlingPCB_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the open load DTC for PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_OpenLoadHandlingPCB_Param1 = FALSE
/// \input  Dem_SetEventStatus_HitCount      = 0u
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount      = 1u
/// \output Dem_SetEventStatus_Param1        = NTC_PCB_E_OPENLOAD
/// \output Dem_SetEventStatus_Param2        = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenLoadHandlingPCB_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_OpenLoadHandlingPCB_Param1 = FALSE;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_OpenLoadHandlingPCB(RSens_OpenLoadHandlingPCB_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_OPENLOAD, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenLoadHandlingPCB_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function is handlng correctly 
///                     the open load DTC for PCB
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_OpenLoadHandlingPCB_Param1 = 3u;
/// \input  Dem_SetEventStatus_HitCount      = 0u;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount      = 1u
/// \output Dem_SetEventStatus_Param1        = NTC_PCB_E_OPENLOAD
/// \output Dem_SetEventStatus_Param2        = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenLoadHandlingPCB_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_OpenLoadHandlingPCB_Param1 = 3u;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_OpenLoadHandlingPCB(RSens_OpenLoadHandlingPCB_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_OPENLOAD, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenLoadHandlingPCB
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenLoadHandlingPCB(void)
{
  Mt_RSens_OpenLoadHandlingPCB_TestCase_1();
  Mt_RSens_OpenLoadHandlingPCB_TestCase_2();
  Mt_RSens_OpenLoadHandlingPCB_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CheckErrFlagsPCB
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the PCB and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount     = 0u;
/// \input  Rsens_asPCB_ErrState.boSh2Gnd   = TRUE;
/// \input  Rsens_asPCB_ErrState.boOpenload = FALSE;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount     = 2u
/// \output Dem_SetEventStatus_Param1       = NTC_PCB_E_OPENLOAD
/// \output Dem_SetEventStatus_Param2       = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_CheckErrFlagsPCB(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  Rsens_asPCB_ErrState.boSh2Gnd = TRUE;
  Rsens_asPCB_ErrState.boOpenload = FALSE;

  //Step 3) Call the FUT
  RSens_CheckErrFlagsPCB();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_OPENLOAD, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CheckErrFlagsNtc_Thzs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the NTC and set/deset the corresponding DTC
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input ucIdx = asTestCaseData[ucI].ucId;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = asTestCaseData[ucI].ucDemParam
///
//-----------------------------------------------------------------------------
void Mt_RSens_CheckErrFlagsNtc_Thzs(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_Param1 = 0u;
  struct { uint8   ucId;  uint16 ucDemParam } asTestCaseData[]
    = { {          6u,                 0u, },
        {          1u,        NTCs_SC_GND, },
        {          3u,        NTCs_SC_BAT, },
        {          5u,            NTCs_OL, },
  };

  for (uint8 ucI = 0u; ucI < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucI++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    ucIdx = asTestCaseData[ucI].ucId;
    //Step 3) Call the FUT
    RSens_CheckErrFlagsNtc_Thzs();
    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucI].ucDemParam, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenloadHandlingRCODBin_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount                = 0u
/// \input  Rsens_asRCODBin_ErrState[ucIdx].boOpenload = FALSE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                = 1u
/// \output Dem_SetEventStatus_Param1                  = RCODs_OL
/// \output Dem_SetEventStatus_Param2                  = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenloadHandlingRCODBin_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asRCODBin_ErrState[ucIdx].boOpenload = FALSE;
  }

  //Step 3) Call the FUT
  RSens_OpenloadHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_OL, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenloadHandlingRCODBin_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount            = 0u
/// \input  Rsens_asRCODBin_ErrState[1].boOpenload = TRUE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount            = 1u
/// \output Dem_SetEventStatus_Param1              = RCODs_OL
/// \output Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenloadHandlingRCODBin_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  Rsens_asRCODBin_ErrState[1].boOpenload = TRUE;

  //Step 3) Call the FUT
  RSens_OpenloadHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_OL, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_OpenloadHandlingRCODBin
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_OpenloadHandlingRCODBin(void)
{
  Mt_RSens_OpenloadHandlingRCODBin_TestCase_1();
  Mt_RSens_OpenloadHandlingRCODBin_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount = 0u;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 1u
/// \output Dem_SetEventStatus_Param1   = RCODs_SC_BAT
/// \output Dem_SetEventStatus_Param2   = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call the FUT
  RSens_Sh2VbatHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_HitCount               = 0u
/// \input Rsens_asRCODBin_ErrState[ucIdx].boSh2Vbat = FALSE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount              = 1u
/// \output Dem_SetEventStatus_Param1                = RCODs_SC_BAT
/// \output Dem_SetEventStatus_Param2                = DEM_EVENT_STATUS_PREPASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asRCODBin_ErrState[ucIdx].boSh2Vbat = FALSE;
  }

  //Step 3) Call the FUT
  RSens_Sh2VbatHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PREPASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_HitCount               = 0u
/// \input Rsens_asRCODBin_ErrState[ucIdx].boSh2Vbat = FALSE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount              = 1u
/// \output Dem_SetEventStatus_Param1                = RCODs_SC_BAT
/// \output Dem_SetEventStatus_Param2                = DEM_EVENT_STATUS_PREFAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rsens_asRCODBin_ErrState[ucIdx].boSh2Vbat = FALSE;
  }

  //Step 3) Call the FUT
  RSens_Sh2VbatHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PREFAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2VbatHandlingRCODBin
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2VbatHandlingRCODBin(void)
{
  Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_1();
  Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_2();
  //Mt_RSens_Sh2VbatHandlingRCODBin_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingRCODBin_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount              = 0u
/// \input  Rsens_asRCODBin_ErrState[0...3].boSh2Gnd = FALSE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount              = 1u
/// \output Dem_SetEventStatus_Param1                = RCODs_SC_GND
/// \output Dem_SetEventStatus_Param2                = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingRCODBin_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  for (uint8 ucIdx = 0; ucIdx < 4; ucIdx++)
  {
    Rsens_asRCODBin_ErrState[ucIdx].boSh2Gnd = FALSE;
  }

  //Step 3) Call the FUT
  RSens_Sh2GndHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingRCODBin_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Dem_SetEventStatus_HitCount          = 0u
/// \input  Rsens_asRCODBin_ErrState[1].boSh2Gnd = TRUE
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount          = 1u
/// \output Dem_SetEventStatus_Param1            = RCODs_SC_GND
/// \output Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingRCODBin_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Dem_SetEventStatus_HitCount = 0u;
  Rsens_asRCODBin_ErrState[1].boSh2Gnd = TRUE;

  //Step 3) Call the FUT
  RSens_Sh2GndHandlingRCODBin();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, RCODs_SC_GND, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Sh2GndHandlingRCODBin
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Sh2GndHandlingRCODBin(void)
{
  Mt_RSens_Sh2GndHandlingRCODBin_TestCase_1();
  Mt_RSens_Sh2GndHandlingRCODBin_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CheckErrFlagsRCODs_LedDrvs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify the error flag for short
///                    to ground for the RCODBin and set/deset the corresponding DTC
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1 = 0u;
/// \input ucIdx = [0..6];
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = asTestCaseData[ucI].ucDemParam
///
//-----------------------------------------------------------------------------
void Mt_RSens_CheckErrFlagsRCODs_LedDrvs(void)
{
  //Step 1) Set pre - conditions
  Dem_SetEventStatus_Param1 = 0u;
   struct {uint8   ucId;  uint16 ucDemParam} asTestCaseData[]
    = { {          6u,                 0u, },
        {          0u,       RCODs_SC_GND, },
        {          2u,       RCODs_SC_BAT, },
        {          4u,           RCODs_OL, },
    };

    for (uint8 ucI = 0u; ucI < sizeof(asTestCaseData) / sizeof(asTestCaseData[0]); ucI++)
    {
      //Step 2) Assign all input values to the corresponding input variables identified in the FUT
      ucIdx = asTestCaseData[ucI].ucId;
      //Step 3) Call the FUT
       RSens_CheckErrFlagsRCODs_LedDrvs();
      //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
      AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, asTestCaseData[ucI].ucDemParam, == );
    }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalcInterpolationTemperatures_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if parallel resistor exists
///                     and then calculates the temperatures based on interpolation
///                     between voltage and the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_boResistor_Para_Test = TRUE;
/// \input  RSens_CalcInterpolationTemperatures_Param1 = 1u;
/// \input  RSens_CalcInterpolationTemperatures_Param2 = 500u;
/// \input  RSens_CalcInterpolationTemperatures_Param3 = &pasTestTable;
///
///   - Expectations:
///
/// \output  RSens_CalcInterpolationTemperatures_RetVal = 1309
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalcInterpolationTemperatures_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  NtcTables pasTestTable =
  {
  {-40, 3857, 3744},
  {  0, 3470, 3296},
  { 25, 2872, 2792},
  { 60, 1782, 1550},
  { 80, 1252, 1060},
  {100,  860,  714},
  {120,  590,  484},
  {150,  344,  279}
  };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boResistor_Para_Test = TRUE;
  RSens_CalcInterpolationTemperatures_Param1 = 1u;
  RSens_CalcInterpolationTemperatures_Param2 = 500u;
  RSens_CalcInterpolationTemperatures_Param3 = &pasTestTable;

  //Step 3) Call the FUT
  RSens_CalcInterpolationTemperatures_RetVal = RSens_CalcInterpolationTemperatures(RSens_CalcInterpolationTemperatures_Param1, RSens_CalcInterpolationTemperatures_Param2, RSens_CalcInterpolationTemperatures_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_CalcInterpolationTemperatures_RetVal, 1309, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalcInterpolationTemperatures_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if parallel resistor exists
///                     and then calculates the temperatures based on interpolation
///                     between voltage and the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_boResistor_Para_Test = FALSE
/// \input  RSens_CalcInterpolationTemperatures_Param1 = 1u
/// \input  RSens_CalcInterpolationTemperatures_Param2 = 500u
/// \input  RSens_CalcInterpolationTemperatures_Param3 = &pasTestTable
///
///   - Expectations:
///
/// \output RSens_CalcInterpolationTemperatures_RetVal = 1186
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalcInterpolationTemperatures_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  NtcTables pasTestTable =
  {
  {-40, 3857, 3744},
  {  0, 3470, 3296},
  { 25, 2872, 2792},
  { 60, 1782, 1550},
  { 80, 1252, 1060},
  {100,  860,  714},
  {120,  590,  484},
  {150,  344,  279}
  };

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boResistor_Para_Test = FALSE;
  RSens_CalcInterpolationTemperatures_Param1 = 2u;
  RSens_CalcInterpolationTemperatures_Param2 = 500u;
  RSens_CalcInterpolationTemperatures_Param3 = &pasTestTable;

  //Step 3) Call the FUT
  RSens_CalcInterpolationTemperatures_RetVal = RSens_CalcInterpolationTemperatures(RSens_CalcInterpolationTemperatures_Param1, RSens_CalcInterpolationTemperatures_Param2, RSens_CalcInterpolationTemperatures_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_CalcInterpolationTemperatures_RetVal, 1186, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalcInterpolationTemperatures
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify if parallel resistor exists
///                     and then calculates the temperatures based on interpolation
///                     between voltage and the temperatures
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalcInterpolationTemperatures(void)
{
  Mt_RSens_CalcInterpolationTemperatures_TestCase_1();
  Mt_RSens_CalcInterpolationTemperatures_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                  = 10u
/// \input  RSens_Calculate_Binning_Param2                  = TRUE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV11]        = 14u
/// \input  Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount        = 0u
/// \input  Rsens_Binning_Thresholds_Lmm[ucBinningClassIdx] = 0u
/// \input  Rsens_Binning_Thresholds[ucBinningClassIdx]     = 0u
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = TRUE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 14u;
  Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount = 0u;

  for (uint8 ucBinningClassIdx = 0u; ucBinningClassIdx < CFG_BIN_CLASS_CNT; ucBinningClassIdx++)
  {
    Rsens_Binning_Thresholds_Lmm[ucBinningClassIdx] = 0u;
    Rsens_Binning_Thresholds[ucBinningClassIdx] = 0u;
  }
  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetVoltage_NTCs_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                          = 1u;
/// \input  RSens_Calculate_Binning_Param2                          = TRUE;
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                = 15u;
///
///   - Expectations:
///
/// \output RSens_aucBinClassesArry[RSens_Calculate_Binning_Param1] = 15u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = TRUE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 15u;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_aucBinClassesArry[RSens_Calculate_Binning_Param1], 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                  = 1u;
/// \input  RSens_Calculate_Binning_Param2                  = FALSE;
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]        = 16u;
/// \input  Rsens_Binning_Thresholds_Lmm[ucBinningClassIdx] = 1000u;
/// \input  Rsens_Binning_Thresholds[ucBinningClassIdx]     = 1000u;
///
///   - Expectations:
///
/// \output  boLMMBinUpdateStatus[RSens_Calculate_Binning_Param1] = FALSE
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 16u;
  for (uint8 ucBinningClassIdx = 0u; ucBinningClassIdx < CFG_BIN_CLASS_CNT; ucBinningClassIdx++)
  {
    Rsens_Binning_Thresholds_Lmm[ucBinningClassIdx] = 1000u;
    Rsens_Binning_Thresholds[ucBinningClassIdx] = 1000u;
  }

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boLMMBinUpdateStatus[RSens_Calculate_Binning_Param1], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                                                                         = 1u
/// \input  RSens_Calculate_Binning_Param2                                                                         = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                                                               = 16u
/// \input  asLmmAdc[RSens_aucBinClassesArry[RSens_Calculate_Binning_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_VALID
/// \input  asLmmAdc[15 - RSENS_LMM_CODING_OFFSET].ucADC2Value = 850u;
/// \input  asEepromBinning[1].eSigQty = SIG_VALID;
///
///   - Expectations:
///
/// \output boLMMBinUpdateStatus[RSens_Calculate_Binning_Param1] = TRUE
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 16u;
  asLmmAdc[RSens_aucBinClassesArry[RSens_Calculate_Binning_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_VALID;
  asLmmAdc[15 - RSENS_LMM_CODING_OFFSET].ucADC2Value = 850u;
  asEepromBinning[1].eSigQty = SIG_VALID;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boLMMBinUpdateStatus[RSens_Calculate_Binning_Param1], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                                 = 1u
/// \input  RSens_Calculate_Binning_Param2                                 = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                       = 22u
/// \input  boLMMBinUpdateStatus[RSENS_LED_DRV02]                          = FALSE
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                = 0u
/// \input  asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning      = 8u
/// \input  asEepromBinning[RSens_Calculate_Binning_Param1].eSigQty        = SIG_INVALID
///
///   - Expectations:
///
/// \output asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning = 8u
/// \output Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount -         = 1u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02]  = 22u;
  boLMMBinUpdateStatus[RSENS_LED_DRV02]     = FALSE;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount = 0u;
  asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning = 8u;
  asEepromBinning[RSens_Calculate_Binning_Param1].eSigQty = SIG_INVALID;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning, 8u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                                         = 1u
/// \input  RSens_Calculate_Binning_Param2                                         = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                               = 22u
/// \input  boLMMBinUpdateStatus[RSENS_LED_DRV02]                                  = FALSE
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                        = 0u
/// \input  asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning              = 5u
/// \input  asEepromBinning[RSens_Calculate_Binning_Param1].eSigQty                = SIG_VALID
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFaul     = FALSE
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault  = FALSE
///
///   - Expectations:
///
/// \output Rsens_CheckErrorBinning_RetVal                                      = 0u
/// \output Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02]  = 22u;
  boLMMBinUpdateStatus[RSENS_LED_DRV02]     = FALSE;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount = 0u;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault = FALSE;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault = FALSE;
  asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning = 5u;
  asEepromBinning[RSens_Calculate_Binning_Param1].eSigQty = SIG_VALID;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rsens_CheckErrorBinning_RetVal, 0u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1                                        = 1u
/// \input  RSens_Calculate_Binning_Param2                                        = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                              = 22u
/// \input  boLMMBinUpdateStatus[RSENS_LED_DRV02]                                 = FALSE
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                       = 0u
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault   = TRUE
///
///   - Expectations:
///
/// \output Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault = FALSE
/// \output Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                       = 1u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 22u;
  boLMMBinUpdateStatus[RSENS_LED_DRV02]    = FALSE;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount = 0u;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault = TRUE;
 
  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1           = 2u;
/// \input  RSens_Calculate_Binning_Param2           = FALSE;
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 14u;
///
///   - Expectations:
///
/// \output boLMMBinUpdateStatus[2]                  = FALSE;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 2u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV03] = 14u;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(boLMMBinUpdateStatus[2], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_Calculate_Binning_Param1           = 2u
/// \input  RSens_Calculate_Binning_Param2           = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 15u
///
///   - Expectations:
///
/// \output Rsens_asRCODBin_ErrState[2].boSh2Gnd   = FALSE
/// \output Rsens_asRCODBin_ErrState[2].boSh2Vbat  = FALSE
/// \output Rsens_asRCODBin_ErrState[2].boOpenload = FALSE
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 2u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV03] = 15u;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rsens_asRCODBin_ErrState[2].boSh2Gnd, FALSE, == );
  AL_UNITTEST_CHECK(Rsens_asRCODBin_ErrState[2].boSh2Vbat, FALSE, == );
  AL_UNITTEST_CHECK(Rsens_asRCODBin_ErrState[2].boOpenload, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function limits to the correspoding binning voltage
///                     in case the received binning voltage exceeds the threshold
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_unCodShortGND                                                                                    = 134u
/// \input  RSens_unCodShortBAT                                                                                    = 5100u
/// \input  RSens_unCodOpenLoad                                                                                    = 4773u
/// \input  RSens_Calculate_Binning_Param1                                                                         = 1u
/// \input  RSens_Calculate_Binning_Param2                                                                         = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                                                               = 15u
/// \input  asLmmAdc[RSens_aucBinClassesArry[RSens_Calculate_Binning_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_VALID
/// \input  asLmmAdc[15=4 - RSENS_LMM_CODING_OFFSET].ucADC2Value = 1144u
///
///   - Expectations:
///
/// \output Rte_Write_RSens_BinningClass_sVal_01_Param1.eSigQty     = SIG_VALID
/// \output Rte_Write_RSens_BinningClass_sVal_01_Param1.ucBinning   = eBinningClass0
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  RSens_unCodShortGND = 134u;
  RSens_unCodShortBAT = 5100u;
  RSens_unCodOpenLoad = 4773u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 15u;
  boLMMBinUpdateStatus[RSens_Calculate_Binning_Param1] = FALSE;
  asLmmAdc[RSens_aucBinClassesArry[RSens_Calculate_Binning_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_VALID;
  asLmmAdc[14 - RSENS_LMM_CODING_OFFSET].ucADC2Value = 1144u;
 
  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rte_Write_RSens_BinningClass_sVal_01_Param1.eSigQty,   SIG_VALID,      == );
  AL_UNITTEST_CHECK(Rte_Write_RSens_BinningClass_sVal_01_Param1.ucBinning, eBinningClass0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault                          = FALSE
/// \input  RSens_Calculate_Binning_Param1                                                               = 1u
/// \input  RSens_Calculate_Binning_Param2                                                               = FALSE
/// \input  RSens_aucBinClassesArry[RSENS_LED_DRV02]                                                     = 22u
/// \input  boLMMBinUpdateStatus[RSENS_LED_DRV02]                                                        = FALSE
/// \input  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                                              = 0u
/// \input  asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning                                    = 1u
/// \input  asEepromBinning[RSens_Calculate_Binning_Param1].eSigQty                                      = SIG_VALID
/// \input  aRsens_Binning_Thresholds[asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning]         = 0u
///
///   - Expectations:
///
/// \output Rsens_CheckErrorBinning_RetVal                                      = 0u
/// \output Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
 
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault = FALSE;
  RSens_Calculate_Binning_Param1 = 1u;
  RSens_Calculate_Binning_Param2 = FALSE;
  RSens_aucBinClassesArry[RSENS_LED_DRV02] = 22u;
  boLMMBinUpdateStatus[RSENS_LED_DRV02] = FALSE;
  Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount = 0u;
  asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning = 1u;
  asEepromBinning[RSens_Calculate_Binning_Param1].eSigQty = SIG_VALID;
  Rsens_Binning_Thresholds[asEepromBinning[RSens_Calculate_Binning_Param1].ucBinning] = 0u;

  //Step 3) Call the FUT
  RSens_Calculate_Binning(RSens_Calculate_Binning_Param1, RSens_Calculate_Binning_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Rsens_CheckErrorBinning_RetVal, 0u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Calculate_Binning
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function classifies the binning resistors into
///                     binning classes
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Calculate_Binning(void)
{
  Mt_RSens_Calculate_Binning_TestCase_1();
  Mt_RSens_Calculate_Binning_TestCase_2();
  Mt_RSens_Calculate_Binning_TestCase_3();
  Mt_RSens_Calculate_Binning_TestCase_4();
  Mt_RSens_Calculate_Binning_TestCase_5();
  Mt_RSens_Calculate_Binning_TestCase_6();
  Mt_RSens_Calculate_Binning_TestCase_7();
  Mt_RSens_Calculate_Binning_TestCase_8();
  Mt_RSens_Calculate_Binning_TestCase_9();
  Mt_RSens_Calculate_Binning_TestCase_10();
  Mt_RSens_Calculate_Binning_TestCase_11();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_CalculateTemp_Thzs_Param1                                                           = 1u;
/// \input  CodingParameters.psCodingParameters_Blocks                                                = &Coding_Dummy;
/// \input  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
/// \input  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]     = 1u;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                         = SIG_SNA;
///
///   - Expectations:
///
/// \output RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1] = 1500;
/// \output RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                   = SIG_INVALID;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1]=1u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1] = SIG_SNA;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], 1500, == );
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1], SIG_INVALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_CalculateTemp_Thzs_Param1                                                           = 1u;
/// \input  CodingParameters.psCodingParameters_Blocks                                                = &Coding_Dummy;
/// \input  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
/// \input  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]     = 2u;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                         = SIG_SNA;
///
///   - Expectations:
///
/// \output RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1] = 1500;
/// \output RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                   = SIG_INVALID;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 2u;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1] = SIG_SNA;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], 1500, == );
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1], SIG_INVALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_CalculateTemp_Thzs_Param1                                                           = 1u;
/// \input  CodingParameters.psCodingParameters_Blocks                                                = &Coding_Dummy;
/// \input  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
/// \input  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]     = 3u;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                         = SIG_SNA;
///
///   - Expectations:
///
/// \output RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1] = 1500;
/// \output RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                   = SIG_INVALID;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 3u;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1] = SIG_SNA;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], 1500, == );
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1], SIG_INVALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_CalculateTemp_Thzs_Param1                                                                                                          = 1u;
/// \input  CodingParameters.psCodingParameters_Blocks                                                                                               = &Coding_Dummy;
/// \input  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1]                                                = 16u;
/// \input  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]                                                    = 4u;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                                                                        = SIG_SNA;
/// \input  asLmmAdc[Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_INVALID;
///
///   - Expectations:
///
/// \output RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1] = 1500;
/// \output RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                   = SIG_INVALID;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 16u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 4u;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1] = SIG_SNA;
  asLmmAdc[Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_INVALID;
  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], 1500, == );
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1], SIG_INVALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_CalculateTemp_Thzs_Param1                                                                                                          = 1u;
/// \input  CodingParameters.psCodingParameters_Blocks                                                                                               = &Coding_Dummy;
/// \input  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1]                                                = 16u;
/// \input  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]                                                    = 4u;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                                                                        = SIG_SNA;
/// \input  asLmmAdc[Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_VALID;
///
///   - Expectations:
///
/// \output RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1] = 1500;
/// \output RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                   = SIG_INVALID;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 16u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 4u;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1] = SIG_SNA;
  asLmmAdc[Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] - 1u - RSENS_LMM_CODING_OFFSET].eQlty = CDD_MLC_QLTY_VALID;
  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], 1500, == );
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1], SIG_INVALID , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input   RSens_CalculateTemp_Thzs_Param1                                                           = 1u;
/// \input   CodingParameters.psCodingParameters_Blocks                                                = &Coding_Dummy;
/// \input   Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
/// \input   Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]     = 5u;
///
///   - Expectations:
///
/// \output  RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1]       = RSENS_INIT_TEMP;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 5u;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], RSENS_INIT_TEMP, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_CalculateTemp_Thzs_Param1                                                           = 1u;
/// \input  CodingParameters.psCodingParameters_Blocks                                                = &Coding_Dummy;
/// \input  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 0u;
/// \input  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1]     = 1u;
/// \input  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                         = SIG_INVALID;
///
///   - Expectations:
///
/// \output RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1]       = RSENS_INIT_TEMP;
/// \output RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1]                         = SIG_SNA;
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_CalculateTemp_Thzs_Param1 = 1u;
  CodingParameters.psCodingParameters_Blocks = &Coding_Dummy;
  Coding_Dummy.Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 0u;
  Coding_Dummy.Thermo1.NTC_Types.ucNtcType_Thermozones[RSens_CalculateTemp_Thzs_Param1] = 1u;
  RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1] = SIG_INVALID;

  //Step 3) Call the FUT
  RSens_CalculateTemp_Thzs(RSens_CalculateTemp_Thzs_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.s16_NTCTemperatureCelsius[RSens_CalculateTemp_Thzs_Param1], RSENS_INIT_TEMP, == );
  AL_UNITTEST_CHECK(RSens_sNTCTemperatureVal.eSigQty[RSens_CalculateTemp_Thzs_Param1], SIG_SNA, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_CalculateTemp_Thzs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads out all the NTCs sources and
///                     then calculates the temperatures
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_CalculateTemp_Thzs(void)
{
  Mt_RSens_CalculateTemp_Thzs_TestCase_1();
  Mt_RSens_CalculateTemp_Thzs_TestCase_2();
  Mt_RSens_CalculateTemp_Thzs_TestCase_3();
  Mt_RSens_CalculateTemp_Thzs_TestCase_4();
  Mt_RSens_CalculateTemp_Thzs_TestCase_5();
  Mt_RSens_CalculateTemp_Thzs_TestCase_6();
  Mt_RSens_CalculateTemp_Thzs_TestCase_7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of RSens
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks       = &Coding_Dummy;
/// \input  Rte_Read_CodM_Rsens_Para_Param1.eCodingState                    = eParaFct0_CodingDataValid;
/// \input  Coding_Dummy.LmmConfig.LMM_Config_Diagnosis.ucLTMP_LMM_NODES[0] = 1u;
///
///   - Expectations:
///
/// \output RSens_Data_asnLMM[0][LMMCOL - 1u]                               = 10u;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_Rsens_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Coding_Dummy.LmmConfig.LMM_Config_Diagnosis.ucLTMP_LMM_NODES[0] = 1u;

  //Step 3) Call the FUT
  RSens_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_Data_asnLMM[0][LMMCOL - 1u], 10u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of RSens
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input   Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks             = &Coding_Dummy;
/// \input   Rte_Read_CodM_Rsens_Para_Param1.eCodingState                          = eParaFct0_CodingDataValid;
/// \input   RSens_eCodingMode                                                     = RSENS_CODINGMODE_INVALID;
/// \input   Coding_Dummy.Thermo1.PCBNtc_ErrThresh.unPcbNtc_Sh2GndThreshold        = 1u;
/// \input   Coding_Dummy.Thermo1.PCBNtc_ErrThresh.unPcbNtc_OpenLoad               = 2u;
/// \input   Coding_Dummy.Thermo1.PCBNtc_ErrThresh.unPcbDebounceFilterT            = 3u;
/// \input   Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_Sh2GndThreshold = 4u;
/// \input   Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_Sh2Vbat         = 5u;
/// \input   Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_OpenLoad        = 6u;
/// \input   Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.ucDebounceFilterT     = 7u;
///
///   - Expectations:
///
/// \output RSens_unPCBShortGND                                                    = 1u;
/// \output RSens_unPCBOpenLoad                                                    = 2u;
/// \output RSens_unCodShortGND                                                    = 4u;
/// \output RSens_unCodShortBAT                                                    = 5u;
/// \output RSens_unCodOpenLoad                                                    = 6u;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Init_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_Rsens_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  RSens_eCodingMode = RSENS_CODINGMODE_INVALID;
  Coding_Dummy.Thermo1.PCBNtc_ErrThresh.unPcbNtc_Sh2GndThreshold = 1u;
  Coding_Dummy.Thermo1.PCBNtc_ErrThresh.unPcbNtc_OpenLoad = 2u;
  Coding_Dummy.Thermo1.PCBNtc_ErrThresh.unPcbDebounceFilterT = 3u;
  Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_Sh2GndThreshold = 4u;
  Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_Sh2Vbat = 5u;
  Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.unNtc_OpenLoad = 6u;
  Coding_Dummy.Thermo1.ExtNTCsErrThresh_DebFilter.ucDebounceFilterT = 7u;

  //Step 3) Call the FUT
  RSens_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_unPCBShortGND, 1u, == );
  AL_UNITTEST_CHECK(RSens_unPCBOpenLoad, 2u, == );
  AL_UNITTEST_CHECK(RSens_unCodShortGND, 4u, == );
  AL_UNITTEST_CHECK(RSens_unCodShortBAT, 5u, == );
  AL_UNITTEST_CHECK(RSens_unCodOpenLoad, 6u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Init_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of RSens
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  Rte_Read_CodM_Rsens_Para_Param1.eCodingState              = eParaFct0_CodingDataInvalid;
///
///   - Expectations:
///
/// \output RSens_unPCBShortGND                                       = 1u;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Init_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_Rsens_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;

  //Step 3) Call the FUT
  RSens_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_unPCBShortGND, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of RSens
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Init(void)
{
  Mt_RSens_Init_TestCase_1();
  Mt_RSens_Init_TestCase_2();
  Mt_RSens_Init_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Cycle0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of RSens according to the
///                     defined cycle time
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_boCodingValid             = FALSE;
/// \input  Dem_SetEventStatus_HitCount     = 0u;
/// \input  Rsens_asPCB_ErrState.boSh2Gnd   = TRUE;
/// \input  Rsens_asPCB_ErrState.boOpenload = FALSE;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 3u;
/// \output Dem_SetEventStatus_Param1   = NTC_PCB_E_OPENLOAD;
/// \output Dem_SetEventStatus_Param2   = DEM_EVENT_STATUS_PASSED;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Cycle0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boCodingValid = FALSE;
  Dem_SetEventStatus_HitCount = 0u;
  Rsens_asPCB_ErrState.boSh2Gnd = TRUE;
  Rsens_asPCB_ErrState.boOpenload = FALSE;

  //Step 3) Call the FUT
  RSens_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 3u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, NTC_PCB_E_OPENLOAD, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Cycle0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of RSens according to the
///                     defined cycle time
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_boCodingValid   = TRUE;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 0u;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Cycle0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boCodingValid = TRUE;

  //Step 3) Call the FUT
  RSens_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Cycle0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of RSens according to the
///                     defined cycle time
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_boCodingValid   = TRUE;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_HitCount = 0u;
///
//-----------------------------------------------------------------------------
void Mt_RSens_Cycle0_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boCodingValid = TRUE;

  //Step 3) Call the FUT
  RSens_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 7u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of RSens according to the
///                     defined cycle time
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_RSens_Cycle0(void)
{
  Mt_RSens_Cycle0_TestCase_1();
  Mt_RSens_Cycle0_TestCase_2();
  Mt_RSens_Cycle0_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riRSens_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of RSens
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
/// \input  Rte_Read_CodM_Rsens_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input  Coding_Dummy.LmmConfig.LMM_Config_Diagnosis.ucLTMP_LMM_NODES[0] = 1u;
///
///   - Expectations:
///
/// \output   AL_UNITTEST_CHECK(RSens_Data_asnLMM[0][LMMCOL - 1u], 10u, == );
///
//-----------------------------------------------------------------------------
void Mt_riRSens_Init(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_Rsens_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_Rsens_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Coding_Dummy.LmmConfig.LMM_Config_Diagnosis.ucLTMP_LMM_NODES[0] = 1u;

  //Step 3) Call the FUT
  riRSens_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(RSens_Data_asnLMM[0][LMMCOL - 1u], 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpRSens_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the cycle function of RSens according to the
///                     defined cycle time
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  RSens_boCodingValid = TRUE
///
///   - Expectations:
///
///
//-----------------------------------------------------------------------------
void Mt_rpRSens_Cycle0(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  RSens_boCodingValid = TRUE;

  //Step 3) Call the FUT
  rpRSens_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_RSens_UpdateNTCBINLMMErrors
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function gathers the binning and ntc errors 
///                     for specific NTC source type which are sent to the diagnosis 
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  ucThzId                 : thermozone index
/// \input  ucCodNtcSource          : NTC type source  from coding
/// \input  ucNtcIdx                : NTC index 
/// \input  ucLedDrvId              : LED driver index
/// \input  ucCodBinIdx             : Binning type source from coding
/// \input  ucBinIdx                : binning index
/// \input  eSigQty                 : NTC/binning signal quality
/// \input  boNTCBinErrors_Detected : NTC/binning error status
///
///   - Expectations:
///
/// \output aboNTCBinError_Out : ntc/binning error status for specific ntc source type
///
//-----------------------------------------------------------------------------
void Mt_RSens_UpdateNTCBINLMMErrors(void)
{

  struct {  uint8 ucThzId;  uint8 ucCodNtcSource;  uint8 ucNtcIdx; uint8 ucLedDrvId;  uint8 ucCodBinIdx; uint8 ucBinIdx; teRte_SigQty eSigQty; boolean boNTCBinErrors_Detected; boolean aboNTCBinError_Out;
  }asTestCaseData[] =
  {
    {                 4u,                     9u,              8u,               3u,                22u,            24u,          SIG_INVALID,                          FALSE,                        TRUE  },
    {                 4u,                     9u,              8u,               3u,                22u,            24u,          SIG_VALID,                            TRUE,                        FALSE  },
    {                 2u,                     6u,              5u,               1u,                16u,            15u,          SIG_VALID,                            FALSE,                       FALSE  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CodingParameters.psCodingParameters_Blocks->Thermo1.NTC_SOURCES.ucNtcSource_Thermozones[asTestCaseData[ucIdx].ucThzId] = asTestCaseData[ucIdx].ucCodNtcSource;
   
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    RSens_sNTCTemperatureVal.eSigQty[asTestCaseData[ucIdx].ucThzId]     = asTestCaseData[ucIdx].eSigQty;
    RSens_aboNTCBinErrors[asTestCaseData[ucIdx].ucNtcIdx]               = asTestCaseData[ucIdx].boNTCBinErrors_Detected;

    Rsens_asRCODBin_ErrState[asTestCaseData[ucIdx].ucLedDrvId].eSigQty  = asTestCaseData[ucIdx].eSigQty;
    RSens_aucBinClassesArry[asTestCaseData[ucIdx].ucLedDrvId]           = asTestCaseData[ucIdx].ucCodBinIdx;
    RSens_aboNTCBinErrors[asTestCaseData[ucIdx].ucBinIdx]               = asTestCaseData[ucIdx].boNTCBinErrors_Detected;

    //Step 3) Call the FUT
    RSens_UpdateNTCBINLMMErrors();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Rte_Write_RSens_NTC_BIN_Input_Errors_Param1.aboNTCBinError_Stat[asTestCaseData[ucIdx].ucNtcIdx], asTestCaseData[ucIdx].aboNTCBinError_Out, == );
    AL_UNITTEST_CHECK(Rte_Write_RSens_NTC_BIN_Input_Errors_Param1.aboNTCBinError_Stat[asTestCaseData[ucIdx].ucBinIdx], asTestCaseData[ucIdx].aboNTCBinError_Out, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Rsens_CheckErrorBinning
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function map for D409 the Led channel values
///                     assigned to the analog input sources
///
///    - Test Design Technique: DT (Decision Table)
///
/// \Steps:
///         Step1: Set pre - conditions
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///
/// - Preconditions:
///
/// \input  asTestCaseData[ucIdx].ucCodBinSource     : input Binning Source Index from coding
/// \input  asTestCaseData[ucIdx].ucLedDrvId         : input Led Driver Index (0-11)
/// \input  asTestCaseData[ucIdx].ucLedChBinClass    : input Binning Class for each LED channel
/// \input  asTestCaseData[ucIdx].unLedChBinCurrent  : input Binning Current for each LED channel
///
///   - Expectations:
///
/// \output asTestCaseData[ucIdx].ucBinClassDiag    : output Binning Class for D409
/// \output asTestCaseData[ucIdx].unBinCurrentDiag  : output Binning Current for D409
//-----------------------------------------------------------------------------
void Mt_RSens_Update_D409Diag(void)
{
  uint8 ucLedIdx; 
  uint8 ucCodBin; 

  struct {
    uint8 ucCodBinSource;  uint8 ucLedDrvId;  uint8 ucLedChBinClass; uint16 unLedChBinCurrent; uint8 ucBinClassDiag; uint16 unBinCurrentDiag;
  }asTestCaseData[] =
  {
    {   /* IO13 */   13u,              0u,                      0u,                     930u,                    0u,           930u         },
    {   /* IO14 */   14u,              1u,                      2u,                     705u,                    2u,           705u         },
    {   /* IO3  */   3u,               2u,                      5u,                     705u,                    5u,           705u         },
    {   /* IO10 */   10u,              3u,                      1u,                     930u,                    1u,           930u         },
    {   /* LMM5 */   19u,              4u,                      2u,                     730u,                  255u,           65535u       },
    {   /* LMM2 */   16u,              5u,                      3u,                     535u,                  255u,           65535u       },
    {   /* LMM6 */   20u,             11u,                      4u,                     535u,                  255u,           65535u       },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    ucLedIdx = asTestCaseData[ucIdx].ucLedDrvId;
    ucCodBin = asTestCaseData[ucIdx].ucCodBinSource - 1;

    //Step 1) Set pre - conditions
    RSens_aucBinClassesArry[ucLedIdx] = asTestCaseData[ucIdx].ucCodBinSource;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_CtrlLed_BinningClass_Param1.aucBinningSelect[ucLedIdx] = asTestCaseData[ucIdx].ucLedChBinClass;
    Rte_Read_CtrlLed_TgtLedSig_sVal_Param1[ucLedIdx].unCurrent = asTestCaseData[ucIdx].unLedChBinCurrent;

    //Step 3) Call the FUT
    RSens_Update_D409Diag();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

    if (ucCodBin < CFG_NTC_BIN_CNT) // Check only for IO
    {
      AL_UNITTEST_CHECK(Rte_Write_RSens_BinningDataDiag_Param1.aucBinClass[ucCodBin], asTestCaseData[ucIdx].ucBinClassDiag, == );
      AL_UNITTEST_CHECK(Rte_Write_RSens_BinningDataDiag_Param1.aunBinCurrent[ucCodBin], asTestCaseData[ucIdx].unBinCurrentDiag, == );
    }
  }
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
  ALUnitTest_AddFunction("Mt_RSens_Calculate_Binning",             Mt_RSens_Calculate_Binning);
  ALUnitTest_AddFunction("Mt_Rsens_ParallelResistor_Exists",       Mt_Rsens_ParallelResistor_Exists);
  ALUnitTest_AddFunction("Mt_RSens_TempLimitation",                Mt_RSens_TempLimitation);
  ALUnitTest_AddFunction("Mt_Rsens_CheckErrorBinning",             Mt_Rsens_CheckErrorBinning);
  ALUnitTest_AddFunction("Mt_Rsens_GetTemperature",                Mt_Rsens_GetTemperature);
  ALUnitTest_AddFunction("Mt_RSens_Rte_Read_PCBNTC",               Mt_RSens_Rte_Read_PCBNTC);
  ALUnitTest_AddFunction("Mt_RSens_Rte_Read_ExtNTC",               Mt_RSens_Rte_Read_ExtNTC);
  ALUnitTest_AddFunction("Mt_RSens_RteAccess_Write_BinnigClasses", Mt_RSens_RteAccess_Write_BinnigClasses);
  ALUnitTest_AddFunction("Mt_RSens_ParaFct0",                      Mt_RSens_ParaFct0);
  ALUnitTest_AddFunction("Mt_RSens_CheckVoltageRange",             Mt_RSens_CheckVoltageRange);
  ALUnitTest_AddFunction("Mt_RSens_CalculateTemp_Pcb",             Mt_RSens_CalculateTemp_Pcb);
  ALUnitTest_AddFunction("Mt_Rsens_GetInterpolationNTCInputs",     Mt_Rsens_GetInterpolationNTCInputs);
  ALUnitTest_AddFunction("Mt_RSens_Sh2GndHandlingNtcs",            Mt_RSens_Sh2GndHandlingNtcs);
  ALUnitTest_AddFunction("Mt_RSens_Sh2VbatHandlingNtcs",           Mt_RSens_Sh2VbatHandlingNtcs);
  ALUnitTest_AddFunction("Mt_RSens_OpenloadHandlingNtcs",          Mt_RSens_OpenloadHandlingNtcs);
  ALUnitTest_AddFunction("Mt_RSens_Sh2GndHandlingPCB",             Mt_RSens_Sh2GndHandlingPCB);
  ALUnitTest_AddFunction("Mt_RSens_OpenLoadHandlingPCB",           Mt_RSens_OpenLoadHandlingPCB);
  ALUnitTest_AddFunction("Mt_RSens_CheckErrFlagsPCB",              Mt_RSens_CheckErrFlagsPCB);
  ALUnitTest_AddFunction("Mt_RSens_CheckErrFlagsNtc_Thzs",         Mt_RSens_CheckErrFlagsNtc_Thzs);
  ALUnitTest_AddFunction("Mt_RSens_OpenloadHandlingRCODBin",       Mt_RSens_OpenloadHandlingRCODBin);
  ALUnitTest_AddFunction("Mt_RSens_Sh2VbatHandlingRCODBin",        Mt_RSens_Sh2VbatHandlingRCODBin);
  ALUnitTest_AddFunction("Mt_RSens_Sh2GndHandlingRCODBin",         Mt_RSens_Sh2GndHandlingRCODBin);
  ALUnitTest_AddFunction("Mt_RSens_CheckErrFlagsRCODs_LedDrvs",    Mt_RSens_CheckErrFlagsRCODs_LedDrvs);
  ALUnitTest_AddFunction("Mt_RSens_CalcInterpolationTemperatures", Mt_RSens_CalcInterpolationTemperatures);
  ALUnitTest_AddFunction("Mt_RSens_CalculateTemp_Thzs",            Mt_RSens_CalculateTemp_Thzs);
  ALUnitTest_AddFunction("Mt_RSens_Init",                          Mt_RSens_Init);
  ALUnitTest_AddFunction("Mt_RSens_Cycle0",                        Mt_RSens_Cycle0);
  ALUnitTest_AddFunction("Mt_riRSens_Init",                        Mt_riRSens_Init);
  ALUnitTest_AddFunction("Mt_rpRSens_Cycle0",                      Mt_rpRSens_Cycle0);
  ALUnitTest_AddFunction("Mt_RSens_UpdateNTCBINLMMErrors",         Mt_RSens_UpdateNTCBINLMMErrors);
  ALUnitTest_AddFunction("Mt_RSens_Update_D409Diag",               Mt_RSens_Update_D409Diag);
}
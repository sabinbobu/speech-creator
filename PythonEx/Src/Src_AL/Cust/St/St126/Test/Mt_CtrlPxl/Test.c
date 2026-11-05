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
/// \brief  Unit Test Cases for CtrlPxl
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaCtrlPxl.c
//            - CtrlPxl.c
//            - CtrlPxl_Data.c
//            - CtrlPxl_Diag.c
//            - CtrlPxl_MemHandling.c
//            - CtrlPxl_RteAccess.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>
#include <string.h>

// Stub headers
#include "Test_Stubs.h"
#include "Test_Ext.h"

// Headers of the unit test Module
#include "Test.h"


//-----------------------------------------------------------------------------
// DATA TYPES TO SIMULATE CODING DATA
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
///  Description
///      Reset arrays used to store coding by CtrlPxl filled with invalid data.
///
//-----------------------------------------------------------------------------
void Mt_CodingInvalid(void)
{
  for (uint8_fast ucLmm = 0u; ucLmm < CTRLPXL_CFG_NR_OF_MATRIX_DRV; ucLmm++)
  {
    for (uint8_fast ucPxl = 0u; ucPxl < CTRLPXL_CFG_NR_OF_PXLs_STRING; ucPxl++)
    {
      CTRLPXL_SEGMENT_POSITION[ucLmm][ucPxl] = 0xFFu;
    }
  }
  for (uint8_fast ucSegIdx = 0u; ucSegIdx < CTRLPXL_CFG_MAX_NR_OF_PXL; ucSegIdx++)
  {
    CTRLPXL_SEGMENT_MAP[ucSegIdx] = 0xFFu;
  }
}


//----------------------------------------------------------------------------
//    TEST CASES
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  ctaaCtrlPxl.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_riCtrlPxl_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function checks the validity of  coding 
///                     parameter status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_boCodMap_OK                     = FALSE
/// \input Coding_State                            = eParaFct0_CodingDataInvalid
/// \input Rte_Read_CodM_CtrlPxl_Para_HitCount     = 0u
///
/// - Expectations:
///
/// \output CtrlPxl_boCodMap_OK                    = FALSE
/// \output Rte_Read_CodM_CtrlPxl_Para_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_riCtrlPxl_Init_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_boCodMap_OK   = FALSE;
  Coding_State          = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_CtrlPxl_Para_HitCount = 0u;

  //Step 3) Call FUT
  riCtrlPxl_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_boCodMap_OK,              FALSE, ==);
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_HitCount, 1u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_riCtrlPxl_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function checks the validity of  coding 
///                     parameter status. In case it is valid, will perform
///                     pixel mapping
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_boCodMap_OK                     = FALSE
/// \input Coding_State                            = eParaFct0_CodingDataValid
/// \input Rte_Read_CodM_CtrlPxl_Para_HitCount     = 0u
///
/// - Expectations:
///
/// \output CtrlPxl_boCodMap_OK                    = TRUE
/// \output Rte_Read_CodM_CtrlPxl_Para_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_riCtrlPxl_Init_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_boCodMap_OK   = FALSE;
  Coding_State          = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CtrlPxl_Para_HitCount = 0u;

  //Step 3) Call FUT
  riCtrlPxl_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_boCodMap_OK,                TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_riCtrlPxl_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that in init phase, the coding parameters validity
///                     is checked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_riCtrlPxl_Init(void)
{
  Mt_CtrlPxl_riCtrlPxl_Init_TestCase1();
  Mt_CtrlPxl_riCtrlPxl_Init_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_rpCtrlPxl_Cycle0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function skips processing intensities if
///                     coding parameters are corrupted
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_boCodMap_OK                              = FALSE
/// \input Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 0u
/// \input Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount   = 0u
///
/// - Expectations:
///
/// \output Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount    = 1u
/// \output Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount  = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_rpCtrlPxl_Cycle0_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_boCodMap_OK     = FALSE;
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount        = 0u;
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount      = 0u;

  //Step 3) Call FUT
  rpCtrlPxl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount,     0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_rpCtrlPxl_Cycle0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function does processing of intensities if
///                     coding parameters are correct
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_boCodMap_OK                              = TRUE
/// \input Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 0u
/// \input Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount   = 0u
///
/// - Expectations:
///
/// \output Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount    = 1u
/// \output Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_rpCtrlPxl_Cycle0_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_boCodMap_OK     = TRUE;
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount       = 0u;
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount     = 0u;

  //Step 3) Call FUT
  rpCtrlPxl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount,     1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_rpCtrlPxl_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the cyclic routine does the processing of 
///                     intensities if the coding parameters are correct
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_rpCtrlPxl_Cycle0(void)
{
  Mt_CtrlPxl_rpCtrlPxl_Cycle0_TestCase1();
  Mt_CtrlPxl_rpCtrlPxl_Cycle0_TestCase2();
}


//-----------------------------------------------------------------------------
//  CtrlPxl.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function initializes the CtrlPxl by
///                     handling coding data. In case it's invalid,
///                     the module is not mapping any intensity
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_boCodMap_OK                     = FALSE
/// \input Coding_State                            = eParaFct0_CodingDataInvalid
/// \input Rte_Read_CodM_CtrlPxl_Para_HitCount     = 0u
///
/// - Expectations:
///
/// \output CtrlPxl_boCodMap_OK                    = FALSE
/// \output Rte_Read_CodM_CtrlPxl_Para_HitCount    = 1u
/// \output Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState     = eParaFct0_CodingDataInvalid
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Init_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_boCodMap_OK                 = FALSE;
  Coding_State                        = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_CtrlPxl_Para_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_boCodMap_OK,                FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState, eParaFct0_CodingDataInvalid, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function initializes the CtrlPxl by
///                     handling coding data. In case it's valid,
///                     the module will map intensities based on coding mapping list
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_boCodMap_OK                     = FALSE
/// \input Coding_State                            = eParaFct0_CodingDataValid
/// \input Rte_Read_CodM_CtrlPxl_Para_HitCount     = 0u
///
/// - Expectations:
///
/// \output CtrlPxl_boCodMap_OK                    = TRUE
/// \output Rte_Read_CodM_CtrlPxl_Para_HitCount    = 1u
/// \output Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState     = eParaFct0_CodingDataValid
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Init_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_boCodMap_OK                 = FALSE;
  Coding_State                        = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CtrlPxl_Para_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_boCodMap_OK,                TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState, eParaFct0_CodingDataValid, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that in init phase, the coding parameters validity
///                     is checked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Init(void)
{
  Mt_CtrlPxl_Init_TestCase1();
  Mt_CtrlPxl_Init_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Cycle0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the cyclic routine skips processing the received 
///                     intensities to the right pixel number if the pixel
///                     pixel mapping has failed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input    Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount = 0u
/// \input    Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount   = 0u
/// \input    CtrlPxl_boCodMap_OK                            = FALSE
///
/// - Expectations: 
///
/// \output   Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount = 0u
/// \output   Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Cycle0_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount = 0u;
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount   = 0u;
  CtrlPxl_boCodMap_OK                            = FALSE;

  //Step 3) Call FUT
  CtrlPxl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount,   1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Cycle0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the cyclic routine is processing the received 
///                     intensities to the right pixel number if the pixel
///                     pixel mapping was done successfully
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input    Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount   = 0u
/// \input    Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 0u
/// \input    CtrlPxl_boCodMap_OK                              = TRUE
///
/// - Expectations: 
///
/// \output   Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount   = 1u
/// \output   Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Cycle0_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount = 0u;
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount   = 0u;
  CtrlPxl_boCodMap_OK                            = TRUE;

  //Step 3) Call FUT
  CtrlPxl_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount,       1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the cycle routine calls the corresponding 
///                     functions depending on the validity of the pixel mapping operation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Cycle0(void)
{
  Mt_CtrlPxl_Cycle0_TestCase1();
  Mt_CtrlPxl_Cycle0_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_GetInternalHandlingStruct
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if function return the internal handling structure of the module
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///           CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus = FALSE
///           CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init
///
///    - Expected test results: 
///        - CtrlPxl_GetInternalHandlingStruct_RetVal->sEepromHandling.sEepromControl.boEepromAccessFaultStatus = FALSE
///        - CtrlPxl_GetInternalHandlingStruct_RetVal->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init
///
//----------------------------------------------------------------------------
void Mt_CtrlPxl_GetInternalHandlingStruct(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus = FALSE;
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init;

  //Step 3) Call the FUT
  CtrlPxl_GetInternalHandlingStruct_RetVal = CtrlPxl_GetInternalHandlingStruct();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_GetInternalHandlingStruct_RetVal->sEepromHandling.sEepromControl.boEepromAccessFaultStatus, FALSE, ==);
  AL_UNITTEST_CHECK(CtrlPxl_GetInternalHandlingStruct_RetVal->sEepromHandling.sEepromControl.eEEPromStates, eEEProm_Init, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ProcessIntensities_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the CtrlPxl_ProcessIntensities function remaps
///                     intensities received via RTE from logical units to [chip][pxl]
///                     and conerts the values into the acCepted range for matrix (10bit values)
///                     In case writing status for instrumented frames is requested, the function shall
///                     write the validation frames RTE, otherwise not (avoid unnecessary processing)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     each row of the matrix initialized with a dummy value which will be filled with
///     the values received via RTE port  te_Read_Cpm_CtrlPxl_DeratedMtxPixels, remaped and converted
///
///     Inputs:
/// \input  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount                = 0u
/// \input  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount           = 0u
/// \input  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount                       = 0u
/// \input  Rte_Write_CtrlPxl_ActualPxlError_HitCount                     = 0u
/// \input  NvmBlockInstrumentatedFrames                                  = FALSE
/// \input  CtrlPxl_ProcessIntensities_Param1                             = &UT_PixelIntesities
/// \input  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[0..102] = 0x3C10u
///
///     Output:
/// \output  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount               = 1u
/// \output  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount          = 1u
/// \output  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount                      = 0u
/// \output  Rte_Write_CtrlPxl_ActualPxlError_HitCount                    = 0u
/// \output  CtrlPxl_ProcessIntensities_Param1[0..84]                     = 0x1E0     //CtrlPxl_ProcessIntensities_Param1 contains the remaped intensities converted into pwms
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ProcessIntensities_TestCase1(void)
{
  //Step 1: Set pre-conditions
  /* UNIT TEST variables to initialize and store the results*/
  uint16 UT_PixelIntesities[CTRLPXL_CFG_PXL_NUMBERS] = { 0u };

  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount      = 0u;
  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount = 0u;
  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount             = 0u;
  Rte_Write_CtrlPxl_ActualPxlError_HitCount           = 0u;
  NvmBlockInstrumentatedFrames                        = FALSE;

  CtrlPxl_ProcessIntensities_Param1 = &UT_PixelIntesities;

  //get the matrix intensities via RTE
  for (uint8 ucIdx = 0; ucIdx < CTRLPXL_CFG_NR_OF_LOGICAL_UNITS; ucIdx++)
  {
    Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[ucIdx] = 0x3C10;   //15376 decimal
  }

  //Step 3) Call FUT
  CtrlPxl_ProcessIntensities(CtrlPxl_ProcessIntensities_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlPWM_HitCount,                    0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlError_HitCount,                  0u, == );
  for (uint8 ucPxlIdx = 0u; ucPxlIdx < CTRLPXL_CFG_PXL_NUMBERS; ucPxlIdx++)
  {
    AL_UNITTEST_CHECK(CtrlPxl_ProcessIntensities_Param1[ucPxlIdx],           0x1E0, == );     // 480 = (0x3C10 * 0x3FF) >> 15u
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ProcessIntensities_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the CtrlPxl_ProcessIntensities function remaps
///                     intensities received via RTE from logical units to [chip][pxl]
///                     and conerts the values into the acCepted range for matrix (10bit values)
///                     In case writing status for instrumented frames is requested, the function shall
///                     write the validation frames RTE, otherwise not (avoid unnecessary processing)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     each row of the matrix initialized with a dummy value which will be filled with
///     the values received via RTE port Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels, remaped and converted
///
///     Inputs:
/// \input  NvmBlockInstrumentatedFrames                                      = TRUE
/// \input  CtrlPxl_sMatrixFault.boPxlFault                                   = TRUE
/// \input  CtrlPxl_aPxlState[0u].bPxl.unLedFault                             = 0x0FFFu
/// \input  CTRLPXL_SEGMENT_POSITION[0u][10]                                  = 73u
/// \input  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount                    = 0u
/// \input  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount               = 0u
/// \input  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount                           = 0u
/// \input  Rte_Write_CtrlPxl_ActualPxlError_HitCount                         = 0u
/// \input  CtrlPxl_ProcessIntensities_Param1                                 = &UT_PixelIntesities
/// \input  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[0..102]    = 0x3C10u
///
///     Output:
/// \output  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount                   = 1u
/// \output  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount              = 1u
/// \output  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount                          = 1u
/// \output  Rte_Write_CtrlPxl_ActualPxlError_HitCount                        = 1u
/// \output  Rte_Write_CtrlPxl_ActualPxlPWM_Param1.aucActualPercMtxPWM[73u]   = 0x2F
/// \output  Rte_Write_CtrlPxl_ActualPxlError_Param1.aboMtxSegmentFault[73u]  = TRUE
/// \output  CtrlPxl_ProcessIntensities_Param1[0..84]                         = 0x1E0     //CtrlPxl_ProcessIntensities_Param1 contains the remaped intensities converted into pwms
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ProcessIntensities_TestCase2(void)
{
  //Step 1: Set pre-conditions
  /* UNIT TEST variables to initialize and store the results*/
  uint16 UT_PixelIntesities[CTRLPXL_CFG_PXL_NUMBERS] = { 0u };
  //simulate electrical error for validtion frame
  NvmBlockInstrumentatedFrames          = TRUE;
  CtrlPxl_sMatrixFault.boPxlFault       = TRUE;
  CtrlPxl_aPxlState[0u].bPxl.unLedFault = 0x0FFFu;  //[LMM1] with pixel fault
  CTRLPXL_SEGMENT_POSITION[0u][10]      = 73u;   // segment 73 -> [LMM1][Pxl 11]

  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount      = 0u;
  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount = 0u;
  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount             = 0u;
  Rte_Write_CtrlPxl_ActualPxlError_HitCount           = 0u;
  CtrlPxl_ProcessIntensities_Param1                   = &UT_PixelIntesities;

  //get the matrix intensities via RTE
  for (uint8 ucIdx = 0; ucIdx < CTRLPXL_CFG_NR_OF_LOGICAL_UNITS; ucIdx++) { Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[ucIdx] = 0x3C10;  /*15376 decimal*/ }  
  
  //Step 3) Call FUT
  CtrlPxl_ProcessIntensities(CtrlPxl_ProcessIntensities_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount,                     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlPWM_HitCount,                            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlError_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlPWM_Param1.aucActualPercMtxPWM[73u],   0x2F, == );     // 46% PWM = (0x3C10 * 100) / 0x3FF
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlError_Param1.aboMtxSegmentFault[73u],  TRUE, == );     // [LMM1][Pxl 11] has pxl defect -> segment 73 marks fault
  for (uint8 ucPxlIdx = 0u; ucPxlIdx < CTRLPXL_CFG_PXL_NUMBERS; ucPxlIdx++)
 {
    AL_UNITTEST_CHECK(CtrlPxl_ProcessIntensities_Param1[ucPxlIdx],                   0x1E0, == );     // 480 = (0x3C10 * 0x3FF) >> 15u
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ProcessIntensities_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the CtrlPxl_ProcessIntensities will not remap the intensities
///                     if the pointer to target buffer is invalid and won't write 
///                     the RTE ports
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     Inputs:
/// \input  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount      = 0u
/// \input  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount             = 0u
/// \input  Rte_Write_CtrlPxl_ActualPxlError_HitCount           = 0u
/// \input  NvmBlockInstrumentatedFrames                        = TRUE
/// \input  CtrlPxl_ProcessIntensities_Param1                   = NULL_PTR
///
///     Output:
/// \output  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount     = 1u
/// \output  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount            = 0u
/// \output  Rte_Write_CtrlPxl_ActualPxlError_HitCount          = 0u
/// \output  CtrlPxl_ProcessIntensities_Param1                  = NULL_PTR
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ProcessIntensities_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount = 0u;
  Rte_Write_CtrlPxl_ActualPxlPWM_HitCount        = 0u;
  Rte_Write_CtrlPxl_ActualPxlError_HitCount      = 0u;
  NvmBlockInstrumentatedFrames                   = TRUE;
  CtrlPxl_ProcessIntensities_Param1              = NULL_PTR;

  //Step 3) Call FUT
  CtrlPxl_ProcessIntensities(CtrlPxl_ProcessIntensities_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlPWM_HitCount,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlError_HitCount,      0u, == );
  AL_UNITTEST_CHECK(CtrlPxl_ProcessIntensities_Param1,        NULL_PTR, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ProcessIntensities
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the remapping of intensities received via RTE from
///                     CtrlLed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ProcessIntensities(void)
{
  Mt_CtrlPxl_ProcessIntensities_TestCase1();
  Mt_CtrlPxl_ProcessIntensities_TestCase2();
  Mt_CtrlPxl_ProcessIntensities_TestCase3();
}


//-----------------------------------------------------------------------------
//  CtrlPxl_Data.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_CodingDataValidation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns the status of the
///                        coding parameters
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Coding_State                            = eParaFct0_CodingDataValid
/// \input CtrlPxl_CodingDataValidation_RetVal     = FALSE
/// \input Rte_Read_CodM_CtrlPxl_Para_HitCount     = 0u
///
/// - Expectations:
///
/// \output CtrlPxl_CodingDataValidation_RetVal    = TRUE
/// \output Rte_Read_CodM_CtrlPxl_Para_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_CodingDataValidation(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Coding_State                        = eParaFct0_CodingDataValid;
  CtrlPxl_CodingDataValidation_RetVal = FALSE;
  Rte_Read_CodM_CtrlPxl_Para_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_CodingDataValidation_RetVal = CtrlPxl_CodingDataValidation();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_CodingDataValidation_RetVal, TRUE, ==);
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_HitCount,   1u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ParaFct0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the coding state and
///                        returns the validity of coding data
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_ParaFct0_Param1     = eParaFct0_CodingDataValid
/// \input CtrlPxl_ParaFct0_Param2     = &Coding_Dummy
/// \input CtrlPxl_ParaFct0_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlPxl_ParaFct0_RetVal    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ParaFct0_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_ParaFct0_Param1             = eParaFct0_CodingDataValid;
  CtrlPxl_ParaFct0_Param2             = &Coding_Dummy;
  CtrlPxl_ParaFct0_RetVal             = FALSE;

  //Step 3) Call FUT
  CtrlPxl_ParaFct0_RetVal = CtrlPxl_ParaFct0(CtrlPxl_ParaFct0_Param1, CtrlPxl_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_ParaFct0_RetVal,  TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ParaFct0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the coding state and
///                        returns the validity of coding data
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_ParaFct0_Param1     = eParaFct0_CodingDataInvalid
/// \input CtrlPxl_ParaFct0_Param2     = &Coding_Dummy
/// \input CtrlPxl_ParaFct0_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlPxl_ParaFct0_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ParaFct0_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  CtrlPxl_ParaFct0_Param2 = &Coding_Dummy;
  CtrlPxl_ParaFct0_RetVal = FALSE;

  //Step 3) Call FUT
  CtrlPxl_ParaFct0_RetVal = CtrlPxl_ParaFct0(CtrlPxl_ParaFct0_Param1, CtrlPxl_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_ParaFct0_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ParaFct0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets coding data to invalid
///                        for an undefined command status
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlPxl_ParaFct0_Param1     = 3u
/// \input CtrlPxl_ParaFct0_Param2     = &Coding_Dummy
/// \input CtrlPxl_ParaFct0_RetVal     = FALSE
///
/// - Expectations:
///
/// \output CtrlPxl_ParaFct0_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ParaFct0_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_ParaFct0_Param1 = 3u;
  CtrlPxl_ParaFct0_Param2 = &Coding_Dummy;
  CtrlPxl_ParaFct0_RetVal = FALSE;

  //Step 3) Call FUT
  CtrlPxl_ParaFct0_RetVal = CtrlPxl_ParaFct0(CtrlPxl_ParaFct0_Param1, CtrlPxl_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_ParaFct0_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the coding state and
///                     returns the validity of coding data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ParaFct0(void)
{
 Mt_CtrlPxl_ParaFct0_TestCase1();
 Mt_CtrlPxl_ParaFct0_TestCase2();
 Mt_CtrlPxl_ParaFct0_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_PxlMap_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function will not proceed to the pixel
///                        mapping if the ECU side is Undefined
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input   Undefined Coding Data -> call Mt_InitializeCodingData(eEcu_Undef)
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eEcu_Undef
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 0u
/// \input   CtrlPxl_PxlMap_RetVal                          = TRUE
///
/// - Expectations:
///
/// \output  CtrlPxl_PxlMap_RetVal                          = FALSE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_PxlMap_TestCase1(void)
{
  //Step 1) Set pre-conditions
  Mt_InitializeCodingData(eEcu_Undef);

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eEcu_Undef;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  CtrlPxl_PxlMap_RetVal                         = TRUE;

  //Step 3) Call FUT
  CtrlPxl_PxlMap_RetVal = CtrlPxl_PxlMap(CtrlPxl_PxlMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_RetVal,                              FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,          1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_PxlMap_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function will  proceed to the pixel
///                        mapping to the corresponding led channel/pixel from 
///                        coding map list if the ECU side is known
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input   Valid Coding Data -> call Mt_InitializeCodingData(eEcu_Left)
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eEcu_Left
/// \input   RRte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u
/// \input   CtrlPxl_PxlMap_RetVal                          = FALSE
///
/// - Expectations:
///
/// \output  CtrlPxl_PxlMap_RetVal                          = TRUE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount   =   1u
/// \output  CtrlPxl_PxlMap_Param1[0][0]                    =  12u
/// \output  CtrlPxl_PxlMap_Param1[0][11]                   =  23u
/// \output  CtrlPxl_PxlMap_Param1[0][7]                    =  19u
/// \output  CtrlPxl_PxlMap_Param1[1][1]                    =   0u
/// \output  CtrlPxl_PxlMap_Param1[2][5]                    =  29u
/// \output  CtrlPxl_PxlMap_Param1[3][8]                    =   0u
/// \output  CtrlPxl_PxlMap_Param1[4][5]                    =  41u
/// \output  CtrlPxl_PxlMap_Param1[4][10]                   =  46u
/// \output  CtrlPxl_PxlMap_Param1[5][2]                    =   0u
/// \output  CtrlPxl_PxlMap_Param1[6][6]                    =  54u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_PxlMap_TestCase2(void)
{
  //Step 1) Set pre-conditions
  Mt_InitializeCodingData(eEcu_Left);

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eEcu_Left;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  CtrlPxl_PxlMap_RetVal                         = FALSE;

  //Step 3) Call FUT
  CtrlPxl_PxlMap_RetVal = CtrlPxl_PxlMap(CtrlPxl_PxlMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_RetVal,                        TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[0][0],                   12u, == );  //Logical Unit 13
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[0][11],                  23u, == );  //Logical Unit 24
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[0][7],                   19u, == );  //Logical Unit 20
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[1][1],                    0u, == );  //unsigned coding data - LMM2
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[2][5],                   29u, == );  //Logical Unit 29
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[3][8],                    0u, == );  //unsigned coding data - LMM4
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[4][5],                   41u, == );  //Logical Unit 42
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[4][10],                  46u, == );  //Logical Unit 47
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[5][2],                    0u, == );  //unsigned coding data - LMM6
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[6][6],                   54u, == );  //Logical Unit 54
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_PxlMap_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function skips to make the corresspondance based
///                        on the mapping list if the read information is not in the accepted range 
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eEcu_Right
/// \input   RRte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u
/// \input   CtrlPxl_PxlMap_RetVal                          = FALSE
/// \input   CtrlPxl_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit101 = 7u
/// \input   CtrlPxl_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit101 = 16u
///
/// - Expectations:
///
/// \output  CtrlPxl_PxlMap_RetVal                          = TRUE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 1u
/// \output  CtrlPxl_PxlMap_Param1[7][0]                    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_PxlMap_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eEcu_Right;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  CtrlPxl_PxlMap_RetVal                         = FALSE;

  /* Unit Group 101 - RIGHT */
  CtrlPxl_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit101 = 7u;
  CtrlPxl_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit101 = 16u;  // invalid pixel string

  //Step 3) Call FUT
  CtrlPxl_PxlMap_RetVal = CtrlPxl_PxlMap(CtrlPxl_PxlMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_RetVal,                               TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,          1u, == );
  AL_UNITTEST_CHECK(CtrlPxl_PxlMap_Param1[7][0],                           0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_PxlMap
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the mapping of pixel intensities to the corresponding
///                     led channel/pixel from coding map list
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_PxlMap(void)
{
  Mt_CtrlPxl_PxlMap_TestCase1();
  Mt_CtrlPxl_PxlMap_TestCase2();
  Mt_CtrlPxl_PxlMap_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Data_Matrix_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlPxl_Data_Matrix does not
///                        distribute coding data in case of undefined
///                        mounted headlamp side
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input   undefined coding data -> call Mt_InitializeCodingData(eEcu_Undef);
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eEcu_Undef
/// \input   RRte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u
/// \input   CtrlPxl_Data_Matrix_RetVal                     = TRUE
///
/// - Expectations:
///
/// \output  CtrlPxl_Data_Matrix_RetVal                     = FALSE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 1u
/// \output  CtrlPxl_Data_Matrix_Param2[6][15]              = 0u
/// \output  CtrlPxl_sInternalHandling.sCodingData.aucMapLuToSeg[6][0]   = 0xFFu
/// \output  CtrlPxl_sInternalHandling.sCodingData.aucMapLuToSeg[4][0]   = 0xFFu
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Data_Matrix_TestCase1(void)
{
  //Step 1) Set pre-conditions
  Mt_InitializeCodingData(eEcu_Undef);

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eEcu_Undef;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  CtrlPxl_Data_Matrix_RetVal                    = TRUE;

  //Step 3) Call FUT
  CtrlPxl_Data_Matrix_RetVal = CtrlPxl_Data_Matrix(CtrlPxl_Data_Matrix_Param1, CtrlPxl_Data_Matrix_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_RetVal,                                FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param2[6][0],                             0u, == );
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sCodingData.aucMapLuToSeg[6][0], 0xFFu, == );
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sCodingData.aucMapLuToSeg[4][0], 0xFFu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Data_Matrix_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlPxl_Data_Matrix does not continue
///                        to proceed with saving data in case coding value is not valid.
///                        Despite knowing the mounted side and having coding filled with data,
///                        continue to process ONLY if valid values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input   valid coding data -> call Mt_InitializeCodingData(eEcu_Left);
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eEcu_Left
/// \input   RRte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u
/// \input   CtrlPxl_Data_Matrix_RetVal                     = TRUE
/// \input   CtrlPxl_pCodingArea->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[0][19] = CTRLPXL_CFG_NR_OF_LOGICAL_UNITS + 1
///
/// - Expectations:
///
/// \output  CtrlPxl_Data_Matrix_RetVal                     = FALSE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 1u
/// \output  CtrlPxl_Data_Matrix_Param1[0]                  = 255u
/// \output  CtrlPxl_Data_Matrix_Param1[9]                  = 28u
/// \output  CtrlPxl_Data_Matrix_Param1[21]                 = 0u
/// \output  CtrlPxl_Data_Matrix_Param1[39]                 = 0u
/// \output  CtrlPxl_Data_Matrix_Param2[6][0]               = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Data_Matrix_TestCase2(void)
{
  //Step 1) Set pre-conditions
  Mt_InitializeCodingData(eEcu_Left);

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eEcu_Left;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  CtrlPxl_Data_Matrix_RetVal                    = TRUE;

  CtrlPxl_pCodingArea->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[0][19] = CTRLPXL_CFG_NR_OF_LOGICAL_UNITS + 1; //coding available, but invalid value
    
  //Step 3) Call FUT
  CtrlPxl_Data_Matrix_RetVal = CtrlPxl_Data_Matrix(CtrlPxl_Data_Matrix_Param1, CtrlPxl_Data_Matrix_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_RetVal,                                FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[0],                              255u, == ); // unused segment
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[9],                               28u, == ); // processed data
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[21],                               0u, == ); // no more data to be saved
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[39],                               0u, == ); // no more data to be saved
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param2[6][0],                             0u, == ); // no more data to be saved
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Data_Matrix_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function CtrlPxl_Data_Matrix reads the corresponding
///                        coding data for the headlamp mounted side and copies in parameter
///                        CtrlPxl_Data_Matrix_Param2 the segment associated to the logical unit
///                        and in CtrlPxl_Data_Matrix_Param1 saves the logical unit associated to 
///                        the segment
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input   valid coding data -> call Mt_InitializeCodingData(eEcu_Right);
/// \input   Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eEcu_Right
/// \input   RRte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u
/// \input   CtrlPxl_Data_Matrix_RetVal                     = FALSE
///
/// - Expectations:
///
/// \output  CtrlPxl_Data_Matrix_RetVal                     = TRUE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 1u
/// \output  CtrlPxl_Data_Matrix_Param2[6][0]               = 75u
/// \output  CtrlPxl_Data_Matrix_Param2[0][8]               = 0u
/// \output  CtrlPxl_Data_Matrix_Param2[4][8]               = 0u
/// \output  CtrlPxl_Data_Matrix_Param2[2][8]               = 7u
/// \output  CtrlPxl_Data_Matrix_Param1[75]                 = 47u
/// \output  CtrlPxl_Data_Matrix_Param1[71]                 = 19u
/// \output  CtrlPxl_Data_Matrix_Param1[19]                 = 44u
/// \output  CtrlPxl_Data_Matrix_Param1[7]                  = 32u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Data_Matrix_TestCase3(void)
{
  //Step 1) Set pre-conditions
  Mt_InitializeCodingData(eEcu_Right);

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eEcu_Right;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  CtrlPxl_Data_Matrix_RetVal                    = FALSE;

  //Step 3) Call FUT
  CtrlPxl_Data_Matrix_RetVal = CtrlPxl_Data_Matrix(CtrlPxl_Data_Matrix_Param1, CtrlPxl_Data_Matrix_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_RetVal,                                 TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param2[6][0],                            76u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[75],                              47u, == );  //segment associated to [6][0]
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param2[0][8],                             0u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[71],                              19u, == );  //segment associated to [0][8]
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param2[4][8],                             0u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[19],                              44u, == );  //segment associated to [4][8]
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param2[2][8],                             7u, == );
  AL_UNITTEST_CHECK(CtrlPxl_Data_Matrix_Param1[7],                               32u, == );  //segment associated to [2][8]

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Data_Matrix
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the coding data interpretation of "Matrix sheet" at CtrlPxl Level
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Data_Matrix(void)
{
  Mt_CtrlPxl_Data_Matrix_TestCase1();
  Mt_CtrlPxl_Data_Matrix_TestCase2();
  Mt_CtrlPxl_Data_Matrix_TestCase3();

}

//-----------------------------------------------------------------------------
//  CtrlPxl_RteAccess.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_Intensities_CPM
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  takes the correct intensities
///                     via RTE from CPM module (already with power factor) 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[1] = 0xEFu
/// \input CtrlPxl_RteAccess_Get_Intensities_CPM_Param1[1]         = 0u
/// \input Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount          = 0u
///
///   - Expectations:
///
/// \output CtrlPxl_RteAccess_Get_Intensities_CPM_Param1[1]        = 0xEFu
/// \output Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount         = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_Intensities_CPM(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1.unPxl_Int[1]     = 0xEFu;
  CtrlPxl_RteAccess_Get_Intensities_CPM_Param1[1]     = 0u;
  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount      = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Get_Intensities_CPM(CtrlPxl_RteAccess_Get_Intensities_CPM_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_Intensities_CPM_Param1[1], 0xEFu,  == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_ECU_Side
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function returns the ECU side received via
///                     RTE from IoHwAb module
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1     = eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount   = 0u
///
///   - Expectations:
///
/// \output CtrlPxl_RteAccess_Get_ECU_Side_RetVal         = eEcu_Left
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_ECU_Side(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Get_ECU_Side_RetVal = CtrlPxl_RteAccess_Get_ECU_Side();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_ECU_Side_RetVal,                 eEcu_Left,  == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,                 1u,  == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Read_EcuSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores the ECU side read via
///                     RTE from IoHwAb module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
///  \DT-Info:
///
///   - Inputs:
///       eReceivedSide : mounted side received via RTE
///
///   - Expectations:
///       eMappedSide : the mounted side remaped by CtrlPxl module
///       ucRteReadCnt: counter value to ensure RTE is accesed once only
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Read_EcuSide(void)
{

  struct { teRte_MountingSide eReceivedSide;  teCtrlPxl_EcuSide eMappedSide; uint8 ucRteReadCnt } asTestCaseData[]
    = {  {                    eMountedLeft  ,                      eEcu_Left,                1u },
         {                    eMountedRight ,                     eEcu_Right,                1u },
         {                    eMountedUndef ,                     eEcu_Undef,                1u },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = asTestCaseData[ucIdx].eReceivedSide;

    //Step 3) Call FUT
    CtrlPxl_RteAccess_Read_EcuSide_RetVal = CtrlPxl_RteAccess_Read_EcuSide(&CtrlPxl_RteAccess_Read_EcuSide_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Read_EcuSide_Param1,            asTestCaseData[ucIdx].eMappedSide,  == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,    asTestCaseData[ucIdx].ucRteReadCnt,  == );

  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_Coding
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores the coding parameters 
///                     received via RTE from CodM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState              = eParaFct0_CodingDataValid
/// \input Rte_Read_CodM_CtrlPxl_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy
/// \input Rte_Read_CodM_CtrlPxl_Para_HitCount                         = 0u
///
///   - Expectations:
///
/// \output CtrlPxl_RteAccess_Get_Coding_Param1.eCodingState              = eParaFct0_CodingDataValid
/// \output Rte_Read_CodM_CtrlPxl_Para_HitCount                           = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_Coding(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_CtrlPxl_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CtrlPxl_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_CtrlPxl_Para_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Get_Coding(&CtrlPxl_RteAccess_Get_Coding_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_Coding_Param1.eCodingState, eParaFct0_CodingDataValid, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlPxl_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Set_MLC_EnableTransmission
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Set_MLC_EnableTransmission 
///                     sends the  command to trigger reset communication command for the MLC driver
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///        Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount = 0u
///
///   - Expectations:
///
///       Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount = 1u
///       Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1   = CTRL_PXL_MATRIX_SYSMODE_CTRL_RESETCOMM
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Set_MLC_EnableTransmission(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Set_MLC_EnableTransmission();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount,                                    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1,  CTRL_PXL_MATRIX_SYSMODE_CTRL_RESETCOMM, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Set_MLC_DisableTransmission
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Set_MLC_DisableTransmission 
///                     sends the command to disable communication for the MLC driver
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///        Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount = 0u
///
///   - Expectations:
///
///       Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount = 1u
///       Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1   = CTRL_PXL_MATRIX_SYSMODE_CTRL_SETINACTIVE
///
//-----------------------------------------------------------------------------
//TODO: commented, as function is not deleted from implementation, only commented for this release - still under development
//void Mt_CtrlPxl_RteAccess_Set_MLC_DisableTransmission(void)
//{
//  //Step 1: Set pre-conditions
//  //Step 2) Assign Input values
//  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount = 0u;
//
//  //Step 3) Call FUT
//  CtrlPxl_RteAccess_Set_MLC_DisableTransmission();
//
//  //Step 4) Check expected output values
//  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount,                                      1u, == );
//  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1,  CTRL_PXL_MATRIX_SYSMODE_CTRL_SETINACTIVE, == );
//}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Reset_MLCSettings
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Reset_MLCSettings 
///                     sends the command to reinitialize the MLC driver
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///        Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount  = 0u
///        Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1    = FALSE
///
///   - Expectations:
///
///       Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount = 1u
///       Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Reset_MLCSettings(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount  = 0u;
  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1    = FALSE;
  //Step 3) Call FUT
  CtrlPxl_RteAccess_Reset_MLCSettings();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1,       TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Set_MLCTgtPWMs
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Set_MLCTgtPWMs 
///                     writes the mapped intensities to MLC driver
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 0u
/// \input CtrlPxl_RteAccess_Set_MLCTgtPWMs_Param1          = 15u
/// \input Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1[0][0] = 20u
///
///   - Expectations:
///
/// \output Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 1u
/// \output Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1[0][0] = 15u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Set_MLCTgtPWMs(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount     = 0u;
  CtrlPxl_RteAccess_Set_MLCTgtPWMs_Param1          = 15u;
  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1[0][0] = 20u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Set_MLCTgtPWMs(CtrlPxl_RteAccess_Set_MLCTgtPWMs_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1[0][0], 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_PxlErrorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Get_PxlErrorStatus 
///                     reads the RTE port and returns the correct status
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           unLedFault : pixel fault mapped on bit (12pxls )
///
///       Expectations:
///           boLedFault : status of pixel fault (detected/ no error)
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_PxlErrorStatus(void)
{
  //Step 1: Set pre-conditions
  CtrlPxl_RteAccess_Get_PxlErrorStatus_RetVal                  = FALSE;

  struct { uint16    unLedFault;         boolean boLedFault; } asTestCaseData[]
    = { {              0x0000u ,                   FALSE     },     // no pixel fault
        {              0x01FEu ,                   TRUE      }, };  //  pixel fault

  for (uint8 ucIdx = 0; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_HitCount = 0u;
    Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_Param1[ucIdx].unLedFault = asTestCaseData[ucIdx].unLedFault;

    //Step 3) Call FUT
    CtrlPxl_RteAccess_Get_PxlErrorStatus_RetVal = CtrlPxl_RteAccess_Get_PxlErrorStatus(&CtrlPxl_RteAccess_Get_PxlErrorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_HitCount,                           1u, == );
    AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_PxlErrorStatus_RetVal, asTestCaseData[ucIdx].boLedFault, == );
    AL_UNITTEST_CHECK(CtrlPxl_asPxlState[ucIdx].unLedFault,        asTestCaseData[ucIdx].unLedFault, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_CommErrorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Get_CommErrorStatus
///                     reads the RTE port and returns the correct status
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucCommFault : MLC communication fault mapped on bit ( max. 8 MLCs )
///
///       Expectations:
///           boCommFault : status of communication error (detected/ no error)
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_CommErrorStatus(void)
{
  //Step 1: Set pre-conditions
  CtrlPxl_RteAccess_Get_CommErrorStatus_RetVal = FALSE;

  struct { uint8    ucCommFault;         boolean boCommFault; } asTestCaseData[]
    = { {              0x00u ,                   FALSE     },     // no comm fault
        {              0xAAu ,                   TRUE      }, };  // comm. fault detected

  for (uint8 ucIdx = 0; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount             = 0u;
    Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucMlcStatus   = asTestCaseData[ucIdx].ucCommFault;

    //Step 3) Call FUT
    CtrlPxl_RteAccess_Get_CommErrorStatus_RetVal = CtrlPxl_RteAccess_Get_CommErrorStatus(&CtrlPxl_RteAccess_Get_CommErrorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount,                             1u, == );
    AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_CommErrorStatus_RetVal, asTestCaseData[ucIdx].boCommFault, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_ResetErrorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Get_ResetErrorStatus
///                     reads the RTE port and returns the correct status
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucPwrReset : MLC power reset mapped on bit ( max. 8 MLCs )
///
///       Expectations:
///           boPwrFault : status of internal MLC reset (detected/ no error)
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_ResetErrorStatus(void)
{
  //Step 1: Set pre-conditions
  CtrlPxl_RteAccess_Get_ResetErrorStatus_RetVal = FALSE;

  struct { uint8    ucPwrReset;         boolean boPwrFault; } asTestCaseData[]
    = { {              0x00u ,                   FALSE      },     // no power reset
        {              0xAAu ,                   TRUE       }, };  // power reset detected

  for (uint8 ucIdx = 0; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount            = 0u;
    Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucPowerCycle = asTestCaseData[ucIdx].ucPwrReset;

    //Step 3) Call FUT
    CtrlPxl_RteAccess_Get_ResetErrorStatus_RetVal = CtrlPxl_RteAccess_Get_ResetErrorStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount,                             1u, == );
    AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_ResetErrorStatus_RetVal, asTestCaseData[ucIdx].boPwrFault, == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Write_MatrixFaultStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Write_MatrixFaultStatus
///                     writes correctly the fault states on the RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///         CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boCommFault    = FALSE
///         CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boPxlFault     = TRUE
///         CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boShortToGnd   = TRUE
///         CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boShortToVbat  = FALSE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError  = FALSE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError   = FALSE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError = FALSE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError = FALSE
///
///     - Expectations:
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount                =       1u
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError      =    FALSE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError       =     TRUE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError=     TRUE
///         Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError=   FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Write_MatrixFaultStatus(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boCommFault          = FALSE;
  CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boPxlFault           = TRUE;
  CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boShortToGnd         = TRUE;
  CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1.boShortToVbat        = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError        = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError         = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError  = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Write_MatrixFaultStatus(&CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError,          FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError,            TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError,     TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError,   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Read_VccxLineState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_RteAccess_Read_VccxLineState
///                     reads  correctly the Vccx Status and updates the flags for
///                     the detected error
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           eVccxLineState : Vccx (matrix supply pin) status received via RTE
///
///       Expectations:
///           eVccxState     : Vccx status remapped by CtrlPxl module for internal usage
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Read_VccxLineState(void)
{

  struct { teRte_VccxLineState    eVccxLineState;   teCtrlPxl_VccxLineState eVccxState;     } asTestCaseData[]
    = { {                      eVccx_Short2GND  ,               eMatrixVccx_Short2GND       },    // short to ground detected 
        {                      eVccx_Short2Vbat ,               eMatrixVccx_Short2Vbat      },    // short to vbat detected
        {                                  255u ,                   eMatrixVccx_noError     }, }; // default state

  //Step 1) Set pre - conditions
  Rte_Read_IoHwAbUser_VccxLineState_RetVal = 0u;

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_IoHwAbUser_VccxLineState_HitCount = 0u;
    Rte_Read_IoHwAbUser_VccxLineState_Param1 = asTestCaseData[ulIdx].eVccxLineState;

    //Step 3) Call the FUT
    CtrlPxl_RteAccess_Read_VccxLineState_RetVal = CtrlPxl_RteAccess_Read_VccxLineState(&CtrlPxl_RteAccess_Read_VccxLineState_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Read_VccxLineState_Param1, asTestCaseData[ulIdx].eVccxState,  == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_VccxLineState_HitCount,                         1u, == );

  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_VccxState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Get_VccxState 
///                     returns correctly the Vccx Status decoded from RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input CtrlPxl_RteAccess_Get_VccxState_RetVal             = eMatrixVccx_noError
/// \input Rte_Read_IoHwAbUser_VccxLineState_Param1   = eVccx_Short2GND
///
///   - Expectations:
///
/// \output CtrlPxl_RteAccess_Get_VccxState_RetVal     = eMatrixVccx_Short2GND
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_VccxState(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_RteAccess_Get_VccxState_RetVal           = eMatrixVccx_noError;
  Rte_Read_IoHwAbUser_VccxLineState_Param1 = eVccx_Short2GND;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Get_VccxState_RetVal = CtrlPxl_RteAccess_Get_VccxState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_VccxState_RetVal, eMatrixVccx_Short2GND, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Get_MlcCrcError
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Get_MlcCrcError 
///                     reads correctly the RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount     = 0u
/// \input Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1.aboMlcCorruptedComm[0] = TRUE
///
///   - Expectations:
///
/// \output Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount    = 1u
/// \output CtrlPxl_RteAccess_Get_MlcCrcError_Param1          = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Get_MlcCrcError(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount = 0u;
  Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1.aboMlcCorruptedComm[0] = TRUE;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Get_MlcCrcError(&CtrlPxl_RteAccess_Get_MlcCrcError_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CtrlPxl_RteAccess_Get_MlcCrcError_Param1,         1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Write_MlcErrors
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Write_MlcErrors 
///                     writes on the RTE port the matrix faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount        = 0u
/// \input CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.bCoruptComm  = FALSE
/// \input CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.bLossComm    = TRUE
/// \input CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.bPxlFault    = TRUE
/// \input CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.Reserved     = FALSE
///
///   - Expectations:
///
/// \output Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount    = 1u
/// \output Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.bCoruptComm = FALSE
/// \output Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.bLossComm   = TRUE
/// \output Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.bPxlFault   = TRUE
/// \output Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.Reserved    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Write_MlcErrors(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount = 0u;
  CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.bCoruptComm = FALSE;
  CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.bLossComm   = TRUE;
  CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.bPxlFault   = TRUE;
  CtrlPxl_RteAccess_Write_MlcErrors_Param1.bErr.Reserved    = FALSE;


  //Step 3) Call FUT
  CtrlPxl_RteAccess_Write_MlcErrors(&CtrlPxl_RteAccess_Write_MlcErrors_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.bCoruptComm, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.bLossComm,    TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.bPxlFault,    TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1.auMtxErrorStatus[0u].bErr.Reserved,    FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames 
///                     writes correctly the pixel intensities [%] on the RTE port for
///                     validation frames
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames_Param1.aucActualPercMtxPWM[0..89] = 0x31u
/// \input Rte_Write_CtrlPxl_ActualPxlPWM_Param1.aucActualPercMtxPWM[0..89] = 0x00u
///
///   - Expectations:
///
/// \output Rte_Write_CtrlPxl_ActualPxlPWM_Param1.aucActualPercMtxPWM[0..89] = 0x31u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  for (uint8 ucSegIdx = 0u; ucSegIdx < CFG_MATRIX_MAX_NO_PXL; ucSegIdx++)
  {
    CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames_Param1.aucActualPercMtxPWM[ucSegIdx] = 0x31u;
    Rte_Write_CtrlPxl_ActualPxlPWM_Param1.aucActualPercMtxPWM[ucSegIdx] = 0x00u;
  }

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames(&CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames_Param1);

  //Step 4) Check expected output values
  for (uint8 ucSegIdx = 0u; ucSegIdx < CFG_MATRIX_MAX_NO_PXL; ucSegIdx++)
  {
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlPWM_Param1.aucActualPercMtxPWM[ucSegIdx], 0x31u,==); //RTE port
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames 
///                     writes correctly the pixel defect status on the RTE port for
///                     validaion frames
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames_Param1.aboMtxSegmentFault[0..89] = TRUE
/// \input Rte_Write_CtrlPxl_ActualPxlError_Param1.aboMtxSegmentFault[0..89]                 = FALSE
///
///   - Expectations:
///
/// \output Rte_Write_CtrlPxl_ActualPxlError_Param1.aboMtxSegmentFault[0..89]                 = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  for (uint8 ucSegIdx = 0u; ucSegIdx < CFG_MATRIX_MAX_NO_PXL; ucSegIdx++)
  {
    CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames_Param1.aboMtxSegmentFault[ucSegIdx] = TRUE;
    Rte_Write_CtrlPxl_ActualPxlError_Param1.aboMtxSegmentFault[ucSegIdx] = FALSE;
  }

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames(&CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames_Param1);

  //Step 4) Check expected output values
  for (uint8 ucSegIdx = 0u; ucSegIdx < CFG_MATRIX_MAX_NO_PXL; ucSegIdx++)
  {
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_ActualPxlError_Param1.aboMtxSegmentFault[ucSegIdx], TRUE,==); //RTE port
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_MatrixEE_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_MatrixEE_Init 
///                     triggers correctly the initialization of I2C State Machine
///                     via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_RteAccess_MatrixEE_Init_Param1 = CtrlPxl_MatrixEEClbkInit_Success
/// \input  CtrlPxl_RteAccess_MatrixEE_Init_Param2 = CtrlPxl_MatrixEEClbkInit_Fail
/// \input  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init
/// \input  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount     = 0u
///
///    - Expectations:
/// \output Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount     = 1u
/// \output CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_MatrixEE_Init(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_RteAccess_MatrixEE_Init_Param1 = CtrlPxl_MatrixEEClbkInit_Success;
  CtrlPxl_RteAccess_MatrixEE_Init_Param2 = CtrlPxl_MatrixEEClbkInit_Fail;
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init;
  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount = 0u;
  
  //Step 3) Call FUT
  CtrlPxl_RteAccess_MatrixEE_Init(CtrlPxl_RteAccess_MatrixEE_Init_Param1, CtrlPxl_RteAccess_MatrixEE_Init_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates, eEEProm_Wait,==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount,                           1u,       ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_ReadNvmMatrixData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_ReadEEPromNvmBlock 
///                     triggers correctly the access of Nvm Data via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  UtilMemCopy_HitCount  = 0u
/// \input  CtrlPxl_RteAccess_ReadNvmMatrixData_Param1 = &Mt_DataTest
/// \input  CtrlPxl_RteAccess_ReadNvmMatrixData_Param2 = 10u
///
///    - Expectations:
/// \output UtilMemCopy_HitCount     = 1u
/// \output UtilMemCopy_Input_Param3 = 10u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_ReadNvmMatrixData(void)
{
  //Step 1: Set pre-conditions
  uint8 Mt_DataTest;
  //Step 2) Assign Input values
  UtilMemCopy_HitCount = 0u;
  CtrlPxl_RteAccess_ReadNvmMatrixData_Param1 = &Mt_DataTest;
  CtrlPxl_RteAccess_ReadNvmMatrixData_Param2 = 10u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_ReadNvmMatrixData(CtrlPxl_RteAccess_ReadNvmMatrixData_Param1, CtrlPxl_RteAccess_ReadNvmMatrixData_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_Input_Param3,                                                 10u,       ==);
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                                                      1u,       ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_MtxEE_Read
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_ReadEEPromNvmBlock 
///                     triggers correctly the access of EEPROM Data via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_RteAccess_MtxEE_Read_Param1            = &Mt_DataTest
/// \input  Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount   = 0u
/// \input  CtrlPxl_RteAccess_MtxEE_Read_Param2            = 0u
/// \input  CtrlPxl_RteAccess_MtxEE_Read_Param3            = 255u
/// \input  CtrlPxl_RteAccess_MtxEE_Read_Param4            = CtrlPxl_MtxEEClbkRead_Success
/// \input  CtrlPxl_RteAccess_MtxEE_Read_Param5            = CtrlPxl_MtxEEClbkRead_Fail
///
///    - Expectations:
/// \output CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait
/// \output Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEEStartAdd = 0u
/// \output Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEELength   = 255u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_MtxEE_Read(void)
{
  //Step 1: Set pre-conditions
  uint8 Mt_DataTest;

  //Step 2) Assign Input values
  UtilMemCopy_HitCount = 0u;
  Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount = 0u;
  CtrlPxl_RteAccess_MtxEE_Read_Param1 = &Mt_DataTest;
  CtrlPxl_RteAccess_MtxEE_Read_Param2 = 0u;
  CtrlPxl_RteAccess_MtxEE_Read_Param3 = 255u;
  CtrlPxl_RteAccess_MtxEE_Read_Param4 = CtrlPxl_MtxEEClbkRead_Success;
  CtrlPxl_RteAccess_MtxEE_Read_Param5 = CtrlPxl_MtxEEClbkRead_Fail;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_MtxEE_Read(CtrlPxl_RteAccess_MtxEE_Read_Param1, CtrlPxl_RteAccess_MtxEE_Read_Param2, CtrlPxl_RteAccess_MtxEE_Read_Param3, CtrlPxl_RteAccess_MtxEE_Read_Param4, CtrlPxl_RteAccess_MtxEE_Read_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates,  eEEProm_Wait,  ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEEStartAdd,                                0u,  ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEELength,                                255u,  ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_MtxEE_Write
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_MtxEE_Write 
///                     triggers correctly the access of EEPROM Data via RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_RteAccess_MtxEE_Write_Param1            =   Mt_DataTest
/// \input  Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount    = 0u
/// \input  CtrlPxl_RteAccess_MtxEE_Write_Param2            = 0u
/// \input  CtrlPxl_RteAccess_MtxEE_Write_Param3            = 255u
/// \input  CtrlPxl_RteAccess_MtxEE_Write_Param4            = CtrlPxl_MtxEEClbkWrite_Success
/// \input  CtrlPxl_RteAccess_MtxEE_Write_Param5            = CtrlPxl_MtxEEClbkWrite_Fail
///
///    - Expectations:
/// \output CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait
/// \output Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1.unMatrixEEStartAdd = 0u
/// \output Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1.unMatrixEELength   = 255u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_MtxEE_Write(void)
{
  //Step 1: Set pre-conditions
  uint8 Mt_DataTest[256];

  //Step 2) Assign Input values
  UtilMemCopy_HitCount = 0u;
  Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount = 0u;
  memcpy(CtrlPxl_RteAccess_MtxEE_Write_Param1, Mt_DataTest, sizeof(Mt_DataTest));
  CtrlPxl_RteAccess_MtxEE_Write_Param2 = 0u;
  CtrlPxl_RteAccess_MtxEE_Write_Param3 = 255u;
  CtrlPxl_RteAccess_MtxEE_Write_Param4 = CtrlPxl_MtxEEClbkWrite_Success;
  CtrlPxl_RteAccess_MtxEE_Write_Param5 = CtrlPxl_MtxEEClbkWrite_Fail;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_MtxEE_Write(CtrlPxl_RteAccess_MtxEE_Write_Param1, CtrlPxl_RteAccess_MtxEE_Write_Param2, CtrlPxl_RteAccess_MtxEE_Write_Param3, CtrlPxl_RteAccess_MtxEE_Write_Param4, CtrlPxl_RteAccess_MtxEE_Write_Param5);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlPxl_GetInternalHandlingStruct()->sEepromHandling.sEepromControl.eEEPromStates, eEEProm_Wait, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1.unMatrixEEStartAdd, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1.unMatrixEELength, 255u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_ReadEntireMatrixData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_ReadEntireMatrixData 
///                     access the requested memory type to read data
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           boEepromAccess : command to access Eeprom memory
///           ucMemBuffer[0..255] : data values read from eeprom
///
///       Expectations:
///           ucDataSize     : size of data to be read
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_ReadEntireMatrixData(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values

  struct { boolean boEepromAccess;   uint8 ucMemBuffer[255];   uint16 unDataSize; } asTestCaseData[]
    = { {                 TRUE,           {0xFFu},           CTRL_PXL_EEPROM_SIZE },
        {                FALSE,           {0xFFu},           CTRL_PXL_EEPROM_SIZE },
      };

  //Step 3) Call FUT
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    CtrlPxl_RteAccess_ReadEntireMatrixData_Param1 = asTestCaseData[ucIdx].boEepromAccess;
    CtrlPxl_RteAccess_ReadEntireMatrixData_Param2 = &asTestCaseData[ucIdx].ucMemBuffer[0];

    //Step 3) Call FUT
    CtrlPxl_RteAccess_ReadEntireMatrixData(CtrlPxl_RteAccess_ReadEntireMatrixData_Param1, CtrlPxl_RteAccess_ReadEntireMatrixData_Param2);

    //Step 4) Check expected output values
    if (ucIdx == 0u)
    {
      AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.pucMatrixEEbuffer[0u], 0xFFu, == );
    }
    else
    {
      AL_UNITTEST_CHECK(UtilMemCopy_Input_Param3, asTestCaseData[ucIdx].unDataSize, == );
    }
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_WriteBinningClass
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_WriteBinningClass 
///                     sends correctly the  quality flag and binning class
///                     via RTE
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucBinIdx :  channel binning index
///           ucBinClass : current binning class 
///           boValidity : status of data validity
///
///       Expectations:
///           eSigQty    : status of signal quality of binning data
///           ucBinClass : selected current binning class 
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_WriteBinningClass(void)
{
  //Step 1: Set pre-conditions
   uint8 Mt_BinnClass[12u] = { CTRL_PXL_CFG_MAX_BINNING_CLASSES, 0u, 1u, 2u, 0xFFu, 0u, 0u, 0u, 0u, 0u, 2u, 0u };

  //Step 2) Assign Input values
  struct { uint8 ucBinIdx;                  uint8 ucBinClass;    boolean boValidity;   teRte_SigQty eSigQty;  }asTestCaseData[]
    = {    {           0u,      CTRL_PXL_CFG_BINNING_CLASS_0,               FALSE,             SIG_INVALID  },
           {          10u,                               2u ,                TRUE,                SIG_VALID },
           {          11u,                               0u ,                TRUE,                SIG_VALID },
      };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    CtrlPxl_RteAccess_WriteBinningClass_Param1 = asTestCaseData[ucIdx].boValidity;
    CtrlPxl_RteAccess_WriteBinningClass_Param2 = &Mt_BinnClass[0];

    //Step 3) Call FUT
    CtrlPxl_RteAccess_WriteBinningClass(CtrlPxl_RteAccess_WriteBinningClass_Param1, CtrlPxl_RteAccess_WriteBinningClass_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1[asTestCaseData[ucIdx].ucBinIdx].eSigQty,      asTestCaseData[ucIdx].eSigQty, ==);
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1[asTestCaseData[ucIdx].ucBinIdx].ucBinning, asTestCaseData[ucIdx].ucBinClass, ==);

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM 
///                     triggers correctly the RTE port for writing into NVM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM_Param1 = &Mt_TestData[0]
/// \input  Rte_Write_CtrlPxl_Nvm_WriteData_HitCount              = 0u
///
///    - Expectations :
/// \output Rte_Write_CtrlPxl_Nvm_WriteData_Param1.unSize         = CTRL_PXL_EEPROM_SIZE
/// \output Rte_Write_CtrlPxl_Nvm_WriteData_Param1.pucData[0]     = 0xFFu
/// \output Rte_Write_CtrlPxl_Nvm_WriteData_HitCount              = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  uint8 Mt_TestData[256] = { 0xFFu };
  CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM_Param1 = &Mt_TestData[0];
  Rte_Write_CtrlPxl_Nvm_WriteData_HitCount = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM(CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_Nvm_WriteData_Param1.unSize,    CTRL_PXL_EEPROM_SIZE, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_Nvm_WriteData_Param1.pucData[0],               0xFFu, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_Nvm_WriteData_HitCount,                           1u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus 
///                     sends correctly via the RTE port the matrix eeprom error status:
///                     no access fault or wrong checksum fault
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param1 = TRUE
/// \input  CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param2 = FALSE
/// \input  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount   = 0u
///
///    - Expectations :
/// \output Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault   = FALSE
/// \output Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault = TRUE
/// \output Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount                       = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param1 = TRUE;
  CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param2 = FALSE;
  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount   = 0u;

  //Step 3) Call FUT
  CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus(CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param1, CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault,     FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromWrngChksumFault,    TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount,                            1u, == );

}


//-----------------------------------------------------------------------------
//  CtrlPxl_Diag.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Diag_ErrorDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_Diag_ErrorDetected
///                     writes correctly the fault states on the RTE port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError        = FALSE
/// \input  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError         = FALSE
/// \input  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError  = FALSE
/// \input  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError = FALSE
/// \input  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount              = 0u
/// \input  CtrlPxl_sMatrixFault.boShortToGnd = TRUE
/// \input  CtrlPxl_sMatrixFault.boShortToVbat = FALSE
///
///    - Expectations :
/// \output Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError  = TRUE
/// \output Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError = FALSE
/// \output Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Diag_ErrorDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boCommError        = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boPxlError         = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError  = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError = FALSE;
  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount                  = 0u;
  CtrlPxl_sMatrixFault.boShortToGnd     = TRUE;
  CtrlPxl_sMatrixFault.boShortToVbat    = FALSE;

  //Step 3) Call FUT
  CtrlPxl_Diag_ErrorDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToGndError,     TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1.boShortToVbatError,   FALSE, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_GetMtxFaults
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function CtrlPxl_GetMtxFaults 
///                     returns the error status for the corresponding [chip][pxl.indx]
///                     Inject fault of electrical/communication type on specific lmm
///                     driver and switch number and compute the matrix error.
///
///    - Test Design Technique: DT ( Decision Table )
///
///    - DT- Info:
///       Inputs:
///           ucMtxIdx     : matrix chip index (max 7 MLCs)
///           ucSwNr       : switch index (pixel number)
///           boLossComm   : detection status for loss of communication
///           boCorruptComm   : detection status for corrupt communication
///           boPxlDefect   : detection status for pixel defect
///           ucMlcStatus   : loss of communication status
///           unPxlFault    : detection of pixel fault status
///
///       Expectations:
///           uMtxFaultOut    : Matrix error status 
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_GetMtxFaults(void)
{
  //Step 1) Set pre - conditions
  CtrlPxl_GetMtxFaults_RetVal.ucRaw = 0U;

  struct { uint8 ucMtxIdx; uint8 ucSwNr; boolean boLossComm; boolean boCorruptComm; boolean boPxlDefect; uint8 ucMlcStatus; boolean boCrcFault; uint16 unPxlFault; tuCtrlPxl_bErr uMtxFaultOut; } asTestCaseData[]
       = { {           1u,           6u,               TRUE,                   TRUE,              FALSE,             0x07u,                TRUE,          0x0FFFu,          {.ucRaw = 3u}    },  // loss comm + corrupt comm
           {           3u,           1u,               TRUE,                  FALSE,               TRUE,             0x09u,               FALSE,          0x0F0Cu,          {.ucRaw = 1u}    },  // loss comm
           {           5u,           8u,               TRUE,                  FALSE,               TRUE,             0x01u,               FALSE,          0x0F00u,          {.ucRaw = 4u}    },  // pxl defect 
           {           7u,          11u,              FALSE,                  FALSE,              FALSE,             0x00u,               FALSE,          0x0000u,          {.ucRaw = 0u}    } };// no error
  

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
        //Step 2) Assign all input values to the corresponding input variables identified in the FUT
        CtrlPxl_sMatrixFault.boCommFault  = asTestCaseData[ulIdx].boLossComm;
        CtrlPxl_sMatrixFault.boPxlFault   = asTestCaseData[ulIdx].boPxlDefect;
        
        //1) loss of communication
        CtrlPxl_sMlcStatus.ucMlcStatus    = asTestCaseData[ulIdx].ucMlcStatus;
        //2) corrupt communication
        CtrlPxl_aucCrcState[asTestCaseData[ulIdx].ucMtxIdx] = asTestCaseData[ulIdx].boCorruptComm;
        CtrlPxl_sMatrixFault.boCrcFault = asTestCaseData[ulIdx].boCorruptComm;
        //3) pixel defect
        CtrlPxl_aPxlState[asTestCaseData[ulIdx].ucMtxIdx].bPxl.unLedFault = asTestCaseData[ulIdx].unPxlFault;

        //input parameters [chip][pxl]
        CtrlPxl_GetMtxFaults_Param1 = asTestCaseData[ulIdx].ucMtxIdx;
        CtrlPxl_GetMtxFaults_Param2 = asTestCaseData[ulIdx].ucSwNr;

        //Step 3) Call the FUT
        CtrlPxl_GetMtxFaults_RetVal = CtrlPxl_GetMtxFaults(CtrlPxl_GetMtxFaults_Param1, CtrlPxl_GetMtxFaults_Param2);

        //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
        AL_UNITTEST_CHECK(CtrlPxl_GetMtxFaults_RetVal.ucRaw, asTestCaseData[ulIdx].uMtxFaultOut.ucRaw, == );
   }

 } 

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Diag_Handle_VCCx
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_Diag_Handle_VCCx
///                     interprets correctly the Vccx Status and updates the flags for
///                     the detected error
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucVccxState     : Vccx (matrix supply pin) state 
///           boCommFault     : matrix communication error status ( detected/no error )
///
///       Expectations:
///           boShortToGnd    : short to ground error status
///           boShortToVba    : short to battery error status
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Diag_Handle_VCCx(void)
{
  //Step 1) Set pre - conditions
  CtrlPxl_Force_DefaultVccxState = FALSE;

  struct { teCtrlPxl_VccxLineState ucVccxState;   boolean boCommFault;   boolean boShortToGnd;   boolean boShortToVbat;   } asTestCaseData[]
    = { {             eMatrixVccx_noError    ,                FALSE  ,                 FALSE,                   FALSE ,   },   // no Vccx error
        {             eMatrixVccx_noError    ,                 TRUE  ,                 FALSE,                   FALSE ,   },   // no Vccx error, but faulty comm detected
        {             eMatrixVccx_Short2GND  ,                TRUE   ,                  TRUE,                   FALSE ,   },   // short to ground detected  AND comm. error 
        {             eMatrixVccx_Short2GND  ,                FALSE  ,                  TRUE,                   FALSE ,   },   // short to ground detected, but no comm. error
        {             eMatrixVccx_Short2Vbat ,                TRUE   ,                 FALSE,                   TRUE  ,   },   // short to vbat detected    AND comm. error 
        {             eMatrixVccx_Short2Vbat ,                FALSE  ,                 FALSE,                   TRUE  ,   },   // short to vbat detected,   but no comm. error
        {             eMatrixVccx_noError    ,                FALSE  ,                 FALSE,                   FALSE ,   },   // default state, no new errors set, only comm error
  };

  //Step 1) Set pre - conditions

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    CtrlPxl_sMatrixFault = (tsCtrlPxl_MatrixFaultStates) { FALSE, FALSE, FALSE, FALSE };

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sMatrixFault.boCommFault = asTestCaseData[ulIdx].boCommFault;
    Rte_Read_IoHwAbUser_VccxLineState_Param1 = asTestCaseData[ulIdx].ucVccxState;

    if (ulIdx == 6u) { CtrlPxl_Force_DefaultVccxState = TRUE; }   //force default state

    //Step 3) Call the FUT
    CtrlPxl_Diag_Handle_VCCx();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_sMatrixFault.boShortToGnd,    asTestCaseData[ulIdx].boShortToGnd,  ==);
    AL_UNITTEST_CHECK(CtrlPxl_sMatrixFault.boShortToVbat,   asTestCaseData[ulIdx].boShortToVbat, ==);
    AL_UNITTEST_CHECK(CtrlPxl_sMatrixFault.boShortToVbat,   asTestCaseData[ulIdx].boShortToVbat, ==);

  }

  //restore value
  CtrlPxl_Force_DefaultVccxState = FALSE;
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Diag_HandleMlcPxlFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_Diag_HandleMlcPxlFault
///                     handles pixel defect and goes through debounce mechanism when
///                     pixel defect is present
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucLedFault         :  matrix pixel fault status on bit ( 12 pixels)
///           ulTimer            :  timer value of system clock
///           ulCycleTimer       :  cycle time count
///
///       Expectations:
///           ulDefectTimer      : maturation defect timer value
///           boPxlError         :  pixel defect status
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Diag_HandleMlcPxlFault(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  //reset RTE port values
  for (uint8 ucIdx = 0u; ucIdx < CTRL_PXL_NUMBER_OF_MLC_CHIP; ucIdx++)
  {
    Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_Param1[ucIdx].unLedFault = 0x00u;
  }

  //reset timer
  ulPxlDefect_CycleTimer    = 0u;
  ulPxlDefect_GeneralTimer  = 0u;
  ulPxlDefect_Timer         = 0u;

  struct { uint16 ucLedFault;     uint32 ulTimer;  uint32 ulCycleTimer;   uint32 ulDefectTimer; boolean boPxlError; } asTestCaseData[]
    = {  {            0x0000u,                0u,                   0u,                    0u,          FALSE       },  // no pixel error detected
         {            0x00FFu,             1000u,               21000u,                   20u,          FALSE       },  // seq 1) pixel error detected, but not maturated
         {            0x00FFu,             1000u,              610000u,                  629u,          FALSE       },  // pixel error detected, timer incremented to maturation, next cycle error is set
         {            0x0000u,             1000u,              610000u,                    0u,          TRUE        },  // pixel error no more present, but timer exceeded -> set permanent error, reset timer and start detection again
         {            0x00FFu,                0u,              589000u,                  589u,          FALSE       },  // seq 2) pixel error detected, but not maturated
         {            0x00FFu,           100000u,              511000u,                 1000u,          FALSE       },  // pixel error detected, timer incremented to maturation, next cycle error is set
         {            0x00FFu,            10000u,               10000u,                 1000u,          TRUE        },  // pixel error still present, timer exceeded -> set permanent error, reset timer
         {            0x0000u,            20000u,               10000u,                    0u,          TRUE        },  // pixel error no more present, timer exceeded  (=1000)-> set permanent error, reset timer and start detection again
  };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CtrlPxl_sMatrixFault.boPxlFault = FALSE;
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_Param1[0].unLedFault = asTestCaseData[ucIdx].ucLedFault;
    CtrlPxl_pCodingArea->Sys.PxlDebounce.ucPixelFault_DebounceTime = 60u;

    // assign cycle time count of CtrlPxl module
    LPTMR0_GetTimeElapsed_RetVal  = asTestCaseData[ucIdx].ulCycleTimer;
    //assign timer value of system clock
    ulPxlDefect_GeneralTimer = asTestCaseData[ucIdx].ulTimer;

    //Step 3) Call the FUT
      CtrlPxl_Diag_HandleMlcPxlFault(); 

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
      AL_UNITTEST_CHECK(ulPxlDefect_Timer,            asTestCaseData[ucIdx].ulDefectTimer, == );
      AL_UNITTEST_CHECK(CtrlPxl_sMatrixFault.boPxlFault, asTestCaseData[ucIdx].boPxlError, == );
    }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Diag_HandleMlcCrcFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_Diag_HandleMlcCrcFault
///                     handles CRC defect and goes through debounce mechanism when
///                     corrupt comm defect is present
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucMlcChip          :  matrix chip index
///           boCrcErr           :  matrix crc fault status on a given chip index
///           ulTimer            :  timer value of system clock
///           ulCycleTimer       :  cycle time count
///
///       Expectations:
///           ulDefectTimer      : maturation defect timer value
///           boCrcFault         : crc defect status
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Diag_HandleMlcCrcFault(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  //reset RTE port values
  for (uint8 ucIdx = 0u; ucIdx < CTRL_PXL_NUMBER_OF_MLC_CHIP; ucIdx++)
  {
    Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1.aboMlcCorruptedComm[ucIdx] = 0x00u;
  }

  //reset timer
  ulCrcDefect_CycleTimer    = 0u;
  ulCrcDefect_GeneralTimer  = 0u;
  ulCrcDefect_Timer         = 0u;

  struct { uint8 ucMlcChip;   boolean boCrcErr;     uint32 ulTimer;  uint32 ulCycleTimer;   uint32 ulDefectTimer; boolean boCrcFault; } asTestCaseData[]
    = {  {              0u,             FALSE,                  0u,                   0u,                    0u,          FALSE       },  // no crc error detected
         {              1u,              TRUE,               1000u,               21000u,                   20u,          FALSE       },  // crc error detected, but not maturated
         {              0u,             FALSE,               1000u,              141000u,                  160u,          FALSE       },  // crc error still present, timer incremented to maturation, next cycle error is set
         {              1u,             FALSE,                100u,              141000u,                    0u,          TRUE        },  // crc error no more present, but timer exceeded -> set permanent error, reset timer and start detection again
  };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 1) Set pre - conditions
    CtrlPxl_sMatrixFault.boCrcFault = FALSE;
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1.aboMlcCorruptedComm[asTestCaseData[ucIdx].ucMlcChip] = asTestCaseData[ucIdx].boCrcErr;
    CtrlPxl_pCodingArea->Sys.PxlDebounce.ucCrcFault_DebounceTime = 14u;

    // assign cycle time count of CtrlPxl module
    LPTMR0_GetTimeElapsed_RetVal  = asTestCaseData[ucIdx].ulCycleTimer;
    //assign timer value of system clock
    ulCrcDefect_GeneralTimer = asTestCaseData[ucIdx].ulTimer;

    //Step 3) Call the FUT
     CtrlPxl_Diag_HandleMlcCrcFault();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
     AL_UNITTEST_CHECK(ulCrcDefect_Timer,            asTestCaseData[ucIdx].ulDefectTimer, == );
     AL_UNITTEST_CHECK(CtrlPxl_sMatrixFault.boCrcFault, asTestCaseData[ucIdx].boCrcFault, == );
    }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_Diag_HandleMlcComFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_Diag_HandleMlcComFault
///                     handles communication error and goes through debounce mechanism when
///                     comm. defect is present
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucCommFault        :  matrix communication fault status on bit (max. 8 MLCs)
///           ulTimer            :  timer value of system clock
///           ulCycleTimer       :  cycle time count
///
///       Expectations:
///           ulDefectTimer      : maturation defect timer value
///           boComFault         : comm defect status
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_Diag_HandleMlcComFault(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //reset timer
  ulComDefect_CycleTimer = 0u;
  ulComDefect_GeneralTimer = 0u;
  ulComDefect_Timer = 0u;

  struct {  uint8 ucComFault;     uint32 ulTimer;  uint32 ulCycleTimer;   uint32 ulDefectTimer; boolean boComFault; } asTestCaseData[]
    = {  {           0x00u,                  0u,                   0u,                    0u,          FALSE       },  // no comm error detected
         {           0xFFu,               1000u,               21000u,                   20u,          FALSE       },  // comm error detected, but not maturated
         {           0xFFu,               1000u,              141000u,                  160u,          FALSE       },  // comm error still present, timer incremented to maturation, next cycle error is set
         {           0x00u,                100u,              141000u,                    0u,          TRUE        },  // comm error no more present, but timer exceeded -> set permanent error, reset timer and start detection again
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_Param1.ucMlcStatus = asTestCaseData[ucIdx].ucComFault;
    CtrlPxl_pCodingArea->Sys.PxlDebounce.ucComFault_DebounceTime = 14u;

    // assign cycle time count of CtrlPxl module
    LPTMR0_GetTimeElapsed_RetVal = asTestCaseData[ucIdx].ulCycleTimer;
    //assign timer value of system clock
    ulComDefect_GeneralTimer = asTestCaseData[ucIdx].ulTimer;

    //Step 3) Call the FUT
    CtrlPxl_Diag_HandleMlcComFault();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(ulComDefect_Timer, asTestCaseData[ucIdx].ulDefectTimer, == );
    AL_UNITTEST_CHECK(CtrlPxl_sMatrixFault.boCommFault, asTestCaseData[ucIdx].boComFault, == );
  }
}

//-----------------------------------------------------------------------------
// CtrlPxl_MemHandling.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ProcessMatrixEEPROM
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the main eeprom function  CtrlPxl_ProcessMatrixEEPROM
///                     handles  memory state machine based on the  init state
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           boInitReady  : status of eeprom memory for diag usage
///           eMemoryState : current state of eeprom for the State Machine
///           boValidity : status of data validity
///
///       Expectations:
///           boDiagAllowed    : diagnose control status
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ProcessMatrixEEPROM(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  struct { boolean boInitReady;  teEEPromStates eMemoryState; boolean boDiagAllowed; }asTestCaseData[]
       = { {              TRUE,                 eEEProm_Init,                  TRUE  },
           {             FALSE,           eEEProm_CompareCRC,                 FALSE  },
         };

  
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = asTestCaseData[ucIdx].boInitReady;
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates                   = asTestCaseData[ucIdx].eMemoryState;

    //Step 3) Call the FUT
    CtrlPxl_ProcessMatrixEEPROM();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady, asTestCaseData[ucIdx].boDiagAllowed, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_HandleEEPromData_TestCase1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if function sends the initialization command for EEPROM when
///       the state machine is in the  eEEProm_Init case
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///         CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init
///         Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount = 0u
///
///    - Expected test results: 
///        - the state changes to waiting until callbacks are received
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait
///         Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1.pfnMatrixEECbkFail        = &CtrlPxl_MatrixEEClbkInit_Fail
///         Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1.pfnMatrixEECbkSuccess     = &CtrlPxl_MatrixEEClbkInit_Success
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_HandleEEPromData_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init;
  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount = 0u;

  //Step 3) Call the FUT
  CtrlPxl_HandleEEPromData();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates, eEEProm_Wait, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1.pfnMatrixEECbkFail,       &CtrlPxl_MatrixEEClbkInit_Fail, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1.pfnMatrixEECbkSuccess,    &CtrlPxl_MatrixEEClbkInit_Success, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount,                        1u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_HandleEEPromData_TestCase2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if function sends the command to read from EEPROM when
///       the state machine is in the  eEEProm_Read case. The RTE port must contain
///       the read command parameters
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: none
///         CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Read
///         CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.Data[0] = 0xFFu
///         CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.Data[255] = 0xFFu
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount = 0u
///
///    - Expected test results: 
///        - the state changes to waiting until callbacks are received
///         CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Wait
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.pucMatrixEEbuffer[0] = 0xFFu
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.pucMatrixEEbuffer[255] = 0xFFu
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEELength   = CTRL_PXL_EEPROM_SIZE
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEEStartAdd = CTRL_PXL_START_EEPROM_ADDRESS
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess        = &CtrlPxl_MtxEEClbkRead_Success
///         Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkFail           = &CtrlPxl_MtxEEClbkRead_Fail
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_HandleEEPromData_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Read;
  CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.Data[0]   = 0xFFu;
  CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.Data[255] = 0xFFu;
  Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount = 0u;

  //Step 3) Call the FUT
  CtrlPxl_HandleEEPromData();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates,                             eEEProm_Wait, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.pucMatrixEEbuffer[0],                                           0xFFu, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.pucMatrixEEbuffer[255],                                         0xFFu, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEELength,                                CTRL_PXL_EEPROM_SIZE, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.unMatrixEEStartAdd,                     CTRL_PXL_START_EEPROM_ADDRESS, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkSuccess,  CtrlPxl_MtxEEClbkRead_Success, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1.sMatrixEE0CbkFn.pfnMatrixEECbkFail,        CtrlPxl_MtxEEClbkRead_Fail, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_HandleEEPromData_TestCase3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test if function checks the CRC values from Eeprom and Nvm and sets eeprom fault status
///        TRUE if CRC has invalid value and does not proceed to save the data in Nvm
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_CompareCRC
///          CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.MatrixParam_Data.CrcPatternAndReservedGroup.sCrcPatterAndReserved.ucCrc = 0xFFu  //invalid CRC
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = FALSE
///          Rte_Write_CtrlPxl_Nvm_WriteData_HitCount = 0u
///
///    - Expected test results: 
///        - the state changes to finished because eeprom job is completed if it reached the CRC check
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_HandleEEPromData_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_CompareCRC;
  CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.MatrixParam_Data.CrcPatternAndReservedGroup.sCrcPatterAndReserved.ucCrc = 0xFFu;  //invalid CRC
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromChecksumFaultStatus = FALSE;
  Rte_Write_CtrlPxl_Nvm_WriteData_HitCount = 0u;

  //Step 3) Call the FUT
  CtrlPxl_HandleEEPromData();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates,     eEEProm_Finished, ==);
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromChecksumFaultStatus,   TRUE, ==);
  AL_UNITTEST_CHECK(CtrlPxl_CRC8_Eeprom,                                                                   0xFFu, ==);
  AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_Nvm_WriteData_HitCount,                                                 0u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_HandleEEPromData_TestCase4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test if function sets the Eeprom ready for diagnosis jobs when status Finished
///        is achieved in the State Machine
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
///    - Preconditions: 
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = FALSE
///
///    - Expected test results: 
///        - the state changes to finished because eeprom job is completed if it reached the CRC check
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished
///          CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_HandleEEPromData_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished;
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = FALSE;

  //Step 3) Call the FUT
  CtrlPxl_HandleEEPromData();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates,                   eEEProm_Finished, ==);
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady,             TRUE, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_HandleEEPromData_TestCase5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Check if function covers the empty cases from the State Machine
///        and sends no error status
///
///    - Test Design Technique:  - DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           eState : EEPROM current state
///
///       Expectations:
///        - boSendFault : eeprom fault status via RTE
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_HandleEEPromData_TestCase5(void)
{
  struct { teEEPromStates eState;  boolean boSendFault; } asTestCaseData[]
    =    { {        eEEProm_Write,               FALSE  },
           {         eEEProm_Wait,               FALSE  },
           {          eEEProm_All,               FALSE  },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus = FALSE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = asTestCaseData[ucIdx].eState;

    //Step 3) Call the FUT
    CtrlPxl_HandleEEPromData();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1.boEepromNoAccessFault, asTestCaseData[ucIdx].boSendFault, ==);
  } 
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_HandleEEPromData
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test the State Machine of Eeprom Handling
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_HandleEEPromData(void)
{
  Mt_CtrlPxl_HandleEEPromData_TestCase1();
  Mt_CtrlPxl_HandleEEPromData_TestCase2();
  Mt_CtrlPxl_HandleEEPromData_TestCase3();
  Mt_CtrlPxl_HandleEEPromData_TestCase4();
  Mt_CtrlPxl_HandleEEPromData_TestCase5();

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_ReadAndCheckNvMMatrixData
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: 
///        Test that the function check the CRC validity and based on it sends
///        the corresponding binning data
///
///    - Test Design Technique:  - DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucNvmCrc        : CRC from Nvm block data
///           ucNvmCalculated : CRC calculated over Nvm data
///           ucLedCh  : Led channel index
///
///    - Expected test results: 
///        - ucBinningClass : Binning Class value to be sent over RTE
///        - eBinQlty       : Binning sig. quality value to be sent over RTE
///        - Eeprom State shall be eEEProm_Init to start the State Machine 
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_ReadAndCheckNvMMatrixData(void)
{
  struct { uint8 ucNvmCrc;  uint8 ucNvmCalculated; uint8 ucLedCh;              uint8 ucBinningClass;   teRte_SigQty eBinQlty; } asTestCaseData[]
       = { {        0x00u,                 0x8Cu,             0u,      CTRL_PXL_CFG_BINNING_CLASS_0,                SIG_VALID  },
           {        0xFFu,                  0x0u,             5u,      CTRL_PXL_CFG_BINNING_CLASS_0,                SIG_VALID  },
           {        0x81u,                 0x81u,             11u,                               1u,                SIG_VALID  },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8 ucLedChIDx = asTestCaseData[ucIdx].ucLedCh;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sInternalHandling.sEepromHandling.sMtxEEPromMapping.uMtxEEPromMapping.MatrixParam_Data.CrcPatternAndReservedGroup.sCrcPatterAndReserved.ucCrc = asTestCaseData[ucIdx].ucNvmCrc;
    CtrlPxl_sInternalHandling.sEepromHandling.sCalibNvmDataUsed.aucBinningClass[ucLedChIDx] = asTestCaseData[ucIdx].ucBinningClass;
    Crc_CalculateCRC8H1D_RetVal = asTestCaseData[ucIdx].ucNvmCalculated;

    //Step 3) Call the FUT
    CtrlPxl_ReadAndCheckNvMMatrixData();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1[ucLedChIDx].eSigQty,         asTestCaseData[ucIdx].eBinQlty, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1[ucLedChIDx].ucBinning, asTestCaseData[ucIdx].ucBinningClass, == );
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates,                                 eEEProm_Init, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_MatrixEEClbkInit_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_MatrixEEClbkInit_Fail
///                     sets the correct attributes in case of failed initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init
///
///    - Expectations :
/// \output CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus = TRUE
/// \output CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Finished
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_MatrixEEClbkInit_Fail(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init;

  //Step 3) Call the FUT
  CtrlPxl_MatrixEEClbkInit_Fail();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus,             TRUE, ==);
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates, eEEProm_Finished, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_MatrixEEClbkInit_Success
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function  CtrlPxl_MatrixEEClbkInit_Success
///                     sets the correct attributes in case of successful initialization
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init
///
///    - Expectations :
/// \output CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Read
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_MatrixEEClbkInit_Success(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Init;

  //Step 3) Call the FUT
  CtrlPxl_MatrixEEClbkInit_Success();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates, eEEProm_Read, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_MtxEEClbkWrite_Success
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the main function  CtrlPxl_MtxEEClbkWrite_Success
///                     checks for diagnosis write mode and updates corresponding flags
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           boInitReady : status of eeprom memory for diag usage
///           boDiagWrite : diagnosis control status for writing
///
///    - Expected test results: 
///        - boDiagAllowed     : EEPROM  FLAG for diag control
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_MtxEEClbkWrite_Success(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  struct { boolean boInitReady;  boolean boDiagWrite;  boolean boDiagAllowed; }asTestCaseData[]
       = { {              TRUE,                 FALSE,                  FALSE  },
           {              TRUE,                  TRUE,                  FALSE  },
           {              FALSE,                 TRUE,                  TRUE   },
         };
  
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady                       = asTestCaseData[ucIdx].boInitReady;
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite   = asTestCaseData[ucIdx].boDiagWrite;

    //Step 3) Call the FUT
    CtrlPxl_MtxEEClbkWrite_Success();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite, asTestCaseData[ucIdx].boDiagAllowed, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_MtxEEClbkWrite_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the main function  CtrlPxl_MtxEEClbkWrite_Fail
///                     checks for diagnosis write mode, updates corresponding flags
///                      and sets the eeprom access error
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           boInitReady : status of eeprom memory for diag usage
///           boDiagWrite : diagnosis control status for writing
///
///    - Expected test results: 
///        - eEepromStates     : eeprom state after failed  callback is received
///        - boEepromAccessFaultStatus     : eeprom fault status 
///        - boDiagAllowed     : EEPROM  FLAG for diag control
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_MtxEEClbkWrite_Fail(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  struct { boolean boInitReady;  boolean boDiagWrite;  boolean boDiagAllowed; }asTestCaseData[]
       = { {              TRUE,                 FALSE,                  FALSE  },
           {              TRUE,                  TRUE,                  FALSE  },
           {              FALSE,                 TRUE,                  TRUE   },
         };
  
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady                       = asTestCaseData[ucIdx].boInitReady;
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite   = asTestCaseData[ucIdx].boDiagWrite;

    //Step 3) Call the FUT
    CtrlPxl_MtxEEClbkWrite_Fail();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite, asTestCaseData[ucIdx].boDiagAllowed, == );
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus,                                                                      TRUE, == );
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates,                                                          eEEProm_Finished, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_MtxEEClbkRead_Success
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the  function  CtrlPxl_MtxEEClbkRead_Success
///                     checks for diagnosis write and read request and sets the next state
///                     of EEPROM to jump in the State Machine
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           boInitReady : status of eeprom memory for diag usage
///           boDiagRead  : diagnosis control status for reading
///           boDiagWrite : diagnosis control status for writing
///
///    - Expected test results: 
///        - eEepromStates     : eeprom state after successfull callback is received
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_MtxEEClbkRead_Success(void)
{
  //Step 1) Set pre - conditions
  CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates = eEEProm_Read;  //the only state which allows the call of this function

  struct {    boolean boInitReady;   boolean boDiagRead;     boolean boDiagWrite;    teEEPromStates eEepromState;  }asTestCaseData[]
       = {  {                TRUE,                FALSE,                   FALSE,                     eEEProm_Read },  //eeprom can be used, no diag request
            {               FALSE,                FALSE,                    TRUE,               eEEProm_CompareCRC },  // eeprom not ready for diagnosis
            {                TRUE,                 TRUE,                   FALSE,                 eEEProm_Finished },  // Go to finish state, eeprom is ready to be read with diagnosis
            {                TRUE,                FALSE,                    TRUE,                     eEEProm_Wait },  // Go to Wait state, eeprom is waiting for callback
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = asTestCaseData[ucIdx].boInitReady;
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromRead = asTestCaseData[ucIdx].boDiagRead;
    CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite = asTestCaseData[ucIdx].boDiagWrite;

    //Step 3) Call the FUT
    CtrlPxl_MtxEEClbkRead_Success();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates, asTestCaseData[ucIdx].eEepromState, ==);
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_MtxEEClbkRead_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the main function  CtrlPxl_MtxEEClbkRead_Fail
///                     checks for diagnosis  mode, updates corresponding flags
///                     and sets the eeprom access error
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           boInitReady : status of eeprom memory for diag usage
///           boDiagCtrl  : diagnosis control status
///
///    - Expected test results: 
///        - eEepromState     : eeprom state after failed  callback is received
///        - boFault          : eeprom fault status 
///        - boDeactivateInit : EEPROM  FLAG for diag control
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_MtxEEClbkRead_Fail(void)
{

  struct { boolean boInitReady; boolean boDiagCtrl; teEEPromStates  eEepromState; boolean boFault; boolean boDeactivateInit; } asTestCaseData[]
    =    { {              TRUE,               TRUE,             eEEProm_Finished,             TRUE,                    FALSE },
           {              TRUE,              FALSE,             eEEProm_Finished,             TRUE,                     TRUE },
           {             FALSE,               TRUE,             eEEProm_Finished,             TRUE,                   FALSE  },
           {             FALSE,              FALSE,             eEEProm_Finished,             TRUE,                   FALSE  },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
     //Step 1) Set pre - conditions
     //Step 2) Assign all input values to the corresponding input variables identified in the FUT
      CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady = asTestCaseData[ucIdx].boInitReady;
      CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromRead  = asTestCaseData[ucIdx].boDiagCtrl;
      CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.sDiagControl.sDiagEEPromControlActive.boEEPromWrite = asTestCaseData[ucIdx].boDiagCtrl;
    
     //Step 3) Call the FUT
      CtrlPxl_MtxEEClbkRead_Fail();

     //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
      AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.eEEPromStates, asTestCaseData[ucIdx].eEepromState , == );
      AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromAccessFaultStatus, asTestCaseData[ucIdx].boFault,       == );
      AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boMatrixEEPromInitHandlingReady, asTestCaseData[ucIdx].boDeactivateInit,       == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_CompareEEPromAndNvmData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function  CtrlPxl_CompareEEPromAndNvmData
///                     checks the CRC values, handles the validity/invalidity of data
///                     and sets the eeprom access error status
///
///    - Test Design Technique: DT (Decision Table)
///
///    - DT- Info:
///       Inputs:
///           ucEepromCrc          : CRC from eeprom  data
///           ucNvmCrc             : CRC from Nvm data
///           ucCrcEeCalculated    : CRC calculated over eeprom data
///
///    - Expected test results: 
///        - boMemFault       : eeprom state after CRC values are checked
///        - ucRteAccess      : Rte accessed to copy Eeprom Data into Nvm 
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_CompareEEPromAndNvmData(void)
{

  struct { uint8 ucEepromCrc;   uint8 ucNvmCrc;  uint8 ucCrcEeCalculated; uint8 ucRteAccess;  boolean boMemFault; }asTestCaseData[]
    = {  {             0xFFu,            0xFFu,                    0x00u,                 0u,               TRUE  },    // no eeprom written
         {             0x40u,            0x81u,                    0x81u,                 0u,               TRUE  },    // eeprom changed
         {             0x81u,            0x80u,                    0x81u,                 1u,               TRUE  },    // eeprom valid, Nvm different
         {             0x81u,            0x81u,                    0x81u,                 0u,              FALSE  },    // eeprom == Nvm block
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    Rte_Write_CtrlPxl_Nvm_WriteData_HitCount = 0u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CtrlPxl_CRC8_Eeprom         = asTestCaseData[ucIdx].ucEepromCrc;
    CtrlPxl_CRC8_Nvm            = asTestCaseData[ucIdx].ucNvmCrc;
    Crc_CalculateCRC8H1D_RetVal = asTestCaseData[ucIdx].ucCrcEeCalculated;

    //Step 3) Call the FUT
    CtrlPxl_CompareEEPromAndNvmData();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(CtrlPxl_sInternalHandling.sEepromHandling.sEepromControl.boEepromChecksumFaultStatus, asTestCaseData[ucIdx].boMemFault, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlPxl_Nvm_WriteData_HitCount,                                            asTestCaseData[ucIdx].ucRteAccess, == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlPxl_CheckBrightness
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the birghtness values read from eeprom are in
///                     the accepted range 0..200. Otherwise, limit to the max
///                     value = 200 (0xC8)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Test_BrightnessData[] = BRIGHTNESS_VAL
///
///    - Expectations :
/// \output CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM1.Data[0]  = 0x64u
/// \output CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM2.Data[11] = 0xC8u
/// \output CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM8.Data[2]  = 0xC8u
/// \output CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM8.Data[3]  = 0x64u
///
//-----------------------------------------------------------------------------
void Mt_CtrlPxl_CheckBrightness(void)
{
  //Step 1) Set pre - conditions
  // create the memory section with the brightness values
#define BRIGHTNESS_VAL  { /* LMM1 */  0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM2 */  0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM3 */  0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM4 */  0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM5 */  0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xC8u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM6 */  0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM7 */  0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
                          /* LMM8 */  0xFFu, 0xFFu, 0xFFu, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0x64u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, \
  }

  uint8 Test_BrightnessData[] = BRIGHTNESS_VAL;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CtrlPxl_CheckBrightness_Param1 = &Test_BrightnessData[0];


  //Step 3) Call the FUT
  CtrlPxl_CheckBrightness(CtrlPxl_CheckBrightness_Param1);


  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM1.Data[0],  0x64u, ==);
  AL_UNITTEST_CHECK(CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM2.Data[11], 0xC8u, ==);
  AL_UNITTEST_CHECK(CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM8.Data[2],  0xC8u, ==);
  AL_UNITTEST_CHECK(CTRLPXL_EEPROM_MAPPING_FIELDS.LMMBrightnessAndReservedGroup.sLMMBrightness.LMM8.Data[3],  0x64u, ==);
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
  Mt_InitializeCodingData(eEcu_Undef); 
  //ctaaCtrlPxl.c
  ALUnitTest_AddFunction("Mt_CtrlPxl_riCtrlPxl_Init",                                 Mt_CtrlPxl_riCtrlPxl_Init);
  ALUnitTest_AddFunction("Mt_CtrlPxl_rpCtrlPxl_Cycle0",                               Mt_CtrlPxl_rpCtrlPxl_Cycle0);


  //CtrlPxl.c
  ALUnitTest_AddFunction("Mt_CtrlPxl_Init",                                           Mt_CtrlPxl_Init);
  ALUnitTest_AddFunction("Mt_CtrlPxl_ProcessIntensities",                             Mt_CtrlPxl_ProcessIntensities);
  ALUnitTest_AddFunction("Mt_CtrlPxl_Cycle0",                                         Mt_CtrlPxl_Cycle0);
  ALUnitTest_AddFunction("Mt_CtrlPxl_GetInternalHandlingStruct",                      Mt_CtrlPxl_GetInternalHandlingStruct);
 
 
  //CtrlPxl_Data.c
  ALUnitTest_AddFunction("Mt_CtrlPxl_CodingDataValidation",                           Mt_CtrlPxl_CodingDataValidation);
  ALUnitTest_AddFunction("Mt_CtrlPxl_ParaFct0",                                       Mt_CtrlPxl_ParaFct0);
  ALUnitTest_AddFunction("Mt_CtrlPxl_PxlMap",                                         Mt_CtrlPxl_PxlMap);
  ALUnitTest_AddFunction("Mt_CtrlPxl_Data_Matrix",                                    Mt_CtrlPxl_Data_Matrix);


  //CtrlPxl_RteAccess.c
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_Intensities_CPM",                  Mt_CtrlPxl_RteAccess_Get_Intensities_CPM);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_ECU_Side",                         Mt_CtrlPxl_RteAccess_Get_ECU_Side);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Read_EcuSide",                         Mt_CtrlPxl_RteAccess_Read_EcuSide);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_Coding",                           Mt_CtrlPxl_RteAccess_Get_Coding);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Set_MLC_EnableTransmission",           Mt_CtrlPxl_RteAccess_Set_MLC_EnableTransmission);
 // ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Set_MLC_DisableTransmission",          Mt_CtrlPxl_RteAccess_Set_MLC_DisableTransmission); //TODO: commented, as function is not deleted from implementation, only commented for this release - still under development
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Reset_MLCSettings",                    Mt_CtrlPxl_RteAccess_Reset_MLCSettings);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Set_MLCTgtPWMs",                       Mt_CtrlPxl_RteAccess_Set_MLCTgtPWMs);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_PxlErrorStatus",                   Mt_CtrlPxl_RteAccess_Get_PxlErrorStatus);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_CommErrorStatus",                  Mt_CtrlPxl_RteAccess_Get_CommErrorStatus);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_ResetErrorStatus",                 Mt_CtrlPxl_RteAccess_Get_ResetErrorStatus);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Write_MatrixFaultStatus",              Mt_CtrlPxl_RteAccess_Write_MatrixFaultStatus);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Read_VccxLineState",                   Mt_CtrlPxl_RteAccess_Read_VccxLineState);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_VccxState",                        Mt_CtrlPxl_RteAccess_Get_VccxState);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Get_MlcCrcError",                      Mt_CtrlPxl_RteAccess_Get_MlcCrcError);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Write_MlcErrors",                      Mt_CtrlPxl_RteAccess_Write_MlcErrors);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames",  Mt_CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames",       Mt_CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_MatrixEE_Init",                        Mt_CtrlPxl_RteAccess_MatrixEE_Init);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_ReadNvmMatrixData",                    Mt_CtrlPxl_RteAccess_ReadNvmMatrixData);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_MtxEE_Read",                           Mt_CtrlPxl_RteAccess_MtxEE_Read);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_MtxEE_Write",                          Mt_CtrlPxl_RteAccess_MtxEE_Write);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_ReadEntireMatrixData",                 Mt_CtrlPxl_RteAccess_ReadEntireMatrixData);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_WriteBinningClass",                    Mt_CtrlPxl_RteAccess_WriteBinningClass);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM",         Mt_CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM);
  ALUnitTest_AddFunction("Mt_CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus",            Mt_CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus);

  //CtrlPxl_Diag.c
  ALUnitTest_AddFunction("Mt_CtrlPxl_Diag_ErrorDetected",                             Mt_CtrlPxl_Diag_ErrorDetected);
  ALUnitTest_AddFunction("Mt_CtrlPxl_GetMtxFaults",                                   Mt_CtrlPxl_GetMtxFaults);
  ALUnitTest_AddFunction("Mt_CtrlPxl_Diag_Handle_VCCx",                               Mt_CtrlPxl_Diag_Handle_VCCx);
  ALUnitTest_AddFunction("Mt_CtrlPxl_Diag_HandleMlcPxlFault",                         Mt_CtrlPxl_Diag_HandleMlcPxlFault);
  ALUnitTest_AddFunction("Mt_CtrlPxl_Diag_HandleMlcCrcFault",                         Mt_CtrlPxl_Diag_HandleMlcCrcFault);
  ALUnitTest_AddFunction("Mt_CtrlPxl_Diag_HandleMlcComFault",                         Mt_CtrlPxl_Diag_HandleMlcComFault);

  //CtrlPxl_MemHandling.c
  ALUnitTest_AddFunction("Mt_CtrlPxl_ProcessMatrixEEPROM",                            Mt_CtrlPxl_ProcessMatrixEEPROM);
  ALUnitTest_AddFunction("Mt_CtrlPxl_HandleEEPromData",                               Mt_CtrlPxl_HandleEEPromData);
  ALUnitTest_AddFunction("Mt_CtrlPxl_ReadAndCheckNvMMatrixData",                      Mt_CtrlPxl_ReadAndCheckNvMMatrixData);
  ALUnitTest_AddFunction("Mt_CtrlPxl_MatrixEEClbkInit_Fail",                          Mt_CtrlPxl_MatrixEEClbkInit_Fail);
  ALUnitTest_AddFunction("Mt_CtrlPxl_MatrixEEClbkInit_Success",                       Mt_CtrlPxl_MatrixEEClbkInit_Success);
  ALUnitTest_AddFunction("Mt_CtrlPxl_MtxEEClbkWrite_Success",                         Mt_CtrlPxl_MtxEEClbkWrite_Success);
  ALUnitTest_AddFunction("Mt_CtrlPxl_MtxEEClbkWrite_Fail",                            Mt_CtrlPxl_MtxEEClbkWrite_Fail);
  ALUnitTest_AddFunction("Mt_CtrlPxl_MtxEEClbkRead_Success",                          Mt_CtrlPxl_MtxEEClbkRead_Success);
  ALUnitTest_AddFunction("Mt_CtrlPxl_MtxEEClbkRead_Fail",                             Mt_CtrlPxl_MtxEEClbkRead_Fail);
  ALUnitTest_AddFunction("Mt_CtrlPxl_CompareEEPromAndNvmData",                        Mt_CtrlPxl_CompareEEPromAndNvmData);
  ALUnitTest_AddFunction("Mt_CtrlPxl_CheckBrightness",                                Mt_CtrlPxl_CheckBrightness);

}


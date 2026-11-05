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
/// \brief Module test for CddSwi
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test module
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_DiagValid_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads coding valability
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_boCodingValid = 1u
/// \input  Cod_DiagValid_RetVal = 0u
///
/// - Expectations:
///
/// \output Cod_DiagValid_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_DiagValid_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_boCodingValid = 1u;
  Cod_DiagValid_RetVal = 0u;

  //Step 3) Call FUT

  Cod_DiagValid_RetVal = Cod_DiagValid();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_DiagValid_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS1Shor2GndThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Short to Ground threshould for HSS1 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_GND_THRESHOLD = 23u
/// \input  Cod_HSS1Shor2GndThr_RetVal                                    = 0u
///
/// - Expectations:
///
/// \output Cod_HSS1Shor2GndThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS1Shor2GndThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_GND_THRESHOLD = 23u;
  Cod_HSS1Shor2GndThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS1Shor2GndThr_RetVal = Cod_HSS1Shor2GndThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS1Shor2GndThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS1Shor2VbatThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Short to Vbat threshould for HSS1 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_UBAT_THRESHOLD = 23u
/// \input  Cod_HSS1Shor2VbatThr_RetVal                                    = 0u
///
/// - Expectations:
///
/// \output Cod_HSS1Shor2VbatThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS1Shor2VbatThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_SHORT_TO_UBAT_THRESHOLD = 23u;
  Cod_HSS1Shor2VbatThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS1Shor2VbatThr_RetVal = Cod_HSS1Shor2VbatThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS1Shor2VbatThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS1OpenLoadThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Open Load threshould for HSS1 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD = 23u
/// \input  Cod_HSS1OpenLoadThr_RetVal                                 = 0u
///
/// - Expectations:
///
/// \output Cod_HSS1OpenLoadThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS1OpenLoadThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD = 23u;
  Cod_HSS1OpenLoadThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS1OpenLoadThr_RetVal = Cod_HSS1OpenLoadThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS1OpenLoadThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS2Shor2GndThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Short to Ground threshould for HSS2 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_SHORT_TO_GND_THRESHOLD = 23u
/// \input  Cod_HSS2Shor2GndThr_RetVal                                    = 0u
///
/// - Expectations:
///
/// \output Cod_HSS2Shor2GndThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS2Shor2GndThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_SHORT_TO_GND_THRESHOLD = 23u;
  Cod_HSS2Shor2GndThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS2Shor2GndThr_RetVal = Cod_HSS2Shor2GndThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS2Shor2GndThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS2Shor2VbatThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Short to Vbat threshould for HSS2 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_SHORT_TO_UBAT_THRESHOLD = 23u
/// \input  Cod_HSS2Shor2VbatThr_RetVal                                    = 0u
///
/// - Expectations:
///
/// \output Cod_HSS2Shor2VbatThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS2Shor2VbatThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_SHORT_TO_UBAT_THRESHOLD = 23u;
  Cod_HSS2Shor2VbatThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS2Shor2VbatThr_RetVal = Cod_HSS2Shor2VbatThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS2Shor2VbatThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS2OpenLoadThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Open Load threshould for HSS2 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_OPEN_LOAD_THRESHOLD = 23u
/// \input  Cod_HSS2OpenLoadThr_RetVal                                 = 0u
///
/// - Expectations:
///
/// \output Cod_HSS2OpenLoadThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS2OpenLoadThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS2_OPEN_LOAD_THRESHOLD = 23u;
  Cod_HSS2OpenLoadThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS2OpenLoadThr_RetVal = Cod_HSS2OpenLoadThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS2OpenLoadThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS3Shor2GndThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Short to Ground threshould for HSS3 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_GND_THRESHOLD = 23u
/// \input  Cod_HSS3Shor2GndThr_RetVal                                    = 0u
///
/// - Expectations:
///
/// \output Cod_HSS3Shor2GndThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS3Shor2GndThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_GND_THRESHOLD = 23u;
  Cod_HSS3Shor2GndThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS3Shor2GndThr_RetVal = Cod_HSS3Shor2GndThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS3Shor2GndThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS3Shor2VbatThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Short to Vbat threshould for HSS3 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_UBAT_THRESHOLD = 23u
/// \input  Cod_HSS2Shor3VbatThr_RetVal                                    = 0u
///
/// - Expectations:
///
/// \output Cod_HSS2Shor3VbatThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS3Shor2VbatThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_SHORT_TO_UBAT_THRESHOLD = 23u;
  Cod_HSS3Shor2VbatThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS3Shor2VbatThr_RetVal = Cod_HSS3Shor2VbatThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS3Shor2VbatThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cod_HSS3OpenLoadThr_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads Open Load threshould for HSS3 from coding
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_OPEN_LOAD_THRESHOLD = 23u
/// \input  Cod_HSS3OpenLoadThr_RetVal                                 = 0u
///
/// - Expectations:
///
/// \output Cod_HSS3OpenLoadThr_RetVal = 23u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cod_HSS3OpenLoadThr_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS3_OPEN_LOAD_THRESHOLD = 23u;
  Cod_HSS3OpenLoadThr_RetVal                                    = 0u;

  //Step 3) Call FUT

  Cod_HSS3OpenLoadThr_RetVal = Cod_HSS3OpenLoadThr();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Cod_HSS3OpenLoadThr_RetVal, 23u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_ParaFct0_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi gets coding data
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_ParaFct0_Param1                                         = 1u
/// \input  CddSwi_Rou_ParaFct0_Param2.Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD  = 15u
/// \input  CddSwi_boCodingValid                                               = 0u
/// \input  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD         = 0u
///
/// - Expectations:
///
/// \output CddSwi_boCodingValid                                               = 1u
/// \output CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD         = 15u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_ParaFct0_Param1                                         = 1u;
  CddSwi_Rou_ParaFct0_Param2.Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD  = 15u;
  CddSwi_boCodingValid                                               = 0u;
  CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD         = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_ParaFct0(CddSwi_Rou_ParaFct0_Param1, &CddSwi_Rou_ParaFct0_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddSwi_boCodingValid,                                        1u, == );
  AL_UNITTEST_CHECK(CddSwi_pCodingArea->Fan1.HSS_DIAG.HSS1_OPEN_LOAD_THRESHOLD, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_ParaFct0_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi gets coding data
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_ParaFct0_Param1 = 0u
/// \input  CddSwi_boCodingValid       = 1u
///
/// - Expectations:
///
/// \output CddSwi_boCodingValid       = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_ParaFct0_Param1 = 0u;
  CddSwi_boCodingValid       = 1u;

  //Step 3) Call FUT

  CddSwi_Rou_ParaFct0(CddSwi_Rou_ParaFct0_Param1, &CddSwi_Rou_ParaFct0_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddSwi_boCodingValid,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_ParaFct0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi gets coding data
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_ParaFct0(void)
{
  Mt_CddSwi_Rou_ParaFct0_TestCase_1();
  Mt_CddSwi_Rou_ParaFct0_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Init_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the init functions for Vnd7140 and Vn7140 drivers
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_Init_Param1   = 5u
/// \input  CddVnd7140_Init_HitCount = 0u
/// \input  CddVn7140_Init_Param1    = 5u
/// \input  CddVn7140_Init_HitCount  = 0u
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState = eParaFct0_CodingDataValid
///
/// - Expectations:
///
/// \output CddVnd7140_Init_Param1   = 0u
/// \output CddVnd7140_Init_HitCount = 1u
/// \output CddVn7140_Init_Param1    = 0u
/// \output CddVn7140_Init_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Init_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  const tNvmPara_CodingArea Mt_CodingDummy = { 0u };

  CddVnd7140_Init_Param1   = 5u;
  CddVnd7140_Init_HitCount = 0u;
  CddVn7140_Init_Param1    = 5u;
  CddVn7140_Init_HitCount  = 0u;

  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy;
  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

  //Step 3) Call FUT

  CddSwi_Rou_Init();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_Init_Param1,     0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_Init_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_Param1,      0u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Cycle0_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the cycle functions for Vnd7140 and Vn7140 drivers
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_Cycle0_HitCount = 0u
/// \input  CddVn7140_Cycle0_HitCount  = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_Cycle0_HitCount = 1u
/// \output CddVn7140_Cycle0_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Cycle0_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVnd7140_Cycle0_HitCount = 0u;
  CddVn7140_Cycle0_HitCount  = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_Cycle0();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_Cycle0_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CddVn7140_Cycle0_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_DeInit_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the deinit functions for Vnd7140 and Vn7140 drivers
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_DeInit_Param1   = 5u
/// \input  CddVnd7140_DeInit_HitCount = 0u
/// \input  CddVn7140_DeInit_Param1    = 5u
/// \input  CddVn7140_DeInit_HitCount  = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_DeInit_Param1   = 0u
/// \output CddVnd7140_DeInit_HitCount = 1u
/// \output CddVn7140_DeInit_Param1    = 0u
/// \output CddVn7140_DeInit_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_DeInit_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVnd7140_DeInit_Param1   = 5u;
  CddVnd7140_DeInit_HitCount = 0u;
  CddVn7140_DeInit_Param1    = 5u;
  CddVn7140_DeInit_HitCount  = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_DeInit();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_DeInit_Param1,     0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_DeInit_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CddVn7140_DeInit_Param1,      0u, == );
  AL_UNITTEST_CHECK(CddVn7140_DeInit_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_SetTgt_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the set target function for Vnd7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_SetTgt_Param1   = 0u
/// \input  CddSwi_Rou_SetTgt_Param2   = 0x8000u
/// \input  CddVnd7140_SetTgt_Param1   = 10u
/// \input  CddVnd7140_SetTgt_Param2   = 10u
/// \input  CddVnd7140_SetTgt_Param3   = 10u
/// \input  CddVnd7140_SetTgt_HitCount = 0u
/// \input  CddVn7140_SetTgt_HitCount  = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_SetTgt_Param1   = 0u
/// \output CddVnd7140_SetTgt_Param2   = 0u
/// \output CddVnd7140_SetTgt_Param3   = 0x8000u
/// \output CddVnd7140_SetTgt_HitCount = 1u
/// \output CddVn7140_SetTgt_HitCount  = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_SetTgt_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_SetTgt_Param1   = 0u;
  CddSwi_Rou_SetTgt_Param2   = 0x8000u;
  CddVnd7140_SetTgt_Param1   = 10u;
  CddVnd7140_SetTgt_Param2   = 10u;
  CddVnd7140_SetTgt_Param3   = 10u;
  CddVnd7140_SetTgt_HitCount = 0u;
  CddVn7140_SetTgt_HitCount  = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_SetTgt(CddSwi_Rou_SetTgt_Param1, CddSwi_Rou_SetTgt_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param1,         0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param2,         0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param3,    0x8000u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,        0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_SetTgt_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the set target function for Vn7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_SetTgt_Param1   = 2u
/// \input  CddSwi_Rou_SetTgt_Param2   = 0x8000u
/// \input  CddVn7140_SetTgt_Param1    = 10u
/// \input  CddVn7140_SetTgt_Param2    = 10u
/// \input  CddVn7140_SetTgt_Param3    = 10u
/// \input  CddVn7140_SetTgt_HitCount  = 0u
/// \input  CddVnd7140_SetTgt_HitCount = 0u
///
/// - Expectations:
///
/// \output CddVn7140_SetTgt_Param1    = 0u
/// \output CddVn7140_SetTgt_Param2    = 2u
/// \output CddVn7140_SetTgt_Param3    = 0x8000u
/// \output CddVn7140_SetTgt_HitCount  = 1u
/// \output CddVnd7140_SetTgt_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_SetTgt_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_SetTgt_Param1   = 2u;
  CddSwi_Rou_SetTgt_Param2   = 0x8000u;
  CddVn7140_SetTgt_Param1    = 10u;
  CddVn7140_SetTgt_Param2    = 10u;
  CddVn7140_SetTgt_Param3    = 10u;
  CddVn7140_SetTgt_HitCount  = 0u;
  CddVnd7140_SetTgt_HitCount = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_SetTgt(CddSwi_Rou_SetTgt_Param1, CddSwi_Rou_SetTgt_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_SetTgt_Param1,          0u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_Param2,          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_Param3,     0x8000u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,        1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,       0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_SetTgt_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: TBD when Sbc will be called
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_SetTgt_Param1   = 3u
/// \input  CddSwi_Rou_SetTgt_Param2   = 0x8000u
/// \input  CddVn7140_SetTgt_HitCount  = 0u
/// \input  CddVnd7140_SetTgt_HitCount = 0u
///
/// - Expectations:
///
/// \output CddVn7140_SetTgt_HitCount  = 0u
/// \output CddVnd7140_SetTgt_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_SetTgt_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_SetTgt_Param1   = 3u;
  CddSwi_Rou_SetTgt_Param2   = 0x8000u;
  CddVn7140_SetTgt_HitCount  = 0u;
  CddVnd7140_SetTgt_HitCount = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_SetTgt(CddSwi_Rou_SetTgt_Param1, CddSwi_Rou_SetTgt_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,        0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,       0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_SetTgt_TestCase_4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: test if function goes to default state
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_SetTgt_Param1   = 3u
/// \input  CddSwi_Rou_SetTgt_Param2   = 0x8000u
/// \input  CddSwi_asRouteList[3u].eDrvTyp = 10u
/// \input  CddVn7140_SetTgt_HitCount  = 0u
/// \input  CddVnd7140_SetTgt_HitCount = 0u
///
/// - Expectations:
///
/// \output CddVn7140_SetTgt_HitCount  = 0u
/// \output CddVnd7140_SetTgt_HitCount = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_SetTgt_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_SetTgt_Param1       = 3u;
  CddSwi_Rou_SetTgt_Param2       = 0x8000u;
  CddSwi_asRouteList[3u].eDrvTyp = 10u;
  CddVn7140_SetTgt_HitCount      = 0u;
  CddVnd7140_SetTgt_HitCount     = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_SetTgt(CddSwi_Rou_SetTgt_Param1, CddSwi_Rou_SetTgt_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,        0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,       0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_SetTgt
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function goes to all states
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_SetTgt(void)
{
  Mt_CddSwi_Rou_SetTgt_TestCase_1();
  Mt_CddSwi_Rou_SetTgt_TestCase_2();
  Mt_CddSwi_Rou_SetTgt_TestCase_3();
  Mt_CddSwi_Rou_SetTgt_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_GetState_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi gets the switch status from Vnd7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_GetState_Param1                     = 0u
/// \input  CddVnd7140_GetState_Param1                     = 10u
/// \input  CddVnd7140_GetState_Param2                     = 10u
/// \input  CddVnd7140_GetState_HitCount                   = 0u
/// \input  CddVn7140_GetState_HitCount                    = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal            = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent        = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad       = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND      = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT     = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState           = 1u
/// \input  CddSwi_Rou_GetState_RetVal.unHssActVal         = 10u
/// \input  CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssHwState        = 10u
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_Param1                     = 0u
/// \output CddVnd7140_GetState_Param2                     = 0u
/// \output CddVnd7140_GetState_HitCount                   = 1u
/// \output CddVn7140_GetState_HitCount                    = 0u
/// \output CddSwi_Rou_GetState_RetVal.unHssActVal         = 1u
/// \output CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssHwState        = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_GetState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_GetState_Param1   = 0u;

  CddVnd7140_GetState_Param1   = 10u;
  CddVnd7140_GetState_Param2   = 10u;
  CddVnd7140_GetState_HitCount = 0u;
  CddVn7140_GetState_HitCount  = 0u;

  CddVnd7140_GetState_RetVal.unActVal            = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent        = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad       = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND      = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT     = 1u;
  CddVnd7140_GetState_RetVal.ucHwState           = 1u;

  CddSwi_Rou_GetState_RetVal.unHssActVal         = 10u;
  CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssHwState        = 10u;


  //Step 3) Call FUT

  CddSwi_Rou_GetState_RetVal = CddSwi_Rou_GetState(CddSwi_Rou_GetState_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                  0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                  0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                1u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                 0u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.unHssActVal,      1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.unHssActCurrent,  1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssShort2GND,   1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT,  1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssHwState,     1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_GetState_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi gets the switch status from Vn7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_GetState_Param1                     = 2u
/// \input  CddVn7140_GetState_Param1                      = 10u
/// \input  CddVn7140_GetState_Param2                      = 10u
/// \input  CddVn7140_GetState_HitCount                    = 0u
/// \input  CddVnd7140_GetState_HitCount                   = 0u
/// \input  CddVn7140_GetState_RetVal.unActVal             = 1u
/// \input  CddVn7140_GetState_RetVal.unActCurrent         = 1u
/// \input  CddVn7140_GetState_RetVal.ucErrOpenLoad        = 1u
/// \input  CddVn7140_GetState_RetVal.ucErrShort2GND       = 1u
/// \input  CddVn7140_GetState_RetVal.ucErrShort2VBAT      = 1u
/// \input  CddVn7140_GetState_RetVal.ucHwState            = 1u
/// \input  CddSwi_Rou_GetState_RetVal.unHssActVal         = 10u
/// \input  CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 10u
/// \input  CddSwi_Rou_GetState_RetVal.ucHssHwState        = 10u
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_Param1                     = 0u
/// \output CddVnd7140_GetState_Param2                     = 0u
/// \output CddVnd7140_GetState_HitCount                   = 1u
/// \output CddVn7140_GetState_HitCount                    = 0u
/// \output CddSwi_Rou_GetState_RetVal.unHssActVal         = 1u
/// \output CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 1u
/// \output CddSwi_Rou_GetState_RetVal.ucHssHwState        = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_GetState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_GetState_Param1   = 2u;

  CddVnd7140_GetState_Param1   = 10u;
  CddVnd7140_GetState_Param2   = 10u;
  CddVnd7140_GetState_HitCount = 0u;
  CddVn7140_GetState_HitCount  = 0u;

  CddVn7140_GetState_RetVal.unActVal             = 1u;
  CddVn7140_GetState_RetVal.unActCurrent         = 1u;
  CddVn7140_GetState_RetVal.ucErrOpenLoad        = 1u;
  CddVn7140_GetState_RetVal.ucErrShort2GND       = 1u;
  CddVn7140_GetState_RetVal.ucErrShort2VBAT      = 1u;
  CddVn7140_GetState_RetVal.ucHwState            = 1u;

  CddSwi_Rou_GetState_RetVal.unHssActVal         = 10u;
  CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssHwState        = 10u;


  //Step 3) Call FUT

  CddSwi_Rou_GetState_RetVal = CddSwi_Rou_GetState(CddSwi_Rou_GetState_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_GetState_Param1,                   0u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_Param2,                   2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                0u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.unHssActVal,      1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.unHssActCurrent,  1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssShort2GND,   1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT,  1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssHwState,     1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_GetState_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi does not get the switch status from Vn7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_GetState_Param1                     = 3u
/// \input  CddVn7140_GetState_HitCount                    = 0u
/// \input  CddVnd7140_GetState_HitCount                   = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_HitCount                   = 0u
/// \output CddVn7140_GetState_HitCount                    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_GetState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_GetState_Param1   = 3u;

  CddVnd7140_GetState_HitCount = 0u;
  CddVn7140_GetState_HitCount  = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_GetState_RetVal = CddSwi_Rou_GetState(CddSwi_Rou_GetState_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                 0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_GetState_TestCase_4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test eDrvTle94x1 case
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_GetState_Param1                     = 2u;
/// \input  CddSwi_asRouteList[2u].eDrvTyp                 = eDrvTle94x1
/// \input  IoHwAbUser_GetOutFctDiag_HitCount              = 0u;
/// \input  IoHwAbUser_GetOutFctDiag_Param1                = TRUE;
/// \input  CddSbc_GetPWM_HitCount                         = 0u;
/// \input  CddSbc_GetPWM_RetVal                           = 200u;
/// \input  CddSwi_Rou_GetState_RetVal.unHssActVal         = 10u;
/// \input  CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 10u;
/// \input  CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 10u;
/// \input  CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 10u;
/// \input  CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 10u;
///
/// - Expectations:
///
/// \output IoHwAbUser_GetOutFctDiag_HitCount,             = 1u
/// \output CddSbc_GetPWM_HitCount,                        = 1u
/// \output CddSwi_Rou_GetState_RetVal.unHssActVal,        = 200u
/// \output CddSwi_Rou_GetState_RetVal.unHssActCurrent,    = 0xFFFFu
/// \output CddSwi_Rou_GetState_RetVal.ucHssOpenLoad,      = 0u
/// \output CddSwi_Rou_GetState_RetVal.ucHssShort2GND,     = TRUE
/// \output CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT,    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_GetState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_GetState_Param1                     = 2u;
  CddSwi_asRouteList[2u].eDrvTyp                 = eDrvTle94x1;
  IoHwAbUser_GetOutFctDiag_HitCount              = 0u;
  IoHwAbUser_GetOutFctDiag_Param1                = TRUE;
  CddSbc_GetPWM_HitCount                         = 0u;
  CddSbc_GetPWM_RetVal                           = 200u;

  CddSwi_Rou_GetState_RetVal.unHssActVal         = 10u;
  CddSwi_Rou_GetState_RetVal.unHssActCurrent     = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssOpenLoad       = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssShort2GND      = 10u;
  CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT     = 10u;

  //Step 3) Call FUT

  CddSwi_Rou_GetState_RetVal = CddSwi_Rou_GetState(CddSwi_Rou_GetState_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_GetOutFctDiag_HitCount,               1u, == );
  AL_UNITTEST_CHECK(CddSbc_GetPWM_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.unHssActVal,        200u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.unHssActCurrent, 0xFFFFu, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssOpenLoad,        0u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssShort2GND,     TRUE, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_GetState_RetVal.ucHssShort2VBAT,   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_GetState
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi get correct switch status from Vn7140 driver
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_GetState(void)
{
  Mt_CddSwi_Rou_GetState_TestCase_1();
  Mt_CddSwi_Rou_GetState_TestCase_2();
  Mt_CddSwi_Rou_GetState_TestCase_3();
  Mt_CddSwi_Rou_GetState_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test eRte_eScrollingSatelite_On_Scrolling_Off case
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 0u;
/// \input  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1   = eRte_eScrollingSatelite_On_Scrolling_Off
/// \input  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 10u;
///
/// - Expectations:
///
/// \output Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 1u
/// \output CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 5000u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 0u;
  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1   = eRte_eScrollingSatelite_On_Scrolling_Off;
  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 10u;

  //Step 3) Call FUT

  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_RetVal = CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(&CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1,       5000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test eRte_eScrollingSatelite_On_Scrolling_On case
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 0u;
/// \input  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1   = eRte_eScrollingSatelite_On_Scrolling_On
/// \input  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 1u
/// \output CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 0u;
  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1   = eRte_eScrollingSatelite_On_Scrolling_On;
  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 10u;

  //Step 3) Call FUT

  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_RetVal = CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(&CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1,          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test eRte_eScrollingSatelite_On_Scrolling_Off case
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 0u;
/// \input  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1   = 5u
/// \input  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 10u;
///
/// - Expectations:
///
/// \output Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 1u
/// \output CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount = 0u;
  Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_Param1   = 5u;
  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1    = 10u;

  //Step 3) Call FUT

  CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_RetVal = CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(&CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Read_CtrlSwi_TgtValue_ScrollingSatelite_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_Param1,          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test all states case
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal(void)
{
  Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_1();
  Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_2();
  Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function returnes true when FUSA_DRV01_NAMES = 5u
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[1u] = 5u;
/// \input  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat         = FALSE
/// \input  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat        = FALSE
///
/// - Expectations:
///
/// \output CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat         = FALSE
/// \output CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat        = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[0u]                            = 5u;
  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat         = FALSE;
  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat          = FALSE;

  //Step 3) Call FUT

  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal = CddSwi_Rou_CheckScrollingSatellite_Status();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat,       TRUE, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat,        FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if function returnes true when FUSA_DRV01_NAMES = 7u
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[0u] = 7u;
/// \input  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat         = FALSE
/// \input  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat        = FALSE
///
/// - Expectations:
///
/// \output CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat         = TRUE
/// \output CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

    CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[0u]                    = 7u;
    CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat = FALSE;
    CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat  = FALSE;

  //Step 3) Call FUT

    CddSwi_Rou_CheckScrollingSatellite_Status_RetVal = CddSwi_Rou_CheckScrollingSatellite_Status();

  //Step 4) Check expected output value 

    AL_UNITTEST_CHECK(CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat, FALSE, == );
    AL_UNITTEST_CHECK(CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat,   TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if function returnes true when FUSA_DRV01_NAMES = 7u
///
/// - Preconditions:
///
/// \input  CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[0u] = 7u;
/// \input  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat         = FALSE
/// \input  CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat        = FALSE
///
/// - Expectations:
///
/// \output CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat         = TRUE
/// \output CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

    CddSwi_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[0u] = 2u;
    CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat = FALSE;
    CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat = FALSE;

    //Step 3) Call FUT

    CddSwi_Rou_CheckScrollingSatellite_Status_RetVal = CddSwi_Rou_CheckScrollingSatellite_Status();

    //Step 4) Check expected output value 

    AL_UNITTEST_CHECK(CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingDRLPresent_Stat, FALSE, == );
    AL_UNITTEST_CHECK(CddSwi_Rou_CheckScrollingSatellite_Status_RetVal.boScrollingTIPresent_Stat, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_CddSwi_Rou_CheckScrollingSatellite_Status
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test all states case
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_CheckScrollingSatellite_Status(void)
{
  Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_1();
  Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_2();
  Mt_CddSwi_Rou_CheckScrollingSatellite_Status_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_CddSwi_Rou_Read_Fan1_TgtVal_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads fan 1 request
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_Read_Fan1_TgtVal_Param1                     = 0u
/// \input  CddSwi_Rou_Read_Fan1_TgtVal_RetVal                     = 0u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                  = 1u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan1_RetVal                  = 1u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount                = 0u
///
/// - Expectations:
///
/// \output Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount                = 1u
/// \output CddSwi_Rou_Read_Fan1_TgtVal_RetVal                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Read_Fan1_TgtVal_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_Read_Fan1_TgtVal_Param1                     = 0u;
  CddSwi_Rou_Read_Fan1_TgtVal_RetVal                     = 0u;

  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                  = 1u;
  Rte_Read_CtrlSwi_TgtValue_Fan1_RetVal                  = 1u;
  Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount                = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_Read_Fan1_TgtVal_RetVal = CddSwi_Rou_Read_Fan1_TgtVal(&CddSwi_Rou_Read_Fan1_TgtVal_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Read_CtrlSwi_TgtValue_Fan1_HitCount,           1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_Read_Fan1_TgtVal_RetVal,                1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Read_Fan2_TgtVal_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads fan 2 request
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_Read_Fan2_TgtVal_Param1                     = 0u
/// \input  CddSwi_Rou_Read_Fan2_TgtVal_RetVal                     = 0u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                  = 1u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan2_RetVal                  = 1u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount                = 0u
///
/// - Expectations:
///
/// \output Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount                = 1u
/// \output CddSwi_Rou_Read_Fan2_TgtVal_RetVal                     = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Read_Fan2_TgtVal_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_Rou_Read_Fan2_TgtVal_Param1                     = 0u;
  CddSwi_Rou_Read_Fan2_TgtVal_RetVal                     = 0u;

  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                  = 1u;
  Rte_Read_CtrlSwi_TgtValue_Fan2_RetVal                  = 1u;
  Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount                = 0u;

  //Step 3) Call FUT

  CddSwi_Rou_Read_Fan2_TgtVal_RetVal = CddSwi_Rou_Read_Fan2_TgtVal(&CddSwi_Rou_Read_Fan2_TgtVal_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Read_CtrlSwi_TgtValue_Fan2_HitCount,           1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_Read_Fan2_TgtVal_RetVal,                1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Rou_Write_SwitchStatus_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi writes Switch state to RTE
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssHwState                  = 1u
/// \input  CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].unHssActVal                   = 1u
/// \input  CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].unHssActCurrent               = 1u
/// \input  CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssOpenLoad                 = 1u
/// \input  CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssShort2GND                = 1u
/// \input  CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssShort2VBAT               = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucHwState       = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].unActVal        = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].unActCurrent    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucErrOpenLoad   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucErrShort2GND  = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucErrShort2VBAT = 10u
/// \input  CddSwi_Rou_Write_SwitchStatus_RetVal                                      = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                                    = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                                      = 15u
///
/// - Expectations:
///
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount                                 = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 1u
/// \output CddSwi_Rou_Write_SwitchStatus_RetVal                                   = 15u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Rou_Write_SwitchStatus_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  for (uint8_least ucIdx = 0u; ucIdx < 3u; ucIdx++)
  {
    CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssHwState     = 1u;
    CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].unHssActVal      = 1u;
    CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].unHssActCurrent  = 1u;
    CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssOpenLoad    = 1u;
    CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssShort2GND   = 1u;
    CddSwi_Rou_Write_SwitchStatus_Param1[ucIdx].ucHssShort2VBAT  = 1u;
    Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucHwState       = 10u;
    Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].unActVal        = 10u;
    Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].unActCurrent    = 10u;
    Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucErrOpenLoad   = 10u;
    Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucErrShort2GND  = 10u;
    Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[ucIdx].ucErrShort2VBAT = 10u;
  }

  CddSwi_Rou_Write_SwitchStatus_RetVal                  = 0u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u;

  //Step 3) Call FUT

  CddSwi_Rou_Write_SwitchStatus_RetVal = CddSwi_Rou_Write_SwitchStatus(CddSwi_Rou_Write_SwitchStatus_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                                  1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,          1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,   1u, == );
  AL_UNITTEST_CHECK(CddSwi_Rou_Write_SwitchStatus_RetVal,                                   15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_SetTgt_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the set target function for Vnd7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_SetTgt_Param1       = 0u
/// \input  CddSwi_SetTgt_Param2       = 0x8000u
/// \input  CddVnd7140_SetTgt_Param1   = 10u
/// \input  CddVnd7140_SetTgt_Param2   = 10u
/// \input  CddVnd7140_SetTgt_Param3   = 10u
/// \input  CddVnd7140_SetTgt_HitCount = 0u
/// \input  CddVn7140_SetTgt_HitCount  = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_SetTgt_Param1   = 0u
/// \output CddVnd7140_SetTgt_Param2   = 0u
/// \output CddVnd7140_SetTgt_Param3   = 0x8000u
/// \output CddVnd7140_SetTgt_HitCount = 1u
/// \output CddVn7140_SetTgt_HitCount  = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_SetTgt_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_SetTgt_Param1       = 0u;
  CddSwi_SetTgt_Param2       = 0x8000u;
  CddVnd7140_SetTgt_Param1   = 10u;
  CddVnd7140_SetTgt_Param2   = 10u;
  CddVnd7140_SetTgt_Param3   = 10u;
  CddVnd7140_SetTgt_HitCount = 0u;
  CddVn7140_SetTgt_HitCount  = 0u;

  //Step 3) Call FUT

  CddSwi_SetTgt(CddSwi_SetTgt_Param1, CddSwi_SetTgt_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param1,         0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param2,         0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param3,    0x8000u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,        0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_DeInit_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi calls the deinit functions for Vnd7140 and Vn7140 drivers
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_DeInit_Param1   = 5u
/// \input  CddVnd7140_DeInit_HitCount = 0u
/// \input  CddVn7140_DeInit_Param1    = 5u
/// \input  CddVn7140_DeInit_HitCount  = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_DeInit_Param1   = 0u
/// \output CddVnd7140_DeInit_HitCount = 1u
/// \output CddVn7140_DeInit_Param1    = 0u
/// \output CddVn7140_DeInit_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_DeInit_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVnd7140_DeInit_Param1   = 5u;
  CddVnd7140_DeInit_HitCount = 0u;
  CddVn7140_DeInit_Param1    = 5u;
  CddVn7140_DeInit_HitCount  = 0u;

  //Step 3) Call FUT

  CddSwi_DeInit();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_DeInit_Param1,     0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_DeInit_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CddVn7140_DeInit_Param1,      0u, == );
  AL_UNITTEST_CHECK(CddVn7140_DeInit_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_GetState_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi gets the switch status from Vnd7140 driver
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_GetState_Param1                         = 0u
/// \input  CddVnd7140_GetState_Param1                     = 10u
/// \input  CddVnd7140_GetState_Param2                     = 10u
/// \input  CddVnd7140_GetState_HitCount                   = 0u
/// \input  CddVn7140_GetState_HitCount                    = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal            = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent        = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad       = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND      = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT     = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState           = 1u
/// \input  CddSwi_GetState_RetVal.unHssActVal             = 10u
/// \input  CddSwi_GetState_RetVal.unHssActCurrent         = 10u
/// \input  CddSwi_GetState_RetVal.ucHssOpenLoad           = 10u
/// \input  CddSwi_GetState_RetVal.ucHssShort2GND          = 10u
/// \input  CddSwi_GetState_RetVal.ucHssShort2VBAT         = 10u
/// \input  CddSwi_GetState_RetVal.ucHssHwState            = 10u
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_Param1                     = 0u
/// \output CddVnd7140_GetState_Param2                     = 0u
/// \output CddVnd7140_GetState_HitCount                   = 1u
/// \output CddVn7140_GetState_HitCount                    = 0u
/// \output CddSwi_GetState_RetVal.unHssActVal             = 1u
/// \output CddSwi_GetState_RetVal.unHssActCurrent         = 1u
/// \output CddSwi_GetState_RetVal.ucHssOpenLoad           = 1u
/// \output CddSwi_GetState_RetVal.ucHssShort2GND          = 1u
/// \output CddSwi_GetState_RetVal.ucHssShort2VBAT         = 1u
/// \output CddSwi_GetState_RetVal.ucHssHwState            = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_GetState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddSwi_GetState_Param1       = 0u;

  CddVnd7140_GetState_Param1   = 10u;
  CddVnd7140_GetState_Param2   = 10u;
  CddVnd7140_GetState_HitCount = 0u;
  CddVn7140_GetState_HitCount  = 0u;

  CddVnd7140_GetState_RetVal.unActVal            = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent        = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad       = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND      = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT     = 1u;
  CddVnd7140_GetState_RetVal.ucHwState           = 1u;

  CddSwi_GetState_RetVal.unHssActVal             = 10u;
  CddSwi_GetState_RetVal.unHssActCurrent         = 10u;
  CddSwi_GetState_RetVal.ucHssOpenLoad           = 10u;
  CddSwi_GetState_RetVal.ucHssShort2GND          = 10u;
  CddSwi_GetState_RetVal.ucHssShort2VBAT         = 10u;
  CddSwi_GetState_RetVal.ucHssHwState            = 10u;

  //Step 3) Call FUT

  CddSwi_GetState_RetVal = CddSwi_GetState(CddSwi_GetState_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                  0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                  0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                1u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                 0u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.unHssActVal,          1u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.unHssActCurrent,      1u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.ucHssOpenLoad,        1u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.ucHssShort2GND,       1u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.ucHssShort2VBAT,      1u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.ucHssHwState,         1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_GetState_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi does nothing when index is out of bound
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddSwi_GetState_Param1                         = 4u
/// \input  CddVnd7140_GetState_HitCount                   = 0u
/// \input  CddVn7140_GetState_HitCount                    = 0u
/// \input  CddSwi_GetState_RetVal.unHssActCurrent         = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_HitCount                   = 0u
/// \output CddVn7140_GetState_HitCount                    = 0u
/// \output CddSwi_GetState_RetVal.unHssActCurrent         = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_GetState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddSwi_GetState_Param1                 = 4u;
  CddVnd7140_GetState_HitCount           = 0u;
  CddVn7140_GetState_HitCount            = 0u;
  CddSwi_GetState_RetVal.unHssActCurrent = 0u;

  //Step 3) Call FUT

  CddSwi_GetState_RetVal = CddSwi_GetState(CddSwi_GetState_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                0u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                 0u, == );
  AL_UNITTEST_CHECK(CddSwi_GetState_RetVal.unHssActCurrent,      0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_GetState
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi get correct state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_GetState(void)
{
  Mt_CddSwi_GetState_TestCase_1();
  Mt_CddSwi_GetState_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Init_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi inits drivers and gets the state
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_Init_Param1                                = 5u
/// \input  CddVnd7140_Init_HitCount                              = 0u
/// \input  CddVn7140_Init_Param1                                 = 5u
/// \input  CddVn7140_Init_HitCount                               = 0u
/// \input  CddVnd7140_GetState_Param1                            = 10u
/// \input  CddVnd7140_GetState_Param2                            = 10u
/// \input  CddVnd7140_GetState_HitCount                          = 0u
/// \input  CddVn7140_GetState_HitCount                           = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                   = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                  = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState              = eParaFct0_CodingDataValid
/// \input  CddSwi_pCodingArea                                         = &Mt_CodingDummy
/// \input  CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME    = 8u
/// \input  CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled       = 1u
///
/// - Expectations:
///
/// \output CddVnd7140_Init_Param1                                = 0u
/// \output CddVnd7140_Init_HitCount                              = 1u
/// \output CddVn7140_Init_Param1                                 = 0u
/// \output CddVn7140_Init_HitCount                               = 1u
/// \output CddVnd7140_GetState_Param1                            = 0u
/// \output CddVnd7140_GetState_Param2                            = 1u
/// \output CddVnd7140_GetState_HitCount                          = 2u
/// \output CddVn7140_GetState_HitCount                           = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount                = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 1u
/// \output CddSwi_boFanActive                = TRUE
/// \output CddSwi_boHss3Active                = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  const tNvmPara_CodingArea Mt_CodingDummy = { 0u };

  CddVnd7140_Init_Param1                                = 5u;
  CddVnd7140_Init_HitCount                              = 0u;
  CddVn7140_Init_Param1                                 = 5u;
  CddVn7140_Init_HitCount                               = 0u;
  
  CddVnd7140_GetState_Param1                            = 10u;
  CddVnd7140_GetState_Param2                            = 10u;
  CddVnd7140_GetState_HitCount                          = 0u;
  CddVn7140_GetState_HitCount                           = 0u;

  CddVnd7140_GetState_RetVal.unActVal                   = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent               = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u;
  CddVnd7140_GetState_RetVal.ucHwState                  = 1u;
  
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u;

  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy;
  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

  CddSwi_pCodingArea = &Mt_CodingDummy;

  CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME = 8u;

  CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled = 1u;


  //Step 3) Call FUT

  CddSwi_Init();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_Init_Param1,                                0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_Init_HitCount,                              1u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_Param1,                                 0u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_HitCount,                               1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                            0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                            1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,  1u, == );
  AL_UNITTEST_CHECK(CddSwi_boFanActive,  TRUE, == );
  AL_UNITTEST_CHECK(CddSwi_boHss3Active,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Init_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi inits drivers and gets the state
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_Init_Param1                                = 5u
/// \input  CddVnd7140_Init_HitCount                              = 0u
/// \input  CddVn7140_Init_Param1                                 = 5u
/// \input  CddVn7140_Init_HitCount                               = 0u
/// \input  CddVnd7140_GetState_Param1                            = 10u
/// \input  CddVnd7140_GetState_Param2                            = 10u
/// \input  CddVnd7140_GetState_HitCount                          = 0u
/// \input  CddVn7140_GetState_HitCount                           = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                   = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                  = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState              = eParaFct0_CodingDataValid
/// \input  CddSwi_pCodingArea                                         = &Mt_CodingDummy
/// \input  CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME    = 8u + 1u
/// \input  CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled       = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_Init_Param1                                = 0u
/// \output CddVnd7140_Init_HitCount                              = 1u
/// \output CddVn7140_Init_Param1                                 = 0u
/// \output CddVn7140_Init_HitCount                               = 1u
/// \output CddVnd7140_GetState_Param1                            = 0u
/// \output CddVnd7140_GetState_Param2                            = 1u
/// \output CddVnd7140_GetState_HitCount                          = 2u
/// \output CddVn7140_GetState_HitCount                           = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount                = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 1u
/// \output CddSwi_boFanActive                = FALSE
/// \output CddSwi_boHss3Active                = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Init_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  const tNvmPara_CodingArea Mt_CodingDummy = { 0u };

  CddVnd7140_Init_Param1                                = 5u;
  CddVnd7140_Init_HitCount                              = 0u;
  CddVn7140_Init_Param1                                 = 5u;
  CddVn7140_Init_HitCount                               = 0u;
  
  CddVnd7140_GetState_Param1                            = 10u;
  CddVnd7140_GetState_Param2                            = 10u;
  CddVnd7140_GetState_HitCount                          = 0u;
  CddVn7140_GetState_HitCount                           = 0u;

  CddVnd7140_GetState_RetVal.unActVal                   = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent               = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u;
  CddVnd7140_GetState_RetVal.ucHwState                  = 1u;
  
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u;

  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy;
  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

  CddSwi_pCodingArea = &Mt_CodingDummy;

  CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME = 8u + 1u;
  CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled = 0u;

  //Step 3) Call FUT

  CddSwi_Init();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_Init_Param1,                                0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_Init_HitCount,                              1u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_Param1,                                 0u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_HitCount,                               1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                            0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                            1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,  1u, == );
  AL_UNITTEST_CHECK(CddSwi_boFanActive,  FALSE, == );
  AL_UNITTEST_CHECK(CddSwi_boHss3Active,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Init_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi inits drivers and gets the state
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_Init_Param1                                = 5u
/// \input  CddVnd7140_Init_HitCount                              = 0u
/// \input  CddVn7140_Init_Param1                                 = 5u
/// \input  CddVn7140_Init_HitCount                               = 0u
/// \input  CddVnd7140_GetState_Param1                            = 10u
/// \input  CddVnd7140_GetState_Param2                            = 10u
/// \input  CddVnd7140_GetState_HitCount                          = 0u
/// \input  CddVn7140_GetState_HitCount                           = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                   = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                  = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy
/// \input  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState              = eParaFct0_CodingDataValid
/// \input  CddSwi_pCodingArea                                         = &Mt_CodingDummy
/// \input  CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME    = 0u
/// \input  CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled       = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_Init_Param1                                = 0u
/// \output CddVnd7140_Init_HitCount                              = 1u
/// \output CddVn7140_Init_Param1                                 = 0u
/// \output CddVn7140_Init_HitCount                               = 1u
/// \output CddVnd7140_GetState_Param1                            = 0u
/// \output CddVnd7140_GetState_Param2                            = 1u
/// \output CddVnd7140_GetState_HitCount                          = 2u
/// \output CddVn7140_GetState_HitCount                           = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount                = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 1u
/// \output CddSwi_boFanActive                = FALSE
/// \output CddSwi_boHss3Active                = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Init_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  const tNvmPara_CodingArea Mt_CodingDummy = { 0u };

  CddVnd7140_Init_Param1 = 5u;
  CddVnd7140_Init_HitCount = 0u;
  CddVn7140_Init_Param1 = 5u;
  CddVn7140_Init_HitCount = 0u;

  CddVnd7140_GetState_Param1 = 10u;
  CddVnd7140_GetState_Param2 = 10u;
  CddVnd7140_GetState_HitCount = 0u;
  CddVn7140_GetState_HitCount = 0u;

  CddVnd7140_GetState_RetVal.unActVal = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT = 1u;
  CddVnd7140_GetState_RetVal.ucHwState = 1u;

  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal = 15u;

  Rte_Read_CodM_CddSwi_Para_Param1.psCodingParameters_Blocks = &Mt_CodingDummy;
  Rte_Read_CodM_CddSwi_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

  CddSwi_pCodingArea = &Mt_CodingDummy;

  CddSwi_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME = 0u;
  CddSwi_pCodingArea->Fan1.Fans_Presence.ucFan1Enabled = 0u;

  //Step 3) Call FUT

  CddSwi_Init();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_Init_Param1, 0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_Init_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_Param1, 0u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1, 0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2, 1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount, 2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT, 1u, == );
  AL_UNITTEST_CHECK(CddSwi_boFanActive, FALSE, == );
  AL_UNITTEST_CHECK(CddSwi_boHss3Active, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi inits drivers and gets the state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Init(void)
{
  Mt_CddSwi_Init_TestCase_1();
  Mt_CddSwi_Init_TestCase_2();
  Mt_CddSwi_Init_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cycle0_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads fans state, sets target value for HSS outputs,
///                        gets the switch state and writes it to RTE
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan1_Param                                    = 1u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan2_Param                                    = 1u
/// \input  CddVnd7140_SetTgt_Param1                                                = 10u
/// \input  CddVnd7140_SetTgt_Param2                                                = 10u
/// \input  CddVnd7140_SetTgt_Param3                                                = 10u
/// \input  CddVnd7140_SetTgt_HitCount                                              = 0u
/// \input  CddVn7140_SetTgt_HitCount                                               = 0u
/// \input  CddVnd7140_GetState_Param1                                              = 10u
/// \input  CddVnd7140_GetState_Param2                                              = 10u
/// \input  CddVnd7140_GetState_HitCount                                            = 0u
/// \input  CddVn7140_GetState_HitCount                                             = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                                     = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent                                 = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad                                = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND                               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT                              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                                    = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                                  = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                                    = 15u
/// \input  snHSS3_MinDutyCycle_ut                                                  = 1
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_HitCount                                            = 2u
/// \output CddVn7140_GetState_HitCount                                             = 1u
/// \output CddVnd7140_SetTgt_Param1                                                = 0u
/// \output CddVnd7140_SetTgt_Param2                                                = 1u
/// \output CddVnd7140_SetTgt_Param3                                                = 0x8000u
/// \output CddVnd7140_SetTgt_HitCount                                              = 2u
/// \output CddVn7140_SetTgt_HitCount                                               = 1u
/// \output CddVnd7140_GetState_Param1                                              = 0u
/// \output CddVnd7140_GetState_Param2                                              = 1u
/// \output CddVnd7140_GetState_HitCount                                            = 2u
/// \output CddVn7140_GetState_HitCount                                             = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount,                                 = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cycle0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                                   = 1u;
  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                                   = 1u; 
  CddVnd7140_SetTgt_Param1                                                = 10u;
  CddVnd7140_SetTgt_Param2                                                = 10u;
  CddVnd7140_SetTgt_Param3                                                = 10u;
  CddVnd7140_SetTgt_HitCount                                              = 0u;
  CddVn7140_SetTgt_HitCount                                               = 0u;
  
  CddVnd7140_GetState_Param1                                              = 10u;
  CddVnd7140_GetState_Param2                                              = 10u;
  CddVnd7140_GetState_HitCount                                            = 0u;
  CddVn7140_GetState_HitCount                                             = 0u;
  CddVnd7140_GetState_RetVal.unActVal                                     = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent                                 = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad                                = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND                               = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT                              = 1u;
  CddVnd7140_GetState_RetVal.ucHwState                                    = 1u;

  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                                  = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                                    = 15u;
  snHSS3_MinDutyCycle_ut                                                  = 1;

  //Step 3) Call FUT

  CddSwi_Cycle0();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param1,                              0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param2,                              1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param3,                         0x8000u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                            0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                            1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );

  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cycle0_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads fans state, sets target value for HSS outputs,
///                        gets the switch state and writes it to RTE
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                                   = 0u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                                   = 0u
/// \input  CddVnd7140_SetTgt_Param1                                                = 10u
/// \input  CddVnd7140_SetTgt_Param2                                                = 10u
/// \input  CddVnd7140_SetTgt_Param3                                                = 10u
/// \input  CddVnd7140_SetTgt_HitCount                                              = 0u
/// \input  CddVn7140_SetTgt_HitCount                                               = 0u
/// \input  CddVnd7140_GetState_Param1                                              = 10u
/// \input  CddVnd7140_GetState_Param2                                              = 10u
/// \input  CddVnd7140_GetState_HitCount                                            = 0u
/// \input  CddVn7140_GetState_HitCount                                             = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                                     = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent                                 = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad                                = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND                               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT                              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                                    = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                                  = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                                    = 15u
/// \input  snHSS3_MinDutyCycle_ut                                                  = -1
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_HitCount                                            = 2u
/// \output CddVn7140_GetState_HitCount                                             = 1u
/// \output CddVnd7140_SetTgt_Param1                                                = 0u
/// \output CddVnd7140_SetTgt_Param2                                                = 1u
/// \output CddVnd7140_SetTgt_Param3                                                = 0u
/// \output CddVnd7140_SetTgt_HitCount                                              = 2u
/// \output CddVn7140_SetTgt_HitCount                                               = 1u
/// \output CddVnd7140_GetState_Param1                                              = 0u
/// \output CddVnd7140_GetState_Param2                                              = 1u
/// \output CddVnd7140_GetState_HitCount                                            = 2u
/// \output CddVn7140_GetState_HitCount                                             = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount,                                 = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cycle0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                                   = 0u;
  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                                   = 0u; 
  CddVnd7140_SetTgt_Param1                                                = 10u;
  CddVnd7140_SetTgt_Param2                                                = 10u;
  CddVnd7140_SetTgt_Param3                                                = 10u;
  CddVnd7140_SetTgt_HitCount                                              = 0u;
  CddVn7140_SetTgt_HitCount                                               = 0u;
  
  CddVnd7140_GetState_Param1                                              = 10u;
  CddVnd7140_GetState_Param2                                              = 10u;
  CddVnd7140_GetState_HitCount                                            = 0u;
  CddVn7140_GetState_HitCount                                             = 0u;
  CddVnd7140_GetState_RetVal.unActVal                                     = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent                                 = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad                                = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND                               = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT                              = 1u;
  CddVnd7140_GetState_RetVal.ucHwState                                    = 1u;

  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState                          = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal                           = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent                       = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad                      = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND                     = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT                    = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                                  = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                                    = 15u;
  snHSS3_MinDutyCycle_ut = -1;

  //Step 3) Call FUT

  CddSwi_Cycle0();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param1,                              0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param2,                              1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param3,                              0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                            0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                            1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );

  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_Cycle0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads fans state, sets target value for HSS outputs,
///                        gets the switch state and writes it to RTE
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_Cycle0(void)
{
  Mt_CddSwi_Cycle0_TestCase_1();
  Mt_CddSwi_Cycle0_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_riCddSwi_Init_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi inits drivers and gets the state
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_Init_Param1                                = 5u
/// \input  CddVnd7140_Init_HitCount                              = 0u
/// \input  CddVn7140_Init_Param1                                 = 5u
/// \input  CddVn7140_Init_HitCount                               = 0u
/// \input  CddVnd7140_GetState_Param1                            = 10u
/// \input  CddVnd7140_GetState_Param2                            = 10u
/// \input  CddVnd7140_GetState_HitCount                          = 0u
/// \input  CddVn7140_GetState_HitCount                           = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                   = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                  = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u
///
/// - Expectations:
///
/// \output CddVnd7140_Init_Param1                                = 0u
/// \output CddVnd7140_Init_HitCount                              = 1u
/// \output CddVn7140_Init_Param1                                 = 0u
/// \output CddVn7140_Init_HitCount                               = 1u
/// \output CddVnd7140_GetState_Param1                            = 0u
/// \output CddVnd7140_GetState_Param2                            = 1u
/// \output CddVnd7140_GetState_HitCount                          = 2u
/// \output CddVn7140_GetState_HitCount                           = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount                = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_riCddSwi_Init_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVnd7140_Init_Param1                                = 5u;
  CddVnd7140_Init_HitCount                              = 0u;
  CddVn7140_Init_Param1                                 = 5u;
  CddVn7140_Init_HitCount                               = 0u;
  
  CddVnd7140_GetState_Param1                            = 10u;
  CddVnd7140_GetState_Param2                            = 10u;
  CddVnd7140_GetState_HitCount                          = 0u;
  CddVn7140_GetState_HitCount                           = 0u;

  CddVnd7140_GetState_RetVal.unActVal                   = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent               = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad              = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND             = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT            = 1u;
  CddVnd7140_GetState_RetVal.ucHwState                  = 1u;
  
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState        = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal         = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent     = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad    = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND   = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT  = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                  = 15u;

  //Step 3) Call FUT

  riCddSwi_Init();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_Init_Param1,                                0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_Init_HitCount,                              1u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_Param1,                                 0u, == );
  AL_UNITTEST_CHECK(CddVn7140_Init_HitCount,                               1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                            0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                            1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSwi_rpCddSwi_Cycle0_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if CddSwi reads fans state, sets target value for HSS outputs,
///                        gets the switch state and writes it to RTE
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                                   = 1u
/// \input  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                                   = 1u
/// \input  CddVnd7140_SetTgt_Param1                                                = 10u
/// \input  CddVnd7140_SetTgt_Param2                                                = 10u
/// \input  CddVnd7140_SetTgt_Param3                                                = 10u
/// \input  CddVnd7140_SetTgt_HitCount                                              = 0u
/// \input  CddVn7140_SetTgt_HitCount                                               = 0u
/// \input  CddVnd7140_GetState_Param1                                              = 10u
/// \input  CddVnd7140_GetState_Param2                                              = 10u
/// \input  CddVnd7140_GetState_HitCount                                            = 0u
/// \input  CddVn7140_GetState_HitCount                                             = 0u
/// \input  CddVnd7140_GetState_RetVal.unActVal                                     = 1u
/// \input  CddVnd7140_GetState_RetVal.unActCurrent                                 = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrOpenLoad                                = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2GND                               = 1u
/// \input  CddVnd7140_GetState_RetVal.ucErrShort2VBAT                              = 1u
/// \input  CddVnd7140_GetState_RetVal.ucHwState                                    = 1u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 10u
/// \input  Rte_Write_CddSwi_SwitchStatus_HitCount                                  = 0u
/// \input  Rte_Write_CddSwi_SwitchStatus_RetVal                                    = 15u
///
/// - Expectations:
///
/// \output CddVnd7140_GetState_HitCount                                            = 2u
/// \output CddVn7140_GetState_HitCount                                             = 1u
/// \output CddVnd7140_SetTgt_Param1                                                = 0u
/// \output CddVnd7140_SetTgt_Param2                                                = 1u
/// \output CddVnd7140_SetTgt_Param3                                                = 0x8000u
/// \output CddVnd7140_SetTgt_HitCount                                              = 2u
/// \output CddVn7140_SetTgt_HitCount                                               = 1u
/// \output CddVnd7140_GetState_Param1                                              = 0u
/// \output CddVnd7140_GetState_Param2                                              = 1u
/// \output CddVnd7140_GetState_HitCount                                            = 2u
/// \output CddVn7140_GetState_HitCount                                             = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_HitCount,                                 = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 1u
/// \output Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddSwi_rpCddSwi_Cycle0_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Rte_Read_CtrlSwi_TgtValue_Fan1_Param1                                   = 1u;
  Rte_Read_CtrlSwi_TgtValue_Fan2_Param1                                   = 1u; 
  CddVnd7140_SetTgt_Param1                                                = 10u;
  CddVnd7140_SetTgt_Param2                                                = 10u;
  CddVnd7140_SetTgt_Param3                                                = 10u;
  CddVnd7140_SetTgt_HitCount                                              = 0u;
  CddVn7140_SetTgt_HitCount                                               = 0u;
  
  CddVnd7140_GetState_Param1                                              = 10u;
  CddVnd7140_GetState_Param2                                              = 10u;
  CddVnd7140_GetState_HitCount                                            = 0u;
  CddVn7140_GetState_HitCount                                             = 0u;
  CddVnd7140_GetState_RetVal.unActVal                                     = 1u;
  CddVnd7140_GetState_RetVal.unActCurrent                                 = 1u;
  CddVnd7140_GetState_RetVal.ucErrOpenLoad                                = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2GND                               = 1u;
  CddVnd7140_GetState_RetVal.ucErrShort2VBAT                              = 1u;
  CddVnd7140_GetState_RetVal.ucHwState                                    = 1u;

  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState         = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal          = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent      = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad     = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND    = 10u;
  Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT   = 10u;
  Rte_Write_CddSwi_SwitchStatus_HitCount                                  = 0u;
  Rte_Write_CddSwi_SwitchStatus_RetVal                                    = 15u;

  //Step 3) Call FUT

  rpCddSwi_Cycle0();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param1,                              0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param2,                              1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_Param3,                         0x8000u, == );
  AL_UNITTEST_CHECK(CddVnd7140_SetTgt_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(CddVn7140_SetTgt_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param1,                            0u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_Param2,                            1u, == );
  AL_UNITTEST_CHECK(CddVnd7140_GetState_HitCount,                          2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_HitCount,                           1u, == );

  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActVal,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].unActCurrent,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrOpenLoad,    1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2GND,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucErrShort2VBAT,  1u, == );
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
  CddSwi_Rou_ParaFct0(1, &CddSwi_pCodingArea);
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_DiagValid_TestCase",                                  Mt_CddSwi_Cod_DiagValid_TestCase                            );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS1Shor2GndThr_TestCase",                            Mt_CddSwi_Cod_HSS1Shor2GndThr_TestCase                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS1Shor2VbatThr_TestCase",                           Mt_CddSwi_Cod_HSS1Shor2VbatThr_TestCase                     );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS1OpenLoadThr_TestCase",                            Mt_CddSwi_Cod_HSS1OpenLoadThr_TestCase                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS2Shor2GndThr_TestCase",                            Mt_CddSwi_Cod_HSS2Shor2GndThr_TestCase                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS2Shor2VbatThr_TestCase",                           Mt_CddSwi_Cod_HSS2Shor2VbatThr_TestCase                     );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS2OpenLoadThr_TestCase",                            Mt_CddSwi_Cod_HSS2OpenLoadThr_TestCase                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS3Shor2GndThr_TestCase",                            Mt_CddSwi_Cod_HSS3Shor2GndThr_TestCase                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS3Shor2VbatThr_TestCase",                           Mt_CddSwi_Cod_HSS3Shor2VbatThr_TestCase                     );
  ALUnitTest_AddFunction("Mt_CddSwi_Cod_HSS3OpenLoadThr_TestCase",                            Mt_CddSwi_Cod_HSS3OpenLoadThr_TestCase                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_ParaFct0",                                            Mt_CddSwi_Rou_ParaFct0                                      );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_Init_TestCase",                                       Mt_CddSwi_Rou_Init_TestCase                                 );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_Cycle0_TestCase",                                     Mt_CddSwi_Rou_Cycle0_TestCase                               );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_DeInit_TestCase",                                     Mt_CddSwi_Rou_DeInit_TestCase                               );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_SetTgt",                                              Mt_CddSwi_Rou_SetTgt                                        );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_Read_Fan1_TgtVal_TestCase",                           Mt_CddSwi_Rou_Read_Fan1_TgtVal_TestCase                     );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_Read_Fan2_TgtVal_TestCase",                           Mt_CddSwi_Rou_Read_Fan2_TgtVal_TestCase                     );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_Write_SwitchStatus_TestCase",                         Mt_CddSwi_Rou_Write_SwitchStatus_TestCase                   );
  ALUnitTest_AddFunction("Mt_CddSwi_Init",                                                    Mt_CddSwi_Init                                              );
  ALUnitTest_AddFunction("Mt_CddSwi_Cycle0",                                                  Mt_CddSwi_Cycle0                                            );
  ALUnitTest_AddFunction("Mt_CddSwi_SetTgt_TestCase",                                         Mt_CddSwi_SetTgt_TestCase                                   );
  ALUnitTest_AddFunction("Mt_CddSwi_GetState",                                                Mt_CddSwi_GetState                                          );
  ALUnitTest_AddFunction("Mt_CddSwi_DeInit_TestCase",                                         Mt_CddSwi_DeInit_TestCase                                   );
  ALUnitTest_AddFunction("Mt_CddSwi_riCddSwi_Init_TestCase",                                  Mt_CddSwi_riCddSwi_Init_TestCase                            );
  ALUnitTest_AddFunction("Mt_CddSwi_rpCddSwi_Cycle0_TestCase",                                Mt_CddSwi_rpCddSwi_Cycle0_TestCase                          );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal",                     Mt_CddSwi_Rou_Read_Ti_PosDrl_Scrolling_TgtVal               );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_CheckScrollingSatellite_Status",                      Mt_CddSwi_Rou_CheckScrollingSatellite_Status                );
  ALUnitTest_AddFunction("Mt_CddSwi_Rou_GetState",                                            Mt_CddSwi_Rou_GetState                                      );
}
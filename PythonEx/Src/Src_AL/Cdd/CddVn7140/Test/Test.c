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
/// \brief Module test for CddVn7140
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
/// \Test Case : Mt_CddVn7140_Init_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function initializes hardware ports when EFT data is available
///                        and sets the hardware state for CddVn7140 as supported
/// - Preconditions:
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// \input  CddVn7140_Init_Param1                   = 0u
/// \input  CddVn7140_boEftValid                    = TRUE
/// \input  Cod_DiagValid_HitCount                  = 0u
/// \input  Cod_DiagValid_RetVal                    = TRUE
/// \input  IoHwAbUser_SetHss_Sen_Param1            = FALSE
/// \input  IoHwAbUser_SetHss_Sen_HitCount          = 0u
/// \input  CddVn7140_asStates[0].ucHwState         = 0u
/// \input  CddVn7140_boHssSupport[0]               = TRUE
/// \input  CDDVN7140_ECUVARCFG_aHSS_Type_RetVal    = 1u
///
/// - Expectations:
///
/// \output Cod_DiagValid_HitCount                  = 1u
/// \output IoHwAbUser_SetHss_Sen_Param1            = TRUE
/// \output IoHwAbUser_SetHss_Sen_HitCount          = 1u
/// \output CddVn7140_asStates[0].ucHwState         = 2u (CDDVN7140_CFG_HSS_SUPPORT)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_Init_Param1                  = 0u;
  CddVn7140_boEftValid                   = TRUE;
  Cod_DiagValid_HitCount                 = 0u;
  Cod_DiagValid_RetVal                   = TRUE;

  IoHwAbUser_SetHss_Sen_Param1           = FALSE;
  IoHwAbUser_SetHss_Sen_HitCount         = 0u;

  CddVn7140_asStates[0].ucHwState        = 0u;
  CddVn7140_boHssSupport[0]              = TRUE;
  CDDVN7140_ECUVARCFG_aHSS_Type_RetVal   = 1u;

  //Step 3) Call FUT

  CddVn7140_Init(CddVn7140_Init_Param1);

  //Step 4) Check expected output value 
  
  AL_UNITTEST_CHECK(Cod_DiagValid_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_Sen_Param1,          TRUE, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_Sen_HitCount,          1u, == );

  AL_UNITTEST_CHECK(CddVn7140_asStates[0].ucHwState,         2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Init_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function initializes hardware ports when EFT data is available
///                        and sets the hardware state for CddVn7140 as not supported
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_boEftValid                   = TRUE
/// \input  Cod_DiagValid_HitCount                  = 0u
/// \input  Cod_DiagValid_RetVal                    = TRUE
/// \input  IoHwAbUser_SetHss_Sen_Param1            = FALSE
/// \input  IoHwAbUser_SetHss_Sen_HitCount          = 0u
/// \input  CddVnd7140_asStates[0].ucHwState        = 0u
/// \input  CddVn7140_boHssSupport[0]               = FALSE
///
/// - Expectations:
///
/// \output Cod_DiagValid_HitCount                  = 1u
/// \output IoHwAbUser_SetHss_Sen_Param1            = TRUE
/// \output IoHwAbUser_SetHss_Sen_HitCount          = 1u
/// \output CddVnd7140_asStates[0].ucHwState          = 3u (CDDVN7140_CFG_HSS_NOSUPPORT)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Init_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_boEftValid                   = TRUE;
  Cod_DiagValid_HitCount                 = 0u;
  Cod_DiagValid_RetVal                   = TRUE;

  IoHwAbUser_SetHss_Sen_Param1           = FALSE;
  IoHwAbUser_SetHss_Sen_HitCount         = 0u;

  CddVn7140_asStates[0].ucHwState        = 0u;
  CddVn7140_boHssSupport[0]              = FALSE;

  //Step 3) Call FUT

  CddVn7140_Init(CddVn7140_Init_Param1);

  //Step 4) Check expected output value 
  
  AL_UNITTEST_CHECK(Cod_DiagValid_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_Sen_Param1,          TRUE, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_Sen_HitCount,          1u, == );

  AL_UNITTEST_CHECK(CddVn7140_asStates[0].ucHwState,         3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Init_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not initializes hardware ports 
///                        when EFT data is not available
///                        and sets the hardware state for CddVnd7140 as no EFT
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_Init_Param1                  = 0u
/// \input  CddVn7140_boEftValid                   = FALSE
/// \input  Cod_DiagValid_HitCount                 = 0u
/// \input  Cod_DiagValid_RetVal                   = FALSE
/// \input  IoHwAbUser_SetHss_Sen_HitCount         = 0u
/// \input  CddVn7140_asStates[0].ucHwState        = 0u
///
/// - Expectations:
///
/// \output Cod_DiagValid_HitCount                 = 1u
/// \output IoHwAbUser_SetHss_Sen_HitCount         = 0u
/// \output CddVn7140_asStates[0].ucHwState        = 1u (HSS_NOEFT)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Init_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_Init_Param1                  = 0u;
  CddVn7140_boEftValid                   = FALSE;
  Cod_DiagValid_HitCount                 = 0u;
  Cod_DiagValid_RetVal                   = FALSE;

  IoHwAbUser_SetHss_Sen_HitCount         = 0u;

  CddVn7140_asStates[0].ucHwState          = 0u;

  //Step 3) Call FUT

  CddVn7140_Init(CddVn7140_Init_Param1);

  //Step 4) Check expected output value 
  
  AL_UNITTEST_CHECK(Cod_DiagValid_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_Sen_HitCount,          0u, == );

  AL_UNITTEST_CHECK(CddVn7140_asStates[0].ucHwState,           1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Init
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not initializes hardware ports 
///                        when EFT data is not available
///                        and sets the hardware state for CddVnd7140 as no EFT
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Init(void)
{
  Mt_CddVn7140_Init_TestCase_1();
  Mt_CddVn7140_Init_TestCase_2();
  Mt_CddVn7140_Init_TestCase_3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Cycle0_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the diagnose value and
///                        checks all errors
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_boEftValid                 = 1u
/// \input  CddVn7140_asStates[0u].ucHwState       = 2u
/// \input  CddVn7140_asStates[0u].unDiagVal       = 0u
/// \input  CddVn7140_asStates[0u].unCurrent       = 0u
/// \input  CddVn7140_unCurrentRsens               = 1u
/// \input  IoHwAbUser_GetHss0Sense_HitCount     = 0u
/// \input  IoHwAbUser_GetHss0Sense_Param1       = 3000u
/// \input  CddVn7140_asStates[0u].unTgtVal        = 0x8000u
/// \input  CddVn7140_aunOpenLoadThreshold[0u]     = 2000u
/// \input  CddVn7140_aunShort2GndThreshold[0u]    = 4000u
/// \input  CddVn7140_aunShort2VbatThreshold[0u]   = 4000u
/// \input  CddVn7140_asStates[0u].ucErrOpenload   = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2GND  = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss0Sense_HitCount     = 1u
/// \output CddVn7140_asStates[0u].unDiagVal       = 3000u
/// \output CddVn7140_asStates[0u].unCurrent       = 1153u
/// \output CddVn7140_asStates[0u].ucErrOpenload   = 2u
/// \output CddVn7140_asStates[0u].ucErrShort2GND  = 2u
/// \output CddVn7140_asStates[0u].ucErrShort2VBAT = 2u (No error)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Cycle0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_boEftValid                 = 1u;
  CddVn7140_asStates[0u].ucHwState       = 2u;
  CddVn7140_asStates[0u].unDiagVal       = 0u;
  CddVn7140_asStates[0u].unCurrent       = 0u;
  CddVn7140_unCurrentRsens               = 1u;

  IoHwAbUser_GetHss0Sense_HitCount      = 0u;
  IoHwAbUser_GetHss0Sense_Param1        = 3000u;
  
  CddVn7140_asStates[0u].unTgtVal        = 0x8000u;
  CddVn7140_aunOpenLoadThreshold[0u]     = 2000u;
  CddVn7140_aunShort2GndThreshold[0u]    = 4000u;
  CddVn7140_aunShort2VbatThreshold[0u]   = 4000u;
  CddVn7140_asStates[0u].ucErrOpenload   = 5u;
  CddVn7140_asStates[0u].ucErrShort2GND  = 5u;
  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u;

  //Step 3) Call FUT

  CddVn7140_Cycle0();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss0Sense_HitCount,      1u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unDiagVal,    3000u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unCurrent,    1153u, == );

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrOpenload,   2u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2GND,  2u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2VBAT, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Cycle0_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not read the diagnose value and
///                        does not check all errors when eft data is invalid
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_boEftValid                 = 0u
/// \input  IoHwAbUser_GetHss0Sense_HitCount     = 0u
/// \input  CddVn7140_asStates[0u].ucErrOpenload   = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2GND  = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss0Sense_HitCount     = 0u
/// \output CddVn7140_asStates[0u].ucErrOpenload   = 5u
/// \output CddVn7140_asStates[0u].ucErrShort2GND  = 5u
/// \output CddVn7140_asStates[0u].ucErrShort2VBAT = 5u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Cycle0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_boEftValid                 = 0u;
  IoHwAbUser_GetHss0Sense_HitCount     = 0u;
  CddVn7140_asStates[0u].ucErrOpenload   = 5u;
  CddVn7140_asStates[0u].ucErrShort2GND  = 5u;
  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u;

  //Step 3) Call FUT

  CddVn7140_Cycle0();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss0Sense_HitCount,      0u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrOpenload,   5u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2GND,  5u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2VBAT, 5u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Cycle0
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if cyclic behaviour is reached correctly
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Cycle0(void)
{
  Mt_CddVn7140_Cycle0_TestCase_1();
  Mt_CddVn7140_Cycle0_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the target fron OFF to ON
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_SetTgt_Param1          = 0u
/// \input  CddVn7140_SetTgt_Param2          = 0u
/// \input  CddVn7140_SetTgt_Param3          = 0x8000u
/// \input  CddVn7140_asStates[0u].unPreTgtVal = 0u
/// \input  CddVn7140_asStates[0u].unActVal    = 0u
/// \input  CddVn7140_asStates[0u].unTgtVal    = 0u
/// \input  IoHwAbUser_SetHss_En1_HitCount   = 0u
/// \input  IoHwAbUser_SetHss_En1_Param1     = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_asStates[0u].unPreTgtVal = 0x8000u
/// \output CddVnd7140_asStates[0u].unActVal    = 0x8000u
/// \output CddVnd7140_asStates[0u].unTgtVal    = 0x8000u
/// \output IoHwAbUser_SetHss_En1_HitCount    = 1u
/// \output IoHwAbUser_SetHss_En1_Param1      = 0x8000u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_SetTgt_Param1          = 0u;
  CddVn7140_SetTgt_Param2          = 0u;
  CddVn7140_SetTgt_Param3          = 0x8000u;
  CddVn7140_asStates[0u].unPreTgtVal = 0u;
  CddVn7140_asStates[0u].unActVal    = 0u;
  CddVn7140_asStates[0u].unTgtVal    = 0u;

  IoHwAbUser_SetHss_En1_HitCount   = 0u;
  IoHwAbUser_SetHss_En1_Param1     = 0u;

  //Step 3) Call FUT

  CddVn7140_SetTgt(CddVn7140_SetTgt_Param1, CddVn7140_SetTgt_Param2, CddVn7140_SetTgt_Param3);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unPreTgtVal, 0x8000u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unActVal,    0x8000u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unTgtVal,    0x8000u, == );

  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_HitCount,        1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_Param1,     0x8000u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the target
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_SetTgt_Param1          = 0u
/// \input  CddVn7140_SetTgt_Param2          = 0u
/// \input  CddVn7140_SetTgt_Param3          = 0x9000u
/// \input  CddVn7140_asStates[0u].unPreTgtVal = 0u
/// \input  CddVn7140_asStates[0u].unActVal    = 0u
/// \input  CddVn7140_asStates[0u].unTgtVal    = 0u
/// \input  IoHwAbUser_SetHss_En1_HitCount   = 0u
/// \input  IoHwAbUser_SetHss_En1_Param1     = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_asStates[0u].unTgtVal    = 0x9000u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_SetTgt_Param1 = 0u;
  CddVn7140_SetTgt_Param2 = 0u;
  CddVn7140_SetTgt_Param3 = 0x9000u;
  CddVn7140_asStates[0u].unPreTgtVal = 0u;
  CddVn7140_asStates[0u].unActVal    = 0u;
  CddVn7140_asStates[0u].unTgtVal    = 0u;

  IoHwAbUser_SetHss_En1_HitCount     = 0u;
  IoHwAbUser_SetHss_En1_Param1       = 0u;

  //Step 3) Call FUT

  CddVn7140_SetTgt(CddVn7140_SetTgt_Param1, CddVn7140_SetTgt_Param2, CddVn7140_SetTgt_Param3);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unTgtVal, 0x9000u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function evaluate the target value and set the output
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_SetTgt_Param1          = 0u
/// \input  CddVn7140_SetTgt_Param2          = 0u
/// \input  CddVn7140_SetTgt_Param3          = 1u
/// \input  CddVn7140_asStates[0u].unPreTgtVal = 0u
/// \input  CddVn7140_asStates[0u].unActVal    = 0u
/// \input  CddVn7140_asStates[0u].unTgtVal    = 0u
/// \input  IoHwAbUser_SetHss_En1_HitCount   = 0u
/// \input  IoHwAbUser_SetHss_En1_Param1     = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_asStates[0u].unTgtVal    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values


  CddVn7140_SetTgt_Param1 = 0u;
  CddVn7140_SetTgt_Param2 = 0u;
  CddVn7140_SetTgt_Param3 = 1u;
  CddVn7140_asStates[0u].unPreTgtVal = 0u;
  CddVn7140_asStates[0u].unActVal = 0u;
  CddVn7140_asStates[0u].unTgtVal = 0u;

  IoHwAbUser_SetHss_En1_HitCount = 0u;
  IoHwAbUser_SetHss_En1_Param1 = 0u;

  //Step 3) Call FUT

  CddVn7140_SetTgt(CddVn7140_SetTgt_Param1, CddVn7140_SetTgt_Param2, CddVn7140_SetTgt_Param3);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unTgtVal, 1, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt_TestCase_4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets the target fron ON to OFF
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_SetTgt_Param1          = 0u
/// \input  CddVn7140_SetTgt_Param2          = 0u
/// \input  CddVn7140_SetTgt_Param3          = 0u
/// \input  CddVn7140_asStates[0u].unPreTgtVal = 0x8000u
/// \input  CddVn7140_asStates[0u].unActVal    = 0x8000u
/// \input  CddVn7140_asStates[0u].unTgtVal    = 0x8000u
/// \input  IoHwAbUser_SetHss_En1_HitCount   = 0u
/// \input  IoHwAbUser_SetHss_En1_Param1     = 0x8000u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[0u].unPreTgtVal = 0u
/// \output CddVn7140_asStates[0u].unActVal    = 0u
/// \output CddVn7140_asStates[0u].unTgtVal    = 0u
/// \output IoHwAbUser_SetHss_En1_HitCount   = 1u
/// \output IoHwAbUser_SetHss_En1_Param1     = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_SetTgt_Param1          = 0u;
  CddVn7140_SetTgt_Param2          = 0u;
  CddVn7140_SetTgt_Param3          = 0u;
  CddVn7140_asStates[0u].unPreTgtVal = 0x8000u;
  CddVn7140_asStates[0u].unActVal    = 0x8000u;
  CddVn7140_asStates[0u].unTgtVal    = 0x8000u;

  IoHwAbUser_SetHss_En1_HitCount   = 0u;
  IoHwAbUser_SetHss_En1_Param1     = 0x8000u;

  //Step 3) Call FUT

  CddVn7140_SetTgt(CddVn7140_SetTgt_Param1, CddVn7140_SetTgt_Param2, CddVn7140_SetTgt_Param3);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unPreTgtVal,      0u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unActVal,         0u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unTgtVal,         0u, == );

  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_HitCount,        1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_Param1,          0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt_TestCase_5
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets target value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_SetTgt_Param1          = 0u
/// \input  CddVnd7140_SetTgt_Param2          = 0u
/// \input  CddVnd7140_SetTgt_Param3          = 0x4000u
/// \input  CddVnd7140_asStates[0u].unTgtVal    = 0x8000u
///
/// - Expectations:
///
/// \output CddVnd7140_asStates[0u].unTgtVal    = 0x4000u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_SetTgt_Param1          = 0u;
  CddVn7140_SetTgt_Param2          = 0u;
  CddVn7140_SetTgt_Param3          = 0x4000u;
  CddVn7140_asStates[0u].unTgtVal    = 0x8000u;

  //Step 3) Call FUT

  CddVn7140_SetTgt(CddVn7140_SetTgt_Param1, CddVn7140_SetTgt_Param2, CddVn7140_SetTgt_Param3);

  //Step 4) Check expected output value 
  
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unTgtVal, 0x4000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt_TestCase_6
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets target value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVnd7140_SetTgt_Param1          = 0u
/// \input  CddVnd7140_SetTgt_Param2          = 0u
/// \input  CddVnd7140_SetTgt_Param3          = 0x4000u
/// \input  CddVnd7140_asStates[0u].unTgtVal  = 0x8000u
/// \input  CddVn7140_asStates[0u].ucHwState  = 3u; //noo Hss support
/// \input  IoHwAbUser_SetHss_En1_HitCount    = 0u
/// \input  IoHwAbUser_SetHss_En1_Param1      = 0x8000u
///
/// - Expectations:
///
/// \output CddVnd7140_asStates[0u].unPreTgtVal    = 0x4000u
/// \output CddVnd7140_asStates[0u].unActVal       = 0x4000u
/// \output IoHwAbUser_SetHss_En1_HitCount         = 1u
/// \output IoHwAbUser_SetHss_En1_Param1           = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_SetTgt_Param1          = 0u;
  CddVn7140_SetTgt_Param2          = 0u;
  CddVn7140_SetTgt_Param3          = 0x4000u;
  CddVn7140_asStates[0u].unTgtVal  = 0x8000u;
  CddVn7140_asStates[0u].ucHwState = 3u; //noo Hss support

  IoHwAbUser_SetHss_En1_HitCount = 0u;
  IoHwAbUser_SetHss_En1_Param1   = 0x8000u;


  //Step 3) Call FUT

  CddVn7140_SetTgt(CddVn7140_SetTgt_Param1, CddVn7140_SetTgt_Param2, CddVn7140_SetTgt_Param3);

  //Step 4) Check expected output value 
  
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unPreTgtVal, 0x4000u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unActVal,    0x4000u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_HitCount,          1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_Param1,            0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_SetTgt
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if target value on HSS channel is set
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_SetTgt(void)
{
  Mt_CddVn7140_SetTgt_TestCase_1();
  Mt_CddVn7140_SetTgt_TestCase_2();
  Mt_CddVn7140_SetTgt_TestCase_3();
  Mt_CddVn7140_SetTgt_TestCase_4();
  Mt_CddVn7140_SetTgt_TestCase_5();
  Mt_CddVn7140_SetTgt_TestCase_6();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_GetState_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets and returns the correct switch state
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_GetState_Param1                 = 0u
/// \input  CddVn7140_GetState_Param2                 = 0u
/// \input  CddVn7140_asStates[0u].ucHwState            = 2u
/// \input  CddVn7140_asStates[0u].unActVal             = 11u
/// \input  CddVn7140_asStates[0u].ucErrOpenload        = 1u
/// \input  CddVn7140_asStates[0u].ucErrShort2GND       = 2u
/// \input  CddVn7140_asStates[0u].ucErrShort2VBAT      = 2u
/// \input  CddVn7140_asStates[0u].unCurrent            = 12u
/// \input  CddVn7140_GetState_RetVal.unActVal        = 0u
/// \input  CddVn7140_GetState_RetVal.ucErrOpenLoad   = 0u
/// \input  CddVn7140_GetState_RetVal.ucErrShort2GND  = 0u
/// \input  CddVn7140_GetState_RetVal.ucErrShort2VBAT = 0u
/// \input  CddVn7140_GetState_RetVal.unActCurrent    = 0u
/// \input  CddVn7140_GetState_RetVal.ucHwState       = 0u
///
/// - Expectations:
///
/// \output CddVn7140_GetState_RetVal.unActVal        = 11u
/// \output CddVn7140_GetState_RetVal.ucErrOpenLoad   = 1u
/// \output CddVn7140_GetState_RetVal.ucErrShort2GND  = 2u
/// \output CddVn7140_GetState_RetVal.ucErrShort2VBAT = 2u
/// \output CddVn7140_GetState_RetVal.unActCurrent    = 12u
/// \output CddVn7140_GetState_RetVal.ucHwState       = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_GetState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_GetState_Param1 = 0u;
  CddVn7140_GetState_Param2 = 0u;

  CddVn7140_asStates[0u].ucHwState = 2u;
  CddVn7140_asStates[0u].unActVal = 11u;
  CddVn7140_asStates[0u].ucErrOpenload = 1u;
  CddVn7140_asStates[0u].ucErrShort2GND = 2u;
  CddVn7140_asStates[0u].ucErrShort2VBAT = 2u;
  CddVn7140_asStates[0u].unCurrent = 12u;

  CddVn7140_GetState_RetVal.unActVal = 0u;
  CddVn7140_GetState_RetVal.ucErrOpenLoad = 0u;
  CddVn7140_GetState_RetVal.ucErrShort2GND = 0u;
  CddVn7140_GetState_RetVal.ucErrShort2VBAT = 0u;
  CddVn7140_GetState_RetVal.unActCurrent = 0u;
  CddVn7140_GetState_RetVal.ucHwState = 0u;

  //Step 3) Call FUT

  CddVn7140_GetState_RetVal = CddVn7140_GetState(CddVn7140_GetState_Param1, CddVn7140_GetState_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.unActVal, 11u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucErrOpenLoad, 1u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucErrShort2GND, 2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucErrShort2VBAT, 2u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.unActCurrent, 12u, == );
  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucHwState, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_GetState_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function return the hardware state as no eft data
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_GetState_Param1                 = 0u
/// \input  CddVn7140_GetState_Param2                 = 0u
/// \input  CddVn7140_asStates[0u].ucHwState            = 1u
/// \input  CddVn7140_GetState_RetVal.ucHwState       = 0u
///
/// - Expectations:
///
/// \output CddVn7140_GetState_RetVal.ucHwState       = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_GetState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_GetState_Param1                 = 0u;
  CddVn7140_GetState_Param2                 = 0u;

  CddVn7140_asStates[0u].ucHwState            = 1u;
  CddVn7140_GetState_RetVal.ucHwState       = 0u;

  //Step 3) Call FUT

  CddVn7140_GetState_RetVal = CddVn7140_GetState(CddVn7140_GetState_Param1, CddVn7140_GetState_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucHwState, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_GetState_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function return the hardware state as no hw support
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_GetState_Param1                 = 0u
/// \input  CddVn7140_GetState_Param2                 = 0u
/// \input  CddVn7140_asStates[0u].ucHwState            = 3u
/// \input  CddVn7140_GetState_RetVal.ucHwState       = 0u
///
/// - Expectations:
///
/// \output CddVn7140_GetState_RetVal.ucHwState       = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_GetState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_GetState_Param1                 = 0u;
  CddVn7140_GetState_Param2                 = 0u;

  CddVn7140_asStates[0u].ucHwState            = 3u;
  CddVn7140_GetState_RetVal.ucHwState       = 0u;

  //Step 3) Call FUT

  CddVn7140_GetState_RetVal = CddVn7140_GetState(CddVn7140_GetState_Param1, CddVn7140_GetState_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucHwState, 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_GetState_TestCase_4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function return the hardware state as signal not aquired
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_GetState_Param1                 = 0u
/// \input  CddVn7140_GetState_Param2                 = 0u
/// \input  CddVn7140_asStates[0u].ucHwState            = 0u
/// \input  CddVn7140_GetState_RetVal.ucHwState       = 1u
///
/// - Expectations:
///
/// \output CddVn7140_GetState_RetVal.ucHwState       = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_GetState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_GetState_Param1                 = 0u;
  CddVn7140_GetState_Param2                 = 0u;

  CddVn7140_asStates[0u].ucHwState            = 0u;
  CddVn7140_GetState_RetVal.ucHwState       = 1u;

  //Step 3) Call FUT

  CddVn7140_GetState_RetVal = CddVn7140_GetState(CddVn7140_GetState_Param1, CddVn7140_GetState_Param2);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_GetState_RetVal.ucHwState, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_GetState
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if switch state on HSS channel is reached correctly
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_GetState(void)
{
  Mt_CddVn7140_GetState_TestCase_1();
  Mt_CddVn7140_GetState_TestCase_2();
  Mt_CddVn7140_GetState_TestCase_3();
  Mt_CddVn7140_GetState_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_ReadDiagVal_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the diagnose value when
///                        hardware state is set to support
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_asStates[0u].ucHwState     = 2u
/// \input  CddVn7140_asStates[0u].unDiagVal     = 0u
/// \input  CddVn7140_asStates[1u].unCurrent     = 0u
/// \input  CddVn7140_unCurrentRsens               = 1u
/// \input  IoHwAbUser_GetHss0Sense_HitCount     = 0u
/// \input  IoHwAbUser_GetHss0Sense_Param1       = 26u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss0Sense_HitCount       = 1u
/// \output CddVn7140_asStates[0u].unDiagVal       = 26u
/// \output CddVn7140_asStates[0u].unCurrent       = 10u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_ReadDiagVal_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_asStates[0u].ucHwState       = 2u;
  CddVn7140_asStates[0u].unDiagVal       = 0u;
  CddVn7140_asStates[0u].unCurrent       = 0u;
  CddVn7140_unCurrentRsens                 = 1u;

  IoHwAbUser_GetHss0Sense_HitCount      = 0u;
  IoHwAbUser_GetHss0Sense_Param1        = 26u;

  //Step 3) Call FUT

  CddVn7140_ReadDiagVal();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss0Sense_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unDiagVal,  26u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unCurrent,  10u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_ReadDiagVal_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads the diagnose value when
///                        hardware state is set to support
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_asStates[0u].ucHwState     = 2u
/// \input  CddVn7140_asStates[0u].unDiagVal     = 0u
/// \input  CddVn7140_asStates[0u].unCurrent     = 0u
/// \input  CddVn7140_unCurrentRsens               = 0u
/// \input  IoHwAbUser_GetHss0Sense_HitCount     = 0u
/// \input  IoHwAbUser_GetHss0Sense_Param1       = 26u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss0Sense_HitCount       = 1u
/// \output CddVn7140_asStates[0u].unDiagVal       = 26u
/// \output CddVn7140_asStates[0u].unCurrent       = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_ReadDiagVal_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_asStates[0u].ucHwState     = 2u;
  CddVn7140_asStates[0u].unDiagVal     = 0u;
  CddVn7140_asStates[0u].unCurrent     = 0u;
  CddVn7140_unCurrentRsens               = 0u;

  IoHwAbUser_GetHss0Sense_HitCount     = 0u;
  IoHwAbUser_GetHss0Sense_Param1       = 26u;

  //Step 3) Call FUT

  CddVn7140_ReadDiagVal();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss0Sense_HitCount,    1u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unDiagVal,   26u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].unCurrent,    0u, == );
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_ReadDiagVal_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not read the diagnose value when
///                        hardware state is set to no support
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_asStates[0u].ucHwState       = 2u
/// \input  CddVn7140_asStates[0u].unDiagVal       = 0u
/// \input  CddVn7140_asStates[0u].unCurrent       = 0u
/// \input  CddVn7140_unCurrentRsens                 = 0u
/// \input  IoHwAbUser_GetHss0Sense_HitCount       = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_GetHss0Sense_HitCount     = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_ReadDiagVal_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_asStates[0u].ucHwState       = 1u;
  CddVn7140_asStates[0u].unDiagVal       = 0u;
  CddVn7140_asStates[0u].unCurrent       = 0u;
  CddVn7140_unCurrentRsens                 = 0u;

  IoHwAbUser_GetHss0Sense_HitCount     = 0u;

  //Step 3) Call FUT

  CddVn7140_ReadDiagVal();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_GetHss0Sense_HitCount,  0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_ReadDiagVal
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function reads correctly the diagnose value from IoHwAbUser
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_ReadDiagVal(void)
{
  Mt_CddVn7140_ReadDiagVal_TestCase_1();
  Mt_CddVn7140_ReadDiagVal_TestCase_2();
  Mt_CddVn7140_ReadDiagVal_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Diag_CheckAllErrors_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does sets all error as no
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_asStates[0u].ucHwState       = 2u
/// \input  CddVn7140_asStates[0u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[0u].unDiagVal       = 3000u
/// \input  CddVn7140_aunOpenLoadThreshold[0u]     = 2000u
/// \input  CddVn7140_aunShort2GndThreshold[0u]    = 4000u
/// \input  CddVn7140_aunShort2VbatThreshold[0u]   = 4000u
/// \input  CddVn7140_asStates[0u].ucErrOpenload   = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2GND  = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[0u].ucErrOpenload   = 2u
/// \output CddVn7140_asStates[0u].ucErrShort2GND  = 2u
/// \output CddVn7140_asStates[0u].ucErrShort2VBAT = 2u (No error)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Diag_CheckAllErrors_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_asStates[0u].ucHwState       = 2u;
  CddVn7140_asStates[0u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[0u].unDiagVal       = 3000u;
  CddVn7140_aunOpenLoadThreshold[0u]     = 2000u;
  CddVn7140_aunShort2GndThreshold[0u]    = 4000u;
  CddVn7140_aunShort2VbatThreshold[0u]   = 4000u;
  CddVn7140_asStates[0u].ucErrOpenload   = 5u;
  CddVn7140_asStates[0u].ucErrShort2GND  = 5u;
  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u;

  //Step 3) Call FUT

  CddVn7140_Diag_CheckAllErrors();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrOpenload,   2u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2GND,  2u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2VBAT, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Diag_CheckAllErrors_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not set errors whem hw state is not supported
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_asStates[0u].ucHwState       = 1u
/// \input  CddVn7140_asStates[0u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[0u].unDiagVal       = 3000u
/// \input  CddVn7140_aunOpenLoadThreshold[0u]     = 2000u
/// \input  CddVn7140_aunShort2GndThreshold[0u]    = 4000u
/// \input  CddVn7140_aunShort2VbatThreshold[0u]   = 4000u
/// \input  CddVn7140_asStates[0u].ucErrOpenload   = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2GND  = 5u
/// \input  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[0u].ucErrOpenload   = 2u
/// \output CddVn7140_asStates[0u].ucErrShort2GND  = 2u
/// \output CddVn7140_asStates[0u].ucErrShort2VBAT = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Diag_CheckAllErrors_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_asStates[0u].ucHwState       = 1u;
  CddVn7140_asStates[0u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[0u].unDiagVal       = 3000u;
  CddVn7140_aunOpenLoadThreshold[0u]     = 2000u;
  CddVn7140_aunShort2GndThreshold[0u]    = 4000u;
  CddVn7140_aunShort2VbatThreshold[0u]   = 4000u;
  CddVn7140_asStates[0u].ucErrOpenload   = 5u;
  CddVn7140_asStates[0u].ucErrShort2GND  = 5u;
  CddVn7140_asStates[0u].ucErrShort2VBAT = 5u;

  //Step 3) Call FUT

  CddVn7140_Diag_CheckAllErrors();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrOpenload,   5u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2GND,  5u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[0u].ucErrShort2VBAT, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_Diag_CheckAllErrors
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function check open load, short to ground and shor to vbat errors
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_Diag_CheckAllErrors(void)
{
  Mt_CddVn7140_Diag_CheckAllErrors_TestCase_1();
  Mt_CddVn7140_Diag_CheckAllErrors_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets open load error yes when diag value
///                        does not exced the threshold, short to vbat error is not present
///                        and HSS is active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckOpenload_Param1       = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 3000u
/// \input  CddVn7140_aunOpenLoadThreshold[1u]     = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2VBAT = 2u (CDDVND7140_CFG_ERR_NO)
/// \input  CddVn7140_asStates[1u].ucErrOpenload   = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrOpenload   = 1u (CDDVND7140_CFG_ERR_YES)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckOpenload_Param1       = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[1u].unDiagVal       = 3000u;
  CddVn7140_aunOpenLoadThreshold[1u]     = 4000u;
  CddVn7140_asStates[1u].ucErrShort2VBAT = 2u;
  CddVn7140_asStates[1u].ucErrOpenload   = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckOpenload(CddVn7140_CheckOpenload_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrOpenload, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not set open load error when diag value
///                        does not exced the threshold, short to vbat error is active
///                        and HSS is active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckOpenload_Param1       = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 3000u
/// \input  CddVn7140_aunOpenLoadThreshold[1u]     = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2VBAT = 1u (CDDVND7140_CFG_ERR_YES)
/// \input  CddVn7140_asStates[1u].ucErrOpenload   = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrOpenload   = 5u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckOpenload_Param1       = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[1u].unDiagVal       = 3000u;
  CddVn7140_aunOpenLoadThreshold[1u]     = 4000u;
  CddVn7140_asStates[1u].ucErrShort2VBAT = 1u;
  CddVn7140_asStates[1u].ucErrOpenload   = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckOpenload(CddVn7140_CheckOpenload_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrOpenload, 5u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does set open load error no when diag value
///                        exceds the threshold and HSS is active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckOpenload_Param1       = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 5000u
/// \input  CddVn7140_aunOpenLoadThreshold[1u]     = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2VBAT = 5u
/// \input  CddVn7140_asStates[1u].ucErrOpenload   = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2VBAT = 2u (CDDVD7140_CFG_ERR_NO)
/// \output CddVn7140_asStates[1u].ucErrOpenload   = 2u (CDDVD7140_CFG_ERR_NO)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckOpenload_Param1       = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[1u].unDiagVal       = 5000u;
  CddVn7140_aunOpenLoadThreshold[1u]     = 4000u;
  CddVn7140_asStates[1u].ucErrShort2VBAT = 5u;
  CddVn7140_asStates[1u].ucErrOpenload   = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckOpenload(CddVn7140_CheckOpenload_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrOpenload,   2u, == );
  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2VBAT, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload_TestCase_4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does sets signal not aquired when 
///                        HSS is not active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckOpenload_Param1       = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0u
/// \input  CddVn7140_asStates[1u].ucErrOpenload   = 2u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrOpenload   = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckOpenload_Param1       = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0u;
  CddVn7140_asStates[1u].ucErrOpenload   = 2u;

  //Step 3) Call FUT

  CddVn7140_CheckOpenload(CddVn7140_CheckOpenload_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrOpenload, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload_TestCase_5
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does set correctly HSS duty
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckOpenload_Param1         = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].unTgtVal       = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckOpenload_Param1         = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0u;

  //Step 3) Call FUT

  CddVn7140_CheckOpenload(CddVn7140_CheckOpenload_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].unTgtVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload_TestCase_6
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function evaluates correct the target value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckOpenload_Param1       = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 1u
/// \input  CddVn7140_asStates[1u].ucErrOpenload   = 0u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].unTgtVal   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckOpenload_Param1  = 1u;
  CddVn7140_asStates[1u].unTgtVal = 1u;
  CddVn7140_asStates[1u].ucErrOpenload = 0u;

  //Step 3) Call FUT

  CddVn7140_CheckOpenload(CddVn7140_CheckOpenload_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].unTgtVal, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckOpenload
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function check open load
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckOpenload(void)
{
  Mt_CddVn7140_CheckOpenload_TestCase_1();
  Mt_CddVn7140_CheckOpenload_TestCase_2();
  Mt_CddVn7140_CheckOpenload_TestCase_3();
  Mt_CddVn7140_CheckOpenload_TestCase_4();
  Mt_CddVn7140_CheckOpenload_TestCase_5();
  Mt_CddVn7140_CheckOpenload_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2GND_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets short to ground error yes when diag value
///                        exceds the threshold and HSS is active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2GND_Param1      = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 5000u
/// \input  CddVn7140_aunShort2GndThreshold[1u]    = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2GND  = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2GND  = 1u (CDDVN7140_CFG_ERR_YES)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2GND_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2GND_Param1        = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[1u].unDiagVal       = 5000u;
  CddVn7140_aunShort2GndThreshold[1u]    = 4000u;
  CddVn7140_asStates[1u].ucErrShort2GND  = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2GND(CddVn7140_CheckShort2GND_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2GND, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2GND_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets short to ground error no when diag value
///                        does not exced the threshold and HSS is active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2GND_Param1        = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 3000u
/// \input  CddVn7140_aunShort2GndThreshold[1u]    = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2GND  = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2GND  = 2u (CDDVN7140_CFG_ERR_NO)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2GND_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2GND_Param1        = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[1u].unDiagVal       = 3000u;
  CddVn7140_aunShort2GndThreshold[1u]    = 4000u;
  CddVn7140_asStates[1u].ucErrShort2GND  = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2GND(CddVn7140_CheckShort2GND_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2GND, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2GND_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not set short to ground error when
///                        HSS is not active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2GND_Param1        = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0u
/// \input  CddVn7140_asStates[1u].ucErrShort2GND  = 0u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2GND  = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2GND_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2GND_Param1        = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0u;
  CddVn7140_asStates[1u].ucErrShort2GND  = 0u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2GND(CddVn7140_CheckShort2GND_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2GND, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2GND_TestCase_4
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test subject: Test if function evaluates correct 
///          the target value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2GND_Param1        = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2GND  = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2GND_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2GND_Param1 = 1u;
  CddVn7140_asStates[1u].unTgtVal = 0u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2GND(CddVn7140_CheckShort2GND_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2GND, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2GND_TestCase_5
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test subject: Test if function evaluates correct 
///          the target value
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2GND_Param1        = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 1u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2GND  = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2GND_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2GND_Param1 = 1u;
  CddVn7140_asStates[1u].unTgtVal = 1u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2GND(CddVn7140_CheckShort2GND_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2GND, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2GND
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function check short to ground error
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2GND(void)
{
  Mt_CddVn7140_CheckShort2GND_TestCase_1();
  Mt_CddVn7140_CheckShort2GND_TestCase_2();
  Mt_CddVn7140_CheckShort2GND_TestCase_3();
  Mt_CddVn7140_CheckShort2GND_TestCase_4();
  Mt_CddVn7140_CheckShort2GND_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2VBAT_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets short to vbat error yes when diag value
///                        exceds the threshold and HSS is not active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2VBAT_Param1     = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 5000u
/// \input  CddVn7140_aunShort2VbatThreshold[1u]   = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2VBAT = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2VBAT = 1u (CDDVN7140_CFG_ERR_YES)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2VBAT_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2VBAT_Param1     = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0u;
  CddVn7140_asStates[1u].unDiagVal       = 5000u;
  CddVn7140_aunShort2VbatThreshold[1u]   = 4000u;
  CddVn7140_asStates[1u].ucErrShort2VBAT = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2VBAT(CddVn7140_CheckShort2VBAT_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2VBAT, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2VBAT_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function sets short to vbat error no when diag value
///                        does not exced the threshold and HSS is not active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2VBAT_Param1       = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0u
/// \input  CddVn7140_asStates[1u].unDiagVal       = 3000u
/// \input  CddVn7140_aunShort2VbatThreshold[1u]   = 4000u
/// \input  CddVn7140_asStates[1u].ucErrShort2VBAT = 5u
///
/// - Expectations:
///
/// \output CddVn7140_asStates[1u].ucErrShort2VBAT = 2u (CDDVN7140_CFG_ERR_NO)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2VBAT_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2VBAT_Param1       = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0u;
  CddVn7140_asStates[1u].unDiagVal       = 3000u;
  CddVn7140_aunShort2VbatThreshold[1u]   = 4000u;
  CddVn7140_asStates[1u].ucErrShort2VBAT = 5u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2VBAT(CddVn7140_CheckShort2VBAT_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2VBAT, 2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2VBAT_TestCase_3
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not set short to vbat error when
///                        HSS is active
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_CheckShort2VBAT_Param1     = 1u
/// \input  CddVn7140_asStates[1u].unTgtVal        = 0x8000u
/// \input  CddVn7140_asStates[1u].ucErrShort2VBAT = 0u
///
/// - Expectations:
///
/// \output CddVnd7140_asStates[1u].ucErrShort2VBAT = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2VBAT_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_CheckShort2VBAT_Param1     = 1u;
  CddVn7140_asStates[1u].unTgtVal        = 0x8000u;
  CddVn7140_asStates[1u].ucErrShort2VBAT = 0u;

  //Step 3) Call FUT

  CddVn7140_CheckShort2VBAT(CddVn7140_CheckShort2VBAT_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_asStates[1u].ucErrShort2VBAT, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_CheckShort2VBAT
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function check short to ground error
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_CheckShort2VBAT(void)
{
  Mt_CddVn7140_CheckShort2VBAT_TestCase_1();
  Mt_CddVn7140_CheckShort2VBAT_TestCase_2();
  Mt_CddVn7140_CheckShort2VBAT_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_DeInit_TestCase_1
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does deinitialize driver ports when
///                        eft data is valid
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_DeInit_Param1                 = 0u
/// \input  CddVn7140_boEftValid                    = TRUE
/// \input  IoHwAbUser_SetHss_En1_HitCount          = 0u
/// \input  IoHwAbUser_SetHss_En1_Param1            = 0x8000u (CDDVND7140_CFG_HSS_EN_HIGH)
///
/// - Expectations:
///
/// \output IoHwAbUser_SetHss_En1_HitCount          = 1u
/// \output IoHwAbUser_SetHss_En1_Param1            = 0u (CDDVND7140_CFG_HSS_EN_LOW)
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_DeInit_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_DeInit_Param1                 = 0u;
  CddVn7140_boEftValid                    = TRUE;
  
  IoHwAbUser_SetHss_En1_HitCount          = 0u;
  IoHwAbUser_SetHss_En1_Param1            = 0x8000u;

  //Step 3) Call FUT

  CddVn7140_DeInit(CddVn7140_DeInit_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_HitCount,           1u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_Param1,             0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_DeInit_TestCase_2
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does not deinitialize driver ports when
///                        eft data is valid
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_DeInit_Param1                = 0u
/// \input  CddVn7140_boEftValid                   = FALSE
/// \input  IoHwAbUser_SetHss_Sen_HitCount         = 0u
/// \input  IoHwAbUser_SetHss_En1_HitCount         = 0u
///
/// - Expectations:
///
/// \output IoHwAbUser_SetHss_Sen_HitCount         = 0u
/// \output IoHwAbUser_SetHss_En1_HitCount         = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_DeInit_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  
  CddVn7140_DeInit_Param1                = 0u;
  CddVn7140_boEftValid                   = FALSE;
  
  IoHwAbUser_SetHss_Sen_HitCount         = 0u;
  IoHwAbUser_SetHss_En1_HitCount         = 0u;

  //Step 3) Call FUT

  CddVn7140_DeInit(CddVn7140_DeInit_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_Sen_HitCount,           0u, == );
  AL_UNITTEST_CHECK(IoHwAbUser_SetHss_En1_HitCount,           0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_DeInit
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function does deinitialize driver ports
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_DeInit(void)
{
  Mt_CddVn7140_DeInit_TestCase_1();
  Mt_CddVn7140_DeInit_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddVn7140_InitCodingParams_TestCase
///
/// \FuSa Relevant: NA
///
/// \Test Case Description
///        - Test subject: Test if function gets coding data from CddSwi
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddVn7140_boCodingValid              = 1u
/// \input  CddVn7140_aunShort2GndThreshold[0u]  = 0u
/// \input  CddVn7140_aunOpenLoadThreshold[0u]   = 0u
/// \input  CddVn7140_aunShort2VbatThreshold[0u] = 0u
/// \input  Cod_HSS3Shor2GndThr_RetVal           = 11u
/// \input  Cod_HSS3OpenLoadThr_RetVal           = 13u
/// \input  Cod_HSS3Shor2VbatThr_RetVal          = 15u
/// \input  Cod_HSS3Shor2GndThr_HitCount         = 0u
/// \input  Cod_HSS3OpenLoadThr_HitCount         = 0u
/// \input  Cod_HSS3Shor2VbatThr_HitCount        = 0u
///
/// - Expectations:
///
/// \output CddVn7140_aunShort2GndThreshold[0u]  = 11u
/// \output CddVn7140_aunOpenLoadThreshold[0u]   = 13u
/// \output CddVn7140_aunShort2VbatThreshold[0u] = 15u
/// \output Cod_HSS3Shor2GndThr_HitCount         = 1u
/// \output Cod_HSS3OpenLoadThr_HitCount         = 1u
/// \output Cod_HSS3Shor2VbatThr_HitCount        = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddVn7140_InitCodingParams_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddVn7140_boCodingValid              = 1u;
  CddVn7140_aunShort2GndThreshold[0u]  = 0u;
  CddVn7140_aunOpenLoadThreshold[0u]   = 0u;
  CddVn7140_aunShort2VbatThreshold[0u] = 0u;

  Cod_HSS3Shor2GndThr_RetVal           = 11u;
  Cod_HSS3OpenLoadThr_RetVal           = 13u;
  Cod_HSS3Shor2VbatThr_RetVal          = 15u;

  Cod_HSS3Shor2GndThr_HitCount         = 0u;
  Cod_HSS3OpenLoadThr_HitCount         = 0u;
  Cod_HSS3Shor2VbatThr_HitCount        = 0u;

  //Step 3) Call FUT

  CddVn7140_InitCodingParams();

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(CddVn7140_aunShort2GndThreshold[0u],     11u, == );
  AL_UNITTEST_CHECK(CddVn7140_aunOpenLoadThreshold[0u],      13u, == );
  AL_UNITTEST_CHECK(CddVn7140_aunShort2VbatThreshold[0u],    15u, == );
  AL_UNITTEST_CHECK(Cod_HSS3Shor2GndThr_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Cod_HSS3OpenLoadThr_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Cod_HSS3Shor2VbatThr_HitCount,            1u, == );
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
  ALUnitTest_AddFunction("Mt_CddVn7140_Init",                         Mt_CddVn7140_Init                              );
  ALUnitTest_AddFunction("Mt_CddVn7140_Cycle0",                       Mt_CddVn7140_Cycle0                            );
  ALUnitTest_AddFunction("Mt_CddVn7140_SetTgt",                       Mt_CddVn7140_SetTgt                            );
  ALUnitTest_AddFunction("Mt_CddVn7140_GetState",                     Mt_CddVn7140_GetState                          );
  ALUnitTest_AddFunction("Mt_CddVn7140_ReadDiagVal",                  Mt_CddVn7140_ReadDiagVal                       );
  ALUnitTest_AddFunction("Mt_CddVn7140_Diag_CheckAllErrors",          Mt_CddVn7140_Diag_CheckAllErrors               );
  ALUnitTest_AddFunction("Mt_CddVn7140_CheckOpenload",                Mt_CddVn7140_CheckOpenload                     );
  ALUnitTest_AddFunction("Mt_CddVn7140_CheckShort2GND",               Mt_CddVn7140_CheckShort2GND                    );
  ALUnitTest_AddFunction("Mt_CddVn7140_CheckShort2VBAT",              Mt_CddVn7140_CheckShort2VBAT                   );
  ALUnitTest_AddFunction("Mt_CddVn7140_DeInit",                       Mt_CddVn7140_DeInit                            );
  ALUnitTest_AddFunction("Mt_CddVn7140_InitCodingParams_TestCase",    Mt_CddVn7140_InitCodingParams_TestCase         );
}
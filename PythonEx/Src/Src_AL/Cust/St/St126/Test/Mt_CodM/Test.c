//*****************************************************************************
//* (C) Automotive Lighting Reutlingen GmbH
//* Tuebinger Strasse 123, 72762 Reutlingen, Germany
//*
//* Automotive Lighting Reutlingen GmbH owns all the rights to this work.
//* This work shall not be copied, reproduced, used, modified, transferred
//* or its information shall not be disclosed without the prior written
//* authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

//-----------------------------------------------------------------------------
/// \file   Test.c
///
/// \brief  Unit Test Cases for CodM module
///
/// \author  Braga Ionut-Cosmin
///         mailTo: ionutcosmin.braga[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Files covered by this module unit test:
///
///        Cust/St/St126/App/Swc/CodM:
///             -ctaaCodM.c
///             -CodM_RteAccess.c
///             -CodM_Hw.c
///             -CodM.c
///
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

//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_riCodM_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function provides pointer to coding area.
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
///input
///
/// - Expectations:
///output   CddEft_DataValid_Hit_Count 2u
//--------------------------------------------------------------------------------
void Mt_CodM_riCodM_Init(void)
{
	//-----------------------------------------------------------------------------
	// Inputs
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// Function call
	//-----------------------------------------------------------------------------

	riCodM_Init();

	//-----------------------------------------------------------------------------
	// Outputs
	//-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddEft_DataValid_Hit_Count, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CodM_rpCodM_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function selects the region between UK and EU correctly
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
///input   CodM_Hw_Init_RetVal = FALSE;
///
/// - Expectations:
///output  CodM_Hw_Init_RetVal, FALSE
//-----------------------------------------------------------------------------
void Mt_CodM_rpCodM_Cycle0(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  //CodM_Hw_Init_RetVal = FALSE;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  rpCodM_Cycle0();
  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  //AL_UNITTEST_CHECK(CodM_Hw_Init_RetVal, FALSE, == );

}

//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_InitModules_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function initializes modules with a pointer to coding area. correctly
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
///input   CodM_InitModules_Param1                 = 1;
///input   CodM_InitModules_Param2                 = 2;
///input   CodM_boPavDataValid                     = FALSE;
///input   Rte_Write_CodM_Anima_Para_HitCount      = 0u;
///input   Rte_Write_CodM_FctR_Para_HitCount       = 0u;
///input   Rte_Write_CodM_SysMon_Para_HitCount     = 0u;
///input   Rte_Write_CodM_CddSwi_Para_HitCount     = 0u;
///input   Rte_Write_CodM_CddLed_Para_HitCount     = 0u;
///input   Rte_Write_CodM_SysVolt_Para_HitCount    = 0u;
///input   Rte_Write_CodM_CtrlFan_Para_HitCount    = 0u;
///input   Rte_Write_CodM_Rsens_Para_HitCount      = 0u;
///input   Rte_Write_CodM_CtrlLed_Para_HitCount    = 0u;
///input   Rte_Write_CodM_AppM_Para_HitCount       = 0u;
///input   Rte_Write_CodM_IoHwAbUser_Para_HitCount = 0u;
///input   Rte_Write_CodM_SigPrep_Para_HitCount    = 0u;
///input   Rte_Write_CodM_Err_Para_HitCount        = 0u;
///
/// - Expectations:
///output    Rte_Write_CodM_Anima_Para_HitCount,     1u
///output    Rte_Write_CodM_FctR_Para_HitCount,      1u,
///output    Rte_Write_CodM_SysMon_Para_HitCount,    1u, 
///output    Rte_Write_CodM_CddSwi_Para_HitCount,    1u, 
///output    Rte_Write_CodM_CddLed_Para_HitCount,    1u, 
///output    Rte_Write_CodM_SysVolt_Para_HitCount,   1u, 
///output    Rte_Write_CodM_CtrlFan_Para_HitCount,   1u, 
///output    Rte_Write_CodM_Rsens_Para_HitCount,     1u, 
///output    Rte_Write_CodM_CtrlLed_Para_HitCount,   1u, 
///output    Rte_Write_CodM_AppM_Para_HitCount,      1u, 
///output    Rte_Write_CodM_IoHwAbUser_Para_HitCount,1u, 
///output    Rte_Write_CodM_SigPrep_Para_HitCount,   1u, 
///output    Rte_Write_CodM_Err_Para_HitCount,       1u, 
///output    CodM_InitModules_Param3.eCodingState,   0, 
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_InitModules_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  CodM_InitModules_Param1                  = 1;
  CodM_InitModules_Param2                  = 2;
  CodM_boPavDataValid                      = FALSE;
  Rte_Write_CodM_Anima_Para_HitCount       = 0u;
  Rte_Write_CodM_FctR_Para_HitCount        = 0u;
  Rte_Write_CodM_SysMon_Para_HitCount      = 0u;
  Rte_Write_CodM_CddSwi_Para_HitCount      = 0u;
  Rte_Write_CodM_CddLed_Para_HitCount      = 0u;
  Rte_Write_CodM_SysVolt_Para_HitCount     = 0u;
  Rte_Write_CodM_CtrlFan_Para_HitCount     = 0u;
  Rte_Write_CodM_Rsens_Para_HitCount       = 0u;
  Rte_Write_CodM_CtrlLed_Para_HitCount     = 0u;
  Rte_Write_CodM_AppM_Para_HitCount        = 0u;
  Rte_Write_CodM_IoHwAbUser_Para_HitCount  = 0u;
  Rte_Write_CodM_SigPrep_Para_HitCount     = 0u;
  Rte_Write_CodM_Err_Para_HitCount         = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  CodM_InitModules(CodM_InitModules_Param1);
  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(Rte_Write_CodM_Anima_Para_HitCount,       1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_FctR_Para_HitCount,        1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_SysMon_Para_HitCount,      1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CddSwi_Para_HitCount,      1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CddLed_Para_HitCount,      1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_SysVolt_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CtrlFan_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_Rsens_Para_HitCount,       1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CtrlLed_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_AppM_Para_HitCount,        1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_IoHwAbUser_Para_HitCount,  1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_SigPrep_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_Err_Para_HitCount,         1u,  == );
  AL_UNITTEST_CHECK(CodM_InitModules_Param3.eCodingState,     0,   == );
}

//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_InitModules_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function initializes modules with a pointer to coding area. correctly
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
///input  CodM_InitModules_Param1                 = 1;
///input  CodM_InitModules_Param2                 = 2;
///input  CodM_boPavDataValid                     = FALSE;
///input  Rte_Write_CodM_Anima_Para_HitCount      = 0u;
///input  Rte_Write_CodM_FctR_Para_HitCount       = 0u;
///input  Rte_Write_CodM_SysMon_Para_HitCount     = 0u;
///input  Rte_Write_CodM_CddSwi_Para_HitCount     = 0u;
///input  Rte_Write_CodM_CddLed_Para_HitCount     = 0u;
///input  Rte_Write_CodM_SysVolt_Para_HitCount    = 0u;
///input  Rte_Write_CodM_CtrlFan_Para_HitCount    = 0u;
///input  Rte_Write_CodM_Rsens_Para_HitCount      = 0u;
///input  Rte_Write_CodM_CtrlLed_Para_HitCount    = 0u;
///input  Rte_Write_CodM_AppM_Para_HitCount       = 0u;
///input  Rte_Write_CodM_IoHwAbUser_Para_HitCount = 0u;
///input  Rte_Write_CodM_SigPrep_Para_HitCount    = 0u;
///input  Rte_Write_CodM_Err_Para_HitCount        = 0u;
///
/// - Expectations:
///output    Rte_Write_CodM_Anima_Para_HitCount,     1u
///output    Rte_Write_CodM_FctR_Para_HitCount,      1u, 
///output    Rte_Write_CodM_SysMon_Para_HitCount,    1u, 
///output    Rte_Write_CodM_CddSwi_Para_HitCount,    1u, 
///output    Rte_Write_CodM_CddLed_Para_HitCount,    1u, 
///output    Rte_Write_CodM_SysVolt_Para_HitCount,   1u, 
///output    Rte_Write_CodM_CtrlFan_Para_HitCount,   1u, 
///output    Rte_Write_CodM_Rsens_Para_HitCount,     1u, 
///output    Rte_Write_CodM_CtrlLed_Para_HitCount,   1u, 
///output    Rte_Write_CodM_AppM_Para_HitCount,      1u, 
///output    Rte_Write_CodM_IoHwAbUser_Para_HitCount,1u, 
///output    Rte_Write_CodM_SigPrep_Para_HitCount,   1u, 
///output    Rte_Write_CodM_Err_Para_HitCount,       1u, 
///output    CodM_InitModules_Param2,                2
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_InitModules_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  CodM_InitModules_Param1                  = 1;
  CodM_InitModules_Param2                  = 2;
  CodM_boPavDataValid                      = TRUE;
  Rte_Write_CodM_Anima_Para_HitCount       = 0u;
  Rte_Write_CodM_FctR_Para_HitCount        = 0u;
  Rte_Write_CodM_SysMon_Para_HitCount      = 0u;
  Rte_Write_CodM_CddSwi_Para_HitCount      = 0u;
  Rte_Write_CodM_CddLed_Para_HitCount      = 0u;
  Rte_Write_CodM_SysVolt_Para_HitCount     = 0u;
  Rte_Write_CodM_CtrlFan_Para_HitCount     = 0u;
  Rte_Write_CodM_Rsens_Para_HitCount       = 0u;
  Rte_Write_CodM_CtrlLed_Para_HitCount     = 0u;
  Rte_Write_CodM_AppM_Para_HitCount        = 0u;
  Rte_Write_CodM_IoHwAbUser_Para_HitCount  = 0u;
  Rte_Write_CodM_SigPrep_Para_HitCount     = 0u;
  Rte_Write_CodM_Err_Para_HitCount         = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  CodM_InitModules(CodM_InitModules_Param1);
  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(Rte_Write_CodM_Anima_Para_HitCount,       1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_FctR_Para_HitCount,        1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_SysMon_Para_HitCount,      1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CddSwi_Para_HitCount,      1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CddLed_Para_HitCount,      1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_SysVolt_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CtrlFan_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_Rsens_Para_HitCount,       1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_CtrlLed_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_AppM_Para_HitCount,        1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_IoHwAbUser_Para_HitCount,  1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_SigPrep_Para_HitCount,     1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_CodM_Err_Para_HitCount,         1u,  == );
  AL_UNITTEST_CHECK(CodM_InitModules_Param2,                  2,   == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_InitModules
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function initializes modules with a pointer to coding area. correctly
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_InitModules(void)
{
  Mt_CodM_CodM_InitModules_TestCase_1();
  Mt_CodM_CodM_InitModules_TestCase_2();
}

//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function provides pointer to coding area.
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
///input   CddEft_DataValid_RetVal = 1;
///input   CddEft_DataValid_Hit_Count = 0;
///
/// - Expectations:
///output    CalibrationRom[0] != 0xFF;
///output    CalibrationRom[1] != 0xFF;
///output    CddEft_DataValid_Hit_Count = 1;
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  CddEft_DataValid_RetVal     = TRUE;
  CddEft_DataValid_Hit_Count  = 0u;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  CodM_Init();
  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(CddEft_DataValid_Hit_Count,  1, == );
}


//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function provides pointer to coding area.
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
///input  CddEft_DataValid_RetVal = 0;
///input  CddEft_DataValid_Hit_Count = 0;
///
/// - Expectations:
///output CddEft_DataValid_Hit_Count = 1;
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_Init_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  CddEft_DataValid_RetVal     = FALSE;
  CddEft_DataValid_Hit_Count  = 0u;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  CodM_Init();
  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(CddEft_DataValid_Hit_Count,  1, == );
}

//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_Init_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function provides pointer to coding area.
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
///input  CddEft_DataValid_RetVal = 1;
///input  CddEft_DataValid_Hit_Count = 0;
///input  CalibrationRom[0] = 0xFF;
///input  CalibrationRom[1] = 0xFF;
///
/// - Expectations:
///output    CddEft_DataValid_Hit_Count = 1;
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_Init_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  CddEft_DataValid_RetVal     = TRUE;
  CddEft_DataValid_Hit_Count  = 0u;
  CalibrationRom[0]           = 0xFF;
  CalibrationRom[1]           = 0xFF;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  CodM_Init();
  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(CddEft_DataValid_Hit_Count,  1, == );
}

//--------------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_Init_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function provides pointer to coding area.
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
///input   CddEft_DataValid_RetVal = TRUE;
///input   CddEft_DataValid_Hit_Count = 0;
///input   CalibrationRom[0] = 0x43;
///input   CalibrationRom[1] = 0x27;
///input   SysCrc_RomSegs_GetCalibState_HitCount = 0u
///input   SysCrc_RomSegs_GetCalibState_Param1.boCalibCheckInitStatus = TRUE
///input   SysCrc_RomSegs_GetCalibState_Param1.boCalibFailStatus      = FALSE
///
/// - Expectations:
///output    CddEft_DataValid_Hit_Count            = 1;
///output    SysCrc_RomSegs_GetCalibState_HitCount = 1;
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_Init_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  CddEft_DataValid_RetVal                                     = TRUE;
  CddEft_DataValid_Hit_Count                                  = 0u;
  CalibrationRom[0]                                           = 0x43u;
  CalibrationRom[1]                                           = 0x27u;
  SysCrc_RomSegs_GetCalibState_HitCount                       = 0u;
  SysCrc_RomSegs_GetCalibState_Param1.boCalibCheckInitStatus  = TRUE;
  SysCrc_RomSegs_GetCalibState_Param1.boCalibFailStatus       = FALSE;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------
  CodM_Init();
  //-----------------------------------------------------------------------------
  // Outputs 
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(CddEft_DataValid_Hit_Count,             1, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_GetCalibState_HitCount,  1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CodM_CodM_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function provides pointer to coding area.
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CodM_CodM_Init(void)
{
  Mt_CodM_CodM_Init_TestCase_1();
  Mt_CodM_CodM_Init_TestCase_2();
  Mt_CodM_CodM_Init_TestCase_3();
  Mt_CodM_CodM_Init_TestCase_4();
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
  //CodM.c
  ALUnitTest_AddFunction("Mt_CodM_CodM_InitModules", Mt_CodM_CodM_InitModules);
  ALUnitTest_AddFunction("Mt_CodM_CodM_Init",        Mt_CodM_CodM_Init);
  
  //ctaaCodM.c
  ALUnitTest_AddFunction("Mt_CodM_rpCodM_Cycle0", Mt_CodM_rpCodM_Cycle0);
  ALUnitTest_AddFunction("Mt_CodM_riCodM_Init", Mt_CodM_riCodM_Init);
}

// EOF

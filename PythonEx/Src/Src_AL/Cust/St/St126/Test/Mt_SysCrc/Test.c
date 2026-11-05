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
/// \brief  Unit Test Cases for SysCrc module
///
/// \author  Braga Ionut-Cosmin
///         mailTo: ionutcosmin.braga[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Files covered by this module unit test:
///
///        Cust/St/St126/App/Bsw/Mcal/SysCrc:
///             -ctaaSysCrc.c
///             -SysCrc_Cfg.c
///        Mcal/S32k/S32K_14X/SysCrc:
///             -SysCrc.c
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
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

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_riSysCrc_Init
///
/// \Test Case Description
///        - Test subject: Test if the riSysCrc_Init function is correctly called
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  
///
/// - Expectations:
///
/// \output 
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_riSysCrc_Init(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  riSysCrc_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  // coverage only due to architectural design
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpSysCrc_Cycle0
///
/// \Test Case Description
///        - Test subject: Test if the cycle function is called
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                                     = 1;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulStartAddrOfSegment = SYS_CRC_CAL_START;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulSizeOfSegment      = SYS_CRC_CAL_CRC_OFFSET;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC         = pSysCrc_ulRomCalcCRC;
/// \input  SysCrc_boCRCCalcFinished                                                   = 1u;
/// \input  CddDma_IsJobCompleted_HitCount                                             = 0u;
/// \input  CRC_SetSeedReg_HitCount                                                    = 0u;
/// \input  CddDma_StartJob_HitCount                                                   = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                                               = 0u;
/// \input  CRC_DRV_GetCrcResult_HitCount                                              = 0u;
///
/// - Expectations:
///
/// \output SysCrc_ucRomSegmentIdx                 = 0
/// \output SysCrc_ucProbablyElfFile               = TRUE
/// \output SysCrc_RomSegs_ulRegCalcCRC[1]         = 0
/// \output SysCrc_boCRCCalcFinished               = 0
/// \output CddDma_IsJobCompleted_HitCount         = 1
/// \output CRC_SetSeedReg_HitCount                = 1
/// \output CddDma_StartJob_HitCount               = 0
/// \output CddDma_IsJobCompleted_RetVal           = 0
/// \output CRC_DRV_GetCrcResult_HitCount          = 1
///
//-----------------------------------------------------------------------------
void Mt_rpSysCrc_Cycle0(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  SysCrc_ucRomSegmentIdx                                                     = 1;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulStartAddrOfSegment = SYS_CRC_CAL_START;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulSizeOfSegment      = SYS_CRC_CAL_CRC_OFFSET;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC         = pSysCrc_ulRomCalcCRC;
  SysCrc_boCRCCalcFinished                                                   = 1u;
  CddDma_IsJobCompleted_HitCount                                             = 0u;
  CRC_SetSeedReg_HitCount                                                    = 0u;
  CddDma_StartJob_HitCount                                                   = 0u;
  CddDma_IsJobCompleted_RetVal                                               = 0u;
  CRC_DRV_GetCrcResult_HitCount                                              = 0u;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  rpSysCrc_Cycle0();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(SysCrc_ucRomSegmentIdx,           0, == );
  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,         TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_ulRegCalcCRC[1],   0, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,          1u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_RetVal,     0u, == );
  AL_UNITTEST_CHECK(CRC_DRV_GetCrcResult_HitCount,    1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test the case when the returned CRC status for CAL data segment is failed
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment] = TRUE
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_GetCalibCrcStatus_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment] = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_GetCalibCrcStatus_RetVal = SysCrc_RomSegs_GetCalibCrcStatus();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_GetCalibCrcStatus_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test the case when the returned CRC status for CAL data segment is successful
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment] = FALSE
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_GetCalibCrcStatus_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment] = FALSE;


  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_GetCalibCrcStatus_RetVal = SysCrc_RomSegs_GetCalibCrcStatus();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_GetCalibCrcStatus_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test the case when the returned CRC status for CAL data segment is successful
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus(void)
{
  Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CallbackFunction_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the callback function is executed 
///                         when the parameter of the SysCrc_RomSegs_CallbackFunction function is NULL pointer
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_CallbackFunction_Callback_HitCount = 0
/// \input  SysCrc_RomSegs_CallbackFunction_Param1            = NULL_PTR
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_CallbackFunction_Callback_HitCount = 0
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CallbackFunction_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CallbackFunction_Callback_HitCount = 0;
  SysCrc_RomSegs_CallbackFunction_Param1            = NULL_PTR;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CallbackFunction(SysCrc_RomSegs_CallbackFunction_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_CallbackFunction_Callback_HitCount, 0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CallbackFunction_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test the case when the function pointer of the SysCrc_RomSegs_CallbackFunction is different from NULL pointer
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_CallbackFunction_Callback_HitCount = 0;
/// \input  SysCrc_RomSegs_CallbackFunction_Param1            = &SysCrc_RomSegs_CallbackFunction_Callback;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_CallbackFunction_Callback_HitCount = 1
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CallbackFunction_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CallbackFunction_Callback_HitCount = 0;
  SysCrc_RomSegs_CallbackFunction_Param1            = &SysCrc_RomSegs_CallbackFunction_Callback;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CallbackFunction(SysCrc_RomSegs_CallbackFunction_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_CallbackFunction_Callback_HitCount, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CallbackFunction
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test the case when the function pointer of the SysCrc_RomSegs_CallbackFunction is different from NULL pointer
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CallbackFunction(void)
{
  Mt_SysCrc_SysCrc_RomSegs_CallbackFunction_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_CallbackFunction_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_SegmentCrcCheck, Dem_SetEventStatus and SysCrc_RomSegs_InitCRC functions
///                        are correctly called by the SysCrc_RomSegs_Init function when CRC for CAL data is ok
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input SysCrc_RomSegs_Init_Param1                                              = &SysCrc_Config;
/// \input SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
/// \input SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1234;
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = FALSE;
/// \input Dem_SetEventStatus_HitCount                                             = 0;
/// \input CRC_DRV_Init_HitCount                                                   = 0u;
/// \input CRC_SetSeedReg_HitCount                                                 = 0u;
/// \input CRC_DRV_GetCrcResult_HitCount                                           = 0u;
/// \input CRC_DRV_GetCrcResult_RetVal                                             = 0x1234;
/// \input CddDma_StartJob_HitCount                                                = 0u;
/// \input CddDma_IsJobCompleted_HitCount                                          = 0u;
/// \input CddDma_IsJobCompleted_RetVal                                            = 1u;
/// \input SysCrc_RomSegs_boCrcStatus[eCalibrationSegment]                         = 0u;
/// \input SysCrc_boCRCCalcStarted                                                 = FALSE
/// \input SysCrc_boCRCCalcFinished                                                = FALSE
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Output_Param1 = CRC_CALIB_DEFECT 
/// \output Dem_SetEventStatus_Output_Param2 = 0x03u
/// \output Dem_SetEventStatus_HitCount      = 2
/// \output SysCrc_ucRomSegmentIdx           = 0
/// \output SysCrc_RomSegs_ulRegCalcCRC[0]   = 0
/// \output CRC_DRV_Init_HitCount            = 1
/// \output CddDma_IsJobCompleted_HitCount   = 5
/// \output CddDma_StartJob_HitCount         = 5
/// \output CRC_DRV_GetCrcResult_HitCount    = 1
/// \output CRC_SetSeedReg_HitCount          = 1
/// \output CRC_DRV_Init_HitCount            = 0
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Init_Param1                                              = &SysCrc_Config;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1234;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = FALSE;
  Dem_SetEventStatus_HitCount                                             = 0;
  CRC_DRV_Init_HitCount                                                   = 0u;
  CRC_SetSeedReg_HitCount                                                 = 0u;
  CRC_DRV_GetCrcResult_HitCount                                           = 0u;
  CRC_DRV_GetCrcResult_RetVal                                             = 0x1234;
  CddDma_StartJob_HitCount                                                = 0u;
  CddDma_IsJobCompleted_HitCount                                          = 0u;
  CddDma_IsJobCompleted_RetVal                                            = 1u;
  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment]                         = 0u;
  SysCrc_boCRCCalcStarted                                                 = FALSE;
  SysCrc_boCRCCalcFinished                                                = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Init(SysCrc_RomSegs_Init_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1,    CRC_CALIB_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2,               0x02u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        2, == );
  AL_UNITTEST_CHECK(SysCrc_ucRomSegmentIdx,                             0, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_ulRegCalcCRC[0],                     0, == );
  AL_UNITTEST_CHECK(CRC_DRV_Init_HitCount,                              1, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,                     5, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,                           5, == );
  AL_UNITTEST_CHECK(CRC_DRV_GetCrcResult_HitCount,                      1, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,                            1, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,                           0, == );


}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Init_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_SegmentCrcCheck, Dem_SetEventStatus and SysCrc_RomSegs_InitCRC functions
///                        are correctly called by the SysCrc_RomSegs_Init function when CRC for CAL data is ok
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input SysCrc_RomSegs_Init_Param1                                              = &SysCrc_Config;
/// \input SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
/// \input SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1233;
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
/// \input SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = TRUE;
/// \input Dem_SetEventStatus_HitCount                                             = 0;
/// \input CRC_DRV_GetCrcResult_RetVal                                             = &SysCrc_RomSegs_SegmentCrcCheck_Var1[516];
/// \input CRC_DRV_Init_HitCount                                                   = 0u;
/// \input CRC_SetSeedReg_HitCount                                                 = 0u;
/// \input CRC_DRV_GetCrcResult_HitCount                                           = 0u;
/// \input CddDma_StartJob_HitCount                                                = 0u;
/// \input CddDma_IsJobCompleted_HitCount                                          = 0u;
/// \input CddDma_IsJobCompleted_RetVal                                            = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Output_Param1 = CRC_CALIB_DEFECT 
/// \output Dem_SetEventStatus_Output_Param2 = 0x03u
/// \output Dem_SetEventStatus_HitCount      = 2
/// \output SysCrc_ucRomSegmentIdx           = 0
/// \output SysCrc_RomSegs_ulRegCalcCRC[0]   = 0
/// \output CRC_DRV_Init_HitCount            = 1
/// \output CddDma_StartJob_HitCount         = 1
/// \output SysCrc_boCRCCalcFinished         = 0
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Init_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Init_Param1                                              = &SysCrc_Config;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1233;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = TRUE;
  Dem_SetEventStatus_HitCount                                             = 0;
  CRC_DRV_GetCrcResult_RetVal                                             = &SysCrc_RomSegs_SegmentCrcCheck_Var1[516];
  CRC_DRV_Init_HitCount                                                   = 0u;
  CRC_SetSeedReg_HitCount                                                 = 0u;
  CRC_DRV_GetCrcResult_HitCount                                           = 0u;
  CddDma_StartJob_HitCount                                                = 0u;
  CddDma_IsJobCompleted_HitCount                                          = 0u;
  CddDma_IsJobCompleted_RetVal                                            = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Init(SysCrc_RomSegs_Init_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1,    CRC_CALIB_DEFECT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2,               0x03u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        2, == );
  AL_UNITTEST_CHECK(SysCrc_ucRomSegmentIdx,                             0, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_ulRegCalcCRC[0],                     0, == );
  AL_UNITTEST_CHECK(CRC_DRV_Init_HitCount,                              1, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,                           1, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,                           0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Init
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test if the SysCrc_RomSegs_SegmentCrcCheck, Dem_SetEventStatus and SysCrc_RomSegs_InitCRC functions
///                        are correctly called by the SysCrc_RomSegs_Init function when CRC for CAL data is ok
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Init(void)
{
  Mt_SysCrc_SysCrc_RomSegs_Init_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_Init_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_InitCRC
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_InitCRC function initialize the varibales used for the calculation of the CRC32
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                = 2
/// \input  SysCrc_RomSegs_RomSegs[0].SysCrc_ulStartAddrOfSegment = SYS_CRC_APP_START
///
/// - Expectations:
///
/// \output SysCrc_ucRomSegmentIdx         = 0
/// \output SysCrc_RomSegs_ulRegCalcCRC[0] = 0
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_InitCRC(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                = 2;
  SysCrc_RomSegs_RomSegs[0].SysCrc_ulStartAddrOfSegment = SYS_CRC_APP_START;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_InitCRC();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_ucRomSegmentIdx,         0, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_ulRegCalcCRC[0], 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test the case when the CRC on the segment received from SysCrc_RomSegs_DoCRCSegment function is not ready
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                                     = 0;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulStartAddrOfSegment = 0x0000ffff;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulSizeOfSegment      = 0x520;
/// \input  SysCrc_boCRCCalcFinished                                                   = 0u;
/// \input  CddDma_IsJobCompleted_HitCount                                             = 0u;
/// \input  CRC_SetSeedReg_HitCount                                                    = 0u;
/// \input  CddDma_StartJob_HitCount                                                   = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                                               = 0u;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC         = pSysCrc_ulRomCalcCRC;
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile         = FALSE
/// \output SysCrc_boCRCCalcFinished         = 0u
/// \output CddDma_IsJobCompleted_HitCount   = 1u
/// \output CRC_SetSeedReg_HitCount          = 0u
/// \output CddDma_StartJob_HitCount         = 0u
/// \output CddDma_IsJobCompleted_RetVal     = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                                     = 0;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulStartAddrOfSegment = 0x0000ffff;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulSizeOfSegment      = 0x520;
  SysCrc_boCRCCalcFinished                                                   = 0u;
  CddDma_IsJobCompleted_HitCount                                             = 0u;
  CRC_SetSeedReg_HitCount                                                    = 0u;
  CddDma_StartJob_HitCount                                                   = 0u;
  CddDma_IsJobCompleted_RetVal                                               = 0u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC         = pSysCrc_ulRomCalcCRC;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_DoCRC();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,         TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,          0u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_RetVal,     0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_DoCRC function get and check the next segment 
///                        when the CRC on the segment received from SysCrc_RomSegs_DoCRCSegment function is ready
///                        and there are more segments to check
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                                     = 1;
/// \input  i                                                                          = 0..7u;
/// \input  PC_MemBlock[56 + i]                                                        = 0xFFu;
/// \input  SysCrc_boCRCCalcFinished                                                   = 1u;
/// \input  CddDma_IsJobCompleted_HitCount                                             = 0u;
/// \input  CRC_SetSeedReg_HitCount                                                    = 0u;
/// \input  CddDma_StartJob_HitCount                                                   = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                                               = 0u;
/// \input  CRC_DRV_GetCrcResult_RetVal                                                = 0xA5B57A8Cu;
/// \input  CRC_DRV_GetCrcResult_HitCount                                              = 0u;
///
/// - Expectations:
///
/// \output SysCrc_ucRomSegmentIdx                 = 0
/// \output SysCrc_ucProbablyElfFile               = TRUE
/// \output SysCrc_RomSegs_ulRegCalcCRC[1]         = 0
/// \output SysCrc_boCRCCalcFinished               = 0
/// \output CddDma_IsJobCompleted_HitCount         = 1
/// \output CRC_SetSeedReg_HitCount                = 1
/// \output CddDma_StartJob_HitCount               = 0
/// \output CddDma_IsJobCompleted_RetVal           = 0
/// \output CRC_DRV_GetCrcResult_HitCount          = 1
/// \output SysCrc_RomSegs_ulRegCalcCRC[0]         = 0xA5B57A8Cu
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                                     = 1;

  // Init the memory to be like an elf file
  // RomSeg 1
  for (uint8 i = 0u; i < 8u; i++)
  {
    PC_MemBlock[56 + i] = 0xFFu;
  }
  
  SysCrc_boCRCCalcFinished                                                   = 1u;
  SysCrc_ucProbablyElfFile                                                   = FALSE;
  CddDma_IsJobCompleted_HitCount                                             = 0u;
  CRC_SetSeedReg_HitCount                                                    = 0u;
  CddDma_StartJob_HitCount                                                   = 0u;
  CddDma_IsJobCompleted_RetVal                                               = 0u;
  CRC_DRV_GetCrcResult_RetVal                                                = 0xA5B57A8Cu;
  CRC_DRV_GetCrcResult_HitCount                                              = 0u;
  SysCrc_RomSegs_ulRegCalcCRC[1]                                             = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Init the local ROM seg
  Mt_SysCrc_SysCrc_RomSegs_InitRomSegMem();
  SysCrc_RomSegs_DoCRC();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(SysCrc_ucRomSegmentIdx,           0, == );
  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,         TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_ulRegCalcCRC[1],   0xA5B57A8Cu, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,          1u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_RetVal,     0u, == );
  AL_UNITTEST_CHECK(CRC_DRV_GetCrcResult_HitCount,    1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_DoCRC function  restart all the checking
///                        when the CRC on the segment received from SysCrc_RomSegs_DoCRCSegment function is ready
///                        and there are  no more segments to check
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                                     = 0;
/// \input  i                                                                          = 0..7u;
/// \input  PC_MemBlock[24 + i]                                                        = 0xFFu;
/// \input  SysCrc_boCRCCalcFinished                                                   = 1u;
/// \input  CddDma_IsJobCompleted_HitCount                                             = 0u;
/// \input  CRC_SetSeedReg_HitCount                                                    = 0u;
/// \input  CddDma_StartJob_HitCount                                                   = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                                               = 0u;
/// \input  CRC_DRV_GetCrcResult_RetVal                                                = 0xA5CC3365u;
/// \input  CRC_DRV_GetCrcResult_HitCount                                              = 0u;
///
/// - Expectations:
///
/// \output SysCrc_ucRomSegmentIdx                 = 1
/// \output SysCrc_RomSegs_ulRegCalcCRC[0]         = 0
/// \output SysCrc_boCRCCalcFinished               = 0
/// \output CddDma_IsJobCompleted_HitCount         = 1
/// \output CRC_SetSeedReg_HitCount                = 1
/// \output CddDma_StartJob_HitCount               = 0
/// \output CddDma_IsJobCompleted_RetVal           = 0
/// \output CRC_DRV_GetCrcResult_HitCount          = 1
/// \output SysCrc_RomSegs_ulRegCalcCRC[0]         = 0xA5CC3365u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                                     = 0;
  // Init the memory to be like an elf file
  // RomSeg 2
  for (uint8 i = 0u; i < 8u; i++)
  {
    PC_MemBlock[24 + i] = 0xFFu;
  }
  SysCrc_boCRCCalcFinished                                                   = 1u;
  SysCrc_ucProbablyElfFile                                                   = FALSE;
  CddDma_IsJobCompleted_HitCount                                             = 0u;
  CRC_SetSeedReg_HitCount                                                    = 0u;
  CddDma_StartJob_HitCount                                                   = 0u;
  CddDma_IsJobCompleted_RetVal                                               = 0u;
  CRC_DRV_GetCrcResult_RetVal                                                = 0xA5CC3365u;
  CRC_DRV_GetCrcResult_HitCount                                              = 0u;
  SysCrc_RomSegs_ulRegCalcCRC[0]                                             = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  // Init the local ROM seg
  Mt_SysCrc_SysCrc_RomSegs_InitRomSegMem();
  SysCrc_RomSegs_DoCRC();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_ucRomSegmentIdx,           1, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_ulRegCalcCRC[0],   0xA5CC3365u, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,   1u, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,          1u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,         0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_RetVal,     0u, == );
  AL_UNITTEST_CHECK(CRC_DRV_GetCrcResult_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRC
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test if the SysCrc_RomSegs_DoCRC function  restart all the checking
///                        when the CRC on the segment received from SysCrc_RomSegs_DoCRCSegment function is ready
///                        and there are  no more segments to check
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRC(void)
{
  Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_2();
  Mt_SysCrc_SysCrc_RomSegs_DoCRC_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the returned value for SysCrc_RomSegs_DoCRCSegment function is false when the lenght of the segment part is not equal to a multiple of 4
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_DoCRCSegment_Param1                    = 2;
/// \input  SysCrc_RomSegs_RomSegs[2].SysCrc_ulStartAddrOfSegment = 0x0000ffff;
/// \input  SysCrc_RomSegs_RomSegs[2].SysCrc_ulSizeOfSegment      = 0x10;
/// \input  SysCrc_boCRCCalcFinished                              = 0u;
/// \input  CddDma_IsJobCompleted_HitCount                        = 0u;
/// \input  CRC_SetSeedReg_HitCount                               = 0u;
/// \input  CddDma_StartJob_HitCount                              = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                          = 1u;
/// \input  CRC_DRV_GetCrcResult_HitCount                         = 0u;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_DoCRCSegment_RetVal     = FALSE
/// \output SysCrc_boCRCCalcFinished               = 0
/// \output CddDma_IsJobCompleted_HitCount         = 2
/// \output CRC_SetSeedReg_HitCount                = 0
/// \output CddDma_StartJob_HitCount               = 4
/// \output CddDma_IsJobCompleted_RetVal           = 0
/// \output CRC_DRV_GetCrcResult_HitCount          = 1
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_DoCRCSegment_Param1                    = 2;
  SysCrc_RomSegs_RomSegs[2].SysCrc_ulStartAddrOfSegment = 0x0000ffff;
  SysCrc_RomSegs_RomSegs[2].SysCrc_ulSizeOfSegment      = 0x10;
  SysCrc_boCRCCalcFinished                              = 0u;
  CddDma_IsJobCompleted_HitCount                        = 0u;
  CRC_SetSeedReg_HitCount                               = 0u;
  CddDma_StartJob_HitCount                              = 0u;
  CddDma_IsJobCompleted_RetVal                          = 1u;
  CRC_DRV_GetCrcResult_HitCount                         = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_DoCRCSegment_RetVal = SysCrc_RomSegs_DoCRCSegment(SysCrc_RomSegs_DoCRCSegment_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_DoCRCSegment_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,           0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,     1u, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,            0u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,           2u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_RetVal,       1u, == );
  AL_UNITTEST_CHECK(CRC_DRV_GetCrcResult_HitCount,      0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_DoCRCSegment function tries to take the next segment
///                        when the lenght of the segment part is equal to a multiple of 4(sizeof(uint32))
///                        and the segment was calculated
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_DoCRCSegment_Param1                    = 2;
/// \input  SysCrc_RomSegs_RomSegs[2].SysCrc_ulStartAddrOfSegment = 0x0000ffff;
/// \input  SysCrc_RomSegs_RomSegs[2].SysCrc_ulSizeOfSegment      = 0x10;
/// \input  SysCrc_boCRCCalcFinished                              = 1u;
/// \input  CddDma_IsJobCompleted_HitCount                        = 0u;
/// \input  CRC_SetSeedReg_HitCount                               = 0u;
/// \input  CddDma_StartJob_HitCount                              = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                          = 0u;
/// \input  CRC_DRV_GetCrcResult_HitCount                         = 0u;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_DoCRCSegment_RetVal     = TRUE
/// \output SysCrc_boCRCCalcFinished               = 0
/// \output CddDma_IsJobCompleted_HitCount         = 1
/// \output CRC_SetSeedReg_HitCount                = 1
/// \output CddDma_StartJob_HitCount               = 0
/// \output CddDma_IsJobCompleted_RetVal           = 0
/// \output CRC_DRV_GetCrcResult_HitCount          = 1
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_DoCRCSegment_Param1                     = 2;
  SysCrc_RomSegs_RomSegs[2].SysCrc_ulStartAddrOfSegment = 0x0000ffff;
  SysCrc_RomSegs_RomSegs[2].SysCrc_ulSizeOfSegment      = 0x10;
  SysCrc_boCRCCalcFinished                              = 1u;
  CddDma_IsJobCompleted_HitCount                        = 0u;
  CRC_SetSeedReg_HitCount                               = 0u;
  CddDma_StartJob_HitCount                              = 0u;
  CddDma_IsJobCompleted_RetVal                          = 0u;
  CRC_DRV_GetCrcResult_HitCount                         = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_DoCRCSegment_RetVal = SysCrc_RomSegs_DoCRCSegment(SysCrc_RomSegs_DoCRCSegment_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_DoCRCSegment_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,           0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_HitCount,     1u, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,            1u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,           0u, == );
  AL_UNITTEST_CHECK(CddDma_IsJobCompleted_RetVal,       0u, == );
  AL_UNITTEST_CHECK(CRC_DRV_GetCrcResult_HitCount,      1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test if the SysCrc_RomSegs_DoCRCSegment function tries to take the next segment
///                        when the lenght of the segment part is equal to a multiple of 4(sizeof(uint32))
///                        and the segment was calculated
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment(void)
{
  Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_SegmentCrcCheck function correctly calls the Dem_SetEventStatus function with the right parameters
///                        and the Crc Status is true
///                        when the calculated CRC is different from the CRC stored in ROM
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1234;
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Param1                                   = eCalibrationSegment;
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = FALSE;
/// \input  Dem_SetEventStatus_HitCount                                             = 0;
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_unDtc                = 0x0002;
/// \input  CRC_DRV_Init_HitCount                                                   = 0u;
/// \input  CRC_SetSeedReg_HitCount                                                 = 0u;
/// \input  CRC_DRV_GetCrcResult_HitCount                                           = 0u;
/// \input  CRC_DRV_GetCrcResult_RetVal                                             = 0x1234;
/// \input  CddDma_StartJob_HitCount                                                = 0u;
/// \input  CddDma_IsJobCompleted_HitCount                                          = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                                            = 1u;
/// \input  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment]                         = 0u;
/// \input  SysCrc_boCRCCalcStarted                                                 = FALSE;
/// \input  SysCrc_boCRCCalcFinished                                                = FALSE;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_boCrcStatus[eApplicationSegment] = FALSE
/// \output Dem_SetEventStatus_Output_Param1                = 0x0002
/// \output Dem_SetEventStatus_Output_Param2                = 0x02u
/// \output Dem_SetEventStatus_HitCount                     = 1
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
  
  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1234;
  SysCrc_RomSegs_SegmentCrcCheck_Param1                                   = eCalibrationSegment;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = FALSE;
  Dem_SetEventStatus_HitCount                                             = 0;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_unDtc                = 0x0002;
  CRC_DRV_Init_HitCount                                                   = 0u;
  CRC_SetSeedReg_HitCount                                                 = 0u;
  CRC_DRV_GetCrcResult_HitCount                                           = 0u;
  CRC_DRV_GetCrcResult_RetVal                                             = 0x1234;
  CddDma_StartJob_HitCount                                                = 0u;
  CddDma_IsJobCompleted_HitCount                                          = 0u;
  CddDma_IsJobCompleted_RetVal                                            = 1u;
  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment]                         = 0u;
  SysCrc_boCRCCalcStarted                                                 = FALSE;
  SysCrc_boCRCCalcFinished                                                = FALSE;
 
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_SegmentCrcCheck(SysCrc_RomSegs_SegmentCrcCheck_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_boCrcStatus[eCalibrationSegment], FALSE, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1,                0x0002, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2,                0x02u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                     1, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if SysCrc_RomSegs_SegmentCrcCheck function correctly calls the 
///                        Dem_SetEventStatus function  when the calculated CRC is equal with the CRC stored in ROM
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1234;
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Param1                                   = eCalibrationSegment;
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = TRUE;
/// \input  Dem_SetEventStatus_HitCount                                             = 0;
/// \input  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_unDtc                = 0x0002;
/// \input  CRC_DRV_Init_HitCount                                                   = 0u;
/// \input  CRC_SetSeedReg_HitCount                                                 = 0u;
/// \input  CRC_DRV_GetCrcResult_HitCount                                           = 0u;
/// \input  CRC_DRV_GetCrcResult_RetVal                                             = 0x1234;
/// \input  CddDma_StartJob_HitCount                                                = 0u;
/// \input  CddDma_IsJobCompleted_HitCount                                          = 0u;
/// \input  CddDma_IsJobCompleted_RetVal                                            = 0u;
/// \input  SysCrc_RomSegs_boCrcStatus[eCalibrationSegment]                         = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount                     = 1u
/// \output Dem_SetEventStatus_Output_Param1                = 0x0002
/// \output Dem_SetEventStatus_Output_Param2                = 0x03u
/// \output *((uint32*)(SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment + SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment)) = 0x1234
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------
 
  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0x1234;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1233;
  SysCrc_RomSegs_SegmentCrcCheck_Param1                                   = eCalibrationSegment;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_boSwapCrc            = TRUE;
  Dem_SetEventStatus_HitCount                                             = 0;
  SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_unDtc                = 0x0002;
  CRC_DRV_GetCrcResult_RetVal                                             = &SysCrc_RomSegs_SegmentCrcCheck_Var1[516];
  CRC_DRV_Init_HitCount                                                   = 0u;
  CRC_SetSeedReg_HitCount                                                 = 0u;
  CRC_DRV_GetCrcResult_HitCount                                           = 0u;
  CddDma_StartJob_HitCount                                                = 0u;
  CddDma_IsJobCompleted_HitCount                                          = 0u;
  CddDma_IsJobCompleted_RetVal                                            = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_SegmentCrcCheck(SysCrc_RomSegs_SegmentCrcCheck_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                     1, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1,                0x0002, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2,                0x03u, == );
  AL_UNITTEST_CHECK(*((uint32*)(SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulStartAddrOfSegment + SysCrc_RomSegs_RomSegs[eCalibrationSegment].SysCrc_ulSizeOfSegment)), 0x1234, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test the case when the CRC stored in ROM has an invalid value
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0xffffffff;
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1233;
/// \input  SysCrc_RomSegs_SegmentCrcCheck_Param1                                   = eApplicationSegment;
/// \input  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
/// \input  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
/// \input  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
/// \input  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_boSwapCrc            = FALSE;
/// \input  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_unDtc                = 0x0002;
/// \input  Dem_SetEventStatus_HitCount                                             = 0;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_boCrcStatus[eApplicationSegment]                         = FALSE
/// \output Dem_SetEventStatus_Output_Param1                                        = 0x0002
/// \output Dem_SetEventStatus_Output_Param2                                        = 0x03u
/// \output Dem_SetEventStatus_HitCount                                             = 0
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_SegmentCrcCheck_Var1[517]                                = 0xffffffff;
  SysCrc_RomSegs_SegmentCrcCheck_Var1[516]                                = 0x1233;
  SysCrc_RomSegs_SegmentCrcCheck_Param1                                   = eApplicationSegment;
  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_ulRomCalcCRC         = &SysCrc_RomSegs_SegmentCrcCheck_Var1[517];
  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_ulStartAddrOfSegment = &SysCrc_RomSegs_SegmentCrcCheck_Var1[0];
  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_ulSizeOfSegment      = sizeof(uint32) * 517;
  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_boSwapCrc            = FALSE;
  SysCrc_RomSegs_RomSegs[eApplicationSegment].SysCrc_unDtc                = 0x0002;
  Dem_SetEventStatus_HitCount = 0;

  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_SegmentCrcCheck(SysCrc_RomSegs_SegmentCrcCheck_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_boCrcStatus[eApplicationSegment], FALSE, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1,                0x0002, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2,                0x03u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                     0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test the case when the CRC stored in ROM has an invalid value
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck(void)
{
  Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_2();
  Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if SysCrc_RomSegs_CheckCrc correctly calls the SysCrc_RomSegs_CatchCrc function when the CRC stored in ROM 
///                        has an invalid value
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                             = 1u
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = TRUE
/// \input  SysCrc_ulRomCalcCRC_Var1                                           = 0xffffffffu
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile = TRUE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                          = 1u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc = TRUE;

  SysCrc_ulRomCalcCRC_Var1                                           = 0xffffffffu;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CheckCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_CheckCrc correctly calls SysCrc_RomSegs_CatchCrc function when the CRC stored in ROM 
///                        has a valid value and test if the Dem_SetEventStatus function is called with the right parameters when is no CRC failure
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                             = 0
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = FALSE
/// \input  SysCrc_ulRomCalcCRC_Var1                                           = SYS_CRC_APP_ROM_CALC_CRC
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC
/// \input  SysCrc_RomSegs_ulRegCalcCRC[SysCrc_ucRomSegmentIdx]                = SYS_CRC_APP_ROM_CALC_CRC
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_unDtc        = 0x00000111
/// \input  Dem_SetEventStatus_HitCount                                        = 0
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile         = FALSE
/// \output Dem_SetEventStatus_Output_Param1 = 0x00000111
/// \output Dem_SetEventStatus_Output_Param2 = 0x02u
/// \output Dem_SetEventStatus_HitCount      = 0x01u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                             = 0;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = FALSE;
  SysCrc_ulRomCalcCRC_Var1                                           = SYS_CRC_APP_ROM_CALC_CRC;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;
  SysCrc_RomSegs_ulRegCalcCRC[SysCrc_ucRomSegmentIdx]                = SYS_CRC_APP_ROM_CALC_CRC;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_unDtc        = 0x00000111;
  Dem_SetEventStatus_HitCount                                        = 0;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CheckCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,         FALSE, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1, 0x00000111, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2, 0x02u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,      0x01u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_CheckCrc correctly calls SysCrc_RomSegs_CatchCrc function when the CRC stored in ROM 
///                        has a valid value and test if the Dem_SetEventStatus and SysCrc_RomSegs_CallbackFunction functions are called with the right parameters 
///                        when a CRC failure is reported
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                             = 1u
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = TRUE
/// \input  SysCrc_ulRomCalcCRC_Var1                                           = 0x000000f1u
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC
/// \input  SysCrc_RomSegs_ulRegCalcCRC[1]                                     = 0x0000fff0u
/// \input  SysCrc_RomSegs_RomSegs[1].SysCrc_unDtc                             = 0x00000111
/// \input  Dem_SetEventStatus_HitCount                                        = 0
/// \input  EcuM_FlashCrcFailure_Indication_HitCount                           = 0
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile                 = FALSE
/// \output Dem_SetEventStatus_Output_Param1         = 0x00000111
/// \output Dem_SetEventStatus_Output_Param2         = 0x03u
/// \output Dem_SetEventStatus_HitCount              = 0x01u
/// \output EcuM_FlashCrcFailure_Indication_HitCount = 1
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                             = 0u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = TRUE;
  SysCrc_ulRomCalcCRC_Var1                                           = 0x000000f1u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;
  SysCrc_RomSegs_ulRegCalcCRC[1]                                     = 0x0000fff0u;
  SysCrc_RomSegs_RomSegs[1].SysCrc_unDtc                             = 0x00000111;
  Dem_SetEventStatus_HitCount                                        = 0;
  EcuM_FlashCrcFailure_Indication_HitCount                           = 0;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CheckCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,                 FALSE, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param1,         0x00000111, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Output_Param2,         0x03u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,              0x01u, == );
  AL_UNITTEST_CHECK(EcuM_FlashCrcFailure_Indication_HitCount, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CheckCrc
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test if the SysCrc_RomSegs_CheckCrc correctly calls SysCrc_RomSegs_CatchCrc function when the CRC stored in ROM 
///                        has a valid value and test if the Dem_SetEventStatus and SysCrc_RomSegs_CallbackFunction functions are called with the right parameters 
///                        when a CRC failure is reported
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CheckCrc(void)
{
  Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_2();
  Mt_SysCrc_SysCrc_RomSegs_CheckCrc_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test the case when the swap of the value got from the ROM-Address is not required
///                        and it is a valid value
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                             = 0;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = FALSE;
/// \input  SysCrc_RomSegs_CatchCrc_RetVal                                     = 0;
/// \input  SysCrc_ulRomCalcCRC_Var1                                           = SYS_CRC_APP_ROM_CALC_CRC;
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile       = FALSE
/// \output SysCrc_RomSegs_CatchCrc_RetVal = SYS_CRC_APP_ROM_CALC_CRC
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                             = 0;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = FALSE;
  SysCrc_RomSegs_CatchCrc_RetVal                                     = 0;
  SysCrc_ulRomCalcCRC_Var1                                           = SYS_CRC_APP_ROM_CALC_CRC;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CatchCrc_RetVal = SysCrc_RomSegs_CatchCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,       FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_CatchCrc_RetVal, SYS_CRC_APP_ROM_CALC_CRC, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test the case when the swap of the value got from the ROM-Address is required
///                        and it is an invalid value
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                             = 1u
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = TRUE
/// \input  SysCrc_ulRomCalcCRC_Var1                                           = 0xffffffffu
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile       = TRUE
/// \output SysCrc_RomSegs_CatchCrc_RetVal = 0xffffffffu
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                          = 1u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc = TRUE;

  SysCrc_ulRomCalcCRC_Var1                                           = 0xffffffffu;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CatchCrc_RetVal = SysCrc_RomSegs_CatchCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,       TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_CatchCrc_RetVal, 0xffffffffu, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test the case when the swap of the value got from the ROM-Address is required
///                        and it is a valid value
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_ucRomSegmentIdx                                             = 1u
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = TRUE
/// \input  SysCrc_ulRomCalcCRC_Var1                                           = 0x000000f1u
/// \input  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC
///
/// - Expectations:
///
/// \output SysCrc_ucProbablyElfFile       = FALSE
/// \output SysCrc_RomSegs_CatchCrc_RetVal = 0xf1000000u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_ucRomSegmentIdx                                             = 1u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_boSwapCrc    = TRUE;

  SysCrc_ulRomCalcCRC_Var1                                           = 0x000000f1u;
  SysCrc_RomSegs_RomSegs[SysCrc_ucRomSegmentIdx].SysCrc_ulRomCalcCRC = pSysCrc_ulRomCalcCRC;
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_CatchCrc_RetVal = SysCrc_RomSegs_CatchCrc();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_ucProbablyElfFile,       FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_CatchCrc_RetVal, 0xf1000000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_CatchCrc
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test the case when the swap of the value got from the ROM-Address is required
///                        and it is a valid value
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_CatchCrc(void)
{
  Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_2();
  Mt_SysCrc_SysCrc_RomSegs_CatchCrc_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_Dma_Transfer
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_Dma_Transfer called the CddDma_StartJob function
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_Dma_Transfer_Param1 = SYS_CRC_APP_START;
/// \input  SysCrc_Dma_Transfer_Param2 = CRC_BASE;
/// \input  SysCrc_Dma_Transfer_Param3 = 0x1FE;
/// \input  CddDma_StartJob_HitCount   = 0u;
///
/// - Expectations:
///
/// \output CddDma_StartJob_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_Dma_Transfer(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_Dma_Transfer_Param1 = SYS_CRC_APP_START;
  SysCrc_Dma_Transfer_Param2 = CRC_BASE;
  SysCrc_Dma_Transfer_Param3 = 0x1FE;
  CddDma_StartJob_HitCount   = 0u;
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_Dma_Transfer(SysCrc_Dma_Transfer_Param1, SysCrc_Dma_Transfer_Param2, SysCrc_Dma_Transfer_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,       1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_Crc32_Vector_AUTOSAR started calculating the Hw Crc
///                        if the length of the segment is higher than the maximum DMA transfer size
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = SYS_CRC_APP_CRC_OFFSET;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3    = 0u;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
/// \input  SysCrc_boCRCCalcStarted                       = 0u;
/// \input  SysCrc_ulRomAddress                           = 0u;
/// \input  SysCrc_ulRomLength                            = 0u;
/// \input  SysCrc_boCRCCalcFinished                      = FALSE;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = FALSE
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3 = 0u
/// \output SysCrc_ulRomAddress                        = SYS_CRC_APP_START
/// \output SysCrc_boCRCCalcStarted                    = TRUE
/// \output SysCrc_ulRomLength                         = SYS_CRC_APP_CRC_OFFSET
/// \output SysCrc_boCRCCalcFinished                   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = SYS_CRC_APP_CRC_OFFSET;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3    = 0u;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
  SysCrc_boCRCCalcStarted                       = 0u;
  SysCrc_ulRomAddress                           = 0u;
  SysCrc_ulRomLength                            = 0u;
  SysCrc_boCRCCalcFinished                      = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = SysCrc_RomSegs_Crc32_Vector_AUTOSAR(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3, 0u, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcStarted,                    TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress,                        SYS_CRC_APP_START, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomLength,                         SYS_CRC_APP_CRC_OFFSET, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,                   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_Crc32_Vector_AUTOSAR started calculating the Hw Crc
///                        if the length of the segment is lower than the maximum DMA transfer size
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = 0x100;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3    = 0u;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
/// \input  SysCrc_boCRCCalcStarted                       = 0u;
/// \input  SysCrc_ulRomAddress                           = 0u;
/// \input  SysCrc_ulRomLength                            = 0u;
/// \input  SysCrc_boCRCCalcFinished                      = FALSE;
/// \input  CddDma_StartJob_HitCount                      = 1u;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = FALSE
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3 = 0u
/// \output SysCrc_ulRomAddress                        = SYS_CRC_APP_START
/// \output SysCrc_boCRCCalcStarted                    = TRUE
/// \output SysCrc_ulRomLength                         = 0x100
/// \output SysCrc_boCRCCalcFinished                   = FALSE
/// \output CddDma_StartJob_HitCount                   = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = 0x100;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3    = 0u;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
  SysCrc_boCRCCalcStarted                       = 0u;
  SysCrc_ulRomAddress                           = 0u;
  SysCrc_ulRomLength                            = 0u;
  SysCrc_boCRCCalcFinished                      = FALSE;
  CddDma_StartJob_HitCount                      = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = SysCrc_RomSegs_Crc32_Vector_AUTOSAR(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3, 0u, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcStarted,                    TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress,                        SYS_CRC_APP_START, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomLength,                         0x100, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,                   FALSE, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount,                   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_Crc32_Vector_AUTOSAR finished calculating and 
///                        wait for the next segment
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = SYS_CRC_APP_CRC_OFFSET;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3    = 0u;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
/// \input  SysCrc_boCRCCalcStarted                       = TRUE;
/// \input  SysCrc_ulRomAddress                           = 0u;
/// \input  SysCrc_ulRomLength                            = 0u;
/// \input  SysCrc_boCRCCalcFinished                      = FALSE;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = FALSE
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3 = 0u
/// \output SysCrc_ulRomAddress                        = 0u
/// \output SysCrc_boCRCCalcStarted                    = TRUE
/// \output SysCrc_ulRomLength                         = 0u
/// \output SysCrc_boCRCCalcFinished                   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = 0x100;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3    = 0u;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
  SysCrc_boCRCCalcStarted                       = TRUE;
  SysCrc_ulRomAddress                           = 0u;
  SysCrc_ulRomLength                            = 0u;
  SysCrc_boCRCCalcFinished                      = FALSE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = SysCrc_RomSegs_Crc32_Vector_AUTOSAR(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3, 0u, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcStarted,                    TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress,                        0u, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomLength,                         0u, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,                   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_RomSegs_Crc32_Vector_AUTOSAR finished calculating the Hw Crc
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = SYS_CRC_APP_CRC_OFFSET;
/// \input  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
/// \input  CRC_DRV_GetCrcResult_RetVal                   = 0x1234;
/// \input  CRC_SetSeedReg_Param1                         = 0xFFFFFFFF;
/// \input  SysCrc_boCRCCalcStarted                       = 0u;
/// \input  SysCrc_ulRomAddress                           = 0u;
/// \input  SysCrc_ulRomLength                            = 0u;
/// \input  SysCrc_boCRCCalcFinished                      = TRUE;
/// \input    CRC_SetSeedReg_HitCount                     = 0u;
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = TRUE
/// \output SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3 = 0x1234
/// \output SysCrc_ulRomAddress                        = 0u
/// \output SysCrc_boCRCCalcStarted                    = FALSE
/// \output SysCrc_ulRomLength                         = 0u
/// \output SysCrc_boCRCCalcFinished                   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1    = SYS_CRC_APP_START;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2    = SYS_CRC_APP_CRC_OFFSET;
  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal    = 0u;
  CRC_DRV_GetCrcResult_RetVal                   = 0x1234;
  CRC_SetSeedReg_Param1                         = 0xFFFFFFFF;
  CRC_SetSeedReg_HitCount                       = 0u;
  SysCrc_boCRCCalcStarted                       = 0u;
  SysCrc_ulRomAddress                           = 0u;
  SysCrc_ulRomLength                            = 0u;
  SysCrc_boCRCCalcFinished                      = TRUE;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal = SysCrc_RomSegs_Crc32_Vector_AUTOSAR(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param1, SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param2, &SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_Crc32_Vector_AUTOSAR_Param3, 0x1234, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcStarted,                    FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress,                        0u, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomLength,                         0u, == );
  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished,                   FALSE, == );
  AL_UNITTEST_CHECK(CRC_SetSeedReg_HitCount,                    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test if the SysCrc_RomSegs_Crc32_Vector_AUTOSAR finished calculating the Hw Crc
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR(void)
{
  Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_1();
  Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_2();
  Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_3();
  Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_DmaNotification_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_DmaNotification set correctly the global
///                        variables when the CRC calculation is finished
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_boCRCCalcFinished   = 0u
/// \input  SysCrc_ulRomAddress        = 0u
/// \input  SysCrc_ulRomLength         = 0u
///
/// - Expectations:
///
/// \output SysCrc_boCRCCalcFinished       = 1u
/// \output SysCrc_ulRomAddress            = 0u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_DmaNotification_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_boCRCCalcFinished   = 0u;
  SysCrc_ulRomAddress        = 0u;
  SysCrc_ulRomLength         = 0u;
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_DmaNotification();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished ,       1u, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress ,            0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_DmaNotification_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_DmaNotification function call corectly
///                        SysCrc_Dma_Transfer function when the last block was not
///                         reached
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_boCRCCalcFinished   = 0u
/// \input  SysCrc_ulRomAddress        = 0u
/// \input  SysCrc_ulRomLength         = SYS_CRC_APP_CRC_OFFSET
/// \input  CddDma_StartJob_HitCount   = 0u;
///
/// - Expectations:
///
/// \output SysCrc_boCRCCalcFinished       = 0u
/// \output SysCrc_ulRomAddress            = 0x1FEu
/// \output SysCrc_ulRomLength             = 0xCEDFC
/// \output CddDma_StartJob_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_DmaNotification_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_boCRCCalcFinished     = 0u;
  SysCrc_ulRomAddress          = 0u;
  SysCrc_ulRomLength           = SYS_CRC_APP_CRC_OFFSET;
  CddDma_StartJob_HitCount     = 0u;
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_DmaNotification();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished ,       0u, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress ,            0x1FEu, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomLength ,             0xD9DFC, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount ,       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_DmaNotification_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if the SysCrc_DmaNotification function call corectly
///                         SysCrc_Dma_Transfer function
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_boCRCCalcFinished   = 0u
/// \input  SysCrc_ulRomAddress        = 0u
/// \input  SysCrc_ulRomLength         = 0x200
/// \input  CddDma_StartJob_HitCount   = 0u;
///
/// - Expectations:
///
/// \output SysCrc_boCRCCalcFinished       = FALSE
/// \output SysCrc_ulRomAddress            = 0x1FEu
/// \output SysCrc_ulRomLength             = 0u
/// \output CddDma_StartJob_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_DmaNotification_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_boCRCCalcFinished     = 0u;
  SysCrc_ulRomAddress          = 0u;
  SysCrc_ulRomLength           = 0x200;
  CddDma_StartJob_HitCount     = 0u;
  
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_DmaNotification();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_boCRCCalcFinished ,       FALSE, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomAddress ,            0x1FEu, == );
  AL_UNITTEST_CHECK(SysCrc_ulRomLength ,             0u, == );
  AL_UNITTEST_CHECK(CddDma_StartJob_HitCount ,       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_DmaNotification
///
/// \Functional Safety: ASIL_B
///
/// \Test Case Description
///    - Test subject:  Test if the SysCrc_DmaNotification function call corectly
///                         SysCrc_Dma_Transfer function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_DmaNotification(void)
{
  Mt_SysCrc_SysCrc_DmaNotification_TestCase_1();
  Mt_SysCrc_SysCrc_DmaNotification_TestCase_2();
  Mt_SysCrc_SysCrc_DmaNotification_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_SysCrc_SysCrc_RomSegs_GetCalibState
///
/// \Test Case Description
///        - Test subject: Test that the function saves the current state of the CRC 
///                        init and fail status
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Functional Safety: ASIL_B
///
/// - Preconditions:
///
/// \input  SysCrc_RomSegs_GetCalibState_Param1.boCalibCheckInitStatus = 0u
/// \input  SysCrc_RomSegs_GetCalibState_Param1.boCalibFailStatus      = 0u
/// \input  SysCrc_boCalibCrcCheckInit  = TRUE
/// \input  SysCrc_boCalibCrcStatus     = TRUE
///
/// - Expectations:
///
/// \output SysCrc_RomSegs_GetCalibState_Param1.boCalibCheckInitStatus = TRUE
/// \output SysCrc_RomSegs_GetCalibState_Param1.boCalibFailStatus      = TRUE
///
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_GetCalibState(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_GetCalibState_Param1.boCalibCheckInitStatus = 0u;
  SysCrc_RomSegs_GetCalibState_Param1.boCalibFailStatus      = 0u;
  SysCrc_boCalibCrcCheckInit  = TRUE;
  SysCrc_boCalibCrcStatus     = TRUE;
  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  SysCrc_RomSegs_GetCalibState(&SysCrc_RomSegs_GetCalibState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SysCrc_RomSegs_GetCalibState_Param1.boCalibCheckInitStatus,       TRUE, == );
  AL_UNITTEST_CHECK(SysCrc_RomSegs_GetCalibState_Param1.boCalibFailStatus,            TRUE, == );
}

//-----------------------------------------------------------------------------
/// \brief Mt_SysCrc_SysCrc_RomSegs_InitRomSegMem
///
/// \descr Rom Seg local initialization
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_SysCrc_SysCrc_RomSegs_InitRomSegMem(void)
{
  SysCrc_RomSegs_RomSegs[0].SysCrc_ulStartAddrOfSegment = (uint32)&PC_MemBlock[0];
  SysCrc_RomSegs_RomSegs[0].SysCrc_ulSizeOfSegment = (uint32)&PC_MemBlock[32] - (uint32)&PC_MemBlock[0] - 6u;
  SysCrc_RomSegs_RomSegs[0].SysCrc_boSwapCrc = FALSE;
  SysCrc_RomSegs_RomSegs[0].SysCrc_unDtc = 151u;
  SysCrc_RomSegs_RomSegs[0].SysCrc_ulRomCalcCRC = (uint32)&PC_MemBlock[32] - 6u;
  SysCrc_RomSegs_RomSegs[0].SysCrc_pfnCrcFailure = EcuM_FlashCrcFailure_Indication;
  SysCrc_RomSegs_RomSegs[1].SysCrc_ulStartAddrOfSegment = (uint32)&PC_MemBlock[32];
  SysCrc_RomSegs_RomSegs[1].SysCrc_ulSizeOfSegment = (uint32)&PC_MemBlock[64] - (uint32)&PC_MemBlock[32] - 6u;
  SysCrc_RomSegs_RomSegs[1].SysCrc_boSwapCrc = FALSE;
  SysCrc_RomSegs_RomSegs[1].SysCrc_unDtc = 153u;
  SysCrc_RomSegs_RomSegs[1].SysCrc_ulRomCalcCRC = (uint32)&PC_MemBlock[32] - 6u;
  SysCrc_RomSegs_RomSegs[1].SysCrc_pfnCrcFailure = SysCrc_RomSegs_RomSegCalCbStatus;
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
  ALUnitTest_AddFunction("Mt_SysCrc_riSysCrc_Init",                           Mt_SysCrc_riSysCrc_Init);
  ALUnitTest_AddFunction("Mt_rpSysCrc_Cycle0",                                Mt_rpSysCrc_Cycle0);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_Init",                     Mt_SysCrc_SysCrc_RomSegs_Init);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus",        Mt_SysCrc_SysCrc_RomSegs_GetCalibCrcStatus);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_CallbackFunction",         Mt_SysCrc_SysCrc_RomSegs_CallbackFunction);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_InitCRC",                  Mt_SysCrc_SysCrc_RomSegs_InitCRC);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_DoCRC",                    Mt_SysCrc_SysCrc_RomSegs_DoCRC);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment",             Mt_SysCrc_SysCrc_RomSegs_DoCRCSegment);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck",          Mt_SysCrc_SysCrc_RomSegs_SegmentCrcCheck);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_CheckCrc",                 Mt_SysCrc_SysCrc_RomSegs_CheckCrc);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_CatchCrc",                 Mt_SysCrc_SysCrc_RomSegs_CatchCrc);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_Dma_Transfer",                     Mt_SysCrc_SysCrc_Dma_Transfer);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR",     Mt_SysCrc_SysCrc_RomSegs_Crc32_Vector_AUTOSAR);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_DmaNotification",                  Mt_SysCrc_SysCrc_DmaNotification);
  ALUnitTest_AddFunction("Mt_SysCrc_SysCrc_RomSegs_GetCalibState",            Mt_SysCrc_SysCrc_RomSegs_GetCalibState);
}
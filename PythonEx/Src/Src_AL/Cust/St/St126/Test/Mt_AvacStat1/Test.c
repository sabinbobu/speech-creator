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
///        Cust/St/St126/App/Swc/AfsMaster/AvacStat1:
///             -AvacStat1.c
///             -AvacStat1Util.c
///             -AvacStat1Init.c
///             -AvacStat1Data.c
///             -ctaaAvacStat1.c
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
/// \Test Case : Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets the according DTC (ZERO_LVL_PROG Id)
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  NvmBlockDeltaPwmPara.ucZeroLevProg = 0x00u;
/// \input  Dem_SetEventStatus_HitCount        = 0u;
/// \input  Dem_SetEventStatus_Param1          = 0u;
/// \input  Dem_SetEventStatus_Param2          = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount        = 1u 
/// \output Dem_SetEventStatus_Param1          = ZERO_LVL_PROG 
/// \output Dem_SetEventStatus_Param2          = DEM_EVENT_STATUS_FAILED 
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_1(void)
{

  //Step 1: Set pre-conditions
  NvmBlockDeltaPwmPara.ucZeroLevProg = 0x00u;

  //Step 2) Assign Input values
  Dem_SetEventStatus_HitCount        = 0u;
  Dem_SetEventStatus_Param1          = 0u;
  Dem_SetEventStatus_Param2          = 0u;

  //Step 3) Call FUT
  AvacStat1_CheckZeroLvl();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              ZERO_LVL_PROG, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,    DEM_EVENT_STATUS_FAILED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function clears the according DTC (ZERO_LVL_PROG Id)
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
/// \input  Dem_SetEventStatus_HitCount        = 0u;
/// \input  Dem_SetEventStatus_Param1          = 0u;
/// \input  Dem_SetEventStatus_Param2          = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount        = 1u 
/// \output Dem_SetEventStatus_Param1          = ZERO_LVL_PROG 
/// \output Dem_SetEventStatus_Param2          = DEM_EVENT_STATUS_PASSED 
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;

  //Step 2) Assign Input values
  Dem_SetEventStatus_HitCount        = 0u;
  Dem_SetEventStatus_Param1          = 0u;
  Dem_SetEventStatus_Param2          = 0u;

  //Step 3) Call FUT
  AvacStat1_CheckZeroLvl();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              ZERO_LVL_PROG, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,    DEM_EVENT_STATUS_PASSED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function filters value
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Util_Order1Filter_Param1 = 1u;
/// \input  AvacStat1Util_Order1Filter_Param2 = 0u;
/// \input  AvacStat1Util_Order1Filter_Param3 = 1u;
///
/// - Expectations:
///
/// \output AvacStat1Util_Order1Filter_Param1 = 0u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1Util_Order1Filter_Param2 = 0u;
  AvacStat1Util_Order1Filter_Param3 = 1u;

  //Step 2) Assign Input values
  AvacStat1Util_Order1Filter_Param1 = 1u;

  //Step 3) Call FUT
  AvacStat1Util_Order1Filter(&AvacStat1Util_Order1Filter_Param1, AvacStat1Util_Order1Filter_Param2, AvacStat1Util_Order1Filter_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Util_Order1Filter_Param1, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function does not filter value when beta = 0
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Util_Order1Filter_Param1 = 1u;
/// \input  AvacStat1Util_Order1Filter_Param2 = 0u;
/// \input  AvacStat1Util_Order1Filter_Param3 = 0u;
///
/// - Expectations:
///
/// \output AvacStat1Util_Order1Filter_Param1 = 1u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Util_Order1Filter_Param1 = 1u;
  AvacStat1Util_Order1Filter_Param2 = 0u;
  AvacStat1Util_Order1Filter_Param3 = 0u;

  //Step 3) Call FUT
  AvacStat1Util_Order1Filter(&AvacStat1Util_Order1Filter_Param1, AvacStat1Util_Order1Filter_Param2, AvacStat1Util_Order1Filter_Param3);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Util_Order1Filter_Param1, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Util_Order1FilterInit_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function Initialize filter variable
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Util_Order1FilterInit_Param1 = 1u
/// \input  AvacStat1Util_Order1FilterInit_Param2 = 1u
///
/// - Expectations:
///
/// \output AvacStat1Util_Order1FilterInit_Param1 = 512u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Util_Order1FilterInit_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Util_Order1FilterInit_Param1 = 1u;
  AvacStat1Util_Order1FilterInit_Param2 = 1u;

  //Step 3) Call FUT
  AvacStat1Util_Order1FilterInit(&AvacStat1Util_Order1FilterInit_Param1, AvacStat1Util_Order1FilterInit_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Util_Order1FilterInit_Param1, 512u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Util_Order1FilterValue_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns value after scaling
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Util_Order1FilterValue_Param1 = 256u;
/// \input  AvacStat1Util_Order1FilterValue_RetVal = 0u;
///
/// - Expectations:
///
/// \output AvacStat1Util_Order1FilterValue_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Util_Order1FilterValue_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Util_Order1FilterValue_Param1 = 256u;
  AvacStat1Util_Order1FilterValue_RetVal = 0u;

  //Step 3) Call FUT
  AvacStat1Util_Order1FilterValue_RetVal = AvacStat1Util_Order1FilterValue(&AvacStat1Util_Order1FilterValue_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Util_Order1FilterValue_RetVal, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test ASL phase read interface in ASL adjustment phase
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE  = eDcmPhase_Adj;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 0u;
/// \input  AvacStat1Data_ReadAslPhase_Param1                         = 255u;
///
/// - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 1u;
/// \output AvacStat1Data_ReadAslPhase_Param1                         = eAvacStat1State_Adj;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE  = eDcmPhase_Adj;

  //Step 2) Assign Input values
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 0u;
  AvacStat1Data_ReadAslPhase_Param1                         = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ReadAslPhase(&AvacStat1Data_ReadAslPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadAslPhase_Param1,         eAvacStat1State_Adj, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject: Test ASL phase read interface ASL fail phase
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE  = eDcmPhase_Fail;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 0u;
/// \input  AvacStat1Data_ReadAslPhase_Param1                         = 255u;
///
/// - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 1u;
/// \output AvacStat1Data_ReadAslPhase_Param1                         = eAvacStat1State_Fail;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE  = eDcmPhase_Fail;

  //Step 2) Assign Input values
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 0u;
  AvacStat1Data_ReadAslPhase_Param1                         = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ReadAslPhase(&AvacStat1Data_ReadAslPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadAslPhase_Param1,        eAvacStat1State_Fail, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test ASL phase read interface is ASL init phase
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE  = eDcmPhase_Init;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 0u;
/// \input  AvacStat1Data_ReadAslPhase_Param1                         = 255u;
///
/// - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 1u;
/// \output AvacStat1Data_ReadAslPhase_Param1                         = eAvacStat1State_Fail;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE  = eDcmPhase_Init;

  //Step 2) Assign Input values
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount           = 0u;
  AvacStat1Data_ReadAslPhase_Param1                         = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ReadAslPhase(&AvacStat1Data_ReadAslPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadAslPhase_Param1,        eAvacStat1State_Init, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test speed mode write interface for Low Speed configuration
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_AvacStat1_SpeedMode_Param1   = 255u;
/// \input  Rte_Write_AvacStat1_SpeedMode_HitCount = 0u;
/// \input  AvacStat1Data_WriteSpeedMode_Param1    = eLOW_SPEED;
///
/// - Expectations:
///
/// \output Rte_Write_AvacStat1_SpeedMode_Param1   = eDcm_LOW_SPEED;
/// \output Rte_Write_AvacStat1_SpeedMode_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Write_AvacStat1_SpeedMode_Param1   = 255u;
  Rte_Write_AvacStat1_SpeedMode_HitCount = 0u;
  AvacStat1Data_WriteSpeedMode_Param1    = eLOW_SPEED;

  //Step 3) Call FUT
  AvacStat1Data_WriteSpeedMode(&AvacStat1Data_WriteSpeedMode_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_HitCount,               1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_Param1,     eDcm_LOW_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test speed mode write interface for High Speed configuration
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_AvacStat1_SpeedMode_Param1   = 255u;
/// \input  Rte_Write_AvacStat1_SpeedMode_HitCount = 0u;
/// \input  AvacStat1Data_WriteSpeedMode_Param1    = eHIGH_SPEED;
///
/// - Expectations:
///
/// \output Rte_Write_AvacStat1_SpeedMode_Param1   = eDcm_HIGH_SPEED;
/// \output Rte_Write_AvacStat1_SpeedMode_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Write_AvacStat1_SpeedMode_Param1   = 255u;
  Rte_Write_AvacStat1_SpeedMode_HitCount = 0u;
  AvacStat1Data_WriteSpeedMode_Param1    = eHIGH_SPEED;

  //Step 3) Call FUT
  AvacStat1Data_WriteSpeedMode(&AvacStat1Data_WriteSpeedMode_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_HitCount,               1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_Param1,    eDcm_HIGH_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test speed mode write interface for Undefined Speed configuration
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_AvacStat1_SpeedMode_Param1   = 255u;
/// \input  Rte_Write_AvacStat1_SpeedMode_HitCount = 0u;
/// \input  AvacStat1Data_WriteSpeedMode_Param1    = eUNDEFINED;
///
/// - Expectations:
///
/// \output Rte_Write_AvacStat1_SpeedMode_Param1   = eDcm_UNDEF_SPEED;
/// \output Rte_Write_AvacStat1_SpeedMode_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Write_AvacStat1_SpeedMode_Param1   = 255u;
  Rte_Write_AvacStat1_SpeedMode_HitCount = 0u;
  AvacStat1Data_WriteSpeedMode_Param1    = eUNDEFINED;

  //Step 3) Call FUT
  AvacStat1Data_WriteSpeedMode(&AvacStat1Data_WriteSpeedMode_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_HitCount,               1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_Param1,   eDcm_UNDEF_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test avac out write interface for positive valid AVAC angle value
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver = 255u;
/// \input  Rte_Write_ppsAvacStat1Out_Port_Param1.State         = 255u;
/// \input  Rte_Write_ppsAvacStat1Out_Port_HitCount             = 0u;
/// \input  AvacStat1Data_WriteAvacOut_Param1.nAngle            = 1;
/// \input  AvacStat1Data_WriteAvacOut_Param1.eSigQty           = SIG_VALID;
///
/// - Expectations:
///
/// \output Rte_Write_ppsAvacStat1Out_Port_HitCount             = 1u;
/// \output Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver = 1;
/// \output Rte_Write_ppsAvacStat1Out_Port_Param1.State         = SIG_VALID;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver = 255u;
  Rte_Write_ppsAvacStat1Out_Port_Param1.State         = 255u;
  Rte_Write_ppsAvacStat1Out_Port_HitCount             = 0u;
  AvacStat1Data_WriteAvacOut_Param1.nAngle            = 1;
  AvacStat1Data_WriteAvacOut_Param1.eSigQty           = SIG_VALID;

  //Step 3) Call FUT
  AvacStat1Data_WriteAvacOut(&AvacStat1Data_WriteAvacOut_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacStat1Out_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver, 1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacStat1Out_Port_Param1.State, SIG_VALID, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test avac out write interface for negative valid AVAC angle value
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver = 255u;
/// \input  Rte_Write_ppsAvacStat1Out_Port_Param1.State         = 255u;
/// \input  Rte_Write_ppsAvacStat1Out_Port_HitCount             = 0u;
/// \input  AvacStat1Data_WriteAvacOut_Param1.nAngle            = -1;
/// \input  AvacStat1Data_WriteAvacOut_Param1.eSigQty           = SIG_VALID;
///
/// - Expectations:
///
/// \output Rte_Write_ppsAvacStat1Out_Port_HitCount             = 1u;
/// \output Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver = -1;
/// \output Rte_Write_ppsAvacStat1Out_Port_Param1.State         = SIG_VALID;
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver = 255u;
  Rte_Write_ppsAvacStat1Out_Port_Param1.State         = 255u;
  Rte_Write_ppsAvacStat1Out_Port_HitCount             = 0u;
  AvacStat1Data_WriteAvacOut_Param1.nAngle            = -1;
  AvacStat1Data_WriteAvacOut_Param1.eSigQty           = SIG_VALID;

  //Step 3) Call FUT
  AvacStat1Data_WriteAvacOut(&AvacStat1Data_WriteAvacOut_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacStat1Out_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacStat1Out_Port_Param1.Position->Ver, -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacStat1Out_Port_Param1.State, SIG_VALID, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ReadSpeed_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test speed and acceleration read interface
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  AvacStat1Data_ReadSpeed_Param1.nSpeed                                      = 255u;
/// \input  AvacStat1Data_ReadSpeed_Param1.eSigQty                                     = 255u;
/// \input  AvacStat1Data_ReadSpeed_Param1.nAcceleration                               = 255u;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount        = 1u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount        = 1u
/// \output AvacStat1Data_ReadSpeed_Param1.nSpeed        = 100u
/// \output AvacStat1Data_ReadSpeed_Param1.eSigQty       = SIG_VALID
/// \output AvacStat1Data_ReadSpeed_Param1.nAcceleration = 50u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ReadSpeed_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
  AvacStat1Data_ReadSpeed_Param1.nSpeed                                      = 255u;
  AvacStat1Data_ReadSpeed_Param1.eSigQty                                     = 255u;
  AvacStat1Data_ReadSpeed_Param1.nAcceleration                               = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ReadSpeed(&AvacStat1Data_ReadSpeed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadSpeed_Param1.nSpeed,               100u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadSpeed_Param1.eSigQty,         SIG_VALID, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadSpeed_Param1.nAcceleration,         50u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ReadPitch_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test pitch read interface
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle           = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty          = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                = 0u;
/// \input  AvacStat1Data_ReadPitch_Param1.nAngle        = 255u;
/// \input  AvacStat1Data_ReadPitch_Param1.eSigQty       = 255u;
///
/// - Expectations:
///
/// \output te_Read_Pitch_Angle_HitCount                = 1u
/// \output vacStat1Data_ReadPitch_Param1.nAngle        = 100u
/// \output vacStat1Data_ReadPitch_Param1.eSigQty       = SIG_VALID
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ReadPitch_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle           = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty          = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                = 0u;
  AvacStat1Data_ReadPitch_Param1.nAngle        = 255u;
  AvacStat1Data_ReadPitch_Param1.eSigQty       = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ReadPitch(&AvacStat1Data_ReadPitch_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadPitch_Param1.nAngle,        100u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_ReadPitch_Param1.eSigQty,  SIG_VALID, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_GetAvacS_En_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns TRUE
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_GetAvacS_En_RetVal = FALSE;
///
/// - Expectations:
///
/// \output AvacStat1Data_GetAvacS_En_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_GetAvacS_En_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_GetAvacS_En_RetVal = FALSE;

  //Step 3) Call FUT
  AvacStat1Data_GetAvacS_En_RetVal = AvacStat1Data_GetAvacS_En();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_GetAvacS_En_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_GetAvacS_Ok_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns TRUE
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_GetAvacS_Ok_RetVal = FALSE;
///
/// - Expectations:
///
/// \output AvacStat1Data_GetAvacS_Ok_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_GetAvacS_Ok_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_GetAvacS_Ok_RetVal = FALSE;

  //Step 3) Call FUT
  AvacStat1Data_GetAvacS_Ok_RetVal = AvacStat1Data_GetAvacS_Ok();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_GetAvacS_Ok_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_GetLowBeamOn_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns TRUE
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_boLowBeamOn         = TRUE;
/// \input  AvacStat1Data_GetLowBeamOn_RetVal = FALSE;
///
/// - Expectations:
///
/// \output AvacStat1Data_GetLowBeamOn_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_GetLowBeamOn_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_boLowBeamOn         = TRUE;
  AvacStat1Data_GetLowBeamOn_RetVal = FALSE;

  //Step 3) Call FUT
  AvacStat1Data_GetLowBeamOn_RetVal = AvacStat1Data_GetLowBeamOn();
  AvacStat1Data_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_GetLowBeamOn_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns validity of coding (TRUE) when coding is valid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_ParaFct0_Param1 = eParaFct0_CodingDataValid;
/// \input  AvacStat1Data_ParaFct0_Param2 = &AvacStat1_Coding_Dummy;
/// \input  AvacStat1Data_ParaFct0_RetVal = 255u;
///
/// - Expectations:
///
/// \output AvacStat1Data_ParaFct0_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  AvacStat1Data_ParaFct0_Param2 = &AvacStat1_Coding_Dummy;
  AvacStat1Data_ParaFct0_RetVal = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ParaFct0_RetVal = AvacStat1Data_ParaFct0(AvacStat1Data_ParaFct0_Param1, AvacStat1Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_ParaFct0_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns validity of coding (FALSE) when coding is invalid by incorect starting address (NULL_PTR)
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_ParaFct0_Param1 = eParaFct0_CodingDataValid;
/// \input  AvacStat1Data_ParaFct0_Param2 = &NULL_PTR;
/// \input  AvacStat1Data_ParaFct0_RetVal = 255u;
///
/// - Expectations:
///
/// \output AvacStat1Data_ParaFct0_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  AvacStat1Data_ParaFct0_Param2 = NULL_PTR;
  AvacStat1Data_ParaFct0_RetVal = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ParaFct0_RetVal = AvacStat1Data_ParaFct0(AvacStat1Data_ParaFct0_Param1, AvacStat1Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_ParaFct0_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns validity of coding (FALSE) when coding is invalid by incorect starting address (NULL_PTR) and general invalidated (eParaFct0_CodingDataInvalid)
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input  AvacStat1Data_ParaFct0_Param2 = NULL_PTR;
/// \input  AvacStat1Data_ParaFct0_RetVal = 255u;
///
/// - Expectations:
///
/// \output AvacStat1Data_ParaFct0_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  AvacStat1Data_ParaFct0_Param2 = NULL_PTR;
  AvacStat1Data_ParaFct0_RetVal = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ParaFct0_RetVal = AvacStat1Data_ParaFct0(AvacStat1Data_ParaFct0_Param1, AvacStat1Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_ParaFct0_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns validity of coding
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1Data_ParaFct0_Param1 = 255u;
/// \input  AvacStat1Data_ParaFct0_Param2 = NULL_PTR;
/// \input  AvacStat1Data_ParaFct0_RetVal = 255u;
///
/// - Expectations:
///
/// \output AvacStat1Data_ParaFct0_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  AvacStat1Data_ParaFct0_Param1 = 255u;
  AvacStat1Data_ParaFct0_Param2 = NULL_PTR;
  AvacStat1Data_ParaFct0_RetVal = 255u;

  //Step 3) Call FUT
  AvacStat1Data_ParaFct0_RetVal = AvacStat1Data_ParaFct0(AvacStat1Data_ParaFct0_Param1, AvacStat1Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1Data_ParaFct0_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_Get_CodingPara_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function gets validity of coding (eParaFct0_CodingDataValid) when RTE reports coding valid and it has a valid starting address
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount                = 1u
/// \output AvacStat1Data_Get_CodingPara_Param1.eCodingState = eParaFct0_CodingDataValid
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_Get_CodingPara_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;

  //Step 3) Call FUT
  AvacStat1Data_Get_CodingPara(&AvacStat1Data_Get_CodingPara_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                                       1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_Get_CodingPara_Param1.eCodingState, eParaFct0_CodingDataValid, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1Data_CodingDataValidation_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function gets validity of coding (eParaFct0_CodingDataValid) when RTE reports coding valid and it has a valid starting address
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount                = 1u
/// \output AvacStat1Data_CodingDataValidation_RetVal        = eParaFct0_CodingDataValid
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1Data_CodingDataValidation_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //--

  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;

  //Step 3) Call FUT
  AvacStat1Data_CodingDataValidation_RetVal = AvacStat1Data_CodingDataValidation();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                                       1u, == );
  AL_UNITTEST_CHECK(AvacStat1Data_CodingDataValidation_RetVal,        eParaFct0_CodingDataValid, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets low speed mode
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED          = 2u;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE                   = eDcmPhase_Adj;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount                            = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  Rte_Write_AvacStat1_SpeedMode_Param1                                       = 255u;
/// \input  Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 1u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 1u
/// \output Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 1u
/// \output Rte_Write_AvacStat1_SpeedMode_Param1                                       = eDcm_LOW_SPEED
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED          = 2u;

  //Step 2) Assign Input values
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE                   = eDcmPhase_Adj;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
  Rte_Write_AvacStat1_SpeedMode_Param1                                       = 255u;
  Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 0u;

  //Step 3) Call FUT
  AvacStat1_SetSpeedMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_Param1,      eDcm_LOW_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets high speed mode
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED          = 2u;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE                   = eDcmPhase_Adj;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount                            = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 300u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  Rte_Write_AvacStat1_SpeedMode_Param1                                       = 255u;
/// \input  Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 1u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 1u
/// \output Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 1u
/// \output Rte_Write_AvacStat1_SpeedMode_Param1                                       = eDcm_HIGH_SPEED
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED           = 2u;

  //Step 2) Assign Input values
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE                   = eDcmPhase_Adj;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 300u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
  Rte_Write_AvacStat1_SpeedMode_Param1                                       = 255u;
  Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 0u;

  //Step 3) Call FUT
  AvacStat1_SetSpeedMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_Param1,     eDcm_HIGH_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets undefined speed mode
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED          = 2u;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE                   = eDcmPhase_Init;
/// \input  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount                            = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 300u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  Rte_Write_AvacStat1_SpeedMode_Param1                                       = 255u;
/// \input  Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 1u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 1u
/// \output Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 1u
/// \output Rte_Write_AvacStat1_SpeedMode_Param1                                       = eDcm_UNDEF_SPEED
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED = 2u;

  //Step 2) Assign Input value
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE                   = eDcmPhase_Init;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 300u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
  Rte_Write_AvacStat1_SpeedMode_Param1                                       = 255u;
  Rte_Write_AvacStat1_SpeedMode_HitCount                                     = 0u;

  //Step 3) Call FUT
  AvacStat1_SetSpeedMode();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_HitCount,                1u, == );
  AL_UNITTEST_CHECK(Rte_Write_AvacStat1_SpeedMode_Param1,    eDcm_UNDEF_SPEED, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Init_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test init function when ASL marked present in coding
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                         = 255u;
/// \input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                       = 255u;
/// \input  NvM_WriteBlock_HitCount                                   = 0u;
/// \input  NvM_WriteBlock_Param1                                     = 255;
/// \input  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = TRUE;
/// \input  AvacStat1_nAutoAngleMax                                   = 50;
/// \input  AvacStat1_nAutoAngleMin                                   = 50;
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount                          = 1u
/// \output NvmBlockDeltaPwmPara.eASL_Present                          = eASL_Present
/// \output NvmBlockDeltaPwmPara.eNVM_VAC_Input                        = eInput_HLS
/// \output NvM_WriteBlock_HitCount                                    = 1u
/// \output NvM_WriteBlock_Param1                                      = NvmBlockDeltaPwmParaId
/// \output AvacStat1_nAutoAngleMax                                    = 875
/// \output AvacStat1_nAutoAngleMin                                    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Init_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_nAutoAngleMax             = 50;
  AvacStat1_nAutoAngleMin             = 50;
  NvmBlockDeltaPwmPara.eASL_Present   = 255u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 255u;

  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;

  NvM_WriteBlock_HitCount                                   = 0u;
  NvM_WriteBlock_Param1                                     = 255;
  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = TRUE;

  //Step 3) Call FUT
  AvacStat1_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eASL_Present,         eASL_Present, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eNVM_VAC_Input,         eInput_HLS, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1,           NvmBlockDeltaPwmParaId, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMax,                            875, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMin,                              0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Init_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test init function when ASL marked absent in coding
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                         = 255u;
/// \input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                       = 255u;
/// \input  NvM_WriteBlock_HitCount                                   = 0u;
/// \input  NvM_WriteBlock_Param1                                     = 255;
/// \input  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = FALSE;
/// \input  AvacStat1_nAutoAngleMax                                   = 50;
/// \input  AvacStat1_nAutoAngleMin                                   = 50;
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount                          = 1u
/// \output NvmBlockDeltaPwmPara.eASL_Present                          = eASL_Absent
/// \output NvmBlockDeltaPwmPara.eNVM_VAC_Input                        = eInput_HLS
/// \output NvM_WriteBlock_HitCount                                    = 1u
/// \output NvM_WriteBlock_Param1                                      = NvmBlockDeltaPwmParaId
/// \output AvacStat1_nAutoAngleMax                                    = 875
/// \output AvacStat1_nAutoAngleMin                                    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Init_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_nAutoAngleMax             = 50;
  AvacStat1_nAutoAngleMin             = 50;
  NvmBlockDeltaPwmPara.eASL_Present   = 255u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 255u;

  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
  NvM_WriteBlock_HitCount                                   = 0u;
  NvM_WriteBlock_Param1                                     = 255;
  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = FALSE;

  //Step 3) Call FUT
  AvacStat1_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eASL_Present,          eASL_Absent, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eNVM_VAC_Input,         eInput_HLS, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1,           NvmBlockDeltaPwmParaId, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMax,                            875, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMin,                              0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Init_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test init function when coding is not valid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataInvalid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                         = 255u;
/// \input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                       = 255u;
/// \input  NvM_WriteBlock_HitCount                                   = 0u;
/// \input  NvM_WriteBlock_Param1                                     = 255;
/// \input  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = FALSE;
/// \input  AvacStat1_nAutoAngleMax                                   = 50;
/// \input  AvacStat1_nAutoAngleMin                                   = 50;
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount                          = 1u
/// \output NvmBlockDeltaPwmPara.eASL_Present                          = 255u
/// \output NvmBlockDeltaPwmPara.eNVM_VAC_Input                        = 255u
/// \output NvM_WriteBlock_HitCount                                    = 0u
/// \output NvM_WriteBlock_Param1                                      = 255u
/// \output AvacStat1_nAutoAngleMax                                    = 875
/// \output AvacStat1_nAutoAngleMin                                    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Init_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_nAutoAngleMax             = 50;
  AvacStat1_nAutoAngleMin             = 50;
  NvmBlockDeltaPwmPara.eASL_Present   = 255u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 255u;

  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;

  NvM_WriteBlock_HitCount                                   = 0u;
  NvM_WriteBlock_Param1                                     = 255;
  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = FALSE;

  //Step 3) Call FUT
  AvacStat1_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eASL_Present,                 255u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eNVM_VAC_Input,               255u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,                             0u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1,                             255u, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMax,                            875, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMin,                              0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to flag motor free without params filtering 
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byStaticFilterSampleTime         = 255u;
/// \input  AvacStat1_bySampleTimeLong                 = 255u;
/// \input  AvacStat1_byLwrRegulationExtendedMode      = 0x00u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter   = 0;
/// \input  AvacStat1_SetStaticFilterParameters_RetVal = FALSE;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode      = 0x08u
/// \output AvacStat1_nLwrStaticFilterServiceCounter   = 255u
/// \output AvacStat1_SetStaticFilterParameters_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byStaticFilterSampleTime         = 255u;
  AvacStat1_bySampleTimeLong                 = 255u;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode      = 0x00u;
  AvacStat1_nLwrStaticFilterServiceCounter   = 0;
  AvacStat1_SetStaticFilterParameters_RetVal = FALSE;

  //Step 3) Call FUT
  AvacStat1_SetStaticFilterParameters_RetVal = AvacStat1_SetStaticFilterParameters();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode,        0x08u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrStaticFilterServiceCounter,      255u, == );
  AL_UNITTEST_CHECK(AvacStat1_SetStaticFilterParameters_RetVal,    TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation motde to flag motor free with params filtering
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byStaticFilterSampleTime                      = 200u;
/// \input  AvacStat1_bySampleTimeLong                              = 255u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter                = 0;
/// \input  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;
/// \input  AvacStat1_nLwrConstantSpeedCounter                      = 0;
/// \input  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
/// \input  AvacStat1_byTstatic                                     = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 20u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode      = 0x08u
/// \output AvacStat1_nLwrStaticFilterServiceCounter   = 9U
/// \output AvacStat1_SetStaticFilterParameters_RetVal = FALSE
/// \output AvacStat1_nLwrConstantSpeedCounter         = 100u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byStaticFilterSampleTime                      = 200u;
  AvacStat1_bySampleTimeLong                              = 255u;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
  AvacStat1_nLwrStaticFilterServiceCounter                = 10;
  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;

  AvacStat1_nLwrConstantSpeedCounter                      = 0;
  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
  AvacStat1_byTstatic                                     = 0u;
  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 0u;
  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 20u;

  //Step 3) Call FUT
  AvacStat1_SetStaticFilterParameters_RetVal = AvacStat1_SetStaticFilterParameters();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode,        0x08u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrStaticFilterServiceCounter,        9u, == );
  AL_UNITTEST_CHECK(AvacStat1_SetStaticFilterParameters_RetVal,   FALSE, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrConstantSpeedCounter,             100, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function does not set regulation mode to flag motor free without params filtering
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byStaticFilterSampleTime                      = 200u;
/// \input  AvacStat1_bySampleTimeLong                              = 255u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter                = 0;
/// \input  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;
/// \input  AvacStat1_nLwrConstantSpeedCounter                      = 0;
/// \input  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
/// \input  AvacStat1_byTstatic                                     = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 0u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode      = 0x00u
/// \output AvacStat1_nLwrStaticFilterServiceCounter   = 9U
/// \output AvacStat1_SetStaticFilterParameters_RetVal = FALSE
/// \output AvacStat1_nLwrConstantSpeedCounter         = 100u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byStaticFilterSampleTime                      = 200u;
  AvacStat1_bySampleTimeLong                              = 255u;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
  AvacStat1_nLwrStaticFilterServiceCounter                = 10;
  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;

  AvacStat1_nLwrConstantSpeedCounter                      = 0;
  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
  AvacStat1_byTstatic                                     = 0u;
  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4]       = 5u;
  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 0u;

  //Step 3) Call FUT
  AvacStat1_SetStaticFilterParameters_RetVal = AvacStat1_SetStaticFilterParameters();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode,        0x00u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrStaticFilterServiceCounter,        9u, == );
  AL_UNITTEST_CHECK(AvacStat1_SetStaticFilterParameters_RetVal,   FALSE, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrConstantSpeedCounter,             100, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function does not set regulation motde to flag motor free without params filtering and different filter coeficients
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byStaticFilterSampleTime                      = 200u;
/// \input  AvacStat1_bySampleTimeLong                              = 255u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter                = 0;
/// \input  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;
/// \input  AvacStat1_nLwrConstantSpeedCounter                      = 0;
/// \input  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
/// \input  AvacStat1_byTstatic                                     = 20u;
/// \input  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 0u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode      = 0x00u
/// \output AvacStat1_nLwrStaticFilterServiceCounter   = 9U
/// \output AvacStat1_SetStaticFilterParameters_RetVal = FALSE
/// \output AvacStat1_nLwrConstantSpeedCounter         = 100u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byStaticFilterSampleTime                      = 200u;
  AvacStat1_bySampleTimeLong                              = 255u;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
  AvacStat1_nLwrStaticFilterServiceCounter                = 10;
  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;

  AvacStat1_nLwrConstantSpeedCounter                      = 0;
  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
  AvacStat1_byTstatic                                     = 20u;
  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4]       = 5u;
  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 0u;

  //Step 3) Call FUT
  AvacStat1_SetStaticFilterParameters_RetVal = AvacStat1_SetStaticFilterParameters();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode,        0x00u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrStaticFilterServiceCounter,        9u, == );
  AL_UNITTEST_CHECK(AvacStat1_SetStaticFilterParameters_RetVal,   FALSE, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrConstantSpeedCounter,             100, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function does not set regulation motde to flag motor free with params filtering and different filter coeficients
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byStaticFilterSampleTime                      = 200u;
/// \input  AvacStat1_bySampleTimeLong                              = 255u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter                = 0;
/// \input  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;
/// \input  AvacStat1_nLwrConstantSpeedCounter                      = 20;
/// \input  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
/// \input  AvacStat1_byTstatic                                     = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4]       = 5u;
/// \input  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 0u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode      = 0x00u
/// \output AvacStat1_nLwrStaticFilterServiceCounter   = 9U
/// \output AvacStat1_SetStaticFilterParameters_RetVal = FALSE
/// \output AvacStat1_nLwrConstantSpeedCounter         = 19
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byStaticFilterSampleTime                      = 200u;
  AvacStat1_bySampleTimeLong                              = 255u;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
  AvacStat1_nLwrStaticFilterServiceCounter                = 10;
  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;

  AvacStat1_nLwrConstantSpeedCounter                      = 20;
  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
  AvacStat1_byTstatic                                     = 20u;
  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[1]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[2]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[3]       = 5u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[4]       = 5u;
  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 0u;

  //Step 3) Call FUT
  AvacStat1_SetStaticFilterParameters_RetVal = AvacStat1_SetStaticFilterParameters();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode,        0x00u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrStaticFilterServiceCounter,        9u, == );
  AL_UNITTEST_CHECK(AvacStat1_SetStaticFilterParameters_RetVal,   FALSE, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrConstantSpeedCounter,              19, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode = Power on delay
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param3           = 0x02u;
/// \input  AvacStat1_byLwrRegulationExtendedMode = 0x00u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x40u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationExtendedMode = 0x00u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param3           = 0x02u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x40u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode = Freeze
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param3           = 0x01u;
/// \input  AvacStat1_byLwrRegulationExtendedMode = 0x00u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x20u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationExtendedMode = 0x00u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param3           = 0x01u;
  
  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x20u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to vehicle start
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 1u;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x04u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 10u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  AvacStat1_byLwrRegulationMode                                          = 5u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x02u
/// \output AvacStat1_byLwrRegulationMode         = 3u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 10u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 1u;
  AvacStat1_SetRegMode_Param3                                            = 0x04u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  AvacStat1_byLwrRegulationMode                                          = 5u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x02u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Acceleration
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 200u;
/// \input  AvacStat1_SetRegMode_Param2                                            = -10;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x05u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 1u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  NvmBlockStatAvac1Para.byAccFilterCoeff                                 = 1u;
/// \input  AvacStat1_LwrAccelerationFilter                                        = -100;
/// \input  AvacStat1_byLwrRegulationMode                                          = 3u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x00u
/// \output AvacStat1_byLwrRegulationMode         = 1u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 1u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 200u;
  AvacStat1_SetRegMode_Param2                                            = -10;
  AvacStat1_SetRegMode_Param3                                            = 0x05u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  NvmBlockStatAvac1Para.byAccFilterCoeff                                 = 1u;
  AvacStat1_LwrAccelerationFilter                                        = -100;
  AvacStat1_byLwrRegulationMode                                          = 3u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x00u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Zero Speed
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 1u;
/// \input  AvacStat1_SetRegMode_Param2                                            = 0;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x04u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED      = 10u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  AvacStat1_byLwrRegulationMode                                          = 5u;
/// \input  AvacStat1_nLwrTransientStateCounter                                    = 0u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x00u
/// \output AvacStat1_byLwrRegulationMode         = 5u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED       = 10u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 1u;
  AvacStat1_SetRegMode_Param2                                            = 0;
  AvacStat1_SetRegMode_Param3                                            = 0x04u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  AvacStat1_byLwrRegulationMode                                          = 5u;
  AvacStat1_nLwrTransientStateCounter                                    = 0u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x00u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            5u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Transient State when speed vehicle is availbale and grater than 0
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 1u;
/// \input  AvacStat1_SetRegMode_Param2                                            = 0;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x04u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED      = 10u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  AvacStat1_byLwrRegulationMode                                          = 5u;
/// \input  AvacStat1_nLwrTransientStateCounter                                    = 1u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x00u
/// \output AvacStat1_byLwrRegulationMode         = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_6(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED       = 10u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 1u;
  AvacStat1_SetRegMode_Param2                                            = 0;
  AvacStat1_SetRegMode_Param3                                            = 0x04u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x00u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  AvacStat1_byLwrRegulationMode                                          = 5u;
  AvacStat1_nLwrTransientStateCounter                                    = 1u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x00u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_7
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Below Min Speed
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 0u;
/// \input  AvacStat1_SetRegMode_Param2                                            = 0;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x04u
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x01u
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED      = 0u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 1u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  AvacStat1_byLwrRegulationMode                                          = 4u;
/// \input  AvacStat1_nLwrTransientStateCounter                                    = 0u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x01u
/// \output AvacStat1_byLwrRegulationMode         = 4u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_7(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED       = 0u;
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED  = 1u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 0u;
  AvacStat1_SetRegMode_Param2                                            = 0;
  AvacStat1_SetRegMode_Param3                                            = 0x04u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x01u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  AvacStat1_byLwrRegulationMode                                          = 4u;
  AvacStat1_nLwrTransientStateCounter                                    = 0u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x01u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            4u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_8
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Constant Speed
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 1u;
/// \input  AvacStat1_SetRegMode_Param2                                            = 1;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x00u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x01u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED      = 0u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  NvmBlockStatAvac1Para.byHighDynamicLimit                               = 2u;
/// \input  AvacStat1_byLwrRegulationMode                                          = 4u;
/// \input  AvacStat1_nLwrTransientStateCounter                                    = 0u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x01u
/// \output AvacStat1_byLwrRegulationMode         = 0u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_8(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED       = 0u;
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED  = 0u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 1u;
  AvacStat1_SetRegMode_Param2                                            = 1;
  AvacStat1_SetRegMode_Param3                                            = 0x00u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x01u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  NvmBlockStatAvac1Para.byHighDynamicLimit                               = 2u;
  AvacStat1_byLwrRegulationMode                                          = 4u;
  AvacStat1_nLwrTransientStateCounter                                    = 0u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x01u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_9
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Transient State when speed vehicle is not availbale or it is 0
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_SetRegMode_Param1                                            = 1u;
/// \input  AvacStat1_SetRegMode_Param2                                            = 1;
/// \input  AvacStat1_SetRegMode_Param3                                            = 0x00u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                                  = 0x01u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED      = 0u;
/// \input  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
/// \input  NvmBlockStatAvac1Para.byHighDynamicLimit                               = 2u;
/// \input  AvacStat1_byLwrRegulationMode                                          = 4u;
/// \input  AvacStat1_nLwrTransientStateCounter                                    = 1u;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode = 0x01u
/// \output AvacStat1_byLwrRegulationMode         = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_9(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_FROZEN_VEH_SPEED = 0u;
  AvacStat1_pCodingArea->AvacStp.DCMotorData.ucASL_HIGH_FROZEN_VEH_SPEED = 0u;

  //Step 2) Assign Input values
  AvacStat1_SetRegMode_Param1                                            = 1u;
  AvacStat1_SetRegMode_Param2                                            = 1;
  AvacStat1_SetRegMode_Param3                                            = 0x00u;
  AvacStat1_byLwrRegulationExtendedMode                                  = 0x01u;
  NvmBlockStatAvacPrj1Para.byMaxSpeed                                    = 4u;
  NvmBlockStatAvac1Para.byHighDynamicLimit                               = 2u;
  AvacStat1_byLwrRegulationMode                                          = 4u;
  AvacStat1_nLwrTransientStateCounter                                    = 1u;

  //Step 3) Call FUT
  AvacStat1_SetRegMode(AvacStat1_SetRegMode_Param1, AvacStat1_SetRegMode_Param2, AvacStat1_SetRegMode_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0x01u, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationMode,            2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation extanded mode is set to freeze\
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode = 80u;
/// \input  AvacStat1_GetHeadlightAngle_RetVal    = 0;
///
/// - Expectations:
///
/// \output AvacStat1_GetHeadlightAngle_RetVal    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationExtendedMode = 80u;

  //Step 2) Assign Input values
  AvacStat1_GetHeadlightAngle_RetVal    = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal, 0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation mode is set to Below Min Speed
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 1u;
/// \input  AvacStat1_byLwrRegulationMode                  = 4u;
/// \input  AvacStat1_nLwrTransientStateCounter            = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nLwrTransientStateCounter   = 10
/// \output AvacStat1_GetHeadlightAngle_RetVal    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 1u;
  AvacStat1_byLwrRegulationMode                  = 4u;
  AvacStat1_nLwrTransientStateCounter            = 0;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter, 10, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,   0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation mode is set to Vehicle Start
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 1u;
/// \input  AvacStat1_byLwrRegulationMode                  = 3u;
/// \input  AvacStat1_nLwrTransientStateCounter            = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_nAutoAngleGrad                       = 0;
/// \input  AvacStat1_nStaticAngle                         = 30;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nLwrTransientStateCounter   = 10
/// \output AvacStat1_nAutoAngleGrad              = 30
/// \output AvacStat1_GetHeadlightAngle_RetVal    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 1u;
  AvacStat1_byLwrRegulationMode                  = 3u;
  AvacStat1_nLwrTransientStateCounter            = 0;
  AvacStat1_nAutoAngleGrad                       = 0;
  AvacStat1_nStaticAngle                         = 30;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter, 10, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleGrad,            30, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,   0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation mode is set to Transient State and transient counter is grater than 0
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 1u;
/// \input  AvacStat1_byLwrRegulationMode                  = 2u;
/// \input  AvacStat1_nLwrTransientStateCounter            = 1;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nLwrTransientStateCounter   = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 1u;
  AvacStat1_byLwrRegulationMode                  = 2u;
  AvacStat1_nLwrTransientStateCounter            = 1;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter,  0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,   0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation mode is set to Transient State and transient counter is 0
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 1u;
/// \input  AvacStat1_byLwrRegulationMode                  = 2u;
/// \input  AvacStat1_nLwrTransientStateCounter            = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nLwrTransientStateCounter   = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 1u;
  AvacStat1_byLwrRegulationMode                  = 2u;
  AvacStat1_nLwrTransientStateCounter            = 0;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter,  0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,   0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation mode is set to Acceleration
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 1u;
/// \input  AvacStat1_byLwrRegulationMode                  = 1u;
/// \input  AvacStat1_nLwrTransientStateCounter            = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nLwrTransientStateCounter   = 10
/// \output AvacStat1_GetHeadlightAngle_RetVal    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_6(void)
{
  //Step 1: Set pre-conditions
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 1u;
  AvacStat1_byLwrRegulationMode                  = 1u;
  AvacStat1_nLwrTransientStateCounter            = 0;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter, 10, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,   0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_7
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to constant speed and filter constants are not valid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 1u;
/// \input  AvacStat1_byLwrRegulationMode                  = 0u;
/// \input  AvacStat1_nAutoAngle                           = 100;
/// \input  AvacStat1_nAutoAngleGrad                       = 0;
/// \input  AvacStat1_nStaticAngle                         = 0;
/// \input  AvacStat1_nAutoAngleMax                        = -10;
/// \input  AvacStat1_nAutoAngleMin                        = 10;
/// \input  AvacStat1_byStaticFilterSampleTime             = 255u;
/// \input  AvacStat1_bySampleTimeLong                     = 255u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter       = 0;
/// \input  AvacStat1_nLwrTransientStateCounter            = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 100
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_7(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationExtendedMode           = 1u;
  AvacStat1_byLwrRegulationMode                   = 0u;
  AvacStat1_nAutoAngle                            = 100;
  AvacStat1_nAutoAngleGrad                        = 0;
  AvacStat1_nStaticAngle                          = 0;
  AvacStat1_nAutoAngleMax                         = -10;
  AvacStat1_nAutoAngleMin                         = 10;
  AvacStat1_byStaticFilterSampleTime              = 255u;
  AvacStat1_bySampleTimeLong                      = 255u;
  AvacStat1_nLwrStaticFilterServiceCounter        = 0;
  AvacStat1_nLwrTransientStateCounter             = 0;
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,               100, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter,  0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal, -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_8
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to constant speed and filter constants are sustained
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode                   = 1u;
/// \input  AvacStat1_byLwrRegulationMode                           = 0u;
/// \input  AvacStat1_nAutoAngle                                    = 0;
/// \input  AvacStat1_nAutoAngleGrad                                = 100;
/// \input  AvacStat1_nStaticAngle                                  = 0;
/// \input  AvacStat1_nAutoAngleMax                                 = 10;
/// \input  AvacStat1_nAutoAngleMin                                 = -10;
/// \input  AvacStat1_byStaticFilterSampleTime                      = 200u;
/// \input  AvacStat1_bySampleTimeLong                              = 255u;
/// \input  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter                = 10;
/// \input  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;
/// \input  AvacStat1_nLwrConstantSpeedCounter                      = 0;
/// \input  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
/// \input  AvacStat1_byTstatic                                     = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
/// \input  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 0u;
/// \input  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 20u;
/// \input  NvmBlockStatAvac1Para.byStaticMinChange                 = 10000;
/// \input  AvacStat1_nActualHeadlightAngle                         = -10;
/// \input  AvacStat1_nLwrTransientStateCounter                     = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod          = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal                      = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
/// \output AvacStat1_byLwrRegulationExtendedMode        = 0x08u
/// \output AvacStat1_nLwrStaticFilterServiceCounter     = 9u
/// \output AvacStat1_nLwrConstantSpeedCounter           = 100
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_8(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationExtendedMode                   = 1u;
  AvacStat1_byLwrRegulationMode                           = 0u;
  AvacStat1_nAutoAngle                                    = 0;
  AvacStat1_nAutoAngleGrad                                = 100;
  AvacStat1_nStaticAngle                                  = 0;
  AvacStat1_nAutoAngleMax                                 = 10;
  AvacStat1_nAutoAngleMin                                 = -10;
  AvacStat1_byStaticFilterSampleTime                      = 200u;
  AvacStat1_bySampleTimeLong                              = 255u;
  AvacStat1_byLwrRegulationExtendedMode                   = 0x00u;
  AvacStat1_nLwrStaticFilterServiceCounter                = 10;
  AvacStat1_SetStaticFilterParameters_RetVal              = TRUE;
  AvacStat1_nLwrConstantSpeedCounter                      = 0;
  NvmBlockStatAvacPrj1Para.nConstantSpeedInterval         = 100;
  AvacStat1_byTstatic                                     = 0u;
  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtConstSpeed = 10u;
  NvmBlockStatAvacPrj1Para.abyFilterCoefToUnlock[0]       = 0u;
  NvmBlockStatAvacPrj1Para.byFilterCoefInc                = 20u;
  NvmBlockStatAvac1Para.byStaticMinChange                 = 10000;
  AvacStat1_nActualHeadlightAngle                         = -10;
  AvacStat1_nLwrTransientStateCounter                     = 0;
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod          = 10;

  //Step 2) Assign Input values
  AvacStat1_GetHeadlightAngle_RetVal                      = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                             0, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter,              0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,             -10, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode,        0x08u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrStaticFilterServiceCounter,        9u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrConstantSpeedCounter,             100, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_9
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to constant speed and filter constants are not sustained
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationExtendedMode         &= 0x00u;
/// \input  AvacStat1_byLwrRegulationMode                  = 0u;
/// \input  AvacStat1_nAutoAngle                           = 0;
/// \input  AvacStat1_nAutoAngleGrad                       = 0;
/// \input  AvacStat1_nStaticAngle                         = 0;
/// \input  AvacStat1_nAutoAngleMax                        = -10;
/// \input  AvacStat1_nAutoAngleMin                        = 10;
/// \input  AvacStat1_byStaticFilterSampleTime             = 250u;
/// \input  AvacStat1_bySampleTimeLong                     = 255u;
/// \input  AvacStat1_nLwrStaticFilterServiceCounter       = 2;
/// \input  AvacStat1_nLwrTransientStateCounter            = 0;
/// \input  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_byLwrRegulationExtendedMode        = 0
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_9(void)
{
  //Step 1: Set pre-conditions
   AvacStat1_byLwrRegulationExtendedMode         &= 0x00u;
  AvacStat1_byLwrRegulationMode                  = 0u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleGrad                       = 0;
  AvacStat1_nStaticAngle                         = 0;
  AvacStat1_nAutoAngleMax                        = -10;
  AvacStat1_nAutoAngleMin                        = 10;
  AvacStat1_byStaticFilterSampleTime             = 250u;
  AvacStat1_bySampleTimeLong                     = 255u;
  AvacStat1_nLwrStaticFilterServiceCounter       = 2;
  AvacStat1_nLwrTransientStateCounter            = 0;
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 0, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                  0, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter,   0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,  -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_10
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the healight angle
///                         when regulation mode is set to constant speed and
///                         the flag is above max speed
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   AvacStat1_byLwrRegulationExtendedMode          = 0x02u;
/// \input   AvacStat1_byLwrRegulationMode                  = 0u;
/// \input   AvacStat1_nAutoAngle                           = 0;
/// \input   AvacStat1_nAutoAngleGrad                       = 0;
/// \input   AvacStat1_nStaticAngle                         = 0;
/// \input   AvacStat1_nAutoAngleMax                        = -10;
/// \input   AvacStat1_nAutoAngleMin                        = 10;
/// \input   AvacStat1_byStaticFilterSampleTime             = 255u;
/// \input   AvacStat1_bySampleTimeLong                     = 255u;
/// \input   AvacStat1_nLwrStaticFilterServiceCounter       = 0;
/// \input   AvacStat1_nLwrTransientStateCounter            = 0;
/// \input   NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;
/// \input   AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                   = 0
/// \output AvacStat1_nLwrTransientStateCounter    = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal     = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_10(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;
  AvacStat1_byLwrRegulationMode                  = 0u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleGrad                       = 0;
  AvacStat1_nStaticAngle                         = 0;
  AvacStat1_nAutoAngleMax                        = -10;
  AvacStat1_nAutoAngleMin                        = 10;
  AvacStat1_byStaticFilterSampleTime             = 255u;
  AvacStat1_bySampleTimeLong                     = 255u;
  AvacStat1_nLwrStaticFilterServiceCounter       = 0;
  AvacStat1_nLwrTransientStateCounter            = 0;
  NvmBlockStatAvacPrj1Para.nTransientStatePeriod = 10;

  //Step 2) Assign Input values
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                 0, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrTransientStateCounter,  0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal, -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_11
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to zero speed and filter constants are not valid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_nAutoAngle                           = 0;
/// \input  AvacStat1_nAutoAngleMax                        = -10;
/// \input  AvacStat1_nAutoAngleMin                        = 10;
/// \input  AvacStat1_nLwrLoadChangeCounter                = 0;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 10
/// \output AvacStat1_byLwrRegulationExtendedMode        = 150u
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_11(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleMax                        = -10;
  AvacStat1_nAutoAngleMin                        = 10;
  AvacStat1_nLwrLoadChangeCounter                = 0;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                    10, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 150u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrLoadChangeCounter,          0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,     -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_12
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to zero speed and filter constants are sustained
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_nAutoAngle                           = 0;
/// \input  AvacStat1_nAutoAngleMax                        = 10;
/// \input  AvacStat1_nAutoAngleMin                        = -10;
/// \input  AvacStat1_nLwrLoadChangeCounter                = 0;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x80u;
/// \input  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_byLwrRegulationExtendedMode        = 148u
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_12(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleMax                        = 10;
  AvacStat1_nAutoAngleMin                        = -10;
  AvacStat1_nLwrLoadChangeCounter                = 0;
  AvacStat1_byLwrRegulationExtendedMode          = 0x80u;

  //Step 2) Assign Input values
  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                     0, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 148u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrLoadChangeCounter,          0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,       0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_13
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to zero speed and filter constants are not sustained
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_nAutoAngle                           = 0;
/// \input  AvacStat1_nAutoAngleMax                        = 10;
/// \input  AvacStat1_nAutoAngleMin                        = -10;
/// \input  AvacStat1_nLwrLoadChangeCounter                = 0;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x84u;
/// \input  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_byLwrRegulationExtendedMode        = 132u
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_13(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleMax                        = 10;
  AvacStat1_nAutoAngleMin                        = -10;
  AvacStat1_nLwrLoadChangeCounter                = 0;
  AvacStat1_byLwrRegulationExtendedMode          = 0x84u;

  //Step 2) Assign Input values
  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                     0, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 132u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrLoadChangeCounter,          0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,       0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_14
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to zero speed and filter constants are sustained with ref angle maximum
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_nAutoAngle                           = 0;
/// \input  AvacStat1_nAutoAngleMax                        = 10;
/// \input  AvacStat1_nAutoAngleMin                        = -10;
/// \input  AvacStat1_nLwrLoadChangeCounter                = 0;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x81u;
/// \input  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_byLwrRegulationExtendedMode        = 133u
/// \output AvacStat1_nLwrTransientStateCounter          = 0
/// \output AvacStat1_GetHeadlightAngle_RetVal           = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_14(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleMax                        = 10;
  AvacStat1_nAutoAngleMin                        = -10;
  AvacStat1_nLwrLoadChangeCounter                = 0;
  AvacStat1_byLwrRegulationExtendedMode          = 0x81u;

  //Step 2) Assign Input values
  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                     0, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 133u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrLoadChangeCounter,          0, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,       0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_15
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to zero speed and filter constants are sustained with ref angle minimum
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_nAutoAngle                           = 0;
/// \input  AvacStat1_nAutoAngleMax                        = 10;
/// \input  AvacStat1_nAutoAngleMin                        = -10;
/// \input  AvacStat1_nLwrLoadChangeCounter                = 2;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x81u;
/// \input  AvacStat1_nActualHeadlightAngle                = -100;
/// \input  NvmBlockStatAvac1Para.byDynamicMinChange       = 255u;
/// \input  AvacStat1_nRefAngle                            = -2550;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_byLwrRegulationExtendedMode        = 133u
/// \output AvacStat1_nLwrTransientStateCounter          = 1
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -100
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_15(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_nAutoAngle                           = 0;
  AvacStat1_nAutoAngleMax                        = 10;
  AvacStat1_nAutoAngleMin                        = -10;
  AvacStat1_nLwrLoadChangeCounter                = 2;
  AvacStat1_nActualHeadlightAngle                = -100;
  NvmBlockStatAvac1Para.byInterStopMinChange     = 255u;
  AvacStat1_nRefAngle                            = -2550;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationExtendedMode          = 0x81u;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                     0, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 133u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrLoadChangeCounter,          1, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,    -100, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_16
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns the calculated healight angle
///                         when regulation mode is set to zero speed and filter constants are sustained with ref angle variable
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                          = 5u;
/// \input  AvacStat1_nAutoAngle                                   = 0;
/// \input  AvacStat1_nAutoAngleMax                                = 10;
/// \input  AvacStat1_nAutoAngleMin                                = -10;
/// \input  AvacStat1_nLwrLoadChangeCounter                        = 2;
/// \input  AvacStat1_byLwrRegulationExtendedMode                  = 0x85u;
/// \input  AvacStat1_nActualHeadlightAngle                        = -100;
/// \input  NvmBlockStatAvac1Para.byDynamicMinChange               = 255u;
/// \input  AvacStat1_nRefAngle                                    = -2550;
/// \input  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtInterStop = 255u;
///
/// - Expectations:
///
/// \output AvacStat1_nAutoAngle                         = 0
/// \output AvacStat1_byLwrRegulationExtendedMode        = 133u
/// \output AvacStat1_nLwrTransientStateCounter          = 1
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -100
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_16(void)
{
  //Step 1: Set pre-conditions
  NvmBlockStatAvac1Para.byInterStopMinChange             = 255u;

  //Step 2) Assign Input values
  AvacStat1_byLwrRegulationMode                          = 5u;
  AvacStat1_nAutoAngle                                   = 0;
  AvacStat1_nAutoAngleMax                                = 10;
  AvacStat1_nAutoAngleMin                                = -10;
  AvacStat1_nLwrLoadChangeCounter                        = 2;
  AvacStat1_byLwrRegulationExtendedMode                  = 0x85u;
  AvacStat1_nActualHeadlightAngle                        = -100;
  AvacStat1_nRefAngle                                    = -2550;
  NvmBlockStatAvacPrj1Para.byStaticFilterCoefAtInterStop = 255u;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngle,                     0, == );
  AL_UNITTEST_CHECK(AvacStat1_byLwrRegulationExtendedMode, 133u, == );
  AL_UNITTEST_CHECK(AvacStat1_nLwrLoadChangeCounter,          1, == );
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,    -100, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_17
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns healight angle
///                         when regulation mode is out of range
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 9u;
/// \input  AvacStat1_nActualHeadlightAngle                = -101;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -101
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_17(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 9u;
  AvacStat1_nActualHeadlightAngle                = -101;

  //Step 2) Assign Input values
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,    -101, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_18
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns healight angle
///                         when low beam off in case of regulation extended mode valid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;
/// \input  AvacStat1Data_boLowBeamOn                      = FALSE;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_18 (void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;

  //Step 2) Assign Input values
  AvacStat1Data_boLowBeamOn                      = FALSE;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,    -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_19
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns healight angle
///                         when low beam off in case of regulation extended mode invalid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;
/// \input  AvacStat1Data_boLowBeamOn                      = FALSE;
/// \input  NvmBlockStatAvac1Para.byPowerOnMinChange       = 99999u;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_19 (void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_byLwrRegulationExtendedMode          = 0x02u;

  //Step 2) Assign Input values
  AvacStat1Data_boLowBeamOn                      = FALSE;
  NvmBlockStatAvac1Para.byPowerOnMinChange       = 99999u;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,    -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_20
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function directly returns healight angle
///                         when low beam off in case of regulation extended mode valid and angle initial angle 0
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_byLwrRegulationMode                  = 5u;
/// \input  AvacStat1_byLwrRegulationExtendedMode          = 0x10u;
/// \input  AvacStat1Data_boLowBeamOn                      = FALSE;
/// \input  AvacStat1_GetHeadlightAngle_RetVal             = 0;
///
/// - Expectations:
///
/// \output AvacStat1_GetHeadlightAngle_RetVal           = -10
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_20 (void)
{
  //Step 1: Set pre-conditions
  AvacStat1_byLwrRegulationMode                  = 5u;
  AvacStat1_byLwrRegulationExtendedMode          = 0x10u;

  //Step 2) Assign Input values
  AvacStat1Data_boLowBeamOn                      = FALSE;
  AvacStat1_GetHeadlightAngle_RetVal             = 0;

  //Step 3) Call FUT
  AvacStat1_GetHeadlightAngle_RetVal = AvacStat1_GetHeadlightAngle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(AvacStat1_GetHeadlightAngle_RetVal,    -10, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function checks zero lvl prog
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity         = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present  = eASL_Present;
/// \input  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
/// \input  Dem_SetEventStatus_HitCount        = 0u;
/// \input  Dem_SetEventStatus_Param1          = 0u;
/// \input  Dem_SetEventStatus_Param2          = 0u;
/// \input  AvacStat1_ucSamplingUnitTest       = 5u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount        = 1u
/// \output Dem_SetEventStatus_Param1          = ZERO_LVL_PROG
/// \output Dem_SetEventStatus_Param2          = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  NvmBlockDeltaPwmPara.eASL_Present  = eASL_Present;
  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;

  //Step 2) Assign Input values
  AvacStat1_boCodingValidity         = TRUE;
  Dem_SetEventStatus_HitCount        = 0u;
  Dem_SetEventStatus_Param1          = 0u;
  Dem_SetEventStatus_Param2          = 0u;
  AvacStat1_ucSamplingUnitTest       = 5u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              ZERO_LVL_PROG, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,    DEM_EVENT_STATUS_PASSED, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to No Dynamic
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_INVALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_INVALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_INVALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Normal based on ASL input absent and minimum adjusting counter
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Normal based on ASL input absent and maximum adjusting counter
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets regulation mode to Normal based on ASL input absent and maximum adjusting counter + negative safe angle
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000
/// \input  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000;
  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function does not set regulation mode when speed is at init
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_INIT;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000
/// \input  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_6(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_INIT;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000;
  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_7
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets FreezeRegulation when speed is SIG_SNA
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_SNA;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000
/// \input  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_7(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_SNA;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000;
  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_8
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function sets FreezeRegulation when speed is SIG_DISABLED
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = TRUE;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
/// \input  AvacStat1_ucSamplingUnitTest                                               = 1u;
/// \input  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
/// \input  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_DISABLED;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  NvmBlockStatAvacOp1Data.nSafetyAngle                                       = -10000
/// \input  NvmBlockStatAvacOp1Data.unAdjCounter                                       = 65535u
/// \input  NvmBlockStatAvacOp1Data.nHeadlightAngle                                    = -100
/// \input  AvacStat1_ucSafetyDelayUnitTest                                            = 0u;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 1u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 2u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 2u
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_8(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = TRUE;
  NvmBlockDeltaPwmPara.eASL_Present                                          = eASL_Absent;
  AvacStat1_ucSamplingUnitTest                                               = 1u;

  //Step 2) Assign Input values
  Rte_Read_Pitch_Angle_Param1.nAngle                                         = 100u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                                        = SIG_VALID;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 100u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = SIG_DISABLED;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 50u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  NvmBlockStatAvacOp1Data.nHeadlightAngle                                    = -100;
  AvacStat1_ucSafetyDelayUnitTest                                            = 0u;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,          2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,          2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_AvacStat1_Cycle0_TestCase_9
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function checks for coding validity when initially invalid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = FALSE;
/// \input  Dem_SetEventStatus_HitCount                                                = 0u;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                                          = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState                               = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks                  = &AvacStat1_Coding_Dummy;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 0u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 0u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 0u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 0u
/// \output Rte_Read_CodM_Pitch_Para_HitCount,           = 1u
/// \output AvacStat1_boCodingValidity,                  = eParaFct0_CodingDataValid
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_AvacStat1_Cycle0_TestCase_9(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = FALSE;

  //Step 2) Assign Input values
  Dem_SetEventStatus_HitCount                                                = 0u;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  Rte_Read_CodM_Pitch_Para_HitCount                                          = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState                               = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks                  = &AvacStat1_Coding_Dummy;

  //Step 3) Call FUT
  AvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        0u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                      0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,              0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,              0u, == );

  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(AvacStat1_boCodingValidity,  eParaFct0_CodingDataValid, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_rpAvacStat1_Cycle0_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test if function checks for coding validity when initially invalid
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  AvacStat1_boCodingValidity                                                 = FALSE;
/// \input  Dem_SetEventStatus_HitCount                                                = 0u;
/// \input  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// \input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                                          = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState                               = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks                  = &AvacStat1_Coding_Dummy;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_HitCount,                 = 0u
/// \output Rte_Read_Pitch_Angle_HitCount,               = 0u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount,       = 0u
/// \output Rte_Read_SigPrep_DynamicSigs_HitCount,       = 0u
/// \output Rte_Read_CodM_Pitch_Para_HitCount,           = 1u
/// \output AvacStat1_boCodingValidity,                  = eParaFct0_CodingDataValid
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_rpAvacStat1_Cycle0_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  AvacStat1_boCodingValidity                                                 = FALSE;

  //Step 2) Assign Input values
  Dem_SetEventStatus_HitCount                                                = 0u;
  Rte_Read_Pitch_Angle_HitCount                                              = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  Rte_Read_CodM_Pitch_Para_HitCount                                          = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState                               = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks                  = &AvacStat1_Coding_Dummy;

  //Step 3) Call FUT
  rpAvacStat1_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                        0u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,                      0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,              0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,              0u, == );

  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(AvacStat1_boCodingValidity,  eParaFct0_CodingDataValid, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_AvacStat1_riAvacStat1_Init_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///    - Test subject:  Test init function when ASL marked present in coding
///
///    - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;
/// \input  NvmBlockDeltaPwmPara.eASL_Present                         = 255u;
/// \input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                       = 255u;
/// \input  NvM_WriteBlock_HitCount                                   = 0u;
/// \input  NvM_WriteBlock_Param1                                     = 255;
/// \input  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = TRUE;
/// \input  AvacStat1_nAutoAngleMax                                   = 50;
/// \input  AvacStat1_nAutoAngleMin                                   = 50;
///
/// - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount                          = 1u
/// \output NvmBlockDeltaPwmPara.eASL_Present                          = eASL_Present
/// \output NvmBlockDeltaPwmPara.eNVM_VAC_Input                        = eInput_HLS
/// \output NvM_WriteBlock_HitCount                                    = 1u
/// \output NvM_WriteBlock_Param1                                      = NvmBlockDeltaPwmParaId
/// \output AvacStat1_nAutoAngleMax                                    = 875
/// \output AvacStat1_nAutoAngleMin                                    = 0
///
//-----------------------------------------------------------------------------
void Mt_AvacStat1_riAvacStat1_Init_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  NvmBlockDeltaPwmPara.eASL_Present                         = 255u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                       = 255u;
  NvM_WriteBlock_HitCount                                   = 0u;

  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_HitCount                         = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &AvacStat1_Coding_Dummy;

  NvM_WriteBlock_Param1                                     = 255;
  AvacStat1_Coding_Dummy.AvacStp.DCMotorData.ucAsl_Enable   = TRUE;

  AvacStat1_nAutoAngleMax                                   = 50;
  AvacStat1_nAutoAngleMin                                   = 50;

  //Step 3) Call FUT
  riAvacStat1_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eASL_Present,         eASL_Present, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.eNVM_VAC_Input,         eInput_HLS, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1,           NvmBlockDeltaPwmParaId, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMax,                            875, == );
  AL_UNITTEST_CHECK(AvacStat1_nAutoAngleMin,                              0, == );
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
  AvacStat1Data_ParaFct0(1, &AvacStat1_pCodingArea);
  
  ALUnitTest_AddFunction("Mt_AvacStat1_riAvacStat1_Init_TestCase_1",                     Mt_AvacStat1_riAvacStat1_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_rpAvacStat1_Cycle0_TestCase_1",                   Mt_AvacStat1_rpAvacStat1_Cycle0_TestCase_1);

  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_1",               Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_2",               Mt_AvacStat1_AvacStat1_CheckZeroLvl_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_1",               Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_2",               Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_3",               Mt_AvacStat1_AvacStat1_SetSpeedMode_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Init_TestCase_1",                       Mt_AvacStat1_AvacStat1_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Init_TestCase_2",                       Mt_AvacStat1_AvacStat1_Init_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Init_TestCase_3",                       Mt_AvacStat1_AvacStat1_Init_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_1",  Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_2",  Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_3",  Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_4",  Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_4);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_5",  Mt_AvacStat1_AvacStat1_SetStaticFilterParameters_TestCase_5);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_1",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_2",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_3",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_4",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_4);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_5",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_5);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_6",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_6);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_7",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_7);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_8",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_8);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_9",                 Mt_AvacStat1_AvacStat1_SetRegMode_TestCase_9);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_1",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_2",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_3",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_4",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_4);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_5",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_5);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_6",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_6);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_7",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_7);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_8",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_8);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_9",          Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_9);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_10",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_10);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_11",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_11);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_12",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_12);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_13",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_13);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_14",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_14);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_15",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_15);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_16",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_16);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_17",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_17);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_1",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_2",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_3",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_4",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_4);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_5",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_5);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_6",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_6);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_7",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_7);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_8",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_8);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_Cycle0_TestCase_9",                     Mt_AvacStat1_AvacStat1_Cycle0_TestCase_9);

  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_1",           Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_2",           Mt_AvacStat1_AvacStat1Util_Order1Filter_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Util_Order1FilterInit_TestCase_1",       Mt_AvacStat1_AvacStat1Util_Order1FilterInit_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Util_Order1FilterValue_TestCase_1",      Mt_AvacStat1_AvacStat1Util_Order1FilterValue_TestCase_1);
  
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_1",           Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_2",           Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_3",           Mt_AvacStat1_AvacStat1Data_ReadAslPhase_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ReadSpeed_TestCase_1",              Mt_AvacStat1_AvacStat1Data_ReadSpeed_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ReadPitch_TestCase_1",              Mt_AvacStat1_AvacStat1Data_ReadPitch_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_1",         Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_2",         Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_3",         Mt_AvacStat1_AvacStat1Data_WriteSpeedMode_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_1",           Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_2",           Mt_AvacStat1_AvacStat1Data_WriteAvacOut_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_GetAvacS_En_TestCase_1",            Mt_AvacStat1_AvacStat1Data_GetAvacS_En_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_GetAvacS_Ok_TestCase_1",            Mt_AvacStat1_AvacStat1Data_GetAvacS_Ok_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_GetLowBeamOn_TestCase_1",           Mt_AvacStat1_AvacStat1Data_GetLowBeamOn_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_1",               Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_2",               Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_2);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_3",               Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_3);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_4",               Mt_AvacStat1_AvacStat1Data_ParaFct0_TestCase_4);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_Get_CodingPara_TestCase_1",         Mt_AvacStat1_AvacStat1Data_Get_CodingPara_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1Data_CodingDataValidation_TestCase_1",   Mt_AvacStat1_AvacStat1Data_CodingDataValidation_TestCase_1);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_18",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_18);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_19",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_19);
  ALUnitTest_AddFunction("Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_20",         Mt_AvacStat1_AvacStat1_GetHeadlightAngle_TestCase_20);
}
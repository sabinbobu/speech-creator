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
/// \brief  Unit Test Cases for CddDcm module
///
/// \author  Braga Ionut-Cosmin
///         mailTo: ionutcosmin.braga[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Files covered by this module unit test:
///
///        Src_AL/Cdd/CddDcm/Gen:
///             -CddDcmCtrl.c
///             -CddDcmHal.c
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
/// \Test Case : Mt_CddDcm_CddDcmCtrl_BbSettingStart
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function correctly reads messages and DC Motor is moving
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_BbSettingStart_Param1             = 23
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Read_DcmPos0_Port_HitCount               = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 1u
/// \input  Rte_Write_DcmPos0_Port_HitCount              = 0u
/// \input  Rte_Write_DcmPos0_Port_Param1.nPos           = 0u
///
/// - Expectations:
///
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Read_DcmPos0_Port_HitCount,              = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsReady, = 0u
/// \output Rte_Write_DcmPos0_Port_HitCount,             = 1u
/// \output Rte_Write_DcmPos0_Port_Param1.nPos,          = 23
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_BbSettingStart(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CddDcmCtrl_BbSettingStart_Param1             = 23;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Read_DcmPos0_Port_HitCount               = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 1u;
  Rte_Write_DcmPos0_Port_HitCount              = 0u;
  Rte_Write_DcmPos0_Port_Param1.nPos           = 0u;

  //Step 3) Call FUT

  CddDcmCtrl_BbSettingStart(CddDcmCtrl_BbSettingStart_Param1);

  //Step 4) Check expected output value 

  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Read_DcmPos0_Port_HitCount,               1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsMoving, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsReady,  0u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmPos0_Port_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmPos0_Port_Param1.nPos,           23, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_BbSettingStop_
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function correctly reads messages and DC Motor is moving is finished and DC Motor is ready
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u
///
/// - Expectations:
///
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsReady, = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_BbSettingStop_(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_BbSettingStop_();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsMoving, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsReady,  1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_BbSettingDisable_
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function correctly reads messages and DC Motor is disabled
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u
///
/// - Expectations:
///
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_BbSettingDisable_(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u;

  //Step 3) Call FUT
  CddDcmCtrl_BbSettingDisable_();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsMoving, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_BbSettingVoltOnOff_
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function correctly reads messages and DC Motor supply is turned on/off
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_BbSettingVoltOnOff__Param1        = 1u
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsOn     = 0u
///
/// - Expectations:
///
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsOn     = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_BbSettingVoltOnOff_(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_BbSettingVoltOnOff__Param1        = 1u;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsOn     = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_BbSettingVoltOnOff_(CddDcmCtrl_BbSettingVoltOnOff__Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsOn,     1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_BbSettingErr_OnOff_
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function correctly reads messages about any error on DC Motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_BbSettingErr_OnOff__Param1        = 1u
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.ErrElec  = 0u
///
/// - Expectations:
///
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.ErrElec  = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_BbSettingErr_OnOff_(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_BbSettingErr_OnOff__Param1        = 1u;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.ErrElec  = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_BbSettingErr_OnOff_(CddDcmCtrl_BbSettingErr_OnOff__Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.ErrElec,  1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_BbSettingInit_
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function correctly reads messages and DC Motor is ready and in a valid position
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   CddDcmCtrl_BbSettingInit__Param1             = 32u
/// \input   Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input   Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input   Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u
/// \input   Rte_Write_DcmPos0_Port_HitCount              = 0u
/// \input   Rte_Write_DcmPos0_Port_Param1.nPos           = 0u
///
/// - Expectations:
///
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsReady, = 1u
/// \output Rte_Write_DcmPos0_Port_HitCount,             = 1u
/// \output Rte_Write_DcmPos0_Port_Param1.nPos,          = 32u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_BbSettingInit_(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_BbSettingInit__Param1             = 32u;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u;
  Rte_Write_DcmPos0_Port_HitCount              = 0u;
  Rte_Write_DcmPos0_Port_Param1.nPos           = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_BbSettingInit_(CddDcmCtrl_BbSettingInit__Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsReady,  1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmPos0_Port_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmPos0_Port_Param1.nPos,          32u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if eeprom data is updated correctly in different cases. In this case
///                       is tested the case when the status is: motor start
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_UpdateEepromData_Param1 = 1u
/// \input  CddDcmCtrl_UpdateEepromData_Param2 = 9u
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u
/// \input  NvmBlockDcMotorData.boMotorStopped = 1u
/// \input  NvmBlockDcMotorData.nPosition      = 0u
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStarted = 0u
/// \output NvmBlockDcMotorData.nPosition,     = 9u
/// \output CddDcmCtrl_boEepromUpdated,        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_UpdateEepromData_Param1 = 1u;
  CddDcmCtrl_UpdateEepromData_Param2 = 9u;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 1u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_UpdateEepromData(CddDcmCtrl_UpdateEepromData_Param1, CddDcmCtrl_UpdateEepromData_Param2);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStarted,    0u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,         9u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if eeprom data is updated correctly in different cases. In this case
///                       is tested the case when the status is: motor start
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_UpdateEepromData_Param1 = 1u
/// \input  CddDcmCtrl_UpdateEepromData_Param2 = 9u
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u
/// \input  NvmBlockDcMotorData.boMotorStopped = 0u
/// \input  NvmBlockDcMotorData.nPosition      = 0u
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStarted = 1u
/// \output NvmBlockDcMotorData.nPosition,     = 9u
/// \output CddDcmCtrl_boEepromUpdated,        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_UpdateEepromData_Param1 = 1u;
  CddDcmCtrl_UpdateEepromData_Param2 = 9u;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 0u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_UpdateEepromData(CddDcmCtrl_UpdateEepromData_Param1, CddDcmCtrl_UpdateEepromData_Param2);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStarted,    1u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,         9u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if eeprom data is updated correctly in different cases. In this case
///                       is tested the case when the status is: motor stop
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_UpdateEepromData_Param1 = 0u
/// \input  CddDcmCtrl_UpdateEepromData_Param2 = 9u
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u
/// \input  NvmBlockDcMotorData.boMotorStopped = 0u
/// \input  NvmBlockDcMotorData.nPosition      = 0u
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStopped = 1u
/// \output NvmBlockDcMotorData.nPosition,     = 9u
/// \output CddDcmCtrl_boEepromUpdated,        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_UpdateEepromData_Param1 = 0u;
  CddDcmCtrl_UpdateEepromData_Param2 = 9u;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 0u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_UpdateEepromData(CddDcmCtrl_UpdateEepromData_Param1, CddDcmCtrl_UpdateEepromData_Param2);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStopped,    1u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,         9u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if eeprom data is updated correctly in different cases. In this case
///                       is tested the case when the status is: motor stop
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_UpdateEepromData_Param1 = 0u
/// \input  CddDcmCtrl_UpdateEepromData_Param2 = 9u
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u
/// \input  NvmBlockDcMotorData.boMotorStopped = 1u
/// \input  NvmBlockDcMotorData.nPosition      = 0u
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStopped = 1u
/// \output NvmBlockDcMotorData.nPosition,     = 9u
/// \output CddDcmCtrl_boEepromUpdated,        = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_UpdateEepromData_Param1 = 0u;
  CddDcmCtrl_UpdateEepromData_Param2 = 9u;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 1u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_UpdateEepromData(CddDcmCtrl_UpdateEepromData_Param1, CddDcmCtrl_UpdateEepromData_Param2);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStopped,    1u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,         9u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,         FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if eeprom data is not updated when status is undefined
///
/// - Preconditions:
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \input  CddDcmCtrl_UpdateEepromData_Param1 = 3u
/// \input  CddDcmCtrl_UpdateEepromData_Param2 = 9u
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u
/// \input  NvmBlockDcMotorData.boMotorStopped = 1u
/// \input  NvmBlockDcMotorData.nPosition      = 0u
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStarted = 1u
/// \output NvmBlockDcMotorData.boMotorStopped = 1u
/// \output NvmBlockDcMotorData.nPosition,     = 9u
/// \output CddDcmCtrl_boEepromUpdated,        = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_UpdateEepromData_Param1 = 3u;
  CddDcmCtrl_UpdateEepromData_Param2 = 9u;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 1u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_UpdateEepromData(CddDcmCtrl_UpdateEepromData_Param1, CddDcmCtrl_UpdateEepromData_Param2);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStarted,    1u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStopped,    1u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,         0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,          TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_UpdateEepromData
///
/// \FuSa Relevant: NA
///
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_UpdateEepromData(void)
{
  Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_2();
  Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_3();
  Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_4();
  Mt_CddDcm_CddDcmCtrl_UpdateEepromData_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_GetAdjustingTime_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates adjusting time
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_GetAdjustingTime_Param1 = 0u
/// \input  CddDcmCtrl_GetAdjustingTime_Param2 = 10
/// \input  CddDcmCtrl_GetAdjustingTime_Param3 = 11
/// \input  CddDcmCtrl_GetAdjustingTime_RetVal = 0u
///
/// - Expectations:
///
/// \output CddDcmCtrl_GetAdjustingTime_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_GetAdjustingTime_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_GetAdjustingTime_Param1 = 0u;
  CddDcmCtrl_GetAdjustingTime_Param2 = 10;
  CddDcmCtrl_GetAdjustingTime_Param3 = 11;
  CddDcmCtrl_GetAdjustingTime_RetVal = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_GetAdjustingTime_RetVal = CddDcmCtrl_GetAdjustingTime(CddDcmCtrl_GetAdjustingTime_Param1, CddDcmCtrl_GetAdjustingTime_Param2, CddDcmCtrl_GetAdjustingTime_Param3);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_GetAdjustingTime_RetVal,    1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_GetAdjustingTime_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates adjusting time
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_GetAdjustingTime_Param1 = 0u
/// \input  CddDcmCtrl_GetAdjustingTime_Param2 = -11
/// \input  CddDcmCtrl_GetAdjustingTime_Param3 = -10
/// \input  CddDcmCtrl_GetAdjustingTime_RetVal = 0u
///
/// - Expectations:
///
/// \output CddDcmCtrl_GetAdjustingTime_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_GetAdjustingTime_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_GetAdjustingTime_Param1 = 0u;
  CddDcmCtrl_GetAdjustingTime_Param2 = -11;
  CddDcmCtrl_GetAdjustingTime_Param3 = -10;
  CddDcmCtrl_GetAdjustingTime_RetVal = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_GetAdjustingTime_RetVal = CddDcmCtrl_GetAdjustingTime(CddDcmCtrl_GetAdjustingTime_Param1, CddDcmCtrl_GetAdjustingTime_Param2, CddDcmCtrl_GetAdjustingTime_Param3);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_GetAdjustingTime_RetVal,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_GetAdjustingTime
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_GetAdjustingTime(void)
{
  Mt_CddDcm_CddDcmCtrl_GetAdjustingTime_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_GetAdjustingTime_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_AlarmSet
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if 1-s-Alarm for DC motor adjusting started
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boAlarmActive    = TRUE
/// \input  CddDcmCtrl_unAdjustingTime  = 0u
/// \input  CddDcmCtrl_unTimeoutCounter = 12u
/// \input  CddDcmCtrl_AlarmSet_Param1  = 11u
///
/// - Expectations:
///
/// \output CddDcmCtrl_boAlarmActive    = TRUE
/// \output CddDcmCtrl_unAdjustingTime  = 11u
/// \output CddDcmCtrl_unTimeoutCounter = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_AlarmSet(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boAlarmActive    = TRUE;
  CddDcmCtrl_unAdjustingTime  = 0u;
  CddDcmCtrl_unTimeoutCounter = 12u;
  CddDcmCtrl_AlarmSet_Param1  = 11u;

  //Step 3) Call FUT
  CddDcmCtrl_AlarmSet(CddDcmCtrl_AlarmSet_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_boAlarmActive,          TRUE, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_unAdjustingTime,         11u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_unTimeoutCounter,         0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DisableAndPwmOffChannel
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function sets enable pwm output flag to disable
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput = 1u
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DisableAndPwmOffChannel(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput = 1u;

  //Step 3) Call FUT
  CddDcmHal_DisableAndPwmOffChannel();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,         0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DisableChannel
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function disables DC motor driver and sets PWM signal to 0
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput                  = 1u
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput,                 = 0u
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DisableChannel(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput                  = 1u;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u;

  //Step 3) Call FUT
  CddDcmCtrl_DisableChannel();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsMoving, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Disable
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calls function Mt_CddDcm_CddDcmCtrl_DisableChannel to deactivate the DC motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput                  = 1u
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput,                 = 0u
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Disable(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput                  = 1u;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u;

  //Step 3) Call FUT
  CddDcmCtrl_Disable();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsMoving, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Continue_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function re-initiate state machine and data when the data from NvM regarding start and stop position is different
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput        = 1u;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 0u;
/// \input  CddDcmCtrl_nOldPos                 = 0u;
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput        = 0u
/// \output CddDcmCtrl_eState,                 = CtrlDcm_StateNotActive
/// \output CddDcmCtrl_nOldPos,                = 1001
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Continue_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput        = 1u;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 0u;
  CddDcmCtrl_nOldPos                 = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_Continue();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                  0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                         1001, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Continue_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function re-initiate state machine and data when the data from NvM regarding start and stop position is the same
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput        = 1u;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 1u;
/// \input  CddDcmCtrl_nOldPos                 = 0u;
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput        = 0u
/// \output CddDcmCtrl_eState,                 = CtrlDcm_StateNotActive
/// \output CddDcmCtrl_nOldPos,                = 0
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Continue_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput        = 1u;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 1u;
  CddDcmCtrl_nOldPos                 = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_Continue();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                  0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                            0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Continue
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Continue(void)
{
  Mt_CddDcm_CddDcmCtrl_Continue_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_Continue_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_InitChannel_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test motor positioning of last power-on incomplete or unknown
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 0u;
/// \input  NvmBlockDcMotorData.nPosition      = 23;
/// \input  CddDcmCtrl_nOldPos                 = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState,                 = CtrlDcm_StateNotActive
/// \output CddDcmCtrl_nOldPos,                = CtrlDcm_PosUnknown
/// \output CddDcmCtrl_nHighestPos,            = CtrlDcm_PosRangeMax
/// \output CddDcmCtrl_nLowestPos,             = CtrlDcm_PosRangeMin
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_InitChannel_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 0u;
  NvmBlockDcMotorData.nPosition      = 23;
  CddDcmCtrl_nOldPos                 = 0u;
  CddDcmCtrl_nHighestPos             = 0u;
  CddDcmCtrl_nLowestPos              = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_InitChannel();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,           CtrlDcm_PosUnknown, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,      CtrlDcm_PosRangeMax, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,       CtrlDcm_PosRangeMin, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_InitChannel_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test valid and definite motor positioning of last power-on
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                            = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted           = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped           = 1u;
/// \input  NvmBlockDcMotorData.nPosition                = 23;
/// \input  CddDcmCtrl_nOldPos                           = 0u;
/// \input  CddDcmCtrl_nHighestPos                       = 0u;
/// \input  CddDcmCtrl_nLowestPos                        = 0u;
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u
/// \input  Rte_Write_DcmPos0_Port_HitCount              = 0u
/// \input  Rte_Write_DcmPos0_Port_Param1.nPos           = 0u
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState,                           = CtrlDcm_StateNotActive
/// \output CddDcmCtrl_nOldPos,                          = 23
/// \output CddDcmCtrl_nHighestPos,                      = 23
/// \output CddDcmCtrl_nLowestPos,                       = 23
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsReady, = 1u
/// \output Rte_Write_DcmPos0_Port_HitCount,             = 1u
/// \output Rte_Write_DcmPos0_Port_Param1.nPos,          = 23
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_InitChannel_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                           = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted          = 1u;
  NvmBlockDcMotorData.boMotorStopped          = 1u;
  NvmBlockDcMotorData.nPosition               = 23;
  CddDcmCtrl_nOldPos                          = 0u;
  CddDcmCtrl_nHighestPos                      = 0u;
  CddDcmCtrl_nLowestPos                       = 0u;
  CddDcmCtrl_BbSettingInit__Param1            = 32u;
  Rte_Read_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_HitCount           = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsReady = 0u;
  Rte_Write_DcmPos0_Port_HitCount             = 0u;
  Rte_Write_DcmPos0_Port_Param1.nPos          = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_InitChannel();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                           23, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                       23, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                        23, == );
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsReady,  1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmPos0_Port_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmPos0_Port_Param1.nPos,           23, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_InitChannel
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_InitChannel(void)
{
  Mt_CddDcm_CddDcmCtrl_InitChannel_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_InitChannel_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ResetVoltageState
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function clear the internal measured output voltage
///         calculation
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ulOutputLevel_FB = 0u
///
/// - Expectations:
///
/// \output CddDcmHal_ulOutputLevel_FB = 0xffff
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ResetVoltageState(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ulOutputLevel_FB = 0u;

  //Step 3) Call FUT
  CddDcmHal_ResetVoltageState();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmHal_ulOutputLevel_FB, 0xffff, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ResetErrorDetection_
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function resets HalDcm voltage evaluation, CtrlDcm error counting and AL ECs
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_nErrCnt_ms      = 0;
/// \input  CddDcmHal_ulOutputLevel_FB = 0u
/// \input  CddDcmCtrl_nErrCntLow      = 5;
/// \input  CddDcmCtrl_nErrCntHigh     = 5;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,     = -1
/// \output CddDcmHal_ulOutputLevel_FB = 0xffff
/// \output CddDcmCtrl_nErrCntLow,     = 0
/// \output CddDcmCtrl_nErrCntHigh,    = 0
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ResetErrorDetection_(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_nErrCnt_ms      = 0;
  CddDcmHal_ulOutputLevel_FB = 0u;
  CddDcmCtrl_nErrCntLow      = 5;
  CddDcmCtrl_nErrCntHigh     = 5;

  //Step 3) Call FUT
  CddDcmCtrl_ResetErrorDetection_();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,            -1, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulOutputLevel_FB,   0xffff, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,             0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,            0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_IsMovingChannel_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function returns FALSE value for moving status
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                 = CtrlDcm_StateNotActive
/// \input  CddDcmCtrl_IsMovingChannel_RetVal = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_IsMovingChannel_RetVal  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_IsMovingChannel_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                 = CtrlDcm_StateNotActive;
  CddDcmCtrl_IsMovingChannel_RetVal = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_IsMovingChannel_RetVal = CddDcmCtrl_IsMovingChannel();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_IsMovingChannel_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_IsMovingChannel_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function returns TRUE value for moving status
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                 = CtrlDcm_StateMovingUp
/// \input  CddDcmCtrl_IsMovingChannel_RetVal = FALSE
///
/// - Expectations:
///
/// \output CddDcmCtrl_IsMovingChannel_RetVal  = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_IsMovingChannel_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                 = CtrlDcm_StateMovingUp;
  CddDcmCtrl_IsMovingChannel_RetVal = FALSE;

  //Step 3) Call FUT
  CddDcmCtrl_IsMovingChannel_RetVal = CddDcmCtrl_IsMovingChannel();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_IsMovingChannel_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_IsMovingChannel
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_IsMovingChannel(void)
{
  Mt_CddDcm_CddDcmCtrl_IsMovingChannel_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_IsMovingChannel_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Init
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test motor positioning of last power-on incomplete or unknown
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput        = 1u
/// \input  CddDcmCtrl_eVoltage                = 0u
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 0u;
/// \input  NvmBlockDcMotorData.nPosition      = 23;
/// \input  CddDcmCtrl_nOldPos                 = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput        = 0u
/// \output CddDcmCtrl_eVoltage,               = 1u
/// \output CddDcmCtrl_eState,                 = CtrlDcm_StateNotActive
/// \output CddDcmCtrl_nOldPos,                = CtrlDcm_PosUnknown
/// \output CddDcmCtrl_nHighestPos,            = CtrlDcm_PosRangeMax
/// \output CddDcmCtrl_nLowestPos,             = CtrlDcm_PosRangeMin
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Init(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput        = 1u;
  CddDcmCtrl_eVoltage                = 0u;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 0u;
  NvmBlockDcMotorData.nPosition      = 23;
  CddDcmCtrl_nOldPos                 = 0u;
  CddDcmCtrl_nHighestPos             = 0u;
  CddDcmCtrl_nLowestPos              = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_Init();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                  0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eVoltage,                          1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,           CtrlDcm_PosUnknown, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,      CtrlDcm_PosRangeMax, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,       CtrlDcm_PosRangeMin, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_SetOutpLevelChannel_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test output level setting for maximum value
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_SetOutpLevelChannel_Param1 = 1000u
/// \input  CddDcmHal_unOutputLevel              = 0u
///
/// - Expectations:
///
/// \output CddDcmHal_unOutputLevel              = 920u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_SetOutpLevelChannel_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_SetOutpLevelChannel_Param1 = 1000u;
  CddDcmHal_unOutputLevel              = 0u;

  //Step 3) Call FUT
  CddDcmHal_SetOutpLevelChannel(CddDcmHal_SetOutpLevelChannel_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_unOutputLevel, 920u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_SetOutpLevelChannel_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test output level setting for minimum value
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_SetOutpLevelChannel_Param1 = 0u
/// \input  CddDcmHal_unOutputLevel              = 0u
///
/// - Expectations:
///
/// \output CddDcmHal_unOutputLevel              = 80u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_SetOutpLevelChannel_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_SetOutpLevelChannel_Param1 = 0u;
  CddDcmHal_unOutputLevel              = 0u;

  //Step 3) Call FUT
  CddDcmHal_SetOutpLevelChannel(CddDcmHal_SetOutpLevelChannel_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_unOutputLevel, 80u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_GetAdjustingTime
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_SetOutpLevelChannel(void)
{
  Mt_CddDcm_CddDcmHal_SetOutpLevelChannel_TestCase_1();
  Mt_CddDcm_CddDcmHal_SetOutpLevelChannel_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_EnableChannel_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function is setting correctly the flag for DC motor. In this case, it will be tested that the Pwm signal will be turned on again
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_EnableChannel_Param1 = TRUE
/// \input  CddDcmHal_ucEnablePwmOutput    = 0u
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput    = 17u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_EnableChannel_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_EnableChannel_Param1 = TRUE;
  CddDcmHal_ucEnablePwmOutput    = 0u;

  //Step 3) Call FUT
  CddDcmHal_EnableChannel(CddDcmHal_EnableChannel_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput, 17u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_EnableChannel_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: est if function is setting correctly the flag for DC motor. In this case will clear the flag
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_EnableChannel_Param1 = FALSE
/// \input  CddDcmHal_ucEnablePwmOutput    = 1u
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_EnableChannel_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_EnableChannel_Param1 = FALSE;
  CddDcmHal_ucEnablePwmOutput    = 1u;

  //Step 3) Call FUT
  CddDcmHal_EnableChannel(CddDcmHal_EnableChannel_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_EnableChannel
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_EnableChannel(void)
{
  Mt_CddDcm_CddDcmHal_EnableChannel_TestCase_1();
  Mt_CddDcm_CddDcmHal_EnableChannel_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateMovingDown state and is not exceed reflector swivelling range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_ServiceMotor_Param1     = 350;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 1u;
/// \input  NvmBlockDcMotorData.nPosition      = 0u;
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStarted = 0u
/// \output NvmBlockDcMotorData.nPosition,     = 350u
/// \output CddDcmCtrl_boEepromUpdated,        = FALSE
/// \output CddDcmCtrl_eState,                 = CtrlDcm_StateMovingPause
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_ServiceMotor_Param1     = 350;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 1u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;
  CddDcmCtrl_nLowestPos              = 0u;
  CddDcmCtrl_nHighestPos             = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStarted,                    0u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,                       350u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,                         FALSE, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,                CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateMovingDown state and is exceed reflector swivelling range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_ServiceMotor_Param1     = 200;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 1u;
/// \input  NvmBlockDcMotorData.nPosition      = 0u;
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
///
/// - Expectations:
///
/// \output NvmBlockDcMotorData.boMotorStarted = 0u
/// \output NvmBlockDcMotorData.nPosition,     = 200
/// \output CddDcmCtrl_boEepromUpdated,        = FALSE
/// \output CddDcmCtrl_eState,                 = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_ServiceMotor_Param1     = 200;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 1u;
  NvmBlockDcMotorData.nPosition      = 0u;
  CddDcmCtrl_boEepromUpdated         = TRUE;
  CddDcmCtrl_nLowestPos              = 300u;
  CddDcmCtrl_nHighestPos             = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.boMotorStarted,                    0u, == );
  AL_UNITTEST_CHECK(NvmBlockDcMotorData.nPosition,                       200u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,                         FALSE, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,                CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateMovingDown into CtrlDcm_StateMovingUp state and not exceed reflector swivelling range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_ServiceMotor_Param1     = 350;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingPause
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nLowestPos,             = 250
/// \output CddDcmCtrl_nHighestPos,            = 350
/// \output CddDcmCtrl_eState                  = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_ServiceMotor_Param1     = 350;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingPause;
  CddDcmCtrl_boEepromUpdated         = TRUE;
  CddDcmCtrl_nLowestPos              = 0u;
  CddDcmCtrl_nHighestPos             = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                     350, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                    350, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,     CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateMovingDown into CtrlDcm_StateMovingUp state and it is exceed reflector swivelling range
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_ServiceMotor_Param1     = -200;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingPause
/// \input  CddDcmCtrl_boEepromUpdated         = TRUE;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nLowestPos,             = 200
/// \output CddDcmCtrl_nHighestPos,            = 200
/// \output CddDcmCtrl_eState                  = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_ServiceMotor_Param1     = -200;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingPause;
  CddDcmCtrl_boEepromUpdated         = TRUE;
  CddDcmCtrl_nLowestPos              = 0u;
  CddDcmCtrl_nHighestPos             = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                     200, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                    200, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,     CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateNotActive state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateNotActive
/// \input  CddDcmHal_ucEnablePwmOutput = 1u
///
/// - Expectations:
///
/// \output CddDcmHal_ucEnablePwmOutput = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState           = CtrlDcm_StateNotActive;
  CddDcmHal_ucEnablePwmOutput = 1u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,            CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                      0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateMovingUp state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateMovingUp
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState = CtrlDcm_StateMovingUp;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_7
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateMovingDone state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_ServiceMotor_Param1               = 200u
/// \input  CddDcmCtrl_eState                            = CtrlDcm_StateMovingDone
/// \input  Rte_Read_DcmState0_Port_HitCount             = 0u
/// \input  Rte_Write_DcmState0_Port_HitCount            = 0u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u
/// \input  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u
/// \input  CddDcmCtrl_nHighestPos                       = 0u
/// \input  CddDcmCtrl_nLowestPos                        = 0u
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState                            = CtrlDcm_StateNotActive
/// \output Rte_Read_DcmState0_Port_HitCount,            = 1u
/// \output Rte_Write_DcmState0_Port_HitCount,           = 1u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 0u
/// \output Rte_Write_DcmState0_Port_Param1.Bit.IsReady, = 1u
/// \output CddDcmCtrl_nHighestPos                       = 200u
/// \output CddDcmCtrl_nLowestPos                        = 200u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_ServiceMotor_Param1               = 200u;
  CddDcmCtrl_eState                            = CtrlDcm_StateMovingDone;
  Rte_Read_DcmState0_Port_HitCount             = 0u;
  Rte_Write_DcmState0_Port_HitCount            = 0u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsMoving = 1u;
  Rte_Write_DcmState0_Port_Param1.Bit.IsReady  = 0u;
  CddDcmCtrl_nHighestPos                       = 0u;
  CddDcmCtrl_nLowestPos                        = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(Rte_Read_DcmState0_Port_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_HitCount,            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsMoving, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_DcmState0_Port_Param1.Bit.IsReady,  1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                     200u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                      200u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_8
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateLocked state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateLocked
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = CtrlDcm_StateLocked
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState = CtrlDcm_StateLocked;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, CtrlDcm_StateLocked, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_9
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test CtrlDcm_StateErrorOff state
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateErrorOff
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = CtrlDcm_StateErrorOff
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState = CtrlDcm_StateErrorOff;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, CtrlDcm_StateErrorOff, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_10
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test out of bound state value
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState           = 10u
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = 10u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState = 10u;

  //Step 3) Call FUT
  CddDcmCtrl_ServiceMotor(CddDcmCtrl_ServiceMotor_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_ServiceMotor
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_ServiceMotor(void)
{
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_2();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_3();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_4();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_5();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_6();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_7();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_8();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_9();
  Mt_CddDcm_CddDcmCtrl_ServiceMotor_TestCase_10();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calls State-Machine when timeout is done and verify what happens when channel 0 adjusting expired
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boAlarmActive    = TRUE;
/// \input  CddDcmCtrl_unTimeoutCounter = 10u;
/// \input  CddDcmCtrl_unAdjustingTime  = 10u;
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateMovingPause
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boAlarmActive    = TRUE;
  CddDcmCtrl_unTimeoutCounter = 10u;
  CddDcmCtrl_unAdjustingTime  = 10u;
  CddDcmCtrl_eState           = CtrlDcm_StateMovingPause;

  //Step 3) Call FUT
  CddDcmCtrl_AlarmTimeout();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not call State-Machine when timeout is not done
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boAlarmActive    = TRUE;
/// \input  CddDcmCtrl_unTimeoutCounter = 0u;
/// \input  CddDcmCtrl_unAdjustingTime  = 10u;
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateMovingPause
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = CtrlDcm_StateMovingPause
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boAlarmActive    = TRUE;
  CddDcmCtrl_unTimeoutCounter = 0u;
  CddDcmCtrl_unAdjustingTime  = 10u;
  CddDcmCtrl_eState           = CtrlDcm_StateMovingPause;

  //Step 3) Call FUT
  CddDcmCtrl_AlarmTimeout();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, CtrlDcm_StateMovingPause, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not call State-Machine when flag is deactive
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boAlarmActive    = FALSE;
/// \input  CddDcmCtrl_unTimeoutCounter = 0u;
/// \input  CddDcmCtrl_unAdjustingTime  = 10u;
/// \input  CddDcmCtrl_eState           = CtrlDcm_StateMovingPause
///
/// - Expectations:
///
/// \output CddDcmCtrl_eState           = CtrlDcm_StateMovingPause
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boAlarmActive    = FALSE;
  CddDcmCtrl_unTimeoutCounter = 0u;
  CddDcmCtrl_unAdjustingTime  = 10u;
  CddDcmCtrl_eState           = CtrlDcm_StateMovingPause;

  //Step 3) Call FUT
  CddDcmCtrl_AlarmTimeout();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_eState, CtrlDcm_StateMovingPause, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_AlarmTimeout
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_AlarmTimeout(void)
{
  Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_2();
  Mt_CddDcm_CddDcmCtrl_AlarmTimeout_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function evaluates Ctrl messsage data
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 0u;
/// \input  CddDcmCtrl_eState                           = CtrlDcm_StateErrorOff
/// \input  CddDcmCtrl_nOldPos                          = 0u;
/// \input  CddDcmCtrl_nHighestPos                      = 0u;
/// \input  CddDcmCtrl_nLowestPos                       = 0u;
/// \input  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOff;
/// \input  CddDcmCtrl_CtrlMsgChannel_RetVal            = TRUE;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nOldPos,                         = CtrlDcm_PosUnknown
/// \output CddDcmCtrl_nHighestPos,                     = CtrlDcm_PosRangeMax
/// \output CddDcmCtrl_nLowestPos,                      = CtrlDcm_PosRangeMin
/// \output CddDcmCtrl_eState,                          = CtrlDcm_StateLocked
/// \output CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 0u;
  CddDcmCtrl_eState                           = CtrlDcm_StateErrorOff;
  CddDcmCtrl_nOldPos                          = 0u;
  CddDcmCtrl_nHighestPos                      = 0u;
  CddDcmCtrl_nLowestPos                       = 0u;
  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOff;
  CddDcmCtrl_CtrlMsgChannel_RetVal            = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_CtrlMsgChannel_RetVal = CddDcmCtrl_CtrlMsgChannel(CddDcmCtrl_CtrlMsgChannel_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                CtrlDcm_PosUnknown, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,           CtrlDcm_PosRangeMax, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,            CtrlDcm_PosRangeMin, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,                CtrlDcm_StateLocked, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_CtrlMsgChannel_RetVal,               FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function evaluates Ctrl messsage data
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 900u;
/// \input  CddDcmCtrl_eState                           = CtrlDcm_StateLocked
/// \input  CddDcmCtrl_nOldPos                          = 0u;
/// \input  CddDcmCtrl_nHighestPos                      = 0u;
/// \input  CddDcmCtrl_nLowestPos                       = 0u;
/// \input  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOn;
/// \input  CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nOldPos,                         = 800
/// \output CddDcmCtrl_nHighestPos,                     = CtrlDcm_Hysteresis
/// \output CddDcmCtrl_nLowestPos,                      = 0
/// \output CddDcmCtrl_eState,                          = CtrlDcm_StateMovingUp
/// \output CddDcmCtrl_CtrlMsgChannel_RetVal            = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 900u;
  CddDcmCtrl_eState                           = CtrlDcm_StateLocked;
  CddDcmCtrl_nOldPos                          = 0u;
  CddDcmCtrl_nHighestPos                      = 0u;
  CddDcmCtrl_nLowestPos                       = 0u;
  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOn;
  CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE;

  //Step 3) Call FUT
  CddDcmCtrl_CtrlMsgChannel_RetVal = CddDcmCtrl_CtrlMsgChannel(CddDcmCtrl_CtrlMsgChannel_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                              800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,           CtrlDcm_Hysteresis, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                             0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,             CtrlDcm_StateMovingUp, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_CtrlMsgChannel_RetVal,               TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function evaluates Ctrl messsage data
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 900u;
/// \input  CddDcmCtrl_eState                           = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nOldPos                          = 0u;
/// \input  CddDcmCtrl_nHighestPos                      = 1000u;
/// \input  CddDcmCtrl_nLowestPos                       = 0u;
/// \input  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOn;
/// \input  CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nOldPos,                         = 800
/// \output CddDcmCtrl_nHighestPos,                     = 850
/// \output CddDcmCtrl_nLowestPos,                      = 0
/// \output CddDcmCtrl_eState,                          = CtrlDcm_StateMovingUp
/// \output CddDcmCtrl_CtrlMsgChannel_RetVal            = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 900u;
  CddDcmCtrl_eState                           = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nOldPos                          = 0u;
  CddDcmCtrl_nHighestPos                      = 1000u;
  CddDcmCtrl_nLowestPos                       = 0u;
  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOn;
  CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE;

  //Step 3) Call FUT
  CddDcmCtrl_CtrlMsgChannel_RetVal = CddDcmCtrl_CtrlMsgChannel(CddDcmCtrl_CtrlMsgChannel_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                              800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                          850, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                             0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,             CtrlDcm_StateMovingUp, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_CtrlMsgChannel_RetVal,               TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function evaluates Ctrl messsage data
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 0u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
/// \input  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 200u;
/// \input  CddDcmCtrl_eState                           = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nOldPos                          = 0u;
/// \input  CddDcmCtrl_nHighestPos                      = 800u;
/// \input  CddDcmCtrl_nLowestPos                       = 0u;
/// \input  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOn;
/// \input  CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE;
///
/// - Expectations:
///
/// \output CddDcmCtrl_nOldPos,                         = 200
/// \output CddDcmCtrl_nHighestPos,                     = 800
/// \output CddDcmCtrl_nLowestPos,                      = 0
/// \output CddDcmCtrl_eState,                          = CtrlDcm_StateMovingDown
/// \output CddDcmCtrl_CtrlMsgChannel_RetVal            = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.ErrClr = 0u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Bit.Active = 1u;
  CddDcmCtrl_CtrlMsgChannel_Param1.Val.nPos   = 200u;
  CddDcmCtrl_eState                           = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nOldPos                          = 0u;
  CddDcmCtrl_nHighestPos                      = 800u;
  CddDcmCtrl_nLowestPos                       = 0u;
  CddDcmCtrl_eVoltage                         = CtrlDcm_VoltOn;
  CddDcmCtrl_CtrlMsgChannel_RetVal            = FALSE;

  //Step 3) Call FUT
  CddDcmCtrl_CtrlMsgChannel_RetVal = CddDcmCtrl_CtrlMsgChannel(CddDcmCtrl_CtrlMsgChannel_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                              200, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                          800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                             0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,           CtrlDcm_StateMovingDown, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_CtrlMsgChannel_RetVal,               TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel(void)
{
  Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_2();
  Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_3();
  Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsg_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reads dcm target value and evaluates if message datas are TRUE
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 0u;
/// \input  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nOldPos                                                    = 0u;
/// \input  CddDcmCtrl_nHighestPos                                                = 800u;
/// \input  CddDcmCtrl_nLowestPos                                                 = 0u;
/// \input  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOn;
///
/// - Expectations:
///
/// \output Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 1u
/// \output CddDcmCtrl_nOldPos,                                = 800
/// \output CddDcmCtrl_nHighestPos,                            = 800
/// \output CddDcmCtrl_nLowestPos,                             = 0
/// \output CddDcmCtrl_eState,                                 = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsg_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 0u;
  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nOldPos                                                    = 0u;
  CddDcmCtrl_nHighestPos                                                = 800u;
  CddDcmCtrl_nLowestPos                                                 = 0u;
  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOn;

  //Step 3) Call FUT
  CddDcmCtrl_CtrlMsg();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                                800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                            800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                               0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,             CtrlDcm_StateMovingDone, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsg_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reads dcm target value and evaluates if message datas are FALSE
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 1u;
/// \input  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nOldPos                                                    = 0u;
/// \input  CddDcmCtrl_nHighestPos                                                = 800u;
/// \input  CddDcmCtrl_nLowestPos                                                 = 0u;
/// \input  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOn;
///
/// - Expectations:
///
/// \output Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 1u
/// \output CddDcmCtrl_nOldPos,                                = 0
/// \output CddDcmCtrl_nHighestPos,                            = 800
/// \output CddDcmCtrl_nLowestPos,                             = 0
/// \output CddDcmCtrl_eState,                                 = CtrlDcm_StateLocked
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsg_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 1u;
  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nOldPos                                                    = 0u;
  CddDcmCtrl_nHighestPos                                                = 800u;
  CddDcmCtrl_nLowestPos                                                 = 0u;
  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOn;

  //Step 3) Call FUT
  CddDcmCtrl_CtrlMsg();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                                  0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                            800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                               0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,                 CtrlDcm_StateLocked, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CtrlMsg
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CtrlMsg(void)
{
  Mt_CddDcm_CddDcmCtrl_CtrlMsg_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_CtrlMsg_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_VoltChange_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reads vbat voltage and change state to CtrlDcm_VoltOn
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                        = 0u;
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                          = 10000u;
/// \input  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOff;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 1u;
/// \input  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nOldPos                                                    = 0u;
/// \input  CddDcmCtrl_nHighestPos                                                = 800u;
/// \input  CddDcmCtrl_nLowestPos                                                 = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount     = 1u
/// \output Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 1u
/// \output CddDcmCtrl_nOldPos,                                = 0
/// \output CddDcmCtrl_nHighestPos,                            = 800
/// \output CddDcmCtrl_nLowestPos,                             = 0
/// \output CddDcmCtrl_eState,                                 = CtrlDcm_StateLocked
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_VoltChange_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                        = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                          = 10000u;
  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOff;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 1u;
  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nOldPos                                                    = 0u;
  CddDcmCtrl_nHighestPos                                                = 800u;
  CddDcmCtrl_nLowestPos                                                 = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_VoltChange();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                                  0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                            800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                               0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,                 CtrlDcm_StateLocked, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_VoltChange_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reads vbat voltage and change state to CtrlDcm_VoltOff
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                        = 0u;
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                          = 1000u;
/// \input  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOff;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
/// \input  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 1u;
/// \input  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nOldPos                                                    = 0u;
/// \input  CddDcmCtrl_nHighestPos                                                = 800u;
/// \input  CddDcmCtrl_nLowestPos                                                 = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount     = 1u
/// \output Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 0u
/// \output CddDcmCtrl_nOldPos,                                = 0
/// \output CddDcmCtrl_nHighestPos,                            = 800
/// \output CddDcmCtrl_nLowestPos,                             = 0
/// \output CddDcmCtrl_eState,                                 = CtrlDcm_StateMovingDone
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_VoltChange_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                        = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                          = 1000u;
  CddDcmCtrl_eVoltage                                                   = CtrlDcm_VoltOff;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount                    = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 0u;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop    = 1u;
  CddDcmCtrl_eState                                                     = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nOldPos                                                    = 0u;
  CddDcmCtrl_nHighestPos                                                = 800u;
  CddDcmCtrl_nLowestPos                                                 = 0u;

  //Step 3) Call FUT
  CddDcmCtrl_VoltChange();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,                                  0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,                            800, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,                               0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,             CtrlDcm_StateMovingDone, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_VoltChange
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_VoltChange(void)
{
  Mt_CddDcm_CddDcmCtrl_VoltChange_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_VoltChange_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if functioncheck the last measured output Dc-motor level and reports unknown level
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ulOutputLevel_FB       = 0xFFFFu
/// \input  CddDcmHal_GetVoltageState_RetVal = 23u;
///
/// - Expectations:
///
/// \output CddDcmHal_GetVoltageState_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ulOutputLevel_FB       = 0xFFFFu;
  CddDcmHal_GetVoltageState_RetVal = 23u;

  //Step 3) Call FUT
  CddDcmHal_GetVoltageState_RetVal = CddDcmHal_GetVoltageState();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_GetVoltageState_RetVal,             0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function check the last measured output Dc-motor level and reports low level
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ulOutputLevel_FB       = 0u
/// \input  CddDcmHal_GetVoltageState_RetVal = 23u;
///
/// - Expectations:
///
/// \output CddDcmHal_GetVoltageState_RetVal = 2u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ulOutputLevel_FB       = 0u;
  CddDcmHal_GetVoltageState_RetVal = 23u;

  //Step 3) Call FUT
  CddDcmHal_GetVoltageState_RetVal = CddDcmHal_GetVoltageState();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_GetVoltageState_RetVal,             2u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function check the last measured output Dc-motor level and reports high level
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ulOutputLevel_FB       = 1000u
/// \input  CddDcmHal_GetVoltageState_RetVal = 23u;
///
/// - Expectations:
///
/// \output CddDcmHal_GetVoltageState_RetVal = 3u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ulOutputLevel_FB       = 1000u;
  CddDcmHal_GetVoltageState_RetVal = 23u;

  //Step 3) Call FUT
  CddDcmHal_GetVoltageState_RetVal = CddDcmHal_GetVoltageState();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_GetVoltageState_RetVal,             3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reports check the last measured output Dc-motor level and ok level
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ulOutputLevel_FB       = 100u
/// \input  CddDcmHal_GetVoltageState_RetVal = 23u;
///
/// - Expectations:
///
/// \output CddDcmHal_GetVoltageState_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ulOutputLevel_FB       = 100u;
  CddDcmHal_GetVoltageState_RetVal = 23u;

  //Step 3) Call FUT
  CddDcmHal_GetVoltageState_RetVal = CddDcmHal_GetVoltageState();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_GetVoltageState_RetVal,             1u, == );
}

//---------------------------------------------------------------v--------------
/// \Test Case : Mt_CddDcm_CddDcmHal_GetVoltageState
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_GetVoltageState(void)
{
  Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_1();
  Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_2();
  Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_3();
  Mt_CddDcm_CddDcmHal_GetVoltageState_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcm_OutputEnable_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function enables pin
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcm_OutputEnable_Param1        = TRUE
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;
///
/// - Expectations:
///
/// \output IoHwAb_User_SetDio_EN_DC_Param1 = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcm_OutputEnable_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcm_OutputEnable_Param1        = TRUE;
  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;

  //Step 3) Call FUT
  CddDcm_OutputEnable(CddDcm_OutputEnable_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_Param1, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcm_OutputEnable_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function disables pin
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcm_OutputEnable_Param1        = FALSE
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;
///
/// - Expectations:
///
/// \output IoHwAb_User_SetDio_EN_DC_Param1 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcm_OutputEnable_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcm_OutputEnable_Param1        = FALSE;
  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;

  //Step 3) Call FUT
  CddDcm_OutputEnable(CddDcm_OutputEnable_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_Param1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcm_OutputEnable
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcm_OutputEnable(void)
{
  Mt_CddDcm_CddDcm_OutputEnable_TestCase_1();
  Mt_CddDcm_CddDcm_OutputEnable_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcm_GetVdcm
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function returns adc voltage for DCM in mV
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcm_GetVdcm_RetVal                  = 0u
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 0u
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1   = 3u
///
/// - Expectations:
///
/// \output CddDcm_GetVdcm_RetVal = 3u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcm_GetVdcm(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcm_GetVdcm_RetVal                  = 0u;
  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 0u;
  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1   = 3u;

  //Step 3) Call FUT
  CddDcm_GetVdcm_RetVal = CddDcm_GetVdcm();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcm_GetVdcm_RetVal, 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcm_GetVbat
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function returns adc diag voltage for VBAT in mV
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcm_GetVdcm_RetVal                  = 0u
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 0u
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1   = 3u
///
/// - Expectations:
///
/// \output CddDcm_GetVdcm_RetVal = 3u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcm_GetVbat(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcm_GetVbat_RetVal                          = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u;

  //Step 3) Call FUT
  CddDcm_GetVbat_RetVal = CddDcm_GetVbat();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcm_GetVbat_RetVal, 3u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_CalculatePwm
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function returns calculated pwm
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_CalculatePwm_Param1 = 0u;
/// \input  CddDcmHal_CalculatePwm_Param2 = 0u;
/// \input  CddDcmHal_CalculatePwm_RetVal = 1000u
///
/// - Expectations:
///
/// \output CddDcmHal_CalculatePwm_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_CalculatePwm(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_CalculatePwm_Param1 = 0u;
  CddDcmHal_CalculatePwm_Param2 = 0u;
  CddDcmHal_CalculatePwm_RetVal = 1000u;

  //Step 3) Call FUT
  CddDcmHal_CalculatePwm_RetVal = CddDcmHal_CalculatePwm(CddDcmHal_CalculatePwm_Param1, CddDcmHal_CalculatePwm_Param2);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_CalculatePwm_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_SetMotorPwm_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function sets motor pwm
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_SetMotorPwm_Param1 = 1u
/// \input  CddDcmHal_unLastPwmSignal    = 0u
/// \input  Pwm_SetDutyCycle_Param1      = 0u
/// \input  Pwm_SetDutyCycle_Param2      = 0u
/// \input  Pwm_SetDutyCycle_HitCount    = 0u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1      = 5u
/// \output Pwm_SetDutyCycle_Param2      = 32u
/// \output Pwm_SetDutyCycle_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_SetMotorPwm_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_SetMotorPwm_Param1 = 1u;
  CddDcmHal_unLastPwmSignal    = 0u;
  Pwm_SetDutyCycle_Param1      = 0u;
  Pwm_SetDutyCycle_Param2      = 0u;
  Pwm_SetDutyCycle_HitCount    = 0u;

  //Step 3) Call FUT
  CddDcmHal_SetMotorPwm(CddDcmHal_SetMotorPwm_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,            5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,           32u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,          1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_SetMotorPwm_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not set motor pwm
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_SetMotorPwm_Param1 = 1u
/// \input  CddDcmHal_unLastPwmSignal    = 1u
/// \input  Pwm_SetDutyCycle_Param1      = 0u
/// \input  Pwm_SetDutyCycle_Param2      = 0u
/// \input  Pwm_SetDutyCycle_HitCount    = 0u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1      = 0u
/// \output Pwm_SetDutyCycle_Param2      = 0u
/// \output Pwm_SetDutyCycle_HitCount    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_SetMotorPwm_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_SetMotorPwm_Param1 = 1u;
  CddDcmHal_unLastPwmSignal    = 1u;
  Pwm_SetDutyCycle_Param1      = 0u;
  Pwm_SetDutyCycle_Param2      = 0u;
  Pwm_SetDutyCycle_HitCount    = 0u;

  //Step 3) Call FUT
  CddDcmHal_SetMotorPwm(CddDcmHal_SetMotorPwm_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,            0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,            0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_SetMotorPwm
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_SetMotorPwm(void)
{
  Mt_CddDcm_CddDcmHal_SetMotorPwm_TestCase_1();
  Mt_CddDcm_CddDcmHal_SetMotorPwm_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlStart
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function starts the control of dcm
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 0u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_ChannelLevelCtrlStart_RetVal = 23u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1                   = 5u
/// \output Pwm_SetDutyCycle_Param2                   = 0u
/// \output Pwm_SetDutyCycle_HitCount                 = 1u
/// \output CddDcmHal_ChannelLevelCtrlStart_RetVal    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlStart(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  CddDcmHal_ChannelLevelCtrlStart_RetVal = 23u;

  //Step 3) Call FUT
  CddDcmHal_ChannelLevelCtrlStart_RetVal = CddDcmHal_ChannelLevelCtrlStart();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ChannelLevelCtrlStart_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates result of pwm signal
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1                = 5u
/// \output Pwm_SetDutyCycle_Param2                = 0u
/// \output Pwm_SetDutyCycle_HitCount              = 1u
/// \output CddDcmHal_ChannelLevelCtrlOn_RetVal    = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u;

  //Step 3) Call FUT
  CddDcmHal_ChannelLevelCtrlOn_RetVal = CddDcmHal_ChannelLevelCtrlOn();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ChannelLevelCtrlOn_RetVal,    0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates result of pwm signal
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  CddDcmHal_unMotorPwm                   = 9999u
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1                = 5u
/// \output Pwm_SetDutyCycle_HitCount              = 1u
/// \output CddDcmHal_ChannelLevelCtrlOn_RetVal    = 9999u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  CddDcmHal_unMotorPwm                   = 9999u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u;

  //Step 3) Call FUT
  CddDcmHal_ChannelLevelCtrlOn_RetVal = CddDcmHal_ChannelLevelCtrlOn();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ChannelLevelCtrlOn_RetVal, 9999u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates result of pwm signal
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unOutputLevel                = 9999u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  CddDcmHal_unMotorPwm                   = 9999u
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1                = 5u
/// \output Pwm_SetDutyCycle_HitCount              = 1u
/// \output CddDcmHal_ChannelLevelCtrlOn_RetVal    = 1000u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unOutputLevel                = 9999u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  CddDcmHal_unMotorPwm                   = 9999u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u;

  //Step 3) Call FUT
  CddDcmHal_ChannelLevelCtrlOn_RetVal = CddDcmHal_ChannelLevelCtrlOn();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ChannelLevelCtrlOn_RetVal, 1000u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function calculates result of pwm signal
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unOutputLevel                = 99u
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  CddDcmHal_unMotorPwm                   = 999
/// \input  CddDcmHal_ulOutputLevel_FB             = 5u;
/// \input  CddDcmHal_unOutputLevel                = 10u
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1                = 5u
/// \output Pwm_SetDutyCycle_HitCount              = 1u
/// \output CddDcmHal_ChannelLevelCtrlOn_RetVal    = 999u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unOutputLevel                = 99u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  CddDcmHal_unMotorPwm                   = 999u;
  CddDcmHal_ulOutputLevel_FB             = 5u;
  CddDcmHal_unOutputLevel                = 10u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u;

  //Step 3) Call FUT
  CddDcmHal_ChannelLevelCtrlOn_RetVal = CddDcmHal_ChannelLevelCtrlOn();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ChannelLevelCtrlOn_RetVal,  999u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not calculate result of pwm signal
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unOutputLevel                = 99u
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  CddDcmHal_unMotorPwm                   = 999
/// \input  CddDcmHal_ulOutputLevel_FB             = 0u
/// \input  CddDcmHal_unOutputLevel                = 0u
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1                = 0u
/// \output Pwm_SetDutyCycle_HitCount              = 0u
/// \output CddDcmHal_ChannelLevelCtrlOn_RetVal    = 999u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unOutputLevel                = 99u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  CddDcmHal_unMotorPwm                   = 999u;
  CddDcmHal_ulOutputLevel_FB             = 0u;
  CddDcmHal_unOutputLevel                = 0u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  CddDcmHal_ChannelLevelCtrlOn_RetVal    = 23u;

  //Step 3) Call FUT
  CddDcmHal_ChannelLevelCtrlOn_RetVal = CddDcmHal_ChannelLevelCtrlOn();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              0u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ChannelLevelCtrlOn_RetVal,  999u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn(void)
{
  Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_1();
  Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_2();
  Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_3();
  Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_4();
  Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateErrorOff
/// \input  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
/// \input  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
/// \input  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;
///
/// - Expectations:
///
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateErrorOff;
  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 0u;
/// \input  CddDcmCtrl_nErrCntLow                         = 1;
/// \input  CddDcmCtrl_nErrCntHigh                        = 1;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u;
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 20u
/// \output CddDcmCtrl_nErrCntLow,                        = 0
/// \output CddDcmCtrl_nErrCntHigh,                       = 0
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 0u;
  CddDcmCtrl_nErrCntLow                         = 1;
  CddDcmCtrl_nErrCntHigh                        = 1;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                            20u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                              0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                             0, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reports sh2gnd
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 500u;
/// \input  CddDcmCtrl_nErrCntLow                         = 530;
/// \input  CddDcmCtrl_nErrCntHigh                        = 30;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u;
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = FALSE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 20u
/// \output CddDcmCtrl_nErrCntLow,                        = 0
/// \output CddDcmCtrl_nErrCntHigh,                       = 0
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 500u;
  CddDcmCtrl_nErrCntLow                         = 530;
  CddDcmCtrl_nErrCntHigh                        = 30;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                           500u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                            510, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                            10, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,   TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 100u
/// \input  CddDcmCtrl_nErrCntLow                         = -30;
/// \input  CddDcmCtrl_nErrCntHigh                        = -30;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 120u
/// \output CddDcmCtrl_nErrCntLow,                        =  -30
/// \output CddDcmCtrl_nErrCntHigh,                       =  -30
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 100u;
  CddDcmCtrl_nErrCntLow                         = -30;
  CddDcmCtrl_nErrCntHigh                        = -30;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                           120u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                            -30, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                           -30, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateLocked
/// \input  CddDcmCtrl_nErrCnt_ms                         = 100u
/// \input  CddDcmCtrl_nErrCntLow                         = -30;
/// \input  CddDcmCtrl_nErrCntHigh                        = -30;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = -1
/// \output CddDcmCtrl_nErrCntLow,                        = 0
/// \output CddDcmCtrl_nErrCntHigh,                       = 0
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateLocked;
  CddDcmCtrl_nErrCnt_ms                         = 100u;
  CddDcmCtrl_nErrCntLow                         = -30;
  CddDcmCtrl_nErrCntHigh                        = -30;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                             -1, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                              0, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                             0, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateLocked
/// \input  CddDcmCtrl_nErrCnt_ms                         = -100
/// \input  CddDcmCtrl_nErrCntLow                         = -30;
/// \input  CddDcmCtrl_nErrCntHigh                        = -30;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = -100u
/// \output CddDcmCtrl_nErrCntLow,                        =   -30
/// \output CddDcmCtrl_nErrCntHigh,                       =   -30
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateLocked;
  CddDcmCtrl_nErrCnt_ms                         = -100;
  CddDcmCtrl_nErrCntLow                         = -30;
  CddDcmCtrl_nErrCntHigh                        = -30;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                          -100u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                            -30, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                           -30, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_7
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 100u
/// \input  CddDcmCtrl_nErrCntLow                         = 20;
/// \input  CddDcmCtrl_nErrCntHigh                        = 20;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 20u;
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 120u
/// \output CddDcmCtrl_nErrCntLow,                        = 40
/// \output CddDcmCtrl_nErrCntHigh,                       = 20
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 100u;
  CddDcmCtrl_nErrCntLow                         = 20;
  CddDcmCtrl_nErrCntHigh                        = 20;
  CddDcmHal_ulOutputLevel_FB                    = 20u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                           120u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                             40, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                            20, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_8
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not report errors when state condition is not met
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 100u
/// \input  CddDcmCtrl_nErrCntLow                         = 120;
/// \input  CddDcmCtrl_nErrCntHigh                        = 120;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 950u
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = TRUE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 120u
/// \output CddDcmCtrl_nErrCntLow,                        = 120
/// \output CddDcmCtrl_nErrCntHigh,                       = 140
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 100u;
  CddDcmCtrl_nErrCntLow                         = 120;
  CddDcmCtrl_nErrCntHigh                        = 120;
  CddDcmHal_ulOutputLevel_FB                    = 950u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                           120u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                            120, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                           140, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_9
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reports sh2vbat
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 500u
/// \input  CddDcmCtrl_nErrCntLow                         = 30;
/// \input  CddDcmCtrl_nErrCntHigh                        = 530;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = FALSE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 500u
/// \output CddDcmCtrl_nErrCntLow,                        = 10
/// \output CddDcmCtrl_nErrCntHigh,                       = 510
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 500u;
  CddDcmCtrl_nErrCntLow                         = 30;
  CddDcmCtrl_nErrCntHigh                        = 530;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                           500u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                             10, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                           510, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_10
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function reports sh2vbat
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone
/// \input  CddDcmCtrl_nErrCnt_ms                         = 500u
/// \input  CddDcmCtrl_nErrCntLow                         = 30;
/// \input  CddDcmCtrl_nErrCntHigh                        = 30;
/// \input  CddDcmHal_ulOutputLevel_FB                    = 200u
/// \input  te_Write_CddDcm_ErrorStatus_HitCount          = 0u;
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecBAT  = FALSE
/// \input  te_Write_CddDcm_ErrorStatus_Param1.boElecGND  = TRUE
///
/// - Expectations:
///
/// \output CddDcmCtrl_nErrCnt_ms,                        = 500u
/// \output CddDcmCtrl_nErrCntLow,                        = 10
/// \output CddDcmCtrl_nErrCntHigh,                       = 10
/// \output Rte_Write_CddDcm_ErrorStatus_HitCount,        = 1u
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE
/// \output Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_eState                             = CtrlDcm_StateMovingDone;
  CddDcmCtrl_nErrCnt_ms                         = 500u;
  CddDcmCtrl_nErrCntLow                         = 30;
  CddDcmCtrl_nErrCntHigh                        = 30;
  CddDcmHal_ulOutputLevel_FB                    = 200u;

  Rte_Write_CddDcm_ErrorStatus_HitCount         = 0u;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT = FALSE;
  Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND = TRUE;

  //Step 3) Call FUT
  CddDcmCtrl_DoErrorDetection();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCnt_ms,                           500u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntLow,                             10, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nErrCntHigh,                            10, == );

  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecBAT,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddDcm_ErrorStatus_Param1.boElecGND,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_DoErrorDetection
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_DoErrorDetection(void)
{
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_2();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_3();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_4();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_5();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_6();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_7();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_8();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_9();
  Mt_CddDcm_CddDcmCtrl_DoErrorDetection_TestCase_10();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function updates eeprom data 
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boEepromUpdated = FALSE
/// \input  NvM_WriteBlock_HitCount    = 0u;
/// \input  NvM_WriteBlock_RetVal      = E_OK;
///
/// - Expectations:
///
/// \output NvM_WriteBlock_HitCount,   = 1u
/// \output CddDcmCtrl_boEepromUpdated = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boEepromUpdated = FALSE;
  NvM_WriteBlock_HitCount    = 0u;
  NvM_WriteBlock_RetVal      = E_OK;

  //Step 3) Call FUT
  CddDcmCtrl_CyclicAlarm();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,      1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not update eeprom data but the data in NvM is correct
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boEepromUpdated = FALSE
/// \input  NvM_WriteBlock_HitCount    = 0u;
/// \input  NvM_WriteBlock_RetVal      = E_NOT_OK;
///
/// - Expectations:
///
/// \output NvM_WriteBlock_HitCount,   = 1u
/// \output CddDcmCtrl_boEepromUpdated = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boEepromUpdated = FALSE;
  NvM_WriteBlock_HitCount    = 0u;
  NvM_WriteBlock_RetVal      = E_NOT_OK;

  //Step 3) Call FUT
  CddDcmCtrl_CyclicAlarm();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not update eeprom data and the data from NvM is not correct
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boEepromUpdated = TRUE
/// \input  NvM_WriteBlock_HitCount    = 0u;
/// \input  NvM_WriteBlock_RetVal      = E_NOT_OK;
///
/// - Expectations:
///
/// \output NvM_WriteBlock_HitCount,   = 0u
/// \output CddDcmCtrl_boEepromUpdated = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boEepromUpdated = TRUE;
  NvM_WriteBlock_HitCount    = 0u;
  NvM_WriteBlock_RetVal      = E_NOT_OK;

  //Step 3) Call FUT
  CddDcmCtrl_CyclicAlarm();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,       0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_CyclicAlarm
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_CyclicAlarm(void)
{
  Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_2();
  Mt_CddDcm_CddDcmCtrl_CyclicAlarm_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Main_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test main function and check if cyclic functions are called properly
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boEepromUpdated = FALSE
/// \input  NvM_WriteBlock_HitCount    = 0u;
/// \input  NvM_WriteBlock_RetVal      = E_NOT_OK;
///
/// - Expectations:
///
/// \output NvM_WriteBlock_HitCount,   = 1u
/// \output CddDcmCtrl_boEepromUpdated = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Main_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boEepromUpdated = FALSE;
  NvM_WriteBlock_HitCount    = 0u;
  NvM_WriteBlock_RetVal      = E_NOT_OK;

  //Step 3) Call FUT
  CddDcmCtrl_Main();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Main_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test main function and check if cyclic functions are called properly, check if there is any voltage change and evaluates messages data
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boEepromUpdated = FALSE
/// \input  NvM_WriteBlock_HitCount    = 0u;
/// \input  NvM_WriteBlock_RetVal      = E_NOT_OK;
///
/// - Expectations:
///
/// \output NvM_WriteBlock_HitCount,   = 1u
/// \output CddDcmCtrl_boEepromUpdated = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Main_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boEepromUpdated = FALSE;
  NvM_WriteBlock_HitCount    = 0u;
  NvM_WriteBlock_RetVal      = E_NOT_OK;

  //Step 3) Call FUT
  CddDcmCtrl_Main();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,       1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmCtrl_Main
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmCtrl_Main(void)
{
  Mt_CddDcm_CddDcmCtrl_Main_TestCase_1();
  Mt_CddDcm_CddDcmCtrl_Main_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ActivateChannel_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function disables motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ActivateChannel_Param1  = 0u
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount = 0u
/// \input  IoHwAb_User_SetDio_EN_DC_Param1   = 3u
/// \input  Pwm_ClampPwmChannel_HitCount      = 0u
/// \input  Pwm_ClampPwmChannel_Param1        = 3u
/// \input  Pwm_ClampPwmChannel_Param2        = 3u
///
/// - Expectations:
///
/// \output IoHwAb_User_SetDio_EN_DC_HitCount = 1u
/// \output IoHwAb_User_SetDio_EN_DC_Param1,  = FALSE
/// \output Pwm_ClampPwmChannel_HitCount,     = 1u
/// \output Pwm_ClampPwmChannel_Param1,       = 5u
/// \output Pwm_ClampPwmChannel_Param2,       = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ActivateChannel_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ActivateChannel_Param1  = 0u;
  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;
  Pwm_ClampPwmChannel_HitCount      = 0u;
  Pwm_ClampPwmChannel_Param1        = 3u;
  Pwm_ClampPwmChannel_Param2        = 3u;

  //Step 3) Call FUT
  CddDcmHal_ActivateChannel(CddDcmHal_ActivateChannel_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      1u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_Param1,     FALSE, == );
  AL_UNITTEST_CHECK(Pwm_ClampPwmChannel_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Pwm_ClampPwmChannel_Param1,             5u, == );
  AL_UNITTEST_CHECK(Pwm_ClampPwmChannel_Param2,             0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ActivateChannel_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function enables motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ActivateChannel_Param1  = 1u;
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;
/// \input  Pwm_StartPwmChannel_HitCount      = 0u;
/// \input  Pwm_StartPwmChannel_Param1        = 3u;
/// \input  Pwm_SetDutyCycle_HitCount         = 0u;
/// \input  Pwm_SetDutyCycle_Param1           = 3u;
/// \input  Pwm_SetDutyCycle_Param2           = 3u;
/// \input  CddDcmHal_unLastPwmSignal         = 1000u
///
/// - Expectations:
///
/// \output IoHwAb_User_SetDio_EN_DC_HitCount = 1u
/// \output IoHwAb_User_SetDio_EN_DC_Param1,  = TRUE
/// \output Pwm_StartPwmChannel_HitCount,     = 1u
/// \output Pwm_StartPwmChannel_Param1,       = 5u
/// \output Pwm_SetDutyCycle_HitCount,        = 1u
/// \output Pwm_SetDutyCycle_Param1,          = 5u
/// \output Pwm_SetDutyCycle_Param2,          = 0x8000u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ActivateChannel_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ActivateChannel_Param1  = 1u;
  IoHwAb_User_SetDio_EN_DC_HitCount = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1   = 3u;
  Pwm_StartPwmChannel_HitCount      = 0u;
  Pwm_StartPwmChannel_Param1        = 3u;
  Pwm_SetDutyCycle_HitCount         = 0u;
  Pwm_SetDutyCycle_Param1           = 3u;
  Pwm_SetDutyCycle_Param2           = 3u;
  CddDcmHal_unLastPwmSignal         = 1000u;

  //Step 3) Call FUT
  CddDcmHal_ActivateChannel(CddDcmHal_ActivateChannel_Param1);

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      1u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_Param1,      TRUE, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_Param1,             5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,           0x8000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_ActivateChannel
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_ActivateChannel(void)
{
  Mt_CddDcm_CddDcmHal_ActivateChannel_TestCase_1();
  Mt_CddDcm_CddDcmHal_ActivateChannel_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function enables motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput            = 0x01u
/// \input  CddDcmHal_unMotorPwm                   = 100u;
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
/// \input  Pwm_StartPwmChannel_HitCount           = 0u;
/// \input  Pwm_StartPwmChannel_Param1             = 3u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  Pwm_SetDutyCycle_Param1                = 3u;
/// \input  Pwm_SetDutyCycle_Param2                = 3u;
/// \input  CddDcmHal_unLastPwmSignal              = 1000u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1,               = 5u
/// \output Pwm_SetDutyCycle_Param2,               = 0u
/// \output Pwm_SetDutyCycle_HitCount,             = 2u
/// \output CddDcmHal_unMotorPwm,                  = 0u
/// \output IoHwAb_User_SetDio_EN_DC_HitCount,     = 1u
/// \output Pwm_StartPwmChannel_HitCount,          = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput            = 0x01u;
  CddDcmHal_unMotorPwm                   = 100u;

  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  
  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
  Pwm_StartPwmChannel_HitCount           = 0u;
  Pwm_StartPwmChannel_Param1             = 3u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  Pwm_SetDutyCycle_Param1                = 3u;
  Pwm_SetDutyCycle_Param2                = 3u;
  CddDcmHal_unLastPwmSignal              = 1000u;

  //Step 3) Call FUT
  CddDcmHal_DoOutpPwmControl();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              2u, == );
  AL_UNITTEST_CHECK(CddDcmHal_unMotorPwm,                   0u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_HitCount,           1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_2
///
/// \FuSa Relevant:   NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Test Case Description
///        - Test subject: Test if functioncalculate dc pwm value
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput            = 0x01u
/// \input  CddDcmHal_unMotorPwm                   = 100u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 1u;
/// \input  CddDcmHal_ulOutputLevel_FB             = 0u;
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 0u;
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1   = 1u;
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
///
/// - Expectations:
///
/// \output IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 1u
/// \output CddDcmHal_ulOutputLevel_FB,            = 1000u
/// \output Pwm_SetDutyCycle_HitCount,             = 1u
/// \output CddDcmHal_unMotorPwm,                  = 100u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput            = 0x01u;
  CddDcmHal_unMotorPwm                   = 100u;
  CddDcmHal_ulAverageUdcmValue           = 1u;
  CddDcmHal_ulOutputLevel_FB             = 0u;

  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 0u;
  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1   = 1u;
  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;

  //Step 3) Call FUT
  CddDcmHal_DoOutpPwmControl();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount,     1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulOutputLevel_FB,              1000u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_unMotorPwm,                     100u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_3
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if functioncalculate dc pwm value
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput            = 0x01u
/// \input  CddDcmHal_unMotorPwm                   = 100u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 1u;
/// \input  CddDcmHal_ulOutputLevel_FB             = 0u;
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount = 0u;
/// \input  IoHwAbUser_GetAdc_VoltDC_OUT1_Param1   = 1u;
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  CddDcmHal_unLastPwmSignal              = 1000u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1,               = 3u
/// \output Pwm_SetDutyCycle_Param2,               = 3u
/// \output Pwm_SetDutyCycle_HitCount,             = 0u
/// \output CddDcmHal_unMotorPwm,                  = 100u
/// \output IoHwAb_User_SetDio_EN_DC_HitCount,     = 0u
/// \output Pwm_StartPwmChannel_HitCount,          = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput            = 0x01u;
  CddDcmHal_unMotorPwm                   = 100u;

  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  
  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
  Pwm_StartPwmChannel_HitCount           = 0u;
  Pwm_StartPwmChannel_Param1             = 3u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  Pwm_SetDutyCycle_Param1                = 3u;
  Pwm_SetDutyCycle_Param2                = 3u;
  CddDcmHal_unLastPwmSignal              = 1000u;

  //Step 3) Call FUT
  CddDcmHal_DoOutpPwmControl();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                3u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                3u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              0u, == );
  AL_UNITTEST_CHECK(CddDcmHal_unMotorPwm,                 100u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      0u, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_HitCount,           0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_4
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function enables motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput            = 0x02u
/// \input  CddDcmHal_unMotorPwm                   = 100u;
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
/// \input  Pwm_StartPwmChannel_HitCount           = 0u;
/// \input  Pwm_StartPwmChannel_Param1             = 3u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  Pwm_SetDutyCycle_Param1                = 3u;
/// \input  Pwm_SetDutyCycle_Param2                = 3u;
/// \input  CddDcmHal_unLastPwmSignal              = 1000u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1,               = 5u
/// \output Pwm_SetDutyCycle_Param2,               = 0u
/// \output Pwm_SetDutyCycle_HitCount,             = 1u
/// \output CddDcmHal_unMotorPwm,                  = 0u
/// \output IoHwAb_User_SetDio_EN_DC_HitCount,     = 1u
/// \output Pwm_StartPwmChannel_HitCount,          = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput            = 0x02u;
  CddDcmHal_unMotorPwm                   = 100u;

  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  
  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
  Pwm_StartPwmChannel_HitCount           = 0u;
  Pwm_StartPwmChannel_Param1             = 3u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  Pwm_SetDutyCycle_Param1                = 3u;
  Pwm_SetDutyCycle_Param2                = 3u;
  CddDcmHal_unLastPwmSignal              = 1000u;

  //Step 3) Call FUT
  CddDcmHal_DoOutpPwmControl();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_unMotorPwm,                   0u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_HitCount,           0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_5
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not calculate or enables motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput            = 0x02u
/// \input  CddDcmHal_unMotorPwm                   = 100u;
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
/// \input  Pwm_StartPwmChannel_HitCount           = 0u;
/// \input  Pwm_StartPwmChannel_Param1             = 3u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  Pwm_SetDutyCycle_Param1                = 3u;
/// \input  Pwm_SetDutyCycle_Param2                = 3u;
/// \input  CddDcmHal_unLastPwmSignal              = 1000u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1,               = 3u
/// \output Pwm_SetDutyCycle_Param2,               = 3u
/// \output Pwm_SetDutyCycle_HitCount,             = 0u
/// \output CddDcmHal_unMotorPwm,                  = 100u
/// \output IoHwAb_User_SetDio_EN_DC_HitCount,     = 0u
/// \output Pwm_StartPwmChannel_HitCount,          = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput            = 0x02u;
  CddDcmHal_unMotorPwm                   = 100u;

  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  
  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
  Pwm_StartPwmChannel_HitCount           = 0u;
  Pwm_StartPwmChannel_Param1             = 3u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  Pwm_SetDutyCycle_Param1                = 3u;
  Pwm_SetDutyCycle_Param2                = 3u;
  CddDcmHal_unLastPwmSignal              = 1000u;

  //Step 4) Check expected output value 
  CddDcmHal_DoOutpPwmControl();

  //Step 3) Call FUT  
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                3u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                3u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              0u, == );
  AL_UNITTEST_CHECK(CddDcmHal_unMotorPwm,                 100u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      0u, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_HitCount,           0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_6
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not calculate or enables motor
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_ucEnablePwmOutput            = 0x10u
/// \input  CddDcmHal_unMotorPwm                   = 100u;
/// \input  CddDcmHal_unOutputLevel                = 0u;
/// \input  CddDcmHal_ulAverageUdcmValue           = 0u;
/// \input  CddDcmHal_SetMotorPwm_Param1           = 1u;
/// \input  CddDcmHal_unLastPwmSignal              = 1u;
/// \input  Pwm_SetDutyCycle_Param1                = 0u;
/// \input  Pwm_SetDutyCycle_Param2                = 0u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
/// \input  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
/// \input  Pwm_StartPwmChannel_HitCount           = 0u;
/// \input  Pwm_StartPwmChannel_Param1             = 3u;
/// \input  Pwm_SetDutyCycle_HitCount              = 0u;
/// \input  Pwm_SetDutyCycle_Param1                = 3u;
/// \input  Pwm_SetDutyCycle_Param2                = 3u;
/// \input  CddDcmHal_unLastPwmSignal              = 1000u
///
/// - Expectations:
///
/// \output Pwm_SetDutyCycle_Param1,               = 3u
/// \output Pwm_SetDutyCycle_Param2,               = 3u
/// \output Pwm_SetDutyCycle_HitCount,             = 0u
/// \output CddDcmHal_unMotorPwm,                  = 100u
/// \output IoHwAb_User_SetDio_EN_DC_HitCount,     = 0u
/// \output Pwm_StartPwmChannel_HitCount,          = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_ucEnablePwmOutput            = 0x10u;
  CddDcmHal_unMotorPwm                   = 100u;

  CddDcmHal_unOutputLevel                = 0u;
  CddDcmHal_ulAverageUdcmValue           = 0u;
  CddDcmHal_SetMotorPwm_Param1           = 1u;
  CddDcmHal_unLastPwmSignal              = 1u;
  Pwm_SetDutyCycle_Param1                = 0u;
  Pwm_SetDutyCycle_Param2                = 0u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  
  IoHwAb_User_SetDio_EN_DC_HitCount      = 0u;
  IoHwAb_User_SetDio_EN_DC_Param1        = 3u;
  Pwm_StartPwmChannel_HitCount           = 0u;
  Pwm_StartPwmChannel_Param1             = 3u;
  Pwm_SetDutyCycle_HitCount              = 0u;
  Pwm_SetDutyCycle_Param1                = 3u;
  Pwm_SetDutyCycle_Param2                = 3u;
  CddDcmHal_unLastPwmSignal              = 1000u;

  //Step 3) Call FUT
  CddDcmHal_DoOutpPwmControl();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                3u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                3u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,              0u, == );
  AL_UNITTEST_CHECK(CddDcmHal_unMotorPwm,                 100u, == );
  AL_UNITTEST_CHECK(IoHwAb_User_SetDio_EN_DC_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Pwm_StartPwmChannel_HitCount,           0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_DoOutpPwmControl
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_DoOutpPwmControl(void)
{
  Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_1();
  Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_2();
  Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_3();
  Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_4();
  Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_5();
  Mt_CddDcm_CddDcmHal_DoOutpPwmControl_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_IrqHookOutputPwm_TestCase_1
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does not set average Vbat value
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u
/// \input  CddDcmHal_ulAverageUdcmValue                   = 0u
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
/// \output CddDcmHal_ulAverageUdcmValue                   = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_IrqHookOutputPwm_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values  
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u;
  CddDcmHal_ulAverageUdcmValue                   = 0u;

  //Step 3) Call FUT
  CddDcmHal_IrqHookOutputPwm();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulAverageUdcmValue,                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_IrqHookOutputPwm_TestCase_2
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function does sets average Vbat value and check if counter reset is done properly
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u
/// \input  CddDcmHal_ulAverageUdcmValue                   = 0u
///
/// - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
/// \output CddDcmHal_ulAverageUdcmValue                   = 3u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_IrqHookOutputPwm_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values  
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u;
  CddDcmHal_ulAverageUdcmValue                   = 0u;

  //Step 3) Call FUT
  CddDcmHal_IrqHookOutputPwm();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulAverageUdcmValue,                   3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_IrqHookOutputPwm
///
/// \FuSa Relevant: NA
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_IrqHookOutputPwm(void)
{
  Mt_CddDcm_CddDcmHal_IrqHookOutputPwm_TestCase_1();
  Mt_CddDcm_CddDcmHal_IrqHookOutputPwm_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_CddDcmHal_Init
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if function initialize correctly the Dc-motor driver
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unLastPwmSignal    = 1u
/// \input  CddDcmHal_ulOutputLevel_FB   = 0u
/// \input  Pwm_SetDutyCycle_Param1      = 0u
/// \input  Pwm_SetDutyCycle_Param2      = 0u
/// \input  Pwm_SetDutyCycle_HitCount    = 0u
///
/// - Expectations:
///
/// \output CddDcmHal_unLastPwmSignal,   = 0u
/// \output CddDcmHal_ulOutputLevel_FB,  = 0xffff
/// \output Pwm_SetDutyCycle_Param1,     = 5u
/// \output Pwm_SetDutyCycle_Param2,     = 0u
/// \output Pwm_SetDutyCycle_HitCount,   = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_CddDcmHal_Init(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unLastPwmSignal    = 1u;
  CddDcmHal_ulOutputLevel_FB   = 0u;
  Pwm_SetDutyCycle_Param1      = 0u;
  Pwm_SetDutyCycle_Param2      = 0u;
  Pwm_SetDutyCycle_HitCount    = 0u;

  //Step 3) Call FUT

  CddDcmHal_Init();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_unLastPwmSignal,          0u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulOutputLevel_FB,     0xffff, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,            5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,            0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,          1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_riCddDcm_Init
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Check correct execution of function riCddSpiInit
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmHal_unLastPwmSignal          = 1u;
/// \input  CddDcmHal_ulOutputLevel_FB         = 0u;
/// \input  Pwm_SetDutyCycle_Param1            = 0u;
/// \input  Pwm_SetDutyCycle_Param2            = 0u;
/// \input  Pwm_SetDutyCycle_HitCount          = 0u;
/// \input  CddDcmHal_ucEnablePwmOutput        = 1u;
/// \input  CddDcmCtrl_eVoltage                = 0u;
/// \input  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown
/// \input  NvmBlockDcMotorData.boMotorStarted = 1u;
/// \input  NvmBlockDcMotorData.boMotorStopped = 0u;
/// \input  NvmBlockDcMotorData.nPosition      = 23;
/// \input  CddDcmCtrl_nOldPos                 = 0u;
/// \input  CddDcmCtrl_nHighestPos             = 0u;
/// \input  CddDcmCtrl_nLowestPos              = 0u;
///
/// - Expectations:
///
/// \output CddDcmHal_unLastPwmSignal,   = 0u
/// \output CddDcmHal_ulOutputLevel_FB,  = 0xffff
/// \output Pwm_SetDutyCycle_Param1,     = 5u
/// \output Pwm_SetDutyCycle_Param2,     = 0u
/// \output Pwm_SetDutyCycle_HitCount,   = 1u
/// \output CddDcmHal_ucEnablePwmOutput, = 0u
/// \output CddDcmCtrl_eVoltage,         = 1u
/// \output CddDcmCtrl_eState,           = CtrlDcm_StateNotActive
/// \output CddDcmCtrl_nOldPos,          = CtrlDcm_PosUnknown
/// \output CddDcmCtrl_nHighestPos,      = CtrlDcm_PosRangeMax
/// \output CddDcmCtrl_nLowestPos,       = CtrlDcm_PosRangeMin
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_riCddDcm_Init(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmHal_unLastPwmSignal          = 1u;
  CddDcmHal_ulOutputLevel_FB         = 0u;
  Pwm_SetDutyCycle_Param1            = 0u;
  Pwm_SetDutyCycle_Param2            = 0u;
  Pwm_SetDutyCycle_HitCount          = 0u;
  CddDcmHal_ucEnablePwmOutput        = 1u;
  CddDcmCtrl_eVoltage                = 0u;
  CddDcmCtrl_eState                  = CtrlDcm_StateMovingDown;
  NvmBlockDcMotorData.boMotorStarted = 1u;
  NvmBlockDcMotorData.boMotorStopped = 0u;
  NvmBlockDcMotorData.nPosition      = 23;
  CddDcmCtrl_nOldPos                 = 0u;
  CddDcmCtrl_nHighestPos             = 0u;
  CddDcmCtrl_nLowestPos              = 0u;

  //Step 3) Call FUT

  riCddDcm_Init();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(CddDcmHal_unLastPwmSignal,                    0u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulOutputLevel_FB,               0xffff, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param1,                      5u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_Param2,                      0u, == );
  AL_UNITTEST_CHECK(Pwm_SetDutyCycle_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ucEnablePwmOutput,                  0u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eVoltage,                          1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_eState,        CtrlDcm_StateNotActive, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nOldPos,           CtrlDcm_PosUnknown, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nHighestPos,      CtrlDcm_PosRangeMax, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_nLowestPos,       CtrlDcm_PosRangeMin, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddDcm_rpCddDcm_Cycle0
///
/// \FuSa Relevant:   NA
///
/// \Test Case Description
///        - Test subject: Test if CDDDCM calls the cycle function correctly
///
///         - Test Design Technique:  - ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  CddDcmCtrl_boEepromUpdated                     = FALSE;
/// \input  NvM_WriteBlock_HitCount                        = 0u;
/// \input  NvM_WriteBlock_RetVal                          = E_NOT_OK
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
/// \input  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u;
/// \input  CddDcmHal_ulAverageUdcmValue                   = 0u;
///
/// - Expectations:
///
/// \output NvM_WriteBlock_HitCount,                       = 1u
/// \output CddDcmCtrl_boEepromUpdated,                    = FALSE
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 5u
/// \output CddDcmHal_ulAverageUdcmValue,                  = 3u
///
//-----------------------------------------------------------------------------
void Mt_CddDcm_rpCddDcm_Cycle0(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CddDcmCtrl_boEepromUpdated                     = FALSE;
  NvM_WriteBlock_HitCount                        = 0u;
  NvM_WriteBlock_RetVal                          = E_NOT_OK;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = 3u;
  CddDcmHal_ulAverageUdcmValue                   = 0u;

  //Step 3) Call FUT

  for (uint8 ucIdx = 0u; ucIdx < CDDDCM_SUBCYCLE; ucIdx++)
  {
    rpCddDcm_Cycle0();
  }

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,                         1u, == );
  AL_UNITTEST_CHECK(CddDcmCtrl_boEepromUpdated,                   FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount,  5u, == );
  AL_UNITTEST_CHECK(CddDcmHal_ulAverageUdcmValue,                    3u, == );
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
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_BbSettingStart",                    Mt_CddDcm_CddDcmCtrl_BbSettingStart);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_BbSettingStop_",                    Mt_CddDcm_CddDcmCtrl_BbSettingStop_);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_BbSettingDisable_",                 Mt_CddDcm_CddDcmCtrl_BbSettingDisable_);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_BbSettingVoltOnOff_",               Mt_CddDcm_CddDcmCtrl_BbSettingVoltOnOff_);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_BbSettingErr_OnOff_",               Mt_CddDcm_CddDcmCtrl_BbSettingErr_OnOff_);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_BbSettingInit_",                    Mt_CddDcm_CddDcmCtrl_BbSettingInit_);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_UpdateEepromData",                  Mt_CddDcm_CddDcmCtrl_UpdateEepromData);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_GetAdjustingTime",                  Mt_CddDcm_CddDcmCtrl_GetAdjustingTime);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_AlarmSet",                          Mt_CddDcm_CddDcmCtrl_AlarmSet);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_DisableChannel",                    Mt_CddDcm_CddDcmCtrl_DisableChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_Disable",                           Mt_CddDcm_CddDcmCtrl_Disable);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_Continue",                          Mt_CddDcm_CddDcmCtrl_Continue);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_InitChannel",                       Mt_CddDcm_CddDcmCtrl_InitChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_ResetErrorDetection_",              Mt_CddDcm_CddDcmCtrl_ResetErrorDetection_);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_IsMovingChannel",                   Mt_CddDcm_CddDcmCtrl_IsMovingChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_Init",                              Mt_CddDcm_CddDcmCtrl_Init);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_ServiceMotor",                      Mt_CddDcm_CddDcmCtrl_ServiceMotor);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_AlarmTimeout",                      Mt_CddDcm_CddDcmCtrl_AlarmTimeout);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel",                    Mt_CddDcm_CddDcmCtrl_CtrlMsgChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_CtrlMsg",                           Mt_CddDcm_CddDcmCtrl_CtrlMsg);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_VoltChange",                        Mt_CddDcm_CddDcmCtrl_VoltChange);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_DoErrorDetection",                  Mt_CddDcm_CddDcmCtrl_DoErrorDetection);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_CyclicAlarm",                       Mt_CddDcm_CddDcmCtrl_CyclicAlarm);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmCtrl_Main",                              Mt_CddDcm_CddDcmCtrl_Main);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcm_OutputEnable",                          Mt_CddDcm_CddDcm_OutputEnable);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcm_GetVdcm",                               Mt_CddDcm_CddDcm_GetVdcm);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcm_GetVbat",                               Mt_CddDcm_CddDcm_GetVbat);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_ChannelLevelCtrlStart",              Mt_CddDcm_CddDcmHal_ChannelLevelCtrlStart);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_DisableAndPwmOffChannel",            Mt_CddDcm_CddDcmHal_DisableAndPwmOffChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_ResetVoltageState",                  Mt_CddDcm_CddDcmHal_ResetVoltageState);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_SetOutpLevelChannel",                Mt_CddDcm_CddDcmHal_SetOutpLevelChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_EnableChannel",                      Mt_CddDcm_CddDcmHal_EnableChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_GetVoltageState",                    Mt_CddDcm_CddDcmHal_GetVoltageState);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_CalculatePwm",                       Mt_CddDcm_CddDcmHal_CalculatePwm);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_SetMotorPwm",                        Mt_CddDcm_CddDcmHal_SetMotorPwm);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_ActivateChannel",                    Mt_CddDcm_CddDcmHal_ActivateChannel);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn",                 Mt_CddDcm_CddDcmHal_ChannelLevelCtrlOn);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_DoOutpPwmControl",                   Mt_CddDcm_CddDcmHal_DoOutpPwmControl);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_IrqHookOutputPwm",                   Mt_CddDcm_CddDcmHal_IrqHookOutputPwm);
  ALUnitTest_AddFunction("Mt_CddDcm_CddDcmHal_Init",                               Mt_CddDcm_CddDcmHal_Init);
  ALUnitTest_AddFunction("Mt_CddDcm_riCddDcm_Init",                                Mt_CddDcm_riCddDcm_Init);
  ALUnitTest_AddFunction("Mt_CddDcm_rpCddDcm_Cycle0",                              Mt_CddDcm_rpCddDcm_Cycle0);
}
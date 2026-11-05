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
/// \brief Module test for McalIcu
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

#include "Test_Stubs.h"

#include "Test.h"



//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalIcu_Icu_GetMeasurementSens_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function gets PWM Measurement from Sensor 0
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Icu_GetMeasurementSens_Param1               = 0u
/// \input    FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u
/// \input    FTM_DRV_GetInputCaptureMeasurement_Param1   = 10u
/// \input    FTM_DRV_GetInputCaptureMeasurement_Param2   = 10u
/// \input    FTM_DRV_GetInputCaptureMeasurement_RetVal   = 123u
/// \input    Icu_GetMeasurementSens_RetVal               = 0u
///
///   - Expectations:
///
/// \output   FTM_DRV_GetInputCaptureMeasurement_HitCount = 1u
/// \output   FTM_DRV_GetInputCaptureMeasurement_Param1 = 0u
/// \output   FTM_DRV_GetInputCaptureMeasurement_Param2 = 0u
/// \output   Icu_GetMeasurementSens_RetVal = 123u
///
//-----------------------------------------------------------------------------
void Mt_McalIcu_Icu_GetMeasurementSens_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Icu_GetMeasurementSens_Param1               = 0u;
  FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u;
  FTM_DRV_GetInputCaptureMeasurement_Param1   = 10u;
  FTM_DRV_GetInputCaptureMeasurement_Param2   = 10u;
  FTM_DRV_GetInputCaptureMeasurement_RetVal   = 123u;
  Icu_GetMeasurementSens_RetVal               = 0u;

  //Step 3) Call FUT

  Icu_GetMeasurementSens_RetVal = Icu_GetMeasurementSens(Icu_GetMeasurementSens_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_HitCount,     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_Param1,       0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_Param2,       0u, == );
  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_RetVal,                 123u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalIcu_Icu_GetMeasurementSens_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function gets PWM Measurement from Sensor 1
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Icu_GetMeasurementSens_Param1               = 1u
/// \input    FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u
/// \input    FTM_DRV_GetInputCaptureMeasurement_Param1   = 10u
/// \input    FTM_DRV_GetInputCaptureMeasurement_Param2   = 10u
/// \input    FTM_DRV_GetInputCaptureMeasurement_RetVal   = 123u
/// \input    Icu_GetMeasurementSens_RetVal               = 0u
///
///   - Expectations:
///
/// \output   FTM_DRV_GetInputCaptureMeasurement_HitCount = 1u
/// \output   FTM_DRV_GetInputCaptureMeasurement_Param1 = 0u
/// \output   FTM_DRV_GetInputCaptureMeasurement_Param2 = 4u
/// \output   Icu_GetMeasurementSens_RetVal = 123u
///
//-----------------------------------------------------------------------------
void Mt_McalIcu_Icu_GetMeasurementSens_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Icu_GetMeasurementSens_Param1               = 1u;
  FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u;
  FTM_DRV_GetInputCaptureMeasurement_Param1   = 10u;
  FTM_DRV_GetInputCaptureMeasurement_Param2   = 10u;
  FTM_DRV_GetInputCaptureMeasurement_RetVal   = 123u;
  Icu_GetMeasurementSens_RetVal               = 0u;

  //Step 3) Call FUT

  Icu_GetMeasurementSens_RetVal = Icu_GetMeasurementSens(Icu_GetMeasurementSens_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_HitCount,     1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_Param1,       0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_Param2,       4u, == );
  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_RetVal,                 123u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalIcu_Icu_GetMeasurementSens_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function returns 0 when no sensor is selected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Icu_GetMeasurementSens_Param1               = 5u
/// \input    FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u
/// \input    FTM_DRV_GetInputCaptureMeasurement_Param1   = 10u
/// \input    FTM_DRV_GetInputCaptureMeasurement_Param2   = 10u
/// \input    FTM_DRV_GetInputCaptureMeasurement_RetVal   = 123u
/// \input    Icu_GetMeasurementSens_RetVal               = 55u
///
///   - Expectations:
///
/// \output   FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u
/// \output   FTM_DRV_GetInputCaptureMeasurement_Param1 = 10u
/// \output   FTM_DRV_GetInputCaptureMeasurement_Param2 = 10u
/// \output   Icu_GetMeasurementSens_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_McalIcu_Icu_GetMeasurementSens_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Icu_GetMeasurementSens_Param1               = 5u;
  FTM_DRV_GetInputCaptureMeasurement_HitCount = 0u;
  FTM_DRV_GetInputCaptureMeasurement_Param1   = 10u;
  FTM_DRV_GetInputCaptureMeasurement_Param2   = 10u;
  FTM_DRV_GetInputCaptureMeasurement_RetVal   = 123u;
  Icu_GetMeasurementSens_RetVal               = 55u;

  //Step 3) Call FUT

  Icu_GetMeasurementSens_RetVal = Icu_GetMeasurementSens(Icu_GetMeasurementSens_Param1);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_HitCount,     0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_Param1,      10u, == );
  AL_UNITTEST_CHECK(FTM_DRV_GetInputCaptureMeasurement_Param2,      10u, == );
  AL_UNITTEST_CHECK(Icu_GetMeasurementSens_RetVal,                   0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function Configures instance and channel for Sensor PWM 0 and sets the measurement mode to pulse high
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Icu_ChangeMeasurementMode_Param1   = 0u;
/// \input    Icu_ChangeMeasurementMode_Param2   = 1u;
/// \input    FTM_IC_DRV_SetChannelMode_HitCount = 0u;
/// \input    FTM_IC_DRV_SetChannelMode_Param1   = 22u;
/// \input    FTM_IC_DRV_SetChannelMode_Param2   = 22u;
/// \input    FTM_IC_DRV_SetChannelMode_Param3   = FTM_MEASURE_RISING_EDGE_PERIOD;
///
///   - Expectations:
///
/// \output   FTM_IC_DRV_SetChannelMode_HitCount = 1u
/// \output   FTM_IC_DRV_SetChannelMode_Param1 = 0u
/// \output   FTM_IC_DRV_SetChannelMode_Param2 = 0u
/// \output   FTM_IC_DRV_SetChannelMode_Param3 = FTM_MEASURE_PULSE_HIGH
///
//-----------------------------------------------------------------------------
void Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Icu_ChangeMeasurementMode_Param1   = 0u;
  Icu_ChangeMeasurementMode_Param2   = 1u;
  FTM_IC_DRV_SetChannelMode_HitCount = 0u;
  FTM_IC_DRV_SetChannelMode_Param1   = 22u;
  FTM_IC_DRV_SetChannelMode_Param2   = 22u;
  FTM_IC_DRV_SetChannelMode_Param3   = FTM_MEASURE_RISING_EDGE_PERIOD;

  //Step 3) Call FUT

  Icu_ChangeMeasurementMode(Icu_ChangeMeasurementMode_Param1, Icu_ChangeMeasurementMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_HitCount,                      1u, == );
  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_Param1,                        0u, == );
  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_Param2,                        0u, == );
  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_Param3,    FTM_MEASURE_PULSE_HIGH, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function Configures instance and channel for Sensor PWM 0 and measurment mode to rising edge
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Icu_ChangeMeasurementMode_Param1   = 1u;
/// \input    Icu_ChangeMeasurementMode_Param2   = 0u;
/// \input    FTM_IC_DRV_SetChannelMode_HitCount = 0u;
/// \input    FTM_IC_DRV_SetChannelMode_Param1   = 22u;
/// \input    FTM_IC_DRV_SetChannelMode_Param2   = 22u;
/// \input    FTM_IC_DRV_SetChannelMode_Param3   = FTM_MEASURE_PULSE_HIGH;
///
///   - Expectations:
///
/// \output   FTM_IC_DRV_SetChannelMode_HitCount = 1u
/// \output   FTM_IC_DRV_SetChannelMode_Param1 = 0u
/// \output   FTM_IC_DRV_SetChannelMode_Param2 = 4u
/// \output   FTM_IC_DRV_SetChannelMode_Param3 = FTM_MEASURE_RISING_EDGE_PERIOD
///
//-----------------------------------------------------------------------------
void Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Icu_ChangeMeasurementMode_Param1   = 1u;
  Icu_ChangeMeasurementMode_Param2   = 0u;
  FTM_IC_DRV_SetChannelMode_HitCount = 0u;
  FTM_IC_DRV_SetChannelMode_Param1   = 22u;
  FTM_IC_DRV_SetChannelMode_Param2   = 22u;
  FTM_IC_DRV_SetChannelMode_Param3   = FTM_MEASURE_PULSE_HIGH;

  //Step 3) Call FUT

  Icu_ChangeMeasurementMode(Icu_ChangeMeasurementMode_Param1, Icu_ChangeMeasurementMode_Param2);

  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_HitCount,                           1u, == );
  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_Param1,                             0u, == );
  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_Param2,                             4u, == );
  AL_UNITTEST_CHECK(FTM_IC_DRV_SetChannelMode_Param3, FTM_MEASURE_RISING_EDGE_PERIOD, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_McalIcu_Icu_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function Initialises the reading of PWM
///                     from sensors using given configuration
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Icu_Init_Param1                                = &sIcu_Config;
/// \input    FTM_DRV_Init_HitCount                          = 0u;
/// \input    FTM_DRV_Init_Param1                            = 1u;
/// \input    FTM_DRV_Init_Param2.BDMMode                    = FTM_BDM_MODE_00;
/// \input    FTM_DRV_Init_Param3.ftmPeriod                  = 333u;
/// \input    FTM_DRV_Init_Param3.ftmSourceClockFrequency    = 444u;
/// \input    ftmStatePtr[0u]->ftmMode                       = FTM_MODE_INPUT_CAPTURE;
/// \input    ftmStatePtr[0u]->ftmClockSource                = FTM_CLOCK_SOURCE_EXTERNALCLK;
/// \input    ftmStatePtr[0u]->ftmPeriod                     = 11u;
/// \input    ftmStatePtr[0u]->ftmSourceClockFrequency       = 22u;
/// \input    FTM_DRV_InitInputCapture_HitCount              = 0u;
/// \input    FTM_DRV_InitInputCapture_Param1                = 2u;
/// \input    FTM_DRV_InitInputCapture_Param2.nMaxCountValue = 0u;
/// \input    FTM_SC_PWMEN0_HitCount                         = 0u;
/// \input    FTM_SC_PWMEN0_Param1                           = 11u;
/// \input    FTM_SC_PWMEN4_HitCount                         = 0u;
/// \input    FTM_SC_PWMEN4_Param1                           = 11u;
/// \input    FTM_SC_PS_HitCount                             = 0u;
/// \input    FTM_SC_PS_Param1                               = 11u;
/// \input    FTM_SC_PS_RetVal                               = 13u;
/// \input    g_ftmBase1.CONF                                = 0x05u;
/// \input    FTM_RMW_SC_HitCount                            = 0u;
/// \input    FTM_RMW_SC_Param1.CONF                         = 0u;
/// \input    FTM_RMW_SC_Param2                              = 0u;
/// \input    FTM_RMW_SC_Param3                              = 0u;
///
///   - Expectations:
///
/// \output   FTM_DRV_Init_HitCount                          =                        1u
/// \output   FTM_DRV_Init_Param1                            =                        0u
/// \output   FTM_DRV_Init_Param2.BDMMode                    =           FTM_BDM_MODE_11
/// \output   ftmStatePtr[0u]->ftmMode                       =  FTM_MODE_NOT_INITIALIZED
/// \output   ftmStatePtr[0u]->ftmClockSource                =     FTM_CLOCK_SOURCE_NONE
/// \output   ftmStatePtr[0u]->ftmPeriod                     =                      333u
/// \output   ftmStatePtr[0u]->ftmSourceClockFrequency       =                      444u
/// \output   FTM_DRV_InitInputCapture_HitCount              =                        1u
/// \output   FTM_DRV_InitInputCapture_Param1                =                        0u
/// \output   FTM_DRV_InitInputCapture_Param2.nMaxCountValue =                    25000u
/// \output   FTM_SC_PWMEN0_HitCount                         =                        1u
/// \output   FTM_SC_PWMEN0_Param1                           =                        0u
/// \output   FTM_SC_PWMEN4_HitCount                         =                        1u
/// \output   FTM_SC_PWMEN4_Param1                           =                        0u
/// \output   FTM_SC_PS_HitCount                             =                        1u
/// \output   FTM_SC_PS_Param1                               =                     0x04U
/// \output   FTM_RMW_SC_HitCount                            =                        3u
/// \output   FTM_RMW_SC_Param1.CONF                         =                     0x05u
/// \output   FTM_RMW_SC_Param2                              =                      0x7u
/// \output   FTM_RMW_SC_Param3                              =                       13u
///
//-----------------------------------------------------------------------------
void Mt_McalIcu_Icu_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Icu_Init_Param1                                = &sIcu_Config;

  FTM_DRV_Init_HitCount                          = 0u;
  FTM_DRV_Init_Param1                            = 1u;
  FTM_DRV_Init_Param2.BDMMode                    = FTM_BDM_MODE_00;
  FTM_DRV_Init_Param3.ftmPeriod                  = 333u;
  FTM_DRV_Init_Param3.ftmSourceClockFrequency    = 444u;
  ftmStatePtr[0u]->ftmMode                       = FTM_MODE_INPUT_CAPTURE;
  ftmStatePtr[0u]->ftmClockSource                = FTM_CLOCK_SOURCE_EXTERNALCLK;
  ftmStatePtr[0u]->ftmPeriod                     = 11u;
  ftmStatePtr[0u]->ftmSourceClockFrequency       = 22u;

  FTM_DRV_InitInputCapture_HitCount              = 0u;
  FTM_DRV_InitInputCapture_Param1                = 2u;
  FTM_DRV_InitInputCapture_Param2.nMaxCountValue = 0u;

  FTM_SC_PWMEN0_HitCount                         = 0u;
  FTM_SC_PWMEN0_Param1                           = 11u;
  
  FTM_SC_PWMEN4_HitCount                         = 0u;
  FTM_SC_PWMEN4_Param1                           = 11u;

  FTM_SC_PS_HitCount                             = 0u;
  FTM_SC_PS_Param1                               = 11u;
  FTM_SC_PS_RetVal                               = 13u;

  g_ftmBase1.CONF                                = 0x05u;
  FTM_RMW_SC_HitCount                            = 0u;
  FTM_RMW_SC_Param1.CONF                         = 0u;
  FTM_RMW_SC_Param2                              = 0u;
  FTM_RMW_SC_Param3                              = 0u;

  //Step 3) Call FUT

  Icu_Init(Icu_Init_Param1);

  //Step 4) Check expected output values
  
  AL_UNITTEST_CHECK(FTM_DRV_Init_HitCount,                                         1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_Init_Param1,                                           0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_Init_Param2.BDMMode,                      FTM_BDM_MODE_11, == );
  AL_UNITTEST_CHECK(ftmStatePtr[0u]->ftmMode,                FTM_MODE_NOT_INITIALIZED, == );
  AL_UNITTEST_CHECK(ftmStatePtr[0u]->ftmClockSource,            FTM_CLOCK_SOURCE_NONE, == );
  AL_UNITTEST_CHECK(ftmStatePtr[0u]->ftmPeriod,                                  333u, == );
  AL_UNITTEST_CHECK(ftmStatePtr[0u]->ftmSourceClockFrequency,                    444u, == );
    
  AL_UNITTEST_CHECK(FTM_DRV_InitInputCapture_HitCount,                             1u, == );
  AL_UNITTEST_CHECK(FTM_DRV_InitInputCapture_Param1,                               0u, == );
  AL_UNITTEST_CHECK(FTM_DRV_InitInputCapture_Param2.nMaxCountValue,            25000u, == );

  AL_UNITTEST_CHECK(FTM_SC_PWMEN0_HitCount,                                        1u, == );
  AL_UNITTEST_CHECK(FTM_SC_PWMEN0_Param1,                                          0u, == );

  AL_UNITTEST_CHECK(FTM_SC_PWMEN4_HitCount,                                        1u, == );
  AL_UNITTEST_CHECK(FTM_SC_PWMEN4_Param1,                                          0u, == );
  
  AL_UNITTEST_CHECK(FTM_SC_PS_HitCount,                                            1u, == );
  AL_UNITTEST_CHECK(FTM_SC_PS_Param1,                                           0x04U, == );
  
  AL_UNITTEST_CHECK(FTM_RMW_SC_HitCount,                                           3u, == );
  AL_UNITTEST_CHECK(FTM_RMW_SC_Param1.CONF,                                     0x05u, == );
  AL_UNITTEST_CHECK(FTM_RMW_SC_Param2,                                           0x7u, == );
  AL_UNITTEST_CHECK(FTM_RMW_SC_Param3,                                            13u, == );
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
  ALUnitTest_AddFunction("Mt_McalIcu_Icu_GetMeasurementSens_TestCase_1",           Mt_McalIcu_Icu_GetMeasurementSens_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalIcu_Icu_GetMeasurementSens_TestCase_2",           Mt_McalIcu_Icu_GetMeasurementSens_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalIcu_Icu_GetMeasurementSens_TestCase_3",           Mt_McalIcu_Icu_GetMeasurementSens_TestCase_3);
  ALUnitTest_AddFunction("Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_1",        Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_1);
  ALUnitTest_AddFunction("Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_2",        Mt_McalIcu_Icu_ChangeMeasurementMode_TestCase_2);
  ALUnitTest_AddFunction("Mt_McalIcu_Icu_Init_TestCase_1",                         Mt_McalIcu_Icu_Init_TestCase_1);
}
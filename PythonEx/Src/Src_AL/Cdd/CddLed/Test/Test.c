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
/// \brief Unit test of generic code in CddLed module
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include <Test_Ext.h>
#include "Test_Stubs.h"

// Headers of the unit test Module
#include <Test.h>
#include <Test_Adapter.h>

//-----------------------------------------------------------------------------
// Test implementation
//-----------------------------------------------------------------------------
static void InitConditions(void)
{
  RestoreStubContents();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_GetStatus
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check status
///        Check all paths for status calculation
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Disable channel 0
///         Step2: Set current and duty cycle for channels 1..3
///         Step3: Check status for led channels [0..3]
///         Step4: Enable all led channels
///         Step5: Set current and duty cycle for channels 0..3
///         Step6: Set short to gnd error for ch 0
///         Step7: Set open load error for ch 1
///         Step8: Check status for led channels [0..3]
///
///    - Expected test results: 
///        - Read error status, Vin status and voltages
///            Step3) : 
///                 Test_Status.aStatus[0].Err =  eCddLed_NoSupport
///                 Test_Status.aStatus[1].Err =  eCddLed_StatusOk
///                 Test_Status.aStatus[2].Err =  2u
///                 Test_Status.aStatus[3].Err =  eCddLed_ErrUnderVoltage
///
///            Step8) : 
///                 Test_Status.aStatus[0].Err =  eCddLed_ErrShortToGnd
///                 Test_Status.aStatus[1].Err =  eCddLed_ErrOpenLoad,
///                 Test_Status.aStatus[0].Vin =  eCddLed_VinOk
///                 Test_Status.aStatus[1].Vin =  eCddLed_VinLo
///                 Test_Status.aStatus[2].unVLed =  23456u
///                 Test_Status.aStatus[3].unVLed =  0u
///
//-----------------------------------------------------------------------------
void Mt_CddLed_GetStatus(void)
{
  tCddLedStatus Test_Status;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_ulAvailMask = 0x0FFEu;  // disable channel 0
  CddLed_sTarget.aTarget[1].unCurrent_mA = 0u;
  CddLed_sTarget.aTarget[2].unCurrent_mA = 500u;
  CddLed_sTarget.aTarget[3].unCurrent_mA = 1000u;
  CddLed_sTarget.aTarget[1].unDutyCycle_1_32768 = 32768u;
  CddLed_sTarget.aTarget[2].unDutyCycle_1_32768 = 0u;
  CddLed_sTarget.aTarget[3].unDutyCycle_1_32768 = 16384u;

  //Step 3) Call the FUT
  CddLed_GetStatus(&Test_Status);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Status.aStatus[0].Err, eCddLed_NoSupport, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[1].Err, eCddLed_StatusOk,  == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[2].Err, 2u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[3].Err, eCddLed_ErrUnderVoltage,  == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_ulAvailMask          = 0x0FFFu;  // restore
  CddLed_unInputVoltThreshold = 35000u;
  CddLed_sTarget.aTarget[0].unCurrent_mA = 1000u;
  CddLed_sTarget.aTarget[1].unCurrent_mA = 1000u;
  CddLed_sTarget.aTarget[2].unCurrent_mA = 1000u;
  CddLed_sTarget.aTarget[3].unCurrent_mA = 1000u;
  CddLed_sTarget.aTarget[0].unDutyCycle_1_32768 = 32768u;
  CddLed_sTarget.aTarget[1].unDutyCycle_1_32768 = 32768u;
  CddLed_sTarget.aTarget[2].unDutyCycle_1_32768 = 32768u;
  CddLed_sTarget.aTarget[3].unDutyCycle_1_32768 = 16384u;
  Test_Drv_SetInputVoltage_mV(0u, 36000u);
  Test_Drv_SetInputVoltage_mV(1u, 34000u);
  Test_Drv_SetLedVoltage_mV  (2u, 23456u, TRUE);  // use VLED for 100% PWM
  Test_Drv_SetLedVoltOnOff_mV(3u, 12345u);  // use VLED_ON for 50% PWM
  Test_Drv_SetShortToGnd     (0u, TRUE);
  Test_Drv_SetOpenLoad       (1u, TRUE);

  //Step 3) Call the FUT
  CddLed_GetStatus(&Test_Status);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Status.aStatus[0].Err, eCddLed_ErrShortToGnd, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[1].Err, eCddLed_ErrOpenLoad,  == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[0].Vin, eCddLed_VinOk, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[1].Vin, eCddLed_VinLo, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[2].unVLed, 23456u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[3].unVLed, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_Init
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check that CddLed_ulAvailMask contains the number of activated LED
///        channels
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Read CddLed_ulAvailMask
///          CddLed_ulAvailMask = 0x0Fu (ch0..3 activated)
///
//-----------------------------------------------------------------------------
void Mt_CddLed_Init(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_ulAvailMask = 0u;
  Test_Drv_SetInitVal(0x0Fu);  // activate channels 0...3

  //Step 3) Call the FUT
  CddLed_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_ulAvailMask, 0x0Fu, == );

  CddLed_ulAvailMask = 0x0FFFu;  // restore
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_SetTarget
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check current and duty cycle
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Read current and duty cycle for channel 1
///          Test_Drv_GetCurrent(1u)    = 1234u
///          Test_Drv_GetDutyCycle(1u)  = 23456u
///
//-----------------------------------------------------------------------------
void Mt_CddLed_SetTarget(void)
{
  tCddLedTarget Test_Target;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_ulAvailMask = 0x0FFBu;  // disable channel 2
  CddLed_ulOnMask                 = 0xAAu;
  CddLed_aucOffCounter[TEST_Chn0] = 18u;  // 360ms / 20
  CddLed_aunLedVoltage[TEST_Chn0] = 12000u;
  Test_Target.aTarget [TEST_Chn0].unCurrent_mA        = 1234u;
  Test_Target.aTarget [TEST_Chn0].unDutyCycle_1_32768 = 23456u;
  Test_Target.aTarget [TEST_Chn1].unCurrent_mA        = 1234u;
  Test_Target.aTarget [TEST_Chn1].unDutyCycle_1_32768 = 23456u;

  //Step 3) Call the FUT
  CddLed_SetTarget(&Test_Target);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(1u), 1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(1u), 23456u, == );

  CddLed_aunLedVoltage[TEST_Chn0] = 0u;  // reset for further tests
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_SetPara
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check booster voltage threshold
///
///    - Test Design Technique: Requirement based test
///                             Fault injection
/// \Steps:
///         Step1: Set input voltage treshold
///         Step2: Call FUT for no updates on voltage
///         Step3: Check voltage treshold is not changed
///         Step4: Call FUT to update the voltage
///         Step5: Check voltage treshold is computed
///         Step6: Call FUT to update the voltage for Booster Voltage above limit
///         Step7: Check voltage treshold is computed
///
///    - Preconditions: none
///
///    - Expected test results: 
///           Based on the inputs given in the previous steps:
///        - Step 3) CddLed_unInputVoltThreshold = 30000u 
///        - Step 5) CddLed_unInputVoltThreshold = 35500u 
///        - Step 7) CddLed_unInputVoltThreshold = 44000u 
///
//-----------------------------------------------------------------------------
void Mt_CddLed_SetPara(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_unInputVoltThreshold = 30000u;  // set wrong

  //Step 3) Call the FUT
  CddLed_SetPara(FALSE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_unInputVoltThreshold, 30000u, == );  // keep wrong
 

  //Step 3) Call the FUT
  CddLed_SetPara(TRUE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_unInputVoltThreshold, 35000U, == );  // now we shall get correct value

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_OVER_VOLTAGE[11] = 235u;

  //Step 3) Call the FUT
  CddLed_SetPara(TRUE);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_unInputVoltThreshold, 44000U, == );  // now we shall get correct value

  //restore value
  applicationCodingData.Led1.FUSAConfig.FUSA_DRV_LED_OVER_VOLTAGE[11] = 0u;
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_Cycle20ms
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check incrementation of counter
///
///    - Test Design Technique: Requirement based test
///                             ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - CddLed_aucOffCounter[0] = 6u
///        - CddLed_aucOffCounter[1] = 18u
///
//-----------------------------------------------------------------------------
void Mt_CddLed_Cycle20ms(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_aucOffCounter[0] = 5u;
  CddLed_aucOffCounter[1] = 18u;  // 360ms / 20ms = 18 = max. value

  //Step 3) Call the FUT
  CddLed_Cycle20ms();

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aucOffCounter[0],  6u, == );  // incremented value
  AL_UNITTEST_CHECK(CddLed_aucOffCounter[1], 18u, == );  // keep value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_DebounceThermShutDn
///
/// \Test Case Description
///    - Test subject: 
///        Check incrementation and decrementation of debounce counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_DebounceThermShutDn(void)
{
  boolean boRet1, boRet2, boRet3, boRet4;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_aucThermShutDn[TEST_Chn0] = 2u;
  CddLed_aucThermShutDn[TEST_Chn1] = 3u;
  CddLed_aucThermShutDn[TEST_Chn2] = 4u;
  CddLed_aucThermShutDn[TEST_Chn3] = 5u;

  CddLed_aboThermShutDn[TEST_Chn0] = FALSE;
  CddLed_aboThermShutDn[TEST_Chn1] = FALSE;
  CddLed_aboThermShutDn[TEST_Chn2] = FALSE;
  CddLed_aboThermShutDn[TEST_Chn3] = TRUE;

  //Step 3) Call the FUT
  boRet1 = CddLed_DebounceThermShutDn(TEST_Chn0, FALSE);  // decrement
  boRet2 = CddLed_DebounceThermShutDn(TEST_Chn1, TRUE );  // increment
  boRet3 = CddLed_DebounceThermShutDn(TEST_Chn2, TRUE );  // increment and validate
  boRet4 = CddLed_DebounceThermShutDn(TEST_Chn3, TRUE );  // error valid, no increment

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aucThermShutDn[TEST_Chn0], 1u, == );  // decemented
  AL_UNITTEST_CHECK(CddLed_aucThermShutDn[TEST_Chn1], 4u, == );  // incremented
  AL_UNITTEST_CHECK(CddLed_aucThermShutDn[TEST_Chn2], 5u, == );  // incremented
  AL_UNITTEST_CHECK(CddLed_aucThermShutDn[TEST_Chn3], 5u, == );  // not incremented
  AL_UNITTEST_CHECK(boRet1, FALSE, == );  // not validated
  AL_UNITTEST_CHECK(boRet2, FALSE, == );  // not validated
  AL_UNITTEST_CHECK(boRet3, TRUE,  == );  // validated
  AL_UNITTEST_CHECK(boRet4, TRUE,  == );  // validated
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_DebounceOvercurrent
///
/// \Test Case Description
///    - Test subject: 
///        Check incrementation and decrementation of debounce counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_DebounceOvercurrent(void)
{
  boolean boRet1, boRet2, boRet3, boRet4;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_aucOverCurrent[TEST_Chn0] = 2u;
  CddLed_aucOverCurrent[TEST_Chn1] = 3u;
  CddLed_aucOverCurrent[TEST_Chn2] = 4u;
  CddLed_aucOverCurrent[TEST_Chn3] = 5u;

  CddLed_aboOverCurrent[TEST_Chn0] = FALSE;
  CddLed_aboOverCurrent[TEST_Chn1] = FALSE;
  CddLed_aboOverCurrent[TEST_Chn2] = FALSE;
  CddLed_aboOverCurrent[TEST_Chn3] = TRUE;

  //Step 3) Call the FUT
  boRet1 = CddLed_DebounceOvercurrent(TEST_Chn0, FALSE);  // decrement
  boRet2 = CddLed_DebounceOvercurrent(TEST_Chn1, TRUE );  // increment
  boRet3 = CddLed_DebounceOvercurrent(TEST_Chn2, TRUE );  // increment and validate
  boRet4 = CddLed_DebounceOvercurrent(TEST_Chn3, TRUE );  // error valid, no increment

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aucOverCurrent[TEST_Chn0], 1u, == );  // decemented
  AL_UNITTEST_CHECK(CddLed_aucOverCurrent[TEST_Chn1], 4u, == );  // incremented
  AL_UNITTEST_CHECK(CddLed_aucOverCurrent[TEST_Chn2], 5u, == );  // incremented
  AL_UNITTEST_CHECK(CddLed_aucOverCurrent[TEST_Chn3], 5u, == );  // not incremented
  AL_UNITTEST_CHECK(boRet1, FALSE, == );  // not validated
  AL_UNITTEST_CHECK(boRet2, FALSE, == );  // not validated
  AL_UNITTEST_CHECK(boRet3, TRUE,  == );  // validated
  AL_UNITTEST_CHECK(boRet4, TRUE,  == );  // validated
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_EvaluateElectricalErrors
///
/// \Test Case Description
///    - Test subject: 
///        Check error list based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_EvaluateElectricalErrors(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_ulShortUbatMask = 0x55u;   // use alternating bits
  Test_Drv_SetDriverActive(TEST_Chn0, FALSE);
  Test_Drv_SetDriverActive(TEST_Chn1, TRUE );

  //Step 3) Call the FUT
  CddLed_EvaluateElectricalErrors(TEST_Chn0);  // test using bit=1
  CddLed_EvaluateElectricalErrors(TEST_Chn1);  // test using bit=0

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn0], 0x440u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn1],     0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_EvaluateInternalErrors
///
/// \Test Case Description
///    - Test subject: 
///        Check error list based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_EvaluateInternalErrors(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetThermalWarning(TEST_Chn0, FALSE);
  Test_Drv_SetThermalWarning(TEST_Chn1, TRUE );

  //Step 3) Call the FUT
  CddLed_EvaluateInternalErrors(TEST_Chn0);  // test using FALSE
  CddLed_EvaluateInternalErrors(TEST_Chn1);  // test using TRUE

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn0], 0x440u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn1], 0x200u,  == );

#ifdef CDDLED_Cfg_Simulation
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_Simulation_Data.ulSimActivated = CDDLED_SimulationPassword;   
  CddLed_Simulation_Data.ulSimThermalWarning  = 0x55;  // set alternating bit pattern
  CddLed_Simulation_Data.ulSimThermalShutdown = 0xAA;  // set alternating bit pattern
  CddLed_Simulation_Data.ulSimOverCurrent     = 0x55;  // set alternating bit pattern

  //Step 3) Call the FUT
  CddLed_EvaluateInternalErrors(TEST_Chn0);  // test with 1st setting
  CddLed_EvaluateInternalErrors(TEST_Chn1);  // test using inverted setting

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn0], 0x642u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn1], 0x201u, == );

  // reset to default
  CddLed_Simulation_Data.ulSimActivated = CDDLED_SimulationDeactivated;
#endif
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_EvaluateLedVoltage
///
/// \Test Case Description
///    - Test subject: 
///        Check error list based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_EvaluateLedVoltage(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetLedVoltage_mV(TEST_Chn0, 12345u, TRUE);  // normal voltage
  Test_Drv_SetLedVoltage_mV(TEST_Chn1, 12345u, TRUE);  // normal voltage
  CddLed_Settings.ulDisableErrUnderVoltage = 0x03;
  CddLed_Settings.ulDisableErrOverVoltage  = 0x03;

  //Step 3) Call the FUT
  CddLed_EvaluateLedVoltage(TEST_Chn0);  // test according to list above
  CddLed_EvaluateLedVoltage(TEST_Chn1);  //

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn0], 0x6C2u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn1], 0x281u, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_Settings.ulDisableErrUnderVoltage = 0;
  CddLed_Settings.ulDisableErrOverVoltage  = 0;
  Test_Drv_SetLedVoltage_mV(TEST_Chn0, 12345u, FALSE);  // not available
  Test_Drv_SetLedVoltage_mV(TEST_Chn1, 12345u, TRUE);  // normal voltage
  Test_Drv_SetLedVoltage_mV(TEST_Chn2,  2200u, TRUE);  // below 2.25V
  Test_Drv_SetLedVoltage_mV(TEST_Chn3,  5678u, TRUE);  // between 2.25 and 10V

  //Step 3) Call the FUT
  CddLed_EvaluateLedVoltage(TEST_Chn0);  // test according to list above
  CddLed_EvaluateLedVoltage(TEST_Chn1);  //
  CddLed_EvaluateLedVoltage(TEST_Chn2);  //
  CddLed_EvaluateLedVoltage(TEST_Chn3);  //

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn0], 0x6C2u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn1], 0x281u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn2], 0x4A0u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn3], 0x4B0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_EvaluateAuxVoltages
///
/// \Test Case Description
///    - Test subject: 
///        Check error list based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_EvaluateAuxVoltages(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetLedVoltOnOff_mV(TEST_Chn0, 65535u);  // not available
  Test_Drv_SetLedVoltOnOff_mV(TEST_Chn1,  2345u);  // normal voltage

  //Step 3) Call the FUT
  CddLed_EvaluateAuxVoltages(TEST_Chn0);  // test according to list above
  CddLed_EvaluateAuxVoltages(TEST_Chn1);  //

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn0], 0x6C2u, == );
  AL_UNITTEST_CHECK(CddLed_aunErrorList[TEST_Chn1], 0x281u, == );

#ifdef CDDLED_Cfg_Simulation
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_Simulation_Data.ulSimActivated      = CDDLED_SimulationPassword;   
  CddLed_Simulation_Data.aunSimVBoostMeas[0] = 34567u;

  //Step 3) Call the FUT
  CddLed_EvaluateAuxVoltages(TEST_Chn0);  // test with 1st setting
 
  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList   [TEST_Chn0], 0x7C2u, == );
  AL_UNITTEST_CHECK(CddLed_aunInputVoltage[TEST_Chn0], 34567u, == );

   //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_Simulation_Data.ulSimActivated      = CDDLED_SimulationPassword;   
  CddLed_Simulation_Data.aunSimVBoostMeas[0] = 0u;

  //Step 3) Call the FUT
  CddLed_EvaluateAuxVoltages(TEST_Chn0);  // test with 1st setting
 
  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_aunErrorList         [TEST_Chn0], 0x7C2u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetInputVoltage_mV(TEST_Chn0),  45000u, == );
  AL_UNITTEST_CHECK(CddLed_aunInputVoltage[TEST_Chn0],       45000u, == );

  // reset to default
  CddLed_Simulation_Data.ulSimActivated = CDDLED_SimulationDeactivated;
#endif
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_CreateErrStatus
///
/// \Test Case Description
///    - Test subject: 
///        Check error state based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_CreateErrStatus(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetSpiError(TEST_Chn0, TRUE);

  //Step 3) Call the FUT
  CddLed_CreateErrStatus(TEST_Chn0, &Test_Status);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn0].Err, 12u, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Drv_SetSpiError(TEST_Chn0, FALSE);
  CddLed_aunErrorList[TEST_Chn0] =      0u;  // zero pattern
  CddLed_aunErrorList[TEST_Chn1] = 0x5555u;  // use alternating patterns
  CddLed_aunErrorList[TEST_Chn2] = 0x0100u;  // VoltOnOffLow
  CddLed_aunErrorList[TEST_Chn3] = 0xFFFFu;  // 1 pattern
  CddLed_sTarget.aTarget[TEST_Chn2].unDutyCycle_1_32768 = 32768u;

  //Step 3) Call the FUT
  CddLed_CreateErrStatus(TEST_Chn0, &Test_Status);  // 
  CddLed_CreateErrStatus(TEST_Chn1, &Test_Status);  // 
  CddLed_CreateErrStatus(TEST_Chn2, &Test_Status);  // 
  CddLed_CreateErrStatus(TEST_Chn3, &Test_Status);  // 

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn0].Err,    2u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn1].Err,    7u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn2].Err,    4u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn3].Err,    0u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn0].unVLed, 0u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn1].unVLed, 0u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn2].unVLed, 0u, == );
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn3].unVLed, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_CreateChnStatus
///
/// \Test Case Description
///    - Test subject: 
///        Check channel state based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_CreateChnStatus(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_aunErrorList[TEST_Chn0] =      0u;  // zero pattern
  CddLed_aunErrorList[TEST_Chn1] =      0u;  // zero pattern
  CddLed_aunErrorList[TEST_Chn2] = 0x0008u;  // open load
  CddLed_sTarget.aTarget[TEST_Chn0].unDutyCycle_1_32768 = 12345u;
  CddLed_sTarget.aTarget[TEST_Chn1].unDutyCycle_1_32768 = 23456u;
  CddLed_sTarget.aTarget[TEST_Chn2].unDutyCycle_1_32768 = 23456u;
  Test_Status.aStatus[TEST_Chn0].Err = eCddLed_StatusOk;
  Test_Status.aStatus[TEST_Chn1].Err = eCddLed_StatusOk;
  Test_Status.aStatus[TEST_Chn2].Err = eCddLed_StatusOk;

  Test_Drv_SetDutyCycle_1_32768(TEST_Chn0, 23456u);
  Test_Drv_SetDutyCycle_1_32768(TEST_Chn1, 23456u);
  Test_Drv_SetDutyCycle_1_32768(TEST_Chn2, 23456u);

  //Step 3) Call the FUT
  CddLed_CreateChnStatus(TEST_Chn0, &Test_Status);  // Check status of 3 channels
  CddLed_CreateChnStatus(TEST_Chn1, &Test_Status);  // 
  CddLed_CreateChnStatus(TEST_Chn2, &Test_Status);  // 

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn0].Chn, 0u, == );  // undef because of wrong duty
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn1].Chn, 2u, == );  // ok
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn2].Chn, 2u, == );  // ok because open load overwritten by Err state
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_CreateAuxStatus
///
/// \Test Case Description
///    - Test subject: 
///        Check channel state based on injected faults
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - none
///
//-----------------------------------------------------------------------------
void Mt_CddLed_CreateAuxStatus(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_aunErrorList[TEST_Chn0] = 0x0200u;  // thermal warning

  //Step 3) Call the FUT
  CddLed_CreateAuxStatus(TEST_Chn0, &Test_Status);

  //Step 4) Check that the value of the output variables set/changed by the FUT matches the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Status.aStatus[TEST_Chn0].TempData.boThermalWarning, TRUE, == );  // undef because of wrong duty
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
  ALUnitTest_AddFunction("Mt_CddLed_GetStatus"   , Mt_CddLed_GetStatus);
  ALUnitTest_AddFunction("Mt_CddLed_Init"        , Mt_CddLed_Init);
  ALUnitTest_AddFunction("Mt_CddLed_SetTarget"   , Mt_CddLed_SetTarget);
  ALUnitTest_AddFunction("Mt_CddLed_SetPara"     , Mt_CddLed_SetPara);
  ALUnitTest_AddFunction("Mt_CddLed_Cycle20ms"   , Mt_CddLed_Cycle20ms);

  // STATIC_AL functions
  ALUnitTest_AddFunction("Mt_CddLed_DebounceThermShutDn"     , Mt_CddLed_DebounceThermShutDn);
  ALUnitTest_AddFunction("Mt_CddLed_DebounceOvercurrent"     , Mt_CddLed_DebounceOvercurrent);
  ALUnitTest_AddFunction("Mt_CddLed_EvaluateElectricalErrors", Mt_CddLed_EvaluateElectricalErrors);
  ALUnitTest_AddFunction("Mt_CddLed_EvaluateInternalErrors"  , Mt_CddLed_EvaluateInternalErrors);
  ALUnitTest_AddFunction("Mt_CddLed_EvaluateLedVoltage"      , Mt_CddLed_EvaluateLedVoltage);
  ALUnitTest_AddFunction("Mt_CddLed_EvaluateAuxVoltages"     , Mt_CddLed_EvaluateAuxVoltages);
  ALUnitTest_AddFunction("Mt_CddLed_CreateErrStatus"         , Mt_CddLed_CreateErrStatus);
  ALUnitTest_AddFunction("Mt_CddLed_CreateChnStatus"         , Mt_CddLed_CreateChnStatus);
  ALUnitTest_AddFunction("Mt_CddLed_CreateAuxStatus"         , Mt_CddLed_CreateAuxStatus);

  // project specific tests of adapter
  ALUnitTest_AddTests_Adapter();
}

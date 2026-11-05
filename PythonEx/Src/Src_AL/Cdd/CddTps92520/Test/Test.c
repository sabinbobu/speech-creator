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
/// \brief Unit tests for CddTps92520.c and CddTps92520_Com.c
///
//-----------------------------------------------------------------------------

#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"
#include "Test_Ext.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
// Initialization of test cases
//-----------------------------------------------------------------------------
static void InitConditions(void)
{
  RestoreStubContents();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_Init
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on EFT data
///
///    - Test Design Technique:  - Requirement based test
///                              - Fault injection
///
/// \Steps:
///         Step1: Set channel 0 disabled in EFT data
///         Step2: Check configuration : 0x0B
///         Step3: Set EFT data as invalid
///         Step4: Check configuration : 0x00 (no LED channel configured)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Based on the inputs given in previous steps, expected values are:
///           EFT Ch 0 disabled : 0x0B due to configuration of channel 2 missing (xxxxx1011)
///           EFT invalid       : nothing to be configured
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_Init(void)
{
  uint32 ulRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Eft_EcuVarCfg()[TEST_ChipIdx1].aDrv[TEST_Chip0].ucAssignedOutput = TEST_EftDisabled;

  //Step 3) Call the FUT
  ulRet = TEST_ChannelMask & CddTps92520_Init();  // test on channels 0...3

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ulRet, TEST_ChannelMask & 0x0B, == );  // channel 2 missing (xxxxx1011)

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_SetEftDataValid(FALSE);

  //Step 3) Call the FUT
  ulRet = TEST_ChannelMask & CddTps92520_Init();  // test on channels 0...3

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ulRet, 0u, == );  // EftData invalid
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_Cycle20ms
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if all funcion calls inside are processed
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - all functions called
///          unChk = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_Cycle20ms(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aCHxVIN    [TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVIN     = 200u;  // set 4 different values
  CddTps92520_DataMirror.StatRx.aCHxVLED   [TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVLED    = 100u;
  CddTps92520_DataMirror.StatRx.aCHxVLEDON [TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVLEDON  = 120u;
  uint16 unChk = CddTps92520_aunInputVoltage[TEST_Chn2];

  //Step 3) Call the FUT
  CddTps92520_Cycle20ms();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unChk, 0, == ); // make sure that value is set to 0 before calling
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SetCurrent_mA
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check write to data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - High byte of data mirror must be different from 0
///          CddTps92520_DataMirror.CtrlTx.aCHxIADJH[TEST_ChipIdx1][TEST_Chip1].Byte.ucCHxIADJ = 110u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SetCurrent_mA(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlTx.aCHxIADJH[TEST_ChipIdx1][TEST_Chip1].Byte.ucCHxIADJ = 0u;

  //Step 3) Call the FUT
  CddTps92520_SetCurrent_mA(TEST_ChnIllegal, 500u);  // illegal index, check coverage
  CddTps92520_SetCurrent_mA(TEST_Chn3, 500u);  // set to 500mA

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_DataMirror.CtrlTx.aCHxIADJH[TEST_ChipIdx1][TEST_Chip1].Byte.ucCHxIADJ, 110u, == );  // check according to target
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SetDutyCycle_1_32768
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check correct call of interface function to set PWM
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///      - DT-Info:
///         - Inputs:
///            boEftValid      : EFT data validity
///            ulChn           : LED channel index
///            unLedVolt       : LED voltage
///            unDuty1         : previous LED voltage
///            unDuty2         : LED voltage input sample 
///
///         - Expected test results: 
///            unActDuty : actual duty cycle calculated based on table inputs
///          - Use PWM duty if EFT data present
///          - Set PWM duty to 0 if EFT data is not present
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SetDutyCycle_1_32768(void)
{
  struct { boolean boEftValid; uint32 ulChn; uint16 unLedVolt; uint16 unDuty1; uint16 unDuty2; uint16 unActDuty; } asTestCaseData[]
     = { {      FALSE,         TEST_Chn0,         10000u,              0u,         16384u,             0u        },  // no operation
         {      TRUE,          TEST_ChnIllegal,   10000u,              0u,         16384u,             0u        },  // illegal call
         {      TRUE,          TEST_Chn0,          3000u,              0u,             0u,             0u        },
         {      TRUE,          TEST_Chn1,          3000u,              0u,           819u,           819u        },
         {      TRUE,          TEST_Chn2,          3000u,              0u,         16384u,         16384u        },
         {      TRUE,          TEST_Chn3,          3000u,          16384u,             0u,             0u        },
         {      TRUE,          TEST_Chn0,          3000u,          16384u,           819u,           819u        },  // check all combinations
         {      TRUE,          TEST_Chn1,          3000u,          16384u,         16384u,         16384u        },  // - 1 or 2 LEDs
         {      TRUE,          TEST_Chn2,          6000u,              0u,             0u,             0u        },  // - ON or OFF before
         {      TRUE,          TEST_Chn3,          6000u,              0u,           819u,           819u        },  // - new duty 0%, <5% or >5%
         {      TRUE,          TEST_Chn0,          6000u,              0u,         16384u,         16384u        },
         {      TRUE,          TEST_Chn1,          6000u,          16384u,             0u,             0u        },
         {      TRUE,          TEST_Chn2,          6000u,          16384u,           819u,           819u        },
         {      TRUE,          TEST_Chn3,          6000u,          16384u,         16384u,         16384u        } };

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Test_SetEftDataValid(asTestCaseData[ul].boEftValid);                                            // valid/invalid EFT data
    CddTps92520_aunLedVoltage  [asTestCaseData[ul].ulChn] = asTestCaseData[ul].unLedVolt;  // LED forward voltage
    CddTps92520_aunTgtDutyCycle[asTestCaseData[ul].ulChn] = asTestCaseData[ul].unDuty1;    // duty before call

    //Step 3) Call the FUT
    CddTps92520_SetDutyCycle_1_32768(asTestCaseData[ul].ulChn, asTestCaseData[ul].unDuty2);         // set new duty

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)Test_GetLedPwm(asTestCaseData[ul].ulChn), (int)asTestCaseData[ul].unActDuty);
    AL_UNITTEST_CHECK(Test_GetLedPwm(asTestCaseData[ul].ulChn),   asTestCaseData[ul].unActDuty, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetCurrent_mA
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check return value
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - function returns target value
///        - unRet = 1234u (current value)
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetCurrent_mA(void)
{
  uint16 unRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_aunTgtCurrent[TEST_Chn3] = 1234u;        // typical example

  //Step 3) Call the FUT
  (void)  CddTps92520_GetCurrent_mA(TEST_ChnIllegal);  // test using invalid index
  unRet = CddTps92520_GetCurrent_mA(TEST_Chn3);        // test using valid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, 1234u, == );                // compare with target
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetDutyCycle_1_32768
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check return value
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - function returns target value
///        - unRet = 12345u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetDutyCycle_1_32768(void)
{
  uint16 unRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_SetLedPwm(TEST_Chn3, 12345u);                          // typical example

  //Step 3) Call the FUT
  (void)  CddTps92520_GetDutyCycle_1_32768(TEST_ChnIllegal);  // test using invalid index
  unRet = CddTps92520_GetDutyCycle_1_32768(TEST_Chn3);        // test using valid index

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, 12345u, == );                      // compare with target
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetInputVoltage_mV
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - unRet = 1234u (input voltage)
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetInputVoltage_mV(void)
{
  uint16 unRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVIN = 37u;
  CddTps92520_aunInputVoltage[TEST_Chn2] = 1234u;    // typical example

  //Step 3) Call the FUT
  (void)  CddTps92520_GetInputVoltage_mV(TEST_ChnIllegal);  // test using invalid index
  unRet = CddTps92520_GetInputVoltage_mV(TEST_Chn2);        // channel 0, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, 1234u, == );                     // compare with target
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetLedVoltage_mV
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set LED Voltage value
///         Step2: Call FUT wiht invalid index
///         Step3: Call FUT for LED channel 1
///         Step4: Check return value of FUT and voltage value
///         Step5: Set LED Voltage value
///         Step6: Call FUT for LED channel 1
///         Step7: Check return value of FUT and voltage value
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Step 4) boRet = TRUE
///                  unVolt = 12345u
///        - Step 7) boRet = FALSE
///                  unVolt = 0xFFFFu
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetLedVoltage_mV(void)
{
  uint16  unVolt;
  boolean boRet;

  // Test case 1: Check valid voltage
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_aunLedVoltage[TEST_Chn1] = 12345u;   // typical example

  //Step 3) Call the FUT
  (void)  CddTps92520_GetLedVoltage_mV(TEST_ChnIllegal, &unVolt);  // test using invalid index
  boRet = CddTps92520_GetLedVoltage_mV(TEST_Chn1, &unVolt);        // channel 1, device 0

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet,    TRUE, == );                  // compare with target
  AL_UNITTEST_CHECK(unVolt, 12345u, == );                  // compare with target

  // Test case 2: check for invalid voltage
    //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_aunLedVoltage[TEST_Chn1] = 0xFFFFu;   // typical example

  //Step 3) Call the FUT
  boRet = CddTps92520_GetLedVoltage_mV(TEST_Chn1, &unVolt);        // channel 1, device 0

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );                  // compare with target
  AL_UNITTEST_CHECK(unVolt, 0xFFFFu, == );                // compare with target

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsOpenLoad
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return open load error depending on table
///        - note: 2 conditions can set open load:
///          a) CHxCOMPOV = 1
///          b) (unVin - uint16 unLedVolt) <= 2154mV 
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsOpenLoad(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint16 unVin;  uint16 unLedVolt; uint16 unCh1Compov; uint16 unCh2Compov; boolean boResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,    TEST_Chn0,       45000u,     45000u - 2155u,           0u,                 0u,              FALSE       },   // initial eror free
         {   0x8000u,     TEST_Chip0,    TEST_Chn0,       45000u,     45000u - 2155u,           1u,                 0u,              FALSE       },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,       45000u,     65535u,                   0u,                 0u,              FALSE       },   // PWM < 5%
         {   0x4000u,     TEST_Chip0,    TEST_ChnIllegal, 45000u,     45000u - 2155u,           0u,                 0u,              FALSE       },   // illegal call
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,       45000u,     45000u - 2154u,           0u,                 0u,              TRUE        },   // voltage below limit
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,       45000u,     45000u,                   0u,                 0u,              TRUE        },   // voltage below limit
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,       45000u,     45000u - 2155u,           1u,                 0u,              TRUE        },   // error on Ch1
         {   0x4000u,     TEST_Chip0,    TEST_Chn1,       45000u,     45000u - 2155u,           1u,                 0u,              FALSE       },   // no error on Ch2
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,       45000u,     45000u - 2155u,           0u,                 1u,              FALSE       },   // error on Ch1
         {   0x4000u,     TEST_Chip1,    TEST_Chn3,       45000u,     45000u - 2155u,           0u,                 1u,              TRUE        } }; // no error on Ch2

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    boolean boRet;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].unRaw           = asTestCaseData[ul].unSPE;       // SPI error
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH1COMPOV = asTestCaseData[ul].unCh1Compov; // error on Ch1
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH2COMPOV = asTestCaseData[ul].unCh2Compov; // error on Ch2
    CddTps92520_aunInputVoltage[asTestCaseData[ul].ulChn]                             = asTestCaseData[ul].unVin;       // input voltage
    CddTps92520_aunLedVoltage  [asTestCaseData[ul].ulChn]                             = asTestCaseData[ul].unLedVolt;   // LED forward voltage

    //Step 3) Call the FUT
    boRet = CddTps92520_IsOpenLoad(asTestCaseData[ul].ulChn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)boRet, (int)asTestCaseData[ul].boResult);
    AL_UNITTEST_CHECK(boRet, asTestCaseData[ul].boResult, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsShortToGnd
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return short to GND error depending on table
///        - note: 2 conditions are needed to set short to GND:
///          a) CHxSHORT = 1
///          b) unLedVolt < 1647mV
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsShortToGnd(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint16 unLedVolt; uint16 unCh1Short; uint16 unCh2Short; boolean boResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,    TEST_Chn0,         1646u,              0u,                0u,              FALSE       },   // initial eror free
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,        65535u,              1u,                0u,              FALSE       },   // no valid voltage
         {   0x8000u,     TEST_Chip0,    TEST_Chn0,         1646u,              1u,                1u,              FALSE       },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,    TEST_ChnIllegal,   1646u,              0u,                0u,              FALSE       },   // illegal call
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,         1647u,              1u,                0u,              FALSE       },   // voltage above limit
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,         1646u,              1u,                0u,              TRUE        },   // error on Ch1
         {   0x4000u,     TEST_Chip0,    TEST_Chn1,         1646u,              1u,                0u,              FALSE       },   // no error on Ch2
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,         1646u,              0u,                1u,              FALSE       },   // error on Ch1
         {   0x4000u,     TEST_Chip1,    TEST_Chn3,         1646u,              0u,                1u,              TRUE        } }; // no error on Ch2

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    boolean boRet;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization
    CddTps92520_aboShortToGndStatus[0] = FALSE;
    CddTps92520_aboShortToGndStatus[1] = FALSE;
    CddTps92520_aboShortToGndStatus[2] = FALSE;
    CddTps92520_aboShortToGndStatus[3] = FALSE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].unRaw          = asTestCaseData[ul].unSPE;      // SPI error
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH1SHORT = asTestCaseData[ul].unCh1Short; // error on Ch1
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH2SHORT = asTestCaseData[ul].unCh2Short; // error on Ch2
    CddTps92520_aunLedVoltage[asTestCaseData[ul].ulChn]                              = asTestCaseData[ul].unLedVolt;  // LED forward voltage

    //Step 3) Call the FUT
    boRet = CddTps92520_IsShortToGnd(asTestCaseData[ul].ulChn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)boRet, (int)asTestCaseData[ul].boResult);
    AL_UNITTEST_CHECK(boRet, asTestCaseData[ul].boResult, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsOvercurrent
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - boResult : status of detection of SPI error based on inputs given to the DT
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsOvercurrent(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint16 unCh1LsIlim; uint16 unCh1HsIlim; uint16 unCh2LsIlim; uint16 unCh2HsIlim; boolean boResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,    TEST_Chn0,            0u,                 0u,                 0u,                 0u,              FALSE       },   // initial eror free
         {   0x8000u,     TEST_Chip0,    TEST_Chn0,            1u,                 1u,                 1u,                 1u,              FALSE       },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,    TEST_ChnIllegal,      0u,                 0u,                 0u,                 0u,              FALSE       },   // illegal call
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,            0u,                 0u,                 0u,                 0u,              FALSE       },   // 
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,            1u,                 0u,                 0u,                 0u,              TRUE        },   // 
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,            0u,                 1u,                 0u,                 0u,              TRUE        },   // all possible combinations
         {   0x4000u,     TEST_Chip0,    TEST_Chn1,            0u,                 0u,                 0u,                 0u,              FALSE       },   // 
         {   0x4000u,     TEST_Chip0,    TEST_Chn1,            0u,                 0u,                 1u,                 0u,              TRUE        },   // 
         {   0x4000u,     TEST_Chip1,    TEST_Chn3,            0u,                 0u,                 0u,                 1u,              TRUE        } }; // 

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    boolean boRet;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].unRaw           = asTestCaseData[ul].unSPE;        // SPI error
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH1LSILIM = asTestCaseData[ul].unCh1LsIlim;  // error on Ch1 LSS
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH1HSILIM = asTestCaseData[ul].unCh1HsIlim;  // error on Ch1 HSS
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH2LSILIM = asTestCaseData[ul].unCh2LsIlim;  // error on Ch2 LSS
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH2HSILIM = asTestCaseData[ul].unCh2HsIlim;  // error on Ch2 HSS

    //Step 3) Call the FUT
    boRet = CddTps92520_IsOvercurrent(asTestCaseData[ul].ulChn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)boRet, (int)asTestCaseData[ul].boResult);
    AL_UNITTEST_CHECK(boRet, asTestCaseData[ul].boResult, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsThermalShutDown
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - boResult : status of detection of Thermal Shutdown error based on inputs given to the DT
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsThermalShutDown(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint16 unCh1Tp; uint16 unCh2Tp; boolean boResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,    TEST_Chn0,            0u,             0u,          FALSE       },   // initial eror free
         {   0x8000u,     TEST_Chip0,    TEST_Chn0,            1u,             1u,          FALSE       },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,    TEST_ChnIllegal,      0u,             0u,          FALSE       },   // illegal call
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,            0u,             0u,          FALSE       },   // no error
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,            1u,             0u,          TRUE        },   // error on Ch1
         {   0x4000u,     TEST_Chip0,    TEST_Chn1,            0u,             1u,          TRUE        },   // no error
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,            0u,             0u,          FALSE       },   // error on Ch1
         {   0x4000u,     TEST_Chip1,    TEST_Chn3,            1u,             0u,          FALSE       },   // error on Ch1
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,            0u,             1u,          FALSE       } }; // error on Ch2

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    boolean boRet;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aSTATUS2[asTestCaseData[ul].ulChip].unRaw       = asTestCaseData[ul].unSPE;   // SPI error
    CddTps92520_DataMirror.StatRx.aSTATUS2[asTestCaseData[ul].ulChip].Bit.biCH1TP = asTestCaseData[ul].unCh1Tp; // error on Ch1
    CddTps92520_DataMirror.StatRx.aSTATUS2[asTestCaseData[ul].ulChip].Bit.biCH2TP = asTestCaseData[ul].unCh2Tp; // error on Ch2

    //Step 3) Call the FUT
    boRet = CddTps92520_IsThermalShutDown(asTestCaseData[ul].ulChn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)boRet, (int)asTestCaseData[ul].boResult);
    AL_UNITTEST_CHECK(boRet, asTestCaseData[ul].boResult, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsDriverActive
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - boResult: return value represents COMPOV state
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsDriverActive(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint16 unCh1Compov; uint16 unVolt; uint16 unCh2Compov; boolean boResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,    TEST_Chn0,            0u,               12000u,          0u,              TRUE        },   // initial eror free
         {   0x8000u,     TEST_Chip0,    TEST_Chn0,            1u,               12000u,          0u,              TRUE        },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,            0u,               65535u,          0u,              TRUE        },   // PWM <5%
         {   0x4000u,     TEST_Chip0,    TEST_ChnIllegal,      0u,               12000u,          0u,              FALSE       },   // illegal call
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,            1u,               12000u,          0u,              FALSE       },   // error on Ch1
         {   0x4000u,     TEST_Chip0,    TEST_Chn1,            1u,               12000u,          0u,              TRUE        },   // no error on Ch2
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,            0u,               12000u,          1u,              TRUE        },   // no error on Ch1
         {   0x4000u,     TEST_Chip1,    TEST_Chn3,            0u,               12000u,          1u,              FALSE       } }; // error on Ch2

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    boolean boRet;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization
    CddTps92520_aboDriverActiveStatus[0] = TRUE;
    CddTps92520_aboDriverActiveStatus[1] = TRUE;
    CddTps92520_aboDriverActiveStatus[2] = TRUE;
    CddTps92520_aboDriverActiveStatus[3] = TRUE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].unRaw           = asTestCaseData[ul].unSPE;       // SPI error
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH1COMPOV = asTestCaseData[ul].unCh1Compov; // error on Ch1
    CddTps92520_DataMirror.StatRx.aSTATUS1[asTestCaseData[ul].ulChip].Bit.biCH2COMPOV = asTestCaseData[ul].unCh2Compov; // error on Ch2
    CddTps92520_aunLedVoltage[ul]                                                     = asTestCaseData[ul].unVolt;      // needed foe PWM <5% check

    //Step 3) Call the FUT
    boRet = CddTps92520_IsDriverActive(asTestCaseData[ul].ulChn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)boRet, (int)asTestCaseData[ul].boResult);
    AL_UNITTEST_CHECK(boRet, asTestCaseData[ul].boResult, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsThermalWarning
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - boResult : return value represents TW state in register STATUS3
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsThermalWarning(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint16 unTw; boolean boResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,   TEST_Chn0,           0u,           FALSE     },   // initial eror free
         {   0x8000u,     TEST_Chip0,   TEST_Chn0,           1u,           FALSE     },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,   TEST_ChnIllegal,     0u,           FALSE     },   // illegal call
         {   0x4000u,     TEST_Chip1,   TEST_Chn2,           1u,           TRUE      },   // error
         {   0x4000u,     TEST_Chip1,   TEST_Chn3,           0u,           FALSE     } }; // no error

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    boolean boRet;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aSTATUS3[asTestCaseData[ul].ulChip].unRaw    = asTestCaseData[ul].unSPE;  // SPI error
    CddTps92520_DataMirror.StatRx.aSTATUS3[asTestCaseData[ul].ulChip].Bit.biTW = asTestCaseData[ul].unTw;   // error on Ch1

    //Step 3) Call the FUT
    boRet = CddTps92520_IsThermalWarning(asTestCaseData[ul].ulChn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    //printf("\n%d  %d\n", (int)boRet, (int)asTestCaseData[ul].boResult);
    AL_UNITTEST_CHECK(boRet, asTestCaseData[ul].boResult, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_IsSpiError
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on CddTps92520_boSpiErrorLatch
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
/// \Steps:
///         Step1: Set SPI error on Chip idx 0
///         Step2: Call FUT
///         Step3: Check return value of FUT
///         Step4: Remove SPI error on Chip Idx 0
///         Step5: Call FUT
///         Step6: Check return value of FUT
///         Step7: Set SPI error on Chip Idx 0 and Ix 5
///         Step8: Call FUT with invalid index
///         Step9: Check return value of FUT
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return value represents SPI error latched 
///           Step3) boRet = TRUE
///           Step6) boRet = FALSE
///           Step9) boRet = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_IsSpiError(void)
{
    boolean boRet;
    extern boolean CddTps92520_boSpiErrorLatch[CDDTPS92520_Cfg_NbOfDevices];
    //Step 1) Set pre - conditions
    InitConditions();  // default initialization

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_boSpiErrorLatch[TEST_Chip0] = TRUE;  // SPI error

    //Step 3) Call the FUT
    boRet = CddTps92520_IsSpiError(TEST_Chn0);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRet, TRUE, == );

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_boSpiErrorLatch[TEST_Chip0] = FALSE;  // SPI error

    //Step 3) Call the FUT
    boRet = CddTps92520_IsSpiError(TEST_Chn1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRet, FALSE, == );

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_boSpiErrorLatch[TEST_Chip0] = TRUE;  // SPI error
    CddTps92520_boSpiErrorLatch[TEST_Chip5] = TRUE;  // SPI error

    //Step 3) Call the FUT
    boRet = CddTps92520_IsSpiError(TEST_ChnIllegal);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(boRet, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_RawToMillivolt
///
/// \Test Case Description
///    - Test subject: 
///        Check return value
///        Check coverage of all paths
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return value in mV according to raw input value
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_RawToMillivolt(void)
{
  uint32 ulRaw;
  uint16 unExpected;
  uint16 unRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  ulRaw = 123u * 4u;
  unExpected = (uint16)(((float)ulRaw * AD_Range * 1000.f) / 255.f /4.f);  // use floating point calculation for comparison

  //Step 3) Call the FUT
  unRet = CddTps92520_RawToMillivolt(ulRaw);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, unExpected, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_MeasureInputVoltage
///
/// \Test Case Description
///    - Test subject: 
///        Check return value
///        Check coverage of all paths
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return average value 65535 and clear samples
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_MeasureInputVoltage(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_ChipIdx1][TEST_Chip0].unRaw = CDDTPS92520_SpiRxExpected | 0x8000;  // SPI error
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVIN = 123u;
  CddTps92520_aunInputVoltage[1] = 0u;     // chip 0, channel 1
  CddTps92520_aunInputVoltage[2] = 7791u;  // chip 1, channel 0

  //Step 3) Call the FUT
  CddTps92520_MeasureInputVoltage();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_aunInputVoltage[1], 0u, == );  // SPI error, keep initial value
  AL_UNITTEST_CHECK(CddTps92520_aunInputVoltage[2], 0u, == );  // based on CHxVIN
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_MeasureLedVoltage
///
/// \Test Case Description
///    - Test subject: 
///        Check return value
///        Check coverage of all paths
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - check all relevant combinations of input signals
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_MeasureLedVoltage(void)
{
  struct { uint16 unSPE; uint32 ulChip; uint32 ulChn; uint8 ucVLed; uint8 ucVledOn; uint16 unDuty; uint16 unResult; } asTestCaseData[]
     = { {   0x4000u,     TEST_Chip0,    TEST_Chn0,        50u,            60u,         32768u,     0,   /*   3167u */    },   // initial eror free
         {   0x8000u,     TEST_Chip0,    TEST_Chn0,        70u,            80u,         32768u,     0,   /*   3167u */    },   // SPI error --> keep result
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,        90u,           100u,          1637u,                65535u     },   // duty <5%  --> unavailable
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,       110u,           120u,             0u,     0,   /*   6967u */    },   // duty 0    --> VLED
         {   0x4000u,     TEST_Chip1,    TEST_Chn2,       130u,           140u,          1638u,     0,   /*   8868u */    },   // duty ==5% --> VLED_ON
         {   0x4000u,     TEST_Chip1,    TEST_Chn3,       150u,           160u,         32735u,     0,   /*  10134u */    },   // duty >5%  --> VLED_ON
         {   0x4000u,     TEST_Chip0,    TEST_Chn0,       170u,           180u,         32736u,     0,   /*  10768u */    } }; // duty 100% --> VLED

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    uint16 unResultAverage;
    uint16 unResultExpected;

    //Step 1) Set pre - conditions
    InitConditions();  // default initialization
    CddTps92520_aunLedVoltage[asTestCaseData[ul].ulChn] = 0u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddTps92520_DataMirror.StatRx.aCHxVLED  [asTestCaseData[ul].ulChn % 2u][asTestCaseData[ul].ulChip].unRaw            = asTestCaseData[ul].unSPE;      // SPI error
    CddTps92520_DataMirror.StatRx.aCHxVLEDON[asTestCaseData[ul].ulChn % 2u][asTestCaseData[ul].ulChip].unRaw            = asTestCaseData[ul].unSPE;      // SPI error
    CddTps92520_DataMirror.StatRx.aCHxVLED  [asTestCaseData[ul].ulChn % 2u][asTestCaseData[ul].ulChip].Byte.ucCHxVLED   = asTestCaseData[ul].ucVLed;
    CddTps92520_DataMirror.StatRx.aCHxVLEDON[asTestCaseData[ul].ulChn % 2u][asTestCaseData[ul].ulChip].Byte.ucCHxVLEDON = asTestCaseData[ul].ucVledOn;
    CddTps92520_aunTgtDutyCycle[asTestCaseData[ul].ulChn]                                                               = asTestCaseData[ul].unDuty;

    //Step 3) Call the FUT
    CddTps92520_MeasureLedVoltage();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    unResultAverage  = CddTps92520_aunLedVoltage[asTestCaseData[ul].ulChn];
    unResultExpected = asTestCaseData[ul].unResult;

    //printf("\n%d  %d\n", (int)unResultAverage, (int)unResultExpected);
    AL_UNITTEST_CHECK(unResultAverage, unResultExpected, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_CalcCHxIADJ
///
/// \Test Case Description
///    - Test subject: 
///        Check return value
///        Check coverage of all paths
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - High byte of data mirror must be different from 0
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_CalcCHxIADJ(void)
{
  uint16 unRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  unRet = CddTps92520_CalcCHxIADJ(TEST_Chn0, 5000u);  // normal range because of limitiation by EFT data

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, 886u, == );  // based on target

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Eft_EcuVarCfg()[TEST_Chip0].aDrv[TEST_ChipIdx0].unImax = 6000u;  // allow high values

  //Step 3) Call the FUT
  unRet = CddTps92520_CalcCHxIADJ(TEST_Chn0, 5000u);  // overflow

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, 1023u, == );  // limitation

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Eft_Calib()[TEST_Chip0].aDrv[TEST_ChipIdx0].unIFactor  = 1000;    // typical factor
  Test_Eft_Calib()[TEST_Chip0].aDrv[TEST_ChipIdx0].nIOffset   = -100;    // negative offset for underflow

  //Step 3) Call the FUT
  unRet = CddTps92520_CalcCHxIADJ(TEST_Chn0, 0u);  // set to 0mA

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet, 0u, == );  // due to zero limitation
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetSTATUS1
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Call FUT with invalid parameters
///         Step2: Check return value of FUT
///         Step3: Set CH1LSILIM and CH2LSILIM 
///         Step4: Call FUT for channel 2
///         Step5: Check return value of STATUS1 register
///
///    - Expected test results: 
///        - Step2 ) coverage only
///        - Step5 ) STATUS1.Bit.biCH1LSILIM = 0u
///        -         STATUS2.Bit.biCH1LSILIM = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetSTATUS1(void)
{
  tCddTps92520_STATUS1 STATUS1;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddTps92520_GetSTATUS1(TEST_Chn2, NULL_PTR);  // error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Nothing to check: test is for code coverage only
  
  //Step 3) Call the FUT
  CddTps92520_GetSTATUS1(TEST_ChnIllegal, &STATUS1);  // index overflow

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Nothing to check: test is for code coverage only

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aSTATUS1[TEST_Chip1].Bit.biCH1LSILIM = 0u;  // example settings
  CddTps92520_DataMirror.StatRx.aSTATUS1[TEST_Chip1].Bit.biCH1HSILIM = 1u;  //

  //Step 3) Call the FUT
  CddTps92520_GetSTATUS1(TEST_Chn2, &STATUS1);  // channel 0, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(STATUS1.Bit.biCH1LSILIM, 0u, == );  // check for argument passing
  AL_UNITTEST_CHECK(STATUS1.Bit.biCH1HSILIM, 1u, == );  //
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetSTATUS2
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Call FUT with invalid parameters
///         Step2: Check return value of FUT
///         Step3: Set CH1T and CH2T 
///         Step4: Call FUT for channel 2
///         Step5: Check return value of STATUS2 register
///
///    - Expected test results: 
///        - Step2 ) coverage only
///        - Step5 ) STATUS2.Bit.biCH1T = 0u
///        -         STATUS2.Bit.biCH2T = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetSTATUS2(void)
{
  tCddTps92520_STATUS2 STATUS2;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddTps92520_GetSTATUS2(TEST_Chn2, NULL_PTR);  // error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Nothing to check: test is for code coverage only
  
  //Step 3) Call the FUT
  CddTps92520_GetSTATUS2(TEST_ChnIllegal, &STATUS2);  // index overflow

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Nothing to check: test is for code coverage only

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aSTATUS2[TEST_Chip1].Bit.biCH1TP = 0u;  // example settings
  CddTps92520_DataMirror.StatRx.aSTATUS2[TEST_Chip1].Bit.biCH2TP = 1u;  //

  //Step 3) Call the FUT
  CddTps92520_GetSTATUS2(TEST_Chn2, &STATUS2);  // channel 0, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(STATUS2.Bit.biCH1TP, 0u, == );  // check for argument passing
  AL_UNITTEST_CHECK(STATUS2.Bit.biCH2TP, 1u, == );  //
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetSTATUS3
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Call FUT with invalid parameters
///         Step2: Check return value of FUT
///         Step3: Set TW ad PC
///         Step4: Call FUT for channel 2
///         Step5: Check return value of STATUS3 register
///
///    - Expected test results: 
///        - Step2 ) coverage only
///        - Step5 ) STATUS3.Bit.biTW = 0u
///        -         STATUS3.Bit.biPC = 1u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetSTATUS3(void)
{
  tCddTps92520_STATUS3 STATUS3;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddTps92520_GetSTATUS3(TEST_Chn2, NULL_PTR);  // error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Nothing to check: test is for code coverage only
  
  //Step 3) Call the FUT
  CddTps92520_GetSTATUS3(TEST_ChnIllegal, &STATUS3);  // index overflow

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  // Nothing to check: test is for code coverage only

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aSTATUS3[TEST_Chip1].Bit.biTW = 0u;  // example settings
  CddTps92520_DataMirror.StatRx.aSTATUS3[TEST_Chip1].Bit.biPC = 1u;  //

  //Step 3) Call the FUT
  CddTps92520_GetSTATUS3(TEST_Chn2, &STATUS3);  // channel 0, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(STATUS3.Bit.biTW, 0u, == );  // check for argument passing
  AL_UNITTEST_CHECK(STATUS3.Bit.biPC, 1u, == );  //
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetCHxVIN
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - ucCHxVIN = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetCHxVIN(void)
{
  uint8 ucCHxVIN;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVIN = 63u;  // typical example

  //Step 3) Call the FUT
  ucCHxVIN = CddTps92520_GetCHxVIN(TEST_Chn2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ucCHxVIN, 0u, == );  // mod check for target value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetCHxVLED
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - ucCHxVLED = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetCHxVLED(void)
{
  uint8 ucCHxVLED;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVLED = 21u;  // typical example

  //Step 3) Call the FUT
  ucCHxVLED = CddTps92520_GetCHxVLED(TEST_Chn2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ucCHxVLED, 0u, == );  // mod check for target value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetCHxVLEDON
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - ucCHxVLEDON = 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetCHxVLEDON(void)
{
  uint8 ucCHxVLEDON;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxVLEDON = 23u;  // typical example

  //Step 3) Call the FUT
  ucCHxVLEDON = CddTps92520_GetCHxVLEDON(TEST_ChnIllegal);  // index too high
  ucCHxVLEDON = CddTps92520_GetCHxVLEDON(TEST_Chn2);        // valid call

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ucCHxVLEDON, 0u, == );  // mod check for target value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetCHxIADJL
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set SPI error
///         Step2: Check validity of CHxIADJL register
///         Step3: Remove SPI error
///         Step4: Call FUT with invalid channel index
///         Step5: Check validity of CHxIADJL register
///         Step6: Set CHxIADJL reg for Chip 1
///         Step7: Check validity of CHxIADJL register
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Check return value
///        - check if argument is passed correctly
///        - Step 2) boRet = FALSE
///        - Step 5) boRet = FALSE
///        - Step 7) boRet = FALSE
///                  ucCHxIADJL = 2u
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetCHxIADJL(void)
{
  uint8   ucCHxIADJL;
  boolean boRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlRx.aCHxIADJL[TEST_ChipIdx0][TEST_Chip1].unRaw = 0x8000u;  // SPI error

  //Step 3) Call the FUT
  boRet = CddTps92520_GetCHxIADJL(TEST_Chn2, NULL_PTR);  // error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );     // because of SPI error

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlRx.aCHxIADJL[TEST_ChipIdx0][TEST_Chip1].unRaw = 0u;  // no SPI error
  
  //Step 3) Call the FUT
  boRet = CddTps92520_GetCHxIADJL(TEST_ChnIllegal, &ucCHxIADJL);  // index overflow

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );     // mod because of SPI error

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlRx.aCHxIADJL[TEST_ChipIdx0][TEST_Chip1].Bit.bi2CHxIADJ = 2u;  // example setting

  //Step 3) Call the FUT
  boRet = CddTps92520_GetCHxIADJL(TEST_Chn2, &ucCHxIADJL);  // channel 0, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ucCHxIADJL, 2u,   == );  // check for correct argument passing
  AL_UNITTEST_CHECK(boRet,      FALSE, == );  // mod check for data valid info
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_GetCHxIADJH
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function returns correct value based on data mirror
///        Check all paths for code coverage
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
/// \Steps:
///         Step1: Set SPI error
///         Step2: Check validity of CHxIADJH register
///         Step3: Remove SPI error
///         Step4: Call FUT with invalid channel index
///         Step5: Check validity of CHxIADJH register
///         Step6: Set CHxIADJH reg for Chip 1
///         Step7: Check validity of CHxIADJH register
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Check return value
///        - check if argument is passed correctly
///        - Step 2) boRet = FALSE
///        - Step 5) boRet = FALSE
///        - Step 7) boRet = FALSE
///                  ucCHxIADJH = 123u
//-----------------------------------------------------------------------------
void Mt_CddTps92520_GetCHxIADJH(void)
{
  uint8   ucCHxIADJH;
  boolean boRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlRx.aCHxIADJH[TEST_ChipIdx0][TEST_Chip1].unRaw = 0x8000u;  // SPI error

  //Step 3) Call the FUT
  boRet = CddTps92520_GetCHxIADJH(TEST_Chn2, NULL_PTR);  // error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );     // because of SPI error

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlRx.aCHxIADJH[TEST_ChipIdx0][TEST_Chip1].unRaw = 0u;  // no SPI error
  
  //Step 3) Call the FUT
  boRet = CddTps92520_GetCHxIADJH(TEST_ChnIllegal, &ucCHxIADJH);  // index overflow

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );     // mod because of SPI error

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_DataMirror.CtrlRx.aCHxIADJH[TEST_ChipIdx0][TEST_Chip1].Byte.ucCHxIADJ = 123u;  // example setting

  //Step 3) Call the FUT
  boRet = CddTps92520_GetCHxIADJH(TEST_Chn2, &ucCHxIADJH);  // channel 0, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ucCHxIADJH, 123u, == );  // check for correct argument passing
  AL_UNITTEST_CHECK(boRet,      FALSE, == );  // mod check for data valid info
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_EnableChannel
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:  
///        Check if bit CHxEN is set correcty on data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///      - DT-Info:
///         - Inputs:
///            ulChip      : chip index
///            ulChn       : LED channel index
///            boEn        : availability of led channel
///
///         - Expected test results: 
///            - value in data mirror correct
///            unCh1En     : setting of CH1EN in SYSCFG1 reg
///            unCh2En     : setting of CH2EN in SYSCFG1 reg
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_EnableChannel(void)
{
  uint16 unCh1Result, unCh2Result;

  struct { uint32 ulChip; uint32 ulChn; boolean boEn; uint16 unCh1En; uint16 unCh2En; } asTestCaseData[]
     = { {  TEST_Chip0,    TEST_Chn0,       FALSE,           0u,             1u       },   // reset CH1EN, keep  CH2EN
         {  TEST_Chip0,    TEST_Chn1,       FALSE,           0u,             0u       },   // keep  CH1EN, reset CH2EN
         {  TEST_Chip0,    TEST_Chn0,       TRUE,            1u,             0u       },   // set   CH1EN, keep  CH2EN
         {  TEST_Chip0,    TEST_Chn1,       TRUE,            1u,             1u       } }; // keep  CH1EN, set   CH2EN

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization
  // set bits for incremental change step by step
  CddTps92520_DataMirror.CtrlTx.aSYSCFG1[TEST_Chip0].Bit.biCH1EN = 1u;
  CddTps92520_DataMirror.CtrlTx.aSYSCFG1[TEST_Chip0].Bit.biCH2EN = 1u;

  for (uint32 ul = 0; ul < _countof(asTestCaseData); ul++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    // nothing to assign: each step is based on the last one

    //Step 3) Call the FUT
    CddTps92520_EnableChannel(asTestCaseData[ul].ulChn, asTestCaseData[ul].boEn);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    unCh1Result = CddTps92520_DataMirror.CtrlTx.aSYSCFG1[asTestCaseData[ul].ulChip].Bit.biCH1EN;
    unCh2Result = CddTps92520_DataMirror.CtrlTx.aSYSCFG1[asTestCaseData[ul].ulChip].Bit.biCH2EN;
    //printf("\n%d  %d  %d  %d\n", (int)unCh1Result, (int)unCh2Result, (int)asTestCaseData[ul].unCh1En, (int)asTestCaseData[ul].unCh2En);
    AL_UNITTEST_CHECK(unCh1Result, asTestCaseData[ul].unCh1En, == );
    AL_UNITTEST_CHECK(unCh2Result, asTestCaseData[ul].unCh2En, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SetCHxIADJL
///
/// \Test Case Description
///    - Test subject: 
///        Check if function writes correct value to data mirror
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - 
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SetCHxIADJL(void)
{
  tCddTps92520_CHxIADJL CHxIADJL;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CHxIADJL.Bit.bi2CHxIADJ = 2u;  // typical example

  //Step 3) Call the FUT
  CddTps92520_SetCHxIADJL(TEST_Chn3, CHxIADJL);  // channel 1, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_DataMirror.CtrlTx.aCHxIADJL[TEST_ChipIdx1][TEST_Chip1].Bit.bi2CHxIADJ, 2u, == );  // check for target value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SetCHxIADJH
///
/// \Test Case Description
///    - Test subject: 
///        Check if function writes correct value to data mirror
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - 
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SetCHxIADJH(void)
{
  uint8 ucCHxIDJH;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  ucCHxIDJH = 59u;  // typical example

  //Step 3) Call the FUT
  CddTps92520_SetCHxIADJH(TEST_Chn3, ucCHxIDJH);  // channel 1, device 1

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_DataMirror.CtrlTx.aCHxIADJH[TEST_ChipIdx1][TEST_Chip1].Byte.ucCHxIADJ, 59u, == );  // check for target value
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SpiTx
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check for correct transmit value to SPI
///        Check coverage of all paths
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Call FUT for Chip 1
///         Step2: Check return value of SPI data Tx buffer
///         Step3: Call FUT for Chip 0
///         Step4: Check return value of SPI data Tx buffer
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Check return value
///        - check if argument is passed correctly
///        - Step 2) ulRet = 56515u
///        - Step 4) ulRet = 56515u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SpiTx(void)
{
  uint32 ulRet;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  ulRet = CddTps92520_SpiTx(TEST_Chip1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ulRet, 56515u, == );  // value based on default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  ulRet = CddTps92520_SpiTx(TEST_Chip0);  // last instance

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(ulRet, 56515u, == );  // value based on default initialization
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SpiRx
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function writes correct value to data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Call FUT for Chip 1
///         Step2: Check scheduler index value for Rx data
///         Step3: Call FUT for Chip 0
///         Step4: Check scheduler index value for Rx data
///         Step5: Set SPI error for Chip 0
///         Step6: Call FUT for Chip 0
///         Step7: Check scheduler index value for Rx data
///         Step8: Set SPI error for Chip 0
///         Step9: Call FUT for Chip 0
///         Step10: Check scheduler index value for Rx data
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Check return value
///        - check if argument is passed correctly
///        - Step 2) CddTps92520_unSchedIx = 0u
///        - Step 4) CddTps92520_unSchedIx = 3u
///        - Step 7) CddTps92520_unSchedIx = 4u
///        - Step 10) CddTps92520_unSchedIx = 22u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SpiRx(void)
{
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddTps92520_SpiRx(TEST_Chip1, 0xAA | 0x4000U);  // default call

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_unSchedIx, 0u, == );

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_unSchedIx = 2u;  // set start index

  //Step 3) Call the FUT
  CddTps92520_SpiRx(TEST_Chip0, 0x55 | 0x4000U);  // normal call

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_unSchedIx, 3u, == );  // check incrementation of index

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  CddTps92520_SpiRx(TEST_Chip0, 0x55 | 0x8000u);  // normal call with SPI error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_unSchedIx, 4u, == );  // check incrementation of index

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_unSchedIx = 21u;  // set start index

    //Step 3) Call the FUT
  CddTps92520_SpiRx(TEST_Chip0, 0x55 | 0x4000u);  // normal call with SPI error

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddTps92520_unSchedIx, 22u, == );  // check incrementation of index
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddTps92520_SpiGetConfig
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check if function writes correct value to data mirror
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
/// \Steps:
///         Step1: Set EFT valid data
///         Step2: Call FUT for EFT valid data
///         Step3: Check return value of SPI configuration
///         Step4: Set EFT invalid data
///         Step5: Call FUT for EFT invalid data
///         Step6: Check return value of SPI configuration
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Check return value
///        - check if argument is passed correctly
///        - Step 3) unMask - 0x3Eu
///        - Step 6) unMask - 0u
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_SpiGetConfig(void)
{
  uint16 unMask;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_Eft_EcuVarCfg()[TEST_Chip0].ucDrvType = 0;  //
  Test_Eft_EcuVarCfg()[TEST_Chip1].ucDrvType = 1;  //
  Test_Eft_EcuVarCfg()[TEST_Chip2].ucDrvType = 1;  // typical list of drivers
  Test_Eft_EcuVarCfg()[TEST_Chip3].ucDrvType = 1;  //
  Test_Eft_EcuVarCfg()[TEST_Chip4].ucDrvType = 1;  //
  Test_Eft_EcuVarCfg()[TEST_Chip5].ucDrvType = 1;  //
  Test_SetEftDataValid(TRUE);

  //Step 3) Call the FUT
  CddTps92520_SpiGetConfig(&unMask);

  //Step 4) Check return value of the FUT 
  AL_UNITTEST_CHECK(unMask, 0x3Eu, == );  // according to above list

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Test_SetEftDataValid(FALSE);   // invalid EFT data

  //Step 3) Call the FUT
  CddTps92520_SpiGetConfig(&unMask);

  //Step 4) Check return value of the FUT 
  AL_UNITTEST_CHECK(unMask, 0u, == );  // no active drivers
}


//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTps92520_CalcAndAddParity
///
/// \Test Case Description
///    - Test subject: 
///        Check if function writes correct value to data mirror
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - 
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_CalcAndAddParity(void)
{
  uint16 unRet1, unRet2;

  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  unRet1 = CddTps92520_CalcAndAddParity(0x80, 0x5A, 0x55); // create even and odd parity
  unRet2 = CddTps92520_CalcAndAddParity(0x00, 0x5A, 0x55); // (clear bit 7)

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(unRet1, 0x0DFu, == );  // original
  AL_UNITTEST_CHECK(unRet2, 0x15Fu, == );  // bit 7 is cleared and parity bit is set
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_CddTps92520_StAction
///
/// \Test Case Description
///    - Test subject: 
///        Check if function read correct value from data mirror based on requested action
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - 
///
//-----------------------------------------------------------------------------
void Mt_CddTps92520_StAction(void)
{
  boolean boRet = FALSE;
  extern uint8   CddTps92520_aucCHxVIN[CDDTPS92520_AdcSamples][CDDTPS92520_CFG_NO_OF_CHANNELS];
  extern uint8   CddTps92520_aucCHxVLED[CDDTPS92520_AdcSamples][CDDTPS92520_CFG_NO_OF_CHANNELS];  // for averaging VLED values
  extern uint8   CddTps92520_aucCHxVLEDON[CDDTPS92520_AdcSamples][CDDTPS92520_CFG_NO_OF_CHANNELS];  // for averaging VLEDON values
  extern uint16  CddTps92520_unAvrgVinIdx;
  extern uint16  CddTps92520_unAvrgVledIdx;
  extern uint16  CddTps92520_unAvrgVledOnIdx;
  // Test case 1: CDDTPS92520_ST_GETVIN
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_unAvrgVinIdx = 3u;
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_Chn0][TEST_Chip0].unRaw = 0x4010u;
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_Chn1][TEST_Chip0].unRaw = 0x4020u;
  //Step 3) Call the FUT
  boRet = CddTps92520_StAction(1u); // create even CDDTPS92520_ST_GETVIN
  boRet = CddTps92520_StAction(1u);
  boRet = CddTps92520_StAction(1u);
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_Chn0][TEST_Chip0].unRaw = 0x8020u; // SPI Error, ignore
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_Chn1][TEST_Chip0].unRaw = 0x8010u; // SPI Error, ignore
  boRet = CddTps92520_StAction(1u);
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_Chn0][TEST_Chip0].unRaw = 0x4004u; // ADC sample index reset
  CddTps92520_DataMirror.StatRx.aCHxVIN[TEST_Chn1][TEST_Chip0].unRaw = 0x8004u;
  boRet = CddTps92520_StAction(1u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );  // original
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVIN[0][TEST_Chip0],  4U, == );  // avg value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVIN[1][TEST_Chip0], 24U, == );  // avg value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVIN[2][TEST_Chip0], 24U, == );  // avg value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVIN[3][TEST_Chip0],  0U, == );  // ignored due to spi error

  // Test case 2: CDDTPS92520_ST_GETVLED
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_unAvrgVledIdx = 3u;
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_Chn0][TEST_Chip0].unRaw = 0x4010u;
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_Chn1][TEST_Chip0].unRaw = 0x4020u;
  //Step 3) Call the FUT
  boRet = CddTps92520_StAction(2u); // create even CDDTPS92520_ST_GETVLED
  boRet = CddTps92520_StAction(2u);
  boRet = CddTps92520_StAction(2u);
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_Chn0][TEST_Chip0].unRaw = 0x8020u; // SPI Error, ignore
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_Chn1][TEST_Chip0].unRaw = 0x8010u; // SPI Error, ignore
  boRet = CddTps92520_StAction(2u);
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_Chn0][TEST_Chip0].unRaw = 0x4004u; // ADC sample index reset
  CddTps92520_DataMirror.StatRx.aCHxVLED[TEST_Chn1][TEST_Chip0].unRaw = 0x8004u;
  boRet = CddTps92520_StAction(2u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );  // original
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLED[0][TEST_Chn0],  4U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLED[0][TEST_Chn1],  4U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLED[1][TEST_Chn0], 16U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLED[1][TEST_Chn1], 32U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLED[2][TEST_Chn1], 32U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLED[3][TEST_Chn0],  0U, == );  // ignored

    // Test case 3: CDDTPS92520_ST_GETVLEDON
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddTps92520_unAvrgVledOnIdx = 3u;
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_Chn0][TEST_Chip0].unRaw = 0x4010u;
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_Chn1][TEST_Chip0].unRaw = 0x4020u;
  //Step 3) Call the FUT
  boRet = CddTps92520_StAction(3u); // create even CDDTPS92520_ST_GETVLEDON
  boRet = CddTps92520_StAction(3u);
  boRet = CddTps92520_StAction(3u);
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_Chn0][TEST_Chip0].unRaw = 0x8020u; // SPI Error, ignore
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_Chn1][TEST_Chip0].unRaw = 0x8010u; // SPI Error, ignore
  boRet = CddTps92520_StAction(3u);
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_Chn0][TEST_Chip0].unRaw = 0x4004u; // ADC sample index reset
  CddTps92520_DataMirror.StatRx.aCHxVLEDON[TEST_Chn1][TEST_Chip0].unRaw = 0x8004u;
  boRet = CddTps92520_StAction(3u);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );  // original
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLEDON[0][TEST_Chn0], 4U,  == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLEDON[0][TEST_Chn1], 4U,  == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLEDON[1][TEST_Chn0], 16U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLEDON[1][TEST_Chn1], 32U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLEDON[2][TEST_Chn1], 32U, == );  // sampled value
  AL_UNITTEST_CHECK(CddTps92520_aucCHxVLEDON[3][TEST_Chn0], 0U,  == );  // ignored

    // Test case 4: Unknown Action
  //Step 1) Set pre - conditions
  InitConditions();  // default initialization

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  boRet = CddTps92520_StAction(0u); // create even for Unknown action

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(boRet, FALSE, == );  // original

}

void ALUnitTest_AddTests(void)
{
  // public functions of CddTps92520.c
  ALUnitTest_AddFunction("Mt_CddTps92520_Init"                , Mt_CddTps92520_Init);
  ALUnitTest_AddFunction("Mt_CddTps92520_Cycle20ms"           , Mt_CddTps92520_Cycle20ms);
  ALUnitTest_AddFunction("Mt_CddTps92520_SetCurrent_mA"       , Mt_CddTps92520_SetCurrent_mA);
  ALUnitTest_AddFunction("Mt_CddTps92520_SetDutyCycle_1_32768", Mt_CddTps92520_SetDutyCycle_1_32768);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetCurrent_mA"       , Mt_CddTps92520_GetCurrent_mA);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetDutyCycle_1_32768", Mt_CddTps92520_GetDutyCycle_1_32768);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetInputVoltage_mV"  , Mt_CddTps92520_GetInputVoltage_mV);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetLedVoltage_mV"    , Mt_CddTps92520_GetLedVoltage_mV);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsOpenLoad"          , Mt_CddTps92520_IsOpenLoad);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsShortToGnd"        , Mt_CddTps92520_IsShortToGnd);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsOvercurrent"       , Mt_CddTps92520_IsOvercurrent);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsThermalShutDown"   , Mt_CddTps92520_IsThermalShutDown);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsDriverActive"      , Mt_CddTps92520_IsDriverActive);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsThermalWarning"    , Mt_CddTps92520_IsThermalWarning);
  ALUnitTest_AddFunction("Mt_CddTps92520_IsSpiError"          , Mt_CddTps92520_IsSpiError);
  

// static functions of CddTps92520.c
  ALUnitTest_AddFunction("Mt_CddTps92520_RawToMillivolt"      , Mt_CddTps92520_RawToMillivolt      );
  ALUnitTest_AddFunction("Mt_CddTps92520_MeasureInputVoltage" , Mt_CddTps92520_MeasureInputVoltage );
  ALUnitTest_AddFunction("Mt_CddTps92520_MeasureLedVoltage"   , Mt_CddTps92520_MeasureLedVoltage   );
  ALUnitTest_AddFunction("Mt_CddTps92520_CalcCHxIADJ"         , Mt_CddTps92520_CalcCHxIADJ);

  // public functions of CddTps92520_Com.c
  ALUnitTest_AddFunction("Mt_CddTps92520_GetSTATUS1"          , Mt_CddTps92520_GetSTATUS1);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetSTATUS2"          , Mt_CddTps92520_GetSTATUS2);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetSTATUS3"          , Mt_CddTps92520_GetSTATUS3);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetCHxVIN"           , Mt_CddTps92520_GetCHxVIN);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetCHxVLED"          , Mt_CddTps92520_GetCHxVLED);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetCHxVLEDON"        , Mt_CddTps92520_GetCHxVLEDON);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetCHxIADJL"         , Mt_CddTps92520_GetCHxIADJL);
  ALUnitTest_AddFunction("Mt_CddTps92520_GetCHxIADJH"         , Mt_CddTps92520_GetCHxIADJH);
  ALUnitTest_AddFunction("Mt_CddTps92520_EnableChannel"       , Mt_CddTps92520_EnableChannel);
  ALUnitTest_AddFunction("Mt_CddTps92520_SetCHxIADJL"         , Mt_CddTps92520_SetCHxIADJL);
  ALUnitTest_AddFunction("Mt_CddTps92520_SetCHxIADJH"         , Mt_CddTps92520_SetCHxIADJH);
  ALUnitTest_AddFunction("Mt_CddTps92520_SpiTx"               , Mt_CddTps92520_SpiTx);
  ALUnitTest_AddFunction("Mt_CddTps92520_SpiRx"               , Mt_CddTps92520_SpiRx);
  ALUnitTest_AddFunction("Mt_CddTps92520_SpiGetConfig"        , Mt_CddTps92520_SpiGetConfig);

  // static functions of CddTps92520_Com.c
  ALUnitTest_AddFunction("Mt_CddTps92520_CalcAndAddParity"    , Mt_CddTps92520_CalcAndAddParity);
  ALUnitTest_AddFunction("Mt_CddTps92520_StAction"            , Mt_CddTps92520_StAction);
}

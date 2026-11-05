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
/// \file  Test_Adapter.c
///
/// \brief Additional test cases for adapter
///         These tests must be customized according to the adapter implementation
///
//-----------------------------------------------------------------------------

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include <Test_Ext.h>
#include "Test_Stubs.h"

// Headers of the unit test Module
#include <Test_Adapter.h>

//=============================================================================
// Global variable stubs
//=============================================================================
tNvmPara_CodingArea     Coding_Dummy = { 0u };
tParaFct0_Cmd           Coding_State = eParaFct0_CodingDataInvalid;

//=============================================================================
// test Cases
//=============================================================================
//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddLedInit_TestCase1
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check the initialization state of the LED driver for
///        invalid coding parameters
///
///    - Test Design Technique:  - Requirement based test
///                              - Fault injection
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - no voltage on the LED channel 
///          CddLed_sStatus.aStatus[0].unVLed = 0u
///
//-----------------------------------------------------------------------------
void Mt_riCddLedInit_TestCase1(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  riCddLedInit();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_Init(), 0x0FFF, == );
  AL_UNITTEST_CHECK(CddLed_sStatus.aStatus[0].unVLed, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddLedInit_TestCase2
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check the initialization state for each LED channel
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - reset internal error for each Led driver
///        - set input voltage : Test_Drv_GetInputVoltage_mV(led ch.) = 45000u
///
//-----------------------------------------------------------------------------
void Mt_riCddLedInit_TestCase2(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  //Step 3) Call the FUT
  riCddLedInit(); 
  
  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_Init(),                      0x0FFF, == );


  for (uint8 ucIdx = 0u; ucIdx < CDDLED_Cfg_NbOfChannels; ucIdx++)
  {
    uint16 unVoltage = 0U;
    Test_Drv_GetLedVoltage_mV(ucIdx, &unVoltage);
    AL_UNITTEST_CHECK(Test_Drv_IsDriverActive(ucIdx),       FALSE, ==);
    AL_UNITTEST_CHECK(Test_Drv_IsShortToGnd(ucIdx),         FALSE, ==);
    AL_UNITTEST_CHECK(Test_Drv_IsOpenLoad(ucIdx),           FALSE, ==);

    AL_UNITTEST_CHECK(Test_Drv_IsThermalWarning(ucIdx),     FALSE, ==);
    AL_UNITTEST_CHECK(Test_Drv_IsThermalShutDown(ucIdx),    FALSE, ==);
    AL_UNITTEST_CHECK(Test_Drv_IsOvercurrent(ucIdx),        FALSE, ==);

    AL_UNITTEST_CHECK(unVoltage,        0u, ==);
    AL_UNITTEST_CHECK(Test_Drv_GetInputVoltage_mV(ucIdx),  45000u, ==);
  }

  AL_UNITTEST_CHECK(Test_Drv_GetLedVoltOnOff_mV(0u),       1000u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetLedVoltOnOff_mV(1u),        500u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetLedVoltOnOff_mV(2u),       2000u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetLedVoltOnOff_mV(3u),       3000u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetLedVoltOnOff_mV(4u),       1000u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddLedInit
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:  Test the cyclic behaviour of Led driver
///
///    - Test Design Technique:  - Requirement based test
///
///    - Expected test results:  Test cases Mt_riCddLedInit_TestCase1, 
///                               Mt_riCddLedInit_TestCase2 are passed
///
//-----------------------------------------------------------------------------
void Mt_riCddLedInit(void)
{
  Mt_riCddLedInit_TestCase1();
  Mt_riCddLedInit_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddLedNewTarget_TestCase1
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check correct setting of current
///        Check usage of correct data source -> correct CRC calculated over RTE port and 
///        received data
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - current/duty cycle are updated and the fault state is returned FALSE
///
//-----------------------------------------------------------------------------
void Mt_reCddLedNewTarget_TestCase1(void)
{
  //Step 1) Set pre - conditions

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent     = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle   = 23456u;

  Crc_CalculateCRC8H2F_RetVal                 = 0x67;     //CRC calculated over Current
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x67;
  reCddLedNewTarget_RetVal = TRUE;

  //Step 3) Call the FUT
  reCddLedNewTarget_RetVal = reCddLedNewTarget();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),    1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u), 23456u, == );  
  AL_UNITTEST_CHECK(reCddLedNewTarget_RetVal,   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddLedNewTarget_TestCase2
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check correct setting of current
///        Check usage of incorrect data source -> incorrect CRC calculated over RTE port and 
///        received data
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - current/duty cycle are updated and the fault state is returned FALSE because
///          debounce was not reached, but CRC failure is set TRUE
///
//-----------------------------------------------------------------------------
void Mt_reCddLedNewTarget_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent   = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle = 23456u;

  Crc_CalculateCRC8H2F_RetVal                 = 0x67;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x85; //wrong CRC calculated and sent via RTE
  reCddLedNewTarget_RetVal     = TRUE;
  LPTMR0_GetTimeElapsed_RetVal = 0u; //timer started

  //Step 3) Call the FUT
  reCddLedNewTarget_RetVal = reCddLedNewTarget();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),     1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u),  23456u, == );
  AL_UNITTEST_CHECK(reCddLedNewTarget_RetVal,    FALSE, == );
  AL_UNITTEST_CHECK(boCrcFailure,                 TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddLedNewTarget_TestCase3
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check correct setting of current
///        Check usage of incorrect data source -> incorrect CRC calculated over RTE port and 
///        received data
///        in case the debounce for CRC invalid is reached and TI is requested, force current
///        and duty to be 0
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - current/duty cycle are set to 0 and the fault state is returned TRUE because
///          debounce was  reached and Ti was requested
///
//-----------------------------------------------------------------------------
void Mt_reCddLedNewTarget_TestCase3(void)
{
  //Step 1) Set pre - conditions
  LPTMR0_GetTimeElapsed_RetVal                = UTILTIME_MSEC(350); //timer started and timeout
  SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal = TRUE;  //request TI function
  reCddLedNewTarget_RetVal                    = FALSE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent   = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle = 23456u;

  Crc_CalculateCRC8H2F_RetVal                 = 0x67;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x85; //wrong CRC calculated and sent via RTE

  //Step 3) Call the FUT
  reCddLedNewTarget_RetVal = reCddLedNewTarget();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),        0u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u),      0u, == );
  AL_UNITTEST_CHECK(reCddLedNewTarget_RetVal,     TRUE, == );
  AL_UNITTEST_CHECK(boCrcFailure,                 TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddLedNewTarget_TestCase4
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check correct setting of current
///        Check usage of incorrect data source -> incorrect CRC calculated over RTE port and 
///        received data
///        in case the debounce for CRC invalid is not reached and TI is requested, wait 
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - current/duty cycle are updated and the fault state is returned FALSE because
///          debounce was not reached and requirement says to keep LIGHT on for 320ms
///          even in case of CRC error
///
//-----------------------------------------------------------------------------
void Mt_reCddLedNewTarget_TestCase4(void)
{
  //Step 1) Set pre - conditions
  LPTMR0_GetTimeElapsed_RetVal                = UTILTIME_MSEC(150); //timer started but debounce value not reached
  SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal = TRUE;  //request TI function
  reCddLedNewTarget_RetVal                    = FALSE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent   = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle = 23456u;

  Crc_CalculateCRC8H2F_RetVal                 = 0x67;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x85; //wrong CRC calculated and sent via RTE

  //Step 3) Call the FUT
  reCddLedNewTarget_RetVal = reCddLedNewTarget();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),     1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u),  23456u, == );
  AL_UNITTEST_CHECK(reCddLedNewTarget_RetVal,    FALSE, == );
  AL_UNITTEST_CHECK(boCrcFailure,                 TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddLedNewTarget_TestCase5
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check correct setting of current
///        Check usage of incorrect data source -> incorrect CRC calculated over RTE port and 
///        received data
///        in case the debounce for CRC invalid is reached and TI is not requested, let the
///        received current and duty cycle
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - current/duty cycle are not changed because the channel is not a TI FuSa
///          and the fault state is returned TRUE because debounce was  reached
///
//-----------------------------------------------------------------------------
void Mt_reCddLedNewTarget_TestCase5(void)
{
  //Step 1) Set pre - conditions
  LPTMR0_GetTimeElapsed_RetVal                = UTILTIME_MSEC(350); //timer started, and timeout
  SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal = FALSE;  //no request of TI FuSa function
  reCddLedNewTarget_RetVal                    = FALSE;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent   = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle = 23456u;

  Crc_CalculateCRC8H2F_RetVal                 = 0x67;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x85; //wrong CRC calculated and sent via RTE

  //Step 3) Call the FUT
  reCddLedNewTarget_RetVal = reCddLedNewTarget();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),      1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u),   23456u, == );
  AL_UNITTEST_CHECK(reCddLedNewTarget_RetVal,      TRUE, == );
  AL_UNITTEST_CHECK(boCrcFailure,                  TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_reCddLedNewTarget
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:  Test the setting of new target values for LED channel
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Expected test results: Test Cases:
///           Mt_reCddLedNewTarget_TestCase1,
///           Mt_reCddLedNewTarget_TestCase2,
///           Mt_reCddLedNewTarget_TestCase3,
///           Mt_reCddLedNewTarget_TestCase4,
///           Mt_reCddLedNewTarget_TestCase5 are passed
///
//-----------------------------------------------------------------------------
void Mt_reCddLedNewTarget(void)
{
  Mt_reCddLedNewTarget_TestCase1();
  Mt_reCddLedNewTarget_TestCase2();
  Mt_reCddLedNewTarget_TestCase3();
  Mt_reCddLedNewTarget_TestCase4();
  Mt_reCddLedNewTarget_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddLed_Cycle_TestCase1
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check for Invalid Coding Data that driver is not reading
///        coding parameters and does not execute the cyclic routine.
///        General: in case the coding is invalid, the system shall be
///        running with no issue, but not functional (meaning no light
///        shall be controlled)
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - Rte_Read_CtrlLed_LedSettings_sVal_HitCount = 0u
///        - Rte_Write_CddLed_LedState_HitCount         = 0u
///
//-----------------------------------------------------------------------------
void Mt_rpCddLed_Cycle_TestCase1(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_CddLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlLed_LedSettings_sVal_HitCount = 0u;
  Rte_Write_CddLed_LedState_HitCount         = 0u;

  //Step 3) Call the FUT
  rpCddLed_Cycle();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_LedSettings_sVal_HitCount, 0u, ==);
  AL_UNITTEST_CHECK(Rte_Write_CddLed_LedState_HitCount,         0u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddLed_Cycle_TestCase2
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check that for coding valid, the driver reads the settings
///        for the led channels via RTE
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: coding data valid
///
///    - Expected test results: 
///        - updated LED voltage and current parameters
///        - Test_Drv_GetCurrent(0u)   = 1234u
///        - Test_Drv_GetDutyCycle(0u) = 23456u
///
//-----------------------------------------------------------------------------
void Mt_rpCddLed_Cycle_TestCase2(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlLed_LedSettings_sVal_HitCount = 0u;
  Rte_Write_CddLed_LedState_HitCount         = 0u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent   = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle = 23456u;
  Crc_CalculateCRC8H2F_RetVal                 = 0x67;     //CRC calculated over Current
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x67;


  //Step 3) Call the FUT
  rpCddLed_Cycle();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_LedSettings_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CddLed_LedState_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),                 1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u),              23456u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddLed_Cycle_TestCase3
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Test that the driver checks if in the driver initialization,
///        coding has been available and parameters were calculated correctly.
///        If not, Input Voltage Threshold parameter is not computed and will
///        generate pseudo-errors. The cyclic routine needs to calculate
///        the Input Voltage Threshold.
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing)
///
///    - Preconditions: coding data valid and driver not succesfully initialized:
///           CddLed_ParaInit = FALSE
///
///    - Expected test results: 
///        - calculated Input Threshold Voltage and updated LED voltage and current parameters
///        - Test_Drv_GetCurrent(0u)   = 1234u
///        - Test_Drv_GetDutyCycle(0u) = 23456u
///
//-----------------------------------------------------------------------------
void Mt_rpCddLed_Cycle_TestCase3(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlLed_LedSettings_sVal_HitCount  = 0u;
  Rte_Write_CddLed_LedState_HitCount          = 0u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unCurrent = 1234u;
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.asTgtVal->unDutyCycle = 23456u;
  Crc_CalculateCRC8H2F_RetVal = 0x67;     //CRC calculated over Current
  Rte_Read_SysMon_TgtLedSig_sVal_Param1.ucCrc = 0x67;
  CddLed_ParaInit = FALSE;

  //Step 3) Call the FUT
  rpCddLed_Cycle();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_ParaInit, TRUE,  == );
  AL_UNITTEST_CHECK(Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_Param1.boCrc8ErrorStatus, FALSE, == );
  AL_UNITTEST_CHECK(Test_Drv_GetCurrent(0u),    1234u, == );
  AL_UNITTEST_CHECK(Test_Drv_GetDutyCycle(0u), 23456u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCddLed_Cycle
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject:  Test the cyclic behaviour of Led driver
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
///    - Expected test results: Test Cases contained are  passed
///
//-----------------------------------------------------------------------------
void Mt_rpCddLed_Cycle(void)
{
  Mt_rpCddLed_Cycle_TestCase1();
  Mt_rpCddLed_Cycle_TestCase2();
  Mt_rpCddLed_Cycle_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_Get_CodingPara
///
/// \Test Case Description
///    - Test subject: 
///        Check the reading of coding parameters via RTE
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - save the coding data
///
//-----------------------------------------------------------------------------
void Mt_CddLed_Get_CodingPara(void)
{
  //Step 1) Set pre - conditions
  Rte_Read_CodM_CddLed_Para_HitCount = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 3) Call the FUT
  CddLed_Get_CodingPara(&CddLed_Get_CodingPara_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(CddLed_Get_CodingPara_Param1.eCodingState, eParaFct0_CodingDataValid, ==);
  AL_UNITTEST_CHECK(Rte_Read_CodM_CddLed_Para_HitCount, 1u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_CodingDataValidation
///
/// \Test Case Description
///    - Test subject: 
///        Handle coding Data Validation
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - coding data validity
///
//-----------------------------------------------------------------------------
void Mt_CddLed_CodingDataValidation(void)
{
  //Step 1) Set pre - conditions
  CddLed_CodingDataValidation_RetVal = FALSE;
  Rte_Read_CodM_CddLed_Para_HitCount = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CodM_CddLed_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
  Rte_Read_CodM_CddLed_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 3) Call the FUT
  CddLed_CodingDataValidation_RetVal = CddLed_CodingDataValidation();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CodM_CddLed_Para_HitCount,   1u, ==);
  AL_UNITTEST_CHECK(CddLed_CodingDataValidation_RetVal, TRUE, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_Get_CodingPara
///
/// \Test Case Description
///    - Test subject: 
///        CHeck the validity of coding data
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - return coding data validity
///
//-----------------------------------------------------------------------------
void Mt_CddLed_ParaFct0(void)
{
  typedef struct tsTestCaseDataInput
  {
    tParaFct0_Cmd  eCodingCmd;
    tNvmPara_CodingArea* pData;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    boolean RetValidity;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;
  
  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                     ||       Outputs
    //            eCodingCmd          ,  pData,             ||       RetValidity
   {    {  eParaFct0_CodingDataInvalid, &Coding_Dummy    }   ,   {  FALSE } },
   {    {  eParaFct0_CodingDataValid,   &Coding_Dummy    }   ,   {  TRUE  } },
   {    {  255,                         &Coding_Dummy    }   ,   {  FALSE } },
  };

  for (uint8 ucIdx = 0u; ucIdx < sizeof(asTestCaseData)/sizeof(asTestCaseData[0]); ucIdx++)
  {

    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    CddLed_ParaFct0_Param1 =  asTestCaseData[ucIdx].sInputData.eCodingCmd;
    CddLed_ParaFct0_Param2 =  asTestCaseData[ucIdx].sInputData.pData;

    //Step 3) Call the FUT
    CddLed_ParaFct0_RetVal = CddLed_ParaFct0(CddLed_ParaFct0_Param1, CddLed_ParaFct0_Param2);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
    AL_UNITTEST_CHECK(CddLed_ParaFct0_RetVal, asTestCaseData[ucIdx].sOutputData.RetValidity, ==);
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddLed_Rte_SendLedState
///
/// \FuSa Relevant:   ASIL-B
///
/// \Test Case Description
///    - Test subject: 
///        Check the writing of LED status on RTE
///
///    - Test Design Technique:  - Requirement based test
///                              - DT (Decision Table)
///
///    - Preconditions: none
///
///    - Expected test results: 
///        - LED status written on RTE
///           Rte_Write_CddLed_LedState_Param1.aLedStates[1].eLedErrStatus = eCddLed_ErrShortToGnd
///           Rte_Write_CddLed_LedState_Param1.aLedStates[1].boVinBoostOk = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddLed_Rte_SendLedState(void)
{
  //Step 1) Set pre - conditions
  Rte_Write_CddLed_LedState_HitCount = 0u;

  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  CddLed_Rte_SendLedState_Param1.aStatus[1].Err = eCddLed_ErrShortToGnd;
  CddLed_Rte_SendLedState_Param1.aStatus[1].Vin = eCddLed_VinHi;

  //Step 3) Call the FUT
  CddLed_Rte_SendLedState(CddLed_Rte_SendLedState_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CddLed_LedState_Param1.aLedStates[1].eLedErrStatus, eCddLed_ErrShortToGnd, ==);
  AL_UNITTEST_CHECK(Rte_Write_CddLed_LedState_Param1.aLedStates[1].boVinBoostOk, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_CddLed_LedState_HitCount, 1u, == );
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
void ALUnitTest_AddTests_Adapter(void)
{
  ALUnitTest_AddFunction("Mt_riCddLedInit"                 , Mt_riCddLedInit);
  ALUnitTest_AddFunction("Mt_reCddLedNewTarget"            , Mt_reCddLedNewTarget);
  ALUnitTest_AddFunction("Mt_rpCddLed_Cycle"               , Mt_rpCddLed_Cycle);
  ALUnitTest_AddFunction("Mt_CddLed_Get_CodingPara"        , Mt_CddLed_Get_CodingPara);
  ALUnitTest_AddFunction("Mt_CddLed_CodingDataValidation"  , Mt_CddLed_CodingDataValidation);
  ALUnitTest_AddFunction("Mt_CddLed_ParaFct0"              , Mt_CddLed_ParaFct0);
  ALUnitTest_AddFunction("Mt_CddLed_Rte_SendLedState"      , Mt_CddLed_Rte_SendLedState);
}

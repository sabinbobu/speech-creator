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
/// \file   Test.c
///
/// \brief  Unit Test Cases for  CtrlDcm
///
/// \author Pop Anca Alexandra (M01470A)
///         mailTo:ancaalexandra.pop[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
///  Files covered by this module unit test:
///            Cust/St/St126//App/Swc/Ctrl/Dcm:
///            - ctaaCtrlDcm.c
///            - CtrlDcm.c
///            - CtrlDcm_Data.c
///            - CtrlDcm_RteAccess.c
///            - CtrlDcmSm.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
//  Module Test Cases
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetDiagLvl_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify DIAG_LVL error is active if the DIAG_LVL 
///                        is true or the flag for new ignition is needed
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_GetDiagLvl_RetVal = FALSE
/// \input CtrlDcm_boDiagLvl = TRUE
/// \input CtrlDcm_boIgnitionNeeded = TRUE
///
///   - Expectations:
///
/// \output  CtrlDcm_GetDiagLvl_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetDiagLvl_TestCase1(void)
{
    //Step 1) Set pre-conditions
    CtrlDcm_GetDiagLvl_RetVal = FALSE;

    //Step 2) Assign Input values
    CtrlDcm_boDiagLvl = TRUE;
    CtrlDcm_boIgnitionNeeded = TRUE;

    //Step 3) Call FUT
    CtrlDcm_GetDiagLvl_RetVal = CtrlDcm_GetDiagLvl();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_GetDiagLvl_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetDiagLvl_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify DIAG_LVL error is not active if the DIAG_LVL 
///                        is false or the flag for new ignition is not needed
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_GetDiagLvl_RetVal = FALSE
/// \input CtrlDcm_boDiagLvl = FALSE
/// \input CtrlDcm_boIgnitionNeeded = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_GetDiagLvl_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetDiagLvl_TestCase2(void)
{
    //Step 1) Set pre-conditions
    CtrlDcm_GetDiagLvl_RetVal = FALSE;

    //Step 2) Assign Input values
    CtrlDcm_boDiagLvl = FALSE;
    CtrlDcm_boIgnitionNeeded = FALSE;

    //Step 3) Call FUT
    CtrlDcm_GetDiagLvl_RetVal = CtrlDcm_GetDiagLvl();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_GetDiagLvl_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetDiagLvl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the DIAG_LVL error is active or not active
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetDiagLvl(void)
{
    Mt_CtrlDcm_GetDiagLvl_TestCase1();
    Mt_CtrlDcm_GetDiagLvl_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetDiagLvl_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function set DIAG_LVL error only if DC motor
///                        is in master mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_SetDiagLvl_Param1 = TRUE
/// \input  CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft
/// \input  CtrlDcm_boDiagLvl = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boDiagLvl = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetDiagLvl_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SetDiagLvl_Param1 = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boDiagLvl = FALSE;

    //Step 3) Call FUT
    CtrlDcm_SetDiagLvl(CtrlDcm_SetDiagLvl_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetDiagLvl_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function doesn't set DIAG_LVL error 
///                        if DC motor is not in master mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_SetDiagLvl_Param1 = FALSE
/// \input  CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft
///
///   - Expectations:
///
/// \output  CtrlDcm_boDiagLvl = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetDiagLvl_TestCase2(void)
{
    //Step 1) Set pre-conditions
    CtrlDcm_boDiagLvl = FALSE;

    //Step 2) Assign Input values
    CtrlDcm_SetDiagLvl_Param1 = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;

    //Step 3) Call FUT
    CtrlDcm_SetDiagLvl(CtrlDcm_SetDiagLvl_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetDiagLvl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the DIAG_LVL error was set only if DC motor is 
///                     in master mode
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetDiagLvl(void)
{
    Mt_CtrlDcm_SetDiagLvl_TestCase1();
    Mt_CtrlDcm_SetDiagLvl_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSlaveStopRequest_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function set stop request for slave 
///                        only if side is for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_SetSlaveStopRequest_Param1 = TRUE
/// \input  CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft
/// \input  CtrlDcm_boSlaveStop = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSlaveStopRequest_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SetSlaveStopRequest_Param1 = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boSlaveStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_SetSlaveStopRequest(CtrlDcm_SetSlaveStopRequest_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSlaveStopRequest_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function if in slave mode request is only read
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveStop = FALSE
/// \input  CtrlDcm_SetSlaveStopRequest_Param1 = TRUE
/// \input  CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
///
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveStop = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSlaveStopRequest_TestCase2(void)
{
    //Step 1) Set pre-conditions
    CtrlDcm_boSlaveStop = FALSE;
    //Step 2) Assign Input values
    CtrlDcm_SetSlaveStopRequest_Param1 = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;

    //Step 3) Call FUT
    CtrlDcm_SetSlaveStopRequest(CtrlDcm_SetSlaveStopRequest_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSlaveStopRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the stop request for slave was set or if in slave mode
///                     request is only read
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSlaveStopRequest(void)
{
    Mt_CtrlDcm_SetSlaveStopRequest_TestCase1();
    Mt_CtrlDcm_SetSlaveStopRequest_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSlaveSafetyPosition_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function set pos request only if
///                        side is for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_SetSlaveSafetyPosition_Param1 = TRUE
/// \input  CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft
/// \input      CtrlDcm_boSlaveSafetyPos = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveSafetyPos = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSlaveSafetyPosition_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SetSlaveSafetyPosition_Param1 = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boSlaveSafetyPos = FALSE;

    //Step 3) Call FUT
    CtrlDcm_SetSlaveSafetyPosition(CtrlDcm_SetSlaveSafetyPosition_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSlaveSafetyPosition_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function if in slave mode request is only read
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_boSlaveSafetyPos = FALSE
/// \input  CtrlDcm_SetSlaveSafetyPosition_Param1 = TRUE
/// \input  CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
///
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSlaveSafetyPosition_TestCase2(void)
{
    //Step 1) Set pre-conditions
    CtrlDcm_boSlaveSafetyPos = FALSE;

    //Step 2) Assign Input values
    CtrlDcm_SetSlaveSafetyPosition_Param1 = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;

    //Step 3) Call FUT
    CtrlDcm_SetSlaveSafetyPosition(CtrlDcm_SetSlaveSafetyPosition_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSlaveSafetyPosition
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the safety position command for slave 
///                     was set or if in slave mode request is only read
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSlaveSafetyPosition(void)
{
    Mt_CtrlDcm_SetSlaveSafetyPosition_TestCase1();
    Mt_CtrlDcm_SetSlaveSafetyPosition_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetFailIgnitionNeeded
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function set request for ignition
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_SetFailIgnitionNeeded_Param1 = TRUE
/// \input  CtrlDcm_boIgnitionNeeded = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boIgnitionNeeded = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetFailIgnitionNeeded(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SetFailIgnitionNeeded_Param1 = TRUE;
    CtrlDcm_boIgnitionNeeded = FALSE;

    //Step 3) Call FUT
    CtrlDcm_SetFailIgnitionNeeded(CtrlDcm_SetFailIgnitionNeeded_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boIgnitionNeeded, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RetPowerTrainActive
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function powertrain active is deactivated
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_boPowertrainActive = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boPowertrainActive = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RetPowerTrainActive(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = FALSE;
 
    //Step 3) Call FUT
    CtrlDcm_RetPowerTrainActive();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boPowertrainActive, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadEnvironmentSignals_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function engine started and 
///                        set ConVehIgnition with true
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT
/// \input  CtrlDcm_boConVehIgnition = FALSE;
/// \input  CtrlDcm_boPowertrainActive = TRUE;
/// \input  Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output CtrlDcm_boConVehIgnition = TRUE
/// \output  CtrlDcm_boPowertrainActive = FALSE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadEnvironmentSignals_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
    CtrlDcm_boConVehIgnition = FALSE;
    CtrlDcm_boPowertrainActive = TRUE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadEnvironmentSignals();
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boConVehIgnition, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boPowertrainActive, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadEnvironmentSignals_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function engine not started and powertrain is not activated,
///                        set ConVehIgnition with true, reset flag and set PowerTrainActive with false
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT
/// \input  CtrlDcm_boConVehIgnition = TRUE
/// \input  CtrlDcm_boPowertrainActive = TRUE
/// \input  Rte_Read_SysMon_VehNetState_HitCount = 0u
///
///   - Expectations:
///
/// \output CtrlDcm_boConVehIgnition = FALSE
/// \output  CtrlDcm_boPowertrainActive = FALSE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadEnvironmentSignals_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_boPowertrainActive = TRUE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadEnvironmentSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boConVehIgnition, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boPowertrainActive, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadEnvironmentSignals_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify if powertrain is activated and set
///                        PowerTrainAvtive with true
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID
/// \input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_SECU
/// \input  CtrlDcm_boConVehIgnition = TRUE
/// \input  CtrlDcm_boPowertrainActive = FALSE
/// \input  Rte_Read_SysMon_VehNetState_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_boConVehIgnition = FALSE
/// \output  CtrlDcm_boPowertrainActive = TRUE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadEnvironmentSignals_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_SECU;
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_boPowertrainActive = FALSE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadEnvironmentSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boConVehIgnition, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boPowertrainActive, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadEnvironmentSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the enviromental signals are read
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadEnvironmentSignals(void)
{
    Mt_CtrlDcm_ReadEnvironmentSignals_TestCase1();
    Mt_CtrlDcm_ReadEnvironmentSignals_TestCase2();
    Mt_CtrlDcm_ReadEnvironmentSignals_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadStatusSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read RTE signals from CddDcm
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input   Rte_Read_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE
/// \input   Rte_Read_CddDcm_ErrorStatus_Param1.boElecGND = FALSE
/// \input   CtrlDcm_sErrorStatus.boElecBAT = FALSE
/// \input   CtrlDcm_sErrorStatus.boElecGND = TRUE
/// \input   Rte_Read_CddDcm_ErrorStatus_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_sErrorStatus.boElecBAT = TRUE
/// \output  CtrlDcm_sErrorStatus.boElecGND = FALSE
/// \output  Rte_Read_CddDcm_ErrorStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadStatusSignals(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
    Rte_Read_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
    CtrlDcm_sErrorStatus.boElecBAT = FALSE;
    CtrlDcm_sErrorStatus.boElecGND = TRUE;
    Rte_Read_CddDcm_ErrorStatus_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadStatusSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_sErrorStatus.boElecBAT, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_sErrorStatus.boElecGND, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_CddDcm_ErrorStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_LimitAngle_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calculate angle with upper limit
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_LimitAngle_Param1 = 15u
/// \input CtrlDcm_LimitAngle_Param2 = 15u
/// \input CtrlDcm_LimitAngle_Param3 = 10u
///
///   - Expectations:
///
/// \output  CtrlDcm_LimitAngle_RetVal = 10u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_LimitAngle_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_LimitAngle_Param1 = 15u;
    CtrlDcm_LimitAngle_Param2 = 15u;
    CtrlDcm_LimitAngle_Param3 = 10u;

    //Step 3) Call FUT
    CtrlDcm_LimitAngle_RetVal= CtrlDcm_LimitAngle(CtrlDcm_LimitAngle_Param1, CtrlDcm_LimitAngle_Param2, CtrlDcm_LimitAngle_Param3);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_LimitAngle_RetVal, 10u, == );
    
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_LimitAngle_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calculate angle with lower limit
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_LimitAngle_Param1 = 15u
/// \input CtrlDcm_LimitAngle_Param2 = 15u
/// \input CtrlDcm_LimitAngle_Param3 = 20u
///
///   - Expectations:
///
/// \output  CtrlDcm_LimitAngle_RetVal = 15u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_LimitAngle_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_LimitAngle_Param1 = 15u;
    CtrlDcm_LimitAngle_Param2 = 15u;
    CtrlDcm_LimitAngle_Param3 = 20u;

    //Step 3) Call FUT
    CtrlDcm_LimitAngle_RetVal= CtrlDcm_LimitAngle(CtrlDcm_LimitAngle_Param1, CtrlDcm_LimitAngle_Param2, CtrlDcm_LimitAngle_Param3);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_LimitAngle_RetVal, 15u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_LimitAngle_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calculate angle with lower limit
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_LimitAngle_Param1 = 15u
/// \input CtrlDcm_LimitAngle_Param2 = 15u
/// \input CtrlDcm_LimitAngle_Param3 = -20u
///
///   - Expectations:
///
/// \output  CtrlDcm_LimitAngle_RetVal = -15u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_LimitAngle_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_LimitAngle_Param1 = 15u;
    CtrlDcm_LimitAngle_Param2 = 15u;
    CtrlDcm_LimitAngle_Param3 = -20u;

    //Step 3) Call FUT
    CtrlDcm_LimitAngle_RetVal = CtrlDcm_LimitAngle(CtrlDcm_LimitAngle_Param1, CtrlDcm_LimitAngle_Param2, CtrlDcm_LimitAngle_Param3);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_LimitAngle_RetVal, -15u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_LimitAngle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the calculation angle with limitation
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_LimitAngle(void)
{
    Mt_CtrlDcm_LimitAngle_TestCase1();
    Mt_CtrlDcm_LimitAngle_TestCase2();
    Mt_CtrlDcm_LimitAngle_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DetectSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads ecu side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
///
///   - Expectations:
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output  CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectSide(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;

    //Step 3) Call FUT
    CtrlDcm_DetectSide();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_eMountingSide, CtrlDcm_eMountedRight, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns ecu side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
///
///   - Expectations:
///
/// \output  CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnSide(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;

    //Step 3) Call FUT
    CtrlDcm_ReturnSide();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMountingSide, CtrlDcm_eMountedRight, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function collect adjustment errors
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_INVALID
/// \input     CtrlDcm_boLvlAdjFuncFault = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boLvlAdjFuncFault = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_INVALID;
    CtrlDcm_boLvlAdjFuncFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjFunctionalFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjFuncFault, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function collect fault of levelling
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_INVALID
/// \input CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_TIMEOUT
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedRight
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE
///
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveLvlAdjFuncFault = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_INVALID;
    CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_TIMEOUT;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjFunctionalFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveLvlAdjFuncFault, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function collect fault of levelling
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_SECU;
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_E2E_ALIVEERR;
/// \input CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE; 
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveLvlAdjFuncFault = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_SECU;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_E2E_ALIVEERR;
    CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjFunctionalFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveLvlAdjFuncFault, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function collect fault of levelling
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
/// \input CtrlDcm_boVehAttitudeInvalid = FALSE;
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
/// \input CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
///
///   - Expectations:
///
/// \output  CtrlDcm_boSlaveLvlAdjFuncFault = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
    CtrlDcm_boVehAttitudeInvalid = FALSE;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
    CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjFunctionalFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjFuncFault, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function collect fault of levelling
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_INVALID;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;

///
///   - Expectations:
///
/// \output  CtrlDcm_boLvlAdjFuncFault = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_INVALID;
    CtrlDcm_boLvlAdjFuncFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjFunctionalFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjFuncFault, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function collect fault of levelling
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
/// \input CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
/// \input CtrlDcm_boVehAttitudeInvalid = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_boLvlAdjFuncFault = TRUE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase6(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlDcm_SIG_UNAVAILABLE;
    CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
    CtrlDcm_boVehAttitudeInvalid = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjFunctionalFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjFuncFault, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that functional fault of levelling read
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus()
{
    Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase1();
    Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase2();
    Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase3();
    Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase4();
    Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase5();
    Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus_TestCase6();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CodingDataReady_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify if coding data are available
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_CodingDataReady_Param1               = eMountedLeft;
/// \input  Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
///
///   - Expectations:
///
/// \output  CtrlDcm_CodingDataReady_RetVal = TRUE
/// \output  Rte_Read_CodM_Pitch_Para_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CodingDataReady_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_CodingDataReady_Param1               = eMountedLeft;
    Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataValid;

    //Step 3) Call FUT
    CtrlDcm_CodingDataReady_RetVal= CtrlDcm_CodingDataReady(&CtrlDcm_CodingDataReady_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_CodingDataReady_RetVal   , TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CodingDataReady_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify if coding data are not available
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlDcm_CodingDataReady_Param1               = CtrlDcm_eMountedLeft
/// \input  Rte_Read_CodM_Pitch_Para_HitCount            = 0u
/// \input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid
///
///   - Expectations:
///
/// \output  CtrlDcm_CodingDataReady_RetVal    = FALSE
/// \output  Rte_Read_CodM_Pitch_Para_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CodingDataReady_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_CodingDataReady_Param1               = CtrlDcm_eMountedLeft;
    Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;

    //Step 3) Call FUT
    CtrlDcm_CodingDataReady_RetVal = CtrlDcm_CodingDataReady(&CtrlDcm_CodingDataReady_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_CodingDataReady_RetVal   , FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,    1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CodingDataReady
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the coding data are available
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CodingDataReady(void)
{
    Mt_CtrlDcm_CodingDataReady_TestCase1();
    Mt_CtrlDcm_CodingDataReady_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmMinVehAtt
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return minim
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  CtrlDcm_CodingData.DCMotorData.scMin_Vehicle_Attitude = -42
///
///   - Expectations:
///
/// \output  Cod_DcmMinVehAtt_RetVal = -42
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmMinVehAtt(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_CodingData.DCMotorData.scMin_Vehicle_Attitude = -42;
    //Step 3) Call FUT
    Cod_DcmMinVehAtt_RetVal = Cod_DcmMinVehAtt();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmMinVehAtt_RetVal, -42, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmMaxVehAtt
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return maxim
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  CtrlDcm_CodingData.DCMotorData.scMax_Vehicle_Attitude = 49
///
///   - Expectations:
///
/// \output  Cod_DcmMaxVehAtt_RetVal = 49u
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmMaxVehAtt(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_CodingData.DCMotorData.scMax_Vehicle_Attitude = 49;
    //Step 3) Call FUT
    Cod_DcmMaxVehAtt_RetVal = Cod_DcmMaxVehAtt();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmMaxVehAtt_RetVal, 49, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmMinAdjASL
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return minim
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  CtrlDcm_snMin_ASL_Adjust = -250
///
///   - Expectations:
///
/// \output  Cod_DcmMinAdjASL_RetVal = -250
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmMinAdjASL(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_snMin_ASL_Adjust = -250;
    //Step 3) Call FUT
    Cod_DcmMinAdjASL_RetVal = Cod_DcmMinAdjASL();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmMinAdjASL_RetVal, -250, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmMaxAdjASL
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return maxim
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  CtrlDcm_snMax_ASL_Adjust = 50
///
///   - Expectations:
///
/// \output  Cod_DcmMaxAdjASL_RetVal = 50
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmMaxAdjASL(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_snMax_ASL_Adjust = 50;
    //Step 3) Call FUT
    Cod_DcmMaxAdjASL_RetVal = Cod_DcmMaxAdjASL();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmMaxAdjASL_RetVal, 50, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmSp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return safety pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  CtrlDcm_scSafety_Position = -27
///
///   - Expectations:
///
/// \output  Cod_DcmSp_RetVal = -27
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmSp(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_scSafety_Position = -27;
    //Step 3) Call FUT
    Cod_DcmSp_RetVal = Cod_DcmSp();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmSp_RetVal, -27, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmVehAttThrStill
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return vehicle attitude adjustment value from coding
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  CtrlDcm_CodingData.DCMotorData.ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL = 13u
///
///   - Expectations:
///
/// \output  Cod_DcmVehAttThrStill_RetVal = 13u
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmVehAttThrStill(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_CodingData.DCMotorData.ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL = 13u;
    //Step 3) Call FUT
    Cod_DcmVehAttThrStill_RetVal = Cod_DcmVehAttThrStill();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmVehAttThrStill_RetVal, 13u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmFrozenVehSpeedASL
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return frozen vehicle speed
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
///   - Expectations:
///
/// \output  Cod_DcmFrozenVehSpeedASL_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmFrozenVehSpeedASL(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    //Step 3) Call FUT
    Cod_DcmFrozenVehSpeedASL_RetVal = Cod_DcmFrozenVehSpeedASL();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmFrozenVehSpeedASL_RetVal, 0u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmEnable_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return if DCM is disabled
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  NvmBlockDeltaPwmPara.eASL_Present = eASL_Absent
///
///   - Expectations:
///
/// \output  Cod_DcmEnable_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmEnable_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    NvmBlockDeltaPwmPara.eASL_Present = eASL_Absent;
    //Step 3) Call FUT
    Cod_DcmEnable_RetVal = Cod_DcmEnable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmEnable_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmEnable_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return if DCM is enabled
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// \input  NvmBlockDeltaPwmPara.eASL_Present = eASL_Present
///
///   - Expectations:
///
/// \output  Cod_DcmEnable_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmEnable_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    NvmBlockDeltaPwmPara.eASL_Present = eASL_Present;
    //Step 3) Call FUT
    Cod_DcmEnable_RetVal = Cod_DcmEnable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmEnable_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmEnable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return enable status
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmEnable(void)
{
  Mt_Cod_DcmEnable_TestCase1();
  Mt_Cod_DcmEnable_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmVehAttThrMotion
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns value from coding for vehicle attitude
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
///   - Expectations:
///
/// \output  Cod_DcmVehAttThrMotion_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmVehAttThrMotion(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    //Step 3) Call FUT
    Cod_DcmVehAttThrMotion_RetVal = Cod_DcmVehAttThrMotion();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmVehAttThrMotion_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cod_DcmMotionDelayASL
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return motion delay
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
///   - Expectations:
///
/// \output  Cod_DcmMotionDelayASL_RetVal = 0u
///
//-----------------------------------------------------------------------------
void Mt_Cod_DcmMotionDelayASL(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    //Step 3) Call FUT
    Cod_DcmMotionDelayASL_RetVal = Cod_DcmMotionDelayASL();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Cod_DcmMotionDelayASL_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ParaFct0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read coding data, if coding data is valid 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_ParaFct0_Param1                                            = eParaFct0_CodingDataValid
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                         = CtrlDcm_eMountedLeft
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1                              = CtrlDcm_eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount                       = 0u
/// \input CtrlDcm_CodingData                                                 = { 0 }
/// \input CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.scSafety_Position_Left = -70
/// \input CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMin_ASL_Adjust_Left  = -50
/// \input CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMax_ASL_Adjust_Left  = 30
///
///   - Expectations:
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount          = 1u
/// \output  CtrlDcm_CodingData.DCMotorData.scSafety_Position_Left = -70
/// \output  CtrlDcm_CodingData.DCMotorData.snMin_ASL_Adjust_Left  = -50
/// \output  CtrlDcm_CodingData.DCMotorData.snMax_ASL_Adjust_Left  = 30
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ParaFct0_TestCase1(void)
{
    //Step 1) Set pre-conditions
    tNvmPara_AvacStpBlock sEmptyStruct = { 0 };
    //Step 2) Assign Input values
    CtrlDcm_ParaFct0_Param1                                            = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                         = CtrlDcm_eMountedLeft;
    CtrlDcm_RteAccess_Read_EcuSide_Param1                              = CtrlDcm_eMountedLeft;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount                       = 0u;
    CtrlDcm_CodingData                                                 = sEmptyStruct;
    CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.scSafety_Position_Left = -70;
    CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMin_ASL_Adjust_Left  = -50;
    CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMax_ASL_Adjust_Left  = 30;

    //Step 3) Call FUT
    CtrlDcm_ParaFct0(CtrlDcm_ParaFct0_Param1,&CtrlDcm_ParaFct0_Param2);

    //Step 4) Check expected output values
   AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount         , 1u, == );
   AL_UNITTEST_CHECK(CtrlDcm_CodingData.DCMotorData.scSafety_Position_Left, -70, == );
   AL_UNITTEST_CHECK(CtrlDcm_CodingData.DCMotorData.snMin_ASL_Adjust_Left , -50, == );
   AL_UNITTEST_CHECK(CtrlDcm_CodingData.DCMotorData.snMax_ASL_Adjust_Left , 30, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ParaFct0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read coding data, if coding data is valid 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_ParaFct0_Param1                                             = eParaFct0_CodingDataValid
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                          = CtrlDcm_eMountedRight
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1                               = CtrlDcm_eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount                        = 0u
/// \input CtrlDcm_CodingData                                                  = { 0 }
/// \input CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.scSafety_Position_Right = -60
/// \input CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMin_ASL_Adjust_Right  = -30
/// \input CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMax_ASL_Adjust_Right  = 10
///
///   - Expectations:
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount           = 1u
/// \output  CtrlDcm_CodingData.DCMotorData.scSafety_Position_Right = -60
/// \output  CtrlDcm_CodingData.DCMotorData.snMin_ASL_Adjust_Right  = -30
/// \output  CtrlDcm_CodingData.DCMotorData.snMax_ASL_Adjust_Right  = 10
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ParaFct0_TestCase2(void)
{
    //Step 1) Set pre-conditions
    tNvmPara_AvacStpBlock sEmptyStruct = { 0 };
    //Step 2) Assign Input values
    CtrlDcm_ParaFct0_Param1                                             = eParaFct0_CodingDataValid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1                          = CtrlDcm_eMountedRight;
    CtrlDcm_RteAccess_Read_EcuSide_Param1                               = CtrlDcm_eMountedRight;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount                        = 0u;
    CtrlDcm_CodingData                                                  = sEmptyStruct;
    CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.scSafety_Position_Right = -60;
    CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMin_ASL_Adjust_Right  = -30;
    CtrlDcm_ParaFct0_Param2.AvacStp.DCMotorData.snMax_ASL_Adjust_Right  = 10;

    //Step 3) Call FUT
    CtrlDcm_ParaFct0(CtrlDcm_ParaFct0_Param1,&CtrlDcm_ParaFct0_Param2);

    //Step 4) Check expected output values
   AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount          ,  1u, == );
   AL_UNITTEST_CHECK(CtrlDcm_CodingData.DCMotorData.scSafety_Position_Right, -60, == );
   AL_UNITTEST_CHECK(CtrlDcm_CodingData.DCMotorData.snMin_ASL_Adjust_Right , -30, == );
   AL_UNITTEST_CHECK(CtrlDcm_CodingData.DCMotorData.snMax_ASL_Adjust_Right ,  10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ParaFct0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read coding data and store results in local variables
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedRight;
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedRight;
/// \input boLwrSpVz = FALSE;
/// \input CtrlDcm_scSafety_Position = 1u;

///
///   - Expectations:
///
/// \output  CtrlDcm_scSafety_Position = 0u
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ParaFct0_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedRight;
    CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedRight;
    CtrlDcm_scSafety_Position = 1u;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
    CtrlDcm_CodingData.DCMotorData.scSafety_Position_Right = 0;

    //Step 3) Call FUT
    CtrlDcm_ParaFct0(CtrlDcm_ParaFct0_Param1, &CtrlDcm_ParaFct0_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_scSafety_Position, 0, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ParaFct0_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read coding data 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedUndef;
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedUndef;
/// \input boLwrSpVz = TRUE;
/// \input CtrlDcm_scSafety_Position = 1u;
///
///   - Expectations:
///
/// \output  CtrlDcm_scSafety_Position = 0u
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ParaFct0_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedUndef;
    CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedUndef;
    CtrlDcm_scSafety_Position = 0u;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ParaFct0(CtrlDcm_ParaFct0_Param1, &CtrlDcm_ParaFct0_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_scSafety_Position, 0u, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that read coding data
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_ParaFct0(void)
{
    Mt_CtrlDcm_ParaFct0_TestCase1();
    Mt_CtrlDcm_ParaFct0_TestCase2();
    Mt_CtrlDcm_ParaFct0_TestCase3();
    Mt_CtrlDcm_ParaFct0_TestCase4();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read Ecu mounting left from RTE 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_Read_EcuSide_RetVal = CtrlDcm_eMountedLeft
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount= 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedLeft;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedLeft;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_Read_EcuSide_RetVal = CtrlDcm_RteAccess_Read_EcuSide(&CtrlDcm_RteAccess_Read_EcuSide_Param1);
   
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_EcuSide_RetVal, CtrlDcm_eMountedLeft, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read Ecu mounting undefined from RTE 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedUndef;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_Read_EcuSide_RetVal = CtrlDcm_eMountedLeft
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount= 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedLeft;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedUndef;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Read_EcuSide_RetVal = CtrlDcm_RteAccess_Read_EcuSide(&CtrlDcm_RteAccess_Read_EcuSide_Param1);
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_EcuSide_RetVal, CtrlDcm_eMountedLeft, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read Ecu mounting right from RTE 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedRight;
/// \inputRte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u; 
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_Read_EcuSide_RetVal = CtrlDcm_eMountedLeft
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_Read_EcuSide_Param1 = CtrlDcm_eMountedLeft;
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedRight;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Read_EcuSide_RetVal = CtrlDcm_RteAccess_Read_EcuSide(&CtrlDcm_RteAccess_Read_EcuSide_Param1);
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_EcuSide_RetVal, CtrlDcm_eMountedLeft, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_EcuSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that read Ecu mounting side from RTE
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_Read_EcuSide(void)
{
    Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase1();
    Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase2();
    Mt_CtrlDcm_RteAccess_Read_EcuSide_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and set
///                        invalid status with false
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 5u;
/// \input CtrlDcm_RteAccess_ReadSpeed_Param1 = TRUE;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE
/// \output CtrlDcm_RteAccess_ReadSpeed_RetVal = 5u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
    Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 5u;
    CtrlDcm_RteAccess_ReadSpeed_Param1=TRUE;
    Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSpeed_RetVal = CtrlDcm_RteAccess_ReadSpeed(&CtrlDcm_RteAccess_ReadSpeed_Param1);
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSpeed_Param1, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSpeed_RetVal, 5u, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and set
///                        invalid status with true if speed message is invalid or 
///                        timeout and set speed invalid status with true
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
/// \input CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadSpeed_Param1 = TRUE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
    CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
    Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSpeed(&CtrlDcm_RteAccess_ReadSpeed_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSpeed_Param1, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and keep
///                         previous value of speed invalid status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_E2E_CRCERR
/// \input  CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_E2E_CRCERR;
    CtrlDcm_RteAccess_ReadSpeed_Param1 = FALSE;
    Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSpeed(&CtrlDcm_RteAccess_ReadSpeed_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSpeed_Param1, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSpeed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads speed
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSpeed(void)
{
    Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadSpeed_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set electric state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal = eTA_NOMINAL
/// \output  Rte_Read_SysMon_VehicleSpeed_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_NOMINAL;
    Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal = CtrlDcm_RteAccess_ReadVehicleElectricState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal, eTA_NOMINAL, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set electric state with invalid
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal = eInvalid
/// \output  Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal = CtrlDcm_RteAccess_ReadVehicleElectricState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal, eInvalid, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        keep previous value 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_DEFAULT;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDEMARRAGE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_DEFAULT;
    Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eDEMARRAGE;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVehicleElectricState_RetVal = CtrlDcm_RteAccess_ReadVehicleElectricState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleElectricState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads vehicle electric state
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_ReadVehicleElectricState(void)
{
    Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadVehicleElectricState_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        if the vehicle state signal is valid set electric state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVESMainState_RetVal = VESState_Ignition
/// \output  Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
    Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVESMainState_RetVal = CtrlDcm_RteAccess_ReadVESMainState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVESMainState_RetVal, VESState_Ignition, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        if the vehicle state signal is timeout set electric state with start
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVESMainState_RetVal = VESState_Start
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVESMainState_RetVal = CtrlDcm_RteAccess_ReadVESMainState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVESMainState_RetVal, VESState_Start, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        if the vehicle state signal is invalid set electric state with invalid
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = SIG_INVALID;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVESMainState_RetVal = SIG_INVALID
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = SIG_INVALID;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVESMainState_RetVal = CtrlDcm_RteAccess_ReadVESMainState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVESMainState_RetVal, SIG_INVALID, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        keep previous value
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_DEFAULT;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_DEFAULT;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVESMainState_RetVal = CtrlDcm_RteAccess_ReadVESMainState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVESMainState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads vehicle electric state
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVESMainState(void)
{
    Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase3();
    Mt_CtrlDcm_RteAccess_ReadVESMainState_TestCase4();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set vehicle configuration
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal = eModeConfigVehicle_Showroom
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal = CtrlDcm_RteAccess_ReadVehicleModeConfig();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal, eModeConfigVehicle_Showroom, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set vehicle configuration with invalid
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount =0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal = eModeConfigVehicle_Invalid
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal = CtrlDcm_RteAccess_ReadVehicleModeConfig();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal, eModeConfigVehicle_Invalid, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set vehicle configuration with invalid2
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal = eModeConfigVehicle_Invalid2
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal = CtrlDcm_RteAccess_ReadVehicleModeConfig();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadVehicleModeConfig_RetVal, eModeConfigVehicle_Invalid2, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads The state of vehicle configuration
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig(void)
{
    Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set vehicle configuration and set vehicle attitude with false
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param1 = 0.02;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param2 = TRUE;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param3 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
/// \input Rte_Read_ppsAvacStat1Out_Port_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadAvacCommand_Param2 = FALSE
/// \output  Rte_Read_ppsAvacStat1Out_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_VALID;
    CtrlDcm_RteAccess_ReadAvacCommand_Param1=0.02;
    CtrlDcm_RteAccess_ReadAvacCommand_Param2=TRUE;
    CtrlDcm_RteAccess_ReadAvacCommand_Param3= CtrlDcm_eMountedLeft;
    Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
    Rte_Read_ppsAvacStat1Out_Port_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadAvacCommand(&CtrlDcm_RteAccess_ReadAvacCommand_Param1,&CtrlDcm_RteAccess_ReadAvacCommand_Param2, CtrlDcm_RteAccess_ReadAvacCommand_Param3);
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadAvacCommand_Param2, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_ppsAvacStat1Out_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        set vehicle configuration and set vehicle attitude with true
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_INVALID;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param1 = 0.02;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param2 = TRUE;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param3 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
/// \input     Rte_Read_ppsAvacStat1Out_Port_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadAvacCommand_Param2 = TRUE
/// \output      Rte_Read_ppsAvacStat1Out_Port_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_INVALID;
    CtrlDcm_RteAccess_ReadAvacCommand_Param1 = 0.02;
    CtrlDcm_RteAccess_ReadAvacCommand_Param2 = FALSE;
    CtrlDcm_RteAccess_ReadAvacCommand_Param3 = CtrlDcm_eMountedLeft;
    Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
    Rte_Read_ppsAvacStat1Out_Port_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadAvacCommand(&CtrlDcm_RteAccess_ReadAvacCommand_Param1, &CtrlDcm_RteAccess_ReadAvacCommand_Param2, CtrlDcm_RteAccess_ReadAvacCommand_Param3);
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadAvacCommand_Param2, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_ppsAvacStat1Out_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and 
///                        keep current value
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_SNA;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param1 = 0.02;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param2 = TRUE;
/// \input CtrlDcm_RteAccess_ReadAvacCommand_Param3 = CtrlDcm_eMountedLeft;
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
/// \output  CtrlDcm_RteAccess_ReadAvacCommand_Param2 = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_SNA;
    CtrlDcm_RteAccess_ReadAvacCommand_Param1 = 0.02;
    CtrlDcm_RteAccess_ReadAvacCommand_Param2 = FALSE;
    CtrlDcm_RteAccess_ReadAvacCommand_Param3 = CtrlDcm_eMountedLeft;
    Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
    Rte_Read_ppsAvacStat1Out_Port_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadAvacCommand(&CtrlDcm_RteAccess_ReadAvacCommand_Param1, &CtrlDcm_RteAccess_ReadAvacCommand_Param2, CtrlDcm_RteAccess_ReadAvacCommand_Param3);
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadAvacCommand_Param2, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadAvacCommand
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads the state of vehicle configuration
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadAvacCommand(void)
{
    Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadAvacCommand_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDriverErrors
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads errors sent by CddDcm
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
/// \input Rte_Read_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
/// \input CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecBAT = FALSE;
/// \input CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecGND = TRUE;
/// \input Rte_Read_CddDcm_ErrorStatus_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecBAT = TRUE 
/// \output  CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecGND = FALSE
/// \output  Rte_Read_CddDcm_ErrorStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadDriverErrors(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
    Rte_Read_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
    CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecBAT = FALSE;
    CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecGND = TRUE;
    Rte_Read_CddDcm_ErrorStatus_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDriverErrors(&CtrlDcm_RteAccess_ReadDriverErrors_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecBAT, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDriverErrors_Param1.boElecGND, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_CddDcm_ErrorStatus_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if
///                        the state of pitch sensors is no failure set the sensor state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE;
/// \input CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
/// \input     Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE 
/// \output      Rte_Read_Pitch_PlausState_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE;
    CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    Rte_Read_Pitch_PlausState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_RteAccess_ReadSensorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSensorStatus_Param1, CtrlDcm_eHLS_NO_FAILURE, == );
    AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if
///                        the state of pitch sensors is sensor failure set the sensor state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Pitch_PlausState_Param1 = eSENSOR_FAILURE;
/// \input CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_SENSOR_FAILURE 
/// \output     Rte_Read_Pitch_PlausState_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Pitch_PlausState_Param1 = eSENSOR_FAILURE;
    CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    Rte_Read_Pitch_PlausState_HitCount = 0u;

    //Step 3) Call FUT
        CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_RteAccess_ReadSensorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSensorStatus_Param1, CtrlDcm_eHLS_SENSOR_FAILURE, == );
    AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount , 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if
///                        the state of pitch sensors is frozen failure set the sensor state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Pitch_PlausState_Param1 = eFROZEN_FAILURE;
/// \input CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_STORED_FAILURE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
/// \input     Rte_Read_Pitch_PlausState_HitCount = 0u;
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_FROZEN_FAILURE 
/// \output      Rte_Read_Pitch_PlausState_HitCount = 1u; 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Pitch_PlausState_Param1 = eFROZEN_FAILURE;
    CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_STORED_FAILURE;
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    Rte_Read_Pitch_PlausState_HitCount = 0u;

    //Step 3) Call FUT
        CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_RteAccess_ReadSensorStatus_Param1);

    //Step 4) Check expected output values
        AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSensorStatus_Param1, CtrlDcm_eHLS_FROZEN_FAILURE, == );
        AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if
///                        the state of pitch sensors is stored failure set the sensor state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Pitch_PlausState_Param1 = eSTORED_FAILURE;
/// \input CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount = 1u 
/// \output  CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_STORED_FAILURE 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Pitch_PlausState_Param1 = eSTORED_FAILURE;
    CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
    Rte_Read_Pitch_PlausState_HitCount = 0u;
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_RteAccess_ReadSensorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSensorStatus_Param1, CtrlDcm_eHLS_STORED_FAILURE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and leave previous value 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
/// \input Rte_Read_Pitch_PlausState_Param1 = 7u;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
/// \input CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount = 1u 
/// \output  CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    Rte_Read_Pitch_PlausState_Param1 = 7u;
    Rte_Read_Pitch_PlausState_HitCount = 0u;
    CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_RteAccess_ReadSensorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSensorStatus_Param1, CtrlDcm_eHLS_NO_FAILURE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if NVM
///                        input is CAN set the sensor state on no failure
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_STORED_FAILURE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
/// \input Rte_Read_Pitch_PlausState_Param1 = 7u;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount = 1u 
/// \output  CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_NO_FAILURE 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase6(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_ReadSensorStatus_Param1 = CtrlDcm_eHLS_STORED_FAILURE;
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
    Rte_Read_Pitch_PlausState_Param1 = 7u;
    Rte_Read_Pitch_PlausState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadSensorStatus(&CtrlDcm_RteAccess_ReadSensorStatus_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadSensorStatus_Param1, CtrlDcm_eHLS_NO_FAILURE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadSensorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads the state of the pitch sensors
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_ReadSensorStatus(void)
{
    Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase3();
    Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase4();
    Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase5();
    Mt_CtrlDcm_RteAccess_ReadSensorStatus_TestCase6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is valid set target position with positive
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 1u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl= eSigneConsigneSiteD_Positive;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl=2u;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl=5u;
    Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadLevellingTgtPos(&CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl, 2u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Positive, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is valid set target position with negative
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 1u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadLevellingTgtPos(&CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl, 2u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is valid set target position with negative
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ 
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount= 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = 2u;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadLevellingTgtPos(&CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl, 2u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is invalid keep value
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount =0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ 
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount =1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_INVALID;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = 2u;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadLevellingTgtPos(&CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl, 5u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount,1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads target position
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos(void)
{
    Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase3();
    Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is valid set target position with positive
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 1u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CtrlDcm_MasterCommand_Param1.eSigQty = SIG_VALID;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty = SIG_INVALID;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_CtrlDcm_MasterCommand_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_MasterCommand_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl, 2u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Positive, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is valid set target position with negative
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_CtrlDcm_MasterCommand_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ 
/// \output  Rte_Read_CtrlDcm_MasterCommand_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CtrlDcm_MasterCommand_Param1.eSigQty = SIG_VALID;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty = SIG_INVALID;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_CtrlDcm_MasterCommand_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl, 2u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_MasterCommand_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is valid set target position with negative
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input Rte_Read_CtrlDcm_MasterCommand_HitCount=0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ 
/// \output  Rte_Read_CtrlDcm_MasterCommand_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CtrlDcm_MasterCommand_Param1.eSigQty = SIG_VALID;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty = SIG_INVALID;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = 2u;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_CtrlDcm_MasterCommand_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl, 2u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_MasterCommand_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function receive RTE messages and if target levelling
///                        signal is invalid keep value
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
/// \input CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input     CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
/// \input    Rte_Read_CtrlDcm_MasterCommand_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u 
/// \output  CtrlDcm_RteAccess_ReadLevellingTgtPos_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ 
/// \output  Rte_Read_CtrlDcm_MasterCommand_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CtrlDcm_MasterCommand_Param1.eSigQty = SIG_INVALID;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eSigQty = SIG_VALID;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = 2u;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Read_CtrlDcm_MasterCommand_Param1.eRCmdPosLvl.unRCmdPosLvl = 2u;
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl = 5u;
    Rte_Read_CtrlDcm_MasterCommand_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdPosLvl.unRCmdPosLvl, 5u, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_MasterCommand_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads target position
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(void)
{
    Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase3();
    Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault = eDiagLvl_Ok;
/// \input CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1 = FALSE;
/// \input Rte_Write_DrvLedDiag_HitCount = 0u;
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault = eDiagLvl_Ok 
/// \output  Rte_Write_DrvLedDiag_HitCount = 1u 
/// \output  Rte_Read_DrvLedDiag_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault = eDiagLvl_Ok;
    CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1 = FALSE;
    Rte_Write_DrvLedDiag_HitCount = 0u;
    Rte_Read_DrvLedDiag_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Write_DrvLedDiag_Port(CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1);

        //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault, eDiagLvl_Ok,== );
    AL_UNITTEST_CHECK(Rte_Write_DrvLedDiag_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault = eDiagLvl_Nok;
/// \input CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1 = TRUE;
/// \input Rte_Write_DrvLedDiag_HitCount = 0u;
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault = eDiagLvl_Nok 
/// \output  Rte_Write_DrvLedDiag_HitCount = 1u 
/// \output  Rte_Read_DrvLedDiag_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault = eDiagLvl_Nok;
    CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1 = TRUE;
    Rte_Write_DrvLedDiag_HitCount = 0u;
    Rte_Read_DrvLedDiag_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Write_DrvLedDiag_Port(CtrlDcm_RteAccess_Write_DrvLedDiag_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFault, eDiagLvl_Nok, == );
    AL_UNITTEST_CHECK(Rte_Write_DrvLedDiag_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads the state of drvled diag port
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port(void)
{
    Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port_TestCase1();
    Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFaultR = eDiagLvl_Ok;
/// \input CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1 = FALSE;
/// \input Rte_Write_DrvLedDiagR_HitCount = 0u;
/// \input Rte_Read_DrvLedDiagR_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiagR_Param1.eLevellingAdjustFault = eDiagLvl_Ok 
/// \output  Rte_Write_DrvLedDiagR_HitCount = 1u 
/// \output  Rte_Read_DrvLedDiagR_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_DrvLedDiagR_Param1.eLevellingAdjustFaultR = eDiagLvl_Ok;
    CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1 = FALSE;
    Rte_Write_DrvLedDiagR_HitCount = 0u;
    Rte_Read_DrvLedDiagR_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiagR_Param1.eLevellingAdjustFaultR, eDiagLvl_Ok, == );
    AL_UNITTEST_CHECK(Rte_Write_DrvLedDiagR_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiagR_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFaultR = eDiagLvl_Nok;
/// \input CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1 = TRUE;
/// \input Rte_Write_DrvLedDiagR_HitCount = 0u;
/// \input Rte_Read_DrvLedDiagR_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_Param1.eLevellingAdjustFaultR = eDiagLvl_Nok 
/// \output  Rte_Write_DrvLedDiagR_HitCount = 1u 
/// \output  Rte_Read_DrvLedDiagR_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_DrvLedDiagR_Param1.eLevellingAdjustFaultR = eDiagLvl_Nok;
    CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1 = TRUE;
    Rte_Write_DrvLedDiagR_HitCount = 0u;
    Rte_Read_DrvLedDiagR_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiagR_Param1.eLevellingAdjustFaultR, eDiagLvl_Nok, == );
    AL_UNITTEST_CHECK(Rte_Write_DrvLedDiagR_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_DrvLedDiagR_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads the state of drvled diag port
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(void)
{
    Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_TestCase1();
    Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_DcmDiagStatusR_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_Param1.eLevellingAdjustFaultR = eDiagLvl_Ok;
/// \input CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty = SIG_INVALID;
/// \input CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR = TRUE;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR= FALSE 
/// \output  Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_DcmDiagStatusR_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_DcmDiagStatusR_Param1.eLevellingAdjustFaultR = eDiagLvl_Ok;
    CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty = SIG_INVALID;
    CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR= TRUE;
    Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(&CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_DcmDiagStatusR_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_DcmDiagStatusR_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_Param1.eLevellingAdjustFaultR = eDiagLvl_Nok;
/// \input CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty = SIG_INVALID;
/// \input CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR = FALSE;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty = SIG_VALID 
/// \output  CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR= TRUE 
/// \output  Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_DcmDiagStatusR_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_DcmDiagStatusR_Param1.eLevellingAdjustFaultR = eDiagLvl_Nok;
    CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty = SIG_INVALID;
    CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR = FALSE;
    Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(&CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_Param1.boDiagLvlR, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_DcmDiagStatusR_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads the state of drvled diag port
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(void)
{
    Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_TestCase1();
    Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of DC Motor master command
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive;
/// \input Rte_Write_CtrlDcm_MasterCommand_HitCount = 0u;
/// \input     Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive 
/// \output  Rte_Write_CtrlDcm_MasterCommand_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive;
    Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Write_CtrlDcm_MasterCommand_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl, eSigneConsigneSiteD_Positive, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_MasterCommand_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of DC Motor master command
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;
/// \input Rte_Write_CtrlDcm_MasterCommand_HitCount = 0u;
/// \input     Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;

///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ 
/// \output  Rte_Write_CtrlDcm_MasterCommand_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;
    Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Positive;
    Rte_Write_CtrlDcm_MasterCommand_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl, CtrlDcm_eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_MasterCommand_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of DC Motor master command
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = 3u;
/// \input Rte_Write_CtrlDcm_MasterCommand_HitCount = 0u;
/// \input     Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = 0u 
/// \output  Rte_Write_CtrlDcm_MasterCommand_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1.eRCmdSignLvl = 3u;
    Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;
    Rte_Write_CtrlDcm_MasterCommand_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(&CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_MasterCommand_Param1.eRCmdSignLvl, 0u, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_MasterCommand_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads the state of DC Motor master command
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(void)
{
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase1();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase2();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of vehicle configuration
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop = TRUE;
/// \input CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 2u;
/// \input Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 0u;
/// \input Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop = FALSE;
/// \input Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 1u;

///
///   - Expectations:
///
/// \output  Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop = TRUE
/// \output  Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 2u 
/// \output  Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop= TRUE;
    CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 2u;
    Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount = 0u;
    Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop = FALSE;
    Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition = 1u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(&CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.boStop,TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_Param1.sDcmTarget.nPosition, 2u, == );
    AL_UNITTEST_CHECK(Rte_Write_ppCtrlDcmTarget0_DcmTargetValues_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteDcmRoutineAck
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function acknowledge return for Diagnostic routine
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_RteAccess_WriteDcmRoutineAck_Param1 = TRUE;
/// \input Rte_Read_Dcm_RoutineControl_Param1.boRequestAckStatus = FALSE;
/// \input Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
/// \input Rte_Write_Dcm_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Write_Dcm_RoutineControl_Param1.boRequestAckStatus = TRUE
/// \output  Rte_Write_Dcm_RoutineControl_Param1.boRequestStatus = FALSE
/// \output  Rte_Read_Dcm_RoutineControl_HitCount = 1u 
/// \output  Rte_Write_Dcm_RoutineControl_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteDcmRoutineAck(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteDcmRoutineAck_Param1 = TRUE;
    Rte_Read_Dcm_RoutineControl_Param1.boRequestAckStatus = FALSE;
    Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    Rte_Write_Dcm_RoutineControl_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteDcmRoutineAck(CtrlDcm_RteAccess_WriteDcmRoutineAck_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_Dcm_RoutineControl_Param1.boRequestAckStatus, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_Dcm_RoutineControl_Param1.boRequestStatus, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Write_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write values in the DCM status port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = NULL_PTR;
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 7u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = NULL_PTR;
    Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1); 

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write values in the DCM status port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeFrozen;
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;

///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeUnavailable
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L= TRUE
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Init
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    tsCtrlDcm_DcmStatusParameters sParam = { CtrlDcm_eModeUnavailable, CtrlDcm_ePhase_Init, TRUE, TRUE, TRUE };
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam;
    Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeFrozen;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE, eDcmModeUnavailable, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE, eDcmPhase_Init, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write values in the DCM status port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeFrozen;
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;

///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeAvailable
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L= TRUE
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Adj
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    tsCtrlDcm_DcmStatusParameters sParam = { CtrlDcm_eModeAvailable, CtrlDcm_ePhase_Adj, TRUE, TRUE, TRUE };
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam;
    Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeFrozen;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE, eDcmModeAvailable, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE, eDcmPhase_Adj, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write values in the DCM status port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmPhase_Fail;
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeFrozen
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L= TRUE
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Fail
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    tsCtrlDcm_DcmStatusParameters sParam = { CtrlDcm_eModeFrozen, CtrlDcm_ePhase_Fail, TRUE, TRUE, TRUE };
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam;
    Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmPhase_Fail;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE, eDcmModeFrozen, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE, eDcmPhase_Fail, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write values in the DCM status port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmPhase_Fail;
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmModeFactory
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L= TRUE
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    tsCtrlDcm_DcmStatusParameters sParam = { CtrlDcm_eModeFactory, 3u, TRUE, TRUE, TRUE };
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam;
    Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE = eDcmPhase_Fail;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.eASL_MODE, eDcmModeFactory, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write values in the DCM status port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u
/// \input     Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L = FALSE;

///
///   - Expectations:
///
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L= TRUE
/// \output  Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 1u 
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase6(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    tsCtrlDcm_DcmStatusParameters sParam = { 5u, 3u, TRUE, TRUE, TRUE };
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1 = &sParam;
    Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L = FALSE;
    Rte_Write_CtrlDcm_StatusParameters_Port_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_Param1.boLvlAdjFunctionalFault_L, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Write_CtrlDcm_StatusParameters_Port_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that write values in the DCM status port
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(void)
{
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase1();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase2();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase3();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase4();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase5();
    Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port_TestCase6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads actual status DC Motor
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef = FALSE;
///
///   - Expectations:
/// \output CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef = FALSE
///
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef = FALSE;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0(&CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes actual status DC Motor
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef = TRUE
///
///   - Expectations:
/// \output  CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef = TRUE
///
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef = TRUE;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0(CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0_Param1.boDcmCommDef, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Get Dcm Routine Control Routine Status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Start;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmMovementToTop;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = eDcmRightActuator;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmDID = eDD06;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl = eDcmControl_Start
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = eDcmMovementToTop
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmSide =  eDcmRightActuator
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmDID = eDD06
/// \output Rte_Read_Dcm_RoutineControl_HitCount = 1u;
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Start;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmMovementToTop;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = eDcmRightActuator;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmDID = eDD06;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl, eDcmControl_Start, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest, eDcmMovementToTop, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmSide, eDcmRightActuator, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmDID, eDD06, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Get Dcm Routine Control Routine Status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Stop;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmMovementToBottom;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = eDcmLeftActuator;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmDID = 0xFFFF;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl = CtrlDcm_eDcmControl_Stop
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eMovementToBottom
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmSide =  CtrlDcm_eLeftActuator
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmDID = CtrlDcm_eInvalid
/// \output Rte_Read_Dcm_RoutineControl_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Stop;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmMovementToBottom;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = eDcmLeftActuator;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmDID = 0xFFFF;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl, CtrlDcm_eDcmControl_Stop, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest, CtrlDcm_eMovementToBottom, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmSide, CtrlDcm_eLeftActuator, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmDID, CtrlDcm_eInvalid, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Get Dcm Routine Control Routine Status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Results;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmMovementToZero;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = eDcmBothActuators;
/// \input Rte_Read_Dcm_RoutineControl_HitCount =0u;
///
///   - Expectations:
///
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl = CtrlDcm_eDcmControl_Results
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eMovementToZero
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmSide =  CtrlDcm_eBothActuators
/// \output Rte_Read_Dcm_RoutineControl_HitCount =1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Results;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmMovementToZero;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = eDcmBothActuators;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl, CtrlDcm_eDcmControl_Results, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest, CtrlDcm_eMovementToZero, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmSide, CtrlDcm_eBothActuators, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Get Dcm Routine Control Routine Status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Unknown;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmSequence1;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = 3u;
/// \input Rte_Read_Dcm_RoutineControl_HitCount=0u;
///
///   - Expectations:
///
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl = CtrlDcm_eDcmControl_Unknown
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eSequence1
/// \output Rte_Read_Dcm_RoutineControl_HitCount=1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = eDcmControl_Unknown;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmSequence1;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = 3u;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmControl, CtrlDcm_eDcmControl_Unknown, == );
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest, CtrlDcm_eSequence1, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Get Dcm Routine Control Routine Status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmSequence2;
/// \input Rte_Read_Dcm_RoutineControl_HitCount=0u;
///
///   - Expectations:
///
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eSequence2
/// \output     Rte_Read_Dcm_RoutineControl_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmSequence2;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest, CtrlDcm_eSequence2, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Get Dcm Routine Control Routine Status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmStop;
/// \input Rte_Read_Dcm_RoutineControl_HitCount=0u;
/// \input     CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eSequence;
///
///   - Expectations:
///
/// \output CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eStop
/// \output Rte_Read_Dcm_RoutineControl_HitCount =1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase6(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Dcm_RoutineControl_Param1.eDcmRequest = eDcmStop;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest = CtrlDcm_eMovementToZero;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(&CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_Param1.eDcmRequest, CtrlDcm_eStop, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that Get Dcm Routine Control Routine Status
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine()
{
    Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase1();
    Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase2();
    Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase3();
    Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase4();
    Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase5();
    Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine_TestCase6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RteAccess_MapParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the functionMapps the coding parameter in order to acces  in CtrlDcm
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CodM_Pitch_Para_HitCount            = 0u
/// \input Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid
/// 
///   - Expectations:
///
/// \output Rte_Read_CodM_Pitch_Para_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RteAccess_MapParams(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;

    //Step 3) Call FUT
    CtrlDcm_RteAccess_MapParams();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadMasterSignals_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads master signals
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_DcmDiagStatusR_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_Param1.eLevellingAdjustFaultR = eDiagLvl_Ok;
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = TRUE;
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_VALID;
/// \input CtrlDcm_nPosReq = 0.02;
/// \input CtrlDcm_boVehAttitudeInvalid = TRUE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
/// \input NvmBlockDeltaPwmPara.ucZeroLevProg = eDD06;
/// \input Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;
/// 
///   - Expectations:
///
/// \output CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = SIG_VALID
/// \output CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = FALSE
/// \output Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 1u
/// \output CtrlDcm_boVehAttitudeInvalid = FALSE
/// \output CtrlDcm_boTrainingState = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadMasterSignals_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_DcmDiagStatusR_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_DcmDiagStatusR_Param1.eLevellingAdjustFaultR = eDiagLvl_Ok;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = TRUE;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_DcmDiagStatusR_HitCount = 0u;
    Rte_Read_ppsAvacStat1Out_Port_Param1.State = SIG_VALID;
    CtrlDcm_nPosReq = 0.02;
    CtrlDcm_boVehAttitudeInvalid = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    Rte_Read_ppsAvacStat1Out_Port_Param1.Position[CtrlDcm_eMountedLeft].Ver = 0.01;
    NvmBlockDeltaPwmPara.ucZeroLevProg = eDD06;
    
    //Step 3) Call FUT
    CtrlDcm_ReadMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty, SIG_VALID, == );
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_DcmDiagStatusR_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_boVehAttitudeInvalid, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boTrainingState, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadMasterSignals_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads master signals
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
/// \input NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;

/// 
///   - Expectations:
///
/// \output CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE
/// \output CtrlDcm_boTrainingState = TRUE
/// \output Rte_Read_Pitch_PlausState_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadMasterSignals_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE;
    NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
    NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
    CtrlDcm_boTrainingState = FALSE;
    Rte_Read_Pitch_PlausState_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eSensorError, CtrlDcm_eHLS_NO_FAILURE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boTrainingState, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadMasterSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads master signals
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_ReadMasterSignals(void)
{
    Mt_CtrlDcm_ReadMasterSignals_TestCase1();
    Mt_CtrlDcm_ReadMasterSignals_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input      boRecoveryCheck = FALSE;
/// 
///   - Expectations:
///
/// \output boRecoveryCheck = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    boRecoveryCheck = FALSE;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boRecoveryCheck, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault = TRUE
/// \input         boRecoveryCheck  = TRUE
/// 
///   - Expectations:
///
/// \output boRecoveryCheck = FASLE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    boRecoveryCheck = TRUE;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boRecoveryCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault = TRUE
/// \input     boRecoveryCheck  = FALSE
/// 
///   - Expectations:
///
/// \output boRecoveryCheck = FASLE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    boRecoveryCheck = FALSE;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boRecoveryCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault = TRUE
/// \input     boRecoveryCheck  = FALSE
/// \input     LPTMR0_GetTimeElapsed_RetVal = UTILTIME_MSEC(CTRLDCM_CONFIG_TIME_THRESHOLD)
/// \input     LPTMR0_GetTimeElapsed_HitCount = 0u
/// 
///   - Expectations:
///
/// \output CtrlDcm_boLvlAdjHeadlampFault = FASLE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    boRecoveryCheck = FALSE;
    LPTMR0_GetTimeElapsed_RetVal = UTILTIME_MSEC(CTRLDCM_CONFIG_TIME_THRESHOLD);
    LPTMR0_GetTimeElapsed_HitCount=0u;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjHeadlampFault, FALSE, == );
    AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that verify for levelling adjust headlamp fault recovery
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery(void)
{
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase1();
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase2();
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase3();
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_TestCase4();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery for right side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
/// \input         boSlaveRecoveryCheck = FALSE;
/// 
///   - Expectations:
///
/// \output boSlaveRecoveryCheck = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    boSlaveRecoveryCheck = FALSE;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boSlaveRecoveryCheck, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery for right side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault_R = TRUE
/// \input         boSlaveRecoveryCheck  = TRUE
/// 
///   - Expectations:
///
/// \output boSlaveRecoveryCheck = FASLE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    boSlaveRecoveryCheck = TRUE;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boSlaveRecoveryCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery for right side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault_R = TRUE
/// \input     boSlaveRecoveryCheck  = FALSE
/// 
///   - Expectations:
///
/// \output boSlaveRecoveryCheck = FASLE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    boSlaveRecoveryCheck = FALSE;

    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boSlaveRecoveryCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault recovery for right side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_boLvlAdjHeadlampFault_R = TRUE
/// \input     boRecoveryCheck  = FALSE
/// \input     LPTMR0_GetTimeElapsed_RetVal = 2000000000u)
/// \input     LPTMR0_GetTimeElapsed_HitCount = 0u;

///   - Expectations:
///
/// \output CtrlDcm_boLvlAdjHeadlampFault_R = FASLE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    boSlaveRecoveryCheck = FALSE;
    LPTMR0_GetTimeElapsed_RetVal = 2000000000u;
    LPTMR0_GetTimeElapsed_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjHeadlampFault_R, FALSE, == );
    AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that verify for levelling adjust headlamp fault recovery for right side
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R(void)
{
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase1();
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase2();
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase3();
    Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R_TestCase4();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_sErrorStatus.boElecBAT = FALSE;
/// \input     CtrlDcm_sErrorStatus.boElecGND = FALSE;
/// \input         boErrorCheck = FALSE;
/// 
///   - Expectations:
///
/// \output boErrorCheck = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase1()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sErrorStatus.boElecBAT = FALSE;
    CtrlDcm_sErrorStatus.boElecGND = FALSE;
    boErrorCheck = FALSE;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boErrorCheck, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_sErrorStatus.boElecBAT = TRUE;
/// \input     CtrlDcm_sErrorStatus.boElecGND = TRUE;
/// \input     boErrorCheck = TRUE 
/// \input     LPTMR0_GetTimeElapsed_RetVal = 0u;
/// 
///   - Expectations:
///
/// \output boErrorCheck = FASLE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase2()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sErrorStatus.boElecBAT = TRUE;
    CtrlDcm_sErrorStatus.boElecGND = TRUE;
    boErrorCheck = TRUE;
    LPTMR0_GetTimeElapsed_RetVal = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boErrorCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_sErrorStatus.boElecBAT = TRUE;
/// \input     CtrlDcm_sErrorStatus.boElecGND = TRUE;
/// \input     boErrorCheck = FALSE 
/// \input     LPTMR0_GetTimeElapsed_RetVal = 0u;
/// \input     CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// 
///   - Expectations:
///
/// \output CtrlDcm_boLvlAdjHeadlampFault = FASLE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase3()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sErrorStatus.boElecBAT = TRUE;
    CtrlDcm_sErrorStatus.boElecGND = TRUE;
    LPTMR0_GetTimeElapsed_RetVal = 0u;
    boErrorCheck = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjHeadlampFault, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_sErrorStatus.boElecBAT = TRUE;
/// \input     CtrlDcm_sErrorStatus.boElecGND = TRUE;
/// \input     LPTMR0_GetTimeElapsed_RetVal = 200000000u
/// \input     CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input     LPTMR0_GetTimeElapsed_HitCount = 0u;
/// 
///   - Expectations:
///
/// \output CtrlDcm_boLvlAdjHeadlampFault = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase4()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sErrorStatus.boElecBAT = TRUE;
    CtrlDcm_sErrorStatus.boElecGND = TRUE;
    LPTMR0_GetTimeElapsed_RetVal = 200000000u;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    LPTMR0_GetTimeElapsed_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjHeadlampFault, TRUE, == );
    AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input     CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
/// \input     boSlaveErrorCheck = TRUE;
/// 
///   - Expectations:
///
/// \output boSlaveErrorCheck = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase5()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
    boSlaveErrorCheck = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boSlaveErrorCheck, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = TRUE;
/// \input boSlaveErrorCheck = TRUE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 0u;
/// 
///   - Expectations:
///
/// \output boSlaveErrorCheck = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase6()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = TRUE;
    boSlaveErrorCheck = TRUE;
    LPTMR0_GetTimeElapsed_RetVal = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boSlaveErrorCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input boSlaveErrorCheck = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 0u;
/// 
///   - Expectations:
///
/// \output CtrlDcm_boLvlAdjHeadlampFault_R = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase7()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    boSlaveErrorCheck = FALSE;
    LPTMR0_GetTimeElapsed_RetVal = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjHeadlampFault_R, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input boSlaveErrorCheck = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 300000000u;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
/// \input LPTMR0_GetTimeElapsed_HitCount = 0u;
/// 
///   - Expectations:
///
/// \output CtrlDcm_boLvlAdjHeadlampFault_R = TRUE
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase8()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    boSlaveErrorCheck = FALSE;
    LPTMR0_GetTimeElapsed_RetVal = 300000000u;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    LPTMR0_GetTimeElapsed_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadLvlAdjHeadlampFaultStatus();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjHeadlampFault_R, TRUE, == );
    AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that for levelling adjust headlamp fault
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus()
{
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase1();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase2();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase3();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase4();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase5();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase6();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase7();
    Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus_TestCase8();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_CondEnabled
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify if DC motor is enabled by coding data
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
/// 
///   - Expectations:
///
/// \output CtrlDcm_CondEnabled_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_CondEnabled(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    //Step 3) Call FUT
    CtrlDcm_CondEnabled_RetVal=CtrlDcm_CondEnabled();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_CondEnabled_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_RetVehIgnition
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function return ignition conditions fulfillment
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boConVehIgnition = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_RetVehIgnition_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_RetVehIgnition(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boConVehIgnition = TRUE;

    //Step 3) Call FUT
    CtrlDcm_RetVehIgnition_RetVal = CtrlDcm_RetVehIgnition();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_RetVehIgnition_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnboTrainingState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function requested operation from PWF, cont. movement or inscenation
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturnboTrainingState_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnboTrainingState(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReturnboTrainingState_RetVal = CtrlDcm_ReturnboTrainingState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturnboTrainingState_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturneSensorError
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns sensor error status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_FROZEN_FAILURE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturneSensorError_RetVal = CtrlDcm_eHLS_FROZEN_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturneSensorError(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eSensorError = CtrlDcm_eHLS_FROZEN_FAILURE;

    //Step 3) Call FUT
    CtrlDcm_ReturneSensorError_RetVal = CtrlDcm_ReturneSensorError();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturneSensorError_RetVal, CtrlDcm_eHLS_FROZEN_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnboLvlAdjFuncFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns levelling adjust functional fault status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturnboLvlAdjFuncFault_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnboLvlAdjFuncFault(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjFuncFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReturnboLvlAdjFuncFault_RetVal = CtrlDcm_ReturnboLvlAdjFuncFault();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturnboLvlAdjFuncFault_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnboSlaveLvlAdjFuncFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns levelling adjust functional fault status for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturnboSlaveLvlAdjFuncFault_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnboSlaveLvlAdjFuncFault(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReturnboSlaveLvlAdjFuncFault_RetVal = CtrlDcm_ReturnboSlaveLvlAdjFuncFault();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturnboSlaveLvlAdjFuncFault_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  returns levelling adjust headlamp fault status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturnboLvlAdjHeadlampFault_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReturnboLvlAdjHeadlampFault_RetVal = CtrlDcm_ReturnboLvlAdjHeadlampFault();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturnboLvlAdjHeadlampFault_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault_R
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  returns levelling adjust headlamp fault status for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturnboLvlAdjHeadlampFault_R_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault_R(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReturnboLvlAdjHeadlampFault_R_RetVal = CtrlDcm_ReturnboLvlAdjHeadlampFault_R();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturnboLvlAdjHeadlampFault_R_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReturnboExtTakeOver
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  returns takeover status needed for diag takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boDiagDcmOn = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_ReturnboExtTakeOver_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReturnboExtTakeOver(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boDiagDcmOn = TRUE;

    //Step 3) Call FUT
    CtrlDcm_ReturnboExtTakeOver_RetVal = CtrlDcm_ReturnboExtTakeOver();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_ReturnboExtTakeOver_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetSignalMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets CtrlDcm target source
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SetSignalMode_Param1 = eDcmSrc_DiagPos;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
///
///   - Expectations:
///
/// \output CtrlDcm_SignalSrc = eDcmSrc_DiagPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetSignalMode(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SetSignalMode_Param1 = eDcmSrc_DiagPos;
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;

    //Step 3) Call FUT
    CtrlDcm_SetSignalMode(CtrlDcm_SetSignalMode_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_DiagPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_SetSignalMode_Param1 = eDcmSrc_SleepPos;
///
///   - Expectations:
///
/// \output CtrlDcm_boStop = TRUE
/// \output NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    NM_GetMode_HitCount = 0u;
    CtrlDcm_SignalSrc = eDcmSrc_SleepPos;

    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, TRUE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
/// \inputNM_GetMode_Param1 = LIMP_HOME_MODE
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_boStop = FALSE;
///
///   - Expectations:
///
/// \output CtrlDcm_boStop = TRUE
/// \output NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_GetTgtPos_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
    NM_GetMode_Param1 = LIMP_HOME_MODE;
    NM_GetMode_HitCount = 0u;
    CtrlDcm_boStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, TRUE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
/// \inputNM_GetMode_Param1 = VEILLE
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_boStop = TRUE;
///
///   - Expectations:
///
/// \output CtrlDcm_boStop = FALSE
/// \output NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
    NM_GetMode_Param1 = VEILLE;
    NM_GetMode_HitCount = 0u;
    CtrlDcm_boStop = TRUE;

    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, FALSE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
/// \input    CtrlDcm_nTgtPos = 1u;
///
///   - Expectations:
///
/// \output CtrlDcm_nTgtPos = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_nTgtPos = 1u;
    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_nTgtPos, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
/// \input CtrlDcm_nLastPosReq = 100u
/// input CtrlDcm_boStop = TRUE;
/// input CtrlDcm_nTgtPos = 0u;
///
///   - Expectations:
///
/// \output CtrlDcm_boStop = FALSE
/// \output CtrlDcm_nTgtPos = -32u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
    CtrlDcm_nLastPosReq = 100u;
    CtrlDcm_boStop = TRUE;
    CtrlDcm_nTgtPos = 0u;

    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_nTgtPos, -32u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
/// \input CtrlDcm_nLastPosReq = -100u
/// \input snPosMinASL = -4u
/// \input CtrlDcm_boStop = TRUE
///
///   - Expectations:
///
/// \output CtrlDcm_boStop = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos_TestCase6(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
    CtrlDcm_nLastPosReq = -100u;
    snPosMinASL = -4u;
    CtrlDcm_boStop = TRUE;

    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function Calculate Pos, Tmin and Stop based on selected sourc
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_SignalSrc = 4u
/// \input snPosMinASL = 4u
/// \input snPosMaxASL = -20u
/// \input CtrlDcm_boStop = FALSE;
///
///   - Expectations:
///
/// \output CtrlDcm_boStop = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos_TestCase7(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_SignalSrc = 4u;
    snPosMinASL = 4u;
    snPosMaxASL = -20u;
    CtrlDcm_boStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_GetTgtPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_GetTgtPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that calculate Pos, Tmin and Stop based on selected sourc
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_GetTgtPos(void)
{
    Mt_CtrlDcm_GetTgtPos_TestCase1();
    Mt_CtrlDcm_GetTgtPos_TestCase2();
    Mt_CtrlDcm_GetTgtPos_TestCase3();
    Mt_CtrlDcm_GetTgtPos_TestCase4();
    Mt_CtrlDcm_GetTgtPos_TestCase5();
    Mt_CtrlDcm_GetTgtPos_TestCase6();
    Mt_CtrlDcm_GetTgtPos_TestCase7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadCommonSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read common signals for both slave and master ecu
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
/// \input Rte_Read_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
/// \input Rte_Read_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
/// \input CtrlDcm_sErrorStatus.boElecBAT = FALSE;
/// \input CtrlDcm_sErrorStatus.boElecGND = TRUE;
/// \input Rte_Read_CddDcm_ErrorStatus_HitCount = 0u;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty == CtrlDcm_SIG_INVALID;
/// \input CtrlDcm_sErrorStatus.boElecBAT = FALSE;
/// \input CtrlDcm_sErrorStatus.boElecGND = FALSE;
///
///   - Expectations:
///
/// \output CtrlDcm_boConVehIgnition = TRUE
/// \output CtrlDcm_boPowertrainActive = FALSE
/// \output CtrlDcm_sErrorStatus.boElecBAT = TRUE
/// \output CtrlDcm_sErrorStatus.boElecGND  = FALSE
/// \output Rte_Read_CddDcm_ErrorStatus_HitCount = 1u
/// \output CtrlDcm_boLvlAdjFuncFault = TRUE
/// \output boErrorCheck = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadCommonSignals(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
    Rte_Read_CddDcm_ErrorStatus_Param1.boElecBAT = TRUE;
    Rte_Read_CddDcm_ErrorStatus_Param1.boElecGND = FALSE;
    CtrlDcm_sErrorStatus.boElecBAT = FALSE;
    CtrlDcm_sErrorStatus.boElecGND = TRUE;
    Rte_Read_CddDcm_ErrorStatus_HitCount = 0u;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_sLevellingDiagStatusFromRightToLeft.eSigQty == CtrlDcm_SIG_INVALID;
    CtrlDcm_sErrorStatus.boElecBAT = FALSE;
    CtrlDcm_sErrorStatus.boElecGND = FALSE;

    //Step 3) Call FUT
    CtrlDcm_ReadCommonSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boConVehIgnition, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boPowertrainActive, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_sErrorStatus.boElecBAT, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_sErrorStatus.boElecGND, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_CddDcm_ErrorStatus_HitCount, 1u, == );
    AL_UNITTEST_CHECK(CtrlDcm_boLvlAdjFuncFault, TRUE, == );
    AL_UNITTEST_CHECK(boErrorCheck, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagDcmTakeOver_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the takeover of the DC motor using the diag routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
/// \input Rte_Read_SysMon_VehNetState_HitCount=0u
///
///   - Expectations:
///
/// \output  CtrlDcm_boDiagDcmOn = FALSE
/// \output      Rte_Read_SysMon_VehNetState_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DiagDcmTakeOver_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_DiagDcmTakeOver();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boDiagDcmOn, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagDcmTakeOver_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function takeover of the DC motor using the diag routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
/// \input Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = FALSE;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Results;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_boDiagDcmOn = FALSE
/// \output  CtrlDcm_boStartSequence = TRUE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
/// \output  Rte_Read_Dcm_RoutineControl_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DiagDcmTakeOver_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
    Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = FALSE;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Results;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_DiagDcmTakeOver();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boDiagDcmOn, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boStartSequence, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagDcmTakeOver_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function takeover of the DC motor using the diag routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
/// \input Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = FALSE;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Results;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_boDiagDcmOn = FALSE
/// \output  CtrlDcm_boStartSequence = TRUE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
/// \output  Rte_Read_Dcm_RoutineControl_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DiagDcmTakeOver_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
    Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Start;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_DiagDcmTakeOver();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boDiagDcmOn, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boStartSequence, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagDcmTakeOver_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function takeover of the DC motor using the diag routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
/// \input Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Start;
/// \input Rte_Read_Dcm_RoutineControl_Param1.ucStartSequence = 1u;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_boStartSequence = TRUE
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
/// \output  Rte_Read_Dcm_RoutineControl_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DiagDcmTakeOver_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
    Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Start;
    Rte_Read_Dcm_RoutineControl_Param1.ucStartSequence = 1u;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_DiagDcmTakeOver();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStartSequence, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagDcmTakeOver_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function takeover of the DC motor using the diag routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
/// \input Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
/// \input Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Stop;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_Dcm_RoutineControl_HitCount = 0u;
/// \input CtrlDcm_boDiagDcmOn = TRUE;
/// \input CtrlDcm_boStartSequence = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_boDiagDcmOn = FALSE
/// \output  CtrlDcm_boStartSequence = TRUE
/// \output  Rte_Read_Dcm_RoutineControl_Param1.eDcmSide = CtrlDcm_eBothActuators
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u
/// \output  Rte_Read_Dcm_RoutineControl_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DiagDcmTakeOver_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
    Rte_Read_Dcm_RoutineControl_Param1.boRequestStatus = TRUE;
    Rte_Read_Dcm_RoutineControl_Param1.eDcmControl = CtrlDcm_eDcmControl_Stop;
    Rte_Read_SysMon_VehNetState_HitCount = 0u;
    Rte_Read_Dcm_RoutineControl_HitCount = 0u;
    CtrlDcm_boDiagDcmOn = TRUE;
    CtrlDcm_boStartSequence = FALSE;

    //Step 3) Call FUT
    CtrlDcm_DiagDcmTakeOver();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boDiagDcmOn, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boStartSequence, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_Param1.eDcmSide, CtrlDcm_eBothActuators, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_Dcm_RoutineControl_HitCount, 2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagDcmTakeOver
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that takeover of the DC motor using the diag routine control
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_DiagDcmTakeOver()
{
    Mt_CtrlDcm_DiagDcmTakeOver_TestCase1();
    Mt_CtrlDcm_DiagDcmTakeOver_TestCase2();
    Mt_CtrlDcm_DiagDcmTakeOver_TestCase3();
    Mt_CtrlDcm_DiagDcmTakeOver_TestCase4();
    Mt_CtrlDcm_DiagDcmTakeOver_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetDiagPos_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function   set DC motor position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eDD06;
/// \input CtrlDcm_sDcmControlRequest.ucPosRequest = 800u;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
/// \input CtrlDcm_nDiagPos = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_DiagPos
/// \output  CtrlDcm_nDiagPos = -240u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetDiagPos_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eDD06;
    CtrlDcm_sDcmControlRequest.ucPosRequest = 8u;
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
    CtrlDcm_nDiagPos = 0u;
    //Step 3) Call FUT
    CtrlDcm_SetDiagPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_DiagPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_nDiagPos, -360u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetDiagPos_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function   set DC motor position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eInvalid;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_DiagPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetDiagPos_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eInvalid;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_SetDiagPos();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_DiagPos, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SetDiagPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that set DC motor position for routine control
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SetDiagPos(void)
{
    Mt_CtrlDcm_SetDiagPos_TestCase1();
    Mt_CtrlDcm_SetDiagPos_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DiagRoutineControl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function set DC motor position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eInvalid;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_DiagPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DiagRoutineControl(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eInvalid;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_DiagRoutineControl();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_DiagPos, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteMasterSignals_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from master 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boIgnitionNeeded = TRUE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_TgtAll.sDcmTarget.boStop = TRUE
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteMasterSignals_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boIgnitionNeeded = TRUE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveSafetyPos = TRUE;
    CtrlDcm_TgtAll.sDcmTarget.boStop = FALSE;
    CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive;

    //Step 3) Call FUT
    CtrlDcm_WriteMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_TgtAll.sDcmTarget.boStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl, CtrlDcm_eSigneConsigneSiteD_Negativ, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteMasterSignals_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from master 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
/// \input CtrlDcm_boStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
/// \input CtrlDcm_nLastPosReq = 1u;
/// \input CtrlDcm_TgtAll.sDcmTarget.boStop = TRUE;
/// \input CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 1u;
///
///   - Expectations:
///
/// \output  CtrlDcm_TgtAll.sDcmTarget.boStop = FALSE
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteMasterSignals_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boIgnitionNeeded = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
    CtrlDcm_boStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;
    CtrlDcm_nLastPosReq = 1u;
    CtrlDcm_TgtAll.sDcmTarget.boStop = TRUE;
    CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 1u;

    //Step 3) Call FUT
    CtrlDcm_WriteMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_TgtAll.sDcmTarget.boStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteMasterSignals_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from master 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveSafetyPos = FALSE;
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
/// \input CtrlDcm_nPosReq = 1u;
///
///   - Expectations:
///
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteMasterSignals_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveSafetyPos = FALSE;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boIgnitionNeeded = FALSE;
    CtrlDcm_nPosReq = 1u;

    //Step 3) Call FUT
    CtrlDcm_WriteMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl, CtrlDcm_eSigneConsigneSiteD_Positive, == );
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteMasterSignals_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from master 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
/// \input CtrlDcm_nPosReq = -1u;
///
///   - Expectations:
///
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteMasterSignals_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boIgnitionNeeded = FALSE;
    CtrlDcm_nPosReq = -1u;

    //Step 3) Call FUT
    CtrlDcm_WriteMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdSignLvl, CtrlDcm_eSigneConsigneSiteD_Negativ, == );
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteMasterSignals_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from master 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
/// \input CtrlDcm_nPosReq = -1u;
/// \input     nSafetyPos = -32u;
///
///   - Expectations:
///
/// \output  CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty = CtrlDcm_SIG_VALID
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteMasterSignals_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boSlaveStop = TRUE;
    CtrlDcm_boIgnitionNeeded = FALSE;
    CtrlDcm_nPosReq = -1u;
    nSafetyPos = -32u;

    //Step 3) Call FUT
    CtrlDcm_WriteMasterSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingSignalsFromLeftToRight.eSigQty, CtrlDcm_SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteMasterSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that writes signals from master 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteMasterSignals(void)
{
    Mt_CtrlDcm_WriteMasterSignals_TestCase1();
    Mt_CtrlDcm_WriteMasterSignals_TestCase2();
    Mt_CtrlDcm_WriteMasterSignals_TestCase3();
    Mt_CtrlDcm_WriteMasterSignals_TestCase4();
    Mt_CtrlDcm_WriteMasterSignals_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteSlaveSignals_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boIgnitionNeeded = TRUE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_TgtAll.sDcmTarget.nPosition = -32u;
///
///   - Expectations:
///
/// \output  CtrlDcm_TgtAll.sDcmTarget.boStop = TRUE
/// \output  CtrlDcm_nLastPosReq = -32u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteSlaveSignals_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boIgnitionNeeded = TRUE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_TgtAll.sDcmTarget.nPosition = -32u;

    //Step 3) Call FUT
    CtrlDcm_WriteSlaveSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_TgtAll.sDcmTarget.boStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_nLastPosReq, -32u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteSlaveSignals_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes signals from slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
/// \input CtrlDcm_sErrorStatus.boElecBAT = FALSE;
/// \input CtrlDcm_sErrorStatus.boElecGND = FALSE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_TgtAll.sDcmTarget.boStop = FALSE
/// \output  CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteSlaveSignals_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boIgnitionNeeded = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
    CtrlDcm_sErrorStatus.boElecBAT = FALSE;
    CtrlDcm_sErrorStatus.boElecGND = FALSE;
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_boConVehIgnition = FALSE;

    //Step 3) Call FUT
    CtrlDcm_WriteSlaveSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_TgtAll.sDcmTarget.boStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteSlaveSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that writes signals from slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteSlaveSignals(void)
{
    Mt_CtrlDcm_WriteSlaveSignals_TestCase1();
    Mt_CtrlDcm_WriteSlaveSignals_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadSlaveSignals_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read slave signals
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 1u;
/// \input CtrlDcm_nPosReq = 1u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_nPosReq = 0u
/// \output  CtrlDcm_sLevellingDiagStatusFromRightToLeft.boDiagLvlR = FALSE
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadSlaveSignals_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = 1u;
    CtrlDcm_nPosReq = 1u;
    Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ReadSlaveSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_nPosReq, 0u, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadSlaveSignals_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read slave signals
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = -1u;
/// \input CtrlDcm_nPosReq = 1u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_nPosReq = 0u
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ReadSlaveSignals_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;
    Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdPosLvl.unRCmdPosLvl = -1u;
    Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
    CtrlDcm_nPosReq = 1u;

    //Step 3) Call FUT
    CtrlDcm_ReadSlaveSignals();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_nPosReq, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ReadSlaveSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that read slave signals
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_ReadSlaveSignals()
{
    Mt_CtrlDcm_ReadSlaveSignals_TestCase1();
    Mt_CtrlDcm_ReadSlaveSignals_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Frozen_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from assembly to frozen
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Assembly_To_Frozen_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Frozen_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Transition_Assembly_To_Frozen_RetVal = CtrlDcm_Transition_Assembly_To_Frozen();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Assembly_To_Frozen_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Frozen_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from assembly to frozen
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Assembly_To_Frozen_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Frozen_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;

    //Step 3) Call FUT
    CtrlDcm_Transition_Assembly_To_Frozen_RetVal = CtrlDcm_Transition_Assembly_To_Frozen();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Assembly_To_Frozen_RetVal, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Frozen
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the  transition check function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_Transition_Assembly_To_Frozen(void)
{
    Mt_CtrlDcm_Transition_Assembly_To_Frozen_TestCase1();
    Mt_CtrlDcm_Transition_Assembly_To_Frozen_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Factory_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from assembly to factory
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Assembly_To_Factory_RetVal = TRUE
/// \output      Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Factory_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Transition_Assembly_To_Factory_RetVal = CtrlDcm_Transition_Assembly_To_Factory();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Assembly_To_Factory_RetVal, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Factory_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from assembly to factory
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Assembly_To_Factory_RetVal = FALSE
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount=1u
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_Transition_Assembly_To_Factory_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
    CtrlDcm_boTrainingState = TRUE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Transition_Assembly_To_Factory_RetVal = CtrlDcm_Transition_Assembly_To_Factory();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Assembly_To_Factory_RetVal, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount , 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Factory
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the  transition check function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Factory(void)
{
    Mt_CtrlDcm_Transition_Assembly_To_Factory_TestCase1();
    Mt_CtrlDcm_Transition_Assembly_To_Factory_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Unavailable_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from assembly to unavailable
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input     Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Assembly_To_Unavailable_RetVal = FALSE
/// \output      Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Unavailable_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid;
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boConVehIgnition = TRUE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Transition_Assembly_To_Unavailable_RetVal = CtrlDcm_Transition_Assembly_To_Unavailable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Assembly_To_Unavailable_RetVal, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Unavailable_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from assembly to unavailable
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Assembly_To_Unavailable_RetVal = TRUE
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount=1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Unavailable_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boConVehIgnition = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Transition_Assembly_To_Unavailable_RetVal = CtrlDcm_Transition_Assembly_To_Unavailable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Assembly_To_Unavailable_RetVal, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Assembly_To_Unavailable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from assembly to unavailable
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Assembly_To_Unavailable(void)
{
    Mt_CtrlDcm_Transition_Assembly_To_Unavailable_TestCase1();
    Mt_CtrlDcm_Transition_Assembly_To_Unavailable_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Customer_To_Unavailable_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from customer to unavailable
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boConVehIgnition = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Customer_To_Unavailable_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Customer_To_Unavailable_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boConVehIgnition = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Customer_To_Unavailable_RetVal = CtrlDcm_Transition_Customer_To_Unavailable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Customer_To_Unavailable_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Customer_To_Unavailable_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from customer to unavailable
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boConVehIgnition = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Customer_To_Unavailable_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Customer_To_Unavailable_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boConVehIgnition = TRUE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Customer_To_Unavailable_RetVal = CtrlDcm_Transition_Customer_To_Unavailable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Customer_To_Unavailable_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Customer_To_Unavailable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from customer to unavailable
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Customer_To_Unavailable(void)
{
    Mt_CtrlDcm_Transition_Customer_To_Unavailable_TestCase1();
    Mt_CtrlDcm_Transition_Customer_To_Unavailable_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Customer_To_Available_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from customer to available
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Customer_To_Available_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Customer_To_Available_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boConVehIgnition = TRUE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Customer_To_Available_RetVal = CtrlDcm_Transition_Customer_To_Available();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Customer_To_Available_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Customer_To_Available_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from customer to available
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Customer_To_Available_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Customer_To_Available_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boConVehIgnition = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Customer_To_Available_RetVal = CtrlDcm_Transition_Customer_To_Available();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Customer_To_Available_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Customer_To_Available
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from customer to available
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Customer_To_Available(void)
{
    Mt_CtrlDcm_Transition_Customer_To_Available_TestCase1();
    Mt_CtrlDcm_Transition_Customer_To_Available_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseInit_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the behavior in case of state Init
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
/// \input CtrlDcm_boDiagLvl = TRUE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = FALSE
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_State.boEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseInit_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_NormalPos;
    CtrlDcm_boDiagLvl = TRUE;
    CtrlDcm_boSlaveStop = FALSE;
    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseInit();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, FALSE,== );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseInit_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the behavior in case of state Init
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = FALSE
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_State.boEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseInit_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = FALSE;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseInit();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the behavior in case of state Init
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseInit(void)
{
    Mt_CtrlDcm_StateMachine_PhaseInit_TestCase1();
    Mt_CtrlDcm_StateMachine_PhaseInit_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseAdj_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the behavior in case of adjustment state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boDiagLvl = TRUE;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_NormalPos
/// \output  CtrlDcm_boDiagLvl = FALSE
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
/// \output  CtrlDcm_State.boEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseAdj_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boDiagLvl = TRUE;
    CtrlDcm_boSlaveStop = TRUE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseAdj();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_NormalPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseAdj_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the behavior in case of adjustment state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseAdj_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = FALSE;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseAdj();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseAdj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the  behavior in case of adjustment state
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseAdj(void)
{
    Mt_CtrlDcm_StateMachine_PhaseAdj_TestCase1();
    Mt_CtrlDcm_StateMachine_PhaseAdj_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DetectMode_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects main mode of DC motor control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output      Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectMode_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_DetectMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMainMode, CtrlDcm_eModeAssembly, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DetectMode_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects main mode of DC motor control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectMode_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_DetectMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMainMode, CtrlDcm_eModeCustomer, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseAdj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that detects main mode of DC motor control
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectMode(void)
{
    Mt_CtrlDcm_DetectMode_TestCase1();
    Mt_CtrlDcm_DetectMode_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ResetDcmState_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that function verify if DC motor was previously activated and it resets the state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
///
///   - Expectations:
///
/// \output  boFirstEntry = TRUE
/// \output  CtrlDcm_State.ePhase = CtrlDcm_ePhase_Init
/// \output  CtrlDcm_State.boEntry = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ResetDcmState_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    boFirstEntry = TRUE;
    CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;

    //Step 3) Call FUT
    CtrlDcm_ResetDcmState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boFirstEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.ePhase, CtrlDcm_ePhase_Init, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ResetDcmState_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that function verify if DC motor was previously activated and it resets the state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.ePhase = CtrlDcm_ePhase_Init;
///
///   - Expectations:
///
/// \output  boFirstEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ResetDcmState_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    boFirstEntry = FALSE;
    CtrlDcm_State.ePhase = CtrlDcm_ePhase_Init;

    //Step 3) Call FUT
    CtrlDcm_ResetDcmState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boFirstEntry, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ResetDcmState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that verify if DC motor was previously activated and it resets the state 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ResetDcmState(void)
{
    Mt_CtrlDcm_ResetDcmState_TestCase1();
    Mt_CtrlDcm_ResetDcmState_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Adj_To_Fail_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from adjustment to fail for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Adj_To_Fail_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal=CtrlDcm_Transition_Adj_To_Fail_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Adj_To_Fail_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from adjustment to fail for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Adj_To_Fail_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal = CtrlDcm_Transition_Adj_To_Fail_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Adj_To_Fail_Slave_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Adj_To_Fail_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from adjustment to fail for slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_Transition_Adj_To_Fail_Slave(void)
{
    Mt_CtrlDcm_Transition_Adj_To_Fail_Slave_TestCase1();
    Mt_CtrlDcm_Transition_Adj_To_Fail_Slave_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Fail_To_Adj_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from fail to adjustment for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Fail_To_Adj_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal = CtrlDcm_Transition_Fail_To_Adj_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Fail_To_Adj_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from fail to adjustment for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Fail_To_Adj_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    //Step 3) Call FUT
    CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal = CtrlDcm_Transition_Fail_To_Adj_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Fail_To_Adj_Slave_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Fail_To_Adj_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from fail to adjustment for slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Fail_To_Adj_Slave(void)
{
    Mt_CtrlDcm_Transition_Fail_To_Adj_Slave_TestCase1();
    Mt_CtrlDcm_Transition_Fail_To_Adj_Slave_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Adj_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to adjustment for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault               = FALSE
/// \input CtrlDcm_boLvlAdjHeadlampFault                = FALSE
/// \input CtrlDcm_boPowertrainActive                   = TRUE
/// \input Rte_Read_CodM_Pitch_Para_HitCount            = 0u
/// \input Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataValid
/// \input NvmBlockDeltaPwmPara.eASL_Present            = eASL_Present
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Adj_Slave_RetVal = TRUE
/// \output  Rte_Read_CodM_Pitch_Para_HitCount           = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Adj_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault               = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault                = FALSE;
    CtrlDcm_boPowertrainActive                   = TRUE;
    Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    NvmBlockDeltaPwmPara.eASL_Present            = eASL_Present;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Adj_Slave_RetVal = CtrlDcm_Transition_Init_To_Adj_Slave();
    
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Adj_Slave_RetVal, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount          ,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Adj_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to adjustment for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Adj_Slave_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Adj_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boPowertrainActive = FALSE;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
    Rte_Read_CodM_Pitch_Para_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Adj_Slave_RetVal = CtrlDcm_Transition_Init_To_Adj_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Adj_Slave_RetVal, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Adj_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from init to adjustment for slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Adj_Slave(void)
{
    Mt_CtrlDcm_Transition_Init_To_Adj_Slave_TestCase1();
    Mt_CtrlDcm_Transition_Init_To_Adj_Slave_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Fail_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to fail for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Fail_Slave_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Fail_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Fail_Slave_RetVal = CtrlDcm_Transition_Init_To_Fail_Slave();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Fail_Slave_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Fail_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to fail for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Adj_Slave_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Fail_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Fail_Slave_RetVal = CtrlDcm_Transition_Init_To_Fail_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Adj_Slave_RetVal, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Fail_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from init to fail for slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Fail_Slave(void)
{
    Mt_CtrlDcm_Transition_Init_To_Fail_Slave_TestCase1();
    Mt_CtrlDcm_Transition_Init_To_Fail_Slave_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DetectSlaveSubMode_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detect submode of slave mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectSlaveSubMode_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boConVehIgnition = FALSE;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_DetectSlaveSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DetectSlaveSubMode_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detect submode of slave mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectSlaveSubMode_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_DetectSlaveSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeAvailable, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_DetectSlaveSubMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that detect submode of slave mode
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_DetectSlaveSubMode(void)
{
    Mt_CtrlDcm_DetectSlaveSubMode_TestCase1();
    Mt_CtrlDcm_DetectSlaveSubMode_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseInit_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the behavior in case of state Init for Slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_State.boEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseInit_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = TRUE;
    CtrlDcm_SignalSrc = eDcmSrc_SafetyPos;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseInit_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseInit_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the behavior in case of state Init for Slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseInit_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = FALSE;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseInit_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseInit_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the behavior in case of state Init for Slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_StateMachine_PhaseInit_Slave(void)
{
    Mt_CtrlDcm_StateMachine_PhaseInit_Slave_TestCase1();
    Mt_CtrlDcm_StateMachine_PhaseInit_Slave_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eFreeze;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eFreeze;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior_Slave(CtrlDcm_HandleFailStateBehavior_Slave_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eSafety;
/// \inpute CtrlDcm_SignalSrc = eDcmSrc_DiagPos
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eSafety;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior_Slave(CtrlDcm_HandleFailStateBehavior_Slave_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SafetyPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eFreeze_IgnitionNeeded;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boIgnitionNeeded = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eFreeze_IgnitionNeeded;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boIgnitionNeeded = FALSE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior_Slave(CtrlDcm_HandleFailStateBehavior_Slave_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boIgnitionNeeded, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eContinue;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_boIgnitionNeeded = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Slave_Param1 = CtrlDcm_eContinue;
    CtrlDcm_boIgnitionNeeded = TRUE;
    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior_Slave(CtrlDcm_HandleFailStateBehavior_Slave_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boIgnitionNeeded, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the Handle Fail state behavior for Slave control
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_HandleFailStateBehavior_Slave(void)
{
    Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase1();
    Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase2();
    Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase3();
    Mt_CtrlDcm_HandleFailStateBehavior_Slave_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boSlaveLvlAdjFuncFault = TRUE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SafetyPos, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_Slave_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_Slave_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boIgnitionNeeded = FALSE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState_Slave();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boIgnitionNeeded, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_Slave_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the Handle Fail state behavior for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_Slave_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the Handle Fail state behavior for Slave 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_HandleFailState_Slave()
{
    Mt_CtrlDcm_HandleFailState_Slave_TestCase1();
    Mt_CtrlDcm_HandleFailState_Slave_TestCase2();
    Mt_CtrlDcm_HandleFailState_Slave_TestCase3();
    Mt_CtrlDcm_HandleFailState_Slave_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseFail_Slave_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the State Machine: behavior in case of state Err for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = FALSE
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseFail_Slave_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseFail_Slave();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseFail_Slave_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the State Machine: behavior in case of state Err for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = FALSE
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseFail_Slave_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_boSlaveLvlAdjFuncFault = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseFail_Slave();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseFail_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the State Machine: behavior in case of state Err for Slave
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseFail_Slave(void)
{
    Mt_CtrlDcm_StateMachine_PhaseFail_Slave_TestCase1();
    Mt_CtrlDcm_StateMachine_PhaseFail_Slave_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Adj_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to adjustment for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault                = FALSE
/// \input CtrlDcm_boLvlAdjHeadlampFault_R              = FALSE
/// \input CtrlDcm_boLvlAdjFuncFault                    = FALSE
/// \input CtrlDcm_boPowertrainActive                   = TRUE
/// \input Rte_Read_CodM_Pitch_Para_HitCount            = 0u
/// \input Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataValid
/// \input NvmBlockDeltaPwmPara.eASL_Present            = eASL_Present
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Adj_RetVal = TRUE
/// \output  Rte_Read_CodM_Pitch_Para_HitCount     = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Adj_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault                = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R              = FALSE;
    CtrlDcm_boLvlAdjFuncFault                    = FALSE;
    CtrlDcm_boPowertrainActive                   = TRUE;
    Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
    NvmBlockDeltaPwmPara.eASL_Present            = eASL_Present;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Adj_RetVal = CtrlDcm_Transition_Init_To_Adj();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Adj_RetVal, TRUE, == );
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount    ,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Adj_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to adjustment for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault                = TRUE
/// \input CtrlDcm_boLvlAdjHeadlampFault_R              = TRUE
/// \input CtrlDcm_boLvlAdjFuncFault                    = TRUE
/// \input CtrlDcm_boPowertrainActive                   = FALSE
/// \input Rte_Read_CodM_Pitch_Para_HitCount            = 0u
/// \input Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Adj_RetVal = FALSE
/// \output  Rte_Read_CodM_Pitch_Para_HitCount     = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Adj_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault                = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault_R              = TRUE;
    CtrlDcm_boLvlAdjFuncFault                    = TRUE;
    CtrlDcm_boPowertrainActive                   = FALSE;
    Rte_Read_CodM_Pitch_Para_HitCount            = 0u;
    Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Adj_RetVal = CtrlDcm_Transition_Init_To_Adj();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Adj_RetVal, FALSE, == );
    AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount    ,    1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Adj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from init to adjustment for master
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Adj(void)
{
    Mt_CtrlDcm_Transition_Init_To_Adj_TestCase1();
    Mt_CtrlDcm_Transition_Init_To_Adj_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Fail_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to fail for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_STORED_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Fail_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Fail_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_STORED_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Fail_RetVal = CtrlDcm_Transition_Init_To_Fail();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Fail_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Fail_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from init to fail for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_FROZEN_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Init_To_Fail_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Fail_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_FROZEN_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Init_To_Fail_RetVal = CtrlDcm_Transition_Init_To_Fail();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Init_To_Fail_RetVal, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Init_To_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from init to fail for master
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Init_To_Fail(void)
{
    Mt_CtrlDcm_Transition_Init_To_Fail_TestCase1();
    Mt_CtrlDcm_Transition_Init_To_Fail_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Adj_To_Fail_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from adjustment to fail for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_SENSOR_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Adj_To_Fail_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Adj_To_Fail_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_SENSOR_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Adj_To_Fail_RetVal = CtrlDcm_Transition_Adj_To_Fail();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Adj_To_Fail_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Adj_To_Fail_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from adjustment to fail for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_STORED_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Adj_To_Fail_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Adj_To_Fail_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_STORED_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Adj_To_Fail_RetVal = CtrlDcm_Transition_Adj_To_Fail();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Adj_To_Fail_RetVal, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Adj_To_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from adjustment to fail for master
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Adj_To_Fail(void)
{
    Mt_CtrlDcm_Transition_Adj_To_Fail_TestCase1();
    Mt_CtrlDcm_Transition_Adj_To_Fail_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Fail_To_Adj_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from fail to adjustment for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
/// \input CtrlDcm_boPowertrainActive = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Fail_To_Adj_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Fail_To_Adj_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Fail_To_Adj_RetVal = CtrlDcm_Transition_Fail_To_Adj();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Fail_To_Adj_RetVal, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Fail_To_Adj_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function can do the transition from fail to adjustment for master
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_STORED_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_Transition_Fail_To_Adj_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Fail_To_Adj_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_STORED_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Transition_Fail_To_Adj_RetVal = CtrlDcm_Transition_Fail_To_Adj();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_Transition_Fail_To_Adj_RetVal, FALSE, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Transition_Fail_To_Adj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function can do the transition from fail to adjustment for master
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Transition_Fail_To_Adj(void)
{
    Mt_CtrlDcm_Transition_Fail_To_Adj_TestCase1();
    Mt_CtrlDcm_Transition_Fail_To_Adj_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that Handle Fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eFreeze;
/// \input CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eFreeze;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eFreeze;
    CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eFreeze;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior(CtrlDcm_HandleFailStateBehavior_Param1, CtrlDcm_HandleFailStateBehavior_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that Handle Fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eSafety;
/// \input CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eSafety;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eSafety;
    CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eSafety;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior(CtrlDcm_HandleFailStateBehavior_Param1, CtrlDcm_HandleFailStateBehavior_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SafetyPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that Handle Fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eSafety_IgnitionNeeded;
/// \input CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eSafety_IgnitionNeeded;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boIgnitionNeeded = FALSE;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boSlaveSafetyPos = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
/// \output  CtrlDcm_boIgnitionNeeded = TRUE
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eSafety_IgnitionNeeded;
    CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eSafety_IgnitionNeeded;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boIgnitionNeeded = FALSE;
    CtrlDcm_boSlaveStop = TRUE;
    CtrlDcm_boSlaveSafetyPos = FALSE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior(CtrlDcm_HandleFailStateBehavior_Param1, CtrlDcm_HandleFailStateBehavior_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SafetyPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boIgnitionNeeded, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that Handle Fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eContinue;
/// \input CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eContinue;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_NormalPos
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eContinue;
    CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eContinue;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = TRUE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior(CtrlDcm_HandleFailStateBehavior_Param1, CtrlDcm_HandleFailStateBehavior_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_NormalPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that Handle Fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eFreeze_IgnitionNeeded;
/// \input CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eFreeze_IgnitionNeeded;
/// \input     CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_DiagPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_HandleFailStateBehavior_Param1 = CtrlDcm_eFreeze_IgnitionNeeded;
    CtrlDcm_HandleFailStateBehavior_Param2 = CtrlDcm_eFreeze_IgnitionNeeded;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;

    //Step 3) Call FUT
    CtrlDcm_HandleFailStateBehavior(CtrlDcm_HandleFailStateBehavior_Param1, CtrlDcm_HandleFailStateBehavior_Param2);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_DiagPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailStateBehavior
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that Handle Fail state behavior for Master and Slave control
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailStateBehavior(void)
{
    Mt_CtrlDcm_HandleFailStateBehavior_TestCase1();
    Mt_CtrlDcm_HandleFailStateBehavior_TestCase2();
    Mt_CtrlDcm_HandleFailStateBehavior_TestCase3();
    Mt_CtrlDcm_HandleFailStateBehavior_TestCase4();
    Mt_CtrlDcm_HandleFailStateBehavior_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each  Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boLvlAdjFuncFault = TRUE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
/// \output  CtrlDcm_boIgnitionNeeded = TRUE 
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boLvlAdjFuncFault = TRUE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = TRUE;
    CtrlDcm_boSlaveSafetyPos = FALSE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SafetyPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boIgnitionNeeded, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = TRUE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_NormalPos
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
     CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
     CtrlDcm_boSlaveStop = FALSE;
     CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_NormalPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();
    //Step 4) Check expected output values

    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_FROZEN_FAILURE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = TRUE;
/// \input CtrlDcm_boSlaveSafetyPos = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SafetyPos
/// \output  CtrlDcm_boSlaveStop = FALSE
/// \output  CtrlDcm_boSlaveSafetyPos = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase6(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_FROZEN_FAILURE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SafetyPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is in each Handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boPowertrainActive = TRUE;
/// \input CtrlDcm_boLvlAdjFuncFault = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boLvlAdjHeadlampFault = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boDiagLvl = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_NormalPos
/// \output  CtrlDcm_boDiagLvl = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState_TestCase7(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boPowertrainActive = TRUE;
    CtrlDcm_boLvlAdjFuncFault = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boLvlAdjHeadlampFault = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault_R = FALSE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_NO_FAILURE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boDiagLvl = FALSE;

    //Step 3) Call FUT
    CtrlDcm_HandleFailState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_DiagPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_HandleFailState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that is in each Handle fail state behavior
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_HandleFailState(void)
{
    Mt_CtrlDcm_HandleFailState_TestCase1();
    Mt_CtrlDcm_HandleFailState_TestCase2();
    Mt_CtrlDcm_HandleFailState_TestCase3();
    Mt_CtrlDcm_HandleFailState_TestCase4();
    Mt_CtrlDcm_HandleFailState_TestCase5();
    Mt_CtrlDcm_HandleFailState_TestCase6();
    Mt_CtrlDcm_HandleFailState_TestCase7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseFail_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is State Machine: behavior in case of state Err
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = TRUE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = FALSE
/// \output  CtrlDcm_SignalSrc = TeDcmSrc_SleepPosRUE
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseFail_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = TRUE;
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseFail();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseFail_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is State Machine: behavior in case of state Err
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.boEntry = FALSE;
/// \input CtrlDcm_boPowertrainActive = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boSlaveStop = FALSE;
/// \input CtrlDcm_boSlaveSafetyPos = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = FALSE
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boSlaveStop = TRUE
/// \output  CtrlDcm_boSlaveSafetyPos = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseFail_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.boEntry = FALSE;
    CtrlDcm_boPowertrainActive = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boSlaveStop = FALSE;
    CtrlDcm_boSlaveSafetyPos = TRUE;

    //Step 3) Call FUT
    CtrlDcm_StateMachine_PhaseFail();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StateMachine_PhaseFail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that is State Machine: behavior in case of state Err
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StateMachine_PhaseFail(void)
{
    Mt_CtrlDcm_StateMachine_PhaseFail_TestCase1();
    Mt_CtrlDcm_StateMachine_PhaseFail_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeCustomer_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeCustomer_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_ModeCustomer();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeCustomer_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input     CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeCustomer_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boConVehIgnition = FALSE;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_ModeCustomer();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeCustomer_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input     CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeCustomer_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;

    //Step 3) Call FUT
    CtrlDcm_ModeCustomer();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeCustomer
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the enviromental signals are readdetects submode of assembly mode
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeCustomer(void)
{
    Mt_CtrlDcm_ModeCustomer_TestCase1();
    Mt_CtrlDcm_ModeCustomer_TestCase2();
    Mt_CtrlDcm_ModeCustomer_TestCase3();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeAssembly_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
/// \input     CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeFrozen
/// \output      Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeAssembly_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;

    //Step 3) Call FUT
    CtrlDcm_ModeAssembly();
    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeFrozen, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeAssembly_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeFactory
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeAssembly_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ModeAssembly();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeFactory, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeAssembly_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeFactory
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeAssembly_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boConVehIgnition = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_SNA;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
    CtrlDcm_eASLMode = CtrlDcm_eModeFactory;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ModeAssembly();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeFactory, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeAssembly_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeAssembly_TestCase4(void)
{
    //Step 1) Set pre-conditions
        //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boConVehIgnition = FALSE;
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_ModeAssembly();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_ModeAssembly
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that detects submode of assembly mode
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_ModeAssembly()
{
    Mt_CtrlDcm_ModeAssembly_TestCase1();
    Mt_CtrlDcm_ModeAssembly_TestCase2();
    Mt_CtrlDcm_ModeAssembly_TestCase3();
    Mt_CtrlDcm_ModeAssembly_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SubModeFrozen
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is frozen state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boDiagLvl = FALSE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = TRUE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SubModeFrozen()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boDiagLvl = FALSE;
    CtrlDcm_boSlaveStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_SubModeFrozen();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SubModeFactory
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is factory state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = TRUE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SubModeFactory()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boDiagLvl = FALSE;
    CtrlDcm_boSlaveStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_SubModeFactory();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_SubModeUnavailable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that is unavailable mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_boDiagLvl = TRUE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = FALSE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_SubModeUnavailable()
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_boDiagLvl = TRUE;
    CtrlDcm_boSlaveStop = FALSE;
    //Step 3) Call FUT
    CtrlDcm_SubModeUnavailable();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseMode_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that calls main mode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseMode_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_boConVehIgnition = FALSE;
    CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;

    //Step 3) Call FUT
    CtrlDcm_UseMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseMode_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that calls main mode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_eMainMode = CtrlDcm_eModeCustomer;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input     CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseMode_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_eMainMode = CtrlDcm_eModeCustomer;
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;

    //Step 3) Call FUT
    CtrlDcm_UseMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseMode_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that calls main mode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_eMainMode = 2u;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_boConVehIgnition = TRUE;
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
///
///   - Expectations:
///
/// \output  CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseMode_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_eMainMode = 2u;
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_boConVehIgnition = TRUE;
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;

    //Step 3) Call FUT
    CtrlDcm_UseMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eASLMode, CtrlDcm_eModeUnavailable, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that  calls main mode function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseMode(void)
{
    Mt_CtrlDcm_UseMode_TestCase1();
    Mt_CtrlDcm_UseMode_TestCase2();
    Mt_CtrlDcm_UseMode_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the call initialisation for CtrlDcm
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1   = CtrlDcm_eMountedLeft
/// \input CtrlDcm_eMountingSide                        = CtrlDcm_eMountedLeft
/// \input CtrlDcm_atStateMachine                       = { 0 }
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
///   - Expectations:
///
/// \output  CtrlDcm_atStateMachine = CtrlDcm_atStateMachine_Master
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Init_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    tsCtrlDcm_StateMType sEmptyStruct            = { 0 };
    Rte_Read_IoHwAbUser_GetMountingSide_Param1   = CtrlDcm_eMountedLeft;
    CtrlDcm_eMountingSide                        = CtrlDcm_eMountedLeft;
    CtrlDcm_atStateMachine                       = &sEmptyStruct;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_atStateMachine                      , CtrlDcm_atStateMachine_Master, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,                            2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the call initialisation for CtrlDcm
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedRight;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount =0u
///
///   - Expectations:
///
/// \output  CtrlDcm_atStateMachine = CtrlDcm_atStateMachine_Slave
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount =1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Init_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedRight;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_atStateMachine, CtrlDcm_atStateMachine_Slave, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the call initialisation for CtrlDcm
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Init()
{
    Mt_CtrlDcm_Init_TestCase1();
    Mt_CtrlDcm_Init_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Master_Cycle20ms_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Master_Cycle20ms_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boDiagDcmOn = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    CtrlDcm_boConVehIgnition = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_Master_Cycle20ms();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMainMode, CtrlDcm_eModeAssembly, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Master_Cycle20ms_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boDiagDcmOn = TRUE;
/// \input CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eDD06;
/// \input CtrlDcm_sDcmControlRequest.ucPosRequest = 800u;
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
/// \input CtrlDcm_State.boEntry = FALSE;
/// \input CtrlDcm_boStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = TRUE
/// \output  CtrlDcm_boStop = TRUE
/// \output  NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Master_Cycle20ms_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boDiagDcmOn = TRUE;
    CtrlDcm_sDcmControlRequest.eDcmDID = CtrlDcm_eDD06;
    CtrlDcm_sDcmControlRequest.ucPosRequest = 800u;
    NM_GetMode_HitCount = 0u;
    CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
    CtrlDcm_State.boEntry = FALSE;
    CtrlDcm_boStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Master_Cycle20ms();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boStop, TRUE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Master_Cycle20ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads singals , detects mode and submode and writes tg pos
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_Master_Cycle20ms(void)
{
    Mt_CtrlDcm_Master_Cycle20ms_TestCase1();
    Mt_CtrlDcm_Master_Cycle20ms_TestCase2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Slave_Cycle20ms_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
/// \input CtrlDcm_boDiagDcmOn = FALSE;
/// \input CtrlDcm_boStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_boStop = TRUE
/// \output  NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Slave_Cycle20ms_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boConVehIgnition = FALSE;
    NM_GetMode_HitCount = 0u;
    CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
    CtrlDcm_boDiagDcmOn = FALSE;
    CtrlDcm_boStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Slave_Cycle20ms();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, TRUE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Slave_Cycle20ms_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_boDiagDcmOn = TRUE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
/// \input CtrlDcm_boStop = FALSE;
/// \input CtrlDcm_State.boEntry = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = TRUE
/// \output  CtrlDcm_boStop = TRUE
/// \output  NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Slave_Cycle20ms_TestCase2(void)
{
    //Step 1) Set pre-conditions
   //Step 2) Assign Input values
    CtrlDcm_boDiagDcmOn = TRUE;
    CtrlDcm_boConVehIgnition = FALSE;
    NM_GetMode_HitCount = 0u;
    CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
    CtrlDcm_boStop = FALSE;
    CtrlDcm_State.boEntry = FALSE;

    //Step 3) Call FUT
    CtrlDcm_Slave_Cycle20ms();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boStop, TRUE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_Slave_Cycle20ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads singals , detects mode and submode and writes tg pos
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_Slave_Cycle20ms(void)
{
    Mt_CtrlDcm_Slave_Cycle20ms_TestCase1();
    Mt_CtrlDcm_Slave_Cycle20ms_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseSubMode_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in unavailable mode reset the DC motor state and call submode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;
/// \input boFirstEntry = TRUE;
/// \input CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_State.boEntry = FALSE;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boDiagLvl = TRUE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  boFirstEntry = TRUE
/// \output  CtrlDcm_State.ePhase= CtrlDcm_ePhase_Init
/// \output  CtrlDcm_State.boEntry = TRUE
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = FALSE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseSubMode_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eASLMode = CtrlDcm_eModeUnavailable;
    boFirstEntry = TRUE;
    CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_State.boEntry = FALSE;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boDiagLvl = TRUE;
    CtrlDcm_boSlaveStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_UseSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boFirstEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.ePhase, CtrlDcm_ePhase_Init, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, FALSE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseSubMode_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in availabel mode call state machine 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_eMainMode = CtrlDcm_eModeCustomer;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount=1u
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_UseSubMode_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eASLMode = CtrlDcm_eModeAvailable;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 3) Call FUT
    CtrlDcm_UseSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMainMode, CtrlDcm_eModeAssembly, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseSubMode_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in frozen mode reset the DC motor state and call submode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
/// \input boFirstEntry = TRUE;
/// \input CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boDiagLvl = FALSE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  boFirstEntry = TRUE
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = TRUE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseSubMode_TestCase3(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
    boFirstEntry = TRUE;
    CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boDiagLvl = FALSE;
    CtrlDcm_boSlaveStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_UseSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(boFirstEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseSubMode_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in factory mode reset the DC motor state and call submode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eASLMode = CtrlDcm_eModeFrozen;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boDiagLvl = FALSE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = TRUE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseSubMode_TestCase4(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eASLMode = CtrlDcm_eModeFactory;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
    CtrlDcm_boDiagLvl = FALSE;
    CtrlDcm_boSlaveStop = FALSE;

    //Step 3) Call FUT
    CtrlDcm_UseSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseSubMode_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the another mode keep the last changes
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eASLMode = 7u;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_SignalSrc = eDcmSrc_DiagPos;
/// \input CtrlDcm_boDiagLvl = FALSE;
/// \input CtrlDcm_boSlaveStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_SignalSrc = eDcmSrc_SleepPos
/// \output  CtrlDcm_boDiagLvl = TRUE
/// \output  CtrlDcm_boSlaveStop = TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseSubMode_TestCase5(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eASLMode = 7u;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
    CtrlDcm_boDiagLvl = TRUE;
    CtrlDcm_boSlaveStop = TRUE;

    //Step 3) Call FUT
    CtrlDcm_UseSubMode();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_SignalSrc, eDcmSrc_SleepPos, == );
    AL_UNITTEST_CHECK(CtrlDcm_boDiagLvl, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_boSlaveStop, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_UseSubMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that calls submode function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_UseSubMode(void)
{
    Mt_CtrlDcm_UseSubMode_TestCase1();
    Mt_CtrlDcm_UseSubMode_TestCase2();
    Mt_CtrlDcm_UseSubMode_TestCase3();
    Mt_CtrlDcm_UseSubMode_TestCase4();
    Mt_CtrlDcm_UseSubMode_TestCase5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StMch_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the state machine for DC Motor, 
///                       calls state function and goes through each state transition check
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
/// \input CtrlDcm_State.boEntry = FALSE;
/// \input CtrlDcm_boLvlAdjHeadlampFault = TRUE;
/// \input CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
/// \input CtrlDcm_eSensorError = CtrlDcm_eHLS_SENSOR_FAILURE;
/// \input CtrlDcm_boLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlDcm_State.boEntry = TRUE
/// \output  CtrlDcm_State.ePhase = CtrlDcm_ePhase_Fail
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StMch_TestCase1(void)
{
    
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_State.ePhase = CtrlDcm_ePhase_Adj;
    CtrlDcm_State.boEntry = FALSE;
    CtrlDcm_boLvlAdjHeadlampFault = TRUE;
    CtrlDcm_boLvlAdjHeadlampFault_R = TRUE;
    CtrlDcm_eSensorError = CtrlDcm_eHLS_SENSOR_FAILURE;
    CtrlDcm_boLvlAdjFuncFault = TRUE;

    //Step 3) Call FUT
    CtrlDcm_StMch();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_State.boEntry, TRUE, == );
    AL_UNITTEST_CHECK(CtrlDcm_State.ePhase, CtrlDcm_ePhase_Fail, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StMch_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the state machine for DC Motor, 
///                       calls state function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input CtrlDcm_boTrainingState = TRUE;
/// \input CtrlDcm_eMainMode=CtrlDcm_eModeAssembly
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount=0u
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount=0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_StMch_TestCase2(void)
{

    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = TRUE;
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
    //Step 3) Call FUT
    CtrlDcm_StMch();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMainMode, CtrlDcm_eModeAssembly, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_StMch
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that if state machine for DC Motor,
///                     calls state function and goes through each state transition check
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_CtrlDcm_StMch(void)
{
    Mt_CtrlDcm_StMch_TestCase1();
    Mt_CtrlDcm_StMch_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCtrlDcm_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the call initialisation for CtrlDcm
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input     Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlDcm_atStateMachine = CtrlDcm_atStateMachine_Master
/// \output      Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 2u;
///
//-----------------------------------------------------------------------------
void Mt_riCtrlDcm_Init(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlDcm_eMountedLeft;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;

    //Step 3) Call FUT
    riCtrlDcm_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_atStateMachine, CtrlDcm_atStateMachine_Master, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCtrlDcm_Cycle_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
/// \input CtrlDcm_boDiagDcmOn = TRUE;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
/// \input     CtrlDcm_boStop = FALSE;
///
///   - Expectations:
///
/// \output  CtrlDcm_boStop = TRUE
/// \output  NM_GetMode_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_rpCtrlDcm_Cycle_TestCase1(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_eMountingSide = CtrlDcm_eMountedRight;
    CtrlDcm_boDiagDcmOn = TRUE;
    CtrlDcm_boConVehIgnition = FALSE;
    NM_GetMode_HitCount = 0u;
    CtrlDcm_SignalSrc = eDcmSrc_SleepPos;
    CtrlDcm_boStop = FALSE;
    //Step 3) Call FUT
    rpCtrlDcm_Cycle();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_boStop, TRUE, == );
    AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCtrlDcm_Cycle_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
/// \input CtrlDcm_boTrainingState = FALSE;
/// \input CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
/// \input CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
/// \input CtrlDcm_boConVehIgnition = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount=0u
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount=1u
///
//-----------------------------------------------------------------------------
void Mt_rpCtrlDcm_Cycle_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_boDiagDcmOn = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
    CtrlDcm_boTrainingState = FALSE;
    CtrlDcm_eMountingSide = CtrlDcm_eMountedLeft;
    CtrlDcm_eMainMode = CtrlDcm_eModeAssembly;
    CtrlDcm_boConVehIgnition = FALSE;
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
    //Step 3) Call FUT
    rpCtrlDcm_Cycle();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_eMainMode, CtrlDcm_eModeAssembly, == );
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpCtrlDcm_Cycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that reads singals , detects mode and submode and writes tg pos
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------

void Mt_rpCtrlDcm_Cycle(void)
{
    Mt_rpCtrlDcm_Cycle_TestCase1();
    Mt_rpCtrlDcm_Cycle_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlDcm_WriteStatusParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that write status parameters in rte port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlDcm_sDcmStatusParams.eASL_MODE = 1u;
/// \input CtrlDcm_sDcmStatusParams.boLvlAdjFunctionalFault_L = 2u;
///
///   - Expectations:
///
/// \output  CtrlDcm_eMainMode = CtrlDcm_eModeAssembly
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount=1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlDcm_WriteStatusParams(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CtrlDcm_sDcmStatusParams.eASL_MODE = 1u;
    CtrlDcm_sDcmStatusParams.boLvlAdjFunctionalFault_L = 2u;

    //Step 3) Call FUT
    CtrlDcm_WriteStatusParams();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CtrlDcm_sDcmStatusParams.eASL_MODE, 7u, == );
    AL_UNITTEST_CHECK(CtrlDcm_sDcmStatusParams.boLvlAdjFunctionalFault_L, 1u, == );
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
    //CtrlDcmSm.c
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Assembly_To_Frozen", Mt_CtrlDcm_Transition_Assembly_To_Frozen);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Assembly_To_Factory", Mt_CtrlDcm_Transition_Assembly_To_Factory);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Assembly_To_Unavailable", Mt_CtrlDcm_Transition_Assembly_To_Unavailable);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Customer_To_Unavailable", Mt_CtrlDcm_Transition_Customer_To_Unavailable);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Customer_To_Available(", Mt_CtrlDcm_Transition_Customer_To_Available);
    ALUnitTest_AddFunction("Mt_CtrlDcm_StateMachine_PhaseInit(", Mt_CtrlDcm_StateMachine_PhaseInit);
    ALUnitTest_AddFunction("Mt_CtrlDcm_StateMachine_PhaseAdj(", Mt_CtrlDcm_StateMachine_PhaseAdj);
    ALUnitTest_AddFunction("Mt_CtrlDcm_DetectMode", Mt_CtrlDcm_DetectMode);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ResetDcmState", Mt_CtrlDcm_ResetDcmState);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Adj_To_Fail_Slave", Mt_CtrlDcm_Transition_Adj_To_Fail_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Fail_To_Adj_Slave", Mt_CtrlDcm_Transition_Fail_To_Adj_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Init_To_Adj_Slave", Mt_CtrlDcm_Transition_Init_To_Adj_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Init_To_Fail_Slave", Mt_CtrlDcm_Transition_Init_To_Fail_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_DetectSlaveSubMode", Mt_CtrlDcm_DetectSlaveSubMode);
    ALUnitTest_AddFunction("Mt_CtrlDcm_StateMachine_PhaseInit_Slave", Mt_CtrlDcm_StateMachine_PhaseInit_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_HandleFailStateBehavior_Slave", Mt_CtrlDcm_HandleFailStateBehavior_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_HandleFailState_Slave", Mt_CtrlDcm_HandleFailState_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_StateMachine_PhaseFail_Slave", Mt_CtrlDcm_StateMachine_PhaseFail_Slave);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Init_To_Adj", Mt_CtrlDcm_Transition_Init_To_Adj);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Init_To_Fail", Mt_CtrlDcm_Transition_Init_To_Fail);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Adj_To_Fail", Mt_CtrlDcm_Transition_Adj_To_Fail);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Transition_Fail_To_Adj", Mt_CtrlDcm_Transition_Fail_To_Adj);
    ALUnitTest_AddFunction("Mt_CtrlDcm_HandleFailStateBehavior", Mt_CtrlDcm_HandleFailStateBehavior);
    ALUnitTest_AddFunction("Mt_CtrlDcm_HandleFailState", Mt_CtrlDcm_HandleFailState);
    ALUnitTest_AddFunction("Mt_CtrlDcm_StateMachine_PhaseFail", Mt_CtrlDcm_StateMachine_PhaseFail);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ModeCustomer", Mt_CtrlDcm_ModeCustomer);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SubModeFrozen", Mt_CtrlDcm_SubModeFrozen);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SubModeFactory", Mt_CtrlDcm_SubModeFactory);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SubModeUnavailable", Mt_CtrlDcm_SubModeUnavailable);
    ALUnitTest_AddFunction("Mt_CtrlDcm_UseMode", Mt_CtrlDcm_UseMode);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Init", Mt_CtrlDcm_Init);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Master_Cycle20ms", Mt_CtrlDcm_Master_Cycle20ms);
    ALUnitTest_AddFunction("Mt_CtrlDcm_Slave_Cycle20ms", Mt_CtrlDcm_Slave_Cycle20ms);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SubModeFactory", Mt_CtrlDcm_SubModeFactory);
    ALUnitTest_AddFunction("Mt_CtrlDcm_UseSubMode", Mt_CtrlDcm_UseSubMode);
    ALUnitTest_AddFunction("Mt_CtrlDcm_StMch", Mt_CtrlDcm_StMch);
    ALUnitTest_AddFunction("Mt_CtrlDcm_WriteStatusParams", Mt_CtrlDcm_WriteStatusParams);

    //ctaaCtrlDcm.c
    ALUnitTest_AddFunction("Mt_riCtrlDcm_Init", Mt_riCtrlDcm_Init);
    ALUnitTest_AddFunction("Mt_rpCtrlDcm_Cycle", Mt_rpCtrlDcm_Cycle);

    //CtrlDcm.c
    ALUnitTest_AddFunction("Mt_CtrlDcm_GetDiagLvl", Mt_CtrlDcm_GetDiagLvl);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SetDiagLvl", Mt_CtrlDcm_SetDiagLvl);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SetSlaveStopRequest", Mt_CtrlDcm_SetSlaveStopRequest);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SetSlaveSafetyPosition", Mt_CtrlDcm_SetSlaveSafetyPosition);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SetFailIgnitionNeeded", Mt_CtrlDcm_SetFailIgnitionNeeded);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RetPowerTrainActive", Mt_CtrlDcm_RetPowerTrainActive);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadEnvironmentSignals", Mt_CtrlDcm_ReadEnvironmentSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadStatusSignals", Mt_CtrlDcm_ReadStatusSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_LimitAngle", Mt_CtrlDcm_LimitAngle);
    ALUnitTest_AddFunction("Mt_CtrlDcm_DetectSide", Mt_CtrlDcm_DetectSide);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnSide", Mt_CtrlDcm_ReturnSide);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus", Mt_CtrlDcm_ReadLvlAdjFunctionalFaultStatus);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadMasterSignals", Mt_CtrlDcm_ReadMasterSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery", Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery);
    ALUnitTest_AddFunction("Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R", Mt_CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus", Mt_CtrlDcm_ReadLvlAdjHeadlampFaultStatus);
    ALUnitTest_AddFunction("Mt_CtrlDcm_CondEnabled", Mt_CtrlDcm_CondEnabled);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RetVehIgnition", Mt_CtrlDcm_RetVehIgnition);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnboTrainingState", Mt_CtrlDcm_ReturnboTrainingState);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturneSensorError", Mt_CtrlDcm_ReturneSensorError);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnboLvlAdjFuncFault", Mt_CtrlDcm_ReturnboLvlAdjFuncFault);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault", Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnboSlaveLvlAdjFuncFault", Mt_CtrlDcm_ReturnboSlaveLvlAdjFuncFault);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault_R", Mt_CtrlDcm_ReturnboLvlAdjHeadlampFault_R);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReturnboExtTakeOver", Mt_CtrlDcm_ReturnboExtTakeOver);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SetSignalMode", Mt_CtrlDcm_SetSignalMode);
    ALUnitTest_AddFunction("Mt_CtrlDcm_GetTgtPos", Mt_CtrlDcm_GetTgtPos);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadCommonSignals", Mt_CtrlDcm_ReadCommonSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_DiagDcmTakeOver", Mt_CtrlDcm_DiagDcmTakeOver);
    ALUnitTest_AddFunction("Mt_CtrlDcm_SetDiagPos", Mt_CtrlDcm_SetDiagPos);
    ALUnitTest_AddFunction("Mt_CtrlDcm_DiagRoutineControl", Mt_CtrlDcm_DiagRoutineControl);
    ALUnitTest_AddFunction("Mt_CtrlDcm_WriteMasterSignals", Mt_CtrlDcm_WriteMasterSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_WriteSlaveSignals", Mt_CtrlDcm_WriteSlaveSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ReadSlaveSignals", Mt_CtrlDcm_ReadSlaveSignals);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ModeAssembly", Mt_CtrlDcm_ModeAssembly);

    //CtrlDcm_Data.c
    ALUnitTest_AddFunction("Mt_CtrlDcm_CodingDataReady", Mt_CtrlDcm_CodingDataReady);
    ALUnitTest_AddFunction("Mt_Cod_DcmMinVehAtt", Mt_Cod_DcmMinVehAtt);
    ALUnitTest_AddFunction("Mt_Cod_DcmMaxVehAtt", Mt_Cod_DcmMaxVehAtt);
    ALUnitTest_AddFunction("Mt_Cod_DcmMinAdjASL", Mt_Cod_DcmMinAdjASL);
    ALUnitTest_AddFunction("Mt_Cod_DcmMaxAdjASL", Mt_Cod_DcmMaxAdjASL);
    ALUnitTest_AddFunction("Mt_Cod_DcmSp", Mt_Cod_DcmSp);
    ALUnitTest_AddFunction("Mt_Cod_DcmVehAttThrStill", Mt_Cod_DcmVehAttThrStill);
    ALUnitTest_AddFunction("Mt_Cod_DcmFrozenVehSpeedASL", Mt_Cod_DcmFrozenVehSpeedASL);
    ALUnitTest_AddFunction("Mt_Cod_DcmEnable", Mt_Cod_DcmEnable);
    ALUnitTest_AddFunction("Mt_Cod_DcmVehAttThrMotion", Mt_Cod_DcmVehAttThrMotion);
    ALUnitTest_AddFunction("Mt_Cod_DcmMotionDelayASL", Mt_Cod_DcmMotionDelayASL);
    ALUnitTest_AddFunction("Mt_CtrlDcm_ParaFct0", Mt_CtrlDcm_ParaFct0);

    //CtrlDcm_RteAccess.c
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_Read_EcuSide", Mt_CtrlDcm_RteAccess_Read_EcuSide);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadSpeed", Mt_CtrlDcm_RteAccess_ReadSpeed);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadVehicleElectricState", Mt_CtrlDcm_RteAccess_ReadVehicleElectricState);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadVESMainState", Mt_CtrlDcm_RteAccess_ReadVESMainState);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig", Mt_CtrlDcm_RteAccess_ReadVehicleModeConfig);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadAvacCommand", Mt_CtrlDcm_RteAccess_ReadAvacCommand);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadDriverErrors", Mt_CtrlDcm_RteAccess_ReadDriverErrors);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadSensorStatus", Mt_CtrlDcm_RteAccess_ReadSensorStatus);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos", Mt_CtrlDcm_RteAccess_ReadLevellingTgtPos);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port", Mt_CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port", Mt_CtrlDcm_RteAccess_Write_DrvLedDiag_Port);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port", Mt_CtrlDcm_RteAccess_Write_DrvLedDiagR_Port);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port", Mt_CtrlDcm_RteAccess_Read_DrvLedDiagR_Port);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port", Mt_CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues", Mt_CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_WriteDcmRoutineAck", Mt_CtrlDcm_RteAccess_WriteDcmRoutineAck);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0", Mt_CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0", Mt_CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine", Mt_CtrlDcm_RteAccess_ReadDiagDcmControlRoutine);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_MapParams", Mt_CtrlDcm_RteAccess_MapParams);
    ALUnitTest_AddFunction("Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port", Mt_CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port);
   
}
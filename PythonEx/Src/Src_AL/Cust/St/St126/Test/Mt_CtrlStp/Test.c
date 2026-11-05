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
/// \brief Module test for Ctrlstp
///
/// 
/// 
/// author   - Rohit Karekar
/// emailid  - rohitkarekar@external.marelli.com
///
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

#include "Test.h"
#include "Test_Stubs.h"


uint32 ulTimerStart;
uint32 ulTimeElapsed;
boolean boTimerStart = { FALSE };
uint32 ulHBTimer = 0u;
uint32 ulDelayTimer = 0u;

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads functional fault of levelling
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
///  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = TRUE;
///  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eInvalid;
///  CtrlStp_boVehAttitudeInvalid = TRUE;
///
/// - Expectations:
///CtrlStp_boLvlAdjFuncFault, TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_1(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = TRUE;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eInvalid;
  CtrlStp_boVehAttitudeInvalid = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjFunctionalFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boLvlAdjFuncFault, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads functional fault of levelling
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
///  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = FALSE;
///  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_NOMINAL;
///  CtrlStp_boVehAttitudeInvalid = FALSE;
///
/// - Expectations:
///CtrlStp_boLvlAdjFuncFault, FALSE,
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_2(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = FALSE;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_NOMINAL;
  CtrlStp_boVehAttitudeInvalid = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjFunctionalFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boLvlAdjFuncFault, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads functional fault of levelling
///
///        - Test Design Technique: ET(Exploratory Testing )
///		-
///   Preconditions:
///CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = CtrlStp_SIG_TIMEOUT;
///Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
///Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
///CtrlStp_boSlaveLvlAdjFuncFault = TRUE; 
///
///
/// - Expectations:
///  CtrlStp_boSlaveLvlAdjFuncFault, FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_3(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = CtrlStp_SIG_TIMEOUT;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
  CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjFunctionalFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveLvlAdjFuncFault, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads functional fault of levelling
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///   CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
///  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = CtrlStp_SIG_TIMEOUT;
///
///
/// - Expectations:
///  CtrlStp_boSlaveLvlAdjFuncFault, TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_4(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_INVALID;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjFunctionalFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveLvlAdjFuncFault, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads functional fault of levelling
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = CtrlStp_SIG_INVALID;
///  CtrlStp_boLvlAdjFuncFault = FALSE;
///
/// - Expectations:
///  CtrlStp_boSlaveLvlAdjFuncFault, TRUE
///  CtrlStp_sLevellingFeedbackFromRighToLeft.eSigQty, CtrlStp_SIG_INVALID
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_sLevellingFeedbackFromRighToLeft.eSigQty = CtrlStp_SIG_INVALID;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjFunctionalFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_sLevellingFeedbackFromRighToLeft.eSigQty, CtrlStp_SIG_INVALID, == );
  AL_UNITTEST_CHECK(CtrlStp_boLvlAdjFuncFault, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  : Check that if the function reads functional fault of levelling
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus(void)
{
  Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_1();
  Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_2();
  Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_3();
  Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_4();
  Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_unTgtTmin = 0u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_snOffsetCorrection = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_boCurtainAct = TRUE;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 1u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_ON_ANGULAR_SPEED = 2u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_ON_SEGMENT_DIMING = 20u;
///
///   - Expectations:
///
/// \output  CtrlStp_unTgtTmin, 65535
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_boCurtainAct = TRUE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_unTgtTmin = 0u;
/// \input  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input  CtrlStp_snOffsetCorrection = -1;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input  CtrlStp_boCurtainAct = FALSE;
/// \input  CtrlStp_boCurtainDeAct = TRUE;
/// \input  CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 1u;
/// \input  CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_ANGULAR_SPEED = 2u;
///         CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_SEGMENT_DIMING = 20u;
///   - Expectations:
///
/// \output  CtrlStp_unTgtTmin, 65535u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = -1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_boCurtainAct = FALSE;
  CtrlStp_boCurtainDeAct = TRUE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_unTgtTmin = 0u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_snOffsetCorrection = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_boCurtainAct = FALSE;
/// \input CtrlStp_boCurtainDeAct = FALSE;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 1u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_ANGULAR_SPEED = 2u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_SEGMENT_DIMING = 20u;
///
///   - Expectations:
///
/// \output  CtrlStp_unTgtTmin, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_boCurtainAct = FALSE;
  CtrlStp_boCurtainDeAct = FALSE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_unTgtTmin = 0u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_snOffsetCorrection = 0;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_boCurtainAct = FALSE;
/// \input CtrlStp_boCurtainDeAct = FALSE;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 1u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_ANGULAR_SPEED = 2u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_SEGMENT_DIMING = 20u;
///
///   - Expectations:
///
/// \output  CtrlStp_unTgtTmin, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = 0;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_boCurtainAct = FALSE;
  CtrlStp_boCurtainDeAct = FALSE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_unTgtTmin = 0u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_snOffsetCorrection = 0;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = TRUE;
/// \input CtrlStp_boCurtainAct = FALSE;
/// \input CtrlStp_boCurtainDeAct = FALSE;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 1u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_ANGULAR_SPEED = 2u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_SEGMENT_DIMING = 20u;
///
///   - Expectations:
///
/// \output  CtrlStp_unTgtTmin, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = 0;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = TRUE;
  CtrlStp_boCurtainAct = FALSE;
  CtrlStp_boCurtainDeAct = FALSE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_unTgtTmin = 0u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_snOffsetCorrection = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_boCurtainAct = TRUE;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 0u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_ON_ANGULAR_SPEED = 2u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_ON_SEGMENT_DIMING = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_unTgtTmin, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_boCurtainAct = TRUE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets the minimum period for a halfstep
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_unTgtTmin = 0u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_snOffsetCorrection = -1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_boCurtainAct = FALSE;
/// \input CtrlStp_boCurtainDeAct = TRUE;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucHB_APERTURE = 0u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_ANGULAR_SPEED = 2u;
/// \input CtrlStp_CodingData.AfsOffset_OperationData.ucGFHB_CURTAIN_EFFECT_OFF_SEGMENT_DIMING = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransitionSttToAdj_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_unTgtTmin = 0u;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_snOffsetCorrection = -1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_boCurtainAct = FALSE;
  CtrlStp_boCurtainDeAct = TRUE;
  //Step 3) Call FUT
  CtrlStp_SetTgtTmin();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_unTgtTmin, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetTgtTmin
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function sets the minimum period for a halfstep
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetTgtTmin(void)
{
  Mt_CtrlStp_SetTgtTmin_TestCase_1();
  Mt_CtrlStp_SetTgtTmin_TestCase_2();
  Mt_CtrlStp_SetTgtTmin_TestCase_3();
  Mt_CtrlStp_SetTgtTmin_TestCase_4();
  Mt_CtrlStp_SetTgtTmin_TestCase_5();
  Mt_CtrlStp_SetTgtTmin_TestCase_6();
  Mt_CtrlStp_SetTgtTmin_TestCase_7();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = eStpSrc_SleepPos;
/// \input CtrlStp_boStop    = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_boStop, TRUE
/// \output  CtrlStp_nTgtPos, 2, 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_1(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_SleepPos;
  CtrlStp_boStop    = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// - CtrlStp_SignalSrc  = eStpSrc_InscenPos;
/// - CtrlStp_nInscenPos = CTRLSTP_HsPosInvalid;
/// - CtrlStp_boStop     = FALSE;
/// - Expectations:
///  CtrlStp_boStop, TRUE
///  CtrlStp_nTgtPos, 0
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc   = eStpSrc_InscenPos;
  CtrlStp_nInscenPos  = CTRLSTP_HsPosInvalid;
  CtrlStp_boStop      = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// -   CtrlStp_SignalSrc                                            = eStpSrc_InscenPos;
/// -   CtrlStp_nInscenPos                                           = 1;
/// -   CtrlStp_boStop                                               = FALSE;
/// -   CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS     = 100;
/// -   CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving            = TRUE;
/// -   CtrlStp_nTgtPos                                              = 100;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L   = 100;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L    = 100;
/// -   CtrlStp_nPosReq                                              = 10;
/// -   CtrlStp_nOffset                                              = 10;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 10;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 100;
/// - Expectations:
///     CtrlStp_boStop, FALSE
///     CtrlStp_nTgtPos, 100
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc                                            = eStpSrc_InscenPos;
  CtrlStp_nInscenPos                                           = 1;
  CtrlStp_boStop                                               = FALSE;
  CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS     = 100;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving            = TRUE;
  CtrlStp_nTgtPos                                              = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L   = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L    = 100;
  CtrlStp_nPosReq                                              = 10;
  CtrlStp_nOffset                                              = 10;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 10;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 100;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 100, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// -   CtrlStp_SignalSrc                                            = eStpSrc_NormalPos;
/// -   CtrlStp_boStop                                               = FALSE;
/// -   CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS     = 100;
/// -   CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving            = TRUE;
/// -   CtrlStp_nTgtPos                                              = 100;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L   = 100;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L    = 100;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 10;
/// -   CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 100;
/// - Expectations:
/// - CtrlStp_boStop, 0,
/// - CtrlStp_nTgtPos, 0
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc                                            = eStpSrc_NormalPos;
  CtrlStp_boStop                                               = FALSE;
  CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS     = 100;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving            = TRUE;
  CtrlStp_nTgtPos                                              = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L   = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L    = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 10;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 100;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///       CtrlStp_SignalSrc = eStpSrc_NormalPos;
///       CtrlStp_boStop = FALSE;
/// - Expectations:
///       CtrlStp_boStop, FALSE
///       CtrlStp_nTgtPos, 0, =
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_NormalPos;
  CtrlStp_boStop = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
/// - CtrlStp_SignalSrc                                           = eStpSrc_DiagPos;
/// - CtrlStp_sStpControlRequest.eStpSide                         = CtrlStp_eRightActuator;
/// - CtrlStp_boStop                                              = FALSE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving           = TRUE;
/// - CtrlStp_nTgtPos                                             = 100;
/// - CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L  = 100;
/// - CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L   = 100;
/// - CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 10;
/// - CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 100;
/// - CtrlStp_sStpControlRequest.eStpDID                           = CtrlStp_eDF11;
/// - Expectations:
///         AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
///         AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 1, == );
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc                                            = eStpSrc_DiagPos;
  CtrlStp_sStpControlRequest.eStpSide                          = CtrlStp_eRightActuator;
  CtrlStp_boStop                                               = FALSE;
  CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS     = 100;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving            = TRUE;
  CtrlStp_nTgtPos                                              = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L   = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L    = 100;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 10;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 100;
  CtrlStp_sStpControlRequest.eStpDID                           = CtrlStp_eDF11;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///    CtrlStp_SignalSrc                   = eStpSrc_DiagPos;
///    CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
///    CtrlStp_boStop                      = FALSE;
/// - Expectations:
///    CtrlStp_boStop, TRUE
///    CtrlStp_nTgtPos, 0, 
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc                   = eStpSrc_DiagPos;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
  CtrlStp_boStop                      = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = eStpSrc_SafetyPos;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 500;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 200;
/// \input CtrlStp_SafetyPos = 10;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 0;
/// \input CtrlStp_boStop = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, 0,
/// \output CtrlStp_nTgtPos, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_SafetyPos;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 500;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 200;
  CtrlStp_SafetyPos = 10;
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  CtrlStp_boStop = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc                                          = eStpSrc_SafetyPos;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 500;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L  = 0;
/// \input CtrlStp_SafetyPos                                          = 10;
/// \input CtrlStp_ActAll.sLwrActual.nPosition                        = 0;
/// \input CtrlStp_boStop                                             = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, 0,
/// \output CtrlStp_nTgtPos, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc                                          = eStpSrc_SafetyPos;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 500;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L  = 0;
  CtrlStp_SafetyPos                                          = 10;
  CtrlStp_ActAll.sLwrActual.nPosition                        = 0;
  CtrlStp_boStop                                             = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = eStpSrc_ContinPos;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_unTgtTmin = 1u;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, FALSE
/// \output CtrlStp_nTgtPos, 12, 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_ContinPos;
  CtrlStp_boStop = TRUE;
  CtrlStp_unTgtTmin = 1u;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 12, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = 6;
/// \input CtrlStp_boStop = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, FALSE
/// \output CtrlStp_nTgtPos, 0, 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = 6;
  CtrlStp_boStop = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_12
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = eStpSrc_NormalPos;
/// \input NM_GetMode_Param1 = 0x05;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_nTgtPos = 1u;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, TRUE
/// \output CtrlStp_nTgtPos, 0u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_12(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_NormalPos;
  NM_GetMode_Param1 = 0x05;
  CtrlStp_boStop = FALSE;
  CtrlStp_nTgtPos = 1u;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_13
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = eStpSrc_SafetyPos;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1u;
/// \input CtrlStp_SafetyPos = 0;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 0;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_nTgtPos = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, TRUE
/// \output CtrlStp_nTgtPos, 1u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_13(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_SafetyPos;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1u;
  CtrlStp_SafetyPos = 0;
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  CtrlStp_boStop = FALSE;
  CtrlStp_nTgtPos = 0u;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos_TestCase_14
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = eStpSrc_ZeroPos;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1u;
/// \input CtrlStp_SafetyPos = 0;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 0;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_nTgtPos = 0u;
/// \input NM_GetMode_Param1 = 0x05;
///
///   - Expectations:
///
/// \output CtrlStp_boStop, TRUE
/// \output CtrlStp_nTgtPos, 1u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos_TestCase_14(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = eStpSrc_ZeroPos;
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 5000u;
  CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1u;
  CtrlStp_SafetyPos = 0;
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  CtrlStp_boStop = FALSE;
  CtrlStp_nTgtPos = 0u;
  NM_GetMode_Param1 = 0x05;
  //Step 3) Call FUT
  CtrlStp_GetTgtPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStop, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nTgtPos, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetTgtPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the value for Pos, Tmin and Stop based on selected source are calculated correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetTgtPos(void)
{
  Mt_CtrlStp_GetTgtPos_TestCase_1();
  Mt_CtrlStp_GetTgtPos_TestCase_2();
  Mt_CtrlStp_GetTgtPos_TestCase_3();
  Mt_CtrlStp_GetTgtPos_TestCase_4();
  Mt_CtrlStp_GetTgtPos_TestCase_5();
  Mt_CtrlStp_GetTgtPos_TestCase_6();
  Mt_CtrlStp_GetTgtPos_TestCase_7();
  Mt_CtrlStp_GetTgtPos_TestCase_8();
  Mt_CtrlStp_GetTgtPos_TestCase_9();
  Mt_CtrlStp_GetTgtPos_TestCase_10();
  Mt_CtrlStp_GetTgtPos_TestCase_11();
  Mt_CtrlStp_GetTgtPos_TestCase_12();
  Mt_CtrlStp_GetTgtPos_TestCase_13();
  Mt_CtrlStp_GetTgtPos_TestCase_14();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetElecIntStopCondition_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: :  Check that if the stop of the stepper happens in Elecint mode and limphome
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetElecIntStopCondition_RetVal = TRUE;
/// \input NM_GetMode_Param1                      = NM_NORMAL;
/// \input EAPI_GetCurrentEIMode_RetVal           = LEIM_E_INACTIVE;
/// \input NM_GetMode_HitCount                    = 0u;
/// \input EAPI_GetCurrentEIMode_HitCount         = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_GetElecIntStopCondition_RetVal  = FALSE
/// \output NM_GetMode_HitCount                     = 1u
/// \output EAPI_GetCurrentEIMode_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetElecIntStopCondition_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetElecIntStopCondition_RetVal = TRUE;
  NM_GetMode_Param1                      = NM_NORMAL;
  EAPI_GetCurrentEIMode_RetVal           = LEIM_E_INACTIVE;
  NM_GetMode_HitCount                    = 0;
  EAPI_GetCurrentEIMode_HitCount         = 0;

  //Step 3) Call FUT
  CtrlStp_GetElecIntStopCondition_RetVal = CtrlStp_GetElecIntStopCondition();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetElecIntStopCondition_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetElecIntStopCondition_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : Check that if the stop of the stepper happens in Elecint mode and limphome
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetElecIntStopCondition_RetVal = TRUE;
/// \input NM_GetMode_Param1                      = LIMP_HOME_MODE;
/// \input EAPI_GetCurrentEIMode_RetVal           = LEIM_E_INACTIVE;
/// \input NM_GetMode_HitCount                    = 0u;
/// \input EAPI_GetCurrentEIMode_HitCount         = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_GetElecIntStopCondition_RetVal  = FALSE
/// \output NM_GetMode_HitCount                     = 1u
/// \output EAPI_GetCurrentEIMode_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetElecIntStopCondition_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetElecIntStopCondition_RetVal = TRUE;
  NM_GetMode_Param1                      = LIMP_HOME_MODE;
  EAPI_GetCurrentEIMode_RetVal           = LEIM_E_INACTIVE;
  NM_GetMode_HitCount                    = 0;
  EAPI_GetCurrentEIMode_HitCount         = 0;

  //Step 3) Call FUT
  CtrlStp_GetElecIntStopCondition_RetVal = CtrlStp_GetElecIntStopCondition();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetElecIntStopCondition_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetElecIntStopCondition_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : Check that if the stop of the stepper happens in Elecint mode and limphome
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetElecIntStopCondition_RetVal = TRUE;
/// \input NM_GetMode_Param1                      = NM_NORMAL;
/// \input EAPI_GetCurrentEIMode_RetVal           = LEIM_E_ACTIVE;
/// \input NM_GetMode_HitCount                    = 0u;
/// \input EAPI_GetCurrentEIMode_HitCount         = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_GetElecIntStopCondition_RetVal  = FALSE
/// \output NM_GetMode_HitCount                     = 1u
/// \output EAPI_GetCurrentEIMode_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetElecIntStopCondition_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetElecIntStopCondition_RetVal = TRUE;
  NM_GetMode_Param1                      = NM_NORMAL;
  EAPI_GetCurrentEIMode_RetVal           = LEIM_E_ACTIVE;
  NM_GetMode_HitCount                    = 0;
  EAPI_GetCurrentEIMode_HitCount         = 0;

  //Step 3) Call FUT
  CtrlStp_GetElecIntStopCondition_RetVal = CtrlStp_GetElecIntStopCondition();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetElecIntStopCondition_RetVal, FALSE, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetElecIntStopCondition_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : Check that if the stop of the stepper happens in Elecint mode and limphome
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetElecIntStopCondition_RetVal = FALSE;
/// \input NM_GetMode_Param1                      = LIMP_HOME_MODE;
/// \input EAPI_GetCurrentEIMode_RetVal           = LEIM_E_ACTIVE;
/// \input NM_GetMode_HitCount                    = 0u;
/// \input EAPI_GetCurrentEIMode_HitCount         = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_GetElecIntStopCondition_RetVal  = TRUE
/// \output NM_GetMode_HitCount                     = 1u
/// \output EAPI_GetCurrentEIMode_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetElecIntStopCondition_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetElecIntStopCondition_RetVal = FALSE;
  NM_GetMode_Param1                      = LIMP_HOME_MODE;
  EAPI_GetCurrentEIMode_RetVal           = LEIM_E_ACTIVE;
  NM_GetMode_HitCount                    = 0u;
  EAPI_GetCurrentEIMode_HitCount         = 0u;

  //Step 3) Call FUT
  CtrlStp_GetElecIntStopCondition_RetVal = CtrlStp_GetElecIntStopCondition();

  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetElecIntStopCondition_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetElecIntStopCondition
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the stop of the stepper happens in Elecint mode and limphome
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetElecIntStopCondition(void)
{
  Mt_CtrlStp_GetElecIntStopCondition_TestCase_1();
  Mt_CtrlStp_GetElecIntStopCondition_TestCase_2();
  Mt_CtrlStp_GetElecIntStopCondition_TestCase_3();
  Mt_CtrlStp_GetElecIntStopCondition_TestCase_4();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadMasterSignals_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads master signals correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
///
///  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
///
///  Rte_Read_ppsAvacOut_HitCount = 0;
///  Rte_Read_ppsAvacOut_Param1.State = 1;
///  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
///  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
///  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
///
///  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
///  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
///
///  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
///
///  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
///  Rte_Read_Stp_RoutineControl_HitCount = 0u;
///  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
///  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
///
///  CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
///
///
/// - Expectations:
///
///(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1,
///
///(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u,
///(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1,
///(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1,
///
///(Rte_Read_ppsAvacOut_HitCount, 1u,
///(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0,
///
///(Rte_Read_Pitch_PlausState_HitCount, 6u,
///(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE,
///
///(CtrlStp_boDiagStpOn, TRUE,
///
///(CtrlStp_nPosReq, CtrlStp_Simulation_Data.nSimPosReq,
///
///(CtrlStp_boTrainingState, TRUE,
///
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadMasterSignals_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
  Rte_Read_ppsAvacOut_HitCount = 0;
  Rte_Read_ppsAvacOut_Param1.State = 1;
  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
  //Step 3) Call FUT
  CtrlStp_ReadMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE, == );
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_nPosReq, CtrlStp_Simulation_Data.nSimPosReq, == );
  AL_UNITTEST_CHECK(CtrlStp_boTrainingState, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadMasterSignals_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the function reads master signals correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
///
///  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
///
///  Rte_Read_ppsAvacOut_HitCount = 0;
///  Rte_Read_ppsAvacOut_Param1.State = 1;
///  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
///  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
///  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
///
///  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
///  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
///
///  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
///
///  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
///  Rte_Read_Stp_RoutineControl_HitCount = 0u;
///  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
///  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
///
///  CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
///
///
/// - Expectations:
///
///(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1,
///
///(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u,
///(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1,
///(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1,
///
///(Rte_Read_ppsAvacOut_HitCount, 1u,
///(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0,
///
///(Rte_Read_Pitch_PlausState_HitCount, 6u,
///(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE,
///
///(CtrlStp_boDiagStpOn, TRUE,
///
///(CtrlStp_nPosReq, CtrlStp_Simulation_Data.nSimPosReq,
///
///(CtrlStp_boTrainingState, TRUE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadMasterSignals_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
  Rte_Read_ppsAvacOut_HitCount = 0;
  Rte_Read_ppsAvacOut_Param1.State = 1;
  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xF0u;
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  CtrlStp_Simulation_Data.ulSimActivated = 0x0F;
  //Step 3) Call FUT
  CtrlStp_ReadMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE, == );
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_boTrainingState, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadMasterSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  : Check that if the function reads master signals correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadMasterSignals(void)
{
  Mt_CtrlStp_ReadMasterSignals_TestCase_1();
  Mt_CtrlStp_ReadMasterSignals_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from slave are written correctly
///			-
///
///
///        - Test Design Technique: ET(Exploratory Testing )
///  
///    Preconditions:
///  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
///  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
///
///  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
///  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
///
///  Rte_Read_ppsAvacOut_HitCount = 0;
///  Rte_Read_ppsAvacOut_Param1.State = 1;
///  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
///  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
///  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
///
///  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
///  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
///
///  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
///
///  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
///  Rte_Read_Stp_RoutineControl_HitCount = 0u;
///  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
///  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
///
///  CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
///
///
/// - Expectations:
///
///(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1,
///(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1,
///
///(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u,
///(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1,
///(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1,
///
///(Rte_Read_ppsAvacOut_HitCount, 1u,
///(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0,
///
///(Rte_Read_Pitch_PlausState_HitCount, 6u,
///(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE,
///
///(CtrlStp_boDiagStpOn, TRUE,
///
///(CtrlStp_nPosReq, CtrlStp_Simulation_Data.nSimPosReq,
///
///(CtrlStp_boTrainingState, TRUE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Init;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boStop = 2;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = TRUE;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_INVALID;
  //Step 3) Call FUT
  CtrlStp_WriteSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, CtrlStp_boStop, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, CtrlStp_eLvlElecR_NoDefect, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_SteplossRisk, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_SuccessfullyFinished, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR, CtrlStp_eLvlVoltR_NominalVoltage, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from slave are written correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
///  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_unTgtTmin = 4;
///  CtrlStp_boStop = 2;
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
///
///
///  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
///  CtrlStp_nPosReq = 2;
///
/// - Expectations:
///
///  CtrlStp_TgtAll.sLwrTarget.boStop, FALSE,
///  (CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin,
///  (Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 1u,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, CtrlStp_eLvlElecR_OpenCircuit,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_RefInProgress,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR, CtrlStp_eLvlVoltR_OverVoltage
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_unTgtTmin = 4;
  CtrlStp_boStop = 2;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
  CtrlStp_nPosReq = 2;
  //Step 3) Call FUT
  CtrlStp_WriteSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_RefInProgress, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR, CtrlStp_eLvlVoltR_OverVoltage, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from slave are written correctly
///			-
///
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   Preconditions
///  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
///  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_unTgtTmin = 4;
///  CtrlStp_boStop = 2;
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
///
///
///  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
///  CtrlStp_nPosReq = 0;
///
/// - Expectations:
///
///  CtrlStp_TgtAll.sLwrTarget.boStop, FALSE,
///  (CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin,
///  (Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 1u,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, CtrlStp_eLvlElecR_OpenCircuit,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_RefInProgress,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR, CtrlStp_eLvlVoltR_OverVoltage
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_unTgtTmin = 4;
  CtrlStp_boStop = 2;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
  CtrlStp_nPosReq = 0;
  //Step 3) Call FUT
  CtrlStp_WriteSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_WaitingForNewRefCmd, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR, CtrlStp_eLvlVoltR_UnderVoltage, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from slave are written correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
///  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_unTgtTmin = 4;
///  CtrlStp_boStop = 2;
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
///
///  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
///  CtrlStp_nPosReq = 0;
///
/// - Expectations:
///
///  (CtrlStp_TgtAll.sLwrTarget.boStop, FALSE,
///  (CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin,
///  (Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 1u,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_WaitingForNewRefCmd
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_unTgtTmin = 4;
  CtrlStp_boStop = 2;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
  CtrlStp_nPosReq = 0;
  //Step 3) Call FUT
  CtrlStp_WriteSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_WaitingForNewRefCmd, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from slave are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 1u;
///  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_NoInit;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_unTgtTmin = 4;
///  CtrlStp_boStop = 2;
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
///
///  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///  CtrlStp_sLevellingSignalsFromLeftToRight.eSigQty = CtrlStp_SIG_VALID;
///  CtrlStp_nPosReq = 0;
///
/// - Expectations:
///
///  (CtrlStp_TgtAll.sLwrTarget.boStop, FALSE,
///  (CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin,
///  (Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u,
///  (Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u,
///  (Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 1u,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR, CtrlStp_eLvlSteplossR_NoSteploss,
///  (CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR, CtrlStp_eLvlRefStateR_WaitingForNewRefCmd
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_boElecOL = TRUE;
  CtrlStp_boElecSC = FALSE;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_NoDefect;
  //Step 3) Call FUT
  CtrlStp_WriteSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, CtrlStp_eLvlElecR_OpenCircuit, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from slave are written correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
///  CtrlStp_boElecOL = FALSE;
///  CtrlStp_boElecSC = TRUE;
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
///  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
///  CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
///  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
///  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_NoDefect;
/// 
///
///- Expectations:
///
///  CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
///  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
///  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
///  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
///  Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
///  Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
///  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, CtrlStp_eLvlElecR_ShortCircuit
///  
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_boElecOL = FALSE;
  CtrlStp_boElecSC = TRUE;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_NoDefect;
  //Step 3) Call FUT
  CtrlStp_WriteSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR, CtrlStp_eLvlElecR_ShortCircuit, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteSlaveSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  : Check that if the signals from slave are written correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteSlaveSignals(void)
{
  Mt_CtrlStp_WriteSlaveSignals_TestCase_1();
  Mt_CtrlStp_WriteSlaveSignals_TestCase_2();
  Mt_CtrlStp_WriteSlaveSignals_TestCase_3();
  Mt_CtrlStp_WriteSlaveSignals_TestCase_4();
  Mt_CtrlStp_WriteSlaveSignals_TestCase_5();
  Mt_CtrlStp_WriteSlaveSignals_TestCase_6();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from master are written correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  \input //Step 2) Assign Input values
///  \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
///  \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
///  \input CtrlStp_boSubModeError = TRUE;
///  \input CtrlStp_boTrainingState = FALSE;
///  \input CtrlStp_boSlaveStop = TRUE;
///  \input CtrlStp_nTgtPos = 2;
///  \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Init;
///  \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
///  \input Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
///  \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
///  \input CtrlStp_boSlaveRefRequest = TRUE;
///  \input CtrlStp_boDiagStpOn = TRUE;
///  \input CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eBothActuators;
///  \input CtrlStp_nDiagPos = 2;
///  \input Rte_Read_DrvLedDiag_HitCount = 0u;
///  \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
///  \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  \input Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///
/// - Expectations:
///  \output sRte_Read_DrvLedDiag_HitCount, 1u, == );
///  \output Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
///  \output Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
///  \output Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
///  \output Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
///  \output CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, 0, == );
///  \output CtrlStp_TgtAll.sLwrTarget.boStop, CtrlStp_boStop, == );
///  \output CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_Referencing
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteMasterSignals_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  CtrlStp_boSubModeError = TRUE;
  CtrlStp_boTrainingState = FALSE;
  CtrlStp_boSlaveStop = TRUE;
  CtrlStp_nTgtPos = 2;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Init;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_boSlaveRefRequest = TRUE;
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eBothActuators;
  CtrlStp_nDiagPos = 2;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, CtrlStp_boStop, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_Referencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from master are written correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
///  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///  CtrlStp_boSubModeError = FALSE;
///  CtrlStp_boTrainingState = TRUE;
///  CtrlStp_boSlaveStop = FALSE;
///
///  CtrlStp_nTgtPos = 2;
///  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///
///  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
///  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
///
///  CtrlStp_boSlaveRefRequest = FALSE;
///
///  CtrlStp_boDiagStpOn = TRUE;
///  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eBothActuators;
///  CtrlStp_nDiagPos = 0;
///  Rte_Read_DrvLedDiag_HitCount = 0u;
///  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
///  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///  CtrlStp_unTgtTmin = 1;
///
/// - Expectations:
///
///  Rte_Read_DrvLedDiag_HitCount, 1u, == );
///  Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
///  (Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
///  (Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
///  (Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 1u, == );
///  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
///  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
///  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing,
///
//-----------------------------------------------------------------------------

void Mt_CtrlStp_WriteMasterSignals_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boSubModeError = FALSE;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_boSlaveStop = FALSE;
  CtrlStp_nTgtPos = 2;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_boSlaveRefRequest = FALSE;
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eBothActuators;
  CtrlStp_nDiagPos = 0;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_unTgtTmin = 1;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from master are written correctly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///   \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
///   \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///   \input CtrlStp_boSubModeError = FALSE;
///   \input CtrlStp_boTrainingState = TRUE;
///   \input CtrlStp_boSlaveStop = FALSE;
///   \input CtrlStp_nTgtPos = 2;
///   \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
///   \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///   \input Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
///   \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
///   \input CtrlStp_boSlaveRefRequest = FALSE;
///   \input CtrlStp_boDiagStpOn = FALSE;
///   \input CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
///   \input CtrlStp_nPosReq = 1;
///   \input CtrlStp_boVehAttitudeInvalid = TRUE;
///   \input Rte_Read_DrvLedDiag_HitCount = 0u;
///   \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
///   \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///   \input Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///   \input CtrlStp_unTgtTmin = 1;
///
/// - Expectations:
///
///  \output Rte_Read_DrvLedDiag_HitCount, 1u,  
///  \output Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, 
///  \output Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, 
///  \output Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, 
///  \output Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, 
///  \output CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, 
///  \output CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, 
///  \output CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, 
///
//-----------------------------------------------------------------------------

void Mt_CtrlStp_WriteMasterSignals_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boSubModeError = FALSE;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_boSlaveStop = FALSE;
  CtrlStp_nTgtPos = 2;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_boSlaveRefRequest = FALSE;
  CtrlStp_boDiagStpOn = FALSE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
  CtrlStp_nPosReq = 1;
  CtrlStp_boVehAttitudeInvalid = TRUE;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_unTgtTmin = 1;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if the signals from master are written correctly
///
///-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   Preconditions
///   \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
///   \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///   \input CtrlStp_boSubModeError = FALSE;
///   \input CtrlStp_boTrainingState = TRUE;
///   \input CtrlStp_boSlaveStop = FALSE;
///   \input CtrlStp_nTgtPos = 2;
///   \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
///   \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///   \input Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
///   \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
///   \input CtrlStp_boSlaveRefRequest = FALSE;
///   \input CtrlStp_boDiagStpOn = FALSE;
///   \input CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
///   \input CtrlStp_nPosReq = 0;
///   \input CtrlStp_boVehAttitudeInvalid = FALSE;
///   \input Rte_Read_DrvLedDiag_HitCount = 0u;
///   \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
///   \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///   \input Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
///   \input CtrlStp_unTgtTmin = 1;
///
/// - Preconditions:
///
/// - Expectations:
///
///  \output Rte_Read_DrvLedDiag_HitCount, 1u, == );
///  \output Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
///  \output Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
///  \output Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
///  \output Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
///  \output CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
///  \output CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
///  \output CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing
//-----------------------------------------------------------------------------

void Mt_CtrlStp_WriteMasterSignals_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boSubModeError = FALSE;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_boSlaveStop = FALSE;
  CtrlStp_nTgtPos = 2;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_boSlaveRefRequest = FALSE;
  CtrlStp_boDiagStpOn = FALSE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
  CtrlStp_nPosReq = 0;
  CtrlStp_boVehAttitudeInvalid = FALSE;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_unTgtTmin = 1;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : Check that if the signals from master are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_boSubModeError = FALSE;
/// \input CtrlStp_boTrainingState = FALSE;
/// \input CtrlStp_boSlaveStop = TRUE;
/// \input CtrlStp_nTgtPos = 2;
/// \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
/// \input Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
/// \input CtrlStp_boSlaveRefRequest = FALSE;
/// \input CtrlStp_boDiagStpOn = FALSE;
/// \input CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
/// \input CtrlStp_nPosReq = 0;
/// \input CtrlStp_boVehAttitudeInvalid = FALSE;
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
/// \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
/// \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
/// \input Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
/// \input CtrlStp_unTgtTmin = 1;
///
///   - Expectations:
///
/// \output Rte_Read_DrvLedDiag_HitCount, 1u, == );
/// \output Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
/// \output Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
/// \output CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
/// \output CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
/// \output CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteMasterSignals_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boSubModeError = FALSE;
  CtrlStp_boTrainingState = FALSE;
  CtrlStp_boSlaveStop = TRUE;
  CtrlStp_nTgtPos = 2;
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Norm;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_boSlaveRefRequest = FALSE;
  CtrlStp_boDiagStpOn = FALSE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
  CtrlStp_nPosReq = 0;
  CtrlStp_boVehAttitudeInvalid = FALSE;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount = 0u;
  CtrlStp_unTgtTmin = 1;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpStepperActual0_StatusSpinningFront_HitCount, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : Check that if the signals from master are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SafetyPos = -1;
/// \input CtrlStp_boSlaveRefRequest = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlStp_SIG_VALID;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_RefInProgress;
/// \input CtrlStp_boDiagStpOn = FALSE;
/// \input CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
/// \input CtrlStp_boSlaveSafetyPos = TRUE;
/// \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
/// \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
/// \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
/// \input CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
/// \input CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_HitCount, 1u, == );
/// \output  Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output  Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
/// \output  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
/// \output  CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
/// \output  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteMasterSignals_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SafetyPos = -1;
  CtrlStp_boSlaveRefRequest = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlStp_SIG_VALID;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_RefInProgress;
  CtrlStp_boDiagStpOn = FALSE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
  CtrlStp_boSlaveSafetyPos = TRUE;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
  CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : Check that if the signals from master are written correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SafetyPos = 6;
/// \input CtrlStp_boSlaveRefRequest = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlStp_SIG_VALID;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_RefInProgress;
/// \input CtrlStp_boDiagStpOn = FALSE;
/// \input CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
/// \input CtrlStp_boSlaveSafetyPos = TRUE;
/// \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
/// \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
/// \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
/// \input CtrlStp_sLevellingFeedbackFromRighToLeft.ePositionSiteD.unRPosLvl = 10u;
/// \input CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
/// \input CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_HitCount, 1u, == );
/// \output  Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output  Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
/// \output  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
/// \output  CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
/// \output  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteMasterSignals_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SafetyPos = 6;
  CtrlStp_boSlaveRefRequest = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty = CtrlStp_SIG_VALID;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlRefStateR = CtrlStp_eLvlRefStateR_RefInProgress;
  CtrlStp_boDiagStpOn = FALSE;
  CtrlStp_sStpControlRequest.eStpSide = CtrlStp_eLeftActuator;
  CtrlStp_boSlaveSafetyPos = TRUE;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  Rte_Read_DrvLedDiag_HitCount = 0u;
  CtrlStp_sLevellingFeedbackFromRighToLeft.ePositionSiteD.unRPosLvl = 10u;
  CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod = 0u;
  CtrlStp_TgtAll.sLwrTarget.boStop = TRUE;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
  //Step 3) Call FUT
  CtrlStp_WriteMasterSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.unMinStepPeriod, CtrlStp_unTgtTmin, == );
  AL_UNITTEST_CHECK(CtrlStp_TgtAll.sLwrTarget.boStop, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl, CtrlStp_eCmdRefSiteD_NoReferencing, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteMasterSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  : Check that if the signals from master are written correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteMasterSignals(void)
{
  Mt_CtrlStp_WriteMasterSignals_TestCase_1();
  Mt_CtrlStp_WriteMasterSignals_TestCase_2();
  Mt_CtrlStp_WriteMasterSignals_TestCase_3();
  Mt_CtrlStp_WriteMasterSignals_TestCase_4();
  Mt_CtrlStp_WriteMasterSignals_TestCase_5();
  Mt_CtrlStp_WriteMasterSignals_TestCase_6();
  Mt_CtrlStp_WriteMasterSignals_TestCase_7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects offset based on light functions
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// \input Rte_Read_DiagControl_AfsState_HitCount = 0u;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = 1;
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode = TRUE;
/// \input Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = FALSE;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_Afs_Signals_HitCount, 3u, =
/// \output  Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  Rte_Read_DiagControl_AfsState_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request = 1;
  Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode = TRUE;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = FALSE;
  //Step 3) Call FUT
  CtrlStp_DetectOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 3u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagSequenceMachine_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function does STP sequence machine for routine control correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_StepperRoutineControlRequest* test = { 0 };
/// \input CtrlStp_DiagSequenceMachine_Param1 = &test;
/// \input CtrlStp_boStartSequence = FALSE;
/// \input CtrlStp_ulDiagSequenceTimer = 2000u;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagSequenceMachine_RetVal, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagSequenceMachine_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_StepperRoutineControlRequest* test = { 0 };
  CtrlStp_DiagSequenceMachine_Param1 = &test;
  CtrlStp_boStartSequence = FALSE;
  CtrlStp_ulDiagSequenceTimer = 2000u;
  //Step 3) Call FUT
  CtrlStp_DiagSequenceMachine_RetVal = CtrlStp_DiagSequenceMachine(CtrlStp_DiagSequenceMachine_Param1, CtrlStp_DiagSequenceMachine_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagSequenceMachine_RetVal, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagSequenceMachine_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function does STP sequence machine for routine control correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_StepperRoutineControlRequest* test = { 0 };
/// \input CtrlStp_DiagSequenceMachine_Param1 = &test;
/// \input CtrlStp_boStartSequence = TRUE;
/// \input CtrlStp_DiagSequenceMachine_Param2 = 1;
///
///   - Expectations:
///
/// \output CtrlStp_DiagSequenceMachine_RetVal, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagSequenceMachine_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_StepperRoutineControlRequest* test = { 0 };
  CtrlStp_DiagSequenceMachine_Param1 = &test;
  CtrlStp_boStartSequence = TRUE;
  CtrlStp_DiagSequenceMachine_Param2 = 1;
  //Step 3) Call FUT
  CtrlStp_DiagSequenceMachine_RetVal = CtrlStp_DiagSequenceMachine(CtrlStp_DiagSequenceMachine_Param1, CtrlStp_DiagSequenceMachine_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagSequenceMachine_RetVal, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagSequenceMachine_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function does STP sequence machine for routine control correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_StepperRoutineControlRequest* eTest = { 0x11 };
/// \input CtrlStp_DiagSequenceMachine_Param1 = &eTest;
/// \input CtrlStp_boStartSequence = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 100000000u;
/// \input CtrlStp_DiagSequenceMachine_Param2 = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagSequenceMachine_RetVal, CtrlStp_eMovementToTop
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagSequenceMachine_TestCase_3(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_StepperRoutineControlRequest* eTest = { 0x11 };
  CtrlStp_DiagSequenceMachine_Param1 = &eTest;
  CtrlStp_boStartSequence = FALSE;
  LPTMR0_GetTimeElapsed_RetVal = 100000000u;
  CtrlStp_DiagSequenceMachine_Param2 = 1;
  //Step 3) Call FUT
  CtrlStp_DiagSequenceMachine_RetVal = CtrlStp_DiagSequenceMachine(CtrlStp_DiagSequenceMachine_Param1, CtrlStp_DiagSequenceMachine_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagSequenceMachine_RetVal, CtrlStp_eMovementToTop, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagSequenceMachine
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:: Check that if the function does STP sequence machine for routine control correctly  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagSequenceMachine(void)
{
  Mt_CtrlStp_DiagSequenceMachine_TestCase_1();
  Mt_CtrlStp_DiagSequenceMachine_TestCase_2();
  Mt_CtrlStp_DiagSequenceMachine_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadEnvironmentSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads enviromental signals properly
///			-
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// - Preconditions:
///
///  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
///  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
///  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_SECU;
///
/// - Expectations:
///CtrlStp_boConVehIgnition, TRUE
///CtrlStp_boPowertrainActive, TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadEnvironmentSignals(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTA_SECU;
  //Step 3) Call FUT
  CtrlStp_ReadEnvironmentSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boConVehIgnition, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_boPowertrainActive, TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_1
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
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = TRUE;
/// \input  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_eLvlAdjHeadlampFault_L, CtrlStp_eNo_Failure
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eLvlAdjHeadlampFault_L, CtrlStp_eNo_Failure, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_2
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output  CtrlStp_eLvlAdjHeadlampFault_R, CtrlStp_eNo_Failure
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eLvlAdjHeadlampFault_R, CtrlStp_eNo_Failure, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that the function verify for levelling adjust headlamp fault 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// \input boErrorCheck = TRUE;
///
///   - Expectations:
///
/// \output boErrorCheck, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  boErrorCheck = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boErrorCheck, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_4
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input boErrorCheck = FALSE;
/// \input CtrlStp_ulTimeElapsed_us = 1000;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_eLvlAdjHeadlampFault_L, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  boErrorCheck = FALSE;
  CtrlStp_ulTimeElapsed_us = 1000;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eLvlAdjHeadlampFault_L, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_5
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// \input boErrorCheck = FALSE;
/// \input CtrlStp_ulTimeElapsed_us = 1000;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output boErrorCheck, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  boErrorCheck = FALSE;
  CtrlStp_ulTimeElapsed_us = 1000;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boErrorCheck, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_6
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// \input boErrorCheck = FALSE;
/// \input CtrlStp_ulTimeElapsed_us = 0;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  boErrorCheck = FALSE;
  CtrlStp_ulTimeElapsed_us = 0;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_7
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_boElecOL = FALSE;
/// \input CtrlStp_boElecSC = FALSE;
/// \input CtrlStp_eTempMode = 4;
/// \input boErrorCheck = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
///
///   - Expectations:
///
/// \output  boErrorCheck, TRUE
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_boElecOL = FALSE;
  CtrlStp_boElecSC = FALSE;
  CtrlStp_eTempMode = 4;
  boErrorCheck = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boErrorCheck, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_8
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
/// \input CtrlStp_ulTimeElapsed_us = 1000;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  boErrorCheck, TRUE
/// \output  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_ulTimeElapsed_us = 1000;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boErrorCheck, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_9
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
/// \input CtrlStp_ulTimeElapsed_us = 1000;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output boErrorCheck, TRUE
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_ulTimeElapsed_us = 1000;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boErrorCheck, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_10
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ulTimeElapsed_us = 0;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;
/// \input boSlaveErrorCheck = TRUE;
///
///   - Expectations:
///
/// \output boErrorCheck, TRUE
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ulTimeElapsed_us = 0;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;
  boSlaveErrorCheck = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boErrorCheck, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_11
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ulTimeElapsed_us = 0;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;
/// \input boSlaveErrorCheck = FALSE;
/// \input CtrlStp_ulTimeElapsedSlave_us = 1000;
///
///   - Expectations:
///
/// \output  CtrlStp_eLvlAdjHeadlampFault_R, CtrlStp_eFrozen_Failure
/// \output  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ulTimeElapsed_us = 0;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;
  boSlaveErrorCheck = FALSE;
  CtrlStp_ulTimeElapsedSlave_us = 1000;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eLvlAdjHeadlampFault_R, CtrlStp_eFrozen_Failure, == );
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_12
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ulTimeElapsed_us = 0;
/// \input CtrlStp_ulTimeElapsedSlave_us = 0;
/// \input boSlaveErrorCheck = FALSE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_NoSteploss;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_NominalVoltage;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_12(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ulTimeElapsed_us = 0;
  CtrlStp_ulTimeElapsedSlave_us = 0;
  boSlaveErrorCheck = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_NoSteploss;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_NominalVoltage;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_13
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input boSlaveErrorCheck = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_13(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  boSlaveErrorCheck = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_14
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input boSlaveErrorCheck = FALSE;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
/// \input CtrlStp_ulTimeElapsedSlave_us = 1000;
///
///   - Expectations:
///
/// \output CtrlStp_eLvlAdjHeadlampFault_R, CtrlStp_eTransition_Failure
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_14(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  boSlaveErrorCheck = FALSE;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
  CtrlStp_ulTimeElapsedSlave_us = 1000;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eLvlAdjHeadlampFault_R, CtrlStp_eTransition_Failure, == );
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_15
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function verify for levelling adjust headlamp fault 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input boSlaveErrorCheck = FALSE;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
/// \input CtrlStp_ulTimeElapsedSlave_us = 0;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_15(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  boSlaveErrorCheck = FALSE;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
  CtrlStp_ulTimeElapsedSlave_us = 0;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_16
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input boSlaveErrorCheck = FALSE;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_OverVoltage;
/// \input CtrlStp_ulTimeElapsedSlave_us = 0;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_16(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)4;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltOver = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_NoSteploss;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlElecR = CtrlStp_eLvlElecR_Reserved;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlTemperatureR = CtrlStp_eLvlTemperatureR_ColdTemperature;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlVoltR = CtrlStp_eLvlVoltR_NotUsed;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_17
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
/// \input CtrlStp_boElecOL = TRUE;
/// \input boErrorCheck = TRUE;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_17(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_boElecOL = TRUE;
  boErrorCheck = TRUE;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_18
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
/// \input CtrlStp_boElecOL = TRUE;
/// \input boErrorCheck = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 1000000u;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_18(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_boElecOL = TRUE;
  boErrorCheck = FALSE;
  LPTMR0_GetTimeElapsed_RetVal = 1000000u;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_19
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
/// \input CtrlStp_boElecOL = TRUE;
/// \input boErrorCheck = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 0u;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_19(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_boElecOL = TRUE;
  boErrorCheck = FALSE;
  LPTMR0_GetTimeElapsed_RetVal = 0u;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_20
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_boElecOL = TRUE;
/// \input boErrorCheck = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 1000000u;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_20(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_boElecOL = TRUE;
  boErrorCheck = FALSE;
  LPTMR0_GetTimeElapsed_RetVal = 1000000u;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_21
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
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
/// \input CtrlStp_boElecOL = FALSE;
/// \input CtrlStp_boElecSC = FALSE;
/// \input CtrlStp_eTempMode = (tieStpTempMode)4;
/// \input CtrlStp_eTempMode = (tieStpTempMode)5;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
/// \input boErrorCheck = FALSE;
/// \input LPTMR0_GetTimeElapsed_RetVal = 0u;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_21(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  CtrlStp_boElecOL = FALSE;
  CtrlStp_boElecSC = FALSE;
  CtrlStp_eTempMode = (tieStpTempMode)4;
  CtrlStp_eTempMode = (tieStpTempMode)5;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
  boErrorCheck = FALSE;
  LPTMR0_GetTimeElapsed_RetVal = 0u;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadLvlAdjHeadlampFaultStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R, CtrlStp_eLvlAdjHeadlampFault_R, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function verify for levelling adjust headlamp fault
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus(void)
{
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_1();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_2();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_3();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_4();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_5();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_6();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_7();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_8();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_9();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_10();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_11();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_12();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_13();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_14();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_15();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_16();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_17();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_18();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_19();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_20();
  Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus_TestCase_21();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadSlaveSignals_TestCase_1
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
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Positive;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 10;
/// \input CtrlStp_boRefRequest = FALSE;
///
///   - Expectations:
///
/// \output Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u
/// \output CtrlStp_boRefRequest, TRUE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadSlaveSignals_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Positive;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 10;
  CtrlStp_boRefRequest = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReadSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_boRefRequest, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadSlaveSignals_TestCase_2
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
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 100;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
///
///   - Expectations:
///
/// \output Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u
/// \output CtrlStp_boRefRequest, FALSE
///
//-----------------------------------------------------------------------------

void Mt_CtrlStp_ReadSlaveSignals_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 100;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_boRefRequest, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadSlaveSignals_TestCase_3
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
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
/// \input CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 100;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
/// \input CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
///
///   - Expectations:
///
/// \output Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u
/// \output CtrlStp_boRefRequest, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadSlaveSignals_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_NoReferencing;
  CtrlStp_sLevellingSignalsFromLeftToRight.eRCmdPosLvl.unRCmdPosLvl = 100;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
  CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
  //Step 3) Call FUT
  CtrlStp_ReadSlaveSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_boRefRequest, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadSlaveSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function read slave signals
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadSlaveSignals(void)
{
  Mt_CtrlStp_ReadSlaveSignals_TestCase_1();
  Mt_CtrlStp_ReadSlaveSignals_TestCase_2();
  Mt_CtrlStp_ReadSlaveSignals_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckFrame350Recovery_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if Frame 350 was lost and recovered from it
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DEM_350Lost_NotifyStatus_HitCount = 0u;
/// \input Rte_Read_DEM_350Lost_NotifyStatus_Param1 = TRUE;
/// \input CtrlStp_boVehAttitudeInvalid = TRUE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
///
///   - Expectations:
///
/// \output Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 2u
/// \output Rte_Read_DEM_350Lost_NotifyStatus_Param1, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckFrame350Recovery_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_DEM_350Lost_NotifyStatus_HitCount = 0u;
  Rte_Read_DEM_350Lost_NotifyStatus_Param1 = TRUE;
  CtrlStp_boVehAttitudeInvalid = TRUE;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
  //Step 3) Call FUT
  CtrlStp_CheckFrame350Recovery();
  CtrlStp_boVehAttitudeInvalid = FALSE;
  CtrlStp_CheckFrame350Recovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_Param1, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckFrame350Recovery_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if Frame 350 was lost and recovered from it 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DEM_350Lost_NotifyStatus_HitCount = 0u;
/// \input Rte_Read_DEM_350Lost_NotifyStatus_Param1 = FALSE;
/// \input CtrlStp_boVehAttitudeInvalid = TRUE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
///
///   - Expectations:
///
/// \output Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u,
/// \output Rte_Read_DEM_350Lost_NotifyStatus_Param1, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckFrame350Recovery_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_DEM_350Lost_NotifyStatus_HitCount = 0u;
  Rte_Read_DEM_350Lost_NotifyStatus_Param1 = FALSE;
  CtrlStp_boVehAttitudeInvalid = TRUE;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
  //Step 3) Call FUT
  CtrlStp_CheckFrame350Recovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_Param1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckFrame350Recovery
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if Frame 350 was lost and recovered from it
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckFrame350Recovery(void)
{
  Mt_CtrlStp_CheckFrame350Recovery_TestCase_1();
  Mt_CtrlStp_CheckFrame350Recovery_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 3;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 0;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_SteplossRisk
/// \output CtrlStp_DiagStatus.boStpIsMoving, TRUE
/// \output CtrlStp_DiagStatus.boStpCommDef, TRUE
/// \output CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_NoWarning
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
  CtrlStp_ActAll.sLwrActual.nPosition = 3;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 0;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_SteplossRisk, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpIsMoving, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpCommDef, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_NoWarning, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
/// \input  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
/// \input  CtrlStp_ActAll.sLwrActual.nPosition = 3;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss
/// \output  CtrlStp_DiagStatus.boStpIsMoving, FALSE, 
/// \output  CtrlStp_DiagStatus.boStpCommDef, FALSE, 
/// \output  CtrlStp_DiagStatus.eStatStpThermalState, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
  CtrlStp_ActAll.sLwrActual.nPosition = 3;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 1;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 3;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 2;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss
/// \output  CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
/// \output  CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
/// \output  CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
  CtrlStp_ActAll.sLwrActual.nPosition = 3;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 2;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that if the values for levelling diagnosis are returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
/// \input  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
/// \input  CtrlStp_ActAll.sLwrActual.nPosition = 3;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 3;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss
/// \output  CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
/// \output  CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
/// \output  CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
  CtrlStp_ActAll.sLwrActual.nPosition = 3;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 3;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 3;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 4;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss
/// \output  CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
/// \output  CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
/// \output  CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 2;
  CtrlStp_ActAll.sLwrActual.nPosition = 3;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boCommDefect = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 4;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpStepLoss, CtrlStp_eLvlSteplossR_NoSteploss, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpIsMoving, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpCommDef, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eTempMode = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_ColdTemperature
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eTempMode = 1;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_ColdTemperature, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eTempMode = 2;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureWarning
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eTempMode = 2;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureWarning, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eTempMode = 3;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureShutdown
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eTempMode = 3;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureShutdown, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values for levelling diagnosis are returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eTempMode = 4;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureShutdown
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eTempMode = 4;
  //Step 3) Call FUT
  CtrlStp_GetDiagStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureShutdown, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the values for levelling diagnosis are returned in a proper way
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagStatus(void)
{
  Mt_CtrlStp_GetDiagStatus_TestCase_1();
  Mt_CtrlStp_GetDiagStatus_TestCase_2();
  Mt_CtrlStp_GetDiagStatus_TestCase_3();
  Mt_CtrlStp_GetDiagStatus_TestCase_4();
  Mt_CtrlStp_GetDiagStatus_TestCase_5();
  Mt_CtrlStp_GetDiagStatus_TestCase_6();
  Mt_CtrlStp_GetDiagStatus_TestCase_7();
  Mt_CtrlStp_GetDiagStatus_TestCase_8();
  Mt_CtrlStp_GetDiagStatus_TestCase_9();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetDiagLvl
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that function get and return value of DIAG_LVL correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
///  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
///  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///  CtrlStp_boSubModeError = FALSE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
///  
///
/// - Expectations:
///         CtrlStp_GetDiagLvl_RetVal, FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetDiagLvl(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boSubModeError = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = FALSE;
  //Step 3) Call FUT
  CtrlStp_GetDiagLvl_RetVal = CtrlStp_GetDiagLvl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetDiagLvl_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetCmdRef_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the value of referencing command is returned correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// 
/// CtrlStp_boSlaveRefRequest                                        = TRUE
/// CtrlStp_boPowertrainActive                                       = TRUE
/// Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                      = SIG_VALID
/// Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = 1
/// Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 0u
/// CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty              = CtrlStp_SIG_VALID
/// CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX             = 20u
/// 
/// - Expectations:
///         CtrlStp_GetCmdRef_RetVal              = CtrlStp_eCmdRefSiteD_Referencing
///         Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetCmdRef_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boSlaveRefRequest                                        = TRUE;
  CtrlStp_boPowertrainActive                                       = TRUE;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                      = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo           = 1;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 0u;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eSigQty              = CtrlStp_SIG_VALID;
  CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX             = 20u;
  //Step 3) Call FUT
  CtrlStp_GetCmdRef_RetVal = CtrlStp_GetCmdRef();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetCmdRef_RetVal             , CtrlStp_eCmdRefSiteD_Referencing, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                               1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetCmdRef_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the value of referencing command is returned correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// 
/// Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u
/// Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 5000u
/// CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX             = 20u
/// 
/// - Expectations:
///         CtrlStp_GetCmdRef_RetVal              = CtrlStp_eCmdRefSiteD_NoReferencing
///         Rte_Read_SysMon_VehicleSpeed_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetCmdRef_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 5000u;
  CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX             = 20u;
  //Step 3) Call FUT
  CtrlStp_GetCmdRef_RetVal = CtrlStp_GetCmdRef();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetCmdRef_RetVal             , CtrlStp_eCmdRefSiteD_NoReferencing, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                                 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetCmdRef
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the value of referencing command is returned correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetCmdRef(void)
{
  Mt_CtrlStp_GetCmdRef_TestCase_1();
  Mt_CtrlStp_GetCmdRef_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 0;
/// \input CtrlStp_GetOffset_Param2 = 0;
/// \input CtrlStp_GetOffset_Param3 = TRUE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 0;
  CtrlStp_GetOffset_Param2 = 0;
  CtrlStp_GetOffset_Param3 = TRUE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 0;
/// \input CtrlStp_GetOffset_Param2 = 0;
/// \input CtrlStp_GetOffset_Param3 = TRUE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 0;
  CtrlStp_GetOffset_Param2 = 0;
  CtrlStp_GetOffset_Param3 = TRUE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_GetOffset_Param1 = eCtrlAFS_Town;
/// \input  CtrlStp_GetOffset_Param2 = 0;
/// \input  CtrlStp_GetOffset_Param3 = FALSE;
/// \input  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Town_Ped_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_Town;
  CtrlStp_GetOffset_Param2 = 0;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Town_Ped_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_Town;
/// \input CtrlStp_GetOffset_Param2 = 0;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Town_Ped_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_Town;
  CtrlStp_GetOffset_Param2 = 0;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Town_Ped_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
/// \input CtrlStp_GetOffset_Param2 = TRUE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_MW_Boost_L = 2
///
///   - Expectations:
///
/// \output  snOffsetPercentage, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
  CtrlStp_GetOffset_Param2 = TRUE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_MW_Boost_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_MW_L = 2; 
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_MW_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
/// \input CtrlStp_GetOffset_Param2 = TRUE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
  CtrlStp_GetOffset_Param2 = TRUE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_Motorway;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherLhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherLhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherLhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_BDW_LHD_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherLhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_BDW_LHD_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherRhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_BDW_RHD_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherRhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_BDW_RHD_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_12
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eGfhbCmd_Off;
/// \input CtrlStp_GetOffset_Param2 = eCtrlAFS_BadWeatherRhd;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input CtrlStp_GetOffset_Param4 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_12(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_BadWeatherRhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_13
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyLhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_13(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyLhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_14
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyLhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Foggy_LHD_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_14(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyLhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Foggy_LHD_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_15
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyRhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Foggy_RHD_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_15(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyRhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Foggy_RHD_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_16
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyRhd;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_16(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = eCtrlAFS_FoggyRhd;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_17
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 8;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_17(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 8;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 8;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_18(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 8;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = FALSE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 0;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = TRUE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_19(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 0;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = TRUE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 0;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = TRUE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_20(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 0;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = TRUE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = 0;
/// \input CtrlStp_GetOffset_Param2 = FALSE;
/// \input CtrlStp_GetOffset_Param3 = TRUE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset_TestCase_21(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_GetOffset_Param1 = 0;
  CtrlStp_GetOffset_Param2 = FALSE;
  CtrlStp_GetOffset_Param3 = TRUE;
  snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_HB_L = 2;
  //Step 3) Call FUT
  CtrlStp_GetOffset(CtrlStp_GetOffset_Param1, CtrlStp_GetOffset_Param2, CtrlStp_GetOffset_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(snOffsetPercentage, 0, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the value for offset is returned for each light function 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetOffset(void)
{
  Mt_CtrlStp_GetOffset_TestCase_1();
  Mt_CtrlStp_GetOffset_TestCase_2();
  Mt_CtrlStp_GetOffset_TestCase_3();
  Mt_CtrlStp_GetOffset_TestCase_4();
  Mt_CtrlStp_GetOffset_TestCase_5();
  Mt_CtrlStp_GetOffset_TestCase_6();
  Mt_CtrlStp_GetOffset_TestCase_7();
  Mt_CtrlStp_GetOffset_TestCase_8();
  Mt_CtrlStp_GetOffset_TestCase_9();
  Mt_CtrlStp_GetOffset_TestCase_10();
  Mt_CtrlStp_GetOffset_TestCase_11();
  Mt_CtrlStp_GetOffset_TestCase_12();
  Mt_CtrlStp_GetOffset_TestCase_13();
  Mt_CtrlStp_GetOffset_TestCase_14();
  Mt_CtrlStp_GetOffset_TestCase_15();
  Mt_CtrlStp_GetOffset_TestCase_16();
  Mt_CtrlStp_GetOffset_TestCase_17();
  Mt_CtrlStp_GetOffset_TestCase_18();
  Mt_CtrlStp_GetOffset_TestCase_19();
  Mt_CtrlStp_GetOffset_TestCase_20();
  Mt_CtrlStp_GetOffset_TestCase_21();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eGfhbCmd_On;
/// \input CtrlStp_GetOffset_Param2 = 8;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input CtrlStp_GetOffset_Param4 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ApplyOffset_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ApplyOffset_Param1 = 10;
  CtrlStp_ApplyOffset_Param2 = 20;
  CtrlStp_ApplyOffset_Param3 = eGfhbCmd_On;
  CtrlStp_ApplyOffset_Param4 = TRUE;
  ulHBTimer = 0u;
  boTimerStart = FALSE;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  CtrlStp_nOffset = 0;
  //Step 3) Call FUT
  CtrlStp_ApplyOffset(CtrlStp_ApplyOffset_Param1, CtrlStp_ApplyOffset_Param2, CtrlStp_ApplyOffset_Param3, CtrlStp_ApplyOffset_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulHBTimer, 1000u, == );
  AL_UNITTEST_CHECK(boTimerStart, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nOffset, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eGfhbCmd_On;
/// \input CtrlStp_GetOffset_Param2 = 8;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input CtrlStp_GetOffset_Param4 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ApplyOffset_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ApplyOffset_Param1 = 10;
  CtrlStp_ApplyOffset_Param2 = 20;
  CtrlStp_ApplyOffset_Param3 = eGfhbCmd_On;
  CtrlStp_ApplyOffset_Param4 = TRUE;
  ulHBTimer = 0u;
  boTimerStart = TRUE;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  CtrlStp_nOffset = 0;
  //Step 3) Call FUT
  CtrlStp_ApplyOffset(CtrlStp_ApplyOffset_Param1, CtrlStp_ApplyOffset_Param2, CtrlStp_ApplyOffset_Param3, CtrlStp_ApplyOffset_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulHBTimer, 0u, == );
  AL_UNITTEST_CHECK(boTimerStart, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nOffset, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eGfhbCmd_On;
/// \input CtrlStp_GetOffset_Param2 = 8;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input CtrlStp_GetOffset_Param4 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ApplyOffset_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ApplyOffset_Param1 = 10;
  CtrlStp_ApplyOffset_Param2 = 20;
  CtrlStp_ApplyOffset_Param3 = eGfhbCmd_On;
  CtrlStp_ApplyOffset_Param4 = TRUE;
  ulHBTimer = 1001u;
  boTimerStart = TRUE;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  CtrlStp_nOffset = 0;
  //Step 3) Call FUT
  CtrlStp_ApplyOffset(CtrlStp_ApplyOffset_Param1, CtrlStp_ApplyOffset_Param2, CtrlStp_ApplyOffset_Param3, CtrlStp_ApplyOffset_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulHBTimer, 1001u, == );
  AL_UNITTEST_CHECK(boTimerStart, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nOffset, 20, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the value for offset is returned for each light function  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_GetOffset_Param1 = eGfhbCmd_On;
/// \input CtrlStp_GetOffset_Param2 = 8;
/// \input CtrlStp_GetOffset_Param3 = FALSE;
/// \input CtrlStp_GetOffset_Param4 = FALSE;
/// \input snOffsetPercentage;// = 0; // offset from coding is given in 0.1%
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingData.AfsOffset_Left.snAvacStp_AfsLevelling_Off_L = 2;
///
///   - Expectations:
///
/// \output snOffsetPercentage, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ApplyOffset_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ApplyOffset_Param1 = 10;
  CtrlStp_ApplyOffset_Param2 = 20;
  CtrlStp_ApplyOffset_Param3 = eGfhbCmd_Off;
  CtrlStp_ApplyOffset_Param4 = TRUE;
  ulHBTimer = 1001u;
  boTimerStart = TRUE;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  CtrlStp_nOffset = 0;
  //Step 3) Call FUT
  CtrlStp_ApplyOffset(CtrlStp_ApplyOffset_Param1, CtrlStp_ApplyOffset_Param2, CtrlStp_ApplyOffset_Param3, CtrlStp_ApplyOffset_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulHBTimer, 1001u, == );
  AL_UNITTEST_CHECK(boTimerStart, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_nOffset, 20, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the value for offset is returned for each light function 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ApplyOffset(void)
{
  Mt_CtrlStp_ApplyOffset_TestCase_1();
  Mt_CtrlStp_ApplyOffset_TestCase_2();
  Mt_CtrlStp_ApplyOffset_TestCase_3();
  Mt_CtrlStp_ApplyOffset_TestCase_4();

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_EntryErr
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if it is set properly state Error in entry function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Err;
/// \input CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalErr;
/// \input CtrlStp_Status.ucLWRSpeed = CTRLSTP_SignalErr;
///
///   - Expectations:
///
/// \output CtrlStp_Status.ucLWRState, eStpSpnStatus_Err
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_EntryErr(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Err;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalErr;
  CtrlStp_Status.ucLWRSpeed = CTRLSTP_SignalErr;
  //Step 3) Call FUT
  CtrlStp_EntryErr();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRState, eStpSpnStatus_Err, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_EntryDis
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that it is set properly state Disabled in entry function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Dis;
/// \input CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalDis;
/// \input CtrlStp_Status.ucLWRSpeed = CTRLSTP_SignalDis;
///
///   - Expectations:
///
/// \output CtrlStp_Status.ucLWRState, eStpSpnStatus_Dis
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_EntryDis(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Dis;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalDis;
  CtrlStp_Status.ucLWRSpeed = CTRLSTP_SignalDis;
  //Step 3) Call FUT
  CtrlStp_EntryDis();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRState, eStpSpnStatus_Dis, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LvlStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the status for automaticc levelling is stored 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Enable = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpLevelStatus, CtrlStp_eLvlStatus_NotImplemented
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LvlStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Enable = 0u;
  //Step 3) Call FUT
  CtrlStp_LvlStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpLevelStatus, CtrlStp_eLvlStatus_NotImplemented, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LvlStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the status for automaticc levelling is stored
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpLevelStatus, CtrlStp_eLvlStatus_Inhibited
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LvlStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = TRUE;
  //Step 3) Call FUT
  CtrlStp_LvlStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpLevelStatus, CtrlStp_eLvlStatus_Inhibited, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LvlStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the status for automaticc levelling is stored
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_State.eMain = CtrlStp_eState_Fail;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpLevelStatus, CtrlStp_eLvlStatus_InDefect
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LvlStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_State.eMain = CtrlStp_eState_Fail;
  //Step 3) Call FUT
  CtrlStp_LvlStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpLevelStatus, CtrlStp_eLvlStatus_InDefect, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LvlStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the status for automaticc levelling is stored 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
/// \input CtrlStp_State.eMain = CtrlStp_eState_Adj;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpLevelStatus, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LvlStatus_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltUSSM = FALSE;
  CtrlStp_State.eMain = CtrlStp_eState_Adj;
  //Step 3) Call FUT
  CtrlStp_LvlStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpLevelStatus, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LvlStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that if the status for automaticc levelling is stored 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LvlStatus(void)
{
  Mt_CtrlStp_LvlStatus_TestCase_1();
  Mt_CtrlStp_LvlStatus_TestCase_2();
  Mt_CtrlStp_LvlStatus_TestCase_3();
  Mt_CtrlStp_LvlStatus_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagStpTakeOver_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does takeover of the stepper using the diag routine control 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
///
///   - Expectations:
///
/// \output  CtrlStp_boDiagStpOn, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagStpTakeOver_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
  //Step 3) Call FUT
  CtrlStp_DiagStpTakeOver();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagStpTakeOver_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does takeover of the stepper using the diag routine control  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Stop;
///
///   - Expectations:
///
/// \output CtrlStp_boDiagStpOn, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagStpTakeOver_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Stop;
  //Step 3) Call FUT
  CtrlStp_DiagStpTakeOver();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagStpTakeOver_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does takeover of the stepper using the diag routine control  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = FALSE;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagStpTakeOver_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = FALSE;
  //Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
  //Step 3) Call FUT
  CtrlStp_DiagStpTakeOver();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_Param1.boRequestStatus, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagStpTakeOver_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does takeover of the stepper using the diag routine control  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = (uint8)VESState_Start;
///
///   - Expectations:
///
/// \output CtrlStp_boDiagStpOn, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagStpTakeOver_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = (uint8)VESState_Start;
  //Step 3) Call FUT
  CtrlStp_DiagStpTakeOver();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagStpTakeOver_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does takeover of the stepper using the diag routine control  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = TRUE;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input Rte_Read_Stp_RoutineControl_Param1.ucStartSequence =  1u;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input CtrlStp_boDiagStpOn = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_boDiagStpOn, TRUE, == );
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 2u
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagStpTakeOver_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = TRUE;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
  Rte_Read_Stp_RoutineControl_Param1.ucStartSequence =  1u;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  CtrlStp_boDiagStpOn = FALSE;
  //Step 3) Call FUT
  CtrlStp_DiagStpTakeOver();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagStpTakeOver
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function does takeover of the stepper using the diag routine control 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagStpTakeOver(void)
{
  Mt_CtrlStp_DiagStpTakeOver_TestCase_1();
  Mt_CtrlStp_DiagStpTakeOver_TestCase_2();
  Mt_CtrlStp_DiagStpTakeOver_TestCase_3();
  Mt_CtrlStp_DiagStpTakeOver_TestCase_4();
  Mt_CtrlStp_DiagStpTakeOver_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_PosDiagStat_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function stores the position when the stepper is in defect status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_nTgtPos = 302;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.boStpPosDef, TRUE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_PosDiagStat_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_nTgtPos = 302;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  //Step 3) Call FUT
  CtrlStp_PosDiagStat();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpPosDef, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_PosDiagStat_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function stores the position when the stepper is in defect status 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_nTgtPos = 100;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.boStpPosDef, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_PosDiagStat_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_nTgtPos = 100;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  //Step 3) Call FUT
  CtrlStp_PosDiagStat();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.boStpPosDef, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_PosDiagStat
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the function stores the position when the stepper is in defect status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_PosDiagStat(void)
{
  Mt_CtrlStp_PosDiagStat_TestCase_1();
  Mt_CtrlStp_PosDiagStat_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadCommonSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function read common signals for both slave and master ecu in a proper way
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
///  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
///  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
///  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.nPosition = 0;
///  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
///  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 2;// hot temperature warning
///  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 3; // hot temperature stop
///  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
///
/// - Expectations:
///Rte_Read_SysMon_VehNetState_Param1.eSigQty, 0
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadCommonSignals(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Ignition;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.nPosition = 0;
  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsFatalError = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 2;// hot temperature warning
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = 3; // hot temperature stop
  CtrlStp_ActAll.sLwrActual.sStatusError.boVoltNorm = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReadCommonSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_Param1.eSigQty, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefDelay_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for active referencing delay 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_unRefDelayCnt = 2;
///
///   - Expectations:
///
/// \output CtrlStp_CondRefDelay_RetVal1, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefDelay_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_unRefDelayCnt = 2;
  //Step 3) Call FUT
  CtrlStp_CondRefDelay_RetVal1 = CtrlStp_CondRefDelay();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefDelay_RetVal1, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefDelay_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for active referencing delay 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input  CtrlStp_unRefDelayCnt = 0;
///
///   - Expectations:
///
/// \output CtrlStp_CondRefDelay_RetVal1, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefDelay_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_unRefDelayCnt = 0;
  //Step 3) Call FUT
  CtrlStp_CondRefDelay_RetVal1 = CtrlStp_CondRefDelay();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefDelay_RetVal1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefDelay_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for active referencing delay 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_unRefDelayCnt = 0;
///
///   - Expectations:
///
/// \output CtrlStp_CondRefDelay_RetVal1, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefDelay_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_unRefDelayCnt = 0;
  //Step 3) Call FUT
  CtrlStp_CondRefDelay_RetVal1 = CtrlStp_CondRefDelay();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefDelay_RetVal1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefDelay
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check for active referencing delay
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefDelay(void)
{
  Mt_CtrlStp_CondRefDelay_TestCase_1();
  Mt_CtrlStp_CondRefDelay_TestCase_2();
  Mt_CtrlStp_CondRefDelay_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_TempCheck_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function limit Tmin based on low temperature condition 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_TempCheck_Param1 = 1;
/// \input CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT = 2;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boLowTemp = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_TempCheck_RetVal1, 2
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_TempCheck_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_TempCheck_Param1 = 1;
  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT = 2;
  CtrlStp_ActAll.sLwrActual.sStatusError.boLowTemp = TRUE;
  //Step 3) Call FUT
  CtrlStp_TempCheck_RetVal1 = CtrlStp_TempCheck(CtrlStp_TempCheck_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TempCheck_RetVal1, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_TempCheck_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function limit Tmin based on low temperature condition  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_TempCheck_Param1 = 10;
/// \input CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT = 2;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boLowTemp = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_TempCheck_RetVal1, 10
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_TempCheck_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_TempCheck_Param1 = 10;
  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT = 2;
  CtrlStp_ActAll.sLwrActual.sStatusError.boLowTemp = FALSE;
  //Step 3) Call FUT
  CtrlStp_TempCheck_RetVal1 = CtrlStp_TempCheck(CtrlStp_TempCheck_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_TempCheck_RetVal1, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_TempCheck
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function limit Tmin based on low temperature condition  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_TempCheck(void)
{
  Mt_CtrlStp_TempCheck_TestCase_1();
  Mt_CtrlStp_TempCheck_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetContinMove_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function gets target value for continous movement
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod = 10;
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange = 3;
///
///   - Expectations:
///
/// \output CtrlStp_GetContinMove_RetVal1, 15
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetContinMove_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod = 10;
  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange = 3;
  //Step 3) Call FUT
  for (int i = 0; i <= (CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod); i++)
  {
    CtrlStp_GetContinMove_RetVal1 = CtrlStp_GetContinMove();
  }
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetContinMove_RetVal1, 15, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetContinMove_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function gets target value for continous movement 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod = 0;
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange = 3;
///
///   - Expectations:
///
/// \output CtrlStp_GetContinMove_RetVal1, 12
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetContinMove_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod = 0;
  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange = 3;
  //Step 3) Call FUT
  CtrlStp_GetContinMove_RetVal1 = CtrlStp_GetContinMove();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetContinMove_RetVal1, 12, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetContinMove
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the function gets target value for continous movement
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetContinMove(void)
{
  Mt_CtrlStp_GetContinMove_TestCase_1();
  Mt_CtrlStp_GetContinMove_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check if there is a transition to GFHB Curtain Deactivation and a correction of the offset is required from HB offset to any other offset
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1 = 3;
/// \input CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2 = TRUE;
///
///   - Expectations:
///
/// \output  boLastHBCmd, 0
/// \output  CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1 = 3;
  CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2 = TRUE;
  static boolean boLastHBCmd;
  //Step 3) Call FUT
  CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1 = CtrlStp_DetectAfsOffsetCurtainDeactivation(CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1, CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2);
  CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2 = FALSE;
  CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1 = CtrlStp_DetectAfsOffsetCurtainDeactivation(CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1, CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(boLastHBCmd, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1, 1, == );//------------------------------------------------------false
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if there is a transition to GFHB Curtain Deactivation and a correction of the offset is required from HB offset to any other offset 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1 = 0;
/// \input CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2 = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1 = 0;
  CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2 = FALSE;
  //Step 3) Call FUT
  CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1 = CtrlStp_DetectAfsOffsetCurtainDeactivation(CtrlStp_DetectAfsOffsetCurtainDeactivation_Param1, CtrlStp_DetectAfsOffsetCurtainDeactivation_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectAfsOffsetCurtainDeactivation_RetVal1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if there is a transition to GFHB Curtain Deactivation and a correction of the offset is required from HB offset to any other offset
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation(void)
{
  Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation_TestCase_1();
  Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectAfsOffsetCurtainActivation_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if there is a transition to GFHB Curtain Activation and a correction of the offset is required 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_DetectAfsOffsetCurtainActivation_Param1 = 1;
/// \input CtrlStp_snOffsetCorrection = 1;
///
///   - Expectations:
///
/// \output CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectAfsOffsetCurtainActivation_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_DetectAfsOffsetCurtainActivation_Param1 = 1;
  CtrlStp_snOffsetCorrection = 1;
  //Step 3) Call FUT
  CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1 = CtrlStp_DetectAfsOffsetCurtainActivation(CtrlStp_DetectAfsOffsetCurtainActivation_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectAfsOffsetCurtainActivation_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if there is a transition to GFHB Curtain Activation and a correction of the offset is required 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_DetectAfsOffsetCurtainActivation_Param1 = 0;
/// \input CtrlStp_snOffsetCorrection = 0;
///
///   - Expectations:
///
/// \output CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectAfsOffsetCurtainActivation_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_DetectAfsOffsetCurtainActivation_Param1 = 0;
  CtrlStp_snOffsetCorrection = 0;
  //Step 3) Call FUT
  CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1 = CtrlStp_DetectAfsOffsetCurtainActivation(CtrlStp_DetectAfsOffsetCurtainActivation_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectAfsOffsetCurtainActivation_RetVal1, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectAfsOffsetCurtainActivation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if there is a transition to GFHB Curtain Activation and a correction of the offset is required
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectAfsOffsetCurtainActivation(void)
{
  Mt_CtrlStp_DetectAfsOffsetCurtainActivation_TestCase_1();
  Mt_CtrlStp_DetectAfsOffsetCurtainActivation_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ElecDiagStat_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function stores electrical defect status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boElecOL = TRUE;
/// \input CtrlStp_boElecSC = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpElectricDefect, CtrlStp_eLvlElecR_OpenCircuit
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ElecDiagStat_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boElecOL = TRUE;
  CtrlStp_boElecSC = FALSE;
  //Step 3) Call FUT
  CtrlStp_ElecDiagStat();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpElectricDefect, CtrlStp_eLvlElecR_OpenCircuit, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ElecDiagStat_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function stores electrical defect status 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpElectricDefect, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ElecDiagStat_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  //Step 3) Call FUT
  CtrlStp_ElecDiagStat();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpElectricDefect, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ElecDiagStat_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function stores electrical defect status 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_DiagStatus.eStatStpElectricDefect, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ElecDiagStat_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  //Step 3) Call FUT
  CtrlStp_ElecDiagStat();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpElectricDefect, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ElecDiagStat_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function stores electrical defect status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boElecOL = FALSE;
/// \input CtrlStp_boElecSC = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_DiagStatus.eStatStpElectricDefect, CtrlStp_eLvlElecR_ShortCircuit
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ElecDiagStat_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boElecOL = FALSE;
  CtrlStp_boElecSC = TRUE;
  //Step 3) Call FUT
  CtrlStp_ElecDiagStat();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DiagStatus.eStatStpElectricDefect, CtrlStp_eLvlElecR_ShortCircuit, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ElecDiagStat
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores electrical defect status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ElecDiagStat(void)
{
  Mt_CtrlStp_ElecDiagStat_TestCase_1();
  Mt_CtrlStp_ElecDiagStat_TestCase_2();
  Mt_CtrlStp_ElecDiagStat_TestCase_3();
  Mt_CtrlStp_ElecDiagStat_TestCase_4();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eMovementToZero;
///
///   - Expectations:
///
/// \output  CtrlStp_eCurrentDiagState, 19
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eMovementToZero;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eCurrentDiagState, 19, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eSequence1;
///
///   - Expectations:
///
/// \output CtrlStp_eCurrentDiagState, CtrlStp_eMovementToTop
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eSequence1;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eCurrentDiagState, CtrlStp_eMovementToTop, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eSequence2;
///
///   - Expectations:
///
/// \output CtrlStp_eCurrentDiagState, CtrlStp_eMovementToTop
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eSequence2;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eCurrentDiagState, CtrlStp_eMovementToTop, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
/// \input CtrlStp_boDiagRefComplete = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_boDiagRefComplete, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
  CtrlStp_boDiagRefComplete = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boDiagRefComplete, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = FALSE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
/// \input CtrlStp_boDiagRefComplete = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
///
///   - Expectations:
///
/// \output CtrlStp_SignalSrc, 2
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = FALSE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
  CtrlStp_boDiagRefComplete = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
/// \input CtrlStp_boDiagRefComplete = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_SignalSrc = eStpSrc_SleepPos;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, eStpSrc_DiagPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
  CtrlStp_boDiagRefComplete = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_SignalSrc = eStpSrc_SleepPos;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, eStpSrc_DiagPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets the request needed for the takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
/// \input CtrlStp_boDiagRefComplete = TRUE;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_nTgtPos = 29u;
/// \input CtrlStp_SignalSrc = eStpSrc_DiagPos;
///
///   - Expectations:
///
/// \output CtrlStp_SignalSrc, eStpSrc_DiagPos
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
  CtrlStp_boDiagRefComplete = TRUE;
  CtrlStp_boStop = FALSE;
  CtrlStp_nTgtPos = 29u;
  CtrlStp_SignalSrc = eStpSrc_DiagPos;
  //Step 3) Call FUT
  CtrlStp_SetDiagRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, eStpSrc_DiagPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the function sets the request needed for the takeover
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagRequest(void)
{
  Mt_CtrlStp_SetDiagRequest_TestCase_1();
  Mt_CtrlStp_SetDiagRequest_TestCase_2();
  Mt_CtrlStp_SetDiagRequest_TestCase_3();
  Mt_CtrlStp_SetDiagRequest_TestCase_4();
  Mt_CtrlStp_SetDiagRequest_TestCase_5();
  Mt_CtrlStp_SetDiagRequest_TestCase_6();
  Mt_CtrlStp_SetDiagRequest_TestCase_7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_eCurrentDiagState = CtrlStp_eMovementToTop;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 1;
/// \input CtrlStp_nDiagPos = 0;
///
///   - Expectations:
///
/// \output CtrlStp_nDiagPos, 1,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_eCurrentDiagState = CtrlStp_eMovementToTop;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 1;
  CtrlStp_nDiagPos = 0;
  //Step 3) Call FUT
  CtrlStp_SetDiagPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_nDiagPos, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_eCurrentDiagState = CtrlStp_eMovementToBottom;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = -1;
/// \input CtrlStp_nDiagPos = 0;
///
///   - Expectations:
///
/// \output CtrlStp_nDiagPos, -1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_eCurrentDiagState = CtrlStp_eMovementToBottom;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = -1;
  CtrlStp_nDiagPos = 0;
  //Step 3) Call FUT
  CtrlStp_SetDiagPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_nDiagPos, -1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_eCurrentDiagState = CtrlStp_eMovementToZero;
/// \input CtrlStp_nDiagPos = 1;
///
///   - Expectations:
///
/// \output CtrlStp_nDiagPos, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_eCurrentDiagState = CtrlStp_eMovementToZero;
  CtrlStp_nDiagPos = 1;
  //Step 3) Call FUT
  CtrlStp_SetDiagPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_nDiagPos, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
/// \input CtrlStp_eCurrentDiagState = 20;
/// \input CtrlStp_nDiagPos = 1;
///
///   - Expectations:
///
/// \output CtrlStp_nDiagPos, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF11;
  CtrlStp_eCurrentDiagState = 20;
  CtrlStp_nDiagPos = 1;
  //Step 3) Call FUT
  CtrlStp_SetDiagPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_nDiagPos, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDD05;
/// \input CtrlStp_eCurrentDiagState = 20;
/// \input CtrlStp_nDiagPos = 0;
///
///   - Expectations:
///
/// \output CtrlStp_nDiagPos, CtrlStp_sStpControlRequest.snPosRequest
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDD05;
  CtrlStp_eCurrentDiagState = 20;
  CtrlStp_nDiagPos = 0;
  //Step 3) Call FUT
  CtrlStp_SetDiagPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_nDiagPos, CtrlStp_sStpControlRequest.snPosRequest, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
/// \input CtrlStp_eCurrentDiagState = 20;
/// \input CtrlStp_nDiagPos = 1;
///
///   - Expectations:
///
/// \output CtrlStp_nDiagPos, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sStpControlRequest.eStpDID = CtrlStp_eDF10;
  CtrlStp_eCurrentDiagState = 20;
  CtrlStp_nDiagPos = 1;
  //Step 3) Call FUT
  CtrlStp_SetDiagPos();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_nDiagPos, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetDiagPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function sets stepper position for routine control 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetDiagPos(void)
{
  Mt_CtrlStp_SetDiagPos_TestCase_1();
  Mt_CtrlStp_SetDiagPos_TestCase_2();
  Mt_CtrlStp_SetDiagPos_TestCase_3();
  Mt_CtrlStp_SetDiagPos_TestCase_4();
  Mt_CtrlStp_SetDiagPos_TestCase_5();
  Mt_CtrlStp_SetDiagPos_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondParamReady
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the coding parameters are available and also if stepper is supported by EFT data.
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingDataReady_Param1 = CtrlStp_eMountedLeft;
/// \input CtrlStp_CodingDataReady_Param2 = TRUE;//FALSE
/// \input CtrlStp_SetSlaveStopRequest_boStopReq_Param1 = 1;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_CondParamReady_boCodingDataReady_RetVal1, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondParamReady(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingDataReady_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_CodingDataReady_Param2 = TRUE;//FALSE
  CtrlStp_SetSlaveStopRequest_boStopReq_Param1 = 1;
  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 0u;
  //Step 3) Call FUT
  CtrlStp_CondParamReady_boCodingDataReady_RetVal1 = CtrlStp_CondParamReady();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondParamReady_boCodingDataReady_RetVal1, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveStopRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stop request for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boSlaveStop = FALSE;
/// \input CtrlStp_SetSlaveStopRequest_boStopReq_Param1 = 1;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output CtrlStp_boSlaveStop, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSlaveStopRequest(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boSlaveStop = FALSE;
  CtrlStp_SetSlaveStopRequest_boStopReq_Param1 = 1;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_SetSlaveStopRequest(CtrlStp_SetSlaveStopRequest_boStopReq_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagRoutineControl_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
/// \input CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eStop;//255
/// \input CtrlStp_eCurrentDiagState = CtrlStp_eMovementToTop;
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 1u;
///
///   - Expectations:
///
/// \output CtrlStp_eCurrentDiagState, CtrlStp_eStop
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagRoutineControl_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  CtrlStp_sStpControlRequest.eStpRequest = CtrlStp_eStop;//255
  CtrlStp_eCurrentDiagState = CtrlStp_eMovementToTop;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 1u;
  //Step 3) Call FUT
  CtrlStp_DiagRoutineControl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eCurrentDiagState, CtrlStp_eStop, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagRoutineControl_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets stepper position for routine control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_eCurrentDiagState, CtrlStp_eStop
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagRoutineControl_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = TRUE;
  //Step 3) Call FUT
  CtrlStp_DiagRoutineControl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eCurrentDiagState, CtrlStp_eStop, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DiagRoutineControl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the function sets stepper position for routine control
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DiagRoutineControl(void)
{
  Mt_CtrlStp_DiagRoutineControl_TestCase_1();
  Mt_CtrlStp_DiagRoutineControl_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadParam
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that function reads correctly the coding parameters based on mounting side
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CodM_CtrlStp_Para_HitCount = 0u;
/// \input Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = 2u;
/// \input Rte_Read_CodM_CtrlStp_Para_Param1.psCodingParameters_Blocks = 2u;
///
///   - Expectations:
///
/// \output  Rte_Read_CodM_CtrlStp_Para_HitCount, 1u, == );
/// \output  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadParam(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_CtrlStp_Para_HitCount = 0u;
  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = 2u;
  Rte_Read_CodM_CtrlStp_Para_Param1.psCodingParameters_Blocks = 2u;
  //Step 3) Call FUT
  CtrlStp_ReadParam();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturnboExtTakeOver
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function returns takeover status needed for diag takeover
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boDiagStpOn = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturnboExtTakeOver_RetVal, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturnboExtTakeOver(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boDiagStpOn = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReturnboExtTakeOver_RetVal = CtrlStp_ReturnboExtTakeOver();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturnboExtTakeOver_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondOperationStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does correctly operation requested from PWF, cont. movement or inscenation
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boOperationStatus = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_CondOperationStatus_RetVal, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondOperationStatus(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boOperationStatus = TRUE;
  //Step 3) Call FUT
  CtrlStp_CondOperationStatus_RetVal = CtrlStp_CondOperationStatus();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondOperationStatus_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetSubModeErr
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets submode error only if stepper is in master mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boSubModeError = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_GetSubModeErr_RetVal, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetSubModeErr(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boSubModeError = TRUE;
  //Step 3) Call FUT
  CtrlStp_GetSubModeErr_RetVal = CtrlStp_GetSubModeErr();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_GetSubModeErr_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondOperationRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that function returns operation requested from PWF, cont. movement or inscenation
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boOperationRequest = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_CondOperationRequest_RetVal, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondOperationRequest(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boOperationRequest = TRUE;
  //Step 3) Call FUT
  CtrlStp_CondOperationRequest_RetVal = CtrlStp_CondOperationRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondOperationRequest_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondEnabled
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if LWR stepper is enabled by coding data
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CondEnabled_RetVal, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondEnabled(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1;
  //Step 3) Call FUT
  CtrlStp_CondEnabled_RetVal = CtrlStp_CondEnabled();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondEnabled_RetVal, 1, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStatusSignals_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads RTE signals from CddStp
///
///        - Test Design Technique: ET(Exploratory Testing )-
///
/// - Preconditions:
/// - Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
/// - CtrlStp_boConVehIgnition = TRUE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecOL = TRUE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecSC = TRUE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
/// - Expectations:
///   Rte_Read_CodM_CtrlStp_Para_HitCount, 4u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStatusSignals_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecOL = TRUE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecSC = TRUE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)2;
  //Step 3) Call FUT
  CtrlStp_ReadStatusSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_HitCount, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStatusSignals_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads RTE signals from CddStp
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
/// - CtrlStp_boConVehIgnition = TRUE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boOverTempShtDwn = TRUE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecOL = FALSE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecSC = FALSE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boOverTempShtDwn = TRUE;
/// - Expectations:
///   Rte_Read_CodM_CtrlStp_Para_HitCount, 4u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStatusSignals_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boOverTempShtDwn = TRUE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecOL = FALSE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecSC = FALSE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boOverTempShtDwn = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadStatusSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_HitCount, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStatusSignals_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads RTE signals from CddStp
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
/// - CtrlStp_boConVehIgnition = TRUE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
/// - CtrlStp_ActAll.sLwrActual.sStatusError.boOverTempShtDwn = TRUE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecOL = FALSE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecSC = FALSE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boOverTempShtDwn = FALSE;
/// - Expectations:
///   Rte_Read_CodM_CtrlStp_Para_HitCount, 4u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStatusSignals_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecOL = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boElecSC = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boOverTempShtDwn = TRUE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecOL = FALSE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boElecSC = FALSE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boOverTempShtDwn = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReadStatusSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_HitCount, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStatusSignals_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads RTE signals from CddStp
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boOverTempShtDwn = FALSE;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
/// - Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boLowTemp = TRUE;
/// - Expectations:
///    Rte_Read_ppCddStpActual0_sStpActualValues_HitCount, 1u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStatusSignals_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boOverTempShtDwn = FALSE;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.eTempMode = (tieStpTempMode)3;
  Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.sStatusError.boLowTemp = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadStatusSignals();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_ppCddStpActual0_sStpActualValues_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStatusSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function reads RTE signals from CddStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStatusSignals(void)
{
  Mt_CtrlStp_ReadStatusSignals_TestCase_1();
  Mt_CtrlStp_ReadStatusSignals_TestCase_2();
  Mt_CtrlStp_ReadStatusSignals_TestCase_3();
  Mt_CtrlStp_ReadStatusSignals_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_isSafetyPosReached_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function returns TRUE if safety position is reached or actual pos is less than safety pos
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 200;
/// - CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 200;
/// - CtrlStp_SafetyPos = 100;
/// - CtrlStp_ActAll.sLwrActual.nPosition = 1;
/// - Expectations:
///    CtrlStp_isSafetyPosReached_RetVal, 1
//-----------------------------------------------------------------------------
void Mt_CtrlStp_isSafetyPosReached_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 200;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 200;
  CtrlStp_SafetyPos = 100;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  //Step 3) Call FUT
  CtrlStp_isSafetyPosReached_RetVal = CtrlStp_isSafetyPosReached();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_isSafetyPosReached_RetVal, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_isSafetyPosReached_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function returns TRUE if safety position is reached or actual pos is less than safety pos
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
/// - 	CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 1;
/// - 	CtrlStp_SafetyPos = 1;
/// - 	CtrlStp_ActAll.sLwrActual.nPosition = 100;
/// - Expectations:
///     CtrlStp_isSafetyPosReached_RetVal, FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_isSafetyPosReached_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 1;
  CtrlStp_SafetyPos = 1;
  CtrlStp_ActAll.sLwrActual.nPosition = 100;
  //Step 3) Call FUT
  CtrlStp_isSafetyPosReached_RetVal = CtrlStp_isSafetyPosReached();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_isSafetyPosReached_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_isSafetyPosReached_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function returns TRUE if safety position is reached or actual pos is less than safety pos
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 		 CtrlStp_ActAll.sLwrActual.nPosition = 0;
 
/// - Expectations:
///       CtrlStp_isSafetyPosReached_RetVal, TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlStp_isSafetyPosReached_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  //Step 3) Call FUT
  CtrlStp_isSafetyPosReached_RetVal = CtrlStp_isSafetyPosReached();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_isSafetyPosReached_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_isSafetyPosReached
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function returns TRUE if safety position is reached or actual pos is less than safety pos
///    - Test subject:  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_isSafetyPosReached(void)
{
  Mt_CtrlStp_isSafetyPosReached_TestCase_1();
  Mt_CtrlStp_isSafetyPosReached_TestCase_2();
  Mt_CtrlStp_isSafetyPosReached_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetIgnitionNeeded
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets ignition needed flag
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boIgnitionNeeded = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_boIgnitionNeeded, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetIgnitionNeeded(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boIgnitionNeeded = FALSE;
  //Step 3) Call FUT
  CtrlStp_SetIgnitionNeeded(TRUE);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boIgnitionNeeded, TRUE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectSide
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads ecu side correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// - 	Rte_Read_IoHwAbUser_GetMountingSide_Param1   = CtrlStp_eMountedLeft;
/// - 	CtrlStp_RteAccess_Read_EcuSide_Param1        = CtrlStp_eMountedLeft;
/// - 	CtrlStp_RteAccess_Read_EcuSide_Param2        = eMountedLeft;
/// - Expectations:
///       Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, 
///       CtrlStp_RteAccess_Read_EcuSide_RetVal, eMountedLeft,
///       CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedLeft
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectSide(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_RteAccess_Read_EcuSide_Param2 = eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_DetectSide();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_RetVal, eMountedLeft, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedLeft, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_IsMoving
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if stepper is moving
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = 1;
///
///   - Expectations:
///
/// \output CtrlStp_IsMoving_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_IsMoving(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = 1;
  //Step 3) Call FUT
  CtrlStp_IsMoving_RetVal1 = CtrlStp_IsMoving();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_IsMoving_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_riCtrlStpInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the runnable function initialize properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_riCtrlStpInit(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  riCtrlStpInit();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_rpCtrlStp_Cycle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount, 3u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_rpCtrlStp_Cycle_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  rpCtrlStp_Cycle();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_rpCtrlStp_Cycle_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount, 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_rpCtrlStp_Cycle_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  rpCtrlStp_Cycle();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_rpCtrlStp_Cycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_rpCtrlStp_Cycle(void)
{
  Mt_CtrlStp_rpCtrlStp_Cycle_TestCase_1();
  Mt_CtrlStp_rpCtrlStp_Cycle_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls submode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
///
///   - Expectations:
///
/// \output  CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
  //Step 3) Call FUT
  CtrlStp_UseSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls submode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boEntryUnavailable = FALSE;
/// \input CtrlStp_eSubMode = CtrlStp_eSubModeAvailable;
///
///   - Expectations:
///
/// \output CtrlStp_boEntryUnavailable, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boEntryUnavailable = FALSE;
  CtrlStp_eSubMode = CtrlStp_eSubModeAvailable;
  //Step 3) Call FUT
  CtrlStp_UseSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boEntryUnavailable, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls submode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSubMode = CtrlStp_eSubModeFrozen;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeFrozen
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSubMode = CtrlStp_eSubModeFrozen;
  //Step 3) Call FUT
  CtrlStp_UseSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeFrozen, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls submode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSubMode = CtrlStp_eSubModeFactory;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeFactory
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSubMode = CtrlStp_eSubModeFactory;
  //Step 3) Call FUT
  CtrlStp_UseSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeFactory, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls submode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSubMode = CtrlStp_eSubModeAftersale;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeAftersale
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSubMode = CtrlStp_eSubModeAftersale;
  //Step 3) Call FUT
  CtrlStp_UseSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeAftersale, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls submode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_eSubMode = 5;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, 5
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSubMode = 5;
  //Step 3) Call FUT
  CtrlStp_UseSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, 5, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseSubMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function calls submode function 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseSubMode(void)
{
  Mt_CtrlStp_UseSubMode_TestCase_1();
  Mt_CtrlStp_UseSubMode_TestCase_2();
  Mt_CtrlStp_UseSubMode_TestCase_3();
  Mt_CtrlStp_UseSubMode_TestCase_4();
  Mt_CtrlStp_UseSubMode_TestCase_5();
  Mt_CtrlStp_UseSubMode_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Master_Cycle20ms_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
/// \input Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
/// \input Rte_Read_ppsAvacOut_HitCount = 0;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_boDiagStpOn = FALSE;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u
/// \output  Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, 
/// \output  Rte_Read_ppsAvacOut_HitCount, 1u, == );
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Master_Cycle20ms_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
  Rte_Read_ppsAvacOut_HitCount = 0;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_boDiagStpOn = FALSE;
  //Step 3) Call FUT
  CtrlStp_Master_Cycle20ms();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Master_Cycle20ms_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
/// \input Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
/// \input Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
/// \input Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
/// \input Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
/// \input Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
/// \input Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
/// \input Rte_Read_ppsAvacOut_HitCount = 0;
/// \input Rte_Read_ppsAvacOut_Param1.State = 1;
/// \input Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
/// \input Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
/// \input CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
/// \input NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
/// \input CtrlStp_boDiagStpOn = FALSE;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1, == );
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1, == )
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1, == );
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1, == );
/// \output  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1, == );
/// \output  Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
/// \output  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1, == );
/// \output  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1
/// \output  Rte_Read_ppsAvacOut_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadAvacCommand_Param2, 0, == );
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE, =
/// \output  CtrlStp_boDiagStpOn, TRUE, == );
/// \output  CtrlStp_nPosReq, CtrlStp_Simulation_Data.nSimPosReq, == );
/// \output  CtrlStp_boTrainingState, TRUE, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Master_Cycle20ms_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
  Rte_Read_ppsAvacOut_HitCount = 0;
  Rte_Read_ppsAvacOut_Param1.State = 1;
  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE,
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_NO_FAILURE;
  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = CtrlStp_eStpControl_Start;
  CtrlStp_Simulation_Data.ulSimActivated = CTRLSTP_SIMULATION_PASSWORD;
  CtrlStp_boDiagStpOn = FALSE;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_Master_Cycle20ms();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE, == );
  AL_UNITTEST_CHECK(CtrlStp_boDiagStpOn, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_nPosReq, CtrlStp_Simulation_Data.nSimPosReq, == );
  AL_UNITTEST_CHECK(CtrlStp_boTrainingState, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Master_Cycle20ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads singals , detects mode and submode and writes tg pos
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Master_Cycle20ms(void)
{
  Mt_CtrlStp_Master_Cycle20ms_TestCase_1();
  Mt_CtrlStp_Master_Cycle20ms_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Slave_Cycle20ms_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount, 3u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Slave_Cycle20ms_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  //Step 3) Call FUT
  CtrlStp_Slave_Cycle20ms();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Slave_Cycle20ms_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads singals , detects mode and submode and writes tg pos 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_boDiagStpOn = TRUE;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount, 3u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Slave_Cycle20ms_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  CtrlStp_boDiagStpOn = TRUE;
  //Step 3) Call FUT
  CtrlStp_Slave_Cycle20ms();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Slave_Cycle20ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads singals , detects mode and submode and writes tg pos
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Slave_Cycle20ms(void)
{
  Mt_CtrlStp_Slave_Cycle20ms_TestCase_1();
  Mt_CtrlStp_Slave_Cycle20ms_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Test the call initialisation for CtrlDcm 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_Init();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Test the call initialisation for CtrlDcm 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedRight;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Init_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedRight;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_Init();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test the call initialisation for CtrlDcm
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Init(void)
{
  Mt_CtrlStp_Init_TestCase_1();
  Mt_CtrlStp_Init_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls main mode function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_eMainMode = CtrlStp_eModeAssembly;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeFrozen
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseMode_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_eMainMode = CtrlStp_eModeAssembly;
  //Step 3) Call FUT
  CtrlStp_UseMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeFrozen, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls main mode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 1;
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_eMainMode = CtrlStp_eModeCustomer;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseMode_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 1;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_eMainMode = CtrlStp_eModeCustomer;
  //Step 3) Call FUT
  CtrlStp_UseMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseMode_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function calls main mode function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 1;
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_eMainMode = 255;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseMode_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 1;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_eMainMode = 255;
  //Step 3) Call FUT
  CtrlStp_UseMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_UseMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calls main mode function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_UseMode(void)
{
  Mt_CtrlStp_UseMode_TestCase_1();
  Mt_CtrlStp_UseMode_TestCase_2();
  Mt_CtrlStp_UseMode_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteValidationParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if validation parameters are written in rte port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
/// \input CtrlStp_nTgtPos == CtrlStp_ActAll.sLwrActual.nPosition;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
/// \input CtrlStp_Core_sValidationParams.eADL_MODE = CtrlStp_eSubModeFrozen;
/// \input CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_L = 1;
/// \input CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_R = 1;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_L = 1;
/// \input CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = 1;
///
///   - Expectations:
///
/// \output CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_L, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteValidationParams(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  CtrlStp_nTgtPos == CtrlStp_ActAll.sLwrActual.nPosition;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_eSubMode = CtrlStp_eSubModeUnavailable;
  CtrlStp_Core_sValidationParams.eADL_MODE = CtrlStp_eSubModeFrozen;
  CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_L = 1;
  CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_R = 1;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_L = 1;
  CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_R = 1;
  //Step 3) Call FUT
  CtrlStp_WriteValidationParams();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Core_sValidationParams.eLvlAdjHeadlampFault_L, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the behavior function for processing reference run 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
/// \input CtrlStp_nTgtPos == CtrlStp_ActAll.sLwrActual.nPosition;
/// \input CtrlStp_boTrainingState = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_SignalSrc, 0
//-----------------------------------------------------------------------------
void Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  CtrlStp_nTgtPos == CtrlStp_ActAll.sLwrActual.nPosition;
  CtrlStp_boTrainingState = TRUE;
  //Step 3) Call FUT
  CtrlStp_VerifyAndProcessRefRun();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the behavior function for processing reference run  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_SignalSrc = eStpSrc_SleepPos;
///
///   - Expectations:
///
/// \output CtrlStp_SignalSrc, eStpSrc_NormalPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_boStop = FALSE;
  CtrlStp_SignalSrc = eStpSrc_SleepPos;
  //Step 3) Call FUT
  CtrlStp_VerifyAndProcessRefRun();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, eStpSrc_NormalPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the behavior function for processing reference run  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_boIsRefDone = TRUE;
/// \input CtrlStp_SignalSrc = eStpSrc_SleepPos;
///
///   - Expectations:
///
/// \output CtrlStp_SignalSrc, eStpSrc_SleepPos
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_boStop = FALSE;
  CtrlStp_boIsRefDone = TRUE;
  CtrlStp_SignalSrc = eStpSrc_SleepPos;
  //Step 3) Call FUT
  CtrlStp_VerifyAndProcessRefRun();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, eStpSrc_SleepPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_VerifyAndProcessRefRun
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check the behavior function for processing reference run 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_VerifyAndProcessRefRun(void)
{
  Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_1();
  Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_2();
  Mt_CtrlStp_VerifyAndProcessRefRun_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeAfterSale_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for aftersale functionality 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeAfterSale_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SubModeAfterSale();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedLeft, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeAfterSale_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for aftersale functionality 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeAfterSale_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SubModeAfterSale();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedLeft, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeAfterSale_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for aftersale functionality 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1u;
/// \input CtrlStp_CodingDataReady_Param1 = CtrlStp_eMountedLeft;
/// \input CtrlStp_SignalSrc = eStpSrc_SleepPos;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedRight
/// \output CtrlStp_SignalSrc, eStpSrc_SleepPos, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeAfterSale_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1u;
  CtrlStp_CodingDataReady_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_SignalSrc = eStpSrc_SleepPos;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_SubModeAfterSale();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedRight, == );
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, eStpSrc_SleepPos, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeAfterSale
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the submode function for aftersale functionality
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeAfterSale(void)
{
  Mt_CtrlStp_SubModeAfterSale_TestCase_1();
  Mt_CtrlStp_SubModeAfterSale_TestCase_2();
  Mt_CtrlStp_SubModeAfterSale_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeUnavailable_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for unavailable mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_SignalSrc eStpSrc_SleepPos = 1;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_eMountingSide, CtrlStp_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeUnavailable_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_SignalSrc eStpSrc_SleepPos = 1;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SubModeUnavailable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedLeft, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeUnavailable_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for unavailable mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_SignalSrc eStpSrc_SleepPos = 1;
/// \input CtrlStp_boEntryUnavailable = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_boEntryUnavailable, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeUnavailable_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_SignalSrc eStpSrc_SleepPos = 1;
  CtrlStp_boEntryUnavailable = TRUE;
  //Step 3) Call FUT
  CtrlStp_SubModeUnavailable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boEntryUnavailable, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeUnavailable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the submode function for unavailable mode 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeUnavailable(void)
{
  Mt_CtrlStp_SubModeUnavailable_TestCase_1();
  Mt_CtrlStp_SubModeUnavailable_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFactory_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for factory mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boTrainingState = FALSE;
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFactory_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boTrainingState = FALSE;
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SubModeFactory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedLeft, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFactory_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for factory mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedUndef
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFactory_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
  //Step 3) Call FUT
  CtrlStp_SubModeFactory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedUndef, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFactory_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for factory mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boTrainingState = FALSE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedUndef
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFactory_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boTrainingState = FALSE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
  //Step 3) Call FUT
  CtrlStp_SubModeFactory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedUndef, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFactory_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for factory mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_State.boEntry = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalSna
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFactory_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_State.boEntry = FALSE;
  //Step 3) Call FUT
  CtrlStp_SubModeFactory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalSna, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFactory_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for factory mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_State.boEntry = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_boIsRefDone, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFactory_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_State.boEntry = TRUE;
  //Step 3) Call FUT
  CtrlStp_SubModeFactory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boIsRefDone, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFactory
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test the submode function for factory mode 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFactory(void)
{
  Mt_CtrlStp_SubModeFactory_TestCase_1();
  Mt_CtrlStp_SubModeFactory_TestCase_2();
  Mt_CtrlStp_SubModeFactory_TestCase_3();
  Mt_CtrlStp_SubModeFactory_TestCase_4();
  Mt_CtrlStp_SubModeFactory_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SubModeFrozen
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the submode function for factory mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_SignalSrc eStpSrc_SleepPos = 1;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output CtrlStp_eMountingSide, CtrlStp_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SubModeFrozen(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_SignalSrc eStpSrc_SleepPos = 1;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SubModeFrozen();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMountingSide, CtrlStp_eMountedLeft, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeAssembly_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of assembly mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
/// \input CtrlStp_boTrainingState = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_eSubMode, CtrlStp_eSubModeFrozen,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeAssembly_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
  CtrlStp_boTrainingState = TRUE;
  //Step 3) Call FUT
  CtrlStp_ModeAssembly();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeFrozen, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeAssembly_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of assembly mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlStp_boTrainingState = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeFactory
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeAssembly_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  CtrlStp_boTrainingState = FALSE;
  //Step 3) Call FUT
  CtrlStp_ModeAssembly();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeFactory, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeAssembly_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of assembly mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_boConVehIgnition = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeAssembly_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_boConVehIgnition = FALSE;
  //Step 3) Call FUT
  CtrlStp_ModeAssembly();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeAssembly_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of assembly mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input CtrlStp_boConVehIgnition = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_boTrainingState, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeAssembly_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  CtrlStp_boTrainingState = TRUE;
  CtrlStp_boConVehIgnition = TRUE;
  //Step 3) Call FUT
  CtrlStp_ModeAssembly();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boTrainingState, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeAssembly
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function detects submode of assembly mode
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeAssembly(void)
{
  Mt_CtrlStp_ModeAssembly_TestCase_1();
  Mt_CtrlStp_ModeAssembly_TestCase_2();
  Mt_CtrlStp_ModeAssembly_TestCase_3();
  Mt_CtrlStp_ModeAssembly_TestCase_4();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeCustomer_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Check that the function detects submode of customer mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 1;
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeAvailable
/// \output Rte_Read_SysMon_VehNetState_HitCount, 0u, =
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeCustomer_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 1;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = TRUE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_ModeCustomer();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeAvailable, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeCustomer_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of customer mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = FALSE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeAftersale,
/// \output Rte_Read_SysMon_VehNetState_HitCount, 0u, ==
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeCustomer_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = FALSE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_ModeCustomer();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeAftersale, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeCustomer_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of customer mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable
/// \output Rte_Read_SysMon_VehNetState_HitCount, 0u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeCustomer_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boTrainingState = TRUE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_ModeCustomer();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeCustomer_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of customer mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boTrainingState = FALSE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_boConVehIgnition, FALSE, == );
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 0u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeCustomer_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boTrainingState = FALSE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_ModeCustomer();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boConVehIgnition, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeCustomer_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function detects submode of customer mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boTrainingState = FALSE;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_boConVehIgnition, FALSE, == );
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeCustomer_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = 0;
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boTrainingState = FALSE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_ModeCustomer();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boConVehIgnition, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ModeCustomer
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function detects submode of customer mode
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ModeCustomer(void)
{
  Mt_CtrlStp_ModeCustomer_TestCase_1();
  Mt_CtrlStp_ModeCustomer_TestCase_2();
  Mt_CtrlStp_ModeCustomer_TestCase_3();
  Mt_CtrlStp_ModeCustomer_TestCase_4();
  Mt_CtrlStp_ModeCustomer_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Ref_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from init to ref 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boRefReady = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Init_To_Ref_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Ref_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boRefReady = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Init_To_Ref_RetVal1 = CtrlStp_Transition_Init_To_Ref();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Init_To_Ref_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Ref_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from init to ref  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_boRefReady = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Init_To_Ref_RetVal1, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Ref_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_boRefReady = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Init_To_Ref_RetVal1 = CtrlStp_Transition_Init_To_Ref();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Init_To_Ref_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Ref
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from init to ref 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Ref(void)
{
  Mt_CtrlStp_Transition_Init_To_Ref_TestCase_1();
  Mt_CtrlStp_Transition_Init_To_Ref_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Fail_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from init to fail  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_STORED_FAILURE;// CtrlStp_eHLS_FROZEN_FAILURE;false cond
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Init_To_Fail_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Fail_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSensorError = CtrlStp_eHLS_STORED_FAILURE;// CtrlStp_eHLS_FROZEN_FAILURE;false cond
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_Transition_Init_To_Fail_RetVal1 = CtrlStp_Transition_Init_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Init_To_Fail_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Fail_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Check that the stepper does transition from init to fail  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_FROZEN_FAILURE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Init_To_Fail_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Fail_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSensorError = CtrlStp_eHLS_FROZEN_FAILURE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_Transition_Init_To_Fail_RetVal1 = CtrlStp_Transition_Init_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Init_To_Fail_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the stepper does transition from init to fail 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Fail(void)
{
  Mt_CtrlStp_Transition_Init_To_Fail_TestCase_1();
  Mt_CtrlStp_Transition_Init_To_Fail_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_STT_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Check that the stepper does transition from ref to stt  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = 1;
/// \input ulTimerStart = 0u;
/// \input boolean boElectricTransition = FALSE;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
/// \input CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 0;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Ref_To_STT_RetVal1, 0
/// \output  boElectricTransition, 0, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_STT_TestCase_1(void)//-------------------------------tbd
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = 1;
  ulTimerStart = 0u;
  boolean boElectricTransition = FALSE;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
  CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 0;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_STT_RetVal1 = CtrlStp_Transition_Ref_To_STT();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_STT_RetVal1, 0, == );
  AL_UNITTEST_CHECK(boElectricTransition, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_STT_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:   Check that the stepper does transition from ref to stt  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ulTimerStart = 1;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
/// \input ePreviousValue = CtrlStp_eEtatFee_4_1;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Ref_To_STT_RetVal1, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_STT_TestCase_2(void)//-------------------------------tbd
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ulTimerStart = 1;
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
  ePreviousValue = CtrlStp_eEtatFee_4_1;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_STT_RetVal1 = CtrlStp_Transition_Ref_To_STT();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_STT_RetVal1, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_STT
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the stepper does transition from ref to stt  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_STT(void)
{
  Mt_CtrlStp_Transition_Ref_To_STT_TestCase_1();
  Mt_CtrlStp_Transition_Ref_To_STT_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:   Check that the stepper does transition from adj to fail
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_1;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Adj_To_Fail_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  /*CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
  CtrlStp_boLvlAdjFuncFault = 1;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;*/
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Fail_RetVal1 = CtrlStp_Transition_Adj_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Fail_RetVal1, 1, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:   Check that the stepper does transition from adj to fail 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_FROZEN_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = 1;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_Fail_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSensorError = CtrlStp_eHLS_FROZEN_FAILURE;
  CtrlStp_boLvlAdjFuncFault = 1;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Fail_RetVal1 = CtrlStp_Transition_Adj_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Fail_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:    Check that the stepper does transition from adj to fail 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = 0;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_Fail_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
  CtrlStp_boLvlAdjFuncFault = 0;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Fail_RetVal1 = CtrlStp_Transition_Adj_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Fail_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the stepper does transition from adj to fail
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail(void)
{
  Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_1();
  Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_2();
  Mt_CtrlStp_Transition_Adj_To_Fail_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_STT_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:   Check that the stepper does transition from adj to stt
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = 1;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_STT_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_STT_TestCase_1(void)//-------------------------------tbd
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = 1;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_STT_RetVal1 = CtrlStp_Transition_Adj_To_STT();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_STT_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_STT_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from adj to stt 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = 1;
/// \input ulTimerStart = 1u;
/// \input ePreviousValue = CtrlStp_eEtatFee_4_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
/// \input CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_STT_RetVal1, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_STT_TestCase_2(void)
{	
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = 1;
  ulTimerStart = 1u;
  ePreviousValue = CtrlStp_eEtatFee_4_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
  CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 0u;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_STT_RetVal1 = CtrlStp_Transition_Adj_To_STT();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_STT_RetVal1, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_STT
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from adj to stt
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_STT(void)
{
  Mt_CtrlStp_Transition_Adj_To_STT_TestCase_1();
  Mt_CtrlStp_Transition_Adj_To_STT_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_RetVal1 = CtrlStp_Transition_Ref_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 0;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_nTgtPos = 1;
/// \input CtrlStp_boRefRequest = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  CtrlStp_boStop = FALSE;
  CtrlStp_nTgtPos = 1;
  CtrlStp_boRefRequest = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_RetVal1 = CtrlStp_Transition_Ref_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_RetVal1 = CtrlStp_Transition_Ref_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_RetVal1 = CtrlStp_Transition_Ref_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 0;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
/// \input CtrlStp_boRefRequest = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  CtrlStp_boStop = TRUE;
  CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.nPosition;
  CtrlStp_boRefRequest = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_RetVal1 = CtrlStp_Transition_Ref_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the stepper does transition from ref to adj
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj(void)
{
  Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_1();
  Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_2();
  Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_3();
  Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_4();
  Mt_CtrlStp_Transition_Ref_To_Adj_TestCase_5();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Fail_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to fail 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Fail_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Fail_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Fail_RetVal1 = CtrlStp_Transition_Ref_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Fail_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Fail_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from ref to fail 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Ref_To_Fail_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Fail_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Fail_RetVal1 = CtrlStp_Transition_Ref_To_Fail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Fail_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Fail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from ref to fail
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Fail(void)
{
  Mt_CtrlStp_Transition_Ref_To_Fail_TestCase_1();
  Mt_CtrlStp_Transition_Ref_To_Fail_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Ref_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from fail to ref 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX = 100;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Fail_To_Ref_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Ref_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX = 100;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Ref_RetVal1 = CtrlStp_Transition_Fail_To_Ref();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Ref_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Ref_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from fail to ref  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Fail_To_Ref_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Ref_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
  CtrlStp_boLvlAdjFuncFault = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Ref_RetVal1 = CtrlStp_Transition_Fail_To_Ref();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Ref_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Ref
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from fail to ref 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Ref(void)
{
  Mt_CtrlStp_Transition_Fail_To_Ref_TestCase_1();
  Mt_CtrlStp_Transition_Fail_To_Ref_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Adj_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that the stepper does transition from fail to adj  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input CtrlStp_boStop = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Fail_To_Adj_RetVal1, 1,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Adj_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  CtrlStp_boStop = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Adj_RetVal1 = CtrlStp_Transition_Fail_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Adj_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Adj_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from fail to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Fail_To_Adj_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Adj_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
  CtrlStp_boLvlAdjFuncFault = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Adj_RetVal1 = CtrlStp_Transition_Fail_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Adj_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Adj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from fail to adj
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Adj(void)
{
  Mt_CtrlStp_Transition_Fail_To_Adj_TestCase_1();
  Mt_CtrlStp_Transition_Fail_To_Adj_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_STT_To_Ref_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from stt to ref 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input boolean boElectricTransition = TRUE;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 7;
/// \input static teCtrlStp_EtatFee ePreviousValue;
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_STT_To_Ref_RetVal1, 1,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_STT_To_Ref_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boRefRequest = TRUE;
  boolean boElectricTransition = TRUE;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 7;
  static teCtrlStp_EtatFee ePreviousValue;
  ePreviousValue = CtrlStp_eEtatFee_1_1;
  //Step 3) Call FUT
  CtrlStp_Transition_STT_To_Ref_RetVal1 = CtrlStp_Transition_STT_To_Ref();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_STT_To_Ref_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_STT_To_Ref_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from stt to ref  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input boolean boElectricTransition = FALSE;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 0;
/// \input static teCtrlStp_EtatFee ePreviousValue;
/// \input ePreviousValue = CtrlStp_eEtatFee_Invalid;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_STT_To_Ref_RetVal1, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_STT_To_Ref_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_boRefRequest = FALSE;
  boolean boElectricTransition = FALSE;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 0;
  static teCtrlStp_EtatFee ePreviousValue;
  ePreviousValue = CtrlStp_eEtatFee_Invalid;
  //Step 3) Call FUT
  CtrlStp_Transition_STT_To_Ref_RetVal1 = CtrlStp_Transition_STT_To_Ref();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_STT_To_Ref_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_STT_To_Ref
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from stt to ref 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_STT_To_Ref(void)
{
  Mt_CtrlStp_Transition_STT_To_Ref_TestCase_1();
  Mt_CtrlStp_Transition_STT_To_Ref_TestCase_2();
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_STT_To_Adj_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that the stepper does transition from stt to adj  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input boolean boElectricTransition = FALSE;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 7;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_STT_To_Adj_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_STT_To_Adj_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boRefRequest = FALSE;
  boolean boElectricTransition = FALSE;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 7;
  //Step 3) Call FUT
  CtrlStp_Transition_STT_To_Adj_RetVal1 = CtrlStp_Transition_STT_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_STT_To_Adj_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_STT_To_Adj_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from stt to adj 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input boolean boElectricTransition = FALSE;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 0;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_STT_To_Adj_RetVal1, 0
/// \output boElectricTransition, FALSE, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_STT_To_Adj_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_boRefRequest = TRUE;
  boolean boElectricTransition = FALSE;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 0;
  //Step 3) Call FUT
  CtrlStp_Transition_STT_To_Adj_RetVal1 = CtrlStp_Transition_STT_To_Adj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_STT_To_Adj_RetVal1, 0, == );
  AL_UNITTEST_CHECK(boElectricTransition, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_STT_To_Adj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from stt to adj
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_STT_To_Adj(void)
{
  Mt_CtrlStp_Transition_STT_To_Adj_TestCase_1();
  Mt_CtrlStp_Transition_STT_To_Adj_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Frozen_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from assembly to frozen 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
/// \input CtrlStp_boTrainingState = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransitionSttToAdj_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Frozen_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Montage;
  CtrlStp_boTrainingState = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Assembly_To_Frozen_RetVal1 = CtrlStp_Transition_Assembly_To_Frozen();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Assembly_To_Frozen_RetVal1, 1, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Frozen_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from assembly to frozen 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Stockage;
/// \input CtrlStp_boTrainingState = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Assembly_To_Frozen_RetVal1, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Frozen_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Stockage;
  CtrlStp_boTrainingState = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Assembly_To_Frozen_RetVal1 = CtrlStp_Transition_Assembly_To_Frozen();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Assembly_To_Frozen_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Frozen
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from assembly to frozen
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Frozen(void)
{
  Mt_CtrlStp_Transition_Assembly_To_Frozen_TestCase_1();
  Mt_CtrlStp_Transition_Assembly_To_Frozen_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Factory_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from assembly to factory 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boTrainingState = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Assembly_To_Factory_RetVal1, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Factory_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boTrainingState = FALSE;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_AfterMarket;
  //Step 3) Call FUT
  CtrlStp_Transition_Assembly_To_Factory_RetVal1 = CtrlStp_Transition_Assembly_To_Factory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Assembly_To_Factory_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Factory_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from assembly to factory 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boTrainingState = TRUE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Assembly_To_Factory_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Factory_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boTrainingState = TRUE;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Invalid2;
  //Step 3) Call FUT
  CtrlStp_Transition_Assembly_To_Factory_RetVal1 = CtrlStp_Transition_Assembly_To_Factory();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Assembly_To_Factory_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Factory
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from assembly to factory
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Factory(void)
{
  Mt_CtrlStp_Transition_Assembly_To_Factory_TestCase_1();
  Mt_CtrlStp_Transition_Assembly_To_Factory_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Unavailable_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from assembly to unavailable 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boTrainingState = TRUE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Assembly_To_Unavailable_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Unavailable_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boTrainingState = TRUE;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  //Step 3) Call FUT
  CtrlStp_Transition_Assembly_To_Unavailable_RetVal1 = CtrlStp_Transition_Assembly_To_Unavailable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Assembly_To_Unavailable_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Unavailable_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from assembly to unavailable 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = FALSE;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Assembly_To_Unavailable_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Unavailable_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = FALSE;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Usine;
  //Step 3) Call FUT
  CtrlStp_Transition_Assembly_To_Unavailable_RetVal1 = CtrlStp_Transition_Assembly_To_Unavailable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Assembly_To_Unavailable_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Assembly_To_Unavailable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the stepper does transition from assembly to unavailable 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Assembly_To_Unavailable(void)
{
  Mt_CtrlStp_Transition_Assembly_To_Unavailable_TestCase_1();
  Mt_CtrlStp_Transition_Assembly_To_Unavailable_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Unavailable_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from customer to unavailable 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Customer_To_Unavailable_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Unavailable_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Customer_To_Unavailable_RetVal1 = CtrlStp_Transition_Customer_To_Unavailable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Customer_To_Unavailable_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Unavailable_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from customer to unavailable 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Customer_To_Unavailable_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Unavailable_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Customer_To_Unavailable_RetVal1 = CtrlStp_Transition_Customer_To_Unavailable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Customer_To_Unavailable_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Unavailable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from customer to unavailable
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Unavailable(void)
{
  Mt_CtrlStp_Transition_Customer_To_Unavailable_TestCase_1();
  Mt_CtrlStp_Transition_Customer_To_Unavailable_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Available_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from customer to available 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Customer_To_Available_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Available_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Customer_To_Available_RetVal1 = CtrlStp_Transition_Customer_To_Available();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Customer_To_Available_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Available_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Check that the stepper does transition from customer to available 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boTrainingState = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Customer_To_Available_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Available_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boTrainingState = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Customer_To_Available_RetVal1 = CtrlStp_Transition_Customer_To_Available();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Customer_To_Available_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Available
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the stepper does transition from customer to available
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Available(void)
{
  Mt_CtrlStp_Transition_Customer_To_Available_TestCase_1();
  Mt_CtrlStp_Transition_Customer_To_Available_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Aftersale_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Check that the stepper does transition from customer to aftersale 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_boTrainingState = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Customer_To_Aftersale_RetVal1, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Aftersale_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_boTrainingState = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Customer_To_Aftersale_RetVal1 = CtrlStp_Transition_Customer_To_Aftersale();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Customer_To_Aftersale_RetVal1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Aftersale_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the stepper does transition from customer to aftersale 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_boTrainingState = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Customer_To_Aftersale_RetVal1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Aftersale_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_boTrainingState = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Customer_To_Aftersale_RetVal1 = CtrlStp_Transition_Customer_To_Aftersale();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Customer_To_Aftersale_RetVal1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Customer_To_Aftersale
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the stepper does transition from customer to aftersale 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Customer_To_Aftersale(void)
{
  Mt_CtrlStp_Transition_Customer_To_Aftersale_TestCase_1();
  Mt_CtrlStp_Transition_Customer_To_Aftersale_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handle fail state behavior depending on the fault status 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
/// \input CtrlStp_State.boEntry = TRUE;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
///
///   - Expectations:
///
/// \output eLvlFuncHeadlampFault, 0
/// \output CtrlStp_State.boEntry, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  CtrlStp_State.boEntry = TRUE;
  CtrlStp_eLvlAdjHeadlampFault_R = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(eLvlFuncHeadlampFault, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handle fail state behavior depending on the fault status  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_State.boEntry = TRUE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
/// \input eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output  eLvlFuncHeadlampFault, 0
/// \output  CtrlStp_State.boEntry, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_State.boEntry = TRUE;
  CtrlStp_eLvlAdjHeadlampFault_L = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
  eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(eLvlFuncHeadlampFault, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handle fail state behavior depending on the fault status  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input boolean boStepLossRecovered;
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
/// \input eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
/// \input boStepLossRecovered = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
///
///   - Expectations:
///
/// \output  eLvlFuncHeadlampFault, 0
/// \output  CtrlStp_State.boEntry, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  boolean boStepLossRecovered;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
  eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
  boStepLossRecovered = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(eLvlFuncHeadlampFault, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handle fail state behavior depending on the fault status  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input boolean boStepLossRecovered;
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = 1;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
///
///   - Expectations:
///
/// \output  eLvlFuncHeadlampFault, 0
/// \output  CtrlStp_State.boEntry, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  boolean boStepLossRecovered;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = 1;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(eLvlFuncHeadlampFault, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function handle fail state behavior depending on the fault status  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  boolean boStepLossRecovered;
/// \input  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
/// \input  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input  CtrlStp_State.boEntry = TRUE;
/// \input  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
///
///   - Expectations:
///
/// \output  eLvlFuncHeadlampFault, CtrlStp_eNo_Failure
/// \output  CtrlStp_State.boEntry, 1, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  boolean boStepLossRecovered;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFault;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  CtrlStp_State.boEntry = TRUE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  //eLvlFuncHeadlampFault = CtrlStp_eNo_Failure;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(eLvlFuncHeadlampFault, CtrlStp_eNo_Failure, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function handle fail state behavior depending on the fault status 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail(void)
{
  Mt_CtrlStp_StateMachine_StateFail_TestCase_1();
  Mt_CtrlStp_StateMachine_StateFail_TestCase_2();
  Mt_CtrlStp_StateMachine_StateFail_TestCase_3();
  Mt_CtrlStp_StateMachine_StateFail_TestCase_4();
  Mt_CtrlStp_StateMachine_StateFail_TestCase_5();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateSTT
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of stt state works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateSTT(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateSTT();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of state Init works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_boRefReady, FALSE, =
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = TRUE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateInit();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boRefReady, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of state Init works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input CtrlStp_StateMachine_StateInit_Param1 = (uint8)eMountedLeft;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1;// SUPPORT_YES;
///
///   - Expectations:
///
/// \output  CtrlStp_boRefReady, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  CtrlStp_StateMachine_StateInit_Param1 = (uint8)eMountedLeft;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1;// SUPPORT_YES;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateInit();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boRefReady, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of state Init works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
/// \input CtrlStp_StateMachine_StateInit_Param1 = (uint8)eMountedLeft;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1;//
///
///   - Expectations:
///
/// \output  CtrlStp_boRefReady, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
  CtrlStp_StateMachine_StateInit_Param1 = (uint8)eMountedLeft;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1;// SUPPORT_YES;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateInit();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boRefReady, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of state Init works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input CtrlStp_CodingDataReady_Param1 = eMountedLeft;
/// \input Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1u;// SUPPORT_YES;
/// \input Rte_Read_CodM_CtrlStp_Para_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_boRefReady, TRUE, == );
/// \output  Rte_Read_CodM_CtrlStp_Para_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  CtrlStp_CodingDataReady_Param1 = eMountedLeft;
  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 1u;// SUPPORT_YES;
  Rte_Read_CodM_CtrlStp_Para_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateInit();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boRefReady, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if behavior in case of state Init works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit(void)
{
  Mt_CtrlStp_StateMachine_StateInit_TestCase_1();
  Mt_CtrlStp_StateMachine_StateInit_TestCase_2();
  Mt_CtrlStp_StateMachine_StateInit_TestCase_3();
  Mt_CtrlStp_StateMachine_StateInit_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateAdj_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of adjustment state works properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_State.boEntry = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateAdj_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_State.boEntry = TRUE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateAdj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateAdj_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of adjustment state works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateAdj_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateAdj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateAdj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if behavior in case of adjustment state works properly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateAdj(void)
{
  Mt_CtrlStp_StateMachine_StateAdj_TestCase_1();
  Mt_CtrlStp_StateMachine_StateAdj_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateRef
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if behavior in case of state Ref works properly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input  CtrlStp_State.boEntry = TRUE;
/// \input  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input  teCtrlStp_SignalSrc eStpSrc_NormalPos = 0;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateRef(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  CtrlStp_State.boEntry = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  teCtrlStp_SignalSrc eStpSrc_NormalPos = 0;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateRef();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if refference request is handled correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input CtrlStp_State.boEntry = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
/// \input teCtrlStp_SignalSrc eStpSrc_NormalPos = 0;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Proccess_Reference_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  CtrlStp_State.boEntry = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  teCtrlStp_SignalSrc eStpSrc_NormalPos = 0;
  //Step 3) Call FUT
  CtrlStp_Proccess_Reference();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if refference request is handled correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
/// \input CtrlStp_State.boEntry = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, TRUE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Proccess_Reference_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
  CtrlStp_State.boEntry = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
  //Step 3) Call FUT
  CtrlStp_Proccess_Reference();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if refference request is handled correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input boolean boRefRequest;
/// \input boolean boCondIsReady;
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Proccess_Reference_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  boolean boRefRequest;
  boolean boCondIsReady;
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_Proccess_Reference();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if refference request is handled correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input boolean boRefRequest;
/// \input boolean boCondIsReady;
/// \input CtrlStp_State.boEntry = FALSE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Proccess_Reference_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  boolean boRefRequest;
  boolean boCondIsReady;
  CtrlStp_State.boEntry = FALSE;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedUndef;
  //Step 3) Call FUT
  CtrlStp_Proccess_Reference();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if refference request is handled correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
/// \input NM_GetMode_Param1 = 0x04;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input NM_GetMode_HitCount = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
/// \output  NM_GetMode_HitCount, 1u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Proccess_Reference_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  NM_GetMode_Param1 = 0x04;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  NM_GetMode_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_Proccess_Reference();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if refference request is handled correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
/// \input NM_GetMode_Param1 = 0x04;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
/// \input NM_GetMode_HitCount = 0u;
/// \input CtrlStp_boTrainingState = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
/// \output  NM_GetMode_HitCount, 1u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Proccess_Reference_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  NM_GetMode_Param1 = 0x04;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = TRUE;
  NM_GetMode_HitCount = 0u;
  CtrlStp_boTrainingState = FALSE;
  //Step 3) Call FUT
  CtrlStp_Proccess_Reference();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Proccess_Reference
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if refference request is handled correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void  Mt_CtrlStp_Proccess_Reference(void)
{
  Mt_CtrlStp_Proccess_Reference_TestCase_1();
  Mt_CtrlStp_Proccess_Reference_TestCase_2();
  Mt_CtrlStp_Proccess_Reference_TestCase_3();
  Mt_CtrlStp_Proccess_Reference_TestCase_4();
  Mt_CtrlStp_Proccess_Reference_TestCase_5();
  Mt_CtrlStp_Proccess_Reference_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the detection of main mode of stepper control is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
/// \input uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
///
///   - Expectations:
///
/// \output  CtrlStp_eMainMode, CtrlStp_eModeCustomer
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectMode_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Client;
  uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 3) Call FUT
  CtrlStp_DetectMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMainMode, CtrlStp_eModeCustomer, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the detection of main mode of stepper control is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
/// \input uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
///
///   - Expectations:
///
/// \output  CtrlStp_eMainMode, CtrlStp_eModeCustomer
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectMode_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Showroom;
  uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 3) Call FUT
  CtrlStp_DetectMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMainMode, CtrlStp_eModeCustomer, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectMode_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the detection of main mode of stepper control is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Stockage;
/// \input uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
///
///   - Expectations:
///
/// \output  CtrlStp_eMainMode, CtrlStp_eModeCustomer
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectMode_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = eModeConfigVehicle_Stockage;
  uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 3) Call FUT
  CtrlStp_DetectMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMainMode, CtrlStp_eModeCustomer, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectMode_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the detection of main mode of stepper control is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = 0;
///
///   - Expectations:
///
/// \output  CtrlStp_eMainMode, CtrlStp_eModeAssembly
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectMode_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = 0;
  //Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = 0;
  //Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = 0;
  uint8 CtrlStp_DetectMode_ucModeConfigVhl = CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 3) Call FUT
  CtrlStp_DetectMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eMainMode, CtrlStp_eModeAssembly, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the detection of main mode of stepper control is done
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectMode(void)
{
  Mt_CtrlStp_DetectMode_TestCase_1();
  Mt_CtrlStp_DetectMode_TestCase_2();
  Mt_CtrlStp_DetectMode_TestCase_3();
  Mt_CtrlStp_DetectMode_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ResetStpState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Checks if stepper was previously activated and it resets the state if so
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input static boolean CtrlStp_ResetStpState_boFirstEntry = TRUE;
/// \input CtrlStp_State.eMain = CtrlStp_eState_Adj;// = 2,      // Adjustment phase
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, TRUE, == );
///         CtrlStp_State.eMain, CtrlStp_eState_Init
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ResetStpState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  static boolean CtrlStp_ResetStpState_boFirstEntry = TRUE;
  CtrlStp_State.eMain = CtrlStp_eState_Adj;// = 2,      // Adjustment phase
  //Step 3) Call FUT
  CtrlStp_ResetStpState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, TRUE, == );
  AL_UNITTEST_CHECK(CtrlStp_State.eMain, CtrlStp_eState_Init, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ResetStpState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Checks if stepper was previously activated and it resets the state if so 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input static boolean CtrlStp_ResetStpState_boFirstEntry = FALSE;
/// \input CtrlStp_State.eMain = 0;// CtrlStp_eState_Init;// = 2,      // Adjustment phase
///
///   - Expectations:
///
/// \output CtrlStp_ResetStpState_boFirstEntry, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ResetStpState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  static boolean CtrlStp_ResetStpState_boFirstEntry = FALSE;
  CtrlStp_State.eMain = 0;// CtrlStp_eState_Init;// = 2,      // Adjustment phase
  //Step 3) Call FUT
  CtrlStp_ResetStpState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ResetStpState_boFirstEntry, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ResetStpState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Checks if stepper was previously activated and it resets the state if so
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ResetStpState(void)
{
  Mt_CtrlStp_ResetStpState_TestCase_1();
  Mt_CtrlStp_ResetStpState_TestCase_1();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition for adj to fail for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input CtrlStp_boSlaveLvlAdjFuncFault = 1;// CtrlStp_eNo_Failure;
/// \input boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
/// \input CtrlStp_Transition_Adj_To_Fail_Slave_boReturn;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_Fail_Slave_boReturn, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  CtrlStp_boSlaveLvlAdjFuncFault = 1;// CtrlStp_eNo_Failure;
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  CtrlStp_Transition_Adj_To_Fail_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Fail_Slave_boReturn = CtrlStp_Transition_Adj_To_Fail_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Fail_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition for adj to fail for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input CtrlStp_boSlaveLvlAdjFuncFault = CtrlStp_eNo_Failure;
/// \input boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
/// \input CtrlStp_Transition_Adj_To_Fail_Slave_boReturn;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_Fail_Slave_boReturn, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  CtrlStp_boSlaveLvlAdjFuncFault = CtrlStp_eNo_Failure;
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  CtrlStp_Transition_Adj_To_Fail_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Fail_Slave_boReturn = CtrlStp_Transition_Adj_To_Fail_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Fail_Slave_boReturn, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Fail_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition for adj to fail for slave is done 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Fail_Slave(void)
{
  Mt_CtrlStp_Transition_Adj_To_Fail_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Adj_To_Fail_Slave_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Ref_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from adj to ref for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input boolean boAdlReferencingRequest = CtrlStp_RefRequest();
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
/// \input CtrlStp_Transition_Adj_To_Ref_Slave_boReturn;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Adj_To_Ref_Slave_boReturn, 1
///
//------------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Ref_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_boPowertrainActive = TRUE;
  boolean boAdlReferencingRequest = CtrlStp_RefRequest();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
  CtrlStp_Transition_Adj_To_Ref_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Ref_Slave_boReturn = CtrlStp_Transition_Adj_To_Ref_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Ref_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Ref_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from adj to ref for slave is done  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = 1;// CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input boolean boAdlReferencingRequest = CtrlStp_RefRequest();
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
/// \input CtrlStp_Transition_Adj_To_Ref_Slave_boReturn;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Adj_To_Ref_Slave_boReturn, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Ref_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = 1;// CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boPowertrainActive = FALSE;
  boolean boAdlReferencingRequest = CtrlStp_RefRequest();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  boolean boPowerTrainActive = CtrlStp_RetPowerTrainActive();
  CtrlStp_Transition_Adj_To_Ref_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Adj_To_Ref_Slave_boReturn = CtrlStp_Transition_Adj_To_Ref_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Adj_To_Ref_Slave_boReturn, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Adj_To_Ref_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition from adj to ref for slave is done 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Adj_To_Ref_Slave(void)
{
  Mt_CtrlStp_Transition_Adj_To_Ref_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Adj_To_Ref_Slave_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Adj_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from fail to adj for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input boolean boRefRequest = CtrlStp_RefRequest();
/// \input boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input CtrlStp_Transition_Fail_To_Adj_Slave_boReturn;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Fail_To_Adj_Slave_boReturn, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Adj_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  boolean boRefRequest = CtrlStp_RefRequest();
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  CtrlStp_Transition_Fail_To_Adj_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Adj_Slave_boReturn = CtrlStp_Transition_Fail_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Adj_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Adj_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from fail to adj for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = 1;// CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
/// \input boolean boRefRequest = CtrlStp_RefRequest();
/// \input boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input CtrlStp_Transition_Fail_To_Adj_Slave_boReturn;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Fail_To_Adj_Slave_boReturn, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Adj_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = 1;// CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
  boolean boRefRequest = CtrlStp_RefRequest();
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  CtrlStp_Transition_Fail_To_Adj_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Adj_Slave_boReturn, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Adj_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition from fail to adj for slave is done 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Adj_Slave(void)
{
  Mt_CtrlStp_Transition_Fail_To_Adj_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Fail_To_Adj_Slave_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Ref_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from fail to ref for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input boolean boRefRequest = CtrlStp_RefRequest();
/// \input boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input CtrlStp_Transition_Fail_To_Ref_Slave_boReturn;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Fail_To_Ref_Slave_boReturn, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Ref_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  boolean boRefRequest = CtrlStp_RefRequest();
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  CtrlStp_Transition_Fail_To_Ref_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Ref_Slave_boReturn = CtrlStp_Transition_Fail_To_Ref_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Ref_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Ref_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from fail to ref for slave is done  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_R = 1;// CtrlStp_eNo_Failure;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
/// \input boolean boRefRequest = CtrlStp_RefRequest();
/// \input boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
/// \input CtrlStp_Transition_Fail_To_Ref_Slave_boReturn;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Fail_To_Ref_Slave_boReturn, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Ref_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = 1;// CtrlStp_eNo_Failure;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
  boolean boRefRequest = CtrlStp_RefRequest();
  boolean boLvlAdjFuncFault = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  CtrlStp_Transition_Fail_To_Ref_Slave_boReturn;
  //Step 3) Call FUT
  CtrlStp_Transition_Fail_To_Ref_Slave_boReturn = CtrlStp_Transition_Fail_To_Ref_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Fail_To_Ref_Slave_boReturn, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Fail_To_Ref_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition from fail to ref for slave is done 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Fail_To_Ref_Slave(void)
{
  Mt_CtrlStp_Transition_Fail_To_Ref_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Fail_To_Ref_Slave_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Fail_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from ref to fail for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Transition_Ref_To_Fail_Slave_boReturn;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;// CtrlStp_eNo_Failure;
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R()
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Fail_Slave_boReturn, 1,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Fail_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Transition_Ref_To_Fail_Slave_boReturn;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;// CtrlStp_eNo_Failure;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();//CtrlStp_eFrozen_Failure;// TRUE;// CtrlStp_ReturneLvlAdjHeadlampFault_R();
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Fail_Slave_boReturn = CtrlStp_Transition_Ref_To_Fail_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Fail_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Fail_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from ref to fail for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Transition_Ref_To_Fail_Slave_boReturn = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Fail_Slave_boReturn, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Fail_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Transition_Ref_To_Fail_Slave_boReturn = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  teCtrlStp_HeadlampFaultStatus eLvlFuncHeadlampFaultR = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Fail_Slave_boReturn = CtrlStp_Transition_Ref_To_Fail_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Fail_Slave_boReturn, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Fail_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition from ref to fail for slave is done 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Fail_Slave(void)
{
  Mt_CtrlStp_Transition_Ref_To_Fail_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Ref_To_Fail_Slave_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefUpCompl_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if stepper position is reached is no movement is requested
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 0;
/// \input boolean CtrlStp_CondRefUpCompl_boRet = TRUE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_nTgtPos = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_CondRefUpCompl_boRet, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefUpCompl_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.nPosition = 0;
  boolean CtrlStp_CondRefUpCompl_boRet = TRUE;
  CtrlStp_boStop = TRUE;
  CtrlStp_nTgtPos = TRUE;
  //Step 3) Call FUT
  CtrlStp_CondRefUpCompl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefUpCompl_boRet, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefUpCompl_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if stepper position is reached if movement is requested 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.nPosition = TRUE;
/// \input boolean CtrlStp_CondRefUpCompl_boRet = FALSE;
/// \input CtrlStp_boStop = FALSE;
/// \input CtrlStp_nTgtPos = 0;
///
///   - Expectations:
///
/// \output CtrlStp_CondRefUpCompl_boRet, FALSE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefUpCompl_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.nPosition = TRUE;
  boolean CtrlStp_CondRefUpCompl_boRet = FALSE;
  CtrlStp_boStop = FALSE;
  CtrlStp_nTgtPos = 0;
  //Step 3) Call FUT
  CtrlStp_CondRefUpCompl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefUpCompl_boRet, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefUpCompl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if stepper position is reached
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefUpCompl(void)
{
  Mt_CtrlStp_CondRefUpCompl_TestCase_1();
  Mt_CtrlStp_CondRefUpCompl_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from ref to adj for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boStop = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boStop = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn = CtrlStp_Transition_Ref_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from ref to adj for slave is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boStop = TRUE;
/// \input CtrlStp_nTgtPos = 1;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boStop = TRUE;
  CtrlStp_nTgtPos = 1;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn = CtrlStp_Transition_Ref_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from ref to adj for slave is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
/// \input CtrlStp_boRefRequest = TRUE;
/// \input boolean CtrlStp_Transition_Ref_To_Adj_Slave_boRefComplete = CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef;
/// \input boolean CtrlStp_Transition_Ref_To_Adj_Slave_boLvlAdjFuncFault = CtrlStp_boSlaveLvlAdjFuncFault;
/// \input boolean CtrlStp_Transition_Ref_To_Adj_Slave_boRefRequest = CtrlStp_boRefRequest;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = FALSE;
  CtrlStp_boRefRequest = TRUE;
  boolean CtrlStp_Transition_Ref_To_Adj_Slave_boRefComplete = CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef;
  boolean CtrlStp_Transition_Ref_To_Adj_Slave_boLvlAdjFuncFault = CtrlStp_boSlaveLvlAdjFuncFault;
  boolean CtrlStp_Transition_Ref_To_Adj_Slave_boRefRequest = CtrlStp_boRefRequest;
  //CtrlStp_boStop = FALSE;
  //CtrlStp_nTgtPos = CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn = CtrlStp_Transition_Ref_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that if transition from ref to adj for slave is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn = CtrlStp_Transition_Ref_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from ref to adj for slave is done 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
/// \input CtrlStp_boRefRequest = FALSE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = TRUE;
  CtrlStp_boRefRequest = FALSE;
  CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Ref_To_Adj_Slave_boReturn = CtrlStp_Transition_Ref_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Ref_To_Adj_Slave_boReturn, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Ref_To_Adj_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition from ref to adj for slave is done
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Ref_To_Adj_Slave(void)
{
  Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_2();
  Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_3();
  Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_4();
  Mt_CtrlStp_Transition_Ref_To_Adj_Slave_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Adj_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from init to adj for slave is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Init_To_Adj_Slave_RetVal, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Adj_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = FALSE;
  //Step 3) Call FUT
  CtrlStp_Transition_Init_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Init_To_Adj_Slave_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Adj_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if transition from init to adj for slave is done
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_Transition_Init_To_Adj_Slave_RetVal, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Adj_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsOn = TRUE;
  //Step 3) Call FUT
  CtrlStp_Transition_Init_To_Adj_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Transition_Init_To_Adj_Slave_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Transition_Init_To_Adj_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if transition from init to adj for slave is done
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Transition_Init_To_Adj_Slave(void)
{
  Mt_CtrlStp_Transition_Init_To_Adj_Slave_TestCase_1();
  Mt_CtrlStp_Transition_Init_To_Adj_Slave_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_GetStateValue
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the stepper state value is returned correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_State.eMain = CtrlStp_eState_Ref;// = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_eSubMode, CtrlStp_eState_Ref
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_GetStateValue(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.eMain = CtrlStp_eState_Ref;// = 1
  //Step 3) Call FUT
  CtrlStp_GetStateValue();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eState_Ref, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectSlaveSubMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects submode of slave mode when ignition is off
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = FALSE;
/// \input CtrlStp_DetectSlaveSubMode_Param1 = CtrlStp_boConVehIgnition;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectSlaveSubMode_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = FALSE;
  CtrlStp_DetectSlaveSubMode_Param1 = CtrlStp_boConVehIgnition;
  //Step 3) Call FUT
  CtrlStp_DetectSlaveSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeUnavailable, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectSlaveSubMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects submode of slave mode when ignition is on 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = TRUE;
/// \input CtrlStp_DetectSlaveSubMode_Param1 = CtrlStp_boConVehIgnition;
///
///   - Expectations:
///
/// \output CtrlStp_eSubMode, CtrlStp_eSubModeAvailable
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectSlaveSubMode_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = TRUE;
  CtrlStp_DetectSlaveSubMode_Param1 = CtrlStp_boConVehIgnition;
  //Step 3) Call FUT
  CtrlStp_DetectSlaveSubMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_eSubMode, CtrlStp_eSubModeAvailable, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectSlaveSubMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if detects submode of slave mode
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectSlaveSubMode(void)
{
  Mt_CtrlStp_DetectSlaveSubMode_TestCase_1();
  Mt_CtrlStp_DetectSlaveSubMode_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeUnavailable;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Init;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_1(void)//---------------------------------------------not done
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeUnavailable;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Init;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeAvailable;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Ref;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeAvailable;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Ref;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeAftersale;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Adj;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeAftersale;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Adj;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeFrozen;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Fail;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeFrozen;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Fail;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeFactory;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_STT;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = CtrlStp_eSubModeFactory;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_STT;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = 5;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Maxsize;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = 5;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = CtrlStp_eState_Maxsize;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = 5;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = 6;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
/// \input Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_MODE = 5;
  Rte_Write_CtrlStp_Validation_Port_Param1.eADL_PHASE = 6;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_L = 3;
  Rte_Write_CtrlStp_Validation_Port_Param1.eLvlAdjHeadlampFault_R = 3;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(&Rte_Write_CtrlStp_Validation_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the values in the validation port are written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
/// \input CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_Param1 = 0;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_Validation_Port_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_Validation_Port_HitCount = 0;
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_Param1 = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(0);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_Validation_Port_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the values in the validation port are written correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(void)
{
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_1();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_2();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_3();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_4();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_5();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_6();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_7();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port_TestCase_8();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the actual stepper status is written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount = 0;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 0;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 0;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 0;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 1u, == );
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss, eNoStepLoss, == );
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eNoThermalWarning, ==
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eNoElectricalDefect
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount = 0;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 0;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 0;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss, eNoStepLoss, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eNoThermalWarning, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eNoElectricalDefect, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the actual stepper status is written correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 1;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 1;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 1;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 2u, == );
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss, eStepLossRisk, == );
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eColdTemperature, ==
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eOpenCircuitDefect
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 1;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 1;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss, eStepLossRisk, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eColdTemperature, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eOpenCircuitDefect, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the actual stepper status is written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 2;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 2;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 2;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 3u, == );
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eHighTemeratureWarning
/// \output  Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eShortCircuitDefect,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 2;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 2;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 2;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 3u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eHighTemeratureWarning, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eShortCircuitDefect, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the actual stepper status is written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 3;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 3;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 3;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 4u, == );
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eHighTemperatureSD, =
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eReservedElectrical
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 3;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 3;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 3;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 4u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState, eHighTemperatureSD, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect, eReservedElectrical, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the actual stepper status is written correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 4;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 4;
/// \input CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 4
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 5u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpStepLoss = 4;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState = 4;
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect = 4;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_ActStatStp_sVal_0_HitCount, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the actual stepper status is written correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(void)
{
  Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_1();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_2();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_3();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_4();
  Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0_TestCase_5();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = 0;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 17;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpSide = 0;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Start
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eMovementToTop, =
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eBothActuators, == )
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = 0;
  Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 17;
  Rte_Read_Stp_RoutineControl_Param1.eStpSide = 0;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Start, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eMovementToTop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eBothActuators, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 18;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpSide = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Stop,
/// \output CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eMovementToBottom
/// \output CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eLeftActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = 1;
  Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 18;
  Rte_Read_Stp_RoutineControl_Param1.eStpSide = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Stop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eMovementToBottom, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eLeftActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = 2;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 19;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpSide = 2;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Results
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eMovementToZero, ==
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = 2;
  Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 19;
  Rte_Read_Stp_RoutineControl_Param1.eStpSide = 2;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Results, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eMovementToZero, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpControl = 3;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 20;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpSide = 3;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eSequence1, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpControl = 3;
  Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 20;
  Rte_Read_Stp_RoutineControl_Param1.eStpSide = 3;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eSequence1, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input //Rte_Read_Stp_RoutineControl_Param1.eStpControl = 3;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 21;
/// \input //Rte_Read_Stp_RoutineControl_Param1.eStpSide = 3;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eSequence2, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  //Rte_Read_Stp_RoutineControl_Param1.eStpControl = 3;
  Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 21;
  //Rte_Read_Stp_RoutineControl_Param1.eStpSide = 3;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eSequence2, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input //Rte_Read_Stp_RoutineControl_Param1.eStpControl = 3;
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 22;
/// \input //Rte_Read_Stp_RoutineControl_Param1.eStpSide = 3;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  //Rte_Read_Stp_RoutineControl_Param1.eStpControl = 3;
  Rte_Read_Stp_RoutineControl_Param1.eStpRequest = 22;
  //Rte_Read_Stp_RoutineControl_Param1.eStpSide = 3;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl=CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest= CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide= CtrlStp_eRightActuator;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDD05;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDD05;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF10;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
/// \output CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF10;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF11;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF11;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF12;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF12;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if Stp Routine Control Routine Status is read properly  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF13;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
/// \input CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
/// \output  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  Rte_Read_Stp_RoutineControl_Param1.eStpDID = eDF13;
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1;
  Rte_Read_Stp_RoutineControl_Param1.boRequestStatus = 1;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl = CtrlStp_eStpControl_Start;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest = CtrlStp_eMovementToTop;
  CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide = CtrlStp_eRightActuator;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadDiagStpControlRoutine(&CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpControl, CtrlStp_eStpControl_Unknown, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpRequest, CtrlStp_eStop, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadDiagStpControlRoutine_Param1.eStpSide, CtrlStp_eRightActuator, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if Stp Routine Control Routine Status is read properly 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine(void)
{
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_4();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_5();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_6();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_7();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_8();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_9();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_10();
  Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine_TestCase_11();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingLeftFoggyRhdOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R = 20;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R, 20
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingLeftFoggyRhdOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R = 20;
  //Step 3) Call FUT
  Cod_AfsLevellingLeftFoggyRhdOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_RHD_R, 20, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrSttDelay
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 100;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY, 100
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrSttDelay(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY = 100;
  //Step 3) Call FUT
  Cod_LwrSttDelay();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.PitchData.unSTT_TRANSITION_DELAY, 100, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_GFHBOffsetLevellingDelay
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_OperationData.unGFHB_OFFSET_LEVELLING_DELAY = 1000;
///
///   - Expectations:
///
/// \output Cod_GFHBOffsetLevellingDelay_RetVal = 1000
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_GFHBOffsetLevellingDelay(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_OperationData.unGFHB_OFFSET_LEVELLING_DELAY = 1000;
  //Step 3) Call FUT
  Cod_GFHBOffsetLevellingDelay();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_OperationData.unGFHB_OFFSET_LEVELLING_DELAY, 1000, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_GFHBOffsetLevellingDelay
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_OperationData.unGFHB_OFFSET_LEVELLING_DELAY = 1000;
///
///   - Expectations:
///
/// \output Cod_GFHBOffsetLevellingDelay_RetVal = 1000
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LevellingStepperFailureReportTime(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Levelling_Stepper_Failure_Report_Time = 10;
  //Step 3) Call FUT
  Cod_LevellingStepperFailureReportTime();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_Levelling_Stepper_Failure_Report_Time, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrMaxRefSpeed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX = 50;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX, 50,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrMaxRefSpeed(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX = 50;
  //Step 3) Call FUT
  Cod_LwrMaxRefSpeed();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.PitchData.unREFERENCING_SPEED_MAX, 50, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingCorrectSpeed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_OperationData.unOFFSET_AFS_CORRECT_SPEED = 15;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_OperationData.unOFFSET_AFS_CORRECT_SPEED, 15
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingCorrectSpeed(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_OperationData.unOFFSET_AFS_CORRECT_SPEED = 15;
  //Step 3) Call FUT
  Cod_AfsLevellingCorrectSpeed();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_OperationData.unOFFSET_AFS_CORRECT_SPEED, 15, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingOffOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Off_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Off_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingOffOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Off_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingOffOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Off_R, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingLeftFoggyLhdOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingLeftFoggyLhdOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingLeftFoggyLhdOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Foggy_LHD_R, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingLeftBdwRhdOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingLeftBdwRhdOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingLeftBdwRhdOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_RHD_R, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingLeftBdwLhdOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingLeftBdwLhdOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingLeftBdwLhdOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_BDW_LHD_R, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingMWOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingMWOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingMWOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_R, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingMWBoostOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingMWBoostOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingMWBoostOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_MW_Boost_R, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingTownPedOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Town_Ped_R = 1
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Town_Ped_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingTownPedOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Town_Ped_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingTownPedOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_Town_Ped_R, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_AfsLevellingHBOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_AfsLevellingHBOffset(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R = 1;
  //Step 3) Call FUT
  Cod_AfsLevellingHBOffset();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.AfsOffset_Right.snAvacStp_AfsLevelling_HB_R, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrAutorefZeitversatz
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Autoreferencing_Delay = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.Modus.ucAvacStp_Autoreferencing_Delay, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrAutorefZeitversatz(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Autoreferencing_Delay = 1;
  //Step 3) Call FUT
  Cod_LwrAutorefZeitversatz();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_Autoreferencing_Delay, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrWellRefTimeout
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input 
/// \input 
///
///   - Expectations:
///
/// \output  
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrWellRefTimeout(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  //Step 3) Call FUT
  Cod_LwrWellRefTimeout();
  //Step 4) Check expected output value 
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrTestDlPeriode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrTestDlPeriode(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod = 1;
  //Step 3) Call FUT
  Cod_LwrTestDlPeriode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjPeriod, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrTestDlWeg
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrTestDlWeg(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange = 1;
  //Step 3) Call FUT
  Cod_LwrTestDlWeg();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_Test_AdjRange, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrTestDlAktiv
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_TestActive = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.Modus.ucAvacStp_TestActive, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrTestDlAktiv(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_TestActive = 1;
  //Step 3) Call FUT
  Cod_LwrTestDlAktiv();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_TestActive, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrHsWertStart
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS, 1,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrHsWertStart(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS = 1;
  //Step 3) Call FUT
  Cod_LwrHsWertStart();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_Movement_Threshold_HS, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrHsGrad
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L, 1,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrHsGrad(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L = 1;
  //Step 3) Call FUT
  Cod_LwrHsGrad();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.unAvacStp_Transmission_Factor_L, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrEnable
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.Modus.ucAvacStp_Enable, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrEnable(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Modus.ucAvacStp_Enable = 1;
  //Step 3) Call FUT
  Cod_LwrEnable();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Modus.ucAvacStp_Enable, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrHsZeitMinTt
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrHsZeitMinTt(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT = 1;
  //Step 3) Call FUT
  Cod_LwrHsZeitMinTt();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriodMin_LT, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrHsZeitSp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_SP = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_SP, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrHsZeitSp(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_SP = 1;
  //Step 3) Call FUT
  Cod_LwrHsZeitSp();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_SP, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrHsZeitAp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_PP = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_PP, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrHsZeitAp(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_PP = 1;
  //Step 3) Call FUT
  Cod_LwrHsZeitAp();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.Dynamik.unAvacStp_HsPeriod_PP, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrSp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SafetyPos = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_SafetyPos, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrSp(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SafetyPos = 1;
  //Step 3) Call FUT
  Cod_LwrSp();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SafetyPos, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrAp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ParkingPos = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_ParkingPos, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrAp(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ParkingPos = 1;
  //Step 3) Call FUT
  Cod_LwrAp();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ParkingPos, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrMaxWinkelPl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrMaxWinkelPl(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L = 1;
  //Step 3) Call FUT
  Cod_LwrMaxWinkelPl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.unAvacStp_UpperStpMovementRange_L, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrMaxWinkelMi
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrMaxWinkelMi(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L = 1;
  //Step 3) Call FUT
  Cod_LwrMaxWinkelMi();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpMovementRange_L, 1, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrAnschlagPl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrAnschlagPl(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 1;
  //Step 3) Call FUT
  Cod_LwrAnschlagPl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Cod_LwrAnschlagMi
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value from coding is returned in a proper way 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 1;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Cod_LwrAnschlagMi(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L = 1;
  //Step 3) Call FUT
  Cod_LwrAnschlagMi();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.unAvacStp_LowerStpBlockRange_L, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ParaFct0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the coding data is read properly and store results in local variables
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input CtrlStp_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input //CtrlStp_ParaFct0_Param2.AvacStp.SwGeoLi.ucAvacStp_SafetySign_L = 1u;
/// \input CtrlStp_SafetyPos = 1;
/// \input CtrlStp_ParkingPos = 1;
///
///   - Expectations:
///
/// \output CtrlStp_ParaFct0_Param2, 0, == );
/// \output CtrlStp_SafetyPos, 0, == );
/// \output CtrlStp_ParkingPos, 0, == );
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  CtrlStp_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  //CtrlStp_ParaFct0_Param2.AvacStp.SwGeoLi.ucAvacStp_SafetySign_L = 1u;
  CtrlStp_SafetyPos = 1;
  CtrlStp_ParkingPos = 1;
  //Step 3) Call FUT
  CtrlStp_ParaFct0(CtrlStp_ParaFct0_Param1, &CtrlStp_ParaFct0_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ParaFct0_Param2, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_SafetyPos, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_ParkingPos, 0, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ParaFct0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the coding data is read properly and store results in local variables
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedRight;
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input  CtrlStp_ParaFct0_Param1 = eParaFct0_CodingDataValid;
/// \input  CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L, 0,
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  CtrlStp_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L = 1u;
  //Step 3) Call FUT
  CtrlStp_ParaFct0(CtrlStp_ParaFct0_Param1, &CtrlStp_ParaFct0_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L, 0, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ParaFct0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the coding data is read properly and store results in local variables
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = 2u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input CtrlStp_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L = 1u;
/// \input boLwrApVz = TRUE;
/// \input boLwrSpVz = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L, 1
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, ==
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ParaFct0_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = 2u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  CtrlStp_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L = 1u;
  boLwrApVz = TRUE;
  boLwrSpVz = TRUE;
  //Step 3) Call FUT
  CtrlStp_ParaFct0(CtrlStp_ParaFct0_Param1, &CtrlStp_ParaFct0_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingData.SwGeoLi.ucAvacStp_SafetySign_L, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the coding data is read properly and store results in local variables
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ParaFct0(void)
{
  Mt_CtrlStp_ParaFct0_TestCase_1();
  Mt_CtrlStp_ParaFct0_TestCase_2();
  Mt_CtrlStp_ParaFct0_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 0;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadElectricalSuppState_Param1.eElectrSupplyState, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadElectricalSuppState_Param1.eElectrSupplyState, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 1;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 2;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 2
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 2;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 3;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 3
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 3;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 3, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 4;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 4
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 4;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 4, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 5
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 5
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 5;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 5, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 6;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 6
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 6;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 6, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 7;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 7
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 7;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 7, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 8;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 8
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 8;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 8, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 9;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 9
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 9;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 9, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 10;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 10
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 10;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_12
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 11
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 11
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_12(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 11;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, 11, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_13
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 12;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_13(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = 12;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_14
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 0;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadElectricalSuppState_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_14(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadElectricalSuppState_Param2, 0, == );
}
//CtrlStp_eEtatFee_Invalid;

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_15
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the TMC pressure is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_INVALID;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadElectricalSuppState_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_15(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_INVALID;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadElectricalSuppState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadElectricalSuppState_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadElectricalSuppState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the TMC pressure is read correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadElectricalSuppState(void)
{
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_4();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_5();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_6();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_7();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_8();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_9();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_10();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_11();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_12();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_13();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_14();
  Mt_CtrlStp_RteAccess_ReadElectricalSuppState_TestCase_15();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if Autorization to activate boost led for low beam is read correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// - Rte_Read_SysMon_Afs_Signals_HitCount = 0;
/// - Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = 1;
/// - Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = 0;
/// - Rte_Read_SysMon_Afs_Signals_Param1.eLbBoost_Allowed = 1;
/// - 
/// - Expectations:
///    Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
///    Rte_Read_SysMon_Afs_Signals_Param1.eLbBoost_Allowed, 1
///    
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  Rte_Read_SysMon_Afs_Signals_HitCount = 0;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = 1;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = 0;
  Rte_Read_SysMon_Afs_Signals_Param1.eLbBoost_Allowed = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLbBoostAllowed();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_Param1.eLbBoost_Allowed, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if Autorization to activate boost led for low beam is read correctly
///			-
///
/// - Preconditions:
/// - 	tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// -   Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = 1;
/// - 	Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = 1;
/// - 	Rte_Read_DiagControl_AfsState_Param1.eLowBeamBoostAlwd = 1;
/// - 	Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// - 	
/// - Expectations:
///    Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
///    Rte_Read_DiagControl_AfsState_Param1.eLowBeamBoostAlwd, 1
///    
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = 1;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = 1;
  Rte_Read_DiagControl_AfsState_Param1.eLowBeamBoostAlwd = 1;
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLbBoostAllowed();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_DiagControl_AfsState_Param1.eLowBeamBoostAlwd, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description:Check that if Autorization to activate boost led for low beam is read correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// - Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// - Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = 0;
/// - Expectations:
///       Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == )
///       CtrlStp_RteAccess_ReadLbBoostAllowed_Param2, 0
///       
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLbBoostAllowed();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadLbBoostAllowed_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if Autorization to activate boost led for low beam is read correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// -   Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_TIMEOUT;
/// - 	Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
///
/// - Expectations:
///     Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == )
///     CtrlStp_RteAccess_ReadLbBoostAllowed_RetVal, 0
///     
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadLbBoostAllowed_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_TIMEOUT;
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLbBoostAllowed_RetVal = CtrlStp_RteAccess_ReadLbBoostAllowed();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadLbBoostAllowed_RetVal, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLbBoostAllowed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if Autorization to activate boost led for low beam is read correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLbBoostAllowed(void)
{
  Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadLbBoostAllowed_TestCase_4();
}



//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that if reading diagnosis from slave stepper is done correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_HitCount                = 0;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty          = 1;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR        = 1;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR    = 1;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR    = 1;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR        = 1;
///
/// - Expectations:
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_HitCount,                1u
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR,        1
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR,    1
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR,    1
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR,        1
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR = 1;
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingDiagStatus(&CtrlStp_RteAccess_ReadLevellingDiagStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description:Check that if reading diagnosis from slave stepper is done correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///   Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = 0;//SIG_SNA
///   Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0u;
///
/// - Expectations:
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_HitCount,                1u
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, CtrlStp_eLvlElecR_OpenCircuit
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = 0;//SIG_SNA
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingDiagStatus(&CtrlStp_RteAccess_ReadLevellingDiagStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, CtrlStp_eLvlElecR_OpenCircuit, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description:Check that if reading diagnosis from slave stepper is done correctly
///			-
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_INVALID;
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0u;
///
/// - Expectations:
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_HitCount,                1u
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR,        CtrlStp_eLvlElecR_OpenCircuit
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR,    CtrlStp_eLvlSteplossR_SteplossRisk
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR,    1
/// - 	Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR,        CtrlStp_eLvlVoltR_UnderVoltage
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingDiagStatus_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SigPrep_LevellingDiagStatus_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingDiagStatus(&CtrlStp_RteAccess_ReadLevellingDiagStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlElecR, CtrlStp_eLvlElecR_OpenCircuit, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlTemperatureR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlSteplossR, CtrlStp_eLvlSteplossR_SteplossRisk, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlRefStateR, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingDiagStatus_Param1.eLvlVoltR, CtrlStp_eLvlVoltR_UnderVoltage, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if reading diagnosis from slave stepper is done correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus(void)
{
  Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingFeedback_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if reading the feedback from slave stepper is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1, == );
/// \output Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingFeedback_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 1;
  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingFeedback(&CtrlStp_RteAccess_ReadLevellingFeedback_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 1, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingFeedback_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if reading the feedback from slave stepper is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingFeedback_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 0;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 0;
/// \input Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
/// \output  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 0, == );
/// \output  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingFeedback_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingFeedback_HitCount = 0u;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eSigQty = 0;
  Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl = 0;
  Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl = 1;
  //CtrlStp_RteAccess_ReadLevellingFeedback_Param1->eSigQty = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingFeedback(&CtrlStp_RteAccess_ReadLevellingFeedback_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.eRPosSignLvl, 0, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingFeedback_Param1.ePositionSiteD.unRPosLvl, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingFeedback
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if reading the feedback from slave stepper is done correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingFeedback(void)
{
  Mt_CtrlStp_RteAccess_ReadLevellingFeedback_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadLevellingFeedback_TestCase_2();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the state of vehicle configuration is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = 1;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = 1;
///
///   - Expectations:
///
/// \output Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
/// \output Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = 1;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the state of vehicle configuration is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = 0;
/// \input CtrlStp_RteAccess_ReadVehicleModeConfig_Param2 = 15;// eModeConfigVehicle_Invalid2 = 15U
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, ==
/// \output  CtrlStp_RteAccess_ReadVehicleModeConfig_Param2, 15
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = 0;
  CtrlStp_RteAccess_ReadVehicleModeConfig_Param2 = 15;// eModeConfigVehicle_Invalid2 = 15U
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVehicleModeConfig_Param2, 15, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the state of vehicle configuration is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
/// \input Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
/// \input CtrlStp_RteAccess_ReadVehicleModeConfig_Param2 = 1;// eModeConfigVehicle_Invalid2 = 15U
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, ==
/// \output  CtrlStp_RteAccess_ReadVehicleModeConfig_Param2, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;
  Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty = SIG_INVALID;
  CtrlStp_RteAccess_ReadVehicleModeConfig_Param2 = 1;// eModeConfigVehicle_Invalid2 = 15U
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVehicleModeConfig();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVehicleModeConfig_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleModeConfig
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the state of vehicle configuration is done correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleModeConfig(void)
{
  Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadVehicleModeConfig_TestCase_3();

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the state of avac is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppsAvacOut_HitCount = 0;
/// \input Rte_Read_ppsAvacOut_Param1.State = 1;
/// \input Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
///
///   - Expectations:
///
/// \output Rte_Read_ppsAvacOut_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadAvacCommand_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppsAvacOut_HitCount = 0;
  Rte_Read_ppsAvacOut_Param1.State = 1;
  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAvacCommand(&CtrlStp_RteAccess_ReadAvacCommand_Param1, &CtrlStp_RteAccess_ReadAvacCommand_Param2, CtrlStp_RteAccess_ReadAvacCommand_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the state of avac is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppsAvacOut_HitCount = 0u;
/// \input Rte_Read_ppsAvacOut_Param1.State = 3;
/// \input Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
///
///   - Expectations:
///
/// \output Rte_Read_ppsAvacOut_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadAvacCommand_Param2, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppsAvacOut_HitCount = 0u;
  Rte_Read_ppsAvacOut_Param1.State = 3;
  Rte_Read_ppsAvacOut_Param1.Position->Ver = 1;
  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAvacCommand(&CtrlStp_RteAccess_ReadAvacCommand_Param1, &CtrlStp_RteAccess_ReadAvacCommand_Param2, CtrlStp_RteAccess_ReadAvacCommand_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAvacCommand_Param2, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the state of avac is read correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppsAvacOut_HitCount = 0u;
/// \input Rte_Read_ppsAvacOut_Param1.State = 5;//SIG_DEFAULT
/// \input Rte_Read_ppsAvacOut_Param1.Position->Ver = 6;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
/// \input CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
///
///   - Expectations:
///
/// \output Rte_Read_ppsAvacOut_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadAvacCommand_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppsAvacOut_HitCount = 0u;
  Rte_Read_ppsAvacOut_Param1.State = 5;//SIG_DEFAULT
  Rte_Read_ppsAvacOut_Param1.Position->Ver = 6;
  CtrlStp_RteAccess_ReadAvacCommand_Param2 = 0;
  CtrlStp_RteAccess_ReadAvacCommand_Param3 = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAvacCommand(&CtrlStp_RteAccess_ReadAvacCommand_Param1, &CtrlStp_RteAccess_ReadAvacCommand_Param2, CtrlStp_RteAccess_ReadAvacCommand_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_ppsAvacOut_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAvacCommand_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAvacCommand
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the state of avac is read correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAvacCommand(void)
{
  Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadAvacCommand_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the reading vechicle electric state is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 1;
/// \input CtrlStp_RteAccess_ReadVESMainState_Param1.eVESMainState = 1;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 1u, ==
/// \output  CtrlStp_RteAccess_ReadVESMainState_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_HitCount = 0;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 1;
  CtrlStp_RteAccess_ReadVESMainState_Param1.eVESMainState = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVESMainState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVESMainState_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the reading vechicle electric state is done correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
/// \input CtrlStp_RteAccess_ReadVESMainState_Param1.eVESMainState = 0;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount, 1u, ==
/// \output CtrlStp_RteAccess_ReadVESMainState_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  CtrlStp_RteAccess_ReadVESMainState_Param1.eVESMainState = 0;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVESMainState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVESMainState_Param2, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the reading vechicle electric state is done correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
/// \input CtrlStp_RteAccess_ReadVESMainState_Param1.eSigQty = SIG_INVALID;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadVESMainState_RetVal, (uint8)VESState_Invalid
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
  CtrlStp_RteAccess_ReadVESMainState_Param1.eSigQty = SIG_INVALID;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVESMainState_RetVal = CtrlStp_RteAccess_ReadVESMainState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVESMainState_RetVal, (uint8)VESState_Invalid, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the reading vechicle electric state is done correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
/// \input CtrlStp_RteAccess_ReadVESMainState_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount, 1u, == 
/// \output CtrlStp_RteAccess_ReadVESMainState_RetVal, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_TIMEOUT;
  CtrlStp_RteAccess_ReadVESMainState_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVESMainState_RetVal = CtrlStp_RteAccess_ReadVESMainState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVESMainState_RetVal, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVESMainState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the reading vechicle electric state is done correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVESMainState(void)
{
  Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadVESMainState_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads vechicle electric state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0;
/// \input CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eSigQty = 1;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 1;
/// \input CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eElectricNetworkState = 1;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 1;//eTI_DEGRADE
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadVehicleElectricState_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_VehNetState_HitCount = 0;
  CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eSigQty = 1;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 1;
  CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eElectricNetworkState = 1;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 1;//eTI_DEGRADE
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVehicleElectricState_Retval = CtrlStp_RteAccess_ReadVehicleElectricState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVehicleElectricState_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads vechicle electric state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
/// \input CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eElectricNetworkState = 1;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 0;//eTI_NOMINAL
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadVehicleElectricState_Param2, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = 0;
  CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eElectricNetworkState = 1;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 0;//eTI_NOMINAL
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVehicleElectricState_Retval = CtrlStp_RteAccess_ReadVehicleElectricState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVehicleElectricState_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads vechicle electric state 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
/// \input CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eElectricNetworkState = 1;
/// \input Rte_Read_SysMon_VehNetState_HitCount = 0u;
/// \input Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 0;//eTI_NOMINAL
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadVehicleElectricState_Retval, (uint8)eInvalid
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty = SIG_INVALID;
  CtrlStp_RteAccess_ReadVehicleElectricState_Param1.eElectricNetworkState = 1;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = 0;//eTI_NOMINAL
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadVehicleElectricState_Retval = CtrlStp_RteAccess_ReadVehicleElectricState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadVehicleElectricState_Retval, (uint8)eInvalid, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadVehicleElectricState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads vechicle electric state
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadVehicleElectricState(void)
{
  Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadVehicleElectricState_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads speed correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_ReadSpeed_Param1 = 0;
/// \input CtrlStp_RteAccess_ReadSpeed_Param2.eSigQty = SIG_VALID;
/// \input CtrlStp_RteAccess_ReadSpeed_Param2.eVehicleSpeedDispo = 1;/
/// \input uint16 CtrlStp_RteAccess_ReadSpeed_Param3 = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = 1;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehicleSpeed_HitCount, 1u
/// \output  CtrlStp_RteAccess_ReadSpeed_Param1, 0, ==
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_ReadSpeed_Param1 = 0;
  CtrlStp_RteAccess_ReadSpeed_Param2.eSigQty = SIG_VALID;
  CtrlStp_RteAccess_ReadSpeed_Param2.eVehicleSpeedDispo = 1;// eVvhIndisp_SpeedInfoAvailable;
  uint16 CtrlStp_RteAccess_ReadSpeed_Param3 = 0;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = 1;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSpeed(&CtrlStp_RteAccess_ReadSpeed_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSpeed_Param1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads speed correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_ReadSpeed_Param1 = 0;
/// \input CtrlStp_RteAccess_ReadSpeed_Param2.eSigQty = 0;
/// \input CtrlStp_RteAccess_ReadSpeed_Param2.eVehicleSpeedDispo = 1;
/// \input uint16 CtrlStp_RteAccess_ReadSpeed_Param3 = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = 0
///
///   - Expectations:
///
/// \output  (Rte_Read_SysMon_VehicleSpeed_HitCount, 1u
/// \output  (CtrlStp_RteAccess_ReadSpeed_Param1, 0, ==
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_ReadSpeed_Param1 = 0;
  CtrlStp_RteAccess_ReadSpeed_Param2.eSigQty = 0;
  CtrlStp_RteAccess_ReadSpeed_Param2.eVehicleSpeedDispo = 1;// eVvhIndisp_SpeedInfoAvailable;
  uint16 CtrlStp_RteAccess_ReadSpeed_Param3 = 0;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = 0;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSpeed(&CtrlStp_RteAccess_ReadSpeed_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSpeed_Param1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads speed correctly 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_ReadSpeed_Param1 = 0;
/// \input uint16 CtrlStp_RteAccess_ReadSpeed_Param3 = 0;
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = 0;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_VehicleSpeed_HitCount, 1u
/// \output  CtrlStp_RteAccess_ReadSpeed_Param1, 1, ==
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_ReadSpeed_Param1 = 0;
  uint16 CtrlStp_RteAccess_ReadSpeed_Param3 = 0;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo = 0;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSpeed(&CtrlStp_RteAccess_ReadSpeed_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSpeed_Param1, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSpeed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads speed correctly
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSpeed(void)
{
  Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadSpeed_TestCase_3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StpPos2Angle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert stepper position to angle 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_StpPos2Angle_Param1 = 0;
/// \input CtrlStp_StpPos2Angle_Param2 = 200;
/// \input CtrlStp_StpPos2Angle_Param3 = 10;
/// \input CtrlStp_StpPos2Angle_Param4 = 0;
/// \input CtrlStp_StpPos2Angle_Param5 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_StpPos2Angle_Param4, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StpPos2Angle_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_StpPos2Angle_Param1 = 0;
  CtrlStp_StpPos2Angle_Param2 = 200;
  CtrlStp_StpPos2Angle_Param3 = 10;
  CtrlStp_StpPos2Angle_Param4 = 0;
  CtrlStp_StpPos2Angle_Param5 = 0;
  //Step 3) Call FUT
  CtrlStp_StpPos2Angle(CtrlStp_StpPos2Angle_Param1, CtrlStp_StpPos2Angle_Param2, CtrlStp_StpPos2Angle_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_StpPos2Angle_Param4, 0, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StpPos2Angle_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert stepper position to angle  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_StpPos2Angle_Param1 = 10;
/// \input CtrlStp_StpPos2Angle_Param2 = 200;
/// \input CtrlStp_StpPos2Angle_Param3 = 10;
/// \input CtrlStp_StpPos2Angle_Param4 = 0;
/// \input CtrlStp_StpPos2Angle_Param5 = 0;
///
///   - Expectations:
///
/// \output  CtrlStp_StpPos2Angle_Param4, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StpPos2Angle_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_StpPos2Angle_Param1 = 10;
  CtrlStp_StpPos2Angle_Param2 = 200;
  CtrlStp_StpPos2Angle_Param3 = 10;
  CtrlStp_StpPos2Angle_Param4 = 0;
  CtrlStp_StpPos2Angle_Param5 = 0;
  //Step 3) Call FUT
  CtrlStp_StpPos2Angle(CtrlStp_StpPos2Angle_Param1, CtrlStp_StpPos2Angle_Param2, CtrlStp_StpPos2Angle_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_StpPos2Angle_Param4, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StpPos2Angle_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert stepper position to angle  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_StpPos2Angle_Param1 = 2;
/// \input CtrlStp_StpPos2Angle_Param2 = 1;
/// \input CtrlStp_StpPos2Angle_Param3 = 0;
/// \input CtrlStp_StpPos2Angle_Param4 = 0;
/// \input CtrlStp_StpPos2Angle_Param5 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_StpPos2Angle_Param4, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StpPos2Angle_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_StpPos2Angle_Param1 = 2;
  CtrlStp_StpPos2Angle_Param2 = 1;
  CtrlStp_StpPos2Angle_Param3 = 0;
  CtrlStp_StpPos2Angle_Param4 = 0;
  CtrlStp_StpPos2Angle_Param5 = 0;
  //Step 3) Call FUT
  CtrlStp_StpPos2Angle(CtrlStp_StpPos2Angle_Param1, CtrlStp_StpPos2Angle_Param2, CtrlStp_StpPos2Angle_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_StpPos2Angle_Param4, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StpPos2Angle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function convert stepper position to angle 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StpPos2Angle(void)
{
  Mt_CtrlStp_StpPos2Angle_TestCase_1();
  Mt_CtrlStp_StpPos2Angle_TestCase_2();
  Mt_CtrlStp_StpPos2Angle_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Tmin2Speed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert Tmin to speed 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Tmin2Speed_Param1 = 100;
/// \input CtrlStp_Tmin2Speed_Param2 = 200;
///
///   - Expectations:
///
/// \output CtrlStp_Tmin2Speed_RetVal, 50000u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Tmin2Speed_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Tmin2Speed_Param1 = 100;
  CtrlStp_Tmin2Speed_Param2 = 200;
  //Step 3) Call FUT
  CtrlStp_Tmin2Speed_RetVal = CtrlStp_Tmin2Speed(CtrlStp_Tmin2Speed_Param1, CtrlStp_Tmin2Speed_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Tmin2Speed_RetVal, 50000u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Tmin2Speed_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that the function convert Tmin to speed  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Tmin2Speed_Param1 = 0;
/// \input CtrlStp_Tmin2Speed_Param2 = 10;
///
///   - Expectations:
///
/// \output CtrlStp_Tmin2Speed_RetVal, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Tmin2Speed_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Tmin2Speed_Param1 = 0;
  CtrlStp_Tmin2Speed_Param2 = 10;
  //Step 3) Call FUT
  CtrlStp_Tmin2Speed_RetVal = CtrlStp_Tmin2Speed(CtrlStp_Tmin2Speed_Param1, CtrlStp_Tmin2Speed_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Tmin2Speed_RetVal, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Tmin2Speed_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert Tmin to speed 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Tmin2Speed_Param1 = 1;
/// \input CtrlStp_Tmin2Speed_Param2 = 10;
///
///   - Expectations:
///
/// \output CtrlStp_Tmin2Speed_RetVal, 65535u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Tmin2Speed_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Tmin2Speed_Param1 = 1;
  CtrlStp_Tmin2Speed_Param2 = 10;
  //Step 3) Call FUT
  CtrlStp_Tmin2Speed_RetVal = CtrlStp_Tmin2Speed(CtrlStp_Tmin2Speed_Param1, CtrlStp_Tmin2Speed_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Tmin2Speed_RetVal, 65535u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Tmin2Speed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function convert Tmin to speed 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Tmin2Speed(void)
{
  Mt_CtrlStp_Tmin2Speed_TestCase_1();
  Mt_CtrlStp_Tmin2Speed_TestCase_2();
  Mt_CtrlStp_Tmin2Speed_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Speed2Tmin_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  convert speed to Tmin 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Speed2Tmin_Param1 = 200;
/// \input CtrlStp_Speed2Tmin_Param2 = 100;
///
///   - Expectations:
///
/// \output CtrlStp_Speed2Tmin_RetVal, 50000u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Speed2Tmin_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Speed2Tmin_Param1 = 200;
  CtrlStp_Speed2Tmin_Param2 = 100;
  //Step 3) Call FUT
  CtrlStp_Speed2Tmin_RetVal = CtrlStp_Speed2Tmin(CtrlStp_Speed2Tmin_Param1, CtrlStp_Speed2Tmin_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Speed2Tmin_RetVal, 50000u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Speed2Tmin_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  convert speed to Tmin
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Speed2Tmin_Param1 = 0;
/// \input CtrlStp_Speed2Tmin_Param2 = 100;
///
///   - Expectations:
///
/// \output CtrlStp_Speed2Tmin_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Speed2Tmin_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Speed2Tmin_Param1 = 0;
  CtrlStp_Speed2Tmin_Param2 = 100;
  //Step 3) Call FUT
  CtrlStp_Speed2Tmin_RetVal = CtrlStp_Speed2Tmin(CtrlStp_Speed2Tmin_Param1, CtrlStp_Speed2Tmin_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Speed2Tmin_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Speed2Tmin_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  convert speed to Tmin
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Speed2Tmin_Param1 = 1;
/// \input CtrlStp_Speed2Tmin_Param2 = 1000;
///
///   - Expectations:
///
/// \output  CtrlStp_Speed2Tmin_RetVal, 65535u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Speed2Tmin_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Speed2Tmin_Param1 = 1;
  CtrlStp_Speed2Tmin_Param2 = 1000;
  //Step 3) Call FUT
  CtrlStp_Speed2Tmin_RetVal = CtrlStp_Speed2Tmin(CtrlStp_Speed2Tmin_Param1, CtrlStp_Speed2Tmin_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Speed2Tmin_RetVal, 65535u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Speed2Tmin
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function  convert speed to Tmin
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Speed2Tmin(void)
{
  Mt_CtrlStp_Speed2Tmin_TestCase_1();
  Mt_CtrlStp_Speed2Tmin_TestCase_2();
  Mt_CtrlStp_Speed2Tmin_TestCase_3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LimitAngle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function limit angle according to mechanical headlamp parameters 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_LimitAngle_Param1 = 10;
/// \input CtrlStp_LimitAngle_Param2 = 100;
/// \input CtrlStp_LimitAngle_Param3 = 5;
/// \input CtrlStp_LimitAngle_Param4 = 0;
/// \input CtrlStp_LimitAngle_Param5 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_LimitAngle_Param3, 5
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LimitAngle_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_LimitAngle_Param1 = 10;
  CtrlStp_LimitAngle_Param2 = 100;
  CtrlStp_LimitAngle_Param3 = 5;
  CtrlStp_LimitAngle_Param4 = 0;
  CtrlStp_LimitAngle_Param5 = 0;
  //Step 3) Call FUT
  CtrlStp_LimitAngle(CtrlStp_LimitAngle_Param1, CtrlStp_LimitAngle_Param2, CtrlStp_LimitAngle_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_LimitAngle_Param3, 5, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LimitAngle_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function limit angle according to mechanical headlamp parameters 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_LimitAngle_Param1 = 0.1;
/// \input CtrlStp_LimitAngle_Param2 = 0.01;
/// \input CtrlStp_LimitAngle_Param3 = 5;
/// \input CtrlStp_LimitAngle_Param4 = 0;
/// \input CtrlStp_LimitAngle_Param5 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_LimitAngle_Param3, 5
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LimitAngle_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_LimitAngle_Param1 = 0.1;
  CtrlStp_LimitAngle_Param2 = 0.01;
  CtrlStp_LimitAngle_Param3 = 5;
  CtrlStp_LimitAngle_Param4 = 0;
  CtrlStp_LimitAngle_Param5 = 0;
  //Step 3) Call FUT
  CtrlStp_LimitAngle(CtrlStp_LimitAngle_Param1, CtrlStp_LimitAngle_Param2, CtrlStp_LimitAngle_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_LimitAngle_Param3, 5, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LimitAngle_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function limit angle according to mechanical headlamp parameters  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_LimitAngle_Param1 = -0.01;
/// \input CtrlStp_LimitAngle_Param2 = 0.01;
/// \input CtrlStp_LimitAngle_Param3 = 0.01;
/// \input CtrlStp_LimitAngle_Param4 = 0;
/// \input CtrlStp_LimitAngle_Param5 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_LimitAngle_Param3, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LimitAngle_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_LimitAngle_Param1 = -0.01;
  CtrlStp_LimitAngle_Param2 = 0.01;
  CtrlStp_LimitAngle_Param3 = 0.01;
  CtrlStp_LimitAngle_Param4 = 0;
  CtrlStp_LimitAngle_Param5 = 0;
  //Step 3) Call FUT
  CtrlStp_LimitAngle(CtrlStp_LimitAngle_Param1, CtrlStp_LimitAngle_Param2, CtrlStp_LimitAngle_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_LimitAngle_Param3, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_LimitAngle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function limit angle according to mechanical headlamp parameters 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_LimitAngle(void)
{
  Mt_CtrlStp_LimitAngle_TestCase_1();
  Mt_CtrlStp_LimitAngle_TestCase_2();
  Mt_CtrlStp_LimitAngle_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckForStart_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check new halfstep position to decide if movement is requested
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CheckForStart_Param1 = 1u;
/// \input CtrlStp_CheckForStart_Param2 = FALSE;
/// \input CtrlStp_CheckForStart_Param3 = 2;
/// \input CtrlStp_CheckForStart_Param4 = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CheckForStart_Param4, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckForStart_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CheckForStart_Param1 = 1u;
  CtrlStp_CheckForStart_Param2 = FALSE;
  CtrlStp_CheckForStart_Param3 = 2;
  CtrlStp_CheckForStart_Param4 = 1;
  //Step 3) Call FUT
  CtrlStp_CheckForStart(CtrlStp_CheckForStart_Param1, CtrlStp_CheckForStart_Param2, CtrlStp_CheckForStart_Param3, CtrlStp_CheckForStart_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CheckForStart_Param4, 1, == );

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckForStart_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check new halfstep position to decide if movement is requested 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CheckForStart_Param1 = 0u;
/// \input CtrlStp_CheckForStart_Param2 = TRUE;
/// \input CtrlStp_CheckForStart_Param3 = 10;
/// \input CtrlStp_CheckForStart_Param4 = 20;
///
///   - Expectations:
///
/// \output CtrlStp_CheckForStart_Param3, 10
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckForStart_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CheckForStart_Param1 = 0u;
  CtrlStp_CheckForStart_Param2 = TRUE;
  CtrlStp_CheckForStart_Param3 = 10;
  CtrlStp_CheckForStart_Param4 = 20;
  //Step 3) Call FUT
  CtrlStp_CheckForStart(CtrlStp_CheckForStart_Param1, CtrlStp_CheckForStart_Param2, CtrlStp_CheckForStart_Param3, CtrlStp_CheckForStart_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CheckForStart_Param3, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckForStart_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check new halfstep position to decide if movement is requested
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CheckForStart_Param1 = 10u;
/// \input CtrlStp_CheckForStart_Param2 = FALSE;
/// \input CtrlStp_CheckForStart_Param3 = 10;
/// \input CtrlStp_CheckForStart_Param4 = 15;
///
///   - Expectations:
///
/// \output  CtrlStp_CheckForStart_Param3, 10
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckForStart_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CheckForStart_Param1 = 10u;
  CtrlStp_CheckForStart_Param2 = FALSE;
  CtrlStp_CheckForStart_Param3 = 10;
  CtrlStp_CheckForStart_Param4 = 15;
  //Step 3) Call FUT
  CtrlStp_CheckForStart(CtrlStp_CheckForStart_Param1, CtrlStp_CheckForStart_Param2, CtrlStp_CheckForStart_Param3, CtrlStp_CheckForStart_Param4);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CheckForStart_Param3, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CheckForStart
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check new halfstep position to decide if movement is requested 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CheckForStart(void)
{
  Mt_CtrlStp_CheckForStart_TestCase_1();
  Mt_CtrlStp_CheckForStart_TestCase_2();
  Mt_CtrlStp_CheckForStart_TestCase_3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Angle2StpPos_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert angle to halfstep position 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Angle2StpPos_Param1 = 500;
/// \input CtrlStp_Angle2StpPos_Param2 = 0;
/// \input CtrlStp_Angle2StpPos_Param3 = 10;
/// \input CtrlStp_Angle2StpPos_Param4 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_Angle2StpPos_Param4, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Angle2StpPos_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Angle2StpPos_Param1 = 500;
  CtrlStp_Angle2StpPos_Param2 = 0;
  CtrlStp_Angle2StpPos_Param3 = 10;
  CtrlStp_Angle2StpPos_Param4 = 0;
  //Step 3) Call FUT
  CtrlStp_Angle2StpPos(CtrlStp_Angle2StpPos_Param1, CtrlStp_Angle2StpPos_Param2, CtrlStp_Angle2StpPos_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Angle2StpPos_Param4, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Angle2StpPos_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function convert angle to halfstep position  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Angle2StpPos_Param1 = 500;
/// \input CtrlStp_Angle2StpPos_Param2 = 0;
/// \input CtrlStp_Angle2StpPos_Param3 = -1;
/// \input CtrlStp_Angle2StpPos_Param4 = 0;
///
///   - Expectations:
///
/// \output CtrlStp_Angle2StpPos_Param4, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Angle2StpPos_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Angle2StpPos_Param1 = 500;
  CtrlStp_Angle2StpPos_Param2 = 0;
  CtrlStp_Angle2StpPos_Param3 = -1;
  CtrlStp_Angle2StpPos_Param4 = 0;
  //Step 3) Call FUT
  CtrlStp_Angle2StpPos(CtrlStp_Angle2StpPos_Param1, CtrlStp_Angle2StpPos_Param2, CtrlStp_Angle2StpPos_Param3);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Angle2StpPos_Param4, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_Angle2StpPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function convert angle to halfstep position 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_Angle2StpPos(void)
{
  Mt_CtrlStp_Angle2StpPos_TestCase_1();
  Mt_CtrlStp_Angle2StpPos_TestCase_2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_EntryNorm
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets value of state Norm 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_1;
///
///   - Expectations:
///
/// \output CtrlStp_Status.ucLWRState, 2
//----------------------------------------------------------------------------- 
void Mt_CtrlStp_EntryNorm(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  //Step 3) Call FUT
  CtrlStp_EntryNorm();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRState, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CodingDataReady_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if coding data are available and  also EFT data (in this case coding data is illegal)
///         and mounting side (needed to select coding data)
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_CodingDataReady_Param1 = CtrlStp_eMountedLeft;
/// \input  //boolean         CtrlStp_CodingDataReady_Param2 = TRUE;//FALSE
/// \input  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
///
///   - Expectations:
///
/// \output  CtrlStp_CodingDataReady_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CodingDataReady_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingDataReady_Param1 = CtrlStp_eMountedLeft;
  //boolean         CtrlStp_CodingDataReady_Param2 = TRUE;//FALSE
  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  //Step 3) Call FUT
  CtrlStp_CodingDataReady(&CtrlStp_CodingDataReady_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingDataReady_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CodingDataReady_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if coding data are available and  also EFT data (in this case coding data is illegal)
///         and mounting side (needed to select coding data)
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingDataReady_Param1 = eMountedRight;
/// \input CtrlStp_CodingDataReady_Param2 = TRUE;//FALSE
///
///   - Expectations:
///
/// \output CtrlStp_CodingDataReady_Param2, 1u
///
//-----------------------------------------------------------------------------  
void Mt_CtrlStp_CodingDataReady_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingDataReady_Param1 = eMountedRight;
  CtrlStp_CodingDataReady_Param2 = TRUE;//FALSE
  //Step 3) Call FUT
  CtrlStp_CodingDataReady(&CtrlStp_CodingDataReady_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingDataReady_Param2, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CodingDataReady_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if coding data are available and  also EFT data (in this case coding data is illegal)
///         and mounting side (needed to select coding data) 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_CodingDataReady_Param1 = 255u;
/// \input CtrlStp_CodingDataReady_Param2 = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_CodingDataReady_Param2, FALSE
///
//-----------------------------------------------------------------------------  
void Mt_CtrlStp_CodingDataReady_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_CodingDataReady_Param1 = 255u;
  CtrlStp_CodingDataReady_Param2 = FALSE;
  //Step 3) Call FUT
  CtrlStp_CodingDataReady(&CtrlStp_CodingDataReady_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CodingDataReady_Param2, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CodingDataReady
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:Check if coding data are available and  also EFT data (in this case coding data is illegal)
///         and mounting side (needed to select coding data)  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CodingDataReady(void)
{
  Mt_CtrlStp_CodingDataReady_TestCase_1();
  Mt_CtrlStp_CodingDataReady_TestCase_2();
  Mt_CtrlStp_CodingDataReady_TestCase_3();

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - reads HB - high beam command
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// -  Rte_Read_SysMon_StdLgtFcts_Req_HitCount      = 0u;
/// - Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
/// - CtrlStp_RteAccess_ReadHbCmd_Param1.eSigQty    = 1u;
/// - CtrlStp_RteAccess_ReadHbCmd_Param2            = 1u;
/// - Expectations:
///    Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u
///     CtrlStp_RteAccess_ReadHbCmd_Param2, 1u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
  CtrlStp_RteAccess_ReadHbCmd_Param1.eSigQty = 1u;
  CtrlStp_RteAccess_ReadHbCmd_Param2 = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadHbCmd();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadHbCmd_Param2, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - reads HB - high beam command
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// -  Rte_Read_SysMon_StdLgtFcts_Req_HitCount      = 0u;
/// - Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_E2E_TIMEOUT;
/// - CtrlStp_RteAccess_ReadHbCmd_Param1.eSigQty    = 8u;
/// - CtrlStp_RteAccess_ReadHbCmd_Param2            = 0u;
/// - Expectations:
///    Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u
///     CtrlStp_RteAccess_ReadHbCmd_Param2, 0u
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_E2E_TIMEOUT;
  CtrlStp_RteAccess_ReadHbCmd_Param1.eSigQty = 8u;
  CtrlStp_RteAccess_ReadHbCmd_Param2 = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadHbCmd();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadHbCmd_Param2, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - reads HB - high beam command
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_INVALID;
/// - CtrlStp_RteAccess_ReadHbCmd_Param1.eSigQty = SIG_INVALID;
/// - CtrlStp_RteAccess_ReadHbCmd_Param2 = 0u;
/// - Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
/// - Expectations:
///   Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u
///   CtrlStp_RteAccess_ReadHbCmd_RetValue, 0u, =
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_INVALID;
  CtrlStp_RteAccess_ReadHbCmd_Param1.eSigQty = SIG_INVALID;
  CtrlStp_RteAccess_ReadHbCmd_Param2 = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadHbCmd_RetValue = CtrlStp_RteAccess_ReadHbCmd();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadHbCmd_RetValue, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadHbCmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  reads HB - high beam command
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadHbCmd(void)
{
  Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadHbCmd_TestCase_3();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads GFHB - Glare free high beam command 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// \input  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
/// \input  CtrlStp_RteAccess_ReadGfhbCmd_Param1.eGfhb_Cmd = 1u;
/// \input  CtrlStp_RteAccess_ReadGfhbCmd_Param2 = 1u;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_Afs_Signals_HitCount, 1u
/// \output  CtrlStp_RteAccess_ReadGfhbCmd_Param2, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
  CtrlStp_RteAccess_ReadGfhbCmd_Param1.eGfhb_Cmd = 1u;
  CtrlStp_RteAccess_ReadGfhbCmd_Param2 = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadGfhbCmd();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadGfhbCmd_Param2, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads GFHB - Glare free high beam command  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_E2E_TIMEOUT;
/// \input CtrlStp_RteAccess_ReadGfhbCmd_Param1.eGfhb_Cmd = 0u;
/// \input CtrlStp_RteAccess_ReadGfhbCmd_Param2 = 0u;
/// \input Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_Afs_Signals_HitCount, 1u
/// \output CtrlStp_RteAccess_ReadGfhbCmd_Param2, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_E2E_TIMEOUT;
  CtrlStp_RteAccess_ReadGfhbCmd_Param1.eGfhb_Cmd = 0u;
  CtrlStp_RteAccess_ReadGfhbCmd_Param2 = 0u;
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadGfhbCmd();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadGfhbCmd_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads GFHB - Glare free high beam command  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_INVALID;
/// \input CtrlStp_RteAccess_ReadGfhbCmd_Param1.eSigQty = SIG_INVALID;
/// \input Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_Afs_Signals_HitCount, 1u, 
/// \output  CtrlStp_RteAccess_ReadGfhbCmd_RetValue, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_INVALID;
  CtrlStp_RteAccess_ReadGfhbCmd_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadGfhbCmd_RetValue = CtrlStp_RteAccess_ReadGfhbCmd();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadGfhbCmd_RetValue, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadGfhbCmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads GFHB - Glare free high beam command 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadGfhbCmd(void)
{
  Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadGfhbCmd_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description: check that the function reads AFS mode
///        - 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// - 	Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
/// - 	Rte_Read_DiagControl_AfsState_Param1.boDiagRequestAcksStatus = eCtrlAFS_AfsOff;
/// - 	tsRte_AfsDiagControl CtrlStp_RteAccess_ReadAFSMode_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// - 	CtrlStp_RteAccess_ReadAFSMode_Param1.eAfs_Mode = 0u;
/// - 	Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = FALSE;
/// - 	CtrlStp_RteAccess_ReadAFSMode_Param3.eDiagRequestAfsState = 1u;
/// - 	Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState = 1u;
/// - Expectations:
///     Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
///     Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState, 1u,
///     CtrlStp_RteAccess_ReadAFSMode_Param2, 0u, == );
//-------------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestAcksStatus = eCtrlAFS_AfsOff;
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadAFSMode_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  CtrlStp_RteAccess_ReadAFSMode_Param1.eAfs_Mode = 0u;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = FALSE;
  CtrlStp_RteAccess_ReadAFSMode_Param3.eDiagRequestAfsState = 1u;
  Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAFSMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAFSMode_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description: check that the function reads AFS mode
///        - 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// - 	Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// - 	Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_TIMEOUT;
/// - 	Rte_Read_DiagControl_AfsState_Param1.boDiagRequestAcksStatus = eCtrlAFS_AfsOff;
/// - 	tsRte_AfsDiagControl CtrlStp_RteAccess_ReadAFSMode_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// - 	CtrlStp_RteAccess_ReadAFSMode_Param1.eAfs_Mode = 1u;
/// - 	CtrlStp_RteAccess_ReadAFSMode_Param3.eDiagRequestAfsState = 1u;
/// - 	Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode = 1u;

/// - Expectations:
///    Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
///    Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState, 1u
///    CtrlStp_RteAccess_ReadAFSMode_Param2, 0u, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_TIMEOUT;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestAcksStatus = eCtrlAFS_AfsOff;
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadAFSMode_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  CtrlStp_RteAccess_ReadAFSMode_Param1.eAfs_Mode = 1u;
  CtrlStp_RteAccess_ReadAFSMode_Param3.eDiagRequestAfsState = 1u;
  Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAFSMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAFSMode_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: : check that the function reads AFS mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_E2E_CRCERR;
/// \input Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_Afs_Signals_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_E2E_CRCERR;
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAFSMode_RetVal = CtrlStp_RteAccess_ReadAFSMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: check that the function reads AFS mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
/// \input Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
/// \input Rte_Read_DiagControl_AfsState_Param1.boDiagRequestAcksStatus = eCtrlAFS_AfsOff;
/// \input tsRte_AfsDiagControl CtrlStp_RteAccess_ReadAFSMode_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
/// \input CtrlStp_RteAccess_ReadAFSMode_Param1.eAfs_Mode = 0u; //boDiagRequestStatus
/// \input Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = TRUE;
/// \input CtrlStp_RteAccess_ReadAFSMode_Param3.eDiagRequestAfsState = 1u;
/// \input Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState = 1u;
///
///   - Expectations:
///
/// \output Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
/// \output Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState, 1u
/// \output CtrlStp_RteAccess_ReadAFSMode_Param2, 0u, == );
///
//-----------------------------------------------------------------------------  
void Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_Afs_Signals_HitCount = 0u;
  Rte_Read_SysMon_Afs_Signals_Param1.eSigQty = SIG_VALID;
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestAcksStatus = eCtrlAFS_AfsOff;
  tsRte_AfsDiagControl CtrlStp_RteAccess_ReadAFSMode_Param3 = { eCtrlAFS_AfsOff, FALSE, FALSE };
  CtrlStp_RteAccess_ReadAFSMode_Param1.eAfs_Mode = 0u; //boDiagRequestStatus
  Rte_Read_DiagControl_AfsState_Param1.boDiagRequestStatus = TRUE;
  CtrlStp_RteAccess_ReadAFSMode_Param3.eDiagRequestAfsState = 1u;
  Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadAFSMode();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_DiagControl_AfsState_Param1.eDiagRequestAfsState, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadAFSMode_Param2, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadAFSMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: : check that the function reads AFS mode 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadAFSMode(void)
{
  Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadAFSMode_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingTgtPos_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that function reads target position 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
/// \input CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
/// \input CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
/// \input CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdPosLvl.unRCmdPosLvl = 1u;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, =
/// \output  CtrlStp_RteAccess_ReadLevellingTgtPos_Param1, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingTgtPos_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_VALID;
  CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
  CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
  CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdPosLvl.unRCmdPosLvl = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingTgtPos(&CtrlStp_RteAccess_ReadLevellingTgtPos_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadLevellingTgtPos_Param1, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingTgtPos_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that function reads target position  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
/// \input Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_UNAVAILABLE;
/// \input CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
/// \input CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
/// \input CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdPosLvl.unRCmdPosLvl = 1u;
///
///   - Expectations:
///
/// \output  Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, =
/// \output  CtrlStp_RteAccess_ReadLevellingTgtPos_Param1, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingTgtPos_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_LevellingTgtPos_HitCount = 0u;
  Rte_Read_SigPrep_LevellingTgtPos_Param1.eSigQty = SIG_UNAVAILABLE;
  CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdSignLvl = CtrlStp_eSigneConsigneSiteD_Negativ;
  CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdRefLvl = CtrlStp_eCmdRefSiteD_Referencing;
  CtrlStp_RteAccess_ReadLevellingTgtPos_Param2.eRCmdPosLvl.unRCmdPosLvl = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadLevellingTgtPos(&CtrlStp_RteAccess_ReadLevellingTgtPos_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_LevellingTgtPos_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadLevellingTgtPos_Param1, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadLevellingTgtPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function reads target position 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadLevellingTgtPos(void)
{
  Mt_CtrlStp_RteAccess_ReadLevellingTgtPos_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadLevellingTgtPos_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read Ecu mounting side from Rte
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
/// \input CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedLeft;
/// \input CtrlStp_RteAccess_Read_EcuSide_Param2 = eMountedLeft;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_Read_EcuSide_RetVal, eMountedLeft, == );
/// \output CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedLeft
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedLeft;
  CtrlStp_RteAccess_Read_EcuSide_Param2 = eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_RteAccess_Read_EcuSide(&CtrlStp_RteAccess_Read_EcuSide_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_RetVal, eMountedLeft, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedLeft, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read Ecu mounting side from Rte 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedRight;
/// \input CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedRight;
/// \input CtrlStp_RteAccess_Read_EcuSide_Param2 = eMountedRight;
///
///   - Expectations:
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_Read_EcuSide_RetVal, 0u, == );
/// \output  CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedRight
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedRight;
  CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedRight;
  CtrlStp_RteAccess_Read_EcuSide_Param2 = eMountedRight;
  //Step 3) Call FUT
  CtrlStp_RteAccess_Read_EcuSide(&CtrlStp_RteAccess_Read_EcuSide_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_RetVal, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedRight, == );
}  //CtrlStp_eMountedUndef
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function read Ecu mounting side from Rte 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedUndef;
/// \input CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedUndef;
/// \input CtrlStp_RteAccess_Read_EcuSide_Param2 = 255;
///
///   - Expectations:
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_Read_EcuSide_RetVal, 0u, == );
/// \output  CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedUndef,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = CtrlStp_eMountedUndef;
  CtrlStp_RteAccess_Read_EcuSide_Param1 = CtrlStp_eMountedUndef;
  CtrlStp_RteAccess_Read_EcuSide_Param2 = 255;
  //Step 3) Call FUT
  CtrlStp_RteAccess_Read_EcuSide(&CtrlStp_RteAccess_Read_EcuSide_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_RetVal, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_EcuSide_Param1, CtrlStp_eMountedUndef, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Read_EcuSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function read Ecu mounting side from Rte 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Read_EcuSide(void)
{
  Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_1();
  Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_2();
  Mt_CtrlStp_RteAccess_Read_EcuSide_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_MapParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function maps the coding parameter in order to acces the in CtrlStp
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
/// \input CtrlStp_RteAccess_MapParams_Param1.eCodingState = 2u;
/// \input CtrlStp_RteAccess_MapParams_Param1.psCodingParameters_Blocks = 2u;
///
///   - Expectations:
///
/// \output Rte_Read_CodM_CtrlStp_Para_HitCount, 1u, == );
/// \output Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_MapParams(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
  CtrlStp_RteAccess_MapParams_Param1.eCodingState = 2u;
  CtrlStp_RteAccess_MapParams_Param1.psCodingParameters_Blocks = 2u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_MapParams();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function maps the coding parameter in order to acces the in CtrlStp
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues_Param1 = 2u;
///
///   - Expectations:
///
/// \output Rte_Read_ppCddStpActual0_sStpActualValues_HitCount, 1u, == );
/// \output Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.nPosition, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_ppCddStpActual0_sStpActualValues_HitCount = 0u;
  CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues_Param1 = 2u;//->sLwrActual.nPosition
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues(&CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_ppCddStpActual0_sStpActualValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_ppCddStpActual0_sStpActualValues_Param1.sLwrActual.nPosition, 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function maps the coding parameter in order to acces the in CtrlStp
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1 = 0u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eRCmdSignLvl = 1u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eRCmdRefLvl = 1u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eRCmdPosLvl.unRCmdPosLvl = 1u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eSigQty = 1u;
///
///   - Expectations:
///
/// \output Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_TestCase_1(void)//------------------------------------------- if not  working
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1 = 0u;
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eRCmdSignLvl = 1u;
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eRCmdRefLvl = 1u;
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eRCmdPosLvl.unRCmdPosLvl = 1u;
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param2.eSigQty = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(&CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function maps the coding parameter in order to acces the in CtrlStp
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1 = 0u;
/// \input Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
///
///   - Expectations:
///
/// \output Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == )
/// \output Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_TestCase_2(void)//----------------
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1 = 0u;
  Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty = SIG_VALID;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(&CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_MasterCommand_Param1.eSigQty, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function maps the coding parameter in order to acces the in CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(void)
{
  Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
/// \input Rte_Write_DrvLedDiag_HitCount = 0u;
/// \input CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1 = FALSE;
/// \input CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_HitCount, 1u, == );
/// \output  Rte_Write_DrvLedDiag_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault, eDiagLvl_Ok
/// \output  Rte_Write_DrvLedDiag_Param1.eLevellingAdjustFault, eDiagLvl_Ok, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_DrvLedDiag_HitCount = 0u;
  CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1 = FALSE;
  CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_Write_DrvLedDiag_Port(CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault, eDiagLvl_Ok, == );
  AL_UNITTEST_CHECK(Rte_Write_DrvLedDiag_Param1.eLevellingAdjustFault, eDiagLvl_Ok, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of drvled diag port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_DrvLedDiag_HitCount = 0u;
/// \input Rte_Write_DrvLedDiag_HitCount = 0u;
/// \input CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1 = TRUE;
/// \input CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault = 1u;
///
///   - Expectations:
///
/// \output  Rte_Read_DrvLedDiag_HitCount, 1u, == );
/// \output  Rte_Write_DrvLedDiag_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault, eDiagLvl_Nok
/// \output  Rte_Write_DrvLedDiag_Param1.eLevellingAdjustFault, eDiagLvl_Nok, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_DrvLedDiag_HitCount = 0u;
  Rte_Write_DrvLedDiag_HitCount = 0u;
  CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1 = TRUE;
  CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault = 1u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_Write_DrvLedDiag_Port(CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_DrvLedDiag_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Write_DrvLedDiag_Port_Param2.eLevellingAdjustFault, eDiagLvl_Nok, == );
  AL_UNITTEST_CHECK(Rte_Write_DrvLedDiag_Param1.eLevellingAdjustFault, eDiagLvl_Nok, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads The state of drvled diag port
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port(void)
{
  Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port_TestCase_1();
  Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port_TestCase_2();
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the state of stepper master command
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param1 = 0u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2.eRCmdSignLvl = 0u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2.eRCmdRefLvl = 0u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2.eRCmdPosLvl.unRCmdPosLvl = 0u;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
/// \output Rte_Write_CtrlStp_MasterCommand_Param1.eRCmdSignLvl, 0u, == );
/// \output Rte_Write_CtrlStp_MasterCommand_Param1.eRCmdRefLvl, 0u, == );
/// \output Rte_Write_CtrlStp_MasterCommand_Param1.eRCmdPosLvl.unRCmdPosLvl, 13u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlStp_MasterCommand_HitCount = 0u;
  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param1 = 0u;
  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2.eRCmdSignLvl = 0u;
  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2.eRCmdRefLvl = 0u;
  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port_Param2.eRCmdPosLvl.unRCmdPosLvl = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port(&CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_Param1.eRCmdSignLvl, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_Param1.eRCmdRefLvl, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_MasterCommand_Param1.eRCmdPosLvl.unRCmdPosLvl, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads slave stepper diagnostic status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1 = 0u;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == )
/// \output Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eSigQty, 0u
///
//----------------------------------------------------------------------------- 
void Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_TestCase_1(void)//--------------------------------not working
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1 = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(&CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eSigQty, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads slave stepper diagnostic status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1 = 1u;
/// \input Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eSigQty, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1 = 1u;
  Rte_Read_CtrlStp_SlaveDiagStatus_Param1.eSigQty = SIG_VALID;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(&CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eSigQty, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads slave stepper diagnostic status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(void)
{
  Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes slave stepper diagnostic status 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param1 = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlElecR = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlTemperatureR = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlSteplossR = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlRefStateR = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlVoltR = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eSigQty = 0u;
/// \input Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlElecR, 0u, == );
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlTemperatureR, 0u
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlSteplossR, 13u, 
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlRefStateR, 0u, =
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlVoltR, 0u, == );
/// \output  Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eSigQty, 0u, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param1 = 0u;
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlElecR = 0u;
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlTemperatureR = 0u;
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlSteplossR = 0u;
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlRefStateR = 0u;
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eLvlVoltR = 0u;
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param2.eSigQty = 0u;
  Rte_Write_CtrlStp_SlaveDiagStatus_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port(&CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlElecR, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlTemperatureR, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlSteplossR, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlRefStateR, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eLvlVoltR, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveDiagStatus_Param1.eSigQty, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Check that the function writes slave stepper diagnostic status 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
/// \input CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param2.eSigQty = SIG_VALID;
/// \input Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
///
///   - Expectations:
///
/// \output  Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == )
/// \output  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param2.eSigQty = SIG_VALID;
  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_VALID;
  //Step 3) Call FUT
  CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(&CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes slave stepper diagnostic status  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
/// \input Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_SNA;
/// \input CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param2.eSigQty = SIG_SNA;
///
///   - Expectations:
///
/// \output  Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == )
/// \output  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_SlaveFeedback_HitCount = 0u;
  Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty = SIG_SNA;
  CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param2.eSigQty = SIG_SNA;
  //Step 3) Call FUT
  CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(&CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_SlaveFeedback_Param1.eSigQty, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function writes slave stepper diagnostic status 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(void)
{
  Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_TestCase_1();
  Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function writes slave stepper feedback port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param1 = 1u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2.eRPosSignLvl = 0u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2.eSigQty = 0u;
/// \input CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2.ePositionSiteD.unRPosLvl = 0u;
/// \input Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
///
///   - Expectations:
///
/// \output Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
/// \output Rte_Write_CtrlStp_SlaveFeedback_Param1.eRPosSignLvl, 1u, == );
/// \output Rte_Write_CtrlStp_SlaveFeedback_Param1.eSigQty, 1u, == );
/// \output Rte_Write_CtrlStp_SlaveFeedback_Param1.ePositionSiteD.unRPosLvl, 0u
/// \output CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param1, 1u, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param1 = 1u;
  CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2.eRPosSignLvl = 0u;
  CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2.eSigQty = 0u;
  CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param2.ePositionSiteD.unRPosLvl = 0u;
  Rte_Write_CtrlStp_SlaveFeedback_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port(&CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_Param1.eRPosSignLvl, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_Param1.eSigQty, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlStp_SlaveFeedback_Param1.ePositionSiteD.unRPosLvl, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port_Param1, 1u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of vehicle configuration
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues_Param1 = 1u;
/// \input Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
/// \output  Rte_Write_ppCtrlStpTarget0_StpTargetValues_Param1.sLwrTarget.boStop, 0u
/// \output  CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues_Param1, 1u, == 
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues_Param1 = 1u;
  Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(&CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppCtrlStpTarget0_StpTargetValues_Param1.sLwrTarget.boStop, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues_Param1, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_Read_350Lost_Status
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function  get Frame 350 lost status via RTE 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_RteAccess_Read_350Lost_Status_Param1 = 1u;
/// \input CtrlStp_RteAccess_Read_350Lost_Status_Param2 = 1u;
/// \input Rte_Read_DEM_350Lost_NotifyStatus_Param1 = 1u;
/// \input Rte_Read_DEM_350Lost_NotifyStatus_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u, 
/// \output  CtrlStp_RteAccess_Read_350Lost_Status_Param2, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_Read_350Lost_Status(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_RteAccess_Read_350Lost_Status_Param1 = 1u;
  CtrlStp_RteAccess_Read_350Lost_Status_Param2 = 1u;
  Rte_Read_DEM_350Lost_NotifyStatus_Param1 = 1u;
  Rte_Read_DEM_350Lost_NotifyStatus_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_Read_350Lost_Status(&CtrlStp_RteAccess_Read_350Lost_Status_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_DEM_350Lost_NotifyStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_Read_350Lost_Status_Param2, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_WriteStpRoutineAck
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
/// \input Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1u;
/// \input tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
/// \input CtrlStp_RteAccess_WriteStpRoutineAck_HitCount = 0u;
/// \input CtrlStp_RteAccess_WriteStpRoutineAck_Param1 = 1u;
/// \input Rte_Read_Stp_RoutineControl_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
/// \output  Rte_Write_Stp_RoutineControl_Param1.boRequestAckStatus, CtrlStp_RteAccess_WriteStpRoutineAck_Param1
/// \output  Rte_Write_Stp_RoutineControl_Param1.boRequestStatus, FALSE, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_WriteStpRoutineAck(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_Stp_RoutineControl_Param1.boRequestAckStatus = 1u;
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };
  CtrlStp_RteAccess_WriteStpRoutineAck_HitCount = 0u;
  CtrlStp_RteAccess_WriteStpRoutineAck_Param1 = 1u;
  Rte_Read_Stp_RoutineControl_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_WriteStpRoutineAck(CtrlStp_RteAccess_WriteStpRoutineAck_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Stp_RoutineControl_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Stp_RoutineControl_Param1.boRequestAckStatus, CtrlStp_RteAccess_WriteStpRoutineAck_Param1, == );
  AL_UNITTEST_CHECK(Rte_Write_Stp_RoutineControl_Param1.boRequestStatus, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the state machine for Stepper Motor, 
///                       calls state function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_LifePhases_Param1.eSigQty = SIG_TIMEOUT;
/// \input Rte_Read_SysMon_LifePhases_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2 = FALSE;
/// \input CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1.eSigQty = SIG_TIMEOUT;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2, 0
///
//-----------------------------------------------------------------------------

void Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_Param1.eSigQty = SIG_TIMEOUT;
  Rte_Read_SysMon_LifePhases_HitCount = 0u;
  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2 = FALSE;
  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1.eSigQty = SIG_TIMEOUT;
  //Step 3) Call FUT
  //receive bb messages
  //CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality(&CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1.eSigQty);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the state machine for Stepper Motor, 
///                       calls state function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_SysMon_LifePhases_Param1.eSigQty = 1u;
/// \input Rte_Read_SysMon_LifePhases_HitCount = 0u;
/// \input CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2 = FALSE;
/// \input CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1.eSigQty = 1u;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_Param1.eSigQty = 1u;
  Rte_Read_SysMon_LifePhases_HitCount = 0u;
  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2 = FALSE;
  CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1.eSigQty = 1u;// SIG_SNA;
  //Step 3) Call FUT
  //receive bb messages
  //CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality(&CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_Param2, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality(void)
{
  Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadSysMon_LifePhasesQuality_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of the pitch sensors
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE;
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_Pitch_PlausState_Param1 = eNO_FAILURE;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSensorStatus(&CtrlStp_RteAccess_ReadSensorStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_NO_FAILURE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of the pitch sensors
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
/// \input Rte_Read_Pitch_PlausState_Param1 = eSENSOR_FAILURE;
/// \input CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_SENSOR_FAILURE;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_SENSOR_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
  Rte_Read_Pitch_PlausState_Param1 = eSENSOR_FAILURE;
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_SENSOR_FAILURE;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSensorStatus(&CtrlStp_RteAccess_ReadSensorStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_SENSOR_FAILURE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of the pitch sensors 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
/// \input Rte_Read_Pitch_PlausState_Param1 = eFROZEN_FAILURE;
/// \input CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_FROZEN_FAILURE;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_FROZEN_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
  Rte_Read_Pitch_PlausState_Param1 = eFROZEN_FAILURE;
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_FROZEN_FAILURE;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSensorStatus(&CtrlStp_RteAccess_ReadSensorStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_FROZEN_FAILURE, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of the pitch sensors
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
/// \input Rte_Read_Pitch_PlausState_Param1 = eSTORED_FAILURE;
/// \input CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_STORED_FAILURE;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_STORED_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
  Rte_Read_Pitch_PlausState_Param1 = eSTORED_FAILURE;
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = CtrlStp_eHLS_STORED_FAILURE;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSensorStatus(&CtrlStp_RteAccess_ReadSensorStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, CtrlStp_eHLS_STORED_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads The state of the pitch sensors
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
/// \input Rte_Read_Pitch_PlausState_Param1 = 255u;
/// \input CtrlStp_RteAccess_ReadSensorStatus_Param1 = 10u;
/// \input Rte_Read_Pitch_PlausState_HitCount = 0u;
///
///   - Expectations:
///
/// \output  Rte_Read_Pitch_PlausState_HitCount, 1u, == );
/// \output  CtrlStp_RteAccess_ReadSensorStatus_Param1, 10u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = 0;
  Rte_Read_Pitch_PlausState_Param1 = 255u;
  CtrlStp_RteAccess_ReadSensorStatus_Param1 = 10u;
  Rte_Read_Pitch_PlausState_HitCount = 0u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadSensorStatus(&CtrlStp_RteAccess_ReadSensorStatus_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlStp_RteAccess_ReadSensorStatus_Param1, 10u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadSensorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads The state of the pitch sensors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadSensorStatus(void)
{
  Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_4();
  Mt_CtrlStp_RteAccess_ReadSensorStatus_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads actual status stepper 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss = eNoStepLoss;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eNoThermalWarning;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eNoElectricalDefect;
///
///   - Expectations:
///
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_NoWarning
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_NoDefect, == )
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss = eNoStepLoss;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eNoThermalWarning;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eNoElectricalDefect;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_NoWarning, == );
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_NoDefect, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads actual status stepper 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss = eStepLossRisk;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eColdTemperature;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eOpenCircuitDefect;
///
///   - Expectations:
///
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_ColdTemperature
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_OpenCircuit, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss = eStepLossRisk;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eColdTemperature;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eOpenCircuitDefect;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_ColdTemperature, == );
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_OpenCircuit, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads actual status stepper
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss = 5u;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eHighTemeratureWarning;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eShortCircuitDefect;
///
///   - Expectations:
///
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureWarning
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_ShortCircuit, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss = 5u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eHighTemeratureWarning;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eShortCircuitDefect;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureWarning, == );
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_ShortCircuit, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads actual status stepper 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eHighTemperatureSD;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eReservedElectrical;
///
///   - Expectations:
///
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureShutdown
/// \output  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_Reserved, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = eHighTemperatureSD;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = eReservedElectrical;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, CtrlStp_eLvlTemperatureR_HighTemperatureShutdown, == );
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, CtrlStp_eLvlElecR_Reserved, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads actual status stepper 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = 5u;
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = 5u;
///
///   - Expectations:
///
/// \output *CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, 5u,
///         *CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, 5u, =
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState = 5u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = 5u;
  //Step 3) Call FUT
  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(&CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1);
  //Step 4) Check expected output value 
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpElectricDefect, 5u, == );
  //AL_UNITTEST_CHECK(*CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_Param1.eStatStpThermalState, 5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads actual status stepper
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(void)
{
  Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_1();
  Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_2();
  Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_3();
  Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_4();
  Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveRefRequest_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets ref request for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetSlaveRefRequest_Param1 = 1u;
/// \input CtrlStp_ReturnSide_RetVal = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output CtrlStp_boSlaveRefRequest, 0u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSlaveRefRequest_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetSlaveRefRequest_Param1 = 1u;
  CtrlStp_ReturnSide_RetVal = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SetSlaveRefRequest(CtrlStp_SetSlaveRefRequest_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveRefRequest, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveRefRequest_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets ref request for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetSlaveRefRequest_Param1 = 0u;
/// \input CtrlStp_ReturnSide_RetVal = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output  CtrlStp_boSlaveRefRequest, 0u,
///
//-----------------------------------------------------------------------------

void Mt_CtrlStp_SetSlaveRefRequest_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetSlaveRefRequest_Param1 = 0u;
  CtrlStp_ReturnSide_RetVal = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_SetSlaveRefRequest(CtrlStp_SetSlaveRefRequest_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveRefRequest, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveRefRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function sets ref request for slave
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSlaveRefRequest(void)
{
  Mt_CtrlStp_SetSlaveRefRequest_TestCase1();
  Mt_CtrlStp_SetSlaveRefRequest_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetRefRequest_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets ref request only if stepper is in master mode 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetRefRequest_Param1 = 1u;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_boRefRequest, 1u,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetRefRequest_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetRefRequest_Param1 = 1u;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SetRefRequest(CtrlStp_SetRefRequest_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boRefRequest, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetRefRequest_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets ref request only if stepper is in master mode  
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output  CtrlStp_boRefRequest, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetRefRequest_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_SetRefRequest(CtrlStp_SetRefRequest_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boRefRequest, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetRefRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function sets ref request only if stepper is in master mode 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetRefRequest(void)
{
  Mt_CtrlStp_SetRefRequest_TestCase1();
  Mt_CtrlStp_SetRefRequest_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_EntryOff
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets state Disabled for entry function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Status.ucLWRState = 0u;
/// \input CtrlStp_Status.ucLWRPosition = 0u;
/// \input CtrlStp_Status.ucLWRSpeed = 0u;
///
///   - Expectations:
///
/// \output CtrlStp_Status.ucLWRState, eStpSpnStatus_NoInit
/// \output CtrlStp_Status.ucLWRPosition, CTRLSTP_SignalSna
/// \output CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalSna, =
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_EntryOff(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Status.ucLWRState = 0u;
  CtrlStp_Status.ucLWRPosition = 0u;
  CtrlStp_Status.ucLWRSpeed = 0u;
  //Step 3) Call FUT
  CtrlStp_EntryOff();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRState, eStpSpnStatus_NoInit, == );
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRPosition, CTRLSTP_SignalSna, == );
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalSna, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_EntryRefDn
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets state RefDn for entry function
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Status.ucLWRState = 0u;
/// \input CtrlStp_Status.ucLWRPosition = 0u
/// \input CtrlStp_Status.ucLWRSpeed = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_Status.ucLWRState, eStpSpnStatus_Init, 
/// \output  CtrlStp_Status.ucLWRPosition, CTRLSTP_SignalErr
/// \output  CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalErr, =
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_EntryRefDn(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Status.ucLWRState = 0u;
  CtrlStp_Status.ucLWRPosition = 0u;
  CtrlStp_Status.ucLWRSpeed = 0u;
  //Step 3) Call FUT
  CtrlStp_EntryRefDn();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRState, eStpSpnStatus_Init, == );
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRPosition, CTRLSTP_SignalErr, == );
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalErr, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStepLossRecovery_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for recovery of step loss 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_boStepLossCurrentSide, TRUE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStepLossRecovery_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadStepLossRecovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStepLossCurrentSide, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStepLossRecovery_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for recovery of step loss 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_boStepLossRightSide, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStepLossRecovery_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReadStepLossRecovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStepLossRightSide, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStepLossRecovery_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for recovery of step loss 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = 0u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_boStepLossCurrentSide, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStepLossRecovery_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  //Step 3) Call FUT
  CtrlStp_ReadStepLossRecovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStepLossCurrentSide, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStepLossRecovery_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for recovery of step loss 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boStepLossCurrentSide = TRUE;
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = 0u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_boStepLossCurrentSide, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStepLossRecovery_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boStepLossCurrentSide = TRUE;
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadStepLossRecovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStepLossCurrentSide, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStepLossRecovery_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check for recovery of step loss 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = 0u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output CtrlStp_boStepLossCurrentSide, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStepLossRecovery_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sLevellingDiagStatusFromRightToLeft.eLvlSteplossR = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_ReadStepLossRecovery();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boStepLossCurrentSide, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReadStepLossRecovery
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check for recovery of step loss
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReadStepLossRecovery(void)
{
  Mt_CtrlStp_ReadStepLossRecovery_TestCase_1();
  Mt_CtrlStp_ReadStepLossRecovery_TestCase_2();
  Mt_CtrlStp_ReadStepLossRecovery_TestCase_3();
  Mt_CtrlStp_ReadStepLossRecovery_TestCase_4();
  Mt_CtrlStp_ReadStepLossRecovery_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteValidationFrames_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write information needed for validation frames 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u;
/// \input CtrlStp_DiagStatus.eStatStpElectricDefect = 1u;
/// \input CtrlStp_DiagStatus.eStatStpThermalState = 1u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = TRUE;
///
///   - Expectations:
///
/// \output Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteValidationFrames_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u;
  CtrlStp_DiagStatus.eStatStpElectricDefect = 1u;
  CtrlStp_DiagStatus.eStatStpThermalState = 1u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = TRUE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = TRUE;
  //Step 3) Call FUT
  CtrlStp_WriteValidationFrames();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteValidationFrames_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function write information needed for validation frames 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u;
/// \input CtrlStp_DiagStatus.eStatStpElectricDefect = 0u;
/// \input CtrlStp_DiagStatus.eStatStpThermalState = 0u;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
///
///   - Expectations:
///
/// \output Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteValidationFrames_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u;
  CtrlStp_DiagStatus.eStatStpElectricDefect = 0u;
  CtrlStp_DiagStatus.eStatStpThermalState = 0u;
  CtrlStp_ActAll.sLwrActual.sStatusError.boStepLoss = FALSE;
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsMoving = FALSE;
  //Step 3) Call FUT
  CtrlStp_WriteValidationFrames();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_WriteValidationFrames
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function write information needed for validation frames 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_WriteValidationFrames(void)
{
  Mt_CtrlStp_WriteValidationFrames_TestCase_1();
  Mt_CtrlStp_WriteValidationFrames_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DoNorm_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Do function of state Norm 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 1;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
///
///   - Expectations:
///
/// \output CtrlStp_Status.ucLWRPosition, 240u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DoNorm_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 1;
  CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  //Step 3) Call FUT
  CtrlStp_DoNorm();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRPosition, 240u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DoNorm_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:Do function of state Norm 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 1;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 11000;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 1;
/// \input CtrlStp_unTgtTmin = 260;
///
///   - Expectations:
///
/// \output  CtrlStp_Status.ucLWRSpeed, 250u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DoNorm_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 1;
  CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 11000;
  CtrlStp_ActAll.sLwrActual.nPosition = 1;
  CtrlStp_unTgtTmin = 260;
  //Step 3) Call FUT
  CtrlStp_DoNorm();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRSpeed, 250u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DoNorm
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Do function of state Norm
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DoNorm(void)
{
  Mt_CtrlStp_DoNorm_TestCase_1();
  Mt_CtrlStp_DoNorm_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the behavior in case of state Err for Slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = TRUE;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = TRUE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check the behavior in case of state Err for Slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.boEntry = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_State.boEntry = FALSE;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateFail_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateFail_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check the behavior in case of state Err for Slave
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateFail_Slave(void)
{
  Mt_CtrlStp_StateMachine_StateFail_Slave_TestCase_1();
  Mt_CtrlStp_StateMachine_StateFail_Slave_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eFreeze;
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eFreeze;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior_Slave(CtrlStp_HandleFailStateBehavior_Slave_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eSafety;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eSafety;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior_Slave(CtrlStp_HandleFailStateBehavior_Slave_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eFreeze_IgnitionNeeded;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eFreeze_IgnitionNeeded;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior_Slave(CtrlStp_HandleFailStateBehavior_Slave_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eSafety_IgnitionNeeded;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eSafety_IgnitionNeeded;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior_Slave(CtrlStp_HandleFailStateBehavior_Slave_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eSafety_IgnitionNeeded;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 10000;
///
///   - Expectations:
///
/// \output CtrlStp_State.boEntry, FALSE,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Slave_Param1 = CtrlStp_eSafety_IgnitionNeeded;
  CtrlStp_ActAll.sLwrActual.nPosition = 10000;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior_Slave(CtrlStp_HandleFailStateBehavior_Slave_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Slave_Param1 = 25u;
///
///   - Expectations:
///
/// \output  CtrlStp_State.boEntry, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Slave_Param1 = 25u;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior_Slave(CtrlStp_HandleFailStateBehavior_Slave_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function handle fail state behavior for slave
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_Slave(void)
{
  Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_1();
  Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_2();
  Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_3();
  Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_4();
  Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_5();
  Mt_CtrlStp_HandleFailStateBehavior_Slave_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = FALSE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = FALSE;
  CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
  //Step 3) Call FUT
  CtrlStp_HandleFailState_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = TRUE;
  //Step 3) Call FUT
  CtrlStp_HandleFailState_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 4, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_Slave_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_Slave_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_Slave_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_Slave_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_Slave_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for slave 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_Slave_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boSlaveLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function handle fail state behavior for slave
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_Slave(void)
{
  Mt_CtrlStp_HandleFailState_Slave_TestCase_1();
  Mt_CtrlStp_HandleFailState_Slave_TestCase_2();
  Mt_CtrlStp_HandleFailState_Slave_TestCase_3();
  Mt_CtrlStp_HandleFailState_Slave_TestCase_4();
  Mt_CtrlStp_HandleFailState_Slave_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = FALSE;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boLvlAdjFuncFault = TRUE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boLvlAdjFuncFault = TRUE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 4, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 2
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 2
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eTransition_Failure;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 2u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = TRUE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = TRUE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
  //Step 3) Call FUT
  CtrlStp_HandleFailState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 4, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function handle fail state behavior
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailState(void)
{
  Mt_CtrlStp_HandleFailState_TestCase_1();
  Mt_CtrlStp_HandleFailState_TestCase_2();
  Mt_CtrlStp_HandleFailState_TestCase_3();
  Mt_CtrlStp_HandleFailState_TestCase_4();
  Mt_CtrlStp_HandleFailState_TestCase_5();
  Mt_CtrlStp_HandleFailState_TestCase_6();
  Mt_CtrlStp_HandleFailState_TestCase_7();
  Mt_CtrlStp_HandleFailState_TestCase_8();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleDiagLvl_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle the DiagLvl delay
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleDiagLvl_Param1 = FALSE;
/// \input CtrlStp_StartDiagLvlTimer = TRUE;
/// \input ulDelayTimer = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal = 1000u;
///
///   - Expectations:
///
/// \output  ulDelayTimer, 1000
/// \output  CtrlStp_StartDiagLvlTimer, FALSE
/// \output  CtrlStp_boSubModeError, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleDiagLvl_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleDiagLvl_Param1 = FALSE;
  CtrlStp_StartDiagLvlTimer = TRUE;
  ulDelayTimer = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  //Step 3) Call FUT
  CtrlStp_HandleDiagLvl(CtrlStp_HandleDiagLvl_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulDelayTimer, 1000, == );
  AL_UNITTEST_CHECK(CtrlStp_StartDiagLvlTimer, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_boSubModeError, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleDiagLvl_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle the DiagLvl delay
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleDiagLvl_Param1 = FALSE;
/// \input CtrlStp_StartDiagLvlTimer = FALSE;
/// \input ulDelayTimer = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal = 1000u;
///
///   - Expectations:
///
/// \output  ulDelayTimer, 0u
/// \output  CtrlStp_StartDiagLvlTimer, FALSE
/// \output  CtrlStp_boSubModeError, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleDiagLvl_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleDiagLvl_Param1 = FALSE;
  CtrlStp_StartDiagLvlTimer = FALSE;
  ulDelayTimer = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  //Step 3) Call FUT
  CtrlStp_HandleDiagLvl(CtrlStp_HandleDiagLvl_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulDelayTimer, 0u, == );
  AL_UNITTEST_CHECK(CtrlStp_StartDiagLvlTimer, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_boSubModeError, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleDiagLvl_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle the DiagLvl delay
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_HandleDiagLvl_Param1 = FALSE;
/// \input  CtrlStp_StartDiagLvlTimer = FALSE;
/// \input  ulDelayTimer = 2000u;
/// \input  LPTMR0_GetTimeElapsed_RetVal = 1000u;
///
///   - Expectations:
///
/// \output  ulDelayTimer, 2000u
/// \output  CtrlStp_StartDiagLvlTimer, FALSE
/// \output  CtrlStp_boSubModeError, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleDiagLvl_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleDiagLvl_Param1 = FALSE;
  CtrlStp_StartDiagLvlTimer = FALSE;
  ulDelayTimer = 2000u;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  //Step 3) Call FUT
  CtrlStp_HandleDiagLvl(CtrlStp_HandleDiagLvl_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulDelayTimer, 2000u, == );
  AL_UNITTEST_CHECK(CtrlStp_StartDiagLvlTimer, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_boSubModeError, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleDiagLvl_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle the DiagLvl delay
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleDiagLvl_Param1 = TRUE;
/// \input CtrlStp_StartDiagLvlTimer = FALSE;
/// \input ulDelayTimer = 2000u;
/// \input LPTMR0_GetTimeElapsed_RetVal = 1000u
///
///   - Expectations:
///
/// \output  ulDelayTimer, 2000u
/// \output  CtrlStp_StartDiagLvlTimer, FALSE
/// \output  CtrlStp_boSubModeError, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleDiagLvl_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleDiagLvl_Param1 = TRUE;
  CtrlStp_StartDiagLvlTimer = FALSE;
  ulDelayTimer = 2000u;
  LPTMR0_GetTimeElapsed_RetVal = 1000u;
  //Step 3) Call FUT
  CtrlStp_HandleDiagLvl(CtrlStp_HandleDiagLvl_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(ulDelayTimer, 2000u, == );
  AL_UNITTEST_CHECK(CtrlStp_StartDiagLvlTimer, FALSE, == );
  AL_UNITTEST_CHECK(CtrlStp_boSubModeError, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function handle the DiagLvl delay
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleDiagLvl(void)
{
  Mt_CtrlStp_HandleDiagLvl_TestCase_1();
  Mt_CtrlStp_HandleDiagLvl_TestCase_2();
  Mt_CtrlStp_HandleDiagLvl_TestCase_3();
  Mt_CtrlStp_HandleDiagLvl_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eFreeze;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eFreeze;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0, 
/// \output  CtrlStp_boSlaveStop, 1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eFreeze;
  CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eFreeze;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eSafety;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4, =
/// \output  CtrlStp_boSlaveStop, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eSafety;
  CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 4, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eContinue;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eContinue;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 2, 
/// \output  CtrlStp_boSlaveStop, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eContinue;
  CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eContinue;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 2, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eSafety_IgnitionNeeded;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety_IgnitionNeeded;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4, =
/// \output  CtrlStp_boSlaveStop, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eSafety_IgnitionNeeded;
  CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety_IgnitionNeeded;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 4, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eSafety_IgnitionNeeded;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety_IgnitionNeeded;
/// \input CtrlStp_ActAll.sLwrActual.nPosition = 100000u;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 4, 
/// \output  CtrlStp_boSlaveStop, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eSafety_IgnitionNeeded;
  CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety_IgnitionNeeded;
  CtrlStp_ActAll.sLwrActual.nPosition = 100000u;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 4, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eFreeze_IgnitionNeeded;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety_IgnitionNeeded;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0, 
/// \output  CtrlStp_boSlaveStop, 0
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = CtrlStp_eFreeze_IgnitionNeeded;
  CtrlStp_HandleFailStateBehavior_Param2 = CtrlStp_eSafety_IgnitionNeeded;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function handle fail state behavior for Master and Slave control
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_HandleFailStateBehavior_Param1 = 8u;
/// \input CtrlStp_HandleFailStateBehavior_Param2 = 8u;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0, =
/// \output  CtrlStp_boSlaveStop, 0,
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_HandleFailStateBehavior_Param1 = 8u;
  CtrlStp_HandleFailStateBehavior_Param2 = 8u;
  //Step 3) Call FUT
  CtrlStp_HandleFailStateBehavior(CtrlStp_HandleFailStateBehavior_Param1, CtrlStp_HandleFailStateBehavior_Param2);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
  AL_UNITTEST_CHECK(CtrlStp_boSlaveStop, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_HandleFailStateBehavior
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function handle fail state behavior for Master and Slave control
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_HandleFailStateBehavior(void)
{
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_1();
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_2();
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_3();
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_4();
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_5();
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_6();
  Mt_CtrlStp_HandleFailStateBehavior_TestCase_7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_Slave_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function has a proper behavior in case of state Init for Slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
/// \input CtrlStp_CodingDataReady_Param1 = eMountedLeft;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported =1u;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_Slave_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  CtrlStp_CodingDataReady_Param1 = eMountedLeft;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported =1u;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateInit_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_Slave_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function has a proper behavior in case of state Init for Slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
/// \input CtrlStp_CodingDataReady_Param1 = eMountedLeft;
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 0u;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_Slave_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_CtrlStp_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
  CtrlStp_CodingDataReady_Param1 = eMountedLeft;
  CtrlStp_ActAll.sLwrActual.sStatusError.eStatSupported = 0u;
  //Step 3) Call FUT
  CtrlStp_StateMachine_StateInit_Slave();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StateMachine_StateInit_Slave
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if the function has a proper behavior in case of state Init for Slave
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StateMachine_StateInit_Slave(void)
{
  Mt_CtrlStp_StateMachine_StateInit_Slave_TestCase_1();
  Mt_CtrlStp_StateMachine_StateInit_Slave_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StMch_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the state machine for Stepper Motor, 
///                       calls state function and goes through each state transition check
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.eMain = CtrlStp_eState_Adj;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = TRUE;
/// \input CtrlStp_State.boEntry = FALSE;
///
///   - Expectations:
///
/// \output CtrlStp_State.eMain, CtrlStp_eState_Fail
/// \output CtrlStp_State.boEntry, TRUE, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StMch_TestCase1(void)
{

  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlStp_State.eMain = CtrlStp_eState_Adj;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eFrozen_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eFrozen_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_SENSOR_FAILURE;
  CtrlStp_boLvlAdjFuncFault = TRUE;
  CtrlStp_State.boEntry = FALSE;
  //Step 3) Call FUT
  CtrlStp_StMch();
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlStp_State.eMain, CtrlStp_eState_Fail, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StMch_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if in the state machine for Stepper Motor, 
///                       calls state function 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_State.eMain = CtrlStp_eState_Adj;
/// \input CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
/// \input CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
/// \input CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
/// \input CtrlStp_boLvlAdjFuncFault = FALSE;
/// \input CtrlStp_State.boEntry = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_State.eMain, CtrlStp_eState_Adj
/// \output  CtrlStp_State.boEntry, FALSE, == );
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StMch_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlStp_State.eMain = CtrlStp_eState_Adj;
  CtrlStp_eLvlAdjHeadlampFault_L = CtrlStp_eNo_Failure;
  CtrlStp_eLvlAdjHeadlampFault_R = CtrlStp_eNo_Failure;
  CtrlStp_eSensorError = CtrlStp_eHLS_NO_FAILURE;
  CtrlStp_boLvlAdjFuncFault = FALSE;
  CtrlStp_State.boEntry = FALSE;
  //Step 3) Call FUT
  CtrlStp_StMch();
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlStp_State.eMain, CtrlStp_eState_Adj, == );
  AL_UNITTEST_CHECK(CtrlStp_State.boEntry, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StMch
///
/// \Functional Safety: NA
///
/// \Test Case Description 
///    - Test subject:  Test that if state machine for stepper,
///                     calls state function and goes through each state transition check
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StMch(void)
{
  Mt_CtrlStp_StMch_TestCase1();
  Mt_CtrlStp_StMch_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSignalMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets CtrlStp mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SignalSrc = CtrlStp_SetSignalMode_Param1;
///
///   - Expectations:
///
/// \output  CtrlStp_SignalSrc, CtrlStp_SetSignalMode_Param1
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSignalMode(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SignalSrc = CtrlStp_SetSignalMode_Param1;
  //Step 3) Call FUT
  CtrlStp_SetSignalMode(CtrlStp_SetSignalMode_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_SignalSrc, CtrlStp_SetSignalMode_Param1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSubModeError_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets submode error only if stepper is in master mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetSubModeError_Param1 = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output  CtrlStp_boSubModeError, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSubModeError_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetSubModeError_Param1 = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_SetSubModeError(CtrlStp_SetSubModeError_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSubModeError, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSubModeError_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets submode error only if stepper is in master mode
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetSubModeError_Param1 = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_boSubModeError, TRUE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSubModeError_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetSubModeError_Param1 = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SetSubModeError(CtrlStp_SetSubModeError_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSubModeError, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSubModeError
///
/// \Functional Safety: NA
///
/// \Test Case Description 
///    - Test subject:  Test that if the function sets submode error only if stepper is in master mode

///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSubModeError(void)
{
  Mt_CtrlStp_SetSubModeError_TestCase_1();
  Mt_CtrlStp_SetSubModeError_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveSafetyPosition_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets safety position command for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetSlaveSafetyPosition_Param1 = FALSE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
///
///   - Expectations:
///
/// \output  CtrlStp_boSlaveSafetyPos, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSlaveSafetyPosition_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetSlaveSafetyPosition_Param1 = FALSE;
  CtrlStp_eMountingSide = CtrlStp_eMountedLeft;
  //Step 3) Call FUT
  CtrlStp_SetSlaveSafetyPosition(CtrlStp_SetSlaveSafetyPosition_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveSafetyPosition_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function sets safety position command for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_SetSlaveSafetyPosition_Param1 = TRUE;
/// \input CtrlStp_eMountingSide = CtrlStp_eMountedRight;
///
///   - Expectations:
///
/// \output  CtrlStp_boSlaveSafetyPos, FALSE
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSlaveSafetyPosition_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_SetSlaveSafetyPosition_Param1 = TRUE;
  CtrlStp_eMountingSide = CtrlStp_eMountedRight;
  //Step 3) Call FUT
  CtrlStp_SetSlaveSafetyPosition(CtrlStp_SetSlaveSafetyPosition_Param1);
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_boSlaveSafetyPos, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_SetSlaveSafetyPosition
///
/// \Functional Safety: NA
///
/// \Test Case Description 
///    - Test subject: Check that if the function sets safety position command for slave

///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_SetSlaveSafetyPosition(void)
{
  Mt_CtrlStp_SetSlaveSafetyPosition_TestCase_1();
  Mt_CtrlStp_SetSlaveSafetyPosition_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturnValidationParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function return values for validation port
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_L = FALSE;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturnValidationParams_RetVal.boLvlAdjFunctionalFault_L,  0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturnValidationParams(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Core_sValidationParams.boLvlAdjFunctionalFault_L = FALSE;
  //Step 3) Call FUT
  CtrlStp_ReturnValidationParams_RetVal = CtrlStp_ReturnValidationParams();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturnValidationParams_RetVal.boLvlAdjFunctionalFault_L,  0u , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_StartRef
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the stepper has started reference run
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 1;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1;
/// \input CtrlStp_sHeadlampGeo.unAvacStp_UpperStpBlockRange = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_Angle2StpPos_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_StartRef(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_sHeadlampGeo.unAvacStp_Transmission_Factor = 1;
  CtrlStp_sHeadlampGeo.unAvacStp_LowerStpBlockRange = 1;
  CtrlStp_sHeadlampGeo.unAvacStp_UpperStpBlockRange = 1;
  //Step 3) Call FUT
  CtrlStp_StartRef();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Angle2StpPos_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_EntryInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the stepper is in Entry function of state Init
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Err;
/// \input CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalErr;
/// \input CtrlStp_Status.ucLWRSpeed = CTRLSTP_SignalErr;
///
///   - Expectations:
///
/// \output  CtrlStp_Status.ucLWRState, eStpSpnStatus_Sna, =
/// \output  CtrlStp_Status.ucLWRPosition, CTRLSTP_SignalSna
/// \output  CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalSna, =
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_EntryInit(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_Status.ucLWRState = (uint8)eStpSpnStatus_Err;
  CtrlStp_Status.ucLWRPosition = CTRLSTP_SignalErr;
  CtrlStp_Status.ucLWRSpeed = CTRLSTP_SignalErr;
  //Step 3) Call FUT
  CtrlStp_EntryInit();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRState, eStpSpnStatus_Sna, == );
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRPosition, CTRLSTP_SignalSna, == );
  AL_UNITTEST_CHECK(CtrlStp_Status.ucLWRSpeed, CTRLSTP_SignalSna, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondIsReady
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if CddStp accepts new command
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = 1;
///
///   - Expectations:
///
/// \output  CtrlStp_CondIsReady_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondIsReady(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsReady = 1;
  //Step 3) Call FUT
  CtrlStp_CondIsReady_RetVal = CtrlStp_CondIsReady();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondIsReady_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefDnCompl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if stepper is referenced
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_CondRefDnCompl_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefDnCompl(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boIsRef = 1u;
  //Step 3) Call FUT
  CtrlStp_CondRefDnCompl_RetVal = CtrlStp_CondRefDnCompl();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefDnCompl_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_CondRefInProgress
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check if stepper is referencing is in progress
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_CondRefInProgress_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_CondRefInProgress(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_ActAll.sLwrActual.sStatusError.boRefActive = 1u;
  //Step 3) Call FUT
  CtrlStp_CondRefInProgress_RetVal = CtrlStp_CondRefInProgress();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_CondRefInProgress_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RefRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value for refference request is returned
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boRefRequest = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_RefRequest_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RefRequest(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boRefRequest = 1u;
  //Step 3) Call FUT
  CtrlStp_RefRequest_RetVal = CtrlStp_RefRequest();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_RefRequest_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RetPowerTrainActive
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function returns the value for powertrain active 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boPowertrainActive = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_RetPowerTrainActive_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RetPowerTrainActive(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boPowertrainActive = 1u;
  //Step 3) Call FUT
  CtrlStp_RetPowerTrainActive_RetVal = CtrlStp_RetPowerTrainActive();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_RetPowerTrainActive_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturnboTrainingState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function return the value from operation requested from PWF, cont. movement or inscenation
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boTrainingState = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturnboTrainingState_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturnboTrainingState(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boTrainingState = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturnboTrainingState_RetVal = CtrlStp_ReturnboTrainingState();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturnboTrainingState_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturnboLvlAdjFuncFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function returns levelling adjust functional fault status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boLvlAdjFuncFault = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturnboLvlAdjFuncFault_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturnboLvlAdjFuncFault(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boLvlAdjFuncFault = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturnboLvlAdjFuncFault_RetVal = CtrlStp_ReturnboLvlAdjFuncFault();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturnboLvlAdjFuncFault_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturnboSlaveLvlAdjFuncFault
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function returns levelling adjust functional fault status for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boSlaveLvlAdjFuncFault = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturnboSlaveLvlAdjFuncFault_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturnboSlaveLvlAdjFuncFault(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boSlaveLvlAdjFuncFault = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturnboSlaveLvlAdjFuncFault_RetVal = CtrlStp_ReturnboSlaveLvlAdjFuncFault();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturnboSlaveLvlAdjFuncFault_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_RetVehIgnition
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function return ignition conditions fulfillment 
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_boConVehIgnition = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_RetVehIgnition_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_RetVehIgnition(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_boConVehIgnition = 1u;
  //Step 3) Call FUT
  CtrlStp_RetVehIgnition_RetVal = CtrlStp_RetVehIgnition();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_RetVehIgnition_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturnSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the value for ecu side is returned correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eMountingSide = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturnSide_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturnSide(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eMountingSide = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturnSide_RetVal = CtrlStp_ReturnSide();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturnSide_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturneLvlAdjHeadlampFault_L
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if tne function returns levelling adjust headlamp fault status
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eLvlAdjHeadlampFault_L = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturneLvlAdjHeadlampFault_L_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturneLvlAdjHeadlampFault_L(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_L = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturneLvlAdjHeadlampFault_L_RetVal = CtrlStp_ReturneLvlAdjHeadlampFault_L();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturneLvlAdjHeadlampFault_L_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturneLvlAdjHeadlampFault_R
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if the function returns levelling adjust headlamp fault status for slave
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input  CtrlStp_eLvlAdjHeadlampFault_R = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturneLvlAdjHeadlampFault_R_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturneLvlAdjHeadlampFault_R(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eLvlAdjHeadlampFault_R = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturneLvlAdjHeadlampFault_R_RetVal = CtrlStp_ReturneLvlAdjHeadlampFault_R();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturneLvlAdjHeadlampFault_R_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_ReturneSensorError
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if sensor error status is returned correctly
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input CtrlStp_eSensorError = 1u;
///
///   - Expectations:
///
/// \output  CtrlStp_ReturneSensorError_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_ReturneSensorError(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlStp_eSensorError = 1u;
  //Step 3) Call FUT
  CtrlStp_ReturneSensorError_RetVal = CtrlStp_ReturneSensorError();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_ReturneSensorError_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransition_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects change of electric veh state for STT state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_4_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransition_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransition_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ePreviousValue = CtrlStp_eEtatFee_4_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
  //Step 3) Call FUT
  CtrlStp_DetectElecTransition_RetVal = CtrlStp_DetectElecTransition();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectElecTransition_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransition_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects change of electric veh state for STT state
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransition_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransition_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ePreviousValue = CtrlStp_eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_3c;
  //Step 3) Call FUT
  CtrlStp_DetectElecTransition_RetVal = CtrlStp_DetectElecTransition();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectElecTransition_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransition
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if detects change of electric veh state for STT state
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransition(void)
{
  Mt_CtrlStp_DetectElecTransition_TestCase_1();
  Mt_CtrlStp_DetectElecTransition_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransitionSttToAdj_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects change of electric veh state from stt to adj
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransitionSttToAdj_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransitionSttToAdj_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ePreviousValue = CtrlStp_eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
  //Step 3) Call FUT
  CtrlStp_DetectElecTransitionSttToAdj_RetVal = CtrlStp_DetectElecTransitionSttToAdj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectElecTransitionSttToAdj_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransitionSttToAdj_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects change of electric veh state from stt to adj
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_1;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransitionSttToAdj_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransitionSttToAdj_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ePreviousValue = CtrlStp_eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_1;
  //Step 3) Call FUT
  CtrlStp_DetectElecTransitionSttToAdj_RetVal = CtrlStp_DetectElecTransitionSttToAdj();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectElecTransitionSttToAdj_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransitionSttToAdj
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if detects change of electric veh state from stt to adj
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransitionSttToAdj(void)
{
  Mt_CtrlStp_DetectElecTransitionSttToAdj_TestCase_1();
  Mt_CtrlStp_DetectElecTransitionSttToAdj_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransitionSttToRef_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects change of electric veh state from stt to ref
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransitionSttToRef_RetVal, 1u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransitionSttToRef_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ePreviousValue = CtrlStp_eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_4_1;
  //Step 3) Call FUT
  CtrlStp_DetectElecTransitionSttToRef_RetVal = CtrlStp_DetectElecTransitionSttToRef();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectElecTransitionSttToRef_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransitionSttToRef_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that if detects change of electric veh state from stt to ref
///
///        - Test Design Technique: ET(Exploratory Testing )
///
///   - Inputs:
///
/// \input ePreviousValue = CtrlStp_eEtatFee_1_1;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_1;
///
///   - Expectations:
///
/// \output  CtrlStp_DetectElecTransitionSttToAdj_RetVal, 0u
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransitionSttToRef_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ePreviousValue = CtrlStp_eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = CtrlStp_eEtatFee_1_1;
  //Step 3) Call FUT
  CtrlStp_DetectElecTransitionSttToRef_RetVal = CtrlStp_DetectElecTransitionSttToRef();
  //Step 4) Check expected output value 
  AL_UNITTEST_CHECK(CtrlStp_DetectElecTransitionSttToRef_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlStp_DetectElecTransitionSttToRef
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that if detects change of electric veh state from stt to ref
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlStp_DetectElecTransitionSttToRef(void)
{
  Mt_CtrlStp_DetectElecTransitionSttToRef_TestCase_1();
  Mt_CtrlStp_DetectElecTransitionSttToRef_TestCase_2();
}

//=============================================================================
// Test Cases
//=============================================================================
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  -
///
/// \return void      
//-----------------------------------------------------------------------------*/
void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus", Mt_CtrlStp_CtrlStp_ReadLvlAdjHeadlampFaultStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_Slave_Cycle20ms", Mt_CtrlStp_Slave_Cycle20ms);
  ALUnitTest_AddFunction("Mt_CtrlStp_Master_Cycle20ms", Mt_CtrlStp_Master_Cycle20ms);

  /*CtrlStp_RteAccess.h*/
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadLbBoostAllowed", Mt_CtrlStp_RteAccess_ReadLbBoostAllowed);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0", Mt_CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port", Mt_CtrlStp_RteAccess_WriteCtrlStp_Validation_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadSensorStatus", Mt_CtrlStp_RteAccess_ReadSensorStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_WriteStpRoutineAck", Mt_CtrlStp_RteAccess_WriteStpRoutineAck);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_Read_350Lost_Status", Mt_CtrlStp_RteAccess_Read_350Lost_Status);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues", Mt_CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port", Mt_CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port", Mt_CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port", Mt_CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port", Mt_CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port", Mt_CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port", Mt_CtrlStp_RteAccess_Write_DrvLedDiag_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port", Mt_CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues", Mt_CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_MapParams", Mt_CtrlStp_RteAccess_MapParams);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_Read_EcuSide", Mt_CtrlStp_RteAccess_Read_EcuSide);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadAFSMode", Mt_CtrlStp_RteAccess_ReadAFSMode);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadGfhbCmd", Mt_CtrlStp_RteAccess_ReadGfhbCmd);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadHbCmd", Mt_CtrlStp_RteAccess_ReadHbCmd);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadLevellingTgtPos", Mt_CtrlStp_RteAccess_ReadLevellingTgtPos);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadSpeed", Mt_CtrlStp_RteAccess_ReadSpeed);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadVehicleElectricState", Mt_CtrlStp_RteAccess_ReadVehicleElectricState);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadVESMainState", Mt_CtrlStp_RteAccess_ReadVESMainState);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadAvacCommand", Mt_CtrlStp_RteAccess_ReadAvacCommand);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadVehicleModeConfig", Mt_CtrlStp_RteAccess_ReadVehicleModeConfig);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadLevellingFeedback", Mt_CtrlStp_RteAccess_ReadLevellingFeedback);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus", Mt_CtrlStp_RteAccess_ReadLevellingDiagStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadElectricalSuppState", Mt_CtrlStp_RteAccess_ReadElectricalSuppState);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine", Mt_CtrlStp_RteAccess_ReadDiagStpControlRoutine);
  ALUnitTest_AddFunction("Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0", Mt_CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0);


  //CtrlStp_Data.c   
  ALUnitTest_AddFunction("Mt_CtrlStp_ParaFct0", Mt_CtrlStp_ParaFct0);
  ALUnitTest_AddFunction("Mt_CtrlStp_CodingDataReady", Mt_CtrlStp_CodingDataReady);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrAnschlagMi", Mt_CtrlStp_Cod_LwrAnschlagMi);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrAnschlagPl", Mt_CtrlStp_Cod_LwrAnschlagPl);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrMaxWinkelMi", Mt_CtrlStp_Cod_LwrMaxWinkelMi);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrMaxWinkelPl", Mt_CtrlStp_Cod_LwrMaxWinkelPl);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrAp", Mt_CtrlStp_Cod_LwrAp);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrSp", Mt_CtrlStp_Cod_LwrSp);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrHsZeitAp", Mt_CtrlStp_Cod_LwrHsZeitAp);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrHsZeitSp", Mt_CtrlStp_Cod_LwrHsZeitSp);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrHsZeitMinTt", Mt_CtrlStp_Cod_LwrHsZeitMinTt);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrEnable", Mt_CtrlStp_Cod_LwrEnable);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrHsGrad", Mt_CtrlStp_Cod_LwrHsGrad);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrHsWertStart", Mt_CtrlStp_Cod_LwrHsWertStart);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrTestDlAktiv", Mt_CtrlStp_Cod_LwrTestDlAktiv);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrTestDlWeg", Mt_CtrlStp_Cod_LwrTestDlWeg);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrTestDlPeriode", Mt_CtrlStp_Cod_LwrTestDlPeriode);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrWellRefTimeout", Mt_CtrlStp_Cod_LwrWellRefTimeout);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrAutorefZeitversatz", Mt_CtrlStp_Cod_LwrAutorefZeitversatz);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingHBOffset", Mt_CtrlStp_Cod_AfsLevellingHBOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingTownPedOffset", Mt_CtrlStp_Cod_AfsLevellingTownPedOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingMWBoostOffset", Mt_CtrlStp_Cod_AfsLevellingMWBoostOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingMWOffset", Mt_CtrlStp_Cod_AfsLevellingMWOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingLeftBdwLhdOffset", Mt_CtrlStp_Cod_AfsLevellingLeftBdwLhdOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingLeftBdwRhdOffset", Mt_CtrlStp_Cod_AfsLevellingLeftBdwRhdOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingLeftFoggyLhdOffset", Mt_CtrlStp_Cod_AfsLevellingLeftFoggyLhdOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingLeftFoggyRhdOffset", Mt_CtrlStp_Cod_AfsLevellingLeftFoggyRhdOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingOffOffset", Mt_CtrlStp_Cod_AfsLevellingOffOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_AfsLevellingCorrectSpeed", Mt_CtrlStp_Cod_AfsLevellingCorrectSpeed);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrMaxRefSpeed", Mt_CtrlStp_Cod_LwrMaxRefSpeed);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LwrSttDelay", Mt_CtrlStp_Cod_LwrSttDelay);
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_GFHBOffsetLevellingDelay", Mt_CtrlStp_Cod_GFHBOffsetLevellingDelay); 
  ALUnitTest_AddFunction("Mt_CtrlStp_Cod_LevellingStepperFailureReportTime", Mt_CtrlStp_Cod_LevellingStepperFailureReportTime);
  //CtrlStp_Core.c
  ALUnitTest_AddFunction("Mt_CtrlStp_DiagSequenceMachine", Mt_CtrlStp_DiagSequenceMachine);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetSlaveRefRequest", Mt_CtrlStp_SetSlaveRefRequest);
  ALUnitTest_AddFunction("Mt_CtrlStp_DoNorm", Mt_CtrlStp_DoNorm);
  ALUnitTest_AddFunction("Mt_CtrlStp_WriteValidationFrames", Mt_CtrlStp_WriteValidationFrames);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadStepLossRecovery", Mt_CtrlStp_ReadStepLossRecovery);
  ALUnitTest_AddFunction("Mt_CtrlStp_EntryOff", Mt_CtrlStp_EntryOff);
  ALUnitTest_AddFunction("Mt_CtrlStp_EntryRefDn", Mt_CtrlStp_EntryRefDn);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetRefRequest", Mt_CtrlStp_SetRefRequest);
  ALUnitTest_AddFunction("Mt_CtrlStp_EntryNorm", Mt_CtrlStp_EntryNorm);
  ALUnitTest_AddFunction("Mt_CtrlStp_IsMoving", Mt_CtrlStp_IsMoving);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectSide", Mt_CtrlStp_DetectSide);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadStatusSignals", Mt_CtrlStp_ReadStatusSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondEnabled", Mt_CtrlStp_CondEnabled);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondOperationRequest", Mt_CtrlStp_CondOperationRequest);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetSubModeErr", Mt_CtrlStp_GetSubModeErr);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondOperationStatus", Mt_CtrlStp_CondOperationStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturnboExtTakeOver", Mt_CtrlStp_ReturnboExtTakeOver);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadParam", Mt_CtrlStp_ReadParam);
  ALUnitTest_AddFunction("Mt_CtrlStp_DiagRoutineControl", Mt_CtrlStp_DiagRoutineControl);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetSlaveStopRequest", Mt_CtrlStp_SetSlaveStopRequest);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondParamReady", Mt_CtrlStp_CondParamReady);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetDiagPos", Mt_CtrlStp_SetDiagPos);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetDiagRequest", Mt_CtrlStp_SetDiagRequest);
  ALUnitTest_AddFunction("Mt_CtrlStp_ElecDiagStat", Mt_CtrlStp_ElecDiagStat);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectAfsOffsetCurtainActivation", Mt_CtrlStp_DetectAfsOffsetCurtainActivation);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation", Mt_CtrlStp_DetectAfsOffsetCurtainDeactivation);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetContinMove", Mt_CtrlStp_GetContinMove);
  ALUnitTest_AddFunction("Mt_CtrlStp_TempCheck", Mt_CtrlStp_TempCheck);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondRefDelay", Mt_CtrlStp_CondRefDelay);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadCommonSignals", Mt_CtrlStp_ReadCommonSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_PosDiagStat", Mt_CtrlStp_PosDiagStat);
  ALUnitTest_AddFunction("Mt_CtrlStp_DiagStpTakeOver", Mt_CtrlStp_DiagStpTakeOver);
  ALUnitTest_AddFunction("Mt_CtrlStp_LvlStatus", Mt_CtrlStp_LvlStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_EntryErr", Mt_CtrlStp_EntryErr);
  ALUnitTest_AddFunction("Mt_CtrlStp_EntryDis", Mt_CtrlStp_EntryDis); 
  ALUnitTest_AddFunction("Mt_CtrlStp_GetOffset", Mt_CtrlStp_GetOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_ApplyOffset", Mt_CtrlStp_ApplyOffset);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetDiagLvl", Mt_CtrlStp_GetDiagLvl);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetCmdRef", Mt_CtrlStp_GetCmdRef);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetDiagStatus", Mt_CtrlStp_GetDiagStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadEnvironmentSignals", Mt_CtrlStp_ReadEnvironmentSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus", Mt_CtrlStp_ReadLvlAdjFunctionalFaultStatus);
  ALUnitTest_AddFunction("Mt_CtrlStp_CheckFrame350Recovery", Mt_CtrlStp_CheckFrame350Recovery);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadSlaveSignals", Mt_CtrlStp_ReadSlaveSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReadMasterSignals", Mt_CtrlStp_ReadMasterSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_WriteSlaveSignals", Mt_CtrlStp_WriteSlaveSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_WriteMasterSignals", Mt_CtrlStp_WriteMasterSignals);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetTgtPos", Mt_CtrlStp_GetTgtPos); 
  ALUnitTest_AddFunction("Mt_CtrlStp_GetElecIntStopCondition", Mt_CtrlStp_GetElecIntStopCondition);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetIgnitionNeeded", Mt_CtrlStp_SetIgnitionNeeded);
  ALUnitTest_AddFunction("Mt_CtrlStp_isSafetyPosReached", Mt_CtrlStp_isSafetyPosReached);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetTgtTmin", Mt_CtrlStp_SetTgtTmin);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetSubModeError", Mt_CtrlStp_SetSubModeError);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetSlaveSafetyPosition", Mt_CtrlStp_SetSlaveSafetyPosition);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturnValidationParams", Mt_CtrlStp_ReturnValidationParams);
  ALUnitTest_AddFunction("Mt_CtrlStp_StartRef", Mt_CtrlStp_StartRef);
  ALUnitTest_AddFunction("Mt_CtrlStp_EntryInit", Mt_CtrlStp_EntryInit);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondIsReady", Mt_CtrlStp_CondIsReady);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondRefDnCompl", Mt_CtrlStp_CondRefDnCompl);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondRefInProgress", Mt_CtrlStp_CondRefInProgress);
  ALUnitTest_AddFunction("Mt_CtrlStp_RefRequest", Mt_CtrlStp_RefRequest);
  ALUnitTest_AddFunction("Mt_CtrlStp_RetPowerTrainActive", Mt_CtrlStp_RetPowerTrainActive);
  ALUnitTest_AddFunction("Mt_CtrlStp_RetVehIgnition", Mt_CtrlStp_RetVehIgnition);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturnboTrainingState", Mt_CtrlStp_ReturnboTrainingState);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturnboLvlAdjFuncFault", Mt_CtrlStp_ReturnboLvlAdjFuncFault);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturnboSlaveLvlAdjFuncFault", Mt_CtrlStp_ReturnboSlaveLvlAdjFuncFault);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturnSide", Mt_CtrlStp_ReturnSide);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturneLvlAdjHeadlampFault_L", Mt_CtrlStp_ReturneLvlAdjHeadlampFault_L);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturneLvlAdjHeadlampFault_R", Mt_CtrlStp_ReturneLvlAdjHeadlampFault_R);
  ALUnitTest_AddFunction("Mt_CtrlStp_ReturneSensorError", Mt_CtrlStp_ReturneSensorError);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectElecTransition", Mt_CtrlStp_DetectElecTransition);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectElecTransitionSttToAdj", Mt_CtrlStp_DetectElecTransitionSttToAdj);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectElecTransitionSttToRef", Mt_CtrlStp_DetectElecTransitionSttToRef);

  //CtrlStp_Util.c   
  ALUnitTest_AddFunction("Mt_CtrlStp_Angle2StpPos", Mt_CtrlStp_Angle2StpPos);
  ALUnitTest_AddFunction("Mt_CtrlStp_CheckForStart", Mt_CtrlStp_CheckForStart);
  ALUnitTest_AddFunction("Mt_CtrlStp_LimitAngle", Mt_CtrlStp_LimitAngle);
  ALUnitTest_AddFunction("Mt_CtrlStp_Speed2Tmin", Mt_CtrlStp_Speed2Tmin);
  ALUnitTest_AddFunction("Mt_CtrlStp_Tmin2Speed", Mt_CtrlStp_Tmin2Speed);
  ALUnitTest_AddFunction("Mt_CtrlStp_StpPos2Angle", Mt_CtrlStp_StpPos2Angle);

  //CtrlStp.c
  ALUnitTest_AddFunction("Mt_CtrlStp_Init", Mt_CtrlStp_Init);
  ALUnitTest_AddFunction("Mt_CtrlStp_riCtrlStpInit", Mt_CtrlStp_riCtrlStpInit);
  ALUnitTest_AddFunction("Mt_CtrlStp_SubModeAfterSale", Mt_CtrlStp_SubModeAfterSale);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectSlaveSubMode", Mt_CtrlStp_DetectSlaveSubMode);
  ALUnitTest_AddFunction("Mt_CtrlStp_GetStateValue", Mt_CtrlStp_GetStateValue);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Init_To_Adj_Slave", Mt_CtrlStp_Transition_Init_To_Adj_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Ref_To_Adj_Slave", Mt_CtrlStp_Transition_Ref_To_Adj_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_CondRefUpCompl", Mt_CtrlStp_CondRefUpCompl);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Ref_To_Fail_Slave", Mt_CtrlStp_Transition_Ref_To_Fail_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Fail_To_Ref_Slave", Mt_CtrlStp_Transition_Fail_To_Ref_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Fail_To_Adj_Slave", Mt_CtrlStp_Transition_Fail_To_Adj_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Adj_To_Ref_Slave", Mt_CtrlStp_Transition_Adj_To_Ref_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Adj_To_Fail_Slave", Mt_CtrlStp_Transition_Adj_To_Fail_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_ResetStpState", Mt_CtrlStp_ResetStpState);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectMode", Mt_CtrlStp_DetectMode);
  ALUnitTest_AddFunction("Mt_CtrlStp_Proccess_Reference", Mt_CtrlStp_Proccess_Reference);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateRef", Mt_CtrlStp_StateMachine_StateRef);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateAdj", Mt_CtrlStp_StateMachine_StateAdj);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateInit", Mt_CtrlStp_StateMachine_StateInit);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateSTT", Mt_CtrlStp_StateMachine_StateSTT);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateFail", Mt_CtrlStp_StateMachine_StateFail);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Customer_To_Aftersale", Mt_CtrlStp_Transition_Customer_To_Aftersale);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Customer_To_Available", Mt_CtrlStp_Transition_Customer_To_Available);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Customer_To_Unavailable", Mt_CtrlStp_Transition_Customer_To_Unavailable);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Assembly_To_Unavailable", Mt_CtrlStp_Transition_Assembly_To_Unavailable);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Assembly_To_Factory", Mt_CtrlStp_Transition_Assembly_To_Factory);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Assembly_To_Frozen", Mt_CtrlStp_Transition_Assembly_To_Frozen);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_STT_To_Adj", Mt_CtrlStp_Transition_STT_To_Adj);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_STT_To_Ref", Mt_CtrlStp_Transition_STT_To_Ref);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Fail_To_Ref", Mt_CtrlStp_Transition_Fail_To_Ref);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Fail_To_Adj", Mt_CtrlStp_Transition_Fail_To_Adj);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Ref_To_Fail", Mt_CtrlStp_Transition_Ref_To_Fail);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Ref_To_Adj", Mt_CtrlStp_Transition_Ref_To_Adj);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Adj_To_STT", Mt_CtrlStp_Transition_Adj_To_STT);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Adj_To_Fail", Mt_CtrlStp_Transition_Adj_To_Fail);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Ref_To_STT", Mt_CtrlStp_Transition_Ref_To_STT);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Init_To_Fail", Mt_CtrlStp_Transition_Init_To_Fail);
  ALUnitTest_AddFunction("Mt_CtrlStp_Transition_Init_To_Ref", Mt_CtrlStp_Transition_Init_To_Ref);
  ALUnitTest_AddFunction("Mt_CtrlStp_ModeCustomer", Mt_CtrlStp_ModeCustomer);
  ALUnitTest_AddFunction("Mt_CtrlStp_ModeAssembly", Mt_CtrlStp_ModeAssembly);
  ALUnitTest_AddFunction("Mt_CtrlStp_SubModeFrozen", Mt_CtrlStp_SubModeFrozen);
  ALUnitTest_AddFunction("Mt_CtrlStp_SubModeFactory", Mt_CtrlStp_SubModeFactory);
  ALUnitTest_AddFunction("Mt_CtrlStp_SubModeUnavailable", Mt_CtrlStp_SubModeUnavailable);
  ALUnitTest_AddFunction("Mt_CtrlStp_VerifyAndProcessRefRun", Mt_CtrlStp_VerifyAndProcessRefRun);
  ALUnitTest_AddFunction("Mt_CtrlStp_WriteValidationParams", Mt_CtrlStp_WriteValidationParams);
  ALUnitTest_AddFunction("Mt_CtrlStp_UseMode", Mt_CtrlStp_UseMode);
  ALUnitTest_AddFunction("Mt_CtrlStp_UseSubMode", Mt_CtrlStp_UseSubMode);
  ALUnitTest_AddFunction("Mt_CtrlStp_rpCtrlStp_Cycle", Mt_CtrlStp_rpCtrlStp_Cycle);
  ALUnitTest_AddFunction("Mt_CtrlStp_DetectOffset", Mt_CtrlStp_DetectOffset);
  //ALUnitTest_AddFunction("Mt_CtrlStp_Detect_StepLoss_Recovery", Mt_CtrlStp_Detect_StepLoss_Recovery);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateFail_Slave", Mt_CtrlStp_StateMachine_StateFail_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_HandleFailStateBehavior_Slave", Mt_CtrlStp_HandleFailStateBehavior_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_HandleFailState_Slave", Mt_CtrlStp_HandleFailState_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_HandleFailState", Mt_CtrlStp_HandleFailState); 
  ALUnitTest_AddFunction("Mt_CtrlStp_HandleDiagLvl", Mt_CtrlStp_HandleDiagLvl);
  ALUnitTest_AddFunction("Mt_CtrlStp_HandleFailStateBehavior", Mt_CtrlStp_HandleFailStateBehavior);
  ALUnitTest_AddFunction("Mt_CtrlStp_StateMachine_StateInit_Slave", Mt_CtrlStp_StateMachine_StateInit_Slave);
  ALUnitTest_AddFunction("Mt_CtrlStp_SetSignalMode", Mt_CtrlStp_SetSignalMode);
  ALUnitTest_AddFunction("Mt_CtrlStp_StMch", Mt_CtrlStp_StMch);

}

// EOF 
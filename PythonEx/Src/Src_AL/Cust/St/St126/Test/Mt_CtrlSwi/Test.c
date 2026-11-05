//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// \file  Test.c
///
/// \brief  Unit Test Cases for Mcu module
///
/// \author Futo Henrietta Helena (F31185D)
///         mailTo:henrietta-helena.futo[at]marelli.com
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
/// \Test Case :Mt_CtrlSwi_ParaFct0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ParaFct0_Param1 = eParaFct0_CodingDataValid; 	
/// \input CtrlSwi_sCodingParam	   = CtrlSwi_ParaFct0_Param2.Fan1;
///
/// - Expectations:
///
/// \output CtrlSwi_ucDebounce9V   = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN
/// \output CtrlSwi_ucDebounce18V  = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  CtrlSwi_sCodingParam = CtrlSwi_ParaFct0_Param2.Fan1;
  //Step 3) Call FUT
  CtrlSwi_ParaFct0(CtrlSwi_ParaFct0_Param1, CtrlSwi_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_ucDebounce9V, CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN, == );
  AL_UNITTEST_CHECK(CtrlSwi_ucDebounce18V, CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ParaFct0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ParaFct0_Param1 = eParaFct0_CodingDataInalid; 	
/// \input CtrlSwi_sCodingParam	   = CtrlSwi_ParaFct0_Param2.Fan1;
///
/// - Expectations:
///
/// \output CtrlSwi_ucDebounce9V   = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MIN
/// \output CtrlSwi_ucDebounce18V  = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MAX
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  CtrlSwi_sCodingParam = CtrlSwi_ParaFct0_Param2.Fan1;

  //Step 3) Call FUT
  CtrlSwi_ParaFct0(CtrlSwi_ParaFct0_Param1, CtrlSwi_ParaFct0_Param2);

  //Step 4) Check expected output values	
  AL_UNITTEST_CHECK(CtrlSwi_ucDebounce9V, CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MIN, == );
  AL_UNITTEST_CHECK(CtrlSwi_ucDebounce18V, CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MAX, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ParaFct0(void)
{
  Mt_CtrlSwi_ParaFct0_TestCase_1();
  Mt_CtrlSwi_ParaFct0_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_RteAccess_MapParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
///    \input Rte_Write_CodM_CtrlFan_Para_HitCount							 = 0u;
///    \input Rte_Write_CodM_CtrlFan_Para_Param1.eCodingState				 = eParaFct0_CodingDataValid;
///    \input Rte_Write_CodM_CtrlFan_Para_Param1.psCodingParameters_Blocks  = &Coding_Dummy;
///    \input CtrlSwi_sCodingParam											 = CtrlSwi_ParaFct0_Param2.Fan1;
///
/// - Expectations:
///    \output te_Write_CodM_CtrlFan_Para_HitCount  = 1u;
///    \output CtrlSwi_ucDebounce9V				 = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_V_MIN
///    \output CtrlSwi_ucDebounce18V				 = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_V_MAX
//-----------------------------------------------------------------------------

void Mt_CtrlSwi_RteAccess_MapParams(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CodM_CtrlFan_Para_HitCount = 0u;
  Rte_Write_CodM_CtrlFan_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Write_CodM_CtrlFan_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  CtrlSwi_sCodingParam = CtrlSwi_ParaFct0_Param2.Fan1;

  //Step 3) Call FUT
  CtrlSwi_RteAccess_MapParams();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_ucDebounce9V, CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN, == );
  AL_UNITTEST_CHECK(CtrlSwi_ucDebounce18V, CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_Get_ETAT_FEE_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount		 = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty  = SIG_VALID;
/// \input CtrlSwi_Get_ETAT_FEE_Ret_Val					 = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount      = 1u
/// \output CtrlSwi_Get_ETAT_FEE_Ret_Val				= Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Get_ETAT_FEE_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  CtrlSwi_Get_ETAT_FEE_Ret_Val = 0u;

  //Step 3) Call FUT
  CtrlSwi_Get_ETAT_FEE_Ret_Val = CtrlSwi_Get_ETAT_FEE(Rte_Read_SigPrep_ElecSupState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlSwi_Get_ETAT_FEE_Ret_Val, Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_Get_ETAT_FEE_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Rte_Read_SigPrep_ElecSupState_HitCount		 = 0u;
/// \input Rte_Read_SigPrep_ElecSupState_Param1.eSigQty  = SIG_INVALID;
/// \input CtrlSwi_Get_ETAT_FEE_Ret_Val					 = 0u;
///
/// - Expectations:
///
/// \output Rte_Read_SigPrep_ElecSupState_HitCount      = 1u
/// \output CtrlSwi_Get_ETAT_FEE_Ret_Val				= 224u
//-----------------------------------------------------------------------------

void Mt_CtrlSwi_Get_ETAT_FEE_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_INVALID;
  CtrlSwi_Get_ETAT_FEE_Ret_Val = 0u;

  //Step 3) Call FUT
  CtrlSwi_Get_ETAT_FEE_Ret_Val = CtrlSwi_Get_ETAT_FEE(Rte_Read_SigPrep_ElecSupState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_ElecSupState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Get_ETAT_FEE
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Get_ETAT_FEE(void)
{
  Mt_CtrlSwi_Get_ETAT_FEE_TestCase_1();
  Mt_CtrlSwi_Get_ETAT_FEE_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase!1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 1u;
///
/// - Expectations:
///
/// \output CtrlSwi_aucSwitchOnDelay[0u]= CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 1u;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[0u], CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1, == );

}
//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 2u;
///
/// - Expectations:
///
/// \output CtrlSwi_aucSwitchOnDelay[0u]= CFG_CTRLSWI_SWITCH_ON_DELAY_HSS2
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 2u;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[1u], CFG_CTRLSWI_SWITCH_ON_DELAY_HSS2, == );

}
//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 3u;
///
/// - Expectations:
///
/// \output CtrlSwi_aucSwitchOnDelay[2u]= CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 3u;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[2u], CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 0u;
///
/// - Expectations:
///
/// \output CtrlSwi_aucSwitchOnDelay[2u]= CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 0u;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[2u], CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 4u;
///
/// - Expectations:
///
/// \output CtrlSwi_aucSwitchOnDelay[3u]= 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 4u;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[3u], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to  sets the corresponding HSS output
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(void)
{
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_1();
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_2();
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_3();
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_4();
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///
///  - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1 = 4u;
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;
/// \input CtrlSwi_sDiagControl.teMode[0u] = eDiagCtrl_CtrlSwi_Disabled;
///
/// - Expectations:
///
/// \output CtrlSwi_sDiagControl.teMode[0u]			= eDiagCtrl_CtrlSwi_Disabled
/// \output CtrlSwi_sDiagControl.ucHssOutput[0u]	= 0u;
//-----------------------------------------------------------------------------

void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1 = 4u;
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;
  CtrlSwi_sDiagControl.teMode[0u] = eDiagCtrl_CtrlSwi_Disabled;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1, CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sDiagControl.teMode[0u], eDiagCtrl_CtrlSwi_Disabled, == );
  AL_UNITTEST_CHECK(CtrlSwi_sDiagControl.ucHssOutput[0u], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///
///  - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1 = 0u;
/// \input CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;
///
/// - Expectations:
///
/// \output CtrlSwi_sDiagControl.teMode[0u]			= eDiagCtrl_CtrlSwi_Enabled
/// \output CtrlSwi_sDiagControl.ucHssOutput[0u]	= CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2;
/// \output CtrlSwi_aucSwitchOnDelay[0u]			= CFG_CTRLSWI_DIAG_SWITCH_ON_DELAY_HS
//-----------------------------------------------------------------------------

void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1 = 0u;
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;

  //Step 3) Call FUT
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1, CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sDiagControl.teMode[0u], eDiagCtrl_CtrlSwi_Enabled, == );
  AL_UNITTEST_CHECK(CtrlSwi_sDiagControl.ucHssOutput[0u], CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2, == );
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[0u], CFG_CTRLSWI_DIAG_SWITCH_ON_DELAY_HSS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to  sets the corresponding HSS output 
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(void)
{
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_TestCase_1();
  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 2u;
/// \input  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 1u;
///
/// - Expectations:
///
/// \output CtrlSwi_sState.aboHssSwitchOnDelay[2u]=FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 2u;
  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 1u;

  //Step 3) Call FUT
  CtrlSwi_CheckDelaySwitchOnTimer(CtrlSwi_CheckDelaySwitchOnTimer_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssSwitchOnDelay[2u], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 1u;
/// \input  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 0u;
///
/// - Expectations:
///
/// \output CtrlSwi_ucDelaySwitchOnTimer[1u]=FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 1u;
  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 0u;

  //Step 3) Call FUT
  CtrlSwi_CheckDelaySwitchOnTimer(CtrlSwi_CheckDelaySwitchOnTimer_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_ucDelaySwitchOnTimer[1u], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 1u;
/// \input  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 2u;
/// \input    CtrlSwi_sState.aboHssSwitchOnDelay[1u] = TRUE;
///
/// - Expectations:
///
/// \output CtrlSwi_sState.aboHssSwitchOnDelay[1u]=TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 1u;
  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 2u;
  CtrlSwi_sState.aboHssSwitchOnDelay[1u] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_CheckDelaySwitchOnTimer(CtrlSwi_CheckDelaySwitchOnTimer_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssSwitchOnDelay[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_CheckDelaySwitchOnTimer
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckDelaySwitchOnTimer(void)
{
  Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_1();
  Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_2();
  Mt_CtrlSwi_CheckDelaySwitchOnTimer_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_CheckDelayErrorDetectionTimer
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///                  
/// Test subject: This function handels the timer for the switch on delay
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// input : CtrlSwi_CheckDelayErrorDetectionTimer_Param1 = 2u;
/// input : CtrlSwi_ucDelayErrorDetectionTimer[CtrlSwi_CheckDelayErrorDetectionTimer_Param1] = 1u;
/// 
///
/// - Expectations:
///
/// output : CtrlSwi_sState.aboHssStateChangedDiagDisabled[2u]= FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckDelayErrorDetectionTimer(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_CheckDelayErrorDetectionTimer_Param1 = 2u;
  CtrlSwi_ucDelayErrorDetectionTimer[CtrlSwi_CheckDelayErrorDetectionTimer_Param1] = 1u;

  //Step 3) Call FUT
  CtrlSwi_CheckDelayErrorDetectionTimer(CtrlSwi_CheckDelayErrorDetectionTimer_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssStateChangedDiagDisabled[2u], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_SwitchOutput
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///        - Test subject: Check that the function to  sets the corresponding HSS output 
///							with received target
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_SwitchOutput_Param1 = 1u;
/// \input  CtrlSwi_SwitchOutput_Param2 = TRUE;
/// \input  CtrlSwi_sState.aboHssActualState[CtrlSwi_SwitchOutput_Param1] = FALSE;
///
/// - Expectations:
///
/// \output 	AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssPreviousState[1u]=FALSE
/// \output		AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u]= TRUE
/// \output		AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u]= TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_SwitchOutput(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_SwitchOutput_Param1 = 1u;
  CtrlSwi_SwitchOutput_Param2 = TRUE;
  CtrlSwi_sState.aboHssActualState[CtrlSwi_SwitchOutput_Param1] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_SwitchOutput(CtrlSwi_SwitchOutput_Param1, CtrlSwi_SwitchOutput_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssPreviousState[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_OpenLoadHandlingFans_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///        - Test subject: check the set event status value                      
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 2u;
/// \input CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 2u;
/// \input Dem_SetEventStatus_HitCount = 0u;
/// \input Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
/// \input Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
///
/// - Expectations:
///
/// \output 	Dem_SetEventStatus_HitCount	= 1u
/// \output		Dem_SetEventStatus_Param2	= 2u 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 2u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 2u;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

  //Step 3) Call FUT
  CtrlSwi_OpenLoadHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 2u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_OpenLoadHandlingFans_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: check the set event status value                    
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 2u;
/// \input CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 2u;
/// \input Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
/// \input Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;
///
/// - Expectations:
///
/// \output		Dem_SetEventStatus_Param2	= 3u 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = TRUE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = TRUE;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;

  //Step 3) Call FUT
  CtrlSwi_OpenLoadHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_OpenLoadHandlingFans_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: check the set event status value                    
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = FALSE;
/// \input CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = FALSE;
///
/// - Expectations:
///
/// \output 	CtrlSwi_OpenLoadFlag = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = FALSE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OpenLoadHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_OpenLoadFlag, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_OpenLoadHandlingFans_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: check the set event status value                    
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 1;
/// \input 	CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 1;
/// \input 	Dem_SetEventStatus_HitCount = 0u;
/// \input 	Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
/// \input 	Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
/// \input 	CtrlSwi_ucErrTimeout[1] = 1u;
///
/// - Expectations:
///
/// \output 	Dem_SetEventStatus_HitCount	= 1u
/// \output		Dem_SetEventStatus_Param2	= 3u 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_4(void)
{
  // Step 1) Set pre - conditions
    // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 1;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 1;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
  CtrlSwi_ucErrTimeout[1] = 1u;

  //Step 3) Call FUT
  CtrlSwi_OpenLoadHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 0u;
/// \input 	  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 0u;
///
/// \input 	CtrlSwi_OpenLoadFlag = 5u;
///
/// - Expectations:
///
/// \output 	CtrlSwi_OpenLoadFlag	= 0u 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_5(void)
{
  // Step 1) Set pre - conditions
    // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 0u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 0u;
  CtrlSwi_OpenLoadFlag = 5u;

  //Step 3) Call FUT
  CtrlSwi_OpenLoadHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_OpenLoadFlag, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_OpenLoadHandlingFans
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OpenLoadHandlingFans(void)
{
  Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_1();
  Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_2();
  Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_3();
  Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_4();
  Mt_CtrlSwi_OpenLoadHandlingFans_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: check the set event status value                    
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = TRUE;
/// \input 	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = TRUE;
/// \input 	CtrlSwi_Sh2VbatFlag = eERR_SNA;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2VbatFlag			= eERR_YES
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = TRUE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = TRUE;
  CtrlSwi_Sh2VbatFlag = eERR_SNA;
  //Step 3) Call FUT
  CtrlSwi_UpdateSh2VbatFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, eERR_YES, == );
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: check the set event status value                    
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = FALSE;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = FALSE;
/// \input  CtrlSwi_Sh2VbatFlag = eERR_NO;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2VbatFlag  = eERR_SNA
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = FALSE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = FALSE;
  CtrlSwi_Sh2VbatFlag = eERR_NO;

  //Step 3) Call FUT
  CtrlSwi_UpdateSh2VbatFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, eERR_SNA, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the Sh2Vbat                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = 2u;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = 2u;
/// \input  CtrlSwi_Sh2VbatFlag = eERR_SNA;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2VbatFlag = eERR_NO 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = 2u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = 2u;
  CtrlSwi_Sh2VbatFlag = eERR_SNA;
  //Step 3) Call FUT
  CtrlSwi_UpdateSh2VbatFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, eERR_NO, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2VbatFlag
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the set event status value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2VbatFlag(void)
{
  Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_1();
  Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_2();
  Mt_CtrlSwi_UpdateSh2VbatFlag_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2GndFlag_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the Sh2Vbat                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_sState.aboErrOffPermanent[FAN1] = TRUE;
/// \input  CtrlSwi_sState.aboErrOffPermanent[FAN2] = TRUE;
/// \input  CtrlSwi_Sh2GndFlag = eERR_SNA;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2GndFlag = eERR_YES
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2GndFlag_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_sState.aboErrOffPermanent[FAN1] = TRUE;
  CtrlSwi_sState.aboErrOffPermanent[FAN2] = TRUE;
  CtrlSwi_Sh2GndFlag = eERR_SNA;

  //Step 3) Call FUT
  CtrlSwi_UpdateSh2GndFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2GndFlag, eERR_YES, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2GndFlag_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the Sh2Vbat                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_sState.aboErrOffPermanent[FAN1] = FALSE;
/// \input  CtrlSwi_sState.aboErrOffPermanent[FAN2] = FALSE;
/// \input  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = FALSE;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = FALSE;
/// \input  CtrlSwi_Sh2GndFlag = eERR_NO;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2GndFlag = eERR_SNA
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2GndFlag_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_sState.aboErrOffPermanent[FAN1] = FALSE;
  CtrlSwi_sState.aboErrOffPermanent[FAN2] = FALSE;
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = FALSE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = FALSE;
  CtrlSwi_Sh2GndFlag = eERR_NO;

  //Step 3) Call FUT
  CtrlSwi_UpdateSh2GndFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2GndFlag, eERR_SNA, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2GndFlag_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the Sh2Vbat                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_sState.aboErrOffPermanent[FAN1] = FALSE;
/// \input  CtrlSwi_sState.aboErrOffPermanent[FAN2] = FALSE;
/// \input  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 2u;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 2u;
/// \input  CtrlSwi_Sh2GndFlag = eERR_SNA;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2GndFlag = eERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2GndFlag_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_sState.aboErrOffPermanent[FAN1] = FALSE;
  CtrlSwi_sState.aboErrOffPermanent[FAN2] = FALSE;
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 2u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 2u;
  CtrlSwi_Sh2GndFlag = eERR_SNA;

  //Step 3) Call FUT
  CtrlSwi_UpdateSh2GndFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2GndFlag, eERR_NO, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSh2GndFlag
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Updates the error flag for the Sh2Vbat
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSh2GndFlag(void)
{
  Mt_CtrlSwi_UpdateSh2GndFlag_TestCase_1();
  Mt_CtrlSwi_UpdateSh2GndFlag_TestCase_2();
  Mt_CtrlSwi_UpdateSh2GndFlag_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the OpenLoad                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1u;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1u;
/// \input  CtrlSwi_Sh2GndFlag = eERR_SNA;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2GndFlag = eERR_YES
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 1u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 1u;
  CtrlSwi_OpenLoadFlag = eERR_SNA;

  //Step 3) Call FUT
  CtrlSwi_UpdateOpenLoadFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_OpenLoadFlag, eERR_YES, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the OpenLoad                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 2u;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 2u;
/// \input  CtrlSwi_Sh2GndFlag = eERR_SNA;
///
/// - Expectations:
///
/// \output 	CtrlSwi_Sh2GndFlag = eERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 2u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 2u;
  CtrlSwi_Sh2GndFlag = eERR_SNA;

  //Step 3) Call FUT
  CtrlSwi_UpdateOpenLoadFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_OpenLoadFlag, eERR_NO, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Updates the error flag for the OpenLoad                  
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 0u;
/// \input  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 0u;
/// \input  CtrlSwi_Sh2GndFlag = eERR_NO;
///
/// - Expectations:
///
/// \output 	CtrlSwi_OpenLoadFlag = eERR_SNA
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = 0u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = 0u;
  CtrlSwi_Sh2GndFlag = eERR_NO;

  //Step 3) Call FUT
  CtrlSwi_UpdateOpenLoadFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_OpenLoadFlag, eERR_SNA, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateOpenLoadFlag
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Updates the error flag for the OpenLoad
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateOpenLoadFlag(void)
{
  Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_1();
  Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_2();
  Mt_CtrlSwi_UpdateOpenLoadFlag_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSwitchOnTimeCounter_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject:increments the statitic counter in case of the HSS output has no error.                   
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 		CtrlSwi_UpdateSwitchOnTimeCounter_Param1 = 1u;
/// \input 	    CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_UpdateSwitchOnTimeCounter_Param1] = CTRLSWI_CFG_ERR_YES;
///
/// - Expectations:
///
/// \output 	CtrlSwi_sState.aulHssStatisticOnTime[CtrlSwi_UpdateSwitchOnTimeCounter_Param1]== 10000
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSwitchOnTimeCounter_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_UpdateSwitchOnTimeCounter_Param1 = 1u;
  CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_UpdateSwitchOnTimeCounter_Param1] = CTRLSWI_CFG_ERR_YES;

  //Step 3) Call FUT
  CtrlSwi_UpdateSwitchOnTimeCounter(CtrlSwi_UpdateSwitchOnTimeCounter_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aulHssStatisticOnTime[CtrlSwi_UpdateSwitchOnTimeCounter_Param1], 10000, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSwitchOnTimeCounter_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject:increments the statitic counter in case of the HSS output has no error.             
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_UpdateSwitchOnTimeCounter_Param1 = 1u;
/// \input 	CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_UpdateSwitchOnTimeCounter_Param1]  = CTRLSWI_CFG_ERR_NO;
/// \input 	CtrlSwi_sErrState.ucErrOpenLoad[CtrlSwi_UpdateSwitchOnTimeCounter_Param1]    = CTRLSWI_CFG_ERR_NO;
/// \input 	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_UpdateSwitchOnTimeCounter_Param1] = CTRLSWI_CFG_ERR_NO;
///
/// - Expectations:
///
/// \output 	CtrlSwi_sState.aulHssStatisticOnTime[CtrlSwi_UpdateSwitchOnTimeCounter_Param1]= 20000
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSwitchOnTimeCounter_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_UpdateSwitchOnTimeCounter_Param1 = 1u;
  CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_UpdateSwitchOnTimeCounter_Param1] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[CtrlSwi_UpdateSwitchOnTimeCounter_Param1] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_UpdateSwitchOnTimeCounter_Param1] = CTRLSWI_CFG_ERR_NO;

  //Step 3) Call FUT
  CtrlSwi_UpdateSwitchOnTimeCounter(CtrlSwi_UpdateSwitchOnTimeCounter_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aulHssStatisticOnTime[CtrlSwi_UpdateSwitchOnTimeCounter_Param1], 20000, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_UpdateSwitchOnTimeCounter
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  increments the statitic counter in case of the HSS output has no error
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_UpdateSwitchOnTimeCounter(void)
{
  Mt_CtrlSwi_UpdateSwitchOnTimeCounter_TestCase_1();
  Mt_CtrlSwi_UpdateSwitchOnTimeCounter_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_DTCHandling
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject:increments the statitic counter in case of the HSS output has no error.             
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND  = FALSE;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND  = FALSE;
/// \input	CtrlSwi_Sh2GndFlag							= eERR_SNA;
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = FALSE;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = FALSE;
/// \input	CtrlSwi_Sh2VbatFlag							= eERR_SNA;
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad   = FALSE;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad	= FALSE;
/// \input	Dem_SetEventStatus_HitCount					= 0u;
/// \input	Dem_SetEventStatus_Param1					= (uint16)Fan1_E_OC;
/// \input	Dem_SetEventStatus_Param2					= DEM_EVENT_STATUS_PASSED;
///
/// - Expectations:
///
/// \output 	
/// \output CtrlSwi_Sh2GndFlag			 = eERR_NO 
/// \output CtrlSwi_Sh2VbatFlag			 = eERR_NO 
/// \output Dem_SetEventStatus_HitCount	 = 3u
/// \output Dem_SetEventStatus_Param2	 = 2u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_DTCHandling(void)
{
  // Step 1) Set pre - conditions
    // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = FALSE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = FALSE;
  CtrlSwi_Sh2GndFlag = eERR_SNA;
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = FALSE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = FALSE;
  CtrlSwi_Sh2VbatFlag = eERR_SNA;
  CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad = FALSE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad = FALSE;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

  //Step 3) Call FUT
  CtrlSwi_DTCHandling();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2GndFlag, eERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, eERR_SNA, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Function which sets the DTC for Sh2Gnd and updates the error flag             
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = TRUE;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = TRUE;
/// \input	CtrlSwi_Sh2GndFlag						   = eERR_NO;
/// \input	Dem_SetEventStatus_HitCount				   = 0u;
/// \input	Dem_SetEventStatus_Param1				   = (uint16)Fan1_E_OC;
/// \input	Dem_SetEventStatus_Param2				   = DEM_EVENT_STATUS_FAILED;
///
/// - Expectations:
///
/// \output 	
/// \output Dem_SetEventStatus_HitCount	 = 1u 
/// \output Dem_SetEventStatus_Param2	 = 2u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = TRUE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = TRUE;
  CtrlSwi_Sh2GndFlag = eERR_NO;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;

  //Step 3) Call FUT
  CtrlSwi_Sh2GndHandlingFans();
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 2u, == );


}
//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject: Function which sets the DTC for Sh2Gnd and updates the error flag         
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1;
/// \input CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1;
/// \input CtrlSwi_Sh2GndFlag						   = eERR_YES;
/// \input Dem_SetEventStatus_Param1				   = (uint16)Fan1_E_OC;
/// \input Dem_SetEventStatus_Param2				   = DEM_EVENT_STATUS_PASSED;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param2	 = 2u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1;
  CtrlSwi_Sh2GndFlag = eERR_YES;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

  //Step 3) Call FUT
  CtrlSwi_Sh2GndHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 2u, == );


}
//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function increments the statitic counter in case of the HSS output has no error.             
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1u;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1u;
/// \input	CtrlSwi_Sh2GndFlag = eERR_YES;
/// \input	Dem_SetEventStatus_HitCount				   = 0u;
/// \input	Dem_SetEventStatus_Param1				   = (uint16)Fan1_E_OC;
/// \input	Dem_SetEventStatus_Param2				   = DEM_EVENT_STATUS_PASSED;
/// \input	CtrlSwi_ucErrTimeout[0] = 1;
///
/// - Expectations:
///
/// \output 	
/// \output Dem_SetEventStatus_Param2	 = 3u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1u;
  CtrlSwi_Sh2GndFlag = eERR_YES;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
  CtrlSwi_ucErrTimeout[0] = 1;
  //Step 3) Call FUT
  CtrlSwi_Sh2GndHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_4()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function increments the statitic counter in case of the HSS output has no error.             
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_sState.aboErrOffPermanent[FAN1] = 0u;
/// \input	CtrlSwi_sState.aboErrOffPermanent[FAN2] = 0u;
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 0u;
///
/// - Expectations:
///
/// \output 	
/// \output CtrlSwi_Sh2GndFlag			 = 0
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_4(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_sState.aboErrOffPermanent[FAN1] = 0u;
  CtrlSwi_sState.aboErrOffPermanent[FAN2] = 0u;
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 0u;

  //Step 3) Call FUT
  CtrlSwi_Sh2GndHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2GndFlag, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function increments the statitic counter in case of the HSS output has no error.             
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_sState.aboErrOffPermanent[FAN1] = 0u;
/// \input	CtrlSwi_sState.aboErrOffPermanent[FAN2] = 0u;
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1u;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1u;
/// \input	CtrlSwi_Sh2GndFlag = 5u;
///
/// - Expectations:
///
/// \output 	
/// \output CtrlSwi_Sh2GndFlag			 = 5
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_5(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_sState.aboErrOffPermanent[FAN1] = 0u;
  CtrlSwi_sState.aboErrOffPermanent[FAN2] = 0u;
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND = 1u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND = 1u;
  CtrlSwi_Sh2GndFlag = 5u;

  //Step 3) Call FUT
  CtrlSwi_Sh2GndHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2GndFlag, 5u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Sh2GndHandlingFans
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function increments the statitic counter in case of the HSS output has no error
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2GndHandlingFans(void)
{
  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_1();
  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_2();
  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_3();
  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_4();
  Mt_CtrlSwi_Sh2GndHandlingFans_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : Function which sets the DTC for Sh2Gnd and updates the error flag        
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = TRUE;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = TRUE;
/// \input	Dem_SetEventStatus_Param1				    = (uint16)Fan1_E_OC;
/// \input	Dem_SetEventStatus_Param2					= DEM_EVENT_STATUS_FAILED;;
///
/// - Expectations:
///
/// \output 	
/// \output CtrlSwi_Sh2VbatFlag			= eERR_YES
/// \output Dem_SetEventStatus_Param2   = 3u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = TRUE;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = TRUE;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;

  //Step 3) Call FUT
  CtrlSwi_Sh2VbatHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, eERR_YES, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );


}
//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : Function which sets the DTC for Sh2Gnd and updates the error flag        
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input 	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = FALSE;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = FALSE;
/// \input	Dem_SetEventStatus_HitCount					= 0u;
/// \input	Dem_SetEventStatus_Param1					= (uint16)Fan1_E_OC;
/// \input	Dem_SetEventStatus_Param2				    = DEM_EVENT_STATUS_PASSED;
///
/// - Expectations:
///
/// \output 	
/// \output CtrlSwi_Sh2VbatFlag			= eERR_NO
/// \output Dem_SetEventStatus_HitCount = 1u
/// \output Dem_SetEventStatus_Param2   = 2u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = eERR_NO;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = eERR_NO;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;

  //Step 3) Call FUT
  CtrlSwi_Sh2VbatHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, eERR_NO, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 2u, == );

}
//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : Function which sets the DTC for Sh2Gnd and updates the error flag        
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = 1u;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = 1u;
/// \input	Dem_SetEventStatus_HitCount					= 0u;
/// \input	Dem_SetEventStatus_Param1					= (uint16)Fan1_E_OC;
/// \input	Dem_SetEventStatus_Param2					= DEM_EVENT_STATUS_PASSED;
///
/// - Expectations:
///
/// \output 	
/// \output  Dem_SetEventStatus_HitCount= 1u
/// \output  Dem_SetEventStatus_Param2  = 3u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = 1u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = 1u;
  Dem_SetEventStatus_HitCount = 0u;
  Dem_SetEventStatus_Param1 = (uint16)Fan1_E_OC;
  Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
  CtrlSwi_ucErrTimeout[2] = 1u;

  //Step 3) Call FUT
  CtrlSwi_Sh2VbatHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, 3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : Function which sets the DTC for Sh2Gnd and updates the error flag        
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input	CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = 0u;
/// \input	CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = 0u;
///
/// - Expectations:
///
/// \output 	
/// \output  CtrlSwi_Sh2VbatFlag        = 0
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_4(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT = 0u;
  CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT = 0u;

  //Step 3) Call FUT
  CtrlSwi_Sh2VbatHandlingFans();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_Sh2VbatFlag, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Sh2VbatHandlingFans
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Function which sets the DTC for Sh2Gnd and updates the error fla
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Sh2VbatHandlingFans(void)
{
  Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_1();
  Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_2();
  Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_3();
  Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CtrlSwi_CheckExternalTakeover_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function operates the target value with external takeover value
///                    and target value     
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  CtrlSwi_CheckExternalTakeover_Param1	 = 1u;
/// \input  CtrlSwi_sDiagControl.teMode[1u]			 = eDiagCtrl_CtrlSwi_Disabled;
/// \input  CtrlSwi_aboAppMTargetState[1u]			 = TRUE;
/// 
///  
/// - Expectations:
///
/// \output 	
/// \output CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1]= TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckExternalTakeover_TestCase_1(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_CheckExternalTakeover_Param1 = 1u;
  CtrlSwi_sDiagControl.teMode[1u] = eDiagCtrl_CtrlSwi_Disabled;
  CtrlSwi_aboAppMTargetState[1u] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_CheckExternalTakeover(CtrlSwi_CheckExternalTakeover_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function operates the target value with external takeover value
///                    and target value     
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  	CtrlSwi_CheckExternalTakeover_Param1								   = 1u;
/// \input      CtrlSwi_sDiagControl.teMode[1u]										   = eDiagCtrl_CtrlSwi_Enabled;
/// \input      CtrlSwi_sDiagControl.ucHssOutput[CtrlSwi_CheckExternalTakeover_Param1] = FALSE;
///
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1]     = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckExternalTakeover_TestCase_2(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_CheckExternalTakeover_Param1 = 1u;
  CtrlSwi_sDiagControl.teMode[1u] = eDiagCtrl_CtrlSwi_Enabled;
  CtrlSwi_sDiagControl.ucHssOutput[CtrlSwi_CheckExternalTakeover_Param1] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_CheckExternalTakeover(CtrlSwi_CheckExternalTakeover_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function operates the target value with external takeover value
///                    and target value     
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  	CtrlSwi_CheckExternalTakeover_Param1								   = 5u;
/// \input      CtrlSwi_sDiagControl.teMode[1u]										   = eDiagCtrl_CtrlSwi_Disabled;
/// \input      CtrlSwi_sState.aboRetryStarted[CtrlSwi_CheckExternalTakeover_Param1] = TRUE;
///
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1]     = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckExternalTakeover_TestCase_3(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_CheckExternalTakeover_Param1 = 5u;
  CtrlSwi_sDiagControl.teMode[CtrlSwi_CheckExternalTakeover_Param1] = eDiagCtrl_CtrlSwi_Disabled;
  CtrlSwi_sState.aboRetryStarted[CtrlSwi_CheckExternalTakeover_Param1] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_CheckExternalTakeover(CtrlSwi_CheckExternalTakeover_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Sh2VbatHandlingFans_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function operates the target value with external takeover value
///                    and target value     
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  	CtrlSwi_CheckExternalTakeover_Param1								   = 1u;
/// \input      CtrlSwi_sDiagControl.teMode[1u]										   = eDiagCtrl_CtrlSwi_Disabled;
/// \input      CtrlSwi_sDiagControl.ucHssOutput[CtrlSwi_CheckExternalTakeover_Param1] = TRUE;
///
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1]     = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckExternalTakeover_TestCase_4(void)
{
  // Step 1) Set pre - conditions
  // Step 2) Assign Input values
  CtrlSwi_CheckExternalTakeover_Param1 = 1u;
  CtrlSwi_sDiagControl.teMode[CtrlSwi_CheckExternalTakeover_Param1] = eDiagCtrl_CtrlSwi_Disabled;
  CtrlSwi_sState.aboRetryStarted[CtrlSwi_CheckExternalTakeover_Param1] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_CheckExternalTakeover(CtrlSwi_CheckExternalTakeover_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[CtrlSwi_CheckExternalTakeover_Param1], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_CheckExternalTakeover
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function operates the target value with external takeover value
///                    and target value
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckExternalTakeover(void)
{
  Mt_CtrlSwi_CheckExternalTakeover_TestCase_1();
  Mt_CtrlSwi_CheckExternalTakeover_TestCase_2();
  Mt_CtrlSwi_CheckExternalTakeover_TestCase_3();
  Mt_CtrlSwi_CheckExternalTakeover_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : Diagnostic runnable to control for the corresponding output with
///         received targaet
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  	roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param1 = 1u;
/// \input		roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;
/// \input		CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1  = 1u;
/// \input		CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2  = 2u;
///
/// - Expectations:
///	
/// \output 
/// \output CtrlSwi_sDiagControl.teMode[0u]			= eDiagCtrl_CtrlSwi_Enabled
/// \output CtrlSwi_sDiagControl.ucHssOutput[0u]	= CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2
/// \output CtrlSwi_aucSwitchOnDelay[0u]			= CFG_CTRLSWI_DIAG_SWITCH_ON_DELAY_HSS 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param1 = 1u;
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param1 = 1u;
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2 = 2u;

  //Step 3) Call FUT
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param1, roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sDiagControl.teMode[0u], eDiagCtrl_CtrlSwi_Enabled, == );
  AL_UNITTEST_CHECK(CtrlSwi_sDiagControl.ucHssOutput[0u], CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start_Param2, == );
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[0u], CFG_CTRLSWI_DIAG_SWITCH_ON_DELAY_HSS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///
///   - Test subject :  diagnostic runnable to stop the takeover for the corresponding output
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input   roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 1u;
/// \input   CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1  = 1u;
///
/// - Expectations:
///	
/// \output CtrlSwi_aucSwitchOnDelay[0u]= CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 1u;
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop_Param1 = 1u;

  //Step 3) Call FUT
  roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aucSwitchOnDelay[0u], CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   CtrlSwi_Init() reads RTE-Ports of EftCrcStatus and EftData,
///         initializes static variables and RTE-Port ppCtrlSwiStatusError0
///         call RTE ppIoHwAbUserHssTarget0 
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Rte_Write_CodM_CtrlFan_Para_Param1.eCodingState				 = eParaFct0_CodingDataValid;
/// \input Rte_Write_CodM_CtrlFan_Para_Param1.psCodingParameters_Blocks	 = &Coding_Dummy;
/// \input   CtrlSwi_DataValid_RetVal = TRUE;
///
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssTargetState[0] = FALSE
/// \output CtrlSwi_sState.aboHssActualState[0] = FALSE
/// \output CtrlSwi_sVoltState.boSwitchOn[0] = TRUE
/// \output CtrlSwi_sVoltState.boSwitchOn[0] = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Init_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_CtrlFan_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_CtrlFan_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  CtrlSwi_DataValid_RetVal = TRUE;

  //Step 3) Call FUT
  CtrlSwi_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   CtrlSwi_Init() reads RTE-Ports of EftCrcStatus and EftData,
///         initializes static variables and RTE-Port ppCtrlSwiStatusError0
///         call RTE ppIoHwAbUserHssTarget0 
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Rte_Read_CodM_CtrlFan_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
/// \input Rte_Read_CodM_CtrlFan_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
/// \input CtrlSwi_DataValid_RetVal = FALSE;
///
/// - Expectations:
///	
/// \output 
/// \output *Rte_Write_CtrlSwi_StatusErr_Param1.eStatOn = 255;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Init_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Rte_Read_CodM_CtrlFan_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_CtrlFan_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
  CtrlSwi_DataValid_RetVal = FALSE;
  //Step 3) Call FUT
  CtrlSwi_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*Rte_Write_CtrlSwi_StatusErr_Param1.eStatOn, 255, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_Init_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  CtrlSwi_Init() reads RTE-Ports of EftCrcStatus and EftData,
///         initializes static variables and RTE-Port ppCtrlSwiStatusError0
///         call RTE ppIoHwAbUserHssTarget0
///         update the Rte_Write_CtrlSwi_TgtValue_Fan1_Param1
///        
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  CtrlSwi_sState.boEftCrcStatus								 = FALSE;
///
/// - Expectations:
///	
/// \output 
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_Param1 = 0u;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Init_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  CtrlSwi_sState.boEftCrcStatus = FALSE;

  //Step 3) Call FUT
  CtrlSwi_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan1_Param1, 0u, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  CtrlSwi_Init() reads RTE-Ports of EftCrcStatus and EftData,
///         initializes static variables and RTE-Port ppCtrlSwiStatusError0
///         call RTE ppIoHwAbUserHssTarget0
///         update the Rte_Write_CtrlSwi_TgtValue_Fan1_Param1
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Init(void)
{
  Mt_CtrlSwi_Init_TestCase_1();
  Mt_CtrlSwi_Init_TestCase_2();
  Mt_CtrlSwi_Init_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_CtrlSwi_DeInit
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   set the HSS-outputs and the SenseEnable (SEN) to LOW
///        
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// \input  Rte_Write_CtrlSwi_TgtValue_Fan1_Param1	 = 0u;
/// \input  Rte_Write_CtrlSwi_TgtValue_Fan2_Param1   = 0u;
/// \input  Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 0u;
///
/// - Expectations:
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 1u
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_Param1   = 0u
/// \output Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 1u
/// \output Rte_Write_CtrlSwi_TgtValue_Fan2_Param1   = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_DeInit(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Write_CtrlSwi_TgtValue_Fan1_Param1 = 0u;
  Rte_Write_CtrlSwi_TgtValue_Fan2_Param1 = 0u;
  Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_DeInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan1_Param1, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan2_Param1, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckAllErrors_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	   CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
/// \input     CtrlSwi_Diag_CheckAllErrors_Param2 = TRUE;
/// \input     CtrlSwi_Diag_CheckAllErrors_Param3 = TRUE;
/// - Expectations:
///	
/// \output 
/// \output CtrlSwi_sErrState.ucCntOpenLoad[1u]                                 =  0u;
/// \output CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckAllErrors_Param1] =  0u;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = TRUE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = TRUE;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckAllErrors(CtrlSwi_Diag_CheckAllErrors_Param1, CtrlSwi_Diag_CheckAllErrors_Param2, CtrlSwi_Diag_CheckAllErrors_Param3);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[1u], 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckAllErrors_Param1], 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckAllErrors_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///  \Functional Safety: NA
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckAllErrors_Param1		   = 1u;
/// \input	CtrlSwi_Diag_CheckAllErrors_Param2		   = TRUE;
/// \input	CtrlSwi_Diag_CheckAllErrors_Param3		   = FALSE;
/// \input	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1  = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_HSS_SNA;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad	 = CTRLSWI_CFG_HSS_SNA;
///
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntOpenLoad[1u]									= 0u;
/// \output CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckAllErrors_Param1] = 0u;
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = TRUE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = FALSE;
  CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_HSS_SNA;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_HSS_SNA;


  //Step 3) Call FUT
  CtrlSwi_Diag_CheckAllErrors(CtrlSwi_Diag_CheckAllErrors_Param1, CtrlSwi_Diag_CheckAllErrors_Param2, CtrlSwi_Diag_CheckAllErrors_Param3);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[1u], 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckAllErrors_Param1], 0u, == );
}
//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckAllErrors_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	  	CtrlSwi_Diag_CheckAllErrors_Param1                                                  = 1u;
/// \input   	CtrlSwi_Diag_CheckAllErrors_Param2                                                  = FALSE;
/// \input   	CtrlSwi_Diag_CheckAllErrors_Param3                                                  = FALSE;
/// \input   	CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1                                        = 1u;
/// \input   	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_HSS_SNA;
///
/// - Expectations:
///	
/// \output CtrlSwi_sErrState.ucCntOpenLoad[1u]                                 =  0u;
/// \output CtrlSwi_sErrState.ucErrOpenLoad[1u]									=  CTRLSWI_CFG_ERR_SNA;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = FALSE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = FALSE;
  CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_HSS_SNA;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckAllErrors(CtrlSwi_Diag_CheckAllErrors_Param1, CtrlSwi_Diag_CheckAllErrors_Param2, CtrlSwi_Diag_CheckAllErrors_Param3);


  //Step 4) Check expected output values	
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[1u], 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrOpenLoad[1u], CTRLSWI_CFG_ERR_SNA, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
/// \input   	CtrlSwi_Diag_CheckAllErrors_Param2 = TRUE;
/// \input   	CtrlSwi_Diag_CheckAllErrors_Param3 = FALSE;
/// \input   	CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE;
///
/// - Expectations:
///	
/// \output 
/// \output CtrlSwi_sErrState.ucErrShortToGnd[1u]									=  TRUE;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = TRUE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = FALSE;
  CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckAllErrors(CtrlSwi_Diag_CheckAllErrors_Param1, CtrlSwi_Diag_CheckAllErrors_Param2, CtrlSwi_Diag_CheckAllErrors_Param3);

  //Step 4) Check expected output values	
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
/// \input   	CtrlSwi_Diag_CheckAllErrors_Param2 = FALSE;
/// \input   	CtrlSwi_Diag_CheckAllErrors_Param3 = FALSE;
/// \input   	CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE;
///
/// - Expectations:
///	
/// \output CtrlSwi_sErrState.ucErrShortToGnd[1u]          = TRUE;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckAllErrors_Param1 = 1u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = FALSE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = FALSE;
  CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckAllErrors(CtrlSwi_Diag_CheckAllErrors_Param1, CtrlSwi_Diag_CheckAllErrors_Param2, CtrlSwi_Diag_CheckAllErrors_Param3);

  //Step 4) Check expected output values	
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Diag_CheckAllErrors
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckAllErrors(void)
{
  Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_1();
  Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_2();
  Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_3();
  Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_4();
  Mt_CtrlSwi_Diag_CheckAllErrors_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1										 = 1u;
/// \input	CtrlSwi_sErrState.ucCntShortToGnd[1u]										  	 = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_YES;
/// \input  CtrlSwi_Diag_CheckShort2GndDuringOn(CtrlSwi_Diag_CheckShort2GndDuringOn_Param1);
///
/// - Expectations:
/// \output  CtrlSwi_sErrState.ucCntShortToGnd[1u]= 2u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_1(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
  CtrlSwi_sErrState.ucCntShortToGnd[1u] = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_YES;


  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2GndDuringOn(CtrlSwi_Diag_CheckShort2GndDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[1u], 2u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCaser_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1										 = 1u;
/// \input	CtrlSwi_sErrState.ucCntShortToGnd[1u]											 = 70u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_YES;
///
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntShortToGnd[1u]= 60u;
/// \output CtrlSwi_sErrState.ucErrShortToGnd[1u]= CTRLSWI_CFG_ERR_YES ;
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
  CtrlSwi_sErrState.ucCntShortToGnd[1u] = 70u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_YES;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2GndDuringOn(CtrlSwi_Diag_CheckShort2GndDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[1u], 60u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[1u], CTRLSWI_CFG_ERR_YES, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :    Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1										 = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucCntShortToGnd[1u]											 = 3u;
///
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntShortToGnd[1u] = 2u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[1u] = 3u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2GndDuringOn(CtrlSwi_Diag_CheckShort2GndDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[1u], 2u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :    Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1										 = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
///
/// \input	CtrlSwi_sErrState.ucCntShortToGnd[1u]											 = 0u;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1] = CTRLSWI_CFG_ERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[1u] = 0u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2GndDuringOn(CtrlSwi_Diag_CheckShort2GndDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1], CTRLSWI_CFG_ERR_NO, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :    Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///  \Functional Safety: NA
///
///   - Test subject :   This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1										 = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
///
/// - Expectations:
/// \output CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1] = CTRLSWI_CFG_ERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2GndDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1].ucErrShort2GND = 0u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2GndDuringOn(CtrlSwi_Diag_CheckShort2GndDuringOn_Param1);

  //Step 4) Check expected output values
 // AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[CtrlSwi_Diag_CheckShort2GndDuringOn_Param1], CTRLSWI_CFG_ERR_NO, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Diag_CheckShort2GndDuringOn
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2GndDuringOn(void)
{
  Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_1();
  Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_2();
  Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_3();
  Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_4();
  Mt_CtrlSwi_Diag_CheckShort2GndDuringOn_TestCase_5();
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
/// \input  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_YES;
/// \input  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_NO;
///
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]= 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_NO;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :    Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///  \Functional Safety: NA
///
///   - Test subject :   This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
/// \param  ucHssChannel         0: HSS1, 1: HSS2, 2: HSS3
///       
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input 	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_YES;
/// \input 	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_NO;
/// \input 	CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]     = 80u;
///
/// - Expectations:
///	
/// \output CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]= 60u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_2(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = 80u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], 60u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_YES;
/// \input	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_YES;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucErrOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]= CTRLSWI_CFG_ERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_3(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_YES;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], CTRLSWI_CFG_ERR_NO, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_YES;
/// \input	CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]     = 2u;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]= 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = 2u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_YES;
/// \input	CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]     = 0u;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucErrOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]= CTRLSWI_CFG_ERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucCntOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = 0u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrOpenLoad[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], CTRLSWI_CFG_ERR_NO, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_YES;
/// \input	CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = 2u;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]= 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = 2u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = CTRLSWI_CFG_ERR_YES;
/// \input	CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]  = 0u;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]=CTRLSWI_CFG_ERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1] = 0u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], CTRLSWI_CFG_ERR_NO, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
/// \param  ucHssChannel         0: HSS1, 1: HSS2, 2: HSS3
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckOpenloadDuringOn_Param1									   = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1]!= CTRLSWI_CFG_ERR_YES
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_8(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  CtrlSwi_Diag_CheckOpenloadDuringOn_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckOpenloadDuringOn(CtrlSwi_Diag_CheckOpenloadDuringOn_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckOpenloadDuringOn_Param1], CTRLSWI_CFG_ERR_YES, != );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Diag_CheckOpenloadDuringOn
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckOpenloadDuringOn(void)
{
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_1();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_2();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_3();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_4();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_5();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_6();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_7();
  Mt_CtrlSwi_Diag_CheckOpenloadDuringOn_TestCase_8();
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function to check short to Vbat during off-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1										= 1u;
/// \input	CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]	= 2u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_YES;
/// - Expectations:
///	
/// \output CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]	= 3u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1 = 1u;
  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1] = 2u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_YES;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2VbatDuringOff(CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1], 3u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function to check short to Vbat during off-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1								        = 1u;
/// \input	CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]    = 80u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_YES;
/// - Expectations:
/// \output CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]= 60u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1 = 1u;
  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1] = 80u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_YES;


  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2VbatDuringOff(CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1], 60u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function to check short to Vbat during off-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1									    = 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]    = 2u;
/// - Expectations:
///	
/// \output  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]= 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1] = 2u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2VbatDuringOff(CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1], 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///
///   - Test subject :   This function to check short to Vbat during off-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1										= 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]	= 0u;
/// - Expectations:
///	
/// \output CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]= CTRLSWI_CFG_ERR_NO
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1] = 0u;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2VbatDuringOff(CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1], CTRLSWI_CFG_ERR_NO, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function to check short to Vbat during off-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1										= 1u;
/// \input	CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA;
/// - Expectations:
///	
/// \output CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1]!= 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1 = 1u;
  CtrlSwi_aSwitchStatus[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA;

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckShort2VbatDuringOff(CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToVbat[CtrlSwi_Diag_CheckShort2VbatDuringOff_Param1], 1u, != );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  his function to check short to Vbat during off-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff(void)
{
  Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_1();
  Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_2();
  Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_3();
  Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_4();
  Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff_TestCase_5();
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_OperateOutputWithVoltState_Param1										  = 1u;
/// \input 	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input 	CtrlSwi_CheckDelaySwitchOnTimer_Param1											  = 1u;
/// \input 	CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1]			  = 0u;
/// \input 	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
/// \input 	CtrlSwi_sState.aboPreTargestState[CtrlSwi_OperateOutputWithVoltState_Param1]	  = 2u;	
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssNewRequest[CtrlSwi_OperateOutputWithVoltState_Param1]= TRUE
/// \output CtrlSwi_sState.aboPreTargestState[1u],									  = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 1u;
  CtrlSwi_ucDelaySwitchOnTimer[CtrlSwi_CheckDelaySwitchOnTimer_Param1] = 0u;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboPreTargestState[CtrlSwi_OperateOutputWithVoltState_Param1] = 2u;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssNewRequest[CtrlSwi_OperateOutputWithVoltState_Param1], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1										  = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
/// \input	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1]	  = 3u;
/// \input	CtrlSwi_sVoltState.boSwitchOn[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input	CtrlSwi_sState.aboHssSwitchOnDelay[CtrlSwi_OperateOutputWithVoltState_Param1]	  = FALSE;
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssStateChangedDiagDisabled[CtrlSwi_OperateOutputWithVoltState_Param1]=TRUE
/// \output CtrlSwi_aboCddSwiTarget[1u]																=TRUE
/// \output CtrlSwi_sState.aboHssActualState[1u]													=TRUE
/// \output CtrlSwi_sState.aboPreTargestState[1u]													=TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = 3u;
  CtrlSwi_sVoltState.boSwitchOn[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssSwitchOnDelay[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssStateChangedDiagDisabled[CtrlSwi_OperateOutputWithVoltState_Param1], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1										  = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1]	  = 3u;
/// \input	CtrlSwi_sVoltState.boSwitchOn[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input	CtrlSwi_sState.aboHssSwitchOnDelay[CtrlSwi_OperateOutputWithVoltState_Param1]	  = FALSE;
/// \input	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
/// \input	CtrlSwi_sState.aboHssNewRequest[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1]= FALSE
/// \output CtrlSwi_aboCddSwiTarget[1u]														 = TRUE
/// \output CtrlSwi_sState.aboHssActualState[1u]											 = TRUE
/// \output CtrlSwi_sState.aboPreTargestState[1u]											 = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = 3u;
  CtrlSwi_sVoltState.boSwitchOn[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssSwitchOnDelay[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssNewRequest[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1								          = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]       = TRUE;
/// \input	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
/// \input	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1]     = TRUE;
/// \input	CtrlSwi_ucDelayErrorDetectionTimer[1u]											  = 0u;
/// \input	CtrlSwi_sVoltState.boRemainOn[1u]												  = FALSE;
/// - Expectations:
/// \output	CtrlSwi_aboCddSwiTarget[1u],		 = FALSE
/// \output	CtrlSwi_sState.aboHssActualState[1u] = FALSE
/// \output CtrlSwi_sState.aboPreTargestState[1u]= TRUE

//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_ucDelayErrorDetectionTimer[1u] = 0u;
  CtrlSwi_sVoltState.boRemainOn[1u] = FALSE;


  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_OperateOutputWithVoltState_Param1										  = 1u;
/// \input 	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input 	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
/// \input 	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1]     = TRUE;
/// \input 	CtrlSwi_ucDelayErrorDetectionTimer[1u]											  = 0u;
/// \input 	CtrlSwi_sVoltState.boRemainOn[1u]												  = TRUE;
/// \input 	CtrlSwi_sErrState.ucErrShortToGnd[1u]											  = CTRLSWI_CFG_ERR_YES;
/// \input 	CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u]								  = FALSE;
/// - Expectations:
///	
/// \output 
/// \output CtrlSwi_aboCddSwiTarget[1u],													 = FALSE
/// \output CtrlSwi_sState.aboHssActualState[1u],											 = FALSE
/// \output CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1]= TRUE
/// \output CtrlSwi_sState.aboPreTargestState[1u],											 = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_ucDelayErrorDetectionTimer[1u] = 0u;
  CtrlSwi_sVoltState.boRemainOn[1u] = TRUE;
  CtrlSwi_sErrState.ucErrShortToGnd[1u] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1										  = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]       = TRUE;
/// \input	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
/// \input	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1]     = TRUE;
/// \input	CtrlSwi_ucDelayErrorDetectionTimer[1u]				         					  = 0u;
/// \input	CtrlSwi_sVoltState.boRemainOn[1u]												  = TRUE;
/// \input	CtrlSwi_sErrState.ucErrShortToGnd[1u]											  = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u]								  = FALSE;
///
/// - Expectations:
///	
/// \output CtrlSwi_aboCddSwiTarget[1u]	      		= TRUE
/// \output CtrlSwi_sState.aboHssActualState[1u]    = TRUE
/// \output CtrlSwi_sState.aboPreTargestState[1u]   = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_ucDelayErrorDetectionTimer[1u] = 0u;
  CtrlSwi_sVoltState.boRemainOn[1u] = TRUE;
  CtrlSwi_sErrState.ucErrShortToGnd[1u] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1										  = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]		  = TRUE;
/// \input	CtrlSwi_sState.aboPreTargestState[CtrlSwi_OperateOutputWithVoltState_Param1]	  = TRUE;
/// \input	CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
/// \input	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1]	  = TRUE;
/// \input	CtrlSwi_ucDelayErrorDetectionTimer[1u]											  = 0u;
/// \input	CtrlSwi_sVoltState.boRemainOn[1u]												  = TRUE;
/// \input	CtrlSwi_sErrState.ucErrShortToGnd[1u]											  = CTRLSWI_CFG_ERR_NO;
/// \input	CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u]								  = FALSE;
/// - Expectations:
///	
/// \output CtrlSwi_aboCddSwiTarget[1u]          = FALSE
/// \output CtrlSwi_sState.aboHssActualState[1u] = FALSE
/// \output CtrlSwi_sState.aboPreTargestState[1u]= TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboPreTargestState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssShort2GNDDetected[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
  CtrlSwi_ucDelayErrorDetectionTimer[1u] = 0u;
  CtrlSwi_sVoltState.boRemainOn[1u] = TRUE;
  CtrlSwi_sErrState.ucErrShortToGnd[1u] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_OperateOutputWithVoltState_Param1									  = 1u;
/// \input 	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]   = FALSE;
/// \input 	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;
/// - Expectations:
///	
/// \output CtrlSwi_sState.aboHssSwitchOnDelay[1u] = TRUE
/// \output CtrlSwi_aboCddSwiTarget[1u]			   = FALSE
/// \output CtrlSwi_sState.aboHssActualState[1u]   = FALSE
/// \output CtrlSwi_sState.aboPreTargestState[1u]  = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_8(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values

  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = TRUE;


  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssSwitchOnDelay[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1									  = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1]   = FALSE;
/// \input	CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
/// \input	CtrlSwi_CheckDelaySwitchOnTimer_Param1										  = 1u;
/// \input	CtrlSwi_CheckDelayErrorDetectionTimer_Param1								  = 1u;
/// \input	CtrlSwi_ucDelayErrorDetectionTimer[1u]										  = 1u;
/// \input	CtrlSwi_ucDelaySwitchOnTimer[1u]											  = 1u;
/// - Expectations:
///	
/// \output  CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u]= FALSE
/// \output  CtrlSwi_sState.aboHssSwitchOnDelay[1u],          = FALSE
/// \output  CtrlSwi_aboCddSwiTarget[1u],				      = FALSE
/// \output  CtrlSwi_sState.aboHssActualState[1u],			  = FALSE
/// \output  CtrlSwi_sState.aboPreTargestState[1u],			  = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 1u;
  CtrlSwi_CheckDelayErrorDetectionTimer_Param1 = 1u;
  CtrlSwi_ucDelayErrorDetectionTimer[1u] = 1u;
  CtrlSwi_ucDelaySwitchOnTimer[1u] = 1u;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssStateChangedDiagDisabled[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssSwitchOnDelay[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboPreTargestState[1u], FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
/// \input	CtrlSwi_sState.aboHssTargetState[1u] = TRUE;
/// \input	CtrlSwi_sState.aboPreTargestState[1] = TRUE;
/// \input	CtrlSwi_sState.aboHssPreviousState[1u] = FALSE;
/// \input	CtrlSwi_sVoltState.boSwitchOn[1u] = TRUE;
/// \input	CtrlSwi_sState.aboHssSwitchOnDelay[1u] = FALSE;
/// \input	CtrlSwi_sState.aboHssShort2GNDDetected[1u] = TRUE;
/// \input	CtrlSwi_sState.aboHssNewRequest[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;
/// - Expectations:
///	
/// \output  CtrlSwi_sState.aboHssNewRequest[1u],			  = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 1u;
  CtrlSwi_sState.aboHssTargetState[1u] = TRUE;
  CtrlSwi_sState.aboPreTargestState[1] = TRUE;
  CtrlSwi_sState.aboHssPreviousState[1u] = FALSE;
  CtrlSwi_sVoltState.boSwitchOn[1u] = TRUE;
  CtrlSwi_sState.aboHssSwitchOnDelay[1u] = FALSE;
  CtrlSwi_sState.aboHssShort2GNDDetected[1u] = TRUE;
  CtrlSwi_sState.aboHssNewRequest[CtrlSwi_OperateOutputWithVoltState_Param1] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssNewRequest[1u], FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :   This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	CtrlSwi_OperateOutputWithVoltState_Param1 = 2u;
/// \input	CtrlSwi_sState.aboHssTargetState[2u] = TRUE;
/// \input	CtrlSwi_sState.aboHssPreviousState[2u] = TRUE;
/// \input	CtrlSwi_sVoltState.boRemainOn[2u] = TRUE;
/// \input	CtrlSwi_sErrState.ucErrShortToGnd[2u] = 1u;
/// \input	CtrlSwi_sState.aboHssStateChangedDiagDisabled[2u] = FALSE;
/// - Expectations:
///	
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_OperateOutputWithVoltState_Param1 = 2u;
  CtrlSwi_sState.aboHssTargetState[2u] = TRUE;
  CtrlSwi_sState.aboHssPreviousState[2u] = TRUE;
  CtrlSwi_sVoltState.boRemainOn[2u] = TRUE;
  CtrlSwi_sErrState.ucErrShortToGnd[2u] = 1u;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[2u] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_OperateOutputWithVoltState(CtrlSwi_OperateOutputWithVoltState_Param1);

  // Step 4) Check expected output values
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_OperateOutputWithVoltState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_OperateOutputWithVoltState(void)
{
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_1();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_2();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_3();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_4();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_5();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_6();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_7();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_8();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_9();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_10();
  Mt_CtrlSwi_OperateOutputWithVoltState_TestCase_11();
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_riCtrlSwiInit(void)
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  initialisation runnable
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	
/// \input 	CtrlSwi_sState.boEftCrcStatus			 = TRUE;
/// \input 	Rte_Write_CodM_CtrlFan_Para_HitCount     = 0;
/// \input 	CtrlSwi_sState.aboHssAvailable[0u]       = TRUE;
/// \input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// \input 	Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 0u;
/// - Expectations:
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 1u
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_Param1   = 0u
/// \output Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 1u
/// \output Rte_Write_CtrlSwi_TgtValue_Fan2_Param1   = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_riCtrlSwiInit(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  CtrlSwi_DataValid_RetVal = TRUE;
  CtrlSwi_boCodingValid = TRUE;
  Rte_Write_CodM_CtrlFan_Para_HitCount = 0;
  CtrlSwi_sState.aboHssAvailable[0u] = TRUE;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 0u;

  //Step 3) Call FUT
  riCtrlSwiInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan1_Param1, 0u, == );
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan2_Param1, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_1()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: s
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1					 = SysVolt_eLow2;
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// \input Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
///
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
/// \output CtrlSwi_sVoltState.boSwitchOn[0] = FALSE
/// \output CtrlSwi_sVoltState.boRemainOn[0] = FALSE
/// \output CtrlSwi_sVoltState.boSwitchOn[1] = FALSE
/// \output CtrlSwi_sVoltState.boRemainOn[1] = FALSE
/// \output Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Read_CddSwi_SwitchStatus_HitCount          = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ReadRTEPorts_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eLow2;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[1], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[1], FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SwitchStatus_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_2()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///  \Functional Safety: NA
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: s
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1                     = SysVolt_eHigh2;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
/// \input 	CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad					 = 1u;
/// \input 	LPTMR0_GetTimeElapsed_Param1									 = 1u;
/// \input 	LPTMR0_GetTimeElapsed_HitCount									 = 0u;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount					 = 0u;
/// \input 	Rte_Read_CddSwi_SwitchStatus_HitCount							 = 0u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boSwitchOn[0]               =   FALSE	
/// \output CtrlSwi_sVoltState.boRemainOn[0]               =   FALSE	
/// \output CtrlSwi_sVoltState.boSwitchOn[1]               =   FALSE	
/// \output CtrlSwi_sVoltState.boRemainOn[1]               =   FALSE	
/// \output CtrlSwi_sVoltState.boDiagEnabled               =   FALSE
/// \output LPTMR0_GetTimeElapsed_HitCount                 = 1u
/// \output Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Read_CddSwi_SwitchStatus_HitCount          = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ReadRTEPorts_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eHigh2;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
  CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad = 1u;
  LPTMR0_GetTimeElapsed_Param1 = 1u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();
  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[1], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[1], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SwitchStatus_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_3()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///            ppSysVoltRanges0_boFanSwitchOn
///            ppSysVoltRanges0_boFanRemainOn
///            ppSysVoltRanges0_boErrorDiagEnabled
///            ppIoHwAbUserHssSense0_ulActual
///            ppAppMHssTarget0_aeSetting
///            ppCodMCodingDataStatus0
///            Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: s
///
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1					 = SysVolt_eNormal;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
/// \input 	CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad					 = 1u;
/// \input 	LPTMR0_GetTimeElapsed_Param1									 = 1u;
/// \input 	LPTMR0_GetTimeElapsed_HitCount									 = 0u;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount					 = 0u;
/// \input 	Rte_Read_CddSwi_SwitchStatus_HitCount							 = 0u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boSwitchOn[0]               =   TRUE	
/// \output CtrlSwi_sVoltState.boRemainOn[0]               =   TRUE	
/// \output CtrlSwi_sVoltState.boSwitchOn[1]               =   TRUE	
/// \output CtrlSwi_sVoltState.boRemainOn[1]               =   TRUE	
/// \output CtrlSwi_sVoltState.boDiagEnabled               =   TRUE
/// \output Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Read_CddSwi_SwitchStatus_HitCount          = 1u
/// \output LPTMR0_GetTimeElapsed_HitCount				   = 1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
  CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad = 1u;
  LPTMR0_GetTimeElapsed_Param1 = 1u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[0], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[1], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[1], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SwitchStatus_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_4()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1                      = SysVolt_eLow1;
/// \input	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad  = 1u;
/// \input	CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad                   = 1u;
/// \input	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount                    = 0u;
/// \input	Rte_Read_CddSwi_SwitchStatus_HitCount                             = 0u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boSwitchOn[0]               =   FALSE	
/// \output CtrlSwi_sVoltState.boRemainOn[0]               =   TRUE	
/// \output CtrlSwi_sVoltState.boSwitchOn[1]               =   FALSE	
/// \output CtrlSwi_sVoltState.boRemainOn[1]               =   TRUE	
/// \output CtrlSwi_sVoltState.boDiagEnabled               =   FALSE
/// \output Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 1u
/// \output Rte_Read_CddSwi_SwitchStatus_HitCount,         = 1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eLow1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
  CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad = 1u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;


  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[0], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[1], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[1], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SwitchStatus_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_5()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1					 = SysVolt_eUnknown;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;;
/// \input 	CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad					 = 1u;
/// \input 	LPTMR0_GetTimeElapsed_HitCount									 = 0u;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount					 = 0u;
/// \input 	Rte_Read_CddSwi_SwitchStatus_HitCount							 = 0u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
/// \output CtrlSwi_sVoltState.boSwitchOn[0] = FALSE
/// \output CtrlSwi_sVoltState.boRemainOn[0] = FALSE
/// \output CtrlSwi_sVoltState.boSwitchOn[1] = FALSE
/// \output CtrlSwi_sVoltState.boRemainOn[1] = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_5(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values 
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eUnknown;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;;
  CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad = 1u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[0], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boSwitchOn[1], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boRemainOn[1], FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_6()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1	= SysVolt_eHigh1;
/// \input CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad = 1u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eHigh1;
  CtrlSwi_aHssStatus.sSwitchStatus->ucErrOpenLoad = 1u;

  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_7()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1u;
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eHigh2;
/// \input ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eHigh2;
  ucFanLastOperatingVoltageRange = SysVolt_eHigh1;

  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_8()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: s
/// \input Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 0u;
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eHigh2;
/// \input LPTMR0_GetTimeElapsed_Param1 = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal = 0x80000000u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eHigh2;
  LPTMR0_GetTimeElapsed_Param1 = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0x80000000u;
  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_9()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
/// \input LPTMR0_GetTimeElapsed_Param1 = 0u;
/// \input LPTMR0_GetTimeElapsed_RetVal = 0x80000000u;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  LPTMR0_GetTimeElapsed_Param1 = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0x80000000u;
  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_ReadRTEPorts_TestCase_10()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
/// \input ucFanLastOperatingVoltageRange = SysVolt_eLow1;
/// - Expectations:
/// \output CtrlSwi_sVoltState.boDiagEnabled = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_ReadRTEPorts_TestCase_10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  ucFanLastOperatingVoltageRange = SysVolt_eLow1;
  //Step 3) Call FUT
  CtrlSwi_ReadRTEPorts();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sVoltState.boDiagEnabled, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_ReadRTEPorts
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function reads RTE - Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ReadRTEPorts(void)
{
  Mt_CtrlSwi_ReadRTEPorts_TestCase_1();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_2();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_3();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_4();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_5();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_6();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_7();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_8();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_9();
  Mt_CtrlSwi_ReadRTEPorts_TestCase_10();
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_Cycle0_TestCase1()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus				 = TRUE;
/// input 	CtrlSwi_sState.aboHssAvailable[2u]			 = TRUE;
/// input 	CtrlSwi_Diag_CheckAllErrors_Param1			 = 2u;
/// input 	CtrlSwi_Diag_CheckAllErrors_Param2			 = FALSE;
/// input 	CtrlSwi_Diag_CheckAllErrors_Param3			 = TRUE;
/// input 	CtrlSwi_sVoltState.boDiagEnabled			 = FALSE;
/// input 	CtrlSwi_CheckExternalTakeover_Param1		 = 2u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eUnknown;
/// input 	CtrlSwi_sDiagControl.teMode[2u]				 = eDiagCtrl_CtrlSwi_Disabled;
/// input 	CtrlSwi_OperateOutputWithVoltState_Param1	 = 0u;
/// input 	CtrlSwi_aboAppMTargetState[0u]				 = FALSE;
/// input 	CtrlSwi_sState.aboHssTargetState[2u]		 = FALSE;
/// input 	CtrlSwi_aboAppMTargetState[2u]				 = FALSE;
/// input 	CtrlSwi_sState.aboHssPreviousState[2u]		 = FALSE;
/// input 	CtrlSwi_sVoltState.boRemainOn[2u]			 = FALSE;
/// input 	CtrlSwi_ucDelayErrorDetectionTimer[2u]		 = 0u;
/// input 	CtrlSwi_Diag_CheckShort2GndDuringOn_Param1	 = 0u;
/// input 	CtrlSwi_aSwitchStatus[0u].ucErrShort2GND	 = CTRLSWI_CFG_HSS_SNA;
/// input 	Rte_Write_CtrlSwi_HssStatus_HitCount		 = 0u;
/// - Expectations:
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 1u,           
/// \output	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 1u,     
/// \output	Rte_Read_CddSwi_SwitchStatus_HitCount = 1u,              
/// \output	CtrlSwi_sState.aboHssTargetState[2u] = FALSE,            
/// \output	CtrlSwi_sState.aboHssStateChangedDiagDisabled[2u] = FALSE
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  CtrlSwi_sState.aboHssAvailable[2u] = TRUE;
  CtrlSwi_Diag_CheckAllErrors_Param1 = 2u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = FALSE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = TRUE;
  CtrlSwi_sVoltState.boDiagEnabled = FALSE;
  CtrlSwi_CheckExternalTakeover_Param1 = 2u;
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 2u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eUnknown;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
  CtrlSwi_sDiagControl.teMode[2u] = eDiagCtrl_CtrlSwi_Disabled;
  CtrlSwi_OperateOutputWithVoltState_Param1 = 2u;
  CtrlSwi_aboAppMTargetState[2u] = FALSE;
  CtrlSwi_sState.aboHssTargetState[2u] = FALSE;
  CtrlSwi_aboAppMTargetState[2u] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[2u] = FALSE;
  CtrlSwi_CheckDelayErrorDetectionTimer_Param1 = 2u;
  CtrlSwi_SwitchOutput_Param1 = 2u;
  CtrlSwi_SwitchOutput_Param2 = FALSE;
  CtrlSwi_sState.aboHssActualState[2u] = TRUE;
  CtrlSwi_ucDelayErrorDetectionTimer[2u] = 1u;
  CtrlSwi_sVoltState.boRemainOn[2u] = FALSE;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SwitchStatus_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[2u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssStateChangedDiagDisabled[2u], FALSE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_2()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 5u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// -Expectations
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 5u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value

  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :   Mt_CtrlSwi_Cycle0_TestCase_3()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_sState.boEftCrcStatus				   = FALSE;
/// \input 	NvmBlockDeltaPwmPara.eNVM_Function_STT = eOptionSTT_Present;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// \input Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 12u;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_On;
/// - Expectations:
///	
/// \output CtrlSwi_aSwitchStatus[0u].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// \output CtrlSwi_aSwitchStatus[0u].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA, =
/// \output CtrlSwi_aSwitchStatus[0u].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// \output CtrlSwi_aSwitchStatus[0u].ucHwState = CTRLSWI_CFG_HSS_NOSUPPORT,
/// \output CtrlSwi_aSwitchStatus[0u].unActCurrent =             0u
/// \output CtrlSwi_aSwitchStatus[0u].unActVal =                 0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = FALSE;
  NvmBlockDeltaPwmPara.eNVM_Function_STT = eOptionSTT_Present;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 12u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_On;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[0u].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[0u].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[0u].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[0u].ucHwState, CTRLSWI_CFG_HSS_NOSUPPORT, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[0u].unActCurrent, 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[0u].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Cycle0_TestCase_4()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_sState.boEftCrcStatus = FALSE;
/// \input 	NvmBlockDeltaPwmPara.eNVM_Function_STT = eOptionSTT_Present;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = TRUE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input   Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// \input  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 12u
/// \input 	Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
/// \input 	Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_4_1;
/// - Expectations:
///	
/// \output CtrlSwi_sState.aulHssStatisticOnTime[2u]        =      1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_4(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = FALSE;
  NvmBlockDeltaPwmPara.eNVM_Function_STT = eOptionSTT_Present;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 12u;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_4_1;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value	
  AL_UNITTEST_CHECK(CtrlSwi_sState.aulHssStatisticOnTime[2u], 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Cycle0_TestCase_5()
///
///  \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// \input 	CtrlSwi_sState.boEftCrcStatus						    = TRUE;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// \input Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 12u;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
/// \input 	CtrlSwi_sState.aboHssPreviousState[2] = FALSE;
/// \input 	Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1;
/// \input 	CtrlSwi_sVoltState.boSwitchOn[2] = TRUE;
/// \input 	CtrlSwi_sState.aboHssSwitchOnDelay[2] = FALSE;
/// \input 	CtrlSwi_sState.aboHssShort2GNDDetected[2] = FALSE;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
/// \input 	ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_HitCount = 0u;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
///  -Expectations:
/// \output  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 1u
/// \output  Rte_Read_Diag_TiScrollingTakeOver_HitCount = 1u
/// \output  Rte_Read_SysMon_StdLgtTi_Req_HitCount =			 1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 12u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
  CtrlSwi_sState.aboHssPreviousState[2] = FALSE;
  Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1;
  CtrlSwi_sVoltState.boSwitchOn[2] = TRUE;
  CtrlSwi_sState.aboHssSwitchOnDelay[2] = FALSE;
  CtrlSwi_sState.aboHssShort2GNDDetected[2] = FALSE;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
  Rte_Read_Diag_TiScrollingTakeOver_HitCount = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
  CtrlSwi_sErrState.ucErrShortToGnd[HSS3] = 1u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_ScrollingOn_Stat_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Diag_TiScrollingTakeOver_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_6()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input CtrlSwi_sState.boEftCrcStatus						    = TRUE;
/// \input Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// \input Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
/// \input CtrlSwi_sState.aboHssPreviousState[1] = FALSE;
/// \input Rte_Read_CpmHssTarget0_sSetting_Param1.aeSetting[1] = 1;
/// \input CtrlSwi_sVoltState.boSwitchOn[1] = TRUE;
/// \input Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
/// \input ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
///  -Expectations:
/// \output  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 1u,
/// \output  Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount = 1u,
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
  CtrlSwi_sState.aboHssPreviousState[1] = FALSE;
  Rte_Read_CpmHssTarget0_sSetting_Param1.aeSetting[1] = 1;
  CtrlSwi_sVoltState.boSwitchOn[1] = TRUE;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  ucFanLastOperatingVoltageRange = SysVolt_eHigh1;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssTargetState[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_aboCddSwiTarget[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboHssActualState[1u], TRUE, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Cycle0_TestCase_7()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	CtrlSwi_sState.boEftCrcStatus						    = TRUE;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
/// \input 	CtrlSwi_sState.aboHssPreviousState[2] = FALSE;
/// \input 	Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1;
/// \input 	CtrlSwi_sVoltState.boSwitchOn[2] = TRUE;
/// \input 	CtrlSwi_sState.aboHssSwitchOnDelay[2] = FALSE;
/// \input 	CtrlSwi_sState.aboHssShort2GNDDetected[2] = FALSE;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
/// \input 	ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_HitCount = 0u;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
/// - Expectations:
/// \output  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 1u
/// \output  Rte_Read_Diag_TiScrollingTakeOver_HitCount = 1u
/// \output  Rte_Read_SysMon_StdLgtTi_Req_HitCount =			 1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[0].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
  CtrlSwi_sState.aboHssPreviousState[2] = FALSE;
  Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1;
  CtrlSwi_sVoltState.boSwitchOn[2] = TRUE;
  CtrlSwi_sState.aboHssSwitchOnDelay[2] = FALSE;
  CtrlSwi_sState.aboHssShort2GNDDetected[2] = FALSE;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
  Rte_Read_Diag_TiScrollingTakeOver_HitCount = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
  Rte_Read_CpmHssTarget0_sSetting_Param1.aeSetting[0] =1u;
  Rte_Read_CpmHssTarget0_sSetting_Param1.aeSetting[1] = 1u;
  CtrlSwi_sErrState.ucErrShortToVbat[2] = 1u;
  CtrlSwi_sErrState.ucErrShortToGnd[0] = 1u;
  CtrlSwi_sErrState.ucErrShortToGnd[1] = 1u;
  CtrlSwi_sErrState.ucErrShortToGnd[2] = 1u;
  CtrlSwi_sErrState.ucErrOpenLoad[2] = 1u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_ScrollingOn_Stat_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_Diag_TiScrollingTakeOver_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_8()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[1u] = 5u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_8(void)
{
    //Step 1) Set pre - conditions
    //Step 2) Assign Input values
    CtrlSwi_sState.boEftCrcStatus = TRUE;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
    Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
    Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[1u] = 5u;
    Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
    Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
    Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
    Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

    //Step 3) Call FUT
    CtrlSwi_Cycle0();

    //Step 4) Check expected output value

    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_9()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 5u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_SNA;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_9(void)
{
    //Step 1) Set pre - conditions
    //Step 2) Assign Input values
    CtrlSwi_sState.boEftCrcStatus = TRUE;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
    Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
    Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 5u;
    Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_SNA;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
    Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
    Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
    Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

    //Step 3) Call FUT
    CtrlSwi_Cycle0();

    //Step 4) Check expected output value

    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_10()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 5u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = eScrollingTI_Off;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_10(void)
{
    //Step 1) Set pre - conditions
    //Step 2) Assign Input values
    CtrlSwi_sState.boEftCrcStatus = TRUE;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
    Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
    Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 5u;
    Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
    Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
    Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
    Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

    //Step 3) Call FUT
    CtrlSwi_Cycle0();

    //Step 4) Check expected output value

    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
    AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_11()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 1u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = TRUE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 1u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = TRUE;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value

  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_12()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 2u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = TRUE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_12(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = TRUE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 2u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = TRUE;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value

  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_13()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 1u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_13(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 1u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value

  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :       Mt_CtrlSwi_Cycle0_TestCase_14()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// input 	CtrlSwi_sState.boEftCrcStatus = TRUE;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
/// input 	Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 2u;
/// input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
/// input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
/// input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
/// input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// input 	Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
/// - Expectations:
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA, 
/// Output	CtrlSwi_aSwitchStatus[1].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA,  
/// Output	CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA,
/// Output	CtrlSwi_aSwitchStatus[1].unActCurrent = 0u
/// Output	CtrlSwi_aSwitchStatus[1].unActVal =	0u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_14(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2GND = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrOpenLoad = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].ucErrShort2VBAT = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[HSS3].unActVal = 1;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[1].ucHwState = 2u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
  Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = FALSE;
  Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 2u;
  Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling = 5;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value

  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2GND, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrOpenLoad, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].ucErrShort2VBAT, CTRLSWI_CFG_ERR_SNA, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActCurrent, 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_aSwitchStatus[1].unActVal, 0u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Cycle0_TestCase_15()
///
///  \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// \input 	CtrlSwi_sState.boEftCrcStatus						    = TRUE;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
/// \input Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 0u;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
/// \input 	CtrlSwi_sState.aboHssPreviousState[2] = FALSE;
/// \input 	Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1;
/// \input 	CtrlSwi_sVoltState.boSwitchOn[2] = TRUE;
/// \input 	CtrlSwi_sState.aboHssSwitchOnDelay[2] = FALSE;
/// \input 	CtrlSwi_sState.aboHssShort2GNDDetected[2] = FALSE;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
/// \input 	ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_HitCount = 0u;
/// \input 	Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
///  -Expectations:
/// \output  Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 1u
/// \output  Rte_Read_Diag_TiScrollingTakeOver_HitCount = 1u
/// \output  Rte_Read_SysMon_StdLgtTi_Req_HitCount =			 1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_15(void)
{
    //Step 1) Set pre - conditions
    //Step 2) Assign Input values
    CtrlSwi_sState.boEftCrcStatus = TRUE;
    Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus[2].ucHwState = 2u;
    Rte_Read_Diag_TiScrollingTakeOver_Param1 = FALSE;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat = TRUE;
    Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
    Rte_Read_AnimaScrollingActivation_Param1.boPriorityScr = TRUE;
    Rte_Read_AnimaScrollingActivation_Param1.unTgtAniScr[0u] = 0u;
    Rte_Read_SysMon_StdLgtTi_Req_Param1.eSigQty = SIG_INVALID;
    CtrlSwi_sState.aboHssPreviousState[2] = FALSE;
    Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1.unDutyHSS3 = 1;
    CtrlSwi_sVoltState.boSwitchOn[2] = TRUE;
    CtrlSwi_sState.aboHssSwitchOnDelay[2] = FALSE;
    CtrlSwi_sState.aboHssShort2GNDDetected[2] = FALSE;
    Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
    ucFanLastOperatingVoltageRange = SysVolt_eHigh1;
    Rte_Read_CddSwi_ScrollingOn_Stat_HitCount = 0u;
    Rte_Read_Diag_TiScrollingTakeOver_HitCount = 0u;
    Rte_Read_SysMon_StdLgtTi_Req_HitCount = 0u;
    CtrlSwi_sErrState.ucErrShortToGnd[HSS3] = 1u;

    //Step 3) Call FUT
    CtrlSwi_Cycle0();

    //Step 4) Check expected output value
    AL_UNITTEST_CHECK(Rte_Read_CddSwi_ScrollingOn_Stat_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_Diag_TiScrollingTakeOver_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount, 1u, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Cycle0_TestCase_16()
///
///  \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject :  Diag routine takeover when scrolling is set to 50%
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat  = TRUE;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1                           = TRUE;
/// \input 	Rte_Read_Diag_Scrolling_TgtValue_Param1                            = eRte_eScrollingTgt_On_Scrolling_Off;
///
///  -Expectations:
/// \output  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1 = eRte_eScrollingSatelite_On_Scrolling_Off
///
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_16(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat  = TRUE;
  Rte_Read_Diag_TiScrollingTakeOver_Param1                           = TRUE;
  Rte_Read_Diag_Scrolling_TgtValue_Param1                            = eRte_eScrollingTgt_On_Scrolling_Off;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1, eRte_eScrollingSatelite_On_Scrolling_Off, == );
}

// ---------------------------------------------------------------------------- -
/// \Test Case :      Mt_CtrlSwi_Cycle0_TestCase_17()
///
///  \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : Diag routine takeover when scrolling is set to 100%
///
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
/// \input 	Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat  = TRUE;
/// \input 	Rte_Read_Diag_TiScrollingTakeOver_Param1                           = TRUE;
/// \input 	Rte_Read_Diag_Scrolling_TgtValue_Param1                            = eRte_eScrollingTgt_On_Scrolling_On;
///
///  -Expectations:
/// \output  Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1 = eRte_eScrollingSatelite_On_Scrolling_On
///
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_Cycle0_TestCase_17(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingDRLPresent_Stat = FALSE;
  Rte_Read_CddSwi_ScrollingOn_Stat_Param1.boScrollingTIPresent_Stat  = TRUE;
  Rte_Read_Diag_TiScrollingTakeOver_Param1                           = TRUE;
  Rte_Read_Diag_Scrolling_TgtValue_Param1                            = eRte_eScrollingTgt_On_Scrolling_On;

  //Step 3) Call FUT
  CtrlSwi_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1, eRte_eScrollingSatelite_On_Scrolling_On, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  CtrlSwi_Cycle() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Cycle0(void)
{
  Mt_CtrlSwi_Cycle0_TestCase_1();
  Mt_CtrlSwi_Cycle0_TestCase_2();
  Mt_CtrlSwi_Cycle0_TestCase_3();
  Mt_CtrlSwi_Cycle0_TestCase_4();
  Mt_CtrlSwi_Cycle0_TestCase_5();
  Mt_CtrlSwi_Cycle0_TestCase_6();
  Mt_CtrlSwi_Cycle0_TestCase_7();
  Mt_CtrlSwi_Cycle0_TestCase_8();
  Mt_CtrlSwi_Cycle0_TestCase_9();
  Mt_CtrlSwi_Cycle0_TestCase_10();
  Mt_CtrlSwi_Cycle0_TestCase_11();
  Mt_CtrlSwi_Cycle0_TestCase_12();
  Mt_CtrlSwi_Cycle0_TestCase_13();
  Mt_CtrlSwi_Cycle0_TestCase_14();
  Mt_CtrlSwi_Cycle0_TestCase_15();
  Mt_CtrlSwi_Cycle0_TestCase_16();
  Mt_CtrlSwi_Cycle0_TestCase_17();
}

// ---------------------------------------------------------------------------- -
/// \Test Case :     Mt_CtrlSwi_rpCtrlSwi10ms()
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///
///   - Test subject : rpCtrlSwi10ms() reads RTE - Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
/// 
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
/// \input 	Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_1;
/// \input 	Rte_Read_SigPrep_ElecSupState_Param1.eSigQty   = SIG_VALID;
/// \input 	CtrlSwi_sState.boEftCrcStatus				   = TRUE;
/// \input 	CtrlSwi_sState.aboHssAvailable[2u]			   = TRUE;
/// \input 	CtrlSwi_Diag_CheckAllErrors_Param1			   = 2u;
/// \input 	CtrlSwi_Diag_CheckAllErrors_Param2			   = FALSE;
/// \input 	CtrlSwi_Diag_CheckAllErrors_Param3			   = TRUE;
/// \input 	CtrlSwi_sVoltState.boDiagEnabled			   = FALSE;
/// \input 	CtrlSwi_CheckExternalTakeover_Param1		   = 2u;
/// \input 	CtrlSwi_CheckDelaySwitchOnTimer_Param1		   = 2u;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1   = SysVolt_eNormal;
/// \input 	Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
/// \input 	Rte_Read_CddSwi_SwitchStatus_HitCount		   = 0u;
/// \input 	Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;	
/// \input 	CtrlSwi_sDiagControl.teMode[2u]				   = eDiagCtrl_CtrlSwi_Disabled;
/// \input 	CtrlSwi_OperateOutputWithVoltState_Param1	   = 2u;
/// \input 	CtrlSwi_aboAppMTargetState[2u]				   = TRUE;
/// \input 	CtrlSwi_sState.aboHssTargetState[2u]		   = TRUE;
/// \input 	CtrlSwi_sState.aboHssShort2GNDDetected[2u]     = TRUE;
/// \input 	CtrlSwi_sState.aboPreTargestState[2u]		   = FALSE;
/// \input 	CtrlSwi_sState.aboHssPreviousState[2u]		   = FALSE;
/// \input 	CtrlSwi_CheckDelayErrorDetectionTimer_Param1   = 2u;
/// \input 	CtrlSwi_SwitchOutput_Param1					   = 2u;
/// \input 	CtrlSwi_SwitchOutput_Param2					   = TRUE;
/// \input 	CtrlSwi_sState.aboHssActualState[2u]		   = TRUE;
/// \input 	CtrlSwi_ucDelayErrorDetectionTimer[2u]		   = 1u;
/// \input 	CtrlSwi_sVoltState.boRemainOn[2u]			   = FALSE;
/// \input 	Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount       = 0u;
/// \input 	CtrlSwi_UpdateSwitchOnTimeCounter_Param1	   = 2u;
/// - Expectations:
/// \output Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount        =      1u
/// \output Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount  =      1u
/// \output Rte_Read_CddSwi_SwitchStatus_HitCount           =      1u
// ---------------------------------------------------------------------------- -
void Mt_CtrlSwi_rpCtrlSwiCycle0ms(void)
{
  //Step 1) Set pre - conditions
    //Step 2) Assign Input values
  Rte_Read_SigPrep_ElecSupState_Param1.eElectrSupplyState = eEtatFee_1_1;
  Rte_Read_SigPrep_ElecSupState_Param1.eSigQty = SIG_VALID;
  CtrlSwi_sState.boEftCrcStatus = TRUE;
  CtrlSwi_sState.aboHssAvailable[2u] = TRUE;
  CtrlSwi_Diag_CheckAllErrors_Param1 = 2u;
  CtrlSwi_Diag_CheckAllErrors_Param2 = FALSE;
  CtrlSwi_Diag_CheckAllErrors_Param3 = TRUE;
  CtrlSwi_sVoltState.boDiagEnabled = FALSE;
  CtrlSwi_CheckExternalTakeover_Param1 = 2u;
  CtrlSwi_CheckDelaySwitchOnTimer_Param1 = 2u;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1 = SysVolt_eNormal;
  Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_HitCount = 0u;
  Rte_Read_CddSwi_SwitchStatus_Param1.sSwitchStatus->ucErrOpenLoad = 1u;
  CtrlSwi_sDiagControl.teMode[2u] = eDiagCtrl_CtrlSwi_Disabled;
  CtrlSwi_OperateOutputWithVoltState_Param1 = 2u;
  CtrlSwi_aboAppMTargetState[2u] = TRUE;
  CtrlSwi_sState.aboHssTargetState[2u] = TRUE;
  CtrlSwi_sState.aboHssShort2GNDDetected[2u] = TRUE;
  CtrlSwi_sState.aboPreTargestState[2u] = FALSE;
  CtrlSwi_sState.aboHssPreviousState[2u] = FALSE;
  CtrlSwi_CheckDelayErrorDetectionTimer_Param1 = 2u;
  CtrlSwi_SwitchOutput_Param1 = 2u;
  CtrlSwi_SwitchOutput_Param2 = TRUE;
  CtrlSwi_sState.aboHssActualState[2u] = TRUE;
  CtrlSwi_ucDelayErrorDetectionTimer[2u] = 1u;
  CtrlSwi_sVoltState.boRemainOn[2u] = FALSE;
  Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount = 0u;
  CtrlSwi_UpdateSwitchOnTimeCounter_Param1 = 2u;

  //Step 3) Call FUT
  rpCtrlSwiCycle0();

  //Step 4) Check expected output value	
  AL_UNITTEST_CHECK(Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CddSwi_SwitchStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_HandleLSSErrors_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_aSwitchStatus[3].ucErrShort2GND = TRUE;
/// \input CtrlSwi_aSwitchStatus[3].ucErrShort2VBAT = TRUE;
///
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = OUTFCT_GPIO_TI_SC_BAT,
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED,
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleLSSErrors_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[3].ucErrShort2GND = TRUE;
  CtrlSwi_aSwitchStatus[3].ucErrShort2VBAT = TRUE;

  //Step 3) Call FUT
  CtrlSwi_HandleLSSErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, OUTFCT_GPIO_TI_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_HandleLSSErrors_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_aSwitchStatus[3].ucErrShort2GND = FALSE;
/// \input CtrlSwi_aSwitchStatus[3].ucErrShort2VBAT = FALSE;
/// - Expectations:
///
/// \output Dem_SetEventStatus_Param1 = OUTFCT_GPIO_TI_SC_BAT, 
/// \output Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleLSSErrors_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_aSwitchStatus[3].ucErrShort2GND = FALSE;
  CtrlSwi_aSwitchStatus[3].ucErrShort2VBAT = FALSE;

  //Step 3) Call FUT
  CtrlSwi_HandleLSSErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, OUTFCT_GPIO_TI_SC_BAT, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_HandleLSSErrors
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleLSSErrors(void)
{
  Mt_CtrlSwi_HandleLSSErrors_TestCase_1();
  Mt_CtrlSwi_HandleLSSErrors_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrorTimers_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Checks the timer status: start, running or reset the timer init values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ErrorTimers_Param3 = 1;
/// \input CtrlSwi_ErrorTimers_Param1 = TRUE;
/// \input CtrlSwi_ErrorTimers_Param2 = 15u;
///
/// - Expectations:
///
/// \output CtrlSwi_ErrorTimers_RetVal   = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrorTimers_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ErrorTimers_Param3 = 1;
  CtrlSwi_ErrorTimers_Param1 = TRUE;
  CtrlSwi_ErrorTimers_Param2 = 15u;

  //Step 3) Call FUT
  CtrlSwi_ErrorTimers_RetVal = CtrlSwi_ErrorTimers(CtrlSwi_ErrorTimers_Param1, CtrlSwi_ErrorTimers_Param2, CtrlSwi_ErrorTimers_Param3);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_ErrorTimers_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrorTimers_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Checks the timer status: start, running or reset the timer init values
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ErrorTimers_Param3 = 4;
/// \input CtrlSwi_ErrorTimers_Param1 = TRUE;
/// \input CtrlSwi_ErrorTimers_Param2 = 15u;
/// - Expectations:
///
/// \output CtrlSwi_ErrorTimers_RetVal   = 0xFFu
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrorTimers_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ErrorTimers_Param3 = 4;
  CtrlSwi_ErrorTimers_Param1 = TRUE;
  CtrlSwi_ErrorTimers_Param2 = 15u;

  //Step 3) Call FUT
  CtrlSwi_ErrorTimers_RetVal = CtrlSwi_ErrorTimers(CtrlSwi_ErrorTimers_Param1, CtrlSwi_ErrorTimers_Param2, CtrlSwi_ErrorTimers_Param3);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_ErrorTimers_RetVal, 0xFFu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_ErrorTimers
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Checks the timer status: start, running or reset the timer init values
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrorTimers(void)
{
  Mt_CtrlSwi_ErrorTimers_TestCase_1();
  Mt_CtrlSwi_ErrorTimers_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_HandleMaturationTime_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: This function return TimeOut = TRUE based on sTimersCfg Configurations
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  CtrlSwi_HandleMaturationTime_Param2 = 0;
/// \input  CtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boReq_Input = TRUE;
/// \input  CtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boStartStopTimer = FALSE;
/// - Expectations:
///
/// \output CtrlSwi_HandleMaturationTime_RetVal   = 0
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleMaturationTime_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  tsCtrlSwi_TimerCfg test = { 0 };
  CtrlSwi_HandleMaturationTime_Param1 = &test;
  //Step 2) Assign Input values
  CtrlSwi_HandleMaturationTime_Param2 = 0;
  CtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boReq_Input = TRUE;
  CtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boStartStopTimer = FALSE;

  //Step 3) Call FUT
  CtrlSwi_HandleMaturationTime_RetVal = CtrlSwi_HandleMaturationTime(&CtrlSwi_HandleMaturationTime_Param1, CtrlSwi_HandleMaturationTime_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_HandleMaturationTime_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_HandleMaturationTime_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: This function return TimeOut = TRUE based on sTimersCfg Configurations
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_HandleMaturationTime_Param1 = &test;
/// \input CtrlSwi_HandleMaturationTime_Param2 = 1;
///
/// - Expectations:
///
/// \output CtrlSwi_HandleMaturationTime_RetVal   = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleMaturationTime_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  tsCtrlSwi_TimerCfg test = { 0 };
  //Step 2) Assign Input values
  CtrlSwi_HandleMaturationTime_Param1 = &test;
  CtrlSwi_HandleMaturationTime_Param2 = 1;

  //Step 3) Call FUT
  CtrlSwi_HandleMaturationTime_RetVal = CtrlSwi_HandleMaturationTime(&CtrlSwi_HandleMaturationTime_Param1, CtrlSwi_HandleMaturationTime_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_HandleMaturationTime_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_HandleMaturationTime_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: This function return TimeOut = TRUE based on sTimersCfg Configurations
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \inputCtrlSwi_HandleMaturationTime_Param2 = 0;
/// \inputCtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boReq_Input = TRUE;
/// \inputCtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boStartStopTimer = TRUE;
/// \inputLPTMR0_GetTimeElapsed_RetVal = 1111u;
/// - Expectations:
///
/// \output CtrlSwi_HandleMaturationTime_RetVal   = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleMaturationTime_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  tsCtrlSwi_TimerCfg test = { 0 };
  CtrlSwi_HandleMaturationTime_Param1 = &test;
  //Step 2) Assign Input values
  CtrlSwi_HandleMaturationTime_Param2 = 0;
  CtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boReq_Input = TRUE;
  CtrlSwi_HandleMaturationTime_Param1[CtrlSwi_HandleMaturationTime_Param2].boStartStopTimer = TRUE;
  LPTMR0_GetTimeElapsed_RetVal = 1111u;

  //Step 3) Call FUT
  CtrlSwi_HandleMaturationTime_RetVal = CtrlSwi_HandleMaturationTime(&CtrlSwi_HandleMaturationTime_Param1, CtrlSwi_HandleMaturationTime_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_HandleMaturationTime_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_HandleMaturationTime
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function return TimeOut = TRUE based on sTimersCfg Configurations
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_HandleMaturationTime(void)
{
  Mt_CtrlSwi_HandleMaturationTime_TestCase_1();
  Mt_CtrlSwi_HandleMaturationTime_TestCase_2();
  Mt_CtrlSwi_HandleMaturationTime_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_CheckErrRetryTimer_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_CheckErrRetryTimer_Param1 = 1u;
/// \input CtrlSwi_sState.aunRetryTimer[CtrlSwi_CheckErrRetryTimer_Param1] = 1u;
/// - Expectations:
///
/// \output CtrlSwi_sState.aboRetryAllowed[1u] = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckErrRetryTimer_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_CheckErrRetryTimer_Param1 = 1u;
  CtrlSwi_sState.aunRetryTimer[CtrlSwi_CheckErrRetryTimer_Param1] = 1u;
  //Step 3) Call FUT
  CtrlSwi_CheckErrRetryTimer(CtrlSwi_CheckErrRetryTimer_Param1);
  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryAllowed[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_CheckErrRetryTimer_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_CheckErrRetryTimer_Param1 = 1u;
/// \input CtrlSwi_sState.aunRetryTimer[CtrlSwi_CheckErrRetryTimer_Param1] = 2u;
/// - Expectations:
///
/// \output CtrlSwi_sState.aunRetryTimer[1] = 1u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckErrRetryTimer_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_CheckErrRetryTimer_Param1 = 1u;
  CtrlSwi_sState.aunRetryTimer[CtrlSwi_CheckErrRetryTimer_Param1] = 2u;

  //Step 3) Call FUT
  CtrlSwi_CheckErrRetryTimer(CtrlSwi_CheckErrRetryTimer_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aunRetryTimer[1], 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_CheckErrRetryTimer
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_CheckErrRetryTimer(void)
{
  Mt_CtrlSwi_CheckErrRetryTimer_TestCase_1();
  Mt_CtrlSwi_CheckErrRetryTimer_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrRetryStatergy_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ErrRetryStatergy_Param1 = 1u;
/// \input CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
/// \input CtrlSwi_aboAppMTargetState[1u] = TRUE;
/// \input CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
/// \input CtrlSwi_sState.aucRetryCounter[1u] = 0u;
/// \input CtrlSwi_sState.aboRetryAllowed[1u] = TRUE;
/// - Expectations:
///
/// \output CtrlSwi_sState.aboRetryTarget[1u] = TRUE
/// \output CtrlSwi_sState.aucRetryCounter[1u] = 1u
/// \output CtrlSwi_sState.aboRetryAllowed[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ErrRetryStatergy_Param1 = 1u;
  CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
  CtrlSwi_aboAppMTargetState[1u] = TRUE;
  CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
  CtrlSwi_sState.aucRetryCounter[1u] = 0u;
  CtrlSwi_sState.aboRetryAllowed[1u] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_ErrRetryStatergy(CtrlSwi_ErrRetryStatergy_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryTarget[1u], TRUE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aucRetryCounter[1u], 1u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryAllowed[1u], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrRetryStatergy_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ErrRetryStatergy_Param1 = 1u;
/// \input CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
/// \input CtrlSwi_aboAppMTargetState[1u] = TRUE;
/// \input CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
/// \input CtrlSwi_sState.aucRetryCounter[1u] = 5u;
/// - Expectations:
///
/// \output CtrlSwi_sState.aboRetryTarget[1u] - FALSE
/// \output CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ErrRetryStatergy_Param1 = 1u;
  CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
  CtrlSwi_aboAppMTargetState[1u] = TRUE;
  CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
  CtrlSwi_sState.aucRetryCounter[1u] = 5u;

  //Step 3) Call FUT
  CtrlSwi_ErrRetryStatergy(CtrlSwi_ErrRetryStatergy_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboErrOffPermanent[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrRetryStatergy_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ErrRetryStatergy_Param1 = 1u;
/// \input CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
/// \input CtrlSwi_aboAppMTargetState[1u] = TRUE;
/// \input CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
/// \input CtrlSwi_sState.aucRetryCounter[1u] = 6u;
/// - Expectations:
///
/// \output CtrlSwi_sState.aunRetryTimer[1u] = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ErrRetryStatergy_Param1 = 1u;
  CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
  CtrlSwi_aboAppMTargetState[1u] = TRUE;
  CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
  CtrlSwi_sState.aucRetryCounter[1u] = 6u;

  //Step 3) Call FUT
  CtrlSwi_ErrRetryStatergy(CtrlSwi_ErrRetryStatergy_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aunRetryTimer[1u], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrRetryStatergy_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_ErrRetryStatergy_Param1 = 1u;
/// \input CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
/// \input CtrlSwi_aboAppMTargetState[1u] = TRUE;
/// \input CtrlSwi_sState.aboRetryStarted[1u] = FALSE;
/// - Expectations:
///
/// \output CtrlSwi_sState.aunRetryTimer[1u] = 0u
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  CtrlSwi_ErrRetryStatergy_Param1 = 1u;
  CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
  CtrlSwi_aboAppMTargetState[1u] = TRUE;
  CtrlSwi_sState.aboRetryStarted[1u] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_ErrRetryStatergy(CtrlSwi_ErrRetryStatergy_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aunRetryTimer[1u], 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwi_ErrRetryStatergy_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sState.aboRetryTarget[1u]  = TRUE;
/// \input CtrlSwi_sState.aucRetryCounter[1u] = 1u;
/// \input CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
/// \input CtrlSwi_sState.aboRetryAllowed[1u] = TRUE;
/// \input CtrlSwi_ErrRetryStatergy_Param1 = 1u;
/// \input CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
/// \input CtrlSwi_aboAppMTargetState[1u] = FALSE;
/// - Expectations:
///
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
/// \output CtrlSwi_sState.aucRetryCounter[1u] = 0u
/// \output CtrlSwi_sState.aboRetryStarted[1u] = FALSE
/// \output CtrlSwi_sState.aboRetryAllowed[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sState.aboRetryTarget[1u] = TRUE;
  CtrlSwi_sState.aucRetryCounter[1u] = 1u;
  CtrlSwi_sState.aboRetryStarted[1u] = TRUE;
  CtrlSwi_sState.aboRetryAllowed[1u] = TRUE;
  //Step 2) Assign Input values
  CtrlSwi_ErrRetryStatergy_Param1 = 1u;
  CtrlSwi_sState.aboErrOffPermanent[1u] = FALSE;
  CtrlSwi_aboAppMTargetState[1u] = FALSE;

  //Step 3) Call FUT
  CtrlSwi_ErrRetryStatergy(CtrlSwi_ErrRetryStatergy_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aucRetryCounter[1u], 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryStarted[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryAllowed[1u], FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CtrlSwtich_CtrlSwi_ErrRetryStatergy_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sState.aboRetryTarget[1u] = TRUE;
/// \input CtrlSwi_sState.aboRetryStarted[1u] = FALSE;
/// \input CtrlSwi_ErrRetryStatergy_Param1 = 1u;
/// \input CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE;
/// - Expectations:
///
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
/// \output CtrlSwi_sState.aboRetryStarted[1u] = TRUE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sState.aboRetryTarget[1u] = TRUE;
  CtrlSwi_sState.aboRetryStarted[1u] = FALSE;
  //Step 2) Assign Input values
  CtrlSwi_ErrRetryStatergy_Param1 = 1u;
  CtrlSwi_sState.aboErrOffPermanent[1u] = TRUE;

  //Step 3) Call FUT
  CtrlSwi_ErrRetryStatergy(CtrlSwi_ErrRetryStatergy_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryTarget[1u], FALSE, == );
  AL_UNITTEST_CHECK(CtrlSwi_sState.aboRetryStarted[1u], TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwi_ErrRetryStatergy
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check that the function to update the param2 values and other global
///                           variables which are used in this function
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_ErrRetryStatergy(void)
{
  Mt_CtrlSwi_ErrRetryStatergy_TestCase_1();
  Mt_CtrlSwi_ErrRetryStatergy_TestCase_2();
  Mt_CtrlSwi_ErrRetryStatergy_TestCase_3();
  Mt_CtrlSwi_ErrRetryStatergy_TestCase_4();
  Mt_CtrlSwi_ErrRetryStatergy_TestCase_5();
  Mt_CtrlSwi_ErrRetryStatergy_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case : CtrlSwi_Diag_CheckSmRgbErrors_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does the diagnostic for SM_RGB channel based on the inputs given from driver. The actual state is ON and a simulated Short to Gnd event is done
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u
/// \input CtrlSwi_aErrorDebounce[RGB_SM] = 30u
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_YES
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShortToVbat = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE
/// \input CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE
/// 
/// - Expectations:
///
/// \output CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 21u
/// \output CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// 
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u;
  CtrlSwi_aErrorDebounce[RGB_SM] = 30u;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE;
  CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE;

  //Step 2) Assign Input values
  // NA

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckSmRgbErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM], 21u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM], CTRLSWI_CFG_ERR_NO, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : CtrlSwi_Diag_CheckSmRgbErrors_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does the diagnostic for SM_RGB channel based on the inputs given from driver. The actual state is ON and a simulated Short to Gnd event disappear is done
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \input CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 21u
/// \input CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u
/// \input CtrlSwi_aErrorDebounce[RGB_SM] = 30u
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShortToVbat = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE
/// \input CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE
/// 
/// - Expectations:
///
/// \output CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u
/// \output CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 21u;
  CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u;
  CtrlSwi_aErrorDebounce[RGB_SM] = 30u;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE;
  CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE;

  //Step 2) Assign Input values
  // NA

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckSmRgbErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM], 20u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM], CTRLSWI_CFG_ERR_YES, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : CtrlSwi_Diag_CheckSmRgbErrors_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does the diagnostic for SM_RGB channel based on the inputs given from driver. The actual state is ON and a simulated Short to Gnd event is done and error is maturated
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 30u
/// \input CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u
/// \input CtrlSwi_aErrorDebounce[RGB_SM] = 30u
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_YES
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShortToVbat = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE
/// \input CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE
/// 
/// - Expectations:
///
/// \output CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 30u
/// \output CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 30u;
  CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u;
  CtrlSwi_aErrorDebounce[RGB_SM] = 30u;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE;
  CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE;

  //Step 2) Assign Input values
  // NA

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckSmRgbErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM], 30u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM], CTRLSWI_CFG_ERR_YES, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : CtrlSwi_Diag_CheckSmRgbErrors_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does the diagnostic for SM_RGB channel based on the inputs given from driver. The actual state is ON and a simulated Short to Gnd SNA event
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \input CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u
/// \input CtrlSwi_aErrorDebounce[RGB_SM] = 30u
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShortToVbat = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE
/// \input CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE
/// 
/// - Expectations:
///
/// \output CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u
/// \output CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u;
  CtrlSwi_aErrorDebounce[RGB_SM] = 30u;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE;
  CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE;

  //Step 2) Assign Input values
  // NA

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckSmRgbErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM], 20u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM], CTRLSWI_CFG_ERR_YES, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : CtrlSwi_Diag_CheckSmRgbErrors_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does the diagnostic for SM_RGB channel based on the inputs given from driver. The actual state is ON and a simulated Short to Gnd dissapear event
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \input CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u
/// \input CtrlSwi_aErrorDebounce[RGB_SM] = 30u
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShortToVbat = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE
/// \input CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE
/// 
/// - Expectations:
///
/// \output CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 19u
/// \output CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u;
  CtrlSwi_aErrorDebounce[RGB_SM] = 30u;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE;
  CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE;

  //Step 2) Assign Input values
  // NA

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckSmRgbErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM], 19u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM], CTRLSWI_CFG_ERR_YES, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : CtrlSwi_Diag_CheckSmRgbErrors_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function does the diagnostic for SM_RGB channel based on the inputs given from driver. The actual state is ON and a simulated Short to Gnd dissapear event and error totally cleared after debounce time
///                        
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES
/// \input CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 1u
/// \input CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u
/// \input CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u
/// \input CtrlSwi_aErrorDebounce[RGB_SM] = 30u
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_aSwitchStatus[RGB_SM].ucErrShortToVbat = CTRLSWI_CFG_ERR_NO
/// \input CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE
/// \input CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE
/// 
/// - Expectations:
///
/// \output CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 0u
/// \output CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_NO
/// \output CtrlSwi_sState.aboRetryTarget[1u] = FALSE
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_YES;
  CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 0u;
  CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 20u;
  CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 20u;
  CtrlSwi_aErrorDebounce[RGB_SM] = 30u;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2GND = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrOpenLoad = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_aSwitchStatus[RGB_SM].ucErrShort2VBAT = CTRLSWI_CFG_ERR_NO;
  CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] = FALSE;
  CtrlSwi_sState.aboHssActualState[RGB_SM] = TRUE;

  //Step 2) Assign Input values
  // NA

  //Step 3) Call FUT
  CtrlSwi_Diag_CheckSmRgbErrors();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM], 0u, == );
  AL_UNITTEST_CHECK(CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM], CTRLSWI_CFG_ERR_NO, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CtrlSwtich_CtrlSwi_ErrRetryStatergy
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CtrlSwi_Diag_CheckSmRgbError(void)
{
  Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_1();
  Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_2();
  Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_3();
  Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_4();
  Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_5();
  Mt_CtrlSwi_Diag_CheckSmRgbErrors_TestCase_6();
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
  ALUnitTest_AddFunction("Mt_CtrlSwi_OperateOutputWithVoltState",                              Mt_CtrlSwi_OperateOutputWithVoltState                             );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Cycle0",                                                  Mt_CtrlSwi_Cycle0                                                 );
  ALUnitTest_AddFunction("Mt_CtrlSwi_CheckExternalTakeover",                                   Mt_CtrlSwi_CheckExternalTakeover                                  );
  ALUnitTest_AddFunction("Mt_CtrlSwi_ReadRTEPorts",                                            Mt_CtrlSwi_ReadRTEPorts                                           );
  ALUnitTest_AddFunction("Mt_CtrlSwi_HandleMaturationTime",                                    Mt_CtrlSwi_HandleMaturationTime                                   );
  ALUnitTest_AddFunction("Mt_CtrlSwi_ParaFct0",                                                Mt_CtrlSwi_ParaFct0                                               );
  ALUnitTest_AddFunction("Mt_CtrlSwi_RteAccess_MapParams",                                     Mt_CtrlSwi_RteAccess_MapParams                                    );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Get_ETAT_FEE",                                            Mt_CtrlSwi_Get_ETAT_FEE                                           );
  ALUnitTest_AddFunction("Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop",                  Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop                 );
  ALUnitTest_AddFunction("Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start",                 Mt_CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start                );
  ALUnitTest_AddFunction("Mt_CtrlSwi_CheckDelaySwitchOnTimer",                                 Mt_CtrlSwi_CheckDelaySwitchOnTimer                                );
  ALUnitTest_AddFunction("Mt_CtrlSwi_CheckDelayErrorDetectionTimer",                           Mt_CtrlSwi_CheckDelayErrorDetectionTimer                          );
  ALUnitTest_AddFunction("Mt_CtrlSwi_SwitchOutput",                                            Mt_CtrlSwi_SwitchOutput                                           );
  ALUnitTest_AddFunction("Mt_CtrlSwi_OpenLoadHandlingFans",                                    Mt_CtrlSwi_OpenLoadHandlingFans                                   );
  ALUnitTest_AddFunction("Mt_CtrlSwi_UpdateSh2VbatFlag",                                       Mt_CtrlSwi_UpdateSh2VbatFlag                                      );
  ALUnitTest_AddFunction("Mt_CtrlSwi_UpdateSh2GndFlag",                                        Mt_CtrlSwi_UpdateSh2GndFlag                                       );
  ALUnitTest_AddFunction("Mt_CtrlSwi_UpdateOpenLoadFlag",                                      Mt_CtrlSwi_UpdateOpenLoadFlag                                     );
  ALUnitTest_AddFunction("Mt_CtrlSwi_UpdateSwitchOnTimeCounter",                               Mt_CtrlSwi_UpdateSwitchOnTimeCounter                              );
  ALUnitTest_AddFunction("Mt_CtrlSwi_DTCHandling",                                             Mt_CtrlSwi_DTCHandling                                            );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Sh2GndHandlingFans",                                      Mt_CtrlSwi_Sh2GndHandlingFans                                     );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Sh2VbatHandlingFans",                                     Mt_CtrlSwi_Sh2VbatHandlingFans                                    );
  ALUnitTest_AddFunction("Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start",        Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start       );
  ALUnitTest_AddFunction("Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop",         Mt_CtrlSwi_roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop        );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Init",                                                    Mt_CtrlSwi_Init                                                   );
  ALUnitTest_AddFunction("Mt_CtrlSwi_DeInit",                                                  Mt_CtrlSwi_DeInit                                                 );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Diag_CheckAllErrors",                                     Mt_CtrlSwi_Diag_CheckAllErrors                                    );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Diag_CheckShort2GndDuringOn",                             Mt_CtrlSwi_Diag_CheckShort2GndDuringOn                            );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Diag_CheckOpenloadDuringOn",                              Mt_CtrlSwi_Diag_CheckOpenloadDuringOn                             );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff",                           Mt_CtrlSwi_Diag_CheckShort2VbatDuringOff                          );
  ALUnitTest_AddFunction("Mt_CtrlSwi_riCtrlSwiInit",                                           Mt_CtrlSwi_riCtrlSwiInit                                          );
  ALUnitTest_AddFunction("Mt_CtrlSwi_rpCtrlSwiCycle0ms",                                       Mt_CtrlSwi_rpCtrlSwiCycle0ms                                      );
  ALUnitTest_AddFunction("Mt_CtrlSwi_HandleLSSErrors",                                         Mt_CtrlSwi_HandleLSSErrors                                        );
  ALUnitTest_AddFunction("Mt_CtrlSwi_ErrorTimers",                                             Mt_CtrlSwi_ErrorTimers                                            );
  ALUnitTest_AddFunction("Mt_CtrlSwi_CheckErrRetryTimer",                                      Mt_CtrlSwi_CheckErrRetryTimer                                     );
  ALUnitTest_AddFunction("Mt_CtrlSwi_ErrRetryStatergy",                                        Mt_CtrlSwi_ErrRetryStatergy                                       );
  ALUnitTest_AddFunction("Mt_CtrlSwi_Diag_CheckSmRgbError",                                    Mt_CtrlSwi_Diag_CheckSmRgbError                                   );
}

// EOF
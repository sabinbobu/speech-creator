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
/// \brief    Module test for FctR
///   
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================


// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>
#include <string.h>

// Stub headers
#include "Test_Stubs.h"
#include "Test_Ext.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
// DATA TYPES TO SIMULATE CODING DATA
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \brief  Mt_Init_LmmABlock_And_CodingLmmX
///
/// \descr  Function needed to initialize the main structure from coding parameters
///         that FctR module is processing
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_Init_LmmABlock_And_CodingLmmX(void)
{
  //start coding with valid state
  FctR_ucCodingState = FCTR_CODING_VALID;

  // initialize the main coding structures
  FctR_pLmmABlock  = &Mt_init;
  FctR_pCodingArea = &Coding_Dummy;

  // 1) assign configuration to the light function (32 light functions)
  memcpy(FctR_pCodingArea->LmmA.row, &ConfigTable_LmmABlock_LghtFct_Ill_ROW[0], sizeof(ConfigTable_LmmABlock_LghtFct_Ill_ROW));

  // 2) create the configuration table (40 inputs of PWM, ramp, priority, failure and active bit)
  memcpy(FctR_pCodingArea->LmmX.Lut.cell, &ConfigTable[0], sizeof(ConfigTable));

  // 3) assign the configuration index to be selected for the light function
  memcpy(FctR_pLmmABlock->row, &ConfigTable_LmmABlock_LghtFct_Ill_ROW[0], sizeof(ConfigTable_LmmABlock_LghtFct_Ill_ROW));

}


//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
//  ctaaFctR.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riFctRInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable calls and executes
///                     the init function of FctR
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    FctR_TgtLgtReqPrep.Req.ulRaw = 0xFFFFu
///
///   - Expectations:
///
/// \output   FctR_TgtLgtReqPrep.Req.ulRaw = 0u
///
//-----------------------------------------------------------------------------
void Mt_riFctRInit(void)
{

  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgtReqPrep.Req.ulRaw = 0xFFFFu;

  //Step 3) Call FUT
  riFctRInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpFctR_Cycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls and executes
///                     the FctR_Cycle function and reads the illuminant state
///                     from the RTE and saves the error status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u
/// \input    Rte_Read_CtrlLed_ActLed_sState_Param1.uIlluminantState[14].bIllErr.bLedOC = 1u
/// \input    FctR_TgtLgtReq.Req.Bits.biHB_HighBeam = TRUE
///
///   - Expectations:
///
 /// \output   Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 1u
 /// \output   FctR_ActIlluminantStates[15].boIlFailureStatus = TRUE
 /// \output   FctR_ActIlluminantStates[15].unIlluminantErrState = 0b01000000
///
//-----------------------------------------------------------------------------
void Mt_rpFctR_Cycle(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_CtrlLed_ActLed_sState_Param1.uIlluminantState[14].bIllErr.bLedOC = 1u;
  FctR_TgtLgtReq.Req.Bits.biHB_HighBeam = TRUE;

  //Step 3) Call FUT
  rpFctR_Cycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(FctR_ActIlluminantStates[15].boIlFailureStatus,         TRUE, == );
  AL_UNITTEST_CHECK(FctR_ActIlluminantStates[15].unIlluminantErrState,      0b01000000, == );   // open circuit error
}


//-----------------------------------------------------------------------------
//  FctR.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test that the function reads the coding at start-up and 
///                    initializes the main variables for light function parameters
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    FctR_TgtLgtReqPrep.Req.ulRaw = 0xFFFFu
/// \input    FctR_eAimingMode = eBlinkOff
/// \input    Coding_State     = eParaFct0_CodingDataValid
/// \input    Rte_Read_CodM_FctR_Para_Param1.eCodingState = eParaFct0_CodingDataValid
/// \input    Rte_Read_CodM_FctR_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy
/// \input    Rte_Read_CodM_FctR_Para_Param1.psCodingParameters_Blocks->LmmA = Mt_init
/// \input    Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft
///
/// - Expectations: 
///
/// \output   FctR_ucCodingState                  = FCTR_CODING_VALID
/// \output   FctR_pLmmABlock                     = &FctR_pCodingArea->LmmA
/// \output   FctR_TgtLgtReqPrep.Req.ulRaw        = 0u
/// \output   FctR_ucTgtLgtSustained[15u]         = LF_INIT
/// \output   FctR_ucTgtLgtHighPrio[15u]          = LF_INIT
/// \output   FctR_ucTgtLgtHighPrioPrevious[15u]  = LF_INIT
/// \output   FctR_eAimingMode = eAimingOff
///
//-----------------------------------------------------------------------------
void Mt_FctR_Init(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgtReqPrep.Req.ulRaw = 0xFFFFu;
  FctR_eAimingMode = eBlinkOff;
  Coding_State = eParaFct0_CodingDataValid;
  Rte_Read_CodM_FctR_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_FctR_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  Rte_Read_CodM_FctR_Para_Param1.psCodingParameters_Blocks->LmmA = Mt_init;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft;

  //Step 3) Call FUT
  FctR_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_ucCodingState,                  FCTR_CODING_VALID, == );
  AL_UNITTEST_CHECK(FctR_pLmmABlock,               &FctR_pCodingArea->LmmA, == );
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw,                       0u, == );
  AL_UNITTEST_CHECK(FctR_ucTgtLgtSustained[15u],                   LF_INIT, == );
  AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrio[15u],                    LF_INIT, == );
  AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrioPrevious[15u],            LF_INIT, == );
  AL_UNITTEST_CHECK(FctR_eAimingMode,                           eAimingOff, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Cycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the cyclic function gets the light function requests 
///                     from diagnostic routine if activated
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Rte_Read_Diag_LdActivationRoutineControl_HitCount = 0u
/// \input    Rte_Read_CtrlLed_ActLed_sState_Param1.uIlluminantState[14].bIllErr.bLedOC = 1u
/// \input    FctR_TgtLgtReq.Req.Bits.biHB_HighBeam = TRUE
/// \input    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request   = ReqLighted_Off
/// \input    Rte_Read_SysMon_LowBeamCmd_Req_Param1               = ReqLighted_Off
/// \input    Rte_Read_SigPrep_StdLgtClSbl_Req_Param1.eCl_Request = ReqLighted_On
/// \input    Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode        = Afs_Country
/// \input    Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus = TRUE
/// \input    Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.Bits.biHB_HighBeam       = TRUE
/// \input    Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.Bits.biLB_CountryLight   = TRUE
/// \input    Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.Bits.biTI_TurnIndicator  = TRUE
///
///   - Expectations:
///
/// \output   Rte_Read_Diag_LdActivationRoutineControl_HitCount = FCTR_CFG_LOGLMP_MAX + 4u
/// \output   FctR_ActIlluminantStates[15].boIlFailureStatus    = TRUE
/// \output   FctR_ActIlluminantStates[15].unIlluminantErrState = 0b01000000
/// \output   FctR_eActLgtClSbl                                 = CL_CorneringLight
/// \output   FctR_ucClSblTargetState                           = FCTR_CFG_SBL_CL_NOMINAL
/// \output   FctR_TgtPrep_sAfsSignals.eAfsMode                 = Afs_Country
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biHB_HighBeam         = TRUE
///
//-----------------------------------------------------------------------------
void Mt_FctR_Cycle(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_Diag_LdActivationRoutineControl_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_CtrlLed_ActLed_sState_Param1.uIlluminantState[14].bIllErr.bLedOC = 1u;
  FctR_TgtLgtReq.Req.Bits.biHB_HighBeam = TRUE;

  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHb_Request   = ReqLighted_Off;
  Rte_Read_SysMon_LowBeamCmd_Req_Param1               = ReqLighted_Off;
  Rte_Read_SigPrep_StdLgtClSbl_Req_Param1.eCl_Request = ReqLighted_On;
  Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode        = Afs_Country;

  Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus = TRUE;
  Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.Bits.biHB_HighBeam       = TRUE;
  Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.Bits.biLB_CountryLight   = TRUE;
  Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.Bits.biTI_TurnIndicator  = TRUE;

  //Step 3) Call FUT
  FctR_Cycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_Diag_LdActivationRoutineControl_HitCount, FCTR_CFG_LOGLMP_MAX +  4u, == );   //  3 from FctR_TgtLgt_Output
  AL_UNITTEST_CHECK(FctR_ActIlluminantStates[15].boIlFailureStatus,                         TRUE, == );
  AL_UNITTEST_CHECK(FctR_ActIlluminantStates[15].unIlluminantErrState,                0b01000000, == );   // open circuit error
  AL_UNITTEST_CHECK(FctR_eActLgtClSbl,                                         CL_CorneringLight, == );
  AL_UNITTEST_CHECK(FctR_ucClSblTargetState,                             FCTR_CFG_SBL_CL_NOMINAL, == );
  AL_UNITTEST_CHECK(FctR_TgtPrep_sAfsSignals.eAfsMode,                               Afs_Country, == );
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biHB_HighBeam,                              TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_ParaFct0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the coding state and
///                        returns the validity of coding data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      FctR_ParaFct0_eCmd                         = eParaFct0_CodingDataValid
/// \input      FctR_ParaFct0_pData                         = &Coding_Dummy
/// \input      Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedLeft
/// \input      FctR_ucCodingState                           = FCTR_CODING_INVALID
/// \input      FctR_pCodingArea->LmmA.row[31u].cell[15u].ucIdx = 15u
///
/// - Expectations: 
///
/// \output   FctR_ucCodingState = FCTR_CODING_VALID
/// \output   FctR_pLmmABlock->row[31u].cell[15u].ucIdx = 15u
///
//-----------------------------------------------------------------------------
void Mt_FctR_ParaFct0_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_ParaFct0_eCmd = eParaFct0_CodingDataValid;
  FctR_ParaFct0_pData = &Coding_Dummy;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft;
  FctR_ucCodingState = FCTR_CODING_INVALID;
  FctR_pCodingArea->LmmA.row[31u].cell[15u].ucIdx = 15u;

  //Step 3) Call FUT
  FctR_ParaFct0(FctR_ParaFct0_eCmd, FctR_ParaFct0_pData);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_ucCodingState, FCTR_CODING_VALID, == );
  AL_UNITTEST_CHECK(FctR_pLmmABlock->row[31u].cell[15u].ucIdx, 15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_ParaFct0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function reads the coding state and
///                        returns the validity of coding data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      FctR_ParaFct0_eCmd                         = eParaFct0_CodingDataInvalid
/// \input      FctR_ParaFct0_pData                         = &Coding_Dummy
/// \input      Rte_Read_IoHwAbUser_GetMountingSide_Param1   = eMountedRight
/// \input      FctR_ucCodingState                           = FCTR_CODING_VALID
/// \input      FctR_pCodingArea->LmmA_B.row[31u].cell[15u].ucIdx = 255u
///
/// - Expectations: 
///
/// \output   FctR_ucCodingState = FCTR_CODING_INVALID
/// \output   FctR_pLmmABlock->row[31u].cell[15u].ucIdx = 255u
///
//-----------------------------------------------------------------------------
void Mt_FctR_ParaFct0_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_ParaFct0_eCmd = eParaFct0_CodingDataInvalid;
  FctR_ParaFct0_pData = &Coding_Dummy;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  FctR_ucCodingState = FCTR_CODING_VALID;
  FctR_pCodingArea->LmmA_B.row[31u].cell[15u].ucIdx = 255u;

  //Step 3) Call FUT
  FctR_ParaFct0(FctR_ParaFct0_eCmd, FctR_ParaFct0_pData);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_ucCodingState,          FCTR_CODING_INVALID, == );
  AL_UNITTEST_CHECK(FctR_pLmmABlock->row[31u].cell[15u].ucIdx, 255u,  == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_ParaFct0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Check that the function sets coding data to invalid
///                        for an undefined command status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      FctR_ParaFct0_eCmd                            = 3
/// \input      FctR_ParaFct0_pData                           = &Coding_Dummy
/// \input      Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight
/// \input      FctR_ucCodingState                            = FCTR_CODING_INVALID
///
/// - Expectations: 
///
/// \output   FctR_ucCodingState = FCTR_CODING_INVALID
///
//-----------------------------------------------------------------------------
void Mt_FctR_ParaFct0_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_ParaFct0_eCmd = 3;
  FctR_ParaFct0_pData = &Coding_Dummy;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  FctR_ucCodingState = FCTR_CODING_INVALID;

  //Step 3) Call FUT
  FctR_ParaFct0(FctR_ParaFct0_eCmd, FctR_ParaFct0_pData);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_ucCodingState, FCTR_CODING_INVALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that in init phase, the coding parameters validity
///                     is checked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_FctR_ParaFct0(void)
{
  Mt_FctR_ParaFct0_TestCase1();
  Mt_FctR_ParaFct0_TestCase2();
  Mt_FctR_ParaFct0_TestCase3();
}

//-----------------------------------------------------------------------------
//  FctR_RteAccess.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_MapAfsMode
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function does an internal mapping
///                         of the Afs Mode 
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eAfsMode_Input  : input data with  Afs mode
///
///   - Expectations:
///
/// \output  eAfsMode_Output   : internal mapping of Afs mode
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_MapAfsMode(void)
{

  struct { teRte_Ctrl_AFS eAfsMode_Input;  teFctR_AfsMode eAfsMode_Output;   }asTestCaseData[]
    = {  {              eCtrlAFS_AfsOff ,                 Afs_Off            },
         {              eCtrlAFS_Country ,                Afs_Country        },
         {              eCtrlAFS_Town ,                   Afs_Town           },
         {              eCtrlAFS_Motorway ,               Afs_Motorway       },
         {              eCtrlAFS_BadWeatherLhd ,          Afs_BadWeather_Lhd },
         {              eCtrlAFS_BadWeatherRhd ,          Afs_BadWeather_Rhd },
         {              eCtrlAFS_FoggyLhd ,               Afs_Foggy_Lhd      },
         {              eCtrlAFS_FoggyRhd ,               Afs_Foggy_Rhd      },
         {              eCtrlAFS_Invalid ,                Afs_Invalid        },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_RteAccess_MapAfsMode_RetVal = Afs_Off;
    FctR_RteAccess_MapAfsMode_eAfsMode = asTestCaseData[ucIdx].eAfsMode_Input;

    //Step 3) Call the FUT
    FctR_RteAccess_MapAfsMode_RetVal = FctR_RteAccess_MapAfsMode(FctR_RteAccess_MapAfsMode_eAfsMode);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_MapAfsMode_RetVal, asTestCaseData[ucIdx].eAfsMode_Output, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_MapGfHbSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function does an internal mapping
///                         of the GFHB (Glare free High Beam) command 
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eGfhbCmd_Input      : input data with  Gfhb command
///
///   - Expectations:
///
/// \output  eGfHbCmd_Output   : internal mapping of Gfhb command
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_MapGfHbSignals(void)
{

  struct { teRte_Ctrl_AFS eGfhbCmd_Input;  teFctR_AfsMode eGfHbCmd_Output; }asTestCaseData[]
    = {  {              eGfhbCmd_Off ,                 GfHb_Off            },
         {              eGfhbCmd_CurtainAct ,          Curtain_Activation  },
         {              eGfhbCmd_On ,                  GfHb_On             },
         {              eGfhbCmd_CurtainDeAct ,        Curtain_Deactivation},
         {                                 4U ,        GfHb_Off            },  //invalid mode
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_RteAccess_MapGfHbSignals_RetVal    = eGfhbCmd_Off;
    FctR_RteAccess_MapGfHbSignals_eGfHbCmd  = asTestCaseData[ucIdx].eGfhbCmd_Input;

    //Step 3) Call the FUT
    FctR_RteAccess_MapGfHbSignals_RetVal = FctR_RteAccess_MapGfHbSignals(FctR_RteAccess_MapGfHbSignals_eGfHbCmd);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_MapGfHbSignals_RetVal, asTestCaseData[ucIdx].eGfHbCmd_Output, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_MapTiStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the turn indicator status is mapped to
///                         internal type
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eTiStatus_Received   : input data of Etat Clignotant signal value
///
///   - Expectations:
///
/// \output  eTiStatus_Mapped   :  turn indicator active side mapped internally
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_MapTiStatus(void)
{

  struct { teRte_EtatClignotants eTiStatus_Received;  teFctR_TiStatus  eTiStatus_Mapped;  }asTestCaseData[]
    = {  {  eEtatClignotants_IndicatorInactive,                           Ti_Inactive     },
         {  eEtatClignotants_LeftIndicatorActive,                         Ti_ActiveLeft   },
         {  eEtatClignotants_RightIndicatorActive,                        Ti_ActiveRight  },
         {  eEtatClignotants_LeftAndRightIndicatorActive,                 Ti_ActiveBoth   },
         {  4U,                                                           Ti_Inactive     },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_RteAccess_MapTiStatus_RetVal     = Ti_Inactive;
    FctR_RteAccess_MapTiStatus_eTiStatus  = asTestCaseData[ucIdx].eTiStatus_Received;

    //Step 3) Call FUT
    FctR_RteAccess_MapTiStatus_RetVal = FctR_RteAccess_MapTiStatus(FctR_RteAccess_MapTiStatus_eTiStatus);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_MapTiStatus_RetVal,  asTestCaseData[ucIdx].eTiStatus_Mapped, == );
  }

}


//-----------------------------------------------------------------------------
// RTE Write 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Write_TgtLedsVal
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if target LED values are correctly written on
///                         the Rte port
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucIdx].unRampTime         = 0u
/// \input    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucIdx].unTgtIntensity     = 0u
/// \input    FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unRampTime     = ucIdx
/// \input    FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unTgtIntensity = ucIdx + 10u
///
/// - Expectations: 
///
/// \output   FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unRampTime     = ucIdx
/// \output   FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unTgtIntensity = ucIdx + 10u
/// \output   FctR_RteAccess_Write_TgtLedsVal_RetVal                                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Write_TgtLedsVal(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  for (uint8 ucIdx = 0u; ucIdx < CFG_LED_CHANNELS_NR; ucIdx++)
  {
    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucIdx].unRampTime         = 0u;
    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucIdx].unTgtIntensity     = 0u;
    FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unRampTime     = ucIdx;
    FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unTgtIntensity = ucIdx + 10u;
  }

  //Step 3) Call FUT
  FctR_RteAccess_Write_TgtLedsVal_RetVal = FctR_RteAccess_Write_TgtLedsVal(FctR_RteAccess_Write_TgtLedsVal_pData);

  //Step 4) Check expected output values
  for (uint8 ucIdx = 0u; ucIdx < CFG_LED_CHANNELS_NR; ucIdx++)
  {
    AL_UNITTEST_CHECK(FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unRampTime,            ucIdx, ==);
    AL_UNITTEST_CHECK(FctR_RteAccess_Write_TgtLedsVal_pData.asTgtLedVal[ucIdx].unTgtIntensity,  ucIdx + 10u, ==);
    AL_UNITTEST_CHECK(FctR_RteAccess_Write_TgtLedsVal_RetVal,                                            0u, ==);
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Write_LgtFctStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    Test that the light functions status is written 
///                       correctly on RTE port
///
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       ulLgtFctActive  : requested light functions
///
///   - Expectations:
///       boLb     :   active status of Lb   light function
///       boSbl    :   active status of Sbl  light function
///       boTi     :   active status of Ti   light function
///       boHb     :   active status of Hb   light function
///       boGfHb   :   active status of GfHb light function
///       boDrl    :   active status of Drl  light function
///       boPos    :   active status of Pos  light function
///       boFog    :   active status of Fog  light function
///       boSM     :   active status of SM   light function
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Write_LgtFctStatus(void)
{

  struct {
    uint32 ulLgtFctActive;  boolean boLb; boolean boSbl; boolean boTi; boolean boHb; boolean boGfHb; boolean boDrl; boolean boPos; boolean boFog; boolean boSM; } asTestCaseData[]
    =  {
         {        0x1FFu,           TRUE,         FALSE,        FALSE,        FALSE,           FALSE,         FALSE,        FALSE,          FALSE,       FALSE  },    // all LB functions active              /* 0b000000001u  */
         {      0x3E000u,          FALSE,         FALSE,        FALSE,         TRUE,            TRUE,         FALSE,        FALSE,          FALSE,       FALSE  },    // all HB functions active              /* 0b000011000u  */
         {   0x1FC00000u,          FALSE,          TRUE,        FALSE,        FALSE,           FALSE,          TRUE,         TRUE,           TRUE,        TRUE  },    // DRL_POS_SBL_CL_SM functions active   /* 0b111100010u  */
         {   0xE0000000u,          FALSE,         FALSE,         TRUE,        FALSE,           FALSE,         FALSE,        FALSE,          FALSE,       FALSE  },    // TI functions active                  /* 0b000000100u  */
       };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_RteAccess_Write_LgtFctStatus_uStatus.ulRaw = (uint32)0x00u;   //reset for each test case
    Rte_Write_FctR_LgtFctStatus_HitCount = 0u;

    //Step 2) Assign Input values
    FctR_RteAccess_Write_LgtFctStatus_uStatus.ulRaw = asTestCaseData[ucIdx].ulLgtFctActive;

    //Step 3) Call FUT
    FctR_RteAccess_Write_LgtFctStatus_RetVal = FctR_RteAccess_Write_LgtFctStatus(FctR_RteAccess_Write_LgtFctStatus_uStatus);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boLb_Status,       asTestCaseData[ucIdx].boLb,     == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boSbl_Status,      asTestCaseData[ucIdx].boSbl,    == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boTi_Status,       asTestCaseData[ucIdx].boTi,     == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boHb_Status,       asTestCaseData[ucIdx].boHb,     == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boGfHb_Status,     asTestCaseData[ucIdx].boGfHb,   == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boPos_Status,      asTestCaseData[ucIdx].boPos,    == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boFog_Status,      asTestCaseData[ucIdx].boFog,    == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boDrl_Status,      asTestCaseData[ucIdx].boDrl,    == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_Param1.boSM_Status,       asTestCaseData[ucIdx].boSM,     == );

    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctStatus_HitCount,                                         1u,     == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Write_TiWarningMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    Test the writing of Turn Indicator mode value on Rte port
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       eTiWarningMode_In  : TI warning mode input
///
///   - Expectations:
///       eWarningMode_Out   : TI warning mode status for RTE write
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Write_TiWarningMode(void)
{

  struct { teFctr_TiWarningMode eTiWarningMode_In;  teRte_WarningMode eWarningMode_Out;   } asTestCaseData[]
    =   { {                   WarningMode_Autonom,       eWarningMode_AutonomWarningMode  },
          {                   WarningMode_Piloted,       eWarningMode_PilotedWarningMode  },  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Write_FctR_TiWarningMode_HitCount = 0u;
    FctR_RteAccess_Write_TiWarningMode_eTiWarningMode = asTestCaseData[ucIdx].eTiWarningMode_In;

    //Step 3) Call FUT
    FctR_RteAccess_Write_TiWarningMode_RetVal = FctR_RteAccess_Write_TiWarningMode(FctR_RteAccess_Write_TiWarningMode_eTiWarningMode);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_FctR_TiWarningMode_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_TiWarningMode_Param1, asTestCaseData[ucIdx].eWarningMode_Out, == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Write_GfHbCmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that FctR writes correctly the GHFB command
///                        to upper module
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    Rte_Write_FctR_GfHbCmd_Param1         = eGfhbCmd_Off
/// \input    FctR_RteAccess_Write_GfHbCmd_eGfHbCmd = eGfhbCmd_On
///
/// - Expectations: 
///
/// \output   FctR_RteAccess_Write_GfHbCmd_RetVal  = 0u
/// \output   Rte_Write_FctR_GfHbCmd_Param1        = eGfhbCmd_On
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Write_GfHbCmd(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_FctR_GfHbCmd_Param1         = eGfhbCmd_Off;
  FctR_RteAccess_Write_GfHbCmd_eGfHbCmd = eGfhbCmd_On;

  //Step 3) Call FUT
  FctR_RteAccess_Write_GfHbCmd_RetVal = FctR_RteAccess_Write_GfHbCmd(FctR_RteAccess_Write_GfHbCmd_eGfHbCmd);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_RteAccess_Write_GfHbCmd_RetVal, 0u   , ==);
  AL_UNITTEST_CHECK(Rte_Write_FctR_GfHbCmd_Param1, eGfhbCmd_On, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Write_DblCmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if target dbl value is correctly written on Rte port
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    Rte_Write_FctR_AfsDblCmd_Param1.Primary  = 0u
/// \input    FctR_RteAccess_Write_DblCmd_eDblCmd      = STOP_DBL
///
/// - Expectations: 
///
/// \output   Rte_Write_FctR_AfsDblCmd_Param1.Primary = 3u
/// \output   FctR_RteAccess_Write_DblCmd_RetVal      = 0u
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Write_DblCmd(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_FctR_AfsDblCmd_Param1.Primary   = 0u;
  FctR_RteAccess_Write_DblCmd_eDblCmd       = STOP_DBL;

  //Step 3) Call FUT
  FctR_RteAccess_Write_DblCmd_RetVal = FctR_RteAccess_Write_DblCmd(FctR_RteAccess_Write_DblCmd_eDblCmd);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_FctR_AfsDblCmd_Param1.Primary, 3u, ==);
  AL_UNITTEST_CHECK(FctR_RteAccess_Write_DblCmd_RetVal ,     0u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Write_AfsMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the light function to be activated is
///                         correctly computed based on the light function request
///                         and Afs Mode received
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sClSblReq_Received      : input data of SBL and CL requests
///
///   - Expectations:
///
/// \output  boClReq             :  CL request value
/// \output  boSblReq            :  SBL request value
/// \output  boTimeoutDetected   :  confirmation of timeout detection
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Write_AfsMode(void)
{

  struct {  FctR_eAimingType eAimingMode; teFctR_AfsMode eAfsModeReceived;    uint32 ulTgtLgtRequest;  teRte_AfsModeSig_sVal eAfsMode_Sig_Output;  } asTestCaseData[]
    = {
         {                    eBlinkOn,                  Afs_Country,                 (uint32)0x00u,                  eLb_to_PXA_Adjustment        },
         {                    eBlinkOff,                 Afs_Country,                 (uint32)0x0Fu,                  eLb_to_PXA_Adjustment_Blink  },
         {                    eAimOn,                    Afs_Country,                 (uint32)0x0Fu,                  eLb_to_PXA_Adjustment        },
         {                    4U,                        Afs_Country,                 (uint32)0x0Fu,                  eLb_to_PXA_Adjustment        },
         {                    eAimingOff,                Afs_Off,                     (uint32)0x04u,                  eLb_to_PXA_CountryLight      },
         {                    eAimingOff,                Afs_Off,                     (uint32)0x01u,                  eLb_to_PXA_TownLight         },
         {                    eAimingOff,                Afs_Town,                    (uint32)0x02u,                  eLb_to_PXA_Pedestrian        },
         {                    eAimingOff,                Afs_Town,                    (uint32)0x04u,                  eLb_to_PXA_CountryLight      },
         {                    eAimingOff,                Afs_Town,                    (uint32)0x08u,                  eLb_to_PXA_MotorwayLight     },
         {                    eAimingOff,                Afs_Town,                    (uint32)0x10u,                  eLb_to_PXA_LB_Boosted        },
         {                    eAimingOff,                Afs_Town,                    (uint32)0x80u,                  eLb_to_PXA_AfsOff            },   // Lb Adverse Weather  Left without Afs Mode in BadWeather Left
         {                    eAimingOff,                Afs_BadWeather_Lhd,          (uint32)0x80u,                  eLb_to_PXA_BadWeather_Lhd    },
         {                    eAimingOff,                Afs_BadWeather_Lhd,          (uint32)0x20u,                  eLb_to_PXA_AfsOff            },   // Lb Adverse Weather Right without Afs Mode in BadWeather Left -> incorrect combination
         {                    eAimingOff,                Afs_BadWeather_Rhd,          (uint32)0x20u,                  eLb_to_PXA_BadWeather_Rhd    },
         {                    eAimingOff,                Afs_Foggy_Lhd,               (uint32)0x100u,                 eLb_to_PXA_Foggy_Lhd         },
         {                    eAimingOff,                Afs_Foggy_Rhd,               (uint32)0x40u,                  eLb_to_PXA_Foggy_Rhd         },
         {                    eAimingOff,                Afs_BadWeather_Lhd,          (uint32)0x88u,                  eLb_to_PXA_MotorwayLight     },   // 2 light requests: Motorway & ( Bad Weather Left + Afs Bad Weather Left)
      };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus = FALSE;
    FctR_RteAccess_Write_AfsMode_sTgtLgt.Req.ulRaw = (uint32)0x00u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_RteAccess_Write_AfsMode_eAimingMode        = asTestCaseData[ucIdx].eAimingMode;
    FctR_RteAccess_Write_AfsMode_sTgtLgt.Req.ulRaw  = asTestCaseData[ucIdx].ulTgtLgtRequest;
    FctR_RteAccess_Write_AfsMode_eAfsModeReceived   = asTestCaseData[ucIdx].eAfsModeReceived;

    //Step 3) Call FUT
    FctR_RteAccess_Write_AfsMode_RetVal = FctR_RteAccess_Write_AfsMode(FctR_RteAccess_Write_AfsMode_sTgtLgt, FctR_RteAccess_Write_AfsMode_eAfsModeReceived, FctR_RteAccess_Write_AfsMode_eAimingMode);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Rte_Write_FctR_AfsModeSig_sVal_Param1,    asTestCaseData[ucIdx].eAfsMode_Sig_Output, == );
  }

}


//-----------------------------------------------------------------------------
// RTE Read 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_VehNetState
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads the Vehicle state from
///                         RTE and stores the vehicle state
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sVehState_Input     : input data with  vehicle state from SysMon
///
///   - Expectations:
///
/// \output  sVehState_Output  : internal mapping of the vehicle state
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_VehNetState(void)
{
  struct {  tsRte_SysMon_VehNetState  sVehState_Input;          tsFctR_VehState sVehState_Output; }asTestCaseData[]
    = { { { VESState_Stop,      eTI_DEGRADE,    SIG_VALID},     {  eState_Stop,       eTI_DEGRADE   } },
        { { VESState_Ignition,  eTA_NOMINAL,    SIG_VALID},     {  eState_Contact,    eTA_NOMINAL   } },
        { { VESState_Start,     eTA_DEGRADE,    SIG_VALID},     {  eState_Start,      eTA_DEGRADE   } },
        { { VESState_Invalid,   eTI_DISPO_DEM,  SIG_VALID},     {  eState_InvalidSEV, eTI_DISPO_DEM } },
        { { VESState_Start,     eDEMARRAGE,   SIG_INVALID},     {  eState_Stop,       eInvalid      } },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    FctR_RteAccess_Read_VehNetState_psData.eFctR_EtatPrincipSEV = eState_Stop;
    FctR_RteAccess_Read_VehNetState_psData.eFctR_EtatReseauElec = eInvalid;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_SysMon_VehNetState_Param1 = asTestCaseData[ucIdx].sVehState_Input;

    //Step 3) Call the FUT
    FctR_RteAccess_Read_VehNetState_RetVal = FctR_RteAccess_Read_VehNetState(&FctR_RteAccess_Read_VehNetState_psData);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_VehNetState_psData.eFctR_EtatPrincipSEV, asTestCaseData[ucIdx].sVehState_Output.eFctR_EtatPrincipSEV, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_VehNetState_psData.eFctR_EtatReseauElec, asTestCaseData[ucIdx].sVehState_Output.eFctR_EtatReseauElec, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_EngineState
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function reads the engine state from
///                         RTE and does an internal mapping of the engine state
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sElecSupplyState_Input  : input data with  engine state from SigPrep
///
///   - Expectations:
///
/// \output  eEngineState_Output   : internal mapping of the engine state
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_EngineState(void)
{

  struct { tsRte_SigPrep_ElecSupState sElecSupplyState_Input;  teFctR_EngineState eEngineState_Output; }asTestCaseData[]
    = { {              {eEtatFee_4_1,   SIG_VALID} ,                              eEngineRunning       },
        {              {eEtatFee_3c_1,  SIG_VALID} ,                              eSTT_Phase           },
        {              {eEtatFee_3r_1,  SIG_VALID} ,                              eSTT_Phase           },
        {              {eEtatFee_3vr_1, SIG_VALID} ,                              eInvalid_State       },
        {              {eEtatFee_2_1, SIG_INVALID} ,                              eInvalid_State       },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_SigPrep_ElecSupState_Param1 = asTestCaseData[ucIdx].sElecSupplyState_Input;

    //Step 3) Call the FUT
    FctR_RteAccess_Read_EngineState_RetVal = FctR_RteAccess_Read_EngineState(&FctR_RteAccess_Read_EngineState_pData);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_EngineState_pData, asTestCaseData[ucIdx].eEngineState_Output, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_StdLgtFctReq
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function stores the light function
///                         requests from SysMon
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sStdLgtFctReqSysMon_Input  : input data with  light requests from SysMon
/// \input eLowBeamCmdSysMon          : input data with  Low Beam request
///
///   - Expectations:
///
/// \output  sLightReq_Output        : standard light function requests saved
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_StdLgtFctReq(void)
{

  struct      {   tsRte_SysMonLgtFctsReq sStdLgtFctReqSysMon_Input;                 teRte_ReqLightState   eLowBeamCmdSysMon;        tsFctR_StdLgtFctsReq sLightReq_Output; }asTestCaseData[]
    = { /*1*/ {  { ReqLighted_Off,   ReqLighted_Off,   ReqLighted_Off,   ReqLighted_Off,   ReqLighted_Off,                                                /* inputs */   \
                   ReqLighted_Off, eEtatFeuxStationnement_Deactivated, eModeConfigVehicle_Usine, SIG_INIT} , ReqLighted_Off,                              /* inputs */   \
              {             FALSE,            FALSE,            FALSE,            FALSE,            FALSE,                                                /* outputs */  \
                            FALSE,            FALSE,            FALSE,            FALSE,            FALSE,  Pkl_Deactivated, eSig_Valid } },              /* outputs */  \
\
        /*2*/ {  {  ReqLighted_On,    ReqLighted_On,    ReqLighted_On,              ReqLighted_On,    ReqLighted_On,                                      /* inputs */   \
                    ReqLighted_On,   eEtatFeuxStationnement_LeftSide, eModeConfigVehicle_Controle,  SIG_E2E_CRCERR } , ReqLighted_On,                     /* inputs */   \
                 {           TRUE,             TRUE,             TRUE,                       TRUE,             TRUE,                                      /* outputs */  \
                             TRUE,            FALSE,             TRUE,                      FALSE,            FALSE,   Pkl_Left, eSig_Invalid } },        /* outputs */  \
\
        /*3*/ {  {  ReqLighted_On,    ReqLighted_On,    ReqLighted_On,               ReqLighted_On,    ReqLighted_On,                                     /* inputs */   \
                    ReqLighted_On,   eEtatFeuxStationnement_RightSide, eModeConfigVehicle_Showroom,        SIG_SNA } , ReqLighted_On,                     /* inputs */   \
                 {           TRUE,             TRUE,             TRUE,                        TRUE,             TRUE,                                     /* outputs */  \
                             TRUE,            FALSE,             TRUE,                       FALSE,            FALSE,  Pkl_Right, eSig_Valid } },         /* outputs */  \
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_SysMon_StdLgtFcts_Req_Param1 = asTestCaseData[ucIdx].sStdLgtFctReqSysMon_Input;
    Rte_Read_SysMon_LowBeamCmd_Req_Param1 = asTestCaseData[ucIdx].eLowBeamCmdSysMon;

    //Step 3) Call the FUT
    FctR_RteAccess_Read_StdLgtFctReq_RetVal = FctR_RteAccess_Read_StdLgtFctReq(&FctR_RteAccess_Read_StdLgtFctReq_pData);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boDrl_Req,      asTestCaseData[ucIdx].sLightReq_Output.boDrl_Req,     == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boHbFlash_Req,  asTestCaseData[ucIdx].sLightReq_Output.boHbFlash_Req, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boHb_Req,       asTestCaseData[ucIdx].sLightReq_Output.boHb_Req,      == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boLb_Req,       asTestCaseData[ucIdx].sLightReq_Output.boLb_Req,      == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boPos_Req,      asTestCaseData[ucIdx].sLightReq_Output.boPos_Req,     == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boSideM_Req,    asTestCaseData[ucIdx].sLightReq_Output.boSideM_Req,   == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boTiDiag_Req,   asTestCaseData[ucIdx].sLightReq_Output.boTiDiag_Req,  == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boFog_Req,      asTestCaseData[ucIdx].sLightReq_Output.boFog_Req,     == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boClDiag_Req,   asTestCaseData[ucIdx].sLightReq_Output.boClDiag_Req,  == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.boSblDiag_Req,  asTestCaseData[ucIdx].sLightReq_Output.boSblDiag_Req, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.ePkl_Req,       asTestCaseData[ucIdx].sLightReq_Output.ePkl_Req,      == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_StdLgtFctReq_pData.eSigQuality,    asTestCaseData[ucIdx].sLightReq_Output.eSigQuality,   == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_AfsSignals
///
/// \Functional Safety: NA
///
/// \Test Case Description: Check that the function does an internal mapping
///                         of the Afs signals received via RTE and sends
///                         the GFHB command to the AdbMxb algorithm
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sAfsSignals  : input data from SysMon related to Afs requests
///
///   - Expectations:
///
/// \output  sOutData   : internal mapping of Afs requests
/// \output  eGfHbCmd   : GFHB command to be sent to AdbMxb
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_AfsSignals(void)
{

  struct { tsRte_SysMonAfsSignals sAfsSignals; tsFctR_AfsSignals sOutData;  teRte_GfHb_Cmd eGfHbCmd; }asTestCaseData[] 
    = {  {  {eCtrlAFS_Country, eGfhbCmd_On, eLowBeamBoostAllowed_False, FALSE, eAimingModeActivation_False, 0U, SIG_VALID},         /* Input*/
            {eCtrlAFS_Country, eGfhbCmd_On, FALSE, FALSE, FALSE},  eGfhbCmd_On },                                                   /* Output */
         {  {   eCtrlAFS_Town, eGfhbCmd_CurtainAct, eLowBeamBoostAllowed_True, TRUE,  eAimingModeActivation_True, 0U, SIG_VALID},   /* Input*/
            {   eCtrlAFS_Town, eGfhbCmd_CurtainAct, TRUE, TRUE, TRUE},  eGfhbCmd_CurtainAct },                                      /* Output */
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_SysMon_Afs_Signals_Param1 = asTestCaseData[ucIdx].sAfsSignals;

    //Step 3) Call the FUT
    FctR_RteAccess_Read_AfsSignals_RetVal = FctR_RteAccess_Read_AfsSignals(&FctR_RteAccess_Read_AfsSignals_pData);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_AfsSignals_pData.eAfsMode,                               asTestCaseData[ucIdx].sOutData.eAfsMode, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_AfsSignals_pData.eGfHbCmd,                               asTestCaseData[ucIdx].sOutData.eGfHbCmd, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_AfsSignals_pData.boLbBoost_Allowed,             asTestCaseData[ucIdx].sOutData.boLbBoost_Allowed, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_AfsSignals_pData.boPedestrian_Allowed,       asTestCaseData[ucIdx].sOutData.boPedestrian_Allowed, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_AfsSignals_pData.boAimingMode_Activation, asTestCaseData[ucIdx].sOutData.boAimingMode_Activation, == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_GfHbCmd_Param1,                                                        asTestCaseData[ucIdx].eGfHbCmd, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_ReadVehicleModeConfig
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    Test that VehicleModeConfig is evaluated and the
///                       stepper mode config is set correctly
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eSigQty_Input               : signal quality of vehicle Mode Config
/// \input eVehicleConfigSigMsg_Input  : input data with vehicle Mode Config from SigPrep
///
///   - Expectations:
///
/// \output  eCtrlStpVehicleModeCfg_Output   : output value for stepper mode config
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_ReadVehicleModeConfig(void)
{

  struct { teRte_SigQty   eSigQty_Input;  teRte_ModeConfigVehicle   eVehicleConfigSigMsg_Input;    teFctR_ModeConfigVehicle eCtrlStpVehicleModeCfg_Output; }asTestCaseData[]
    = { {                     SIG_VALID,                            eModeConfigVehicle_Usine,                            eFctR_ModeConfigVehicle_Usine     },
        {                     SIG_VALID,                            eModeConfigVehicle_Showroom,                         eFctR_ModeConfigVehicle_Showroom  },
        {                     SIG_VALID,                            eModeConfigVehicle_Controle,                         eFctR_ModeConfigVehicle_Controle  },
        {                       SIG_SNA,                            eModeConfigVehicle_Montage,                          eModeConfigVehicle_Invalid2       },
        {                   SIG_INVALID,                            eModeConfigVehicle_AfterMarket,                      eModeConfigVehicle_Invalid2       },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    Rte_Read_SigPrep_VehicleConfigSig_HitCount = 0u;

    //Step 2) Assign Input values
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eSigQty      = asTestCaseData[ucIdx].eSigQty_Input;
    Rte_Read_SigPrep_VehicleConfigSig_Param1.eVehicleCfg  = asTestCaseData[ucIdx].eVehicleConfigSigMsg_Input;

    //Step 3) Call FUT
    FctR_RteAccess_ReadVehicleModeConfig_RetVal = FctR_RteAccess_ReadVehicleModeConfig();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehicleConfigSig_HitCount, 1u, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_ReadVehicleModeConfig_RetVal, asTestCaseData[ucIdx].eCtrlStpVehicleModeCfg_Output,  == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_TiRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if Turn Indicator activation signals and TI request
///                         are correctly interpreted and FctR compose correctly 
///                         the TI requests based on the RTE inputs
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sTiReqSignals_Received      : input data with Turn Indicator activation signals
/// \input eTurnIndicatorCmd_Received  : input data with Turn Indicator activation request
///
///   - Expectations:
///
/// \output  sTiCommands_Interpreted   : composed turn indicator requests
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_TiRequest(void)
{

  struct {   tsRte_SysMonLgtTiReq sTiReqSignals_Received;                                           teRte_ReqLightState  eTurnIndicatorCmd_Received;     tsFctR_TiReq sTiCommands_Interpreted;  } asTestCaseData[]
    = { {  { eWarningMode_PilotedWarningMode, eEtatClignotants_LeftIndicatorActive, eScrollingTI_On, SIG_VALID },                    ReqLighted_Off,    { FALSE,  TRUE,   Ti_ActiveLeft, WarningMode_Piloted } },
        {  { eWarningMode_AutonomWarningMode, eEtatClignotants_RightIndicatorActive, eScrollingTI_Off, SIG_VALID},                    ReqLighted_On,    { TRUE,  FALSE,  Ti_ActiveRight, WarningMode_Autonom } },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    tsFctR_TiReq  Mt_InitData = { 0u };
    FctR_RteAccess_Read_TiRequest_pData = &Mt_InitData;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_SysMon_StdLgtTi_Req_Param1         = asTestCaseData[ucIdx].sTiReqSignals_Received;
    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1 = asTestCaseData[ucIdx].eTurnIndicatorCmd_Received;

    //Step 3) Call the FUT
    FctR_RteAccess_Read_TiRequest_RetVal = FctR_RteAccess_Read_TiRequest(FctR_RteAccess_Read_TiRequest_pData);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_TiRequest_pData->boTi_Req,           asTestCaseData[ucIdx].sTiCommands_Interpreted.boTi_Req,          == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_TiRequest_pData->boTiScrolling_Req,  asTestCaseData[ucIdx].sTiCommands_Interpreted.boTiScrolling_Req, == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_TiRequest_pData->eTiWarnMode,        asTestCaseData[ucIdx].sTiCommands_Interpreted.eTiWarnMode,       == );
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_TiRequest_pData->eTiStatus,          asTestCaseData[ucIdx].sTiCommands_Interpreted.eTiStatus,         == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_ClSblRequest
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    Test that CL and SBL requests are correctly read from Rte port
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sClSblReq_Received      : input data of SBL and CL requests
///
///   - Expectations:
///
/// \output  boClReq             :  CL request value
/// \output  boSblReq            :  SBL request value
/// \output  boTimeoutDetected   :  confirmation of timeout detection
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_ClSblRequest(void)
{
  //Step 1) Set pre - conditions
  boolean Mt_InitClReq, Mt_InitSblReq, Mt_InitTimeout;
  FctR_RteAccess_Read_ClSblRequest_pboClReq       = &Mt_InitClReq;
  FctR_RteAccess_Read_ClSblRequest_pboSblReq      = &Mt_InitSblReq;
  FctR_RteAccess_Read_ClSblRequest_pboSblClSigQty = &Mt_InitTimeout;

  struct {    tsRte_SigPrepLgtClSblReq sClSblReq_Received;    boolean boClReq;   boolean boSblReq;  boolean boTimeoutDetected; } asTestCaseData[]
    = {  {   { ReqLighted_Off, ReqLighted_On,  SIG_TIMEOUT },           FALSE,               TRUE,                     TRUE    },
         {   { ReqLighted_On,  ReqLighted_Off, SIG_VALID   },           TRUE,               FALSE,                    FALSE    },
     };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_SigPrep_StdLgtClSbl_Req_Param1 = asTestCaseData[ucIdx].sClSblReq_Received;

    //Step 3) Call FUT
    FctR_RteAccess_Read_ClSblRequest_RetVal = FctR_RteAccess_Read_ClSblRequest(FctR_RteAccess_Read_ClSblRequest_pboClReq, FctR_RteAccess_Read_ClSblRequest_pboSblReq, FctR_RteAccess_Read_ClSblRequest_pboSblClSigQty);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(*FctR_RteAccess_Read_ClSblRequest_pboClReq,        asTestCaseData[ucIdx].boClReq,             == );
    AL_UNITTEST_CHECK(*FctR_RteAccess_Read_ClSblRequest_pboSblReq,       asTestCaseData[ucIdx].boSblReq,            == );
    AL_UNITTEST_CHECK(*FctR_RteAccess_Read_ClSblRequest_pboSblClSigQty,  asTestCaseData[ucIdx].boTimeoutDetected,   == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_EcuSide
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function stores the ECU side read via
///                     RTE from IoHwAb module
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input eRteSide : Mounted side detection via RTE port
///
///   - Expectations:
///
/// \output ucHitCount   : number of accesses of IoHwAn RTE port
/// \output eMountedSide : Mounted Side read and decoded
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_EcuSide(void)
{
  //Step 1: Set pre-conditions

  struct { teRte_MountingSide eRteSide; uint8 ucHitCount;   teFctR_EcuSide   eMountedSide; } asTestCaseData[]
      =  {  {             eMountedUndef,              1u,                     eEcu_Undef  },
            {              eMountedLeft,              1u,                     eEcu_Left   },
            {             eMountedRight,              1u,                     eEcu_Right  },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    FctR_RteAccess_Read_EcuSide_eEcuSide = eEcu_Undef;
    //Step 2) Assign Input values
    Rte_Read_IoHwAbUser_GetMountingSide_Param1    = asTestCaseData[ucIdx].eRteSide;
    Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

    //Step 3) Call FUT
    FctR_RteAccess_Read_EcuSide_RetVal = FctR_RteAccess_Read_EcuSide(&FctR_RteAccess_Read_EcuSide_eEcuSide);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(FctR_RteAccess_Read_EcuSide_eEcuSide,           asTestCaseData[ucIdx].eMountedSide,  == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  asTestCaseData[ucIdx].ucHitCount,     == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_RteAccess_Read_LedVoltRange
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads LEDs volt range from Rte and
///                     stores it in an internal type
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions:
///
/// \input eVoltageState_Read : Voltage State read via RTE
///
///   - Expectations:
///
/// \output ucSetVoltageState   : Internal mapping of the Voltage Range Detected 
///
//-----------------------------------------------------------------------------
void Mt_FctR_RteAccess_Read_LedVoltRange(void)
{
  //Step 1: Set pre-conditions
  uint8 Mt_ucInit = 0u;
  FctR_RteAccess_Read_LedVoltRange_pucSetVoltageState = &Mt_ucInit;

  struct { teRte_SysVolt_Results eVoltageState_Read;    uint8 ucSetVoltageState; }asTestCaseData[]
    = {  {                          SysVolt_eNormal,         FCTR_NORMAL_VOLT    },
         {                          SysVolt_eLow1,           FCTR_LOW1_VOLT      },
         {                          SysVolt_eLow2,           FCTR_LOW2_VOLT      },
         {                          SysVolt_eLow5,           FCTR_UNKNOWN_VOLT   },
         {                          SysVolt_eHigh1,          FCTR_UNKNOWN_VOLT   },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 2) Assign Input values
    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1 = asTestCaseData[ucIdx].eVoltageState_Read;

    //Step 3) Call FUT
    FctR_RteAccess_Read_LedVoltRange(FctR_RteAccess_Read_LedVoltRange_pucSetVoltageState);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(*FctR_RteAccess_Read_LedVoltRange_pucSetVoltageState, asTestCaseData[ucIdx].ucSetVoltageState, == );
  }
}


//-----------------------------------------------------------------------------
//  FctR_TgtPrep.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_Get_Hb_Cmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test that the function returns the HB command
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    FctR_TgtPrep_boHBCmd           = TRUE
/// \input    FctR_TgtPrep_Get_Hb_Cmd_RetVal = FALSE
///
/// - Expectations: 
///
/// \output   FctR_TgtPrep_Get_Hb_Cmd_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_Get_Hb_Cmd(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtPrep_boHBCmd            = TRUE;
  FctR_TgtPrep_Get_Hb_Cmd_RetVal  = FALSE;

  //Step 3) Call FUT
  FctR_TgtPrep_Get_Hb_Cmd_RetVal = FctR_TgtPrep_Get_Hb_Cmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtPrep_Get_Hb_Cmd_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_Get_Lb_Cmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function returns the LB command
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    FctR_TgtPrep_boLBCmd           = TRUE
/// \input    FctR_TgtPrep_Get_Lb_Cmd_RetVal = FALSE
///
/// - Expectations: 
///
/// \output   FctR_TgtPrep_Get_Lb_Cmd_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_Get_Lb_Cmd(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtPrep_boLBCmd           = TRUE;
  FctR_TgtPrep_Get_Lb_Cmd_RetVal = FALSE;

  //Step 3) Call FUT
  FctR_TgtPrep_Get_Lb_Cmd_RetVal = FctR_TgtPrep_Get_Lb_Cmd();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtPrep_Get_Lb_Cmd_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_GetClSbl_AfsLight
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that function returns the Cl/Sbl request
///                         computed based on actual value and diagnostic request
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eActLgtClSbl  : actual Cl/Sbl request
/// \input boDiagReq     : diagnostic service request status
/// \input ulLgtDiagReq  : diagnostic service light function activation request
///
///   - Expectations:
///
/// \output  eOutLgtClSbl   : output Cl/Sbl state 
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_GetClSbl_AfsLight(void)
{

  struct { teFctR_LightFunctions eActLgtClSbl;  boolean boDiagReq; uint32 ulLgtDiagReq; teFctR_LightFunctions eOutLgtClSbl; }asTestCaseData[] =
  {
         {             LB_FoggyWeather_LHD,              FALSE,               0x20u,              LB_FoggyWeather_LHD      },
         {             LB_MotorwayLight,                  TRUE,               0x20u,              LB_MotorwayLight         },
         {             LB_AdverseWeather_LHD,             TRUE,          0x2000000u,              SBL_StaticBendingLight   },
         {             SBL_StaticBendingLight,            TRUE,          0x4000000u,              CL_CorneringLight        },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_eActLgtClSbl = asTestCaseData[ucIdx].eActLgtClSbl;
    FctR_TgtPrep_GetClSbl_AfsLight_RetVal = LF_INIT;

    //Step 2) Assign Input values
    Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus     = asTestCaseData[ucIdx].boDiagReq;
    Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.ulRaw    = asTestCaseData[ucIdx].ulLgtDiagReq;

    //Step 3) Call FUT
    FctR_TgtPrep_GetClSbl_AfsLight_RetVal = FctR_TgtPrep_GetClSbl_AfsLight();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(FctR_TgtPrep_GetClSbl_AfsLight_RetVal, asTestCaseData[ucIdx].eOutLgtClSbl, == );

  }

  //restore value
  Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus = FALSE;
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_GetAfsPedestrian
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Get the value of Afs pedestrian signal
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input       FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed = TRUE
/// \input       FctR_TgtPrep_GetAfsPedestrian_RetVal          = FALSE
/// - Expectations: 
///
/// \output   FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed = TRUE
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_GetAfsPedestrian(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed = TRUE;
  FctR_TgtPrep_GetAfsPedestrian_RetVal          = FALSE;

  //Step 3) Call FUT
  FctR_TgtPrep_GetAfsPedestrian_RetVal  = FctR_TgtPrep_GetAfsPedestrian();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtPrep_GetAfsPedestrian_RetVal, TRUE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_Full
///
/// \Functional Safety: NA
///
/// \Test Case Description
/// \Test Case Description
///    - Test subject:   Check that the light functions requests are read from 
///                      the standard light function requests RTE and are correctly
///                      prepared
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    Rte_Read_SysMon_LifePhases_Param1.ePhaseVie              = eNormalMode
/// \input    Rte_Read_IoHwAbUser_GetMountingSide_Param1               = eMountedLeft
/// \input    Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling       = eScrollingTI_On
/// \input    Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1             = ReqLighted_On
/// \input    Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request      = ReqLighted_On
/// \input    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request  = ReqLighted_On
/// \input    Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request      = ReqLighted_Off
/// \input    Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode            = eCtrlAFS_Motorway
/// \input    Rte_Read_SigPrep_StdLgtClSbl_Req_Param1.eCl_Request     = ReqLighted_Off
/// \input    Rte_Read_SigPrep_StdLgtClSbl_Req_Param1.eSbl_Request    = ReqLighted_On
///
/// - Expectations: 
///
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biTI_TiCmdPos             = 1u
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biSBL_StaticBendingLight  = 1u
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biTI_TurnIndicator        = 0u
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biDRL_DaytimeRunningLight = 0u
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biLB_MotorwayLight        = 0u
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biCL_CorneringLight       = 0u
/// \output   FctR_RteAccess_Read_PhaseVie_eEcuOpMode               = eEcu_NormalMode
/// \output   FctR_TgtPrep_eEcuSide                                 = eEcu_Left
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_Full(void)
{
  //Step 1) Set pre-conditions
  FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x00u;

  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie              = eNormalMode;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1               = eMountedLeft;
  Rte_Read_SysMon_StdLgtTi_Req_Param1.eTi_Scrolling        = eScrollingTI_On;
  Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1              = ReqLighted_On;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.ePos_Request       = ReqLighted_On;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eHbFlash_Request   = ReqLighted_On;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eDrl_Request       = ReqLighted_Off;
  Rte_Read_SysMon_Afs_Signals_Param1.eAfs_Mode             = eCtrlAFS_Motorway;
  Rte_Read_SigPrep_StdLgtClSbl_Req_Param1.eCl_Request      = ReqLighted_Off;
  Rte_Read_SigPrep_StdLgtClSbl_Req_Param1.eSbl_Request     = ReqLighted_On;

  //Step 3) Call FUT
  FctR_TgtLgt_Prep_Full();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biTI_TiCmdPos,                      1u, ==);
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biSBL_StaticBendingLight,           1u, ==);
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biTI_TurnIndicator,                 0u, ==); // because position is active
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biDRL_DaytimeRunningLight,          0u, ==);
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biLB_MotorwayLight ,                0u, ==);
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biCL_CorneringLight,                0u, ==);
  AL_UNITTEST_CHECK(FctR_RteAccess_Read_PhaseVie_eEcuOpMode,           eEcu_NormalMode, ==);
  AL_UNITTEST_CHECK(FctR_TgtPrep_eEcuSide,                                   eEcu_Left, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_Ti
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that TI request is mapped correctly to  the
///                         turn indicator light distributions
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boPos          : position light distribution request
/// \input boTi           : turn indicator request command
/// \input boTiScrolling  : scrolling turn indicator request command
/// \input eDebState      : timer debounce state
///
///   - Expectations:
///
/// \output  ulLightReqActive   : turn indicator light function status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_Ti(void)
{

  struct { boolean boPos; boolean boTi; boolean boTiScrolling;  tieDigState eDebState;  uint32 ulLightReqActive; }asTestCaseData[] =
  {
         {         FALSE,        FALSE,                  TRUE,                  Di_On,           (uint32)0x00u   },
         {         TRUE,         TRUE,                  FALSE,                 Di_Sna,             0xC0000000u   },    // TI_TiCmdPos + TI_TiReqPos= 1
         {         FALSE,        TRUE,                  FALSE,                 Di_Sna,             0x20000000u   },    // TI_TurnIndicator = 1
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x00u;
    FctR_TgtPrep_TiDelayTimer.eState = asTestCaseData[ucIdx].eDebState;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_Prep_Ti_boPosReq          = asTestCaseData[ucIdx].boPos;
    FctR_TgtLgt_Prep_Ti_boTiReq           = asTestCaseData[ucIdx].boTi;
    FctR_TgtLgt_Prep_Ti_boTiScrollingReq  = asTestCaseData[ucIdx].boTiScrolling;

    //Step 3) Call FUT
    FctR_TgtLgt_Prep_Ti(FctR_TgtLgt_Prep_Ti_boPosReq, FctR_TgtLgt_Prep_Ti_boTiReq, FctR_TgtLgt_Prep_Ti_boTiScrollingReq);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw, asTestCaseData[ucIdx].ulLightReqActive, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_SetTiLgtStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the TI light function status is set based 
///                     on TI request and debounce timer state
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boTi           : turn indicator request command
/// \input eDebState      : timer debounce state
///
///   - Expectations:
///
/// \output  boTiCmdStatus   : turn indicator light function COMMAND status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_SetTiLgtStatus(void)
{

  struct {  boolean boTi;  tieDigState eDebState;  boolean boTiCmdStatus;   }asTestCaseData[] =
  {
         {         FALSE,                  Di_On,                FALSE      },    //reset static inside
         {         TRUE,                  Di_Off,                TRUE       },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtPrep_TiDelayTimer.eState = asTestCaseData[ucIdx].eDebState;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtPrep_SetTiLgtStatus_boTiReq = asTestCaseData[ucIdx].boTi;

    //Step 3) Call FUT
    FctR_TgtPrep_SetTiLgtStatus_RetVal = FctR_TgtPrep_SetTiLgtStatus(FctR_TgtPrep_SetTiLgtStatus_boTiReq);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtPrep_SetTiLgtStatus_RetVal, asTestCaseData[ucIdx].boTiCmdStatus, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_StdLgtFcts
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the standard light function requests are
///                         prepared correctly based on the evaluation of standard 
///                         light distribution signals
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sStdLgtFctsSig         : standard light functions requests
/// \input eEcuOperationMode      : ECU operational mode
/// \input eEcuSide               : mounted side for EC
///
///   - Expectations:
///
/// \output  ulTgtLgtReqPrepared  : light distributions prepared to be activated 
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_StdLgtFcts(void)
{

  struct { tsFctR_StdLgtFctsReq sStdLgtFctsSig;                       teFctR_EcuOperationgMode eEcuOperationMode;  teFctR_EcuSide  eEcuSide;     uint8 ucTgtReq;    uint8 ucFailure;      uint32 ulTgtLgtReqPrepared; } asTestCaseData[]
    = {                                                                                                                                                               
           /* Drl | HbFlash| Hb_Req| Lb_Req| Pos| SM| TiDi| Fog|  Cl| SblDi| Pkl|   SigQlty| */                                                                       
    /*0*/ {  { 1u,   0u,         0u,     0u,  1u, 0u,  0u,   0u,  0u,    0u,  2u, SIG_VALID } ,  eEcu_NormalMode,                eEcu_Left,                1u,              0u,         (uint32)0xC00000u  },   // output : DRL and Pos
    /*1*/ {  { 0u,   0u,         0u,     1u,  0u, 0u,  0u,   0u,  0u,    0u,  1u, SIG_VALID } ,  eEcu_NormalMode,                eEcu_Left,                1u,              1u,             (uint32)0x00u  },   // output : no light prepared (PKL not active in normal mode)
    /*2*/ {  { 1u,   0u,         0u,     0u,  0u, 0u,  0u,   0u,  0u,    0u,  1u, SIG_VALID } ,  eEcu_NormalMode,                eEcu_Left,                1u,              0u,             (uint32)0x00u  },   // output : no light prepared (PKL not active in normal mode)
    /*3*/ {  { 0u,   0u,         0u,     0u,  0u, 0u,  0u,   0u,  0u,    0u,  2u, SIG_SNA   } ,  eEcu_NormalMode,                eEcu_Right,               1u,              1u,         (uint32)0x800000u  },   // output : POS active (special req. )
    /*4*/ {  { 1u,   2u,         0u,     0u,  0u, 1u,  0u,   0u,  0u,    0u,  2u, SIG_VALID } ,  eEcu_OffMode,                   eEcu_Right,               1u,              1u,       (uint32)0x11800000u  },   // output : off mode -> DRL is off, POS is off unless PKL= 1, active : POS, PKL and SM
    /*5*/ {  { 1u,   0u,         1u,     0u,  1u, 0u,  0u,   1u,  0u,    0u,  1u, SIG_VALID } ,  eEcu_OffMode,                   eEcu_Left,                1u,              1u,        (uint32)0x8000000u  },   // output : off mode -> DRL is off, POS is off unless PKL= 1, active : Fog light
    /*6*/ {  { 0u,   0u,         0u,     0u,  1u, 0u,  0u,   0u,  0u,    0u,  1u, SIG_VALID } ,  eEcu_NormalMode,                eEcu_Left,                1u,              1u,        (uint32)0x1800000u  },   // output : no light prepared (PKL not active in normal mode)
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x00u;
    //Step 2) Assign Input values
    FctR_TgtLgt_Prep_StdLgtFcts_sStdLgtFcts = asTestCaseData[ucIdx].sStdLgtFctsSig;
    FctR_TgtPrep_eEcuOpMode                 = asTestCaseData[ucIdx].eEcuOperationMode;
    FctR_TgtPrep_eEcuSide                   = asTestCaseData[ucIdx].eEcuSide;
    FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight = asTestCaseData[ucIdx].ucTgtReq;
    FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight = asTestCaseData[ucIdx].ucTgtReq;
    FctR_DRLIlluminantsErr = asTestCaseData[ucIdx].ucFailure;
    FctR_Cod_DRLIlluminantsFBit = asTestCaseData[ucIdx].ucFailure;

    //Step 3) Call FUT
    FctR_TgtLgt_Prep_StdLgtFcts(FctR_TgtLgt_Prep_StdLgtFcts_sStdLgtFcts);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw,     asTestCaseData[ucIdx].ulTgtLgtReqPrepared, == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_PklHandling
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Chek that the Parking Light request is computed correctly
///                     on the requested side
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ePklReq                : parking light request input
/// \input eEcuOperationMode      : ECU operational mode
/// \input eEcuSide               : mounted side for ECU
///
///   - Expectations:
///
/// \output  boPklReq    :  parking light request status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_PklHandling(void)
{

  struct { teFctR_PklReq ePklReq;  teFctR_EcuOperationgMode eEcuOperationMode;  teFctR_EcuSide  eEcuSide;  boolean boPklReq; } asTestCaseData[] =
     {
       {          Pkl_Deactivated,                            eEcu_NormalMode,                eEcu_Left,              FALSE  },
       {          Pkl_Left,                                   eEcu_OffMode,                   eEcu_Left,              FALSE  },
       {          Pkl_Right,                                  eEcu_NormalMode,                eEcu_Left,              FALSE  },
       {          Pkl_Right,                                  eEcu_OffMode,                   eEcu_Right,             TRUE   },
       {          Pkl_Right,                                  eEcu_OffMode,                   eEcu_Left,              FALSE  },
     };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign Input values
    FctR_TgtPrep_PklHandling_ePklReq  = asTestCaseData[ucIdx].ePklReq;
    FctR_TgtPrep_eEcuOpMode           = asTestCaseData[ucIdx].eEcuOperationMode;
    FctR_TgtPrep_eEcuSide             = asTestCaseData[ucIdx].eEcuSide;

    //Step 3) Call FUT
    FctR_TgtPrep_PklHandling_RetVal = FctR_TgtPrep_PklHandling(FctR_TgtPrep_PklHandling_ePklReq);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(FctR_TgtPrep_PklHandling_RetVal, asTestCaseData[ucIdx].boPklReq, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_SetTiWarningMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Chek that the Turn Indicator warning mode is computed correctly
///                    based on the ECU operational mode and Turn Indicator signals
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eEcuOpMode             : ECU operational mode
/// \input sTiReq                 : Turn Indicator request signals
/// \input eWarnMode_Actual       : actual TI warning mode
///
///   - Expectations:
///
/// \output  eWarnMode_Set        : TI warning mode after evaluation
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_SetTiWarningMode(void)
{

  struct { teFctR_EcuOperationgMode eEcuOpMode;       tsFctR_TiReq sTiReq;       teFctr_TiWarningMode  eWarnMode_Actual; teFctr_TiWarningMode eWarnMode_Set; }asTestCaseData[] =
    {
         {      eEcu_NormalMode,     { FALSE, FALSE,  Ti_Inactive ,   WarningMode_Autonom} ,        WarningMode_Piloted,         WarningMode_Autonom         },
         {      eEcu_NormalMode,     { TRUE,  FALSE,  Ti_ActiveLeft , WarningMode_Piloted} ,        WarningMode_Autonom,         WarningMode_Piloted         },
         {      eEcu_OffMode,        { TRUE,  FALSE,  Ti_ActiveBoth , WarningMode_Piloted} ,        WarningMode_Autonom,         WarningMode_Autonom         },
    };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign Input values
    FctR_TgtPrep_SetTiWarningMode_eEcuOpMode  = asTestCaseData[ucIdx].eEcuOpMode;
    FctR_TgtPrep_SetTiWarningMode_sTiReq      = asTestCaseData[ucIdx].sTiReq;
    FctR_TgtPrep_eTiWarningMode               = asTestCaseData[ucIdx].eWarnMode_Actual;

    //Step 3) Call FUT
    FctR_TgtPrep_SetTiWarningMode(FctR_TgtPrep_SetTiWarningMode_eEcuOpMode, FctR_TgtPrep_SetTiWarningMode_sTiReq);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(FctR_TgtPrep_eTiWarningMode, asTestCaseData[ucIdx].eWarnMode_Set, == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_WarningMode_Handling
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Manage Turn Indicator Warning Modes and
///                     return the TI command
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eTiWarningMode  : Turn Indicator  Warning Mode
/// \input eTiWarningMode  : Turn Indicator  command request
/// \input eTimerState     : timer debounce state 
///
///   - Expectations:
///
/// \output  boTiAutoMode_On   : Ti Autnonomous mode state
/// \output  boTiCmd           : Turn Indicator command status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_WarningMode_Handling(void)
{

  struct { teFctr_TiWarningMode eTiWarningMode; boolean boTiReq;  tieDigState eTimerState;  boolean boTiAutoMode_On; boolean boTiCmd; } asTestCaseData[] =
     {
         {                WarningMode_Autonom,             TRUE,                    Di_On,                    TRUE,             FALSE },
         {                WarningMode_Piloted,             TRUE,                    Di_Off,                   FALSE,             TRUE },
     };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    boolean Mt_boTiCmd            = TRUE;
    boolean Mt_boTiScrollingCmd   = TRUE;
    FctR_TgtPrep_boTiAutoMode_On  = FALSE;
    FctR_TgtPrep_boTiStatus       = TRUE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtPrep_eTiWarningMode                       = asTestCaseData[ucIdx].eTiWarningMode;
    FctR_TgtLgt_WarningMode_Handling_sTiReq.boTi_Req  = asTestCaseData[ucIdx].boTiReq;
    FctR_TgtLgt_WarningMode_Handling_boTiCmd          = &Mt_boTiCmd;
    FctR_TgtLgt_WarningMode_Handling_boTiScrollingCmd = &Mt_boTiScrollingCmd;
    FctR_TgtPrep_sTiAutoModeTimer.eState              = asTestCaseData[ucIdx].eTimerState;

    //Step 3) Call FUT
    FctR_TgtLgt_WarningMode_Handling(FctR_TgtLgt_WarningMode_Handling_sTiReq, FctR_TgtLgt_WarningMode_Handling_boTiCmd, FctR_TgtLgt_WarningMode_Handling_boTiScrollingCmd);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtPrep_boTiAutoMode_On,                 asTestCaseData[ucIdx].boTiAutoMode_On, == );
    AL_UNITTEST_CHECK(*FctR_TgtLgt_WarningMode_Handling_boTiCmd,    asTestCaseData[ucIdx].boTiCmd,         == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_AutonomMode_Handling
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test the handling of the TI Autonomous mode and the 
///                      returned TI command status
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boTiStatus         : Turn Indicator  command request
/// \input boTiAutoMode_On    : Ti Autnonomous mode state
/// \input eTimerState        : timer debounce state 
///
///   - Expectations:
///
/// \output  eTimerStateUpdated   : timer status updated
/// \output  boTiCmd              : Turn Indicator command status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_AutonomMode_Handling(void)
{

    struct { boolean boTiStatus;  boolean boTiAutoMode_On; tieDigState eTimerState;   tieDigState eTimerStateUpdated; boolean boTiCmd;   } asTestCaseData[] =
    {
        {                 TRUE,                   FALSE,                   Di_Off,                          Di_Sna,              TRUE    },
        {                 TRUE,                   TRUE,                    Di_Sna,                          Di_Sna,              TRUE    },
        {                FALSE,                   TRUE,                    Di_On,                           Di_On,              FALSE    },
     };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    boolean Mt_boTiCmd            = TRUE;
    FctR_TgtLgt_AutonomMode_Handling_boTiCmd = &Mt_boTiCmd;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtPrep_boTiStatus                   = asTestCaseData[ucIdx].boTiStatus;
    FctR_TgtPrep_sTiAutoModeTimer.eState      = asTestCaseData[ucIdx].eTimerState;
    FctR_TgtPrep_boTiAutoMode_On              = asTestCaseData[ucIdx].boTiAutoMode_On;

    //Step 3) Call FUT
    FctR_TgtLgt_AutonomMode_Handling(FctR_TgtLgt_AutonomMode_Handling_boTiCmd);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtPrep_sTiAutoModeTimer.eState,                 asTestCaseData[ucIdx].eTimerStateUpdated, == );
    AL_UNITTEST_CHECK(*FctR_TgtLgt_AutonomMode_Handling_boTiCmd,            asTestCaseData[ucIdx].boTiCmd,            == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_PilotedMode_Handling
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test the handling of the TI Piloted mode and the 
///                      returned TI command and TI Scrolling status
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input eEcuSide           : ecu mounted side
/// \input sTiReq             : Turn Indicator  command signals
///
///   - Expectations:
///
/// \output  boTiCmd              : Turn Indicator command request
/// \output  boTiScrollingCmd     : Turn Indicator Scrolling command status
/// \input boTiStatus             : Turn Indicator  command status
/// \input boTiAutoMode_On        : Ti Autnonomous mode state
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_PilotedMode_Handling(void)
{
  //Step 1) Set pre-conditions
  boolean boTiCmdInit       = FALSE;
  boolean boTiScrollingInit = FALSE;

  struct { teFctR_EcuSide eEcuSide;                         tsFctR_TiReq sTiReq;  boolean boTiCmd; boolean boTiScrollingCmd;  boolean boTiStatus; boolean boTiAutoMode_On; } asTestCaseData[] =
  {
      {                 eEcu_Undef, { FALSE, FALSE, Ti_Inactive,   WarningMode_Autonom},    FALSE,                     FALSE,              FALSE,                 FALSE  },
      {                 eEcu_Left,  { TRUE,  FALSE, Ti_ActiveLeft, WarningMode_Autonom},    TRUE,                      FALSE,              TRUE,                  FALSE  },
      {                 eEcu_Undef, { FALSE, TRUE,  Ti_ActiveBoth, WarningMode_Autonom},    FALSE,                     TRUE,               TRUE,                  FALSE  },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtLgt_PilotedMode_Handling_boTiCmd          = &boTiCmdInit;
    FctR_TgtLgt_PilotedMode_Handling_boTiScrollingCmd = &boTiScrollingInit;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtPrep_eEcuSide                       = asTestCaseData[ucIdx].eEcuSide;
    FctR_TgtLgt_PilotedMode_Handling_sTiReq     = asTestCaseData[ucIdx].sTiReq;

    //Step 3) Call FUT
    FctR_TgtLgt_PilotedMode_Handling(FctR_TgtLgt_PilotedMode_Handling_sTiReq, FctR_TgtLgt_PilotedMode_Handling_boTiCmd, FctR_TgtLgt_PilotedMode_Handling_boTiScrollingCmd);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(*FctR_TgtLgt_PilotedMode_Handling_boTiCmd,          asTestCaseData[ucIdx].boTiCmd,          == );
    AL_UNITTEST_CHECK(*FctR_TgtLgt_PilotedMode_Handling_boTiScrollingCmd, asTestCaseData[ucIdx].boTiScrollingCmd, == );
    AL_UNITTEST_CHECK(FctR_TgtPrep_boTiStatus,                            asTestCaseData[ucIdx].boTiStatus,       == );
    AL_UNITTEST_CHECK(FctR_TgtPrep_boTiAutoMode_On,                       asTestCaseData[ucIdx].boTiAutoMode_On,  == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_GetTiCmdReq
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test the Turn Indicator command is computed correctly
///                      in case diag is requested or not
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boDiagReq          : DD00 diag request
/// \input ulDiagLghtReq      : DD00 diag light function requested
/// \input sTiReq             : Turn Indicator  command status
///
///   - Expectations:
///
/// \output  boTiCmd          : Turn Indicator command request
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_GetTiCmdReq(void)
{

  struct { boolean boDiagReq; uint32 ulDiagLghtReq; boolean boTiPrv;  boolean boTiCmd; } asTestCaseData[] =
  {
         {              TRUE,          0x40000000u,           FALSE,              TRUE  },  //TiCmdPos REQ, Diag requested
         {             FALSE,          0x40000000u,           FALSE,              FALSE },  //TiCmdPos REQ, Diag not requested
         {              TRUE,          0x20000000u,           FALSE,              TRUE  },  //Ti REQ, Diag requested
         {              TRUE,          0x80000000u,           FALSE,              FALSE },  //Ti Scrolling REQ, Diag  requested
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtPrep_GetTiCmdReq_RetVal = FALSE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus  = asTestCaseData[ucIdx].boDiagReq;
    Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.ulRaw = asTestCaseData[ucIdx].ulDiagLghtReq;
    FctR_TgtPrep_boTiCmd = asTestCaseData[ucIdx].boTiPrv;

    //Step 3) Call FUT
    FctR_TgtPrep_GetTiCmdReq_RetVal = FctR_TgtPrep_GetTiCmdReq();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtPrep_GetTiCmdReq_RetVal, asTestCaseData[ucIdx].boTiCmd, == );

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_DiagDD00_ResetCmd
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test the function resets all lights in case of stop command 
///                      from DD00 diag serv, otherwise light will not be affected
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boDiagActRequest     : DD00 diag request
/// \input ulTgtLgtReq_Prv      : light function activated
///
///   - Expectations:
///
/// \output  ulTgtLgtReqReset   : light function request status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_DiagDD00_ResetCmd(void)
{
  struct { boolean boDiagActRequest; uint32 ulTgtLgtReq_Prv; uint32 ulTgtLgtReqReset; }asTestCaseData[] =
  {
         {                    FALSE,             0x20000000u,             0u          },
         {                    TRUE,              0x20000000u,             0x20000000u },
  };
  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtPrep_GetTiCmdReq_RetVal = FALSE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtPrep_DiagDD00_ResetCmd_Param1 = asTestCaseData[ucIdx].boDiagActRequest;
    FctR_TgtLgtReqPrep.Req.ulRaw = asTestCaseData[ucIdx].ulTgtLgtReq_Prv;

    //Step 3) Call FUT
    FctR_TgtPrep_DiagDD00_ResetCmd(FctR_TgtPrep_DiagDD00_ResetCmd_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw, asTestCaseData[ucIdx].ulTgtLgtReqReset, == );

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_Aiming
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Evaluate the value of Aiming Mode Activation request
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input       FctR_TgtLgt_Prep_Aiming_boAimReq     = TRUE
/// \input       FctR_TgtLgt_Prep_Aiming_boHbFlashReq = FALSE
/// - Expectations: 
///
/// \output   FctR_TgtLgtReqPrep.Req.Bits.biHB_AimingMode = 1u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_Aiming(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgt_Prep_Aiming_boAimReq     = TRUE;
  FctR_TgtLgt_Prep_Aiming_boHbFlashReq = FALSE;

  //Step 3) Call FUT
  FctR_TgtLgt_Prep_Aiming(FctR_TgtLgt_Prep_Aiming_boAimReq, FctR_TgtLgt_Prep_Aiming_boHbFlashReq);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biHB_AimingMode, 1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_Lb_Full
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the low beam light distribution to be activated is
///                         correctly computed based on the low beam light function request
///                         and Afs Mode received
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boLbRequest             : low beam command request
/// \input eAfsModeReceived        : AFS mode received
/// \input boPedestrianAllowed     : pedestrian distribution request
/// \input boLbBoost_Allowed       : low beam boost distribution request
///
///   - Expectations:
///
/// \output  ulTgtLgtRequest       : low beam light distribution to be activated 
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_Lb_Full(void)
{

  struct { boolean boLbRequest; teFctR_AfsMode eAfsModeReceived;    boolean boPedestrianAllowed; boolean boLbBoost_Allowed; uint32 ulTgtLgtRequest; } asTestCaseData[]
    = {
         {              FALSE ,                Afs_Country,                            FALSE,                     FALSE,        (uint32)0x00u,      },    /*    off                   */
         {               TRUE ,                Afs_Off,                                FALSE,                     FALSE,        (uint32)0x04u,      },    /*    biLb_CountryLight     */
         {               TRUE ,                Afs_Country,                            FALSE,                     FALSE,        (uint32)0x04u,      },    /*    biLb_CountryLight     */
         {               TRUE ,                Afs_Town,                               FALSE,                     FALSE,        (uint32)0x01u,      },    /*    biLb_TownLight        */
         {               TRUE ,                Afs_Town,                               TRUE,                      FALSE,        (uint32)0x02u,      },    /*    biLb_Pedestrian       */
         {               TRUE ,                Afs_Motorway,                           FALSE,                     FALSE,        (uint32)0x08u,      },    /*    biLb_MotorwayLight    */
         {               TRUE ,                Afs_Motorway,                           FALSE,                     FALSE,        (uint32)0x08u,      },    /*    biLb_MotorwayLight    */
         {               TRUE ,                Afs_BadWeather_Lhd,                     FALSE,                     FALSE,        (uint32)0x80u,      },    /*    biLb_BadWeather_Lhd   */
         {               TRUE ,                Afs_BadWeather_Rhd,                     FALSE,                     FALSE,        (uint32)0x20u,      },    /*    biLb_BadWeather_Rhd   */
         {               TRUE ,                Afs_Foggy_Lhd,                          FALSE,                     FALSE,        (uint32)0x100u,     },    /*    biLb_Foggy_Lhd        */
         {               TRUE ,                Afs_Foggy_Rhd,                          FALSE,                     FALSE,        (uint32)0x40u,      },    /*    biLb_Foggy_Rhd        */
         {               TRUE ,                Afs_Invalid,                            TRUE,                      TRUE,         (uint32)0x04u,      },    /*    biLb_MotorwayLight    */
      };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtLgtReqPrep.Req.ulRaw      = (uint32)0x00u;
    FctR_TgtPrep_sAfsSignals.eAfsMode = Afs_Off;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_Prep_Lb_Full_boLbReq              = asTestCaseData[ucIdx].boLbRequest;
    FctR_TgtPrep_sAfsSignals.eAfsMode             = asTestCaseData[ucIdx].eAfsModeReceived;
    FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed = asTestCaseData[ucIdx].boPedestrianAllowed;
    FctR_TgtPrep_sAfsSignals.boLbBoost_Allowed    = asTestCaseData[ucIdx].boLbBoost_Allowed;

    //Step 3) Call FUT
    FctR_TgtLgt_Prep_Lb_Full(FctR_TgtLgt_Prep_Lb_Full_boLbReq);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw,    asTestCaseData[ucIdx].ulTgtLgtRequest, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_Hb_Full
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the HighBeam light distribution signals are
///                         activated correctly based on the evaluation of standard 
///                         light functions  and ADB requests
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sStdLgtFctsRequest      : standard light functions requests for Hb command
/// \input ucAdbOutFailure         : ADB failure status on GFHB command
/// \input boHBBReq                : High Beam Boost request from ADB module
///
///   - Expectations:
///
/// \output  ulTgtLgtRequest       :  high beam light distribution to be activated 
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_Hb_Full(void)
{

  struct { tsFctR_StdLgtFctsReq sStdLgtFctsRequest;                                                     uint8 ucAdbOutFailure;  boolean boHBBReq; uint32 ulTgtLgtRequest; } asTestCaseData[]
    = {    /* Drl | HbFlash  | Hb_Req  |      Lb_Req  |  Pos| SM|TiDi| Fog|Cl|SblDi|Pkl| SigQlty| */
   /*0*/ {  { 0u,   ReqLighted_On,   0u,             0u,   0u, 0u, 0u, 0u, 0u, 0u, 0u, SIG_VALID } ,                       0U,             FALSE,    (uint32)0x20000u   }, // biHB_FlashToPass reqested
   /*1*/ {  { 0u,   0u,              0u,             0u,   0u, 0u, 0u, 0u, 0u, 0u, 0u, SIG_VALID } ,                       0U,             FALSE,    (uint32)0x00000u   }, // no high beam requested
   /*2*/ {  { 0u,   0u,   ReqLighted_On,  ReqLighted_On,   0u, 0u, 0u, 0u, 0u, 0u, 0u, SIG_VALID } ,                       0U,             FALSE,    (uint32)0x2000u    }, // biHB_HighBeam requested  (Hb, lb = ON)
   /*3*/ {  { 0u,   0u,   ReqLighted_On,             0u,   0u, 0u, 0u, 0u, 0u, 0u, 0u, SIG_VALID } ,                       0U,             FALSE,    (uint32)0x0000u    }, // biHB_HighBeam requested (Hb- on, Lb-off   -> HB off)
   /*4*/ {  { 0u,   0u,              0u,  ReqLighted_On,   0u, 0u, 0u, 0u, 0u, 0u, 0u, SIG_VALID } ,                       0U,             TRUE,     (uint32)0x4000u    }, // biHB_Boost request
   /*5*/ {  { 0u,   0u,   ReqLighted_On,  ReqLighted_On,   0u, 0u, 0u, 0u, 0u, 0u, 0u, SIG_VALID } ,                       6U,             FALSE,    (uint32)0x0000u    }, // biHB_HighBeam with GfhB mode, but with failure
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x00u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_Prep_Hb_Full_sStdLgtFcts    = asTestCaseData[ucIdx].sStdLgtFctsRequest;
    Rte_Read_ppsAdb_Out_sVal_4_Param1.State = asTestCaseData[ucIdx].ucAdbOutFailure;  //6 means failure, otherwise no failure on gfhb
    Rte_Read_Adb_StatusOut_Param1.HBBStatus = asTestCaseData[ucIdx].boHBBReq;

    //Step 3) Call FUT
    FctR_TgtLgt_Prep_Hb_Full(FctR_TgtLgt_Prep_Hb_Full_sStdLgtFcts);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw, asTestCaseData[ucIdx].ulTgtLgtRequest, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prep_ClSbl
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the Cornering Light and Static Bending Light
///                         signals are  activated correctly based on the evaluation 
///                         of AFS mode and CL/SBL requests
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boClReq            : cornering light request command
/// \input boSblReq           : static bending light request comamnd
/// \input eAfsModeReceived   : AFS mode received
/// \input boPedestrian       : Low beam pedestrian command request
///
///   - Expectations:
///
/// \output  eSblClReq       :   Actual SBL/CL request command
/// \output  ucClSblTgtState :   SBL/CL request target state
/// \output  boSblOut        :   static bending light status
/// \output  boClOut         :   cornering light status
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prep_ClSbl(void)
{

  struct { boolean boClReq; boolean boSblReq;  teFctR_AfsMode eAfsModeReceived;   boolean boPedestrian;  teFctR_LightFunctions eSblClReq; uint8 ucClSblTgtState;  boolean boSblOut; boolean boClOut; } asTestCaseData[]
    = {
         {          FALSE ,           FALSE ,                Afs_Off,                            FALSE,            LF_INIT,                 FCTR_CFG_SBL_CL_OFF,            FALSE,         FALSE     },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_Country,                        FALSE,            LF_INIT,                 FCTR_CFG_SBL_CL_OFF,            FALSE,         FALSE     },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_Town,                           FALSE,            LB_TownLight,            FCTR_CFG_SBL_CL_TOWN,            TRUE,         TRUE      },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_Town,                           TRUE ,            LB_Pedestrian,           FCTR_CFG_SBL_CL_PEDESTRIAN,      TRUE,         TRUE      },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_BadWeather_Lhd,                 FALSE,            LB_AdverseWeather_LHD,   FCTR_CFG_SBL_CL_BAD_WEATHER,     TRUE,         TRUE      },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_BadWeather_Rhd,                 FALSE,            LB_AdverseWeather_RHD,   FCTR_CFG_SBL_CL_BAD_WEATHER,     TRUE,         TRUE      },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_Foggy_Lhd,                      FALSE,            LB_FoggyWeather_LHD,     FCTR_CFG_SBL_CL_FOGGY,           TRUE,         TRUE      },    /*    no SBL/CL requested  directly  */
         {          FALSE ,           FALSE ,                Afs_Foggy_Rhd,                      FALSE,            LB_FoggyWeather_RHD,     FCTR_CFG_SBL_CL_FOGGY,           TRUE,         TRUE      },    /*    no SBL/CL requested  directly  */
         {           TRUE ,           TRUE  ,                Afs_Town,                           FALSE,            SBL_StaticBendingLight,  FCTR_CFG_SBL_CL_NOMINAL,         TRUE,         TRUE      },    /*    SBL and CL requested   */
         {          FALSE ,           TRUE  ,                Afs_BadWeather_Lhd,                 FALSE,            SBL_StaticBendingLight,  FCTR_CFG_SBL_CL_NOMINAL,         TRUE,         FALSE     },    /*    SBL requested   */
         {           TRUE ,           FALSE ,                Afs_Country,                        FALSE,            CL_CorneringLight,       FCTR_CFG_SBL_CL_NOMINAL,        FALSE,         TRUE      },    /*    CL requested   */
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x00u;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_Prep_ClSbl_boClReq                = asTestCaseData[ucIdx].boClReq;
    FctR_TgtLgt_Prep_ClSbl_boSblReq               = asTestCaseData[ucIdx].boSblReq;
    FctR_TgtPrep_sAfsSignals.eAfsMode             = asTestCaseData[ucIdx].eAfsModeReceived;
    FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed = asTestCaseData[ucIdx].boPedestrian;

    //Step 3) Call FUT
    FctR_TgtLgt_Prep_ClSbl(FctR_TgtLgt_Prep_ClSbl_boClReq, FctR_TgtLgt_Prep_ClSbl_boSblReq);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_eActLgtClSbl,                                        asTestCaseData[ucIdx].eSblClReq,        == );
    AL_UNITTEST_CHECK(FctR_ucClSblTargetState,                                  asTestCaseData[ucIdx].ucClSblTgtState,  == );
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biCL_CorneringLight,          asTestCaseData[ucIdx].boClOut,          == );
    AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.Bits.biSBL_StaticBendingLight,     asTestCaseData[ucIdx].boSblOut,         == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtPrep_GetClSblTargetState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the Cornering Light and Static Bending Light
///                         target state is returned correctly based on the evaluation 
///                         of diagnostic service or normal operation
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucActClSblState     : SBL/CL request actual state
/// \input boDiagReq           : diagnostic service request comamnd
/// \input ulDiagLgtReq        : siagnostic service light activation request
///
///   - Expectations:
///
/// \output  ucTargetClSblState :   SBL/CL request target state
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtPrep_GetClSblTargetState(void)
{
  struct { uint8 ucActClSblState;  boolean boDiagReq; uint32 ulDiagLgtReq; uint8 ucTargetClSblState; }asTestCaseData[] =
  {
    {        FCTR_CFG_SBL_CL_OFF,              FALSE,          0x00u,        FCTR_CFG_SBL_CL_OFF    },
    {        FCTR_CFG_SBL_CL_OFF,              TRUE,           0x2000u,      FCTR_CFG_SBL_CL_OFF    },
    {        FCTR_CFG_SBL_CL_OFF,              TRUE,           0x2000000u,    FCTR_CFG_SBL_CL_NOMINAL},
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_ucClSblTargetState                 = asTestCaseData[ucIdx].ucActClSblState;
    FctR_TgtPrep_GetClSblTargetState_RetVal = FctR_ucClSblTargetState;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus   = asTestCaseData[ucIdx].boDiagReq;
    Rte_Read_Diag_LdActivationRoutineControl_Param1.uTgtLgtFct.ulRaw  = asTestCaseData[ucIdx].ulDiagLgtReq;

    //Step 3) Call FUT
    FctR_TgtPrep_GetClSblTargetState_RetVal = FctR_TgtPrep_GetClSblTargetState();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_ucClSblTargetState, asTestCaseData[ucIdx].ucTargetClSblState, == );

  }

  //restore value
  Rte_Read_Diag_LdActivationRoutineControl_Param1.boRequestStatus = FALSE;
}


//-----------------------------------------------------------------------------
//  FctR_Tgt.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the variables are correctly initialised
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgtReqPrep.Req.ulRaw                = 1u
/// \input    FctR_TgtLgtReq.Req.ulRaw                    = 1u
/// \input    FctR_ucTgtLgtSustained[ucLogLmp]            = 1u
/// \input    FctR_ucTgtLgtHighPrio[ucLogLmp]             = 1u
/// \input    FctR_ucTgtLgtHighPrioPrevious[ucLogLmp]     = 1u
/// \input    FctR_ulActLmpInt[ucLogLmp]                  = 1u
/// \input    FctR_ucActLmpInt[ucLogLmp]                  = 1u
/// \input    FctR_ucTgtLmpInt[ucLogLmp]                  = 1u
/// \input    FctR_unTgtLmpSpdInv[ucLogLmp]               = 1u
/// \input    FctR_unTgtLmpSpdInv_sk[ucLogLmp]            = 1u
///
/// - Expectations: 
///
/// \output   FctR_TgtLgtReqPrep.Req.ulRaw                = 0
/// \output   FctR_TgtLgtReq.Req.ulRaw                    = 0u
/// \output   FctR_ucTgtLgtSustained[ucLogLmp]            = 255u
/// \output   FctR_ucTgtLgtHighPrio[ucLogLmp]             = 255u
/// \output   FctR_ucTgtLgtHighPrioPrevious[ucLogLmp]     = 255u
/// \output   FctR_ulActLmpInt[ucLogLmp]                  = 0u
/// \output   FctR_ucActLmpInt[ucLogLmp]                  = 0u
/// \output   FctR_ucTgtLmpInt[ucLogLmp]                  = 0u
/// \output   FctR_unTgtLmpSpdInv[ucLogLmp]               = 0u
/// \output   FctR_unTgtLmpSpdInv_sk[ucLogLmp]            = 0u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtInit(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgtReqPrep.Req.ulRaw                = 1u;
  FctR_TgtLgtReq.Req.ulRaw                    = 1u;

  for (uint8 ucLogLmp = 0; ucLogLmp < FCTR_CFG_LOGLMP_MAX; ucLogLmp++)
  {
    FctR_ucTgtLgtSustained[ucLogLmp]        = 1u;
    FctR_ucTgtLgtHighPrio[ucLogLmp]         = 1u;
    FctR_ucTgtLgtHighPrioPrevious[ucLogLmp] = 1u;
    FctR_ulActLmpInt[ucLogLmp]              = 1u;
    FctR_ucActLmpInt[ucLogLmp]              = 1u;
    FctR_ucTgtLmpInt[ucLogLmp]              = 1u;
    FctR_unTgtLmpSpdInv[ucLogLmp]           = 1u;
    FctR_unTgtLmpSpdInv_sk[ucLogLmp]        = 1u;
  }

  //Step 3) Call FUT
  FctR_TgtInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgtReqPrep.Req.ulRaw     , 0u  , ==);
  AL_UNITTEST_CHECK(FctR_TgtLgtReq.Req.ulRaw         , 0u  , ==);

  for (uint8 ucLogLmp = 0; ucLogLmp < FCTR_CFG_LOGLMP_MAX; ucLogLmp++)
  {
    AL_UNITTEST_CHECK(FctR_ucTgtLgtSustained[ucLogLmp] , 255u, == );
    AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrio[ucLogLmp]  , 255u, == );
    AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrioPrevious[ucLogLmp], 255u, == );
    AL_UNITTEST_CHECK(FctR_ulActLmpInt[ucLogLmp]   ,     0u  , == );
    AL_UNITTEST_CHECK(FctR_ucActLmpInt[ucLogLmp]   ,     0u  , == );
    AL_UNITTEST_CHECK(FctR_ucTgtLmpInt[ucLogLmp]   ,     0u  , == );
    AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv[ucLogLmp],     0u  , == );
    AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv_sk[ucLogLmp] , 0u  , == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the new target values for light functions
///                         are computed.
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    Rte_Read_SysMon_StdLgtFcts_Req_HitCount   = 0u
/// \input    Rte_Read_SysMon_StdLgtTi_Req_HitCount     = 0u
/// \input    Rte_Read_SysMon_Afs_Signals_HitCount      = 0u
/// \input    Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount = 0u
/// \input    Rte_Write_FctR_AfsDblCmd_HitCount         = 0u
/// \input    Rte_Write_FctR_AfsModeSig_sVal_HitCount   = 0u
///
/// - Expectations: 
///
/// \output   Rte_Read_SysMon_StdLgtFcts_Req_HitCount   = 1u
/// \output   Rte_Read_SysMon_StdLgtTi_Req_HitCount     = 1u
/// \output   Rte_Read_SysMon_Afs_Signals_HitCount      = 1u
/// \output   Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount = 1u
/// \output   Rte_Write_FctR_AfsDblCmd_HitCount         = 1u
/// \output   Rte_Write_FctR_AfsModeSig_sVal_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount   = 0u;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount     = 0u;
  Rte_Read_SysMon_Afs_Signals_HitCount      = 0u;
  Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount = 0u;
  Rte_Write_FctR_AfsDblCmd_HitCount         = 0u;
  Rte_Write_FctR_AfsModeSig_sVal_HitCount   = 0u;

  //Step 3) Call FUT
  FctR_TgtLgt();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtFcts_Req_HitCount  ,  1u, ==);
  AL_UNITTEST_CHECK(Rte_Read_SysMon_StdLgtTi_Req_HitCount,      1u, ==);
  AL_UNITTEST_CHECK(Rte_Read_SysMon_Afs_Signals_HitCount ,      1u, ==);
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount,  1u, ==);
  AL_UNITTEST_CHECK(Rte_Write_FctR_AfsDblCmd_HitCount  ,        1u, ==);
  AL_UNITTEST_CHECK(Rte_Write_FctR_AfsModeSig_sVal_HitCount  ,  1u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_GetActiveTgtLgtReq
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     : Test that the active status of the specified light 
///                          function is correctly evaluated
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ulLgtFctIdx         : light function index
/// \input ulTgtLgtReq_Raw     : light function requested
///
///   - Expectations:
///
/// \output  sLgtReq_Bit       :   light function requested on bit
/// \output  boLgtFctActive    :   light function active status
///
//-----------------------------------------------------------------------------
void Mt_FctR_GetActiveTgtLgtReq(void)
{

  struct { tAppLightFunction ulLgtFctIdx;  uint32  ulTgtLgtReq_Raw; tsFctR_TgtLgtFctBits sLgtReq_Bit; boolean boLgtFctActive; } asTestCaseData[] =
  {
        {                    HB_HighBeam,          (uint32)0x2000u,        {.biHB_HighBeam     = 1u },                  TRUE  },    // HB active
        {                LB_CountryLight,          (uint32)0x0000u,        {.biLB_CountryLight = 0u },                  FALSE },    // LB not active
        {                            32u,          (uint32)0x0000u,        {.biHB_HighBeam     = 0u },                  FALSE },    // LF not in range
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x00u;
    FctR_GetActiveTgtLgtReq_RetVal = TRUE;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_GetActiveTgtLgtReq_ulLgtFct = asTestCaseData[ucIdx].ulLgtFctIdx;
    FctR_TgtLgtReq.Req.ulRaw = asTestCaseData[ucIdx].ulTgtLgtReq_Raw;

    //Step 3) Call FUT
    FctR_GetActiveTgtLgtReq_RetVal = FctR_GetActiveTgtLgtReq(FctR_GetActiveTgtLgtReq_ulLgtFct);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_GetActiveTgtLgtReq_RetVal, asTestCaseData[ucIdx].boLgtFctActive, == );
    AL_UNITTEST_CHECK(FctR_TgtLgtReq.Req.Bits.biHB_HighBeam,         asTestCaseData[ucIdx].sLgtReq_Bit.biHB_HighBeam, == );
    AL_UNITTEST_CHECK(FctR_TgtLgtReq.Req.Bits.biLB_CountryLight, asTestCaseData[ucIdx].sLgtReq_Bit.biLB_CountryLight, == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Percent_To_RteUnit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the scaling is correctly done
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_Percent_To_RteUnit_ucPercentVal         = 10u
///
/// - Expectations: 
///
/// \output   FctR_Percent_To_RteUnit_RetVal         = 100u
///
//-----------------------------------------------------------------------------
void Mt_FctR_Percent_To_RteUnit(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_Percent_To_RteUnit_ucPercentVal = 10u;

  //Step 3) Call FUT
  FctR_Percent_To_RteUnit_RetVal = FctR_Percent_To_RteUnit(FctR_Percent_To_RteUnit_ucPercentVal);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_Percent_To_RteUnit_RetVal, 100u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_GetPriority
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     : Test that the priority of the specified light 
///                          function is correctly evaluated and returned
///                          from coding structure
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ulLgtFctIdx         : light function index
/// \input ucIllIdx            : illuminant index
///
///   - Expectations:
///
/// \output  ucPriority        :   light function returned priority
///
//-----------------------------------------------------------------------------
void Mt_FctR_GetPriority(void)
{
  //Step 1) Set pre-conditions
  Mt_Init_LmmABlock_And_CodingLmmX();
  FctR_GetPriority_RetVal = LGHT_PRIO_0;

  struct { tAppLightFunction ulLgtFctIdx;  tAppLogLamp ucIllIdx;  uint8 ucPriority; } asTestCaseData[] =
  {
        {            LB_FoggyWeather_LHD,             LOG_LMP_4,   LGHT_PRIO_8  },     //Foggy Weather LHD
        {               TI_TurnIndicator,             LOG_LMP_9,   LGHT_PRIO_7  },     //TI_TurnIndicator
        {                            255,             LOG_LMP_2,   LGHT_PRIO_15  },    //LF index not in range

  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_GetPriority_LgtFct = asTestCaseData[ucIdx].ulLgtFctIdx;
    FctR_GetPriority_LogLmp = asTestCaseData[ucIdx].ucIllIdx;

    //Step 3) Call FUT
    FctR_GetPriority_RetVal = FctR_GetPriority(FctR_GetPriority_LgtFct, FctR_GetPriority_LogLmp);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_GetPriority_RetVal, asTestCaseData[ucIdx].ucPriority, == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_GetIntensity
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     : Test that the intensity of the specified light 
///                          function is correctly evaluated and returned
///                          from coding structure
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ulLgtFctIdx         : light function index
/// \input ucIllIdx            : illuminant index
///
///   - Expectations:
///
/// \output  ucPriority        :   light function returned priority
///
//-----------------------------------------------------------------------------
void Mt_FctR_GetIntensity(void)
{
  //Step 1) Set pre-conditions
  Mt_Init_LmmABlock_And_CodingLmmX();
  FctR_GetIntensity_RetVal = LGHT_CFG_PWM_0;

  struct { tAppLightFunction ulLgtFctIdx;  tAppLogLamp ucIllIdx;  uint8 ucPWMValue; } asTestCaseData[] =
  {
        {            LB_FoggyWeather_LHD,             LOG_LMP_4,   LGHT_CFG_PWM_100  },     //Foggy Weather LHD
        {                LB_CountryLight,             LOG_LMP_1,    LGHT_CFG_PWM_95  },     //LB_CountryLight
        {               TI_TurnIndicator,             LOG_LMP_9,     LGHT_CFG_PWM_0  },     //TI_TurnIndicator
        {                            255,             LOG_LMP_2,     LGHT_CFG_PWM_0  },     //LF index not in range

  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_GetIntensity_LgtFct = asTestCaseData[ucIdx].ulLgtFctIdx;
    FctR_GetIntensity_LogLmp = asTestCaseData[ucIdx].ucIllIdx;

    //Step 3) Call FUT
    FctR_GetIntensity_RetVal = FctR_GetIntensity(FctR_GetIntensity_LgtFct, FctR_GetIntensity_LogLmp);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_GetIntensity_RetVal, asTestCaseData[ucIdx].ucPWMValue, == );

  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_ActLgt_Update
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the actual intensities of logical lamps are updated
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_unTgtLmpSpdInv_sk[0] = 0u
/// \input    FctR_unTgtLmpSpdInv_sk[1] = 1u
/// \input    FctR_unTgtLmpSpdInv_sk[2] = 20u
/// \input    FctR_unTgtLmpSpdInv_sk[3] = 40u
/// \input    FctR_unTgtLmpSpdInv_sk[4] = 10u
/// \input    FctR_ucTgtLmpInt[0]       = 1u
/// \input    FctR_ucTgtLmpInt[1]       = 0u
/// \input    FctR_ucTgtLmpInt[2]       = 0u
/// \input    FctR_ucTgtLmpInt[3]       = 1u
/// \input    FctR_ucTgtLmpInt[4]       = 1u
/// \input    FctR_ulActLmpInt[1]       = 327700u
/// \input    FctR_ulActLmpInt[2]       = 16380u
/// \input    FctR_ulActLmpInt[3]       = 1u
/// \input    FctR_ulActLmpInt[4]       = 1u
///
/// - Expectations: 
///
/// \output   FctR_ucActLmpInt[0]       = 1u
/// \output   FctR_ulActLmpInt[0]       = 16384u
/// \output   FctR_ucActLmpInt[1]       = 0u
/// \output   FctR_ulActLmpInt[1]       = 20u
/// \output   FctR_ucActLmpInt[2]       = 0u
/// \output   FctR_ulActLmpInt[2]       = 0u
/// \output   FctR_ucActLmpInt[3]       = 0u
/// \output   FctR_ulActLmpInt[3]       = 8193u
/// \output   FctR_ucActLmpInt[4]       = 1u
/// \output   FctR_ulActLmpInt[4]       = 16384u
///
//-----------------------------------------------------------------------------
void Mt_FctR_ActLgt_Update(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_unTgtLmpSpdInv_sk[0] = 0u;
  FctR_unTgtLmpSpdInv_sk[1] = 1u;
  FctR_unTgtLmpSpdInv_sk[2] = 20u;
  FctR_unTgtLmpSpdInv_sk[3] = 40u;
  FctR_unTgtLmpSpdInv_sk[4] = 10u;
  FctR_ucTgtLmpInt[0]       = 1u;
  FctR_ucTgtLmpInt[1]       = 0u;
  FctR_ucTgtLmpInt[2]       = 0u;
  FctR_ucTgtLmpInt[3]       = 1u;
  FctR_ucTgtLmpInt[4]       = 1u;
  FctR_ulActLmpInt[1]       = 327700u;
  FctR_ulActLmpInt[2]       = 16380u;
  FctR_ulActLmpInt[3]       = 1u;
  FctR_ulActLmpInt[4]       = 1u;

  //Step 3) Call FUT
  FctR_ActLgt_Update();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_ucActLmpInt[0], 1u, ==);
  AL_UNITTEST_CHECK(FctR_ulActLmpInt[0], 16384u, ==);
  AL_UNITTEST_CHECK(FctR_ucActLmpInt[1], 0u, ==);
  AL_UNITTEST_CHECK(FctR_ulActLmpInt[1], 20u   , ==);
  AL_UNITTEST_CHECK(FctR_ucActLmpInt[2], 0u, ==);
  AL_UNITTEST_CHECK(FctR_ulActLmpInt[2], 0u, ==);
  AL_UNITTEST_CHECK(FctR_ucActLmpInt[3], 0u, ==);
  AL_UNITTEST_CHECK(FctR_ulActLmpInt[3], 8193u , ==);
  AL_UNITTEST_CHECK(FctR_ucActLmpInt[4], 1u, ==);
  AL_UNITTEST_CHECK(FctR_ulActLmpInt[4], 16384u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if FctR_PrioLgtFctPair is correctly computed for DRL_DaytimeRunningLight
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct = 18u;
/// \input    FctR_PrioLgtFctPair[1].ucPrio2         = 15u;
/// \input    FctR_PrioLgtFctPair[10].ucPrio1        = 15u;
/// \input    FctR_PrioLgtFctPair[1].ucLgtFct2       = 0u;
/// \input    FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u;
/// \input    FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[10].ucIdx].biActive = 1;
/// \input    FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[10].ucIdx].biPriority = 8u;
///
/// - Expectations: 
///
/// \output   FctR_PrioLgtFctPair[1].ucPrio2         = 8u
/// \output   FctR_PrioLgtFctPair[10].ucPrio1        = 15u
/// \output   FctR_PrioLgtFctPair[1].ucLgtFct2       = 18u
/// \output   FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct = 18u;
  FctR_PrioLgtFctPair[1].ucPrio2         = 15u;
  FctR_PrioLgtFctPair[10].ucPrio1        = 15u;
  FctR_PrioLgtFctPair[1].ucLgtFct2       = 0u;
  FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u;
  FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[10].ucIdx].biActive = 1;
  FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[10].ucIdx].biPriority = 8u;

  //Step 3) Call FUT
  FctR_TgtLgt_Prio_LgtFctB_LogLmp(FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucPrio2   , 8u , ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[10].ucPrio1  , 15u , ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucLgtFct2 , 18u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[10].ucLgtFct1, 0u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if FctR_PrioLgtFctPair is correctly computed for DRL_DaytimeRunningLight
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct = 18u;
/// \input    FctR_PrioLgtFctPair[1].ucPrio2         = 0u;
/// \input    FctR_PrioLgtFctPair[10].ucPrio1        = 0u;
/// \input    FctR_PrioLgtFctPair[1].ucLgtFct2       = 0u;
/// \input    FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u;
///
/// - Expectations: 
///
/// \output   FctR_PrioLgtFctPair[1].ucPrio2          = 0u
/// \output   FctR_PrioLgtFctPair[10].ucPrio1         = 0u
/// \output   FctR_PrioLgtFctPair[1].ucLgtFct2        = 0u
/// \output   FctR_PrioLgtFctPair[10].ucLgtFct1       = 0u
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct = 18u;
  FctR_PrioLgtFctPair[1].ucPrio2         = 0u;
  FctR_PrioLgtFctPair[10].ucPrio1        = 0u;
  FctR_PrioLgtFctPair[1].ucLgtFct2       = 0u;
  FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u;

  //Step 3) Call FUT
  FctR_TgtLgt_Prio_LgtFctB_LogLmp(FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucPrio2   , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[10].ucPrio1  , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucLgtFct2 , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[10].ucLgtFct1, 0u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     : Test if FctR_PrioLgtFctPair is correctly computed for DRL_DaytimeRunningLight
///                           when the requested light function is not active
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct = 18u;
/// \input    FctR_PrioLgtFctPair[1].ucPrio2         = 0u;
/// \input    FctR_PrioLgtFctPair[10].ucPrio1        = 0u;
/// \input    FctR_PrioLgtFctPair[1].ucLgtFct2       = 0u;
/// \input    FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u;
/// \input    FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[1].ucIdx].biActive = 0u;
/// \input    FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[1].ucIdx].biPriority = 8u;
/// \input      FctR_AccessLogLmpTable[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].Raw = 0xFF;
///
/// - Expectations: 
///
/// \output   FctR_PrioLgtFctPair[1].ucPrio2          = 0u
/// \output   FctR_PrioLgtFctPair[10].ucPrio1         = 8u
/// \output   FctR_PrioLgtFctPair[1].ucLgtFct2        = 0u
/// \output   FctR_PrioLgtFctPair[10].ucLgtFct1       = 18u
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct = 18u;
  FctR_PrioLgtFctPair[1].ucPrio2         = 0u;
  FctR_PrioLgtFctPair[10].ucPrio1        = 0u;
  FctR_PrioLgtFctPair[1].ucLgtFct2       = 0u;
  FctR_PrioLgtFctPair[10].ucLgtFct1      = 0u;
  FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[1].ucIdx].biActive = 0u;
  FctR_pCodingArea->LmmX.Lut.cell[FctR_pLmmABlock->row[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].cell[1].ucIdx].biPriority = 8u;
  FctR_AccessLogLmpTable[FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct].Raw = 0xFF;

  //Step 3) Call FUT
  FctR_TgtLgt_Prio_LgtFctB_LogLmp(FctR_TgtLgt_Prio_LgtFctB_LogLmp_ucLgtFct);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucPrio2   , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucPrio1   , 8u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucLgtFct2 , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucLgtFct1 , 18u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function with the highest priority is chosen
///                     (Note: test cases will be changed)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp(void)
{
  Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase1();
  Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase2();
  Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio_LgtFct
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if FctR_PrioLgtFctPair is correctly computed
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgtReq.Req.ulRaw                   = 0u
/// \input    FctR_TgtLgtReq.Req.Bits.biTI_TurnIndicator = 1u
/// \input    FctR_PrioLgtFctPair[1].ucPrio2             = 0u
/// \input    FctR_PrioLgtFctPair[10].ucPrio1            = 0u
/// \input    FctR_PrioLgtFctPair[1].ucLgtFct2           = 0u
/// \input    FctR_PrioLgtFctPair[10].ucLgtFct1          = 0u
///
/// - Expectations: 
///
/// \output   FctR_PrioLgtFctPair[1].ucPrio2          = 0u
/// \output   FctR_PrioLgtFctPair[10].ucPrio1         = 0u
/// \output   FctR_PrioLgtFctPair[1].ucLgtFct2        = 0u
/// \output   FctR_PrioLgtFctPair[10].ucLgtFct1       = 0u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio_LgtFct(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgtReq.Req.ulRaw                   = 0u;
  FctR_TgtLgtReq.Req.Bits.biTI_TurnIndicator = 1u;
  FctR_PrioLgtFctPair[1].ucPrio2             = 0u;
  FctR_PrioLgtFctPair[10].ucPrio1            = 0u;
  FctR_PrioLgtFctPair[1].ucLgtFct2           = 0u;
  FctR_PrioLgtFctPair[10].ucLgtFct1          = 0u;

  //Step 3) Call FUT
  FctR_TgtLgt_Prio_LgtFct();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucPrio2   , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[10].ucPrio1  , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[1].ucLgtFct2 , 0u, ==);
  AL_UNITTEST_CHECK(FctR_PrioLgtFctPair[10].ucLgtFct1, 0u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio_LgtFct_FinalizePrio
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that the light function with the highest priority ( LOW 15 -> HIGH 1)
///                      is kept active. Check that the special case is treated when priority is not
///                      respected and the light function with Active bit is considered to have 
///                      higher priority
///
///    - Test Design Technique: DT (Decision Table)
///
///  \DT-Info:
///
///   - Inputs:
///       ucLogLmp   : illuminant (loglamp) index (0..15)
///       ucLgtFct1  : first light function requested light
///       ucPrioLgt1 : first light function requested priority
///       ucLgtFct2  : second light function requested light
///       ucPrioLgt2 : second light function requested priority
///
///   - Expectations:
///       ucTgtLgtHighPrio   : output light function to be active after priority evaluation
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio_LgtFct_FinalizePrio(void)
{

  struct { uint8 ucLogLmp;     uint8 ucLgtFct1;  uint8 ucPrioLgt1;     uint8 ucLgtFct2;  uint8 ucPrioLgt2;   uint8 ucTgtLgtHighPrio; }asTestCaseData[] =
  {
         {     LOG_LMP_15,             LF_INIT,      LGHT_PRIO_15,     TI_TurnIndicator,      LGHT_PRIO_15,                 LF_INIT  },
         {      LOG_LMP_1,    TI_TurnIndicator,      LGHT_PRIO_15,              LF_INIT,      LGHT_PRIO_15,        TI_TurnIndicator  },
         {      LOG_LMP_3,         HB_HighBeam,       LGHT_PRIO_6,      LB_CountryLight,       LGHT_PRIO_8,             HB_HighBeam  },
         {      LOG_LMP_3,     LB_CountryLight,       LGHT_PRIO_8,          HB_HighBeam,       LGHT_PRIO_6,         LB_CountryLight  }, //priority is not respected, but active lamp has more priority
         {     LOG_LMP_10,   POS_PositionLight,       LGHT_PRIO_8,     PKL_ParkingLight,       LGHT_PRIO_8,        PKL_ParkingLight  },
         {     LOG_LMP_16,         HB_HighBeam,       LGHT_PRIO_6,             HB_Boost,       LGHT_PRIO_6,             HB_HighBeam  },

  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8 ucLogLamp = asTestCaseData[ucIdx].ucLogLmp;
    FctR_UsageLogLmpTable[asTestCaseData[ucIdx].ucLgtFct1].Raw = 0x200u;  // Illuminant 10 has intensity for 1st LightFct

    //Step 2) Assign Input values
    FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct1  = asTestCaseData[ucIdx].ucLgtFct1;
    FctR_PrioLgtFctPair[ucLogLamp].ucPrio1    = asTestCaseData[ucIdx].ucPrioLgt1;
    FctR_PrioLgtFctPair[ucLogLamp].ucLgtFct2  = asTestCaseData[ucIdx].ucLgtFct2;
    FctR_PrioLgtFctPair[ucLogLamp].ucPrio2    = asTestCaseData[ucIdx].ucPrioLgt2;

    //Step 3) Call FUT
    FctR_TgtLgt_Prio_LgtFct_FinalizePrio();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrio[ucLogLamp], asTestCaseData[ucIdx].ucTgtLgtHighPrio, == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Prio
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the light function which has access to a 
///                         logical lamp is set correctly
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgtReq.Req.ulRaw                   = 0u
/// \input    FctR_ucTgtLgtHighPrio[ulLogLamp]           = 0u
/// \input    FctR_PrioLgtFctPair  [ulLogLamp].ucPrio1   = 0u
/// \input    FctR_PrioLgtFctPair  [ulLogLamp].ucPrio2   = 0u
/// \input    FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct1 = 0u
/// \input    FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct2 = 0u
///
/// - Expectations: 
///
/// \output   FctR_ucTgtLgtHighPrio[ulLogLamp]           = 255u
/// \output   FctR_PrioLgtFctPair  [ulLogLamp].ucPrio1   = 15u 
/// \output   FctR_PrioLgtFctPair  [ulLogLamp].ucPrio2   = 15u 
/// \output   FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct1 = 255u
/// \output   FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct2 = 255u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Prio(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgtReq.Req.ulRaw = 0u;

  for (uint32 ulLogLamp = 0; ulLogLamp < FCTR_CFG_LOGLMP_MAX; ulLogLamp++)
  {
    FctR_ucTgtLgtHighPrio[ulLogLamp]           = 0u;
    FctR_PrioLgtFctPair  [ulLogLamp].ucPrio1   = 0u;
    FctR_PrioLgtFctPair  [ulLogLamp].ucPrio2   = 0u;
    FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct1 = 0u;
    FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct2 = 0u;
  }

  //Step 3) Call FUT
  FctR_TgtLgt_Prio();

  //Step 4) Check expected output values
  for (uint32 ulLogLamp = 0; ulLogLamp < FCTR_CFG_LOGLMP_MAX; ulLogLamp++)
  {
    AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrio[ulLogLamp], 255u, ==);
    AL_UNITTEST_CHECK(FctR_PrioLgtFctPair  [ulLogLamp].ucPrio1  , 15u , ==);
    AL_UNITTEST_CHECK(FctR_PrioLgtFctPair  [ulLogLamp].ucPrio2  , 15u , ==);
    AL_UNITTEST_CHECK(FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct1, 255u, ==);
    AL_UNITTEST_CHECK(FctR_PrioLgtFctPair  [ulLogLamp].ucLgtFct2, 255u, ==);
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the speed of the light function is computed correctly
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal                          = 0u
/// \input    FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp] = 0u
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType                      = 0u
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime                          = 1u
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp                         = 0u
/// \input    FctR_ucTgtLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]       = 2u
/// \input    FctR_ucActLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]       = 1u
///
/// - Expectations: 
///
/// \output   FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal                          = 1u
/// \output   FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp] = 20u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal                          = 0u;
  FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp] = 0u;
  FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType                      = 0u;
  FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime                          = 1u;
  FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp                         = 0u;
  FctR_ucTgtLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]       = 2u;
  FctR_ucActLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]       = 1u;

  //Step 3) Call FUT
  FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal = FctR_TgtLgt_GetLmpSpdInvFromRampType(FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType, FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime, FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal              , 1u , ==);
  AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp], 20u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the speed of the light function is computed correctly
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal                           = 1u
/// \input    FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]  = 1u
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType                       = 1u
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime                           = 1u
/// \input    FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp                          = 0u
/// \input    FctR_ucTgtLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]        = 2u
/// \input    FctR_ucActLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]        = 2u
///
/// - Expectations: 
///
/// \output   FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal                          = 0u
/// \output   FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp] = 0u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal                          = 1u;
  FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp] = 1u;
  FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType                      = 1u;
  FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime                          = 1u;
  FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp                         = 0u;
  FctR_ucTgtLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]       = 2u;
  FctR_ucActLmpInt[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp]       = 2u;

  //Step 3) Call FUT
  FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal = FctR_TgtLgt_GetLmpSpdInvFromRampType(FctR_TgtLgt_GetLmpSpdInvFromRampType_ucRampType, FctR_TgtLgt_GetLmpSpdInvFromRampType_unTime, FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgt_GetLmpSpdInvFromRampType_RetVal              , 0u, ==);
  AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv_sk[FctR_TgtLgt_GetLmpSpdInvFromRampType_LogLamp], 0u, ==);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the speed transition is calculated based on coding
/// 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType(void)
{
  Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType_TestCase1();
  Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_GetLmpSpdInvB
///
/// \Functional Safety: NA
///
///    - Test subject:  Check that the function computes correctly the speed of the 
///                     light function based on its actual intensity, its 
///                     target intensity and ramp time deactivation/ activation/
///                     AFS transition time 
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucLgtFct         : input light function 
/// \input ucLogLmp         : input logical lamp (illuminant index)
/// \input ulLgtActive      : light functions active
/// \input ucClSblAfs       : CL/SBL AFS mode
/// \input ucTgtLgtFct      : target light function (function to achieve)
/// \input ucTgtPwm         : target PWM intensity
/// \input ucActPWM         : actual PWM intensity
/// \input ucClSblPrevPWM   : Cl/SBL PWM intensity
///
///   - Expectations:
///
/// \output  ucLgtSpeed     : calculated light function speed transition
/// \output  unTgtSpdInv    : calculated light function PWM transition
/// \output  ucClSblActPWM  : CL/SBL actual PWM intensity
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_GetLmpSpdInvB(void)
{
  uint8 ucLogLmpId;

  struct {
    uint8 ucLgtFct; uint8 ucLogLmp; uint32 ulLgtActive; uint8 ucClSblAfs;             uint8 ucTgtLgtFct;       uint8 ucTgtPwm;    uint8 ucActPWM;     uint8 ucClSblPrevPWM;  uint8 ucLgtSpeed; uint16 unTgtSpdInv; uint8 ucClSblActPWM;
  }asTestCaseData[] =
  {
    { LB_AdverseWeather_RHD,   LOG_LMP_5,           0x20u,  FCTR_CFG_SBL_CL_OFF,          LB_MotorwayLight,        LGHT_CFG_PWM_97,   LGHT_CFG_PWM_100,   LGHT_CFG_PWM_0,               100u,             666u,         LGHT_CFG_PWM_97   },    // TIME ON
    { LB_AdverseWeather_RHD,   LOG_LMP_2,           0x01u,  FCTR_CFG_SBL_CL_OFF,          LB_MotorwayLight,        LGHT_CFG_PWM_97,   LGHT_CFG_PWM_100,   LGHT_CFG_PWM_0,               0u,               0u,           LGHT_CFG_PWM_97   },    // TIME OFF
    { SBL_StaticBendingLight,  LOG_LMP_4,           0xFFu,  FCTR_CFG_SBL_CL_BAD_WEATHER,  SBL_StaticBendingLight,  LGHT_CFG_PWM_70,   LGHT_CFG_PWM_100,   LGHT_CFG_PWM_60,              50u,              33u,          LGHT_CFG_PWM_70   },    // FCTR_CFG_SBL_CL_AFS_TRANSITION_TIME
    { SBL_StaticBendingLight,  LOG_LMP_4,           0x00u,  FCTR_CFG_SBL_CL_NOMINAL,      SBL_StaticBendingLight,  LGHT_CFG_PWM_100,  LGHT_CFG_PWM_100,   LGHT_CFG_PWM_60,              0u,               0u,           LGHT_CFG_PWM_100  },    // FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT
    { SBL_StaticBendingLight,  LOG_LMP_4,           0x00u,  FCTR_CFG_SBL_CL_OFF,          SBL_StaticBendingLight,  LGHT_CFG_PWM_60,   LGHT_CFG_PWM_95,   LGHT_CFG_PWM_100,              40u,              22u,          LGHT_CFG_PWM_60   },    // FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT
    { SBL_StaticBendingLight,  LOG_LMP_4,           0x00u,  FCTR_CFG_SBL_CL_NOMINAL,      SBL_StaticBendingLight,  LGHT_CFG_PWM_100,  LGHT_CFG_PWM_100,   LGHT_CFG_PWM_60,              0u,               0u,           LGHT_CFG_PWM_100  },    // go back to nominal state to obtain time off in next state; current = FCTR_CFG_SBL_CL_DIM_TIME_ON_PER_PERCENT
    { SBL_StaticBendingLight,  LOG_LMP_4,           0x00u,  FCTR_CFG_SBL_CL_BAD_WEATHER,  SBL_StaticBendingLight,  LGHT_CFG_PWM_60,   LGHT_CFG_PWM_95,   LGHT_CFG_PWM_100,              40u,              22u,          LGHT_CFG_PWM_60   },    // FCTR_CFG_SBL_CL_DIM_TIME_OFF_PER_PERCENT
    { CL_CorneringLight,       LOG_LMP_4,           0x00u,  6u,                           CL_CorneringLight,       LGHT_CFG_PWM_0,    LGHT_CFG_PWM_100,   LGHT_CFG_PWM_60,              0u,               0u,           LGHT_CFG_PWM_0    },    // default case
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    ucClSblDimOut                     = 255u;
    FctR_TgtLgt_GetLmpSpdInvB_RetVal  = 0u;
    FctR_pCodingArea->PXA.DimmingTimes.ucCOUNTRY_TO_ADVERSEW = 10u;
    
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_GetLmpSpdInvB_LgtFct        = asTestCaseData[ucIdx].ucLgtFct;
    FctR_TgtLgt_GetLmpSpdInvB_LogLamp       = asTestCaseData[ucIdx].ucLogLmp;
    ucLogLmpId                              = FctR_TgtLgt_GetLmpSpdInvB_LogLamp;
    FctR_ucClSblTargetState                 = asTestCaseData[ucIdx].ucClSblAfs;
    FctR_TgtLgtReq.Req.ulRaw                = asTestCaseData[ucIdx].ulLgtActive;
    FctR_ucTgtLgtHighPrio[ucLogLmpId]       = asTestCaseData[ucIdx].ucTgtLgtFct;
    FctR_ucTgtLgtSustained[ucLogLmpId]      = asTestCaseData[ucIdx].ucTgtLgtFct;
    FctR_ucTgtLmpInt[ucLogLmpId]            = asTestCaseData[ucIdx].ucTgtPwm;
    FctR_ucActLmpInt[ucLogLmpId]            = asTestCaseData[ucIdx].ucActPWM;
    FctR_ucTgtClSblLmpInt_Prv[ucLogLmpId]   = asTestCaseData[ucIdx].ucClSblPrevPWM;

    //Step 3) Call the FUT
    FctR_TgtLgt_GetLmpSpdInvB_RetVal = FctR_TgtLgt_GetLmpSpdInvB(FctR_TgtLgt_GetLmpSpdInvB_LgtFct, FctR_TgtLgt_GetLmpSpdInvB_LogLamp);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtLgt_GetLmpSpdInvB_RetVal,             asTestCaseData[ucIdx].ucLgtSpeed,       == );
    AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv_sk[ucLogLmpId],           asTestCaseData[ucIdx].unTgtSpdInv,      == );
    AL_UNITTEST_CHECK(FctR_ucTgtClSblLmpInt_Prv[ucLogLmpId],        asTestCaseData[ucIdx].ucClSblActPWM,    == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_GetLmpSpdInv
///
/// \Functional Safety: NA
///
///    - Test subject:  Check that the function computes correctly the speed of the 
///                     light function based on the ramp time
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucLgtFct         : input light function 
/// \input ucLogLmp         : input logical lamp (illuminant index)
///
///   - Expectations:
///
/// \output  ucLgtSpeed     : calculated light function speed transition
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_GetLmpSpdInv(void)
{

    struct {        uint8 ucLgtFct;   uint8 ucLogLmp;  uint8 ucLgtSpeed;  }asTestCaseData[] =
           {
           { LB_AdverseWeather_RHD,       LOG_LMP_5,            100u     },    // TIME ON
           {   FCTR_CFG_LGTFCT_MAX,       LOG_LMP_2,              0u     },    // TIME OFF
           };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    ucClSblDimOut                     = 255u;
    FctR_TgtLgtReq.Req.ulRaw          = 0xFF;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_GetLmpSpdInv_LgtFct     = asTestCaseData[ucIdx].ucLgtFct;
    FctR_TgtLgt_GetLmpSpdInv_ucLogLamp  = asTestCaseData[ucIdx].ucLogLmp;

    //Step 3) Call the FUT
    FctR_TgtLgt_GetLmpSpdInv_RetVal = FctR_TgtLgt_GetLmpSpdInv(FctR_TgtLgt_GetLmpSpdInv_LgtFct, FctR_TgtLgt_GetLmpSpdInv_ucLogLamp);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_TgtLgt_GetLmpSpdInv_RetVal,             asTestCaseData[ucIdx].ucLgtSpeed,       == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Sustain_LogLamp
///
/// \Functional Safety: NA
///
///    - Test subject:  Check that the function evaluates the special cases of :
///          TS1) Cornering or SBL light requests with AFS mode and updates the CL/SBL pwm intensity with the one of the AFS mode
///          TS2) Cornering or SBL light requests with AFS mode Cornering and keeps the CL pwm intensity with the coding value
///          TS3) TI_TurnIndicator with DRL/POS light requests  (TI_POS_TurnIndicatorPos)
///          TS4) TI_TurnIndicator with DRL/POS light requests  (TI_POS_TurnIndicatorPos) and active bit set to 1
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boValid                : coding validity
/// \input ucIl                   : illuminant index
///
/// \ sLgtFct struct input data
/// \input ucActualLgtFct         : higher prio (actual) light function requested
/// \input ucSustainedLgtFct      : sustained light function requested
/// \input ucPrevLgtFct           : previous light function activated
///
/// \ sLightFctPWM struct input data
/// \input ucTgtLmpInt            : target light function intensity
/// \input ucActLmpInt            : actual light function intensity
///
/// \input ulLgtActive            : light function active
///
/// \ sSblClAfs struct input data
/// \input eActLgtClSbl            : Actual state of Cl/Sbl Afs Mode
/// \input ucClSblTargetState      : Target state of Cl/Sbl Afs Mode
/// \input ucCOUNTRY_TO_ADVERSEW   : timing of FAS transition
///
///   - Expectations:
///
/// \ sOutputData struct output data
/// \output ucTgtLmpIntUpdated     : calculated target light function intensity
/// \output ucTgtClSblLmpInt_Prv   : calculated target CL/SBL intensity previous cycle
/// \output unTgtLmpSpdInv         : calculated target light speed transition
/// \output unTgtLmpSpdInv_sk      : calculated target light speed transition for inverse
/// \output ucTgtLgtSustained      : updated target light function
/// \output ucTgtLgtHighPrio       : updated target light function with higher prio
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Sustain_LogLamp(void)
{

  /* data types created to shorten header of input/output table*/
  uint8 ucLogLmpId = 0u;
  typedef struct
  {
    uint8 ucActualLgtFct;
    uint8 ucSustainedLgtFct;
    uint8 ucPrevLgtFct;
  }tsLgtFct;

  typedef struct
  {
    uint8 ucTgtLmpInt;
    uint8 ucActLmpInt;
  }tsLgtFctPWM;

  typedef struct
  {
    teFctR_LightFunctions eActLgtClSbl;
    uint8 ucClSblTargetState;
    uint8 ucCOUNTRY_TO_ADVERSEW;
  }tsSblClAFSData;

  typedef struct {
    uint8 ucTgtLmpIntUpdated;
    uint8 ucTgtClSblLmpInt_Prv;
    uint8 unTgtLmpSpdInv;
    uint8 unTgtLmpSpdInv_sk;
    uint8 ucTgtLgtSustained;
    uint8 ucTgtLgtHighPrio;
  }tsOutputData;


  struct {
    boolean boValid; uint8 ucIl;  tsLgtFct sLgtFct; tsLgtFctPWM sLightFctPWM;  uint32 ulLgtActive;  tsSblClAFSData sSblClAfs; tsOutputData sOutputData;
  }asTestCaseData[] =
    {
 /*TS1)   boValid | ucLogLmp |               ActualLgtFct  |       SustainedLgtFct |             PrevLgtFct |            TgtLmpInt |         ActLmpInt |         ulLgtActive |           ActLgtClSbl | ClSblTargetState | COUNTRY_TO_ADVERSEW*/
    {           1u, LOG_LMP_4,      { SBL_StaticBendingLight, SBL_StaticBendingLight,     CL_CorneringLight },   { LGHT_CFG_PWM_100, LGHT_CFG_PWM_100 },       (uint32)0x00u,  { LB_TownLight, FCTR_CFG_SBL_CL_TOWN,            20u }, \
    \
    /*  --- RESULTS -----   ucTgtLmpIntUpdated |        ucTgtClSblLmpInt_Prv |      unTgtLmpSpdInv |     unTgtLmpSpdInv_sk|       ucTgtLgtSustained |         ucTgtLgtHighPrio */  \
     {                          LGHT_CFG_PWM_0 ,              LGHT_CFG_PWM_0,                 100u,                     20u,  SBL_StaticBendingLight,     SBL_StaticBendingLight }  },  // Test case covers Sustained == Actual, but Previous != Actual  -> target changed with AFS mode ActLgtClSbl = LB_TownLight intensity
    \
 /*TS2)   boValid | ucLogLmp |               ActualLgtFct  |       SustainedLgtFct |             PrevLgtFct |            TgtLmpInt |         ActLmpInt |        ulLgtActive |           ActLgtClSbl | ClSblTargetState | COUNTRY_TO_ADVERSEW*/
    {           1u, LOG_LMP_4,      { SBL_StaticBendingLight,   CL_CorneringLight,   SBL_StaticBendingLight },   { LGHT_CFG_PWM_70, LGHT_CFG_PWM_100 },      (uint32)0x00u,    {   CL_CorneringLight, FCTR_CFG_SBL_CL_OFF,                4u }, \
    \
    /*  --- RESULTS -----   ucTgtLmpIntUpdated |        ucTgtClSblLmpInt_Prv |      unTgtLmpSpdInv |     unTgtLmpSpdInv_sk|       ucTgtLgtSustained |         ucTgtLgtHighPrio */  \
     {                          LGHT_CFG_PWM_100,            LGHT_CFG_PWM_100,                  20u,                     0u,   SBL_StaticBendingLight,     SBL_StaticBendingLight }  },    //Test case covers Sustained != Actual and  // Prio(Actual) higher than Prio(Sustained) -> target equals the one of CL = 0 PWM
    \
 /*TS3)   boValid | ucLogLmp |               ActualLgtFct  |       SustainedLgtFct |             PrevLgtFct |            TgtLmpInt |         ActLmpInt |        ulLgtActive |           ActLgtClSbl | ClSblTargetState | COUNTRY_TO_ADVERSEW*/
    {          1u, LOG_LMP_11,      {      TI_TurnIndicator, TI_POS_TurnIndicatorPos, SBL_StaticBendingLight },  { LGHT_CFG_PWM_100, LGHT_CFG_PWM_100 },  (uint32)0x20000000u, {   CL_CorneringLight, FCTR_CFG_SBL_CL_OFF,                4u }, \
    \
    /*  --- RESULTS -----   ucTgtLmpIntUpdated |        ucTgtClSblLmpInt_Prv |      unTgtLmpSpdInv |     unTgtLmpSpdInv_sk|       ucTgtLgtSustained |         ucTgtLgtHighPrio */  \
     {                          LGHT_CFG_PWM_0 ,              LGHT_CFG_PWM_0,                   0u,                     0u,  TI_POS_TurnIndicatorPos,          TI_TurnIndicator }  },    //Test case covers I_TurnIndicator with DRL/POS light requests  and NO Active Bit set -> target equals 0 PWM in case TI is active
    \
 /*TS4)   boValid | ucLogLmp |               ActualLgtFct  |       SustainedLgtFct |             PrevLgtFct |            TgtLmpInt |         ActLmpInt |        ulLgtActive |           ActLgtClSbl | ClSblTargetState | COUNTRY_TO_ADVERSEW*/
    {          1u,  LOG_LMP_9,      { TI_POS_TurnIndicatorPos,     TI_TurnIndicator, SBL_StaticBendingLight },   { LGHT_CFG_PWM_100,   LGHT_CFG_PWM_0 },  (uint32)0x20000000u, {   CL_CorneringLight, FCTR_CFG_SBL_CL_OFF,                4u }, \
    \
    /*  --- RESULTS -----   ucTgtLmpIntUpdated |        ucTgtClSblLmpInt_Prv |      unTgtLmpSpdInv |     unTgtLmpSpdInv_sk|       ucTgtLgtSustained |         ucTgtLgtHighPrio */  \
     {                          LGHT_CFG_PWM_0 ,              LGHT_CFG_PWM_0,                   0u,                     0u,  TI_POS_TurnIndicatorPos,   TI_POS_TurnIndicatorPos }  },    //Test case covers TI_TurnIndicator with DRL/POS light requests and Active Bit = 1 -> target equals 0 PWM in case TI is active
 /*TS5)   boValid | ucLogLmp |               ActualLgtFct  |       SustainedLgtFct |             PrevLgtFct |            TgtLmpInt |         ActLmpInt |        ulLgtActive |           ActLgtClSbl | ClSblTargetState | COUNTRY_TO_ADVERSEW*/
    {          0u,  LOG_LMP_1,      {         LB_TownLight,         LB_CountryLight,          LB_TownLight },   { LGHT_CFG_PWM_100,   LGHT_CFG_PWM_100 },        (uint32)0x00u, {   CL_CorneringLight, FCTR_CFG_SBL_CL_OFF,                0u }, \
    \
    /*  --- RESULTS -----   ucTgtLmpIntUpdated |        ucTgtClSblLmpInt_Prv |      unTgtLmpSpdInv |     unTgtLmpSpdInv_sk|       ucTgtLgtSustained |         ucTgtLgtHighPrio */  \
     {                          LGHT_CFG_PWM_0 ,              LGHT_CFG_PWM_0,                   0u,                     0u,                 LF_INIT,                    LF_INIT }  },    //Test case covers invalid coding -> init values + last values
 /*TS6)   boValid | ucLogLmp |               ActualLgtFct  |       SustainedLgtFct |             PrevLgtFct |            TgtLmpInt |         ActLmpInt |        ulLgtActive |           ActLgtClSbl | ClSblTargetState | COUNTRY_TO_ADVERSEW*/
    {           1u, LOG_LMP_2,      {     LB_MotorwayLight,        LB_CountryLight,         LB_MotorwayLight },   { LGHT_CFG_PWM_97, LGHT_CFG_PWM_100 },      (uint32)0x00u,    {   CL_CorneringLight, FCTR_CFG_SBL_CL_OFF,                4u }, \
    \
    /*  --- RESULTS -----   ucTgtLmpIntUpdated |        ucTgtClSblLmpInt_Prv |      unTgtLmpSpdInv |     unTgtLmpSpdInv_sk|       ucTgtLgtSustained |         ucTgtLgtHighPrio */  \
     {                         LGHT_CFG_PWM_97 ,              LGHT_CFG_PWM_0,                   0u,                     0u,         LB_CountryLight,          LB_MotorwayLight }  },    //Test case covers Sustained != Actual and Previous == Actual -> target equals the one of actual ilght LB_MotorwayLight PWM =97

    };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    FctR_ucCodingState                         = asTestCaseData[ucIdx].boValid;
    ucLogLmpId                                 = asTestCaseData[ucIdx].ucIl;
    FctR_ucTgtClSblLmpInt_Prv[ucLogLmpId]      = LGHT_CFG_PWM_0;
    FctR_unTgtLmpSpdInv[ucLogLmpId]            = 0u;
    FctR_TgtPrep_boTiCmd                       = FALSE;


    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgt_Sustain_LogLamp_ucLogLamp                     = ucLogLmpId;
    FctR_ucTgtLgtHighPrio[ucLogLmpId]                         = asTestCaseData[ucIdx].sLgtFct.ucActualLgtFct;
    FctR_ucTgtLgtSustained[ucLogLmpId]                        = asTestCaseData[ucIdx].sLgtFct.ucSustainedLgtFct;
    FctR_ucTgtLgtHighPrioPrevious[ucLogLmpId]                 = asTestCaseData[ucIdx].sLgtFct.ucPrevLgtFct;
    FctR_ucTgtLmpInt[ucLogLmpId]                              = asTestCaseData[ucIdx].sLightFctPWM.ucTgtLmpInt;
    FctR_ucActLmpInt[ucLogLmpId]                              = asTestCaseData[ucIdx].sLightFctPWM.ucActLmpInt;

    FctR_eActLgtClSbl                                         = asTestCaseData[ucIdx].sSblClAfs.eActLgtClSbl;
    FctR_ucClSblTargetState                                   = asTestCaseData[ucIdx].sSblClAfs.ucClSblTargetState;
    FctR_pCodingArea->PXA.DimmingTimes.ucCOUNTRY_TO_ADVERSEW  = asTestCaseData[ucIdx].sSblClAfs.ucCOUNTRY_TO_ADVERSEW;


    //Step 3) Call the FUT
    FctR_TgtLgt_Sustain_LogLamp(FctR_TgtLgt_Sustain_LogLamp_ucLogLamp);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_ucTgtLmpInt[ucLogLmpId],           asTestCaseData[ucIdx].sOutputData.ucTgtLmpIntUpdated,     == );
    AL_UNITTEST_CHECK(FctR_ucTgtClSblLmpInt_Prv[ucLogLmpId],  asTestCaseData[ucIdx].sOutputData.ucTgtClSblLmpInt_Prv,   == );
    AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv[ucLogLmpId],        asTestCaseData[ucIdx].sOutputData.unTgtLmpSpdInv,         == );
    AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv_sk[ucLogLmpId],     asTestCaseData[ucIdx].sOutputData.unTgtLmpSpdInv_sk,      == );
    AL_UNITTEST_CHECK(FctR_ucTgtLgtSustained[ucLogLmpId],     asTestCaseData[ucIdx].sOutputData.ucTgtLgtSustained,      == );
    AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrio[ucLogLmpId],      asTestCaseData[ucIdx].sOutputData.ucTgtLgtHighPrio,       == );
    }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Sustain
///
/// \Functional Safety: NA
///
/// \Test Case Description
/// \Test Case Description
///    - Test subject:   Check that the function evaluates the special case of 
///                      Cornering or SBL light requests with AFS mode and updates
///                      the CL/SBL pwm intensity with the one of the AFS mode
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_ucTgtClSblLmpInt_Prv[LOG_LMP_4]      = 0u
/// \input    FctR_unTgtLmpSpdInv[LOG_LMP_4]            = 0u
/// \input    FctR_TgtLgt_Sustain_LogLamp_ucLogLamp     = LOG_LMP_4
/// \input    FctR_ucTgtLgtHighPrio[LOG_LMP_4]          = SBL_StaticBendingLight
/// \input    FctR_ucTgtLgtSustained[LOG_LMP_4]         = SBL_StaticBendingLight
/// \input    FctR_ucTgtLgtHighPrioPrevious[LOG_LMP_4]  = CL_CorneringLight
/// \input    FctR_pCodingArea->PXA.DimmingTimes.ucCOUNTRY_TO_ADVERSEW = 20u //20s
/// \input    FctR_eActLgtClSbl                         = LB_AdverseWeather_RHD
/// \input    FctR_ucClSblTargetState                   = FCTR_CFG_SBL_CL_TOWN
/// \input    FctR_ucTgtLmpInt[LOG_LMP_4]               = LGHT_CFG_PWM_100
/// \input    FctR_ucActLmpInt[LOG_LMP_4]               = LGHT_CFG_PWM_100
///
/// - Expectations: 
///
/// \output   FctR_ucTgtLmpInt[LOG_LMP_4]           = LGHT_CFG_PWM_70
/// \output   FctR_ucTgtClSblLmpInt_Prv[LOG_LMP_4]  = LGHT_CFG_PWM_70
/// \output   FctR_unTgtLmpSpdInv[LOG_LMP_4]        = 100u
/// \output   FctR_unTgtLmpSpdInv_sk[LOG_LMP_4]     = 66u
/// \output   FctR_ucTgtLgtSustained[LOG_LMP_4]     = SBL_StaticBendingLight
/// \output   FctR_ucTgtLgtHighPrio[LOG_LMP_4]      = SBL_StaticBendingLight
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Sustain(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_ucCodingState                    = FCTR_CODING_VALID;
  FctR_ucTgtClSblLmpInt_Prv[LOG_LMP_4]  = 0u;
  FctR_unTgtLmpSpdInv[LOG_LMP_4]        = 0u;

  //Step 2) Assign Input values
  FctR_TgtLgt_Sustain_LogLamp_ucLogLamp     = LOG_LMP_4;    // Illuminant 4 - LB [SBL]
  FctR_ucTgtLgtHighPrio[LOG_LMP_4]          = SBL_StaticBendingLight;
  FctR_ucTgtLgtSustained[LOG_LMP_4]         = SBL_StaticBendingLight;
  FctR_ucTgtLgtHighPrioPrevious[LOG_LMP_4]  = CL_CorneringLight;
  FctR_pCodingArea->PXA.DimmingTimes.ucCOUNTRY_TO_ADVERSEW = 20u; //20ms
  FctR_eActLgtClSbl                         = LB_AdverseWeather_RHD;
  FctR_ucClSblTargetState                   = FCTR_CFG_SBL_CL_TOWN;
  FctR_ucTgtLmpInt[LOG_LMP_4]               = LGHT_CFG_PWM_100;
  FctR_ucActLmpInt[LOG_LMP_4]               = LGHT_CFG_PWM_100;

  /* Test case covers Sustained == Actual, but Previous != Actual*/
  //Step 3) Call FUT
  FctR_TgtLgt_Sustain();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_ucTgtLmpInt[LOG_LMP_4],                   LGHT_CFG_PWM_70, == );   //target changed with AFS mode ActLgtClSbl = Adverse Weather intensity
  AL_UNITTEST_CHECK(FctR_ucTgtClSblLmpInt_Prv[LOG_LMP_4],          LGHT_CFG_PWM_70, == ); 
  AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv[LOG_LMP_4],                           100u, == );
  AL_UNITTEST_CHECK(FctR_unTgtLmpSpdInv_sk[LOG_LMP_4],                         66u, == );
  AL_UNITTEST_CHECK(FctR_ucTgtLgtSustained[LOG_LMP_4],      SBL_StaticBendingLight, == );
  AL_UNITTEST_CHECK(FctR_ucTgtLgtHighPrio[LOG_LMP_4],       SBL_StaticBendingLight, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_Output
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the output values of light functions are calculated
///                         according to the failure status
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_ucTgtLmpInt[ucLogLamp]                                             = 1u
/// \input    FctR_unTgtLmpSpdInv[ucLogLamp]                                          = 1u
/// \input    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unTgtIntensity = 0u
/// \input    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unRampTime     = 0u
/// \input    Rte_Write_FctR_TgtLed_sVal_HitCount                                     = 0u
/// \input    Rte_Write_FctR_AfsDblCmd_HitCount                                       = 0u
/// \input    Rte_Write_FctR_AfsModeSig_sVal_HitCount                                 = 0u
/// \input    FctR_ucTgtLgtHighPrioPrevious[LOG_LMP_3]                = LB_Boost
/// \input    FctR_ucTgtLgtHighPrio[LOG_LMP_2]                        = LB_CountryLight
/// \input    FctR_ucTgtLgtHighPrio[LOG_LMP_3]                        = LB_MotorwayLight
/// \input    FctR_ucTgtLgtHighPrio[LOG_LMP_4]                        = LB_MotorwayLight
/// \input    FctR_ucTgtLgtHighPrio[LOG_LMP_8]                        = POS_PositionLight
/// \input    FctR_ucTgtLgtHighPrioFbit[LOG_LMP_8]                    = DRL_DaytimeRunningLight
/// \input    FctR_ucTgtLgtHighPrio[LOG_LMP_11]                       = LOG_LMP__UKN
/// \input    FctR_ucTgtLgtHighPrioFbit[LOG_LMP_11]                   = LB_CountryLight
/// \input    FctR_LgtFctFailureFBit.Bits.biLB_MotorwayLight          = TRUE
/// \input    FctR_LgtFctFailureFBit.Bits.biHB_HighBeam               = TRUE
/// \input    FctR_LgtFctFailureFBit.Bits.biLB_CountryLight           = TRUE
/// \input    FctR_LgtFctFailureFBit.Bits.biDRL_DaytimeRunningLight   = TRUE
///
/// - Expectations: 
///
/// \output   Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unTgtIntensity = 10u
/// \output   Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unRampTime     = 20u
/// \output   Rte_Write_FctR_TgtLed_sVal_HitCount                                     = 1u
/// \output   Rte_Write_FctR_AfsDblCmd_HitCount                                       = 1u
/// \output   Rte_Write_FctR_AfsModeSig_sVal_HitCount                                 = 1u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_Output(void)
{

  //Step 1) Set pre-conditions
  Rte_Write_FctR_TgtLed_sVal_HitCount     = 0u;
  Rte_Write_FctR_AfsDblCmd_HitCount       = 0u;
  Rte_Write_FctR_AfsModeSig_sVal_HitCount = 0u;

  //Step 2) Assign Input values
  for (uint8 ucLogLamp = 0u; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {
    FctR_ucTgtLmpInt[ucLogLamp]                                             = 1u;
    FctR_unTgtLmpSpdInv[ucLogLamp]                                          = 1u;
    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unTgtIntensity = 0u;
    Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unRampTime     = 0u;
  }
  
  /* assign LFs for Log Lamps*/
  FctR_ucTgtLgtHighPrioPrevious[LOG_LMP_3] = LB_Boost;
  FctR_ucTgtLgtHighPrio[LOG_LMP_2]         = LB_CountryLight;
  FctR_ucTgtLgtHighPrio[LOG_LMP_3]         = LB_MotorwayLight;
  FctR_ucTgtLgtHighPrio[LOG_LMP_4]         = LB_MotorwayLight;

  /* check for actual f bit for high prio light is present AND high prio light is OFF*/
  FctR_ucTgtLgtHighPrio[LOG_LMP_8]         = POS_PositionLight;
  FctR_ucTgtLgtHighPrioFbit[LOG_LMP_8]     = DRL_DaytimeRunningLight;

  /* check for invalid LF*/
  FctR_ucTgtLgtHighPrio[LOG_LMP_11] = LOG_LMP__UKN;
  FctR_ucTgtLgtHighPrioFbit[LOG_LMP_11] = LB_CountryLight;

  /* set failure for LFs */
  FctR_LgtFctFailureFBit.ulRaw = (uint32)0x0000u;
  FctR_LgtFctFailureFBit.Bits.biLB_MotorwayLight          = TRUE;
  FctR_LgtFctFailureFBit.Bits.biHB_HighBeam               = TRUE;
  FctR_LgtFctFailureFBit.Bits.biLB_CountryLight           = TRUE;
  FctR_LgtFctFailureFBit.Bits.biDRL_DaytimeRunningLight   = TRUE;

  //Step 3) Call FUT
  FctR_TgtLgt_Output();

  //Step 4) Check expected output values
  for (uint8 ucLogLamp = 0u; ucLogLamp < FCTR_CFG_LOGLMP_MAX; ucLogLamp++)
  {
    if( (ucLogLamp != LOG_LMP_2) &&  (ucLogLamp != LOG_LMP_3)  && (ucLogLamp != LOG_LMP_4) && (ucLogLamp != LOG_LMP_5)) //because of failure on Light Function => switch off
    {
      AL_UNITTEST_CHECK(Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unTgtIntensity, 10u, == );
      AL_UNITTEST_CHECK(Rte_Write_FctR_TgtLed_sVal_Param1.asTgtLedVal[ucLogLamp].unRampTime, 20u, == );
    }
  }

  AL_UNITTEST_CHECK(Rte_Write_FctR_TgtLed_sVal_HitCount,      1u, ==);
  AL_UNITTEST_CHECK(Rte_Write_FctR_AfsDblCmd_HitCount,        1u, ==);
  AL_UNITTEST_CHECK(Rte_Write_FctR_AfsModeSig_sVal_HitCount,  1u, ==);
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_KeepTiStatusOn
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the DBL activation and deactivation command
///                        is computed correctly on the low beam and high beam
///                        distribution
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sCurrentReq   : input light functions requests
///
///   - Expectations:
///
/// \output  eTgtDblCmd   :  output value for dynamic bending light (DBL) command
///
//-----------------------------------------------------------------------------
void Mt_FctR_KeepTiStatusOn(void)
{
  struct { boolean boTIBlinking; uint32 ulTimerValue;  boolean boTiStatus; }asTestCaseData[] =
         {
           {              TRUE,                   0u,              TRUE    },
           {              FALSE,                  0u,              TRUE    },
           {              FALSE,             500005u,             FALSE    },
         };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_sLightStatus.boTiBlink_Status  = asTestCaseData[ucIdx].boTIBlinking;
    LPTMR0_GetTimeElapsed_RetVal        = asTestCaseData[ucIdx].ulTimerValue;

    //Step 3) Call the FUT
    FctR_KeepTiStatusOn();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_sLightStatus.boTi_Status, asTestCaseData[ucIdx].boTiStatus, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtDbl_Output
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the DBL activation and deactivation command
///                        is computed correctly on the low beam and high beam
///                        distribution
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sCurrentReq   : input light functions requests
///
///   - Expectations:
///
/// \output  eTgtDblCmd   :  output value for dynamic bending light (DBL) command
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtDbl_Output(void)
{

  struct { tsFctR_TgtLgtReq sCurrentReq;    teFctR_DblCommand eTgtDblCmd; } asTestCaseData[] =
  {
         {             (uint32)0x22000u,                       PLAY_DBL  },  // HB and HB Flash req
         {            (uint32)0x800000u,                       STOP_DBL  },  // Position Light req
         {                (uint32)0x01u,                       PLAY_DBL  },  // LB Town
         {               (uint32)0x100u,                       STOP_DBL  },  // Foggy weather
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    Rte_Write_FctR_AfsDblCmd_Param1.Primary = STOP_DBL;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtLgtReq.Req.ulRaw = asTestCaseData[ucIdx].sCurrentReq.Req.ulRaw;

    //Step 3) Call the FUT
    FctR_TgtDbl_Output();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Rte_Write_FctR_AfsDblCmd_Param1.Primary, asTestCaseData[ucIdx].eTgtDblCmd, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_CheckSblCl_LightStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the Cornering Light / Static Bending Light 
///                         active status is set correctly based on the sustained
///                         light function
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucLogLmp         : input illuminant (log lamp) index
/// \input ucLgtSustained   : input light function active on current illuminant
///
///   - Expectations:
///
/// \output  boSblClActive  :  SBL/CL function active status
///
//-----------------------------------------------------------------------------
void Mt_FctR_CheckSblCl_LightStatus(void)
{
  for (uint8 ucIlIdx = 0u; ucIlIdx < FCTR_CFG_LOGLMP_MAX; ucIlIdx++) { FctR_ucTgtLgtSustained[ucIlIdx] = 0xFFu; }

  struct { uint8 ucLogLmp;      uint8 ucLgtSustained;   boolean boSblClActive;  } asTestCaseData[] =
  {
         {      LOG_LMP_8,      PKL_ParkingLight,                       FALSE   },
         {      LOG_LMP_3,      FL_FogLight,                            FALSE   },
         {      LOG_LMP_8,      SBL_StaticBendingLight,                  TRUE   },
         {      LOG_LMP_9,      CL_CorneringLight,                       TRUE   },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    FctR_CheckSblCl_LightStatus_RetVal = FALSE;
    uint8 ucIllIdx = asTestCaseData[ucIdx].ucLogLmp;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_ucTgtLgtSustained[ucIllIdx] = asTestCaseData[ucIdx].ucLgtSustained;

    //Step 3) Call the FUT
    FctR_CheckSblCl_LightStatus_RetVal = FctR_CheckSblCl_LightStatus();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_CheckSblCl_LightStatus_RetVal, asTestCaseData[ucIdx].boSblClActive, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_TgtLgt_StorePrep
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the light requests are prepared taking into
///                         account also the battery voltage range
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    FctR_TgtLgtReq.Req.ulRaw     = (uint32)0u
/// \input    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1 = SysVolt_eLow2
/// \input    FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x2004
///
/// - Expectations: 
///
/// \output   FctR_TgtLgtReq.Req.ulRaw     = 0u
///
//-----------------------------------------------------------------------------
void Mt_FctR_TgtLgt_StorePrep(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  FctR_TgtLgtReq.Req.ulRaw     = (uint32)0u;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1 = SysVolt_eLow2;
  FctR_TgtLgtReqPrep.Req.ulRaw = (uint32)0x2004;    // LB_CountryLight & HB_HighBeam

  //Step 3) Call FUT
  FctR_TgtLgt_StorePrep();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_TgtLgtReq.Req.ulRaw, 0u, ==);  //light is not allowed to be switched off in case of battery voltage issue
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_SetLgtReq_VoltCond
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the battery voltage range is evaluated 
///                        in the activation of light function requested
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sCurrentReq   : input light functions requests
/// \input ucVoltRange   : input battery voltage range
///
///   - Expectations:
///
/// \output  sActualReq   :  light functions requests active
///
//-----------------------------------------------------------------------------
void Mt_FctR_SetLgtReq_VoltCond(void)
{

  struct { tsFctR_TgtLgtReq sCurrentReq;    uint8 ucVoltRange; tsFctR_TgtLgtReq sActualReq; } asTestCaseData[] =
  {
         {             (uint32)0x22000u,    FCTR_LOW2_VOLT,                  (uint32)0x00u  },  // HB and HB Flash req + battery issues = no light
         {            (uint32)0x800000u,    FCTR_UNKNOWN_VOLT,               (uint32)0x00u  },  // Position Light req  + range issues   = no light
         {                (uint32)0x11u,    FCTR_NORMAL_VOLT,                (uint32)0x11u  },  // LB Town + LB_Boost  + battery normal = req. light
         {                (uint32)0x15u,    FCTR_LOW1_VOLT,                  (uint32)0x11u  },  // LB Town + LB_Boost + LB Country + battery issue = do not allow new request (country not accepted)
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_SetLgtReq_VoltCond_sCurReq.Req.ulRaw = asTestCaseData[ucIdx].sCurrentReq.Req.ulRaw;
    FctR_SetLgtReq_VoltCond_ucVoltRange       = asTestCaseData[ucIdx].ucVoltRange;

    //Step 3) Call the FUT
    FctR_SetLgtReq_VoltCond_RetVal = FctR_SetLgtReq_VoltCond(FctR_SetLgtReq_VoltCond_sCurReq, FctR_SetLgtReq_VoltCond_ucVoltRange);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_SetLgtReq_VoltCond_RetVal.Req.ulRaw, asTestCaseData[ucIdx].sActualReq.Req.ulRaw, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_StoreIlluminantFailureFunction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test the failure status of light functions is set correctly
///                        based on the failure status and light functionality served 
///                        by each illuminant
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucIlluminantName[FCTR_CFG_LOGLMP_MAX]    : input light functionality for each illuminant 
/// \input boIlluminantFailure[FCTR_CFG_LOGLMP_MAX] : input failure status for each illuminant
/// \input ulLgtActive                              : input light functions requests
///
///   - Expectations:
///
/// \output  sLightFailureStatus                    :  light functions failure status
///
//-----------------------------------------------------------------------------
void Mt_FctR_StoreIlluminantFailureFunction(void)
{

  struct { uint8 ucIlluminantName[FCTR_CFG_LOGLMP_MAX];  uint8 boIlluminantFailure[FCTR_CFG_LOGLMP_MAX];                       uint32 ulLgtActive;     tsFctR_LightFailureStatus sLightFailureStatus; } asTestCaseData[] =
    {                                                                                                                                                 /*  Lb | Sbl| Ti| Hb|GfHb| Drl| Pos */
 /*TC1) */ {  { FCTR_CH_UNKNOWN_NAME, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, \
              { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },         (uint32)0x00u,     {   0u,   0u, 0u, 0u,  0u,  0u,  0u  }          },
    \
 /*TC2) */ {  { FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB, FCTR_CH_NAME_LB, FCTR_CH_NAME_CL, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_TI, FCTR_CH_NAME_PXL_LB, FCTR_CH_NAME_SM, FCTR_CH_NAME_FOG, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB }, \
              { TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE },                     (uint32)0x00u,     {   1u,   0u, 0u, 1u,  1u,  0u,  0u  }          },
    \
 /*TC3) */ {  { FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB, FCTR_CH_NAME_LB, FCTR_CH_NAME_CL, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_TI, FCTR_CH_NAME_PXL_LB, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB }, \
              { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE },                 (uint32)0xC00000u,     {   1u,   1u, 1u, 1u,  1u,  1u,  1u  }          },
    \
 /*TC4) */ {  { FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB, FCTR_CH_NAME_LB, FCTR_CH_NAME_CL, FCTR_CH_NAME_RGB, FCTR_CH_NAME_SM, FCTR_CH_NAME_TI_SCRL, FCTR_CH_NAME_TI, FCTR_CH_NAME_PXL_LB, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB }, \
              { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE },                 (uint32)0xC00000u,     {   1u,   1u, 1u, 1u,  1u,  0u,  0u  }          },
    };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    for (uint8 ucIlIdx = 0u; ucIlIdx < FCTR_CFG_LOGLMP_MAX; ucIlIdx++) {
      FctR_ActIlluminantStates[ucIlIdx].ucIlluminantName    = asTestCaseData[ucIdx].ucIlluminantName[ucIlIdx];
      FctR_ActIlluminantStates[ucIlIdx].boIlFailureStatus   = asTestCaseData[ucIdx].boIlluminantFailure[ucIlIdx];
    }

    FctR_TgtLgtReq.Req.ulRaw  = asTestCaseData[ucIdx].ulLgtActive;

    //Step 3) Call the FUT
    FctR_StoreIlluminantFailureFunction();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boLb_State,        asTestCaseData[ucIdx].sLightFailureStatus.boLb_State,       == );
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boSbl_State,       asTestCaseData[ucIdx].sLightFailureStatus.boSbl_State,      == );
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boTi_State,        asTestCaseData[ucIdx].sLightFailureStatus.boTi_State,       == );
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boHb_State,        asTestCaseData[ucIdx].sLightFailureStatus.boHb_State,       == );
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boGfHb_State,      asTestCaseData[ucIdx].sLightFailureStatus.boGfHb_State,     == );
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boDrl_State,       asTestCaseData[ucIdx].sLightFailureStatus.boDrl_State,      == );
    AL_UNITTEST_CHECK(FctR_sLightFailureStatus.boPos_State,       asTestCaseData[ucIdx].sLightFailureStatus.boPos_State,      == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_StoreIlluminantStatusFunction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test the status of active light functions is set correctly
///                        based on the active status  and light functionality served 
///                        by each illuminant
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucIlluminantName[FCTR_CFG_LOGLMP_MAX]   : input light functionality for each illuminant 
/// \input boIlluminantStatus[FCTR_CFG_LOGLMP_MAX] : input active status for each illuminant
/// \input ulLgtActive                             : input light functions requests
///
///   - Expectations:
///
/// \output  sLightActiveStatus                    :  light functions active status
///
//-----------------------------------------------------------------------------
void Mt_FctR_StoreIlluminantStatusFunction(void)
{

  struct { uint8 ucIlluminantName[FCTR_CFG_LOGLMP_MAX];  uint8 boIlluminantStatus[FCTR_CFG_LOGLMP_MAX];                       uint32 ulLgtActive;                    tsFctR_LightStatus sLightActiveStatus; } asTestCaseData[] =
    {                                                                                                                                                 /*  Lb | Sbl|TiBlnk| Ti| Hb|GfHb| Drl| Pos| SM| Fog*/
 /*TC1) */ {  { FCTR_CH_UNKNOWN_NAME, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu }, \
              { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },         (uint32)0x00u,     {   0u,   0u,    0u, 0u, 0u,  0u,  0u,  0u, 0u, 0u  } },
    \
 /*TC2) */ {  { FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB, FCTR_CH_NAME_LB, FCTR_CH_NAME_CL, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_TI, FCTR_CH_NAME_PXL_LB, FCTR_CH_NAME_SM, FCTR_CH_NAME_FOG, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB }, \
              { TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE },                     (uint32)0x00u,     {   1u,   0u,    0u, 0u, 1u,  1u,  0u,  0u, 1u, 1u  } },
    \
 /*TC3) */ {  { FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB, FCTR_CH_NAME_LB, FCTR_CH_NAME_CL, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_DRL_POS, FCTR_CH_NAME_TI, FCTR_CH_NAME_PXL_LB, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB }, \
              { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE },                 (uint32)0xC00000u,     {   1u,   1u,    1u, 0u, 1u,  1u,  1u,  1u, 0u, 0u  } },
    \
 /*TC4) */ {  { FCTR_CH_NAME_LB_FUSA, FCTR_CH_NAME_LB, FCTR_CH_NAME_LB, FCTR_CH_NAME_CL, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_TI, FCTR_CH_NAME_PXL_LB, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_UNKNOWN_NAME, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB, FCTR_CH_NAME_PXL_HB }, \
              { TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE },              (uint32)0xC00000u,     {   1u,   1u,    1u, 0u, 1u,  1u,  0u,  0u, 0u, 0u  } },
    };


  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    for (uint8 ucIlIdx = 0u; ucIlIdx < FCTR_CFG_LOGLMP_MAX; ucIlIdx++) {
      FctR_ActIlluminantStates[ucIlIdx].ucIlluminantName    = asTestCaseData[ucIdx].ucIlluminantName[ucIlIdx];
      FctR_ActIlluminantStates[ucIlIdx].boIlluminantStatus  = asTestCaseData[ucIdx].boIlluminantStatus[ucIlIdx];
    }

    FctR_TgtLgtReq.Req.ulRaw  = asTestCaseData[ucIdx].ulLgtActive;

    //Step 3) Call the FUT
    FctR_StoreIlluminantStatusFunction();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_sLightStatus.boLb_Status,        asTestCaseData[ucIdx].sLightActiveStatus.boLb_Status,       == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boSbl_Status,       asTestCaseData[ucIdx].sLightActiveStatus.boSbl_Status,      == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boTiBlink_Status,   asTestCaseData[ucIdx].sLightActiveStatus.boTiBlink_Status,  == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boTi_Status,        asTestCaseData[ucIdx].sLightActiveStatus.boTi_Status,       == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boHb_Status,        asTestCaseData[ucIdx].sLightActiveStatus.boHb_Status,       == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boGfHb_Status,      asTestCaseData[ucIdx].sLightActiveStatus.boGfHb_Status,     == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boDrl_Status,       asTestCaseData[ucIdx].sLightActiveStatus.boDrl_Status,      == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boPos_Status,       asTestCaseData[ucIdx].sLightActiveStatus.boPos_Status,      == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boSM_Status,        asTestCaseData[ucIdx].sLightActiveStatus.boSM_Status,       == );
    AL_UNITTEST_CHECK(FctR_sLightStatus.boFog_Status,       asTestCaseData[ucIdx].sLightActiveStatus.boFog_Status,      == );
  }

}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_DiagFeedback
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the diagnostic feedback is set based on the timer
///                        configuration and force error reset is computed based on input error
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input sTimerCfg       : input timer configuration for a specific light function
/// \input ulTimerElapsed  : timer elapsed time since starting
/// \input boDiagFbk_Prv   : previous status of diagnostic feedbacks
/// \input boForceReset    : error force reset command
///
///   - Expectations:
///
/// \output  boDiagFbk_Act   :  actual status of diagnostic feedbacks
///
//-----------------------------------------------------------------------------
void Mt_FctR_DiagFeedback(void)
{

  struct {                    tsDiagFeedback_Cfg sTimerCfg;       uint32 ulTimerElapsed;  boolean boDiagFbk_Prv; boolean boForceReset; boolean boDiagFbk_Act;  }asTestCaseData[]
    =  { { { TRUE,  TRUE,  0U,     FCTR_CFG_DIAG_FEEDBACK_GFHB, TRUE  },          0U,                     TRUE,                 TRUE,                   TRUE   },
         { { TRUE,  FALSE, 0u,     FCTR_CFG_DIAG_FEEDBACK_GFHB, TRUE  },          0u,                     TRUE,                 FALSE,                  FALSE  },
         { { TRUE,  TRUE,  15000u, FCTR_CFG_DIAG_FEEDBACK_LB,   TRUE  },          1000u,                  FALSE,                FALSE,                  FALSE  },
         { { TRUE,  TRUE,  25000u, FCTR_CFG_DIAG_FEEDBACK_LB,   FALSE },          1000u,                  FALSE,                TRUE,                   TRUE   },
         { { TRUE,  FALSE, 25000u, FCTR_CFG_DIAG_FEEDBACK_POS,  FALSE },          1000u,                  FALSE,                FALSE,                  FALSE  },
         { { FALSE, FALSE, 25000u, FCTR_CFG_DIAG_FEEDBACK_POS,  FALSE },          1000u,                  TRUE,                 FALSE,                  TRUE   },
         { { FALSE, FALSE, 25000u, FCTR_CFG_DIAG_FEEDBACK_POS,  FALSE },          1000u,                  TRUE,                 TRUE,                   FALSE  },
      };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    FctR_DiagFeedback_psDiagSettings  = &asTestCaseData[ucIdx].sTimerCfg;
    FctR_DiagFeedback_pboDiagFeedback = &asTestCaseData[ucIdx].boDiagFbk_Prv;
    FctR_DiagFeedback_boForceErrReset = asTestCaseData[ucIdx].boForceReset;
    LPTMR0_GetTimeElapsed_RetVal      = asTestCaseData[ucIdx].ulTimerElapsed;

    //Step 3) Call FUT
    FctR_DiagFeedback(FctR_DiagFeedback_psDiagSettings, FctR_DiagFeedback_pboDiagFeedback, FctR_DiagFeedback_boForceErrReset);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(*FctR_DiagFeedback_pboDiagFeedback, asTestCaseData[ucIdx].boDiagFbk_Act, == );

  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Tgt_HandleLgtFctFailure
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the diagnostic feedback is set based on error detection
///                        and the feedback is sent via RTE
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucDiagLgt       : light function diagnosis to be checked
/// \input boUnderVoltage  : undervoltage status
/// \input sLgtFail        : light function failure status
/// \input boLbCmd         : low beam request status
/// \input boSblTimeOut    : static bending light timeout status
/// \input ulTimeEl        : timer elapsed time since starting
/// \input ulTgtReq        : target light function request
/// \input sVehNet         : vehicle network status
///
///   - Expectations:
///
/// \output  sLgtDiagnosis   :  actual status of diagnostic feedbacks
///
//-----------------------------------------------------------------------------
void Mt_FctR_Tgt_HandleLgtFctFailure(void)
{

  struct {
    uint8 ucDiagLgt;  boolean boUnderVoltage;                   tsFctR_LightFailureStatus sLgtFail;  boolean boLbCmd; boolean boSblTimeOut; uint32 ulTimeEl; uint32 ulTgtReq;            tsRte_SysMon_VehNetState sVehNet;            tsRte_LgtFctState sLgtDiagnosis;
  }asTestCaseData[]
    =  {                                          /* LB |  SBL |   TI |   HB | GFHB |  DRL |   POS */                                                                         /* VESState |     ElecNetState | SigQlty  */          /* LB |  SBL |   TI |   HB | GFHB |  DRL |   POS */
    { FCTR_CFG_DIAG_FEEDBACK_LB,       FALSE,    {  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },          TRUE,               FALSE,            0x00U,           0x00u,  {eState_Start, eState_TA_DEGRADE, SIG_VALID },      {  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  },
    { FCTR_CFG_DIAG_FEEDBACK_LB,        TRUE,    {   TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },          TRUE,               FALSE,            0x00u,           0x00u,  {eState_Start, eState_TA_DEGRADE, SIG_VALID },      {   TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE }  },
    { FCTR_CFG_DIAG_FEEDBACK_SBL,       TRUE,    {  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },         FALSE,                TRUE,            0x00u,           0x00u,  {eState_Start, eState_TA_NOMINAL, SIG_VALID },      {   TRUE,  TRUE, FALSE, FALSE,  TRUE, FALSE, FALSE }  },
    { FCTR_CFG_DIAG_FEEDBACK_SBL,      FALSE,    {  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },         FALSE,               FALSE,            0x00u,           0x00u,  {eState_Start, eState_TA_SECU,    SIG_VALID },      {   TRUE, FALSE, FALSE, FALSE,  TRUE, FALSE, FALSE }  },
    { FCTR_CFG_DIAG_FEEDBACK_GFHB,     FALSE,    {  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },         FALSE,               FALSE,            0x00u,           0x00u,  {eState_Stop,  eState_TI_DEGRADE, SIG_VALID },      {   TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }  },
    { FCTR_CFG_DIAG_FEEDBACK_GFHB,     FALSE,    {  FALSE, FALSE, FALSE, FALSE,  TRUE, FALSE, FALSE },         FALSE,               FALSE,            0x00u,        0x20000u,  {eState_Start, eState_TA_NOMINAL, SIG_VALID },      {   TRUE, FALSE, FALSE, FALSE,  TRUE, FALSE, FALSE }  },  // HB_F2P active
    { FCTR_CFG_DIAG_FEEDBACK_POS,      FALSE,    {  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  },         FALSE,               FALSE,             200u,       0x800000u,  {eState_Start, eState_TA_NOMINAL, SIG_VALID },      {   TRUE, FALSE, FALSE, FALSE,  TRUE, FALSE,  TRUE }  },  // position active
    { FCTR_CFG_DIAG_FEEDBACK_DRL,      FALSE,    {  FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE },         FALSE,               FALSE,             200u,       0x400000u,  {eState_Start, eState_TA_NOMINAL, SIG_VALID },      {   TRUE, FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE }  },  // DRL active
    };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre-conditions
    uint8 ucDiagIdx = asTestCaseData[ucIdx].ucDiagLgt;
    asDiagFeedback_Cfg[ucDiagIdx].boPrvCmd  = FALSE;
    aboDiagFeedback[ucDiagIdx]              = FALSE;
    if (ucIdx > 1u)
    {
      Rte_Read_AdbMxb_Gfhb_Diag_Param1 = TRUE;
      FctR_sLightStatus.boGfHb_Status = FALSE;
    }
    else
    {
      Rte_Read_AdbMxb_Gfhb_Diag_Param1 = FALSE;
      FctR_sLightStatus.boGfHb_Status = TRUE;
    }
    FctR_ucTgtLgtSustained[LOG_LMP_8]       = SBL_StaticBendingLight;
    boMxbFault = TRUE;
    Rte_Read_ppsAdb_Out_sVal_0_Param1.State = 1u;

    tsRte_LgtFctState sDiagStateInit        = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    Rte_Write_FctR_LgtFctState_Param1       = sDiagStateInit;

    //Step 2) Assign Input values
    Rte_Read_DEM_UV_NotifyStatus_Param1     = asTestCaseData[ucIdx].boUnderVoltage;
    Rte_Read_DEM_OV_NotifyStatus_Param1     = asTestCaseData[ucIdx].boUnderVoltage;
    FctR_TgtPrep_boLBCmd                    = asTestCaseData[ucIdx].boLbCmd;
    FctR_sLightFailureStatus                = asTestCaseData[ucIdx].sLgtFail;
    FctR_TgtPrep_boClSblTimeOut             = asTestCaseData[ucIdx].boSblTimeOut;
    Rte_Read_SysMon_VehNetState_Param1      = asTestCaseData[ucIdx].sVehNet;
    FctR_TgtLgtReq.Req.ulRaw                = asTestCaseData[ucIdx].ulTgtReq;
    LPTMR0_GetTimeElapsed_RetVal            = asTestCaseData[ucIdx].ulTimeEl;

    //Step 3) Call FUT
    FctR_Tgt_HandleLgtFctFailure();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctState_Param1.boLb_State,   asTestCaseData[ucIdx].sLgtDiagnosis.boLb_State,   == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctState_Param1.boSbl_State,  asTestCaseData[ucIdx].sLgtDiagnosis.boSbl_State,  == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctState_Param1.boGfHb_State, asTestCaseData[ucIdx].sLgtDiagnosis.boGfHb_State, == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctState_Param1.boPos_State,  asTestCaseData[ucIdx].sLgtDiagnosis.boPos_State,  == );
    AL_UNITTEST_CHECK(Rte_Write_FctR_LgtFctState_Param1.boDrl_State,  asTestCaseData[ucIdx].sLgtDiagnosis.boDrl_State,  == );

  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Get_UnderVoltageStatusDebounced
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test that the function returns the under voltage status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      Rte_Read_DEM_UV_NotifyStatus_Param1          = TRUE
/// \input      FctR_RteAccess_Read_UV_Status_pboStatus      = FALSE
/// \input      FctR_Get_UnderVoltageStatusDebounced_RetVal  = FALSE
///
/// - Expectations: 
///
/// \output     FctR_Get_UnderVoltageStatusDebounced_RetVal =  TRUE
///
//-----------------------------------------------------------------------------
void Mt_FctR_Get_UnderVoltageStatusDebounced(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_DEM_UV_NotifyStatus_Param1          = TRUE;
  FctR_RteAccess_Read_UV_Status_pboStatus      = FALSE;
  FctR_Get_UnderVoltageStatusDebounced_RetVal  = FALSE;

  //Step 3) Call FUT
  FctR_Get_UnderVoltageStatusDebounced_RetVal = FctR_Get_UnderVoltageStatusDebounced();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_Get_UnderVoltageStatusDebounced_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Get_OverVoltageStatusDebounced
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Test that the function returns the over voltage status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     Rte_Read_DEM_OV_NotifyStatus_Param1          = FALSE
/// \input     FctR_RteAccess_Read_OV_Status_pboStatus      = TRUE
/// \input     FctR_Get_OverVoltageStatusDebounced_RetVal   = TRUE
///
/// - Expectations: 
///
/// \output    FctR_Get_OverVoltageStatusDebounced_RetVal =   FALSE
///
//-----------------------------------------------------------------------------
void Mt_FctR_Get_OverVoltageStatusDebounced(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_DEM_OV_NotifyStatus_Param1            = FALSE;
  FctR_RteAccess_Read_OV_Status_pboStatus        = TRUE;
  FctR_Get_OverVoltageStatusDebounced_RetVal     = TRUE;

  //Step 3) Call FUT
  FctR_Get_OverVoltageStatusDebounced_RetVal = FctR_Get_OverVoltageStatusDebounced();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(FctR_Get_OverVoltageStatusDebounced_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Tgt_LgtFctFailureReaction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the affected light function  is set in case
///                        the F-bit is active
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input ucLogLamp           : input illuminant index
/// \input ucLgtFct            : input light function 
/// \input boIlFailureStatus   : failure status of the illuminant
/// \input ulFailureFBitStatus : failure bit (F-bit) active status for the light function
///
///   - Expectations:
///
/// \output  ulFctR_LgtFctFailureFBit   :  light function failure bit set
///
//-----------------------------------------------------------------------------
void Mt_FctR_Tgt_LgtFctFailureReaction(void)
{

  struct { uint8 ucLogLamp;         uint8 ucLgtFct; boolean boIlFailureStatus; uint32 ulFailureFBitStatus;  uint32 ulFctR_LgtFctFailureFBit;  } asTestCaseData[] =
  {
         {       LOG_LMP_2, LB_CountryLight,                            FALSE,           (uint32)0x00u,                      (uint32)0x00u     },
         {       LOG_LMP_8, FCTR_CFG_LGTFCT_MAX,                        TRUE,            (uint32)0x00u,                      (uint32)0x00u     },   //invalid case
         {       LOG_LMP_9, DRL_DaytimeRunningLight,                    TRUE,            (uint32)0x00u,                      (uint32)0x400000u },
         {       LOG_LMP_8, DRL_DaytimeRunningLight,                    TRUE,            (uint32)0x400000u,                  (uint32)0x400000u },  // Failure on LFs remains set from previous case
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    uint8_fast   ucLogLmpIdx        = asTestCaseData[ucIdx].ucLogLamp;
    FctR_LgtFctFailureFBit.ulRaw    = asTestCaseData[ucIdx].ulFailureFBitStatus;
    FctR_ActIlluminantStates[ucLogLmpIdx].boIlluminantStatus = FALSE;  //make status OFF for the Illuminant considering they have been switched off because  of failure

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_ucTgtLgtHighPrio[ucLogLmpIdx]                      = asTestCaseData[ucIdx].ucLgtFct;
    FctR_ActIlluminantStates[ucLogLmpIdx].boIlFailureStatus = asTestCaseData[ucIdx].boIlFailureStatus;

    //Step 3) Call the FUT
    FctR_Tgt_LgtFctFailureReaction();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_LgtFctFailureFBit.ulRaw, asTestCaseData[ucIdx].ulFctR_LgtFctFailureFBit, == );
  }
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_ProccessAimingMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Check that the function will go thorugh each state of
///                        aiming mode, start by blinking and then keep function active
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boAimingActive : aiming mode request
/// \input eAimingMode    : input aiming mode state
/// \input ulTmrStart     : input start time of timer
/// \input ulTmrElapsed   : time elapsed since timer started
///
///   - Expectations:
///
/// \output  ucCntAiming             : aiming counter value (max = FCTR_AIM_COUNTER = 10 )
/// \output  eAimingModeTransition   :  aiming mode state transition
///
//-----------------------------------------------------------------------------
void Mt_FctR_ProccessAimingMode(void)
{

  struct { boolean boAimingActive;    FctR_eAimingType eAimingMode;   uint32 ulTmrStart; uint32 ulTmrElapsed; uint8 ucCntAiming;  FctR_eAimingType eAimingModeTransition; }asTestCaseData[]
    = {
         {                  FALSE,                      eAimingOff,                  0u,                 0u,                0u,             eAimingOff     },  // counter, timer = 0
         {                   TRUE,                      eAimingOff,                  0u,                 0u,                0u,             eBlinkOn       },  // counter, timer = 0
         {                  FALSE,                        eBlinkOn,                  0u,                 0u,                0u,             eAimingOff     },  // counter, timer = 0
         {                   TRUE,                        eBlinkOn,                 10u,              1000u,                0u,             eBlinkOn       },  // keep state
         {                  FALSE,                          eAimOn,                  0u,                 0u,                0u,             eAimingOff     },  // no more aiming req -> OFF state
         {                   TRUE,                          eAimOn,                  0u,                 0u,                0u,             eAimOn         },  // aiming req -> keep state
         {                   TRUE,                              4u,                 10u,                10u,                0u,             4u             },  // unknown aiming state
         /* keep the same order!!!  blinking phase ON  for Aiming -> for 10 times switch to Blink OFF */
  /*1*/  {                   TRUE,                        eBlinkOn,                 20u,            100000u,                1u,             eBlinkOff      },  // counter = 1 -> keep state until cnt reaches max
  /*2*/  {                   TRUE,                        eBlinkOn,                 30u,            100000u,                2u,             eBlinkOff      },  // counter = 2
  /*3*/  {                   TRUE,                        eBlinkOn,                 40u,            100000u,                3u,             eBlinkOff      },  // counter = 3
  /*4*/  {                   TRUE,                        eBlinkOn,                 50u,            100000u,                4u,             eBlinkOff      },  // counter = 4
  /*5*/  {                   TRUE,                        eBlinkOn,                 60u,            100000u,                5u,             eBlinkOff      },  // counter = 5
  /*6*/  {                   TRUE,                        eBlinkOn,                 70u,            100000u,                6u,             eBlinkOff      },  // counter = 6
  /*7*/  {                   TRUE,                        eBlinkOn,                 80u,            100000u,                7u,             eBlinkOff      },  // counter = 7
  /*8*/  {                   TRUE,                        eBlinkOn,                 90u,            100000u,                8u,             eBlinkOff      },  // counter = 8
  /*9*/  {                   TRUE,                        eBlinkOn,                100u,            100000u,                9u,             eBlinkOff      },  // counter = 9
  /*10*/ {                   TRUE,                        eBlinkOn,                 10u,            100000u,  FCTR_AIM_COUNTER,             eAimOn         },  // counter reached FCTR_AIM_COUNTER = 10
         /* end blinking phase for Aiming -> 10 times reached ->  switch to Aiming ON*/
         /* start blinking phase OFF for Aiming -> for 10 times switch to Blink ON */
  /*10*/ {                   TRUE,                       eBlinkOff,                 20u,            100000u,  FCTR_AIM_COUNTER,             eAimOn         },  // counter reached FCTR_AIM_COUNTER = 10 in BlinkOn state
         /* end blinking phase for Aiming -> 10 times reached  -> switch to Aiming ON */
         {                  FALSE,                       eBlinkOff,                  0u,                 0u,                0u,             eAimingOff     },  // no more aiming req -> OFF state
         {                   TRUE,                       eBlinkOff,                  0u,                 0u,                0u,             eBlinkOff      },  // keep state
         {                   TRUE,                       eBlinkOff,                 20u,            100000u,                0u,             eBlinkOn       },  // counter not reached FCTR_AIM_COUNTER
    };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    FctR_ulAimBlinkTime = 10u; // 10ms

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_TgtPrep_sAfsSignals.boAimingMode_Activation  = asTestCaseData[ucIdx].boAimingActive;
    FctR_eAimingMode                                  = asTestCaseData[ucIdx].eAimingMode;
    ulTimerStart                                      = asTestCaseData[ucIdx].ulTmrStart;
    LPTMR0_GetTimeElapsed_RetVal = asTestCaseData[ucIdx].ulTmrElapsed;

    //Step 3) Call the FUT
    FctR_ProccessAimingMode();

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_eAimingMode,       asTestCaseData[ucIdx].eAimingModeTransition,  == );
    AL_UNITTEST_CHECK(ucCounter,              asTestCaseData[ucIdx].ucCntAiming,            == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_CtrlDelayStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the function configures the timer and 
///                        calculates the timing delay 
///
///    - Test Design Technique: DT( Decision Table )
///
///  \DT-Info:
///
///   - Inputs:
///
/// \input boReqInput      : input light request status
/// \input ulTimeM         : input timer value (ms)
/// \input scTiTimerSel    : timer selection
///
///   - Expectations:
///
/// \output  ucTimersDelayStatus   :  timer timeout status
///
//-----------------------------------------------------------------------------
void Mt_FctR_CtrlDelayStatus(void)
{

  struct { boolean boReqInput;  TIMER ulTimeM;        sint8 scTiTimerSel;     uint8 ucTimersDelayStatus } asTestCaseData[] =
  {
         {              TRUE,           1000u,    FCTR_NUMBER_OF_TIMERS,      FCTR_INVALID_TIMER_CONFIG },
         {              FALSE,          5000u,    FCTR_HB_FAULT_DETECTION,    FALSE                     },
         {              TRUE,           2000u,    FCTR_HB_FAULT_DETECTION,    FALSE                     },
         {              FALSE,          1000u,    FCTR_LB_FAULT_DETECTION,    FALSE                     },
         {              TRUE,           0u,       FCTR_LB_FAULT_DETECTION,    TRUE                      },
  };

  for (uint8 ucIdx = 0u; ucIdx < _countof(asTestCaseData); ucIdx++)
  {
    //Step 1) Set pre - conditions
    LPTMR0_GetTimeElapsed_RetVal      = asTestCaseData[ucIdx].ulTimeM;

    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FctR_CtrlDelayStatus_boReqInput   = asTestCaseData[ucIdx].boReqInput;
    FctR_CtrlDelayStatus_ulTimeMs     = asTestCaseData[ucIdx].ulTimeM;
    FctR_CtrlDelayStatus_scTiTimerSel = asTestCaseData[ucIdx].scTiTimerSel;

    //Step 3) Call the FUT
    FctR_CtrlDelayStatus_RetVal = FctR_CtrlDelayStatus(FctR_CtrlDelayStatus_boReqInput, FctR_CtrlDelayStatus_ulTimeMs, FctR_CtrlDelayStatus_scTiTimerSel);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(FctR_CtrlDelayStatus_RetVal, asTestCaseData[ucIdx].ucTimersDelayStatus, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_SpecialBehaviorDrlPos
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the function detects failure on DRL
///                        and in case DRL and POS are requested and failure bit is set
///                        then the TRUE value will force to turn off DRL request and
///                        the FALSE value will keep DRL activated
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///
///   - Inputs:
///
/// \input FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight     = 1u;
/// \input FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight           = 1u;
/// \input FctR_DRLIlluminantsErr                                = 1u;
/// \input FctR_Cod_DRLIlluminantsFBit                           = 1u;
/// \input FctR_SpecialBehaviorDrlPos_RetVal                     = FALSE;
///
///   - Expectations:
///
/// \output FctR_SpecialBehaviorDrlPos_RetVal                    = TRUE;
///
//-----------------------------------------------------------------------------
void Mt_FctR_SpecialBehaviorDrlPos(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  FctR_TgtLgtReq.Req.Bits.biDRL_DaytimeRunningLight = 1u;
  FctR_TgtLgtReq.Req.Bits.biPOS_PositionLight = 1u;
  FctR_DRLIlluminantsErr = 1u;
  FctR_Cod_DRLIlluminantsFBit = 1u;
  FctR_SpecialBehaviorDrlPos_RetVal = FALSE;

  //Step 3) Call the FUT
  FctR_SpecialBehaviorDrlPos_RetVal = FctR_SpecialBehaviorDrlPos();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(FctR_SpecialBehaviorDrlPos_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_FctR_Tgt_GetActLedState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:     Test that the function gets actual LED states
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///
///   - Inputs:
///
/// \input Rte_Read_CtrlLed_ActLed_sState_Param1.boIlluminantStatus[0u]     = TRUE;
/// \input Rte_Read_CtrlLed_ActLed_sState_Param1.ucIlluminantFctName[0u]    = 3u;
/// \input Rte_Read_CtrlLed_ActLed_sState_Param1.uIlluminantState[0u].unRaw = 0xFFFFu;
///
///   - Expectations:
///
/// \output FctR_DRLIlluminantsErr                                          != 0u;
///
//-----------------------------------------------------------------------------
void Mt_FctR_Tgt_GetActLedState(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  Rte_Read_CtrlLed_ActLed_sState_Param1.boIlluminantStatus[0u] = TRUE;
  Rte_Read_CtrlLed_ActLed_sState_Param1.ucIlluminantFctName[0u] = 3u;
  Rte_Read_CtrlLed_ActLed_sState_Param1.uIlluminantState[0u].unRaw = 0xFFFFu;

  //Step 3) Call the FUT
  FctR_Tgt_GetActLedState();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  AL_UNITTEST_CHECK(FctR_DRLIlluminantsErr, 0u, != );
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
  //initialize the coding for FctR
  Mt_Init_LmmABlock_And_CodingLmmX();


  // ctaaFctR.c
  ALUnitTest_AddFunction("Mt_riFctRInit",                                 Mt_riFctRInit);
  ALUnitTest_AddFunction("Mt_rpFctR_Cycle",                               Mt_rpFctR_Cycle);

  // FctR.c
  ALUnitTest_AddFunction("Mt_FctR_Init",                                  Mt_FctR_Init);
  ALUnitTest_AddFunction("Mt_FctR_Cycle",                                 Mt_FctR_Cycle);
  ALUnitTest_AddFunction("Mt_FctR_ParaFct0",                              Mt_FctR_ParaFct0);

  //FctR_Data
  // ALUnitTest_AddFunction("Mt_FctR_Cod_Valid", Mt_FctR_Cod_Valid);   // to be created (optional)


  // FctR_RteAccess.c
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_MapAfsMode",                  Mt_FctR_RteAccess_MapAfsMode);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_MapGfHbSignals",              Mt_FctR_RteAccess_MapGfHbSignals);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_MapTiStatus",                 Mt_FctR_RteAccess_MapTiStatus);
 // ALUnitTest_AddFunction("Mt_FctR_RteAccess_Get_FailureGfHB",             Mt_FctR_RteAccess_Get_FailureGfHB);    // to be created

  /*write*/
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_TgtLedsVal",            Mt_FctR_RteAccess_Write_TgtLedsVal);
 // ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_LgtFctState",          Mt_FctR_RteAccess_Write_LgtFctState);    // to be created (optional)
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_LgtFctStatus",          Mt_FctR_RteAccess_Write_LgtFctStatus);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_TiWarningMode",         Mt_FctR_RteAccess_Write_TiWarningMode);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_GfHbCmd",               Mt_FctR_RteAccess_Write_GfHbCmd);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_DblCmd",                Mt_FctR_RteAccess_Write_DblCmd);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Write_AfsMode",               Mt_FctR_RteAccess_Write_AfsMode);

  /* read */
  //ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_ActLedState",            Mt_FctR_RteAccess_Read_ActLedState);    // to be created (optional)
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_VehNetState",            Mt_FctR_RteAccess_Read_VehNetState);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_EngineState",            Mt_FctR_RteAccess_Read_EngineState);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_StdLgtFctReq",           Mt_FctR_RteAccess_Read_StdLgtFctReq);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_AfsSignals",             Mt_FctR_RteAccess_Read_AfsSignals);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_ReadVehicleModeConfig",       Mt_FctR_RteAccess_ReadVehicleModeConfig);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_TiRequest",              Mt_FctR_RteAccess_Read_TiRequest);
 // ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_HBB",                    Mt_FctR_RteAccess_Read_HBB);    // to be created (optional)

  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_ClSblRequest",           Mt_FctR_RteAccess_Read_ClSblRequest);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_EcuSide",                Mt_FctR_RteAccess_Read_EcuSide);
  ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_LedVoltRange",           Mt_FctR_RteAccess_Read_LedVoltRange);
  //ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_PhaseVie",               Mt_FctR_RteAccess_Read_PhaseVie);       // to be created (optional)
  //ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_OV_Status",              Mt_FctR_RteAccess_Read_OV_Status);      // to be created (optional)
  //ALUnitTest_AddFunction("Mt_FctR_RteAccess_Read_UV_Status",              Mt_FctR_RteAccess_Read_UV_Status);      // to be created (optional)


  // FctR_TgtPrep.c
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_Get_Hb_Cmd",                    Mt_FctR_TgtPrep_Get_Hb_Cmd);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_Get_Lb_Cmd",                    Mt_FctR_TgtPrep_Get_Lb_Cmd);  
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_GetClSbl_AfsLight",             Mt_FctR_TgtPrep_GetClSbl_AfsLight);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_GetAfsPedestrian",              Mt_FctR_TgtPrep_GetAfsPedestrian);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_Full",                      Mt_FctR_TgtLgt_Prep_Full);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_Ti",                        Mt_FctR_TgtLgt_Prep_Ti);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_SetTiLgtStatus",                Mt_FctR_TgtPrep_SetTiLgtStatus);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_StdLgtFcts",                Mt_FctR_TgtLgt_Prep_StdLgtFcts);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_PklHandling",                   Mt_FctR_TgtPrep_PklHandling);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_SetTiWarningMode",              Mt_FctR_TgtPrep_SetTiWarningMode);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_WarningMode_Handling",           Mt_FctR_TgtLgt_WarningMode_Handling);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_AutonomMode_Handling",           Mt_FctR_TgtLgt_AutonomMode_Handling);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_PilotedMode_Handling",           Mt_FctR_TgtLgt_PilotedMode_Handling);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_GetTiCmdReq",                   Mt_FctR_TgtPrep_GetTiCmdReq);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_DiagDD00_ResetCmd",             Mt_FctR_TgtPrep_DiagDD00_ResetCmd);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_Aiming",                    Mt_FctR_TgtLgt_Prep_Aiming);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_Lb_Full",                   Mt_FctR_TgtLgt_Prep_Lb_Full);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_Hb_Full",                   Mt_FctR_TgtLgt_Prep_Hb_Full);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prep_ClSbl",                     Mt_FctR_TgtLgt_Prep_ClSbl);
  ALUnitTest_AddFunction("Mt_FctR_TgtPrep_GetClSblTargetState",           Mt_FctR_TgtPrep_GetClSblTargetState);


  // FctR_Tgt.c
  ALUnitTest_AddFunction("Mt_FctR_TgtInit",                               Mt_FctR_TgtInit);
  ALUnitTest_AddFunction("Mt_FctR_SpecialBehaviorDrlPos",                 Mt_FctR_SpecialBehaviorDrlPos);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt",                                Mt_FctR_TgtLgt);
  ALUnitTest_AddFunction("Mt_FctR_GetActiveTgtLgtReq",                    Mt_FctR_GetActiveTgtLgtReq);
  ALUnitTest_AddFunction("Mt_FctR_Percent_To_RteUnit",                    Mt_FctR_Percent_To_RteUnit);
  ALUnitTest_AddFunction("Mt_FctR_GetPriority",                           Mt_FctR_GetPriority);
  ALUnitTest_AddFunction("Mt_FctR_GetIntensity",                          Mt_FctR_GetIntensity);
  ALUnitTest_AddFunction("Mt_FctR_ActLgt_Update",                         Mt_FctR_ActLgt_Update);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp",            Mt_FctR_TgtLgt_Prio_LgtFctB_LogLmp);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prio_LgtFct",                    Mt_FctR_TgtLgt_Prio_LgtFct);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prio_LgtFct_FinalizePrio",       Mt_FctR_TgtLgt_Prio_LgtFct_FinalizePrio);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Prio",                           Mt_FctR_TgtLgt_Prio);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType",       Mt_FctR_TgtLgt_GetLmpSpdInvFromRampType);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_GetLmpSpdInvB",                  Mt_FctR_TgtLgt_GetLmpSpdInvB);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_GetLmpSpdInv",                   Mt_FctR_TgtLgt_GetLmpSpdInv);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Sustain_LogLamp",                Mt_FctR_TgtLgt_Sustain_LogLamp);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Sustain",                        Mt_FctR_TgtLgt_Sustain);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_Output",                         Mt_FctR_TgtLgt_Output);
  ALUnitTest_AddFunction("Mt_FctR_KeepTiStatusOn",                        Mt_FctR_KeepTiStatusOn);
  ALUnitTest_AddFunction("Mt_FctR_TgtDbl_Output",                         Mt_FctR_TgtDbl_Output);
  ALUnitTest_AddFunction("Mt_FctR_CheckSblCl_LightStatus",                Mt_FctR_CheckSblCl_LightStatus);
  ALUnitTest_AddFunction("Mt_FctR_TgtLgt_StorePrep",                      Mt_FctR_TgtLgt_StorePrep);
  ALUnitTest_AddFunction("Mt_FctR_SetLgtReq_VoltCond",                    Mt_FctR_SetLgtReq_VoltCond);
  ALUnitTest_AddFunction("Mt_FctR_StoreIlluminantFailureFunction",        Mt_FctR_StoreIlluminantFailureFunction);
  ALUnitTest_AddFunction("Mt_FctR_StoreIlluminantStatusFunction",         Mt_FctR_StoreIlluminantStatusFunction);
  ALUnitTest_AddFunction("Mt_FctR_DiagFeedback",                          Mt_FctR_DiagFeedback);
  ALUnitTest_AddFunction("Mt_FctR_Tgt_HandleLgtFctFailure",               Mt_FctR_Tgt_HandleLgtFctFailure);
  ALUnitTest_AddFunction("Mt_FctR_Get_UnderVoltageStatusDebounced",       Mt_FctR_Get_UnderVoltageStatusDebounced);
  ALUnitTest_AddFunction("Mt_FctR_Get_OverVoltageStatusDebounced",        Mt_FctR_Get_OverVoltageStatusDebounced);
  ALUnitTest_AddFunction("Mt_FctR_Tgt_LgtFctFailureReaction",             Mt_FctR_Tgt_LgtFctFailureReaction);
  ALUnitTest_AddFunction("Mt_FctR_ProccessAimingMode",                    Mt_FctR_ProccessAimingMode);
  ALUnitTest_AddFunction("Mt_FctR_CtrlDelayStatus",                       Mt_FctR_CtrlDelayStatus);
  ALUnitTest_AddFunction("Mt_FctR_Tgt_GetActLedState",                    Mt_FctR_Tgt_GetActLedState);


}
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
/// \brief  Unit Test Cases for Err
///
/// \author Calugar Radu Silviu (M01472A)
///         mailTo:radusilviu.calugar[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - ctaaErrCust.c
//            - ErrCust.c
//            - ErrCust_RteAccess.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
//  Module Test Cases
//-----------------------------------------------------------------------------

/*ErrCust_RteAccess.C*/
//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase1
///
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to CtrlStp for Actual status data
///
///   - Test subject: Simulate and test read OF RTE wrapper to CtrlStp for Actual status data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree = 0u
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl  = 0u
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl  = FALSE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl  = FALSE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl  = FALSE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp  = FALSE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl   = FALSE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl = FALSE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.cStatStpPosDegree      = 1u
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpLevelStatus    = 1u
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss       = TRUE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef           = TRUE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = TRUE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpIsMoving          = TRUE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef            = TRUE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState   = TRUE
///
/// - Expectations:
///
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree  = 1u
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl   = 1u
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl   = TRUE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl   = TRUE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl   = TRUE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp   = TRUE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl    = TRUE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl  = TRUE
///    \output Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount                     = 1u  
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase1(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree  = 0u;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl   = 0u;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl   = FALSE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl   = FALSE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl   = FALSE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp   = FALSE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl    = FALSE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl  = FALSE;

  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.cStatStpPosDegree       = 1u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpLevelStatus     = 1u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss        = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef            = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect  = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpIsMoving           = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef             = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState    = TRUE;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp(&ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree,  1u    , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl,   1u    , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl,   TRUE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl,   TRUE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl,   TRUE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp,   TRUE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl,    TRUE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl,  TRUE  , == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount,                     1u    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to CtrlStp for Actual status data
///
///   - Test subject: Simulate and test read OF RTE wrapper to CtrlStp for Actual status data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree = 0u
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl  = 0u
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl  = TRUE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl  = TRUE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl  = TRUE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp  = TRUE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl   = TRUE
///    \input ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl = TRUE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.cStatStpPosDegree      = 1u
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpLevelStatus    = 1u
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss       = FALSE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef           = FALSE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect = FALSE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpIsMoving          = FALSE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef            = FALSE
///    \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState   = FALSE
///
/// - Expectations:
///
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree  = 1u
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl   = 1u
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl   = FALSE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl   = FALSE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl   = FALSE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp   = FALSE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl    = FALSE
///    \output ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl  = FALSE
///    \output Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount                     = 1u  
///
//-----------------------------------------------------------------------------

void Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase2(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree  = 0u;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl   = 0u;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl   = TRUE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl   = TRUE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl   = TRUE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp   = TRUE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl    = TRUE;
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl  = TRUE;

  //Step 2) Assign Input values
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount = 0u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.cStatStpPosDegree       = 1u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpLevelStatus     = 1u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss        = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef            = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpElectricDefect  = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpIsMoving           = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef             = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState    = FALSE;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_CtrlStp_ActStatStp(&ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.cStpPosDegree,  1u     , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.ucStsAutoLvl,   1u     , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boStpLossLvl,   FALSE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boCommDefLvl,   FALSE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boElecDefLvl,   FALSE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boMoveLvlStp,   FALSE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boPosDefLvl,    FALSE  , == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_CtrlStp_ActStatStp_Param1.boThermDefLvl,  FALSE  , == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount                   ,  1u     , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Simulate and test read OF RTE wrapper to CtrlStp for Actual status data
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase(void)
{
  Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase1();
  Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to IoHwAbUser for headlamp side
///
///   - Test subject: Simulate and test read of RTE wrapper to CtrlStp for Actual status data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1 = eUndef
///
/// - Expectations:
///
/// \output ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1 = eLeft
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase1(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1  = eUndef;

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(&ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1,  eLeft, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount            ,  1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to IoHwAbUser for headlamp side
///
///   - Test subject: Simulate and test read of RTE wrapper to CtrlStp for Actual status data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1 = eUndef
///
/// - Expectations:
///
/// \output ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1 = eRight
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase2(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1  = eUndef;

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(&ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1,  eRight, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount            ,  1u    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to IoHwAbUser for headlamp side
///
///   - Test subject: Simulate and test read of RTE wrapper to CtrlStp for Actual status data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedUndef
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
/// \input ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1 = eLeft
///
/// - Expectations:
///
/// \output ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1 = eUndef
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase3(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1  = eLeft;

  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedUndef;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(&ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_Param1,  eUndef, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount            ,  1u    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Simulate and test read of RTE wrapper to CtrlStp for Actual status data
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase(void)
{
  Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase1();
  Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase2();
  Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to FctR for Light Functions state
///
///   - Test subject: Test the correct behaviour of reading the RTE wrapper to FctR for Light Functions state
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE  
/// \input  Rte_Read_FctR_LgtFctState_HitCount = 0u
/// \input  Rte_Read_FctR_LgtFctState_Param1.boLb_State   = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boSbl_State  = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boTi_State   = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boHb_State   = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boGfHb_State = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boDrl_State  = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boPos_State  = FALSE
///
/// - Expectations: 
///
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = FALSE
/// \output  Rte_Read_FctR_LgtFctState_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase1(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State  = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State   = TRUE;

  //Step 2) Assign Input values
  Rte_Read_FctR_LgtFctState_HitCount             = 0;
  Rte_Read_FctR_LgtFctState_Param1.boLb_State    = FALSE;
  Rte_Read_FctR_LgtFctState_Param1.boSbl_State   = FALSE;
  Rte_Read_FctR_LgtFctState_Param1.boTi_State    = FALSE;
  Rte_Read_FctR_LgtFctState_Param1.boHb_State    = FALSE;
  Rte_Read_FctR_LgtFctState_Param1.boGfHb_State  = FALSE;
  Rte_Read_FctR_LgtFctState_Param1.boDrl_State   = FALSE;
  Rte_Read_FctR_LgtFctState_Param1.boPos_State   = FALSE;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_FctR_LgtFctErrState(&ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State,   FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State,  FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State,   FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State,   FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_FctR_LgtFctState_HitCount                           ,   1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to FctR for Light Functions state
///
///   - Test subject: Test the correct behaviour of reading the RTE wrapper to FctR for Light Functions state
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_HitCount = 0u
/// \input  Rte_Read_FctR_LgtFctState_Param1.boLb_State   = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boSbl_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boTi_State   = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boHb_State   = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boGfHb_State = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boDrl_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boPos_State  = TRUE
///
/// - Expectations: 
///
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \output  Rte_Read_FctR_LgtFctState_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase2(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State  = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State   = TRUE;

  //Step 2) Assign Input values
  Rte_Read_FctR_LgtFctState_HitCount             = 0;
  Rte_Read_FctR_LgtFctState_Param1.boLb_State    = TRUE;
  Rte_Read_FctR_LgtFctState_Param1.boSbl_State   = TRUE;
  Rte_Read_FctR_LgtFctState_Param1.boTi_State    = TRUE;
  Rte_Read_FctR_LgtFctState_Param1.boHb_State    = TRUE;
  Rte_Read_FctR_LgtFctState_Param1.boGfHb_State  = TRUE;
  Rte_Read_FctR_LgtFctState_Param1.boDrl_State   = TRUE;
  Rte_Read_FctR_LgtFctState_Param1.boPos_State   = TRUE;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_FctR_LgtFctErrState(&ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State,    TRUE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State,   TRUE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State,    TRUE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State,    TRUE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State,  TRUE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State,   TRUE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_FctR_LgtFctState_HitCount                           ,   1u  , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the correct behaviour of reading the RTE wrapper to FctR for Light Functions state
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase(void)
{
  Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase1();
  Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_TI_FctErrState_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to FctR for Light Functions state
///
///   - Test subject: Description: Test the correct behaviour of APPLI_Send_Defaut function.
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1 = TRUE
/// \input Rte_Read_FctR_TiFailureStatus_HitCount = 0u
///
/// - Expectations: 
///
/// \output ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1 = TRUE
/// \output Rte_Read_FctR_TiFailureStatus_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_TI_FctErrState_TestCase(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1  = TRUE;

  //Step 2) Assign Input values
  Rte_Read_FctR_TiFailureStatus_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_FctR_TI_FctErrState(&ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_FctR_TiFailureStatus_HitCount,             1u, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_TI_FctErrState_Param1,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to FctR for Light Functions status
///
///   - Test subject: Description: Test the correct behaviour of reading the RTE wrapper to FctR for Light Functions state
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_HitCount = 0u
/// \input  Rte_Read_FctR_LgtFctState_Param1.boLb_State   = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boSbl_State  = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boTi_State   = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boHb_State   = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boGfHb_State = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boDrl_State  = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boPos_State  = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boDrl_State  = FALSE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boPos_State  = FALSE
///
/// - Expectations: 
///
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = FALSE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = FALSE
/// \output  Rte_Read_FctR_LgtFctState_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase1(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boLb_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSbl_Status   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boTi_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boHb_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boGfHb_Status  = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boDrl_Status   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boPos_Status   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSM_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boFog_Status   = TRUE;

  //Step 2) Assign Input values
  Rte_Read_FctR_LgtFctStatus_HitCount              = 0u;
  Rte_Read_FctR_LgtFctStatus_Param1.boLb_Status    = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boSbl_Status   = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boTi_Status    = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boHb_Status    = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boGfHb_Status  = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boDrl_Status   = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boPos_Status   = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boFog_Status   = FALSE;
  Rte_Read_FctR_LgtFctStatus_Param1.boSM_Status    = FALSE;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_FctR_LgtFctStatus(&ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boLb_Status,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSbl_Status,   FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boTi_Status,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boHb_Status,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boGfHb_Status,  FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boDrl_Status,   FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boPos_Status,   FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSM_Status,    FALSE, == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boFog_Status,   FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_FctR_LgtFctStatus_HitCount,                            1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Read RTE wrapper to FctR for Light Functions status
///
///   - Test subject: Description: Test the correct behaviour of reading the RTE wrapper to FctR for Light Functions state
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \input  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_HitCount = 0u
/// \input  Rte_Read_FctR_LgtFctState_Param1.boLb_State   = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boSbl_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boTi_State   = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boHb_State   = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boGfHb_State = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boDrl_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boPos_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boDrl_State  = TRUE
/// \input  Rte_Read_FctR_LgtFctState_Param1.boPos_State  = TRUE
///
/// - Expectations: 
///
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boLb_State   = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boSbl_State  = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boTi_State   = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boHb_State   = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boGfHb_State = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boDrl_State  = TRUE
/// \output  ErrCust_RteAccess_Read_FctR_LgtFctErrState_Param1.boPos_State  = TRUE
/// \output  Rte_Read_FctR_LgtFctState_HitCount                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase2(void)
{
  //Step 1) Set pre - conditions
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boLb_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSbl_Status   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boTi_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boHb_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boGfHb_Status  = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boDrl_Status   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boPos_Status   = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSM_Status    = TRUE;
  ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boFog_Status   = TRUE;
  
  //Step 2) Assign Input values
  Rte_Read_FctR_LgtFctStatus_HitCount              = 0u;
  Rte_Read_FctR_LgtFctStatus_Param1.boLb_Status    = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boSbl_Status   = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boTi_Status    = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boHb_Status    = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boGfHb_Status  = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boDrl_Status   = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boPos_Status   = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boFog_Status   = TRUE;
  Rte_Read_FctR_LgtFctStatus_Param1.boSM_Status    = TRUE;

  //Step 3) Call FUT
  ErrCust_RteAccess_Read_FctR_LgtFctStatus(&ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boLb_Status,    TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSbl_Status,   TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boTi_Status,    TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boHb_Status,    TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boGfHb_Status,  TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boDrl_Status,   TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boPos_Status,   TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boSM_Status,    TRUE,  == );
  AL_UNITTEST_CHECK(ErrCust_RteAccess_Read_FctR_LgtFctStatus_Param1.boFog_Status,   TRUE,  == );
  AL_UNITTEST_CHECK(Rte_Read_FctR_LgtFctStatus_HitCount                         ,   1u  ,  == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the correct behaviour of reading the RTE wrapper to FctR for Light Functions state
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase(void)
{
  Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase1();
  Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase2();
}

/*ctaaErrCust.c*/

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
///
/// - Expectations: 
///
/// \output  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u   , == );
/// \output  AL_UNITTEST_CHECK(ErrCust_boLeft, FALSE, == );
///
//-----------------------------------------------------------------------------
void Mt_riErrCust_Init_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  
  //Step 3) Call FUT
  riErrCust_Init();
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u   , == );
  AL_UNITTEST_CHECK(ErrCust_boLeft                              ,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpErrCust_Cycle0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test ErrCust cycle function, check for hook , reset hook, get trusted adress and write dummy data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input   ErrCust_ulMPU_Trigger_Fault_Hook = 0u;
/// \input   LPTMR0_GetTimeElapsed_RetVal = FT_MSEC(300u) + 1;
///
/// - Expectations: 
///
/// \output  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust, FALSE, == );
///
//-----------------------------------------------------------------------------
void Mt_rpErrCust_Cycle0_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ulMPU_Trigger_Fault_Hook  = 0u;
  LPTMR0_GetTimeElapsed_RetVal      = FT_MSEC(300u) + 1;

  //Step 3) Call FUT
  rpErrCust_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpErrCust_Cycle0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test ErrCust cycle function, don,t check for hook , reset hook, get trusted adress and write dummy data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \input  ErrCust_ulMPU_Trigger_Fault_Hook = ERRCUST_MPU_ACCESS_FAULT_HOOK_ACTIVATION;
/// \input  LPTMR0_GetTimeElapsed_RetVal = FT_MSEC(300u) + 1;
///
/// - Expectations: 
///
/// \output  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust, FALSE, == );
///
//-----------------------------------------------------------------------------
void Mt_rpErrCust_Cycle0_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ulMPU_Trigger_Fault_Hook  = ERRCUST_MPU_ACCESS_FAULT_HOOK_ACTIVATION;
  LPTMR0_GetTimeElapsed_RetVal      = FT_MSEC(300u) + 1;

  //Step 3) Call FUT
  rpErrCust_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpErrCust_Cycle0_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the correct behaviour of ErrCust cycle function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_rpErrCust_Cycle0_TestCase(void)
{
  Mt_rpErrCust_Cycle0_TestCase1();
  Mt_rpErrCust_Cycle0_TestCase2();
}

/* ErrCust.c */

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output  ErrCust_boLeft = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u   , == );
  AL_UNITTEST_CHECK(ErrCust_boLeft                              ,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
/// \output  ErrCust_boLeft = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u  , == );
  AL_UNITTEST_CHECK(ErrCust_boLeft                              ,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_boNvmDirtyErrCust = FALSE
/// \input NvmBlockErrCustPs.aucErrStatus[0u] = 0x05u
/// \input NvmBlockErrCustPs.aucAgingCounter[0u] = 2u
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output NvmBlockErrCustPs.aucAgingCounter[0] = 1U
/// \output ErrCust_boNvmDirtyErrCust = TRUE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase3(void)
{
  //Step 1) Set pre - conditions
  ErrCust_boNvmDirtyErrCust  = FALSE;

  //Step 2) Assign Input values
  NvmBlockErrCustPs.aucErrStatus[0u]            = 0x05u;
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 2u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucAgingCounter[0]        ,  1u  , == );
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust                   ,  TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u  , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  NvmBlockErrCustPs.aucErrStatus[0u] = 0x02u
/// \input  NvmBlockErrCustPs.aucAgingCounter[0u] = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output NvmBlockErrCustPs.aucAgingCounter[0u] = 0u
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockErrCustPs.aucErrStatus[0u]            = 0x02u;
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucAgingCounter[0u]       ,  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_aucStatus[0u]                         = 0u
/// \input NvmBlockErrCustPs.aucAgingCounter[0u]         = 5u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[0u] = 0x4Cu
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase5(void)
{
  //Step 1) Set pre - conditions
  ErrCust_aucStatus[0u]                         = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 2) Assign Input values
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 5u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_aucStatus[0u]                       ,  0x4Cu, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_aucStatus[0u] = 0u
/// \input NvmBlockErrCustPs.aucAgingCounter[0u] = 5u
/// \input NvmBlockErrCustPs.aucErrStatus[0u] = ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[0u] = 0x4Cu
/// \output NvmBlockErrCustPs.aucErrStatus[0u] = 0u
/// \output ErrCust_boNvmDirtyErrCust = TRUE
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase6(void)
{
  //Step 1) Set pre - conditions
  ErrCust_aucStatus[0u]                         = 0u;

  //Step 2) Assign Input values
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 5u;
  NvmBlockErrCustPs.aucErrStatus[0u]            = ERRCUST_STATUS_TEST_FAILED_THIS_CYCLE;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_aucStatus[0u]                       ,  0x4Cu, == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrStatus[0u]          ,  0u   , == );
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust                   ,  TRUE , == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_aucStatus[0u]                         = 0u
/// \input NvmBlockErrCustPs.aucAgingCounter[0u]         = 5u
/// \input NvmBlockErrCustPs.aucErrStatus[0u]            = 0x03u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[0u] = 0x4Cu
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase7(void)
{
  //Step 1) Set pre - conditions
  ErrCust_aucStatus[0u]                         = 0u;

  //Step 2) Assign Input values
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 5u;
  NvmBlockErrCustPs.aucErrStatus[0u]            = 0x03u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_aucStatus[0u]                       ,  0x4Cu, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Initialisation of Ps error status at system boot
///
///   - Test subject: Description: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockErrCustPs.aucAgingCounter[0u]         = 0u
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u
///
/// - Expectations: 
///
/// \output NvmBlockErrCustPs.aucAgingCounter[0u] = 0u
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;

  //Step 3) Call FUT
  ErrCust_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucAgingCounter[0u]       ,  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Init_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test the correct behaviour of initialisation of Ps error status at system boot
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Init_TestCase(void)
{
  Mt_ErrCust_Init_TestCase1();
  Mt_ErrCust_Init_TestCase2();
  Mt_ErrCust_Init_TestCase3();
  Mt_ErrCust_Init_TestCase4();
  Mt_ErrCust_Init_TestCase5();
  Mt_ErrCust_Init_TestCase6();
  Mt_ErrCust_Init_TestCase7();
  Mt_ErrCust_Init_TestCase8();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores the actual captured freeze frame data and environmental conditions
///
///   - Test subject: Description: Test that current entry is available for storage, store the index of data and signalize that current value is available
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockErrCustPs.aucAgingCounter[0u] = ERRCUST_MIN_AGE
/// \input ErrCust_CaptureFreezeFrameData_Param1 = 0u
///
/// - Expectations: 
///
/// \output NvmBlockFreezeFrameDataPs.aucDtcId[0u] = ErrCust_CaptureFreezeFrameData_Param1
/// \output NvmBlockFreezeFrameDataPs.aucAge[0u]   = ERRCUST_YOUNGEST_AGE_FFD
/// \output NvmBlockErrCustPs.aucErrFreezeFrameIndex[ErrCust_CaptureFreezeFrameData_Param1] = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureFreezeFrameData_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockFreezeFrameDataPs.aucAge[0u]   = ERRCUST_MIN_AGE;
  ErrCust_CaptureFreezeFrameData_Param1  = 0u;
  //Step 3) Call FUT

  ErrCust_CaptureFreezeFrameData(ErrCust_CaptureFreezeFrameData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucDtcId[0u] ,                                          ErrCust_CaptureFreezeFrameData_Param1, == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucAge[0u],                                             ERRCUST_YOUNGEST_AGE_FFD             , == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrFreezeFrameIndex[ErrCust_CaptureFreezeFrameData_Param1],  0u                                   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores the actual captured freeze frame data and environmental conditions
///
///   - Test subject: Description: Test that data frame age has the maximum possible value, store dtc index and signalize that current value is available
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockFreezeFrameDataPs.aucAge[0]   = ERRCUST_MAX_AGE
/// \input ErrCust_CaptureFreezeFrameData_Param1 = 0
///
/// - Expectations: 
///
/// \output NvmBlockFreezeFrameDataPs.aucDtcId[0u] = ErrCust_CaptureFreezeFrameData_Param1
/// \output NvmBlockErrCustPs.aucErrFreezeFrameIndex[ErrCust_CaptureFreezeFrameData_Param1] = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureFreezeFrameData_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockFreezeFrameDataPs.aucAge[0]    = ERRCUST_MAX_AGE;
  ErrCust_CaptureFreezeFrameData_Param1  = 0;

  //Step 3) Call FUT
  ErrCust_CaptureFreezeFrameData(ErrCust_CaptureFreezeFrameData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucDtcId[0u],                                           ErrCust_CaptureFreezeFrameData_Param1 , == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrFreezeFrameIndex[ErrCust_CaptureFreezeFrameData_Param1],  0u                                    , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores the actual captured freeze frame data and environmental conditions
///
///   - Test subject: Description: Test that age of data is ready to be increased and check increased data age
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockFreezeFrameDataPs.aucAge[0]   = ERRCUST_MAX_AGE +1u;
/// \input ErrCust_CaptureFreezeFrameData_Param1 = 0
///
/// - Expectations: 
///
/// \output AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucAge[0u], 2u, == );
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureFreezeFrameData_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockFreezeFrameDataPs.aucAge[0]    = ERRCUST_MIN_AGE +1u ;
  ErrCust_CaptureFreezeFrameData_Param1  = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureFreezeFrameData(ErrCust_CaptureFreezeFrameData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucAge[0u],  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores the actual captured freeze frame data and environmental conditions
///
///   - Test subject: Description: Test that in all other cases data from Nvm is filled
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockFreezeFrameDataPs.aucAge[0] = ERRCUST_MAX_AGE + 1u
/// \input ErrCust_CaptureFreezeFrameData_Param1 = 0u
///
/// - Expectations: 
///
/// \output NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE  [0u] = 0u  
/// \output NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE     [0u] = 153u
/// \output NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS                [0u] = 1u  
/// \output NvmBlockFreezeFrameDataPs.aucLVL_INFO                       [0u] = 13u 
/// \output NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC           [0u] = 0u  
/// \output NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC                  [0u] = 0u  
/// \output NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC                 [0u] = 0u  
/// \output NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC                   [0u] = 0u  
/// \output NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC  [0u] = 0u  
/// \output NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC  [0u] = 0u  
/// \output ErrCust_boNvmDirtyFreezeFrameData = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureFreezeFrameData_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockFreezeFrameDataPs.aucAge[0]    = ERRCUST_MAX_AGE + 1u;
  ErrCust_CaptureFreezeFrameData_Param1  = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureFreezeFrameData(ErrCust_CaptureFreezeFrameData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE  [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE     [0u] ,  153u  , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS                [0u] ,  1u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucLVL_INFO                       [0u] ,  13u   , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC           [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC                  [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC                 [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC                   [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC  [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC  [0u] ,  0u    , == );
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyFreezeFrameData                                ,  TRUE  , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function stores the actual captured freeze frame data and environmental conditions
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureFreezeFrameData_TestCase(void)
{
  Mt_ErrCust_CaptureFreezeFrameData_TestCase1();
  Mt_ErrCust_CaptureFreezeFrameData_TestCase2();
  Mt_ErrCust_CaptureFreezeFrameData_TestCase3();
  Mt_ErrCust_CaptureFreezeFrameData_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores aftermarket ATTITUDE ECU data
///
///   - Test subject: Description: Test that quality of signal is valid and store stepper info
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                    = 0u
/// \input Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = SIG_VALID
/// \input ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snOffsetCalibVehicleAttitude  = 10u
/// \input Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 12u
///
/// - Expectations: 
///
/// \output ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snInstValVehiculeAttitude    = 6u 
/// \output ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snOffsetCalibVehicleAttitude = 0u
/// \output Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                   = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase1(void)
{
  //Step 1) Set pre - conditions
  ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snOffsetCalibVehicleAttitude   = 10u;
                                                                                  
  //Step 2) Assign Input values                                                   
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                     = 0u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                               = SIG_VALID;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle  = 12u;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketAttitudeEcuData(&ErrCust_CaptureAftermarketAttitudeEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snInstValVehiculeAttitude    ,  6u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snOffsetCalibVehicleAttitude ,  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                   ,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores aftermarket ATTITUDE ECU data
///
///   - Test subject: Description: Test that quality of signal is not valid and update the maximum valid position value
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \input Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                    = 0u
/// \input Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = SIG_SNA
/// \input ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snOffsetCalibVehicleAttitude  = 0x55u
///
/// - Expectations: 
///
/// \output ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snInstValVehiculeAttitude    = 0x99u 
/// \output Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                   = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase2(void)
{
  //Step 1) Set pre - conditions
  ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snInstValVehiculeAttitude  = 0x55u;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                 = 0u;
  //Step 2) Assign Input values                                               
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                           = SIG_SNA;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketAttitudeEcuData(&ErrCust_CaptureAftermarketAttitudeEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketAttitudeEcuData_Param1.snInstValVehiculeAttitude,  0x99u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehiclePitchAngle_HitCount                               ,  1u   , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function stores ECU data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase(void)
{
  Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase1();
  Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores aftermarket CONTEXT ECU data
///
///   - Test subject: Description: Test that Rte provider ports are called and maxim accepted Voltage is reached
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV + 1
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount           = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount          = 0u
/// \input Rte_Read_SigPrep_OdometerTotal_HitCount        = 0u
/// \input Rte_Read_IoHwAb_GetSens_Raw_HitCount           = 0u
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount= 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount          = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount         = 1u
/// \output Rte_Read_SigPrep_OdometerTotal_HitCount       = 1u
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values 
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1    = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV + 1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
  Rte_Read_SysMon_VehNetState_HitCount            = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount           = 0u;
  Rte_Read_SigPrep_OdometerTotal_HitCount         = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount            = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketContextEcuData(&ErrCust_CaptureAftermarketContextEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount          ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount         ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_OdometerTotal_HitCount       ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount          ,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores aftermarket CONTEXT ECU data
///
///   - Test subject: Description: Test that voltage suply is stored and maxim accepted Voltage is not reached
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1   = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV - 1
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount           = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount          = 0u
/// \input Rte_Read_SigPrep_OdometerTotal_HitCount        = 0u
/// \input Rte_Read_IoHwAb_GetSens_Raw_HitCount           = 0u
///
/// - Expectations: 
///
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucEtatInfo        = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucVehicleSpeed    = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ulKilometrage     = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_FL_Bhs  = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_RL_Bhs  = 0u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount= 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount          = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount         = 1u
/// \output Rte_Read_SigPrep_OdometerTotal_HitCount       = 1u
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values 
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1    = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV - 1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
  Rte_Read_SysMon_VehNetState_HitCount            = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount           = 0u;
  Rte_Read_SigPrep_OdometerTotal_HitCount         = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount            = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketContextEcuData(&ErrCust_CaptureAftermarketContextEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucEtatInfo        ,  0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucVehicleSpeed    ,  0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ulKilometrage     ,  0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_FL_Bhs  ,  0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_RL_Bhs  ,  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                    ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                              ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount                             ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_OdometerTotal_HitCount                           ,  1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount                              ,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   Stores aftermarket CONTEXT ECU data
///
///   - Test subject: Description: Test that vehicle speed is stored and maxim accepted speed is reached
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                      = 0u
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                    = 0u
/// \input Rte_Read_SysMon_VehNetState_HitCount                              = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 25600u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID
/// \input Rte_Read_SigPrep_OdometerTotal_HitCount                           = 0u
/// \input Rte_Read_IoHwAb_GetSens_Raw_HitCount                              = 0u
///
/// - Expectations: 
///
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucEtatInfo        = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucVehicleSpeed    = 255u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ulKilometrage     = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_FL_Bhs  = 0u
/// \output ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_RL_Bhs  = 0u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount= 1u
/// \output Rte_Read_SysMon_VehNetState_HitCount          = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount         = 1u
/// \output Rte_Read_SigPrep_OdometerTotal_HitCount       = 1u
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values 
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                      = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                    = 0u;
  Rte_Read_SysMon_VehNetState_HitCount                              = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 25600u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  Rte_Read_SigPrep_OdometerTotal_HitCount                           = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount                              = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketContextEcuData(&ErrCust_CaptureAftermarketContextEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucEtatInfo        ,   0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucVehicleSpeed    , 255u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ulKilometrage     ,   0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_FL_Bhs  ,   0u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketContextEcuData_Param1.ucInstVal_RL_Bhs  ,   0u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                    ,   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount                              ,   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount                             ,   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_OdometerTotal_HitCount                           ,   1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount                              ,   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureFreezeFrameData_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test that the function stores aftermarket CONTEXT ECU data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase(void)
{
  Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase1();
  Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase2();
  Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetClearMemoryType_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns clear type according to the value of the parameter
///
///   - Test subject: Description: Test if there is request for clearing all DTCs and return specific enum for clear all DTCs
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ucGetClearMemoryType_Param1 = ERRCUST_ALL_GROUP_OF_DTCS
/// \input ErrCust_ucGetClearMemoryType_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ucGetClearMemoryType_RetVal = eErrCust_ClearAllDtcs
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetClearMemoryType_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetClearMemoryType_Param1  = ERRCUST_ALL_GROUP_OF_DTCS;
  ErrCust_ucGetClearMemoryType_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetClearMemoryType_RetVal = ErrCust_ucGetClearMemoryType(ErrCust_ucGetClearMemoryType_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetClearMemoryType_RetVal,  eErrCust_ClearAllDtcs , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetClearMemoryType_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns clear type according to the value of the parameter
///
///   - Test subject: Description: Test if there is a request for clearing a certain group of DTCs and return specific enum for clear all DTCs
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ucGetClearMemoryType_Param1 = ERRCUST_GRP_P
/// \input ErrCust_ucGetClearMemoryType_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ucGetClearMemoryType_RetVal = eErrCust_ClearGroupOfDtcs
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetClearMemoryType_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetClearMemoryType_Param1  = ERRCUST_GRP_P;
  ErrCust_ucGetClearMemoryType_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetClearMemoryType_RetVal = ErrCust_ucGetClearMemoryType(ErrCust_ucGetClearMemoryType_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetClearMemoryType_RetVal,  eErrCust_ClearGroupOfDtcs, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetClearMemoryType_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns clear type according to the value of the parameter
///
///   - Test subject: Description: Test if there is a request for clearing a a single DTC and return specific enum for clear type to single DTC
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ucGetClearMemoryType_Param1 = 0xDEF487
/// \input ErrCust_ucGetClearMemoryType_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ucGetClearMemoryType_RetVal = eErrCust_ClearSingleDtc
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetClearMemoryType_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetClearMemoryType_Param1  = 0xDEF487; //condition for dtc code to be equal with function parameter
  ErrCust_ucGetClearMemoryType_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetClearMemoryType_RetVal = ErrCust_ucGetClearMemoryType(ErrCust_ucGetClearMemoryType_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetClearMemoryType_RetVal,  eErrCust_ClearSingleDtc, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetClearMemoryType_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns clear type according to the value of the parameter
///
///   - Test subject: Description: Test if Dtc is not founded and return specific enum for clear type from initialization phase
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ucGetClearMemoryType_Param1 = 0x11u
/// \input ErrCust_ucGetClearMemoryType_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ucGetClearMemoryType_RetVal = eErrCust_ClearNotSupported
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetClearMemoryType_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetClearMemoryType_Param1  = 0x11u; 
  ErrCust_ucGetClearMemoryType_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetClearMemoryType_RetVal = ErrCust_ucGetClearMemoryType(ErrCust_ucGetClearMemoryType_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetClearMemoryType_RetVal,  eErrCust_ClearNotSupported, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetClearMemoryType_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if this function returns clear type according to the value of the parameter
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetClearMemoryType_TestCase(void)
{
  Mt_ErrCust_ucGetClearMemoryType_TestCase1();
  Mt_ErrCust_ucGetClearMemoryType_TestCase2();
  Mt_ErrCust_ucGetClearMemoryType_TestCase3();
  Mt_ErrCust_ucGetClearMemoryType_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearMemory_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function clear both Customer errors from Nvm and RAM and also correponding DemEventIds errors(ALEC ID) from Nvm and RAM according to DTC code received over the CAN via pointer parameter
///
///   - Test subject: Description: Test if clear all DTCs case works
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ClearMemory_Param1[0u] = 0u
/// \input ErrCust_ClearMemory_Param1[1u] = 0u
/// \input ErrCust_ClearMemory_Param1[2u] = 0u
/// \input ErrCust_ClearMemory_RetVal     = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ClearMemory_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearMemory_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ClearMemory_Param1[0u]  = 0u;
  ErrCust_ClearMemory_Param1[1u]  = 0u;
  ErrCust_ClearMemory_Param1[2u]  = 0u;
  ErrCust_ClearMemory_RetVal      = 0u;

  //Step 3) Call FUT
  ErrCust_ClearMemory_RetVal = ErrCust_ClearMemory(ErrCust_ClearMemory_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ClearMemory_RetVal,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearMemory_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function clear both Customer errors from Nvm and RAM and also correponding DemEventIds errors(ALEC ID) from Nvm and RAM according to DTC code received over the CAN via pointer parameter
///
///   - Test subject: Description: Test if clear group of DTCs case works
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ClearMemory_Param1[0u] = 0u
/// \input ErrCust_ClearMemory_Param1[1u] = 0u
/// \input ErrCust_ClearMemory_Param1[2u] = 0u
/// \input ErrCust_ClearMemory_RetVal     = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ClearMemory_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearMemory_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ClearMemory_Param1[0u]  = 0xFFu;
  ErrCust_ClearMemory_Param1[1u]  = 0xFFu;
  ErrCust_ClearMemory_Param1[2u]  = 0xFFu;
  ErrCust_ClearMemory_RetVal      = 0u;

  //Step 3) Call FUT
  ErrCust_ClearMemory_RetVal = ErrCust_ClearMemory(ErrCust_ClearMemory_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ClearMemory_RetVal,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearMemory_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function clear both Customer errors from Nvm and RAM and also correponding DemEventIds errors(ALEC ID) from Nvm and RAM according to DTC code received over the CAN via pointer parameter
///
///
///   - Test subject: Description: Test if clear one DTC case works
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ClearMemory_Param1[0u] = 0xDE
/// \input ErrCust_ClearMemory_Param1[1u] = 0xF4
/// \input ErrCust_ClearMemory_Param1[2u] = 0x87
/// \input ErrCust_ClearMemory_RetVal     = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ClearMemory_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearMemory_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ClearMemory_Param1[0u]  = 0xDE;
  ErrCust_ClearMemory_Param1[1u]  = 0xF4;
  ErrCust_ClearMemory_Param1[2u]  = 0x87;
  ErrCust_ClearMemory_RetVal      = 0u;

  //Step 3) Call FUT
  ErrCust_ClearMemory_RetVal = ErrCust_ClearMemory(ErrCust_ClearMemory_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ClearMemory_RetVal,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearMemory_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function clear both Customer errors from Nvm and RAM and also correponding DemEventIds errors(ALEC ID) from Nvm and RAM according to DTC code received over the CAN via pointer parameter
///
///
///   - Test subject: Description: Test if DTC or group of DTCs not supported case works
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ClearMemory_Param1[0u] = 0xDD
/// \input ErrCust_ClearMemory_Param1[1u] = 0xDD
/// \input ErrCust_ClearMemory_Param1[2u] = 0xDD
/// \input ErrCust_ClearMemory_RetVal     = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ClearMemory_RetVal = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearMemory_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ClearMemory_Param1[0u]  = 0xDD;
  ErrCust_ClearMemory_Param1[1u]  = 0xDD;
  ErrCust_ClearMemory_Param1[2u]  = 0xDD;
  ErrCust_ClearMemory_RetVal      = 0u;

  //Step 3) Call FUT
  ErrCust_ClearMemory_RetVal = ErrCust_ClearMemory(ErrCust_ClearMemory_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ClearMemory_RetVal,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearMemory_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if This function clear both Customer errors from Nvm and RAM and also correponding DemEventIds errors(ALEC ID) from Nvm and RAM according to DTC code received over the CAN via pointer parameter
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearMemory_TestCase(void)
{
  Mt_ErrCust_ClearMemory_TestCase1();
  Mt_ErrCust_ClearMemory_TestCase2();
  Mt_ErrCust_ClearMemory_TestCase3();
  Mt_ErrCust_ClearMemory_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetStatusOfDTC_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function return the current status of the DTC given as parameter
///
///   - Test subject: Description: Test if function returns corect the status of Dtc with index 0
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ucGetStatusOfDTC_Param1 = 0u
/// \input ErrCust_ucGetStatusOfDTC_RetVal = 0u
///
/// - Expectations: 
///
/// \output     AL_UNITTEST_CHECK(ErrCust_ucGetStatusOfDTC_RetVal, 80u, == );
/// \output     AL_UNITTEST_CHECK(ErrCust_aucStatus[0u], 64u, == );
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetStatusOfDTC_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetStatusOfDTC_Param1  = 0u;
  ErrCust_ucGetStatusOfDTC_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetStatusOfDTC_RetVal = ErrCust_ucGetStatusOfDTC(ErrCust_ucGetStatusOfDTC_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetStatusOfDTC_RetVal,  80u, == );
  AL_UNITTEST_CHECK(ErrCust_aucStatus[0u],            64u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_SetAvailableDtc_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function fill the buffer received as parameter with the first available DTC code that match the ucDTCStatusMask
///
///   - Test subject: Description: Test firs available DTC code and stores bytes in a buffer
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_SetAvailableDtc_Param1[0u] = 0u
/// \input ErrCust_SetAvailableDtc_Param1[1u] = 0u
/// \input ErrCust_SetAvailableDtc_Param1[2u] = 0u
/// \input ErrCust_SetAvailableDtc_Param2     = 64u
///
/// - Expectations: 
///
/// \output ErrCust_SetAvailableDtc_Param1[0u] = 0u
/// \output ErrCust_SetAvailableDtc_Param1[1u] = 0u
/// \output ErrCust_SetAvailableDtc_Param1[2u] = 0u
/// \output ErrCust_SetAvailableDtc_Param1[3u] = 80u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_SetAvailableDtc_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_SetAvailableDtc_Param1[0u]  = 0u;
  ErrCust_SetAvailableDtc_Param1[1u]  = 0u;
  ErrCust_SetAvailableDtc_Param1[2u]  = 0u;
  ErrCust_SetAvailableDtc_Param2      = 64u;

  //Step 3) Call FUT
  ErrCust_SetAvailableDtc(ErrCust_SetAvailableDtc_Param1, ErrCust_SetAvailableDtc_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_SetAvailableDtc_Param1[0u],  0u , == );
  AL_UNITTEST_CHECK(ErrCust_SetAvailableDtc_Param1[1u],  0u , == );
  AL_UNITTEST_CHECK(ErrCust_SetAvailableDtc_Param1[2u],  0u , == );
  AL_UNITTEST_CHECK(ErrCust_SetAvailableDtc_Param1[3u],  80u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_SetAvailableDtc_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function fill the buffer received as parameter with the first available DTC code that match the ucDTCStatusMask
///
///   - Test subject: Description: Test if there is no match of ucDTCStatusMask found for the current DTC and check the increment of index
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_SetAvailableDtc_Param1[0u] = 0u
/// \unput ErrCust_SetAvailableDtc_Param1[1u] = 0u
/// \unput ErrCust_SetAvailableDtc_Param1[2u] = 0u
/// \unput ErrCust_SetAvailableDtc_Param2     = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ucDtcIndex = ERRCUST_IxPsErrorMax
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_SetAvailableDtc_TestCase2(void)
{
  //Step 1) Set pre - conditions
  ErrCust_ucDtcIndex = 
  //Step 2) Assign Input values
  ErrCust_SetAvailableDtc_Param1[0u]  = 0u;
  ErrCust_SetAvailableDtc_Param1[1u]  = 0u;
  ErrCust_SetAvailableDtc_Param1[2u]  = 0u;
  ErrCust_SetAvailableDtc_Param2      = 0u;

  //Step 3) Call FUT
  ErrCust_SetAvailableDtc(&ErrCust_SetAvailableDtc_Param1, ErrCust_SetAvailableDtc_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucDtcIndex,  ERRCUST_IxPsErrorMax, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_SetAvailableDtc_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function fill the buffer for a recived parameter and test if there is not match found for a current DTC
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_SetAvailableDtc_TestCase(void)
{
  Mt_ErrCust_SetAvailableDtc_TestCase1();
  Mt_ErrCust_SetAvailableDtc_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetErrorCount_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns the number of logged custom error entries - DTCs
///
///   - Test subject: Description: Test if if actual status is matching with receveid status and increment index of error counter
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_SetAvailableDtc_Param1 = 0u
/// \unput ErrCust_SetAvailableDtc_Param2 = 0u
/// \unput ErrCust_ucGetErrorCount_RetVal = 0u
/// - Expectations: 
///
/// \output ErrCust_ucDtcIndex = ERRCUST_IxPsErrorMax
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetErrorCount_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetErrorCount_Param1  = 64u;
  ErrCust_ucGetErrorCount_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetErrorCount_RetVal = ErrCust_ucGetErrorCount(ErrCust_ucGetErrorCount_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetErrorCount_RetVal,  ERRCUST_IxPsErrorMax, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ucGetErrorCount_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns the number of logged custom error entries - DTCs
///
///   - Test subject: Description: Test if if actual status is not matching with receveid status and index of error counter is not incremented
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_SetAvailableDtc_Param1 = 0u
/// \input ErrCust_ucGetErrorCount_RetVal = 0u
/// - Expectations: 
///
/// \output ErrCust_ucDtcIndex            = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetErrorCount_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucGetErrorCount_Param1  = 0u;
  ErrCust_ucGetErrorCount_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ucGetErrorCount_RetVal = ErrCust_ucGetErrorCount(ErrCust_ucGetErrorCount_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucGetErrorCount_RetVal,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_SetAvailableDtc_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if returns the number of logged custom error entries - DTCs
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ucGetErrorCount_TestCase(void)
{
  Mt_ErrCust_ucGetErrorCount_TestCase1();
  Mt_ErrCust_ucGetErrorCount_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ulGetDtcCode_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function returns the DTC code corresponding with the given DTC index
///
///   - Test subject: Description: Test if if function is returning DTC code corresponding with the given DTC index
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     ErrCust_ulGetDtcCode_Param1 = 1u
/// \input     ErrCust_ulGetDtcCode_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ulGetDtcCode_RetVal   = 84u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ulGetDtcCode_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ulGetDtcCode_Param1  = 1u;
  ErrCust_ulGetDtcCode_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ulGetDtcCode_RetVal = ErrCust_ulGetDtcCode(ErrCust_ulGetDtcCode_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_RetVal,  84u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Cycle0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   ErrCust cyclic main function
///
///   - Test subject: Description: Test if time elapsed is more than 300ms and set status of Nvm write
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LPTMR0_GetTimeElapsed_RetVal = 30000000u
/// \input ErrCust_boNvmDirtyErrCust    = TRUE
///
/// - Expectations: 
///
/// \output ErrCust_boNvmDirtyErrCust = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Cycle0_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  LPTMR0_GetTimeElapsed_RetVal  = 30000000u;
  ErrCust_boNvmDirtyErrCust     = TRUE;

  //Step 3) Call FUT
  ErrCust_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Cycle0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   ErrCust cyclic main function
///
///   - Test subject: Description: Test if time elapsed is less than 300ms and set status of Nvm write
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input LPTMR0_GetTimeElapsed_RetVal = 0u
/// \input ErrCust_boNvmDirtyErrCust    = TRUE
///
/// - Expectations: 
///
/// \output ErrCust_boNvmDirtyErrCust = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Cycle0_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  LPTMR0_GetTimeElapsed_RetVal  = 0u;
  ErrCust_boNvmDirtyErrCust     = TRUE;

  //Step 3) Call FUT
  ErrCust_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Cycle0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   ErrCust cyclic main function
///
///   - Test subject: Description: Test if time elapsed is more than 300ms and store Nvm state
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  LPTMR0_GetTimeElapsed_RetVal      = 30000000u
/// \input  ErrCust_boNvmDirtyErrCust         = TRUE
/// \input  ErrCust_boNvmDirtyFreezeFrameData = TRUE
/// \input  NvM_WriteBlock_RetVal             = E_NOT_OK
///
/// - Expectations: 
///
/// \output ErrCust_boNvmDirtyErrCust = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Cycle0_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  LPTMR0_GetTimeElapsed_RetVal       = 30000000u;
  ErrCust_boNvmDirtyErrCust          = TRUE;
  ErrCust_boNvmDirtyFreezeFrameData  = TRUE;
  NvM_WriteBlock_RetVal              = E_NOT_OK;

  //Step 3) Call FUT
  ErrCust_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Cycle0_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   ErrCust cyclic main function
///
///   - Test subject: Description: Test if time elapsed is more than 300ms and store Nvm state
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  LPTMR0_GetTimeElapsed_RetVal      = 30000000u
/// \input  ErrCust_boNvmDirtyErrCust         = TRUE
/// \input  ErrCust_boNvmDirtyFreezeFrameData = TRUE
/// \input  NvM_WriteBlock_RetVal             = E_OK
///
/// - Expectations: 
///
/// \output ErrCust_boNvmDirtyErrCust = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Cycle0_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  LPTMR0_GetTimeElapsed_RetVal       = 30000000u;
  ErrCust_boNvmDirtyErrCust          = TRUE;
  ErrCust_boNvmDirtyFreezeFrameData  = TRUE;
  NvM_WriteBlock_RetVal              = E_OK;

  //Step 3) Call FUT
  ErrCust_Cycle0();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Cycle0_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: ErrCust cyclic main function
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///XXX---------------------------------------------------------------------------
void Mt_ErrCust_Cycle0_TestCase(void)
{
  Mt_ErrCust_Cycle0_TestCase1();
  Mt_ErrCust_Cycle0_TestCase2();
  Mt_ErrCust_Cycle0_TestCase3();
  Mt_ErrCust_Cycle0_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ResetDtcIndex_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr   This function is used by diagnosis in order to reset Dtc index right before reading the available DTCs
///
///   - Test subject: Test if the function resets DTC index
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ucDtcIndex = 3u
///
/// - Expectations: 
///
/// \output ErrCust_ucDtcIndex = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ResetDtcIndex_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ucDtcIndex  = 3u;

  //Step 3) Call FUT
  ErrCust_ResetDtcIndex();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ucDtcIndex,  0u , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearFreezeFrameData_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr This function clear freeze frame data corresponding to 'ucFreezeFrameIdx' parameter
///        from table ErrCust_ClearFreezeFrameData which is linked with dtc indicated by aucDtcId field from the same table
///
///   - Test subject: Test if a valid DTC is required then decrease the age for all DTCs which have an age bigger than the age of freeze frame data which will be cleared
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockFreezeFrameDataPs.aucAge[0u]   = 20u
/// \input NvmBlockFreezeFrameDataPs.aucAge[1u]   = 2u
/// \input NvmBlockFreezeFrameDataPs.aucDtcId[0u] = 3u
/// \input ErrCust_ClearFreezeFrameData_Param1    = 1u
///
/// - Expectations: 
///
/// \output NvmBlockFreezeFrameDataPs.aucAge[0u] = 19u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearFreezeFrameData_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockFreezeFrameDataPs.aucAge[0u]    = 20u;
  NvmBlockFreezeFrameDataPs.aucAge[1u]    = 2u;
  NvmBlockFreezeFrameDataPs.aucDtcId[0u]  = 3u;
  ErrCust_ClearFreezeFrameData_Param1     = 1u;

  //Step 3) Call FUT
  ErrCust_ClearFreezeFrameData(ErrCust_ClearFreezeFrameData_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucAge[0u],  19u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearFreezeFrameData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr This function clear freeze frame data corresponding to 'ucFreezeFrameIdx' parameter
///        from table ErrCust_ClearFreezeFrameData which is linked with dtc indicated by aucDtcId field from the same table
///
///   - Test subject: Test if there is not a valid DTC required Aand check if rest of the fields are reseted
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockFreezeFrameDataPs.aucAge[0u]   = 20u
/// \input NvmBlockFreezeFrameDataPs.aucAge[0u]   = 2u
/// \input NvmBlockFreezeFrameDataPs.aucDtcId[0u] = 3u
/// \input ErrCust_ClearFreezeFrameData_Param1    = 1u
///
/// - Expectations: 
///
/// \output (NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE[0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE   [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS              [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.aucLVL_INFO                     [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC         [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC                [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC               [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC                 [0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC[0u] = 0u
/// \output (NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC[0u] = 0u
/// \output ErrCust_boNvmDirtyFreezeFrameData = TRUE                                                    
/// \output NvmBlockFreezeFrameDataPs.aucDtcId[ErrCust_ClearFreezeFrameData_Param1] = ERRCUST_DTC_AVAILABLE_FOR_FFD
/// \output (NvmBlockFreezeFrameDataPs.aucAge[ErrCust_ClearFreezeFrameData_Param1] = ERRCUST_MIN_AGE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearFreezeFrameData_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  NvmBlockFreezeFrameDataPs.aucAge[0u]    = 20u;
  NvmBlockFreezeFrameDataPs.aucAge[0u]    = 2u;
  NvmBlockFreezeFrameDataPs.aucDtcId[0u]  = 3u;
  ErrCust_ClearFreezeFrameData_Param1     = 1u;

  //Step 3) Call FUT
  ErrCust_ClearFreezeFrameData(ErrCust_ClearFreezeFrameData_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.asnOFFSET_CALIB_VEHICLE_ATTITUDE [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.asnINST_VAL_VEHICULE_ATTITUDE    [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.ascINSTANT_LVL_POS               [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucLVL_INFO                      [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucVOLTAGE_TERMINAL_DTC          [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucETAT_INFO_DTC                 [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.VEHICLE_SPEED_DTC                [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.KILOMETRAGE_DTC                  [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.INST_VAL_FL_BODY_HIGH_SENSOR_DTC [0u],          0u                            , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.INST_VAL_RL_BODY_HIGH_SENSOR_DTC [0u],          0u                            , == );
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyFreezeFrameData,                                        TRUE                          , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucDtcId[ErrCust_ClearFreezeFrameData_Param1],  ERRCUST_DTC_AVAILABLE_FOR_FFD , == );
  AL_UNITTEST_CHECK(NvmBlockFreezeFrameDataPs.aucAge[ErrCust_ClearFreezeFrameData_Param1]  ,  ERRCUST_MIN_AGE               , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearFreezeFrameData_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function clear freeze frame data corresponding to 'ucFreezeFrameIdx' parameter
///        from table ErrCust_ClearFreezeFrameData which is linked with dtc indicated by aucDtcId field from the same table
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearFreezeFrameData_TestCase(void)
{
  Mt_ErrCust_ClearFreezeFrameData_TestCase1();
  Mt_ErrCust_ClearFreezeFrameData_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetActualErrorIndex_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Get actual error dtc index based on Alec Index input
///
///   - Test subject: Test if the function returns actual error dtc index based on Alec Index input
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_GetActualErrorIndex_Param1 = 0u
/// \input ErrCust_GetActualErrorIndex_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_GetActualErrorIndex_RetVal = ErrCust_aPsRefList[ErrCust_GetActualErrorIndex_Param1]
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetActualErrorIndex_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_GetActualErrorIndex_Param1  = 0u;
  ErrCust_GetActualErrorIndex_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_GetActualErrorIndex_RetVal = ErrCust_GetActualErrorIndex(ErrCust_GetActualErrorIndex_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_RetVal,  ErrCust_aPsRefList[ErrCust_GetActualErrorIndex_Param1], == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ConvertValueSint2Int_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Convert signed values into unsigned values 
///
///   - Test subject: Test if the signet value is grater or equal to 0 and store it to returned value
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ConvertValueSint2Int_Param1 = 4u
/// \input ErrCust_ConvertValueSint2Int_Param2 = 0u
/// \input ErrCust_ConvertValueSint2Int_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ConvertValueSint2Int_RetVal = 4u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ConvertValueSint2Int_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ConvertValueSint2Int_Param1  = 4u;
  ErrCust_ConvertValueSint2Int_Param2  = 0u;
  ErrCust_ConvertValueSint2Int_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ConvertValueSint2Int_RetVal = ErrCust_ConvertValueSint2Int(ErrCust_ConvertValueSint2Int_Param1, ErrCust_ConvertValueSint2Int_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ConvertValueSint2Int_RetVal,  4u, == ); //ErrCust_ConvertValueSint2Int_Param1
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ConvertValueSint2Int_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Convert signed values into unsigned values 
///
///   - Test subject: Test if the signet value is smaller than  0 and return converted value
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ConvertValueSint2Int_Param1 = -1u
/// \input ErrCust_ConvertValueSint2Int_Param2 =  0u
/// \input ErrCust_ConvertValueSint2Int_RetVal =  0u
///
/// - Expectations: 
///
/// \output ErrCust_ConvertValueSint2Int_RetVal = -2147483648u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ConvertValueSint2Int_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ConvertValueSint2Int_Param1  = -1u;
  ErrCust_ConvertValueSint2Int_Param2  =  0u;
  ErrCust_ConvertValueSint2Int_RetVal  =  0u;

  //Step 3) Call FUT
  ErrCust_ConvertValueSint2Int_RetVal = ErrCust_ConvertValueSint2Int(ErrCust_ConvertValueSint2Int_Param1, ErrCust_ConvertValueSint2Int_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ConvertValueSint2Int_RetVal,  -2147483648u , == );//ErrCust_ConvertValueSint2Int_RetVal = (1u << (ErrCust_ConvertValueSint2Int_Param2 - 1u)) | ((uint32)ErrCust_ConvertValueSint2Int_Param1 & ((1u << ErrCust_ConvertValueSint2Int_Param2) - 1u)), == )
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ConvertValueSint2Int_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function converts signed values into unsigned values 
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ConvertValueSint2Int_TestCase(void)
{
  Mt_ErrCust_ConvertValueSint2Int_TestCase1();
  Mt_ErrCust_ConvertValueSint2Int_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ConvertValueInt2Sint_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Convert unsigned values into signed values  
///
///   - Test subject: Test if the unsigned value is grater or equal to 0 and return converted value
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ConvertValueInt2Sint_Param1 = 1u
/// \input ErrCust_ConvertValueInt2Sint_Param2 = 1u
/// \input ErrCust_ConvertValueInt2Sint_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_ConvertValueSint2Int_RetVal = -2147483648u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ConvertValueInt2Sint_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ConvertValueInt2Sint_Param1  = 1u;
  ErrCust_ConvertValueInt2Sint_Param2  = 1u;
  ErrCust_ConvertValueInt2Sint_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ConvertValueInt2Sint_RetVal = ErrCust_ConvertValueInt2Sint(ErrCust_ConvertValueInt2Sint_Param1, ErrCust_ConvertValueInt2Sint_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ConvertValueSint2Int_RetVal,  -2147483648u, == ); //ErrCust_ConvertValueSint2Int_RetVal = ErrCust_ConvertValueInt2Sint_Param1 | (sint32)(ERRCUST_32_BIT_MASK << ErrCust_ConvertValueInt2Sint_Param2);
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ConvertValueInt2Sint_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Convert unsigned values into signed values  
///
///   - Test subject: Test if the unsigned value is grater or equal to 0 and return converted value
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ConvertValueInt2Sint_Param1 = 10u
/// \input ErrCust_ConvertValueInt2Sint_Param2 =  5u
/// \input ErrCust_ConvertValueInt2Sint_RetVal =  5u
///
/// - Expectations: 
///
/// \output ErrCust_ConvertValueSint2Int_RetVal = -2147483648u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ConvertValueInt2Sint_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ConvertValueInt2Sint_Param1  = 10u;
  ErrCust_ConvertValueInt2Sint_Param2  =  5u;
  ErrCust_ConvertValueInt2Sint_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_ConvertValueInt2Sint_RetVal = ErrCust_ConvertValueInt2Sint(ErrCust_ConvertValueInt2Sint_Param1, ErrCust_ConvertValueInt2Sint_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_ConvertValueSint2Int_RetVal,  -2147483648u, == ); 
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ConvertValueSint2Int_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function converts unsigned values into signed values 
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ConvertValueInt2Sint_TestCase(void)
{
  Mt_ErrCust_ConvertValueInt2Sint_TestCase1();
  Mt_ErrCust_ConvertValueInt2Sint_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetStatusOfDtc_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -This function returns the status of a DTC code corresponding with the given DTC index
///
///   - Test subject: Test if function returns corect DTC code
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_GetStatusOfDtc_Param1 = 0u
/// \input ErrCust_aucStatus[0u]         = 64u
/// \input ErrCust_GetStatusOfDtc_RetVal = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[0u]         = 64u
/// \output ErrCust_GetStatusOfDtc_RetVal = 64u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetStatusOfDtc_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_GetStatusOfDtc_Param1  = 0u;
  ErrCust_aucStatus[0u]          = 64u;
  ErrCust_GetStatusOfDtc_RetVal  = 0u;

  //Step 3) Call FUT
  ErrCust_GetStatusOfDtc_RetVal = ErrCust_GetStatusOfDtc(ErrCust_GetStatusOfDtc_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aucStatus[0u],          64u, == ); 
  AL_UNITTEST_CHECK(ErrCust_GetStatusOfDtc_RetVal,  64u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Stores aftermarket LVL ECU data
///   - Test subject: Test if the function stores maximum voltage and stepper info
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                             = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV + 10u
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                           = 0u
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss       = TRUE
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef           = TRUE
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef            = TRUE
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState   = TRUE
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                            = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV + 10u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                          = 0u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss      = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef          = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef           = TRUE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState  = TRUE;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketLvlEcuData(&ErrCust_CaptureAftermarketLvlEcuData_Param1.ucVoltageTerminal);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr -Stores aftermarket LVL ECU data
///   - Test subject: Test if the function stores maximum voltage and stepper info
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                             = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV - 10u
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss       = FALSE
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef           = FALSE
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef            = FALSE
/// \input Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState   = FALSE
/// \input ErrCust_CaptureAftermarketLvlEcuData_Param1.scInstantLvlPos              = 0u
/// \input ErrCust_CaptureAftermarketLvlEcuData_Param1.ucLvlInfo                    = 0u
/// \input ErrCust_CaptureAftermarketLvlEcuData_Param1.ucVoltageTerminal            = 0u
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                           = 0u
///
/// - Expectations: 
///
/// \output ErrCust_CaptureAftermarketLvlEcuData_Param1.scInstantLvlPos   =   1u
/// \output ErrCust_CaptureAftermarketLvlEcuData_Param1.ucLvlInfo         =  13u
/// \output ErrCust_CaptureAftermarketLvlEcuData_Param1.ucVoltageTerminal = 254u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                            = ERRCUST_MAX_ACCEPTED_VOLTAGE_MV - 10u;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpStepLoss      = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpCommDef          = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.boStpPosDef           = FALSE;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1.StatStp.eStatStpThermalState  = FALSE;
  ErrCust_CaptureAftermarketLvlEcuData_Param1.scInstantLvlPos             = 0u;
  ErrCust_CaptureAftermarketLvlEcuData_Param1.ucLvlInfo                   = 0u;
  ErrCust_CaptureAftermarketLvlEcuData_Param1.ucVoltageTerminal           = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                          = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketLvlEcuData(&ErrCust_CaptureAftermarketLvlEcuData_Param1.ucVoltageTerminal);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketLvlEcuData_Param1.scInstantLvlPos,      1u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketLvlEcuData_Param1.ucLvlInfo,           13u, == );
  AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketLvlEcuData_Param1.ucVoltageTerminal,  254u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount,                   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the function stores aftermarket LVL ECU data
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase(void)
{
  Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase1();
  Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ClearAllErrCustAndDemEventIds_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr This function clear RAM tables(ErrCust_aucStatus and Dem_astEventStatus), 
///         and NvmBlockTable (NvmBlockErrCustPs and NvmBlockDemData) according to value of the first parameter
///
///   - Test subject: Test if all DTCs are cleared
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_aucStatus[0u]                         = 1u
/// \input NvmBlockErrCustPs.aucAgingCounter[0u]         = 1u
/// \input NvmBlockErrCustPs.aucErrStatus[0u]            = 1u
/// \input NvmBlockErrCustPs.aucErrFreezeFrameIndex[0u]  = 1u
/// \input ErrCust_boNvmDirtyErrCust                     = FALSE
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[0u]                        = ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE
/// \output NvmBlockErrCustPs.aucAgingCounter[0u]        = 0u
/// \output NvmBlockErrCustPs.aucErrStatus[0u]           = ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR
/// \output NvmBlockErrCustPs.aucErrFreezeFrameIndex[0u] = ERRCUST_DTC_AVAILABLE_FOR_FFD
/// \output ErrCust_boNvmDirtyErrCust                    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ClearAllErrCustAndDemEventIds_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_aucStatus[0u]                         = 1u;
  NvmBlockErrCustPs.aucAgingCounter[0u]         = 1u;
  NvmBlockErrCustPs.aucErrStatus[0u]            = 1u;
  NvmBlockErrCustPs.aucErrFreezeFrameIndex[0u]  = 1u;
  ErrCust_boNvmDirtyErrCust                     = FALSE;

  //Step 3) Call FUT
  ErrCust_ClearAllErrCustAndDemEventIds();

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(ErrCust_aucStatus[0u]                       ,  ERRCUST_STATUS_TEST_NOT_COMPLETED_THIS_CYCLE , == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucAgingCounter[0u]       ,  0u                                           , == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrStatus[0u]          ,  ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR, == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrFreezeFrameIndex[0u],  ERRCUST_DTC_AVAILABLE_FOR_FFD                , == );
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust                   ,  TRUE                                         , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_MapDtc_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Map each DEM event id(ALEC ID) to the coresponding DTC code
///         There is a relationship: 1(DTC) to many(ALEC)
///
///   - Test subject: Test if all DTCs are cleared
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_MapDtc_Param1[0u] = 11u
///
/// - Expectations: 
///
/// \output ErrCust_MapDtc_Param1[0u] = ERRCUST_IxPsError_NONE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_MapDtc_TestCase(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_MapDtc_Param1[0u]  = 11u;

  //Step 3) Call FUT
  ErrCust_MapDtc(ErrCust_MapDtc_Param1);

  //Step 4) Check expected output value   
  AL_UNITTEST_CHECK(ErrCust_MapDtc_Param1[0u],  ERRCUST_IxPsError_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if it is a mapped cust error type (Ps) 
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1 = 0u
/// \input ErrCust_ErrHandling_Param2 = 0u
/// \input ErrCust_aPsRefList[0u]     = 11u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1  = 0u;
  ErrCust_ErrHandling_Param2  = 0u;
  ErrCust_aPsRefList[0u]      = 11u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if it is not a mapped cust error type (Ps) 
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1 = 0u
/// \input ErrCust_ErrHandling_Param2 = 0u
/// \input ErrCust_aPsRefList[0u]     = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]     = ERRCUST_IxPsError_NONE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1  = 0u;
  ErrCust_ErrHandling_Param2  = 0u;
  ErrCust_aPsRefList[0u]      = 0u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  ERRCUST_IxPsError_NONE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if the DTC test failed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1 = 0u
/// \input ErrCust_ErrHandling_Param2 = DEM_STATUS_TEST_FAILED
/// \input ErrCust_aPsRefList[0u]     = 11u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1  = 0u;
  ErrCust_ErrHandling_Param2  = DEM_STATUS_TEST_FAILED;
  ErrCust_aPsRefList[0u]      = 11u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if the DTC test is not failed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1 = 0u
/// \input ErrCust_ErrHandling_Param2 = DEM_STATUS_TEST_FAILED-1
/// \input ErrCust_aPsRefList[0u]     = 11u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1  = 0u;
  ErrCust_ErrHandling_Param2  = DEM_STATUS_TEST_FAILED - 1u;
  ErrCust_aPsRefList[0u]      = 11u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if update is necessary, clear all the corresponding status flags when a dtc test failed and process NVM
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_FAILED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[11u]                   = 47u
/// \output NvmBlockErrCustPs.aucErrStatus[11u]      = 34u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_FAILED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = 0u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aucStatus[11u]             ,  47u, == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrStatus[11u],  34u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if update is not necessary
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_FAILED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = ERRCUST_STATUS_TEST_FAILED
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                   = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_FAILED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = ERRCUST_STATUS_TEST_FAILED;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if this is the first occurrence of the current DTC
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                    = 0u
/// \input ErrCust_ErrHandling_Param2                    = DEM_STATUS_TEST_FAILED
/// \input ErrCust_aPsRefList[0u]                        = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]     = 0u
/// \input NvmBlockErrCustPs.aucAgingCounter[11u]        = 0u
/// \input NvmBlockErrCustPs.aucErrFreezeFrameIndex[11u] = ERRCUST_DTC_AVAILABLE_FOR_FFD
/// \input ErrCust_CaptureFreezeFrameData_Param1         = 12u
///
/// - Expectations: 
///
/// \output ErrCust_CaptureFreezeFrameData_Param1        = 12u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase7(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                     = 0u;
  ErrCust_ErrHandling_Param2                     = DEM_STATUS_TEST_FAILED;
  ErrCust_aPsRefList[0u]                         = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]      = 0u;
  NvmBlockErrCustPs.aucAgingCounter[11u]         = 0u;
  NvmBlockErrCustPs.aucErrFreezeFrameIndex[11u]  = ERRCUST_DTC_AVAILABLE_FOR_FFD;
  ErrCust_CaptureFreezeFrameData_Param1          = 12u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_CaptureFreezeFrameData_Param1,  12u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if this is not the first occurrence of the current DTC
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                    = 0u
/// \input ErrCust_ErrHandling_Param2                    = DEM_STATUS_TEST_FAILED
/// \input ErrCust_aPsRefList[0u]                        = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]     = 0u
/// \input NvmBlockErrCustPs.aucAgingCounter[11u]        = 1u
/// \input NvmBlockErrCustPs.aucErrFreezeFrameIndex[11u] = ERRCUST_DTC_AVAILABLE_FOR_FFD
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0]                        = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase8(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                     = 0u;
  ErrCust_ErrHandling_Param2                     = DEM_STATUS_TEST_FAILED;
  ErrCust_aPsRefList[0u]                         = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]      = 0u;
  NvmBlockErrCustPs.aucAgingCounter[11u]         = 1u;
  NvmBlockErrCustPs.aucErrFreezeFrameIndex[11u]  = ERRCUST_DTC_AVAILABLE_FOR_FFD;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase9
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if the DTC test passed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                    = 0u
/// \input ErrCust_ErrHandling_Param2                    = DEM_STATUS_TEST_FAILED
/// \input ErrCust_aPsRefList[0u]                        = 11u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                        = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase9(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1  = 0u;
  ErrCust_ErrHandling_Param2  = DEM_STATUS_TEST_PASSED ;
  ErrCust_aPsRefList[0u]      = 11u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase10
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if the DTC test failed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  ErrCust_ErrHandling_Param1 = 0u
/// \input  ErrCust_ErrHandling_Param2 = DEM_STATUS_TEST_FAILED - 1u
/// \input  ErrCust_aPsRefList[0u]     = 11u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                        = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase10(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1  = 0u;
  ErrCust_ErrHandling_Param2  = DEM_STATUS_TEST_FAILED - 1u;
  ErrCust_aPsRefList[0u]      = 11u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase11
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if update is necessary
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = 0u 
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase11(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = 0u ;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase12
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if update is not necessary
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = ERRCUST_STATUS_TEST_PASSED 
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                    = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase12(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = ERRCUST_STATUS_TEST_PASSED;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase13
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if DTC is cleared only if all mapped ALECs are passed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = 0u
/// \input ErrCust_boLeft                            = TRUE
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0]                     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase13(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = 0u;
  ErrCust_boLeft                             = TRUE;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase14
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if at least one ALEC is failed than de DTC shall not be cleared
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = 0u
/// \input ErrCust_boLeft                            = FALSE
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0]                     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase14(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = 0u;
  ErrCust_boLeft                             = FALSE;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase15
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if alec test passed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = 0u
/// \input ErrCust_boLeft                            = FALSE
/// \input Dem_boEventPassed_HitCount                = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0]                     = 11u
/// \output Dem_boEventPassed_HitCount                = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase15(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = 0u;
  ErrCust_boLeft                             = FALSE;
  Dem_boEventPassed_HitCount                 = 0u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0]     ,  11u, == );
  AL_UNITTEST_CHECK(Dem_boEventPassed_HitCount,  1u , == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase16
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if alec test failed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                = 0u
/// \input ErrCust_ErrHandling_Param2                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]] = 0u
/// \input ErrCust_boLeft                            = TRUE
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0]                     = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase16(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                 = 0u;
  ErrCust_ErrHandling_Param2                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]  = 0u;
  ErrCust_boLeft                             = TRUE;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase17
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if is the 2nd operation cycle since the DTC test passed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = ERRCUST_DTC_AGING_COUNTER_MAX - 1u
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[11u] = 128u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase17(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = ERRCUST_DTC_AGING_COUNTER_MAX - 1u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aucStatus[11u],  128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase18
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if is not the 2nd operation cycle since the DTC test passed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = ERRCUST_DTC_AGING_COUNTER_MAX 
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u] = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase18(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = ERRCUST_DTC_AGING_COUNTER_MAX;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase19
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if DTC test passed in the last 40  operation cycle
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = 0u 
/// \input ErrCust_ClearMemory_Param1[0u]                            = 0xFFu
/// \input ErrCust_ClearMemory_Param1[1u]                            = 0xFFu
/// \input ErrCust_ClearMemory_Param1[2u]                            = 0xFFu
///
/// - Expectations: 
///
/// \output ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                = 128u
/// \output ErrCust_ClearMemory_RetVal                               = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase19(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                = 0u;
  ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                    = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u;
  ErrCust_boLeft                                            = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0]]  = 0u;
  ErrCust_ClearMemory_Param1[0u]                            = 0xFFu;
  ErrCust_ClearMemory_Param1[1u]                            = 0xFFu;
  ErrCust_ClearMemory_Param1[2u]                            = 0xFFu;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aucStatus[ErrCust_aPsRefList[0u]],  128u, == );
  AL_UNITTEST_CHECK(ErrCust_ClearMemory_RetVal               ,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase20
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if DTC test failed in the last 40  operation cycle
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = 1u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u] = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase20(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = 1u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase21
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if NVM is processed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = 1u
/// \input NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]    = ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                                  = 11u
/// \output NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]] = 0u
/// \output ErrCust_boNvmDirtyErrCust                              = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase21(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = 1u;
  NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]     = ERRCUST_STATUS_TEST_NOT_COMPLETED_SINCE_CLEAR;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0]                                 ,  11u, == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]],  0u, == );
  AL_UNITTEST_CHECK(ErrCust_boNvmDirtyErrCust                             ,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase22
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if NVM is not processed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = 1u
/// \input NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]    = 0u
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                                   = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase22(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = 1u;
  NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]     = 0u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase22
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if NVM is processed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = 1u
/// \input NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]    = ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u]                                  = 11u
/// \output NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]] = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase23(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = 1u;
  NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]     = ERRCUST_STATUS_TEST_FAILED_SINCE_CLEAR;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u]                                 ,  11u, == );
  AL_UNITTEST_CHECK(NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]] ,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase22
///
/// \Functional Safety: NA
///
/// \Test Case Description :
/// \descr  Build the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///         This routine is called every time, a state change of any ALEC ID occurs
///
///   - Test subject: Test if NVM is NOT processed
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ErrHandling_Param1                                = 0u
/// \input ErrCust_ErrHandling_Param2                                = DEM_STATUS_TEST_PASSED
/// \input ErrCust_aPsRefList[0u]                                    = 11u
/// \input ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                 = 0u
/// \input ErrCust_boLeft                                            = TRUE
/// \input NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]] = 1u
/// \input NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]    = 0U
///
/// - Expectations: 
///
/// \output ErrCust_aPsRefList[0u] = 11u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase24(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  ErrCust_ErrHandling_Param1                                 = 0u;
  ErrCust_ErrHandling_Param2                                 = DEM_STATUS_TEST_PASSED;
  ErrCust_aPsRefList[0u]                                     = 11u;
  ErrCust_aucStatus[ErrCust_aPsRefList[0u]]                  = 0u;
  ErrCust_boLeft                                             = TRUE;
  NvmBlockErrCustPs.aucAgingCounter[ErrCust_aPsRefList[0u]]  = 1u;
  NvmBlockErrCustPs.aucErrStatus[ErrCust_aPsRefList[0u]]     = 0u;

  //Step 3) Call FUT
  ErrCust_ErrHandling(ErrCust_ErrHandling_Param1, ErrCust_ErrHandling_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(ErrCust_aPsRefList[0u],  11u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ErrHandling_TestCase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if the status of the  DTC code which is linked to 'unAlecId' according with 'ucAlecStatus'
///
///   - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ErrHandling_TestCase(void)
{    
   Mt_ErrCust_ErrHandling_TestCase1();
   Mt_ErrCust_ErrHandling_TestCase2();
   Mt_ErrCust_ErrHandling_TestCase3();
   Mt_ErrCust_ErrHandling_TestCase4();
   Mt_ErrCust_ErrHandling_TestCase5();
   Mt_ErrCust_ErrHandling_TestCase6();
   Mt_ErrCust_ErrHandling_TestCase7();
   Mt_ErrCust_ErrHandling_TestCase8();
   Mt_ErrCust_ErrHandling_TestCase9();
   Mt_ErrCust_ErrHandling_TestCase10();
   Mt_ErrCust_ErrHandling_TestCase11();
   Mt_ErrCust_ErrHandling_TestCase12();
   Mt_ErrCust_ErrHandling_TestCase13();
   Mt_ErrCust_ErrHandling_TestCase14();
   Mt_ErrCust_ErrHandling_TestCase15();
   Mt_ErrCust_ErrHandling_TestCase16();
   Mt_ErrCust_ErrHandling_TestCase17();
   Mt_ErrCust_ErrHandling_TestCase18();
   Mt_ErrCust_ErrHandling_TestCase19();
   Mt_ErrCust_ErrHandling_TestCase20();
   Mt_ErrCust_ErrHandling_TestCase21();
   Mt_ErrCust_ErrHandling_TestCase22();
   Mt_ErrCust_ErrHandling_TestCase23();
   Mt_ErrCust_ErrHandling_TestCase24();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                      low beam light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_LB
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_LB
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_LB;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_LB;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                      high beam light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_hB
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_HB
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_HB;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_HB;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     DayTime Running light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_DRL_POS
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_DRL_POS
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_DRL_POS;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_DRL_POS;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     Turn Indicator light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_TI
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_TI
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_TI;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_TI;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     Side Marker light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_SM
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_SM
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_SM;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_SM;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     RGB light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_RGB
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_RGB
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_RGB;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_RGB;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     fog  light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_FOG
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_FOG
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_FOG;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_FOG;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     cornering  light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_CORNERING
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_CL
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1                   = ERRCUST_LIGHT_FUNCTION_CORNERING;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_CL;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function return binning class and NTC errors for 
///                     unknown  light function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param1                   = 8u
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_CL
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE
/// \input ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE
///
///    - Expectations :
///
/// \output ErrCust_GetNTCBinningErrorPerChannel_RetVal  = 0u
///
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase9(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_GetNTCBinningErrorPerChannel_Param1 = 8u; // Light functions
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucChannelName[0] = ERRCUST_LF_CL;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucRbinError[0]   = TRUE;
  ErrCust_GetNTCBinningErrorPerChannel_Param2.aucNtcError[0]    = TRUE;

  //Step 3) Call FUT
  ErrCust_GetNTCBinningErrorPerChannel_RetVal = ErrCust_GetNTCBinningErrorPerChannel(ErrCust_GetNTCBinningErrorPerChannel_Param1, ErrCust_GetNTCBinningErrorPerChannel_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetNTCBinningErrorPerChannel_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_GetNTCBinningErrorPerChannel
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that function return binning class and NTC errorS per light function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_GetNTCBinningErrorPerChannel(void)
{
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase1();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase2();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase3();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase4();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase5();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase6();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase7();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase8();
  Mt_ErrCust_GetNTCBinningErrorPerChannel_TestCase9();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ReadNtcVal
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls the RTE for thermozone states
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input ErrCust_ReadNtcVal_Param1.eSigQty[1]             = 1u
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount    = 0u
/// \input ErrCust_ReadNtcVal_RetVal                        = 0u
///
///    - Expectations :
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[1]  = 0u
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount           = 1u
/// \output ErrCust_ReadNtcVal_RetVal                               = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ReadNtcVal(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_ReadNtcVal_Param1.eSigQty[1]           = 1u;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 0u;
  ErrCust_ReadNtcVal_RetVal                      = 0u;

  //Step 3) Call FUT
  ErrCust_ReadNtcVal_RetVal = ErrCust_ReadNtcVal(&ErrCust_ReadNtcVal_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[1],  0u, == );
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount,           1u, == );
  AL_UNITTEST_CHECK(ErrCust_ReadNtcVal_RetVal,                               0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Get_NTC_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls an array of function pointers for each led channel
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_Get_NTC_Param1                                                       = 1u
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ErrCust_Get_NTC_Param1]  = SIG_VALID
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                                = 0u
///
///    - Expectations :
///
/// \input ErrCust_Get_NTC_RetVal                         = 0u
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Get_NTC_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_Get_NTC_Param1                                                       = 1u;
  Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ErrCust_Get_NTC_Param1]  = SIG_VALID;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount                                = 0u;

  //Step 3) Call FUT+
  ErrCust_Get_NTC_RetVal = ErrCust_Get_NTC(ErrCust_Get_NTC_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Get_NTC_RetVal,                         0u, == );
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Get_NTC_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls an array of function pointers for each led channel
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_Get_NTC_Param1                                                       = 1u
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ErrCust_Get_NTC_Param1]  = SIG_INVALID
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                                = 0u
///
///    - Expectations :
///
/// \output ErrCust_Get_NTC_RetVal                         = 1u
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Get_NTC_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_Get_NTC_Param1                                                       = 1u;
  Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ErrCust_Get_NTC_Param1]  = SIG_INVALID;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount                                = 0u;

  //Step 3) Call FUT
  ErrCust_Get_NTC_RetVal = ErrCust_Get_NTC(ErrCust_Get_NTC_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Get_NTC_RetVal,                         1u, == );
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Get_NTC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls an array of function pointers for each led channel
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Get_NTC(void)
{
  Mt_ErrCust_Get_NTC_TestCase1();
  Mt_ErrCust_Get_NTC_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ReadTgtBinningVal_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls an array of function pointers for each led channel
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input Rte_Read_RSens_BinningClass_sVal_02_RetVal                                               = 10u
/// \input Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty                                       = SIG_INIT
/// \input Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning                                     = 3u
/// \input ErrCust_ReadTgtBinningVal_Param1                                                         = 2u
/// \input Diag_Callbacks_D420_apfnReadTgtBinningClass_sVal_List[ErrCust_ReadTgtBinningVal_Param1]  = Rte_Read_RSens_BinningClass_sVal_02
/// \input ErrCust_ReadTgtBinningVal_Param2                                                         = &MtTest
/// \input ErrCust_ReadTgtBinningVal_RetVal                                                         = 0u
///
///    - Expectations :
///
/// \input ErrCust_ReadTgtBinningVal_RetVal             = 10u
/// \input ErrCust_ReadTgtBinningVal_Param2->eSigQty    = SIG_INIT
/// \input ErrCust_ReadTgtBinningVal_Param2->ucBinning  = 3u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ReadTgtBinningVal_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_BinningClass_sVal_02_RetVal                                   = 10u;
  Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty                           = SIG_INIT;
  Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning                         = 3u;
  tsRte_Binning0 MtTest                                                        = { 0u, SIG_VALID };
  ErrCust_ReadTgtBinningVal_Param1                                             = 2u;
  ErrCust_apfnReadTgtBinningClass_sVal_List[ErrCust_ReadTgtBinningVal_Param1]  = Rte_Read_RSens_BinningClass_sVal_02;
  ErrCust_ReadTgtBinningVal_Param2                                             = &MtTest;
  ErrCust_ReadTgtBinningVal_RetVal                                             = 0u;

  //Step 3) Call FUT
  ErrCust_ReadTgtBinningVal_RetVal = ErrCust_ReadTgtBinningVal(ErrCust_ReadTgtBinningVal_Param1, ErrCust_ReadTgtBinningVal_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ReadTgtBinningVal_RetVal,                  10u, == );
  AL_UNITTEST_CHECK(ErrCust_ReadTgtBinningVal_Param2->eSigQty,    SIG_INIT, == );
  AL_UNITTEST_CHECK(ErrCust_ReadTgtBinningVal_Param2->ucBinning,        3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ReadTgtBinningVal_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls an array of function pointers for each led channel
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_ReadTgtBinningVal_Param1                                                        = 2u
/// \input Diag_Callbacks_D420_apfnReadTgtBinningClass_sVal_List[ErrCust_ReadTgtBinningVal_Param1] = NULL_PTR
/// \input ErrCust_ReadTgtBinningVal_Param2                                                        = &MtTest
/// \input ErrCust_ReadTgtBinningVal_RetVal                                                        = 0u
///
///    - Expectations :
///
/// \output ErrCust_ReadTgtBinningVal_RetVal == 0u;
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ReadTgtBinningVal_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  tsRte_Binning0 MtTest                                                        = { 0u, SIG_VALID };
  ErrCust_ReadTgtBinningVal_Param1                                             = 2u;
  ErrCust_apfnReadTgtBinningClass_sVal_List[ErrCust_ReadTgtBinningVal_Param1]  = NULL_PTR;
  ErrCust_ReadTgtBinningVal_Param2                                             = &MtTest;
  ErrCust_ReadTgtBinningVal_RetVal                                             = 0u;

  //Step 3) Call FUT
  ErrCust_ReadTgtBinningVal_RetVal = ErrCust_ReadTgtBinningVal(ErrCust_ReadTgtBinningVal_Param1, ErrCust_ReadTgtBinningVal_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ReadTgtBinningVal_RetVal,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_ReadTgtBinningVal
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function calls an array of function pointers for each led channel
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_ReadTgtBinningVal(void)
{
  Mt_ErrCust_ReadTgtBinningVal_TestCase1();
  Mt_ErrCust_ReadTgtBinningVal_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Get_BinningClass_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if function verify signal qty is SIG_VALID and 
///                     or binning is  binningClassErr return true
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning  = eBinningClassErr
/// \input Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty    = SIG_VALID
/// \input ErrCust_Get_BinningClass_Param1                       = 2u
/// \input ErrCust_ReadTgtBinningVal_Param1                      = 2u
///
///    - Expectations :
///
/// \output ErrCust_Get_BinningClass_RetVal  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Get_BinningClass_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning  = eBinningClassErr;
  Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty    = SIG_VALID;
  ErrCust_Get_BinningClass_Param1                       = 2u;
  ErrCust_ReadTgtBinningVal_Param1                      = 2u;

  //Step 3) Call FUT
  ErrCust_Get_BinningClass_RetVal = ErrCust_Get_BinningClass(ErrCust_Get_BinningClass_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Get_BinningClass_RetVal,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Get_BinningClass_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if function verify signal qty is SIG_VALID and 
///                     or binning is different by binningClassErr return false
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input Rte_Read_RSens_BinningClass_sVal_02_Param1.ucBinning  = eBinningClass1
/// \input Rte_Read_RSens_BinningClass_sVal_02_Param1.eSigQty    = SIG_VALID
/// \input ErrCust_Get_BinningClass_Param1                       = 1u
/// \input ErrCust_ReadTgtBinningVal_Param1                      = 1u
///
///    - Expectations :
///
/// \output ErrCust_Get_BinningClass_RetVal  = 0u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Get_BinningClass_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_BinningClass_sVal_01_Param1.ucBinning  = eBinningClass1;
  Rte_Read_RSens_BinningClass_sVal_01_Param1.eSigQty    = SIG_VALID;
  ErrCust_Get_BinningClass_Param1                       = 1u;
  ErrCust_ReadTgtBinningVal_Param1                      = 1u;

  //Step 3) Call FUT
  ErrCust_Get_BinningClass_RetVal = ErrCust_Get_BinningClass(ErrCust_Get_BinningClass_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Get_BinningClass_RetVal,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Get_BinningClass
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that function return binning class for each led channel
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Get_BinningClass(void)
{
  Mt_ErrCust_Get_BinningClass_TestCase1();
  Mt_ErrCust_Get_BinningClass_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CodingDataValidation_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function get and handle coding parameters for ErrCust module
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input Rte_Read_CodM_Err_Para_Param1.eCodingState               = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks  = &sUT_Coding_Stub;
/// \input Rte_Read_CodM_Err_Para_HitCount                          = 0u;
///
///    - Expectations :
///
/// \input ErrCust_CodingDataValidation_RetVal  = TRUE
/// \input Rte_Read_CodM_Err_Para_HitCount      = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CodingDataValidation_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  tNvmPara_CodingArea sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_Param1.eCodingState               = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks  = &sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_HitCount                          = 0u;

  //Step 3) Call FUT
  ErrCust_CodingDataValidation_RetVal = ErrCust_CodingDataValidation();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_CodingDataValidation_RetVal,  TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_Err_Para_HitCount,        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CodingDataValidation_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function get and handle coding parameters for ErrCust module
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input Rte_Read_CodM_Err_Para_Param1.eCodingState               = eParaFct0_CodingDataInvalid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks  = &sUT_Coding_Stub;
/// \input Rte_Read_CodM_Err_Para_HitCount                          = 0u;
///
///    - Expectations :
///
/// \input ErrCust_CodingDataValidation_RetVal  = FALSE
/// \input Rte_Read_CodM_Err_Para_HitCount      = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CodingDataValidation_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  tNvmPara_CodingArea sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_Param1.eCodingState               = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks  = &sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_HitCount                          = 0u;

  //Step 3) Call FUT
  ErrCust_CodingDataValidation_RetVal = ErrCust_CodingDataValidation();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_CodingDataValidation_RetVal,  FALSE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_Err_Para_HitCount,         1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CodingDataValidation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that function  get and handle coding parameters for ErrCust module
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CodingDataValidation(void)
{
  Mt_ErrCust_CodingDataValidation_TestCase1();
  Mt_ErrCust_CodingDataValidation_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Data_ParaFct0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function ErrCust_Data_ParaFct0 get coding data and return
///                     valid coding data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_Data_ParaFct0_Param1                             = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks  = &sUT_Coding_Stub;
///
///    - Expectations :
///
/// \output ErrCust_Data_ParaFct0_RetVal  = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Data_ParaFct0_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  tNvmPara_CodingArea sUT_Coding_Stub;
  ErrCust_Data_ParaFct0_Param1                             = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks  = &sUT_Coding_Stub;

  //Step 3) Call FUT
  ErrCust_Data_ParaFct0_RetVal = ErrCust_Data_ParaFct0(ErrCust_Data_ParaFct0_Param1, &ErrCust_Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Data_ParaFct0_RetVal,  TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Data_ParaFct0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function ErrCust_Data_ParaFct0 get coding data and return
///                     valid coding data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_Data_ParaFct0_Param1 = eParaFct0_CodingDataInvalid
///
///    - Expectations :
///
/// \output ErrCust_Data_ParaFct0_RetVal  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Data_ParaFct0_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_Data_ParaFct0_Param1  = eParaFct0_CodingDataInvalid;

  //Step 3) Call FUT
  ErrCust_Data_ParaFct0_RetVal = ErrCust_Data_ParaFct0(ErrCust_Data_ParaFct0_Param1, &ErrCust_Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Data_ParaFct0_RetVal,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Data_ParaFct0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function ErrCust_Data_ParaFct0 get coding data and return
///                     valid coding data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_Data_ParaFct0_Param1  = 2u
///
///    - Expectations :
///
/// \output ErrCust_Data_ParaFct0_RetVal  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Data_ParaFct0_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_Data_ParaFct0_Param1  = 2u;

  //Step 3) Call FUT
  ErrCust_Data_ParaFct0_RetVal = ErrCust_Data_ParaFct0(ErrCust_Data_ParaFct0_Param1, &ErrCust_Data_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_Data_ParaFct0_RetVal,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_Data_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that function get and handle coding parameters for Diag module
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_Data_ParaFct0(void)
{
  Mt_ErrCust_Data_ParaFct0_TestCase1();
  Mt_ErrCust_Data_ParaFct0_TestCase2();
  Mt_ErrCust_Data_ParaFct0_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function verify if length is different by 2 bytes return 
///                      Incorrect Message Length Or Invalid Format
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]  = 0
///
///    - Expectations :
///
/// \output IMLOIF
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]  = 0;
  ErrCust_boCodingValidity                                   = TRUE;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData(ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1);

  //Step 4) Check expected output values
  //AL_UNITTEST_CHECK(ErrCust_CaptureAftermarketRbinNtcFailureEcuData_RetVal, IMLOIF, == );
}

tNvmPara_CodingArea sUT_Coding_Stub;
//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function verify if length is different by 2 bytes return 
///                      Torque Converter Clutch Locked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]  = 0;
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]  = 0;
/// \input Rte_Read_CodM_Err_Para_Param1.eCodingState                 = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks    = &sUT_Coding_Stub;
/// \input Rte_Read_CodM_Err_Para_HitCount                            = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount               = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                 = eLeft;
/// \input //ErrCust_Get_NTC_Param1[0]                                = 0u;
/// \input //ErrCust_Get_NTC_Param1[1]                                = 0u;
/// \input //ErrCust_Get_NTC_Param1[2]                                = 0u;
/// \input //ErrCust_Get_NTC_Param1[3]                                = 0u;
/// \input //ErrCust_Get_NTC_Param2                                   = 0u;
/// \input //ErrCust_Get_NTC_HitCount                                 = 0u;
/// \input //ErrCust_Get_NTC_RetVal                                   = DIAG_OK;
///
///    - Expectations :
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]  = 0;
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]  = 0;
  Rte_Read_CodM_Err_Para_Param1.eCodingState                 = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks    = &sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_HitCount                            = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount               = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1                 = eLeft;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData(ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function verify if length is different by 2 bytes return 
///                      Torque Converter Clutch Locked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]                                = 0;
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]                                = 0;
/// \input sUT_Coding_Stub.MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.BasePwm_Left_Unit1    = 0u;
/// \input sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.BasePwm_Right_Unit1  = 0u;
/// \input Rte_Read_CodM_Err_Para_Param1.eCodingState                                               = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks                                  = &sUT_Coding_Stub;
/// \input Rte_Read_CodM_Err_Para_HitCount                                                          = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount                                             = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                                               = eRight;
///
///    - Expectations :
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]                                 = 0;
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]                                 = 0;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit10      = 1u;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit10     = 1u;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.BasePwm_Right_Unit10  = 1u;
  Rte_Read_CodM_Err_Para_Param1.eCodingState                                                = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks                                   = &sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_HitCount                                                           = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount                                              = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1                                                = eRight;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData(ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function verify if length is different by 2 bytes return 
///                      Torque Converter Clutch Locked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]                                  = 0;
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]                                  = 0;
/// \input sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit1        = 3u;
/// \input sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit1       = 2u;
/// \input sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit1       = 7u;
/// \input sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit1  = 3u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[1u]                                    = SIG_INVALID;
/// \input Rte_Read_CodM_Err_Para_Param1.eCodingState                                                 = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks                                    = &sUT_Coding_Stub;
/// \input Rte_Read_CodM_Err_Para_HitCount                                                            = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount                                               = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                                                 = eLeft;
///
///    - Expectations :
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]                                  = 0;
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]                                  = 0;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit1        = 3u;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit1       = 2u;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit1       = 7u;
  sUT_Coding_Stub.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit1  = 3u;
  Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[1u]                                    = SIG_INVALID;
  Rte_Read_CodM_Err_Para_Param1.eCodingState                                                 = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks                                    = &sUT_Coding_Stub;
  Rte_Read_CodM_Err_Para_HitCount                                                            = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount                                               = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1                                                 = eRight;
  ErrCust_Get_NTC_Param1                                                                     = 0u;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData(ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function verify if length is different by 2 bytes return 
///                      Torque Converter Clutch Locked
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]  = 0;
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]  = 0;
/// \input Rte_Read_CodM_Err_Para_Param1.eCodingState                 = eParaFct0_CodingDataInvalid;
/// \input Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks    = &sUT_Coding_Stub;
///
///    - Expectations :
///
/// \input ErrCust_CaptureAftermarketRbinNtcFailureEcuData_RetVal  = CNC
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[0]  = 0;
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1[1]  = 0;
  Rte_Read_CodM_Err_Para_Param1.eCodingState                 = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_Err_Para_Param1.psCodingParameters_Blocks    = &sUT_Coding_Stub;

  //Step 3) Call FUT
  ErrCust_CaptureAftermarketRbinNtcFailureEcuData(ErrCust_CaptureAftermarketRbinNtcFailureEcuData_Param1);

  //Step 4) Check expected output values
  // no output
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that function  diagnostic subservice that returns the RBIN/NTC failure per light function
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData(void)
{
  Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase1();
  Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase2();
  Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase3();
  Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase4();
  Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData_TestCase5();
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
  /*ErrCust_RteAccess.c*/
  ALUnitTest_AddFunction("Mt_ErrCust_RteAccess_Read_FctR_TI_FctErrState_TestCase",          Mt_ErrCust_RteAccess_Read_FctR_TI_FctErrState_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase",          Mt_ErrCust_RteAccess_Read_FctR_LgtFctErrState_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase",            Mt_ErrCust_RteAccess_Read_FctR_LgtFctStatus_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase",   Mt_ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase",           Mt_ErrCust_RteAccess_Read_CtrlStp_ActStatStp_TestCase);
   
  /*ctaaErrCust*/
  ALUnitTest_AddFunction("Mt_riErrCust_Init_TestCase",                                      Mt_riErrCust_Init_TestCase);
  ALUnitTest_AddFunction("Mt_rpErrCust_Cycle0_TestCase",                                    Mt_rpErrCust_Cycle0_TestCase);
   
  /*ErrCust.c*/
  ALUnitTest_AddFunction("Mt_ErrCust_Init_TestCase",                                        Mt_ErrCust_Init_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_CaptureFreezeFrameData_TestCase",                      Mt_ErrCust_CaptureFreezeFrameData_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase",           Mt_ErrCust_CaptureAftermarketAttitudeEcuData_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase",            Mt_ErrCust_CaptureAftermarketContextEcuData_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ucGetClearMemoryType_TestCase",                        Mt_ErrCust_ucGetClearMemoryType_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ClearMemory_TestCase",                                 Mt_ErrCust_ClearMemory_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ucGetStatusOfDTC_TestCase",                            Mt_ErrCust_ucGetStatusOfDTC_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_SetAvailableDtc_TestCase",                             Mt_ErrCust_SetAvailableDtc_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ucGetErrorCount_TestCase",                             Mt_ErrCust_ucGetErrorCount_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_Cycle0_TestCase",                                      Mt_ErrCust_Cycle0_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ulGetDtcCode_TestCase",                                Mt_ErrCust_ulGetDtcCode_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ResetDtcIndex_TestCase",                               Mt_ErrCust_ResetDtcIndex_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ClearFreezeFrameData_TestCase",                        Mt_ErrCust_ClearFreezeFrameData_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_GetActualErrorIndex_TestCase",                         Mt_ErrCust_GetActualErrorIndex_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ConvertValueSint2Int_TestCase",                        Mt_ErrCust_ConvertValueSint2Int_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ConvertValueInt2Sint_TestCase",                        Mt_ErrCust_ConvertValueInt2Sint_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_GetStatusOfDtc_TestCase",                              Mt_ErrCust_GetStatusOfDtc_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ErrHandling_TestCase",                                 Mt_ErrCust_ErrHandling_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase",                Mt_ErrCust_CaptureAftermarketLvlEcuData_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_ClearAllErrCustAndDemEventIds_TestCase",               Mt_ErrCust_ClearAllErrCustAndDemEventIds_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_MapDtc_TestCase",                                      Mt_ErrCust_MapDtc_TestCase);
  ALUnitTest_AddFunction("Mt_ErrCust_GetNTCBinningErrorPerChannel",                         Mt_ErrCust_GetNTCBinningErrorPerChannel);
  ALUnitTest_AddFunction("Mt_ErrCust_ReadTgtBinningVal",                                    Mt_ErrCust_ReadTgtBinningVal);
  ALUnitTest_AddFunction("Mt_ErrCust_Get_BinningClass",                                     Mt_ErrCust_Get_BinningClass);
  ALUnitTest_AddFunction("Mt_ErrCust_ReadNtcVal",                                           Mt_ErrCust_ReadNtcVal);
  ALUnitTest_AddFunction("Mt_ErrCust_Get_NTC",                                              Mt_ErrCust_Get_NTC);
  ALUnitTest_AddFunction("Mt_ErrCust_CodingDataValidation",                                 Mt_ErrCust_CodingDataValidation);
  ALUnitTest_AddFunction("Mt_ErrCust_Data_ParaFct0",                                        Mt_ErrCust_Data_ParaFct0);
  ALUnitTest_AddFunction("Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData",              Mt_ErrCust_CaptureAftermarketRbinNtcFailureEcuData);
}


// EOF

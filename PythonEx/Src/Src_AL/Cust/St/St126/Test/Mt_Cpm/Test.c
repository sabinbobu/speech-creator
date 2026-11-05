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
/// \brief  Unit Test Cases for Cpm
///
/// \author	Maramreddy SathishReddy(F01517E)
///         sathishreddy.maramreddy[at]externalmarelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - Cpm_Adapter.c
//=============================================================================

//=============================================================================
// Includes
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
/// \Test Case : Mt_Cpm_Cpm_RteAccess_Read_Vbat
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to check the  Read Vbat voltage Rte call wrapper 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input	Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input	Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1    = 1u;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 1u;
/// \output Cpm_RteAccess_Read_Vbat_RetVal                  = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Read_Vbat(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = 1u;

  //Step 3) Call FUT
  Cpm_RteAccess_Read_Vbat_RetVal = Cpm_RteAccess_Read_Vbat();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_RteAccess_Read_Vbat_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_ParaFct0_TestCase_1()
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to check the coding parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input	 Cpm_ParaFct0_Param1    = eParaFct0_CodingDataValid;
/// \input	 Cpm_ParaFct0_Param2    = 1u;
///
///   - Expectations:
///
/// \output Cpm_boCodingValid       = TRUE;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Cpm_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  Cpm_ParaFct0_Param2 = 1u;

  //Step 3) Call FUT
  Cpm_ParaFct0_RetVal = Cpm_ParaFct0(Cpm_ParaFct0_Param1, &Cpm_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_ParaFct0_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_ParaFct0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to check the coding parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input	 Cpm_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
/// \input	 Cpm_ParaFct0_Param2 = 1u;
///
///   - Expectations:
///
/// \output Cpm_boCodingValid	= FALSE;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Cpm_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  Cpm_ParaFct0_Param2 = 1u;

  //Step 3) Call FUT
  Cpm_ParaFct0_RetVal = Cpm_ParaFct0(Cpm_ParaFct0_Param1, &Cpm_ParaFct0_Param2);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_ParaFct0_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_ParaFct0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to check the coding parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input	 Cpm_ParaFct0_Param1 = 5u;
/// \input	 Cpm_ParaFct0_Param2 = 1u;
///
///   - Expectations:
///
/// \output Cpm_boCodingValid	= FALSE;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_ParaFct0_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Cpm_ParaFct0_Param1 = 5u;
  Cpm_ParaFct0_Param2 = 1u;

  //Step 3) Call FUT
  Cpm_ParaFct0_RetVal = Cpm_ParaFct0(Cpm_ParaFct0_Param1, &Cpm_ParaFct0_Param2);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_ParaFct0_RetVal, FALSE, == );
}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check this function to check the coding parameters based on given inputs
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_ParaFct0(void)
{
  Mt_Cpm_Cpm_ParaFct0_TestCase_1();
  Mt_Cpm_Cpm_ParaFct0_TestCase_2();
  Mt_Cpm_Cpm_ParaFct0_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_MapParams
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to Maps the coding parameter in order to acces them in Thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input	 Rte_Read_CodM_AppM_Para_HitCount                         = 0u;
/// \input	 Rte_Read_CodM_AppM_Para_Param1.eCodingState              = eParaFct0_CodingDataValid;
/// \input	 Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
///
///   - Expectations:
///
/// \output  Cpm_boCodingValid                                         = TRUE;
/// \output  Rte_Read_CodM_AppM_Para_HitCount                          = 1u ;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_MapParams(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_AppM_Para_HitCount = 0u;
  Rte_Read_CodM_AppM_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 3) Call FUT
  Cpm_MapParams_RetVal = Cpm_MapParams();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_MapParams_RetVal, TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_AppM_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_Read_PhaseVie
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to  Read Ecu operating mode from Rte
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_SysMon_LifePhases_Param1.eSigQty        = SIG_VALID;
/// \input Rte_Read_SysMon_LifePhases_Param1.ePhaseVie      = eNormalMode;
/// \input Rte_Read_SysMon_LifePhases_HitCoun               = 0u;
/// \input Std_ReturnType Cpm_Read_PhaseVie_RetVal          = eSwitchToStadby;
///
///   - Expectations:
///
/// \output  Rte_Read_SysMon_LifePhases_HitCount           = 1u;
/// \output  Cpm_Read_PhaseVie_RetVal                      = eStandBy;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_Read_PhaseVie(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode;
  Rte_Read_SysMon_LifePhases_HitCount = 0u;
  Cpm_Read_PhaseVie_RetVal = eSwitchToStadby;

  //Step 3) Call FUT 
  Cpm_Read_PhaseVie_RetVal = Cpm_Read_PhaseVie(&Cpm_Read_PhaseVie_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_Read_PhaseVie_RetVal, eStandBy, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_RteAccess_Get_ECU_Side_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to  return ECU side, used for coding data handling
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input	 Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
/// \input	 Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
/// \input	 Cpm_RteAccess_Get_ECU_Side_RetVal             = 1u;
///
///   - Expectations:
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u;
/// \output  Cpm_RteAccess_Get_ECU_Side_RetVal             = eMountedRight;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Get_ECU_Side_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Cpm_RteAccess_Get_ECU_Side_RetVal = 1u;

  //Step 3) Call FUT 
  Cpm_RteAccess_Get_ECU_Side_RetVal = Cpm_RteAccess_Get_ECU_Side();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_Param1, eMountedRight, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ECU_Side_RetVal, eMountedRight, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_RteAccess_Get_ECU_Side_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check this function to  return ECU side, used for coding data handling
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input	 Rte_Read_IoHwAbUser_GetMountingSide_Param1    = 5u;
/// \input	 Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
/// \input	 Cpm_RteAccess_Get_ECU_Side_RetVal             = 1u;
///
///   - Expectations:
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = 5u;
/// \output  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 1u;
/// \output  Cpm_RteAccess_Get_ECU_Side_RetVal             = 255u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Get_ECU_Side_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = 5u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  Cpm_RteAccess_Get_ECU_Side_RetVal = 1u;

  //Step 3) Call FUT 
  Cpm_RteAccess_Get_ECU_Side_RetVal = Cpm_RteAccess_Get_ECU_Side();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_Param1, 5u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ECU_Side_RetVal, 255u, == );
}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_RteAccess_Get_ECU_Side
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check this function to  return ECU side, used for coding data handling
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Get_ECU_Side(void)
{
  Mt_Cpm_Cpm_RteAccess_Get_ECU_Side_TestCase_1();
  Mt_Cpm_Cpm_RteAccess_Get_ECU_Side_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check this function to  returns the status of ETAT_FEUX_STATIONMENT
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty  = SIG_VALID;
/// \input Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_LeftSide;
///
///   - Expectations:
///
/// \output Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_Deactivated;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_LeftSide;

  //Step 3) Call FUT
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal, eEtatFeuxStationnement_Deactivated, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check this function to  returns the status of ETAT_FEUX_STATIONMENT
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input	 Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty  = SIG_VALID;
/// \input	 Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_Deactivated;
///
///   - Expectations:
///
/// \output Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_Deactivated;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_SNA;
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_LeftSide;

  //Step 3) Call FUT
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal, eEtatFeuxStationnement_Deactivated, == );
}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function to  returns the status of ETAT_FEUX_STATIONMENT
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT(void)
{
  Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_TestCase_1();
  Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_RteAccess_Write_PwFact_Temp
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Check this function to Write power factor and temperature per thermozone
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input   Rte_Write_Cpm_PowFact_Temp_HitCount = 0u;
///
///   - Expectations:
///
/// \output Rte_Write_Cpm_PowFact_Temp_HitCount = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_RteAccess_Write_PwFact_Temp(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Write_Cpm_PowFact_Temp_HitCount = 0u;

  //Step 3) Call FUT
  Cpm_RteAccess_Write_PwFact_Temp(&Cpm_RteAccess_Write_PwFact_Temp_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Cpm_PowFact_Temp_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCoun                      = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                    = 50u;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                = SIG_VALID;
/// \input Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal               = eEtatFeuxStationnement_LeftSide;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                   = eMountedRight;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_RetVal                   = eMountedUndef;
/// \input Rte_Read_RSens_PcbTemperature_HitCount                       = 0u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_SNA;
/// \input CPM_Gen_Param5.eQty                                          = TESIGQTY_SIG_VALID;
///
/// - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount               = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                    = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                     = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount              = 1u;
/// \output Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal              = eEtatFeuxStationnement_LeftSide;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = 1u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_LeftSide;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_RetVal = eMountedUndef;
  Rte_Read_RSens_PcbTemperature_HitCount = 0u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_SNA;
  }
  CPM_Gen_Param5.eQty = TESIGQTY_SIG_VALID;

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal, eEtatFeuxStationnement_LeftSide, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                 = 1u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_HitCount                      = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount                 = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                    = 50u;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                = SIG_VALID;
/// \input Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal               = eEtatFeuxStationnement_LeftSide;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                   = eMountedRight;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_RetVal                   = eMountedUndef;
/// \input Rte_Read_RSens_PcbTemperature_HitCount                       = 0u;
/// \input CPM_Gen_Param5.eQty                                          = TESIGQTY_SIG_SNA;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
///
/// - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount               = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                    = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                     = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount              = 1u;
/// \output Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal              = eEtatFeuxStationnement_LeftSide;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = 1u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_LeftSide;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_RetVal = eMountedUndef;
  Rte_Read_RSens_PcbTemperature_HitCount = 0u;
  CPM_Gen_Param5.eQty = TESIGQTY_SIG_SNA;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal, eEtatFeuxStationnement_LeftSide, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input Rte_Read_RSens_PcbTemperature_HitCount          = 0u;
/// \input Rte_Write_CpmHssTarget0_sSetting_HitCount       = 0u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                    = 1u;
/// \input sThzTemperatures.eSigQty[ucChIdx]               = SIG_VALID;
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
/// \output Rte_Write_CpmHssTarget0_sSetting_HitCount      = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  Rte_Read_RSens_PcbTemperature_HitCount = 0u;
  Rte_Write_CpmHssTarget0_sSetting_HitCount = 0u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INIT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_CpmHssTarget0_sSetting_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                 = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                      = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                       = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                  = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                     = 50u;
/// \input CPM_PARA_aucTz2Temp[CFG_THERMOZONES_NR]                       = 13u;
/// \input  CPM_PARA_aucTz2Temp[ucChIdx]                                 = 10u;
/// \input  Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  CPM_PARA_aucTz2Temp[CFG_THERMOZONES_NR] = 13u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_TIMEOUT;
/// \input sThzTemperatures.eSigQty[ucChIdx] = SIG_VALID;
 ///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_TIMEOUT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                    = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DEFAULT;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DEFAULT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                    = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DISABLED;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DISABLED;
  }
  
  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_UNAVAILABLE;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_UNAVAILABLE;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_SNA;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_9(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_SNA;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                 = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                      = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                       = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCoun                   = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                     = 50u;
/// \input  CPM_PARA_aucTz2Temp[ucChIdx]                                 = 40u;
/// \input  Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
/// \input  NM_GetMode_Param1                                            = LIMP_HOME_MODE;
///
/// \input ///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
/// \output Cpm_aboFanCtrl[0]                              = 1u;
/// \output Cpm_aboFanCtrl[1]                              = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_10(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  NM_GetMode_Param1 = LIMP_HOME_MODE;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_aboFanCtrl[0], 1u, == );
  AL_UNITTEST_CHECK(Cpm_aboFanCtrl[1], 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_11
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INIT;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_11(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INIT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_12
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 40u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_12(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_13
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                    = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_TIMEOUT;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_13(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_TIMEOUT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_14
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                 = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                    = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                 = 40u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DEFAULT;
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_14(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DEFAULT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}
///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_15
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DEFAULT;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_15(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DISABLED;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_16
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                       = 50u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_E2E_ALIVEERR;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_16(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_TIMEOUT;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_17
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                  = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                       = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                        = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                 = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                   = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                      = 50u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit] = 2000;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                   = 0u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]   = SIG_E2E_ALIVEERR;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_17(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_E2E_ALIVEERR;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_18
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                                  = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                                       = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                                        = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                                 = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                                   = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                                      = 50u;
/// \input NvmBlockInstrumentatedFrames                                                   = TRUE;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit]                 = 40000;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_VALID;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                                   = 0u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_E2E_ALIVEERR;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_VALID;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucChIdx] = 12;
/// \input CPM_PARA_alTzTemp[ucChJdx][ucChIdx]                                            = 1u;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  =  1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       =  1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        =  1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount =  1u
//-----------------------------------------------------------------------------

void Mt_Cpm_Cpm_CodingValidCycle_TestCase_18(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  NvmBlockInstrumentatedFrames = TRUE;

  for (uint8_fast ucLogicalUnit = 0u; ucLogicalUnit < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucLogicalUnit++)
  {
    Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit] = 40000;
  }

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
  }

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 0u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_E2E_ALIVEERR;
  }

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucChIdx] = 12;
  }

  for (uint8 ucChJdx = 1u; ucChJdx > 0u; ucChJdx--)
  {
    for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
    {
      CPM_PARA_alTzTemp[ucChJdx][ucChIdx] = 1u;
    }
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_19
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                     = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                      = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount               = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCoun                  = 0u;
/// \input NvmBlockInstrumentatedFrames                                 = TRUE;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  =  1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       =  1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        =  1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount =  1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_19(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  NvmBlockInstrumentatedFrames = TRUE;

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_20
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:

/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount   = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount        = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount         = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount  = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount    = 0u;
/// \input NvmBlockInstrumentatedFrames                    = TRUE;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount =  1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount      =  1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount       =  1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount=  1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_20(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  NvmBlockInstrumentatedFrames = TRUE;
  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_21
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                                  = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                                       = 0u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                                  = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                                       = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                                        = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                                 = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                                   = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                                      = 50u;
/// \input NvmBlockInstrumentatedFrames                                                   = FALSE;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit]                 = 40000;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_VALID;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                                   = 0u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_E2E_ALIVEERR;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_VALID;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucChIdx] = 12;
/// \input CPM_PARA_alTzTemp[ucChJdx][ucChIdx]                                            = 1u;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount = 1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount      = 1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount	      = 1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount= 1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_21(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  NvmBlockInstrumentatedFrames = FALSE;

  for (uint8_fast ucLogicalUnit = 0u; ucLogicalUnit < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucLogicalUnit++)
  {
    Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit] = 40000;
  }

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
  }

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 0u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_E2E_ALIVEERR;
  }

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucChIdx] = 12;
  }

  for (uint8 ucChJdx = 0u; ucChJdx < 3u; ucChJdx++)
  {
    for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
    {
      CPM_PARA_alTzTemp[ucChJdx][ucChIdx] = 1u;
    }
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_22
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                                  = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                                       = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                                        = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                                 = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                                   = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                                      = 50u;
/// \input NvmBlockInstrumentatedFrames                                                   = FALSE;
/// \input CPM_Gen_Param4->unDutyCycle[ucChIdx]                                           = 60000;
/// \input CPM_Gen_Param4->unCurrent[ucChIdx]                                             = 60000;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit]                 = 40000;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_VALID;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                                   = 0u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_E2E_ALIVEERR;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]                   = SIG_VALID;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucChIdx] = 12;
/// \input CPM_PARA_alTzTemp[ucChJdx][ucChIdx]                                            = 1u;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_22(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  NvmBlockInstrumentatedFrames = FALSE;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)(CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS); ucChIdx++)
  {
    CPM_Gen_Param4.unDutyCycle[ucChIdx] = 60000;
    CPM_Gen_Param4.unCurrent[ucChIdx] = 60000;
  }

  for (uint8_fast ucLogicalUnit = 0u; ucLogicalUnit < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucLogicalUnit++)
  {
    Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucLogicalUnit] = 40000;
  }

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
  }

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 0u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_E2E_ALIVEERR;
  }

  for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucChIdx] = 12;
  }

  for (uint8 ucChJdx = 0u; ucChJdx < 3u; ucChJdx++)
  {
    for (uint8 ucChIdx = 0u; ucChIdx < CPM_CFG_MAX_NO_OF_THERMOZONES; ucChIdx++)
    {
      CPM_PARA_alTzTemp[ucChJdx][ucChIdx] = 1u;
    }
  }

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_23
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input 	Rte_Read_RSens_ThermzoneTemperatures_HitCount       = 0u;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount            = 0u;
/// \input 	Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount             = 0u;
/// \input 	Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount      = 0u;
/// \input 	Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount        = 0u;
/// \input 	CPM_PARA_alTzTemp[1u][1u]                           = 50u;
/// \input 	NvmBlockInstrumentatedFrames                        = FALSE;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unCurrent   = 3000;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 40000;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_23(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  NvmBlockInstrumentatedFrames = FALSE;
  Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unCurrent = 3000;
  Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 32767;

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}


//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_24
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input 	Rte_Read_RSens_ThermzoneTemperatures_HitCount       = 0u;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount            = 0u;
/// \input 	Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount             = 0u;
/// \input 	Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount      = 0u;
/// \input 	Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount        = 0u;
/// \input 	CPM_PARA_alTzTemp[1u][1u]                           = 50u;
/// \input 	NvmBlockInstrumentatedFrames                        = FALSE;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unCurrent   = 0xFFFF;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 0xFFFF;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_24(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
    Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
    Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
    for (uint8 i = 0; i < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; i++)
    {
        Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[i] = 65534;

    }
   for (uint8 i = 0; i < 12u; i++)
    {
        Rte_Read_CtrlLed_TgtLedSig_sVal_Param1[i].unDutyCycle= 0xFFFF;
    }
    Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
    Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
    CPM_PARA_alTzTemp[1u][1u] = 50u;
    NvmBlockInstrumentatedFrames = FALSE;
    Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unCurrent = 0xFFFF;
    Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 0xFFFF;

    //Step 3) Call FUT
    Cpm_CodingValidCycle();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
}

//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle_TestCase_25
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input 	Rte_Read_RSens_ThermzoneTemperatures_HitCount       = 0u;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount            = 0u;
/// \input 	Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount             = 0u;
/// \input 	Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount      = 0u;
/// \input 	Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount        = 0u;
/// \input 	CPM_PARA_alTzTemp[1u][1u]                           = 50u;
/// \input 	NvmBlockInstrumentatedFrames                        = FALSE;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unCurrent   = 3000;
/// \input 	Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 40000;
///
///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_25(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockInstrumentatedFrames = TRUE;
  for (uint8 ucIdx = 0; ucIdx < 12; ucIdx++)
  {
    Rte_Read_RSens_ThermzoneTemperatures_Param1.s16_NTCTemperatureCelsius[ucIdx] = 0u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucIdx] = SIG_VALID;
    Rte_Read_CtrlLed_TgtHssSig_sVal_Param1.unDutyCycle = 32768u;
    Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unCurrent = 3000;
    Rte_Read_CtrlLed_TgtLedSig_sVal_Param1->unDutyCycle = 32768u;
    CPM_PARA_alTzTemp[0][ucIdx] = 100u;
    CPM_PARA_alTzTemp[1][ucIdx] = 100u;
    CPM_PARA_alTzTemp[2][ucIdx] = 100u;
    CPM_PARA_alTzTemp[3][ucIdx] = 100u;
    CPM_PARA_alTzTemp[4][ucIdx] = 100u;
    CPM_Gen_Param4.unDutyCycle[ucIdx] = 0x8000u;
  }
  for (uint8 ucIdx = 0; ucIdx < 103; ucIdx++)
  {
    Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucIdx] = 65534;
  }
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit1   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit2   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit3   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit4   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit5   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit6   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit7   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit8   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit9   = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit10  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit11  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit12  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit13  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit14  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit15  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit16  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit17  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit18  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit19  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit20  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit21  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit22  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit23  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit24  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit25  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit26  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit27  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit28  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit29  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit30  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit31  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit32  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit33  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit34  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit35  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit36  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit37  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit38  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit39  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit40  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit41  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit42  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit43  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit44  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit45  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit46  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit47  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit48  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit49  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit50  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit51  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit52  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit53  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit54  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit55  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit56  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit57  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit58  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit59  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit60  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit61  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit62  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit63  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit64  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit65  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit66  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit67  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit68  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit69  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit70  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit71  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit72  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit73  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit74  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit75  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit76  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit77  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit78  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit79  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit80  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit81  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit82  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit83  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit84  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit85  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit86  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit87  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit88  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit89  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit90  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit91  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit92  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit93  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit94  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit95  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit96  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit97  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit98  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit99  = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit100 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit101 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit102 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.ThermZone_Right_Unit103 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit1 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit2 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit3 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit4 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit5 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit6 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit7 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit8 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit9 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit10 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit11 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit12 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit13 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit14 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit15 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit16 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit17 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit18 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit19 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit20 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit21 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit22 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit23 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit24 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit25 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit26 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit27 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit28 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit29 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit30 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit31 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit32 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit33 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit34 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit35 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit36 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit37 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit38 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit39 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit40 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit41 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit42 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit43 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit44 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit45 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit46 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit47 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit48 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit49 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit50 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit51 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit52 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit53 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit54 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit55 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit56 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit57 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit58 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit59 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit60 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit61 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit62 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit63 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit64 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit65 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit66 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit67 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit68 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit69 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit70 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit71 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit72 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit73 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit74 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit75 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit76 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit77 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit78 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit79 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit80 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit81 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit82 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit83 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit84 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit85 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit86 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit87 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit88 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit89 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit90 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit91 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit92 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit93 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit94 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit95 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit96 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit97 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit98 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit99 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit100 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit101 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit102 = 4;
  Coding_Dummy.MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit103 = 4;
  CPM_Data_DriverMap_Param1 = eMountedRight;
  CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit60 = 2;

  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 2u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 2u, == );
}

///-----------------------------------------------------------------------------
/// \Test Case : Mt_Cpm_Cpm_CodingValidCycle_TestCase_26
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  cyclic function of Cpm which is only called when the coding is
///         valid. Calls the thermal model, fan, cmd and power management.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                 = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                      = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount                       = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                = 0u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCoun                   = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                     = 50u;
/// \input  CPM_PARA_aucTz2Temp[ucChIdx]                                 = 40u;
/// \input  Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
/// \input  NM_GetMode_Param1                                            = LIMP_HOME_MODE;
/// \input  Cpm_aboFanCtrl[0]                                            = 1u;
/// \input  Cpm_aboFanCtrl[1]                                            = 1u;
///
/// \input ///   - Expectations:
///
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount  = 1u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount       = 1u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount        = 1u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 1u;
/// \output Cpm_aboFanCtrl[0]                              = 1u;
/// \output Cpm_aboFanCtrl[1]                              = 1u;
///-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle_TestCase_26(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  NM_GetMode_Param1 = LIMP_HOME_MODE;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_INVALID;
  }
  Cpm_aboFanCtrl[0] = 0u;
  Cpm_aboFanCtrl[1] = 0U;
  //Step 3) Call FUT
  Cpm_CodingValidCycle();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_aboFanCtrl[0], 1u, == );
  AL_UNITTEST_CHECK(Cpm_aboFanCtrl[1], 1u, == );
}
//------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_CodingValidCycle
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_CodingValidCycle(void)
{
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_1();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_2();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_3();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_4();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_5();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_6();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_7();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_8();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_9();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_10();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_11();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_12();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_13();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_14();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_15();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_16();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_17();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_18();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_19();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_20();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_21();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_22();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_23();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_24();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_25();
  Mt_Cpm_Cpm_CodingValidCycle_TestCase_26();
  
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CPM_Data_DriverMap_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for maps the datas from mappinglist sheet for thermo
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input CPM_Data_DriverMap_Param1                                                           = eMountedRight;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit60 = 2;
///
///   - Expectations:
/// \output CPM_Data_DriverMap_RetVal = 43u;
//-----------------------------------------------------------------------------
void Mt_Cpm_CPM_Data_DriverMap_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedRight;
  CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit60 = 2;

  //Step 3) Call FUT
  CPM_Data_DriverMap_RetVal = CPM_Data_DriverMap(CPM_Data_DriverMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 43u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CPM_Data_DriverMap_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input CPM_Data_DriverMap_Param1                                                          = eMountedLeft;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7 = 2;
///
///   - Expectations:
/// \output	CPM_Data_DriverMap_RetVal = 246u
//-----------------------------------------------------------------------------
void Mt_Cpm_CPM_Data_DriverMap_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedLeft;
  CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7 = 2;

  //Step 3) Call FUT
  CPM_Data_DriverMap_RetVal = CPM_Data_DriverMap(CPM_Data_DriverMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 246u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CPM_Data_DriverMap_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input	 CPM_Data_DriverMap_Param1    = eMountedUndef;
///
///   - Expectations:
///
/// \output	CPM_Data_DriverMap_RetVal     = 0u
//-----------------------------------------------------------------------------
void Mt_Cpm_CPM_Data_DriverMap_TestCase_3(void)
{
  //Step 1) Set pre-conditions
//Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedUndef;

  //Step 3) Call FUT
  CPM_Data_DriverMap_RetVal = CPM_Data_DriverMap(CPM_Data_DriverMap_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );

}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CPM_Data_DriverMap
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///                     coding date.
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_CPM_Data_DriverMap(void)
{
  Mt_Cpm_CPM_Data_DriverMap_TestCase_1();
  Mt_Cpm_CPM_Data_DriverMap_TestCase_2();
  Mt_Cpm_CPM_Data_DriverMap_TestCase_3();
}


//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CpmThermo_SetPara_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
///
/// \input	 CPM_Data_DriverMap_Param1                                                      = eMountedUndef;
/// \input	 CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_RisingRateLimiter  = 10;
/// \input  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 2000;
///   - Expectations:
///
/// \output	CPM_Data_DriverMap_RetVal                                                      = 0u;
/// \output CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 208;
//-----------------------------------------------------------------------------
void  Mt_Cpm_CpmThermo_SetPara_TestCase_1(void)
{
  //Step 1) Set pre-conditions
 //Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedUndef;
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_RisingRateLimiter = 10;
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 2000;

  //Step 3) Call FUT
  CpmThermo_SetPara();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter, 208, == )
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CpmThermo_SetPara_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_RisingRateLimiter    = 230;
/// \input  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter   = 10;
/// \input  CPM_Data_DriverMap_Param1                                                        = eMountedRight;
/// \input  Rte_Read_IoHwAbUser_GetMountingSide_Param1                                       = eMountedRight;
///
///   - Expectations:
///
/// \output	CPM_Data_DriverMap_RetVal = 0u
//-----------------------------------------------------------------------------
void  Mt_Cpm_CpmThermo_SetPara_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_RisingRateLimiter = 230;
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 10;
  CPM_Data_DriverMap_Param1 = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.ThermZone_Left_Unit96 = 0;

  //Step 3) Call FUT
  CpmThermo_SetPara();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CpmThermo_SetPara_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input CPM_Data_DriverMap_Param1                                                             = eMountedRight;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                                            = eMountedRight;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7    = 2;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit24 = 3;
///
///   - Expectations:
///
/// \output	CPM_Data_DriverMap_RetVal = 0u
//-----------------------------------------------------------------------------
void  Mt_Cpm_CpmThermo_SetPara_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7 = 2;
  CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit24 = 3;

  //Step 3) Call FUT
  CpmThermo_SetPara();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CpmThermo_SetPara_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input CPM_Data_DriverMap_Param1                                                               = eMountedLeft;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                                              = eMountedLeft;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7      = 2;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit24  = 3;
///
///   - Expectations:
///
/// \output	CPM_Data_DriverMap_RetVal = 0u
//-----------------------------------------------------------------------------
void  Mt_Cpm_CpmThermo_SetPara_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedLeft;
  CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7 = 9;
  CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit24 = 3;
  CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit7 = 15;

  //Step 3) Call FUT
  CpmThermo_SetPara();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CpmThermo_SetPara_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:

/// \input CPM_Data_DriverMap_Param1                                                                 = eMountedUndef;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                                                = eMountedUndef;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7        = 2;
/// \input CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit24	   = 3;
///
///   - Expectations:
///
/// \output	CPM_Data_DriverMap_RetVal = 0u
//-----------------------------------------------------------------------------
void  Mt_Cpm_CpmThermo_SetPara_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  CPM_Data_DriverMap_Param1 = eMountedUndef;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedUndef;
  for (uint8 ucIdx = 0u; ucIdx < CPM_CFG_MAX_NO_OF_LOGICAL_UNIT; ucIdx++)
  {
    CPM_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7 = 2;
    CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit24 = 3;
    CPM_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit7 = 15;
  }

  //Step 3) Call FUT
  CpmThermo_SetPara();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );
}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_CpmThermo_SetPara
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///                     coding date.
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_CpmThermo_SetPara(void)
{
  Mt_Cpm_CpmThermo_SetPara_TestCase_1();
  Mt_Cpm_CpmThermo_SetPara_TestCase_2();
  Mt_Cpm_CpmThermo_SetPara_TestCase_3();
  Mt_Cpm_CpmThermo_SetPara_TestCase_4();
  Mt_Cpm_CpmThermo_SetPara_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_CodM_AppM_Para_HitCount                                               = 0u;
/// \input Rte_Read_CodM_AppM_Para_Param1.eCodingState                                    = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks                       = &Coding_Dummy;
/// \input CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 2000;
/// \input CPM_Data_DriverMap_Param1                                                      = eMountedLeft;
///
///   - Expectations:
///
/// \output	Rte_Read_CodM_AppM_Para_HitCount                                                = 1u ;
/// \output	CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter  = 208;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_Init_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_AppM_Para_HitCount = 0u;
  Rte_Read_CodM_AppM_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 2000;
  CPM_Data_DriverMap_Param1 = eMountedLeft;
 
  //Step 3) Call FUT
  Cpm_Init();

  //Step 4) Check expected output values
  for (uint8 ucIdx = 0u; ucIdx < CPM_FAN_NR; ucIdx++)
  {
    AL_UNITTEST_CHECK(Cpm_aboFanCtrl[ucIdx], 0u, == );
  }
  AL_UNITTEST_CHECK(Rte_Read_CodM_AppM_Para_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter, 208, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_CodM_AppM_Para_HitCount                                               = 0u;
/// \input Rte_Read_CodM_AppM_Para_Param1.eCodingState                                    = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks                       = &Coding_Dummy;
/// \input CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 2000;
/// \input CPM_Data_DriverMap_Param1                                                      = eMountedLeft;
///
///   - Expectations:
///
/// \output	Rte_Read_CodM_AppM_Para_HitCount                                                = 1u ;
/// \output	CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter  = 208;
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_Init_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_AppM_Para_HitCount = 0u;
  Rte_Read_CodM_AppM_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
  Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 2000;
  CPM_Data_DriverMap_Param1 = eMountedLeft;

  //Step 3) Call FUT
  Cpm_Init();

  //Step 4) Check expected output values
  for (uint8 ucIdx = 0u; ucIdx < CPM_FAN_NR; ucIdx++)
  {
    AL_UNITTEST_CHECK(Cpm_aboFanCtrl[ucIdx], 0u, == );
  }
  AL_UNITTEST_CHECK(Rte_Read_CodM_AppM_Para_HitCount, 1u, == );
  AL_UNITTEST_CHECK(CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter, 208, == );
}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for  initializing the RTE outputs, private variables and
///        coding date.
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_Init(void)
{
  Mt_Cpm_Cpm_Init_TestCase_1();
  Mt_Cpm_Cpm_Init_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_Cycle20ms_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function to  monitoring the internal and external
///         temperatures, the supply voltage and vehicle state to reduce the
///         duty cycle of the single channels, request the fan and CMD. Further
///         it evaluate the binning classes, the external takeover and applies
///         the values to the channels.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_SysMon_LifePhases_Param1.eSigQty                        = SIG_VALID;
/// \input Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                      = eNormalMode;
/// \input Rte_Read_SysMon_LifePhases_HitCount                              = 0u;
/// \input Cpm_Read_PhaseVie_RetVal                                         = 1u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_HitCount                    = 0u;
/// \input Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount                         = 0u;
/// \input Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCoun                           = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount                   = 0u;
/// \input Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1                     = 1u;
/// \input Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount                     = 0u;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_HitCount                          = 0u;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount                     = 0u;
/// \input CPM_PARA_alTzTemp[1u][1u]                                        = 50u;
/// \input Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty                    = SIG_VALID;
/// \input Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal                   = eEtatFeuxStationnement_LeftSide;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1                       = eMountedRight;
/// \input Rte_Read_IoHwAbUser_GetMountingSide_RetVal                       = eMountedUndef;
/// \input Rte_Read_RSens_PcbTemperature_HitCount                           = 0u;
/// \input CPM_PARA_aucTz2Temp[ucChIdx]                                     = 10u;
/// \input Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx]     = SIG_VALID;
///
///   - Expectations:
/// \output Rte_Read_RSens_ThermzoneTemperatures_HitCount       = 0u;
/// \output Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount            = 0u;
/// \output Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount             = 0u;
/// \output Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount      = 0u;
/// \output Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal      = eEtatFeuxStationnement_LeftSide;
/// \output Rte_Read_SysMon_LifePhases_HitCount                 = 1u;
/// \output Cpm_Read_PhaseVie_RetVal                            = eNormalMode;
//---------------------------------------------------------------------------------------------
void Mt_Cpm_Cpm_Cycle20ms_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode;
  Rte_Read_SysMon_LifePhases_HitCount = 0u;
  Cpm_Read_PhaseVie_RetVal = 1u;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1 = 1u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount = 0u;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount = 0u;
  CPM_PARA_alTzTemp[1u][1u] = 50u;
  Rte_Read_SysMon_StdLgtFcts_Req_Param1.eSigQty = SIG_VALID;
  Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal = eEtatFeuxStationnement_LeftSide;
  Rte_Read_IoHwAbUser_GetMountingSide_Param1 = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_RetVal = eMountedUndef;
  Rte_Read_RSens_PcbTemperature_HitCount = 0u;

  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 10u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_VALID;
    Rte_Read_CtrlLed_Cpm_TgtPxlSig_Param1.unPxl_Int[ucChIdx] = 65536;

  }

  //Step 3) Call FUT
  Cpm_Cycle20ms();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 0u, == );

  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT_RetVal, eEtatFeuxStationnement_LeftSide, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_Read_PhaseVie_RetVal, eNormalMode, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_Cycle20ms_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function to  monitoring the internal and external
///         temperatures, the supply voltage and vehicle state to reduce the
///         duty cycle of the single channels, request the fan and CMD. Further
///         it evaluate the binning classes, the external takeover and applies
///         the values to the channels.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input	 Rte_Read_SysMon_LifePhases_Param1.eSigQty    = SIG_VALID;
/// \input	 Rte_Read_SysMon_LifePhases_Param1.ePhaseVie  = eNormalMode;
/// \input	 Rte_Read_SysMon_LifePhases_HitCount          = 0u;
/// \input	 Cpm_Read_PhaseVie_RetVal                     = 1u;
/// \input	 Cpm_boCodingValid                            = FALSE;
///
///   - Expectations:
/// \output Cpm_Read_PhaseVie_RetVal                     = eNormalMode;
//---------------------------------------------------------------------------------------------
void Mt_Cpm_Cpm_Cycle20ms_TestCase_2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode;
  Rte_Read_SysMon_LifePhases_HitCount = 0u;
  Cpm_Read_PhaseVie_RetVal = 1u;

  //Step 3) Call FUT
  Cpm_Cycle20ms();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Cpm_Read_PhaseVie_RetVal, eNormalMode, == );
}

// ------------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_Cpm_Cycle20ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function to  monitoring the internal and external
///         temperatures, the supply voltage and vehicle state to reduce the
///         duty cycle of the single channels, request the fan and CMD. Further
///         it evaluate the binning classes, the external takeover and applies
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Cpm_Cpm_Cycle20ms(void)
{
  Mt_Cpm_Cpm_Cycle20ms_TestCase_1();
  Mt_Cpm_Cpm_Cycle20ms_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_riCpmInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function to initialisation runnable for Cpm
///        Calling once at start up.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input Rte_Read_CodM_AppM_Para_HitCount                                                = 0u;
/// \input Rte_Read_CodM_AppM_Para_Param1.eCodingState                                     = eParaFct0_CodingDataValid;
/// \input Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks                        = &Coding_Dummy;
/// \input CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter  = 0;
/// \input CPM_Data_DriverMap_Param1                                                       = eMountedLeft;
/// \input Cpm_ParaFct0_Param1                                                              = eParaFct0_CodingDataValid;
/// \input Cpm_ParaFct0_Param2                                                              = 1u;
///
///   - Expectations:
/// \output Cpm_aboFanCtrl[ucIdx]                  = 0u
/// \output CPM_Data_DriverMap_RetVal              = 0u
/// \output Rte_Read_CodM_AppM_Para_HitCount       = 1u
//---------------------------------------------------------------------------------------------
void Mt_Cpm_riCpmInit(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_AppM_Para_HitCount = 0u;
  Rte_Read_CodM_AppM_Para_Param1.eCodingState = eParaFct0_CodingDataValid;
  Rte_Read_CodM_AppM_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  CPM_pCodingArea->Thermo1.Thermzones_PowRateLimiter.ucPowFct_FallingRateLimiter = 0;
  CPM_Data_DriverMap_Param1 = eMountedLeft;
  Cpm_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  Cpm_ParaFct0_Param2 = 1u;
 
  //Step 3) Call FUT
  riCpmInit();

  //Step 4) Check expected output values
  for (uint8 ucIdx = 0u; ucIdx < CPM_FAN_NR; ucIdx++)
  {
    AL_UNITTEST_CHECK(Cpm_aboFanCtrl[ucIdx], 0u, == );
  }
  AL_UNITTEST_CHECK(CPM_Data_DriverMap_RetVal, 0u, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_AppM_Para_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Cpm_rpCpm20ms
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function to set the configuration parameter for every input parameter 
///                      for the generic alghoritm for CPM and Fan
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign Input values
///         Step3: Call FUT
///         Step4: Check expected output values
///
/// - Preconditions:
/// \input	 Rte_Read_RSens_ThermzoneTemperatures_HitCount      = 0u;
/// \input	 Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount           = 0u;
/// \input	 Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount            = 0u;
/// \input	 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount     = 0u;
/// \input	 Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount       = 0u;
/// \input	 Rte_Read_SysMon_LifePhases_Param1.eSigQty          = SIG_VALID;
/// \input	 Rte_Read_SysMon_LifePhases_Param1.ePhaseVie        = eNormalMode;
/// \input	 Rte_Read_SysMon_LifePhases_HitCount                = 0u;
/// \input	 Cpm_Read_PhaseVie_RetVal                           = 1u;
/// \input	 Cpm_boCodingValid                                  = TRUE;
///
///   - Expectations:
/// \output  Rte_Read_SysMon_LifePhases_HitCount           = 1u;
/// \output  Cpm_Read_PhaseVie_RetVal                      = eNormalMode;
/// \output  Rte_Read_RSens_ThermzoneTemperatures_HitCount =  1u;
/// \output  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount      =  1u;
/// \output  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount       =  1u;
/// \output  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount=  1u;
//---------------------------------------------------------------------------------------------
void Mt_Cpm_rpCpm20ms(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_RSens_ThermzoneTemperatures_HitCount = 0u;
  Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount = 0u;
  Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount = 0u;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount = 0u;
  Rte_Write_Cpm_SigPrepTx_PowerFactor_HitCount = 0u;
  Rte_Read_SysMon_LifePhases_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie = eNormalMode;
  Rte_Read_SysMon_LifePhases_HitCount = 0u;
  Cpm_Read_PhaseVie_RetVal = 1u;
  for (uint8_fast ucChIdx = 0u; ucChIdx < (uint8)CPM_CFG_LED_MAX_NO_OF_LS_CHANNELS; ucChIdx++)
  {
    CPM_PARA_aucTz2Temp[ucChIdx] = 40u;
    Rte_Read_RSens_ThermzoneTemperatures_Param1.eSigQty[ucChIdx] = SIG_DISABLED;
  }

  //Step 3) Call FUT
  rpCpm20ms();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Cpm_Read_PhaseVie_RetVal, eNormalMode, == );
  AL_UNITTEST_CHECK(Rte_Read_RSens_ThermzoneTemperatures_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_TgtLedSig_sVal_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlLed_Cpm_TgtPxlSig_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount, 1u, == );
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
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_RteAccess_Read_Vbat",                 Mt_Cpm_Cpm_RteAccess_Read_Vbat);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_ParaFct0",                            Mt_Cpm_Cpm_ParaFct0);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_MapParams",                           Mt_Cpm_Cpm_MapParams);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_Read_PhaseVie",                       Mt_Cpm_Cpm_Read_PhaseVie);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_RteAccess_Get_ECU_Side",              Mt_Cpm_Cpm_RteAccess_Get_ECU_Side);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT", Mt_Cpm_Cpm_RteAccess_Get_ETAT_FEUX_STATIONMENT);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_RteAccess_Write_PwFact_Temp",         Mt_Cpm_Cpm_RteAccess_Write_PwFact_Temp);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_Init",                                Mt_Cpm_Cpm_Init);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_CodingValidCycle",                    Mt_Cpm_Cpm_CodingValidCycle);
  ALUnitTest_AddFunction("Mt_Cpm_CPM_Data_DriverMap",                      Mt_Cpm_CPM_Data_DriverMap);
  ALUnitTest_AddFunction("Mt_Cpm_CpmThermo_SetPara",                       Mt_Cpm_CpmThermo_SetPara);
  ALUnitTest_AddFunction("Mt_Cpm_Cpm_Cycle20ms",                           Mt_Cpm_Cpm_Cycle20ms);
  ALUnitTest_AddFunction("Mt_Cpm_riCpmInit",                               Mt_Cpm_riCpmInit);
  ALUnitTest_AddFunction("Mt_Cpm_rpCpm20ms",                               Mt_Cpm_rpCpm20ms);
}

// EOF
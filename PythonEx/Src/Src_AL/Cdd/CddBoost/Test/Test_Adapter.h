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
/// \file  Test_Adapter.h
///
/// \brief Additional test cases for adapter
//         These test must be customized according to the adapter implementation
///
//-----------------------------------------------------------------------------
#ifndef TEST_ADAPTER_2022_01_21_H_
#define TEST_ADAPTER_2022_01_21_H_


//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <RteCommonTypes.h>

// Headers of the Module
#include <CddBoost.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================
extern  tCddBoostStatus       CddBoost_sStatus;
extern  tNvmPara_CodingArea*  CddBoost_pCodingArea;
extern  boolean               CddBoost_boCodingValidity;
extern  boolean               CddBoost_boParaInit;

extern  tCddBoostTarget       CddBoost_sTarget;
extern  uint16                CddBoost_unV_Boost;

//=============================================================================
// Module function declarations
//=============================================================================
extern void     riCddBoostInit(void);
extern void     reCddBoostNewTarget(void);
extern void     rpCddBoost_Cycle(void);
extern void     CddBoost_GetStatus(tCddBoostStatus* pStatus);
extern boolean  CddBoost_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern boolean  CddBoost_CodingDataValidation(void);
extern void     CddBoost_CalcTgtBoostVolt(boolean boValid);

//=============================================================================
// Adapter unit test suit function declaration
//=============================================================================
void ALUnitTest_AddTests_Adapter(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

//=============================================================================
// Module function return value stubs
//=============================================================================

//=============================================================================
// Module static variables inside functions 
//=============================================================================



#endif // TEST_ADAPTER_2022_01_21_H_

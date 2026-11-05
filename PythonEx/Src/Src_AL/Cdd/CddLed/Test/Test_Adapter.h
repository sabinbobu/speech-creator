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
///         These test must be customized according to the adapter implementation
///
//-----------------------------------------------------------------------------
#ifndef TEST_ADAPTER_2021_08_23_H_
#define TEST_ADAPTER_2021_08_23_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <RteCommonTypes.h>

// Headers of the Module
#include <CddLed.h>
#include <CddLed_Adapter.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================
extern tCddLedStatus CddLed_sStatus;
extern boolean       CddLed_ParaInit;

//=============================================================================
// Module function declarations
//=============================================================================
extern void     riCddLedInit(void);
extern void     rpCddLed_Cycle(void);
extern boolean  reCddLedNewTarget(void);
extern boolean  CddLed_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
extern boolean  CddLed_CodingDataValidation(void);
extern void     CddLed_Rte_SendLedState(tCddLedStatus sStatus);
extern void     CddLed_Get_CodingPara(tsCddLed_CodingParam *sCodingParam);

//=============================================================================
// Adapter unit test suit function declaration
//=============================================================================
void ALUnitTest_AddTests_Adapter(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
tParaFct0_Cmd         CddLed_ParaFct0_Param1;
tNvmPara_CodingArea*  CddLed_ParaFct0_Param2;
tCddLedStatus         CddLed_Rte_SendLedState_Param1;
tsCddLed_CodingParam  CddLed_Get_CodingPara_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
boolean     CddLed_ParaFct0_RetVal;
boolean     CddLed_CodingDataValidation_RetVal;
boolean     reCddLedNewTarget_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================
boolean boCrcFailure;
TIMER   ulCrcTimer;
tsRte_TgtLedSig0_ASIL sASIL_Target_ASIL;

//=============================================================================
// Global stubs variables
//=============================================================================
extern tNvmPara_CodingArea     Coding_Dummy;
extern tParaFct0_Cmd           Coding_State;


#endif // TEST_ADAPTER_2021_08_23_H_

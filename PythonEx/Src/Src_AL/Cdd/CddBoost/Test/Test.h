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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

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
extern tCddBoostTarget CddBoost_sTarget;
extern uint32          CddBoost_ulAvailMask;
extern boolean         CddBoost_boIsRunning;
extern boolean         CddBoost_boParaValid;

//=============================================================================
// Module function declarations
//=============================================================================
extern void   CddBoost_Init(void);
extern void   CddBoost_SetPara(boolean boValid);
extern void   CddBoost_Cycle20ms(void);
extern void   CddBoost_SetTarget(tCddBoostTarget* pTarget);
extern void   CddBoost_GetStatus(tCddBoostStatus* pStatus);
extern void   CddBoost_Shutdown(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
tCddBoostTarget CddBoost_SetTarget_Param1;
tCddBoostStatus CddBoost_GetStatus_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_

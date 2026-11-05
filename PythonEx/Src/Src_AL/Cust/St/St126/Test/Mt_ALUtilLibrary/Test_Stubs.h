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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <UtilDebounce.h>
#include <UtilMath.h>
#include <UtilBase.h>
#include <Fee.h>

//=============================================================================
// Stub function declarations
//=============================================================================
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
uint16 ShiftValue(volatile uint16 unArg);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint32         LPTMR0_GetTimeElapsed_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint32         LPTMR0_GetTimeElapsed_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint32 LPTMR0_GetTimeElapsed_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

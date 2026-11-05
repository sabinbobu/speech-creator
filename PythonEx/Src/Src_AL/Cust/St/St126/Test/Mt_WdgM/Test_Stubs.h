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
#include <stdio.h>
#include <AL_Helper.h>
#include <Std_Types.h>

//=============================================================================
// Stub function declarations
//=============================================================================
void  CddSbc_SetWdgWindowModeAnd200ms(void);
void  Lpit_ClearInterruptFlag(uint8 ucTimerInst, uint8 ucTimerCh);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint8 Lpit_ClearInterruptFlag_Param1;
extern uint8 Lpit_ClearInterruptFlag_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================


//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 CddSbc_SetWdgWindowModeAnd200ms_HitCount;
extern uint8 Lpit_ClearInterruptFlag_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

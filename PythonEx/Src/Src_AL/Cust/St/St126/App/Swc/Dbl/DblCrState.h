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
/// \file  DblCrState.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef DBL_CR_STATE_2023_09_18_H_
#define DBL_CR_STATE_2023_09_18_H_

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>

//-----------------------------------------------------------------------------
//  Data type definitions
//-----------------------------------------------------------------------------
typedef struct
{
  //input
  boolean boReq_Input;
  TIMER   ulTimeMs_Input;
  //internal
  TIMER   ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsDblCrState_TimerCfg;

//=============================================================================
// function prototypes
//=============================================================================
void DblCrState_Init(void);
sint32 DblCrState_State_Machine(void);


#endif // DBL_CR_STATE_2023_09_18_H_

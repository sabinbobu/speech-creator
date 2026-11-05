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

#include <Fee.h>

//=============================================================================
// Stub function declarations
//=============================================================================

uint32  LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
boolean roDiag_IntegrationMode(void);
void    roDiag_Callbacks_ProgramingSessionAccepted(void);
void    roDiag_Callbacks_NRC_Response(uint8 ucCode);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tieFeeState          Fee_State;
extern MemIf_JobResultType  Fee_JobResult;
extern uint32               LPTMR0_GetTimeElapsed_Param1;
extern uint8                roDiag_Callbacks_NRC_Response_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint32   LPTMR0_GetTimeElapsed_RetVal;
extern boolean  roDiag_IntegrationMode_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8  LPTMR0_GetTimeElapsed_HitCount;
extern uint8  roDiag_IntegrationMode_HitCount;
extern uint8  roDiag_Callbacks_ProgramingSessionAccepted_HitCount;
extern uint8  roDiag_Callbacks_NRC_Response_HitCount;


#endif // TEST_STUBS_2023_08_25_H_

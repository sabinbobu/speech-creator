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
#include <CddMlc_Cod.h>
#include <CddTpsGen2_Types.h>
//=============================================================================
// Typedef
//=============================================================================


//=============================================================================
// Stub function declarations
//=============================================================================
extern boolean CddMlc_IsMlcPowered(void);
extern tsCddMlc_CodingData* CddMlc_pfGetCodingData(void);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

//=============================================================================
// Stub function returned value stubs
//=============================================================================
boolean CddMlc_IsMlcPowered_RetVal;
tsCddMlc_CodingData CddMlc_pfGetCodingData_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 CddMlc_IsMlcPowered_HitCount;
uint8 CddMlc_pfGetCodingData_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

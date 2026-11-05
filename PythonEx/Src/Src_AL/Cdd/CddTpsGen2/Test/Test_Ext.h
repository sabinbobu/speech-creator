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
/// \file  Test_Ext.h
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2021_08_13_H_
#define TEST_EXT_2021_08_13_H_

#include <Std_Types.h>
#include <CddTpsGen2_Cod.h>

#define CDDTPSGEN2_Para_Get_CHIP_ID(ucIdx)   TestExt_Get_Chip_Id(ucIdx)

//=============================================================================
// Stub function declarations
//=============================================================================
uint8 TestExt_Get_Chip_Id(uint8 ucIdx);
void  TestExt_RestoreStubContents(void);
void  TestExt_ActionSuccessClbk(void);
void  TestExt_ActionFailedClbk(void);
//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint8 TestExt_Get_Chip_Id_RetVal[CDDTPSGEN2_MAX_CHIPs];

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 TestExt_Get_Chip_Id_HitCount;
uint8 TestExt_ActionSuccessClbk_HitCount;
uint8 TestExt_ActionFailedClbk_HitCount;

#endif // TEST_EXT_2021_08_13_H_

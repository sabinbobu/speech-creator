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
/// \file  Test_Ext.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <CddTpsGen2_Cod.h>
#include <../Cfg/CddTpsGen2_Cfg.h>
#include <string.h>


//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
uint8 aucUartMsg_Backup[CDDTPSGEN2_MAX_CMD_LENGTH];
uint8 aucUartMsg_Used[CDDTPSGEN2_MAX_CMD_LENGTH];

//-----------------------------------------------------------------------------
// Stub functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \brief TestExt_Get_Chip_Id
///
/// \descr Stub function for TestExt_Get_Chip_Id
///
/// \param  uint8
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 TestExt_Get_Chip_Id(uint8 ucIdx)
{
  TestExt_Get_Chip_Id_HitCount++;
  return TestExt_Get_Chip_Id_RetVal[ucIdx];
}
//-----------------------------------------------------------------------------
/// \brief RestoreStubContents
///
/// \descr Function used in unit test for reseting aucUartMsg_Used struct 
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void TestExt_RestoreStubContents(void)
{
  memcpy(aucUartMsg_Used, aucUartMsg_Backup, sizeof(aucUartMsg_Used));
}

//-----------------------------------------------------------------------------
/// \brief TestExt_ActionSuccessClbk
///
/// \descr Stub function for TestExt_ActionSuccessClbk
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void TestExt_ActionSuccessClbk(void)
{
  TestExt_ActionSuccessClbk_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief TestExt_ActionFailedClbk
///
/// \descr Stub function for TestExt_ActionFailedClbk
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void TestExt_ActionFailedClbk(void)
{
  TestExt_ActionFailedClbk_HitCount++;
}




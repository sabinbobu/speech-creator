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
/// \file  RSensRteAccess.c
///
/// \brief Rte wrapper for RSens module
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "RSensRteAccess.h"
#include <RSens.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//lint +e451 Header file repeatedly included but does not have a standard include guard
#include <Cfg/Cfg.h>
#include <CodM_Para_Led.h>
#include <IoHwAbUser.h>

//=============================================================================
// variables
//=============================================================================

// Array of function pointers to write NTCs temperature value in celsius
STATIC_AL Std_ReturnType(*RSens_RteAccess_apfnWriteBinningClasses_List[RSENS_LED_BINNING_CLASSES]) (const tsRte_Binning0* psBinClass) =
{
  Rte_Write_RSens_BinningClass_sVal_00,
  Rte_Write_RSens_BinningClass_sVal_01,
  Rte_Write_RSens_BinningClass_sVal_02,
  Rte_Write_RSens_BinningClass_sVal_03,
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)
  Rte_Write_RSens_BinningClass_sVal_04,
  Rte_Write_RSens_BinningClass_sVal_05,
  Rte_Write_RSens_BinningClass_sVal_06,
  Rte_Write_RSens_BinningClass_sVal_07,
  Rte_Write_RSens_BinningClass_sVal_08,
  Rte_Write_RSens_BinningClass_sVal_09,
  Rte_Write_RSens_BinningClass_sVal_10,
  Rte_Write_RSens_BinningClass_sVal_11,
#endif
};

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  RSens_RteAccess_Write_BinnigClasses
///
/// \descr  Write actual binning classes for each led channel (protected port)
///
/// \param  ucIdx      - led channel index
///         sActBinSig - pointer to the data structure with actual binning value
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType RSens_RteAccess_Write_BinnigClasses(uint8 ucIdx, tsRte_Binning0* sActBinSig)
{
  Std_ReturnType ucReturnVal;

  ucReturnVal = RSens_RteAccess_apfnWriteBinningClasses_List[ucIdx](sActBinSig);

  return ucReturnVal;
}

uint16 RSens_Rte_Read_ExtNTC(const uint32 ulIx)
{
  //uint16 unVoltage = IoHwAbUser_GetVoltage_NTCs((uint8)ulIx);  // LDMO-2121 IoHwAb_GetVoltage_NTCs RTE port added instead of direct function call

  tsRte_Voltage_mV stData;
  uint16 unVoltage;

  if (ulIx < UTIL_COUNTOF(stData.aunNtcVoltage))
  {
    (void)Rte_Read_IoHwAb_GetVoltage_NTCs(&stData);
    unVoltage = (uint16)stData.aunNtcVoltage[ulIx];
  }
  else
  {
    unVoltage = 0xFFFFU;
  }

  return  unVoltage;
}

void RSens_Rte_Read_PCBNTC(uint16* const ucData)
{ 
  uint16 unPcbVoltage;

  (void)Rte_Read_IoHwAb_GetPCB(&unPcbVoltage);

  *ucData = unPcbVoltage;

}


// EOF

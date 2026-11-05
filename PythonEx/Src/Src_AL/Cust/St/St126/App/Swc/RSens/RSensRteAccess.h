#ifndef __RSENS_RTE_ACCESS_H__
#define __RSENS_RTE_ACCESS_H__

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
/// \file  RSensRteAccess.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Sergej Immel  (F55102A)
///         mailTo:sergej.immel@al-lighting.com
//-----------------------------------------------------------------------------

#include <Cfg/Cfg.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
#ifndef UNIT_TEST
#include <Rte.h>
#endif
//lint +e451 Header file repeatedly included but does not have a standard include guard
#include <AL_Helper.h>
#include <Std_Types.h>
#include <IoHwAbUser.h>
#include <UtilMath.h>

STATIC_AL ORDER1_Filter                 IoHwAbUser_tPCB_Filter;

//=============================================================================
// function prototypes
//=============================================================================
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_00(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_01(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_02(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_03(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_04(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_05(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_06(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_07(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_08(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_09(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_10(const tsRte_Binning0* ppara1);
Std_ReturnType Rte_Write_RSens_BinningClass_sVal_11(const tsRte_Binning0* ppara1);

Std_ReturnType RSens_RteAccess_Write_BinnigClasses(uint8 ucIdx, tsRte_Binning0* sActBinSig);
uint16 RSens_Rte_Read_ExtNTC(const uint32 ulIx);
void RSens_Rte_Read_PCBNTC(uint16* const ucData);

//=============================================================================
// inline functions
//=============================================================================

//write

// write RSens_acRteIdx_PcbTemperature
LOCAL_INLINE Std_ReturnType RSens_Rte_Write_PcbTemperature(const tsRte_PcbTemperatureMsg *pdata)
{
  return Rte_Write_RSens_PcbTemperature((const void*)pdata);
}

// send ALEC status to Dem
LOCAL_INLINE void RSens_SetALEC(uint16 ErrTmrEnum, boolean boSetError)
{
  Rte_Call_DemPrj_ReportErrorStatus(ErrTmrEnum, boSetError);
}

// read IoHwAb_User_GetAdc_VoltNtcExt
//LOCAL_INLINE uint16 RSens_Rte_Read_ExtNTC(const uint32 ulIx)
//{
//   return IoHwAb_User_Read_PCBTemperature();
//}

// read IoHwAb_User_GetAdc_VoltNtcPcb
LOCAL_INLINE uint16 RSens_Rte_Read_PcbNTC(void)
{
  //return Rte_Call_IoHwAb_User_GetAdc_VoltNtcPcb();
  return E_OK;
}

// read IoHwAb_User_GetAdc_VoltBin
LOCAL_INLINE uint16 RSens_Rte_Read_Bin(const uint32 ulIx)
{
  //return Rte_Call_IoHwAb_User_GetAdc_VoltBin(ulIx);
  return E_OK;
}

// read from RSens
LOCAL_INLINE Std_ReturnType RSens_Rte_Read_PcbTemperature(const tsRte_PcbTemperatureMsg *pdata)
{
  //return Rte_Read_RSens_PcbTemperature((void*)pdata);
  return E_OK;
}
#endif // __RSENS_RTE_ACCESS_H__

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
/// \file  CddBoost_RoutCfg.h
///
/// \brief
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_BOOST_ROUT_CFG_2021_07_01_H_
#define CDD_BOOST_ROUT_CFG_2021_07_01_H_

//-----------------------------------------------------------------------------
// Imcludes
//-----------------------------------------------------------------------------


#ifdef UNIT_TEST

#include <Test_Ext.h>

#else
#include <Swc/CodM/CodM.h>
#include <CddNcv78702.h>
#include <Rte.h>

//-----------------------------------------------------------------------------
// Typedef
//-----------------------------------------------------------------------------
extern CONST_AL tNvmPara_CodingArea*  CddBoost_pCodingArea;


//-----------------------------------------------------------------------------
// Access to chip specific implementation
//-----------------------------------------------------------------------------
#define CDDBOOST_Drv_Init()                            CddNcv78702_Init()
#define CDDBOOST_Drv_Shutdown()                        CddNcv78702_Shutdown()
#define CDDBOOST_Drv_SetBoosterVoltage(Idx,VBoost_mV)  CddNcv78702_SetBoosterVoltage(Idx, VBoost_mV)

#define CDDBOOST_Drv_IsReset(Idx)                      CddNcv78702_IsReset(Idx)
#define CDDBOOST_Drv_IsSpiError(Idx)                   CddNcv78702_IsSpiError(Idx)
#define CDDBOOST_Drv_IsThermalShutDown(Idx)            CddNcv78702_IsThermalShutDown(Idx)
#define CDDBOOST_Drv_IsThermalWarning(Idx)             CddNcv78702_IsThermalWarning(Idx)

//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDBOOST_GetECUSupply(pVolt)                 (void)Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(pVolt)

//-----------------------------------------------------------------------------
// Parameter access
//-----------------------------------------------------------------------------
#define CDDBOOST_Para_LED_VBAT_MIN_ON_V               (100u * (uint32)CddBoost_pCodingArea->Led1.LedSupplyVoltage.LED_SUPPLY_MIN_ON_V)           // [0.1V]-->[mV]
#define CDDBOOST_Para_BOOST_VOLT_HEADROOM             (100u * (uint32)CddBoost_pCodingArea->Led1.LedBoostConverter.ucBOOST_VOLT_HEADROOM)        // [0.1V]-->[mV]
#define CDDBOOST_Para_BOOST_VOLT_ERROR_THRESHOLD      (100u * (uint32)CddBoost_pCodingArea->Led1.LedBoostConverter.ucBOOST_VOLT_ERROR_THRESHOLD) // [0.1V]-->[mV]
#define CDDBOOST_Para_FUSA_DRV_LED_OVER_VOLTAGE(x)    (200u * (uint32)CddBoost_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_LED_OVER_VOLTAGE[x])      // [0.2V]-->[mV]

#endif //UNIT TEST

#endif // CDD_BOOST_ROUT_CFG_2021_07_01_H_

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
/// \file  CddLed_RoutCfg.h
///
/// \brief
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_LED_ROUT_CFG_2021_07_01_H_
#define CDD_LED_ROUT_CFG_2021_07_01_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#ifdef UNIT_TEST

#include <Test_Ext.h>

#else

#include <CddTps92520.h>
#include <Swc/CodM/CodM.h>
#include <IoHwAbUser.h>
#include <Rte/Rte.h>

//-----------------------------------------------------------------------------
// Typedef
//-----------------------------------------------------------------------------
extern CONST_AL tNvmPara_CodingArea*  CddLed_pCodingArea;


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDLED_GetECUSupply(pVolt)                Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(pVolt)



//-----------------------------------------------------------------------------
// Access to chip specific implementation
//-----------------------------------------------------------------------------
#define CDDLED_Drv_Init()                    CddTps92520_Init()
#define CDDLED_Drv_Cycle20ms()               CddTps92520_Cycle20ms()

#define CDDLED_Drv_SetCurrent(Idx,Current)   CddTps92520_SetCurrent_mA       (Idx, Current);
#define CDDLED_Drv_SetDutyCycle(Idx,Duty)    CddTps92520_SetDutyCycle_1_32768(Idx, Duty);

#define CDDLED_Drv_GetCurrent_mA(Idx)        CddTps92520_GetCurrent_mA        (Idx)
#define CDDLED_Drv_GetDutyCycle_1_32768(Idx) CddTps92520_GetDutyCycle_1_32768 (Idx)

#define CDDLED_Drv_GetInputVoltage_mV(Idx)   CddTps92520_GetInputVoltage_mV(Idx)
#define CDDLED_Drv_GetLedVoltage_mV(Idx,Ptr) CddTps92520_GetLedVoltage_mV  (Idx, Ptr)

#define CDDLED_Drv_IsDriverActive(Idx)       CddTps92520_IsDriverActive   (Idx)
#define CDDLED_Drv_IsShortToGnd(Idx)         CddTps92520_IsShortToGnd     (Idx)
#define CDDLED_Drv_IsOpenLoad(Idx)           CddTps92520_IsOpenLoad       (Idx)
#define CDDLED_Drv_IsOvercurrent(Idx)        CddTps92520_IsOvercurrent    (Idx)
#define CDDLED_Drv_IsThermalShutDown(Idx)    CddTps92520_IsThermalShutDown(Idx)
#define CDDLED_Drv_IsThermalWarning(Idx)     CddTps92520_IsThermalWarning (Idx)
#define CDDLED_Drv_IsSpiError(Idx)           CddTps92520_IsSpiError       (Idx)




//-----------------------------------------------------------------------------
// Parameter access
//-----------------------------------------------------------------------------
#define CDDLED_Para_BOOST_VOLT_HEADROOM           (100u * (uint32)CddLed_pCodingArea->Led1.LedBoostConverter.ucBOOST_VOLT_HEADROOM)        // [0.1V]-->[mV]
#define CDDLED_Para_BOOST_VOLT_ERROR_THRESHOLD    (100u * (uint32)CddLed_pCodingArea->Led1.LedBoostConverter.ucBOOST_VOLT_ERROR_THRESHOLD) // [0.1V]-->[mV]
#define CDDLED_Para_FUSA_DRV_LED_UNDER_VOLTAGE(x) (200u * (uint32)CddLed_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_LED_UNDER_VOLTAGE[x])     // [0.2V]-->[mV]
#define CDDLED_Para_FUSA_DRV_LED_OVER_VOLTAGE(x)  (200u * (uint32)CddLed_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_LED_OVER_VOLTAGE[x])      // [0.2V]-->[mV]
#define CDDLED_Para_LED_SHORT_UBAT_RANGE                          CddLed_pCodingArea->Led1.LedErrDetect.LED_SHORT_UBAT_RANGE             // [%]
#define CDDLED_Para_LED_OVERCURRENT_DEBOUNCE                      CddLed_pCodingArea->Led1.LedErrDetect.LED_OVERCURRENT_DEBOUNCE         // [20ms]

#endif //UNIT TEST

#endif // CDD_LED_ROUT_CFG_2021_07_01_H_

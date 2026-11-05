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
/// \file   CtrlLed_Rte.h
///
/// \brief  header file for RTE access
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_LED_RTE_2021_03_30_H_
#define CTRL_LED_RTE_2021_03_30_H_
//=============================================================================
// includes
//=============================================================================
#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <RteCommonTypes.h>
#endif
#include "CtrlLed_Types.h"

//=============================================================================
// Prototypes
//=============================================================================
uint16 CtrlLed_RteAccess_Read_Vbat(void);
uint8 CtrlLed_RteAccess_Get_ECU_Side(void);
uint8 CtrlLed_Rte_Get_BinningClass(uint8_fast ucIdx);
void CtrlLed_RteAccess_Get_CodingPara(tsCtrlLed_CodingParam *sCodingParam);
void CtrlLed_RteAccess_Set_ChannelSettings(tsCtrlLed_ChannelSettings* psChannelSettings);
void CtrlLed_RteAccess_Get_ChannelState(uint8_fast ucIdx, tsCtrlLed_aChannelState *psChannelState);
void CtrlLed_RteAccess_Set_IlluminantsStatus(uint8_fast ucIdxIl, uint16 unIlluminantState, boolean boIlluminantStatus, uint8 ucChFctName);
void CtrlLed_RteAccess_Set_ChanelLedStatus(uint8_fast ucIdx, boolean boChanelLedState);
void CtrlLed_RteAccess_Set_Channel_Fbit(uint8_fast ucIdx, boolean boFbit);
void CtrlLed_RteAccess_Get_HSS3_Status(uint8 *pucDataErr, boolean *pboEnabled);
void CtrlLed_RteAccess_Set_HSS3_Duty(uint16 unDuty);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
uint8 CtrlLed_RteAccess_VoltageRange(void);
void CtrlLed_RteAccess_Get_MatrixLuErrors(uint8 ucLu, tuCtrlLed_bErr *puStatus);
void CtrlLed_RteAccess_Get_MatrixVccxErrors(boolean *pboVccxGnd, boolean *pboVccxBat);
void CtrlLed_RteAccess_Get_MatrixSystemMode(boolean *pboData);
boolean CtrlLed_RteAccess_Get_DD01_Diag_Status(void);
void CtrlLed_RteAccess_Get_Diag_Pixel_Intensity(uint8 *pucData);
#endif
//=============================================================================
// defines
//=============================================================================

//---------------------------------------sender---------------------------------------
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  #define CTRLLED_RTE_SE_TGT_PXL_PWM(pTarget)                   (void)Rte_Write_CtrlLed_Cpm_TgtPxlSig(pTarget); //to Cpm
#endif
#define CTRLLED_RTE_SE_TGT_HSS3_PWM(pTarget)                    CtrlLed_RteAccess_Set_HSS3_Duty(pTarget); //to Cpm


#define CTRLLED_RTE_SE_TGT_LED_SIG(pTarget)                       (void)Rte_Write_CtrlLed_TgtLedSig_sVal(pTarget); //to Cpm

#define CTRLLED_RTE_SE_ILL_STS(illuminant, state, status, name)    CtrlLed_RteAccess_Set_IlluminantsStatus(illuminant, state, status, name); //to FctR

#define CTRLLED_RTE_SE_CH_STS(ch, states)                         CtrlLed_RteAccess_Set_ChanelLedStatus(ch, states); //to Diag

#define CTRLLED_RTE_SE_CH_SETTINGS(pTarget)                       CtrlLed_RteAccess_Set_ChannelSettings(pTarget); //to CddLed

#define CTRLLED_RTE_SE_CH_FBIT(ch, fbit)                          CtrlLed_RteAccess_Set_Channel_Fbit(ch, fbit); //to SysMon



//---------------------------------------receiver---------------------------------------
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  #define CTRLLED_RTE_RE_TGT_PXL_INTENSITIES(pTarget)         (void)Rte_Read_AdbPxa_IntensityMatrix(pTarget); //from AdbPxa

  #define CTRLLED_RTE_RE_GET_LU_MTX_ERR(logicalUnits, pTarget) CtrlLed_RteAccess_Get_MatrixLuErrors(logicalUnits, pTarget); //from CtrlPxl
  
  #define CTRLLED_RTE_RE_GET_VCCX_MTX_ERR(pboTgt1, pboTgt2)    CtrlLed_RteAccess_Get_MatrixVccxErrors(pboTgt1, pboTgt2); //from CtrlPxl

  #define CTRLLED_RTE_RE_GET_MTX_EEPROM_ERR(pboTarget)         (void)Rte_Read_CtrlPxl_MtxEeprom_ErrorStatus(pboTarget); //from CtrlPxl

  #define CTRLLED_RTE_RE_GET_MTX_SYS_MODE(pTarget)             CtrlLed_RteAccess_Get_MatrixSystemMode(pTarget); //from CddMlc

  #define CTRLLED_RTE_RE_VOLT_RNG                              CtrlLed_RteAccess_VoltageRange(); //from SysVolt

  #define CTRLLED_RTE_RE_PIXEL_LED_DIAG_ENABLE                 CtrlLed_RteAccess_Get_DD01_Diag_Status(); //from Diag_Callback
  #define CTRLLED_RTE_RE_PIXEL_LED_DIAG_INTENSITY(pTarget)     CtrlLed_RteAccess_Get_Diag_Pixel_Intensity(pTarget); //from Diag_Callback

#endif

#define CTRLLED_RTE_RE_TGT_LED(pTarget)                  (void)Rte_Read_FctR_TgtLed_sVal(pTarget); //from FctR

#define CTRLLED_RTE_RE_HSS3_STATUS(pTarget, pboTarget )      CtrlLed_RteAccess_Get_HSS3_Status(pTarget, pboTarget); //from CtrlSwi

#define CTRLLED_RTE_RE_BINNING_CLASS(channel)            CtrlLed_Rte_Get_BinningClass(channel); //from RSens

#define CTRLLED_RTE_RE_VOLT_MV                           CtrlLed_RteAccess_Read_Vbat(); //from IoHw

#define CTRLLED_RTE_RE_GET_ECU_SIDE                      CtrlLed_RteAccess_Get_ECU_Side(); //from IoHw

#define CTRLLED_RTE_RE_GET_CODING_DATA(pTarget)          (void)CtrlLed_RteAccess_Get_CodingPara(pTarget); //from CodM

#define CTRLLED_RTE_RE_GET_LED_STATES(channel, pTarget)  (void)CtrlLed_RteAccess_Get_ChannelState(channel, pTarget); //from SysMon


#endif // CTRL_LED_RTE_2021_03_30_H_

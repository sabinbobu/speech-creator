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
/// \file   IoHwAbUser.h
///
/// \brief  Basic Software I/O Hardware Abstraction User
///
/// \descr  Headfile
///
///         Additional information can be found in the design description
///        
//-----------------------------------------------------------------------------

#ifndef IO_HW_AB_USER_2021_09_13_H_
#define IO_HW_AB_USER_2021_09_13_H_
//=============================================================================
// Includes
//=============================================================================

#include <AL_Helper.h>
#include "IoHwAbUser_Cfg.h"
#include "IoHwAbUser_Types.h"
#include <RteCommonTypes.h>
#include <Cfg/Cfg.h>
#include <Dio.h>

//=============================================================================
// Exported functions
//=============================================================================

tiu16Voltage_mV IoHwAbUser_GetVoltage_NTCs(uint8 ucIdx);

void            IoHwAbUser_Init(void);
void            IoHwAbUser_DeInit(void);
void            IoHwAbUser_Cycle(void);
void            IoHwAbUser_GetMountingSideRaw(tieMountingSideRaw* pulVal);
void            IoHwAbUser_InitGetMountingSide(void);
void            IoHwAbUser_GetMountingSide(tieMountingSide* peVal);
void IoHwAbUser_SetBoostMode(const boolean boEnable1);
void            IoHwAbUser_SetHss(const tieHssState* aeSetting);
void            IoHwAbUser_ResetHss(boolean boSettingValue);
void            IoHwAbUser_SenseEnableHss(boolean boSettingValue);
void            IoHwAbUser_SetDirLwr(boolean boSettingValue);
void            IoHwAbUser_SetLwrSleep(boolean boSettingValue);
void            IoHwAbUser_SetLwrDrvOff(boolean boSettingValue);
void            IoHwAbUser_SetHss_En1(tun16Percent_1_328 unTgtVal);
void            IoHwAbUser_SetHss_En2(tun16Percent_1_328 unTgtVal);
void            IoHwAbUser_SetHss_En3(tun16Percent_1_328 unTgtVal);
void            IoHwAbUser_SetTgtHss3(tun16Percent_1_328 unTgtVal);
void            IoHwAbUser_SetHss_Error(boolean boSettingValue);
void            IoHwAbUser_SetHss_Sen(boolean boSettingValue);
void            IoHwAbUser_SetHss_Sel1(boolean boSettingValue);
void            IoHwAbUser_SetHss_Sel2(boolean boSettingValue);
void            IoHwAbUser_SetVccxEn(boolean boSettingValue);
void            IoHwAbUserTimer0Notification(void);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
void            IoHwAbUser_VccxStateCyclicCheck(void);
void            IoHwAbUser_Set_Vccx_State(boolean boVccx_desiredState);
#endif
void            IoHwAbUser_GetHss0Sense(uint32* unDiagVal);
void            IoHwAbUser_GetHss1Sense(uint32* unDiagVal);
void            IoHwAbUser_GetHss2Sense(uint32* unDiagVal);
void            IoHwAbUser_GetVoltage_NTC(void);
void            IoHwAbUser_Get_PCB(void);
tiu16Voltage_mV IoHwAbUser_Read_VCCX1(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT1(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT2(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT3(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT4(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT5(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT6(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT7(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT8(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT9(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT10(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT11(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT12(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT13(void);
tiu16Voltage_mV IoHwAbUser_GetVoltage_EXT14(void);

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
void IoHwAbUser_SetLSSDiagnostic(boolean boDiagStatus);
void IoHwAbUser_GetOutFctDiag(boolean *boLssDiagnostic);
#endif

#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
void            IoHwAb_User_SetDio_EN_DC(Dio_LevelType ucSignal);
void            IoHwAbUser_GetAdc_VoltDC_OUT1(uint16 *pio_signal);
#endif

#endif // IO_HW_AB_USER_2021_09_13_H_

// EOF

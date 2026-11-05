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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"


//=============================================================================
// Stub function parameter stubs
//=============================================================================

uint32          CddStp_UnitTest__GptTickCount;
uint32          CddStp_UnitTest__GptIsIni;
uint32          CddStp_UnitTest__GptIsRunning;

uint16                   Dem_SetEventStatus_Param1;
uint8                    Dem_SetEventStatus_Param2;
uint32                   LPTMR0_GetTimeElapsed_Param1;
Pwm_ChannelType          Pwm_StartPwmChannel_Param1;
boolean                  IoHwAbUser_SetDirLwr_Param1;
boolean                  IoHwAbUser_SetLwrSleep_Param1;
boolean                  IoHwAbUser_SetLwrDrvOff_Param1;
tsLpit_LpitTmrCfg* Lpit_LpitSetTmrChCompVal_Param1;
tsLpit_LpitTmrCfg* Lpit_LpitSetTmrChIntEnbl_Param1;
tsLpit_LpitTmrCfg* Lpit_LpitSetTmrEnblBit_Param1;
tsLpit_LpitTmrCfg* Lpit_LpitClearTimeout_Param1;
tsLpit_LpitTmrCfg* Lpit_LpitReturnCount_Param1;
uint32                   Lpit_LpitSetTmrChCompVal_Param2;
uint32                   Lpit_LpitSetTmrChIntEnbl_Param2;
uint32                   Lpit_LpitSetTmrEnblBit_Param2;
tsRteCodingParameters    Rte_Read_CodM_CddStp_Para_Param1;
tsRte_CtrlStpTarget      Rte_Read_ppCtrlStpTarget0_StpTargetValues_Param1;
tsRte_CddStpActual       Rte_Write_ppCddStpActual0_sStpActualValues_Param1;
teRte_MountingSide       Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_CtrlStpValidation  Rte_Read_CtrlStp_Validation_Port_Param1;
tiu32Voltage_mV      Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
Pwm_ChannelType      Pwm_ClampPwmChannel_Param1;
tePwm_OutputState    Pwm_ClampPwmChannel_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint32         LPTMR0_GetTimeElapsed_RetVal;
Std_ReturnType Rte_Read_CodM_CddStp_Para_RetVal;
Std_ReturnType Rte_Read_ppCtrlStpTarget0_StpTargetValues_RetVal;
Std_ReturnType Rte_Write_ppCddStpActual0_sStpActualValues_RetVal;
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType Rte_Read_CtrlStp_Validation_Port_RetVal;
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_RetVal;
boolean        CddEft_DataValid_RetVal;
uint32 Lpit_LpitReturnCount_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Dem_SetEventStatus_HitCount;
uint8 LPTMR0_GetTimeElapsed_HitCount;
uint8 Pwm_StartPwmChannel_HitCount;
uint8 IoHwAbUser_SetDirLwr_HitCount;
uint8 IoHwAbUser_SetLwrSleep_HitCount;
uint8 IoHwAbUser_SetLwrDrvOff_HitCount;
uint8 Lpit_LpitSetTmrChCompVal_HitCount;
uint8 Lpit_LpitSetTmrChIntEnbl_HitCount;
uint8 Lpit_LpitSetTmrEnblBit_HitCount;
uint8 Rte_Read_CodM_CddStp_Para_HitCount;
uint8 Rte_Read_ppCtrlStpTarget0_StpTargetValues_HitCount;
uint8 Rte_Write_ppCddStpActual0_sStpActualValues_HitCount;
uint8 Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8 Rte_Read_CtrlStp_Validation_Port_HitCount;
uint8 CddEft_DataValid_Hit_Count;
uint8 ENABLE_INTERRUPTS_HitCount;
uint8 DISABLE_INTERRUPTS_HitCount;
uint8 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint8 Pwm_ClampPwmChannel_HitCount;
uint8 Lpit_LpitReturnCount_HitCount;
uint8 Lpit_LpitClearTimeout_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType Channel) { return CddStp_UnitTest__GptTickCount; }
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType Channel) { return CddStp_UnitTest__GptTickCount; }
FUNC(void, GPT_CODE)          Gpt_StopTimer(Gpt_ChannelType Channel) { CddStp_UnitTest__GptIsRunning = FALSE; }
FUNC(void, GPT_CODE)          Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value) { CddStp_UnitTest__GptIsRunning = TRUE; }

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Param1 = unAlecId;
  Dem_SetEventStatus_Param2 = ucTestStatus;
  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;

  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Pwm_StartPwmChannel
///
/// \descr  Stub function created to simulate the behaviour of Pwm_StartPwmChannel
///
/// \param  channelNumber
///
/// \return void
//-----------------------------------------------------------------------------
void Pwm_StartPwmChannel(Pwm_ChannelType channelNumber)
{
  Pwm_StartPwmChannel_Param1 = channelNumber;
  Pwm_StartPwmChannel_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Pwm_ClampPwmChannel
///
/// \descr  Stub function created to simulate the behaviour of Pwm_ClampPwmChannel
///
/// \param  channelNumber, level
///
/// \return void
//-----------------------------------------------------------------------------
void Pwm_ClampPwmChannel(Pwm_ChannelType channelNumber, tePwm_OutputState level)
{
  Pwm_ClampPwmChannel_Param1 = channelNumber;
  Pwm_ClampPwmChannel_Param2 = level;
  Pwm_ClampPwmChannel_HitCount++;
}


//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetDirLwr
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_SetDirLwr
///
/// \param  boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetDirLwr(boolean boSettingValue)
{
  IoHwAbUser_SetDirLwr_Param1 = boSettingValue;
  IoHwAbUser_SetDirLwr_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetDirLwr
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_SetDirLwr
///
/// \param  boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetLwrSleep(boolean boSettingValue)
{
  IoHwAbUser_SetLwrSleep_Param1 = boSettingValue;
  IoHwAbUser_SetLwrSleep_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_SetLwrDrvOff
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_SetLwrDrvOff
///
/// \param  boSettingValue
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_SetLwrDrvOff(boolean boSettingValue)
{
  IoHwAbUser_SetLwrDrvOff_Param1 = boSettingValue;
  IoHwAbUser_SetLwrDrvOff_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Lpit_LpitSetTmrChCompVal
///
/// \descr  Stub function created to simulate the behaviour of Lpit_LpitSetTmrChCompVal
///
/// \param  psLpitTmr
/// \param  ulCompVal
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitSetTmrChCompVal(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal)
{
  Lpit_LpitSetTmrChCompVal_Param1 = psLpitTmr;
  Lpit_LpitSetTmrChCompVal_Param2 = ulCompVal;
  Lpit_LpitSetTmrChCompVal_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Lpit_LpitClearTimeout
///
/// \descr  Stub function created to simulate the behaviour of Lpit_LpitSetTmrChCompVal
///
/// \param  psLpitTmr
/// \param  ulCompVal
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitClearTimeout(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
  Lpit_LpitClearTimeout_Param1 = psLpitTmr;
  Lpit_LpitClearTimeout_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Lpit_LpitReturnCount
///
/// \descr  Stub function created to simulate the behaviour of Lpit_LpitSetTmrChCompVal
///
/// \param  psLpitTmr
/// \param  ulCompVal
///
/// \return void
//-----------------------------------------------------------------------------
uint32 Lpit_LpitReturnCount(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr)
{
  Lpit_LpitReturnCount_Param1 = psLpitTmr;
  Lpit_LpitReturnCount_HitCount++;
  return Lpit_LpitReturnCount_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Lpit_LpitSetTmrChIntEnbl
///
/// \descr  Stub function created to simulate the behaviour of Lpit_LpitSetTmrChIntEnbl
///
/// \param  psLpitTmr
/// \param  ulIntEnbl
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitSetTmrChIntEnbl(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl)
{
  Lpit_LpitSetTmrChIntEnbl_Param1 = psLpitTmr;
  Lpit_LpitSetTmrChIntEnbl_Param2 = ulIntEnbl;
  Lpit_LpitSetTmrChIntEnbl_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Lpit_LpitSetTmrEnblBit
///
/// \descr  Stub function created to simulate the behaviour of Lpit_LpitSetTmrEnblBit
///
/// \param  psLpitTmr
/// \param  ulEnblBit
///
/// \return void
//-----------------------------------------------------------------------------
void Lpit_LpitSetTmrEnblBit(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit)
{
  Lpit_LpitSetTmrEnblBit_Param1 = psLpitTmr;
  Lpit_LpitSetTmrEnblBit_Param2 = ulEnblBit;
  Lpit_LpitSetTmrEnblBit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CddStp_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_CddStp_Para
///
/// \param  *pData
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CddStp_Para(tsRteCodingParameters* pparam1)
{
  *pparam1 = Rte_Read_CodM_CddStp_Para_Param1;
  Rte_Read_CodM_CddStp_Para_HitCount++;
  return Rte_Read_CodM_CddStp_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppCtrlStpTarget0_StpTargetValues
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppCtrlStpTarget0_StpTargetValues
///
/// \param  *pparam1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppCtrlStpTarget0_StpTargetValues(tsRte_CtrlStpTarget* pparam1)
{
  *pparam1 = Rte_Read_ppCtrlStpTarget0_StpTargetValues_Param1;
  Rte_Read_ppCtrlStpTarget0_StpTargetValues_HitCount++;
  return Rte_Read_ppCtrlStpTarget0_StpTargetValues_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_ppCddStpActual0_sStpActualValues
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_ppCddStpActual0_sStpActualValues
///
/// \param  *pparam1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ppCddStpActual0_sStpActualValues(const tsRte_CddStpActual* pparam1)
{
  Rte_Write_ppCddStpActual0_sStpActualValues_Param1 = *pparam1;
  Rte_Write_ppCddStpActual0_sStpActualValues_HitCount++;
  return Rte_Write_ppCddStpActual0_sStpActualValues_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;
  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_Validation_Port
///
/// \descr Stub used to simulate the behaviour of Rte_Read_CtrlStp_Validation_Port
///
/// \param   ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_Validation_Port(tsRte_CtrlStpValidation* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_Validation_Port_Param1;
  Rte_Read_CtrlStp_Validation_Port_HitCount++;
  return Rte_Read_CtrlStp_Validation_Port_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddEft_DataValid
///
/// \descr  Stub function created to simulate the behaviour of CddEft_DataValid
///
/// \param  void
///
/// \return CddEft_DataValid_RetVal
//-----------------------------------------------------------------------------
boolean CddEft_DataValid(void)
{
  CddEft_DataValid_Hit_Count++;
  return CddEft_DataValid_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  ENABLE_INTERRUPTS
///
/// \descr  Stub function created to simulate the behaviour of ENABLE_INTERRUPTS
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void ENABLE_INTERRUPTS(void)
{
  ENABLE_INTERRUPTS_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DISABLE_INTERRUPTS
///
/// \descr  Stub function created to simulate the behaviour of DISABLE_INTERRUPTS
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void DISABLE_INTERRUPTS(void)
{
  DISABLE_INTERRUPTS_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr Stub function to simulate the behavior of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;
}


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

tiu32Voltage_mV      Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
tDcmStateMsg         Rte_Read_DcmState0_Port_Param1;
tDcmPosMsg           Rte_Read_DcmPos0_Port_Param1;
tsRte_CtrlDcmTarget  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1;
tDcmStateMsg         Rte_Write_DcmState0_Port_Param1;
tsRte_DcmStatusError Rte_Write_CddDcm_ErrorStatus_Param1;
tDcmPosMsg           Rte_Write_DcmPos0_Port_Param1;
uint16               IoHwAbUser_GetAdc_VoltDC_OUT1_Param1;
Dio_LevelType        IoHwAb_User_SetDio_EN_DC_Param1;
uint16               Dem_SetEventStatus_Param1;
uint8                Dem_SetEventStatus_Param2;
Pwm_ChannelType      Pwm_StartPwmChannel_Param1;
Pwm_ChannelType      Pwm_SetDutyCycle_Param1;
uint16               Pwm_SetDutyCycle_Param2;
Pwm_ChannelType      Pwm_ClampPwmChannel_Param1;
tePwm_OutputState    Pwm_ClampPwmChannel_Param2;
NvM_BlockIdType      NvM_WriteBlock_Param1;
void*                NvM_WriteBlock_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType NvM_WriteBlock_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint8 Rte_Read_DcmState0_Port_HitCount;
uint8 Rte_Read_DcmPos0_Port_HitCount;
uint8 Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount;
uint8 Rte_Write_DcmState0_Port_HitCount;
uint8 Rte_Write_CddDcm_ErrorStatus_HitCount;
uint8 Rte_Write_DcmPos0_Port_HitCount;
uint8 IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount;
uint8 IoHwAb_User_SetDio_EN_DC_HitCount;
uint8 Dem_SetEventStatus_HitCount;
uint8 Pwm_StartPwmChannel_HitCount;
uint8 Pwm_SetDutyCycle_HitCount;
uint8 Pwm_ClampPwmChannel_HitCount;
uint8 NvM_WriteBlock_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Rte_Write_DcmPos0_Port
///
/// \descr Stub function to simulate the behavior of Rte_Write_DcmPos0_Port
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Write_DcmPos0_Port(tDcmPosMsg* ppara1)
{
  Rte_Write_DcmPos0_Port_Param1 = *ppara1;
  Rte_Write_DcmPos0_Port_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_CddDcm_ErrorStatus
///
/// \descr Stub function to simulate the behavior of Rte_Write_CddDcm_ErrorStatus
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Write_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1)
{
  Rte_Write_CddDcm_ErrorStatus_Param1 = *ppara1;
  Rte_Write_CddDcm_ErrorStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_DcmState0_Port
///
/// \descr Stub function to simulate the behavior of Rte_Write_DcmState0_Port
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Write_DcmState0_Port(tDcmStateMsg* ppara1)
{
  Rte_Write_DcmState0_Port_Param1 = *ppara1;
  Rte_Write_DcmState0_Port_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_ppCtrlDcmTarget0_DcmTargetValues
///
/// \descr Stub function to simulate the behavior of Rte_Read_ppCtrlDcmTarget0_DcmTargetValues
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1)
{
  *ppara1 = Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_Param1;
  Rte_Read_ppCtrlDcmTarget0_DcmTargetValues_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_DcmPos0_Port
///
/// \descr Stub function to simulate the behavior of Rte_Read_DcmPos0_Port
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Read_DcmPos0_Port(tDcmPosMsg* ppara1)
{
  *ppara1 = Rte_Read_DcmPos0_Port_Param1;
  Rte_Read_DcmPos0_Port_HitCount++;
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
void Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_DcmState0_Port
///
/// \descr Stub function to simulate the behavior of Rte_Read_DcmState0_Port
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Read_DcmState0_Port(tDcmStateMsg* ppara1)
{
  *ppara1 = Rte_Read_DcmState0_Port_Param1;
  Rte_Read_DcmState0_Port_HitCount++;
}

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
/// \brief  IoHwAb_User_SetDio_EN_DC
///
/// \descr  Stub function created to simulate the behaviour of IoHwAb_User_SetDio_EN_DC
///
/// \param  pio_signal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAb_User_SetDio_EN_DC(Dio_LevelType signal)
{
  IoHwAb_User_SetDio_EN_DC_Param1 = signal;
  IoHwAb_User_SetDio_EN_DC_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_GetAdc_VoltDC_OUT1
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_GetAdc_VoltDC_OUT1
///
/// \param  pio_signal
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_GetAdc_VoltDC_OUT1(uint16 *pio_signal)
{
  *pio_signal = IoHwAbUser_GetAdc_VoltDC_OUT1_Param1;
  IoHwAbUser_GetAdc_VoltDC_OUT1_HitCount++;
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
/// \brief  Pwm_SetDutyCycle
///
/// \descr  Stub function created to simulate the behaviour of Pwm_SetDutyCycle
///
/// \param  channelNumber, DutyCycle
///
/// \return void
//-----------------------------------------------------------------------------
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
  Pwm_SetDutyCycle_Param1 = ChannelNumber;
  Pwm_SetDutyCycle_Param2 = DutyCycle;
  Pwm_SetDutyCycle_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  - BlockId, NvM_SrcPtr
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
  NvM_WriteBlock_Param1 = BlockId;
  NvM_WriteBlock_Param2 = NvM_SrcPtr;
  NvM_WriteBlock_HitCount++;
  return NvM_WriteBlock_RetVal;
}
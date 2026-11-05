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

uint32_t          FTM_DRV_Init_Param1;
ftm_user_config_t FTM_DRV_Init_Param2;
ftm_state_t       FTM_DRV_Init_Param3;
uint32_t          FTM_DRV_InitInputCapture_Param1;
ftm_input_param_t FTM_DRV_InitInputCapture_Param2;
uint32_t          FTM_IC_DRV_SetChannelMode_Param1;
uint8_t           FTM_IC_DRV_SetChannelMode_Param2;
ftm_ic_op_mode_t  FTM_IC_DRV_SetChannelMode_Param3;
bool              FTM_IC_DRV_SetChannelMode_Param4;
uint32_t          FTM_DRV_GetInputCaptureMeasurement_Param1;
uint8_t           FTM_DRV_GetInputCaptureMeasurement_Param2;
uint8             FTM_SC_PWMEN0_Param1;
uint8             FTM_SC_PWMEN4_Param1;
uint8             FTM_SC_PS_Param1;
FTM_Type          FTM_RMW_SC_Param1;
uint32            FTM_RMW_SC_Param2;
uint16            FTM_RMW_SC_Param3;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

status_t FTM_DRV_Init_RetVal;
status_t FTM_DRV_InitInputCapture_RetVal;
status_t FTM_IC_DRV_SetChannelMode_RetVal;
uint16_t FTM_DRV_GetInputCaptureMeasurement_RetVal;
uint16   FTM_SC_PWMEN0_RetVal;
uint16   FTM_SC_PWMEN4_RetVal;
uint16   FTM_SC_PS_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 FTM_DRV_Init_HitCount;
uint8 FTM_DRV_InitInputCapture_HitCount;
uint8 FTM_IC_DRV_SetChannelMode_HitCount;
uint8 FTM_DRV_GetInputCaptureMeasurement_HitCount;
uint8 FTM_SC_PWMEN0_HitCount;
uint8 FTM_SC_PWMEN4_HitCount;
uint8 FTM_SC_PS_HitCount;
uint8 FTM_RMW_SC_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  FTM_RMW_SC
///
/// \descr  Stub function created to simulate the behaviour of FTM_RMW_SC
///
/// \param  base
/// \param  mask
/// \param  value
///
/// \return void
//-----------------------------------------------------------------------------
void FTM_RMW_SC(FTM_Type base, uint32 mask, uint16 value)
{
  FTM_RMW_SC_Param1 = base;
  FTM_RMW_SC_Param2 = mask;
  FTM_RMW_SC_Param3 = value;
  FTM_RMW_SC_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_SC_PS
///
/// \descr  Stub function created to simulate the behaviour of FTM_SC_PS
///
/// \param  param
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 FTM_SC_PS(uint8 param)
{
  FTM_SC_PS_Param1 = param;
  FTM_SC_PS_HitCount++;
  return FTM_SC_PS_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_SC_PWMEN4
///
/// \descr  Stub function created to simulate the behaviour of FTM_SC_PWMEN4
///
/// \param  param
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 FTM_SC_PWMEN4(uint8 param)
{
  FTM_SC_PWMEN4_Param1 = param;
  FTM_SC_PWMEN4_HitCount++;
  return FTM_SC_PWMEN4_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_SC_PWMEN0
///
/// \descr  Stub function created to simulate the behaviour of FTM_SC_PWMEN0
///
/// \param  param
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 FTM_SC_PWMEN0(uint8 param)
{
  FTM_SC_PWMEN0_Param1 = param;
  FTM_SC_PWMEN0_HitCount++;
  return FTM_SC_PWMEN0_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_GetInputCaptureMeasurement
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_GetInputCaptureMeasurement
///
/// \param  instance
/// \param  channel
///
/// \return uint16_t
//-----------------------------------------------------------------------------
uint16_t FTM_DRV_GetInputCaptureMeasurement(uint32_t instance, uint8_t channel)
{
  FTM_DRV_GetInputCaptureMeasurement_Param1 = instance;
  FTM_DRV_GetInputCaptureMeasurement_Param2 = channel;
  FTM_DRV_GetInputCaptureMeasurement_HitCount++;
  return FTM_DRV_GetInputCaptureMeasurement_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_IC_DRV_SetChannelMode
///
/// \descr  Stub function created to simulate the behaviour of FTM_IC_DRV_SetChannelMode
///
/// \param  instance
/// \param  channel
/// \param  inputMode
/// \param  enableContinuousCapture
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t FTM_IC_DRV_SetChannelMode(uint32_t instance, uint8_t channel, ftm_ic_op_mode_t inputMode, bool enableContinuousCapture)
{
  FTM_IC_DRV_SetChannelMode_Param1 = instance;
  FTM_IC_DRV_SetChannelMode_Param2 = channel;
  FTM_IC_DRV_SetChannelMode_Param3 = inputMode;
  FTM_IC_DRV_SetChannelMode_Param4 = enableContinuousCapture;
  FTM_IC_DRV_SetChannelMode_HitCount++;
  return FTM_IC_DRV_SetChannelMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_Init
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_Init
///
/// \param  instance
/// \param  info
/// \param  state
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t FTM_DRV_Init(uint32_t instance, const ftm_user_config_t* info, ftm_state_t* state)
{
  FTM_DRV_Init_Param1 = instance;
  FTM_DRV_Init_Param2 = *info;
  *state = FTM_DRV_Init_Param3;
  FTM_DRV_Init_HitCount++;
  return FTM_DRV_Init_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FTM_DRV_InitInputCapture
///
/// \descr  Stub function created to simulate the behaviour of FTM_DRV_InitInputCapture
///
/// \param  instance
/// \param  param
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t FTM_DRV_InitInputCapture(uint32_t instance, const ftm_input_param_t* param)
{
  FTM_DRV_InitInputCapture_Param1 = instance;
  FTM_DRV_InitInputCapture_Param2 = *param;
  FTM_DRV_InitInputCapture_HitCount++;
  return FTM_DRV_InitInputCapture_RetVal;
}



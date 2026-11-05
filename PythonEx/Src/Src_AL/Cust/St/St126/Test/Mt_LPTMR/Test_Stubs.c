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
// Stub function declarations
//=============================================================================

void     LPTMR_DRV_GetConfig(const uint32_t instance, lptmr_config_t * const config);
uint16_t LPTMR_DRV_GetCounterValueByCount(const uint32_t instance);
void     LPTMR_DRV_ClearCompareFlag(const uint32_t instance);
void     LPTMR_DRV_Init(const uint32_t instance, const lptmr_config_t * const config, const bool startCounter);
bool     LPTMR_DRV_IsRunning(const uint32_t instance);
void     LPTMR_DRV_StartCounter(const uint32_t instance);
void     LPTMR_DRV_StopCounter(const uint32_t instance);
void     RTX_Timer_Notification(void);


//=============================================================================
// Stub function parameter stubs
//=============================================================================

uint32_t        LPTMR_DRV_GetConfig_Param1;
lptmr_config_t  LPTMR_DRV_GetConfig_Param2;
uint32_t        LPTMR_DRV_GetCounterValueByCount_Param1;
uint32_t        LPTMR_DRV_ClearCompareFlag_Param1;
uint32_t        LPTMR_DRV_Init_Param1;
lptmr_config_t* LPTMR_DRV_Init_Param2;
bool            LPTMR_DRV_Init_Param3;
uint32_t        LPTMR_DRV_IsRunning_Param1;
uint32_t        LPTMR_DRV_StartCounter_Param1;
uint32_t        LPTMR_DRV_StopCounter_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

uint16_t        LPTMR_DRV_GetCounterValueByCount_RetVal;
bool            LPTMR_DRV_IsRunning_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 LPTMR_DRV_GetConfig_HitCount;
uint8 LPTMR_DRV_GetCounterValueByCount_HitCount;
uint8 LPTMR_DRV_ClearCompareFlag_HitCount;
uint8 LPTMR_DRV_Init_HitCount;
uint8 LPTMR_DRV_IsRunning_HitCount;
uint8 LPTMR_DRV_StartCounter_HitCount;
uint8 LPTMR_DRV_StopCounter_HitCount;
uint8 RTX_Timer_Notification_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_GetConfig
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_GetConfig
///
/// \param  instance
/// \param  config
///
/// \return void
//-----------------------------------------------------------------------------
void LPTMR_DRV_GetConfig(const uint32_t instance, lptmr_config_t * const config)
{
  LPTMR_DRV_GetConfig_Param1 = instance;
  *config = LPTMR_DRV_GetConfig_Param2;
  LPTMR_DRV_GetConfig_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_GetCounterValueByCount
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_GetCounterValueByCount
///
/// \param  instance
///
/// \return uint16_t
//-----------------------------------------------------------------------------
uint16_t LPTMR_DRV_GetCounterValueByCount(const uint32_t instance)
{
  LPTMR_DRV_GetCounterValueByCount_Param1 = instance;
  LPTMR_DRV_GetCounterValueByCount_HitCount++;
  return LPTMR_DRV_GetCounterValueByCount_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_ClearCompareFlag
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_ClearCompareFlag
///
/// \param  instance
///
/// \return void
//-----------------------------------------------------------------------------
void LPTMR_DRV_ClearCompareFlag(const uint32_t instance)
{
  LPTMR_DRV_ClearCompareFlag_Param1 = instance;
  LPTMR_DRV_ClearCompareFlag_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_Init
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_Init
///
/// \param  instance
/// \param  config
/// \param  startCounter
///
/// \return void
//-----------------------------------------------------------------------------
void LPTMR_DRV_Init(const uint32_t instance, const lptmr_config_t * const config, const bool startCounter)
{
  LPTMR_DRV_Init_Param1 = instance;
  LPTMR_DRV_Init_Param2 = config;
  LPTMR_DRV_Init_Param3 = startCounter;
  LPTMR_DRV_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_IsRunning
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_IsRunning
///
/// \param  instance
///
/// \return bool
//-----------------------------------------------------------------------------
bool LPTMR_DRV_IsRunning(const uint32_t instance)
{
  LPTMR_DRV_IsRunning_Param1 = instance;
  LPTMR_DRV_IsRunning_HitCount++;
  return LPTMR_DRV_IsRunning_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_StartCounter
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_StartCounter
///
/// \param  instance
///
/// \return void
//-----------------------------------------------------------------------------
void LPTMR_DRV_StartCounter(const uint32_t instance)
{
  LPTMR_DRV_StartCounter_Param1 = instance;
  LPTMR_DRV_StartCounter_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LPTMR_DRV_StopCounter
///
/// \descr  Stub function created to simulate the behaviour of LPTMR_DRV_StopCounter
///
/// \param  instance
///
/// \return void
//-----------------------------------------------------------------------------
void LPTMR_DRV_StopCounter(const uint32_t instance)
{
  LPTMR_DRV_StopCounter_Param1 = instance;
  LPTMR_DRV_StopCounter_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  RTX_Timer_Notification
///
/// \descr  Stub function created to simulate the behaviour of RTX_Timer_Notification
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void RTX_Timer_Notification(void)
{
  RTX_Timer_Notification_HitCount++;
}


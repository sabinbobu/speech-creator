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
uint32_t                              SvcAccessReg32_Param1;
uint32_t                              SvcAccessReg32_Param2;
uint32_t                              SvcAccessReg32_Param3;

clock_manager_user_config_t*          CLOCK_SYS_Init_Param1;
uint8_t                               CLOCK_SYS_Init_Param2;
clock_manager_callback_user_config_t* CLOCK_SYS_Init_Param3;
uint8_t                               CLOCK_SYS_Init_Param4;

uint8_t                               CLOCK_SYS_UpdateConfiguration_Param1;
clock_manager_policy_t                CLOCK_SYS_UpdateConfiguration_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint32_t SvcAccessReg32_RetVal;
status_t CLOCK_SYS_UpdateConfiguration_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 CLOCK_SYS_Init_HitCount;
uint8 CLOCK_SYS_UpdateConfiguration_HitCount;
uint8 SvcAccessReg32_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  CLOCK_SYS_Init
///
/// \descr  Stub function created to simulate the behaviour of CLOCK_SYS_Init
///
/// \param  **clockConfigsPtr
/// \param  configsNumber
/// \param  **callbacksPtr
/// \param  callbacksNumber
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t CLOCK_SYS_Init(clock_manager_user_config_t const** clockConfigsPtr, uint8_t configsNumber, clock_manager_callback_user_config_t** callbacksPtr, uint8_t callbacksNumber)
{
  clockConfigsPtr = &CLOCK_SYS_Init_Param1;
  configsNumber = &CLOCK_SYS_Init_Param2;
  callbacksPtr = CLOCK_SYS_Init_Param3;
  callbacksNumber = CLOCK_SYS_Init_Param4;
  CLOCK_SYS_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CLOCK_SYS_UpdateConfiguration
///
/// \descr  Stub function created to simulate the behaviour of CLOCK_SYS_UpdateConfiguration
///
/// \param  targetConfigIndex
/// \param  policy
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex, clock_manager_policy_t policy)
{
  CLOCK_SYS_UpdateConfiguration_Param1 = targetConfigIndex;
  CLOCK_SYS_UpdateConfiguration_Param2 = policy;
  CLOCK_SYS_UpdateConfiguration_HitCount++;
  return CLOCK_SYS_UpdateConfiguration_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  SvcAccessReg32
///
/// \descr  Stub function created to simulate the behaviour of SvcAccessReg32
///
/// \param  *pRegister
/// \param  ClrMask
/// \param  SetMask
///
/// \return uint32_t
//-----------------------------------------------------------------------------
__attribute__((always_inline)) uint32_t SvcAccessReg32(volatile uint32_t* pRegister, uint32_t ClrMask, uint32_t SetMask)
{
  SvcAccessReg32_Param1 = *pRegister;
  SvcAccessReg32_Param2 = ClrMask;
  SvcAccessReg32_Param3 = SetMask;
  SvcAccessReg32_HitCount++;
  return SvcAccessReg32_RetVal;
}


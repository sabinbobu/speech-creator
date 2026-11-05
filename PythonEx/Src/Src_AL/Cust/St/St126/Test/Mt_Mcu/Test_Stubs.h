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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <Mcu.h>

//=============================================================================
// Stub function declarations
//=============================================================================
status_t CLOCK_SYS_Init(clock_manager_user_config_t const** clockConfigsPtr, uint8_t configsNumber, clock_manager_callback_user_config_t** callbacksPtr, uint8_t callbacksNumber);
status_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex, clock_manager_policy_t policy);
__attribute__((always_inline)) uint32_t SvcAccessReg32(volatile uint32_t* pRegister, uint32_t ClrMask, uint32_t SetMask);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint32_t                              SvcAccessReg32_Param1;
extern uint32_t                              SvcAccessReg32_Param2;
extern uint32_t                              SvcAccessReg32_Param3;

extern clock_manager_user_config_t*          CLOCK_SYS_Init_Param1;
extern uint8_t                               CLOCK_SYS_Init_Param2;
extern clock_manager_callback_user_config_t* CLOCK_SYS_Init_Param3;
extern uint8_t                               CLOCK_SYS_Init_Param4;

extern uint8_t                               CLOCK_SYS_UpdateConfiguration_Param1;
extern clock_manager_policy_t                CLOCK_SYS_UpdateConfiguration_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint32_t SvcAccessReg32_RetVal;
extern status_t CLOCK_SYS_UpdateConfiguration_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 CLOCK_SYS_Init_HitCount;
extern uint8 CLOCK_SYS_UpdateConfiguration_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

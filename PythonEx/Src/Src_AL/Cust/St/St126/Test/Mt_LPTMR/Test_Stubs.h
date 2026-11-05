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

#include <ALUnitTest_UserInterface.h>
#include <AL_Helper.h>
#include <LPTMR.h>

//=============================================================================
// Stub function declarations
//=============================================================================

extern void     LPTMR_DRV_GetConfig(const uint32_t instance, lptmr_config_t * const config);
extern uint16_t LPTMR_DRV_GetCounterValueByCount(const uint32_t instance);
extern void     LPTMR_DRV_ClearCompareFlag(const uint32_t instance);
extern void     LPTMR_DRV_Init(const uint32_t instance, const lptmr_config_t * const config, const bool startCounter);
extern bool     LPTMR_DRV_IsRunning(const uint32_t instance);
extern void     LPTMR_DRV_StartCounter(const uint32_t instance);
extern void     LPTMR_DRV_StopCounter(const uint32_t instance);
extern void     RTX_Timer_Notification(void);


//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint32_t        LPTMR_DRV_GetConfig_Param1;
extern lptmr_config_t  LPTMR_DRV_GetConfig_Param2;
extern uint32_t        LPTMR_DRV_GetCounterValueByCount_Param1;
extern uint32_t        LPTMR_DRV_ClearCompareFlag_Param1;
extern uint32_t        LPTMR_DRV_Init_Param1;
extern lptmr_config_t* LPTMR_DRV_Init_Param2;
extern bool            LPTMR_DRV_Init_Param3;
extern uint32_t        LPTMR_DRV_IsRunning_Param1;
extern uint32_t        LPTMR_DRV_StartCounter_Param1;
extern uint32_t        LPTMR_DRV_StopCounter_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint16_t        LPTMR_DRV_GetCounterValueByCount_RetVal;
extern bool            LPTMR_DRV_IsRunning_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 LPTMR_DRV_GetConfig_HitCount;
extern uint8 LPTMR_DRV_GetCounterValueByCount_HitCount;
extern uint8 LPTMR_DRV_ClearCompareFlag_HitCount;
extern uint8 LPTMR_DRV_Init_HitCount;
extern uint8 LPTMR_DRV_IsRunning_HitCount;
extern uint8 LPTMR_DRV_StartCounter_HitCount;
extern uint8 LPTMR_DRV_StopCounter_HitCount;
extern uint8 RTX_Timer_Notification_HitCount;


#endif // TEST_STUBS_2023_08_25_H_

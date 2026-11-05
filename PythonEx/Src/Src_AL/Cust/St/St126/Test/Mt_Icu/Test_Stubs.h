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

#include <Icu_TargetTypes.h>

//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================

status_t FTM_DRV_Init(uint32_t instance, const ftm_user_config_t* info, ftm_state_t* state);
status_t FTM_DRV_InitInputCapture(uint32_t instance, const ftm_input_param_t* param);
status_t FTM_IC_DRV_SetChannelMode(uint32_t instance, uint8_t channel, ftm_ic_op_mode_t inputMode, bool enableContinuousCapture);
uint16_t FTM_DRV_GetInputCaptureMeasurement(uint32_t instance, uint8_t channel);
uint16   FTM_SC_PWMEN0(uint8 param);
uint16   FTM_SC_PWMEN4(uint8 param);
uint16   FTM_SC_PS(uint8 param);
void     FTM_RMW_SC(FTM_Type base, uint32 mask, uint16 value);


//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint32_t          FTM_DRV_Init_Param1;
extern ftm_user_config_t FTM_DRV_Init_Param2;
extern ftm_state_t       FTM_DRV_Init_Param3;
extern uint32_t          FTM_DRV_InitInputCapture_Param1;
extern ftm_input_param_t FTM_DRV_InitInputCapture_Param2;
extern uint32_t          FTM_IC_DRV_SetChannelMode_Param1;
extern uint8_t           FTM_IC_DRV_SetChannelMode_Param2;
extern ftm_ic_op_mode_t  FTM_IC_DRV_SetChannelMode_Param3;
extern bool              FTM_IC_DRV_SetChannelMode_Param4;
extern uint32_t          FTM_DRV_GetInputCaptureMeasurement_Param1;
extern uint8_t           FTM_DRV_GetInputCaptureMeasurement_Param2;
extern uint8             FTM_SC_PWMEN0_Param1;
extern uint8             FTM_SC_PWMEN4_Param1;
extern uint8             FTM_SC_PS_Param1;
extern FTM_Type          FTM_RMW_SC_Param1;
extern uint32            FTM_RMW_SC_Param2;
extern uint16            FTM_RMW_SC_Param3;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern status_t FTM_DRV_Init_RetVal;
extern status_t FTM_DRV_InitInputCapture_RetVal;
extern status_t FTM_IC_DRV_SetChannelMode_RetVal;
extern uint16_t FTM_DRV_GetInputCaptureMeasurement_RetVal;
extern uint16   FTM_SC_PWMEN0_RetVal;
extern uint16   FTM_SC_PWMEN4_RetVal;
extern uint16   FTM_SC_PS_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 FTM_DRV_Init_HitCount;
extern uint8 FTM_DRV_InitInputCapture_HitCount;
extern uint8 FTM_IC_DRV_SetChannelMode_HitCount;
extern uint8 FTM_DRV_GetInputCaptureMeasurement_HitCount;
extern uint8 FTM_SC_PWMEN0_HitCount;
extern uint8 FTM_SC_PWMEN4_HitCount;
extern uint8 FTM_SC_PS_HitCount;
extern uint8 FTM_RMW_SC_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

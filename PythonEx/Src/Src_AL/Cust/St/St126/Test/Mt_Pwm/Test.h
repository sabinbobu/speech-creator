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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <UtilUtility.h>
#include <Pwm.h>

//=============================================================================
// Module global variables
//=============================================================================
pwm_channel_to_config_map_t pwm_channel_to_config_map_lut[14] =
{/* channel, inst map index, inst map chan */
	{ 1, 0, 2}, // LEDCTRL1
	{ 2, 0, 1}, // LEDCTRL2
	{ 3, 1, 3}, // LEDCTRL3
	{ 4, 1, 2}, // LEDCTRL4
	{ 5, 1, 1}, // LEDCTRL5
	{ 6, 1, 0}, // LEDCTRL6
	{ 7, 4, 0}, // LEDCTRL7
	{ 8, 2, 2}, // LEDCTRL8
	{ 9, 2, 1}, // LEDCTRL9
	{10, 2, 0}, // LEDCTRL10
	{11, 2, 4}, // LEDCTRL11
	{12, 2, 3}, // LEDCTRL12
	{0, 0, 0}, // dummy 13  
	{13, 5, 0}, // dummy 14
};

pwm_instance_t pwm_pal_instances[5] =
{
	{PWM_INST_TYPE_FTM, 0},
	{PWM_INST_TYPE_FTM, 1},
	{PWM_INST_TYPE_FTM, 2},
	{PWM_INST_TYPE_FTM, 3},
	{PWM_INST_TYPE_FTM, 5},
};

pwm_ftm_timebase_t pwm_pal_1_timebase0 =
{
	// sourceClock, prescaler, deadtimePrescaler
	FTM_CLOCK_SOURCE_SYSTEMCLK, FTM_CLOCK_DIVID_BY_1, FTM_DEADTIME_DIVID_BY_1  // 80MHz for Boost sync

};
pwm_ftm_timebase_t pwm_pal_1_timebase1 =
{
  FTM_CLOCK_SOURCE_SYSTEMCLK, FTM_CLOCK_DIVID_BY_8, FTM_DEADTIME_DIVID_BY_1 // 10MHz for Ledctrl
};

pwm_ftm_timebase_t pwm_pal_1_timebase2 =
{
  FTM_CLOCK_SOURCE_SYSTEMCLK, FTM_CLOCK_DIVID_BY_128, FTM_DEADTIME_DIVID_BY_1 // 625kHz for ST
};

pwm_channel_t pwm_pal_configs_FTM0[3U] =
{
	/* channel, channelType, period, duty,  polarity, insertDeadtime*/
	/*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
	{5, PWM_EDGE_ALIGNED, 25000U, 0u , PWM_ACTIVE_HIGH, FALSE,
	  0, FALSE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u }, //LEDCTRL_7
	{6, PWM_EDGE_ALIGNED, 25000U, 1u , PWM_ACTIVE_HIGH, FALSE,
	  0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u }, //LEDCTRL_2
	{7, PWM_EDGE_ALIGNED, 25000U, 0u , PWM_ACTIVE_HIGH, FALSE,
	  0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u }, //LEDCTRL_1
};

pwm_channel_t pwm_pal_configs_FTM1[4U] =
{
  {1, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, FALSE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_6
  {5, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, FALSE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_5
  {6, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, FALSE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_4
  {7, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_3
};

pwm_channel_t pwm_pal_configs_FTM2[5U] =
{
  {0, PWM_EDGE_ALIGNED, 25000U, 100u, PWM_ACTIVE_HIGH, FALSE,
	0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_10
  {1, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_9
  {2, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, FALSE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_8
  {4, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, FALSE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_12
  {5, PWM_EDGE_ALIGNED, 25000U, 0u, PWM_ACTIVE_HIGH, FALSE,
	0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0u}, //LEDCTRL_11
};

pwm_channel_t pwm_pal_configs_FTM3[2U] =
{
  {5, PWM_EDGE_ALIGNED, 0U, 0U, PWM_ACTIVE_HIGH, FALSE, 0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //ST_STEP_AHL
  {4, PWM_EDGE_ALIGNED, 0U, 0U, PWM_ACTIVE_HIGH, FALSE, 0, TRUE, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //ST_STEP_LWR
};

pwm_global_config_t pwm_pal_configs[4U] =
{
	/* pwmChannels,  numberOfPwmChannels */
   {&pwm_pal_configs_FTM0[0], UTIL_COUNTOF(pwm_pal_configs_FTM0)},
   {&pwm_pal_configs_FTM1[0], UTIL_COUNTOF(pwm_pal_configs_FTM1)},
   {&pwm_pal_configs_FTM2[0], UTIL_COUNTOF(pwm_pal_configs_FTM2)},
   {&pwm_pal_configs_FTM3[0], UTIL_COUNTOF(pwm_pal_configs_FTM3)},
};

pwm_config_instance_map_t Pwm_Instance_Map[4U] =
{
  {&pwm_pal_instances[0],  &pwm_pal_configs[0]},
  {&pwm_pal_instances[1],  &pwm_pal_configs[1]},
  {&pwm_pal_instances[2],  &pwm_pal_configs[2]},
  {&pwm_pal_instances[3],  &pwm_pal_configs[3]},
};

extern const Pwm_SpecificType Pwm_Config =
{
  UTIL_COUNTOF(Pwm_Instance_Map),
  (pwm_config_instance_map_t*)&Pwm_Instance_Map[0]
};

ftm_pwm_fault_param_t faultConfig =
{
	FALSE, /* Output pin state on fault */
	FALSE, /* PWM fault interrupt state */
	0U, /* Fault filter value */
	FTM_FAULT_CONTROL_DISABLED,  /* Fault mode */
	{
		{
			FALSE, /* Fault channel state (Enabled/Disabled) */
			FALSE, /* Fault channel filter state (Enabled/Disabled) */
			FTM_POLARITY_LOW, /* Fault channel state (Enabled/Disabled) */
		},
		{
			FALSE, /* Fault channel state (Enabled/Disabled) */
			FALSE, /* Fault channel filter state (Enabled/Disabled) */
			FTM_POLARITY_LOW, /* Fault channel state (Enabled/Disabled) */
		},
		{
			FALSE, /* Fault channel state (Enabled/Disabled) */
			FALSE, /* Fault channel filter state (Enabled/Disabled) */
			FTM_POLARITY_LOW, /* Fault channel state (Enabled/Disabled) */
		},
		{
			FALSE, /* Fault channel state (Enabled/Disabled) */
			FALSE, /* Fault channel filter state (Enabled/Disabled) */
			FTM_POLARITY_LOW, /* Fault channel state (Enabled/Disabled) */
		}
	}
};

//=============================================================================
// Module function declarations
//=============================================================================
extern void    Pwm_Init(const Pwm_ConfigType* ConfigPtr);
extern void    Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);
extern void    Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
extern uint16  Pwm_CalculateChannelHwDuty(uint16 unDuty, uint16 unFtmPeriod);
extern void    Pwm_SetChannelOutput(FTM_Type* sFtmBase, uint8 ucChannelIdx, tePwm_OutputState eLevel);
extern void    Pwm_StartPwmChannel(Pwm_ChannelType channelNumber);
extern void    Pwm_ClampPwmChannel(Pwm_ChannelType channelNumber, tePwm_OutputState level);
extern void    Pwm_GetFreq(Pwm_ChannelType ChannelNumber, uint16* freq);

extern status_t FTM_DRV_ControlChannelOutput(uint32_t instance, uint8_t channel, bool enableChannelOutput);
extern status_t FTM_DRV_FastUpdatePwmChannels(uint32_t instance, uint8_t numberOfChannels, const uint8_t * channels, const uint16_t * duty, bool softwareTrigger);
extern status_t FTM_DRV_UpdatePwmPeriod(uint32_t instance, ftm_pwm_update_option_t typeOfUpdate, uint32_t newValue, bool softwareTrigger);
extern status_t FTM_DRV_DeinitPwm(uint32_t instance);
extern status_t FTM_DRV_InitPwm(uint32_t instance, const ftm_pwm_param_t * param);
extern status_t FTM_DRV_InitPwmDutyCycleChannel(uint32_t instance, const ftm_pwm_param_t * param);
extern void     FTM_DRV_InitPwmCombinedChannel(uint32_t instance, const ftm_pwm_param_t * param);
extern void     FTM_DRV_InitPwmIndependentChannel(uint32_t instance, const ftm_pwm_param_t * param);

//=============================================================================
// Module function parameter stubs
//=============================================================================
Pwm_ConfigType*          Pwm_Init_Param1;
Pwm_ChannelType          Pwm_SetPeriodAndDuty_Param1;
Pwm_PeriodType           Pwm_SetPeriodAndDuty_Param2;
uint16                   Pwm_SetPeriodAndDuty_Param3;
Pwm_ChannelType          Pwm_SetDutyCycle_Param1;
uint16                   Pwm_SetDutyCycle_Param2;
uint16                   Pwm_CalculateChannelHwDuty_Param1;
uint16                   Pwm_CalculateChannelHwDuty_Param2;
FTM_Type                 Pwm_SetChannelOutput_Param1;
uint8                    Pwm_SetChannelOutput_Param2;
tePwm_OutputState        Pwm_SetChannelOutput_Param3;
Pwm_ChannelType          Pwm_StartPwmChannel_Param1;
Pwm_ChannelType          Pwm_ClampPwmChannel_Param1;
tePwm_OutputState        Pwm_ClampPwmChannel_Param2;
Pwm_ChannelType          Pwm_GetFreq_Param1;
uint16                   Pwm_GetFreq_Param2;

uint32_t                 FTM_DRV_ControlChannelOutput_Param1;
uint8_t                  FTM_DRV_ControlChannelOutput_Param2;
bool                     FTM_DRV_ControlChannelOutput_Param3;
uint32_t                 FTM_DRV_FastUpdatePwmChannels_Param1;
uint8_t                  FTM_DRV_FastUpdatePwmChannels_Param2;
uint8_t                  FTM_DRV_FastUpdatePwmChannels_Param3;
uint16_t                 FTM_DRV_FastUpdatePwmChannels_Param4;
bool                     FTM_DRV_FastUpdatePwmChannels_Param5;
uint32_t                 FTM_DRV_UpdatePwmPeriod_Param1;
ftm_pwm_update_option_t  FTM_DRV_UpdatePwmPeriod_Param2;
uint32_t                 FTM_DRV_UpdatePwmPeriod_Param3;
bool                     FTM_DRV_UpdatePwmPeriod_Param4;
uint32_t                 FTM_DRV_UpdatePwmChannel_Param1;
uint8_t                  FTM_DRV_UpdatePwmChannel_Param2;
ftm_pwm_update_option_t  FTM_DRV_UpdatePwmChannel_Param3;
uint16_t                 FTM_DRV_UpdatePwmChannel_Param4;
uint16_t                 FTM_DRV_UpdatePwmChannel_Param5;
bool                     FTM_DRV_UpdatePwmChannel_Param6;
uint32_t                 FTM_DRV_DeinitPwm_Param1;
uint32_t                 FTM_DRV_InitPwm_Param1;
ftm_pwm_param_t          FTM_DRV_InitPwm_Param2;
uint32_t                 FTM_DRV_InitPwmDutyCycleChannel_Param1;
ftm_pwm_param_t          FTM_DRV_InitPwmDutyCycleChannel_Param2;
uint32_t                 FTM_DRV_InitPwmCombinedChannel_Param1;
ftm_pwm_param_t          FTM_DRV_InitPwmCombinedChannel_Param2;
uint32_t                 FTM_DRV_InitPwmIndependentChannel_Param1;
ftm_pwm_param_t          FTM_DRV_InitPwmIndependentChannel_Param2;



//=============================================================================
// Module function return value stubs
//=============================================================================
uint16 Pwm_CalculateChannelHwDuty_RetVal;

status_t FTM_DRV_ControlChannelOutput_RetVal;
status_t FTM_DRV_FastUpdatePwmChannels_RetVal;
status_t FTM_DRV_UpdatePwmPeriod_RetVal;
status_t FTM_DRV_UpdatePwmChannel_RetVal;
status_t FTM_DRV_DeinitPwm_RetVal;
status_t FTM_DRV_InitPwm_RetVal;
status_t FTM_DRV_InitPwmDutyCycleChannel_RetVal;

//=============================================================================
// Module Global Stubs
//=============================================================================
ftm_state_t   ftmStatePtr1, ftmStatePtr2, ftmStatePtr3, ftmStatePtr4, ftmStatePtr5;
ftm_state_t * ftmStatePtr[5u] = { &ftmStatePtr1, &ftmStatePtr2, &ftmStatePtr3, &ftmStatePtr4, &ftmStatePtr5 };
FTM_Type   g_ftmBase1, g_ftmBase2, g_ftmBase3, g_ftmBase4, g_ftmBase5;
FTM_Type * g_ftmBase[5u] = { &g_ftmBase1 , &g_ftmBase2 , &g_ftmBase3 , &g_ftmBase4, &g_ftmBase5 };

#endif // TEST_2023_08_25_H_

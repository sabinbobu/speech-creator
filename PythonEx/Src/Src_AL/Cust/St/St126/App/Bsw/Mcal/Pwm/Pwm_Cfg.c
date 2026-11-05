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
/// \file  Pwm_Cfg.c
///
/// \brief  pwm configuration
///
/// \descr  configuration of Pwm
///
///
/// \author Alexandru Mertic (F98665C)
//-----------------------------------------------------------------------------

//=============================================================================
// Include
//=============================================================================

#include <Pwm.h>
#include <pwm_pal.h>
#include <UtilUtility.h>
#include <Cfg/Cfg.h>

STATIC_AL pwm_ftm_timebase_t pwm_pal_1_timebase0 = 
{
  // sourceClock, prescaler, deadtimePrescaler
  FTM_CLOCK_SOURCE_SYSTEMCLK, FTM_CLOCK_DIVID_BY_1, FTM_DEADTIME_DIVID_BY_1  // 80MHz for Boost sync
  
};
STATIC_AL pwm_ftm_timebase_t pwm_pal_1_timebase1 =
{
  FTM_CLOCK_SOURCE_SYSTEMCLK, FTM_CLOCK_DIVID_BY_8, FTM_DEADTIME_DIVID_BY_1 // 10MHz for Ledctrl
};

STATIC_AL pwm_ftm_timebase_t pwm_pal_1_timebase2 =
{
  FTM_CLOCK_SOURCE_SYSTEMCLK, FTM_CLOCK_DIVID_BY_128, FTM_DEADTIME_DIVID_BY_1 // 625kHz for ST
};

#define SHIFT_0    0U
#define SHIFT_30   300U
#define SHIFT_60   600U
#define SHIFT_90   900U
#define SHIFT_120  1200U
#define SHIFT_150  1500U
#define SHIFT_180  1800U
#define SHIFT_210  2100U
#define SHIFT_240  2400U
#define SHIFT_270  2700U
#define SHIFT_300  3000U
#define SHIFT_330  3300U
#define PWM_DUTY_0 1U


#define SHIFT_DEGREE_TO_CNT(clock_freq, period, shift) (((((clock_freq)/(period)))  * (shift)/3600U))
#define SHIFT_OFFSET(x) (uint32)( SHIFT_DEGREE_TO_CNT(10000000ULL, 400U, (x) ))

#ifdef LDMO_A0_SAMPLE
  #ifdef SAMPLE_FULL

/* channel, channelType, period, duty,  polarity, insertDeadtime*/
/*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
STATIC_AL pwm_channel_t pwm_pal_configs_FTM0[3U] =
{
  /* channel, channelType, period, duty,  polarity, insertDeadtime*/
  /*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
  {5, PWM_EDGE_ALIGNED, 25000U, PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_0) , PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_0) }, //LEDCTRL_7
  {6, PWM_EDGE_ALIGNED, 25000U, PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_0) , PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_0) }, //LEDCTRL_2
  {7, PWM_EDGE_ALIGNED, 25000U, PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_0) , PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_0) }, //LEDCTRL_1
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM1[4U] =
{
  {1, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_120)}, //LEDCTRL_6
  {5, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_120)}, //LEDCTRL_5
  {6, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_120)}, //LEDCTRL_4
  {7, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_120)}, //LEDCTRL_3
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM2[5U] =
{
  {0, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_240), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_240), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_240)}, //LEDCTRL_10
  {1, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_240), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_240), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_240)}, //LEDCTRL_9
  {2, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_240), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_240), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_240)}, //LEDCTRL_8
  {4, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_240), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_240), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_240)}, //LEDCTRL_12
  {5, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_240), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_240), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_240)}, //LEDCTRL_11
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM3[2U] =
{
  {5, PWM_EDGE_ALIGNED, 0U, 0U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //ST_STEP_AHL
  {4, PWM_EDGE_ALIGNED, 0U, 0U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //ST_STEP_LWR
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM4[1U] =
{
  {5, PWM_EDGE_ALIGNED, 100U, 50U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase0, 0}, //Boost Sync
};

// instType, instIdx
STATIC_AL pwm_instance_t pwm_pal_instances[5] =
{
    {PWM_INST_TYPE_FTM, 0},
    {PWM_INST_TYPE_FTM, 1},
    {PWM_INST_TYPE_FTM, 2},
    {PWM_INST_TYPE_FTM, 3},
    {PWM_INST_TYPE_FTM, 4},
};

// pwmChannels,  numberOfPwmChannels
STATIC_AL pwm_global_config_t pwm_pal_configs[5U] =
{
 {&pwm_pal_configs_FTM0[0], UTIL_COUNTOF(pwm_pal_configs_FTM0)},
 {&pwm_pal_configs_FTM1[0], UTIL_COUNTOF(pwm_pal_configs_FTM1)},
 {&pwm_pal_configs_FTM2[0], UTIL_COUNTOF(pwm_pal_configs_FTM2)},
 {&pwm_pal_configs_FTM3[0], UTIL_COUNTOF(pwm_pal_configs_FTM3)},
 {&pwm_pal_configs_FTM4[0], UTIL_COUNTOF(pwm_pal_configs_FTM4)},
};

// pwm instance mapping
STATIC_AL pwm_config_instance_map_t Pwm_Instance_Map[5U] =
{
  {&pwm_pal_instances[0],  &pwm_pal_configs[0]},
  {&pwm_pal_instances[1],  &pwm_pal_configs[1]},
  {&pwm_pal_instances[2],  &pwm_pal_configs[2]},
  {&pwm_pal_instances[3],  &pwm_pal_configs[3]},
  {&pwm_pal_instances[4],  &pwm_pal_configs[4]},
};

  #elif defined(SAMPLE_ECO)
STATIC_AL pwm_channel_t pwm_pal_configs_FTM0[2] =
{
  /* channel, channelType, period, duty,  polarity, insertDeadtime*/
  /*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
  {6, PWM_EDGE_ALIGNED, 25000U, PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_0), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_0)}, //LEDCTRL_2
  {7, PWM_EDGE_ALIGNED, 25000U, PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_0), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, SHIFT_OFFSET(SHIFT_0)}, //LEDCTRL_1
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM1[3] =
{
  {5, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //LEDCTRL_5
  {6, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //LEDCTRL_4
  {7, PWM_EDGE_ALIGNED, 25000U + SHIFT_OFFSET(SHIFT_120), PWM_DUTY_0 + SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //LEDCTRL_3
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM2[2] =
{
  {1, PWM_EDGE_ALIGNED, 100U, 50U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase0, 0}, //BOOST SYNC
  {4, PWM_EDGE_ALIGNED, 100U,  0U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase0, 0}, //DC_MOTOR
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM3[2] = 
{

};

// instType, instIdx
STATIC_AL pwm_instance_t pwm_pal_instances[4] =
{
    {PWM_INST_TYPE_FTM, 0},
    {PWM_INST_TYPE_FTM, 1},
    {PWM_INST_TYPE_FTM, 2},
    {PWM_INST_TYPE_FTM, 3},
};

// pwmChannels,  numberOfPwmChannels
STATIC_AL pwm_global_config_t pwm_pal_configs[4U] =
{
  {&pwm_pal_configs_FTM0[0], UTIL_COUNTOF(pwm_pal_configs_FTM0)},
  {&pwm_pal_configs_FTM1[0], UTIL_COUNTOF(pwm_pal_configs_FTM1)},
  {&pwm_pal_configs_FTM2[0], UTIL_COUNTOF(pwm_pal_configs_FTM2)},
  {&pwm_pal_configs_FTM3[0], UTIL_COUNTOF(pwm_pal_configs_FTM3)},
};

// pwm instance mapping
STATIC_AL pwm_config_instance_map_t Pwm_Instance_Map[4U] =
{
  {&pwm_pal_instances[0],  &pwm_pal_configs[0]},
  {&pwm_pal_instances[1],  &pwm_pal_configs[1]},
  {&pwm_pal_instances[2],  &pwm_pal_configs[2]},
  {&pwm_pal_instances[3],  &pwm_pal_configs[3]}
};

  #endif

#elif defined(LDMO_B0_SAMPLE)
  #ifdef SAMPLE_FULL

/* channel, channelType, period, duty,  polarity, insertDeadtime*/
/*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
STATIC_AL pwm_channel_t pwm_pal_configs_FTM0[1U] = {};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM1[4U] =
{
  /* channel, channelType, period, duty,  polarity, insertDeadtime*/
  /*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
  {0, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_0),  PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_1
  {2, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_30), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_2
  {5, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_60), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_3
  {7, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_90), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_4
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM2[4U] =
{
  {1, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_150), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_6
  {3, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_180), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_7
  {5, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_210), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_8
  {7, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_270), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_10
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM3[4U] =
{
  {1, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_240), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_9
  {2, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_300), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_11
  {5, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_5
  {6, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_330), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_12
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM4[1U] =
{
  {5, PWM_EDGE_ALIGNED, 0U, 0U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //ST_STEP_LWR
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM5[1U] =
{
  {1, PWM_EDGE_ALIGNED, 25000U,  SHIFT_OFFSET(SHIFT_0), PWM_ACTIVE_HIGH, false,
    0, false, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //HSS_EN_3 - fixed frequency of 400Hz
};

// instType, instIdx
STATIC_AL pwm_instance_t pwm_pal_instances[6U] =
{
    {PWM_INST_TYPE_FTM, 0},
    {PWM_INST_TYPE_FTM, 1},
    {PWM_INST_TYPE_FTM, 2},
    {PWM_INST_TYPE_FTM, 3},
    {PWM_INST_TYPE_FTM, 4},
    {PWM_INST_TYPE_FTM, 5},
};

// pwmChannels,  numberOfPwmChannels
STATIC_AL pwm_global_config_t pwm_pal_configs[6U] =
{
 {&pwm_pal_configs_FTM0[0], UTIL_COUNTOF(pwm_pal_configs_FTM0)},
 {&pwm_pal_configs_FTM1[0], UTIL_COUNTOF(pwm_pal_configs_FTM1)},
 {&pwm_pal_configs_FTM2[0], UTIL_COUNTOF(pwm_pal_configs_FTM2)},
 {&pwm_pal_configs_FTM3[0], UTIL_COUNTOF(pwm_pal_configs_FTM3)},
 {&pwm_pal_configs_FTM4[0], UTIL_COUNTOF(pwm_pal_configs_FTM4)},
 {&pwm_pal_configs_FTM5[0], UTIL_COUNTOF(pwm_pal_configs_FTM5)},
};

// pwm instance mapping
STATIC_AL pwm_config_instance_map_t Pwm_Instance_Map[6U] =
{
  {&pwm_pal_instances[0],  &pwm_pal_configs[0]},
  {&pwm_pal_instances[1],  &pwm_pal_configs[1]},
  {&pwm_pal_instances[2],  &pwm_pal_configs[2]},
  {&pwm_pal_instances[3],  &pwm_pal_configs[3]},
  {&pwm_pal_instances[4],  &pwm_pal_configs[4]},
  {&pwm_pal_instances[5],  &pwm_pal_configs[5]},
};

  #elif defined(SAMPLE_ECO)

STATIC_AL pwm_channel_t pwm_pal_configs_FTM0[1] ={};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM1[4] =
{
  /* channel, channelType, period, duty,  polarity, insertDeadtime*/
  /*deadtime,  enableComplementaryChannel, complementaryChannelPolarity, timebase*/
  {0, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_0),   PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_1
  {2, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_90),  PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_2
  {5, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_180), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_3
  {7, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_270), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0U}, //LEDCTRL_4
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM2[1] =
{
  {3, PWM_EDGE_ALIGNED, 20000U,  0U, PWM_ACTIVE_HIGH, false, 0, false, PWM_DUPLICATED, &pwm_pal_1_timebase0, 0}, //DC_MOTOR 80MHz period 20000 -> 4KHz
};

STATIC_AL pwm_channel_t pwm_pal_configs_FTM3[1] = 
{
  {5, PWM_EDGE_ALIGNED, 25000U, SHIFT_OFFSET(SHIFT_120), PWM_ACTIVE_HIGH, false,
    0, true, PWM_DUPLICATED, &pwm_pal_1_timebase1, 0}, //LEDCTRL_5
};

// instType, instIdx
STATIC_AL pwm_instance_t pwm_pal_instances[4U] =
{
    {PWM_INST_TYPE_FTM, 0},
    {PWM_INST_TYPE_FTM, 1},
    {PWM_INST_TYPE_FTM, 2},
    {PWM_INST_TYPE_FTM, 3},
};

// pwmChannels,  numberOfPwmChannels
STATIC_AL pwm_global_config_t pwm_pal_configs[4U] =
{
  {&pwm_pal_configs_FTM0[0], UTIL_COUNTOF(pwm_pal_configs_FTM0)},
  {&pwm_pal_configs_FTM1[0], UTIL_COUNTOF(pwm_pal_configs_FTM1)},
  {&pwm_pal_configs_FTM2[0], UTIL_COUNTOF(pwm_pal_configs_FTM2)},
  {&pwm_pal_configs_FTM3[0], UTIL_COUNTOF(pwm_pal_configs_FTM3)},
};

// pwm instance mapping
STATIC_AL pwm_config_instance_map_t Pwm_Instance_Map[4U] =
{
  {&pwm_pal_instances[0],  &pwm_pal_configs[0]},
  {&pwm_pal_instances[1],  &pwm_pal_configs[1]},
  {&pwm_pal_instances[2],  &pwm_pal_configs[2]},
  {&pwm_pal_instances[3],  &pwm_pal_configs[3]}
};

  #endif
#endif

const Pwm_SpecificType Pwm_Config =
{
  UTIL_COUNTOF(Pwm_Instance_Map),
  (pwm_config_instance_map_t*) &Pwm_Instance_Map[0]
};

/* DO NOT EVER CHANGE <CHANNEL> AND <FUNCTION> IN COMMENT */
/* OTHE ONLY MODIFICATIONS NEEDED ARE THE <INST MAP INDEX> AND <INSTANCE MAP CHANNEL>*/
pwm_channel_to_config_map_t pwm_channel_to_config_map_lut[PWM_NUM_OF_CHANNELS] =
{/* channel, inst map index, inst map chan, //function*/
#ifdef LDMO_A0_SAMPLE
  #ifdef SAMPLE_FULL
    { 0, 4, 0}, // Boost Sync
    { 1, 0, 2}, // LEDCTRL1
    { 2, 0, 1}, // LEDCTRL2
    { 3, 1, 3}, // LEDCTRL3
    { 4, 1, 2}, // LEDCTRL4
    { 5, 1, 1}, // LEDCTRL5
    { 6, 1, 0}, // LEDCTRL6
    { 7, 0, 0}, // LEDCTRL7
    { 8, 2, 2}, // LEDCTRL8
    { 9, 2, 1}, // LEDCTRL9
    {10, 2, 0}, // LEDCTRL10
    {11, 2, 4}, // LEDCTRL11
    {12, 2, 3}, // LEDCTRL12
    {13, 2, 1}, // DC_MOTOR
    {14, 3, 0}, // ST_AHL
    {15, 3, 1}, // ST_LWR
  #elif defined(SAMPLE_ECO)
    {0, 2, 0}, // Boost Sync
    {1, 0, 1}, // LEDCTRL1
    {2, 0, 0}, // LEDCTRL2
    {3, 1, 2}, // LEDCTRL3
    {4, 1, 1}, // LEDCTRL4
    {5, 1, 0}, // LEDCTRL5
    {6, 2, 1}, // DC_MOTOR
    {7, 3, 1}, // SENS_1_UC
    {8, 3, 0}, // SENS_2_UC
  #endif

#elif defined(LDMO_B0_SAMPLE)
  #ifdef SAMPLE_FULL
    { 0, 1, 0}, // LEDCTRL1
    { 1, 1, 1}, // LEDCTRL2
    { 2, 1, 2}, // LEDCTRL3
    { 3, 1, 3}, // LEDCTRL4
    { 4, 3, 2}, // LEDCTRL5
    { 5, 2, 0}, // LEDCTRL6
    { 6, 2, 1}, // LEDCTRL7
    { 7, 2, 2}, // LEDCTRL8
    { 8, 3, 0}, // LEDCTRL9
    { 9, 2, 3}, // LEDCTRL10
    {10, 3, 1}, // LEDCTRL11
    {11, 3, 3}, // LEDCTRL12
    {12, 4, 0}, // ST_LWR
    {13, 5, 0}, // HSS_EN_3
  #elif defined(SAMPLE_ECO)
    {0, 1, 0}, // LEDCTRL1
    {1, 1, 1}, // LEDCTRL2
    {2, 1, 2}, // LEDCTRL3
    {3, 1, 3}, // LEDCTRL4
    {4, 3, 0}, // LEDCTRL5
    {5, 2, 0}, // DC_MOTOR
  #endif
#endif
};


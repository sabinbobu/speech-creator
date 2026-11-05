#ifndef PWM_CFG_2020_11_17_H_
  #define PWM_CFG_2020_11_17_H_

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
/// \file  Pwm_Types.h
///
/// \brief PWM - Types
///
/// \descr Here are defined the specific Types used in the PWM module
///
/// \author Alexandru Mertic (F98665C)
///         mailTo:alexandru-laurentiu.mertic(at)magnetimarelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

  #include <Std_Types.h>
  #include <Cfg/Cfg.h>
  
  #if defined(__cplusplus)
  extern "C"
  {
  #endif

//=============================================================================
//  defines
//=============================================================================

  #define PWM_PERIOD_INVALID 0xFFFFU

  #ifdef LDMO_A0_SAMPLE
    #ifdef SAMPLE_FULL
      #define PWM_NUM_OF_CHANNELS 16U
    #elif defined(SAMPLE_ECO)
      #define PWM_NUM_OF_CHANNELS 9U
    #endif
  #elif defined (LDMO_B0_SAMPLE)
    #ifdef SAMPLE_FULL
      #define PWM_NUM_OF_CHANNELS 14U
    #elif defined(SAMPLE_ECO)
      #define PWM_NUM_OF_CHANNELS 6U
    #endif
  #endif

//=============================================================================
//  types
//=============================================================================

  typedef uint8 Pwm_ChannelHandleType;

  typedef struct pwm_config_instance_map_t
  {
    void* pwm_instance;
    void* pwm_global_config;
  } pwm_config_instance_map_t;

  typedef struct Pwm_SpecificType
  {
    uint8 ucCountOfPwmInstances;
    pwm_config_instance_map_t* Pwm_Cfg_atyCharacteristics;
  } Pwm_SpecificType;

  typedef struct pwm_channel_to_config_map_t
  {
    uint8 channel;
    uint8 instance_map_index;
    uint8 instance_map_chann;
  } pwm_channel_to_config_map_t;

  typedef enum
  {
    PWM_LOW = 0,
    PWM_HIGH
  }tePwm_OutputState;

//=============================================================================
//  variables
//=============================================================================

  extern pwm_channel_to_config_map_t pwm_channel_to_config_map_lut[PWM_NUM_OF_CHANNELS];
  

  #if defined(__cplusplus)
  }
  #endif

#endif /* PWM_CFG_2020_11_17_H_ */

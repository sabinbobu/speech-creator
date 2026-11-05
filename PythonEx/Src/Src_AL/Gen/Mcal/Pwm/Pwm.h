#ifndef PWM_2020_11_16_H_
  #define PWM_2020_11_16_H_

  #include <Std_Types.h>
  #include <AL_Helper.h>
  #include <Pwm_TargetTypes.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef Pwm_SpecificType Pwm_ConfigType;
  typedef uint32 Pwm_PeriodType;
  typedef uint32 Pwm_ChannelType;
 
 extern const Pwm_SpecificType Pwm_Config;

 void Pwm_Init(const Pwm_ConfigType* ConfigPtr);
 void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);
 void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
 void Pwm_StartPwmChannel(Pwm_ChannelType channelNumber);
 void Pwm_ClampPwmChannel(Pwm_ChannelType channelNumber, tePwm_OutputState level);
 void Pwm_GetFreq(Pwm_ChannelType ChannelNumber, uint16* freq);

  #if defined(__cplusplus)
  }
  #endif

#endif // PWM_2020_11_16_H_

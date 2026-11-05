#ifndef GPT_2019_02_07_H_
  #define GPT_2019_02_07_H_

  #include <Std_Types.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef uint8  Gpt_ConfigType;

  typedef uint32 Gpt_ValueType;
  typedef uint32 Gpt_ChannelType;

  extern const Gpt_ConfigType Gpt_ConfigData;

  void          Gpt_Init          (const Gpt_ConfigType* ConfigPtr);
  Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);
  
  #if defined(__cplusplus)
  }
  #endif

#endif // GPT_2019_02_07_H_

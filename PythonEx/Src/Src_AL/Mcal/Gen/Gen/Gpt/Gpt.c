#include <chrono>

#include <Gpt.h>

const  Gpt_ConfigType Gpt_ConfigData = (Gpt_ConfigType) 1U;

void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
  (void) ConfigPtr;

  return;
}

Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
  (void) Channel;

  return (Gpt_ValueType) 0U;
}

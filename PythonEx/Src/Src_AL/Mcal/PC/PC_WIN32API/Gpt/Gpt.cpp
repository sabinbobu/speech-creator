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
  static_cast<void>(Channel);

  using local_time_point_type =
    std::chrono::high_resolution_clock::time_point;

  static local_time_point_type Gpt_tyInitialTimePointNow =
    std::chrono::high_resolution_clock::now();

  const auto duration_now_in_microseconds =
    std::chrono::duration_cast<std::chrono::microseconds>
      (  std::chrono::high_resolution_clock::now()
       - Gpt_tyInitialTimePointNow);

  return static_cast<Gpt_ValueType>(duration_now_in_microseconds.count());
}

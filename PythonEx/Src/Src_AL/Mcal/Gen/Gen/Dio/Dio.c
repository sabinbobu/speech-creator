#include <Dio.h>

void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
  (void) ConfigPtr;

  return;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  (void) ChannelId;
  (void) Level;

  return;
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
  (void) ChannelId;

  return (Dio_LevelType) STD_LOW;
}

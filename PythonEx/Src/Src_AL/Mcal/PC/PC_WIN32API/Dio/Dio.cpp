#include <cstdint>
#include <iostream>

#include <Dio.h>

Dio_ChannelType Dio_WriteChannel_Param1;
Dio_LevelType Dio_WriteChannel_Param2;
Dio_ChannelType Dio_ReadChannel_Param1;
uint32 Dio_ReadChannel_HitCount;
Dio_LevelType Dio_ReadChannel_RetVal;
namespace
{
  std::uint32_t Dio_ulDioWriteCounter;
}

extern "C"
void Dio_Init(const Dio_ConfigType*)
{
}


void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{

  Dio_WriteChannel_Param1 = ChannelId;
  Dio_WriteChannel_Param2 = Level;

  //if(Level == STD_HIGH)
  //{
  //  std::cout << "PORT Dio_ChannelType ChannelId: " << ChannelId << " is high, ";
  //}

  //if(Level == STD_LOW)
  //{
  //  std::cout << "PORT Dio_ChannelType ChannelId: " << ChannelId << " is low,  ";
  //}

  //std::cout << "Dio_ulDioWriteCounter: " << Dio_ulDioWriteCounter << std::endl;

  //++Dio_ulDioWriteCounter;
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
  Dio_ReadChannel_Param1 = ChannelId;

  static_cast<void>(ChannelId);

  Dio_ReadChannel_HitCount++;
  return Dio_ReadChannel_RetVal;
}

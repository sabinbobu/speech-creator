#include <Dio.h>
#include <UtilUtility.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

/* PRQA S 303,306,316 EOF */

void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
  (void) ConfigPtr;

  return;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  (void) ChannelId;
  (void) Level;
  GPIO_Type* base;

  for (uint32 i = 0; i < UTIL_COUNTOF(Dio_ChannelMap); ++i)
  {
    if (ChannelId == Dio_ChannelMap[i].ChannelId)
    {
      base = (GPIO_Type*) Dio_ChannelMap[i].PortBase;
      if (Level == STD_HIGH)
      {
        base->PSOR |= (uint32)(1UL << Dio_ChannelMap[i].Pin);
      }
      else
      {
        base->PCOR |= (uint32)(1UL << Dio_ChannelMap[i].Pin);
      }
      break;
    }
  }
  

  return;
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
  GPIO_Type* base;
  Dio_LevelType level = STD_LOW;

  for (uint32 i = 0; i < UTIL_COUNTOF(Dio_ChannelMap); ++i)
  {
    if (ChannelId == Dio_ChannelMap[i].ChannelId)
    {
      base = (GPIO_Type*) Dio_ChannelMap[i].PortBase;
      level = ((Dio_LevelType)((base->PDIR >> Dio_ChannelMap[i].Pin) & 0x01u) == 0U) ? STD_LOW : STD_HIGH;
      break;
    }
  }
  return level;
}

#include <algorithm>

#include <Mcu.h>

namespace
{
  bool& Mcu_InitHasBeenCalled()
  {
    static bool boMcu_InitHasBeenCalled;

    return boMcu_InitHasBeenCalled;
  }
}

const Mcu_ConfigType Mcu_ConfigData = (Mcu_ConfigType) 0U;



void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
  (void)ConfigPtr;

  Mcu_InitHasBeenCalled() = true;
}

Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
  static_cast<void>(ClockSetting);

  return E_NOT_OK;
}

Std_ReturnType Mcu_DistributePllClock(void)
{
  return E_NOT_OK;
}

Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
  return E_OK;
}

Mcu_ResetType Mcu_GetResetReason()
{
  return (Mcu_InitHasBeenCalled() ? MCU_POWER_ON_RESET : MCU_RESET_UNDEFINED);
}

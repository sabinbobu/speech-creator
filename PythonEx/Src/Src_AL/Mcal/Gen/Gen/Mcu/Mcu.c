#include <Mcu.h>

const Mcu_ConfigType Mcu_ConfigData = (Mcu_ConfigType) 0U;

static boolean Mcu_boInitHasBeenCalled = (boolean) FALSE;

void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
  (void) ConfigPtr;

  return;

  Mcu_boInitHasBeenCalled = (boolean) TRUE;
}

Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
  (void) ClockSetting;

  return (Std_ReturnType) E_NOT_OK;
}

Std_ReturnType Mcu_DistributePllClock(void)
{
  return (Std_ReturnType) E_NOT_OK;
}

Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
  const uint32 RamSectionTop =
    RamSection.McuRamSectionBaseAddress + RamSection.McuRamSectionSize;

  for(uint32 ulRamAddr = RamSection.McuRamSectionBaseAddress; ulRamAddr < RamSectionTop; ++ulRamAddr)
  {
    *(uint8*) ulRamAddr = RamSection.McuRamDefaultValue;
  }

  return E_OK;
}

Mcu_ResetType Mcu_GetResetReason(void)
{
  return ((Mcu_boInitHasBeenCalled != (boolean) FALSE)
           ? MCU_POWER_ON_RESET
           : MCU_RESET_UNDEFINED);
}

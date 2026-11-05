#ifndef MCU_2019_02_07_H_
  #define MCU_2019_02_07_H_

  #include <Std_Types.h>
  #include <Mcu_TargetTypes.h>

#ifdef UNIT_TEST
#include <../../Mcal/PC/PC_WIN32API/Mcu/Device_TargetTypes.h>
#endif
  
  #if defined(__cplusplus)
  extern "C"
  {
  #endif
  #if defined (CPU_S32K142)
    #define NUM_OF_PERIPHERAL_CLOCKS_0                         23U /* Count of peripheral clock user configurations. */
  #elif defined (CPU_S32K144) || defined (UNIT_TEST)
    #define NUM_OF_PERIPHERAL_CLOCKS_0                         23U /* Count of peripheral clock user configurations. */
  #elif defined (CPU_S32K146) || defined (UNIT_TEST)
    #define NUM_OF_PERIPHERAL_CLOCKS_0                         26U /* Count of peripheral clock user configurations. */
  #endif

  #define CLOCK_MANAGER_CALLBACK_CNT                         0U /*!< Count of user Callbacks */
  #define CLOCK_MANAGER_CONFIG_CNT                           1U /*!< Count of user configuration */
  #define RCM_SRS_CMU_LOC_MASK                               0x10u


  typedef uint32 Mcu_ConfigType;
  typedef const Mcu_ClockSpecificType Mcu_ClockType;
  typedef uint32 Mcu_RamSectionType;

  extern const Mcu_ConfigType Mcu_ConfigData;
  extern const Mcu_ClockType  Mcu_ClockData;

  void           Mcu_Init              (const Mcu_ConfigType* ConfigPtr);
  Std_ReturnType Mcu_InitClock         (Mcu_ClockType* ClockSetting);
  Std_ReturnType Mcu_DistributePllClock(void);
  Mcu_ResetType  Mcu_GetResetReason    (void);
  void           Mcu_PerformReset      (void);
  #if defined(__cplusplus)
  }
  #endif

#endif // MCU_2019_02_07_H_

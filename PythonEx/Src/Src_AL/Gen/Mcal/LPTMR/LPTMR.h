#ifndef LPTMR_2021_09_03_H_
  #define LPTMR_2021_09_03_H_

  #include <Std_Types.h>
  #include <AL_Helper.h>
  #include <LPTMR_TargetTypes.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif
  typedef LPTMR_SpecificType LPTMR_ConfigType;

#ifdef UNIT_TEST
  #define false 0
  #define true  1
  typedef unsigned int       uint32_t;
  typedef unsigned short     uint16_t;
  #define bool  boolean

  typedef enum {
    LPTMR_PRESCALE_2 = 0x00u, /*!< Timer mode: prescaler 2, Glitch filter mode: invalid */
    LPTMR_PRESCALE_4_GLITCHFILTER_2 = 0x01u, /*!< Timer mode: prescaler 4, Glitch filter mode: 2 clocks */
    LPTMR_PRESCALE_8_GLITCHFILTER_4 = 0x02u, /*!< Timer mode: prescaler 8, Glitch filter mode: 4 clocks */
    LPTMR_PRESCALE_16_GLITCHFILTER_8 = 0x03u, /*!< Timer mode: prescaler 16, Glitch filter mode: 8 clocks */
    LPTMR_PRESCALE_32_GLITCHFILTER_16 = 0x04u, /*!< Timer mode: prescaler 32, Glitch filter mode: 16 clocks */
    LPTMR_PRESCALE_64_GLITCHFILTER_32 = 0x05u, /*!< Timer mode: prescaler 64, Glitch filter mode: 32 clocks */
    LPTMR_PRESCALE_128_GLITCHFILTER_64 = 0x06u, /*!< Timer mode: prescaler 128, Glitch filter mode: 64 clocks */
    LPTMR_PRESCALE_256_GLITCHFILTER_128 = 0x07u, /*!< Timer mode: prescaler 256, Glitch filter mode: 128 clocks */
    LPTMR_PRESCALE_512_GLITCHFILTER_256 = 0x08u, /*!< Timer mode: prescaler 512, Glitch filter mode: 256 clocks */
    LPTMR_PRESCALE_1024_GLITCHFILTER_512 = 0x09u, /*!< Timer mode: prescaler 1024, Glitch filter mode: 512 clocks */
    LPTMR_PRESCALE_2048_GLITCHFILTER_1024 = 0x0Au, /*!< Timer mode: prescaler 2048, Glitch filter mode: 1024 clocks */
    LPTMR_PRESCALE_4096_GLITCHFILTER_2048 = 0x0Bu, /*!< Timer mode: prescaler 4096, Glitch filter mode: 2048 clocks */
    LPTMR_PRESCALE_8192_GLITCHFILTER_4096 = 0x0Cu, /*!< Timer mode: prescaler 8192, Glitch filter mode: 4096 clocks */
    LPTMR_PRESCALE_16384_GLITCHFILTER_8192 = 0x0Du, /*!< Timer mode: prescaler 16384, Glitch filter mode: 8192 clocks */
    LPTMR_PRESCALE_32768_GLITCHFILTER_16384 = 0x0Eu, /*!< Timer mode: prescaler 32768, Glitch filter mode: 16384 clocks */
    LPTMR_PRESCALE_65536_GLITCHFILTER_32768 = 0x0Fu  /*!< Timer mode: prescaler 65536, Glitch filter mode: 32768 clocks */
  } lptmr_prescaler_t;

  typedef enum {
    LPTMR_CLOCKSOURCE_SIRCDIV2 = 0x00u, /*!< SIRC clock */
    LPTMR_CLOCKSOURCE_1KHZ_LPO = 0x01u, /*!< 1kHz LPO clock */
    LPTMR_CLOCKSOURCE_RTC = 0x02u, /*!< RTC clock */
    LPTMR_CLOCKSOURCE_PCC = 0x03u  /*!< PCC configured clock */
  } lptmr_clocksource_t;

  typedef enum {
    LPTMR_WORKMODE_TIMER = 0u, /*!< Timer */
    LPTMR_WORKMODE_PULSECOUNTER = 1u  /*!< Pulse counter */
  } lptmr_workmode_t;

  typedef enum
  {
    LPTMR_COUNTER_UNITS_TICKS = 0x00U,
    LPTMR_COUNTER_UNITS_MICROSECONDS = 0x01U
  } lptmr_counter_units_t;

  typedef enum {
    LPTMR_PINSELECT_TRGMUX = 0x00u, /*!< Count pulses from TRGMUX trigger */
#if FEATURE_LPTMR_HAS_INPUT_ALT1_SELECTION
    LPTMR_PINSELECT_ALT1 = 0x01u, /*!< Count pulses from pin alternative 1 */
#endif
    LPTMR_PINSELECT_ALT2 = 0x02u, /*!< Count pulses from pin alternative 2 */
    LPTMR_PINSELECT_ALT3 = 0x03u  /*!< Count pulses from pin alternative 3 */
  } lptmr_pinselect_t;

  typedef enum {
    LPTMR_PINPOLARITY_RISING = 0u, /*!< Count pulse on rising edge */
    LPTMR_PINPOLARITY_FALLING = 1u  /*!< Count pulse on falling edge */
  } lptmr_pinpolarity_t;

  typedef struct
  {
    /* General parameters */
    boolean dmaRequest;                    /*!< Enable/Disable DMA requests */
    boolean interruptEnable;               /*!< Enable/Disable Interrupt */
    boolean freeRun;                       /*!< Enable/Disable Free Running Mode */
    lptmr_workmode_t workMode;          /*!< Time/Pulse Counter Mode */
    /* Counter parameters */
    lptmr_clocksource_t clockSelect;    /*!< Clock selection for Timer/Glitch filter */
    lptmr_prescaler_t prescaler;        /*!< Prescaler Selection */
    boolean bypassPrescaler;               /*!< Enable/Disable prescaler bypass */
    uint32 compareValue;              /*!< Compare value */
    lptmr_counter_units_t counterUnits; /*!< Compare value units */
    /* Pulse Counter specific parameters */
    lptmr_pinselect_t pinSelect;        /*!< Pin selection for Pulse-Counter */
    lptmr_pinpolarity_t pinPolarity;    /*!< Pin Polarity for Pulse-Counter */
  } lptmr_config_t;
#endif


  extern const LPTMR_SpecificType LPTMR_Config;

  void LPTMR_INIT(const LPTMR_ConfigType* ConfigPtr);
  boolean LPTMR_Check_Config(void);
  void LPTMR0_IRQHandler(void);
  uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue);

  #if defined(__cplusplus)
  }
  #endif
#endif // LPTMR_2021_09_03_H_

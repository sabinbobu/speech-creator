#include <Mcu.h>
#include <UtilUtility.h>
#include <Cfg/Cfg.h>
#ifndef UNIT_TEST
#include <clock_S32K1xx.h>
#endif

/*! [at]brief peripheral clock configuration 0 */
static peripheral_clock_config_t peripheralClockConfig0[NUM_OF_PERIPHERAL_CLOCKS_0] = {
    {
        .clockName = ADC0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SPLL_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = ADC1_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SPLL_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = LPSPI0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = LPSPI1_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = LPUART1_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = LPIT0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = LPTMR0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FTM0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV1,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FTM1_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV1,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FTM2_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV1,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FTM3_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV1,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
#if defined (CPU_S32K146)
    {
        .clockName = FTM4_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV1,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FTM5_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV1,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = LPUART2_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_SOSC_DIV2,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
#endif
    {
        .clockName = CRC0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = DMAMUX0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FTFC0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PDB0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PDB1_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = RTC0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = FlexCAN0_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PORTA_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PORTB_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PORTC_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PORTD_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
    {
        .clockName = PORTE_CLK,
        .clkGate = true,
        .clkSrc = CLK_SRC_OFF,
        .frac = MULTIPLY_BY_ONE,
        .divider = DIVIDE_BY_ONE,
    },
};
/* *************************************************************************
* Configuration structure for Clock Configuration 0
* ************************************************************************* */
/*! /brief User Configuration structure clock_managerCfg_0 */
static clock_manager_user_config_t clockMan1_InitConfig0 = {
    .scgConfig =
    {
        .sircConfig =
        {
            .range = SCG_SIRC_RANGE_HIGH,         /* Slow IRC high range clock (8 MHz) */  
            .div1 = SCG_ASYNC_CLOCK_DISABLE,      /* Slow IRC Clock Divider 1: Clock output is disabled */
            .div2 = SCG_ASYNC_CLOCK_DISABLE,      /* Slow IRC Clock Divider 3: Clock output is disabled */
            .initialize = true,
            .enableInStop = true,                 /* Enable SIRC in stop mode */
            .enableInLowPower = true,             /* Enable SIRC in low power mode */
            .locked = false,                      /* unlocked */
        },
        .fircConfig =
        {
            .range = SCG_FIRC_RANGE_48M,           /*!< RANGE      */
            .div1 = SCG_ASYNC_CLOCK_DISABLE,      /* Fast IRC Clock Divider 1: Clock output is disabled */
            .div2 = SCG_ASYNC_CLOCK_DISABLE,      /* Fast IRC Clock Divider 3: Clock output is disabled */ 
            .regulator = true,                    /* FIRC regulator is enabled */
            .locked = false,                      /* unlocked */
            .initialize = true,
        },   
        .soscConfig =
        {
            .freq = 16000000U,                    /* System Oscillator frequency: 16000000Hz */
            .monitorMode = SCG_SOSC_MONITOR_RESET,/* Monitor generates reset */
            .extRef = SCG_SOSC_REF_OSC,           /* Internal oscillator of OSC requested. */
            .gain = SCG_SOSC_GAIN_LOW,            /* Configure crystal oscillator for low-gain operation */
            .range = SCG_SOSC_RANGE_HIGH,         /* High frequency range selected for the crystal oscillator of 8 MHz to 40 MHz. */
            .div1 = SCG_ASYNC_CLOCK_DIV_BY_4,     /* System OSC Clock Divider 1: divided by 4 */
            .div2 = SCG_ASYNC_CLOCK_DIV_BY_1,     /* System OSC Clock Divider 3: divided by 1 */       
            .locked = false,                      /* SOSC disabled */
            .initialize = true,
        }, 
        .spllConfig =
        {
            .monitorMode = SCG_SPLL_MONITOR_RESET,/* Monitor generates reset */
            .prediv = (uint8_t)SCG_SPLL_CLOCK_PREDIV_BY_1,/* Divided by 1 */
            .mult = (uint8_t)SCG_SPLL_CLOCK_MULTIPLY_BY_20,/* Multiply Factor is 20 */
            .src = 0U,
            .div1 = SCG_ASYNC_CLOCK_DISABLE,      /* System PLL Clock Divider 1: Clock output is disabled */
            .div2 = SCG_ASYNC_CLOCK_DIV_BY_4,     /* System PLL Clock Divider 3: divided by 4 */         
            .locked = false,                      /* unlocked */
            .initialize = true,
        },
        .rtcConfig =
        {
            .initialize = false,
        },
        .clockOutConfig =
        {
            .source = SCG_CLOCKOUT_SRC_SIRC,      /* Slow IRC. */
            .initialize = true,
        },
        .clockModeConfig =
        {
            .rccrConfig =
            {  
                .divSlow = SCG_SYSTEM_CLOCK_DIV_BY_3,/* Slow Clock Divider: divided by 3 */
                .divBus = SCG_SYSTEM_CLOCK_DIV_BY_2,/* Bus Clock Divider: divided by 2 */
                .divCore = SCG_SYSTEM_CLOCK_DIV_BY_2,/* Core Clock Divider: divided by 2 */
                .src = SCG_SYSTEM_CLOCK_SRC_SYS_PLL,/* System PLL */

            },
            .vccrConfig =
            {
                .divSlow = SCG_SYSTEM_CLOCK_DIV_BY_4,/* Slow Clock Divider: divided by 4 */
                .divBus = SCG_SYSTEM_CLOCK_DIV_BY_2,/* Bus Clock Divider: divided by 2 */
                .divCore = SCG_SYSTEM_CLOCK_DIV_BY_2,/* Core Clock Divider: divided by 2 */
                .src = SCG_SYSTEM_CLOCK_SRC_SIRC, /* Slow IRC */
            },
            .hccrConfig =
            {
                .divSlow = SCG_SYSTEM_CLOCK_DIV_BY_3,/* Slow Clock Divider: divided by 3 */
                .divBus = SCG_SYSTEM_CLOCK_DIV_BY_2,/* Bus Clock Divider: divided by 2 */
                .divCore = SCG_SYSTEM_CLOCK_DIV_BY_2,/* Core Clock Divider: divided by 2 */
                .src = SCG_SYSTEM_CLOCK_SRC_SYS_PLL,/* System PLL */
            },
            .initialize = true,
        },
    },
    .simConfig =
    {
        .clockOutConfig =
        {
            .initialize = true, /*!< Initialize    */
            .enable = true,                       /* enabled */
            .source = SIM_CLKOUT_SEL_SYSTEM_RTC_CLK,/* RTC CLK as selected by SIM CLK 32 KHz Select */
            .divider = SIM_CLKOUT_DIV_BY_5,       /* Divided by 5 */
        },
        .lpoClockConfig =
        {
            .initialize = true, /*!< Initialize    */
            .sourceRtcClk = SIM_RTCCLK_SEL_SOSCDIV1_CLK,/* SOSCDIV1 clock */
            .sourceLpoClk = SIM_LPO_CLK_SEL_LPO_128K,/* 128 kHz LPO clock */
            .enableLpo32k = true, /*!< LPO32KCLKEN   */
            .enableLpo1k = true, /*!< LPO1KCLKEN    */
        },
        .tclkConfig =
        {
            .initialize = false, /*!< Initialize    */
        },
        .platGateConfig =
        {
            .initialize = true, /*!< Initialize    */
            .enableMscm = true, /*!< CGCMSCM       */
            .enableMpu = true, /*!< CGCMPU        */
            .enableDma = true, /*!< CGCDMA        */
            .enableErm = true, /*!< CGCERM        */
            .enableEim = true, /*!< CGCEIM        */
        },
        .traceClockConfig =
        {
            .initialize = true, /*!< Initialize    */
            .divEnable = true, /*!< TRACEDIVEN    */
            .source = CLOCK_TRACE_SRC_CORE_CLK, /*!< TRACECLK_SEL  */
            .divider = 0U, /*!< TRACEDIV      */
            .divFraction = false, /*!< TRACEFRAC     */
        },
    },
    .pccConfig =
    {
        .count = NUM_OF_PERIPHERAL_CLOCKS_0, /*!< Number of the peripheral clock control configurations  */
        .peripheralClocks = peripheralClockConfig0, /*!< Peripheral clock control configurations  */
    },
    .pmcConfig =
    {
        .lpoClockConfig =
        {
        .initialize = true,  /*!< Initialize    */
        .enable = true, /*!< Enable/disable LPO     */
        .trimValue = 0, /*!< Trimming value for LPO */
        },
    },
};


/*! /brief Array of pointers to User configuration structures */
static clock_manager_user_config_t const * g_clockManConfigsArr[] = {
  &clockMan1_InitConfig0
};

/*! /brief Array of pointers to User defined Callbacks configuration structures */
/* The tool do not support generate Callbacks configuration. It's always empty. */
static clock_manager_callback_user_config_t * g_clockManCallbacksArr[] = { NULL_PTR };

const Mcu_ClockSpecificType Mcu_ClockData =
{
  (void**)g_clockManConfigsArr,  // PRQA S 310, 311 // Necessary cast to avoid using ThirdParty structures
  (void**)g_clockManCallbacksArr // PRQA S 310 // Necessary cast to avoid using ThirdParty structures
};


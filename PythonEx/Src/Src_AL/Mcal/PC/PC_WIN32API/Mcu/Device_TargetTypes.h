//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Device_TargetTypes.h
///
/// \brief  Peripheral Access Layer for S32K14X
//
//   This file contains register definitions and macros for easy access to their
//   bit fields.
///
//-----------------------------------------------------------------------------
#ifndef DEVICE_TARGET_TYPES_2023_10_11_H
#define DEVICE_TARGET_TYPES_2023_10_11_H

//=============================================================================
// Target Device File ( S32K 14X family )
//=============================================================================


//=============================================================================
// Includes
//=============================================================================


//=============================================================================
// Definitions
//=============================================================================

typedef signed char             int8_t;
typedef unsigned int            uint32_t;
typedef unsigned short          uint16_t;
typedef unsigned char           uint8_t;
typedef volatile unsigned long  vuint32;
typedef uint8_t                 AppModeType;

#define     __IO    volatile        /*!< Defines 'read / write' permissions */
#define     __I     volatile        /*!< Defines 'read only' permissions */

#define     bool  boolean
#define     false 0
#define     true  1
#define     NULL    ((void *)0)


/* ----------------------------------------------------------------------------
   -- STATUS TYPES
   ---------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
   // @brief Status return codes.
   // Common error codes will be a unified enumeration (C enum) that will contain all error codes
   // (common and specific). There will be separate "error values spaces" (or slots), each of 256
   // positions, allocated per functionality.
  ---------------------------------------------------------------------------- */
typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS                         = 0x000U,    /*!< Generic operation success status */
    STATUS_ERROR                           = 0x001U,    /*!< Generic operation failure status */
    STATUS_BUSY                            = 0x002U,    /*!< Generic operation busy status */
    STATUS_TIMEOUT                         = 0x003U,    /*!< Generic operation timeout status */
    STATUS_UNSUPPORTED                     = 0x004U,    /*!< Generic operation unsupported status */
    /* MCU specific error codes */
    STATUS_MCU_GATED_OFF                   = 0x100U,  /*!< Module is gated off */
    STATUS_MCU_TRANSITION_FAILED           = 0x101U,  /*!< Error occurs during transition. */
    STATUS_MCU_INVALID_STATE               = 0x102U,  /*!< Unsupported in current state. */
    STATUS_MCU_NOTIFY_BEFORE_ERROR         = 0x103U,  /*!< Error occurs during send "BEFORE" notification. */
    STATUS_MCU_NOTIFY_AFTER_ERROR          = 0x104U,  /*!< Error occurs during send "AFTER" notification. */
    /* I2C specific error codes */
    STATUS_I2C_RECEIVED_NACK               = 0x200U,  /*!< NACK signal received  */
    STATUS_I2C_TX_UNDERRUN                 = 0x201U,  /*!< TX underrun error */
    STATUS_I2C_RX_OVERRUN                  = 0x202U,  /*!< RX overrun error */
    STATUS_I2C_ARBITRATION_LOST            = 0x203U,  /*!< Arbitration lost */
    STATUS_I2C_ABORTED                     = 0x204U,  /*!< A transfer was aborted */
    STATUS_I2C_BUS_BUSY                    = 0x205U,  /*!< I2C bus is busy, cannot start transfer */
    /* CAN specific error codes */
    STATUS_CAN_BUFF_OUT_OF_RANGE           = 0x300U,  /*!< The specified MB index is out of the configurable range */
    STATUS_CAN_NO_TRANSFER_IN_PROGRESS     = 0x301U,  /*!< There is no transmission or reception in progress */
    /* Security specific error codes */
    STATUS_SEC_SEQUENCE_ERROR              = 0x402U,  /*!< The sequence of commands or subcommands is out of
                                                            sequence */
    STATUS_SEC_KEY_NOT_AVAILABLE           = 0x403U,  /*!< A key is locked due to failed boot measurement or
                                                            an active debugger */
    STATUS_SEC_KEY_INVALID                 = 0x404U,  /*!< A function is called to perform an operation with
                                                            a key that is not allowed for the given operation */
    STATUS_SEC_KEY_EMPTY                   = 0x405U,  /*!< Attempt to use a key that has not been initialized yet */
    STATUS_SEC_NO_SECURE_BOOT              = 0x406U,  /*!< The conditions for a secure boot process are not met */
    STATUS_SEC_KEY_WRITE_PROTECTED         = 0x407U,  /*!< Request for updating a write protected key slot,
                                                            or activating debugger with write protected key(s) */
    STATUS_SEC_KEY_UPDATE_ERROR            = 0x408U,  /*!< Key update did not succeed due to errors in
                                                            verification of the messages */
    STATUS_SEC_RNG_SEED                    = 0x409U,  /*!< Returned by CMD_RND and CMD_DEBUG if the seed has not
                                                            been initialized before */
    STATUS_SEC_NO_DEBUGGING                = 0x40AU,  /*!< DEBUG command authentication failed */
    STATUS_SEC_MEMORY_FAILURE              = 0x40CU,  /*!< General memory technology failure
                                                            (multibit ECC error, common fault detected) */
    STATUS_SEC_HSM_INTERNAL_MEMORY_ERROR   = 0x410U,  /*!< An internal memory error encountered while
                                                           executing the command */
    STATUS_SEC_INVALID_COMMAND             = 0x411U,  /*!< Command value out of range */
    STATUS_SEC_TRNG_ERROR                  = 0x412U,  /*!< One or more statistical tests run on the TRNG output failed */
    STATUS_SEC_HSM_FLASH_BLOCK_ERROR       = 0x413U,  /*!< Error reading, programming or erasing one of the HSM flash blocks */
    STATUS_SEC_INTERNAL_CMD_ERROR          = 0x414U,  /*!< An internal command processor error while executing a command */
    STATUS_SEC_MAC_LENGTH_ERROR            = 0x415U,  /*!< MAC/Message length out of range */
    STATUS_SEC_INVALID_ARG                 = 0x421U,  /*!< Invalid command argument */
    STATUS_SEC_TRNG_CLOCK_ERROR            = 0x423U,  /*!< TRNG not provided with a stable clock */
    /* SPI specific error codes */
    STATUS_SPI_TX_UNDERRUN                 = 0x500U,  /*!< TX underrun error */
    STATUS_SPI_RX_OVERRUN                  = 0x501U,  /*!< RX overrun error */
    STATUS_SPI_ABORTED                     = 0x502U,  /*!< A transfer was aborted */
    /* UART specific error codes */
    STATUS_UART_TX_UNDERRUN                = 0x600U,  /*!< TX underrun error */
    STATUS_UART_RX_OVERRUN                 = 0x601U,  /*!< RX overrun error */
    STATUS_UART_ABORTED                    = 0x602U,  /*!< A transfer was aborted */
    /* I2S specific error codes */
    STATUS_I2S_TX_UNDERRUN                 = 0x700U,  /*!< TX underrun error */
    STATUS_I2S_RX_OVERRUN                  = 0x701U,  /*!< RX overrun error */
    STATUS_I2S_ABORTED                     = 0x702U,  /*!< A transfer was aborted */
    /* SBC specific error codes */
    SBC_NVN_ERROR                          = 0x800U, /*!< Unsuccessful attempt writing to non volatile memory
                                                          (0x73 and 0x74). Set device to factory settings. */
    SBC_COMM_ERROR                         = 0x801U, /*!< Data transfer was aborted */
    SBC_CMD_ERROR                          = 0x802U, /*!< Wrong command. */
    SBC_ERR_NA                             = 0x803U, /*!< Feature/device not available */
    SBC_MTPNV_LOCKED                       = 0x804U, /*!< Unable to write MTPNV cells, NVMPS = 0 */

    /* FLASH specific error codes */
    STATUS_FLASH_ERROR_ENABLE              = 0x901U, /*!< It's impossible to enable an operation */
    STATUS_FLASH_ERROR_NO_BLOCK            = 0x902U, /*!< No blocks have been enabled for Array Integrity check */
    STATUS_FLASH_INPROGRESS                = 0x903U, /*!< InProgress status */

    /* SAI specific error codes */
    STATUS_SAI_ABORTED                     = 0xA00U, /*!< SAI aborted status */

    /* ENET specific error codes */
    STATUS_ENET_RX_QUEUE_EMPTY             = 0xA01U, /*!< There is no available frame in the receive queue */
    STATUS_ENET_TX_QUEUE_FULL              = 0xA02U, /*!< There is no available space for the frame in the transmit queue */
    STATUS_ENET_BUFF_NOT_FOUND             = 0xA03U, /*!< The specified buffer was not found in the queue */

    /* FCCU specific error codes */
    STATUS_FCCU_ERROR_CONFIG_TIMEOUT       = 0xB01U, /*!< FCCU triggers TimeOut when try to enter in Config State */
    STATUS_FCCU_ERROR_INIT_FCCU            = 0xB02U, /*!< FCCU Initializing FCCU Module */
    STATUS_FCCU_ERROR_SET_CONFIG           = 0xB03U, /*!< FCCU Fail to Enter in Config Mode  */
    STATUS_FCCU_ERROR_SET_NORMAL           = 0xB04U, /*!< FCCU Fail to Enter in Normal Mode  */
    STATUS_FCCU_ERROR_APPLY_NCF_CONFIG     = 0xB05U, /*!< FCCU Fail to set NoCritical Faults  */
    STATUS_FCCU_ERROR_UPDATE_FREEZE        = 0xB06U, /*!< FCCU Fail to update Freez Status registers */
    STATUS_FCCU_ERROR_CLEAR_FREEZE         = 0xB07U, /*!< FCCU Fail to Clear Freez Status registers */
    STATUS_FCCU_ERROR_SET_EOUT             = 0xB08U, /*!< FCCU Fail to Set Eout Configuration */
    STATUS_FCCU_ERROR_FAULT_DETECTED       = 0xB09U, /*!< FCCU Faults Detected */
    STATUS_FCCU_ERROR_OTHER                = 0xB0AU, /*!< FCCU other Error */

    /* EMIOS specific error codes */
    STATUS_EMIOS_WRONG_MODE                = 0xC00U,   /*!< EMIOS unsuccessful attempt selecting wrong mode. */
    STATUS_EMIOS_CNT_BUS_OVERFLOW          = 0xC01U,   /*!< EMIOS counter bus overflow. */
    STATUS_EMIOS_WRONG_CNT_BUS             = 0xC02U,   /*!< EMIOS unsuccessful attempt selecting wrong counter bus. */
    STATUS_EMIOS_ENABLE_GLOBAL_FRZ         = 0xC03U,   /*!< EMIOS must set global allow enter debug mode first. */

    /* EEE specific error codes */
    STATUS_EEE_ERROR_NO_ENOUGH_SPACE       = 0xD00U, /*!< The data is too big to fit in any of the block */
    STATUS_EEE_ERROR_NO_ENOUGH_BLOCK       = 0xD01U, /*!< The block numbers is not enough for round robin */
    STATUS_EEE_ERROR_DATA_NOT_FOUND        = 0xD02U, /*!< The required data is not found in the EEPROM emulation */
    STATUS_EEE_ERROR_NOT_IN_CACHE          = 0xD03U, /*!< The required data is not in the cache table */
    STATUS_EEE_ERROR_PROGRAM_INDICATOR     = 0xD04U, /*!< Failed to make block indicator to non-blank for several times */
    STATUS_EEE_HVOP_INPROGRESS             = 0xD05U, /*!< The high voltage operation is in progress */

    /* uSDHC specific error codes */
    STATUS_USDHC_OUT_OF_RANGE              = 0xE00U,    /*!< The size of data to be sent is larger than maximum size of ADMA table */
    STATUS_USDHC_PREPARE_ADMA_FAILED       = 0xE01U,    /*!< Failed to prepare the ADMA table */

    /* TDM specific error codes */
    STATUS_TDM_DIARY_FULL                  = 0xF01U, /*!< No empty flash left in diary region */

    /* PHY specific error codes */
    STATUS_PHY_ACCESS_FAILED               = 0x1001U, /*!< Could not access PHY registers */
    STATUS_PHY_INCOMPATIBLE_DEVICE         = 0x1002U  /*!< The selected PHY driver is not compatible with the device */
} status_t;



/* ----------------------------------------------------------------------------
   -- CLOCK TYPES
   ---------------------------------------------------------------------------- */

//=============================================================================
// Definitions
//=============================================================================

   /*! @brief TClk clock frequency. */
#define NUMBER_OF_TCLK_INPUTS 3U
    /** LMEM - Register Layout Typedef */

#define FTM_INSTANCE_COUNT         (4u)

#define    CLK_SRC_SPLL_DIV2    0x06U             /*!< SCGPCLK System PLL clock */
#define    CLK_SRC_SOSC_DIV2    0x01U             /*!< OSCCLK - System Oscillator Bus Clock */
#define    CLK_SRC_SOSC_DIV1    0x01U             /*!< OSCCLK - System Oscillator Bus Clock */
#define    CLK_SRC_OFF          0x00U             /*!< Clock is off */

/* ----------------------------------------------------------------------------
    // @brief Clock names
   ---------------------------------------------------------------------------- */
typedef enum {

    /* Main clocks */
    CORE_CLK                     = 0u,       /*!< Core clock                     */
    BUS_CLK                      = 1u,       /*!< Bus clock                      */
    SLOW_CLK                     = 2u,       /*!< Slow clock                     */
    CLKOUT_CLK                   = 3u,       /*!< CLKOUT clock                   */

    /* Other internal clocks used by peripherals. */
    SIRC_CLK                     = 4u,       /*!< SIRC clock                     */
    FIRC_CLK                     = 5u,       /*!< FIRC clock                     */
    SOSC_CLK                     = 6u,       /*!< SOSC clock                     */
    SPLL_CLK                     = 7u,       /*!< SPLL clock                     */
    RTC_CLKIN_CLK                = 8u,       /*!< RTC_CLKIN clock                */
    SCG_CLKOUT_CLK               = 9u,       /*!< SCG CLK_OUT clock              */

    SIRCDIV1_CLK                 = 10u,      /*!< SIRCDIV1 functional clock      */
    SIRCDIV2_CLK                 = 11u,      /*!< SIRCDIV2 functional clock      */
    FIRCDIV1_CLK                 = 12u,      /*!< FIRCDIV1 functional clock      */
    FIRCDIV2_CLK                 = 13u,      /*!< FIRCDIV2 functional clock      */
    SOSCDIV1_CLK                 = 14u,      /*!< SOSCDIV1 functional clock      */
    SOSCDIV2_CLK                 = 15u,      /*!< SOSCDIV2 functional clock      */
    SPLLDIV1_CLK                 = 16u,      /*!< SPLLDIV1 functional clock      */
    SPLLDIV2_CLK                 = 17u,      /*!< SPLLDIV2 functional clock      */

    SCG_END_OF_CLOCKS            = 18u,      /*!< End of SCG clocks              */

    /* SIM clocks */
    SIM_FTM0_CLOCKSEL            = 21u,      /*!< FTM0 External Clock Pin Select */
    SIM_FTM1_CLOCKSEL            = 22u,      /*!< FTM1 External Clock Pin Select */
    SIM_FTM2_CLOCKSEL            = 23u,      /*!< FTM2 External Clock Pin Select */
    SIM_FTM3_CLOCKSEL            = 24u,      /*!< FTM3 External Clock Pin Select */
    SIM_CLKOUTSELL               = 25u,      /*!< CLKOUT Select                  */
    SIM_RTCCLK_CLK               = 26u,      /*!< RTCCLK clock                   */
    SIM_LPO_CLK                  = 27u,      /*!< LPO clock                      */
    SIM_LPO_1K_CLK               = 28u,      /*!< LPO 1KHz clock                 */
    SIM_LPO_32K_CLK              = 29u,      /*!< LPO 32KHz clock                */
    SIM_LPO_128K_CLK             = 30u,      /*!< LPO 128KHz clock               */
    SIM_EIM_CLK                  = 31u,      /*!< EIM clock source               */
    SIM_ERM_CLK                  = 32u,      /*!< ERM clock source               */
    SIM_DMA_CLK                  = 33u,      /*!< DMA clock source               */
    SIM_MPU_CLK                  = 34u,      /*!< MPU clock source               */
    SIM_MSCM_CLK                 = 35u,      /*!< MSCM clock source              */
    SIM_END_OF_CLOCKS            = 36u,      /*!< End of SIM clocks              */

    /* PCC clocks */
    CMP0_CLK                     = 41u,      /*!< CMP0 clock source              */
    CRC0_CLK                     = 42u,      /*!< CRC0 clock source              */
    DMAMUX0_CLK                  = 43u,      /*!< DMAMUX0 clock source           */
    EWM0_CLK                     = 44u,      /*!< EWM0 clock source              */
    PORTA_CLK                    = 45u,      /*!< PORTA clock source             */
    PORTB_CLK                    = 46u,      /*!< PORTB clock source             */
    PORTC_CLK                    = 47u,      /*!< PORTC clock source             */
    PORTD_CLK                    = 48u,      /*!< PORTD clock source             */
    PORTE_CLK                    = 49u,      /*!< PORTE clock source             */
    RTC0_CLK                     = 50u,      /*!< RTC0 clock source              */
    PCC_END_OF_BUS_CLOCKS        = 51u,      /*!< End of BUS clocks              */
    FlexCAN0_CLK                 = 52u,      /*!< FlexCAN0 clock source          */
    FlexCAN1_CLK                 = 53u,      /*!< FlexCAN1 clock source          */
    FlexCAN2_CLK                 = 54u,      /*!< FlexCAN2 clock source          */
    PDB0_CLK                     = 55u,      /*!< PDB0 clock source              */
    PDB1_CLK                     = 56u,      /*!< PDB1 clock source              */
    PCC_END_OF_SYS_CLOCKS        = 57u,      /*!< End of SYS clocks              */
    FTFC0_CLK                    = 58u,      /*!< FTFC0 clock source             */
    PCC_END_OF_SLOW_CLOCKS       = 59u,      /*!< End of SLOW clocks             */
    FTM0_CLK                     = 60u,      /*!< FTM0 clock source              */
    FTM1_CLK                     = 61u,      /*!< FTM1 clock source              */
    FTM2_CLK                     = 62u,      /*!< FTM2 clock source              */
    FTM3_CLK                     = 63u,      /*!< FTM3 clock source              */
    PCC_END_OF_ASYNCH_DIV1_CLOCKS= 64u,      /*!< End of ASYNCH DIV1 clocks      */
    ADC0_CLK                     = 65u,      /*!< ADC0 clock source              */
    ADC1_CLK                     = 66u,      /*!< ADC1 clock source              */
    FLEXIO0_CLK                  = 67u,      /*!< FLEXIO0 clock source           */
    LPI2C0_CLK                   = 68u,      /*!< LPI2C0 clock source            */
    LPIT0_CLK                    = 69u,      /*!< LPIT0 clock source             */
    LPSPI0_CLK                   = 70u,      /*!< LPSPI0 clock source            */
    LPSPI1_CLK                   = 71u,      /*!< LPSPI1 clock source            */
    LPSPI2_CLK                   = 72u,      /*!< LPSPI2 clock source            */
    LPTMR0_CLK                   = 73u,      /*!< LPTMR0 clock source            */
    LPUART0_CLK                  = 74u,      /*!< LPUART0 clock source           */
    LPUART1_CLK                  = 75u,      /*!< LPUART1 clock source           */
    LPUART2_CLK                  = 76u,      /*!< LPUART2 clock source           */
    PCC_END_OF_ASYNCH_DIV2_CLOCKS= 77u,      /*!< End of ASYNCH DIV2 clocks      */
    PCC_END_OF_CLOCKS            = 78u,      /*!< End of PCC clocks              */
    CLOCK_NAME_COUNT             = 79u,      /*!< The total number of entries    */
} clock_names_t;


 /* ----------------------------------------------------------------------------
 * @brief SIM CLK32KSEL clock source select
 * Implements sim_rtc_clk_sel_src_t_Class
    ---------------------------------------------------------------------------- */
typedef enum
{
  SIM_RTCCLK_SEL_SOSCDIV1_CLK = 0x0U,           /*!< SOSCDIV1 clock          */
  SIM_RTCCLK_SEL_LPO_32K = 0x1U,           /*!< 32 kHz LPO clock        */
  SIM_RTCCLK_SEL_RTC_CLKIN = 0x2U,           /*!< RTC_CLKIN clock         */
  SIM_RTCCLK_SEL_FIRCDIV1_CLK = 0x3U,           /*!< FIRCDIV1 clock          */
} sim_rtc_clk_sel_src_t;


 /* ----------------------------------------------------------------------------
 * @brief SIM LPOCLKSEL clock source select
 * Implements sim_lpoclk_sel_src_t_Class
    ---------------------------------------------------------------------------- */
typedef enum
{
  SIM_LPO_CLK_SEL_LPO_128K = 0x0,           /*!< 128 kHz LPO clock */
  SIM_LPO_CLK_SEL_NO_CLOCK = 0x1,           /*!< No clock */
  SIM_LPO_CLK_SEL_LPO_32K = 0x2,           /*!< 32 kHz LPO clock which is divided by the 128 kHz LPO clock */
  SIM_LPO_CLK_SEL_LPO_1K = 0x3,           /*!< 1 kHz LPO clock which is divided by the 128 kHz LPO clock */
} sim_lpoclk_sel_src_t;

 /* ----------------------------------------------------------------------------
 * @brief SIM CLKOUT select
 * Implements sim_clkout_src_t_Class
    ---------------------------------------------------------------------------- */
typedef enum
{
    SIM_CLKOUT_SEL_SYSTEM_SCG_CLKOUT     = 0U,     /*!< SCG CLKOUT                                   */
    SIM_CLKOUT_SEL_SYSTEM_SOSC_DIV2_CLK  = 2U,     /*!< SOSC DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_SIRC_DIV2_CLK  = 4U,     /*!< SIRC DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_FIRC_DIV2_CLK  = 6U,     /*!< FIRC DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_HCLK           = 7U,     /*!< HCLK                                         */
    SIM_CLKOUT_SEL_SYSTEM_SPLL_DIV2_CLK  = 8U,     /*!< SPLL DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_BUS_CLK        = 9U,     /*!< BUS_CLK                                      */
    SIM_CLKOUT_SEL_SYSTEM_LPO_128K_CLK   = 10U,    /*!< LPO_CLK 128 Khz                              */
    SIM_CLKOUT_SEL_SYSTEM_LPO_CLK        = 12U,    /*!< LPO_CLK as selected by SIM LPO CLK Select    */
    SIM_CLKOUT_SEL_SYSTEM_RTC_CLK        = 14U,    /*!< RTC CLK as selected by SIM CLK 32 KHz Select */

#if defined (QuadSPI_INSTANCE_COUNT)
    SIM_CLKOUT_SEL_SYSTEM_SFIF_CLK_HYP   = 5U,     /*!< SFIF_CLK_HYP                                 */
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK        = 11U,    /*!< IPG_CLK                                      */
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK_SFIF   = 13U,    /*!< IPG_CLK_SFIF                                 */
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK_2XSFIF = 15U     /*!< IP_CLK_2XSFIF                                */
#endif
} sim_clkout_src_t;

/*!
 * @brief SIM CLKOUT divider
 * Implements sim_clkout_div_t_Class
 */
typedef enum
{
  SIM_CLKOUT_DIV_BY_1 = 0x0U,        /*!< Divided by 1 */
  SIM_CLKOUT_DIV_BY_2 = 0x1U,        /*!< Divided by 2 */
  SIM_CLKOUT_DIV_BY_3 = 0x2U,        /*!< Divided by 3 */
  SIM_CLKOUT_DIV_BY_4 = 0x3U,        /*!< Divided by 4 */
  SIM_CLKOUT_DIV_BY_5 = 0x4U,        /*!< Divided by 5 */
  SIM_CLKOUT_DIV_BY_6 = 0x5U,        /*!< Divided by 6 */
  SIM_CLKOUT_DIV_BY_7 = 0x6U,        /*!< Divided by 7 */
  SIM_CLKOUT_DIV_BY_8 = 0x7U,        /*!< Divided by 8 */
} sim_clkout_div_t;

/*!
 * @brief SCG system clock source.
 * Implements scg_system_clock_src_t_Class
 */
typedef enum
{
  SCG_SYSTEM_CLOCK_SRC_SYS_OSC = 1U,       /*!< System OSC. */
  SCG_SYSTEM_CLOCK_SRC_SIRC = 2U,       /*!< Slow IRC.   */
  SCG_SYSTEM_CLOCK_SRC_FIRC = 3U,       /*!< Fast IRC.   */
  SCG_SYSTEM_CLOCK_SRC_SYS_PLL = 6U,       /*!< System PLL. */
  SCG_SYSTEM_CLOCK_SRC_NONE = 255U      /*!< MAX value.  */
} scg_system_clock_src_t;

/*!
 * @brief SCG system clock divider value.
 * Implements scg_system_clock_div_t_Class
 */
typedef enum
{
  SCG_SYSTEM_CLOCK_DIV_BY_1 = 0U,     /*!< Divided by 1. */
  SCG_SYSTEM_CLOCK_DIV_BY_2 = 1U,     /*!< Divided by 2. */
  SCG_SYSTEM_CLOCK_DIV_BY_3 = 2U,     /*!< Divided by 3. */
  SCG_SYSTEM_CLOCK_DIV_BY_4 = 3U,     /*!< Divided by 4. */
  SCG_SYSTEM_CLOCK_DIV_BY_5 = 4U,     /*!< Divided by 5. */
  SCG_SYSTEM_CLOCK_DIV_BY_6 = 5U,     /*!< Divided by 6. */
  SCG_SYSTEM_CLOCK_DIV_BY_7 = 6U,     /*!< Divided by 7. */
  SCG_SYSTEM_CLOCK_DIV_BY_8 = 7U,     /*!< Divided by 8. */
  SCG_SYSTEM_CLOCK_DIV_BY_9 = 8U,     /*!< Divided by 9. */
  SCG_SYSTEM_CLOCK_DIV_BY_10 = 9U,     /*!< Divided by 10. */
  SCG_SYSTEM_CLOCK_DIV_BY_11 = 10U,    /*!< Divided by 11. */
  SCG_SYSTEM_CLOCK_DIV_BY_12 = 11U,    /*!< Divided by 12. */
  SCG_SYSTEM_CLOCK_DIV_BY_13 = 12U,    /*!< Divided by 13. */
  SCG_SYSTEM_CLOCK_DIV_BY_14 = 13U,    /*!< Divided by 14. */
  SCG_SYSTEM_CLOCK_DIV_BY_15 = 14U,    /*!< Divided by 15. */
  SCG_SYSTEM_CLOCK_DIV_BY_16 = 15U,    /*!< Divided by 16. */
} scg_system_clock_div_t;

/*!
 * @brief SCG ClockOut type.
 * Implements scg_clockout_src_t_Class
 */
typedef enum
{
  SCG_CLOCKOUT_SRC_SCG_SLOW = 0U,   /*!< SCG SLOW.   */
  SCG_CLOCKOUT_SRC_SOSC = 1U,   /*!< System OSC. */
  SCG_CLOCKOUT_SRC_SIRC = 2U,   /*!< Slow IRC.   */
  SCG_CLOCKOUT_SRC_FIRC = 3U,   /*!< Fast IRC.   */
  SCG_CLOCKOUT_SRC_SPLL = 6U,   /*!< System PLL. */
} scg_clockout_src_t;
/*! @} */

/*!
 * @brief SCG asynchronous clock divider value.
 * Implements scg_async_clock_div_t_Class
 */
typedef enum
{
  SCG_ASYNC_CLOCK_DISABLE = 0U,        /*!< Clock output is disabled.  */
  SCG_ASYNC_CLOCK_DIV_BY_1 = 1U,        /*!< Divided by 1.              */
  SCG_ASYNC_CLOCK_DIV_BY_2 = 2U,        /*!< Divided by 2.              */
  SCG_ASYNC_CLOCK_DIV_BY_4 = 3U,        /*!< Divided by 4.              */
  SCG_ASYNC_CLOCK_DIV_BY_8 = 4U,        /*!< Divided by 8.              */
  SCG_ASYNC_CLOCK_DIV_BY_16 = 5U,        /*!< Divided by 16.             */
  SCG_ASYNC_CLOCK_DIV_BY_32 = 6U,        /*!< Divided by 32.             */
  SCG_ASYNC_CLOCK_DIV_BY_64 = 7U         /*!< Divided by 64.             */
} scg_async_clock_div_t;

/*!
 * @brief SCG system OSC monitor mode.
 * Implements scg_sosc_monitor_mode_t_Class
 */
typedef enum
{
  SCG_SOSC_MONITOR_DISABLE = 0U,                         /*!< Monitor disable.                          */
  SCG_SOSC_MONITOR_INT = 1U,                         /*!< Interrupt when system OSC error detected. */
  SCG_SOSC_MONITOR_RESET = 2U,                          /*!< Reset when system OSC error detected.     */
} scg_sosc_monitor_mode_t;

/*!
 * @brief SCG OSC frequency range select
 * Implements scg_sosc_range_t_Class
 */
typedef enum
{
  SCG_SOSC_RANGE_MID = 2U,  /*!< Medium frequency range selected for the crystal OSC (4 Mhz to 8 Mhz).  */
  SCG_SOSC_RANGE_HIGH = 3U,  /*!< High frequency range selected for the crystal OSC (8 Mhz to 40 Mhz).   */
} scg_sosc_range_t;

/*!
 * @brief SCG OSC high gain oscillator select.
 * Implements scg_sosc_gain_t_Class
 */
typedef enum
{
  SCG_SOSC_GAIN_LOW = 0x0,  /*!< Configure crystal oscillator for low-power operation */
  SCG_SOSC_GAIN_HIGH = 0x1,  /*!< Configure crystal oscillator for high-gain operation */
} scg_sosc_gain_t;

/*!
 * @brief SCG OSC external reference clock select.
 * Implements scg_sosc_ext_ref_t_Class
 */
typedef enum
{
  SCG_SOSC_REF_EXT = 0x0,     /*!< External reference clock requested    */
  SCG_SOSC_REF_OSC = 0x1,     /*!< Internal oscillator of OSC requested. */
} scg_sosc_ext_ref_t;

/*!
 * @brief Debug trace clock source select
 * Implements clock_trace_src_t_Class
 */
typedef enum
{
  CLOCK_TRACE_SRC_CORE_CLK = 0x0          /*!< core clock     */
} clock_trace_src_t;

/*!
 * @brief SCG slow IRC clock frequency range.
 * Implements scg_sirc_range_t_Class
 */
typedef enum
{
  SCG_SIRC_RANGE_HIGH = 1U,  /*!< Slow IRC high range clock (8 MHz). */
} scg_sirc_range_t;

/*!
 * @brief SCG fast IRC clock frequency range.
 * Implements scg_firc_range_t_Class
 */
typedef enum
{
  SCG_FIRC_RANGE_48M,   /*!< Fast IRC is trimmed to 48MHz.  */
} scg_firc_range_t;

/*!
 * @brief SCG system PLL monitor mode.
 * Implements scg_spll_monitor_mode_t_Class
 */
typedef enum
{
  SCG_SPLL_MONITOR_DISABLE = 0U,                         /*!< Monitor disable.                          */
  SCG_SPLL_MONITOR_INT = 1U,                         /*!< Interrupt when system PLL error detected. */
  SCG_SPLL_MONITOR_RESET = 2U                          /*!< Reset when system PLL error detected.     */
} scg_spll_monitor_mode_t;

/*!
 * @brief SCG system PLL predivider.
 */
typedef enum
{
  SCG_SPLL_CLOCK_PREDIV_BY_1 = 0U,
  SCG_SPLL_CLOCK_PREDIV_BY_2 = 1U,
  SCG_SPLL_CLOCK_PREDIV_BY_3 = 2U,
  SCG_SPLL_CLOCK_PREDIV_BY_4 = 3U,
  SCG_SPLL_CLOCK_PREDIV_BY_5 = 4U,
  SCG_SPLL_CLOCK_PREDIV_BY_6 = 5U,
  SCG_SPLL_CLOCK_PREDIV_BY_7 = 6U,
  SCG_SPLL_CLOCK_PREDIV_BY_8 = 7U

} scg_spll_clock_prediv_t;

/*!
 * @brief SCG system PLL multiplier.
 */
typedef enum
{
  SCG_SPLL_CLOCK_MULTIPLY_BY_16 = 0U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_17 = 1U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_18 = 2U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_19 = 3U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_20 = 4U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_21 = 5U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_22 = 6U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_23 = 7U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_24 = 8U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_25 = 9U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_26 = 10U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_27 = 11U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_28 = 12U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_29 = 13U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_30 = 14U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_31 = 15U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_32 = 16U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_33 = 17U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_34 = 18U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_35 = 19U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_36 = 20U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_37 = 21U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_38 = 22U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_39 = 23U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_40 = 24U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_41 = 25U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_42 = 26U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_43 = 27U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_44 = 28U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_45 = 29U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_46 = 30U,
  SCG_SPLL_CLOCK_MULTIPLY_BY_47 = 31U
} scg_spll_clock_multiply_t;

/*! @brief PCC clock source select
 *  Implements peripheral_clock_source_t_Class
 */
typedef uint8_t peripheral_clock_source_t;

/*! @brief PCC fractional value select
 *  Implements peripheral_clock_frac_t_Class
 */
typedef enum
{
  MULTIPLY_BY_ONE = 0x00U,             /*!< Fractional value is zero */
  MULTIPLY_BY_TWO = 0x01U              /*!< Fractional value is one */
} peripheral_clock_frac_t;

/*! @brief PCC divider value select
 *  Implements peripheral_clock_divider_t_Class
 */
typedef enum
{
  DIVIDE_BY_ONE = 0x00U,             /*!< Divide by 1 (pass-through, no clock divide) */
  DIVIDE_BY_TWO = 0x01U,             /*!< Divide by 2 */
  DIVIDE_BY_THREE = 0x02U,             /*!< Divide by 3 */
  DIVIDE_BY_FOUR = 0x03U,             /*!< Divide by 4 */
  DIVIDE_BY_FIVE = 0x04U,             /*!< Divide by 5 */
  DIVIDE_BY_SIX = 0x05U,             /*!< Divide by 6 */
  DIVIDE_BY_SEVEN = 0x06U,             /*!< Divide by 7 */
  DIVIDE_BY_EIGTH = 0x07U              /*!< Divide by 8 */
} peripheral_clock_divider_t;


/*!
 * @brief The clock notification type.
 * Implements clock_manager_notify_t_Class
 */
typedef enum
{
  CLOCK_MANAGER_NOTIFY_RECOVER = 0x00U,  /*!< Notify IP to recover to previous work state.      */
  CLOCK_MANAGER_NOTIFY_BEFORE = 0x01U,  /*!< Notify IP that system will change clock setting.  */
  CLOCK_MANAGER_NOTIFY_AFTER = 0x02U,  /*!< Notify IP that have changed to new clock setting. */
} clock_manager_notify_t;

/*!
 * @brief The callback type, indicates what kinds of notification this callback handles.
 * Implements clock_manager_callback_type_t_Class
 */
typedef enum
{
  CLOCK_MANAGER_CALLBACK_BEFORE = 0x01U, /*!< Callback handles BEFORE notification.          */
  CLOCK_MANAGER_CALLBACK_AFTER = 0x02U, /*!< Callback handles AFTER notification.           */
  CLOCK_MANAGER_CALLBACK_BEFORE_AFTER = 0x03U  /*!< Callback handles BEFORE and AFTER notification */
} clock_manager_callback_type_t;

/*!
 * @brief Clock transition policy.
 * Implements clock_manager_policy_t_Class
 */
typedef enum
{
  CLOCK_MANAGER_POLICY_AGREEMENT,  /*!< Clock transfers gracefully. */
  CLOCK_MANAGER_POLICY_FORCIBLE    /*!< Clock transfers forcefully. */
} clock_manager_policy_t;

/*!
 * @brief SIM ClockOut configuration.
 * Implements sim_clock_out_config_t_Class
 */
typedef struct
{
  bool              initialize;     /*!< Initialize or not the ClockOut clock.  */
  bool              enable;         /*!< SIM ClockOut enable.                   */
  sim_clkout_src_t  source;         /*!< SIM ClockOut source select.            */
  sim_clkout_div_t  divider;        /*!< SIM ClockOut divide ratio.             */
} sim_clock_out_config_t;


/*!
 * @brief SIM LPO Clocks configuration.
 * Implements sim_lpo_clock_config_t_Class
 */
typedef struct
{
  bool                  initialize;       /*!< Initialize or not the LPO clock.     */
  sim_rtc_clk_sel_src_t sourceRtcClk;     /*!< RTC_CLK source select.               */
  sim_lpoclk_sel_src_t  sourceLpoClk;     /*!< LPO clock source select.             */
  bool                  enableLpo32k;     /*!< MSCM Clock Gating Control enable.    */
  bool                  enableLpo1k;      /*!< MSCM Clock Gating Control enable.    */
} sim_lpo_clock_config_t;

/*!
 * @brief SIM  Platform Gate Clock configuration.
 * Implements sim_tclk_config_t_Class
 */

typedef struct
{
  bool      initialize;                         /*!< Initialize or not the TCLK clock.  */
  uint32_t  tclkFreq[NUMBER_OF_TCLK_INPUTS];    /*!< TCLKx frequency.                    */
  uint32_t  extPinSrc[FTM_INSTANCE_COUNT];     /*!< FTMx frequency.                    */
} sim_tclk_config_t;

/*!
 * @brief SIM  Platform Gate Clock configuration.
 * Implements sim_plat_gate_config_t_Class
 */
typedef struct
{
  bool initialize;     /*!< Initialize or not the Trace clock.  */
  bool enableMscm;     /*!< MSCM Clock Gating Control enable.   */
  bool enableMpu;      /*!< MPU Clock Gating Control enable.    */
  bool enableDma;      /*!< DMA Clock Gating Control enable.    */
  bool enableErm;      /*!< ERM Clock Gating Control enable.    */
  bool enableEim;      /*!< EIM Clock Gating Control enable.    */
} sim_plat_gate_config_t;

/*!
 * @brief SIM QSPI reference clock gating.
 * Implements sim_qspi_ref_clk_gating_t_Class
 */
typedef struct
{
  bool enableQspiRefClk;      /*!< qspi internal reference clock gating control enable.          */
} sim_qspi_ref_clk_gating_t;


/*!
 * @brief SIM Debug Trace clock configuration.
 * Implements sim_trace_clock_config_t_Class
 */
typedef struct
{
  bool               initialize;    /*!< Initialize or not the Trace clock.  */
  bool               divEnable;     /*!< Trace clock divider enable.         */
  clock_trace_src_t  source;        /*!< Trace clock select.                 */
  uint8_t            divider;       /*!< Trace clock divider divisor.        */
  bool               divFraction;   /*!< Trace clock divider fraction.       */
} sim_trace_clock_config_t;

/*!
 * @brief SIM configure structure.
 * Implements sim_clock_config_t_Class
 */
typedef struct
{
  sim_clock_out_config_t    clockOutConfig;                 /*!< Clock Out configuration.           */
  sim_lpo_clock_config_t    lpoClockConfig;                 /*!< Low Power Clock configuration.     */
  sim_tclk_config_t         tclkConfig;                     /*!< TCLK, FTM option Clock configuration. */
  sim_plat_gate_config_t    platGateConfig;                 /*!< Platform Gate Clock configuration. */
  sim_trace_clock_config_t  traceClockConfig;               /*!< Trace clock configuration.         */
  sim_qspi_ref_clk_gating_t qspiRefClkGating;               /*!< Qspi Reference Clock Gating.       */
} sim_clock_config_t;


/*!
 * @brief SCG system clock configuration.
 * Implements scg_system_clock_config_t_Class
 */
typedef struct
{
  scg_system_clock_div_t divSlow;  /*!< Slow clock divider.      */
  scg_system_clock_div_t divBus;   /*!< BUS clock divider.       */
  scg_system_clock_div_t divCore;  /*!< Core clock divider.      */
  scg_system_clock_src_t src;      /*!< System clock source.     */
} scg_system_clock_config_t;

/*!
 * @name SCG Clockout.
 * @{
 */

/*!
 * @brief SCG system OSC configuration.
 * Implements scg_sosc_config_t_Class
 */
typedef struct
{
  uint32_t  freq;                        /*!< System OSC frequency.                                 */

  scg_sosc_monitor_mode_t monitorMode;   /*!< System OSC Clock monitor mode.                       */

  scg_sosc_ext_ref_t extRef;             /*!< System OSC External Reference Select.                */
  scg_sosc_gain_t    gain;               /*!< System OSC high-gain operation.                      */

  scg_sosc_range_t   range;              /*!< System OSC frequency range.                          */

  scg_async_clock_div_t div1;            /*!< Asynchronous peripheral source.                      */
  scg_async_clock_div_t div2;            /*!< Asynchronous peripheral source.                      */

  bool enableInStop;                     /*!< System OSC is enable or not in stop mode.            */
  bool enableInLowPower;                 /*!< System OSC is enable or not in low power mode.       */

  bool locked;                           /*!< System OSC Control Register can be written.          */

  bool initialize;                       /*!< Initialize or not the System OSC module.             */
} scg_sosc_config_t;


/*!
 * @brief SCG slow IRC clock configuration.
 * Implements scg_sirc_config_t_Class
 */
typedef struct
{
  scg_sirc_range_t range;         /*!< Slow IRC frequency range.                 */

  scg_async_clock_div_t div1;     /*!< Asynchronous peripheral source.           */
  scg_async_clock_div_t div2;     /*!< Asynchronous peripheral source.           */

  bool initialize;                /*!< Initialize or not the SIRC module.        */
  bool enableInStop;              /*!< SIRC is enable or not in stop mode.       */
  bool enableInLowPower;          /*!< SIRC is enable or not in low power mode.  */

  bool locked;                    /*!< SIRC Control Register can be written.     */
} scg_sirc_config_t;


/*!
 * @brief SCG fast IRC clock configuration.
 * Implements scg_firc_config_t_Class
 */
typedef struct
{
  scg_firc_range_t range;            /*!< Fast IRC frequency range.                 */

  scg_async_clock_div_t div1;        /*!< Asynchronous peripheral source.           */
  scg_async_clock_div_t div2;        /*!< Asynchronous peripheral source.           */

  bool enableInStop;                 /*!< FIRC is enable or not in stop mode.       */
  bool enableInLowPower;             /*!< FIRC is enable or not in lowpower mode.   */
  bool regulator;                    /*!< FIRC regulator is enable or not.          */
  bool locked;                       /*!< FIRC Control Register can be written.     */

  bool initialize;                   /*!< Initialize or not the FIRC module.        */
} scg_firc_config_t;


/*!
 * @brief SCG system PLL configuration.
 * Implements scg_spll_config_t_Class
 */
typedef struct
{
  scg_spll_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.                    */

  uint8_t        prediv;               /*!< PLL reference clock divider.                    */
  uint8_t        mult;                 /*!< System PLL multiplier.                          */
  uint8_t        src;                  /*!< System PLL source.                              */

  scg_async_clock_div_t div1;          /*!< Asynchronous peripheral source.                 */
  scg_async_clock_div_t div2;          /*!< Asynchronous peripheral source.                 */

  bool enableInStop;                   /*!< System PLL clock is enable or not in stop mode. */

  bool locked;                         /*!< System PLL Control Register can be written.     */
  bool initialize;                     /*!< Initialize or not the System PLL module.        */
} scg_spll_config_t;

/*!
 * @brief SCG RTC configuration.
 * Implements scg_rtc_config_t_Class
 */
typedef struct
{
  uint32_t rtcClkInFreq;              /*!< RTC_CLKIN frequency.                            */
  bool initialize;                    /*!< Initialize or not the RTC.                      */
} scg_rtc_config_t;

/*!
 * @brief SCG Clock Mode Configuration structure.
 * Implements scg_clock_mode_config_t_Class
 */
typedef struct
{
  scg_system_clock_config_t rccrConfig;      /*!< Run Clock Control configuration.                 */
  scg_system_clock_config_t vccrConfig;      /*!< VLPR Clock Control configuration.                */
  scg_system_clock_config_t hccrConfig;      /*!< HSRUN Clock Control configuration.               */
  scg_system_clock_src_t    alternateClock;  /*!< Alternate clock used during initialization       */
  bool                      initialize;      /*!< Initialize or not the Clock Mode Configuration.  */
} scg_clock_mode_config_t;

/*!
 * @brief SCG ClockOut Configuration structure.
 * Implements scg_clockout_config_t_Class
 */
typedef struct
{
  scg_clockout_src_t        source;          /*!< ClockOut source select.                          */
  bool                      initialize;      /*!< Initialize or not the ClockOut.                  */
} scg_clockout_config_t;

/*!
 * @brief SCG configure structure.
 * Implements scg_config_t_Class
 */
typedef struct
{
  scg_sirc_config_t         sircConfig;      /*!< Slow internal reference clock configuration.     */
  scg_firc_config_t         fircConfig;      /*!< Fast internal reference clock configuration.     */
  scg_sosc_config_t         soscConfig;      /*!< System oscillator configuration.                 */
  scg_spll_config_t         spllConfig;      /*!< System Phase locked loop configuration.          */
  scg_rtc_config_t          rtcConfig;       /*!< Real Time Clock configuration.                   */
  scg_clockout_config_t     clockOutConfig;  /*!< SCG ClockOut Configuration.                      */
  scg_clock_mode_config_t   clockModeConfig; /*!< SCG Clock Mode Configuration.                    */
} scg_config_t;


/*! @brief PCC peripheral instance clock configuration.
 *  Implements peripheral_clock_config_t_Class
 */
typedef struct
{
  /* clockName   is the name of the peripheral clock
   *    must be one of the following values (see the clock_names_t type from S32K1xx_clock_names.h)
   *    PCC_DMA0_CLOCK
   *    PCC_MPU0_CLOCK
   *    ...
   *    PCC_LPUART3_CLOCK
   */
  clock_names_t clockName;
  bool clkGate;                                      /*!< Peripheral clock gate.                     */
  peripheral_clock_source_t clkSrc;                  /*!< Peripheral clock source.                   */
  peripheral_clock_frac_t frac;                      /*!< Peripheral clock fractional value.         */
  peripheral_clock_divider_t divider;                /*!< Peripheral clock divider value.            */
} peripheral_clock_config_t;

/*! @brief PCC configuration.
 *  Implements pcc_config_t_Class
 */
typedef struct
{
  uint32_t count;                                    /*!< Number of peripherals to be configured.               */
  peripheral_clock_config_t * peripheralClocks;       /*!< Pointer to the peripheral clock configurations array. */
} pcc_config_t;

/*! @brief PMC LPO configuration.
 * Implements pmc_lpo_clock_config_t_Class
 */
typedef struct
{
  bool                  initialize;       /*!< Initialize or not the PMC LPO settings. */
  bool                  enable;           /*!< Enable/disable LPO     */
  int8_t                trimValue;        /*!< LPO trimming value     */
} pmc_lpo_clock_config_t;

/*!
 * @brief PMC configure structure.
 * Implements pmc_config_t_Class
 */
typedef struct
{
  pmc_lpo_clock_config_t lpoClockConfig;   /*!< Low Power Clock configuration.     */
} pmc_config_t;

/*!
 * @brief Clock configuration structure.
 * Implements clock_manager_user_config_t_Class
 */
typedef struct
{
  scg_config_t                scgConfig;      /*!< SCG Clock configuration.      */
  sim_clock_config_t          simConfig;      /*!< SIM Clock configuration.      */
  pcc_config_t                pccConfig;      /*!< PCC Clock configuration.      */
  pmc_config_t                pmcConfig;      /*!< PMC Clock configuration.      */
} clock_manager_user_config_t;


/*!
 * @brief Clock notification structure passed to clock callback function.
 * Implements clock_notify_struct_t_Class
 */
typedef struct
{
  uint8_t targetClockConfigIndex;    /*!< Target clock configuration index. */
  clock_manager_policy_t policy;     /*!< Clock transition policy.          */
  clock_manager_notify_t notifyType; /*!< Clock notification type.          */
} clock_notify_struct_t;

/*!
 * @brief Type of clock callback functions.
 */
typedef status_t(*clock_manager_callback_t)(clock_notify_struct_t *notify,
  void* callbackData);

/*!
 * @brief Structure for callback function and its parameter.
 * Implements clock_manager_callback_user_config_t_Class
 */
typedef struct
{
  clock_manager_callback_t      callback;      /*!< Entry of callback function.     */
  clock_manager_callback_type_t callbackType;  /*!< Callback type.                  */
  void* callbackData;                          /*!< Parameter of callback function. */
} clock_manager_callback_user_config_t;



/* ----------------------------------------------------------------------------
   -- PERIPHERAL ACCESS LAYER
   ---------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
   -- MPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

#define     MPU_EAR_EDR_COUNT  4u
#define     MPU_RGD_COUNT      8u
#define     MPU_RGDAAC_COUNT   8u

/** MPU - Register Layout Typedef */
typedef struct {
   uint32_t CESR;                              /**< Control/Error Status Register, offset: 0x0 */
  struct {                                         /* offset: 0x10, array step: 0x8 */
      uint32_t EAR;
      uint32_t EDR;
  } EAR_EDR[MPU_EAR_EDR_COUNT];
  uint8_t RESERVED_1[976];
  struct {                                         /* offset: 0x400, array step: 0x10 */
     uint32_t WORD0;                             /**< Region Descriptor 0, Word 0..Region Descriptor 7, Word 0, array offset: 0x400, array step: 0x10 */
     uint32_t WORD1;                             /**< Region Descriptor 0, Word 1..Region Descriptor 7, Word 1, array offset: 0x404, array step: 0x10 */
     uint32_t WORD2;                             /**< Region Descriptor 0, Word 2..Region Descriptor 7, Word 2, array offset: 0x408, array step: 0x10 */
     uint32_t WORD3;                             /**< Region Descriptor 0, Word 3..Region Descriptor 7, Word 3, array offset: 0x40C, array step: 0x10 */
  } RGD[MPU_RGD_COUNT];
   uint32_t RGDAAC[MPU_RGDAAC_COUNT];
} MPU_Type;

MPU_Type  Mpu;

#define MPU_BASE  &Mpu

#define MPU                                     (MPU_BASE)

/* ----------------------------------------------------------------------------
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

#define     MCM_LMDR_COUNT     2u

/** MCM - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[8];
  __I  uint16_t PLASC;                             /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  __I  uint16_t PLAMC;                             /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  __IO uint32_t CPCR;                              /**< Core Platform Control Register, offset: 0xC */
  __IO uint32_t ISCR;                              /**< Interrupt Status and Control Register, offset: 0x10 */
  uint8_t RESERVED_1[28];
  __IO uint32_t PID;                               /**< Process ID Register, offset: 0x30 */
  uint8_t RESERVED_2[12];
  __IO uint32_t CPO;                               /**< Compute Operation Control Register, offset: 0x40 */
  uint8_t RESERVED_3[956];
  __IO uint32_t LMDR[MCM_LMDR_COUNT];              /**< Local Memory Descriptor Register, array offset: 0x400, array step: 0x4 */
  __IO uint32_t LMDR2;                             /**< Local Memory Descriptor Register2, offset: 0x408 */
  uint8_t RESERVED_4[116];
  __IO uint32_t LMPECR;                            /**< LMEM Parity and ECC Control Register, offset: 0x480 */
  uint8_t RESERVED_5[4];
  __IO uint32_t LMPEIR;                            /**< LMEM Parity and ECC Interrupt Register, offset: 0x488 */
  uint8_t RESERVED_6[4];
  __I  uint32_t LMFAR;                             /**< LMEM Fault Address Register, offset: 0x490 */
  __I  uint32_t LMFATR;                            /**< LMEM Fault Attribute Register, offset: 0x494 */
  uint8_t RESERVED_7[8];
  __I  uint32_t LMFDHR;                            /**< LMEM Fault Data High Register, offset: 0x4A0 */
  __I  uint32_t LMFDLR;                            /**< LMEM Fault Data Low Register, offset: 0x4A4 */
} MCM_Type;

MCM_Type  Mcm;

#define MCM_BASE  &Mcm

#define MCM                                     (MCM_BASE)

/* ----------------------------------------------------------------------------
   -- ERM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

#define     ERM_EARn_COUNT     2u

/** ERM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR0;                               /**< ERM Configuration Register 0, offset: 0x0 */
  uint8_t RESERVED_0[12];
  __IO uint32_t SR0;                               /**< ERM Status Register 0, offset: 0x10 */
  uint8_t RESERVED_1[236];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __I  uint32_t EAR;                               /**< ERM Memory n Error Address Register, array offset: 0x100, array step: 0x10 */
    uint8_t RESERVED_0[12];
  } EARn[ERM_EARn_COUNT];
} ERM_Type;

ERM_Type  Erm;

#define ERM_BASE  &Erm

#define ERM                                     (ERM_BASE)

/* ----------------------------------------------------------------------------
   -- EIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

#define     EIM_EICHDn_COUNT   2u

/** EIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t EIMCR;                             /**< Error Injection Module Configuration Register, offset: 0x0 */
  __IO uint32_t EICHEN;                            /**< Error Injection Channel Enable register, offset: 0x4 */
  uint8_t RESERVED_0[248];
  struct {                                         /* offset: 0x100, array step: 0x100 */
    __IO uint32_t WORD0;                             /**< Error Injection Channel Descriptor n, Word0, array offset: 0x100, array step: 0x100 */
    __IO uint32_t WORD1;                             /**< Error Injection Channel Descriptor n, Word1, array offset: 0x104, array step: 0x100 */
    uint8_t RESERVED_0[248];
  } EICHDn[EIM_EICHDn_COUNT];
} EIM_Type;

EIM_Type  Eim;

#define EIM_BASE  &Eim

#define EIM                                     (EIM_BASE)

/* ----------------------------------------------------------------------------
   -- SCG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/** SCG - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  uint8_t RESERVED_0[8];
  __I  uint32_t CSR;                               /**< Clock Status Register, offset: 0x10 */
  __IO uint32_t RCCR;                              /**< Run Clock Control Register, offset: 0x14 */
  __IO uint32_t VCCR;                              /**< VLPR Clock Control Register, offset: 0x18 */
  __IO uint32_t HCCR;                              /**< HSRUN Clock Control Register, offset: 0x1C */
  __IO uint32_t CLKOUTCNFG;                        /**< SCG CLKOUT Configuration Register, offset: 0x20 */
  uint8_t RESERVED_1[220];
  __IO uint32_t SOSCCSR;                           /**< System OSC Control Status Register, offset: 0x100 */
  __IO uint32_t SOSCDIV;                           /**< System OSC Divide Register, offset: 0x104 */
  __IO uint32_t SOSCCFG;                           /**< System Oscillator Configuration Register, offset: 0x108 */
  uint8_t RESERVED_2[244];
  __IO uint32_t SIRCCSR;                           /**< Slow IRC Control Status Register, offset: 0x200 */
  __IO uint32_t SIRCDIV;                           /**< Slow IRC Divide Register, offset: 0x204 */
  __IO uint32_t SIRCCFG;                           /**< Slow IRC Configuration Register, offset: 0x208 */
  uint8_t RESERVED_3[244];
  __IO uint32_t FIRCCSR;                           /**< Fast IRC Control Status Register, offset: 0x300 */
  __IO uint32_t FIRCDIV;                           /**< Fast IRC Divide Register, offset: 0x304 */
  __IO uint32_t FIRCCFG;                           /**< Fast IRC Configuration Register, offset: 0x308 */
  uint8_t RESERVED_4[756];
  __IO uint32_t SPLLCSR;                           /**< System PLL Control Status Register, offset: 0x600 */
  __IO uint32_t SPLLDIV;                           /**< System PLL Divide Register, offset: 0x604 */
  __IO uint32_t SPLLCFG;                           /**< System PLL Configuration Register, offset: 0x608 */
} SCG_Type;

SCG_Type  Scg;

#define SCG_BASE  &Scg

#define SCG                                     (SCG_BASE)

/* ----------------------------------------------------------------------------
   -- S32_SCB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

  /** S32_SCB - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[8];
  __IO uint32_t ACTLR;                             /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  __I  uint32_t CPUID;                             /**< CPUID Base Register, offset: 0xD00 */
  __IO uint32_t ICSR;                              /**< Interrupt Control and State Register, offset: 0xD04 */
  __IO uint32_t VTOR;                              /**< Vector Table Offset Register, offset: 0xD08 */
  __IO uint32_t AIRCR;                             /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  __IO uint32_t SCR;                               /**< System Control Register, offset: 0xD10 */
  __IO uint32_t CCR;                               /**< Configuration and Control Register, offset: 0xD14 */
  __IO uint32_t SHPR1;                             /**< System Handler Priority Register 1, offset: 0xD18 */
  __IO uint32_t SHPR2;                             /**< System Handler Priority Register 2, offset: 0xD1C */
  __IO uint32_t SHPR3;                             /**< System Handler Priority Register 3, offset: 0xD20 */
  __IO uint32_t SHCSR;                             /**< System Handler Control and State Register, offset: 0xD24 */
  __IO uint32_t CFSR;                              /**< Configurable Fault Status Registers, offset: 0xD28 */
  __IO uint32_t HFSR;                              /**< HardFault Status register, offset: 0xD2C */
  __IO uint32_t DFSR;                              /**< Debug Fault Status Register, offset: 0xD30 */
  __IO uint32_t MMFAR;                             /**< MemManage Address Register, offset: 0xD34 */
  __IO uint32_t BFAR;                              /**< BusFault Address Register, offset: 0xD38 */
  __IO uint32_t AFSR;                              /**< Auxiliary Fault Status Register, offset: 0xD3C */
  uint8_t RESERVED_2[72];
  __IO uint32_t CPACR;                             /**< Coprocessor Access Control Register, offset: 0xD88 */
  uint8_t RESERVED_3[424];
  __IO uint32_t FPCCR;                             /**< Floating-point Context Control Register, offset: 0xF34 */
  __IO uint32_t FPCAR;                             /**< Floating-point Context Address Register, offset: 0xF38 */
  __IO uint32_t FPDSCR;                            /**< Floating-point Default Status Control Register, offset: 0xF3C */
} S32_SCB_Type, *S32_SCB_MemMapPtr;

S32_SCB_Type SCB_Register_Layout;

/** Peripheral S32_SCB base pointer */
#define S32_SCB                                  (&SCB_Register_Layout)
/** Array initializer of S32_SCB peripheral base pointers */
#define S32_SCB_BASE_PTRS                        { S32_SCB }
/* CPACR Bit Fields */
#define S32_SCB_CPACR_CP10_MASK                  0x10
#define S32_SCB_CPACR_CP11_MASK                  0x25

/* ----------------------------------------------------------------------------
   -- S32_SCB Register Masks
   ---------------------------------------------------------------------------- */
#define S32_SCB_AIRCR_VECTKEY_MASK               0xFFFF0000u
#define S32_SCB_AIRCR_VECTKEY_SHIFT              16u
#define S32_SCB_AIRCR_VECTKEY(x)                 (((uint32_t)(((uint32_t)(x))<<S32_SCB_AIRCR_VECTKEY_SHIFT))&S32_SCB_AIRCR_VECTKEY_MASK)
#define S32_SCB_AIRCR_SYSRESETREQ_MASK           0x4u
#define S32_SCB_AIRCR_SYSRESETREQ_SHIFT          2u
#define S32_SCB_AIRCR_SYSRESETREQ(x)             (((uint32_t)(((uint32_t)(x))<<S32_SCB_AIRCR_SYSRESETREQ_SHIFT))&S32_SCB_AIRCR_SYSRESETREQ_MASK)
#define S32_SCB_AIRCR_VECTKEY_MASK               0xFFFF0000u

/* ----------------------------------------------------------------------------
   -- LMEM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

typedef struct {
  __IO uint32_t PCCCR;                             /**< Cache control register, offset: 0x0 */
  __IO uint32_t PCCLCR;                            /**< Cache line control register, offset: 0x4 */
  __IO uint32_t PCCSAR;                            /**< Cache search address register, offset: 0x8 */
  __IO uint32_t PCCCVR;                            /**< Cache read/write value register, offset: 0xC */
  uint8_t RESERVED_0[16];
  __IO uint32_t PCCRMR;                            /**< Cache regions mode register, offset: 0x20 */
} LMEM_Type, *LMEM_MemMapPtr;
/* LMEM - Peripheral instance base addresses */

LMEM_Type LMem_Register_Layout;

#define LMEM                                     (&LMem_Register_Layout)

/* ----------------------------------------------------------------------------
   -- LMEM Register Masks
   ---------------------------------------------------------------------------- */
#define LMEM_PCCCR_INVW0_MASK                    0x1
#define LMEM_PCCCR_INVW0_SHIFT                   1u
#define LMEM_PCCCR_INVW1_MASK                    0x2
#define LMEM_PCCCR_INVW1_SHIFT                   2u
#define LMEM_PCCCR_INVW0(x)                      (((uint32_t)(((uint32_t)(x))<<LMEM_PCCCR_INVW0_SHIFT))&LMEM_PCCCR_INVW0_MASK)
#define LMEM_PCCCR_INVW1(x)                      (((uint32_t)(((uint32_t)(x))<<LMEM_PCCCR_INVW1_SHIFT))&LMEM_PCCCR_INVW1_MASK)
#define LMEM_PCCCR_GO_MASK                       0x1
#define LMEM_PCCCR_GO_SHIFT                      1u
#define LMEM_PCCCR_GO(x)                         (((uint32_t)(((uint32_t)(x))<<LMEM_PCCCR_GO_SHIFT))&LMEM_PCCCR_GO_MASK)
#define LMEM_PCCCR_ENCACHE_MASK                  0x1u
#define LMEM_PCCCR_ENCACHE_SHIFT                 0u
#define LMEM_PCCCR_ENCACHE(x)                    (((uint32_t)(((uint32_t)(x))<<LMEM_PCCCR_ENCACHE_SHIFT))&LMEM_PCCCR_ENCACHE_MASK)


/* ----------------------------------------------------------------------------
   -- RCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/** RCM - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __I  uint32_t SRS;                               /**< System Reset Status Register, offset: 0x8 */
  __IO uint32_t RPC;                               /**< Reset Pin Control register, offset: 0xC */
  uint8_t RESERVED_0[8];
  __IO uint32_t SSRS;                              /**< Sticky System Reset Status Register, offset: 0x18 */
  __IO uint32_t SRIE;                              /**< System Reset Interrupt Enable Register, offset: 0x1C */
} RCM_Type, *RCM_MemMapPtr;
/* RCM - Peripheral instance base addresses */

RCM_Type RCM_Register_Layout;

#define RCM                                      (&RCM_Register_Layout)

/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */
/* SRS Bit Fields */
#define RCM_SRS_SACKERR_MASK                     0x2000u
#define RCM_SRS_MDM_AP_MASK                      0x800u
#define RCM_SRS_SW_MASK                          0x400u
#define RCM_SRS_LOCKUP_MASK                      0x200u
#define RCM_SRS_JTAG_MASK                        0x100u
#define RCM_SRS_POR_MASK                         0x80u
#define RCM_SRS_PIN_MASK                         0x40u
#define RCM_SRS_WDOG_MASK                        0x20u
#define RCM_SRS_LOL_MASK                         0x8u
#define RCM_SRS_LOC_MASK                         0x4u
#define RCM_SRS_LVD_MASK                         0x2u

#define RCM_SSRS_SPOR_MASK                       0x80u

#define RCM_SSRS_SPOR_MASK                       0x80u
#define RCM_SSRS_SPOR_SHIFT                      7u
#define RCM_SSRS_SPOR(x)                         (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_SPOR_SHIFT))&RCM_SSRS_SPOR_MASK)


#endif // DEVICE_TARGET_TYPES_2023_10_11_H

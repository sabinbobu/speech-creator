//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddTpsGen2_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_CFG_2024_01_30_H_
#define CDD_TPS_GEN2_CFG_2024_01_30_H_

//=============================================================================
// includes
//=============================================================================
#include <CddTpsGen2_Types.h>

//=============================================================================
// Protocol - frame configuration
//=============================================================================
//Length of ADCID Addressing broadcast write command
#define CDDTPSGEN2_N_TX_ADCID        (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_01_BYTE  + CDDTPSGEN2_N_CRC_BYTES)
//Length of SYSCFG/CMWTAP/PWMTICK broadcast command
#define CDDTPSGEN2_N_TX_DEF_CFG      (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_03_BYTES + CDDTPSGEN2_N_CRC_BYTES)

// If PWM Synchronization Type is exclusive Sofware - Broadcast SSYNC Command
#if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_SW_BROADCAST_CMD)
  //Length of SOFTSYNC->SSYNC broadcast command
#define CDDTPSGEN2_N_TX_SSYNC      (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_01_BYTE  + CDDTPSGEN2_N_CRC_BYTES)
#else
#define CDDTPSGEN2_N_TX_SSYNC      0u
#endif

//Configure basic communication broadcast command
#define CDDTPSGEN2_N_TX_CFG_COM      (CDDTPSGEN2_N_TX_ADCID + CDDTPSGEN2_N_TX_DEF_CFG + CDDTPSGEN2_N_TX_SSYNC)

//Length of Clear FAULT chip write command
#define CDDTPSGEN2_N_TX_CLRFLT       (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_03_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_CLRFLT       (CDDTPSGEN2_N_ACK )


//Configure Chip configuration write command
#define CDDTPSGEN2_N_TX_CFG_CHIP     (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_03_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_CFG_CHIP     (CDDTPSGEN2_N_ACK)

//Configure Phase Shifts settings write command
#define CDDTPSGEN2_N_TX_CFG_PHASE    (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_16_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_CFG_PHASE    (CDDTPSGEN2_N_ACK)

//Configure LED segments settings write command
#define CDDTPSGEN2_N_TX_CFG_STRING   (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_12_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_CFG_STRING   (CDDTPSGEN2_N_ACK)


//Transmission lengths: Header + Payload + CRC
#define CDDTPSGEN2_N_TX_WIDTH        (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_16_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_TX_ICID         (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_TX_CONFIG       (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_TX_ADC          (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_TX_FAULT        (CDDTPSGEN2_N_HEADER_BYTES + CDDTPSGEN2_N_CRC_BYTES)

//Reception lengths: Tx + Header + Payload + CRC
#define CDDTPSGEN2_N_BR_RX_ADCID     (CDDTPSGEN2_N_01_BYTE  + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_BR_RX_DEF_CFG   (CDDTPSGEN2_N_01_BYTE  + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_WIDTH        (CDDTPSGEN2_N_ACK)
#define CDDTPSGEN2_N_RX_ICID         (CDDTPSGEN2_N_01_BYTE +CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_CONFIG1      (CDDTPSGEN2_N_16_BYTES+CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_CONFIG2      (CDDTPSGEN2_N_16_BYTES+CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_ADC          (CDDTPSGEN2_N_02_BYTES+CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_N_RX_FAULT        (CDDTPSGEN2_N_03_BYTES+CDDTPSGEN2_N_CRC_BYTES)

#define CDDTPSGEN2_EE_N_RX_STATUS    (CDDTPSGEN2_N_01_BYTE   + CDDTPSGEN2_N_CRC_BYTES)
#define CDDTPSGEN2_EE_N_RX_READ_DATA (CDDTPSGEN2_N_16_BYTES  + CDDTPSGEN2_N_CRC_BYTES)

//=============================================================================
// global defines
//=============================================================================

#define CDDTPSGEN2_TPS92662A_MAX_SWITCHS_PER_DEVICE 12U
#define CDDTPSGEN2_TPS92663A_MAX_SWITCHS_PER_DEVICE  6U 

#define CDDTPSGEN2_COD_DEV_ADDR_SLAVE_MAX_ID        7U
#define CDDTPSGEN2_COD_DEV_ADDR_MASTER_OFFSET_ID    8U
#define CDDTPSGEN2_COD_DEV_ADDR_MASTER_MAX_ID       (CDDTPSGEN2_COD_DEV_ADDR_SLAVE_MAX_ID+CDDTPSGEN2_COD_DEV_ADDR_MASTER_OFFSET_ID)

// Mlc System Clock Frequency
#define CDDTPSGEN2_SYS_CLK             CDDTPSGEN2_CLK_FREQ_8MHz
#define CDDTPSGEN2_BAUDRATE_500Kbps             5u
#define CDDTPSGEN2_BAUDRATE_1Mbps               10u

// Number of Mlc chips that driver has to control
#define CDDTPSGEN2_MAX_CHIPs                    CFG_MLC_Chip_Cnt
#define CDDTPSGEN2_LAST_CHIP                    (CDDTPSGEN2_MAX_CHIPs-1U)
#define CDDTPSGEN2_ADDR_NOT_CONNECTED           (uint8)CFG_MLC_Chip_Not_Connected

// chip address configuration 
#define CDDTPSGEN2_ADDRESS_LIST  {    \
                                    (uint8)CDDTPSGEN2_DEV_ID00,  \
                                    (uint8)CDDTPSGEN2_DEV_ID01,  \
                                    (uint8)CDDTPSGEN2_DEV_ID02,  \
                                    (uint8)CDDTPSGEN2_DEV_ID03,  \
                                    (uint8)CDDTPSGEN2_DEV_ID04,  \
                                    (uint8)CDDTPSGEN2_DEV_ID05,  \
                                    (uint8)CDDTPSGEN2_DEV_ID06,  \
                                    (uint8)CDDTPSGEN2_DEV_ID07   \
                                 }

// The Mlc driver transmission is active at startup
#define CDDTPSGEN2_START_AT_POWERUP  CDDTPSGEN2_FEATURE_ON

// Mlc configuration used in broadcast commands //LDM.SYRS.32990
#define CDDTPSGEN2_CFG_SLEWRATE      { \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE),   \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE),   \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE),   \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE),   \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE),   \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE),   \
                                    CDDTPSGEN2_SET_SLEWRATE_REG((uint8)SLOW_RATE) }

#define CDDTPSGEN2_CFG_OVLMT         {  \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT),    \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT),    \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT),    \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT),    \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT),    \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT),    \
                                    CDDTPSGEN2_SET_OVLMT_REG((uint8)VTH_O3_DEFAULT) }   \

#define CDDTPSGEN2_CFG_PARLED        {  \
                                    (uint8)CDDTPSGEN2_PARLED_NONE,    \
                                    (uint8)CDDTPSGEN2_PARLED_NONE,    \
                                    (uint8)CDDTPSGEN2_PARLED_NONE,    \
                                    (uint8)CDDTPSGEN2_PARLED_NONE,    \
                                    (uint8)CDDTPSGEN2_PARLED_NONE,    \
                                    (uint8)CDDTPSGEN2_PARLED_NONE,    \
                                    (uint8)CDDTPSGEN2_PARLED_NONE }


#define CDDTPSGEN2_CFG_SYSCFG         /*(CDDTPSGEN2_ACKEN|CDDTPSGEN2_PWR)  // */  (CDDTPSGEN2_ACKEN|CDDTPSGEN2_CMWEN|CDDTPSGEN2_PWR)
#define CDDTPSGEN2_CFG_CMWTAP_8MHz         (uint8)CDDTPSGEN2_CMWTAP_BIT21_DEFAULT     // 2^21 = 2,097,152 / 8MHz SYC_CLK = 381,469ms
#define CDDTPSGEN2_CFG_CMWTAP_16MHz        (uint8)CDDTPSGEN2_CMWTAP_BIT22             // 2^22 = 4,194,304 / 16MHz SYC_CLK = 381,469ms

//=============================================================================
// Matrix PWM Frequency
//=============================================================================
#define CDDTPSGEN2_CFG_PWMTICK_8MHz  (uint8)CDDTPSGEN2_CLK8_PWM_200HZ    //LDM.SYRS.32984
#define CDDTPSGEN2_CFG_PWMTICK_16MHz (uint8)CDDTPSGEN2_CLK16_PWM_200HZ   //LDM.SYRS.32984

//=============================================================================
// Sensitivity of segment fault detection and flickering avoidance 
//=============================================================================
// Minimum PWM Duty Cycle Threshold
#define CDDTPSGEN2_MIN_PWM_THD       5u    // For target values under 0.5%
// Predefined PWM Duty Cycle Applied for values under threshold
#define CDDTPSGEN2_MIN_PWM_VAL       0u    // Set predefined minimum  0.0%

//=============================================================================
// Multichip PWM Synchronization Strategy
//=============================================================================
#define CDDTPSGEN2_SYNC_TYPE               CDDTPSGEN2_SYNC_HW_MASTER_SLAVE    // Master-Slave Topology Synchronization

#if (CDDTPSGEN2_SYNC_TYPE == CDDTPSGEN2_SYNC_HW_MASTER_SLAVE)
#define CDDTPSGEN2_SYNC_MASTER_DEV_NBR     CDDTPSGEN2_DEV_ID06          // Select the address of the synchronization master chip
#endif

// Mlc configuration used in LED Phase Shift commands
#define CDDTPSGEN2_PHASE_SHIFT_CFG      { \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS,    \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS,    \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS,    \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS,    \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS,    \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS,    \
                                       CDDTPSGEN2_CFG_1STRING_OF_12LEDS}

// Minimum timouts for marking that LMM chip is off
#define CDDTPSGEN2_TIMEOUT_THD       10u   // 10 times x 10ms LMM Cyclic Task = 100ms 

// Number of clearing faults to be sent until LED Status Monitor shall be started
#define CDDTPSGEN2_CFG_CLR_FLT_CNT   10u   // 10 times x 10ms LMM Cyclic Task = 100ms

//Define a complete segment string with Duty Cycle 00.00%
#define CDDTPSGEN2_DEFAULT_STRING    {(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00,(uint8)CDDTPSGEN2_DEF_WIDTH_00p00}

// Default Widths (4 bit resolution) for Communication Watchdog Timeout
#define CDDTPSGEN2_DEFAULT_WIDTHS    {   \
                                    CDDTPSGEN2_DEFAULT_STRING,    \
                                    CDDTPSGEN2_DEFAULT_STRING,    \
                                    CDDTPSGEN2_DEFAULT_STRING,    \
                                    CDDTPSGEN2_DEFAULT_STRING,    \
                                    CDDTPSGEN2_DEFAULT_STRING,    \
                                    CDDTPSGEN2_DEFAULT_STRING,    \
                                    CDDTPSGEN2_DEFAULT_STRING }

// Init Target Values at Startup, before calling CddMlc_SetTargetValues function.
#define CDDTPSGEN2_DUTY_CYCLE_INIT   { \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                  { 0u, 0u, 0, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u }}


// Use LookUpTable for 0xA001 Polynom 16 bit CRC Computation
#define CDDTPSGEN2_LOOKUP_TABLE_CRC    CDDTPSGEN2_FEATURE_ON

//=============================================================================
// Cycle Time Measurements
//=============================================================================
// Activate computation time measurement of Mlc Cyclic function
#define CDDTPSGEN2_MEASURE_CYCLE_TIME  CDDTPSGEN2_FEATURE_OFF
// Number of bits for computing moving average of mean time
#define CDDTPSGEN2_MOVING_AVERAGE_BITS 8u                          // 256 Samples used for mean time computation   
//=============================================================================

//=============================================================================
// I2C - EEPROM Communication Configuration
//=============================================================================
//#define CDDTPSGEN2_I2C_ENABLED         CDDTPSGEN2_FEATURE_OFF         // I2C EEPROM Communication Enabled
#define CDDTPSGEN2_I2C_ENABLED         CDDTPSGEN2_FEATURE_ON            // I2C EEPROM Communication Enabled


#if (CDDTPSGEN2_I2C_ENABLED == CDDTPSGEN2_FEATURE_ON)
//take address from coding
#define CDDTPSGEN2_I2C_DEV_NBR         CDDTPSGEN2_DEV_ID04                        // Select the address of the chip that has EEPROM on I2C
#define CDDTPSGEN2_CFG_I2CTICK_8MHz    (uint8)CDDTPSGEN2_I2C_CLK8_DIV20           // I2C Tick Divider set to 20 => 400KHz (for 8MHz CLK)
#define CDDTPSGEN2_CFG_I2CTICK_16MHz   (uint8)CDDTPSGEN2_I2C_CLK16_DIV40_DEFAULT  // I2C Tick Divider set to 40 => 400KHz (for 16MHz CLK)
#define CDDTPSGEN2_EEPROM_SIZE         256u                                       // Size of I2C EEPROM [Bytes]
#define CDDTPSGEN2_I2C_INIT_TIMEOUT    CDDTPSGEN2_TIMEOUT_THD + 1u                // Timeout for Initialization Phase 
#define CDDTPSGEN2_READ_LOOP_TIMEOUT   CDDTPSGEN2_TIMEOUT_THD + 10u               // Timeout for Multi Byte Read ~40 Operations
#define CDDTPSGEN2_WRITE_BYTE_TIMEOUT  CDDTPSGEN2_TIMEOUT_THD                     // Timeout for Single Byte Write ~4 Operations

#define CDDTPSGEN2_I2C_DEV_TYPE_ID       (0x0AU)
#define CDDTPSGEN2_I2C_BLOCK_BITS_MASK   (0x06U)
#endif

//=============================================================================
// RTE Interface Wrapper
//=============================================================================
#define CDDTPSGEN2_RTE_INTERFACES                            CDDTPSGEN2_FEATURE_ON                // RTE Wrapper Interfaces are used
#define CDDTPSGEN2_MATRIX_COMMUNICATION_CONTROL              CDDTPSGEN2_FEATURE_ON                // enable wrapper function for taking control over communication of matrix (enable/disable comm)


#endif // CDD_TPS_GEN2_CFG_2024_01_30_H_

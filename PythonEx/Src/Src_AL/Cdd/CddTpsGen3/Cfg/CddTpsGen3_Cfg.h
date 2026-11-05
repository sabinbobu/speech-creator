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
/// \file  CddTpsGen3_Cfg.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_CFG_2024_02_05_H
#define CDD_TPS_GEN3_CFG_2024_02_05_H


//=============================================================================
// includes
//=============================================================================
#include <CddTpsGen3_Types.h>

#define CDDTPSGEN3_MAX_CHIPs                    CFG_MLC_Chip_Cnt
#define CDDTPSGEN3_LAST_CHIP                    (CDDTPSGEN3_MAX_CHIPs-1U)
#define CDDTPSGEN3_ADDR_NOT_CONNECTED           (uint8)CFG_MLC_Chip_Not_Connected

#define CDDTPSGEN3_TPS9266x_MAX_SWITCHS_PER_DEVICE  16U

#define CDDTPSGEN3_BAUDRATE_500Kbps                 5u
#define CDDTPSGEN3_BAUDRATE_1Mbps                   10u

#define CDDTPSGEN3_COD_DEV_ADDR_GEN3_ADDR_MAX_ID    15U
#define CDDTPSGEN3_COD_DEV_ADDR_GEN3_START_ADDR_ID  32U
#define CDDTPSGEN3_COD_DEV_ADDR_SLAVE_MAX_ID        (CDDTPSGEN3_COD_DEV_ADDR_GEN3_START_ADDR_ID + CDDTPSGEN3_COD_DEV_ADDR_GEN3_ADDR_MAX_ID)
#define CDDTPSGEN3_COD_DEV_ADDR_MASTER_OFFSET_ID    (CDDTPSGEN3_COD_DEV_ADDR_GEN3_ADDR_MAX_ID + 1U)
#define CDDTPSGEN3_COD_DEV_ADDR_MASTER_MAX_ID       (CDDTPSGEN3_COD_DEV_ADDR_SLAVE_MAX_ID + CDDTPSGEN3_COD_DEV_ADDR_MASTER_OFFSET_ID)



// chip address configuration 
#define CDDTPSGEN3_ADDRESS_LIST  {    \
                                    (uint8)CDDTPSGEN3_DEV_ID00,  \
                                    (uint8)CDDTPSGEN3_DEV_ID01,  \
                                    (uint8)CDDTPSGEN3_DEV_ID02,  \
                                    (uint8)CDDTPSGEN3_DEV_ID03,  \
                                    (uint8)CDDTPSGEN3_DEV_ID04,  \
                                    (uint8)CDDTPSGEN3_DEV_ID05,  \
                                    (uint8)CDDTPSGEN3_DEV_ID06,  \
                                    (uint8)CDDTPSGEN3_DEV_ID07,  \
                                    (uint8)CDDTPSGEN3_DEV_ID08,  \
                                    (uint8)CDDTPSGEN3_DEV_ID09,  \
                                    (uint8)CDDTPSGEN3_DEV_ID10,  \
                                    (uint8)CDDTPSGEN3_DEV_ID11,  \
                                    (uint8)CDDTPSGEN3_DEV_ID12,  \
                                    (uint8)CDDTPSGEN3_DEV_ID13,  \
                                    (uint8)CDDTPSGEN3_DEV_ID14,  \
                                    (uint8)CDDTPSGEN3_DEV_ID15   \
                                 }

// The Mlc driver transmission is active at startup
#define CDDTPSGEN3_START_AT_POWERUP  CDDTPSGEN3_FEATURE_ON


// Mlc configuration used in broadcast commands //LDM.SYRS.32990
//TODO: recoomandation for GEN3 was to set to MEDIUM SLEWRATE

#define CDDTPSGEN3_SLEWRATE     MEDIUM_SLEWRATE

#define CDDTPSGEN3_CFG_SLEWRATE_REGL      { \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGL((uint8)CDDTPSGEN3_SLEWRATE) }

#define CDDTPSGEN3_CFG_SLEWRATE_REGH      { \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE),   \
                                              CDDTPSGEN3_SET_SLEWRATE_REGH((uint8)CDDTPSGEN3_SLEWRATE) }


#define CDDTPSGEN3_CFG_SYSCFG        (CDDTPSGEN3_ACKEN | CDDTPSGEN3_CHPMP_SS  )//(CDDTPSGEN3_ACKEN|CDDTPSGEN3_CMWEN|CDDTPSGEN3_PWR)

#define CDDTPSGEN3_CFG_CMWTAP_8MHz   (uint8)CDDTPSGEN3_CMWTAP_BIT21_DEFAULT     // 2^21 = 2,097,152 / 8MHz SYC_CLK = 381,469ms
#define CDDTPSGEN3_CFG_CMWTAP_16MHz  (uint8)CDDTPSGEN3_CMWTAP_BIT22             // 2^22 = 4,194,304 / 16MHz SYC_CLK = 381,469ms

#define CDDTPSGEN3_CFG_STATUS        (CDDTPSGEN3_PWR)
#define CDDTPSGEN3_CFG_MTPCFG        (CDDTPSGEN3_FS_PIN )

//=============================================================================
// Matrix PWM Frequency
//=============================================================================
#define CDDTPSGEN3_CFG_PWMTICK_8MHz  (uint8)CDDTPSGEN3_CLK8_PWM_200HZ   //LDM.SYRS.32984
#define CDDTPSGEN3_CFG_PWMTICK_16MHz (uint8)CDDTPSGEN3_CLK16_PWM_200HZ  //LDM.SYRS.32984

//=============================================================================
// Sensitivity of segment fault detection and flickering avoidance 
//=============================================================================
// Minimum PWM Duty Cycle Threshold
#define CDDTPSGEN3_MIN_PWM_THD       5u    // For target values under 0.5%
// Predefined PWM Duty Cycle Applied for values under threshold
#define CDDTPSGEN3_MIN_PWM_VAL       0u    // Set predefined minimum  0.0%


//=============================================================================
// Multichip PWM Synchronization Strategy
//=============================================================================
#define CDDTPSGEN3_SYNC_TYPE         CDDTPSGEN3_SYNC_SW_BROADCAST_CMD //CDDTPSGEN3_SYNC_HW_MASTER_SLAVE    // Master-Slave Topology Synchronization

#if (CDDTPSGEN3_SYNC_TYPE == CDDTPSGEN3_SYNC_HW_MASTER_SLAVE)
#define CDDTPSGEN3_SYNC_MASTER_DEV_NBR     CDDTPSGEN3_DEV_ID01          // Select the address of the synchronization master chip
#endif

// Mlc configuration used in LED Phase Shift commands
#define CDDTPSGEN3_PHASE_SHIFT_CFG      { \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS,    \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS,    \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS,    \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS,    \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS,    \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS,    \
                                              CDDTPSGEN3_CFG_1STRING_OF_16LEDS}


//TODO : settings from NIO
// Minimum timouts for marking that Mlc chip is off
#define CDDTPSGEN3_TIMEOUT_THD       26u   // 26 times x 10ms Mlc Cyclic Task = 260ms (~ same as comm wathdog monitor)

// Number of clearing faults to be sent until LED Status Monitor shall be started
#define CDDTPSGEN3_CFG_CLR_FLT_CNT   25u   // 25 times x 10ms Mlc Cyclic Task = 250ms
// END TO DO


//Define a complete segment string with Duty Cycle 00.00%
#define CDDTPSGEN3_DEFAULT_STRING    {  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,   \
                                        (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,   \
                                        (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,   \
                                        (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00,  (uint8)CDDTPSGEN3_DEF_WIDTH_00p00    }

// Default Widths (8 bit resolution) for Communication Watchdog Timeout
#define CDDTPSGEN3_DEFAULT_WIDTHS    {   \
                                              CDDTPSGEN3_DEFAULT_STRING,    \
                                              CDDTPSGEN3_DEFAULT_STRING,    \
                                              CDDTPSGEN3_DEFAULT_STRING,    \
                                              CDDTPSGEN3_DEFAULT_STRING,    \
                                              CDDTPSGEN3_DEFAULT_STRING,    \
                                              CDDTPSGEN3_DEFAULT_STRING,    \
                                              CDDTPSGEN3_DEFAULT_STRING }

// Init Target Values at Startup, before calling CddMlc_SetTargetValues function.
#define CDDTPSGEN3_DUTY_CYCLE_INIT   { \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },    \
                                            { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u }}


// Use LookUpTable for 0xA001 Polynom 16 bit CRC Computation
#define CDDTPSGEN3_LOOKUP_TABLE_CRC    CDDTPSGEN3_FEATURE_ON

//=============================================================================
// Protocol - frame configuration
//=============================================================================


//step 1) Configure Chip configuration write command
#define CDDTPSGEN3_N_TX_CFG_CHIP          (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_03_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CFG_CHIP          (CDDTPSGEN3_N_ACK)
#define CDDTPSGEN3_N_RX_SYSCONFIG         (CDDTPSGEN3_N_03_BYTES + CDDTPSGEN3_N_CRC_BYTES)

//step 2) Configure basic communication  command  - software synchronization
//Length of SOFTSYNC->SSYNC broadcast command + add the PWR set in this command ( reason: it's the next register)
#define CDDTPSGEN3_N_TX_CFG_SSYNC         (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_02_BYTES  + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CFG_SSYNC         (CDDTPSGEN3_N_ACK)

//step 3) Configure Phase Shifts settings write command
#define CDDTPSGEN3_N_TX_CFG_PHASE_MSB     (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_16_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_TX_CFG_PHASE_LSB     (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_04_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CFG_PHASE         (CDDTPSGEN3_N_ACK)

//step 4) Configure LED segments settings write command
#define CDDTPSGEN3_N_TX_CFG_STRING        (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_02_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_TX_CFG_DEFWIDTH      (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_16_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CFG_STRING        (CDDTPSGEN3_N_ACK)

//step 5) Configure write command to exit failsafe
#define CDDTPSGEN3_N_TX_CFG_EXITFAILSAFE (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_01_BYTE + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CFG_EXITFAILSAFE (CDDTPSGEN3_N_ACK)

//step 5) Configure write command out control
#define CDDTPSGEN3_N_TX_CFG_OUTCTRL (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_01_BYTE + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CFG_OUTCTRL (CDDTPSGEN3_N_ACK)


//Reception lengths: Tx + Header + Payload + CRC
#define CDDTPSGEN3_N_BR_RX_ADCID     (CDDTPSGEN3_N_01_BYTE  + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_BR_RX_DEF_CFG   (CDDTPSGEN3_N_01_BYTE  + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_ICID         (CDDTPSGEN3_N_01_BYTE  + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_WIDTH        (CDDTPSGEN3_N_ACK)
#define CDDTPSGEN3_N_RX_FAULT        (CDDTPSGEN3_N_04_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_ADC          (CDDTPSGEN3_N_04_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_STATUS       (CDDTPSGEN3_N_01_BYTE  + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_SLEWRATE     (CDDTPSGEN3_N_04_BYTES + CDDTPSGEN3_N_CRC_BYTES)

//Length of Clear FAULT chip write command
#define CDDTPSGEN3_N_TX_CLRFLT       (CDDTPSGEN3_N_HEADER_BYTES + CDDTPSGEN3_N_04_BYTES + CDDTPSGEN3_N_CRC_BYTES)
#define CDDTPSGEN3_N_RX_CLRFLT       (CDDTPSGEN3_N_ACK )

#endif // CDD_TPS_GEN3_CFG_2024_02_05_H

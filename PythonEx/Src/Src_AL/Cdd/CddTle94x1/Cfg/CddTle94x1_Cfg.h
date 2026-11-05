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
/// \file   CddTle94x1_Cfg.h
///
/// \brief  API for CddTle94x1
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
///
//-----------------------------------------------------------------------------

#ifndef CDD_TLE94X1_CFG_2021_03_08_H_
#define CDD_TLE94X1_CFG_2021_03_08_H_


//=============================================================================
//  preprocessor definitions
//=============================================================================

//=============================================================================
//  includes
//=============================================================================

//=============================================================================
//  definitions
//=============================================================================
//===============================================================
//                    CAN CONFIGURATION
//===============================================================

//===============================================================
//                VCC2 SETTING
//===============================================================
#define CDDTLE94X1_CFG_VCC2_ACTIVATION                       1u
#define CDDTLE94X1_CFG_VCC2_DEACTIVATION                     0u

//===============================================================
//              SEQUENCE ERROR CONFIGURATION
//===============================================================

//===============================================================
//               WAIT INTERVAL CONFIGURATION
//===============================================================
// The number of cycles to wait before reporting errors.
// NOTE: The device should enter sleep/stp mode before the timer expires
//
// 9000 cycles corresponds to 0.01 [ms]
//===============================================================
// Commands
#define  CDDTLE94X1_CFG_WRITE_CMD                            0x80u
#define  CDDTLE94X1_CFG_READ_CMD                             0x00u

// Default messages
#define CDDTLE94X1_CFG_CLEAR_ALL                             0x00u

// Masks
#define CDDTLE94X1_CFG_STATUS_INFORMATION_FIELD           0x000000FFu
#define CDDTLE94X1_CFG_RECEIVED_DATA                          0xFFFFu
#define CDDTLE94X1_CFG_ADDRESS_FIELD                            0x7Fu

// Errors
#define ERROR_ON                                                1u
#define NO_ERROR                                                0u
#define CDDTLE94X1_CFG_ERROR                               0xFFFFu

//Register configuration
// CAN modes
#define CDDTLE94X1_CFG_CAN_OFF                                  0x00u
#define CDDTLE94X1_CFG_CAN_WAKE_ON                              0x01u
#define CDDTLE94X1_CFG_CAN_RECEIVE_ONLY                         0x02u
#define CDDTLE94X1_CFG_CAN_NORMAL                               0x03u
#define CDDTLE94X1_CFG_CAN_OFF_SWK                              0x04u
#define CDDTLE94X1_CFG_CAN_WAKE_ON_SWK                          0x05u
#define CDDTLE94X1_CFG_CAN_RECEIVE_ONLY_SWK                     0x06u
#define CDDTLE94X1_CFG_CAN_NORMAL_SWK                           0x07u

// Init configuration
#define CDDTLE94X1_CFG_DISABLE                                     0u
#define CDDTLE94X1_CFG_ENABLE                                      1u

// SBC modes
#define CDDTLE94X1_CFG_NORMAL_MODE                                 0u
#define CDDTLE94X1_CFG_SLEEP_MODE                                  1u
#define CDDTLE94X1_CFG_STOP_MODE                                   2u

// VCC1_OV_RST
#define CDDTLE94X1_CFG_VCC1_OV_RST_0                               0u
#define CDDTLE94X1_CFG_VCC1_OV_RST_1                               1u

// VCC2 Modes
#define CDDTLE94X1_CFG_VCC2_OFF                                    0u // VCC2 Off
#define CDDTLE94X1_CFG_VCC2_ON1                                    1u // VCC2 On in Normal Mode
#define CDDTLE94X1_CFG_VCC2_ON2                                    2u // VCC2 On in Normal and Stop Mode
#define CDDTLE94X1_CFG_VCC2_ON3                                    3u // VCC2 always ON

// Thermal Shutdown Threshold
#define CDDTLE94X1_CFG_TSD_THR_0                                   0u // Default shutdown threshold selected
#define CDDTLE94X1_CFG_TSD_THR_1                                   1u // higher shutdown threshold selected

// VCC1 Reset Threshold Control
#define CDDTLE94X1_CFG_VCC1_RT_Vrt1                                0u // Vrt1_selected
#define CDDTLE94X1_CFG_VCC1_RT_Vrt2                                1u // Vrt2_selected
#define CDDTLE94X1_CFG_VCC1_RT_Vrt3                                2u // Vrt3_selected
#define CDDTLE94X1_CFG_VCC1_RT_Vrt4                                3u // Vrt4_selected

// Reset Delay Time Selection
#define CDDTLE94X1_CFG_RSTN_DEL_tRD1                               0u // The extended reset delay time tRD1 is seletced(default)
#define CDDTLE94X1_CFG_RSTN_DEL_tRD2                               1u // The reduced tRD2 delay time is seletced

// SS_MOD_FR
#define CDDTLE94X1_CFG_SS_MOD_FR_00                                0u // spread spectrum disabled
#define CDDTLE94X1_CFG_SS_MOD_FR_01                                1u // 15.625kHz Modulation Frequency
#define CDDTLE94X1_CFG_SS_MOD_FR_02                                2u // 31.250kHz Modulation Frequency
#define CDDTLE94X1_CFG_SS_MOD_FR_03                                3u // 62.500kHz Modulation Frequency

// GPIO
#define CDDTLE94X1_CFG_GPIO_000                                    0u // FO selected (default)
#define CDDTLE94X1_CFG_GPIO_001                                    1u // FO selected
#define CDDTLE94X1_CFG_GPIO_010                                    2u // FO selected
#define CDDTLE94X1_CFG_GPIO_011                                    3u // High-Side controlled by TIMER (Cyclic Sense)
#define CDDTLE94X1_CFG_GPIO_100                                    4u // Off
#define CDDTLE94X1_CFG_GPIO_101                                    5u // Wake input enabled (16us static filter)
#define CDDTLE94X1_CFG_GPIO_110                                    6u // Low-Side Switch controlled by PWM
#define CDDTLE94X1_CFG_GPIO_111                                    7u // High-Side Switch controlled by PWM

//PWM_DC
#define CDDTLE94X1_CFG_PWM_DC_0                                    0u // 100% off, i.e. HS/LS = Off
#define CDDTLE94X1_CFG_PWM_DC_100                                0xFF // 100% on, i.e. HS/LS always On

// Register Masks
#define CDDTLE94X1_CFG_CAN_MODE_MASK                             0x07

//CHECKSUM
#define CDDTLE94X1_CFG_WD_Checksum_0                               0u // Counts as 0 for checksum calculation
#define CDDTLE94X1_CFG_WD_Checksum_1                               1u // Counts as 1 for checksum calculation

//WD_WIN
#define CDDTLE94X1_CFG_WD_TimeOut                                  0u // Watchdog works as a Time-Out watchdog
#define CDDTLE94X1_CFG_WD_Window                                   1u // Watchdog works as a Window watchdog

//WD_TIMER
#define CDDTLE94X1_CFG_WD_TIMER_10ms                               0u // 10ms
#define CDDTLE94X1_CFG_WD_TIMER_20ms                               1u // 20ms
#define CDDTLE94X1_CFG_WD_TIMER_50ms                               2u // 50ms
#define CDDTLE94X1_CFG_WD_TIMER_100ms                              3u // 100ms
#define CDDTLE94X1_CFG_WD_TIMER_200ms                              4u // 200ms
#define CDDTLE94X1_CFG_WD_TIMER_500ms                              5u // 500ms
#define CDDTLE94X1_CFG_WD_TIMER_1000ms                             6u // 1000ms
#define CDDTLE94X1_CFG_WD_TIMER_10000ms                            7u // 10000ms

#ifndef ERR_DISABLED
#define ERR_DISABLED 255U
#endif /*ERR_DISABLED*/

#ifndef ERR_SNA
#define ERR_SNA 0U
#endif /*ERR_SNA*/

#ifndef ERR_NO
#define ERR_NO 2U
#endif /*ERR_NO*/

#ifndef ERR_YES
#define ERR_YES 1U
#endif /*ERR_YES*/

#ifndef NotAvailable
#define NotAvailable 253U
#endif /*NotAvailable*/

#define OTHER_RESET 255U
#define ERROR_ACTIVE 0x5A01
//=============================================================================
//  types
//=============================================================================

//=============================================================================
//  global variable
//=============================================================================

//=============================================================================
//  inline functions
//=============================================================================

//=============================================================================
//Intern prototypes
//=============================================================================

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

#endif // EOF CDD_TLE94X1_CFG_021_03_08_H_

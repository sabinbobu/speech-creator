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
/// \file  CddMlc_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_MLC_TYPES_2024_04_01_H
#define CDD_MLC_TYPES_2024_04_01_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define CDDMLC_CFG_MAX_CHIPS  CFG_MLC_Chip_Cnt
#define CDDMLC_CFG_MAX_ADDRS  8U

#define CDDMLC_POWERUP_CYCLE_GUARD                  5U            //50ms (cyclic period x 5 )

/* MLC BUS */
#define CDDMLC_COD_MATRIX_INTERFACE_PRIVATE_CAN     0U
#define CDDMLC_COD_MATRIX_INTERFACE_SATELLITE_CAN   1U

#define CDDMLC_COD_DEV_ADDR_NOT_CONNECTED           CFG_MLC_Chip_Not_Connected
#define CDDMLC_COD_DEV_ADDR_GEN3_START              32U
#define CDDMLC_COD_DEV_GEN3_MAX_DEV_ADDRS           15U
#define CDDMLC_COD_DEV_GEN3_MASTER_OFFSET_ID        (CDDMLC_COD_DEV_GEN3_MAX_DEV_ADDRS + 1U)
#define CDDMLC_COD_DEV_ADDR_GEN3_MAX_ID             (CDDMLC_COD_DEV_ADDR_GEN3_START + CDDMLC_COD_DEV_GEN3_MAX_DEV_ADDRS + CDDMLC_COD_DEV_GEN3_MASTER_OFFSET_ID)

#define CDDMLC_TPSGEN2_3A_MAX_SWITCHES_PER_DEVICE   6U
#define CDDMLC_TPSGEN2_MAX_SWITCHES_PER_DEVICE      12U
#define CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE      CFG_MATRIX_LEDs_PER_CH_Cnt

//=============================================================================
// Sensitivity of segment fault detection and flickering avoidance 
//=============================================================================
// Minimum PWM Duty Cycle Threshold
#define CDDMLC_MIN_PWM_THD       5u    // For target values under 0.5%
// Predefined PWM Duty Cycle Applied for values under threshold
#define CDDMLC_MIN_PWM_VAL       0u    // Set predefined minimum  0.0%


//=============================================================================
// Types 
//=============================================================================

typedef enum {
  SENSOR_QLTY_INVALID = 0,                     // Invalid Value        (Init value or Timeout)
  SENSOR_QLTY_SNA   = 1,                       // Signal Not Available (Keep Last Value)
  SENSOR_QLTY_VALID = 2                        // Valid Signal         (Up-to-Date)
} teCddMlc_SigQuality;

typedef struct {
  uint8 ucADC1Value;                            // Value of 8-Bit ADC
  uint8 ucADC2Value;                            // Value of 8-Bit ADC
  teCddMlc_SigQuality eQlty;                    // Quality Factor  
} tsCddMlc_SensorData;

// Debug ----------------------------------------------------------------------
#ifndef UNIT_TEST
#define CDDMLC_Cfg_Simulation
#else
#undef CDDMLC_Cfg_Simulation
#endif // CDDMLC_MT

#ifdef CDDMLC_Cfg_Simulation
//simulation support
typedef struct
{
  uint16 unLedFault;       // used to store pixel simulated status
  boolean boCrcFault;      // used to store CRC simulated status 
}tsCddMlc_SimulationData;
#endif

#endif // CDD_MLC_TYPES_2024_04_01_H

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
/// \file  Test_Ext.h
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2024_09_17_H
#define TEST_EXT_2024_09_17_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define TEST_Cfg_Chips              7u   // support up to 7 devices for test
#define TEST_Cfg_Pixels             16u  // support up to 16 channels for test

#define TEST_BIT_ENABLED            1u
#define TEST_BIT_DISABLED           0u

#define TEST_Chip0                  0u   // chip index
#define TEST_Chip1                  1u
#define TEST_Chip2                  2u
#define TEST_Chip3                  3u
#define TEST_Chip4                  4u
#define TEST_Chip5                  5u
#define TEST_Chip6                  6u
#define TEST_ChipInvalid            7u

#define TEST_DRV_GEN2_MASTER        8u
#define TEST_DRV_GEN3_MASTER        16u
#define TEST_DRV_GEN3_OFFSET        32u

#define TEST_DRV_BAUDRATE_500Kbps   5u
#define TEST_DRV_BAUDRATE_1Mbps     10u

#define TEST_DRV_COD_TYPE_DISABLED_UART_ADDRS        { 255u, 255u, 255u, 255u, 255u, 255u, 255u                       }
#define TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS         { 0u,   255u, 2u,   255u, 4u,   5u,   255  }
#define TEST_DRV_COD_TYPE_TPSGEN3_664_UART_ADDRS     { 11u + TEST_DRV_GEN3_OFFSET + TEST_DRV_GEN3_MASTER, 255u,  255u, 255u, 255u, 255u, 12u + TEST_DRV_GEN3_OFFSET }
#define TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS       { 11u + TEST_DRV_GEN3_OFFSET + TEST_DRV_GEN3_MASTER, 255u,  12u + TEST_DRV_GEN3_OFFSET, 255u, 4u, 255u, 6u + TEST_DRV_GEN2_MASTER  }


#define TEST_DRV_PWM_1_1024_50PERCENTAGE  { 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u } 
#define TEST_DRV_PWM_1_1024_20PERCENTAGE  { 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u } 
#define TEST_DRV_PWM_1_1024_HBFLAT_16PXLS {  20u,  10u,  54u,  55u,  54u,  51u,	 45u,  39u,  10u,  20u,  30u,  40u,   0u,   0u,   3u,   0u } 
#define TEST_DRV_PWM_1_1024_00PERCENTAGE  {   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u } 

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

typedef enum {
  SENSOR_QLTY_INVALID = 0,       // Invalid Value        (Init value or Timeout)
  SENSOR_QLTY_SNA     = 1,       // Signal Not Available (Keep Last Value)
  SENSOR_QLTY_VALID   = 2        // Valid Signal         (Up-to-Date)
} teCddMlc_SigQuality;

typedef struct {
  uint8 ucADC1Value;              // Value of 8-Bit ADC
  uint8 ucADC2Value;              // Value of 8-Bit ADC
  teCddMlc_SigQuality eQlty;      // Quality Factor  
} tsCddMlc_SensorData;

typedef struct
{
  uint8*    pucTxData;
  uint8     ucTxDataLength;
  uint8*    pucRxData;
  uint8     ucRxDataLength;
  boolean   boToBeProcessed;
}tsCddUart_MessageEntryType;

//-----------------------------------------------------------------------------
// Access to other modules
//-----------------------------------------------------------------------------
boolean CddMlc_IsMlcPowered(void);

//-----------------------------------------------------------------------------
// Access to chip specific implementation
//-----------------------------------------------------------------------------

#define CDDTPSGEN3_Para_Get_CHIP_ID(ucIdx)        Test_Drv_GetCHIP_ID(ucIdx)
#define CDDTPSGEN3_Para_Get_BAUDRATE              Test_Drv_GetBAUDRATE()
#define CDDTPSGEN3_Para_IS_CODING_VALID           Test_Drv_GetCodingStatus()

//-----------------------------------------------------------------------------
// Stub functions for chip specific implementation
//-----------------------------------------------------------------------------
boolean Test_Drv_GetCodingStatus  (void);
uint8   Test_Drv_GetCHIP_ID       (uint8 ucChipIdx);
uint8   Test_Drv_GetBAUDRATE      (void);
boolean Test_Drv_IsMlcPowered     (void);

void    Test_Drv_SetCodingStatus  (boolean boCodingValid);
void    Test_Drv_SetBAUDRATE      (uint8 ucBaudRate);
void    Test_Drv_SetMlcPower      (boolean boVccxEn);
void    Test_Drv_SetCHIP_IDs      (uint8* pucCodingAddress);

//-----------------------------------------------------------------------------
// Access to coding
//-----------------------------------------------------------------------------
// Function to initialize stub values
void    RestoreStubContents(void);

#endif // TEST_EXT_2024_09_17_H

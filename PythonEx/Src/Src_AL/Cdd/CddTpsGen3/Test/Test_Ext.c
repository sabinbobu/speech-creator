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
/// \file  Test_Ext.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "Test_Ext.h"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define TEST_BACKUP 0  // index 0 used for backup
#define TEST_USE    1  // index 1 used for operation

//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------

struct
{
  boolean boCodingStatus;
  uint8   aucDrvCodingId[TEST_Cfg_Chips];
  uint8   ucBaudRate;
  uint16  aunTargetPWM[TEST_Cfg_Pixels];
  boolean boIsMlcPowered;
}
TestStruct[2] =
{
  {
    FALSE,                                        // coding status
    TEST_DRV_COD_TYPE_TPSGEN3_664_UART_ADDRS,     // coded IDs for chips
    TEST_DRV_BAUDRATE_500Kbps,                    // coded baud rate
    TEST_DRV_PWM_1_1024_00PERCENTAGE,             // target pwm
    FALSE                                         // mlc power status
  },
};

//-----------------------------------------------------------------------------
// Stub functions for chip specific implementation
//-----------------------------------------------------------------------------
boolean CddMlc_IsMlcPowered(void)                       { return Test_Drv_IsMlcPowered();                            }

//-----------------------------------------------------------------------------
// Functions to set/read stub values
//-----------------------------------------------------------------------------

boolean Test_Drv_GetCodingStatus(void)                  {   return  TestStruct[TEST_USE].boCodingStatus;             }
uint8   Test_Drv_GetCHIP_ID     (uint8 ucChipIdx)       {   return  TestStruct[TEST_USE].aucDrvCodingId[ucChipIdx];  }
uint8   Test_Drv_GetBAUDRATE    (void)                  {   return  TestStruct[TEST_USE].ucBaudRate;                 }
boolean Test_Drv_IsMlcPowered   (void)                  {   return  TestStruct[TEST_USE].boIsMlcPowered;             }

void Test_Drv_SetCodingStatus   (boolean boCodingValid) {  TestStruct[TEST_USE].boCodingStatus = boCodingValid;      }
void Test_Drv_SetBAUDRATE       (uint8 ucBaudRate)      {  TestStruct[TEST_USE].ucBaudRate     = ucBaudRate;         }
void Test_Drv_SetMlcPower       (boolean boVccxEn)      {  TestStruct[TEST_USE].boIsMlcPowered = boVccxEn;           }

void Test_Drv_SetCHIP_IDs(uint8* pucCodingAddress)
{
  for (uint8 ucChipIdx = 0u; ucChipIdx < TEST_Cfg_Chips; ucChipIdx++)
  {
    TestStruct[TEST_USE].aucDrvCodingId[ucChipIdx] = pucCodingAddress[ucChipIdx];
  }
}

//-----------------------------------------------------------------------------
// Function to initialize stub values
//-----------------------------------------------------------------------------
void RestoreStubContents(void)
{
  TestStruct[TEST_USE] = TestStruct[TEST_BACKUP];
}
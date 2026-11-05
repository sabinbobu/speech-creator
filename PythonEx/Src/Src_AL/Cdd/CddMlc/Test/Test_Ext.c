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
#include <Test_Ext.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define TEST_BACKUP 0  // index 0 used for backup
#define TEST_USE    1  // index 1 used for operation

#define TEST_DRV_INIT_MAXCHIPS(x)    { x, x, x, x, x, x, x }
#define TEST_DRV_INIT_PWMS           { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u }

//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------

tsPara_CodingArea applicationCodingData = { 
        { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A,   
          5u,     /* baud rate */
          TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS,       
          4u,     /* eeprom ID*/
          0u, 0u,   CDDMLC_CODING_LTMP_NODES } };

struct
{
  boolean boCallFct;
  boolean boVccx_EnHigh;
  boolean boIsPWR_Gen2;
  boolean boIsPWR_Gen3;
  boolean boIsDrvInit_Gen2;
  boolean boIsDrvInit_Gen3;
  boolean boReinitMtxSch;
  boolean aboIsComFaultGEN2   [TEST_Cfg_Chips];
  boolean aboIsComFaultGEN3   [TEST_Cfg_Chips];
  boolean aboIsCrcFaultGEN2   [TEST_Cfg_Chips];
  boolean aboIsCrcFaultGEN3   [TEST_Cfg_Chips];
  uint16  aunShortToGndGEN2   [TEST_Cfg_Chips];
  uint16  aunShortToGndGEN3   [TEST_Cfg_Chips];
  uint16  aunPixelDuty_1_1024 [TEST_Cfg_Chips][TEST_Cfg_Pixels];
  tsSwitchFault         asDevFaultError[TEST_Cfg_Chips];
  tsCddMlc_SensorData   asDevSensorDataGEN2[TEST_Cfg_Chips];
  tsCddMlc_SensorData   asDevSensorDataGEN3[TEST_Cfg_Chips];
}
TestStruct[2] =
{
  {
    FALSE,                                                                // Call Gen2/ Gen3 (Init/ Cycle fcts)
    FALSE,                                                                // VCCX power
    FALSE,                                                                // power on reset status GEN2
    FALSE,                                                                // power on reset status GEN3
    FALSE,                                                                // driver init status GEN2
    FALSE,                                                                // driver init status GEN3
    FALSE,                                                                // boReinitMtxSch
    {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE },     // communication fault GEN2
    {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE },     // communication fault GEN3
    {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE },     // corrupt communication fault GEN2
    {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE },     // corrupt communication fault GEN3
    {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE },     // short to GND GEN2
    {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE },     // short to GND GEN3
    TEST_DRV_INIT_MAXCHIPS(TEST_DRV_INIT_PWMS),                           // target duty cycle
    { {0x00u}, {0x00u}, {0x00u}, {0x00u}, {0x00u}, {0x00u}, {0x00u} },     // pixel fault status
    { {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID} },                              /* sensor data GEN 2*/
    { {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID}, \
      {0u, 0u, CDD_MLC_QLTY_INVALID} }                              /* sensor data GEN 3*/
  }
};

struct
{
  TestDrv_InitEEPROM   sInitEEPROM;
  TestDrv_ReadEEPROM   sReadEEPROM;
  TestDrv_WriteEEPROM  sWriteEEPROM;
}TEST_STRUCT_EEPROM[2] = 
{ 
  {
    {
      NULL_PTR,
      NULL_PTR
    },
    {
      NULL_PTR,
      0u,
      0u,
      NULL_PTR,
      NULL_PTR
    },
    {
      NULL_PTR,
      0u,
      0u,
      NULL_PTR,
      NULL_PTR
    }
  }  
};


//-----------------------------------------------------------------------------
// Stub functions for chip specific implementation
//-----------------------------------------------------------------------------
void CddTpsGen2_Init(void)    { TestStruct[TEST_USE].boCallFct = TRUE; }
void CddTpsGen2_Cycle(void)   { TestStruct[TEST_USE].boCallFct = TRUE; }
void CddTpsGen3_Init(void)    { TestStruct[TEST_USE].boCallFct = TRUE; }
void CddTpsGen3_Cycle(void)   { TestStruct[TEST_USE].boCallFct = TRUE; }

//-----------------------------------------------------------------------------
// Functions to set/read stub values
//-----------------------------------------------------------------------------

boolean Test_Drv_GetVccxEn          (void)                                                      { return TestStruct[TEST_USE].boVccx_EnHigh;                                }
boolean Test_Drv_GetPWR_Gen2        (void)                                                      { return TestStruct[TEST_USE].boIsPWR_Gen2;                                 }
boolean Test_Drv_GetPWR_Gen3        (void)                                                      { return TestStruct[TEST_USE].boIsPWR_Gen3;                                 }
boolean Test_Drv_GetDrvInit_Gen2    (void)                                                      { return TestStruct[TEST_USE].boIsDrvInit_Gen2;                             }
boolean Test_Drv_GetDrvInit_Gen3    (void)                                                      { return TestStruct[TEST_USE].boIsDrvInit_Gen3;                             }
boolean Test_Drv_GetReinitMatrix    (void)                                                      { return TestStruct[TEST_USE].boReinitMtxSch;                               }
void    Test_Drv_GetReinitMatrixRTE (boolean* pboReinit)                                        { *pboReinit = TestStruct[TEST_USE].boReinitMtxSch;                         }
boolean Test_Drv_IsFctCalled        (void)                                                      { return TestStruct[TEST_USE].boCallFct;                                    }
boolean Test_Drv_IsComFaultGEN2     (uint8_fast ucChipIdx)                                      { return TestStruct[TEST_USE].aboIsComFaultGEN2   [ucChipIdx];              }
boolean Test_Drv_IsComFaultGEN3     (uint8_fast ucChipIdx)                                      { return TestStruct[TEST_USE].aboIsComFaultGEN3   [ucChipIdx];              }
boolean Test_Drv_IsCrcFaultGEN2     (uint8_fast ucChipIdx)                                      { return TestStruct[TEST_USE].aboIsCrcFaultGEN2   [ucChipIdx];              }
boolean Test_Drv_IsCrcFaultGEN3     (uint8_fast ucChipIdx)                                      { return TestStruct[TEST_USE].aboIsCrcFaultGEN3   [ucChipIdx];              }
uint16  Test_Drv_GetShortToGndGEN2  (uint8_fast ucChipIdx)                                      { return TestStruct[TEST_USE].aunShortToGndGEN2   [ucChipIdx];              }
uint16  Test_Drv_GetShortToGndGEN3  (uint8_fast ucChipIdx)                                      { return TestStruct[TEST_USE].aunShortToGndGEN3   [ucChipIdx];              }
uint16  Test_Drv_GetDutyCycle       (uint8_fast ucChipIdx, uint8_fast ucPxlIdx)                 { return TestStruct[TEST_USE].aunPixelDuty_1_1024 [ucChipIdx][ucPxlIdx];    }
void    Test_Drv_GetSensorDataGEN2  (uint8_fast ucChipIdx, tsCddMlc_SensorData* pSensorData)    { *pSensorData  = TestStruct[TEST_USE].asDevSensorDataGEN2[ucChipIdx];      }
void    Test_Drv_GetSensorDataGEN3  (uint8_fast ucChipIdx, tsCddMlc_SensorData* pSensorData)    { *pSensorData  = TestStruct[TEST_USE].asDevSensorDataGEN3[ucChipIdx];      }


void    Test_Drv_SetVccxEn          (boolean boEnable)                                          { TestStruct[TEST_USE].boVccx_EnHigh                      = boEnable;       }
void    Test_Drv_SetPWR_Gen2        (boolean boPWR)                                             { TestStruct[TEST_USE].boIsPWR_Gen2                       = boPWR;          }
void    Test_Drv_SetPWR_Gen3        (boolean boPWR)                                             { TestStruct[TEST_USE].boIsPWR_Gen3                       = boPWR;          }
void    Test_Drv_SetDrvInit_Gen2    (boolean boDrvInit)                                         { TestStruct[TEST_USE].boIsDrvInit_Gen2                   = boDrvInit;      }
void    Test_Drv_SetDrvInit_Gen3    (boolean boDrvInit)                                         { TestStruct[TEST_USE].boIsDrvInit_Gen3                   = boDrvInit;      }
void    Test_Drv_SetReinitMatrix    (boolean boReinit)                                          { TestStruct[TEST_USE].boReinitMtxSch                     = boReinit;       }
void    Test_Drv_SetComFaultGEN2    (uint8_fast ucChipIdx, boolean boComFault)                  { TestStruct[TEST_USE].aboIsComFaultGEN2[ucChipIdx]       = boComFault;     }
void    Test_Drv_SetComFaultGEN3    (uint8_fast ucChipIdx, boolean boComFault)                  { TestStruct[TEST_USE].aboIsComFaultGEN3[ucChipIdx]       = boComFault;     }
void    Test_Drv_SetCrcFaultGEN2    (uint8_fast ucChipIdx, boolean boCrcFault)                  { TestStruct[TEST_USE].aboIsCrcFaultGEN2[ucChipIdx]       = boCrcFault;     }
void    Test_Drv_SetCrcFaultGEN3    (uint8_fast ucChipIdx, boolean boCrcFault)                  { TestStruct[TEST_USE].aboIsCrcFaultGEN3[ucChipIdx]       = boCrcFault;     }
void    Test_Drv_SetShortToGndGEN2  (uint8_fast ucChipIdx, uint16  unPxlShortGnd)               { TestStruct[TEST_USE].aunShortToGndGEN2[ucChipIdx]       = unPxlShortGnd;  }
void    Test_Drv_SetShortToGndGEN3  (uint8_fast ucChipIdx, uint16  unPxlShortGnd)               { TestStruct[TEST_USE].aunShortToGndGEN3[ucChipIdx]       = unPxlShortGnd;  }
void    Test_Drv_SetSensorDataGEN2  (uint8_fast ucChipIdx, tsCddMlc_SensorData  sSensorData)    { TestStruct[TEST_USE].asDevSensorDataGEN2[ucChipIdx]     = sSensorData;    }
void    Test_Drv_SetSensorDataGEN3  (uint8_fast ucChipIdx, tsCddMlc_SensorData  sSensorData)    { TestStruct[TEST_USE].asDevSensorDataGEN3[ucChipIdx]     = sSensorData;    }

/* setter for pixels of custom matrix chip from the string */
void Test_Drv_SetDutyCycle_1_1024(uint8_fast ucChipIdx, uint16* punDuty_1_1024)
{
  for (uint16 unPxlDuty = 0u; unPxlDuty < TEST_Cfg_Pixels; unPxlDuty++)
  {
    TestStruct[TEST_USE].aunPixelDuty_1_1024[ucChipIdx][unPxlDuty] = punDuty_1_1024[unPxlDuty];
  }
}

/* setter for all pixels from the string */
void Test_Drv_SetTgtMtxPixels(uint16* punDuty)
{
  for (uint16 unChipIdx = 0u; unChipIdx < TEST_Cfg_Chips; unChipIdx++)
  {
    for (uint16 unPxlDuty = 0u; unPxlDuty < TEST_Cfg_Pixels; unPxlDuty++)
    {
      TestStruct[TEST_USE].aunPixelDuty_1_1024[unChipIdx][unPxlDuty] = punDuty[unChipIdx * TEST_Cfg_Pixels + unPxlDuty];
    }
  }
}

void Test_Drv_GetTgtMtxPixels(uint16* punDuty)
{
  for (uint16 unChipIdx = 0u; unChipIdx < TEST_Cfg_Chips; unChipIdx++)
  {
    for (uint16 unPxlDuty = 0u; unPxlDuty < TEST_Cfg_Pixels; unPxlDuty++)
    {
      punDuty[unChipIdx * TEST_Cfg_Pixels + unPxlDuty] = TestStruct[TEST_USE].aunPixelDuty_1_1024[unChipIdx][unPxlDuty];
    }
  }
}

void Test_Drv_I2C_SetStartInit(Test_Drv_pFnct pfnInitSuccessClbk, Test_Drv_pFnct pfnInitFailedClbk)
{
  TEST_STRUCT_EEPROM[TEST_USE].sInitEEPROM.pfnInitSuccessClbk = pfnInitSuccessClbk;
  TEST_STRUCT_EEPROM[TEST_USE].sInitEEPROM.pfnInitFailedClbk  = pfnInitFailedClbk;
}

void Test_Drv_I2C_SetReadEeprom(uint8* ucData_List, uint16 unStartAddress, uint16 unLength, Test_Drv_pFnct pfnReadSuccessClbk, Test_Drv_pFnct pfnReadFailedClbk)
{
  TEST_STRUCT_EEPROM[TEST_USE].sReadEEPROM.pucReadData        = ucData_List;
  TEST_STRUCT_EEPROM[TEST_USE].sReadEEPROM.unReadStartAddress = unStartAddress;
  TEST_STRUCT_EEPROM[TEST_USE].sReadEEPROM.unReadLength       = unLength;
  TEST_STRUCT_EEPROM[TEST_USE].sReadEEPROM.pfnReadSuccessClbk = pfnReadSuccessClbk;
  TEST_STRUCT_EEPROM[TEST_USE].sReadEEPROM.pfnReadFailedClbk  = pfnReadFailedClbk;
}

void Test_Drv_I2C_SetWriteEeprom(uint8* ucData_List, uint16 unStartAddress, uint16 unLength, Test_Drv_pFnct pfnWriteSuccessClbk, Test_Drv_pFnct pfnWriteFailedClbk)
{
  TEST_STRUCT_EEPROM[TEST_USE].sWriteEEPROM.pucWriteData        = ucData_List;
  TEST_STRUCT_EEPROM[TEST_USE].sWriteEEPROM.unWriteStartAddress = unStartAddress;
  TEST_STRUCT_EEPROM[TEST_USE].sWriteEEPROM.unWriteLength       = unLength;
  TEST_STRUCT_EEPROM[TEST_USE].sWriteEEPROM.pfnWriteSuccessClbk = pfnWriteSuccessClbk;
  TEST_STRUCT_EEPROM[TEST_USE].sWriteEEPROM.pfnWriteFailedClbk  = pfnWriteFailedClbk;
}

TestDrv_InitEEPROM  Test_Drv_I2C_GetStartInit   () {  return TEST_STRUCT_EEPROM[TEST_USE].sInitEEPROM;  }
TestDrv_ReadEEPROM  Test_Drv_I2C_GetReadEeprom  () {  return TEST_STRUCT_EEPROM[TEST_USE].sReadEEPROM;  }
TestDrv_WriteEEPROM Test_Drv_I2C_GetWriteEeprom () {  return TEST_STRUCT_EEPROM[TEST_USE].sWriteEEPROM; }

void  Test_Drv_I2C_CallbackFunction_Stub() { }

//-----------------------------------------------------------------------------
// Function to initialize stub values
//-----------------------------------------------------------------------------

void RestoreStubContents(void)
{
  TestStruct[TEST_USE]           = TestStruct[TEST_BACKUP];
  TEST_STRUCT_EEPROM[TEST_USE]   = TEST_STRUCT_EEPROM[TEST_BACKUP];
  TestStruct[TEST_USE].boCallFct = FALSE;
}


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
/// \file  Test_Drv_Ext.h
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2024_08_06_H
#define TEST_EXT_2024_08_06_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <CddMlc_Cod.h>
#include <CddMlc.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define TEST_Cfg_Chips  CDDMLC_CFG_MAX_CHIPS                    // support up to 7 devices for test
#define TEST_Cfg_Pixels CDDMLC_TPSGENx_MAX_SWITCHES_PER_DEVICE  // support up to 16 channels for test

#define TEST_Chip0                 0u  // chip index
#define TEST_Chip1                 1u
#define TEST_Chip2                 2u
#define TEST_Chip3                 3u
#define TEST_Chip4                 4u
#define TEST_Chip5                 5u
#define TEST_Chip6                 6u

#define CODM_PARA_LMM_CONFIG_SIZE  7u
#define CODM_PARA_LMM_NODES_SIZE   8u

#define CDDMLC_CODING_LTMP_NODES   {252u, 114u, 174u, 88u, 54u, 32u, 20u, 10u}

#define TEST_DRV_DISABLED           0u
#define TEST_DRV_TYPE_TPSGEN2_662A  1u
#define TEST_DRV_TYPE_TPSGEN2_663A  2u
#define TEST_DRV_TYPE_TPSGEN3_664   3u
#define TEST_DRV_TYPE_TPSGEN3_665   4u
#define TEST_DRV_TYPE_TPSGEN3_667   5u
#define TEST_DRV_TYPE_TPSGENx_1     6u
#define TEST_DRV_TYPE_TPSGENx_2     7u
#define TEST_DRV_TYPE_NXP           8u  /* not supported */

#define TEST_DRV_GEN2_MASTER        8u
#define TEST_DRV_GEN3_MASTER        16u
#define TEST_DRV_GEN3_OFFSET        32u

#define TEST_DRV_COD_TYPE_DISABLED_UART_ADDRS        { 255u, 255u, 255u, 255u, 255u, 255u, 255u                       }
#define TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS         { 0u,   255u, 2u,   255u, 4u,   5u,   6u + TEST_DRV_GEN2_MASTER  }
#define TEST_DRV_COD_TYPE_TPSGEN3_664_UART_ADDRS     { 11u + TEST_DRV_GEN3_OFFSET + TEST_DRV_GEN3_MASTER, 255u,  255u, 255u, 255u, 255u, 12u + TEST_DRV_GEN3_OFFSET }
#define TEST_DRV_COD_TYPE_TPSGEN3_665_UART_ADDRS     { 11u + TEST_DRV_GEN3_OFFSET + TEST_DRV_GEN3_MASTER, 255u,  255u, 255u, 255u, 255u, 12u + TEST_DRV_GEN3_OFFSET }
#define TEST_DRV_COD_TYPE_TPSGEN3_667_UART_ADDRS     { 11u + TEST_DRV_GEN3_OFFSET + TEST_DRV_GEN3_MASTER, 255u,  255u, 255u, 255u, 255u, 12u + TEST_DRV_GEN3_OFFSET }
#define TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS       { 11u + TEST_DRV_GEN3_OFFSET + TEST_DRV_GEN3_MASTER, 255u,  12u + TEST_DRV_GEN3_OFFSET, 255u, 4u, 255u, 6u + TEST_DRV_GEN2_MASTER  }
#define TEST_DRV_COD_TYPE_NXP_UART_ADDRS             { 16u,   255u, 255u, 255u, 255u, 255u, 255u                       }

#define CDDMLC_CODINGCONFIG                                                                                                                       \
{                                                                                                                                                 \
 /* 0 */ { CDDMLC_COD_MATRIX_TYPE_DISABLED    ,   5u,   TEST_DRV_COD_TYPE_DISABLED_UART_ADDRS,      255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 1 */ { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_662A,   5u,   TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS,       4u,   0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 2 */ { CDDMLC_COD_MATRIX_TYPE_TPSGEN2_663A,   10u,  TEST_DRV_COD_TYPE_TPSGEN2_UART_ADDRS,       255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 3 */ { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_664 ,   5u,   TEST_DRV_COD_TYPE_TPSGEN3_664_UART_ADDRS,   255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 4 */ { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_665 ,   10u,  TEST_DRV_COD_TYPE_TPSGEN3_665_UART_ADDRS,   255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 5 */ { CDDMLC_COD_MATRIX_TYPE_TPSGEN3_667 ,   10u,  TEST_DRV_COD_TYPE_TPSGEN3_667_UART_ADDRS,   255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 6 */ { CDDMLC_COD_MATRIX_TYPE_TPSGENx_1   ,   5u,   TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS,     255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 7 */ { CDDMLC_COD_MATRIX_TYPE_TPSGENx_2   ,   10u,  TEST_DRV_COD_TYPE_TPSGENx_1_UART_ADDRS,     255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES },   \
 /* 8 */ { CDDMLC_COD_MATRIX_TYPE_NXP         ,   0u,   TEST_DRV_COD_TYPE_NXP_UART_ADDRS,           255u, 0u, 0u,   CDDMLC_CODING_LTMP_NODES }    \
}

/* access to UART definition of devices - for callback functions*/
#define TEST_DRV_UART_DEV_MATRIX_GEN2    0u
#define TEST_DRV_UART_DEV_MATRIX_GEN3    1u
#define TEST_DRV_UART_DEV_MATRIX_INVALID 2u

#define TEST_DRV_PWM_1_1024_50PERCENTAGE { 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u, 512u} 
#define TEST_DRV_PWM_1_1024_20PERCENTAGE { 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u, 204u} 
#define TEST_DRV_PWM_1_1024_00PERCENTAGE {   0u,   0u,   0u,   0u,   0u,   0u,   0u,   0u,  0u,   0u,   0u,   0u,  0u,   0u,   0u,   0u  } 

#define TEST_DRV_PWM_VALS_7CHIPS_16PXL_00PWMs { TEST_DRV_PWM_1_1024_00PERCENTAGE, TEST_DRV_PWM_1_1024_00PERCENTAGE, TEST_DRV_PWM_1_1024_00PERCENTAGE, TEST_DRV_PWM_1_1024_00PERCENTAGE, TEST_DRV_PWM_1_1024_00PERCENTAGE, TEST_DRV_PWM_1_1024_00PERCENTAGE, TEST_DRV_PWM_1_1024_00PERCENTAGE  }

#define TEST_DRV_PWM_VALS_7CHIPS_16PXL  \
{                                       \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,    \
  TEST_DRV_PWM_1_1024_00PERCENTAGE ,    \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,    \
  TEST_DRV_PWM_1_1024_00PERCENTAGE ,    \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,    \
  TEST_DRV_PWM_1_1024_00PERCENTAGE ,    \
  TEST_DRV_PWM_1_1024_20PERCENTAGE      \
}

#define TEST_DRV_PWM_VALS_7CHIPS_16PXL_20PERC  \
{                                              \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_20PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_20PERCENTAGE             \
}

#define TEST_DRV_PWM_VALS_7CHIPS_16PXL_50PERC  \
{                                              \
  TEST_DRV_PWM_1_1024_50PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_50PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_50PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_50PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_50PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_50PERCENTAGE ,           \
  TEST_DRV_PWM_1_1024_50PERCENTAGE             \
}

#define TEST_DRV_EEPROM_START_ADDR(ucOffset)     ucOffset 
#define TEST_DRV_EEPROM_SIZE                     256u  

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

typedef struct
{
  uint8 LMM_CHIP_TYPE;        //Which type of LMM controller is used
  uint8 LMM_UART_COMM_SPEED;  // Select the speed (kbps) for LMM UART communication
  uint8 LMM__UART_CAN_ADDRESSES[CODM_PARA_LMM_CONFIG_SIZE]; // Values: 0.. 7;255 ~255= no LMM;TPS92662A&TPS92663A // (TI) Addr. 0…7 are allowed
  uint8 EEPROM_ADDRESS; // Values: 0.. 7;255 ~255= no EEPROM ~ EEPROM, connected to LMM address
  uint8 ucLMM_OC_SC_RETRY_COUNTER;
  uint8 ucLMM_OC_SC_RETRY_DELAY;
  uint8 ucLTMP_LMM_NODES[CODM_PARA_LMM_NODES_SIZE];
}tsPara_LmmConfig_Diagnosis;

typedef struct
{
  tsPara_LmmConfig_Diagnosis LMM_Config_Diagnosis;
} tsPara_LmmBlock;

typedef struct
{
  tsPara_LmmBlock LmmConfig;
}tsPara_CodingArea;

extern tsPara_CodingArea applicationCodingData;

typedef void(*Test_Drv_pFnct)(void);          // I2C Callback Function Definition

typedef struct TestDrv_InitEEPROM
{
  Test_Drv_pFnct pfnInitSuccessClbk;
  Test_Drv_pFnct pfnInitFailedClbk;
}TestDrv_InitEEPROM;

typedef struct TestDrv_ReadEEPROM
{
  uint8*          pucReadData;
  uint16          unReadStartAddress;
  uint16          unReadLength;
  Test_Drv_pFnct  pfnReadSuccessClbk;
  Test_Drv_pFnct  pfnReadFailedClbk;
}TestDrv_ReadEEPROM;

typedef struct TestDrv_WriteEEPROM
{
  uint8*          pucWriteData;
  uint16          unWriteStartAddress;
  uint16          unWriteLength;
  Test_Drv_pFnct  pfnWriteSuccessClbk;
  Test_Drv_pFnct  pfnWriteFailedClbk;
}TestDrv_WriteEEPROM;


//-----------------------------------------------------------------------------
// Access to other modules
//-----------------------------------------------------------------------------

#define CDDMLC_IS_VCCX_POWERED                          Test_Drv_GetVccxEn() 

#define CDDMLC_GET_TARGET_PWM(pTarget)                  Test_Drv_GetTgtMtxPixels(pTarget)
#define CDDMLC_GET_REINIT_MLC(pTarget)                  Test_Drv_GetReinitMatrixRTE(pTarget)

#define CDDMLC_GET_VCCX_FAULT(pTarget)                  (void)Rte_Read_IoHwAbUser_VccxLineState(pTarget);

#define CDDMLC_RTE_SEND_MTX_COMM_STATUS(pTarget)        (void)Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal(pTarget);
#define CDDMLC_RTE_SEND_MTX_CRC_STATUS(pTarget)         (void)Rte_Write_CtrlPxl_CddMlc_CrcError_sVal(pTarget);
#define CDDMLC_RTE_SEND_MTX_PXL_FAULT(pTarget)          (void)Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal(pTarget);
#define CDDMLC_RTE_SEND_MTX_ADC_DATA(pTarget)           (void)Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal(pTarget);
#define CDDMLC_RTE_SEND_CLR_REINIT_MLC(pTarget)         (void)Rte_Write_CtrlPxl_CddMlc_ReinitMatrix(pTarget);
#define CDDMLC_RTE_SEND_MTX_INIT_STATUS(pTarget)        (void)Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal(pTarget);

//-----------------------------------------------------------------------------
// Access to chip specific implementation
//-----------------------------------------------------------------------------

#define CDDMLC_DRV_GEN2_SetDutyCycle(DrvId, Duty)         Test_Drv_SetDutyCycle_1_1024(DrvId, Duty)
#define CDDMLC_DRV_GEN3_SetDutyCycle(DrvId, Duty)         Test_Drv_SetDutyCycle_1_1024(DrvId, Duty)

#define CDDMLC_DRV_GEN2_ReinitMatrix(Cmd)                 Test_Drv_SetReinitMatrix(Cmd)
#define CDDMLC_DRV_GEN3_ReinitMatrix(Cmd)                 Test_Drv_SetReinitMatrix(Cmd)

#define CDDMLC_DRV_GEN2_IsShortToGnd(DrvId)               Test_Drv_GetShortToGndGEN2(DrvId)
#define CDDMLC_DRV_GEN2_IsComFault(DrvId)                 Test_Drv_IsComFaultGEN2(DrvId)

#define CDDMLC_DRV_GEN3_IsShortToGnd(DrvId)               Test_Drv_GetShortToGndGEN3(DrvId)
#define CDDMLC_DRV_GEN3_IsComFault(DrvId)                 Test_Drv_IsComFaultGEN3(DrvId)

#define CDDMLC_DRV_GEN2_GetSensorInfo(DrvId, pData)       Test_Drv_GetSensorDataGEN2(DrvId, pData)
#define CDDMLC_DRV_GEN3_GetSensorInfo(DrvId, pData)       Test_Drv_GetSensorDataGEN3(DrvId, pData)

#define CDDMLC_DRV_GEN2_GetPWRStatus(void)                Test_Drv_GetPWR_Gen2()
#define CDDMLC_DRV_GEN3_GetPWRStatus(void)                Test_Drv_GetPWR_Gen3()

#define CDDMLC_DRV_GEN2_IsCrcFault(DrvId)                 Test_Drv_IsCrcFaultGEN2(DrvId)
#define CDDMLC_DRV_GEN3_IsCrcFault(DrvId)                 Test_Drv_IsCrcFaultGEN3(DrvId)

#define CDDMLC_DRV_GEN2_IsDrvInit(void)                   Test_Drv_GetDrvInit_Gen2()
#define CDDMLC_DRV_GEN3_IsDrvInit(void)                   Test_Drv_GetDrvInit_Gen3()


#define CDDMLC_DRV_GEN2_InitEEprom(CbOk, CbNOk)                     (void)Test_Drv_I2C_SetStartInit  (CbOk, CbNOk)
#define CDDMLC_DRV_GEN2_ReadEEprom(pData, Adr, Len, CbOk, CbNOk)    (void)Test_Drv_I2C_SetReadEeprom (pData, Adr, Len, CbOk, CbNOk)
#define CDDMLC_DRV_GEN2_WriteEEprom(pData, Adr, Len, CbOk, CbNOk)   (void)Test_Drv_I2C_SetWriteEeprom(pData, Adr, Len, CbOk, CbNOk)

#define CDDMLC_EEPROM_TIMEOUT(void)                                 // intentionally empty
#define CDDMLC_EEPROM_CONNECTED_ID(void)                            applicationCodingData.LmmConfig.LMM_Config_Diagnosis.EEPROM_ADDRESS

//-----------------------------------------------------------------------------
// Stub functions for chip specific implementation
//-----------------------------------------------------------------------------
extern void CddTpsGen2_Init (void);
extern void CddTpsGen2_Cycle(void);
extern void CddTpsGen3_Init (void);
extern void CddTpsGen3_Cycle(void);

//-----------------------------------------------------------------------------
// Access to coding
//-----------------------------------------------------------------------------

// Functions to set/read stub values
boolean Test_Drv_GetVccxEn          (void);
boolean Test_Drv_GetPWR_Gen2        (void);
boolean Test_Drv_GetPWR_Gen3        (void);
boolean Test_Drv_GetDrvInit_Gen2    (void);
boolean Test_Drv_GetDrvInit_Gen3    (void);
boolean Test_Drv_GetReinitMatrix    (void);
void    Test_Drv_GetReinitMatrixRTE (boolean* pboReinit);
boolean Test_Drv_IsFctCalled        (void);
boolean Test_Drv_IsComFaultGEN2     (uint8_fast ucChipIdx);
boolean Test_Drv_IsComFaultGEN3     (uint8_fast ucChipIdx);
boolean Test_Drv_IsCrcFaultGEN2     (uint8_fast ucChipIdx);
boolean Test_Drv_IsCrcFaultGEN3     (uint8_fast ucChipIdx);
uint16  Test_Drv_GetShortToGndGEN2  (uint8_fast ucChipIdx);
uint16  Test_Drv_GetShortToGndGEN3  (uint8_fast ucChipIdx);
uint16  Test_Drv_GetDutyCycle       (uint8_fast ucChipIdx, uint8_fast ucPxlIdx);
void    Test_Drv_GetSensorDataGEN2  (uint8_fast ucChipIdx, tsCddMlc_SensorData* pSensorData);
void    Test_Drv_GetSensorDataGEN3  (uint8_fast ucChipIdx, tsCddMlc_SensorData* pSensorData);
void    Test_Drv_GetTgtMtxPixels    (uint16* punDuty);


void    Test_Drv_SetVccxEn          (boolean boEnable);
void    Test_Drv_SetPWR_Gen2        (boolean boPWR);
void    Test_Drv_SetPWR_Gen3        (boolean boPWR);
void    Test_Drv_SetDrvInit_Gen2    (boolean botDrvInit);
void    Test_Drv_SetDrvInit_Gen3    (boolean botDrvInit);
void    Test_Drv_SetReinitMatrix    (boolean boReinit);
void    Test_Drv_SetComFaultGEN2    (uint8_fast ucChipIdx, boolean boComFault);
void    Test_Drv_SetComFaultGEN3    (uint8_fast ucChipIdx, boolean boComFault);
void    Test_Drv_SetCrcFaultGEN2    (uint8_fast ucChipIdx, boolean boCrcFault);
void    Test_Drv_SetCrcFaultGEN3    (uint8_fast ucChipIdx, boolean boCrcFault);
void    Test_Drv_SetShortToGndGEN2  (uint8_fast ucChipIdx, uint16  unPxlShortGnd);
void    Test_Drv_SetShortToGndGEN3  (uint8_fast ucChipIdx, uint16  unPxlShortGnd);
void    Test_Drv_SetSensorDataGEN2  (uint8_fast ucChipIdx, tsCddMlc_SensorData  sSensorData);
void    Test_Drv_SetSensorDataGEN3  (uint8_fast ucChipIdx, tsCddMlc_SensorData  sSensorData);
void    Test_Drv_SetDutyCycle_1_1024(uint8_fast ucChipIdx, uint16* punDuty_1_1024);
void    Test_Drv_SetTgtMtxPixels    (uint16* punDuty);

void Test_Drv_I2C_SetStartInit      (Test_Drv_pFnct pfnInitSuccessClbk, Test_Drv_pFnct pfnInitFailedClbk);
void Test_Drv_I2C_SetReadEeprom     (uint8* ucData_List, uint16 unStartAddress, uint16 unLength, Test_Drv_pFnct pfnReadSuccessClbk,  Test_Drv_pFnct pfnReadFailedClbk);
void Test_Drv_I2C_SetWriteEeprom    (uint8* ucData_List, uint16 unStartAddress, uint16 unLength, Test_Drv_pFnct pfnWriteSuccessClbk, Test_Drv_pFnct pfnWriteFailedClbk);

TestDrv_InitEEPROM  Test_Drv_I2C_GetStartInit   (void);
TestDrv_ReadEEPROM  Test_Drv_I2C_GetReadEeprom  (void);
TestDrv_WriteEEPROM Test_Drv_I2C_GetWriteEeprom (void);
void                Test_Drv_I2C_CallbackFunction_Stub(void);

// Function to initialize stub values
void    RestoreStubContents(void);

#endif // TEST_EXT_2024_08_06_H

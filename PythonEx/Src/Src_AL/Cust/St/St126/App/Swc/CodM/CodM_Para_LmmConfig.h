#ifndef __CODM_PARA_LMMCONFIG_H__
#define __CODM_PARA_LMMCONFIG_H__
//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

///-----------------------------------------------------------------------------
///  \file   NvM_Para_LmmConfig.h
///
///  \brief  Content of datagroup "LmmConfig"
///
///  \descr  Source: LDMO_CodingTool_FULL.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author This file is auto generated - please do not edit
///
///  \date   11.08.2021, 16:51:19
///-----------------------------------------------------------------------------
#define CODM_PARA_LMM_CONFIG_SIZE  7u
#define CODM_PARA_LMM_NODES_SIZE   8u

typedef struct
{
uint8 ucLMM_CHIP_TYPE                 ; //Which type of LMM controller is used

uint8 unLMM_UART_COMM_SPEED;

uint8 ucLMM__UART_CAN_ADDRESSES[CODM_PARA_LMM_CONFIG_SIZE]; // Values: 0.. 7;255 ~255= no LMM;TPS92662A&TPS92663A // (TI) Addr. 0…7 are allowed

                                        // (TI) Addr. 0…7 are allowed
uint8 ucEEPROM_ADDRESS                ; // Values: 0.. 7;255 ~255= no EEPROM ~ EEPROM
                                        // connected to LMM address
uint8 ucLMM_OC_SC_RETRY_COUNTER       ; // Values 0..255~ Number of times the ECU tries
                                        // to turn on the Segment after failure detection
                                        // before a defect is recorded
uint8 ucLMM_OC_SC_RETRY_DELAY         ; // Unit: 10ms ~ Values 0..2550ms ~ Time between
                                        // retries
uint8 ucLTMP_LMM_NODES[CODM_PARA_LMM_NODES_SIZE]             ; // Values: 0.. 255 ~ ADC Value from LMM Register ~ ADC value at -40°C
}
tsNvmPara_LmmConfig_LMM_Config_Diagnosis;

typedef struct 
{
  tsNvmPara_LmmConfig_LMM_Config_Diagnosis LMM_Config_Diagnosis;
} tsNvmPara_LmmConfigBlock;



#endif // __CODM_PARA_LMMCONFIG_H__

// EOF
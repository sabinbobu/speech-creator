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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <Fee_TargetTypes.h>

//=============================================================================
// Typedef
//=============================================================================

typedef struct
{
  uint8_t brownOutCode;               /*!< Brown-out detection code */
  uint16_t numOfRecordReqMaintain;    /*!< Number of EEPROM quick write records requiring maintenance */
  uint16_t sectorEraseCount;          /*!< EEPROM sector erase count */
} flash_eeprom_status_t;


//=============================================================================
// Stub function declarations
//=============================================================================
status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf, flash_ssd_config_t * const pSSDConfig);
status_t FLASH_DRV_DEFlashPartition(const flash_ssd_config_t * pSSDConfig, uint8_t uEEEDataSizeCode, uint8_t uDEPartitionCode, uint8_t uCSEcKeySize, bool uSFE, bool flexRamEnableLoadEEEData);
status_t FLASH_DRV_SetFlexRamFunction(const flash_ssd_config_t * pSSDConfig, flash_flexRam_function_control_code_t flexRamFuncCode, uint16_t byteOfQuickWrite, flash_eeprom_status_t * const pEEPROMStatus);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern flash_user_config_t*                  FLASH_DRV_Init_Param1;
extern flash_ssd_config_t*                   FLASH_DRV_Init_Param2;
extern flash_ssd_config_t*                   FLASH_DRV_DEFlashPartition_Param1;
extern uint8_t                               FLASH_DRV_DEFlashPartition_Param2;
extern uint8_t                               FLASH_DRV_DEFlashPartition_Param3;
extern uint8_t                               FLASH_DRV_DEFlashPartition_Param4;
extern bool                                  FLASH_DRV_DEFlashPartition_Param5;
extern bool                                  FLASH_DRV_DEFlashPartition_Param6;
extern flash_ssd_config_t*                   FLASH_DRV_SetFlexRamFunction_Param1;
extern flash_flexRam_function_control_code_t FLASH_DRV_SetFlexRamFunction_Param2;
extern uint16_t                              FLASH_DRV_SetFlexRamFunction_Param3;
extern flash_eeprom_status_t*                FLASH_DRV_SetFlexRamFunction_Param4;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern status_t FLASH_DRV_Init_RetVal;
extern status_t FLASH_DRV_DEFlashPartition_RetVal;
extern status_t FLASH_DRV_SetFlexRamFunction_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 FLASH_DRV_Init_HitCount;
extern uint8 FLASH_DRV_DEFlashPartition_HitCount;
extern uint8 FLASH_DRV_SetFlexRamFunction_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

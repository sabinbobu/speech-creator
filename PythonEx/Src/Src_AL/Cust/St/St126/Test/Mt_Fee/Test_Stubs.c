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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"


//=============================================================================
// Stub function parameter stubs
//=============================================================================

flash_user_config_t*                  FLASH_DRV_Init_Param1;
flash_ssd_config_t*                   FLASH_DRV_Init_Param2;
flash_ssd_config_t*                   FLASH_DRV_DEFlashPartition_Param1;
uint8_t                               FLASH_DRV_DEFlashPartition_Param2;
uint8_t                               FLASH_DRV_DEFlashPartition_Param3;
uint8_t                               FLASH_DRV_DEFlashPartition_Param4;
bool                                  FLASH_DRV_DEFlashPartition_Param5;
bool                                  FLASH_DRV_DEFlashPartition_Param6;
flash_ssd_config_t*                   FLASH_DRV_SetFlexRamFunction_Param1;
flash_flexRam_function_control_code_t FLASH_DRV_SetFlexRamFunction_Param2;
uint16_t                              FLASH_DRV_SetFlexRamFunction_Param3;
flash_eeprom_status_t*                FLASH_DRV_SetFlexRamFunction_Param4;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

status_t FLASH_DRV_Init_RetVal;
status_t FLASH_DRV_DEFlashPartition_RetVal;
status_t FLASH_DRV_SetFlexRamFunction_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 FLASH_DRV_Init_HitCount;
uint8 FLASH_DRV_DEFlashPartition_HitCount;
uint8 FLASH_DRV_SetFlexRamFunction_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  FLASH_DRV_Init
///
/// \descr  Stub function to simulate the behavior of the FLASH_DRV_Init
///
/// \param  pUserConf
/// \param  pSSDConfig
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf, flash_ssd_config_t * const pSSDConfig)
{
  FLASH_DRV_Init_Param1 = pUserConf;
  FLASH_DRV_Init_Param2 = pSSDConfig;
  FLASH_DRV_Init_HitCount++;
  return FLASH_DRV_Init_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FLASH_DRV_DEFlashPartition
///
/// \descr  Stub function to simulate the behaviour of FLASH_DRV_DEFlashPartition
///
/// \param  pSSDConfig
/// \param  uEEEDataSizeCode
/// \param  uDEPartitionCode
/// \param  uCSEcKeySize
/// \param  uSFE
/// \param  flexRamEnableLoadEEEData
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t FLASH_DRV_DEFlashPartition(const flash_ssd_config_t * pSSDConfig, uint8_t uEEEDataSizeCode, uint8_t uDEPartitionCode, uint8_t uCSEcKeySize, bool uSFE, bool flexRamEnableLoadEEEData)
{
  FLASH_DRV_DEFlashPartition_Param1 = pSSDConfig;
  FLASH_DRV_DEFlashPartition_Param2 = uEEEDataSizeCode;
  FLASH_DRV_DEFlashPartition_Param3 = uDEPartitionCode;
  FLASH_DRV_DEFlashPartition_Param4 = uCSEcKeySize;
  FLASH_DRV_DEFlashPartition_Param5 = uSFE;
  FLASH_DRV_DEFlashPartition_Param6 = flexRamEnableLoadEEEData;
  FLASH_DRV_DEFlashPartition_HitCount++;
  return FLASH_DRV_DEFlashPartition_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FLASH_DRV_SetFlexRamFunction
///
/// \descr  Stub function to simulate the behavior of FLASH_DRV_SetFlexRamFunction
///
/// \param  pSSDConfig
/// \param  flexRamFuncCode
/// \param  byteOfQuickWrite
/// \param  pEEPROMStatus
///
/// \return status_t
//-----------------------------------------------------------------------------
status_t FLASH_DRV_SetFlexRamFunction(const flash_ssd_config_t * pSSDConfig, flash_flexRam_function_control_code_t flexRamFuncCode, uint16_t byteOfQuickWrite, flash_eeprom_status_t * const pEEPROMStatus)
{
  FLASH_DRV_SetFlexRamFunction_Param1 = pSSDConfig;
  FLASH_DRV_SetFlexRamFunction_Param2 = flexRamFuncCode;
  FLASH_DRV_SetFlexRamFunction_Param3 = byteOfQuickWrite;
  FLASH_DRV_SetFlexRamFunction_Param4 = pEEPROMStatus;
  FLASH_DRV_SetFlexRamFunction_HitCount++;
  return FLASH_DRV_SetFlexRamFunction_RetVal;
}

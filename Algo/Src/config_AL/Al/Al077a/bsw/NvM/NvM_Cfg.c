#include "Fee_Cfg.h"
#include "NvM_Cfg.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_CfgRamBlock_2[NVM_CFG_BLOCK_2_LENGTH]; /* Permanent RAM data for NvM block 2. */
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
#define NVM_START_SEC_CONST_8
#include "NvM_MemMap.h"
const uint8 NvM_CfgRomDefaults_2[NVM_CFG_BLOCK_2_LENGTH] = { 9U, 8U, 7U, 6U, 5U, 4U, 3U, 2U }; /* ROM default data for NvM block 2. */
#define NVM_STOP_SEC_CONST_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_CfgRamBlock_3[NVM_CFG_BLOCK_3_LENGTH]; /* Permanent RAM data for NvM block 3. */
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
#define NVM_START_SEC_CONST_8
#include "NvM_MemMap.h"
const uint8 NvM_CfgRomDefaults_3[NVM_CFG_BLOCK_3_LENGTH] = { 1U, 3U, 5U, 7U, 9U, 11U, 13U, 15U }; /* ROM default data for NvM block 3. */
#define NVM_STOP_SEC_CONST_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_CfgRamBlock_4[NVM_CFG_BLOCK_4_LENGTH]; /* Permanent RAM data for NvM block 4. */
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
#define NVM_START_SEC_CONST_8
#include "NvM_MemMap.h"
const uint8 NvM_CfgRomDefaults_4[NVM_CFG_BLOCK_4_LENGTH] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }; /* ROM default data for NvM block 4. */
#define NVM_STOP_SEC_CONST_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_CfgRamBlock_5[NVM_CFG_BLOCK_5_LENGTH]; /* Permanent RAM data for NvM block 5. */
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
#define NVM_START_SEC_CONST_8
#include "NvM_MemMap.h"
const uint8 NvM_CfgRomDefaults_5[NVM_CFG_BLOCK_5_LENGTH] = { 0U }; /* ROM default data for NvM block 5. */
#define NVM_STOP_SEC_CONST_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_CONST_8
#include "NvM_MemMap.h"
const uint8 NvM_CfgRomDefaults_6[NVM_CFG_BLOCK_6_LENGTH] = { 6U, 5U, 4U, 3U, 2U, 1U, 0U, 9U }; /* ROM default data for NvM block 6. */
#define NVM_STOP_SEC_CONST_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_CfgRamBlock_7[NVM_CFG_BLOCK_7_LENGTH]; /* Permanent RAM data for NvM block 7. */
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_CfgRamBlock_8[NVM_CFG_BLOCK_8_LENGTH]; /* Permanent RAM data for NvM block 8. */
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
#define NVM_START_SEC_CONST_8
#include "NvM_MemMap.h"
const uint8 NvM_CfgRomDefaults_8[NVM_CFG_BLOCK_8_LENGTH] = { 8U, 7U, 6U, 5U, 4U, 3U, 2U, 1U }; /* ROM default data for NvM block 8. */
#define NVM_STOP_SEC_CONST_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "NvM_MemMap.h"
const NvM_BlockDescriptorType NvM_BlockDescriptorTable[NVM_CFG_BLOCK_COUNT] =
{
    {
        2U, /* NvM block identifier. */
        8U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_16_ID, /* Primary Fee block reference: FEE_BLOCK_16_ID; NvMTargetBlockReference/NvMFeeRef. */
        0U, /* Redundant Fee block reference: not used; NvMTargetBlockReference/NvMFeeRef. */
        1U, /* Number of configured Fee copies. */
        32U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_NATIVE, /* Native management. */
        NvM_CfgRamBlock_2, /* Permanent RAM data pointer. */
        NvM_CfgRomDefaults_2, /* ROM defaults pointer. */
        NULL_PTR, /* No initialization callback configured. */
        FALSE, /* Write protection disabled. */
        FALSE, /* Write-once behavior disabled. */
        TRUE, /* Data is retained across software changes. */
        0U, /* Additional retries after failed reads. */
        0U, /* Additional retries after failed writes. */
        TRUE, /* CRC protection enabled. */
        NVM_CRC16, /* Configured CRC algorithm: crc16. */
        TRUE, /* Compare RAM CRC with stored CRC. */
        TRUE, /* Maintain CRC for the RAM copy. */
        TRUE, /* Allow NvM_SetRamBlockStatus for this block. */
        TRUE, /* Selected for NvM_ReadAll. */
        TRUE, /* Selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    },
    {
        3U, /* NvM block identifier. */
        8U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_17_ID, /* Primary Fee block reference: FEE_BLOCK_17_ID; NvMTargetBlockReference/NvMFeeRef. */
        FEE_BLOCK_33_ID, /* Redundant Fee block reference: FEE_BLOCK_33_ID; NvMTargetBlockReference/NvMFeeRef. */
        2U, /* Number of configured Fee copies. */
        24U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_REDUNDANT, /* Redundant management. */
        NvM_CfgRamBlock_3, /* Permanent RAM data pointer. */
        NvM_CfgRomDefaults_3, /* ROM defaults pointer. */
        NULL_PTR, /* No initialization callback configured. */
        FALSE, /* Write protection disabled. */
        TRUE, /* Write-once behavior enabled. */
        TRUE, /* Data is retained across software changes. */
        1U, /* Additional retries after failed reads. */
        1U, /* Additional retries after failed writes. */
        TRUE, /* CRC protection enabled. */
        NVM_CRC8, /* Configured CRC algorithm: crc8. */
        FALSE, /* Do not compare RAM CRC with stored CRC. */
        FALSE, /* Do not maintain CRC for the RAM copy. */
        TRUE, /* Allow NvM_SetRamBlockStatus for this block. */
        TRUE, /* Selected for NvM_ReadAll. */
        TRUE, /* Selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    },
    {
        4U, /* NvM block identifier. */
        8U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_32_ID, /* Primary Fee block reference: FEE_BLOCK_32_ID; NvMTargetBlockReference/NvMFeeRef. */
        0U, /* Redundant Fee block reference: not used; NvMTargetBlockReference/NvMFeeRef. */
        1U, /* Number of configured Fee copies. */
        48U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_NATIVE, /* Native management. */
        NvM_CfgRamBlock_4, /* Permanent RAM data pointer. */
        NvM_CfgRomDefaults_4, /* ROM defaults pointer. */
        NULL_PTR, /* No initialization callback configured. */
        FALSE, /* Write protection disabled. */
        FALSE, /* Write-once behavior disabled. */
        TRUE, /* Data is retained across software changes. */
        0U, /* Additional retries after failed reads. */
        0U, /* Additional retries after failed writes. */
        TRUE, /* CRC protection enabled. */
        NVM_CRC32, /* Configured CRC algorithm: crc32. */
        FALSE, /* Do not compare RAM CRC with stored CRC. */
        TRUE, /* Maintain CRC for the RAM copy. */
        TRUE, /* Allow NvM_SetRamBlockStatus for this block. */
        TRUE, /* Selected for NvM_ReadAll. */
        TRUE, /* Selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    },
    {
        5U, /* NvM block identifier. */
        1U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_48_ID, /* Primary Fee block reference: FEE_BLOCK_48_ID; NvMTargetBlockReference/NvMFeeRef. */
        0U, /* Redundant Fee block reference: not used; NvMTargetBlockReference/NvMFeeRef. */
        1U, /* Number of configured Fee copies. */
        16U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_NATIVE, /* Native management. */
        NvM_CfgRamBlock_5, /* Permanent RAM data pointer. */
        NvM_CfgRomDefaults_5, /* ROM defaults pointer. */
        NULL_PTR, /* No initialization callback configured. */
        TRUE, /* Write protection enabled. */
        FALSE, /* Write-once behavior disabled. */
        TRUE, /* Data is retained across software changes. */
        0U, /* Additional retries after failed reads. */
        0U, /* Additional retries after failed writes. */
        FALSE, /* CRC protection disabled. */
        NVM_CRC_NONE, /* Configured CRC algorithm: none. */
        FALSE, /* Do not compare RAM CRC with stored CRC. */
        FALSE, /* Do not maintain CRC for the RAM copy. */
        TRUE, /* Allow NvM_SetRamBlockStatus for this block. */
        TRUE, /* Selected for NvM_ReadAll. */
        TRUE, /* Selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    },
    {
        6U, /* NvM block identifier. */
        8U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_65_ID, /* Primary Fee block reference: FEE_BLOCK_65_ID; NvMTargetBlockReference/NvMFeeRef. */
        0U, /* Redundant Fee block reference: not used; NvMTargetBlockReference/NvMFeeRef. */
        1U, /* Number of configured Fee copies. */
        64U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_NATIVE, /* Native management. */
        NULL_PTR, /* No permanent RAM pointer; caller supplies RAM. */
        NvM_CfgRomDefaults_6, /* ROM defaults pointer. */
        NULL_PTR, /* No initialization callback configured. */
        FALSE, /* Write protection disabled. */
        FALSE, /* Write-once behavior disabled. */
        TRUE, /* Data is retained across software changes. */
        0U, /* Additional retries after failed reads. */
        0U, /* Additional retries after failed writes. */
        TRUE, /* CRC protection enabled. */
        NVM_CRC16, /* Configured CRC algorithm: crc16. */
        FALSE, /* Do not compare RAM CRC with stored CRC. */
        FALSE, /* Do not maintain CRC for the RAM copy. */
        FALSE, /* Do not allow NvM_SetRamBlockStatus for this block. */
        FALSE, /* Not selected for NvM_ReadAll. */
        FALSE, /* Not selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    },
    {
        7U, /* NvM block identifier. */
        8U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_80_ID, /* Primary Fee block reference: FEE_BLOCK_80_ID; NvMTargetBlockReference/NvMFeeRef. */
        0U, /* Redundant Fee block reference: not used; NvMTargetBlockReference/NvMFeeRef. */
        1U, /* Number of configured Fee copies. */
        64U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_NATIVE, /* Native management. */
        NvM_CfgRamBlock_7, /* Permanent RAM data pointer. */
        NULL_PTR, /* No ROM defaults configured. */
        NULL_PTR, /* No initialization callback configured. */
        FALSE, /* Write protection disabled. */
        FALSE, /* Write-once behavior disabled. */
        TRUE, /* Data is retained across software changes. */
        0U, /* Additional retries after failed reads. */
        0U, /* Additional retries after failed writes. */
        TRUE, /* CRC protection enabled. */
        NVM_CRC8, /* Configured CRC algorithm: crc8. */
        FALSE, /* Do not compare RAM CRC with stored CRC. */
        FALSE, /* Do not maintain CRC for the RAM copy. */
        TRUE, /* Allow NvM_SetRamBlockStatus for this block. */
        TRUE, /* Selected for NvM_ReadAll. */
        TRUE, /* Selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    },
    {
        8U, /* NvM block identifier. */
        8U, /* Number of data bytes in this block. */
        0U, /* MemIf device index; this profile uses device 0. */
        FEE_BLOCK_64_ID, /* Primary Fee block reference: FEE_BLOCK_64_ID; NvMTargetBlockReference/NvMFeeRef. */
        FEE_BLOCK_81_ID, /* Redundant Fee block reference: FEE_BLOCK_81_ID; NvMTargetBlockReference/NvMFeeRef. */
        2U, /* Number of configured Fee copies. */
        128U, /* Fee payload capacity in bytes. */
        NVM_BLOCK_REDUNDANT, /* Redundant management. */
        NvM_CfgRamBlock_8, /* Permanent RAM data pointer. */
        NvM_CfgRomDefaults_8, /* ROM defaults pointer. */
        NULL_PTR, /* No initialization callback configured. */
        FALSE, /* Write protection disabled. */
        FALSE, /* Write-once behavior disabled. */
        TRUE, /* Data is retained across software changes. */
        0U, /* Additional retries after failed reads. */
        0U, /* Additional retries after failed writes. */
        FALSE, /* CRC protection disabled. */
        NVM_CRC_NONE, /* Configured CRC algorithm: none. */
        FALSE, /* Do not compare RAM CRC with stored CRC. */
        FALSE, /* Do not maintain CRC for the RAM copy. */
        TRUE, /* Allow NvM_SetRamBlockStatus for this block. */
        TRUE, /* Selected for NvM_ReadAll. */
        TRUE, /* Selected for NvM_WriteAll. */
        FALSE /* Do not report block status to BswM. */
    }
};
#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "NvM_MemMap.h"

#ifndef NVM_CFG_H
#define NVM_CFG_H

#include "NvM_Types.h"

#define NVM_CFG_BLOCK_COUNT 7U /* Number of configured NvM block descriptors. */
#define NVM_CFG_COMPILED_CONFIG_ID 1U /* Compiled configuration identity; NVM-SWS §3.3. */
#define NVM_CFG_MAIN_FUNCTION_PERIOD_SECONDS 0.01F /* NVMCommon NvMMainFunctionPeriod, in seconds. */
#define NVM_CFG_STANDARD_JOB_QUEUE_SIZE 4U /* Maximum number of standard asynchronous jobs that can wait in the NvM queue. */
#define NVM_CFG_CRC_BYTES_PER_CALL 3U /* Maximum incremental CRC data bytes per main-function call. */
#define NVM_CFG_SET_RAM_BLOCK_STATUS_API 1U /* Enable NvM_SetRamBlockStatus in the API profile. */
#define NVM_CFG_VERSION_INFO_API 1U /* Enable NvM_GetVersionInfo in the API profile. */
#define NVM_CFG_VENDOR_ID 1U /* AUTOSAR vendor identifier reported by NvM. */
#define NVM_CFG_MODULE_ID 20U /* AUTOSAR module identifier assigned to NvM. */
#define NVM_CFG_SW_MAJOR_VERSION 1U /* Major software version returned by NvM. */
#define NVM_CFG_SW_MINOR_VERSION 0U /* Minor software version returned by NvM. */
#define NVM_CFG_SW_PATCH_VERSION 0U /* Patch software version returned by NvM. */
#define NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION 0U /* Enable global multi-block BswM status notifications. */
#define NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION 0U /* At least one block enables BswM block status notifications. */
#define NVM_CFG_SINGLE_BLOCK_CALLBACK_ENABLED 0U /* Single-block completion callback configured. */
#define NVM_CFG_MULTI_BLOCK_CALLBACK_ENABLED 0U /* Multi-block completion callback configured. */
#define NVM_CFG_DEM_ENABLED 0U /* Any DEM event IDs are configured. */
#define NVM_CFG_DEM_EVENT_HARDWARE_ENABLED 0U /* Event enabled for hardware or lower-layer failure. */
#define NVM_CFG_DEM_EVENT_HARDWARE_ID 0U /* DEM identifier for hardware or lower-layer failure. */
#define NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ENABLED 0U /* Event enabled for stored block integrity validation failure. */
#define NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ID 0U /* DEM identifier for stored block integrity validation failure. */
#define NVM_CFG_DEM_EVENT_REQUEST_FAILED_ENABLED 0U /* Event enabled for NvM request failure. */
#define NVM_CFG_DEM_EVENT_REQUEST_FAILED_ID 0U /* DEM identifier for NvM request failure. */
#define NVM_CFG_DEM_EVENT_LOSS_OF_REDUNDANCY_ENABLED 0U /* Event enabled for loss of one valid redundant storage copy. */
#define NVM_CFG_DEM_EVENT_LOSS_OF_REDUNDANCY_ID 0U /* DEM identifier for loss of one valid redundant storage copy. */
#define NVM_CFG_DEM_EVENT_WRITE_PROTECTED_ENABLED 0U /* Event enabled for write request rejected because the block is protected. */
#define NVM_CFG_DEM_EVENT_WRITE_PROTECTED_ID 0U /* DEM identifier for write request rejected because the block is protected. */
#define NVM_CFG_MAX_PHYSICAL_BLOCK_LENGTH 128U /* Largest referenced physical Fee payload, in bytes. */

typedef struct
{
    NvM_BlockIdType block_id;
    uint16 block_length;
    uint8 memif_device_index;
    uint16 memif_block_number;
    uint16 memif_redundant_block_number;
    uint8 nv_block_count;
    uint16 fee_block_size;
    NvM_BlockManagementType management_type;
    uint8 *ram_ptr;
    const uint8 *rom_ptr;
    NvM_InitBlockCallbackType init_block_callback;
    boolean write_protected;
    boolean write_once;
    boolean resistant_to_changed_sw;
    uint8 max_read_retries;
    uint8 max_write_retries;
    boolean crc_enabled;
    NvM_CrcType crc_type;
    boolean crc_compare_mechanism;
    boolean calc_ram_block_crc;
    boolean use_set_ram_block_status;
    boolean select_block_for_read_all;
    boolean select_block_for_write_all;
    boolean bswm_block_status_information;
} NvM_BlockDescriptorType;
typedef NvM_BlockDescriptorType NvM_BlockConfigType;

#define NVM_CFG_BLOCK_2_LENGTH 8U /* NvM block 2 data length in bytes. */
extern uint8 NvM_CfgRamBlock_2[NVM_CFG_BLOCK_2_LENGTH]; /* Permanent RAM data for NvM block 2. */
extern const uint8 NvM_CfgRomDefaults_2[NVM_CFG_BLOCK_2_LENGTH]; /* ROM defaults for NvM block 2. */
#define NVM_CFG_BLOCK_3_LENGTH 8U /* NvM block 3 data length in bytes. */
extern uint8 NvM_CfgRamBlock_3[NVM_CFG_BLOCK_3_LENGTH]; /* Permanent RAM data for NvM block 3. */
extern const uint8 NvM_CfgRomDefaults_3[NVM_CFG_BLOCK_3_LENGTH]; /* ROM defaults for NvM block 3. */
#define NVM_CFG_BLOCK_4_LENGTH 8U /* NvM block 4 data length in bytes. */
extern uint8 NvM_CfgRamBlock_4[NVM_CFG_BLOCK_4_LENGTH]; /* Permanent RAM data for NvM block 4. */
extern const uint8 NvM_CfgRomDefaults_4[NVM_CFG_BLOCK_4_LENGTH]; /* ROM defaults for NvM block 4. */
#define NVM_CFG_BLOCK_5_LENGTH 1U /* NvM block 5 data length in bytes. */
extern uint8 NvM_CfgRamBlock_5[NVM_CFG_BLOCK_5_LENGTH]; /* Permanent RAM data for NvM block 5. */
extern const uint8 NvM_CfgRomDefaults_5[NVM_CFG_BLOCK_5_LENGTH]; /* ROM defaults for NvM block 5. */
#define NVM_CFG_BLOCK_6_LENGTH 8U /* NvM block 6 data length in bytes. */
extern const uint8 NvM_CfgRomDefaults_6[NVM_CFG_BLOCK_6_LENGTH]; /* ROM defaults for NvM block 6. */
#define NVM_CFG_BLOCK_7_LENGTH 8U /* NvM block 7 data length in bytes. */
extern uint8 NvM_CfgRamBlock_7[NVM_CFG_BLOCK_7_LENGTH]; /* Permanent RAM data for NvM block 7. */
#define NVM_CFG_BLOCK_8_LENGTH 8U /* NvM block 8 data length in bytes. */
extern uint8 NvM_CfgRamBlock_8[NVM_CFG_BLOCK_8_LENGTH]; /* Permanent RAM data for NvM block 8. */
extern const uint8 NvM_CfgRomDefaults_8[NVM_CFG_BLOCK_8_LENGTH]; /* ROM defaults for NvM block 8. */

extern const NvM_BlockDescriptorType NvM_BlockDescriptorTable[NVM_CFG_BLOCK_COUNT];

#endif /* NVM_CFG_H */

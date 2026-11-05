#ifndef NVM_TYPES_H
#define NVM_TYPES_H

#include "Std_Types.h"

typedef uint16 NvM_BlockIdType;

typedef enum
{
    NVM_CRC_NONE = 0U,
    NVM_CRC8 = 1U,
    NVM_CRC16 = 2U,
    NVM_CRC32 = 3U
} NvM_CrcType;

typedef enum
{
    NVM_BLOCK_NATIVE = 0U,
    NVM_BLOCK_REDUNDANT = 1U
} NvM_BlockManagementType;

typedef enum
{
    NVM_REQ_OK = 0x00U,
    NVM_REQ_NOT_OK = 0x01U,
    NVM_REQ_PENDING = 0x02U,
    NVM_REQ_INTEGRITY_FAILED = 0x03U,
    NVM_REQ_BLOCK_SKIPPED = 0x04U,
    NVM_REQ_NV_INVALIDATED = 0x05U,
    NVM_REQ_CANCELED = 0x06U,
    NVM_REQ_REDUNDANCY_FAILED = 0x07U,
    NVM_REQ_RESTORED_FROM_ROM = 0x08U,
    NVM_REQ_VERIFY_FAILED = 0x09U
} NvM_RequestResultType;

typedef enum
{
    NVM_READ_BLOCK = 0U,
    NVM_WRITE_BLOCK = 1U,
    NVM_RESTORE_BLOCK_DEFAULTS = 2U,
    NVM_ERASE_NV_BLOCK = 3U,
    NVM_INVALIDATE_NV_BLOCK = 4U,
    NVM_READ_ALL_BLOCK = 5U
} NvM_BlockRequestType;

typedef enum
{
    NVM_READ_ALL = 0U,
    NVM_WRITE_ALL = 1U,
    NVM_VALIDATE_ALL = 2U,
    NVM_FIRST_INIT_ALL = 3U,
    NVM_CANCEL_WRITE_ALL = 4U
} NvM_MultiBlockRequestType;

typedef enum
{
    NVM_INIT_READ_BLOCK = 0U,
    NVM_INIT_RESTORE_BLOCK_DEFAULTS = 1U,
    NVM_INIT_READ_ALL_BLOCK = 2U,
    NVM_INIT_FIRST_INIT_ALL = 3U
} NvM_InitBlockRequestType;

typedef Std_ReturnType (*NvM_InitBlockCallbackType)(NvM_InitBlockRequestType InitBlockRequest);

typedef struct
{
    uint8 reserved;
} NvM_ConfigType;

#endif /* NVM_TYPES_H */
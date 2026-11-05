/* Integration-owned requirements (no NvM code): NVM-SWS-033 (Fee region/geometry),
 * NVM-SWS-034 (physical storage format owned by Fee) and NVM-SWS-035 (Fls/Fee callback routing
 * and scheduling); NvM only polls MemIf, see NVM-SWS-030..032. */
#include "NvM.h"
#include "NvM_Cfg.h"
#include "NvM_MemIf.h"
#include "SchM_NvM.h"
#if NVM_CFG_DEM_ENABLED
#include "Dem.h"
#endif
#include "MemIf.h"
#include "Crc.h"
#if (NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION != 0U) || \
    (NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION != 0U)
#include NVM_CFG_BSWM_INTERFACE_INCLUDE
#endif

#include <string.h>

#define NVM_MAX_PHYSICAL_BLOCK_LENGTH NVM_CFG_MAX_PHYSICAL_BLOCK_LENGTH

#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"

typedef enum
{
    NVM_JOB_IDLE = 0U,
    NVM_JOB_READ,
    NVM_JOB_WRITE,
    NVM_JOB_RESTORE,
    NVM_JOB_READ_ALL,
    NVM_JOB_WRITE_ALL
} NvM_JobType;

typedef enum
{
    NVM_CRC_JOB_IDLE = 0U,
    NVM_CRC_JOB_WRITE,
    NVM_CRC_JOB_READ
} NvM_CrcJobType;

static const NvM_BlockConfigType *nvm_blocks;
static uint16 nvm_block_count;
static boolean nvm_initialized;
static NvM_JobType nvm_job;
static NvM_BlockIdType nvm_job_block;
static boolean nvm_job_is_multi;
static uint8 nvm_retry_count;
static boolean nvm_io_started;
static NvM_CrcJobType nvm_crc_job;
static uint16 nvm_crc_offset;
static uint32 nvm_crc_value;
static uint32 nvm_crc_expected;
static NvM_JobType nvm_queue_job[NVM_CFG_STANDARD_JOB_QUEUE_SIZE];
static NvM_BlockIdType nvm_queue_block[NVM_CFG_STANDARD_JOB_QUEUE_SIZE];
static void *nvm_queue_client_buffer[NVM_CFG_STANDARD_JOB_QUEUE_SIZE];
static const void *nvm_queue_write_source[NVM_CFG_STANDARD_JOB_QUEUE_SIZE];
static boolean nvm_queue_client_read[NVM_CFG_STANDARD_JOB_QUEUE_SIZE];
static uint16 nvm_queue_head;
static uint16 nvm_queue_tail;
static uint16 nvm_queue_count;
static NvM_RequestResultType nvm_result[NVM_CFG_BLOCK_COUNT];
static boolean nvm_ram_valid[NVM_CFG_BLOCK_COUNT];
static boolean nvm_ram_changed[NVM_CFG_BLOCK_COUNT];
static boolean nvm_write_protected[NVM_CFG_BLOCK_COUNT];
static uint32 nvm_last_crc[NVM_CFG_BLOCK_COUNT];
static boolean nvm_last_crc_valid[NVM_CFG_BLOCK_COUNT];
static uint32 nvm_ram_crc[NVM_CFG_BLOCK_COUNT];
static boolean nvm_ram_crc_valid[NVM_CFG_BLOCK_COUNT];
static boolean nvm_background_crc_pending[NVM_CFG_BLOCK_COUNT];
static boolean nvm_background_crc_active;
static uint16 nvm_background_crc_block_index;
static uint16 nvm_background_crc_offset;
static uint32 nvm_background_crc_value;
static uint8 nvm_last_read_copy[NVM_CFG_BLOCK_COUNT];
static uint8 nvm_active_copy;
static uint8 nvm_redundant_copy_attempts;
static boolean nvm_redundant_write_success;
static boolean nvm_redundant_read_fallback;
static boolean nvm_redundant_write_failure;
static boolean nvm_multi_cancel_requested;
static boolean nvm_multi_started;
static boolean nvm_multi_failed;
static NvM_RequestResultType nvm_multi_result;
static void *nvm_client_buffer;
static const void *nvm_client_write_source;
static boolean nvm_client_read;
static NvM_JobType nvm_multi_job;
static NvM_JobType nvm_pending_multi_job;
static uint16 nvm_multi_index;
static boolean nvm_multi_active;
static boolean nvm_pending_multi_active;
static uint8 nvm_transfer_buffer[NVM_MAX_PHYSICAL_BLOCK_LENGTH];

#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"

STATIC void NvM_ResetClientBuffer(void);
STATIC void NvM_Finish(NvM_BlockIdType id, NvM_RequestResultType result);
STATIC Std_ReturnType NvM_Start(NvM_BlockIdType id, NvM_JobType job, boolean multi_job);
STATIC Std_ReturnType NvM_SubmitActiveJob(const NvM_BlockConfigType *block);
/* NVM-API-001, -003, -005; MT_NvM_MainFunction_006 and MT_NvM_MainFunction_008. */
STATIC Std_ReturnType NvM_Enqueue(NvM_BlockIdType id, NvM_JobType job, void *client_buffer,
                                  const void *write_source, boolean client_read);
STATIC void NvM_ResetQueue(void);
STATIC void NvM_FinishMultiBlock(void);
STATIC void NvM_QueueMultiBlock(NvM_JobType job);

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

#if NVM_CFG_DEM_ENABLED
STATIC void NvM_ReportDemEvent(Dem_EventIdType event_id, Dem_EventStatusType event_status)
{
    (void)Dem_SetEventStatus(event_id, event_status);
}
#endif
STATIC void NvM_BeginCrcCalculation(NvM_CrcJobType job, const NvM_BlockConfigType *block);
STATIC void NvM_ProcessCrcChunk(void);
STATIC void NvM_ProcessBackgroundCrc(void);

STATIC uint16 NvM_CrcSize(const NvM_BlockConfigType *block)
{
    uint16 size = 0U;
    if (block->crc_enabled != FALSE)
    {
        if (block->crc_type == NVM_CRC8)
        {
            size = 1U;
        }
        else if (block->crc_type == NVM_CRC16)
        {
            size = 2U;
        }
        else if (block->crc_type == NVM_CRC32)
        {
            size = 4U;
        }
        else
        {
            /* Unsupported CRC type retains the initialized zero size. */
        }
    }
    return size;
}

STATIC uint16 NvM_PhysicalLength(const NvM_BlockConfigType *block)
{
    return (uint16)(block->block_length + NvM_CrcSize(block));
}

STATIC void NvM_StoreCrc(uint8 *buffer, uint16 offset, NvM_CrcType type, uint32 crc)
{
    buffer[offset] = (uint8)crc;
    if (type == NVM_CRC16)
    {
        buffer[offset + 1U] = (uint8)(crc >> 8U);
    }
    else if (type == NVM_CRC32)
    {
        buffer[offset + 1U] = (uint8)(crc >> 8U);
        buffer[offset + 2U] = (uint8)(crc >> 16U);
        buffer[offset + 3U] = (uint8)(crc >> 24U);
    }
    else
    {
        /* CRC8 is already stored in the first byte. */
    }
}

STATIC uint32 NvM_LoadCrc(const uint8 *buffer, uint16 offset, NvM_CrcType type)
{
    uint32 crc = buffer[offset];
    if (type == NVM_CRC16)
    {
        crc |= (uint32)buffer[offset + 1U] << 8U;
    }
    else if (type == NVM_CRC32)
    {
        crc |= (uint32)buffer[offset + 1U] << 8U;
        crc |= (uint32)buffer[offset + 2U] << 16U;
        crc |= (uint32)buffer[offset + 3U] << 24U;
    }
    else
    {
        /* CRC8 is already loaded from the first byte. */
    }
    return crc;
}

STATIC void NvM_BeginCrcCalculation(NvM_CrcJobType job, const NvM_BlockConfigType *block)
{
    nvm_crc_job = job;
    nvm_crc_offset = 0U;
    nvm_crc_value = 0UL;
    nvm_crc_expected = (job == NVM_CRC_JOB_READ) ?
                           NvM_LoadCrc(nvm_transfer_buffer, block->block_length, block->crc_type) :
                           0UL;
}

/* Precondition: admission and NvM_IsConfigurationValid guarantee a non-null source and
 * NvM_PhysicalLength(block) <= fee_block_size <= NVM_MAX_PHYSICAL_BLOCK_LENGTH. */
STATIC void NvM_PrepareWrite(const NvM_BlockConfigType *block, const uint8 *source)
{
    uint16 physical_length = NvM_PhysicalLength(block);
    (void)memcpy(nvm_transfer_buffer, source, block->block_length);
    if (block->crc_enabled != FALSE)
    {
        NvM_BeginCrcCalculation(NVM_CRC_JOB_WRITE, block);
    }
    if (block->fee_block_size > physical_length)
    {
        /* NVM-CFG-003: fill configured Fee capacity after the user data and CRC. */
        (void)memset(&nvm_transfer_buffer[physical_length], 0xFFU,
                     (size_t)(block->fee_block_size - physical_length));
    }
}

STATIC boolean NvM_IsConfigurationValid(const NvM_BlockConfigType *blocks, uint16 block_count)
{
    /* NVM-CFG-001..004: enforce the configured ID, block-type, device and Fee mapping bounds. */
    boolean valid = FALSE;
    if ((blocks != NULL) && (block_count == NVM_CFG_BLOCK_COUNT))
    {
        uint16 max_block_id = 0xFFFFU;
        for (uint16 index = 0U; index < block_count; ++index)
        {
            if (blocks[index].management_type == NVM_BLOCK_REDUNDANT)
            {
                /* NVM-CFG-001/002; MT_NvM_Init_003: redundancy limits IDs to 15 bits. */
                max_block_id = 0x7FFFU;
                break;
            }
        }
        valid = TRUE;
        for (uint16 index = 0U; index < block_count; ++index)
        {
            const NvM_BlockConfigType *block = &blocks[index];
            if ((block->block_id < 2U) || (block->block_id > max_block_id) ||
                (block->block_length == 0U) ||
                (block->block_length > NVM_MAX_PHYSICAL_BLOCK_LENGTH) ||
                ((block->management_type != NVM_BLOCK_NATIVE) &&
                 (block->management_type != NVM_BLOCK_REDUNDANT)) ||
                ((block->management_type == NVM_BLOCK_NATIVE) &&
                 (block->nv_block_count != 1U)) ||
                ((block->management_type == NVM_BLOCK_REDUNDANT) &&
                 (block->nv_block_count != 2U)) ||
                ((block->ram_ptr == NULL) &&
                 ((block->calc_ram_block_crc != FALSE) ||
                  (block->use_set_ram_block_status != FALSE))) ||
                (block->memif_device_index != 0U) ||
                (block->memif_block_number == 0U) ||
                (block->memif_block_number == 0xFFFFU) ||
                ((block->management_type == NVM_BLOCK_NATIVE) &&
                 (block->memif_redundant_block_number != 0U)) ||
                ((block->management_type == NVM_BLOCK_REDUNDANT) &&
                 ((block->memif_redundant_block_number == 0U) ||
                  (block->memif_redundant_block_number == 0xFFFFU) ||
                  (block->memif_redundant_block_number == block->memif_block_number))) ||
                ((block->bswm_block_status_information != FALSE) &&
                 (block->bswm_block_status_information != TRUE)) ||
                (NvM_PhysicalLength(block) > NVM_MAX_PHYSICAL_BLOCK_LENGTH) ||
                ((block->crc_type != NVM_CRC_NONE) && (block->crc_type != NVM_CRC8) &&
                 (block->crc_type != NVM_CRC16) && (block->crc_type != NVM_CRC32)) ||
                ((block->crc_enabled == FALSE) && (block->crc_type != NVM_CRC_NONE)) ||
                ((block->crc_enabled != FALSE) && (NvM_CrcSize(block) == 0U)) ||
                (block->fee_block_size < NvM_PhysicalLength(block)) ||
                (block->fee_block_size > NVM_MAX_PHYSICAL_BLOCK_LENGTH))
            {
                valid = FALSE;
            }
            for (uint16 previous = 0U; previous < index; ++previous)
            {
                if (block->block_id == blocks[previous].block_id)
                {
                    valid = FALSE;
                }
            }
        }
    }
    return valid;
}

STATIC uint16 NvM_FindBlockIndex(NvM_BlockIdType id)
{
    uint16 index = 0U;
    while ((index < nvm_block_count) && (nvm_blocks[index].block_id != id))
    {
        ++index;
    }
    return index;
}

STATIC const NvM_BlockConfigType *NvM_FindBlock(NvM_BlockIdType id)
{
    uint16 index = NvM_FindBlockIndex(id);
    return (index < nvm_block_count) ? &nvm_blocks[index] : NULL;
}

/* Precondition: id belongs to an accepted request, hence to the validated descriptor table. */
STATIC const NvM_BlockConfigType *NvM_GetBlock(NvM_BlockIdType id)
{
    return &nvm_blocks[NvM_FindBlockIndex(id)];
}

STATIC uint16 NvM_ActiveMemIfBlockNumber(const NvM_BlockConfigType *block)
{
    return ((block->management_type == NVM_BLOCK_REDUNDANT) && (nvm_active_copy != 0U)) ?
               block->memif_redundant_block_number : block->memif_block_number;
}

/* NVM-SWS-018; MT_NvM_ReadBlock_012: try the other redundant copy once. */
STATIC boolean NvM_TrySecondaryRead(const NvM_BlockConfigType *block)
{
    boolean submitted = FALSE;
    if ((block->management_type == NVM_BLOCK_REDUNDANT) &&
        (nvm_redundant_read_fallback == FALSE))
    {
        nvm_active_copy = (uint8)(1U - nvm_active_copy);
        nvm_redundant_read_fallback = TRUE;
        nvm_retry_count = 0U;
        nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
        submitted = TRUE;
    }
    return submitted;
}

STATIC void NvM_SetResultLocked(NvM_BlockIdType id, NvM_RequestResultType result)
{
    if (id == 0U)
    {
        nvm_multi_result = result;
    }
    else
    {
        uint16 index = NvM_FindBlockIndex(id);
        uint16 offset;
        uint16 queue_index = nvm_queue_head;
        NvM_RequestResultType stored_result = result;
        for (offset = 0U; offset < nvm_queue_count; ++offset)
        {
            if (nvm_queue_block[queue_index] == id)
            {
                /* NVM-SWS-011: a newer accepted request keeps the block result pending. */
                stored_result = NVM_REQ_PENDING;
                break;
            }
            queue_index = (uint16)((queue_index + 1U) % NVM_CFG_STANDARD_JOB_QUEUE_SIZE);
        }
        nvm_result[index] = stored_result;
    }
}

STATIC void NvM_SetResult(NvM_BlockIdType id, NvM_RequestResultType result)
{
    SchM_Enter_NvM();
    NvM_SetResultLocked(id, result);
    SchM_Exit_NvM();
}

#if NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION
STATIC NvM_MultiBlockRequestType NvM_BswM_MultiBlockRequest(
    NvM_JobType job, NvM_RequestResultType result)
{
    NvM_MultiBlockRequestType request = NVM_READ_ALL;
    if (job == NVM_JOB_WRITE_ALL)
    {
        request = (result == NVM_REQ_CANCELED) ? NVM_CANCEL_WRITE_ALL : NVM_WRITE_ALL;
    }
    return request;
}
#endif

STATIC void NvM_FinishMultiBlock(void)
{
    NvM_JobType completed_job = nvm_multi_job;
    NvM_RequestResultType completed_result;
    if (nvm_multi_cancel_requested != FALSE)
    {
        completed_result = NVM_REQ_CANCELED;
    }
    else if (nvm_multi_failed != FALSE)
    {
        completed_result = NVM_REQ_NOT_OK;
    }
    else
    {
        completed_result = NVM_REQ_OK;
    }
    nvm_multi_result = completed_result;
    if (nvm_pending_multi_active != FALSE)
    {
        nvm_multi_job = nvm_pending_multi_job;
        nvm_pending_multi_active = FALSE;
        nvm_multi_index = 0U;
        nvm_multi_started = FALSE;
        nvm_multi_cancel_requested = FALSE;
        nvm_multi_failed = FALSE;
        nvm_multi_result = NVM_REQ_PENDING;
    }
    else
    {
        nvm_multi_active = FALSE;
        nvm_multi_started = FALSE;
        nvm_multi_cancel_requested = FALSE;
    }
    NvM_SetResult(0U, nvm_multi_result);
#if NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION
    /* SWS_NvM_00889: publish the result after aggregate state is finalized. */
    BswM_NvM_CurrentJobMode(
        NvM_BswM_MultiBlockRequest(completed_job, completed_result), completed_result);
#endif
#if NVM_CFG_DEM_EVENT_REQUEST_FAILED_ENABLED
    if ((completed_job == NVM_JOB_READ_ALL) && (completed_result == NVM_REQ_NOT_OK))
    {
        /* NVM-SWS-036 and §7/T-07: report a terminal ReadAll failure after aggregation. */
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_REQUEST_FAILED_ID, DEM_EVENT_STATUS_FAILED);
    }
#endif
#if NVM_CFG_MULTI_BLOCK_CALLBACK_ENABLED && \
    !NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION
    NvM_MultiBlockRequestType callback_request = NVM_READ_ALL;
    if (completed_job == NVM_JOB_WRITE_ALL)
    {
        callback_request = (completed_result == NVM_REQ_CANCELED) ?
                               NVM_CANCEL_WRITE_ALL : NVM_WRITE_ALL;
    }
    /* NVM-SWS §3.3/§4.3: notify after publishing the terminal aggregate result. */
    (void)NVM_CFG_MULTI_BLOCK_CALLBACK(callback_request, completed_result);
#endif
}

STATIC void NvM_SetJobPending(NvM_BlockIdType id, NvM_JobType job, boolean multi_job)
{
    uint16 block_index = NvM_FindBlockIndex(id);
    nvm_job_block = id;
    nvm_job = job;
    nvm_job_is_multi = multi_job;
    nvm_retry_count = 0U;
    nvm_io_started = FALSE;
    nvm_crc_job = NVM_CRC_JOB_IDLE;
    nvm_active_copy = 0U;
    nvm_redundant_copy_attempts = 0U;
    nvm_redundant_write_success = FALSE;
    nvm_redundant_read_fallback = FALSE;
    nvm_redundant_write_failure = FALSE;
    if (nvm_blocks[block_index].management_type == NVM_BLOCK_REDUNDANT)
    {
        nvm_active_copy = (job == NVM_JOB_WRITE) ?
                              (uint8)(1U - nvm_last_read_copy[block_index]) :
                              nvm_last_read_copy[block_index];
    }
    SchM_Enter_NvM();
    if (job == NVM_JOB_READ)
    {
        /* NVM-SWS-018: invalidate PRAM when a single-block or ReadAll read starts. */
        nvm_ram_valid[block_index] = FALSE;
    }
    NvM_SetResultLocked(id, NVM_REQ_PENDING);
    SchM_Exit_NvM();
}

STATIC void NvM_ResetQueue(void)
{
    uint16 index;
    nvm_queue_head = 0U;
    nvm_queue_tail = 0U;
    nvm_queue_count = 0U;
    for (index = 0U; index < NVM_CFG_STANDARD_JOB_QUEUE_SIZE; ++index)
    {
        nvm_queue_job[index] = NVM_JOB_IDLE;
        nvm_queue_block[index] = 0U;
        nvm_queue_client_buffer[index] = NULL;
        nvm_queue_write_source[index] = NULL;
        nvm_queue_client_read[index] = FALSE;
    }
}

STATIC Std_ReturnType NvM_Enqueue(NvM_BlockIdType id, NvM_JobType job, void *client_buffer,
                                  const void *write_source, boolean client_read)
{
    Std_ReturnType result = E_NOT_OK;
    /* Precondition: the public caller validated initialization and the block ID. */
    uint16 block_index = NvM_FindBlockIndex(id);
    SchM_Enter_NvM();
    if (nvm_queue_count < NVM_CFG_STANDARD_JOB_QUEUE_SIZE)
    {
        nvm_queue_block[nvm_queue_tail] = id;
        nvm_queue_job[nvm_queue_tail] = job;
        nvm_queue_client_buffer[nvm_queue_tail] = client_buffer;
        nvm_queue_write_source[nvm_queue_tail] = write_source;
        nvm_queue_client_read[nvm_queue_tail] = client_read;
        nvm_queue_tail = (uint16)((nvm_queue_tail + 1U) % NVM_CFG_STANDARD_JOB_QUEUE_SIZE);
        ++nvm_queue_count;
        NvM_SetResultLocked(id, NVM_REQ_PENDING);
        if (job == NVM_JOB_READ)
        {
            nvm_ram_valid[block_index] = FALSE;
        }
        else if (job == NVM_JOB_WRITE)
        {
            nvm_ram_valid[block_index] = TRUE;
            nvm_ram_changed[block_index] = TRUE;
        }
        else
        {
        }
        result = E_OK;
    }
    SchM_Exit_NvM();
#if NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION
    /* SWS_NvM_00890: notify only after the single-block request was accepted. */
    if ((result == E_OK) &&
        (nvm_blocks[block_index].bswm_block_status_information != FALSE))
    {
        BswM_NvM_CurrentBlockMode(id, NVM_REQ_PENDING);
    }
#endif
    return result;
}

STATIC Std_ReturnType NvM_StartNextQueuedJob(void)
{
    Std_ReturnType result = E_NOT_OK;
    boolean have_job = FALSE;
    boolean wait_for_background_crc = FALSE;
    NvM_BlockIdType id = 0U;
    NvM_JobType job = NVM_JOB_IDLE;
    SchM_Enter_NvM();
    /* Precondition (NvM_MainFunction): no active job and a nonempty queue. */
    id = nvm_queue_block[nvm_queue_head];
    job = nvm_queue_job[nvm_queue_head];
    if ((job == NVM_JOB_WRITE) &&
        (nvm_blocks[NvM_FindBlockIndex(id)].calc_ram_block_crc != FALSE) &&
        (nvm_background_crc_pending[NvM_FindBlockIndex(id)] != FALSE))
    {
        /* NVM-SWS-007; MT_NvM_MainFunction_016: hold the write until its RAM CRC completes. */
        wait_for_background_crc = TRUE;
    }
    if (wait_for_background_crc == FALSE)
    {
        nvm_client_buffer = nvm_queue_client_buffer[nvm_queue_head];
        nvm_client_write_source = nvm_queue_write_source[nvm_queue_head];
        nvm_client_read = nvm_queue_client_read[nvm_queue_head];
        nvm_queue_head = (uint16)((nvm_queue_head + 1U) % NVM_CFG_STANDARD_JOB_QUEUE_SIZE);
        --nvm_queue_count;
        have_job = TRUE;
    }
    SchM_Exit_NvM();
    if (have_job != FALSE)
    {
        result = NvM_Start(id, job, FALSE);
        if (result != E_OK)
        {
            NvM_SetResult(id, NVM_REQ_NOT_OK);
        }
    }
    else
    {
        /* NvM_MainFunction calls this only for a nonempty queue; an undequeued job awaits its RAM CRC. */
        NvM_ProcessBackgroundCrc();
        result = E_OK;
    }
    return result;
}

STATIC void NvM_ResetClientBuffer(void)
{
    nvm_client_buffer = NULL;
    nvm_client_write_source = NULL;
    nvm_client_read = FALSE;
}

STATIC NvM_RequestResultType NvM_ConvertMemIfResult(MemIf_JobResultType result)
{
    NvM_RequestResultType converted = NVM_REQ_NOT_OK;
    if (result == MEMIF_JOB_OK)
    {
        converted = NVM_REQ_OK;
    }
    else if (result == MEMIF_BLOCK_INVALID)
    {
        /* NVM-SWS-018: preserve invalidation as NV_INVALIDATED, not default recovery. */
        converted = NVM_REQ_NV_INVALIDATED;
    }
    else if (result == MEMIF_JOB_CANCELED)
    {
        converted = NVM_REQ_CANCELED;
    }
    else
    {
        converted = NVM_REQ_NOT_OK;
    }
    return converted;
}

STATIC boolean NvM_IsBusyStatus(MemIf_StatusType status)
{
    boolean busy = FALSE;
    if ((status == MEMIF_BUSY) || (status == MEMIF_BUSY_INTERNAL))
    {
        busy = TRUE;
    }
    return busy;
}

STATIC Std_ReturnType NvM_SubmitActiveJob(const NvM_BlockConfigType *block)
{
    Std_ReturnType result = E_NOT_OK;
    /* NVM-SWS-030..032: NvM uses only MemIf and forwards configured logical block numbers. */
    if (nvm_job == NVM_JOB_READ)
    {
        result = MemIf_Read(block->memif_device_index, NvM_ActiveMemIfBlockNumber(block), 0U,
                            nvm_transfer_buffer, NvM_PhysicalLength(block));
    }
    else
    {
        /* Only asynchronous write jobs remain; NvM_Start submits only read or write jobs. */
        result = MemIf_Write(block->memif_device_index, NvM_ActiveMemIfBlockNumber(block),
                             nvm_transfer_buffer);
    }
    return result;
}

/* Copy source data to the permanent RAM block or, if absent, to the caller buffer.
 * Precondition: request admission guarantees one of the two destinations. */
STATIC void NvM_CopyToDestination(const NvM_BlockConfigType *block, const void *source)
{
    void *destination = block->ram_ptr;
    if (destination == NULL)
    {
        destination = nvm_client_buffer;
    }
    (void)memcpy(destination, source, block->block_length);
}

/* Complete a CRC job once the last chunk has been processed. */
STATIC void NvM_CompleteCrcJob(const NvM_BlockConfigType *block)
{
    NvM_CrcJobType completed_job = nvm_crc_job;
    nvm_crc_job = NVM_CRC_JOB_IDLE;
    if ((completed_job == NVM_CRC_JOB_READ) && (nvm_crc_value != nvm_crc_expected))
    {
#if NVM_CFG_DEM_EVENT_HARDWARE_ENABLED
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_HARDWARE_ID, DEM_EVENT_STATUS_FAILED);
#endif
#if NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ENABLED
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ID, DEM_EVENT_STATUS_FAILED);
#endif
    }
    if (completed_job == NVM_CRC_JOB_WRITE)
    {
        uint16 block_index = NvM_FindBlockIndex(nvm_job_block);
        if ((block->crc_compare_mechanism != FALSE) &&
            (nvm_last_crc_valid[block_index] != FALSE) &&
            (nvm_last_crc[block_index] == nvm_crc_value))
        {
            NvM_Finish(nvm_job_block, NVM_REQ_OK);
        }
        else
        {
            NvM_StoreCrc(nvm_transfer_buffer, block->block_length, block->crc_type,
                         nvm_crc_value);
            nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
        }
    }
    else if (nvm_crc_value == nvm_crc_expected)
    {
        uint16 block_index = NvM_FindBlockIndex(nvm_job_block);
        NvM_CopyToDestination(block, nvm_transfer_buffer);
        nvm_last_crc[block_index] = nvm_crc_value;
        nvm_last_crc_valid[block_index] = TRUE;
        NvM_Finish(nvm_job_block, NVM_REQ_OK);
    }
    else if (nvm_retry_count < block->max_read_retries)
    {
        ++nvm_retry_count;
        nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
    }
    else if (NvM_TrySecondaryRead(block) != FALSE)
    {
        /* Secondary copy read has been started; completion is handled by the next poll. */
    }
    else if (block->rom_ptr != NULL)
    {
        NvM_CopyToDestination(block, block->rom_ptr);
        NvM_Finish(nvm_job_block, NVM_REQ_RESTORED_FROM_ROM);
    }
    else if ((block->init_block_callback != NULL) &&
             (block->init_block_callback(NVM_INIT_RESTORE_BLOCK_DEFAULTS) == E_OK))
    {
        if (block->ram_ptr == NULL)
        {
            NvM_Finish(nvm_job_block, NVM_REQ_INTEGRITY_FAILED);
        }
        else
        {
            uint16 block_index = NvM_FindBlockIndex(nvm_job_block);
            if ((nvm_client_buffer != NULL) && (nvm_client_buffer != block->ram_ptr))
            {
                (void)memcpy(nvm_client_buffer, block->ram_ptr, block->block_length);
            }
            nvm_ram_changed[block_index] = TRUE;
            /* NVM-SWS-018; callback recovery requires a configured RAM destination. */
            NvM_Finish(nvm_job_block, NVM_REQ_RESTORED_FROM_ROM);
        }
    }
    else
    {
        NvM_Finish(nvm_job_block, NVM_REQ_INTEGRITY_FAILED);
    }
}

/* NVM-SWS-007, -017, -037..038; chunk CRC work and dispatch by configured AUTOSAR width. */
STATIC void NvM_ProcessCrcChunk(void)
{
    const NvM_BlockConfigType *block = NvM_GetBlock(nvm_job_block);
    uint16 remaining = (uint16)(block->block_length - nvm_crc_offset);
    uint16 chunk_length = (remaining > NVM_CFG_CRC_BYTES_PER_CALL) ?
                              (uint16)NVM_CFG_CRC_BYTES_PER_CALL : remaining;
    boolean first_call = (nvm_crc_offset == 0U) ? TRUE : FALSE;
    const uint8 *data = &nvm_transfer_buffer[nvm_crc_offset];
    if (block->crc_type == NVM_CRC8)
    {
        uint8 start_value = first_call ? 0U : (uint8)nvm_crc_value;
        nvm_crc_value = Crc_CalculateCRC8(data, chunk_length, start_value, first_call);
    }
    else if (block->crc_type == NVM_CRC16)
    {
        uint16 start_value = first_call ? 0U : (uint16)nvm_crc_value;
        nvm_crc_value = Crc_CalculateCRC16(data, chunk_length, start_value, first_call);
    }
    else
    {
        uint32 start_value = first_call ? 0UL : nvm_crc_value;
        nvm_crc_value = Crc_CalculateCRC32(data, chunk_length, start_value, first_call);
    }
    nvm_crc_offset = (uint16)(nvm_crc_offset + chunk_length);
    if (nvm_crc_offset >= block->block_length)
    {
        NvM_CompleteCrcJob(block);
    }
}

STATIC void NvM_ProcessBackgroundCrc(void)
{
    if (nvm_background_crc_active == FALSE)
    {
        for (uint16 index = 0U; index < nvm_block_count; ++index)
        {
            if (nvm_background_crc_pending[index] != FALSE)
            {
                nvm_background_crc_active = TRUE;
                nvm_background_crc_block_index = index;
                nvm_background_crc_offset = 0U;
                nvm_background_crc_value = 0UL;
                break;
            }
        }
    }
    if (nvm_background_crc_active != FALSE)
    {
        const NvM_BlockConfigType *block = &nvm_blocks[nvm_background_crc_block_index];
        uint16 remaining = (uint16)(block->block_length - nvm_background_crc_offset);
        uint16 chunk_length = (remaining > NVM_CFG_CRC_BYTES_PER_CALL) ?
                                  (uint16)NVM_CFG_CRC_BYTES_PER_CALL : remaining;
        boolean first_call = (nvm_background_crc_offset == 0U) ? TRUE : FALSE;
        const uint8 *data = &block->ram_ptr[nvm_background_crc_offset];
        if (block->crc_type == NVM_CRC8)
        {
            uint8 start_value = first_call ? 0U : (uint8)nvm_background_crc_value;
            nvm_background_crc_value = Crc_CalculateCRC8(data, chunk_length, start_value, first_call);
        }
        else if (block->crc_type == NVM_CRC16)
        {
            uint16 start_value = first_call ? 0U : (uint16)nvm_background_crc_value;
            nvm_background_crc_value = Crc_CalculateCRC16(data, chunk_length, start_value, first_call);
        }
        else
        {
            uint32 start_value = first_call ? 0UL : nvm_background_crc_value;
            nvm_background_crc_value = Crc_CalculateCRC32(data, chunk_length, start_value, first_call);
        }
        nvm_background_crc_offset = (uint16)(nvm_background_crc_offset + chunk_length);
        if (nvm_background_crc_offset >= block->block_length)
        {
            nvm_ram_crc[nvm_background_crc_block_index] = nvm_background_crc_value;
            nvm_ram_crc_valid[nvm_background_crc_block_index] = TRUE;
            nvm_background_crc_pending[nvm_background_crc_block_index] = FALSE;
            nvm_background_crc_active = FALSE;
        }
    }
}

/* NVM-SWS-014, -018..019, -036; poll, retry, recover and report configured production events. */
STATIC boolean NvM_PollOrRetryActiveJob(const NvM_BlockConfigType *block, uint8 retry_limit)
{
    boolean consumed = FALSE;
    if (nvm_io_started == FALSE)
    {
        if (nvm_retry_count < retry_limit)
        {
            ++nvm_retry_count;
            nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
            consumed = TRUE;
        }
    }
    else if (NvM_IsBusyStatus(MemIf_GetStatus(block->memif_device_index)) != FALSE)
    {
        consumed = TRUE;
    }
    else
    {
        /* MemIf is idle; evaluate the job result. */
    }
    return consumed;
}

/* Returns TRUE when the outcome was handled by a retry, recovery or completion. */
STATIC boolean NvM_HandleJobOutcome(const NvM_BlockConfigType *block, MemIf_JobResultType result,
                                    uint8 retry_limit)
{
    boolean handled = TRUE;
    if ((result == MEMIF_JOB_OK) && (nvm_job == NVM_JOB_READ))
    {
        if (block->crc_enabled != FALSE)
        {
            NvM_BeginCrcCalculation(NVM_CRC_JOB_READ, block);
            NvM_ProcessCrcChunk();
        }
        else
        {
            NvM_CopyToDestination(block, nvm_transfer_buffer);
            NvM_Finish(nvm_job_block, NVM_REQ_OK);
        }
    }
    else if ((nvm_job == NVM_JOB_READ) && (result != MEMIF_BLOCK_INVALID) &&
             (result != MEMIF_JOB_CANCELED) && (nvm_retry_count < retry_limit))
    {
        ++nvm_retry_count;
        nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
    }
    else if ((nvm_job == NVM_JOB_READ) && (result != MEMIF_JOB_CANCELED) &&
             (NvM_TrySecondaryRead(block) != FALSE))
    {
        /* Secondary copy read has been started; completion is handled by the next poll. */
    }
    else if ((nvm_job == NVM_JOB_READ) && (result != MEMIF_BLOCK_INVALID) &&
             (result != MEMIF_JOB_CANCELED) && (block->rom_ptr != NULL))
    {
        NvM_CopyToDestination(block, block->rom_ptr);
        NvM_Finish(nvm_job_block, NVM_REQ_RESTORED_FROM_ROM);
    }
    else if ((nvm_job == NVM_JOB_READ) && (result != MEMIF_BLOCK_INVALID) &&
             (result != MEMIF_JOB_CANCELED) && (block->init_block_callback != NULL) &&
             (block->init_block_callback(NVM_INIT_RESTORE_BLOCK_DEFAULTS) == E_OK))
    {
        uint16 block_index = NvM_FindBlockIndex(nvm_job_block);
        if ((nvm_client_buffer != NULL) && (block->ram_ptr != NULL) &&
            (nvm_client_buffer != block->ram_ptr))
        {
            (void)memcpy(nvm_client_buffer, block->ram_ptr, block->block_length);
        }
        nvm_ram_changed[block_index] = TRUE;
        NvM_Finish(nvm_job_block, NVM_REQ_RESTORED_FROM_ROM);
    }
    else if ((nvm_job == NVM_JOB_WRITE) && (result == MEMIF_JOB_FAILED) &&
             (nvm_retry_count < retry_limit))
    {
        ++nvm_retry_count;
        nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
    }
    else
    {
        handled = FALSE;
    }
    return handled;
}

/* Complete a write (including redundant copy handling) or any remaining job type. */
STATIC void NvM_CompleteActiveJob(const NvM_BlockConfigType *block, MemIf_JobResultType result)
{
    if ((nvm_job == NVM_JOB_WRITE) &&
        (block->management_type == NVM_BLOCK_REDUNDANT))
    {
        uint16 block_index = NvM_FindBlockIndex(nvm_job_block);
        if (result == MEMIF_JOB_OK)
        {
            nvm_redundant_write_success = TRUE;
            nvm_last_read_copy[block_index] = nvm_active_copy;
        }
        else
        {
            nvm_redundant_write_failure = TRUE;
        }
        if (nvm_redundant_copy_attempts == 0U)
        {
            nvm_redundant_copy_attempts = 1U;
            nvm_active_copy = (uint8)(1U - nvm_active_copy);
            nvm_retry_count = 0U;
            nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
        }
        else
        {
            if (nvm_redundant_write_success == FALSE)
            {
#if NVM_CFG_DEM_EVENT_REQUEST_FAILED_ENABLED
                NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_REQUEST_FAILED_ID, DEM_EVENT_STATUS_FAILED);
#endif
            }
            NvM_Finish(nvm_job_block, (nvm_redundant_write_success != FALSE) ?
                                          NVM_REQ_OK : NVM_REQ_NOT_OK);
        }
    }
    else
    {
        if ((nvm_job == NVM_JOB_WRITE) && (result == MEMIF_JOB_FAILED))
        {
#if NVM_CFG_DEM_EVENT_REQUEST_FAILED_ENABLED
            NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_REQUEST_FAILED_ID, DEM_EVENT_STATUS_FAILED);
#endif
        }
        NvM_Finish(nvm_job_block, NvM_ConvertMemIfResult(result));
    }
}

STATIC void NvM_ProcessActiveJob(void)
{
    /* An active job always carries a block ID from the validated descriptor table. */
    const NvM_BlockConfigType *block = NvM_GetBlock(nvm_job_block);
    uint8 retry_limit = (nvm_job == NVM_JOB_READ) ? block->max_read_retries
                                                  : block->max_write_retries;
    if (NvM_PollOrRetryActiveJob(block, retry_limit) == FALSE)
    {
        MemIf_JobResultType result = nvm_io_started ?
                                         MemIf_GetJobResult(block->memif_device_index) :
                                         MEMIF_JOB_FAILED;
        if ((nvm_job == NVM_JOB_READ) &&
            ((result == MEMIF_JOB_FAILED) || (result == MEMIF_BLOCK_INCONSISTENT)))
        {
#if NVM_CFG_DEM_EVENT_HARDWARE_ENABLED
            NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_HARDWARE_ID, DEM_EVENT_STATUS_FAILED);
#endif
            if (result == MEMIF_JOB_FAILED)
            {
#if NVM_CFG_DEM_EVENT_REQUEST_FAILED_ENABLED
                NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_REQUEST_FAILED_ID, DEM_EVENT_STATUS_FAILED);
#endif
            }
            else
            {
#if NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ENABLED
                NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ID, DEM_EVENT_STATUS_FAILED);
#endif
            }
        }
        if ((nvm_job == NVM_JOB_WRITE) && (result == MEMIF_JOB_FAILED))
        {
#if NVM_CFG_DEM_EVENT_HARDWARE_ENABLED
            NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_HARDWARE_ID, DEM_EVENT_STATUS_FAILED);
#endif
        }
        if (NvM_HandleJobOutcome(block, result, retry_limit) == FALSE)
        {
            NvM_CompleteActiveJob(block, result);
        }
    }
}

STATIC boolean NvM_IsWriteAllWaitingForMemIf(void)
{
    boolean waiting = FALSE;
    if ((nvm_multi_active != FALSE) && (nvm_multi_job == NVM_JOB_WRITE_ALL) &&
        (MemIf_GetStatus(MEMIF_BROADCAST_ID) == MEMIF_BUSY_INTERNAL))
    {
        waiting = TRUE;
    }
    return waiting;
}

/* NVM-SWS-020..024; traverse eligible blocks and aggregate asynchronous and start-time failures. */
STATIC void NvM_StartNextMultiBlock(void)
{
    if ((nvm_multi_index >= nvm_block_count) || (nvm_multi_cancel_requested != FALSE))
    {
        NvM_FinishMultiBlock();
    }
    else
    {
        nvm_multi_started = TRUE;
        NvM_BlockIdType id = nvm_blocks[nvm_multi_index].block_id;
        NvM_JobType single_job = (nvm_multi_job == NVM_JOB_READ_ALL) ? NVM_JOB_READ : NVM_JOB_WRITE;
        if ((single_job == NVM_JOB_WRITE) && (nvm_ram_changed[nvm_multi_index] == FALSE))
        {
            NvM_SetResult(id, NVM_REQ_BLOCK_SKIPPED);
            ++nvm_multi_index;
        }
        else if (((single_job == NVM_JOB_READ) &&
                  (nvm_blocks[nvm_multi_index].select_block_for_read_all == FALSE)) ||
                 ((single_job == NVM_JOB_WRITE) &&
                  (nvm_blocks[nvm_multi_index].select_block_for_write_all == FALSE)) ||
                 (nvm_blocks[nvm_multi_index].ram_ptr == NULL))
        {
            NvM_SetResult(id, NVM_REQ_BLOCK_SKIPPED);
            ++nvm_multi_index;
        }
        else if ((single_job == NVM_JOB_WRITE) &&
                 (nvm_blocks[nvm_multi_index].calc_ram_block_crc != FALSE) &&
                 (nvm_background_crc_pending[nvm_multi_index] != FALSE))
        {
            /* NVM-SWS-007/-021: finish this block's RAM CRC before WriteAll starts its write. */
            NvM_ProcessBackgroundCrc();
        }
        else
        {
            nvm_multi_started = TRUE;
#if NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION
            /* SWS_NvM_00892: report only blocks actually selected for processing. */
            if (nvm_blocks[nvm_multi_index].bswm_block_status_information != FALSE)
            {
                BswM_NvM_CurrentBlockMode(id, NVM_REQ_PENDING);
            }
#endif
            Std_ReturnType result = NvM_Start(id, single_job, TRUE);
            if (result != E_OK)
            {
                nvm_multi_failed = TRUE;
                NvM_SetResult(id, NVM_REQ_NOT_OK);
#if NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION
                /* SWS_NvM_00949: report a block whose start-time processing failed. */
                if (nvm_blocks[nvm_multi_index].bswm_block_status_information != FALSE)
                {
                    BswM_NvM_CurrentBlockMode(id, NVM_REQ_NOT_OK);
                }
#endif
                ++nvm_multi_index;
            }
        }
    }
}

STATIC void NvM_Finish(NvM_BlockIdType id, NvM_RequestResultType result)
{
    const NvM_BlockConfigType *block = NvM_GetBlock(id);
    uint16 block_index = NvM_FindBlockIndex(id);
    NvM_JobType completed_job = nvm_job;
#if NVM_CFG_SINGLE_BLOCK_CALLBACK_ENABLED
    NvM_JobType completed_multi_job = nvm_multi_job;
    boolean completed_job_is_multi = nvm_job_is_multi;
#endif
    boolean redundant_read_fallback = nvm_redundant_read_fallback;
    boolean redundant_write_failure = nvm_redundant_write_failure;
    if ((block->ram_ptr != NULL) && nvm_client_read &&
        ((result == NVM_REQ_OK) || (result == NVM_REQ_RESTORED_FROM_ROM)))
    {
        (void)memcpy(nvm_client_buffer, block->ram_ptr, block->block_length);
    }
    SchM_Enter_NvM();
    if ((nvm_job_is_multi != FALSE) &&
        (result != NVM_REQ_OK) &&
        (result != NVM_REQ_CANCELED))
    {
        nvm_multi_failed = TRUE;
    }
    SchM_Enter_NvM();
    if ((nvm_job == NVM_JOB_WRITE) && (result == NVM_REQ_OK))
    {
        nvm_ram_valid[block_index] = TRUE;
        nvm_ram_changed[block_index] = FALSE;
        if (block->crc_enabled != FALSE)
        {
            nvm_last_crc[block_index] = nvm_crc_value;
            nvm_last_crc_valid[block_index] = TRUE;
        }
    }
    if ((nvm_job == NVM_JOB_READ) &&
        ((result == NVM_REQ_OK) || (result == NVM_REQ_RESTORED_FROM_ROM)))
    {
        nvm_ram_valid[block_index] = TRUE;
        /* NVM-SWS-018/-021: recovered defaults remain eligible for a later NvM_WriteAll. */
        nvm_ram_changed[block_index] =
            (result == NVM_REQ_RESTORED_FROM_ROM) ? TRUE : FALSE;
    }
    if (((nvm_job == NVM_JOB_READ) && (result != NVM_REQ_OK)) ||
        ((nvm_job == NVM_JOB_WRITE) && (result != NVM_REQ_OK)) ||
        ((nvm_job == NVM_JOB_RESTORE) && (result == NVM_REQ_RESTORED_FROM_ROM)))
    {
        /* NVM-SWS-016/-018/-019: failures or default restoration invalidate the cached NV CRC. */
        nvm_last_crc_valid[block_index] = FALSE;
    }
    if ((nvm_job == NVM_JOB_READ) && (result == NVM_REQ_OK) &&
        (block->management_type == NVM_BLOCK_REDUNDANT))
    {
        nvm_last_read_copy[block_index] = nvm_active_copy;
    }
    if ((block->write_once != FALSE) &&
        (((nvm_job == NVM_JOB_WRITE) && (result == NVM_REQ_OK)) ||
         ((nvm_job == NVM_JOB_READ) &&
          ((result == NVM_REQ_OK) || (result == NVM_REQ_RESTORED_FROM_ROM)))))
    {
        nvm_write_protected[block_index] = TRUE;
    }
    nvm_job = NVM_JOB_IDLE;
    nvm_io_started = FALSE;
    nvm_crc_job = NVM_CRC_JOB_IDLE;
    NvM_ResetClientBuffer();
    /* NVM-SWS-020..024; MT_NvM_MainFunction_010: only multi-owned jobs advance. */
    if (nvm_job_is_multi != FALSE)
    {
        ++nvm_multi_index;
    }
    nvm_job_is_multi = FALSE;
    /* NVM-SWS-011/-013/-015: publish completion only after ownership and administration are final. */
    NvM_SetResultLocked(id, result);
    SchM_Exit_NvM();
#if NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION
    /* SWS_NvM_00891/00949: report the result after publishing the block state. */
    if (block->bswm_block_status_information != FALSE)
    {
        BswM_NvM_CurrentBlockMode(id, result);
    }
#endif
    /* SWS_NvM_00835/-00653/-00654/-00203/-00213; §7/T-07; MT_NvM_ReadBlock_006/MT_NvM_MainFunction_006. */
#if NVM_CFG_DEM_EVENT_HARDWARE_ENABLED
    if (result == NVM_REQ_OK)
    {
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_HARDWARE_ID, DEM_EVENT_STATUS_PASSED);
    }
#endif
#if NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ENABLED
    if ((completed_job == NVM_JOB_READ) && (result == NVM_REQ_OK))
    {
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_INTEGRITY_FAILED_ID, DEM_EVENT_STATUS_PASSED);
    }
#endif
#if NVM_CFG_DEM_EVENT_REQUEST_FAILED_ENABLED
    if (result == NVM_REQ_OK)
    {
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_REQUEST_FAILED_ID, DEM_EVENT_STATUS_PASSED);
    }
#endif
#if NVM_CFG_DEM_EVENT_LOSS_OF_REDUNDANCY_ENABLED
    /* NVM-SWS-018 and §7: report loss only when a redundant read succeeds on its fallback copy. */
    if ((completed_job == NVM_JOB_READ) && (result == NVM_REQ_OK) &&
        (redundant_read_fallback != FALSE))
    {
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_LOSS_OF_REDUNDANCY_ID,
                           DEM_EVENT_STATUS_FAILED);
    }
    if ((completed_job == NVM_JOB_WRITE) && (result == NVM_REQ_OK) &&
        (block->management_type == NVM_BLOCK_REDUNDANT) &&
        (redundant_write_failure == FALSE))
    {
        NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_LOSS_OF_REDUNDANCY_ID, DEM_EVENT_STATUS_PASSED);
    }
#endif
#if NVM_CFG_SINGLE_BLOCK_CALLBACK_ENABLED
    NvM_BlockRequestType callback_request = NVM_RESTORE_BLOCK_DEFAULTS;
    if (completed_job == NVM_JOB_READ)
    {
        callback_request = ((completed_job_is_multi != FALSE) &&
                            (completed_multi_job == NVM_JOB_READ_ALL)) ?
                               NVM_READ_ALL_BLOCK : NVM_READ_BLOCK;
    }
    else if (completed_job == NVM_JOB_WRITE)
    {
        callback_request = NVM_WRITE_BLOCK;
    }
    /* NVM-SWS §3.3/§4.3: publish block state before notifying the application. */
    (void)NVM_CFG_SINGLE_BLOCK_CALLBACK(callback_request, result);
#endif
}

STATIC Std_ReturnType NvM_Start(NvM_BlockIdType id, NvM_JobType job, boolean multi_job)
{
    /* Callers pass an initialized module, a validated ID and an idle job state. */
    const NvM_BlockConfigType *block = NvM_GetBlock(id);
    uint16 block_index = NvM_FindBlockIndex(id);
    Std_ReturnType request = E_NOT_OK;
    if ((job != NVM_JOB_WRITE) || (nvm_write_protected[block_index] == FALSE))
    {
        if (multi_job != FALSE)
        {
            /* NVM-SWS-013/-019/-021: multi-block jobs always source data from configured PRAM. */
            NvM_ResetClientBuffer();
        }
        NvM_SetJobPending(id, job, multi_job);
        if (job == NVM_JOB_READ)
        {
            nvm_io_started = (NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE;
            request = E_OK;
        }
        else if (job == NVM_JOB_WRITE)
        {
            const uint8 *source = (nvm_client_write_source != NULL) ?
                                      nvm_client_write_source : block->ram_ptr;
            if ((block->ram_ptr != NULL) && (nvm_client_write_source != NULL))
            {
                (void)memcpy(block->ram_ptr, nvm_client_write_source, block->block_length);
            }
            NvM_PrepareWrite(block, source);
            nvm_io_started = (nvm_crc_job == NVM_CRC_JOB_WRITE) ?
                                 FALSE :
                                 ((NvM_SubmitActiveJob(block) == E_OK) ? TRUE : FALSE);
            request = E_OK;
        }
        else
        {
            request = E_OK;
        }
    }
    return request;
}
STATIC void NvM_ProcessBlock(NvM_BlockIdType id, NvM_JobType job)
{
    /* NVM-SWS-016/-021: restore defaults without MemIf I/O and retain their changed state. */
    const NvM_BlockConfigType *block = NvM_GetBlock(id);
    (void)job;
    if (block->rom_ptr != NULL)
    {
        /* NvM_RestoreBlockDefaults admission guarantees a destination. */
        void *destination = nvm_client_buffer;
        (void)memcpy(destination, block->rom_ptr, block->block_length);
        if (destination == block->ram_ptr)
        {
            uint16 block_index = NvM_FindBlockIndex(id);
            nvm_ram_valid[block_index] = TRUE;
            nvm_ram_changed[block_index] = TRUE;
        }
        NvM_Finish(id, NVM_REQ_RESTORED_FROM_ROM);
    }
    else
    {
        boolean has_ram_backup = (block->ram_ptr != NULL) ? TRUE : FALSE;
        boolean caller_only_destination =
            ((block->ram_ptr != NULL) && (nvm_client_buffer != block->ram_ptr)) ? TRUE : FALSE;
        Std_ReturnType callback_result;
        if (has_ram_backup != FALSE)
        {
            (void)memcpy(nvm_transfer_buffer, block->ram_ptr, block->block_length);
        }
        callback_result = block->init_block_callback(NVM_INIT_RESTORE_BLOCK_DEFAULTS);
        if (callback_result != E_OK)
        {
            if (has_ram_backup != FALSE)
            {
                (void)memcpy(block->ram_ptr, nvm_transfer_buffer, block->block_length);
            }
            NvM_Finish(id, NVM_REQ_NOT_OK);
        }
        else if (block->ram_ptr == NULL)
        {
            NvM_Finish(id, NVM_REQ_NOT_OK);
        }
        else
        {
            if (caller_only_destination != FALSE)
            {
                (void)memcpy(nvm_client_buffer, block->ram_ptr, block->block_length);
                (void)memcpy(block->ram_ptr, nvm_transfer_buffer, block->block_length);
            }
            if (caller_only_destination == FALSE)
            {
                uint16 block_index = NvM_FindBlockIndex(id);
                /* NVM-SWS-016: only a restore into configured PRAM changes its administration. */
                nvm_ram_valid[block_index] = TRUE;
                nvm_ram_changed[block_index] = TRUE;
            }
            NvM_Finish(id, NVM_REQ_RESTORED_FROM_ROM);
        }
    }
}

/* NVM-SWS-001, -002; MT_NvM_Init_004/MT_NvM_Init_002: reset state, preserve PRAM, leave lower layers alone. */
STATIC void NvM_InitWithTable(const NvM_BlockConfigType *table, uint16 table_count)
{
    uint16 index;
    nvm_blocks = table;
    nvm_block_count = table_count;
    nvm_initialized = NvM_IsConfigurationValid(nvm_blocks, nvm_block_count);
    if (nvm_initialized == FALSE)
    {
        nvm_blocks = NULL;
        nvm_block_count = 0U;
    }
    nvm_job = NVM_JOB_IDLE;
    nvm_job_block = 0U;
    nvm_job_is_multi = FALSE;
    nvm_retry_count = 0U;
    nvm_io_started = FALSE;
    nvm_crc_job = NVM_CRC_JOB_IDLE;
    nvm_crc_offset = 0U;
    nvm_crc_value = 0UL;
    nvm_crc_expected = 0UL;
    NvM_ResetQueue();
    nvm_multi_active = FALSE;
    nvm_pending_multi_active = FALSE;
    nvm_multi_started = FALSE;
    nvm_multi_cancel_requested = FALSE;
    nvm_multi_failed = FALSE;
    nvm_multi_job = NVM_JOB_IDLE;
    nvm_pending_multi_job = NVM_JOB_IDLE;
    nvm_multi_result = NVM_REQ_OK;
    nvm_multi_index = 0U;
    nvm_active_copy = 0U;
    nvm_redundant_copy_attempts = 0U;
    nvm_redundant_write_success = FALSE;
    nvm_redundant_read_fallback = FALSE;
    nvm_redundant_write_failure = FALSE;
    NvM_ResetClientBuffer();
    nvm_background_crc_active = FALSE;
    nvm_background_crc_block_index = 0U;
    nvm_background_crc_offset = 0U;
    nvm_background_crc_value = 0UL;
    for (index = 0U; index < NVM_CFG_BLOCK_COUNT; ++index)
    {
        nvm_result[index] = NVM_REQ_OK;
        nvm_ram_valid[index] = FALSE;
        nvm_ram_changed[index] = FALSE;
        nvm_write_protected[index] = FALSE;
        nvm_last_read_copy[index] = 0U;
        nvm_last_crc[index] = 0UL;
        nvm_last_crc_valid[index] = FALSE;
        nvm_ram_crc[index] = 0UL;
        nvm_ram_crc_valid[index] = FALSE;
        nvm_background_crc_pending[index] = FALSE;
    }
    if (nvm_initialized != FALSE)
    {
        for (index = 0U; index < nvm_block_count; ++index)
        {
            nvm_write_protected[index] = nvm_blocks[index].write_protected;
        }
    }
}

/* NVM-SWS-001, -002; MT_NvM_Init_004/MT_NvM_Init_002: reset state, preserve PRAM, leave lower layers alone. */
void NvM_Init(const NvM_ConfigType *ConfigPtr)
{
    (void)ConfigPtr;
    NvM_InitWithTable(NvM_BlockDescriptorTable, NVM_CFG_BLOCK_COUNT);
}


/* NVM-API-001/002, NVM-SWS-011: expose the latest block/multi-block request result. */
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType *RequestResultPtr)
{
    uint16 block_index = NvM_FindBlockIndex(BlockId);
    Std_ReturnType result = E_NOT_OK;
    SchM_Enter_NvM();
    if ((RequestResultPtr != NULL) && (nvm_initialized != FALSE) && (BlockId == 0U))
    {
        *RequestResultPtr = nvm_multi_result;
        result = E_OK;
    }
    else if ((RequestResultPtr != NULL) && (block_index < nvm_block_count))
    {
        *RequestResultPtr = nvm_result[block_index];
        result = E_OK;
    }
    else
    {
    }
    SchM_Exit_NvM();
    return result;
}

#if NVM_CFG_VERSION_INFO_API
void NvM_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
    if (versioninfo != NULL)
    {
        versioninfo->vendorID = NVM_CFG_VENDOR_ID;
        versioninfo->moduleID = NVM_CFG_MODULE_ID;
        versioninfo->sw_major_version = NVM_CFG_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = NVM_CFG_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = NVM_CFG_SW_PATCH_VERSION;
    }
}
#endif

#if NVM_CFG_SET_RAM_BLOCK_STATUS_API
/* NVM-SWS-015, -019a: update configured PRAM validity/changed state without changing request result. */
Std_ReturnType NvM_SetRamBlockStatus(NvM_BlockIdType BlockId, boolean BlockChanged)
{
    uint16 block_index = NvM_FindBlockIndex(BlockId);
    Std_ReturnType result = E_NOT_OK;
    SchM_Enter_NvM();
    if ((block_index < nvm_block_count) && (nvm_blocks[block_index].ram_ptr != NULL) &&
        (nvm_blocks[block_index].use_set_ram_block_status != FALSE))
    {
        nvm_ram_changed[block_index] = BlockChanged;
        if (BlockChanged != FALSE)
        {
            /* NVM-SWS-015/-019a: explicitly changed PRAM is valid and eligible for WriteAll. */
            nvm_ram_valid[block_index] = TRUE;
        }
        if ((BlockChanged != FALSE) && (nvm_blocks[block_index].calc_ram_block_crc != FALSE))
        {
            nvm_background_crc_pending[block_index] = TRUE;
            if ((nvm_background_crc_active != FALSE) &&
                (nvm_background_crc_block_index == block_index))
            {
                nvm_background_crc_active = FALSE;
            }
        }
        result = E_OK;
    }
    SchM_Exit_NvM();
    return result;
}
#endif

/* NVM-API-001/002, NVM-SWS-010..013, -018; MT_NvM_MainFunction_001. */
Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, void *NvM_DstPtr)
{
    const NvM_BlockConfigType *b = NvM_FindBlock(BlockId);
    Std_ReturnType result = E_NOT_OK;
    if ((b != NULL) && ((NvM_DstPtr != NULL) || (b->ram_ptr != NULL)))
    {
        void *destination = (NvM_DstPtr != NULL) ? NvM_DstPtr : b->ram_ptr;
        boolean copy_to_destination = (destination != b->ram_ptr) ? TRUE : FALSE;
        result = NvM_Enqueue(BlockId, NVM_JOB_READ, destination, NULL, copy_to_destination);
    }
    return result;
}

/* NVM-API-001/002, -004, NVM-SWS-010..013, -019; MT_NvM_MainFunction_001, MT_NvM_WriteBlock_005. */
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, const void *NvM_SrcPtr)
{
    const NvM_BlockConfigType *b = NvM_FindBlock(BlockId);
    const void *source = (NvM_SrcPtr != NULL) ? NvM_SrcPtr : ((b != NULL) ? b->ram_ptr : NULL);
    uint16 block_index = NvM_FindBlockIndex(BlockId);
    boolean write_protected = FALSE;
    Std_ReturnType result = E_NOT_OK;
    if ((b != NULL) && (source != NULL))
    {
        SchM_Enter_NvM();
        if (nvm_write_protected[block_index] != FALSE)
        {
            write_protected = TRUE;
        }
        SchM_Exit_NvM();
        if (write_protected != FALSE)
        {
#if NVM_CFG_DEM_EVENT_WRITE_PROTECTED_ENABLED
            NvM_ReportDemEvent(NVM_CFG_DEM_EVENT_WRITE_PROTECTED_ID, DEM_EVENT_STATUS_FAILED);
#endif
        }
        else
        {
            result = NvM_Enqueue(BlockId, NVM_JOB_WRITE, NULL, source, FALSE);
        }
    }
    return result;
}

/* NVM-API-001/002, NVM-SWS-016; MT_NvM_MainFunction_001. */
Std_ReturnType NvM_RestoreBlockDefaults(NvM_BlockIdType BlockId, void *NvM_DestPtr)
{
    const NvM_BlockConfigType *b = NvM_FindBlock(BlockId);
    Std_ReturnType result = E_NOT_OK;
    if ((nvm_initialized != FALSE) && (b != NULL) &&
        ((b->rom_ptr != NULL) || (b->init_block_callback != NULL)) &&
        ((b->ram_ptr != NULL) || (NvM_DestPtr != NULL)))
    {
        void *destination = (NvM_DestPtr != NULL) ? NvM_DestPtr : b->ram_ptr;
        result = NvM_Enqueue(BlockId, NVM_JOB_RESTORE, destination, NULL, FALSE);
    }
    return result;
}

/* NVM-SWS-003/-020: initiate startup loading as an asynchronous multi-block request. */
void NvM_ReadAll(void)
{
    NvM_QueueMultiBlock(NVM_JOB_READ_ALL);
}

STATIC void NvM_QueueMultiBlock(NvM_JobType job)
{
    boolean accepted = FALSE;
    SchM_Enter_NvM();
    if (nvm_initialized != FALSE)
    {
        if (nvm_multi_active == FALSE)
        {
            nvm_multi_job = job;
            nvm_multi_index = 0U;
            nvm_multi_active = TRUE;
            nvm_multi_started = FALSE;
            nvm_multi_cancel_requested = FALSE;
            nvm_multi_failed = FALSE;
            accepted = TRUE;
        }
        else if (nvm_pending_multi_active == FALSE)
        {
            nvm_pending_multi_job = job;
            nvm_pending_multi_active = TRUE;
            accepted = TRUE;
        }
        else
        {
            /* NVM-SWS-023: preserve the single pending multi-block slot when it is full. */
        }
        if (accepted != FALSE)
        {
            NvM_SetResultLocked(0U, NVM_REQ_PENDING);
        }
    }
    SchM_Exit_NvM();
#if NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION
    /* SWS_NvM_00888: report each accepted active or queued multi-block request. */
    if (accepted != FALSE)
    {
        BswM_NvM_CurrentJobMode(
            NvM_BswM_MultiBlockRequest(job, NVM_REQ_PENDING), NVM_REQ_PENDING);
    }
#endif
}

    /* NVM-SWS-020..021: initiate asynchronous shutdown persistence of eligible changed PRAM. */
    void NvM_WriteAll(void)
    {
        NvM_QueueMultiBlock(NVM_JOB_WRITE_ALL);
    }

    void NvM_CancelWriteAll(void)
    {
        boolean cancel_active_job = FALSE;
        boolean cancel_pending_job = FALSE;
        NvM_BlockIdType block_id = 0U;
        SchM_Enter_NvM();
        if ((nvm_multi_active != FALSE) && (nvm_multi_job == NVM_JOB_WRITE_ALL))
        {
            nvm_multi_cancel_requested = TRUE;
            /* NVM-SWS-022/-024; MT_NvM_CancelWriteAll_001: preserve unrelated client work. */
            if ((nvm_job != NVM_JOB_IDLE) && (nvm_job_is_multi != FALSE))
            {
                block_id = nvm_job_block;
                cancel_active_job = TRUE;
            }
        }

        #define NVM_STOP_SEC_CODE
        #include "NvM_MemMap.h"
        if ((nvm_pending_multi_active != FALSE) &&
            (nvm_pending_multi_job == NVM_JOB_WRITE_ALL))
        {
            nvm_pending_multi_active = FALSE;
            cancel_pending_job = TRUE;
        }
        SchM_Exit_NvM();
#if NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION
        if (cancel_pending_job != FALSE)
        {
            /* SWS_NvM_00889: an accepted queued WriteAll canceled before start is terminal too. */
            BswM_NvM_CurrentJobMode(NVM_CANCEL_WRITE_ALL, NVM_REQ_CANCELED);
        }
#else
        (void)cancel_pending_job;
#endif
        if (cancel_active_job != FALSE)
        {
            MemIf_Cancel(0U);
            NvM_Finish(block_id, NVM_REQ_CANCELED);
        }
    }

    /* NVM-SWS-004..006: poll MemIf and advance one configured NvM job per scheduled call. */
    void NvM_MainFunction(void)
    {
        if ((nvm_initialized != FALSE) && (NvM_IsWriteAllWaitingForMemIf() == FALSE))
        {
            if (nvm_job != NVM_JOB_IDLE)
            {
                if (nvm_crc_job != NVM_CRC_JOB_IDLE)
                {
                    NvM_ProcessCrcChunk();
                }
                else if (nvm_job == NVM_JOB_RESTORE)
                {
                    NvM_ProcessBlock(nvm_job_block, nvm_job);
                }
                else
                {
                    NvM_ProcessActiveJob();
                }
            }
            else if ((nvm_queue_count > 0U) &&
                     ((nvm_multi_active == FALSE) || (nvm_multi_started == FALSE)))
            {
                (void)NvM_StartNextQueuedJob();
                if (nvm_crc_job != NVM_CRC_JOB_IDLE)
                {
                    NvM_ProcessCrcChunk();
                }
            }
            else if (nvm_multi_active != FALSE)
            {
                if ((nvm_multi_started != FALSE) ||
                    (MemIf_GetStatus(MEMIF_BROADCAST_ID) == MEMIF_IDLE))
                {
                    NvM_StartNextMultiBlock();
                    if (nvm_crc_job != NVM_CRC_JOB_IDLE)
                    {
                        NvM_ProcessCrcChunk();
                    }
                }
            }
            else
            {
                NvM_ProcessBackgroundCrc();
            }
        }
    }

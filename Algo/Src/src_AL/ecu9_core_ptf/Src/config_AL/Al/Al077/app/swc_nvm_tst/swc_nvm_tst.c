#include "NvM.h"
#include "swc_nvm_tst.h"

#define SWC_NVM_TST_BLOCK_ID 8U
#define SWC_NVM_TST_BLOCK_LENGTH NVM_CFG_BLOCK_8_LENGTH
#define SWC_NVM_TST_RECORD_MAGIC_0 0xA5U
#define SWC_NVM_TST_RECORD_MAGIC_1 0x5AU
#define SWC_NVM_TST_DATA_OFFSET 2U

volatile Swc_NvMTstResultType swc_nvm_tst_result = SWC_NVM_TST_PENDING;
volatile Swc_NvMTstStateType swc_nvm_tst_state = SWC_NVM_TST_IDLE;
uint8 swc_nvm_tst_expected_buffer[SWC_NVM_TST_BLOCK_LENGTH];
uint8 swc_nvm_tst_read_buffer[SWC_NVM_TST_BLOCK_LENGTH];

static const uint8 swc_nvm_tst_payload[SWC_NVM_TST_BLOCK_LENGTH - SWC_NVM_TST_DATA_OFFSET] =
{
    0x31U, 0x42U, 0x53U, 0x64U, 0x75U, 0x86U
};

static void swc_nvm_tst_prepare_expected_record(void)
{
    uint8 index;

    swc_nvm_tst_expected_buffer[0U] = SWC_NVM_TST_RECORD_MAGIC_0;
    swc_nvm_tst_expected_buffer[1U] = SWC_NVM_TST_RECORD_MAGIC_1;
    for (index = 0U; index < (SWC_NVM_TST_BLOCK_LENGTH - SWC_NVM_TST_DATA_OFFSET); index++)
    {
        swc_nvm_tst_expected_buffer[SWC_NVM_TST_DATA_OFFSET + index] =
            swc_nvm_tst_payload[index];
    }
}

static boolean swc_nvm_tst_record_matches(void)
{
    uint8 index;
    boolean matches = TRUE;

    for (index = 0U; index < SWC_NVM_TST_BLOCK_LENGTH; index++)
    {
        if (swc_nvm_tst_read_buffer[index] != swc_nvm_tst_expected_buffer[index])
        {
            matches = FALSE;
            break;
        }
    }

    return matches;
}

static void swc_nvm_tst_start_write(void)
{
    if (NvM_WriteBlock(SWC_NVM_TST_BLOCK_ID, swc_nvm_tst_expected_buffer) == E_OK)
    {
        swc_nvm_tst_state = SWC_NVM_TST_WAIT_WRITE;
    }
    else
    {
        swc_nvm_tst_state = SWC_NVM_TST_ERROR;
    }
}

void swc_nvm_tst_init(void)
{
    uint8 index;

    swc_nvm_tst_prepare_expected_record();
    for (index = 0U; index < SWC_NVM_TST_BLOCK_LENGTH; ++index)
    {
        swc_nvm_tst_read_buffer[index] = 0U;
    }
    swc_nvm_tst_result = SWC_NVM_TST_PENDING;
}

void swc_nvm_tst_runnable(void)
{
    NvM_RequestResultType request_result;

    switch (swc_nvm_tst_state)
    {
        case SWC_NVM_TST_START_READ:
            if (NvM_ReadBlock(SWC_NVM_TST_BLOCK_ID, swc_nvm_tst_read_buffer) == E_OK)
            {
                swc_nvm_tst_state = SWC_NVM_TST_WAIT_READ;
            }
            else
            {
                swc_nvm_tst_state = SWC_NVM_TST_ERROR;
            }
            break;

        case SWC_NVM_TST_WAIT_READ:
            if ((NvM_GetErrorStatus(SWC_NVM_TST_BLOCK_ID, &request_result) == E_OK) &&
                (request_result != NVM_REQ_PENDING))
            {
                if (request_result == NVM_REQ_OK)
                {
                    if (swc_nvm_tst_read_buffer[0U] == SWC_NVM_TST_RECORD_MAGIC_0)
                    {
                        if ((swc_nvm_tst_read_buffer[1U] == SWC_NVM_TST_RECORD_MAGIC_1) &&
                            (swc_nvm_tst_record_matches() != FALSE))
                        {
                            swc_nvm_tst_state = SWC_NVM_TST_READ_DONE;
                        }
                        else
                        {
                            swc_nvm_tst_state = SWC_NVM_TST_ERROR;
                        }
                    }
                    else
                    {
                        swc_nvm_tst_state = SWC_NVM_TST_START_WRITE;
                    }
                }
                else if ((request_result == NVM_REQ_RESTORED_FROM_ROM) ||
                         (request_result == NVM_REQ_NV_INVALIDATED))
                {
                    swc_nvm_tst_state = SWC_NVM_TST_START_WRITE;
                }
                else
                {
                    swc_nvm_tst_state = SWC_NVM_TST_ERROR;
                }
            }
            break;

        case SWC_NVM_TST_START_WRITE:
            swc_nvm_tst_start_write();
            break;

        case SWC_NVM_TST_WAIT_WRITE:
            if ((NvM_GetErrorStatus(SWC_NVM_TST_BLOCK_ID, &request_result) == E_OK) &&
                (request_result != NVM_REQ_PENDING))
            {
                swc_nvm_tst_state = (request_result == NVM_REQ_OK) ?
                                        SWC_NVM_TST_WRITE_DONE : SWC_NVM_TST_ERROR;
            }
            break;

        case SWC_NVM_TST_WRITE_DONE:
            swc_nvm_tst_result = SWC_NVM_TST_WRITE_COMPLETED;
            break;

        case SWC_NVM_TST_READ_DONE:
            swc_nvm_tst_result = SWC_NVM_TST_READ_PASSED;
            break;

        case SWC_NVM_TST_ERROR:
            swc_nvm_tst_result = SWC_NVM_TST_FAILED;
            break;

        case SWC_NVM_TST_IDLE:
            swc_nvm_tst_state = SWC_NVM_TST_IDLE;
            break;

        default:
            swc_nvm_tst_result = SWC_NVM_TST_FAILED;
            swc_nvm_tst_state = SWC_NVM_TST_ERROR;
            break;
    }
}

#include "Fee.h"
#include "swc_fee_test.h"

#define SWC_FEE_TEST_BLOCK_NUMBER 48U
#define SWC_FEE_TEST_BLOCK_LENGTH 16U

typedef enum
{
    SWC_FEE_TEST_START_ERASE = 0U,
    SWC_FEE_TEST_WAIT_ERASE,
    SWC_FEE_TEST_START_WRITE,
    SWC_FEE_TEST_WAIT_WRITE,
    SWC_FEE_TEST_START_READ,
    SWC_FEE_TEST_WAIT_READ,
    SWC_FEE_TEST_DONE,
    SWC_FEE_TEST_ERROR
} Swc_FeeTestStateType;

static Swc_FeeTestStateType swc_fee_test_state;
static uint8 swc_fee_test_write_buffer[SWC_FEE_TEST_BLOCK_LENGTH];
static uint8 swc_fee_test_read_buffer[SWC_FEE_TEST_BLOCK_LENGTH];

volatile Swc_FeeTestResultType swc_fee_test_result = SWC_FEE_TEST_PENDING;

void swc_fee_test_init(void)
{
    uint8 index;
    for (index = 0U; index < SWC_FEE_TEST_BLOCK_LENGTH; ++index)
    {
        swc_fee_test_write_buffer[index] = ((index % 2U) == 0U) ? 0xAAU : 0x55U;
        swc_fee_test_read_buffer[index] = 0U;
    }
    swc_fee_test_state = SWC_FEE_TEST_START_ERASE;
    swc_fee_test_result = SWC_FEE_TEST_PENDING;
}

void swc_fee_test_runnable(void)
{
    uint8 index;
    MemIf_JobResultType job_result;
    switch (swc_fee_test_state)
    {
        case SWC_FEE_TEST_START_ERASE:
            if (Fee_EraseImmediateBlock(SWC_FEE_TEST_BLOCK_NUMBER) == E_OK)
            {
                swc_fee_test_state = SWC_FEE_TEST_WAIT_ERASE;
            }
            break;

        case SWC_FEE_TEST_WAIT_ERASE:
            job_result = Fee_GetJobResult();
            if (job_result != MEMIF_JOB_PENDING)
            {
                swc_fee_test_state = (job_result == MEMIF_JOB_OK) ?
                                         SWC_FEE_TEST_START_WRITE : SWC_FEE_TEST_ERROR;
            }
            break;

        case SWC_FEE_TEST_START_WRITE:
            if (Fee_Write(SWC_FEE_TEST_BLOCK_NUMBER, swc_fee_test_write_buffer) == E_OK)
            {
                swc_fee_test_state = SWC_FEE_TEST_WAIT_WRITE;
            }
            break;

        case SWC_FEE_TEST_WAIT_WRITE:
            job_result = Fee_GetJobResult();
            if (job_result != MEMIF_JOB_PENDING)
            {
                swc_fee_test_state = (job_result == MEMIF_JOB_OK) ?
                                         SWC_FEE_TEST_START_READ : SWC_FEE_TEST_ERROR;
            }
            break;

        case SWC_FEE_TEST_START_READ:
            if (Fee_Read(SWC_FEE_TEST_BLOCK_NUMBER, 0U, swc_fee_test_read_buffer,
                         SWC_FEE_TEST_BLOCK_LENGTH) == E_OK)
            {
                swc_fee_test_state = SWC_FEE_TEST_WAIT_READ;
            }
            break;

        case SWC_FEE_TEST_WAIT_READ:
            job_result = Fee_GetJobResult();
            if (job_result != MEMIF_JOB_PENDING)
            {
                if (job_result == MEMIF_JOB_OK)
                {
                    for (index = 0U; index < SWC_FEE_TEST_BLOCK_LENGTH; ++index)
                    {
                        if (swc_fee_test_read_buffer[index] != swc_fee_test_write_buffer[index])
                        {
                            swc_fee_test_state = SWC_FEE_TEST_ERROR;
                            break;
                        }
                    }
                    if (swc_fee_test_state != SWC_FEE_TEST_ERROR)
                    {
                        swc_fee_test_state = SWC_FEE_TEST_DONE;
                    }
                }
                else
                {
                    swc_fee_test_state = SWC_FEE_TEST_ERROR;
                }
            }
            break;

        case SWC_FEE_TEST_DONE:
            swc_fee_test_result = SWC_FEE_TEST_PASSED;
            break;

        case SWC_FEE_TEST_ERROR:
        default:
            swc_fee_test_result = SWC_FEE_TEST_FAILED;
            break;
    }
}

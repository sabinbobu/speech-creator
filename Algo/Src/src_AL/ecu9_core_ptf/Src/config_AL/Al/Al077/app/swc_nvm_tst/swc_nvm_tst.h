#ifndef SWC_NVM_TST_H
#define SWC_NVM_TST_H

#include "NvM_Cfg.h"

typedef enum
{
    SWC_NVM_TST_PENDING = 0U,
    SWC_NVM_TST_WRITE_COMPLETED,
    SWC_NVM_TST_READ_PASSED,
    SWC_NVM_TST_FAILED
} Swc_NvMTstResultType;

typedef enum
{
    SWC_NVM_TST_START_READ = 0U,
    SWC_NVM_TST_WAIT_READ,
    SWC_NVM_TST_START_WRITE,
    SWC_NVM_TST_WAIT_WRITE,
    SWC_NVM_TST_WRITE_DONE,
    SWC_NVM_TST_READ_DONE,
    SWC_NVM_TST_IDLE,
    SWC_NVM_TST_ERROR
} Swc_NvMTstStateType;

extern volatile Swc_NvMTstResultType swc_nvm_tst_result;
extern volatile Swc_NvMTstStateType swc_nvm_tst_state;
extern uint8 swc_nvm_tst_expected_buffer[NVM_CFG_BLOCK_8_LENGTH];
extern uint8 swc_nvm_tst_read_buffer[NVM_CFG_BLOCK_8_LENGTH];

void swc_nvm_tst_init(void);
void swc_nvm_tst_runnable(void);

#endif /* SWC_NVM_TST_H */

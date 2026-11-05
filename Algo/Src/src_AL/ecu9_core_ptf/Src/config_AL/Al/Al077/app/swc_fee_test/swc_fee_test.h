#ifndef SWC_FEE_TEST_H
#define SWC_FEE_TEST_H

typedef enum
{
    SWC_FEE_TEST_PENDING = 0U,
    SWC_FEE_TEST_PASSED,
    SWC_FEE_TEST_FAILED
} Swc_FeeTestResultType;

extern volatile Swc_FeeTestResultType swc_fee_test_result;

void swc_fee_test_init(void);
void swc_fee_test_runnable(void);

#endif /* SWC_FEE_TEST_H */

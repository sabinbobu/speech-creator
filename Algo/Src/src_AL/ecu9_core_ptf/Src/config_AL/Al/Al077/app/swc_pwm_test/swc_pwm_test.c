#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "swc_pwm_test.h"

#define SWC_PWM_TEST_DUTY_10_PERCENT  (0x0CCC)
#define SWC_PWM_TEST_DUTY_90_PERCENT  (0x7333)

static uint8 swc_pwm_test_high_duty;

void swc_pwm_test_init(void)
{
    swc_pwm_test_high_duty = 0U;
}

void swc_pwm_test_toggle(void)
{
    swc_pwm_test_high_duty = (swc_pwm_test_high_duty == 0U) ? 1U : 0U;
    Pwm_SetDutyCycle(PWM_TIMG_CHANNEL1,
                     (swc_pwm_test_high_duty != 0U) ?
                     SWC_PWM_TEST_DUTY_90_PERCENT : SWC_PWM_TEST_DUTY_10_PERCENT);
}

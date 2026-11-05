#include "Gpt.h"
#include "Gpt_Cfg.h"
#include "swc_adc_test.h"
#include "swc_pwm_test.h"
#include "swc_spi_test.h"

void swc_gpt_test_init(void)
{
    Gpt_EnableNotification(GPT_TIMG_CHANNEL2);
    Gpt_StartTimer(GPT_TIMG_CHANNEL2, 10000U);
}

void Gpt_Channel_Notify1(void)
{
    swc_pwm_test_toggle();
    swc_spi_test_trigger();
    swc_adc_test_trigger_conversion();
}

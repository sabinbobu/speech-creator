#include "Dio.h"
#include "swc_led.h"

static Dio_LevelType swc_led_output_level;

void swc_led_init(void)
{
    swc_led_output_level = STD_LOW;
    Dio_WriteChannel(DioConf_DioChannel_PA0_HSS_EN1, swc_led_output_level);
}

void swc_led_runnable(void)
{
    swc_led_output_level = (swc_led_output_level == STD_LOW) ? STD_HIGH : STD_LOW;
    Dio_WriteChannel(DioConf_DioChannel_PA0_HSS_EN1, swc_led_output_level);
}

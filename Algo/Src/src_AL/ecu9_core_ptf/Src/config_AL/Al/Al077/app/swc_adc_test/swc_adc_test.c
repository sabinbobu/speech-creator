#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Adc_Types.h"
#include "Os.h"
#include "swc_adc_test.h"

Adc_ValueGroupType Adc_AppBuffer[ADC_MAX_GROUP][ADC_NUM_CHANNEL];
Adc_ValueGroupType Adc_AppReadBuffer[ADC_MAX_GROUP][ADC_NUM_CHANNEL];
volatile uint32 gAdcAppGroupDone[ADC_MAX_GROUP];

void swc_adc_test_init(void)
{
    uint32 group;

    for (group = 0U; group < AdcConfigSet.maxGroup; group++)
    {
        gAdcAppGroupDone[group] = FALSE;
        Adc_EnableGroupNotification(group);
        Adc_StartGroupConversion(group);
    }
}

void swc_adc_test_trigger_conversion(void)
{
    Adc_StartGroupConversion(0U);
    Adc_StartGroupConversion(1U);
}

static void swc_adc_test_process_group(uint32 group)
{
    if (Adc_GetGroupStatus(group) == ADC_STREAM_COMPLETED)
    {
        (void)Adc_ReadGroup(group, &Adc_AppReadBuffer[group][0]);
    }

    gAdcAppGroupDone[group] = TRUE;
}

void AdcApp_HwUnit0_Group0EndNotification(void)
{
    swc_adc_test_process_group(0U);
}

void AdcApp_HwUnit1_Group1EndNotification(void)
{
    swc_adc_test_process_group(1U);
}

#include "Icu.h"
#include "Icu_Cfg.h"

volatile uint32 Icu_SignalNotificationNumber = 0U;

void swc_icu_test_init(void)
{
    Icu_EnableNotification(ICU_TIM_CHANNEL21);
    Icu_SetActivationCondition(ICU_TIM_CHANNEL21, ICU_BOTH_EDGES);
    Icu_EnableEdgeDetection(ICU_TIM_CHANNEL21);
    Icu_EnableNotification(ICU_TIM_CHANNEL6);
    Icu_SetActivationCondition(ICU_TIM_CHANNEL6, ICU_BOTH_EDGES);
    Icu_EnableEdgeDetection(ICU_TIM_CHANNEL6);
}

void Icu_SignalNotification_Channel_6(void)
{
    Icu_SignalNotificationNumber++;
}

void Icu_SignalNotification_Channel_21(void)
{
    Icu_SignalNotificationNumber++;
}

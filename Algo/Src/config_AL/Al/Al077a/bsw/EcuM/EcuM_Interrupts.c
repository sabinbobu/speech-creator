#include "Fls_Cfg.h"
#include "Fls_Irq.h"
#include "Adc_Cfg.h"
#include "Gpt_Cfg.h"
#include "Icu_Cfg.h"
#include "Icu_Irq.h"
#include "Spi_Cfg.h"
#include "Can_Irq.h"
#include "msp.h"
#include "hw_interrupt.h"
#include "common_interrupt.h"

void EcuM_Interrupts_Init(void)
{
#if defined(GPT_CHANNEL_0) || defined(GPT_CHANNEL_1)
    NVIC_EnableIRQ(TIMG0_INT_IRQn);
    NVIC_SetPriority(TIMG0_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_2) || defined(GPT_CHANNEL_3)
    NVIC_EnableIRQ(TIMG6_INT_IRQn);
    NVIC_SetPriority(TIMG6_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_4) || defined(GPT_CHANNEL_5)
    NVIC_EnableIRQ(TIMG7_INT_IRQn);
    NVIC_SetPriority(TIMG7_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_6) || defined(GPT_CHANNEL_7)
    NVIC_EnableIRQ(TIMG8_INT_IRQn);
    NVIC_SetPriority(TIMG8_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_8) || defined(GPT_CHANNEL_9)
    NVIC_EnableIRQ(TIMG12_INT_IRQn);
    NVIC_SetPriority(TIMG12_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_10) || defined(GPT_CHANNEL_11) || defined(GPT_CHANNEL_12) || defined(GPT_CHANNEL_13)
    NVIC_EnableIRQ(TIMA0_INT_IRQn);
    NVIC_SetPriority(TIMA0_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_14) || defined(GPT_CHANNEL_15)
    NVIC_EnableIRQ(TIMA1_INT_IRQn);
    NVIC_SetPriority(TIMA1_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_16) || defined(GPT_CHANNEL_17)
    NVIC_EnableIRQ(TIMG9_INT_IRQn);
    NVIC_SetPriority(TIMG9_INT_IRQn, 3);
#endif
#if defined(GPT_CHANNEL_18) || defined(GPT_CHANNEL_19) || defined(GPT_CHANNEL_20) || defined(GPT_CHANNEL_21)
    NVIC_EnableIRQ(TIMG14_INT_IRQn);
    NVIC_SetPriority(TIMG14_INT_IRQn, 3);
#endif
#if defined(SPI_UNIT_SPI0_ACTIVE)
    NVIC_EnableIRQ(SPI0_INT_IRQn);
    NVIC_SetPriority(SPI0_INT_IRQn, 3);
#endif
#if defined(SPI_UNIT_SPI1_ACTIVE)
    NVIC_EnableIRQ(SPI1_INT_IRQn);
    NVIC_SetPriority(SPI1_INT_IRQn, 3);
#endif
#if defined(SPI_UNIT_SPI2_ACTIVE)
    NVIC_EnableIRQ(SPI2_INT_IRQn);
    NVIC_SetPriority(SPI2_INT_IRQn, 3);
#endif
#if (SPI_DMA_ENABLE == STD_ON)
    NVIC_EnableIRQ(DMA_INT_IRQn);
    NVIC_SetPriority(DMA_INT_IRQn, 3);
#endif
#if (STD_ON == FLS_USE_INTERRUPTS)
    NVIC_EnableIRQ(FLASHCTL_INT_IRQn);
#endif
#if (STD_ON == FLS_TIMEOUT_SUPERVISION_ENABLED)
    AppUtils_TimerInit();
    NVIC_EnableIRQ(SysTick_IRQn);
    AppUtils_InterruptEnable();
#endif
    NVIC_EnableIRQ(ADC0_INT_IRQn);
    NVIC_EnableIRQ(ADC1_INT_IRQn);
#if defined(ICU_RESOURCE_TIMG8)
    NVIC_EnableIRQ(TIMG8_INT_IRQn);
    NVIC_SetPriority(TIMG8_INT_IRQn, 3);
#endif
#if defined(ICU_RESOURCE_TIMG14)
    NVIC_EnableIRQ(TIMG14_INT_IRQn);
    NVIC_SetPriority(TIMG14_INT_IRQn, 3);
#endif
#if defined(CAN_CONTROLLER_MCAN0)
    NVIC_EnableIRQ(CANFD0_INT_IRQn);
    NVIC_SetPriority(CANFD0_INT_IRQn, 3);
#endif
}

#if defined(CAN_CONTROLLER_MCAN0)
void CANFD0_IRQHandler(void)
{
    Can_0_Int0ISR();
}
#endif

void GROUP0_IRQHandler(void)
{
    if (Interrupt_getPendingGroup(INTERRUPT_GROUP_0) == INTERRUPT_GROUP0_IIDX_FLASH)
    {
        Fls_Grp0IntISR();
    }
}

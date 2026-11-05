#include "Os.h"
#include "SchM_NvM.h"

void SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Fee_FEE_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Fee_FEE_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }
void SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0(void) { DisableAllInterrupts(); }
void SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0(void) { EnableAllInterrupts(); }

void SchM_Enter_NvM(void)
{
    DisableAllInterrupts();
}

void SchM_Exit_NvM(void)
{
    EnableAllInterrupts();
}

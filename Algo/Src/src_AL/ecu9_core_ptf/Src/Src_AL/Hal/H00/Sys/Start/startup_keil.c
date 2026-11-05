#include <stdint.h>

// WORKAROUND: proof of concept; to be included in scatter file
__asm(".global __STACK_END\n"
      ".equ    __STACK_END,  0x20210000\n"
      ".global __STACK_SIZE\n"
      ".equ    __STACK_SIZE, 0x00000800\n");

extern unsigned int __STACK_END;

/* Keil runtime entry */
extern void __main(void);

/* Default handler */
void Default_Handler(void);

/* Reset handler */
void Reset_Handler(void);

/* Core exception handlers */
extern void NMI_Handler         (void) __attribute__((weak, alias("Default_Handler")));
extern void HardFault_Handler   (void);// __attribute__((weak, alias("Default_Handler")));
extern void SVC_Handler         (void) __attribute__((weak, alias("Default_Handler")));
extern void PendSV_Handler      (void) __attribute__((weak, alias("Default_Handler")));
extern void SysTick_Handler     (void) __attribute__((weak, alias("Default_Handler")));

/* Device Specific Interrupt Handlers */
extern void GROUP0_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void GROUP1_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG8_ICU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart3_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void ADC0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void ADC1_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void CANFD0_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void DAC0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG9_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void SPI0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void SPI1_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void SPI2_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void CANFD1_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart1_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart4_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart0_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG0_PWM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG6_GPT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMA0_PWM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMA1_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG7_IRQHandler    (void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG12_PWM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void TIMG14_ICU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart5_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void I2C0_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void I2C1_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void I2C2_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart7_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void AESADV_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
extern void Cdd_Uart6_Inst_ISR  (void) __attribute__((weak, alias("Default_Handler")));
extern void LFSS_IRQHandler     (void) __attribute__((weak, alias("Default_Handler")));
extern void DMA_IRQHandler      (void) __attribute__((weak, alias("Default_Handler")));

/* Interrupt Vector Table */
__attribute__((used, section(".intvecs")))
void (* const interruptVectors[])(void) =
{
    (void (*)(void))(&__STACK_END),  /* Initial Stack Pointer */
    /* The initial stack pointer */
    Reset_Handler,           /* The reset handler         */
    NMI_Handler,             /* The NMI handler           */
    HardFault_Handler,       /* The hard fault handler    */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    SVC_Handler,             /* SVCall handler            */
    0,                       /* Reserved                  */
    0,                       /* Reserved                  */
    PendSV_Handler,          /* The PendSV handler        */
    SysTick_Handler,         /* SysTick handler           */
    GROUP0_IRQHandler,       /* GROUP0 interrupt handler  */
    GROUP1_IRQHandler,       /* GROUP1 interrupt handler  */
    TIMG8_ICU_IRQHandler,    /* TIMG8 interrupt handler   */
    Cdd_Uart3_Inst_ISR,      /* UART3 interrupt handler   */
    ADC0_IRQHandler,         /* ADC0 interrupt handler    */
    ADC1_IRQHandler,         /* ADC1 interrupt handler    */
    CANFD0_IRQHandler,       /* CANFD0 interrupt handler  */
    DAC0_IRQHandler,         /* DAC0 interrupt handler    */
    TIMG9_IRQHandler,        /* TIMG9 interrupt handler   */
    SPI0_IRQHandler,         /* SPI0 interrupt handler    */
    SPI1_IRQHandler,         /* SPI1 interrupt handler    */
    SPI2_IRQHandler,         /* SPI2 interrupt handler    */
    CANFD1_IRQHandler,       /* CANFD1 interrupt handler  */
    Cdd_Uart1_Inst_ISR,      /* UART1 interrupt handler   */
    Cdd_Uart4_Inst_ISR,      /* UART4 interrupt handler   */
    Cdd_Uart0_Inst_ISR,      /* UART0 interrupt handler   */
    TIMG0_PWM_IRQHandler,        /* TIMG0 interrupt handler   */
    TIMG6_GPT_IRQHandler,        /* TIMG6 interrupt handler   */
    TIMA0_PWM_IRQHandler,        /* TIMA0 interrupt handler   */
    TIMA1_IRQHandler,        /* TIMA1 interrupt handler   */
    TIMG7_IRQHandler,        /* TIMG7 interrupt handler   */
    TIMG12_PWM_IRQHandler,       /* TIMG12 interrupt handler  */
    TIMG14_ICU_IRQHandler,       /* TIMG14 interrupt handler  */
    Cdd_Uart5_Inst_ISR,      /* UART5 interrupt handler   */
    I2C0_IRQHandler,         /* I2C0 interrupt handler    */
    I2C1_IRQHandler,         /* I2C1 interrupt handler    */
    I2C2_IRQHandler,         /* I2C2 interrupt handler    */
    Cdd_Uart7_Inst_ISR,      /* UART7 interrupt handler   */
    AESADV_IRQHandler,       /* AESADV interrupt handler  */
    Cdd_Uart6_Inst_ISR,      /* UART6 interrupt handler   */
    LFSS_IRQHandler,         /* LFSS interrupt handler    */
    DMA_IRQHandler,          /* DMA interrupt handler     */
};

/* Reset Handler */
void Reset_Handler(void)
{
  __main();   /* Enter Keil runtime */
}

/* Default interrupt handler */
void Default_Handler(void)
{
  while (1)
  {
    /* Infinite loop */
  }
}

void HardFault_Handler(void)
{
  while (1)
  {
    /* Infinite loop */
  }
}
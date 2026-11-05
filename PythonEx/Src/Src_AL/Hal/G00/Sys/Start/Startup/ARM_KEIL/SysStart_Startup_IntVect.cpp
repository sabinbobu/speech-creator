
#include <algorithm>
#include <array>
#include <cstddef>

#include <Cpu/HalCpu.h>
#include <mcal_reg_access.h>

extern "C"
{
  extern std::uint32_t Image$$ER_STACK$$ZI$$Limit;
}

extern "C" void __my_startup                        () __attribute__((section(".startup"),used, noinline));
extern "C" void __vector_unused_irq                 () __attribute__((used, noinline));
extern "C" void __nmi_handler                       () __attribute__((used, noinline));
extern "C" void __hard_fault_handler                () __attribute__((used, noinline));
extern "C" void __mem_manage_handler                () __attribute__((used, noinline));
extern "C" void __bus_fault_handler                 () __attribute__((used, noinline));
extern "C" void __usage_fault_handler               () __attribute__((used, noinline));
extern "C" void __svc_handler                       () __attribute__((used, noinline));
extern "C" void __debug_mon_handler                 () __attribute__((used, noinline));
extern "C" void __pend_sv_handler                   () __attribute__((used, noinline));
extern "C" void SysTick_Handler                     () __attribute__((used, noinline));
extern "C" void DMA0_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 0 transfer complete
extern "C" void DMA1_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 1 transfer complete
extern "C" void DMA2_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 2 transfer complete
extern "C" void DMA3_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 3 transfer complete
extern "C" void DMA4_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 4 transfer complete
extern "C" void DMA5_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 5 transfer complete
extern "C" void DMA6_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 6 transfer complete
extern "C" void DMA7_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 7 transfer complete
extern "C" void DMA8_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 8 transfer complete
extern "C" void DMA9_IRQHandler                     () __attribute__((used, noinline)); // DMA channel 9 transfer complete
extern "C" void DMA10_IRQHandler                    () __attribute__((used, noinline)); // DMA channel 10 transfer complete
extern "C" void DMA11_IRQHandler                    () __attribute__((used, noinline)); // DMA channel 11 transfer complete
extern "C" void DMA12_IRQHandler                    () __attribute__((used, noinline)); // DMA channel 12 transfer complete
extern "C" void DMA13_IRQHandler                    () __attribute__((used, noinline)); // DMA channel 13 transfer complete
extern "C" void DMA14_IRQHandler                    () __attribute__((used, noinline)); // DMA channel 14 transfer complete
extern "C" void DMA15_IRQHandler                    () __attribute__((used, noinline)); // DMA channel 15 transfer complete
extern "C" void DMA_Error_IRQHandler                () __attribute__((used, noinline)); // DMA error interrupt channels 0-15
extern "C" void MCM_IRQHandler                      () __attribute__((used, noinline)); // FPU sources
extern "C" void FTFC_IRQHandler                     () __attribute__((used, noinline)); // FTFC Command complete
extern "C" void Read_Collision_IRQHandler           () __attribute__((used, noinline)); // FTFC Read collision
extern "C" void LVD_LVW_IRQHandler                  () __attribute__((used, noinline)); // PMC Low voltage detect interrupt
extern "C" void FTFC_Fault_IRQHandler               () __attribute__((used, noinline)); // FTFC Double bit fault detect
extern "C" void WDOG_EWM_IRQHandler                 () __attribute__((used, noinline)); // Single interrupt vector for WDOG and EWM
extern "C" void RCM_IRQHandler                      () __attribute__((used, noinline)); // RCM Asynchronous Interrupt
extern "C" void LPI2C0_Master_IRQHandler            () __attribute__((used, noinline)); // LPI2C0 Master Interrupt
extern "C" void LPI2C0_Slave_IRQHandler             () __attribute__((used, noinline)); // LPI2C0 Slave Interrupt
extern "C" void LPSPI0_IRQHandler                   () __attribute__((used, noinline)); // LPSPI0 Interrupt
extern "C" void LPSPI1_IRQHandler                   () __attribute__((used, noinline)); // LPSPI1 Interrupt
extern "C" void LPSPI2_IRQHandler                   () __attribute__((used, noinline)); // LPSPI2 Interrupt
extern "C" void Reserved45_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 45
extern "C" void Reserved46_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 46
extern "C" void LPUART0_RxTx_IRQHandler             () __attribute__((used, noinline)); // LPUART0 Transmit / Receive Interrupt
extern "C" void Reserved48_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 48
extern "C" void LPUART1_RxTx_IRQHandler             () __attribute__((used, noinline)); // LPUART1 Transmit / Receive  Interrupt
extern "C" void Reserved50_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 50
extern "C" void LPUART2_RxTx_IRQHandler             () __attribute__((used, noinline)); // LPUART2 Transmit / Receive  Interrupt
extern "C" void Reserved52_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 52
extern "C" void Reserved53_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 53
extern "C" void Reserved54_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 54
extern "C" void ADC0_IRQHandler                     () __attribute__((used, noinline)); // ADC0 interrupt request.
extern "C" void ADC1_IRQHandler                     () __attribute__((used, noinline)); // ADC1 interrupt request.
extern "C" void CMP0_IRQHandler                     () __attribute__((used, noinline)); // CMP0 interrupt request
extern "C" void Reserved58_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 58
extern "C" void Reserved59_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 59
extern "C" void ERM_single_fault_IRQHandler         () __attribute__((used, noinline)); // ERM single bit error correction
extern "C" void ERM_double_fault_IRQHandler         () __attribute__((used, noinline)); // ERM double bit error non-correctable
extern "C" void RTC_IRQHandler                      () __attribute__((used, noinline)); // RTC alarm interrupt
extern "C" void RTC_Seconds_IRQHandler              () __attribute__((used, noinline)); // RTC seconds interrupt
extern "C" void LPIT0_Ch0_IRQHandler                () __attribute__((used, noinline)); // LPIT0 channel 0 overflow interrupt
extern "C" void LPIT0_Ch1_IRQHandler                () __attribute__((used, noinline)); // LPIT0 channel 1 overflow interrupt
extern "C" void LPIT0_Ch2_IRQHandler                () __attribute__((used, noinline)); // LPIT0 channel 2 overflow interrupt
extern "C" void LPIT0_Ch3_IRQHandler                () __attribute__((used, noinline)); // LPIT0 channel 3 overflow interrupt
extern "C" void PDB0_IRQHandler                     () __attribute__((used, noinline)); // PDB0 interrupt
extern "C" void Reserved69_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 69
extern "C" void Reserved70_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 70
extern "C" void Reserved71_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 71
extern "C" void Reserved72_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 72
extern "C" void SCG_IRQHandler                      () __attribute__((used, noinline)); // SCG bus interrupt request
extern "C" void LPTMR0_IRQHandler                   () __attribute__((used, noinline)); // LPTIMER interrupt request
extern "C" void PORTA_IRQHandler                    () __attribute__((used, noinline)); // Port A pin detect interrupt
extern "C" void PORTB_IRQHandler                    () __attribute__((used, noinline)); // Port B pin detect interrupt
extern "C" void PORTC_IRQHandler                    () __attribute__((used, noinline)); // Port C pin detect interrupt
extern "C" void PORTD_IRQHandler                    () __attribute__((used, noinline)); // Port D pin detect interrupt
extern "C" void PORTE_IRQHandler                    () __attribute__((used, noinline)); // Port E pin detect interrupt
extern "C" void SWI_IRQHandler                      () __attribute__((used, noinline)); // Software interrupt
extern "C" void Reserved81_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 81
extern "C" void Reserved82_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 82
extern "C" void Reserved83_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 83
extern "C" void PDB1_IRQHandler                     () __attribute__((used, noinline)); // PDB1 interrupt
extern "C" void FLEXIO_IRQHandler                   () __attribute__((used, noinline)); // FlexIO Interrupt
extern "C" void Reserved86_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 86
extern "C" void Reserved87_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 87
extern "C" void Reserved88_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 88
extern "C" void Reserved89_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 89
extern "C" void Reserved90_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 90
extern "C" void Reserved91_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 91
extern "C" void Reserved92_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 92
extern "C" void Reserved93_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 93
extern "C" void DRV_CAN_f_it_CanErr                 () __attribute__((used, noinline)); // CAN0 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
extern "C" void CAN0_Error_IRQHandler               () __attribute__((used, noinline)); // CAN0 Interrupt indicating that errors were detected on the CAN bus
extern "C" void CAN0_Wake_Up_IRQHandler             () __attribute__((used, noinline)); // CAN0 Interrupt asserted when Pretended Networking operation is enabled, and a valid message matches the selected filter criteria during Low Power mode
extern "C" void DRV_CAN_f_it_Can_BUF_0_15           () __attribute__((used, noinline)); // CAN0 OR'ed Message buffer (0-15)
extern "C" void DRV_CAN_f_it_Can_BUF_16_31          () __attribute__((used, noinline)); // CAN0 OR'ed Message buffer (16-31)
extern "C" void Reserved99_IRQHandler               () __attribute__((used, noinline)); // Reserved Interrupt 99
extern "C" void Reserved100_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 100
extern "C" void CAN1_ORed_IRQHandler                () __attribute__((used, noinline)); // CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
extern "C" void CAN1_Error_IRQHandler               () __attribute__((used, noinline)); // CAN1 Interrupt indicating that errors were detected on the CAN bus
extern "C" void Reserved103_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 103
extern "C" void CAN1_ORed_0_15_MB_IRQHandler        () __attribute__((used, noinline)); // CAN1 OR'ed Interrupt for Message buffer (0-15)
extern "C" void CAN1_ORed_16_31_MB_IRQHandler       () __attribute__((used, noinline)); // CAN1 OR'ed Interrupt for Message buffer (16-31)
extern "C" void Reserved106_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 106
extern "C" void Reserved107_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 107
extern "C" void CAN2_ORed_IRQHandler                () __attribute__((used, noinline)); // CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
extern "C" void CAN2_Error_IRQHandler               () __attribute__((used, noinline)); // CAN2 Interrupt indicating that errors were detected on the CAN bus
extern "C" void Reserved110_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 110
extern "C" void CAN2_ORed_0_15_MB_IRQHandler        () __attribute__((used, noinline)); // CAN2 OR'ed Message buffer (0-15)
extern "C" void Reserved112_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 112
extern "C" void Reserved113_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 113
extern "C" void Reserved114_IRQHandler              () __attribute__((used, noinline)); // Reserved Interrupt 114
extern "C" void FTM0_Ch0_Ch1_IRQHandler             () __attribute__((used, noinline)); // FTM0 Channel 0 and 1 interrupt
extern "C" void FTM0_Ch2_Ch3_IRQHandler             () __attribute__((used, noinline)); // FTM0 Channel 2 and 3 interrupt
extern "C" void FTM0_Ch4_Ch5_IRQHandler             () __attribute__((used, noinline)); // FTM0 Channel 4 and 5 interrupt
extern "C" void FTM0_Ch6_Ch7_IRQHandler             () __attribute__((used, noinline)); // FTM0 Channel 6 and 7 interrupt
extern "C" void FTM0_Fault_IRQHandler               () __attribute__((used, noinline)); // FTM0 Fault interrupt
extern "C" void FTM0_Ovf_Reload_IRQHandler          () __attribute__((used, noinline)); // FTM0 Counter overflow and Reload interrupt
extern "C" void FTM1_Ch0_Ch1_IRQHandler             () __attribute__((used, noinline)); // FTM1 Channel 0 and 1 interrupt
extern "C" void FTM1_Ch2_Ch3_IRQHandler             () __attribute__((used, noinline)); // FTM1 Channel 2 and 3 interrupt
extern "C" void FTM1_Ch4_Ch5_IRQHandler             () __attribute__((used, noinline)); // FTM1 Channel 4 and 5 interrupt
extern "C" void FTM1_Ch6_Ch7_IRQHandler             () __attribute__((used, noinline)); // FTM1 Channel 6 and 7 interrupt
extern "C" void FTM1_Fault_IRQHandler               () __attribute__((used, noinline)); // FTM1 Fault interrupt
extern "C" void FTM1_Ovf_Reload_IRQHandler          () __attribute__((used, noinline)); // FTM1 Counter overflow and Reload interrupt
extern "C" void FTM2_Ch0_Ch1_IRQHandler             () __attribute__((used, noinline)); // FTM2 Channel 0 and 1 interrupt
extern "C" void FTM2_Ch2_Ch3_IRQHandler             () __attribute__((used, noinline)); // FTM2 Channel 2 and 3 interrupt
extern "C" void FTM2_Ch4_Ch5_IRQHandler             () __attribute__((used, noinline)); // FTM2 Channel 4 and 5 interrupt
extern "C" void FTM2_Ch6_Ch7_IRQHandler             () __attribute__((used, noinline)); // FTM2 Channel 6 and 7 interrupt
extern "C" void FTM2_Fault_IRQHandler               () __attribute__((used, noinline)); // FTM2 Fault interrupt
extern "C" void FTM2_Ovf_Reload_IRQHandler          () __attribute__((used, noinline)); // FTM2 Counter overflow and Reload interrupt
extern "C" void FTM3_Ch0_Ch1_IRQHandler             () __attribute__((used, noinline)); // FTM3 Channel 0 and 1 interrupt
extern "C" void FTM3_Ch2_Ch3_IRQHandler             () __attribute__((used, noinline)); // FTM3 Channel 2 and 3 interrupt
extern "C" void FTM3_Ch4_Ch5_IRQHandler             () __attribute__((used, noinline)); // FTM3 Channel 4 and 5 interrupt
extern "C" void FTM3_Ch6_Ch7_IRQHandler             () __attribute__((used, noinline)); // FTM3 Channel 6 and 7 interrupt
extern "C" void FTM3_Fault_IRQHandler               () __attribute__((used, noinline)); // FTM3 Fault interrupt
extern "C" void FTM3_Ovf_Reload_IRQHandler          () __attribute__((used, noinline)); // FTM3 Counter overflow and Reload interrupt
extern "C" void FTM4_Ch0_Ch1_IRQHandler             () __attribute__((used, noinline)); // FTM4 Channel 0 and 1 interrupt
extern "C" void FTM4_Ch2_Ch3_IRQHandler             () __attribute__((used, noinline)); // FTM4 Channel 2 and 3 interrupt
extern "C" void FTM4_Ch4_Ch5_IRQHandler             () __attribute__((used, noinline)); // FTM4 Channel 4 and 5 interrupt
extern "C" void FTM4_Ch6_Ch7_IRQHandler             () __attribute__((used, noinline)); // FTM4 Channel 6 and 7 interrupt
extern "C" void FTM4_Fault_IRQHandler               () __attribute__((used, noinline)); // FTM4 Fault interrupt
extern "C" void FTM4_Ovf_Reload_IRQHandler          () __attribute__((used, noinline)); // FTM4 Counter overflow and Reload interrupt
extern "C" void FTM5_Ch0_Ch1_IRQHandler             () __attribute__((used, noinline)); // FTM5 Channel 0 and 1 interrupt
extern "C" void FTM5_Ch2_Ch3_IRQHandler             () __attribute__((used, noinline)); // FTM5 Channel 2 and 3 interrupt
extern "C" void FTM5_Ch4_Ch5_IRQHandler             () __attribute__((used, noinline)); // FTM5 Channel 4 and 5 interrupt
extern "C" void FTM5_Ch6_Ch7_IRQHandler             () __attribute__((used, noinline)); // FTM5 Channel 6 and 7 interrupt
extern "C" void FTM5_Fault_IRQHandler               () __attribute__((used, noinline)); // FTM5 Fault interrupt
extern "C" void FTM5_Ovf_Reload_IRQHandler          () __attribute__((used, noinline)); // FTM5 Counter overflow and Reload interrupt
extern "C" void DefaultISR                          () __attribute__((used, noinline)); // 151


extern "C" void __vector_unused_irq                 () { for(;;) { HalCpuNop(); } }
extern "C" void __nmi_handler                       () { for(;;) { HalCpuNop(); } }
extern "C" void __hard_fault_handler                () { for(;;) { HalCpuNop(); } }
extern "C" void __mem_manage_handler                () { for(;;) { HalCpuNop(); } }
extern "C" void __bus_fault_handler                 () { for(;;) { HalCpuNop(); } }
extern "C" void __usage_fault_handler               () { for(;;) { HalCpuNop(); } }
extern "C" void __svc_handler                       () { for(;;) { HalCpuNop(); } }
extern "C" void __debug_mon_handler                 () { for(;;) { HalCpuNop(); } }
extern "C" void __pend_sv_handler                   () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA0_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA1_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA2_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA3_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA4_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA5_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA6_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void DMA7_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void DMA8_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void DMA9_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void DMA10_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void DMA11_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void DMA12_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void DMA13_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void DMA14_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void DMA15_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void DMA_Error_IRQHandler                () { for(;;) { HalCpuNop(); } }
extern "C" void MCM_IRQHandler                      () { for(;;) { HalCpuNop(); } }
extern "C" void FTFC_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void Read_Collision_IRQHandler           () { for(;;) { HalCpuNop(); } }
extern "C" void LVD_LVW_IRQHandler                  () { for(;;) { HalCpuNop(); } }
extern "C" void FTFC_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void WDOG_EWM_IRQHandler                 () { for(;;) { HalCpuNop(); } }
extern "C" void RCM_IRQHandler                      () { for(;;) { HalCpuNop(); } }
extern "C" void LPI2C0_Master_IRQHandler            () { for(;;) { HalCpuNop(); } }
extern "C" void LPI2C0_Slave_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void LPSPI0_IRQHandler                   () { for(;;) { HalCpuNop(); } }
extern "C" void LPSPI1_IRQHandler                   () { for(;;) { HalCpuNop(); } }
extern "C" void LPSPI2_IRQHandler                   () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved45_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved46_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void LPUART0_RxTx_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved48_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void LPUART1_RxTx_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved50_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void LPUART2_RxTx_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved52_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved53_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved54_IRQHandler               () { for(;;) { HalCpuNop(); } }
//extern "C" void ADC0_IRQHandler                     () { for(;;) { HalCpuNop(); } }
//extern "C" void ADC1_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void CMP0_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved58_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved59_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void ERM_single_fault_IRQHandler         () { for(;;) { HalCpuNop(); } }
extern "C" void ERM_double_fault_IRQHandler         () { for(;;) { HalCpuNop(); } }
extern "C" void RTC_IRQHandler                      () { for(;;) { HalCpuNop(); } }
extern "C" void RTC_Seconds_IRQHandler              () { for(;;) { HalCpuNop(); } }
//extern "C" void LPIT0_Ch0_IRQHandler                () { for(;;) { HalCpuNop(); } }
//extern "C" void LPIT0_Ch1_IRQHandler                () { for(;;) { HalCpuNop(); } }
extern "C" void LPIT0_Ch2_IRQHandler                () { for(;;) { HalCpuNop(); } }
extern "C" void LPIT0_Ch3_IRQHandler                () { for(;;) { HalCpuNop(); } }
//extern "C" void PDB0_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved69_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved70_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved71_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved72_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void SCG_IRQHandler                      () { for(;;) { HalCpuNop(); } }
//extern "C" void LPTMR0_IRQHandler                   () { for(;;) { HalCpuNop(); } }
extern "C" void PORTA_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void PORTB_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void PORTC_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void PORTD_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void PORTE_IRQHandler                    () { for(;;) { HalCpuNop(); } }
extern "C" void SWI_IRQHandler                      () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved81_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved82_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved83_IRQHandler               () { for(;;) { HalCpuNop(); } }
//extern "C" void PDB1_IRQHandler                     () { for(;;) { HalCpuNop(); } }
extern "C" void FLEXIO_IRQHandler                   () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved86_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved87_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved88_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved89_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved90_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved91_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved92_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved93_IRQHandler               () { for(;;) { HalCpuNop(); } }
//extern "C" void DRV_CAN_f_it_CanErr                () { for(;;) { HalCpuNop(); } }
extern "C" void CAN0_Error_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void CAN0_Wake_Up_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void DRV_CAN_f_it_Can_BUF_0_15           () { for(;;) { HalCpuNop(); } }
//extern "C" void DRV_CAN_f_it_Can_BUF_16_31          () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved99_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved100_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void CAN1_ORed_IRQHandler                () { for(;;) { HalCpuNop(); } }
extern "C" void CAN1_Error_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved103_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void CAN1_ORed_0_15_MB_IRQHandler        () { for(;;) { HalCpuNop(); } }
extern "C" void CAN1_ORed_16_31_MB_IRQHandler       () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved106_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved107_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void CAN2_ORed_IRQHandler                () { for(;;) { HalCpuNop(); } }
extern "C" void CAN2_Error_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved110_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void CAN2_ORed_0_15_MB_IRQHandler        () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved112_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved113_IRQHandler              () { for(;;) { HalCpuNop(); } }
extern "C" void Reserved114_IRQHandler              () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM0_Ch0_Ch1_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM0_Ch2_Ch3_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM0_Ch4_Ch5_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM0_Ch6_Ch7_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void FTM0_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void FTM0_Ovf_Reload_IRQHandler          () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM1_Ch0_Ch1_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM1_Ch2_Ch3_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM1_Ch4_Ch5_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM1_Ch6_Ch7_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void FTM1_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void FTM1_Ovf_Reload_IRQHandler          () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM2_Ch0_Ch1_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM2_Ch2_Ch3_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM2_Ch4_Ch5_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM2_Ch6_Ch7_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void FTM2_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void FTM2_Ovf_Reload_IRQHandler          () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM3_Ch0_Ch1_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM3_Ch2_Ch3_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM3_Ch4_Ch5_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM3_Ch6_Ch7_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void FTM3_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void FTM3_Ovf_Reload_IRQHandler          () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM4_Ch0_Ch1_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM4_Ch2_Ch3_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM4_Ch4_Ch5_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM4_Ch6_Ch7_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void FTM4_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void FTM4_Ovf_Reload_IRQHandler          () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM5_Ch0_Ch1_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM5_Ch2_Ch3_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM5_Ch4_Ch5_IRQHandler             () { for(;;) { HalCpuNop(); } }
//extern "C" void FTM5_Ch6_Ch7_IRQHandler             () { for(;;) { HalCpuNop(); } }
extern "C" void FTM5_Fault_IRQHandler               () { for(;;) { HalCpuNop(); } }
extern "C" void FTM5_Ovf_Reload_IRQHandler          () { for(;;) { HalCpuNop(); } }
extern "C" void DefaultISR                          () { for(;;) { HalCpuNop(); } }

namespace
{
  using isr_type = void(*)(void);

  constexpr std::size_t number_of_interrupts = 256U;
}

extern "C"
const std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".intvec")));

// See pages 238-242 in the microcontroller manual.
extern "C"
const std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  (isr_type) &Image$$ER_STACK$$ZI$$Limit,
                             // 0x0000, initial stack pointer
  __my_startup,              // 0x0004, reset
  __nmi_handler,             // 0x0008, nmi exception
  __hard_fault_handler,      // 0x000C, hard fault exception
  __mem_manage_handler,      // 0x0010, memory management exception
  __bus_fault_handler,       // 0x0014, bus fault exception
  __usage_fault_handler,     // 0x0018, usage fault exception
  __vector_unused_irq,       // 0x001C, reserved
  __vector_unused_irq,       // 0x0020, reserved
  __vector_unused_irq,       // 0x0024, reserved
  __vector_unused_irq,       // 0x0028, reserved
  __svc_handler,             // 0x002C, svc handler
  __debug_mon_handler,       // 0x0030, debug monitor
  __vector_unused_irq,       // 0x0034, reserved
  __pend_sv_handler,         // 0x0038, pending svc
  SysTick_Handler,           // 0x003C, system tick handler
  DMA0_IRQHandler,                                 // DMA channel 0 transfer complete
  DMA1_IRQHandler,                                 // DMA channel 1 transfer complete
  DMA2_IRQHandler,                                 // DMA channel 2 transfer complete
  DMA3_IRQHandler,                                 // DMA channel 3 transfer complete
  DMA4_IRQHandler,                                 // DMA channel 4 transfer complete
  DMA5_IRQHandler,                                 // DMA channel 5 transfer complete
  DMA6_IRQHandler,                                 // DMA channel 6 transfer complete
  DMA7_IRQHandler,                                 // DMA channel 7 transfer complete
  DMA8_IRQHandler,                                 // DMA channel 8 transfer complete
  DMA9_IRQHandler,                                 // DMA channel 9 transfer complete
  DMA10_IRQHandler,                                // DMA channel 10 transfer complete
  DMA11_IRQHandler,                                // DMA channel 11 transfer complete
  DMA12_IRQHandler,                                // DMA channel 12 transfer complete
  DMA13_IRQHandler,                                // DMA channel 13 transfer complete
  DMA14_IRQHandler,                                // DMA channel 14 transfer complete
  DMA15_IRQHandler,                                // DMA channel 15 transfer complete
  DMA_Error_IRQHandler,                            // DMA error interrupt channels 0-15
  MCM_IRQHandler,                                  // FPU sources
  FTFC_IRQHandler,                                 // FTFC Command complete
  Read_Collision_IRQHandler,                       // FTFC Read collision
  LVD_LVW_IRQHandler,                              // PMC Low voltage detect interrupt
  FTFC_Fault_IRQHandler,                           // FTFC Double bit fault detect
  WDOG_EWM_IRQHandler,                             // Single interrupt vector for WDOG and EWM
  RCM_IRQHandler,                                  // RCM Asynchronous Interrupt
  LPI2C0_Master_IRQHandler,                        // LPI2C0 Master Interrupt
  LPI2C0_Slave_IRQHandler,                         // LPI2C0 Slave Interrupt
  LPSPI0_IRQHandler,                               // LPSPI0 Interrupt
  LPSPI1_IRQHandler,                               // LPSPI1 Interrupt
  LPSPI2_IRQHandler,                               // LPSPI2 Interrupt
  Reserved45_IRQHandler,                           // Reserved Interrupt 45
  Reserved46_IRQHandler,                           // Reserved Interrupt 46
  LPUART0_RxTx_IRQHandler,                         // LPUART0 Transmit / Receive Interrupt
  Reserved48_IRQHandler,                           // Reserved Interrupt 48
  LPUART1_RxTx_IRQHandler,                         // LPUART1 Transmit / Receive  Interrupt
  Reserved50_IRQHandler,                           // Reserved Interrupt 50
  LPUART2_RxTx_IRQHandler,                         // LPUART2 Transmit / Receive  Interrupt
  Reserved52_IRQHandler,                           // Reserved Interrupt 52
  Reserved53_IRQHandler,                           // Reserved Interrupt 53
  Reserved54_IRQHandler,                           // Reserved Interrupt 54
  ADC0_IRQHandler,                                 // ADC0 interrupt request.
  ADC1_IRQHandler,                                 // ADC1 interrupt request.
  CMP0_IRQHandler,                                 // CMP0 interrupt request
  Reserved58_IRQHandler,                           // Reserved Interrupt 58
  Reserved59_IRQHandler,                           // Reserved Interrupt 59
  ERM_single_fault_IRQHandler,                     // ERM single bit error correction
  ERM_double_fault_IRQHandler,                     // ERM double bit error non-correctable
  RTC_IRQHandler,                                  // RTC alarm interrupt
  RTC_Seconds_IRQHandler,                          // RTC seconds interrupt
  LPIT0_Ch0_IRQHandler,                            // LPIT0 channel 0 overflow interrupt
  LPIT0_Ch1_IRQHandler,                            // LPIT0 channel 1 overflow interrupt
  LPIT0_Ch2_IRQHandler,                            // LPIT0 channel 2 overflow interrupt
  LPIT0_Ch3_IRQHandler,                            // LPIT0 channel 3 overflow interrupt
  PDB0_IRQHandler,                                 // PDB0 interrupt
  Reserved69_IRQHandler,                           // Reserved Interrupt 69
  Reserved70_IRQHandler,                           // Reserved Interrupt 70
  Reserved71_IRQHandler,                           // Reserved Interrupt 71
  Reserved72_IRQHandler,                           // Reserved Interrupt 72
  SCG_IRQHandler,                                  // SCG bus interrupt request
  LPTMR0_IRQHandler,                               // LPTIMER interrupt request
  PORTA_IRQHandler,                                // Port A pin detect interrupt
  PORTB_IRQHandler,                                // Port B pin detect interrupt
  PORTC_IRQHandler,                                // Port C pin detect interrupt
  PORTD_IRQHandler,                                // Port D pin detect interrupt
  PORTE_IRQHandler,                                // Port E pin detect interrupt
  SWI_IRQHandler,                                  // Software interrupt
  Reserved81_IRQHandler,                           // Reserved Interrupt 81
  Reserved82_IRQHandler,                           // Reserved Interrupt 82
  Reserved83_IRQHandler,                           // Reserved Interrupt 83
  PDB1_IRQHandler,                                 // PDB1 interrupt
  FLEXIO_IRQHandler,                               // FlexIO Interrupt
  Reserved86_IRQHandler,                           // Reserved Interrupt 86
  Reserved87_IRQHandler,                           // Reserved Interrupt 87
  Reserved88_IRQHandler,                           // Reserved Interrupt 88
  Reserved89_IRQHandler,                           // Reserved Interrupt 89
  Reserved90_IRQHandler,                           // Reserved Interrupt 90
  Reserved91_IRQHandler,                           // Reserved Interrupt 91
  Reserved92_IRQHandler,                           // Reserved Interrupt 92
  Reserved93_IRQHandler,                           // Reserved Interrupt 93
  DRV_CAN_f_it_CanErr,                            // CAN0 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
  CAN0_Error_IRQHandler,                          // CAN0 Interrupt indicating that errors were detected on the CAN bus
  CAN0_Wake_Up_IRQHandler,                         // CAN0 Interrupt asserted when Pretended Networking operation is enabled, and a valid message matches the selected filter criteria during Low Power mode
  DRV_CAN_f_it_Can_BUF_0_15,                       // CAN0 OR'ed Message buffer (0-15)
  DRV_CAN_f_it_Can_BUF_16_31,                      // CAN0 OR'ed Message buffer (16-31)
  Reserved99_IRQHandler,                           // Reserved Interrupt 99
  Reserved100_IRQHandler,                          // Reserved Interrupt 100
  CAN1_ORed_IRQHandler,                            // CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
  CAN1_Error_IRQHandler,                           // CAN1 Interrupt indicating that errors were detected on the CAN bus
  Reserved103_IRQHandler,                          // Reserved Interrupt 103
  CAN1_ORed_0_15_MB_IRQHandler,                    // CAN1 OR'ed Interrupt for Message buffer (0-15)
  CAN1_ORed_16_31_MB_IRQHandler,                   // CAN1 OR'ed Interrupt for Message buffer (16-31)
  Reserved106_IRQHandler,                          // Reserved Interrupt 106
  Reserved107_IRQHandler,                          // Reserved Interrupt 107
  CAN2_ORed_IRQHandler,                            // CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning]
  CAN2_Error_IRQHandler,                           // CAN2 Interrupt indicating that errors were detected on the CAN bus
  Reserved110_IRQHandler,                          // Reserved Interrupt 110
  CAN2_ORed_0_15_MB_IRQHandler,                    // CAN2 OR'ed Message buffer (0-15)
  Reserved112_IRQHandler,                          // Reserved Interrupt 112
  Reserved113_IRQHandler,                          // Reserved Interrupt 113
  Reserved114_IRQHandler,                          // Reserved Interrupt 114
  FTM0_Ch0_Ch1_IRQHandler,                         // FTM0 Channel 0 and 1 interrupt
  FTM0_Ch2_Ch3_IRQHandler,                         // FTM0 Channel 2 and 3 interrupt
  FTM0_Ch4_Ch5_IRQHandler,                         // FTM0 Channel 4 and 5 interrupt
  FTM0_Ch6_Ch7_IRQHandler,                         // FTM0 Channel 6 and 7 interrupt
  FTM0_Fault_IRQHandler,                           // FTM0 Fault interrupt
  FTM0_Ovf_Reload_IRQHandler,                      // FTM0 Counter overflow and Reload interrupt
  FTM1_Ch0_Ch1_IRQHandler,                         // FTM1 Channel 0 and 1 interrupt
  FTM1_Ch2_Ch3_IRQHandler,                         // FTM1 Channel 2 and 3 interrupt
  FTM1_Ch4_Ch5_IRQHandler,                         // FTM1 Channel 4 and 5 interrupt
  FTM1_Ch6_Ch7_IRQHandler,                         // FTM1 Channel 6 and 7 interrupt
  FTM1_Fault_IRQHandler,                           // FTM1 Fault interrupt
  FTM1_Ovf_Reload_IRQHandler,                      // FTM1 Counter overflow and Reload interrupt
  FTM2_Ch0_Ch1_IRQHandler,                         // FTM2 Channel 0 and 1 interrupt
  FTM2_Ch2_Ch3_IRQHandler,                         // FTM2 Channel 2 and 3 interrupt
  FTM2_Ch4_Ch5_IRQHandler,                         // FTM2 Channel 4 and 5 interrupt
  FTM2_Ch6_Ch7_IRQHandler,                         // FTM2 Channel 6 and 7 interrupt
  FTM2_Fault_IRQHandler,                           // FTM2 Fault interrupt
  FTM2_Ovf_Reload_IRQHandler,                      // FTM2 Counter overflow and Reload interrupt
  FTM3_Ch0_Ch1_IRQHandler,                         // FTM3 Channel 0 and 1 interrupt
  FTM3_Ch2_Ch3_IRQHandler,                         // FTM3 Channel 2 and 3 interrupt
  FTM3_Ch4_Ch5_IRQHandler,                         // FTM3 Channel 4 and 5 interrupt
  FTM3_Ch6_Ch7_IRQHandler,                         // FTM3 Channel 6 and 7 interrupt
  FTM3_Fault_IRQHandler,                           // FTM3 Fault interrupt
  FTM3_Ovf_Reload_IRQHandler,                      // FTM3 Counter overflow and Reload interrupt
  FTM4_Ch0_Ch1_IRQHandler,                         // FTM4 Channel 0 and 1 interrupt
  FTM4_Ch2_Ch3_IRQHandler,                         // FTM4 Channel 2 and 3 interrupt
  FTM4_Ch4_Ch5_IRQHandler,                         // FTM4 Channel 4 and 5 interrupt
  FTM4_Ch6_Ch7_IRQHandler,                         // FTM4 Channel 6 and 7 interrupt
  FTM4_Fault_IRQHandler,                           // FTM4 Fault interrupt
  FTM4_Ovf_Reload_IRQHandler,                      // FTM4 Counter overflow and Reload interrupt
  FTM5_Ch0_Ch1_IRQHandler,                         // FTM5 Channel 0 and 1 interrupt
  FTM5_Ch2_Ch3_IRQHandler,                         // FTM5 Channel 2 and 3 interrupt
  FTM5_Ch4_Ch5_IRQHandler,                         // FTM5 Channel 4 and 5 interrupt
  FTM5_Ch6_Ch7_IRQHandler,                         // FTM5 Channel 6 and 7 interrupt
  FTM5_Fault_IRQHandler,                           // FTM5 Fault interrupt
  FTM5_Ovf_Reload_IRQHandler,                      // FTM5 Counter overflow and Reload interrupt
  DefaultISR,                                      // 151
  DefaultISR,                                      // 152
  DefaultISR,                                      // 153
  DefaultISR,                                      // 154
  DefaultISR,                                      // 155
  DefaultISR,                                      // 156
  DefaultISR,                                      // 157
  DefaultISR,                                      // 158
  DefaultISR,                                      // 159
  DefaultISR,                                      // 160
  DefaultISR,                                      // 161
  DefaultISR,                                      // 162
  DefaultISR,                                      // 163
  DefaultISR,                                      // 164
  DefaultISR,                                      // 165
  DefaultISR,                                      // 166
  DefaultISR,                                      // 167
  DefaultISR,                                      // 168
  DefaultISR,                                      // 169
  DefaultISR,                                      // 170
  DefaultISR,                                      // 171
  DefaultISR,                                      // 172
  DefaultISR,                                      // 173
  DefaultISR,                                      // 174
  DefaultISR,                                      // 175
  DefaultISR,                                      // 176
  DefaultISR,                                      // 177
  DefaultISR,                                      // 178
  DefaultISR,                                      // 179
  DefaultISR,                                      // 180
  DefaultISR,                                      // 181
  DefaultISR,                                      // 182
  DefaultISR,                                      // 183
  DefaultISR,                                      // 184
  DefaultISR,                                      // 185
  DefaultISR,                                      // 186
  DefaultISR,                                      // 187
  DefaultISR,                                      // 188
  DefaultISR,                                      // 189
  DefaultISR,                                      // 190
  DefaultISR,                                      // 191
  DefaultISR,                                      // 192
  DefaultISR,                                      // 193
  DefaultISR,                                      // 194
  DefaultISR,                                      // 195
  DefaultISR,                                      // 196
  DefaultISR,                                      // 197
  DefaultISR,                                      // 198
  DefaultISR,                                      // 199
  DefaultISR,                                      // 200
  DefaultISR,                                      // 201
  DefaultISR,                                      // 202
  DefaultISR,                                      // 203
  DefaultISR,                                      // 204
  DefaultISR,                                      // 205
  DefaultISR,                                      // 206
  DefaultISR,                                      // 207
  DefaultISR,                                      // 208
  DefaultISR,                                      // 209
  DefaultISR,                                      // 210
  DefaultISR,                                      // 211
  DefaultISR,                                      // 212
  DefaultISR,                                      // 213
  DefaultISR,                                      // 214
  DefaultISR,                                      // 215
  DefaultISR,                                      // 216
  DefaultISR,                                      // 217
  DefaultISR,                                      // 218
  DefaultISR,                                      // 219
  DefaultISR,                                      // 220
  DefaultISR,                                      // 221
  DefaultISR,                                      // 222
  DefaultISR,                                      // 223
  DefaultISR,                                      // 224
  DefaultISR,                                      // 225
  DefaultISR,                                      // 226
  DefaultISR,                                      // 227
  DefaultISR,                                      // 228
  DefaultISR,                                      // 229
  DefaultISR,                                      // 230
  DefaultISR,                                      // 231
  DefaultISR,                                      // 232
  DefaultISR,                                      // 233
  DefaultISR,                                      // 234
  DefaultISR,                                      // 235
  DefaultISR,                                      // 236
  DefaultISR,                                      // 237
  DefaultISR,                                      // 238
  DefaultISR,                                      // 239
  DefaultISR,                                      // 240
  DefaultISR,                                      // 241
  DefaultISR,                                      // 242
  DefaultISR,                                      // 243
  DefaultISR,                                      // 244
  DefaultISR,                                      // 245
  DefaultISR,                                      // 246
  DefaultISR,                                      // 247
  DefaultISR,                                      // 248
  DefaultISR,                                      // 249
  DefaultISR,                                      // 250
  DefaultISR,                                      // 251
  DefaultISR,                                      // 252
  DefaultISR,                                      // 253
  DefaultISR                                       // 254
}};

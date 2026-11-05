//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddDma_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------

// EXAMPLE USAGE IN C FILE
//static uint32               u32__VinAdcValues[5];
//const  CddDma_ParameterType SysVolt_VinConfigParam = {  .pu32__SourceAddress = (uint32*) &(((CddAdc_Register_ADCAn_StructType*)  &ADCA0VCR00)->Reg_ADCAnDIR.ElementsArray[VCHAN_ADC0_010].Data),
//                                                       .pu32__TargetAddress = (uint32*) &u32__VinAdcValues[0U],
//                                                       .u16__Repetitions   =  5,
//                                                     };
//
//
//void SysVolt_VinAdc_Callback()
//{
//   CddDma_StartJob(SYSVOLT_ADC_VIN, &SysVolt_VinConfigParam, SysVolt_VinAdc_Callback);
//}
//
//



//=============================================================================
// help
//=============================================================================
// Structure is:
// a)  CDDDMA_CONFIG_MACRO__BEGIN
// b)     CDDDMA_CONIG_DMA_CHANNEL(<CHANNEL_NAME>, <DMA_IRQ_xyz>,   <DMA_TRIGGER_sourceXyz>, <DMA_ADDRESS_targetXyz>, <DMA_ADDRESS_xyz>, <DMA_TRANSFER_SIZE_xyz>)
// c) CDDDMA_CONFIG_MACRO__END
//
// a) Maco Begin
//    CDDDMA_CONFIG_MACRO__BEGIN
// b) Every DMA Channel can be assigned to be used for DMA Operations.
//    CDDDMA_CONIG_DMA_CHANNEL(<CHANNEL_NAME>, <DMA_IRQ_xyz>,   <DMA_TRIGGER_xyz>, <DMA_TRIGGER_sourceXyz>, <DMA_ADDRESS_targetXyz>, <DMA_TRANSFER_SIZE_xyz>)
//      <CHANNEL_NAME>          == Unique Name, defined by User                                                              <SYSVOLT_ADC_VIN/....>
//      <DMA_IRQ_xyz>           == DMA IRQ Output Channel         found in: CddDma_Types.h Enum => CddDma_InterruptRequestChannel_EnumType   <DMA_IRQ_INTDMA0/.../DMA_IRQ_INTDMA15>
//      <DMA_TRIGGER_xyz>       == HW Trigger                     found in: CddDma_Types.h Enum => CddDma_Trigger_EnumType                   <DMA_TRIGGER_HW_0_TO_7_NR00_INTTAUD0I0/.../DMA_TRIGGER_HW_8_TO_15_NR63_RESERVED_18>
//      <DMA_TRIGGER_sourceXyz> == Source Is Fixed or Incremented found in: CddDma_Types.h Enum => CddDma_AddressOperations_EnumType         <DMA_ADDRESS_INCREMENTED/DMA_ADDRESS_FIXED>
//      <DMA_ADDRESS_targetXyz> == Target Is Fixed or Incremented found in: CddDma_Types.h Enum => CddDma_AddressOperations_EnumType         <DMA_ADDRESS_INCREMENTED/DMA_ADDRESS_FIXED>
//      <DMA_TRANSFER_SIZE_xyz> == Used Transfer Size             found in: CddDma_Types.h Enum => CddDma_TransferSize_EnumType              <DMA_TRANSFER_SIZE_8/DMA_TRANSFER_SIZE_16/DMA_TRANSFER_SIZE_32>
//      <DMA_LOOP_MODE_xyz>     == DMA Automatic Restart          found in: CddDma_Types.h Enum => CddDma_LoopMode_EnumType                  <DMA_LOOP_MODE_NONE/DMA_LOOP_MODE_ENDLESS>
// c) Macro End
//    CDDDMA_CONFIG_MACRO__END


#ifdef CDDDMA_MAC_EXPAND
#include <CddDma_Mac.h>

CDDDMA_CONFIG_MACRO__BEGIN
/*CDDDMA_CONIG_DMA_CHANNEL(IO_HW_AB_DMA_LASER_SENS_ADC, CDDDMA0_IRQn,         CDDDMA_REQ_DISABLED,      DMA_ADDRESS_FIXED,          DMA_ADDRESS_INCREMENTED,    DMA_TRANSFER_SIZE_32b,    DMA_LOOP_MODE_ENDLESS)*/
CDDDMA_CONIG_DMA_CHANNEL(LPSPI0_TX,                     DMA_IRQ_INTDMA0,      CDDDMA_REQ_LPSPI0_TX,     DMA_ADDRESS_INCREMENTED,    DMA_ADDRESS_FIXED,          DMA_TRANSFER_SIZE_2x32,   DMA_LOOP_MODE_NONE)
CDDDMA_CONIG_DMA_CHANNEL(LPSPI0_RX,                     DMA_IRQ_INTDMA1,      CDDDMA_REQ_LPSPI0_RX,     DMA_ADDRESS_FIXED,          DMA_ADDRESS_INCREMENTED,    DMA_TRANSFER_SIZE_16,     DMA_LOOP_MODE_NONE)
CDDDMA_CONIG_DMA_CHANNEL(LPSPI1_TX,                     DMA_IRQ_INTDMA2,      CDDDMA_REQ_LPSPI1_TX,     DMA_ADDRESS_INCREMENTED,    DMA_ADDRESS_FIXED,          DMA_TRANSFER_SIZE_2x32,   DMA_LOOP_MODE_NONE)
CDDDMA_CONIG_DMA_CHANNEL(LPSPI1_RX,                     DMA_IRQ_INTDMA3,      CDDDMA_REQ_LPSPI1_RX,     DMA_ADDRESS_FIXED,          DMA_ADDRESS_INCREMENTED,    DMA_TRANSFER_SIZE_16,     DMA_LOOP_MODE_NONE)

CDDDMA_CONIG_DMA_CHANNEL(SYS_CRC,                       DMA_IRQ_INTDMA4,      CDDDMA_REQ_DISABLED,      DMA_ADDRESS_INCREMENTED,    DMA_ADDRESS_FIXED,          DMA_TRANSFER_SIZE_8,      DMA_LOOP_MODE_ENDLESS) //to modify size
CDDDMA_CONIG_DMA_CHANNEL(CDDUART_DMA_TX_CHANNEL,        DMA_IRQ_INTDMA5,      CDDDMA_REQ_LPUART1_TX,    DMA_ADDRESS_INCREMENTED,    DMA_ADDRESS_FIXED,          DMA_TRANSFER_SIZE_8,      DMA_LOOP_MODE_NONE)
CDDDMA_CONIG_DMA_CHANNEL(ADC_ADC0_DMA_CONV_CH,          DMA_IRQ_INTDMA6,      CDDDMA_REQ_ADC0,          DMA_ADDRESS_INCREMENTED,    DMA_ADDRESS_INCREMENTED,    DMA_TRANSFER_SIZE_32,     DMA_LOOP_MODE_ENDLESS)
CDDDMA_CONIG_DMA_CHANNEL(ADC_ADC1_DMA_CONV_CH,          DMA_IRQ_INTDMA7,      CDDDMA_REQ_ADC1,          DMA_ADDRESS_INCREMENTED,    DMA_ADDRESS_INCREMENTED,    DMA_TRANSFER_SIZE_32,     DMA_LOOP_MODE_ENDLESS)
/*ALWAYS LET DMA_RX_CHANNEL THE LAST - NEEDS HIGH PRIORITY*/
CDDDMA_CONIG_DMA_CHANNEL(CDDUART_DMA_RX_CHANNEL,        DMA_IRQ_INTDMA8,      CDDDMA_REQ_LPUART1_RX,    DMA_ADDRESS_FIXED,          DMA_ADDRESS_INCREMENTED,    DMA_TRANSFER_SIZE_8,      DMA_LOOP_MODE_NONE)

// DMA CHANEL 15 reserved for corTst
#ifdef UNIT_TEST
CDDDMA_CONIG_DMA_CHANNEL(UNIT_TEST_CHANNEL, CDDDMA_NotAvail_IRQn, CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1, DMA_ADDRESS_FIXED, DMA_ADDRESS_FIXED, DMA_TRANSFER_SIZE_2x32, DMA_LOOP_MODE_ENDLESS)
#endif 

CDDDMA_CONFIG_MACRO__END
#endif
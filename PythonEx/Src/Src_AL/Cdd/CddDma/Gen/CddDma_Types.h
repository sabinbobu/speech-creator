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
/// \file  CddDma_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_DMA_TYPES_2020_11_27_H_
#define CDD_DMA_TYPES_2020_11_27_H_

#include <CddDma.h>

#ifndef UNIT_TEST
#include <CddDma_S32K_14X.h>
#else
#include "CddDma_S32K_14X_Types.h"
#endif



#define CDDDMA_DMA_TRIGGER_UNIT_SIZE  36U

#define CDDDMA_REGISTER_U32_DOWNCAST     (uint32)
#define CDDDMA_REGISTER_U16_DOWNCAST     (uint16)
#define CDDDMA_REGISTER_U8_DOWNCAST      (uint8)


#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA0  DMA0_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA1  DMA1_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA2  DMA2_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA3  DMA3_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA4  DMA4_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA5  DMA5_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA6  DMA6_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA7  DMA7_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA8  DMA8_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA9  DMA9_IRQHandler 
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA10 DMA10_IRQHandler
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA11 DMA11_IRQHandler
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA12 DMA12_IRQHandler
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA13 DMA13_IRQHandler
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA14 DMA14_IRQHandler
#define CDDDMA_TRIGGER_DMA_IRQ_INTDMA15 DMA15_IRQHandler


typedef enum  teCddDma_AddressOperations
{
  DMA_ADDRESS_INCREMENTED = 0U,
  DMA_ADDRESS_FIXED = 1U
} teCddDma_AddressOperations;


typedef enum  teCddDma_TransferSize
{
  DMA_TRANSFER_SIZE_8 = 0U,
  DMA_TRANSFER_SIZE_16 = 1U,
  DMA_TRANSFER_SIZE_32 = 2U,
  DMA_TRANSFER_SIZE_2x32 = 3U
} teCddDma_TransferSize;

typedef enum teCddDma_Source_Trigger
{
  CDDDMA_REQ_DISABLED = 0U,
  CDDDMA_REQ_LPUART0_RX = 2U,
  CDDDMA_REQ_LPUART0_TX = 3U,
  CDDDMA_REQ_LPUART1_RX = 4U,
  CDDDMA_REQ_LPUART1_TX = 5U,
  CDDDMA_REQ_LPUART2_RX = 6U,
  CDDDMA_REQ_LPUART2_TX = 7U,
  CDDDMA_REQ_FLEXIO_SHIFTER0 = 10U,
  CDDDMA_REQ_FLEXIO_SHIFTER1 = 11U,
  CDDDMA_REQ_FLEXIO_SHIFTER2 = 12U,
  CDDDMA_REQ_FLEXIO_SHIFTER3 = 13U,
  CDDDMA_REQ_LPSPI0_RX = 14U,
  CDDDMA_REQ_LPSPI0_TX = 15U,
  CDDDMA_REQ_LPSPI1_RX = 16U,
  CDDDMA_REQ_LPSPI1_TX = 17U,
  CDDDMA_REQ_LPSPI2_RX = 18U,
  CDDDMA_REQ_LPSPI2_TX = 19U,
  CDDDMA_REQ_FTM1_CHANNEL_0 = 20U,
  CDDDMA_REQ_FTM1_CHANNEL_1 = 21U,
  CDDDMA_REQ_FTM1_CHANNEL_2 = 22U,
  CDDDMA_REQ_FTM1_CHANNEL_3 = 23U,
  CDDDMA_REQ_FTM1_CHANNEL_4 = 24U,
  CDDDMA_REQ_FTM1_CHANNEL_5 = 25U,
  CDDDMA_REQ_FTM1_CHANNEL_6 = 26U,
  CDDDMA_REQ_FTM1_CHANNEL_7 = 27U,
  CDDDMA_REQ_FTM2_CHANNEL_0 = 28U,
  CDDDMA_REQ_FTM2_CHANNEL_1 = 29U,
  CDDDMA_REQ_FTM2_CHANNEL_2 = 30U,
  CDDDMA_REQ_FTM2_CHANNEL_3 = 31U,
  CDDDMA_REQ_FTM2_CHANNEL_4 = 32U,
  CDDDMA_REQ_FTM2_CHANNEL_5 = 33U,
  CDDDMA_REQ_FTM2_CHANNEL_6 = 34U,
  CDDDMA_REQ_FTM2_CHANNEL_7 = 35U,
  CDDDMA_REQ_FTM0_OR_CH0_CH7 = 36U,
  CDDDMA_REQ_FTM3_OR_CH0_CH7 = 37U,
  CDDDMA_REQ_FTM4_OR_CH0_CH7 = 38U,
  CDDDMA_REQ_FTM5_OR_CH0_CH7 = 39U,
  CDDDMA_REQ_ADC0 = 42U,
  CDDDMA_REQ_ADC1 = 43U,
  CDDDMA_REQ_LPI2C0_RX = 44U,
  CDDDMA_REQ_LPI2C0_TX = 45U,
  CDDDMA_REQ_PDB0 = 46U,
  CDDDMA_REQ_PDB1 = 47U,
  CDDDMA_REQ_CMP0 = 48U,
  CDDDMA_REQ_PORTA = 49U,
  CDDDMA_REQ_PORTB = 50U,
  CDDDMA_REQ_PORTC = 51U,
  CDDDMA_REQ_PORTD = 52U,
  CDDDMA_REQ_PORTE = 53U,
  CDDDMA_REQ_FLEXCAN0 = 54U,
  CDDDMA_REQ_FLEXCAN1 = 55U,
  CDDDMA_REQ_FLEXCAN2 = 56U,
  CDDDMA_REQ_LPTMR0 = 59U,
  CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED0 = 62U,
  CDDDMA_REQ_DMAMUX_ALWAYS_ENABLED1 = 63U
} teCddDma_Source_Trigger;

typedef enum teCddDma_LoopMode
{
  DMA_LOOP_MODE_NONE = 0U,
  DMA_LOOP_MODE_ENDLESS = 1U
} teCddDma_LoopMode;

typedef enum teCddDma_InterruptRequestChannel
{
  /* Auxiliary constants */
  CDDDMA_NotAvail_IRQn = -128,             /**< Not available device specific interrupt */
  /* Device specific interrupts */
  DMA_IRQ_INTDMA0 = 0u,               /**< DMA channel 0 transfer complete */
  DMA_IRQ_INTDMA1 = 1u,               /**< DMA channel 1 transfer complete */
  DMA_IRQ_INTDMA2 = 2u,               /**< DMA channel 2 transfer complete */
  DMA_IRQ_INTDMA3 = 3u,               /**< DMA channel 3 transfer complete */
  DMA_IRQ_INTDMA4 = 4u,               /**< DMA channel 4 transfer complete */
  DMA_IRQ_INTDMA5 = 5u,               /**< DMA channel 5 transfer complete */
  DMA_IRQ_INTDMA6 = 6u,               /**< DMA channel 6 transfer complete */
  DMA_IRQ_INTDMA7 = 7u,               /**< DMA channel 7 transfer complete */
  DMA_IRQ_INTDMA8 = 8u,               /**< DMA channel 8 transfer complete */
  DMA_IRQ_INTDMA9 = 9u,               /**< DMA channel 9 transfer complete */
  DMA_IRQ_INTDMA10 = 10u,              /**< DMA channel 10 transfer complete */
  DMA_IRQ_INTDMA11 = 11u,              /**< DMA channel 11 transfer complete */
  DMA_IRQ_INTDMA12 = 12u,              /**< DMA channel 12 transfer complete */
  DMA_IRQ_INTDMA13 = 13u,              /**< DMA channel 13 transfer complete */
  DMA_IRQ_INTDMA14 = 14u,              /**< DMA channel 14 transfer complete */
  DMA_IRQ_INTDMA15 = 15u,              /**< DMA channel 15 transfer complete */
  CDDDMA_Error_IRQn = 16u           /**< DMA error interrupt channels 0-15 */
} teCddDma_InterruptRequestChannel;

typedef enum teCddDma_Arbitration_Algorithm {
  CDDDMA_ARBITRATION_FIXED_PRIORITY = 0U,  /*!< Fixed Priority */
  CDDDMA_ARBITRATION_ROUND_ROBIN           /*!< Round-Robin arbitration */
} teCddDma_Arbitration_Algorithm;

#endif // CDD_DMA_TYPES_2020_11_27_H_
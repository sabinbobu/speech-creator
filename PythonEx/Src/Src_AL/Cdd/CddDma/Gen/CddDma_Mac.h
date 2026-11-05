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
/// \file  CddDma_Mac.h
///
/// \brief
///
//-----------------------------------------------------------------------------
/*
    MACRO EXTENSIONS
*/

// FOR DMA0
#if defined(CDDDMA_MAC_STEP1_CREATE_ENUM_DYNCONFIG_VIRTUAL_DMA_NAMES)
#include "CddDma_Mac_Prep.h"
#define CDDDMA_CONFIG_MACRO__BEGIN                                                                                                                     typedef enum CddDma_DynConfig_DmaChannelName_EnumType{
#define CDDDMA_CONIG_DMA_CHANNEL(virtualDmaName, irqChannel, trigger, sourceAddressOperation, targetAddressOperation, transferSize, loopMode)              virtualDmaName,
#define CDDDMA_CONFIG_MACRO__END                                                                                                                       VIRTUAL_TRIGGER_NAMES_COUNT}CddDma_DynConfig_DmaChannelName_EnumType;
#elif defined(CDDDMA_MAC_STEP2_CREATE_CONST_ARRAY)
#include "CddDma_Mac_Prep.h"
#define CDDDMA_CONFIG_MACRO__BEGIN                             STATIC_AL tsCddDmaConfig const CddDma_cast__DynConfig_Triggers[VIRTUAL_TRIGGER_NAMES_COUNT+1] = {
#define CDDDMA_CONIG_DMA_CHANNEL(virtualDmaName, irqChannel, trigger, sourceAddressOperation, targetAddressOperation, transferSize, loopMode)     { .eDmaSourceTriggerName = trigger, .eDmaIrqNumber     = irqChannel, .eTransferSize     = transferSize,  .eSourceIncrement  = sourceAddressOperation, .eTargetIncrement  = targetAddressOperation, .eLoopMode=loopMode  },
#define CDDDMA_CONFIG_MACRO__END                                                                                                                  { .eDmaSourceTriggerName = CDDDMA_REQ_DISABLED, .eDmaIrqNumber     = CDDDMA_NotAvail_IRQn, .eLoopMode=DMA_LOOP_MODE_NONE, .eTransferSize     = DMA_TRANSFER_SIZE_8,  .eSourceIncrement  = DMA_ADDRESS_INCREMENTED, .eTargetIncrement  = DMA_ADDRESS_INCREMENTED  }};
#elif defined(CDDDMA_MAC_STEP3_CREATE_INTERRUPT_DEFINES)
#include "CddDma_Mac_Prep.h"
#define CDDDMA_CONFIG_MACRO__BEGIN                                                                                                                    
#define CDDDMA_CONIG_DMA_CHANNEL(virtualDmaName, irqChannel, trigger, sourceAddressOperation, targetAddressOperation, transferSize, loopMode)               void CDDDMA_TRIGGER_##irqChannel(void) { afpDmaCallbacks[virtualDmaName](); }
#define CDDDMA_CONFIG_MACRO__END                                                                                                                      
#else
#error CDDDMA_MAC_xyz undefined!
#endif
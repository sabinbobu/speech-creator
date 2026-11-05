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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

// Headers of the Module
#include <CddDma_Types.h>
#include <CddDma.h>
#include <CddDma_Cfg.h>
#include <CddDma_S32K_14X.h>

//=============================================================================
// Typedefs
//=============================================================================
typedef struct tsCddDmaConfig
{
  teCddDma_Source_Trigger                     eDmaSourceTriggerName;
  teCddDma_InterruptRequestChannel            eDmaIrqNumber;
  teCddDma_TransferSize                       eTransferSize;
  teCddDma_AddressOperations                  eSourceIncrement;
  teCddDma_AddressOperations                  eTargetIncrement;
  teCddDma_LoopMode                           eLoopMode;
} tsCddDmaConfig;

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern volatile  tsCddDma_S32K_146_Registers*          CddDma_psRegister;
extern volatile tsCddDmaMux_S32K_146_Register*         CddDma_DmaMux_psRegister;

extern tsCddDmaConfig CONST_AL CddDma_cast__DynConfig_Triggers[VIRTUAL_TRIGGER_NAMES_COUNT + 1];

extern CddDma_tfpCallback      afpDmaCallbacks[(uint8)VIRTUAL_TRIGGER_NAMES_COUNT + 1U];


//=============================================================================
// Module function declarations
//=============================================================================

//=============================================================================
// Module function parameter stubs
//=============================================================================

boolean                                   CddDma_IsJobCompleted_eDmaChannelName;
CddDma_DynConfig_DmaChannelName_EnumType  CddDma_GenerateTriggerSignal_eDmaChannelName;
CddDma_DynConfig_DmaChannelName_EnumType  CddDma_EnableHwTrigger_eDmaChannelName;
uint8                                     CddDma_EnableHwTrigger_boEnabled;
CddDma_DynConfig_DmaChannelName_EnumType  CddDma_StartJob_ForInterrupt_eDmaChannelName;
CONST_AL tsCddDma_Parameter               CddDma_StartJob_ForInterrupt_psParameter;
CddDma_DynConfig_DmaChannelName_EnumType  CddDma_StartJob_eDmaChannelName;
CONST_AL tsCddDma_Parameter               CddDma_StartJob_psParameter;
CddDma_tfpCallback                        CddDma_StartJob_fpCallback;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean CddDma_IsJobCompleted_boRetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================


//=============================================================================
// Test variable stubs
//=============================================================================
tsCddDma_S32K_146_Registers       Mt_CddDma_Dma_Register;
tsCddDmaMux_S32K_146_Register     Mt_CddDma_DmaMux_Register;

//global variables needed to test the transfer type (HW, SW) in CddDma_StartJob and CddDma_StartJob_ForInterrupt
tsCddDma_Parameter Mt_CddDma_CDDDMA_CHECK_ADDRESS_False = { .pulSourceAddress = (uint32*)0x00050000U,    //exceeds ROM margins
                                                            .pulTargetAddress = (uint32*)0x2000FEEEU,    //exceeds RAM margins
                                                            .unRepetitions    = 8U,
};


tsCddDma_Parameter Mt_CddDma_CDDDMA_CHECK_ADDRESS_True = {  .pulSourceAddress = (uint32*)0x00000550U,    //ROM address
                                                            .pulTargetAddress = (uint32*)0x20001000U,    //RAM address
                                                            .unRepetitions    = 16U,
};


#endif // TEST_2023_08_25_H_

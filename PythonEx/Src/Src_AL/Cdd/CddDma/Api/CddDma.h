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
/// \file  CddDma.h
///
/// \brief
///
//-----------------------------------------------------------------------------

#ifndef UNIT_TEST
#include <CddDma_S32K_14X.h>
#else
#include <CddDma_PC_WIN32API.h>
#endif


#ifndef CDD_DMA_2020_11_27_H_
#define CDD_DMA_2020_11_27_H_

#include <AL_Helper.h>

#define CDDDMA_MAC_EXPAND

#define  CDDDMA_MAC_STEP1_CREATE_ENUM_DYNCONFIG_VIRTUAL_DMA_NAMES
#include <CddDma_Cfg.h>
#undef   CDDDMA_MAC_STEP1_CREATE_ENUM_DYNCONFIG_VIRTUAL_DMA_NAMES

#undef CDDDMA_MAC_EXPAND

//TODO: move on low layer part
#define RAM_START 0x1fff0000U
#define RAM_END   0x2000EFFFU
#define ROM_START 0x00000510U
#define ROM_END   0x000FFFFFU

#define CDDDMA_CHECK_ADDRESS(address) (((uint32)address > ROM_START && (uint32)address < ROM_END) || ((uint32)address > RAM_START && (uint32)address < RAM_END))


// Callback function:  void xxx_MyCallback(void); CddDma_StartJob(chanName, &pst__Parameter, xxx_MyCallback);
typedef void(*CddDma_tfpCallback)(void);  // callback function for data reception

// DMA Job Parameter Definition
typedef struct tsCddDma_Parameter
{
  volatile uint32*                                      pulSourceAddress;
  volatile uint32*                                      pulTargetAddress;
  uint16                                       unRepetitions;
} tsCddDma_Parameter;


//============================================================================
// Function defines
//============================================================================
boolean CddDma_IsJobCompleted(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName);
void    CddDma_GenerateTriggerSignal(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName);
void    CddDma_StartJob(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter, CONST_AL CddDma_tfpCallback fpCallback);
void    CddDma_StartJob_ForInterrupt(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, CONST_AL tsCddDma_Parameter* psParameter);
void    CddDma_EnableHwTrigger(CddDma_DynConfig_DmaChannelName_EnumType eDmaChannelName, boolean boEnabled);
void    CddDma_Init(void);

#endif // CDD_DMA_2020_11_27_H_
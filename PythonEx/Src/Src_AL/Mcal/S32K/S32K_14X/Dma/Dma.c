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
/// \file  Dma.cpp
///
/// \brief  
///
/// \descr  
///
/// \author Mertic Alexandru (F98665C)
///         mailTo:alexandru-laurentiu.mertic(at)marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Mcal/Dma/Dma.h>
#include <Cfg/Cfg.h>
#include <stddef.h>
#include <string.h>
#include <UtilUtility.h>
#include <edma_driver.h>

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif


//=============================================================================
// Private macros
//=============================================================================

//=============================================================================
// Public variables definitions
//=============================================================================
extern uint8 ApplCmd_HWVariant;

//=============================================================================
// Private variables definitions
//=============================================================================


//=============================================================================
// Public functions definitions
//=============================================================================
//-----------------------------------------------------------------------------
// \brief   spi_init
//
// \descr   Initialized Spi peripheral
//
// \param   void
//
// \return  -
//-----------------------------------------------------------------------------
void Dma_Init(const Dma_ConfigType* ConfigPtr)
{
  EDMA_DRV_Init((edma_state_t*)ConfigPtr->Dma_Cfg_atyCharacteristics[0].controler_state, 
    (const edma_user_config_t*)ConfigPtr->Dma_Cfg_atyCharacteristics[0].init_config, 
    (edma_chn_state_t* const*)ConfigPtr->Dma_Cfg_atyCharacteristics[0].chn_state_array, 
    (const edma_channel_config_t* const*)ConfigPtr->Dma_Cfg_atyCharacteristics[0].config_array, 
    (uint32)ConfigPtr->Dma_Cfg_atyCharacteristics[0].channels_count);
}


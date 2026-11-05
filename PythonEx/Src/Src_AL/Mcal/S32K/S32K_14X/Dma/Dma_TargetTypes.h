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
/// \file  Dma_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef DMA_CFG_2020_11_09_H_
  #define DMA_CFG_2020_11_09_H_

  #include <Std_Types.h>
 
  
  typedef struct DmaSpecificCharacteristicsType
  {
    void* controler_state;
    void* init_config;
    void* chn_state_array;
    void* config_array;
    uint8 channels_count;
  } DmaSpecificCharacteristicsType;

  typedef struct Dma_SpecificType
  {
    uint8 ucCountOfSpiInstances;
    const DmaSpecificCharacteristicsType* Dma_Cfg_atyCharacteristics;
  } Dma_SpecificType;


#endif // DMA_CFG_2020_11_09_H_

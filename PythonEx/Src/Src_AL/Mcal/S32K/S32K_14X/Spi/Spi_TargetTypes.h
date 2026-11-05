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
/// \file  Spi_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SPI_CFG_2020_11_07_H_
  #define SPI_CFG_2020_11_07_H_

  #include <Std_Types.h>
  #include <Cfg/Cfg.h>
 
  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  #define NUMBER_OF_FRAMES 32U
  #define SPI_SBC_WRITE_FRAME(addr, regval)       ((uint16)((uint16)(regval) << 8U) | (uint16)((uint16)1U << 7U) | (uint16)(addr))
  #define SPI_STEP_WRITE_FRAME(addr, regval)      ((uint16)((uint16)(addr) << 9U) | (uint16)(regval))

  #define SPI_BUCK_1_14_READ_FRAME(addr)          ((uint16)(addr) << 9U) 
  #define SPI_BUCK_1_14_WRITE_FRAME(addr, regval) (((uint16)((uint16)(addr) << 9U) | (uint16)(regval)) | (uint16)((uint16)1U << 15U))

  typedef enum 
  {
    e_active_config_SBC,
    e_active_config_BOOST,
#ifdef SAMPLE_FULL
    e_active_config_STEPPER,
#endif
    e_active_config_BUCK,
    e_total_number_of_spi_instances
  } te_active_configuration;

  typedef struct
  {
    uint8 spi_instance;
    te_active_configuration config;
    const void* spi_state;
    const void* Spi_Cfg_atyCharacteristics;
  } spi_config_map_t;

  typedef struct Spi_SpecificType
  {
    uint8 ucCountOfSpiInstances;
    spi_config_map_t* spi_map;
  } Spi_SpecificType;

  #if defined(__cplusplus)
  }
  #endif

#endif // SPI_CFG_2020_11_07_H_

#ifndef SPI_2020_06_11_H_
  #define SPI_2020_06_11_H_

  #include <Std_Types.h>
  #include <Spi_Cfg.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef Spi_SpecificType Spi_ConfigType;

  extern const Spi_SpecificType Spi_Config;

  void Spi_Init(const Spi_ConfigType* ConfigPtr);
  uint8 Spi_Transmit(te_active_configuration active_config, uint16 *tx_buf, uint16 * const rx_buf, uint32 size);
  void spi_set_parity_bit(uint16 *u16_frame_data, uint8 u8_parity_bit_position);

  #if defined(__cplusplus)
  }
  #endif

#endif // SPI_2020_06_11_H_

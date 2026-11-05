#ifndef CDD_SPI_TYPES_2020_11_24_H_
#define CDD_SPI_TYPES_2020_11_24_H_

#include <Std_Types.h>

//Interface enum
#define CDDSPI_MAC_DECL_IFC_ENUM
#include <CddSpi_Cfg.h>
#undef  CDDSPI_MAC_DECL_IFC_ENUM
//Device frames enum
#define CDDSPI_MAC_DECL_DEVFRM_ENUM
#include <CddSpi_Cfg.h>
#undef CDDSPI_MAC_DECL_DEVFRM_ENUM

typedef struct tsCddSpiDevCfg
{
  uint8 ucSpiIfc;      //Spi interface that the device is attached to
  uint8 ucCs;          //Chipselect number
  uint8 ucDataLen;     //Data Lenght
  uint8 ucMaxElements; //Max number of device elements
  uint8 ucElements;    //Actual number of device elements
  uint8 ucBrs;         //Bit rate 
  uint8 ucCPol;        //Clock Polarity
  uint8 ucCPha;        //Clock Phae
  uint8 ucDataDir;     //Data direction: MSB or LSB
}tsCddSpiDevCfg;

typedef struct tsCddSpiTransferData
{
  uint32 ulTCR_data;
  uint32 ulTDR_data;
} tsCddSpiTransferData;

#endif // CDD_SPI_TYPES_2020_11_24_H_

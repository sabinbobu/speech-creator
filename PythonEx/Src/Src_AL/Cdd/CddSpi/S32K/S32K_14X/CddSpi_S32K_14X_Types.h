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
/// \file  CddSpi_S32K14X_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_SPI_S32K14X_TYPES_2020_11_24_H_
#define CDD_SPI_S32K14X_TYPES_2020_11_24_H_

#include <Std_Types.h>

//Version ID Register
typedef struct tsCddSpi_S32K146_VERID
{
  uint32 u16FEATURE : 16;
  uint32 u8MINOR    : 8;
  uint32 u8MAJOR    : 8;
} tsCddSpi_S32K146_VERID;

typedef union tuCddSpi_S32K146_VERID
{
  tsCddSpi_S32K146_VERID sBit;
  uint32                 ulData;
  uint16                 aunData[2];
  uint8                  aucData[4];
} tuCddSpi_S32K146_VERID;

//Parameter Register
typedef struct tsCddSpi_S32K146_PARAM
{

  uint32 u8TXFIFO : 8;
  uint32 u8RXFIFO : 8;
  uint32          : 16;
} tsCddSpi_S32K146_PARAM;

typedef union tuCddSpi_S32K146_PARAM
{
  tsCddSpi_S32K146_PARAM sBit;
  uint32                 ulData;
  uint16                 aunData[2];
  uint8                  aucData[4];
} tuCddSpi_S32K146_PARAM;

//Control Register
typedef struct tsCddSpi_S32K146_CR
{
  uint32 u1MEN   : 1;
  uint32 u1RST   : 1;
  uint32 u1DOZEN : 1;
  uint32 u1DBGEN : 1;
  uint32         : 4;
  uint32 u1RTF   : 1;
  uint32 u1RRF   : 1;
  uint32         : 22;
} tsCddSpi_S32K146_CR;

typedef union tuCddSpi_S32K146_CR
{
  tsCddSpi_S32K146_CR sBit;
  uint32              ulData;
  uint16              aunData[2];
  uint8               aucData[4];
} tuCddSpi_S32K146_CR;

//Status Register
typedef struct tsCddSpi_S32K146_SR
{
  uint32 u1TDF : 1;
  uint32 u1RDF : 1;
  uint32       : 6;
  uint32 u1WCF : 1;
  uint32 u1FCF : 1;
  uint32 u1TCF : 1;
  uint32 u1TEF : 1;
  uint32 u1REF : 1;
  uint32 u1DMF : 1;
  uint32       : 10;
  uint32 u1MBF : 1;
  uint32       : 7;
} tsCddSpi_S32K146_SR;

typedef union tuCddSpi_S32K146_SR
{
  tsCddSpi_S32K146_SR sBit;
  uint32              ulData;
  uint16              aunData[2];
  uint8               aucData[4];
} tuCddSpi_S32K146_SR;

//Interrupt Enable Register
typedef struct tsCddSpi_S32K146_IER
{
  uint32 u1TDIE : 1;
  uint32 u1RDIE : 1;
  uint32        : 6;
  uint32 u1WCIE : 1;
  uint32 u1FCIE : 1;
  uint32 u1TCIE : 1;
  uint32 u1TEIE : 1;
  uint32 u1REIE : 1;
  uint32 u1DMIE : 1;
  uint32        : 18;
} tsCddSpi_S32K146_IER;

typedef union tuCddSpi_S32K146_IER
{
  tsCddSpi_S32K146_IER sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_IER;

//DMA Enable Register
typedef struct tsCddSpi_S32K146_DER
{
  uint32 u1TDDE : 1;
  uint32 u1RDDE : 1;
  uint32        : 30;
} tsCddSpi_S32K146_DER;

typedef union tuCddSpi_S32K146_DER
{
  tsCddSpi_S32K146_DER sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_DER;

//Configuration Register Register 0
typedef struct tsCddSpi_S32K146_CFGR0
{
  uint32 u1HREN    : 1;
  uint32 u1HRPOL   : 1;
  uint32 u1HRSEL   : 1;
  uint32           : 5;
  uint32 u1CIRFIFO : 1;
  uint32 u1RDMO    : 1;
  uint32           : 22;
} tsCddSpi_S32K146_CFGR0;

typedef union tuCddSpi_S32K146_CFGR0
{
  tsCddSpi_S32K146_CFGR0 sBit;
  uint32                 ulData;
  uint16                 aunData[2];
  uint8                  aucData[4];
} tuCddSpi_S32K146_CFGR0;

//Configuration Register Register 1
typedef struct tsCddSpi_S32K146_CFGR1
{
  uint32 u1MASTER  : 1;
  uint32 u1SAMPLE  : 1;
  uint32 u1AUTOPCS : 1;
  uint32 u1NOSTALL : 1;
  uint32           : 4;
  uint32 u4PCSPOL  : 4;
  uint32           : 4;
  uint32 u3MATCFG  : 3;
  uint32           : 5;
  uint32 u2PINCFG  : 2;
  uint32 u1OUTCFG  : 1;
  uint32 u1PCSCFG  : 1;
  uint32           : 4;
} tsCddSpi_S32K146_CFGR1;

typedef union tuCddSpi_S32K146_CFGR1
{
  tsCddSpi_S32K146_CFGR1 sBit;
  uint32                 ulData;
  uint16                 aunData[2];
  uint8                  aucData[4];
} tuCddSpi_S32K146_CFGR1;

//Data Match Register 0
typedef struct tsCddSpi_S32K146_DMR0
{
  uint32 u32MATCH0 : 32;
} tsCddSpi_S32K146_DMR0;

typedef union tuCddSpi_S32K146_DMR0
{
  tsCddSpi_S32K146_DMR0 sBit;
  uint32                 ulData;
  uint16                 aunData[2];
  uint8                  aucData[4];
} tuCddSpi_S32K146_DMR0;

//Data Match Register 1
typedef struct tsCddSpi_S32K146_DMR1
{
  uint32 u32MATCH1 : 32;
} tsCddSpi_S32K146_DMR1;

typedef union tuCddSpi_S32K146_DMR1
{
  tsCddSpi_S32K146_DMR1 sBit;
  uint32                 ulData;
  uint16                 aunData[2];
  uint8                  aucData[4];
} tuCddSpi_S32K146_DMR1;

//Clock Configuration Register
typedef struct tsCddSpi_S32K146_CCR
{
  uint32 u8SCKDIV : 8;
  uint32 u8DBT    : 8;
  uint32 u8PCSSCK : 8;
  uint32 u8SCKPCS : 8;
} tsCddSpi_S32K146_CCR;

typedef union tuCddSpi_S32K146_CCR
{
  tsCddSpi_S32K146_CCR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_CCR;

//FIFO Control Register
typedef struct tsCddSpi_S32K146_FCR
{
  uint32 u2TXWATER : 2;
  uint32           : 14;
  uint32 u2RXWATER : 2;
  uint32           : 14;
} tsCddSpi_S32K146_FCR;

typedef union tuCddSpi_S32K146_FCR
{
  tsCddSpi_S32K146_FCR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_FCR;

//FIFO Status Register
typedef struct tsCddSpi_S32K146_FSR
{
  uint32 u3TXCOUNT : 3;
  uint32           : 13;
  uint32 u3RXCOUNT : 3;
  uint32           : 13;
} tsCddSpi_S32K146_FSR;

typedef union tuCddSpi_S32K146_FSR
{
  tsCddSpi_S32K146_FSR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_FSR;

//Transmit Command Register
typedef struct tsCddSpi_S32K146_TCR
{
  uint32 u12FRAMESZ : 12;
  uint32            : 4;
  uint32 u2WIDTH    : 2;
  uint32 u1TXMSK    : 1;
  uint32 u1RXMSK    : 1;
  uint32 u1CONTC    : 1;
  uint32 u1CONT     : 1;
  uint32 u1BYSW     : 1;
  uint32 u1LSBF     : 1;
  uint32 u2PCS      : 2;
  uint32            : 1;
  uint32 u3PRESCALE : 3;
  uint32 u1CPHA     : 1;
  uint32 u1CPOL     : 1;
} tsCddSpi_S32K146_TCR;

typedef union tuCddSpi_S32K146_TCR
{
  tsCddSpi_S32K146_TCR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_TCR;

//Transmit Data Register
typedef struct tsCddSpi_S32K146_TDR
{
  uint32 u32DATA : 32;
} tsCddSpi_S32K146_TDR;

typedef union tuCddSpi_S32K146_TDR
{
  tsCddSpi_S32K146_TDR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_TDR;

//Receive Status Register
typedef struct tsCddSpi_S32K146_RSR
{
  uint32 u1SOF     : 1;
  uint32 u1RXEMPTY : 1;
  uint32           : 30;
} tsCddSpi_S32K146_RSR;

typedef union tuCddSpi_S32K146_RSR
{
  tsCddSpi_S32K146_RSR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_RSR;

//Receive Data Register
typedef struct tsCddSpi_S32K146_RDR
{
  uint32 u32DATA : 32;
} tsCddSpi_S32K146_RDR;

typedef union tuCddSpi_S32K146_RDR
{
  tsCddSpi_S32K146_RDR sBit;
  uint32               ulData;
  uint16               aunData[2];
  uint8                aucData[4];
} tuCddSpi_S32K146_RDR;

typedef struct tsCddSpi_S32K146_PERI
{
  tuCddSpi_S32K146_VERID unVERID;                  /**< Version ID Register, offset: 0x0 */
  tuCddSpi_S32K146_PARAM unPARAM;                  /**< Parameter Register, offset: 0x4 */
  uint8                  aulReserved1[8];
  tuCddSpi_S32K146_CR    unCR;                     /**< Control Register, offset: 0x10 */
  tuCddSpi_S32K146_SR    unSR;                     /**< Status Register, offset: 0x14 */
  tuCddSpi_S32K146_IER   unIER;                    /**< Interrupt Enable Register, offset: 0x18 */
  tuCddSpi_S32K146_DER   unDER;                    /**< DMA Enable Register, offset: 0x1C */
  tuCddSpi_S32K146_CFGR0 unCFGR0;                  /**< Configuration Register 0, offset: 0x20 */
  tuCddSpi_S32K146_CFGR1 unCFGR1;                  /**< Configuration Register 1, offset: 0x24 */
  uint8                  aulReserved2[8];
  tuCddSpi_S32K146_DMR0  unDMR0;                   /**< Data Match Register 0, offset: 0x30 */
  tuCddSpi_S32K146_DMR1  unDMR1;                   /**< Data Match Register 1, offset: 0x34 */
  uint8                 aulReserved3[8];
  tuCddSpi_S32K146_CCR   unCCR;                    /**< Clock Configuration Register, offset: 0x40 */
  uint8                  aulReserved4[20];
  tuCddSpi_S32K146_FCR   unFCR;                    /**< FIFO Control Register, offset: 0x58 */
  tuCddSpi_S32K146_FSR   unFSR;                    /**< FIFO Status Register, offset: 0x5C */
  tuCddSpi_S32K146_TCR   unTCR;                    /**< Transmit Command Register, offset: 0x60 */
  tuCddSpi_S32K146_TDR   unTDR;                    /**< Transmit Data Register, offset: 0x64 */
  uint8                  aulReserved5[8];
  tuCddSpi_S32K146_RSR   unRSR;                    /**< Receive Status Register, offset: 0x70 */
  tuCddSpi_S32K146_RDR   unRDR;                    /**< Receive Data Register, offset: 0x74 */
} tsCddSpi_S32K146_PERI;


#endif // CDD_SPI_S32K14X_TYPES_2020_11_24_H_

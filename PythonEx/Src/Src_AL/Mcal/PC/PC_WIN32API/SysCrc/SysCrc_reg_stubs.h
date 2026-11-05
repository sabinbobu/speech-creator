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
/// \file  SysCrc_reg_stubs.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_CRC_REG_STUBS_2021_11_18_H_
#define SYS_CRC_REG_STUBS_2021_11_18_H_

//=============================================================================
// Includes
//=============================================================================
 #include <Std_Types.h>
#include <Device_TargetTypes.h>


//=============================================================================
// Exported Macros
//=============================================================================


#define __IO  volatile
#define bool  _Bool
#define false 0
#define true  1


//=============================================================================
// Exported Types
//=============================================================================


/** CRC - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    __IO uint32 DATA;                              /**< CRC Data register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint16 L;                                 /**< CRC_DATAL register., offset: 0x0 */
      __IO uint16 H;                                 /**< CRC_DATAH register., offset: 0x2 */
    } DATA_16;
    struct {                                         /* offset: 0x0 */
      __IO uint8 LL;                                 /**< CRC_DATALL register., offset: 0x0 */
      __IO uint8 LU;                                 /**< CRC_DATALU register., offset: 0x1 */
      __IO uint8 HL;                                 /**< CRC_DATAHL register., offset: 0x2 */
      __IO uint8 HU;                                 /**< CRC_DATAHU register., offset: 0x3 */
    } DATA_8;
  } DATAu;
  __IO uint32 GPOLY;                             /**< CRC Polynomial register, offset: 0x4 */
  __IO uint32 CTRL;                              /**< CRC Control register, offset: 0x8 */
} CRC_Type, *CRC_MemMapPtr;


typedef enum
{
    CRC_BITS_16 = 0U,   /*!< Generate 16-bit CRC code */
    CRC_BITS_32 = 1U    /*!< Generate 32-bit CRC code */
} crc_bit_width_t;

typedef enum
{
    CRC_TRANSPOSE_NONE              = 0x00U,    /*!< No transpose */
    CRC_TRANSPOSE_BITS              = 0x01U,    /*!< Transpose bits in bytes */
    CRC_TRANSPOSE_BITS_AND_BYTES    = 0x02U,    /*!< Transpose bytes and bits in bytes */
    CRC_TRANSPOSE_BYTES             = 0x03U     /*!< Transpose bytes */
} crc_transpose_t;


typedef struct
{

    crc_bit_width_t crcWidth;               /*!< Selects 16-bit or 32-bit CRC protocol. */
    uint32 polynomial;                    /*!< CRC Polynomial, MSBit first.<br/>
                                             *   Example polynomial: 0x1021U = 1_0000_0010_0001 = x^12+x^5+1 */
    bool readTranspose;                     /*!< Swap on the CRC_OUTP content. */
    crc_transpose_t writeTranspose;         /*!< Type of transpose when writing CRC input data. */
    bool complementChecksum;                /*!< True if the result shall be complement of the actual checksum. */
    uint32 seed;                          /*!< Starting checksum value. */
} crc_user_config_t;

CRC_Type    CrcReg;

/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base address */
#define CRC_BASE                                 (&CrcReg)
/** Peripheral CRC base pointer */
#define CRC                                      ((CRC_Type *)CRC_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           { CRC_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC }

#endif // SYS_CRC_REG_STUBS_2021_11_18_H_

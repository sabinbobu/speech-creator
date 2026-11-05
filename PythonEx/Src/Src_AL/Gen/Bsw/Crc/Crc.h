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
/// \file  Crc.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CRC_2019_10_21_H_
  #define CRC_2019_10_21_H_

  #include <Std_Types.h>
#include <AL_Helper.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
// CRC8H2F Init Value (Seed)
#define CRC_SEED_INIT_CRC8H2F_VAL       (uint8)0xFFu

//-----------------------------------------------------------------------------
// Structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// This type contains the CRC Protocol Information.
//-----------------------------------------------------------------------------
uint16 Crc_CalculateCRC16(CONST_AL uint8* pucCrc_DataPtr,
                          uint16_least unCrc_Length,
                          uint16       unCrc_StartValue16);


uint32 Crc_CalculateCRC32(CONST_AL uint8* pucCrc_DataPtr,
                          uint32_least ulCrc_Length,
                          uint32       ulCrc_StartValue32);

uint32 Crc_CalculateCRC32P4(CONST_AL uint8 *DataPtr,
                            CONST_AL uint32 Length,
                            CONST_AL uint32 StartValue32);

uint8 Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr,
                           CONST_AL uint32 Length,
                           CONST_AL uint8  StartValue8);

uint8 Crc_CalculateCRC8H1D(CONST_AL uint8 *DataPtr,
                           CONST_AL uint32 Length,
                           CONST_AL uint8  StartValue8);

uint32 Crc_CalculateCRC32_4C11DB7(CONST_AL uint8*  pucCrc_DataPtr,
                                  uint32  ulCrc_Length,
                                  uint32  ulCrc_StartValue32);

#endif // CRC_2019_10_21_H_

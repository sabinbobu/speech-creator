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
/// \file  SysCrc_Cfg.c
///
/// \brief
///
/// \author Cruciu Denis-Mihai (F31196D)
///         mailTo: denis-mihai.cruciu[at]marelli.com
//-----------------------------------------------------------------------------
#include <SysCrc.h>
#if defined UNIT_TEST
  #include <SysCrc_reg_stubs.h>
#else
  #include <crc_driver.h>

#endif



static const crc_user_config_t SysCrc_Config0 = {
  .crcWidth = CRC_BITS_32,
  .readTranspose = CRC_TRANSPOSE_BITS_AND_BYTES,
  .writeTranspose = CRC_TRANSPOSE_BITS_AND_BYTES,
  .complementChecksum = true,
  .polynomial = 0x04C11DB7u, /*CRC: Ethernet(IEEE 802,3) CCITT32 CRC - 32 */
  .seed = 0xFFFFFFFFu
};

const SysCrc_SpecificType SysCrc_Config =
{
  1U,
  (crc_user_config_t*)&SysCrc_Config0 // PRQA S 310, 311 // Necessary cast to avoid using ThirdParty structures
};

//EOF

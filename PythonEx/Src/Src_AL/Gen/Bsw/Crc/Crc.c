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
/// \file  Crc.c
///
/// \brief Routine for Program Flash Memory CRC calculation.
///
/// \descr  This module contains subroutines which calculates the
///         CRC checksum of the program flash memory
///
/// \author Muscan Samuel (F67522C)
///         mailTo:samuel-remus.muscan[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Bsw/Crc/Crc.h>
#include <AL_Helper.h>


//=============================================================================
// Functions
//=============================================================================

// CRC 32P4 TABLE
static const uint32 s_TableCrc32P4[256U] = {
  0X00000000u,  0X30850FF5u,  0X610A1FEAu,  0X518F101Fu,  0XC2143FD4u,
  0XF2913021u,  0XA31E203Eu,  0X939B2FCBu,  0X159615F7u,  0X25131A02u,
  0X749C0A1Du,  0X441905E8u,  0XD7822A23u,  0XE70725D6u,  0XB68835C9u,
  0X860D3A3Cu,  0X2B2C2BEEu,  0X1BA9241Bu,  0X4A263404u,  0X7AA33BF1u,
  0XE938143Au,  0XD9BD1BCFu,  0X88320BD0u,  0XB8B70425u,  0X3EBA3E19u,
  0X0E3F31ECu,  0X5FB021F3u,  0X6F352E06u,  0XFCAE01CDu,  0XCC2B0E38u,
  0X9DA41E27u,  0XAD2111D2u,  0X565857DCu,  0X66DD5829u,  0X37524836u,
  0X07D747C3u,  0X944C6808u,  0XA4C967FDu,  0XF54677E2u,  0XC5C37817u,
  0X43CE422Bu,  0X734B4DDEu,  0X22C45DC1u,  0X12415234u,  0X81DA7DFFu,
  0XB15F720Au,  0XE0D06215u,  0XD0556DE0u,  0X7D747C32u,  0X4DF173C7u,
  0X1C7E63D8u,  0X2CFB6C2Du,  0XBF6043E6u,  0X8FE54C13u,  0XDE6A5C0Cu,
  0XEEEF53F9u,  0X68E269C5u,  0X58676630u,  0X09E8762Fu,  0X396D79DAu,
  0XAAF65611u,  0X9A7359E4u,  0XCBFC49FBu,  0XFB79460Eu,  0XACB0AFB8u,
  0X9C35A04Du,  0XCDBAB052u,  0XFD3FBFA7u,  0X6EA4906Cu,  0X5E219F99u,
  0X0FAE8F86u,  0X3F2B8073u,  0XB926BA4Fu,  0X89A3B5BAu,  0XD82CA5A5u,
  0XE8A9AA50u,  0X7B32859Bu,  0X4BB78A6Eu,  0X1A389A71u,  0X2ABD9584u,
  0X879C8456u,  0XB7198BA3u,  0XE6969BBCu,  0XD6139449u,  0X4588BB82u,
  0X750DB477u,  0X2482A468u,  0X1407AB9Du,  0X920A91A1u,  0XA28F9E54u,
  0XF3008E4Bu,  0xC38581BEu,  0X501EAE75u,  0X609BA180u,  0X3114B19Fu,
  0X0191BE6Au,  0XFAE8F864u,  0XCA6DF791u,  0X9BE2E78Eu,  0XAB67E87Bu,
  0X38FCC7B0u,  0X0879C845u,  0X59F6D85Au,  0X6973D7AFu,  0XEF7EED93u,
  0XDFFBE266u,  0X8E74F279u,  0XBEF1FD8Cu,  0X2D6AD247u,  0X1DEFDDB2u,
  0X4C60CDADu,  0X7CE5C258u,  0XD1C4D38Au,  0XE141DC7Fu,  0XB0CECC60u,
  0X804BC395u,  0X13D0EC5Eu,  0X2355E3ABu,  0X72DAF3B4u,  0X425FFC41u,
  0XC452C67Du,  0XF4D7C988u,  0XA558D997u,  0X95DDD662u,  0X0646F9A9u,
  0X36C3F65Cu,  0X674CE643u,  0X57C9E9B6u,  0XC8DF352Fu,  0XF85A3ADAu,
  0XA9D52AC5u,  0X99502530u,  0X0ACB0AFBu,  0X3A4E050Eu,  0X6BC11511u,
  0X5B441AE4u,  0XDD4920D8u,  0XEDCC2F2Du,  0XBC433F32u,  0X8CC630C7u,
  0X1F5D1F0Cu,  0X2FD810F9u,  0X7E5700E6u,  0X4ED20F13u,  0XE3F31EC1u,
  0XD3761134u,  0X82F9012Bu,  0XB27C0EDEu,  0X21E72115u,  0X11622EE0u,
  0X40ED3EFFu,  0X7068310Au,  0XF6650B36u,  0XC6E004C3u,  0X976F14DCu,
  0XA7EA1B29u,  0X347134E2u,  0X04F43B17u,  0X557B2B08u,  0X65FE24FDu,
  0X9E8762F3u,  0XAE026D06u,  0XFF8D7D19u,  0XCF0872ECu,  0X5C935D27u,
  0X6C1652D2u,  0X3D9942CDu,  0X0D1C4D38u,  0X8B117704u,  0XBB9478F1u,
  0XEA1B68EEu,  0XDA9E671Bu,  0X490548D0u,  0X79804725u,  0X280F573Au,
  0X188A58CFu,  0XB5AB491Du,  0X852E46E8u,  0XD4A156F7u,  0XE4245902u,
  0X77BF76C9u,  0X473A793Cu,  0X16B56923u,  0X263066D6u,  0XA03D5CEAu,
  0X90B8531Fu,  0XC1374300u,  0XF1B24CF5u,  0X6229633Eu,  0X52AC6CCBu,
  0X03237CD4u,  0X33A67321u,  0X646F9A97u,  0X54EA9562u,  0X0565857Du,
  0X35E08A88u,  0XA67BA543u,  0X96FEAAB6u,  0XC771BAA9u,  0XF7F4B55Cu,
  0X71F98F60u,  0X417C8095u,  0X10F3908Au,  0X20769F7Fu,  0XB3EDB0B4u,
  0X8368BF41u,  0XD2E7AF5Eu,  0XE262A0ABu,  0X4F43B179u,  0X7FC6BE8Cu,
  0X2E49AE93u,  0X1ECCA166u,  0X8D578EADu,  0XBDD28158u,  0XEC5D9147u,
  0XDCD89EB2u,  0X5AD5A48Eu,  0X6A50AB7Bu,  0X3BDFBB64u,  0X0B5AB491u,
  0X98C19B5Au,  0XA84494AFu,  0XF9CB84B0u,  0XC94E8B45u,  0X3237CD4Bu,
  0X02B2C2BEu,  0X533DD2A1u,  0X63B8DD54u,  0XF023F29Fu,  0XC0A6FD6Au,
  0X9129ED75u,  0XA1ACE280u,  0X27A1D8BCu,  0X1724D749u,  0X46ABC756u,
  0X762EC8A3u,  0XE5B5E768u,  0XD530E89Du,  0X84BFF882u,  0XB43AF777u,
  0X191BE6A5u,  0X299EE950u,  0X7811F94Fu,  0X4894F6BAu,  0XDB0FD971u,
  0XEB8AD684u,  0XBA05C69Bu,  0X8A80C96Eu,  0X0C8DF352u,  0X3C08FCA7u,
  0X6D87ECB8u,  0X5D02E34Du,  0XCE99CC86u,  0XFE1CC373u,  0XAF93D36Cu,
  0X9F16DC99u
};

//-----------------------------------------------------------------------------
/// \brief Crc_CalculateCRC32P4
///
/// \descr This function calculates CRC32 following E2E Autosar Profile 4 polynomial 0xF4ACFB13
///        This function Calculate CRC32 Lookup Table with Channel Input: CRC32 and CRC32P4.
///
/// \param  pucCrc_DataPtr -> Buffer which contains the bytes over which CRC32 is performed
///         ulCrc_Length -> Number of bytes from pucCrc_DataPtr used for CRC32 calculation 
///         ulCrc_StartValue32 -> Initial value for CRC32 calculation
///
/// \return ulCrc32_result - calculated CRC32
//-----------------------------------------------------------------------------
uint32 Crc_CalculateCRC32P4(CONST_AL uint8 *DataPtr,
                            CONST_AL uint32 Length,
                            CONST_AL uint32 StartValue32)
{
  uint32 LengthIdx = 0U;
  uint32 u32CrcValue = StartValue32;

  /* Start calculate CRC value by using a table */
  for (LengthIdx = (uint32)0UL; LengthIdx < Length; LengthIdx++)
  {
    u32CrcValue = (uint32)(u32CrcValue >> 8u) ^ s_TableCrc32P4[(uint8)((uint8)(u32CrcValue & 0xFFu) ^ (uint8)(DataPtr[LengthIdx]))];
  }

  // Negate mask
  u32CrcValue = ~u32CrcValue;

  return u32CrcValue;
}


//-----------------------------------------------------------------------------
/// \brief Crc_CalculateCRC32
///
/// \descr This function calculates CRC32
///
/// \param  pucCrc_DataPtr -> Buffer which contains the bytes over which CRC32 is performed
///         ulCrc_Length -> Number of bytes from pucCrc_DataPtr used for CRC32 calculation 
///         ulCrc_StartValue32 -> Initial value for CRC32 calculation
///
/// \return ulCrc32_result - calculated CRC32
//-----------------------------------------------------------------------------
uint32 Crc_CalculateCRC32(CONST_AL uint8* pucCrc_DataPtr,
                          uint32_least ulCrc_Length,
                          uint32       ulCrc_StartValue32)
{
  // The lookup table for the CRC-32/MPEG-2 (based on nibbles).
  static const uint32 crc32_lookup_table[16U] =
  {
    0x00000000UL, 0x04C11DB7UL, 0x09823B6EUL, 0x0D4326D9UL,
    0x130476DCUL, 0x17C56B6BUL, 0x1A864DB2UL, 0x1E475005UL,
    0x2608EDB8UL, 0x22C9F00FUL, 0x2F8AD6D6UL, 0x2B4BCB61UL,
    0x350C9B64UL, 0x31CD86D3UL, 0x3C8EA00AUL, 0x384fBDBDUL
  };

  uint32 ulCrc32_result = ulCrc_StartValue32;

  CONST_AL uint8* pucCrc_DataEnd = (CONST_AL uint8*) (pucCrc_DataPtr + ulCrc_Length);

  while (pucCrc_DataPtr != pucCrc_DataEnd)
  {
    const uint8 ucThe_byte = *pucCrc_DataPtr;

    ulCrc32_result = (uint32)(ulCrc32_result << 4u) ^ crc32_lookup_table[(uint8)((uint8)(ulCrc32_result >> 28u) ^ (uint8)(ucThe_byte >> 4u))];
    ulCrc32_result = (uint32)(ulCrc32_result << 4u) ^ crc32_lookup_table[(uint8)((uint8)(ulCrc32_result >> 28u) ^ (uint8)(ucThe_byte & 0x0Fu))];

    ++pucCrc_DataPtr;
  }

  return ulCrc32_result;
}


//-----------------------------------------------------------------------------
/// \brief Crc_CalculateCRC16
///
/// \descr This function calculates CRC16
///
/// \param  pucCrc_DataPtr -> Buffer which contains the bytes over which CRC16 is performed
///         unCrc_Length -> Number of bytes from pucCrc_DataPtr used for CRC16 calculation
///         unCrc_StartValue16 -> Initial value for CRC16 calculation
///
/// \return unCrc16_result - calculated CRC16
//-----------------------------------------------------------------------------
uint16 Crc_CalculateCRC16(CONST_AL uint8* pucCrc_DataPtr,
                          uint16_least unCrc_Length,
                          uint16       unCrc_StartValue16)
{
  // The lookup table for the CRC-16 CCIT
  static const uint16 crc16_lookup_table[256U] =
  {
    0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50a5U, 0x60c6U, 0x70e7U,
    0x8108U, 0x9129U, 0xa14aU, 0xb16bU, 0xc18cU, 0xd1adU, 0xe1ceU, 0xf1efU,
    0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52b5U, 0x4294U, 0x72f7U, 0x62d6U,
    0x9339U, 0x8318U, 0xb37bU, 0xa35aU, 0xd3bdU, 0xc39cU, 0xf3ffU, 0xe3deU,
    0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64e6U, 0x74c7U, 0x44a4U, 0x5485U,
    0xa56aU, 0xb54bU, 0x8528U, 0x9509U, 0xe5eeU, 0xf5cfU, 0xc5acU, 0xd58dU,
    0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76d7U, 0x66f6U, 0x5695U, 0x46b4U,
    0xb75bU, 0xa77aU, 0x9719U, 0x8738U, 0xf7dfU, 0xe7feU, 0xd79dU, 0xc7bcU,
    0x48c4U, 0x58e5U, 0x6886U, 0x78a7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U,
    0xc9ccU, 0xd9edU, 0xe98eU, 0xf9afU, 0x8948U, 0x9969U, 0xa90aU, 0xb92bU,
    0x5af5U, 0x4ad4U, 0x7ab7U, 0x6a96U, 0x1a71U, 0x0a50U, 0x3a33U, 0x2a12U,
    0xdbfdU, 0xcbdcU, 0xfbbfU, 0xeb9eU, 0x9b79U, 0x8b58U, 0xbb3bU, 0xab1aU,
    0x6ca6U, 0x7c87U, 0x4ce4U, 0x5cc5U, 0x2c22U, 0x3c03U, 0x0c60U, 0x1c41U,
    0xedaeU, 0xfd8fU, 0xcdecU, 0xddcdU, 0xad2aU, 0xbd0bU, 0x8d68U, 0x9d49U,
    0x7e97U, 0x6eb6U, 0x5ed5U, 0x4ef4U, 0x3e13U, 0x2e32U, 0x1e51U, 0x0e70U,
    0xff9fU, 0xefbeU, 0xdfddU, 0xcffcU, 0xbf1bU, 0xaf3aU, 0x9f59U, 0x8f78U,
    0x9188U, 0x81a9U, 0xb1caU, 0xa1ebU, 0xd10cU, 0xc12dU, 0xf14eU, 0xe16fU,
    0x1080U, 0x00a1U, 0x30c2U, 0x20e3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
    0x83b9U, 0x9398U, 0xa3fbU, 0xb3daU, 0xc33dU, 0xd31cU, 0xe37fU, 0xf35eU,
    0x02b1U, 0x1290U, 0x22f3U, 0x32d2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
    0xb5eaU, 0xa5cbU, 0x95a8U, 0x8589U, 0xf56eU, 0xe54fU, 0xd52cU, 0xc50dU,
    0x34e2U, 0x24c3U, 0x14a0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
    0xa7dbU, 0xb7faU, 0x8799U, 0x97b8U, 0xe75fU, 0xf77eU, 0xc71dU, 0xd73cU,
    0x26d3U, 0x36f2U, 0x0691U, 0x16b0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,
    0xd94cU, 0xc96dU, 0xf90eU, 0xe92fU, 0x99c8U, 0x89e9U, 0xb98aU, 0xa9abU,
    0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18c0U, 0x08e1U, 0x3882U, 0x28a3U,
    0xcb7dU, 0xdb5cU, 0xeb3fU, 0xfb1eU, 0x8bf9U, 0x9bd8U, 0xabbbU, 0xbb9aU,
    0x4a75U, 0x5a54U, 0x6a37U, 0x7a16U, 0x0af1U, 0x1ad0U, 0x2ab3U, 0x3a92U,
    0xfd2eU, 0xed0fU, 0xdd6cU, 0xcd4dU, 0xbdaaU, 0xad8bU, 0x9de8U, 0x8dc9U,
    0x7c26U, 0x6c07U, 0x5c64U, 0x4c45U, 0x3ca2U, 0x2c83U, 0x1ce0U, 0x0cc1U,
    0xef1fU, 0xff3eU, 0xcf5dU, 0xdf7cU, 0xaf9bU, 0xbfbaU, 0x8fd9U, 0x9ff8U,
    0x6e17U, 0x7e36U, 0x4e55U, 0x5e74U, 0x2e93U, 0x3eb2U, 0x0ed1U, 0x1ef0U
  };

  uint16 unCrc16_result = unCrc_StartValue16;

  CONST_AL uint8* pucCrc_DataEnd = (CONST_AL uint8*)(pucCrc_DataPtr + unCrc_Length);

  while (pucCrc_DataPtr != pucCrc_DataEnd)
  {
    uint8 ucTableIndex = ((uint8)(unCrc16_result >> 8u)) ^ (*(pucCrc_DataPtr++));
    unCrc16_result = (uint16)(unCrc16_result << 8u) ^ crc16_lookup_table[ucTableIndex];
  }

  return unCrc16_result;
}


// CRC 8H2F TABLE
static const uint8 s_Table8H2F[256U] =
{
  0x00U, 0x2FU, 0x5EU, 0x71U, 0xBCU, 0x93U, 0xE2U, 0xCDU, 0x57U, 0x78U, 0x09U,
  0x26U, 0xEBU, 0xC4U, 0xB5U, 0x9AU, 0xAEU, 0x81U, 0xF0U, 0xDFU, 0x12U, 0x3DU,
  0x4CU, 0x63U, 0xF9U, 0xD6U, 0xA7U, 0x88U, 0x45U, 0x6AU, 0x1BU, 0x34U, 0x73U,
  0x5CU, 0x2DU, 0x02U, 0xCFU, 0xE0U, 0x91U, 0xBEU, 0x24U, 0x0BU, 0x7AU, 0x55U,
  0x98U, 0xB7U, 0xC6U, 0xE9U, 0xDDU, 0xF2U, 0x83U, 0xACU, 0x61U, 0x4EU, 0x3FU,
  0x10U, 0x8AU, 0xA5U, 0xD4U, 0xFBU, 0x36U, 0x19U, 0x68U, 0x47U, 0xE6U, 0xC9U,
  0xB8U, 0x97U, 0x5AU, 0x75U, 0x04U, 0x2BU, 0xB1U, 0x9EU, 0xEFU, 0xC0U, 0x0DU,
  0x22U, 0x53U, 0x7CU, 0x48U, 0x67U, 0x16U, 0x39U, 0xF4U, 0xDBU, 0xAAU, 0x85U,
  0x1FU, 0x30U, 0x41U, 0x6EU, 0xA3U, 0x8CU, 0xFDU, 0xD2U, 0x95U, 0xBAU, 0xCBU,
  0xE4U, 0x29U, 0x06U, 0x77U, 0x58U, 0xC2U, 0xEDU, 0x9CU, 0xB3U, 0x7EU, 0x51U,
  0x20U, 0x0FU, 0x3BU, 0x14U, 0x65U, 0x4AU, 0x87U, 0xA8U, 0xD9U, 0xF6U, 0x6CU,
  0x43U, 0x32U, 0x1DU, 0xD0U, 0xFFU, 0x8EU, 0xA1U, 0xE3U, 0xCCU, 0xBDU, 0x92U,
  0x5FU, 0x70U, 0x01U, 0x2EU, 0xB4U, 0x9BU, 0xEAU, 0xC5U, 0x08U, 0x27U, 0x56U,
  0x79U, 0x4DU, 0x62U, 0x13U, 0x3CU, 0xF1U, 0xDEU, 0xAFU, 0x80U, 0x1AU, 0x35U,
  0x44U, 0x6BU, 0xA6U, 0x89U, 0xF8U, 0xD7U, 0x90U, 0xBFU, 0xCEU, 0xE1U, 0x2CU,
  0x03U, 0x72U, 0x5DU, 0xC7U, 0xE8U, 0x99U, 0xB6U, 0x7BU, 0x54U, 0x25U, 0x0AU,
  0x3EU, 0x11U, 0x60U, 0x4FU, 0x82U, 0xADU, 0xDCU, 0xF3U, 0x69U, 0x46U, 0x37U,
  0x18U, 0xD5U, 0xFAU, 0x8BU, 0xA4U, 0x05U, 0x2AU, 0x5BU, 0x74U, 0xB9U, 0x96U,
  0xE7U, 0xC8U, 0x52U, 0x7DU, 0x0CU, 0x23U, 0xEEU, 0xC1U, 0xB0U, 0x9FU, 0xABU,
  0x84U, 0xF5U, 0xDAU, 0x17U, 0x38U, 0x49U, 0x66U, 0xFCU, 0xD3U, 0xA2U, 0x8DU,
  0x40U, 0x6FU, 0x1EU, 0x31U, 0x76U, 0x59U, 0x28U, 0x07U, 0xCAU, 0xE5U, 0x94U,
  0xBBU, 0x21U, 0x0EU, 0x7FU, 0x50U, 0x9DU, 0xB2U, 0xC3U, 0xECU, 0xD8U, 0xF7U,
  0x86U, 0xA9U, 0x64U, 0x4BU, 0x3AU, 0x15U, 0x8FU, 0xA0U, 0xD1U, 0xFEU, 0x33U,
  0x1CU, 0x6DU, 0x42U
};


//-----------------------------------------------------------------------------
/// \brief Crc_CalculateCRC8H2F
///
/// \descr This function calculates CRC8 following Autosar E2E Profile 2 polynomial 0x2F
///        This function Calculates CRC8 using a Lookup Table.
///
/// \param  DataPtr -> Buffer which contains the bytes over which CRC8H2F is performed
///         Length -> Number of bytes from DataPtr used for CRC8 calculation 
///         StartValue8 -> Initial value for CRC8 calculation
///
/// \return u8CrcValue - calculated CRC8
//-----------------------------------------------------------------------------
uint8 Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr,
                           CONST_AL uint32 Length,
                           CONST_AL uint8  StartValue8)
{
  uint32 LengthIdx = 0U;
  uint8  u8CrcValue = StartValue8;

  /* Start calculate CRC value by using a table */
  for (LengthIdx = (uint32)0UL; LengthIdx < Length; LengthIdx++)
  {
    u8CrcValue = s_Table8H2F[u8CrcValue ^ (uint8)(DataPtr[LengthIdx])];
  }

  // Negate mask
  u8CrcValue = ~u8CrcValue;

  return u8CrcValue;
}


// CRC 8H1D TABLE
static const uint8 s_Table8H1D[256U] =
{
  0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53, 0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
  0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E, 0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
  0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4, 0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
  0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19, 0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
  0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40, 0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
  0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D, 0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
  0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7, 0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
  0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A, 0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
  0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75, 0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
  0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8, 0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
  0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2, 0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
  0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F, 0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
  0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66, 0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
  0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB, 0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
  0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1, 0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
  0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C, 0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4
};

//-----------------------------------------------------------------------------
/// \brief Crc_CalculateCRC8H1D
///
/// \descr This function calculates CRC8 following CRC8_SAE_J1850  polynomial 0x1D
///        This function Calculates CRC8 using a Lookup Table.
///
/// \param  DataPtr -> Buffer which contains the bytes over which CRC8H1D is performed
///         Length -> Number of bytes from DataPtr used for CRC8 calculation 
///         StartValue8 -> Initial value for CRC8 calculation
///
/// \return u8CrcValue - calculated CRC8
//-----------------------------------------------------------------------------
uint8 Crc_CalculateCRC8H1D(CONST_AL uint8 *DataPtr,
                           CONST_AL uint32 Length,
                           CONST_AL uint8  StartValue8)
{
  uint32 LengthIdx = 0U;
  uint8  u8CrcValue = StartValue8;

  /* Start calculate CRC value by using a table */
  for (LengthIdx = (uint32)0UL; LengthIdx < Length; LengthIdx++)
  {
    u8CrcValue = s_Table8H1D[u8CrcValue ^ (uint8)(DataPtr[LengthIdx])];
  }

  // Negate mask
  u8CrcValue = ~u8CrcValue;

  return u8CrcValue;
}

//CRC32 4C11DB7 Table
static const uint32 aulCrc_Table32[256U] =
{
  0x00000000uL, 0x77073096uL, 0xEE0E612CuL, 0x990951BAuL,
  0x076DC419uL, 0x706AF48FuL, 0xE963A535uL, 0x9E6495A3uL,
  0x0EDB8832uL, 0x79DCB8A4uL, 0xE0D5E91EuL, 0x97D2D988uL,
  0x09B64C2BuL, 0x7EB17CBDuL, 0xE7B82D07uL, 0x90BF1D91uL,
  0x1DB71064uL, 0x6AB020F2uL, 0xF3B97148uL, 0x84BE41DEuL,
  0x1ADAD47DuL, 0x6DDDE4EBuL, 0xF4D4B551uL, 0x83D385C7uL,
  0x136C9856uL, 0x646BA8C0uL, 0xFD62F97AuL, 0x8A65C9ECuL,
  0x14015C4FuL, 0x63066CD9uL, 0xFA0F3D63uL, 0x8D080DF5uL,
  0x3B6E20C8uL, 0x4C69105EuL, 0xD56041E4uL, 0xA2677172uL,
  0x3C03E4D1uL, 0x4B04D447uL, 0xD20D85FDuL, 0xA50AB56BuL,
  0x35B5A8FAuL, 0x42B2986CuL, 0xDBBBC9D6uL, 0xACBCF940uL,
  0x32D86CE3uL, 0x45DF5C75uL, 0xDCD60DCFuL, 0xABD13D59uL,
  0x26D930ACuL, 0x51DE003AuL, 0xC8D75180uL, 0xBFD06116uL,
  0x21B4F4B5uL, 0x56B3C423uL, 0xCFBA9599uL, 0xB8BDA50FuL,
  0x2802B89EuL, 0x5F058808uL, 0xC60CD9B2uL, 0xB10BE924uL,
  0x2F6F7C87uL, 0x58684C11uL, 0xC1611DABuL, 0xB6662D3DuL,
  0x76DC4190uL, 0x01DB7106uL, 0x98D220BCuL, 0xEFD5102AuL,
  0x71B18589uL, 0x06B6B51FuL, 0x9FBFE4A5uL, 0xE8B8D433uL,
  0x7807C9A2uL, 0x0F00F934uL, 0x9609A88EuL, 0xE10E9818uL,
  0x7F6A0DBBuL, 0x086D3D2DuL, 0x91646C97uL, 0xE6635C01uL,
  0x6B6B51F4uL, 0x1C6C6162uL, 0x856530D8uL, 0xF262004EuL,
  0x6C0695EDuL, 0x1B01A57BuL, 0x8208F4C1uL, 0xF50FC457uL,
  0x65B0D9C6uL, 0x12B7E950uL, 0x8BBEB8EAuL, 0xFCB9887CuL,
  0x62DD1DDFuL, 0x15DA2D49uL, 0x8CD37CF3uL, 0xFBD44C65uL,
  0x4DB26158uL, 0x3AB551CEuL, 0xA3BC0074uL, 0xD4BB30E2uL,
  0x4ADFA541uL, 0x3DD895D7uL, 0xA4D1C46DuL, 0xD3D6F4FBuL,
  0x4369E96AuL, 0x346ED9FCuL, 0xAD678846uL, 0xDA60B8D0uL,
  0x44042D73uL, 0x33031DE5uL, 0xAA0A4C5FuL, 0xDD0D7CC9uL,
  0x5005713CuL, 0x270241AAuL, 0xBE0B1010uL, 0xC90C2086uL,
  0x5768B525uL, 0x206F85B3uL, 0xB966D409uL, 0xCE61E49FuL,
  0x5EDEF90EuL, 0x29D9C998uL, 0xB0D09822uL, 0xC7D7A8B4uL,
  0x59B33D17uL, 0x2EB40D81uL, 0xB7BD5C3BuL, 0xC0BA6CADuL,
  0xEDB88320uL, 0x9ABFB3B6uL, 0x03B6E20CuL, 0x74B1D29AuL,
  0xEAD54739uL, 0x9DD277AFuL, 0x04DB2615uL, 0x73DC1683uL,
  0xE3630B12uL, 0x94643B84uL, 0x0D6D6A3EuL, 0x7A6A5AA8uL,
  0xE40ECF0BuL, 0x9309FF9DuL, 0x0A00AE27uL, 0x7D079EB1uL,
  0xF00F9344uL, 0x8708A3D2uL, 0x1E01F268uL, 0x6906C2FEuL,
  0xF762575DuL, 0x806567CBuL, 0x196C3671uL, 0x6E6B06E7uL,
  0xFED41B76uL, 0x89D32BE0uL, 0x10DA7A5AuL, 0x67DD4ACCuL,
  0xF9B9DF6FuL, 0x8EBEEFF9uL, 0x17B7BE43uL, 0x60B08ED5uL,
  0xD6D6A3E8uL, 0xA1D1937EuL, 0x38D8C2C4uL, 0x4FDFF252uL,
  0xD1BB67F1uL, 0xA6BC5767uL, 0x3FB506DDuL, 0x48B2364BuL,
  0xD80D2BDAuL, 0xAF0A1B4CuL, 0x36034AF6uL, 0x41047A60uL,
  0xDF60EFC3uL, 0xA867DF55uL, 0x316E8EEFuL, 0x4669BE79uL,
  0xCB61B38CuL, 0xBC66831AuL, 0x256FD2A0uL, 0x5268E236uL,
  0xCC0C7795uL, 0xBB0B4703uL, 0x220216B9uL, 0x5505262FuL,
  0xC5BA3BBEuL, 0xB2BD0B28uL, 0x2BB45A92uL, 0x5CB36A04uL,
  0xC2D7FFA7uL, 0xB5D0CF31uL, 0x2CD99E8BuL, 0x5BDEAE1DuL,
  0x9B64C2B0uL, 0xEC63F226uL, 0x756AA39CuL, 0x026D930AuL,
  0x9C0906A9uL, 0xEB0E363FuL, 0x72076785uL, 0x05005713uL,
  0x95BF4A82uL, 0xE2B87A14uL, 0x7BB12BAEuL, 0x0CB61B38uL,
  0x92D28E9BuL, 0xE5D5BE0DuL, 0x7CDCEFB7uL, 0x0BDBDF21uL,
  0x86D3D2D4uL, 0xF1D4E242uL, 0x68DDB3F8uL, 0x1FDA836EuL,
  0x81BE16CDuL, 0xF6B9265BuL, 0x6FB077E1uL, 0x18B74777uL,
  0x88085AE6uL, 0xFF0F6A70uL, 0x66063BCAuL, 0x11010B5CuL,
  0x8F659EFFuL, 0xF862AE69uL, 0x616BFFD3uL, 0x166CCF45uL,
  0xA00AE278uL, 0xD70DD2EEuL, 0x4E048354uL, 0x3903B3C2uL,
  0xA7672661uL, 0xD06016F7uL, 0x4969474DuL, 0x3E6E77DBuL,
  0xAED16A4AuL, 0xD9D65ADCuL, 0x40DF0B66uL, 0x37D83BF0uL,
  0xA9BCAE53uL, 0xDEBB9EC5uL, 0x47B2CF7FuL, 0x30B5FFE9uL,
  0xBDBDF21CuL, 0xCABAC28AuL, 0x53B39330uL, 0x24B4A3A6uL,
  0xBAD03605uL, 0xCDD70693uL, 0x54DE5729uL, 0x23D967BFuL,
  0xB3667A2EuL, 0xC4614AB8uL, 0x5D681B02uL, 0x2A6F2B94uL,
  0xB40BBE37uL, 0xC30C8EA1uL, 0x5A05DF1BuL, 0x2D02EF8DuL
};

//-----------------------------------------------------------------------------
/// \brief Crc_CalculateCRC32_4C11DB7
///
/// \descr Function to calculete CRC32 with Initial value of the CRC32 is	0xFFFFFFFF
///        The polynomial used is		0x04C11DB7
///
/// \param  pucCrc_DataPtr; ulCrc_Length; ulCrc_StartValue32; boCrc_IsFirstCall
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32  Crc_CalculateCRC32_4C11DB7(CONST_AL uint8*  pucCrc_DataPtr,
                                    uint32  ulCrc_Length,
                                    uint32  ulCrc_StartValue32)
{
  // width   = 32
  // poly    = 0x04C11DB7
  // init    = 0xFFFFFFFF
  // refin   = true
  // refout  = true
  // xorout  = 0xFFFFFFFF
  // check   = 0xCBF43926
  // residue =0x00000000DEBB20E3
  // name    = "crc32"

  //=============================================================================
  // Private Variables
  //=============================================================================
  uint32 ulCrc_Value = ulCrc_StartValue32;

  for (uint32 Crc_LoopCounter = 0U; Crc_LoopCounter < ulCrc_Length; ++Crc_LoopCounter)
  {
    ulCrc_Value ^= 0xFFuL & (uint32)pucCrc_DataPtr[Crc_LoopCounter];
    ulCrc_Value = (ulCrc_Value >> 8u) ^ (aulCrc_Table32[(uint8)(ulCrc_Value)]);
  }
  /* #40 Final CRC value is XORed with 0xFFFFFFFFUL*/
  return ulCrc_Value ^ ulCrc_StartValue32;
}

// EOF

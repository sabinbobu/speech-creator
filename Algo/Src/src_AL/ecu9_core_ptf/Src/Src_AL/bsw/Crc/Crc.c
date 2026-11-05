#include "Crc.h"
#include <stddef.h>

#define CRC8_POLYNOMIAL 0x1DU
#define CRC8_INIT 0xFFU
#define CRC8_XOR_OUT 0xFFU
#define CRC16_POLYNOMIAL 0x1021U
#define CRC16_INIT 0xFFFFU
#define CRC32_POLYNOMIAL 0x04C11DB7UL
#define CRC32_INIT 0xFFFFFFFFUL
#define CRC32_XOR_OUT 0xFFFFFFFFUL

STATIC uint8 Crc_CalculateCRC8Byte(uint8 crc, uint8 data)
{
    uint8 bit;
    uint8 next_crc = (uint8)(crc ^ data);
    for (bit = 0U; bit < 8U; ++bit)
    {
        if ((next_crc & 0x80U) != 0U)
        {
            next_crc = (uint8)((next_crc << 1U) ^ CRC8_POLYNOMIAL);
        }
        else
        {
            next_crc = (uint8)(next_crc << 1U);
        }
    }
    return next_crc;
}

STATIC uint16 Crc_CalculateCRC16Byte(uint16 crc, uint8 data)
{
    uint8 bit;
    uint16 next_crc = (uint16)(crc ^ ((uint16)data << 8U));
    for (bit = 0U; bit < 8U; ++bit)
    {
        if ((next_crc & 0x8000U) != 0U)
        {
            next_crc = (uint16)((next_crc << 1U) ^ CRC16_POLYNOMIAL);
        }
        else
        {
            next_crc = (uint16)(next_crc << 1U);
        }
    }
    return next_crc;
}

STATIC uint32 Crc_CalculateCRC32Byte(uint32 crc, uint8 data)
{
    uint8 bit;
    uint32 next_crc = (uint32)(crc ^ ((uint32)data << 24U));
    for (bit = 0U; bit < 8U; ++bit)
    {
        if ((next_crc & 0x80000000UL) != 0UL)
        {
            next_crc = (next_crc << 1U) ^ CRC32_POLYNOMIAL;
        }
        else
        {
            next_crc = next_crc << 1U;
        }
    }
    return next_crc;
}

uint8 Crc_CalculateCRC8(const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8,
                        uint8 Crc_IsFirstCall)
{
    uint8 crc = Crc_StartValue8;
    if (Crc_IsFirstCall != 0U)
    {
        crc = CRC8_INIT;
    }
    if ((Crc_DataPtr != NULL) || (Crc_Length == 0U))
    {
        uint32 index;
        for (index = 0U; index < Crc_Length; ++index)
        {
            crc = Crc_CalculateCRC8Byte(crc, Crc_DataPtr[index]);
        }
        crc = (uint8)(crc ^ CRC8_XOR_OUT);
    }
    else
    {
        crc = 0U;
    }
    return crc;
}

uint16 Crc_CalculateCRC16(const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16,
                          uint8 Crc_IsFirstCall)
{
    uint16 crc = Crc_StartValue16;
    if (Crc_IsFirstCall != 0U)
    {
        crc = CRC16_INIT;
    }
    if ((Crc_DataPtr != NULL) || (Crc_Length == 0U))
    {
        uint32 index;
        for (index = 0U; index < Crc_Length; ++index)
        {
            crc = Crc_CalculateCRC16Byte(crc, Crc_DataPtr[index]);
        }
    }
    else
    {
        crc = 0U;
    }
    return crc;
}

uint32 Crc_CalculateCRC32(const uint8 *Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32,
                          uint8 Crc_IsFirstCall)
{
    uint32 crc = Crc_StartValue32;
    if (Crc_IsFirstCall != 0U)
    {
        crc = CRC32_INIT;
    }
    if ((Crc_DataPtr != NULL) || (Crc_Length == 0U))
    {
        uint32 index;
        for (index = 0U; index < Crc_Length; ++index)
        {
            crc = Crc_CalculateCRC32Byte(crc, Crc_DataPtr[index]);
        }
        crc = crc ^ CRC32_XOR_OUT;
    }
    else
    {
        crc = 0UL;
    }
    return crc;
}
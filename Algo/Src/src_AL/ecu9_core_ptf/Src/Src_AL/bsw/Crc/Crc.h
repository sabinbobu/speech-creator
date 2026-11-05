#ifndef CRC_H
#define CRC_H

#include "Std_Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    uint8 Crc_CalculateCRC8(const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8,
                            uint8 Crc_IsFirstCall);

    uint16 Crc_CalculateCRC16(const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16,
                              uint8 Crc_IsFirstCall);

    uint32 Crc_CalculateCRC32(const uint8 *Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32,
                              uint8 Crc_IsFirstCall);

#ifdef __cplusplus
}
#endif

#endif /* CRC_H */
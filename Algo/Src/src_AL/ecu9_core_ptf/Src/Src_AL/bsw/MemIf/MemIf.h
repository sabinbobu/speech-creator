#ifndef MEMIF_H
#define MEMIF_H

#include "MemIf_Types.h"
#include "MemIf_Cfg.h"
#include "Fee.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if MEMIF_FEE_SET_MODE_SUPPORTED
#define MemIf_SetMode(Mode) Fee_SetMode((Mode))
#endif

/* MEMIF-IMP-001..004, MEMIF-SWS-001..003; MT_MemIf_Read_001 covers mapping, ignored device, and pass-through. */
#define MemIf_Read(DeviceIndex, BlockNumber, BlockOffset, DataBufferPtr, Length)                 \
    Fee_Read((BlockNumber), (BlockOffset), (DataBufferPtr), (Length))
#define MemIf_Write(DeviceIndex, BlockNumber, DataBufferPtr)                                    \
    Fee_Write((BlockNumber), (DataBufferPtr))
#define MemIf_Cancel(DeviceIndex) Fee_Cancel()
#define MemIf_GetStatus(DeviceIndex) Fee_GetStatus()
#define MemIf_GetJobResult(DeviceIndex) Fee_GetJobResult()
#define MemIf_InvalidateBlock(DeviceIndex, BlockNumber) Fee_InvalidateBlock((BlockNumber))
#define MemIf_EraseImmediateBlock(DeviceIndex, BlockNumber)                                      \
    Fee_EraseImmediateBlock((BlockNumber))

#if MEMIF_VERSION_INFO_API
void MemIf_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MEMIF_H */
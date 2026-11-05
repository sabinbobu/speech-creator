#ifndef NVM_H
#define NVM_H

#include "NvM_Types.h"
#include "NvM_Cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void NvM_Init(const NvM_ConfigType *ConfigPtr);
    Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId,
                                      NvM_RequestResultType *RequestResultPtr);
#if NVM_CFG_VERSION_INFO_API
    void NvM_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif
#if NVM_CFG_SET_RAM_BLOCK_STATUS_API
    Std_ReturnType NvM_SetRamBlockStatus(NvM_BlockIdType BlockId, boolean BlockChanged);
#endif
    Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, void *NvM_DstPtr);
    Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, const void *NvM_SrcPtr);
    Std_ReturnType NvM_RestoreBlockDefaults(NvM_BlockIdType BlockId, void *NvM_DestPtr);
    void NvM_ReadAll(void);
    void NvM_WriteAll(void);
    void NvM_CancelWriteAll(void);

#ifdef __cplusplus
}
#endif

#endif /* NVM_H */
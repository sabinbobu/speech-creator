#ifndef NVM_EXTERNALS_H
#define NVM_EXTERNALS_H

/* Application/external callbacks used by NvM. */
#include "NvM.h"

#ifdef __cplusplus
extern "C"
{
#endif

    Std_ReturnType NvM_SingleBlockCallbackFunction(NvM_BlockRequestType BlockRequest,
                                                   NvM_RequestResultType JobResult);
    Std_ReturnType NvM_MultiBlockCallbackFunction(NvM_MultiBlockRequestType MultiBlockRequest,
                                                  NvM_RequestResultType JobResult);
    Std_ReturnType NvM_InitBlockCallbackFunction(NvM_InitBlockRequestType InitBlockRequest);

#ifdef __cplusplus
}
#endif

#endif /* NVM_EXTERNALS_H */
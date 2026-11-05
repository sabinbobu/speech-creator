#ifndef SCHM_NVM_H
#define SCHM_NVM_H

/* NvM scheduled function. */
#include "NvM.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void NvM_MainFunction(void);
    void SchM_Enter_NvM(void);
    void SchM_Exit_NvM(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHM_NVM_H */
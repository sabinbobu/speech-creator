#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

#include "Std_Types.h"

typedef enum
{
    MEMIF_UNINIT = 0U,
    MEMIF_IDLE,
    MEMIF_BUSY,
    MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

typedef enum
{
    MEMIF_JOB_OK = 0U,
    MEMIF_JOB_FAILED,
    MEMIF_JOB_PENDING,
    MEMIF_JOB_CANCELED,
    MEMIF_BLOCK_INCONSISTENT,
    MEMIF_BLOCK_INVALID
} MemIf_JobResultType;

typedef enum
{
    MEMIF_MODE_SLOW = 0U,
    MEMIF_MODE_FAST
} MemIf_ModeType;

#endif /* MEMIF_TYPES_H */
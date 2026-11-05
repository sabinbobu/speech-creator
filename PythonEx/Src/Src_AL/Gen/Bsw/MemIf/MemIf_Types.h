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
/// \file   MemIf_Types.h
///
/// \brief  Types for the status of the memory abstraction interface 
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


/*---- Protection against multiple inclusion -------------------------------*/
#if !defined MEM_IF_TYPES_2021_03_31_H_
#define MEM_IF_TYPES_2021_03_31_H_

#include <Std_Types.h>


/*---- API Type definitions ------------------------------------------------*/

/* A memory hardware abstraction module's state is denoted in 
 * this type. Mainly used in MemIf_GetStatus and related 
 * APIs of memory hardware abstraction modules.
 */
typedef enum
{
    MEMIF_UNINIT = 0,
    MEMIF_IDLE,
    MEMIF_BUSY,
    MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

/* A requested job can have one these values after it has been
 * processed. Use in MemIf_GetJobResult and related memory 
 * hardware abstraction module APIs. 
 */
typedef enum
{
    MEMIF_JOB_OK = 0,
    MEMIF_JOB_FAILED,
    MEMIF_JOB_PENDING,
    MEMIF_JOB_CANCELLED,
    MEMIF_BLOCK_INCONSISTENT,
    MEMIF_BLOCK_INVALID
} MemIf_JobResultType;


/* Specifies the processing speed of requested jobs. The exact 
 * processing duration in the different modes depends on 
 * configuration of the underlying memory hardware abstraction 
 * modules.   
 */
typedef enum
{
    MEMIF_MODE_SLOW = 0,
    MEMIF_MODE_FAST
} MemIf_ModeType;


/*--------------------------------------------------------------------------*/

#endif // MEM_IF_TYPES_2021_03_31_H_

/*---- End of File ---------------------------------------------------------*/

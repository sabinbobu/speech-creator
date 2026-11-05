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
/// \file  MemIf_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------



#if (!defined MEM_IF_CFG_2021_03_31_H_)    /* Multiple inclusion protection viewed from MemIf.h */
#define MEM_IF_CFG_2021_03_31_H_



/*---- API CFG Defines -----------------------------------------------------*/

#define MEMIF_NUMBER_OF_DEVICES     (1u)

/* Logical Device Names */
#define MEMIF_Fee (0u)

#define MEMIF_VERSION_INFO_API  (STD_ON)
#define MEMIF_CFG_USE_FCT_API   (STD_ON)

/* ------------------------------------------------------------------------ */
/*              Configurations for Development mode                         */
/*                             */
/* ------------------------------------------------------------------------ */
/* preprocessor switch for DET */


/*---- API CFG Macros ------------------------------------------------------*/

/*---- API CFG Type definitions --------------------------------------------*/
/* type definitions for referencing APIs of underlying
 * memory hardware abstraction modules
 */

#if 0
typedef P2FUNC (void, MEMIF_CODE, MemIf_ApiSetModeType)
            (
                MemIf_ModeType      Mode
            );
typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiReadType)
            (
                uint16              BlockNumber,
                uint16              BlockOffset,
                MemIf_DataPtr_pu8   DataBufferPtr,
                uint16              Length
            );
typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiWriteType)
            (
                uint16              BlockNumber,
                MemIf_DataPtr_pu8   DataBufferPtr
            );

typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiEraseImmediateBlockType)
            (
                uint16              BlockNumber
            );

typedef P2FUNC (Std_ReturnType, MEMIF_CODE, MemIf_ApiInvalidateBlockType)
            (
                uint16              BlockNumber
            );

typedef P2FUNC (void, MEMIF_CODE, MemIf_ApiCancelType)
            (
                void
            );
typedef P2FUNC (MemIf_StatusType, MEMIF_CODE, MemIf_ApiGetStatusType)
            (
                void
            );
typedef P2FUNC (MemIf_JobResultType, MEMIF_CODE, MemIf_ApiGetJobResultType)
            (
                void
            );

#endif
/*---- Include of the MemHwAs ---------------------------*/
#ifndef UNIT_TEST
#include <Fee.h>
#else
#include <Fee_TargetTypes.h>
#include <Fee.h>
#endif


/*---- API CFG Structures --------------------------------------------------*/

/*---- API CFG Constants ---------------------------------------------------*/

    /* mapping of MemIf_Read() */
    #define MemIf_Read(DeviceIndex, BlockNumber, BlockOffset, DataBufferPtr, Length) \
                    Fee_Read( \
                        (BlockNumber), \
                        (BlockOffset), \
                        (DataBufferPtr), \
                        (Length))

    /* mapping of MemIf_EraseImmediateBlock() */
    #define MemIf_EraseImmediateBlock(DeviceIndex, BlockNumber) \
                Fee_EraseImmediateBlock(BlockNumber)

    /* mapping of MemIf_InvalidateBlock() */
    #define MemIf_InvalidateBlock(DeviceIndex, BlockNumber) \
                Fee_InvalidateBlock(BlockNumber)

    /* mapping of MemIf_Write() */
    #define MemIf_Write(DeviceIndex, BlockNumber, DataBufferPtr) \
                Fee_Write(BlockNumber, DataBufferPtr)

    /* mapping of MemIf_Cancel() */
    #define MemIf_Cancel(DeviceIndex) \
                Fee_Cancel()

    /* mapping of MemIf_GetJobResult() */
    #define MemIf_GetJobResult(DeviceIndex) \
                Fee_GetJobResult()



#endif // MEM_IF_CFG_2021_03_31_H_

/*---- End of File ---------------------------------------------------------*/

//****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  AnimMa.c
///
/// \brief   Contains the logic to activate sequences
///
/// \author Sevastre Georgiana (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "AnimMa.h"
#include "AnimMa_Types.h"
#include "AnimMa_Blocks.h"
#include "AnimMa_Cod.h"
#include <Std_Types.h>

#if defined(UNIT_TEST)
#ifdef STATIC_AL
#undef STATIC_AL
#endif
#define STATIC_AL

#ifdef AM_INLINE
#undef AM_INLINE
#endif
#define AM_INLINE

#define bool           boolean
#define true           TRUE
#define false          FALSE

#endif


STATIC_AL uint32 AnimMa_FindSequence(teRte_ExtLightingAnimationReq ucSeqId);
/// Invalid sequence ID
#define ANIMMA_INVALID_SEQ_ID           255u

/// Number of currently active sequences (must be less than or equal to ANIMMA_NR_SEQUENCES)
STATIC_AL uint8 AnimMa_ucActiveSeqCnt;

/// IDs of active sequences
tActiveSequence AnimMa_aActiveSeq[ANIMMA_NR_SEQUENCES];

///mounting side init
STATIC_AL uint8 AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_INIT;

//-----------------------------------------------------------------------------
/// Return the index for AnimMa_pCodingData (byte stream) where the sequence with id ucSeqId starts.
/// Returns 0 if the sequence was not found.
//-----------------------------------------------------------------------------
tCodIdxL AnimMa_Cod_GetSequenceIdx(teRte_ExtLightingAnimationReq eSeqId)
{
    tCodIdxL       i;
    const tCodIdxL unLastDictIdx = AnimMa_Cod_GetFirstSequenceIdx();
    tCodIdxL       unIdx = 0;

    for (i = AnimMa_Cod_GetDictFirstEntryIdx(); i < unLastDictIdx; i += ANIMMA_COD_BYTES_SEQ_ENTRY)
    {
        if ((uint8)eSeqId == AnimMa_Cod_GetCodingData()[i])
        {
            unIdx += unLastDictIdx;
            break;
        }
        // MSB first
        unIdx += AnimMa_Cod_MakeIdx((uint8)AnimMa_Cod_GetCodingData()[i + 1U], (uint8)AnimMa_Cod_GetCodingData()[i + 2U]);
    }

    if (i == unLastDictIdx)
    {
        // no match: return 0
        unIdx = 0;
    }

    return (uint16)unIdx;
}

//-----------------------------------------------------------------------------
/// get the number of pixels that is used for the current active sequence(s)
//-----------------------------------------------------------------------------
sint32 AnimMa_GetPxlNr(void)
{
    return ANIMMA_NR_PIXELS;
}

//-----------------------------------------------------------------------------
/// Return true if the coding data are valid
//-----------------------------------------------------------------------------
STATIC_AL bool AnimMa_isCodingValid(void)
{
    return AnimMa_pCodingData != NULL_PTR;
}

//-----------------------------------------------------------------------------
/// Elapsed time calculation find sequence
//-----------------------------------------------------------------------------
STATIC_AL uint32 AnimMa_FindSequence(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 i;

    for (i = 0u; i < AnimMa_ucActiveSeqCnt; i++)
    {
        if (AnimMa_aActiveSeq[i].ucSeqId == ucSeqId)
        {
            break;
        }
    }
    return i;
}

//-----------------------------------------------------------------------------
/// Elapsed time calculation check validity
//-----------------------------------------------------------------------------
#ifndef UNIT_TEST
STATIC_AL inline bool AnimMa_IsIdxValid(uint32 ulIdx)
#else
STATIC_AL bool AnimMa_IsIdxValid(uint32 ulIdx)
#endif
{
    return ulIdx < AnimMa_ucActiveSeqCnt;
}
//-----------------------------------------------------------------------------
/// Return true if the sequence is currently active
//-----------------------------------------------------------------------------
bool AnimMa_isSequenceActive(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 i;

    for (i = 0u; i < AnimMa_ucActiveSeqCnt; i++)
    {
        if (AnimMa_aActiveSeq[i].ucSeqId == ucSeqId)
        {
            break;
        }
    }

    return (i == AnimMa_ucActiveSeqCnt) ? false : true;
}

//-----------------------------------------------------------------------------
/// Return true if the sequence is currently active
//-----------------------------------------------------------------------------
bool AnimMa_isStopSequenceActive(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 i;

    for (i = 0u; i < AnimMa_ucActiveSeqCnt; i++)
    {
        if ((AnimMa_aActiveSeq[i].ucSeqId == ucSeqId)
            && (AnimMa_aActiveSeq[i].unStopBlocks != 0u)
            && (AnimMa_aActiveSeq[i].unSeqStatus == StopSeqRun))

        {
            break;
        }
    }

    return (i == AnimMa_ucActiveSeqCnt) ? false : true;
}

//-----------------------------------------------------------------------------
/// Return true if the sequence with Stop Blocks inside is in the running phase
//-----------------------------------------------------------------------------
bool AnimMa_isSeqActivePhase_WithNoRunningIDs(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 i;

    for (i = 0u; i < AnimMa_ucActiveSeqCnt; i++)
    {
        const tCodIdxL unSeqCodIdx = AnimMa_aActiveSeq[i].unSeqCodIdx;
        uint32 unNrBlks = AnimMa_Cod_GetNrBlocks(unSeqCodIdx);

        if ((AnimMa_aActiveSeq[i].ucSeqId == ucSeqId)
            && (AnimMa_aActiveSeq[i].unStopBlocks == unNrBlks)
            && (AnimMa_aActiveSeq[i].unSeqStatus == ActiveSeqRun))

        {
            break;
        }
    }

    return (i == AnimMa_ucActiveSeqCnt) ? false : true;
}

//-----------------------------------------------------------------------------
/// Return true if the index ucIdx is a valid index into the coding data
//-----------------------------------------------------------------------------
STATIC_AL bool AnimMa_isSeqCodIdxValid(uint16 unIdx)
{
    return unIdx > (uint16)0u;
}

//-----------------------------------------------------------------------------
/// tick for sequence nSeq; nSeq is index for AnimMa_aActiveSeq.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcSequence(uint32 nSeq)
{
    const tCodIdxL unSeqCodIdx = AnimMa_aActiveSeq[nSeq].unSeqCodIdx;
    uint32         ulBlkId;
    uint32         ulNrBlks = AnimMa_Cod_GetNrBlocks(unSeqCodIdx);
    uint32         ulActiveBlkId = AnimMa_aActiveSeq[nSeq].ucBlkFstIdx;
    uint8          ucRunStop = (uint8)AnimMa_aActiveSeq[nSeq].unSeqStatus;

    AnimMa_InitAtSequenceStart();
    for (ulBlkId = 0; ulBlkId < ulNrBlks; ulBlkId++)
    {
        if (ucRunStop == (uint8)ActiveSeqRun)  // Run normal block
        {
            AnimMa_rcBlock(ulActiveBlkId, AnimMa_aActiveSeq[nSeq].ulTime, AnimMa_ucMountingSide);
        }
        else if (ucRunStop == (uint8)StopSeqRun) // Run stop block 
        {
            bool bBlockStop = AnimMa_rcStopBlock(ulActiveBlkId, AnimMa_aActiveSeq[nSeq].ulTime, AnimMa_ucMountingSide);
            // Each time when the stop blocks runs to the end, number of active stop blocks is reduced by 1.
            if (bBlockStop == true)
            {
                AnimMa_aActiveSeq[nSeq].unStopBlocks--;
            }
        }
        else
        {
            //do nothing
        }

        ulActiveBlkId++;
    }

    AnimMa_aActiveSeq[nSeq].ulTime += ANIMMA_CYCLE_TIME;
}

//-----------------------------------------------------------------------------
/// clear the sequence and its content , nSeq is index for AnimMa_aActiveSeq.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_clearSequence(uint32 nSeq)
{
    uint32 j;
    uint32 ulBlockNumber = AnimMa_Cod_GetNrBlocks(AnimMa_aActiveSeq[nSeq].unSeqCodIdx);

    AnimMa_DeleteBlocks(AnimMa_aActiveSeq[nSeq].ucBlkFstIdx, AnimMa_aActiveSeq[nSeq].unSeqCodIdx);
    AnimMa_aActiveSeq[nSeq].ucSeqId = eExtLightingAnimationReq_Invalid;
    for (j = nSeq + 1u; j < AnimMa_ucActiveSeqCnt; j++)
    {
        AnimMa_aActiveSeq[j - 1u].ucSeqId = AnimMa_aActiveSeq[j].ucSeqId;
        AnimMa_aActiveSeq[j - 1u].unSeqCodIdx = AnimMa_aActiveSeq[j].unSeqCodIdx;
        AnimMa_aActiveSeq[j - 1u].ulTime = AnimMa_aActiveSeq[j].ulTime;
        AnimMa_aActiveSeq[j - 1u].ucBlkFstIdx = AnimMa_aActiveSeq[j].ucBlkFstIdx - (uint8)ulBlockNumber;
        AnimMa_aActiveSeq[j - 1u].unSeqStatus = AnimMa_aActiveSeq[j].unSeqStatus;
        AnimMa_aActiveSeq[j - 1u].unStopBlocks = AnimMa_aActiveSeq[j].unStopBlocks;
    }
    AnimMa_ucActiveSeqCnt--;
}

//-----------------------------------------------------------------------------
/// set the current coding data
//-----------------------------------------------------------------------------
void AnimMa_setCodingData(const tNvmPara_CodingArea * pData)
{
    AnimMa_pCodingData = pData;
}

//-----------------------------------------------------------------------------
/// Start a sequence. Returns true if the sequence was not running and is started.
//-----------------------------------------------------------------------------
void AnimMa_startSequence(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint16 unCodIdx;

    if (AnimMa_isCodingValid())
    {
        if (AnimMa_ucActiveSeqCnt < ANIMMA_NR_SEQUENCES)
        {
            if (!AnimMa_isSequenceActive(ucSeqId))
            {
                unCodIdx = (uint16)AnimMa_Cod_GetSequenceIdx(ucSeqId);

                if (AnimMa_isSeqCodIdxValid(unCodIdx))
                {
                    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].unSeqCodIdx = unCodIdx;
                    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ucSeqId = ucSeqId;
                    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ulTime = 0;
                    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ucBlkFstIdx = AnimMa_AllocateBlocks(unCodIdx);
                    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].unSeqStatus = ActiveSeqRun;
                    AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].unStopBlocks = AnimMa_StopBlocksNr(unCodIdx);
                    AnimMa_ucActiveSeqCnt++;
                    AnimMa_InitAtSequenceStart();
                }
            }
        }
    }

}

//-----------------------------------------------------------------------------
/// [ms] Return elapsed time in miliseconds. If sequence ucSeqId is not active, return 0xFFFFFF
//-----------------------------------------------------------------------------
uint32 AnimMa_getElapsedTime(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 ulIdx;
    uint32 ulTime;
    ulIdx = AnimMa_FindSequence(ucSeqId);
    if (AnimMa_IsIdxValid(ulIdx))
    {
        ulTime = AnimMa_aActiveSeq[AnimMa_ucActiveSeqCnt].ulTime;
    }
    else
    {
        ulTime = 0xFFFFFF;
    }
    return ulTime;
}

//-----------------------------------------------------------------------------
/// Start a sequence. 
//-----------------------------------------------------------------------------
void AnimMa_stopSequence(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 i;
    // remove from the list of active sequences and flatten the list of active sequences (no holes)
    for (i = 0; i < AnimMa_ucActiveSeqCnt; i++)
    {
        if (AnimMa_aActiveSeq[i].ucSeqId == ucSeqId)
        {
            AnimMa_clearSequence(i);
            AnimMa_InitAtSequenceStart();
            break;
        }
    }
}

//-----------------------------------------------------------------------------
/// Stop a sequence by running all the stop blocks for the defined time between tStart and tStop
//-----------------------------------------------------------------------------
void AnimMa_softStopSequence(teRte_ExtLightingAnimationReq ucSeqId)
{
    uint32 i;

    // remove from the list of active sequences and flatten the list of active sequences (no holes)
    for (i = 0; i < AnimMa_ucActiveSeqCnt; i++)
    {
        if (AnimMa_aActiveSeq[i].ucSeqId == ucSeqId)
        {
            if (AnimMa_aActiveSeq[i].unStopBlocks != 0U)  // THere is stop block in the sequence
            {
                if (AnimMa_aActiveSeq[i].unSeqStatus == ActiveSeqRun) // 1. Reset the sequence time; 2. Initialize the stop block content. 
                {
                    AnimMa_aActiveSeq[i].ulTime = 0u;
                    AnimMa_InitBlocksContent(AnimMa_aActiveSeq[i].ucBlkFstIdx, AnimMa_aActiveSeq[i].unSeqCodIdx);
                }

                AnimMa_aActiveSeq[i].unSeqStatus = StopSeqRun;
            }
            else  // There is no stop block any more in the sequence, delete the sequence
            {
                AnimMa_clearSequence(i);
                break;
            }
        }
    }
}

//-----------------------------------------------------------------------------
/// Return the number of active sequneces
//-----------------------------------------------------------------------------
uint8 AnimMa_ActiveSeqNr(void)
{
    return AnimMa_ucActiveSeqCnt;
}

//-----------------------------------------------------------------------------
/// Set the applicable mounting side of the AnimMa block
//-----------------------------------------------------------------------------
void AnimMa_setMountingSide(uint8 ucMountingSide)
{
    AnimMa_ucMountingSide = ucMountingSide;
}

//-----------------------------------------------------------------------------
/// Return the applicable mounting side in the AnimMa Block
//-----------------------------------------------------------------------------
uint8 AnimMa_getMountSide(void)
{
    return AnimMa_ucMountingSide;
}

//-----------------------------------------------------------------------------
/// initialize at startup
//-----------------------------------------------------------------------------
void rcAnimMaInit(void)
{
    uint32 i;

    AnimMa_ucActiveSeqCnt = 0;
    AnimMa_ucMountingSide = ANIMMA_MOUNTINGSIDE_INIT;

    for (i = 0U; i < ANIMMA_NR_SEQUENCES; i++)
    {
        AnimMa_aActiveSeq[i].ucSeqId = eExtLightingAnimationReq_Invalid;
        AnimMa_aActiveSeq[i].unSeqCodIdx = 0;
        AnimMa_aActiveSeq[i].ulTime = 0;
        AnimMa_aActiveSeq[i].ucBlkFstIdx = 0;
        AnimMa_aActiveSeq[i].unSeqStatus = Inactive;
        AnimMa_aActiveSeq[i].unStopBlocks = 0;
    }
}

//-----------------------------------------------------------------------------
/// runable for updates
//-----------------------------------------------------------------------------
void rcAnimMa50(void)
{
    uint32 i;

    if (AnimMa_isCodingValid())
    {
        for (uint8 j = 0U; j < (uint8)ANIMMA_NR_PIXELS; j++)
        {
            AnimMaRamp_aucPxlIntTgt[j] = 0;
        }

        for (i = 0u; i < AnimMa_ucActiveSeqCnt; i++)
        {

            AnimMa_rcSequence(i);

            // when the Stop sequence is finished, clear the memory as well, i is unActiveSeqId
            if ((AnimMa_aActiveSeq[i].unStopBlocks == 0u) && (AnimMa_aActiveSeq[i].unSeqStatus == StopSeqRun))
            {
                AnimMa_clearSequence(i);
                break;
            }
        }
    }
}
// EOF

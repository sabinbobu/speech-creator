//-----------------------------------------------------------------------------
/// Animation Master, definition of blocks
//-----------------------------------------------------------------------------
// PRQA S 316 EOF

#include "AnimMa.h"
#include "AnimMa_Types.h"
#include "AnimMa_Blocks.h"
#include "AnimMa_Cod.h"

#if defined(GOOGLE_TEST) || defined(UNIT_TEST)
#ifdef STATIC_AL
#undef STATIC_AL
#endif
#define STATIC_AL

#ifdef AM_INLINE
#undef AM_INLINE
#endif
#define AM_INLINE
#endif

/// Resolution to calculate dim ramps
#define ANIMMA_RAMP_RESOLUTION 4096U
#define ANIMMA_PATTERN_MAX_VALUE 100U //the max value of the pattern

//=============================================================================
// Start definitions of uninitialzied 32 bit variables
//=============================================================================
/// Number of blocks that are currently allocated (index to AnimMa_aActiveBlocks)
STATIC_AL uint32 AnimMa_unActiveBlocksCnt;

/// Array of blocks that are currently allocated
tActiveBlock AnimMa_aActiveBlocks[ANIMMA_NR_BLOCKS];

/// Number of run10 block contexts that are currently allocated (index to AnimMa_aActiveBlocksRun10)
STATIC_AL uint32 AnimMa_unActiveBlocksRun10Cnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksRun10Cnt;
/// Array of run10 block contexts that are currently allocated
tActiveBlockRun10 AnimMa_aActiveBlocksRun10[ANIMMA_NR_BLOCKS_RUN10];

/// Number of runN block contexts that are currently allocated (index to AnimMa_aActiveBlocksRunN)
STATIC_AL uint32 AnimMa_unActiveBlocksRunNCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksRunNCnt;
/// Array of runN block contexts that are currently allocated
tActiveBlockRunN AnimMa_aActiveBlocksRunN[ANIMMA_NR_BLOCKS_RUNN];

/// Number of SparkleLfsr block contexts that are currently allocated (index to AnimMa_aActiveBlocksSparkleLfsr)
STATIC_AL uint32 AnimMa_unActiveBlocksSparkleLfsrCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksSparkleLfsrCnt;
/// Array of SparkleLfsr block contexts that are currently allocated
tActiveBlockSparkleLfsr AnimMa_aActiveBlocksSparkleLfsr[ANIMMA_NR_BLOCKS_SPARKLE_LFSR];

/// Number of SparkleXor64 block contexts that are currently allocated (index to AnimMa_aActiveBlocksSparkleXor64)
STATIC_AL uint32 AnimMa_unActiveBlocksSparkleXor64Cnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksSparkleXor64Cnt;
/// Array of SparkleXor64 block contexts that are currently allocated
tActiveBlockSparkleXor64 AnimMa_aActiveBlocksSparkleXor64[ANIMMA_NR_BLOCKS_SPARKLE_XOR64];

/// Number of Blink block contexts that are currently allocated (index to AnimMa_aActiveBlocksBlink)
STATIC_AL uint32 AnimMa_unActiveBlocksBlinkCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksBlinkCnt;

// Number of dimming blocks
STATIC_AL uint32 AnimMa_unActiveBlocksClampCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksClampCnt;

// Number of invert blocks
STATIC_AL uint32 AnimMa_unActiveBlocksInvertCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksInvertCnt;

/// Array of Flex block contexts that can be allocated
STATIC_AL uint32 AnimMa_unActiveBlocksFlexCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksFlexCnt;
tActiveBlockFlex AnimMa_aActiveBlocksFlex[ANIMMA_NR_BLOCKS_FLEX];

// Number of invert blocks
STATIC_AL uint32 AnimMa_unActiveBlocksSpeedAssignCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksSpeedAssignCnt;

/// Number of PiecewiseLinear block contexts that are currently allocated (index to AnimMa_aActiveBlocksPiecewiseLinear)
STATIC_AL uint32 AnimMa_unActiveBlocksPiecewiseLinearCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksPiecewiseLinearCnt;
tActiveBlockPiecewiseLinear AnimMa_aActiveBlocksPiecewiseLinear[ANIMMA_NR_BLOCKS_PIECEWISELINEAR];

// Number of InvertIntensity blocks
STATIC_AL uint32 AnimMa_unActiveBlocksInvertIntensityCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksInvertIntensityCnt;

/// Number of Repetition block contexts that are currently allocated (index to AnimMa_aActiveBlocksRepetition)
STATIC_AL uint32 AnimMa_unActiveBlocksRepetitionCnt;
STATIC_AL uint32 AnimMa_unDeactivateBlocksRepetitionCnt;
tActiveBlockRepetition AnimMa_aActiveBlocksRepetition[ANIMMA_NR_BLOCKS_REPETITION];

/// Number of Repetition blocks that can be running concurrently (defines stack size)
#define ANIMMA_MAX_NR_NESTED_REPETITIONS ANIMMA_NR_BLOCKS_REPETITION

/// Elements of the Repetition block stack
typedef struct
{
    uint32 ulTimeOffset; ///< [ms] time offset for the Repetition block
    uint8 ucRepBlkCntDn;   ///< Number of blocks that the Repetition block works on (modifies), count down value
} tAnimMa_Repetition;

/// Stack for concurrent Repetition blocks
typedef struct
{
    tAnimMa_Repetition aValues[ANIMMA_MAX_NR_NESTED_REPETITIONS];
    uint8 ucCnt; ///< Next free index into aValues = number of concurrent Repetition blocks; 0 <= ucCnt <= ANIMMA_MAX_NR_NESTED_REPETITIONS
} tAnimMa_RepetitionStack;

/// store state of time modifications (modified by e.g. TimeOffset block)
STATIC_AL struct
{
    uint32 ulTimeOffset;    ///< [ms] time offset that is applied to Tstart and Tend.
    uint32 ulTimeOffsetRepetition; ///< [ms] time offset that is applied to Tstart and Tend.
    tAnimMa_RepetitionStack RepetitionStack; ///< Stack for concurrent repetitions
    bool bInitContext;      ///< true = initialize context of blocks
    uint8 ucInitContextCnt; ///< count down: number of block context initializations
} sTimeWarp;

/// function type for block execution
typedef void(*tAnimMa_rcFuncType)(uint32 ulActiveBlkId, uint32 ulTime);

/// [%] Array of target intensities
uint8 AnimMaRamp_aucPxlIntTgt[ANIMMA_NR_PIXELS];
/// [%] Array of target increments
uint8 AnimMaRamp_aucPxlIntInc[ANIMMA_NR_PIXELS];
/// [%] Array of target decrements
uint8 AnimMaRamp_aucPxlIntDec[ANIMMA_NR_PIXELS];


STATIC_AL CONST_AL uint8 * AnimMa_Cod_GetBlockSpecific(tCodIdxL unBlkIdx) { return &(AnimMa_Cod_GetCodingData()[unBlkIdx]); }
STATIC_AL void AnimMa_Ramp_Init(const uint32 dt, const uint32 y1, const uint32 y2, const uint32 timestep, tStepRamp * pRamp);
STATIC_AL void AnimMa_Ramp_UpdateDelta(const uint32 dt, const uint32 y1, const uint32 y2, const uint32 timestep, tStepRamp * pRamp);
STATIC_AL void AnimMa_Ramp_Step(tStepRamp * pRamp);
STATIC_AL void AnimMa_PiecewiseLinear_InitRamp(uint32 ulIdx, const tBlockSpecificPiecewiseLinear * pCodSpc, tStepRamp * pRamp);
STATIC_AL void AnimMa_InitBlockContext(uint32 ulActiveBlkId);
STATIC_AL void AnimMa_InitContext(uint32 ulActiveBlkId);

//-----------------------------------------------------------------------------
/// Initializes all data structures (for example, at start up)
//-----------------------------------------------------------------------------
void AnimMa_Blocks_Init(void)
{
    AnimMa_unActiveBlocksCnt = 0U;
    AnimMa_unActiveBlocksRun10Cnt = 0U;
    AnimMa_unDeactivateBlocksRun10Cnt = 0U;
    AnimMa_unActiveBlocksRunNCnt = 0U;
    AnimMa_unDeactivateBlocksRunNCnt = 0U;
    AnimMa_unActiveBlocksSparkleLfsrCnt = 0U;
    AnimMa_unDeactivateBlocksSparkleLfsrCnt = 0U;
    AnimMa_unActiveBlocksSparkleXor64Cnt = 0U;
    AnimMa_unDeactivateBlocksSparkleXor64Cnt = 0U;
    AnimMa_unActiveBlocksBlinkCnt = 0U;
    AnimMa_unDeactivateBlocksBlinkCnt = 0U;
    AnimMa_unActiveBlocksClampCnt = 0U;
    AnimMa_unDeactivateBlocksClampCnt = 0U;
    AnimMa_unActiveBlocksInvertCnt = 0U;
    AnimMa_unDeactivateBlocksInvertCnt = 0U;
    AnimMa_unActiveBlocksFlexCnt = 0U;
    AnimMa_unDeactivateBlocksFlexCnt = 0U;
    AnimMa_unActiveBlocksSpeedAssignCnt = 0U;
    AnimMa_unDeactivateBlocksSpeedAssignCnt = 0U;
    AnimMa_unActiveBlocksPiecewiseLinearCnt = 0U;
    AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 0U;
    AnimMa_unActiveBlocksInvertIntensityCnt = 0U;
    AnimMa_unDeactivateBlocksInvertIntensityCnt = 0U;
    AnimMa_unActiveBlocksRepetitionCnt = 0U;
    AnimMa_unDeactivateBlocksRepetitionCnt = 0U;

    AnimMa_InitAtSequenceStart();
}

//-----------------------------------------------------------------------------
/// initializes internal data before the first block of a sequence is executed
//-----------------------------------------------------------------------------
void AnimMa_InitAtSequenceStart(void)
{
    sTimeWarp.ulTimeOffset = 0U;
    sTimeWarp.bInitContext = false;
    sTimeWarp.ucInitContextCnt = 0U;
    sTimeWarp.ulTimeOffsetRepetition = 0U;
    sTimeWarp.RepetitionStack.ucCnt = 0U;
}

//-----------------------------------------------------------------------------
/// Returns a modified time: adds offsets from block TimeOffset and block Repetition.
/// Used to manipulate TStart and TEnd.
//-----------------------------------------------------------------------------
STATIC_AL uint32 AnimMa_TimeWarp(uint32 unTime)
{
    return unTime + ((uint32)sTimeWarp.ulTimeOffset + (uint32)sTimeWarp.ulTimeOffsetRepetition);
}

//-----------------------------------------------------------------------------
/// Push unTime and ucBlockCnt to Repetition stack. Update sTimeWarp.unTimeOffsetRepetition.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_RepetitionStack_Push(const uint32 unTime, const uint8 ucBlockCnt)
{
    const uint32 unIdx = sTimeWarp.RepetitionStack.ucCnt;

    if (unIdx < (uint32)ANIMMA_MAX_NR_NESTED_REPETITIONS)
    {
        sTimeWarp.RepetitionStack.aValues[unIdx].ulTimeOffset = unTime;
        sTimeWarp.RepetitionStack.aValues[unIdx].ucRepBlkCntDn = ucBlockCnt;
        sTimeWarp.ulTimeOffsetRepetition += unTime;
        sTimeWarp.RepetitionStack.ucCnt++;
    }
}

//-----------------------------------------------------------------------------
/// Pop last value from Repetition stack. Update sTimeWarp.unTimeOffsetRepetition.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_RepetitionStack_Pop(void)
{
    const uint32 unIdx = sTimeWarp.RepetitionStack.ucCnt;

    if (unIdx > 0U)
    {
        sTimeWarp.ulTimeOffsetRepetition -= sTimeWarp.RepetitionStack.aValues[unIdx - 1U].ulTimeOffset;
        sTimeWarp.RepetitionStack.ucCnt--;
    }
}

//-----------------------------------------------------------------------------
/// Update the Repetition stack: pop (remove) an element if its (number of) blocks have been executed
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_UpdateRepetition(void)
{
    bool bPopAllowed = true;
    uint8 i = sTimeWarp.RepetitionStack.ucCnt;

    // search through stack from last element to first element
    while ((uint32)i > 0U)
    {
        i--;

        if (sTimeWarp.RepetitionStack.aValues[i].ucRepBlkCntDn > 0U)
        {
            sTimeWarp.RepetitionStack.aValues[i].ucRepBlkCntDn--;
            bPopAllowed = false;
        }
        else
        {
            if (bPopAllowed)
            {
                AnimMa_RepetitionStack_Pop();
            }
        }
    }
}

//-----------------------------------------------------------------------------
/// Enable initializations of block contexts such that next ucNr calls to rcBlock will initialize block contexts.
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE void AnimMa_EnableInitContext(uint8 ucNr)
{
    sTimeWarp.bInitContext = true;
    sTimeWarp.ucInitContextCnt = (sTimeWarp.ucInitContextCnt > ucNr) ? (sTimeWarp.ucInitContextCnt) : (ucNr);
}

//-----------------------------------------------------------------------------
/// Calls AnimMa_InitBlockContext() if required by time warp.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_InitContext(uint32 ulActiveBlkId)
{
    if (sTimeWarp.bInitContext)
    {
        if (sTimeWarp.ucInitContextCnt > (uint8)0)
        {
            AnimMa_InitBlockContext(ulActiveBlkId);
            sTimeWarp.ucInitContextCnt--;
        }
        else
        {
            sTimeWarp.bInitContext = false;
        }
    }
}

//-----------------------------------------------------------------------------
/// convenient function: access to array of target intensities
//-----------------------------------------------------------------------------
const uint8 * AnimMa_GetPxlTgt(void)
{
    return &(AnimMaRamp_aucPxlIntTgt[0]);
}

//-----------------------------------------------------------------------------
/// convenient function: access to array of target increments
//-----------------------------------------------------------------------------
const uint8 * AnimMa_GetPxlInc(void)
{
    return &(AnimMaRamp_aucPxlIntInc[0]);
}

//-----------------------------------------------------------------------------
/// convenient function: access to array of target decrements
//-----------------------------------------------------------------------------
const uint8 * AnimMa_GetPxlDec(void)
{
    return &(AnimMaRamp_aucPxlIntDec[0]);
}

//-----------------------------------------------------------------------------
/// Return smallest uint8 that is greater than ucDividend / ucDivisor
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE uint8 AnimMa_CeilU8(const uint8 ucDividend, const uint8 ucDivisor)
{
    return (uint8)(((uint32)ucDividend + ((uint32)ucDivisor - 1u)) / (uint32)ucDivisor);
}

//-----------------------------------------------------------------------------
/// Return scaled parameter (high resolution)
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE uint32 Ramp_Phys2HighRes(uint32 ulParam)
{
    return ANIMMA_RAMP_RESOLUTION * ulParam;
}

//-----------------------------------------------------------------------------
/// Return none-scaled parameter (low resolution)
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE uint8 Ramp_HighRes2Param(uint32 ulValue)
{
    return (uint8)(ulValue / ANIMMA_RAMP_RESOLUTION);
}

//-----------------------------------------------------------------------------
/// Initialize ramp structure: ramp starts at y1 and reaches y2 after time dt with step size defined by dt and timestep.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_Ramp_Init(const uint32 dt, const uint32 y1, const uint32 y2, const uint32 timestep, tStepRamp * pRamp)
{
    pRamp->ulCur = y1;
    pRamp->ulTgt = y2;
    AnimMa_Ramp_UpdateDelta(dt, y1, y2, timestep, pRamp);
}

//-----------------------------------------------------------------------------
/// Returns smallest uint32 that is greater than (dividend1 * dividend2) / divisor.
//-----------------------------------------------------------------------------
STATIC_AL uint32 muldiv32_ceil(uint32 dividend1, uint32 dividend2, uint32 divisor)
{
    uint64 t = (uint64)dividend1 * (uint64)dividend2;
    t += (uint64)divisor - (uint64)1u;
    t /= (uint64)divisor;
    return (uint32)t;
}

//-----------------------------------------------------------------------------
/// Initialize ramp structure: ramp starts at y1 and reaches y2 after time dt with step size defined by dt and timestep.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_Ramp_UpdateDelta(const uint32 dt, const uint32 y1, const uint32 y2, const uint32 timestep, tStepRamp * pRamp)
{
    if (dt > 0u)
    {
        uint32 dy;

        if (y2 > y1)
        {
            dy = y2 - y1;
        }
        else
        {
            dy = y1 - y2;
        }

        pRamp->ulDelta = muldiv32_ceil(dy, timestep, dt);
    }
    else
    {
        pRamp->ulDelta = 0u;
    }
}

//-----------------------------------------------------------------------------
/// Update ramp, single step. Change current value towards target value.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_Ramp_Step(tStepRamp * pRamp)
{
    if (pRamp->ulTgt > pRamp->ulCur)
    {
        if ((pRamp->ulTgt - pRamp->ulCur) > (pRamp->ulDelta))
        {
            pRamp->ulCur += pRamp->ulDelta;
        }
        else
        {
            pRamp->ulCur = pRamp->ulTgt;
        }
    }
    else if (pRamp->ulCur > pRamp->ulTgt)
    {
        if ((pRamp->ulCur - pRamp->ulTgt) > (pRamp->ulDelta))
        {
            pRamp->ulCur -= pRamp->ulDelta;
        }
        else
        {
            pRamp->ulCur = pRamp->ulTgt;
        }
    }
    else
    {
        // intentionally left blank (current value is at target value)
    }
}

//-----------------------------------------------------------------------------
/// Initialize ramp from array element with index unIdx from pCodSpc.
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_PiecewiseLinear_InitRamp(uint32 ulIdx, const tBlockSpecificPiecewiseLinear * pCodSpc, tStepRamp * pRamp)
{
    if (pCodSpc->ucN > (uint8)0)
    {
        if (ulIdx < (uint32)pCodSpc->ucN)
        {
            const uint32 dt = Ramp_Phys2HighRes(AnimMa_Cod_Param2Ms(AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Time(pCodSpc, ulIdx)));
            const uint32 y1 = (ulIdx == 0u) ? Ramp_Phys2HighRes(pCodSpc->ucInitI) : Ramp_Phys2HighRes(AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Intensity(pCodSpc, ulIdx - 1u));
            const uint32 y2 = Ramp_Phys2HighRes(AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Intensity(pCodSpc, ulIdx));
            AnimMa_Ramp_Init(dt, y1, y2, Ramp_Phys2HighRes(ANIMMA_CYCLE_TIME), pRamp);
        }
        else
        {
            const uint32 y = Ramp_Phys2HighRes(AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Intensity(pCodSpc, (uint32)pCodSpc->ucN - 1u));
            AnimMa_Ramp_Init(0, y, y, Ramp_Phys2HighRes(ANIMMA_CYCLE_TIME), pRamp);
        }
    }
    else
    {
        const uint32 y = Ramp_Phys2HighRes(pCodSpc->ucInitI);
        AnimMa_Ramp_Init(0, y, y, Ramp_Phys2HighRes(ANIMMA_CYCLE_TIME), pRamp);
    }
}

//-----------------------------------------------------------------------------
/// Initialize the context of the given block.
//-----------------------------------------------------------------------------
// PRQA S 5316 ++
// QAC(Prio2) Msg: 5316(HIS metrics violation: 'AnimMa_InitBlockContext() : STCYC = 19' exceeds threshold 15 for Cyclomatic complexity (STCYC).) Depth: 0 Ref:  
// Rationale: code is maintainable, testable and well structured.
STATIC_AL void AnimMa_InitBlockContext(uint32 ulActiveBlkId)
{
    uint16 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;
    uint16 unBlkGenIdx = AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx;

    switch (AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucType)
    {
    case (uint8)RUN10:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksRun10Cnt)
        {
            AnimMa_aActiveBlocksRun10[unBlkCtxIdx].ucMovePos = AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucPStart;
        }
    }
    break;
    case (uint8)RUNN:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksRunNCnt)
        {
            AnimMa_aActiveBlocksRunN[unBlkCtxIdx].ucMovePos = AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucPStart;
        }
    }
    break;
    case (uint8)SPARKLE_LFSR:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksSparkleLfsrCnt)
        {
            const tBlockSpecificSparkleLfsr * pCodSpc = (const tBlockSpecificSparkleLfsr *)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
            AnimMa_aActiveBlocksSparkleLfsr[unBlkCtxIdx].unNextTime = AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucTStart));
            for (sint32 i = 0; i < ANIMMA_BLOCK_LFSR_NR_REG_BYTES; i++)
            {
                AnimMa_aActiveBlocksSparkleLfsr[unBlkCtxIdx].ucReg[i] = pCodSpc->aucStartValue[i];
            }
        }
    }
    break;
    case (uint8)SPARKLE_XOR64:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksSparkleXor64Cnt)
        {
            const tBlockSpecificSparkleXor64 * pCodSpc = (const tBlockSpecificSparkleXor64 *)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].unNextTime = AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucTStart));
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg = (uint64)(pCodSpc->aucStartValue[0]);
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[1]) << 8u;
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[2]) << 16u;
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[3]) << 24u;
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[4]) << 32u;
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[5]) << 40u;
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[6]) << 48u;
            AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg |= (uint64)(pCodSpc->aucStartValue[7]) << 56u;
        }
    }
    break;
    case (uint8)CLAMP:
    {
        const tBlockSpecificClamp * pCodSpc = (const tBlockSpecificClamp *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    }
    break;
    case (uint8)INVERT:
    {
        // nothing to initialize
    }
    break;
    case (uint8)FLEX:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksFlexCnt)
        {
            const tBlockSpecificFlex * pCodSpc = (const tBlockSpecificFlex *)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
            AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulNextTime = AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucTStart));
            AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulPos = 0;
        }
    }
    break;
    case (uint8)SPEEDASSIGN:
    {
        const tBlockSpecificSpeedAssign * pCodSpc = (const tBlockSpecificSpeedAssign *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    }
    break;
    case (uint8)PIECEWISELINEAR:
    {
        const tBlockSpecificPiecewiseLinear * pCodSpc = (const tBlockSpecificPiecewiseLinear *)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
        AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ulNextTime = AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucTStart));
        // sanity check: array is expected to exist if number of function points is greater than zero
        if ((uint32)pCodSpc->ucN > 0u)
        {
            AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ulNextTime += AnimMa_Cod_Param2Ms(AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Time(pCodSpc, 0));
        }
        AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ucIdx = 0;
        AnimMa_PiecewiseLinear_InitRamp(AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ucIdx, pCodSpc, &AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ramp);
    }
    break;
    case (uint8)INVERTINTENSITY:
    {
        // nothing to initialize
    }
    break;
    case (uint8)TIMEOFFSET:
    {
        // nothing to initialize
    }
    case (uint8)REPETITION:
    {
        const tBlockSpecificRepetition * pCodSpc = (const tBlockSpecificRepetition *)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
        AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ulNextTime = AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(AnimMa_Cod_GetBlockGenericBlkGenIdx(unBlkGenIdx)->ucTStart));
        AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ulNextTime += AnimMa_Cod_Param2Ms(pCodSpc->ucRepetitionTime);
        AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ucRepCntDn = pCodSpc->ucNrRepetitions;
    }
    break;
    default:
        break;
    }
}// PRQA S 5316 code is maintainable, testable and well structured.

//-----------------------------------------------------------------------------
/// Allocate the blocks context of the given block.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// PRQA S 5316 ++
// QAC(Prio2) Msg: 5316(HIS metrics violation: 'AnimMa_AllocateBlockContext() : STCYC = 21' exceeds threshold 15 for Cyclomatic complexity (STCYC).) Depth: 0 Ref:   
// Rationale: code is maintainable, testable and well structured.
STATIC_AL uint8 AnimMa_AllocateBlockContext(uint8 blocktype)
{
    uint32 ulCtxId = ANIMMA_INVALID_BLOCK_IDX;
    switch (blocktype)
    {
    case (uint8)RUN10:
    {
        if (AnimMa_unActiveBlocksRun10Cnt < ANIMMA_NR_BLOCKS_RUN10)
        {
            ulCtxId = AnimMa_unActiveBlocksRun10Cnt;
            AnimMa_unActiveBlocksRun10Cnt++;
        }
    }
    break;
    case (uint8)RUNN:
    {
        if (AnimMa_unActiveBlocksRunNCnt < ANIMMA_NR_BLOCKS_RUNN)
        {
            ulCtxId = AnimMa_unActiveBlocksRunNCnt;
            AnimMa_unActiveBlocksRunNCnt++;
        }
    }
    break;
    case (uint8)SPARKLE_LFSR:
    {
        if (AnimMa_unActiveBlocksSparkleLfsrCnt < ANIMMA_NR_BLOCKS_SPARKLE_LFSR)
        {
            ulCtxId = AnimMa_unActiveBlocksSparkleLfsrCnt;
            AnimMa_unActiveBlocksSparkleLfsrCnt++;
        }
    }
    break;
    case (uint8)SPARKLE_XOR64:
    {
        if (AnimMa_unActiveBlocksSparkleXor64Cnt < ANIMMA_NR_BLOCKS_SPARKLE_XOR64)
        {
            ulCtxId = AnimMa_unActiveBlocksSparkleXor64Cnt;
            AnimMa_unActiveBlocksSparkleXor64Cnt++;
        }
    }
    break;
    case (uint8)CLAMP: // No Memomory allocation
    {
        ulCtxId = AnimMa_unActiveBlocksClampCnt;
        AnimMa_unActiveBlocksClampCnt++;
    }
    break;
    case (uint8)INVERT: // No Memory Allocation
    {
        // nothing to allocate, return 0 as default (which is not invalid, so allocation was successful)
        ulCtxId = AnimMa_unActiveBlocksInvertCnt;
        AnimMa_unActiveBlocksInvertCnt++;
    }
    break;
    case (uint8)BLINK:
    {
        if (AnimMa_unActiveBlocksBlinkCnt < ANIMMA_NR_BLOCKS_BLINK)
        {
            ulCtxId = AnimMa_unActiveBlocksBlinkCnt;
            AnimMa_unActiveBlocksBlinkCnt++;
        }
    }
    break;
    case (uint8)FLEX:
    {
        if (AnimMa_unActiveBlocksFlexCnt < ANIMMA_NR_BLOCKS_FLEX)
        {
            ulCtxId = AnimMa_unActiveBlocksFlexCnt;
            AnimMa_unActiveBlocksFlexCnt++;
        }
    }
    break;
    case (uint8)SPEEDASSIGN: // No Memomory allocation
    {
        ulCtxId = AnimMa_unActiveBlocksSpeedAssignCnt;
        AnimMa_unActiveBlocksSpeedAssignCnt++;
    }
    break;
    case (uint8)PIECEWISELINEAR:
    {
        if (AnimMa_unActiveBlocksPiecewiseLinearCnt < ANIMMA_NR_BLOCKS_BLINK)
        {
            ulCtxId = AnimMa_unActiveBlocksPiecewiseLinearCnt;
            AnimMa_unActiveBlocksPiecewiseLinearCnt++;
        }
    }
    break;
    case (uint8)INVERTINTENSITY: // No Memory Allocation
    {
        ulCtxId = AnimMa_unActiveBlocksInvertIntensityCnt;
        AnimMa_unActiveBlocksInvertIntensityCnt++;
    }
    break;
    case (uint8)TIMEOFFSET: // No Memory Allocation
       ulCtxId = 0;
       ulCtxId = AnimMa_unActiveBlocksRepetitionCnt;
       AnimMa_unActiveBlocksRepetitionCnt++;
    break;
    case (uint8)REPETITION:
    {
        ulCtxId = AnimMa_unActiveBlocksRepetitionCnt;
        AnimMa_unActiveBlocksRepetitionCnt++;
    }
    break;
    default:
        break;
    }

    return (uint8)ulCtxId;
}// PRQA S 5316 code is maintainable, testable and well structured.

//-----------------------------------------------------------------------------
/// Delete the block context of the given block.
//-----------------------------------------------------------------------------
// PRQA S 5330 ++
// QAC(Prio2) Msg: 5330(HIS metrics violation: 'AnimMa_DeleteBlockContext() : STST3 = 68' exceeds threshold 50 for Number of statements in function (STST3).) Depth: 0 Ref:  
// Rationale: code is maintainable, testable and well structured.
STATIC_AL void AnimMa_DeleteBlockContext(uint32 unBlkCtxIdx, uint8 blocktype)
{
    uint32 ulCtxIdx;

    switch (blocktype)
    {
    case (uint8)RUN10:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksRun10Cnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksRun10Cnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksRun10[ulCtxIdx - 1u].ucMovePos = AnimMa_aActiveBlocksRun10[ulCtxIdx].ucMovePos;
            }
            AnimMa_unActiveBlocksRun10Cnt--;
            AnimMa_unDeactivateBlocksRun10Cnt++;
        }
    }
    break;
    case (uint8)RUNN:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksRunNCnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksRunNCnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksRunN[ulCtxIdx - 1u].ucMovePos = AnimMa_aActiveBlocksRunN[ulCtxIdx].ucMovePos;
            }
            AnimMa_unActiveBlocksRunNCnt--;
            AnimMa_unDeactivateBlocksRunNCnt++;
        }
    }
    break;
    case (uint8)SPARKLE_LFSR:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksSparkleLfsrCnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksSparkleLfsrCnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksSparkleLfsr[ulCtxIdx - 1u].unNextTime = AnimMa_aActiveBlocksSparkleLfsr[ulCtxIdx].unNextTime;
                for (sint32 i = 0; i < ANIMMA_BLOCK_LFSR_NR_REG_BYTES; i++)
                {
                    AnimMa_aActiveBlocksSparkleLfsr[ulCtxIdx - 1u].ucReg[i] = AnimMa_aActiveBlocksSparkleLfsr[ulCtxIdx].ucReg[i];
                }
            }
            AnimMa_unActiveBlocksSparkleLfsrCnt--;
            AnimMa_unDeactivateBlocksSparkleLfsrCnt++;
        }
    }
    break;
    case (uint8)SPARKLE_XOR64:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksSparkleXor64Cnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksSparkleXor64Cnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksSparkleXor64[ulCtxIdx - 1u].unNextTime = AnimMa_aActiveBlocksSparkleXor64[ulCtxIdx].unNextTime;
                AnimMa_aActiveBlocksSparkleXor64[ulCtxIdx - 1u].ulReg = AnimMa_aActiveBlocksSparkleXor64[ulCtxIdx].ulReg;
            }
            AnimMa_unActiveBlocksSparkleXor64Cnt--;
            AnimMa_unDeactivateBlocksSparkleXor64Cnt++;
        }
    }
    break;

    case (uint8)CLAMP:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksClampCnt)
        {
            AnimMa_unActiveBlocksClampCnt--;
            AnimMa_unDeactivateBlocksClampCnt++;
        }
    }
    break;

    case (uint8)INVERT:
    {
        AnimMa_unActiveBlocksInvertCnt--;
        AnimMa_unDeactivateBlocksInvertCnt++;
    }
    break;
    case (uint8)BLINK:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksBlinkCnt)
        {
            AnimMa_unActiveBlocksBlinkCnt--;
            AnimMa_unDeactivateBlocksBlinkCnt++;
        }
    }
    break;
    case (uint8)FLEX:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksFlexCnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksFlexCnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksFlex[ulCtxIdx - 1u].ulNextTime = AnimMa_aActiveBlocksFlex[ulCtxIdx].ulNextTime;
                AnimMa_aActiveBlocksFlex[ulCtxIdx - 1u].ulPos = AnimMa_aActiveBlocksFlex[ulCtxIdx].ulPos;
            }
            AnimMa_unActiveBlocksFlexCnt--;
            AnimMa_unDeactivateBlocksFlexCnt++;
        }
    }
    break;
    case (uint8)SPEEDASSIGN:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksSpeedAssignCnt)
        {
            AnimMa_unActiveBlocksSpeedAssignCnt--;
            AnimMa_unDeactivateBlocksSpeedAssignCnt++;
        }
    }
    break;
    case (uint8)PIECEWISELINEAR:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksPiecewiseLinearCnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksPiecewiseLinearCnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksPiecewiseLinear[ulCtxIdx - 1u].ulNextTime = AnimMa_aActiveBlocksPiecewiseLinear[ulCtxIdx].ulNextTime;
                AnimMa_aActiveBlocksPiecewiseLinear[ulCtxIdx - 1u].ucIdx = AnimMa_aActiveBlocksPiecewiseLinear[ulCtxIdx].ucIdx;
            }
            AnimMa_unActiveBlocksPiecewiseLinearCnt--;
            AnimMa_unDeactivateBlocksPiecewiseLinearCnt++;
        }
    }
    break;
    case (uint8)INVERTINTENSITY:
    {
        AnimMa_unActiveBlocksInvertIntensityCnt--;
        AnimMa_unDeactivateBlocksInvertIntensityCnt++;
    }
    break;
    case (uint8)TIMEOFFSET:
    {
        // intentionally left empty: nothing to do
    }
    case (uint8)REPETITION:
    {
        if (unBlkCtxIdx < AnimMa_unActiveBlocksRepetitionCnt)
        {
            for (ulCtxIdx = unBlkCtxIdx + 1u; ulCtxIdx < AnimMa_unActiveBlocksRepetitionCnt; ulCtxIdx++)
            {
                AnimMa_aActiveBlocksRepetition[ulCtxIdx - 1u].ulNextTime = AnimMa_aActiveBlocksRepetition[ulCtxIdx].ulNextTime;
                AnimMa_aActiveBlocksRepetition[ulCtxIdx - 1u].ucRepCntDn = AnimMa_aActiveBlocksRepetition[ulCtxIdx].ucRepCntDn;
            }
            AnimMa_unActiveBlocksRepetitionCnt--;
            AnimMa_unDeactivateBlocksRepetitionCnt++;
        }
    }
    break;
    default:
        break;
    }
}
// PRQA S 5330 code is maintainable, testable and well structured.

//-----------------------------------------------------------------------------
/// Allocate the blocks of the given sequence. unSeqCodIdx is the index into coding parameters.
/// Return the index into AnimMa_aActiveBlocks[] for the first block.
//-----------------------------------------------------------------------------
uint8 AnimMa_AllocateBlocks(uint32 ulSeqCodIdx)
{
    uint32 blk;
    const uint32 unNrBlks = AnimMa_Cod_GetNrBlocks(ulSeqCodIdx);
    uint32 ulRet;

    if (AnimMa_unActiveBlocksCnt + unNrBlks >= ANIMMA_NR_BLOCKS)
    {
        ulRet = ANIMMA_INVALID_BLOCK_IDX;
    }
    else
    {
        ulRet = AnimMa_unActiveBlocksCnt;

        for (blk = 0; blk < unNrBlks; blk++)
        {
            AnimMa_aActiveBlocks[AnimMa_unActiveBlocksCnt].unGenParamCodIdx = AnimMa_Cod_GetBlockGenIdx(ulSeqCodIdx, blk);
            AnimMa_aActiveBlocks[AnimMa_unActiveBlocksCnt].unSpcParamCodIdx = AnimMa_Cod_GetBlockSpcIdx(ulSeqCodIdx, blk);
            AnimMa_aActiveBlocks[AnimMa_unActiveBlocksCnt].ucBlkCtxIdx = AnimMa_AllocateBlockContext(AnimMa_Cod_GetBlockGeneric(ulSeqCodIdx, blk)->ucType);
            AnimMa_InitBlockContext(AnimMa_unActiveBlocksCnt);
            AnimMa_unActiveBlocksCnt++;
        }
    }

    return (uint8)ulRet;
}

//-----------------------------------------------------------------------------
/// AnimMa_DeleteBlocks
//-----------------------------------------------------------------------------
// PRQA S 5310 ++
// QAC(Prio2) Msg: 5316(HIS metrics violation: 'AnimMa_DeleteBlocks() : STCYC = 19' exceeds threshold 15 for Cyclomatic complexity (STCYC).) Depth: 0 Ref:  
// Rationale: code is maintainable, testable and well structured
void AnimMa_DeleteBlocks(uint32 ulBlkFstIdx, uint32 ulSeqCodIdx)
{
    const uint32 ulNrBlks = AnimMa_Cod_GetNrBlocks(ulSeqCodIdx);
    sint32 snActiveBlockIdx = 0;
    uint32 unBlkFstIdxDiff;
    AnimMa_unDeactivateBlocksRun10Cnt = 0;
    AnimMa_unDeactivateBlocksRunNCnt = 0;
    AnimMa_unDeactivateBlocksSparkleLfsrCnt = 0;
    AnimMa_unDeactivateBlocksSparkleXor64Cnt = 0;
    AnimMa_unDeactivateBlocksClampCnt = 0;
    AnimMa_unDeactivateBlocksInvertCnt = 0;
    AnimMa_unDeactivateBlocksBlinkCnt = 0;
    AnimMa_unDeactivateBlocksFlexCnt = 0;
    AnimMa_unDeactivateBlocksPiecewiseLinearCnt = 0;
    AnimMa_unDeactivateBlocksInvertIntensityCnt = 0;
    AnimMa_unDeactivateBlocksRepetitionCnt = 0;

    // Reduce from larger index in the active block
    for (uint32 blk = ulBlkFstIdx + ulNrBlks; blk > ulBlkFstIdx; blk--)
    {
        AnimMa_DeleteBlockContext((uint32)AnimMa_aActiveBlocks[blk - 1U].ucBlkCtxIdx, AnimMa_Cod_GetBlockGeneric(ulSeqCodIdx, (blk - ulBlkFstIdx - 1U))->ucType);
    }

    for (uint32 blk = ulBlkFstIdx + ulNrBlks; blk < AnimMa_unActiveBlocksCnt; blk++)
    {
        AnimMa_aActiveBlocks[blk - ulNrBlks].unGenParamCodIdx = AnimMa_aActiveBlocks[blk].unGenParamCodIdx;
        AnimMa_aActiveBlocks[blk - ulNrBlks].unSpcParamCodIdx = AnimMa_aActiveBlocks[blk].unSpcParamCodIdx;

        switch (AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[blk].unGenParamCodIdx)->ucType)
        {
        case (uint8)RUN10:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksRun10Cnt;
        }
        break;
        case (uint8)RUNN:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksRunNCnt;
        }
        break;
        case (uint8)SPARKLE_LFSR:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksSparkleLfsrCnt;
        }
        break;
        case (uint8)SPARKLE_XOR64:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksSparkleXor64Cnt;
        }
        break;
        case (uint8)CLAMP:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksClampCnt;
        }
        break;
        case (uint8)INVERT:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksInvertCnt;
        }
        break;
        case (uint8)BLINK:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksBlinkCnt;
        }
        break;
        case (uint8)FLEX:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksFlexCnt;
        }
        break;
        case (uint8)SPEEDASSIGN:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksSpeedAssignCnt;
        }
        break;
        case (uint8)PIECEWISELINEAR:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksPiecewiseLinearCnt;
        }
        break;
        case (uint8)INVERTINTENSITY:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksInvertIntensityCnt;
        }
        break;
        case (uint8)TIMEOFFSET:
        {
            // intentionally left empty: nothing to do;
        }
        case (uint8)REPETITION:
        {
            unBlkFstIdxDiff = AnimMa_unDeactivateBlocksRepetitionCnt;
        }
        break;
        default:
            break;
        }

        AnimMa_aActiveBlocks[blk - ulNrBlks].ucBlkCtxIdx = (uint8)(AnimMa_aActiveBlocks[blk].ucBlkCtxIdx - unBlkFstIdxDiff);
    }

    // The deallocated blocks are given non valid block Index

    for (uint8 ucI = 0; ucI < ulNrBlks; ucI++)
    {
        snActiveBlockIdx = (sint32)((sint32)AnimMa_unActiveBlocksCnt - (sint32)ucI - 1);

        if ((snActiveBlockIdx >= 0) && (snActiveBlockIdx < (sint32)ANIMMA_NR_BLOCKS))
        {
            AnimMa_aActiveBlocks[snActiveBlockIdx].ucBlkCtxIdx = (uint8)ANIMMA_INVALID_BLOCK_IDX; // deleted block has an invalid block index
        }
        else
        {
            //don't increment ucI anymore, because the ActiveBlockCnt is less than ucI and the index will be negative
            break;
        }
    }

    AnimMa_unActiveBlocksCnt -= ulNrBlks;

    if (AnimMa_unActiveBlocksCnt == 0U)
    {
        for (uint8 i = 0U; i < (uint8)ANIMMA_NR_PIXELS; i++)
        {
            AnimMaRamp_aucPxlIntTgt[i] = 0;
        }
    }
}
//PRQA S 5316 1 readability and design review 11.05.22 Ionut CABA/Florin ONUFRICIUC : no risk for the increased path
//PRQA S 5310 1 code is maintainable, testable and well structured.

//-----------------------------------------------------------------------------
// Init the content of all the block in one sequence
//-----------------------------------------------------------------------------
void AnimMa_InitBlocksContent(uint32 ulBlkFstIdx, uint32 ulSeqCodIdx)
{
    uint32 blk;
    const uint32 ulNrBlks = AnimMa_Cod_GetNrBlocks(ulSeqCodIdx);

    for (blk = ulBlkFstIdx; blk < ulBlkFstIdx + ulNrBlks; blk++)
    {
        AnimMa_InitBlockContext(blk);
    }
}

//-----------------------------------------------------------------------------
// Calculate the stop block number in one sequence
//-----------------------------------------------------------------------------
uint8 AnimMa_StopBlocksNr(uint32 ulSeqCodIdx)
{
    uint32 blk;
    uint32 ulNrBlks = AnimMa_Cod_GetNrBlocks(ulSeqCodIdx);
    uint8 ucRet = 0;

        for (blk = 0; blk < ulNrBlks; blk++)
        {
            if (0U != ((AnimMa_Cod_GetBlockGeneric(ulSeqCodIdx, blk)->ucFlags) &ANIMMA_BLOCK_STOPFLAG))
            {
                ucRet++;
            }
        }

    return ucRet;
}


//-----------------------------------------------------------------------------
/// Copy
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_copyKernel(sint32 nStartPos, uint8 nKnlSize, const uint8 * pcKernel, uint8 nPStart, uint8 nPEnd)
{
    sint32 nPos = nStartPos;

    for (nPos = nStartPos; nPos <= nStartPos + (sint32)nKnlSize; nPos++)
    {
        if ((nPos >= (sint32)nPStart) && (nPos <= (sint32)nPEnd))
        {
            AnimMaRamp_aucPxlIntTgt[nPos] = pcKernel[nPos - nStartPos];
        }
    }

}

//-----------------------------------------------------------------------------
/// Block execution for Run10 block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockRun10(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric       * pCodGen = (const tBlockGeneric       *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificRun10 * pCodSpc = (const tBlockSpecificRun10 *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 ulBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;

    // TBD handle this globally
    if (ulBlkCtxIdx >= AnimMa_unActiveBlocksRun10Cnt)
    {
        return;
    }

    uint32 i;
    uint8 nFillValue;
    sint32 nStartPos;

    if (pCodSpc->ucType == (uint8)RUN)
    {
        nFillValue = 0U;
    }
    else
    {
        nFillValue = ANIMMA_PATTERN_MAX_VALUE; 
    }


    // [50 ms]
    if (pCodSpc->ucSpeed > 0U)
    {
        uint32 unCodTime = ANIMMA_CYCLE_TIME * (uint32)pCodSpc->ucSpeed;
        uint32 unAllTime = ANIMMA_CYCLE_TIME * ((uint32)pCodSpc->ucSpeed + (uint32)pCodSpc->ucWaitTime);
        uint32 unDeltaTime = (ulTime - AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(pCodGen->ucTStart))) % ((uint32)unAllTime);

        if ((ulTime != 0U) && (unDeltaTime == 0U))
        {
            unDeltaTime = unAllTime;
            AnimMa_aActiveBlocksRun10[ulBlkCtxIdx].ucMovePos = pCodGen->ucPStart;
        }
        else if (unDeltaTime <= unCodTime)
        {
            AnimMa_aActiveBlocksRun10[ulBlkCtxIdx].ucMovePos = (uint8)(pCodGen->ucPStart + (unDeltaTime * (((uint32)pCodGen->ucPEnd - (uint32)pCodGen->ucPStart) + (uint32)pCodSpc->ucPatternSize)) / unCodTime);
        }
        else
        {
            // do nothing
        }
    }
    else
    {
        AnimMa_aActiveBlocksRun10[ulBlkCtxIdx].ucMovePos++;
    }


    // clear register if a sequence is finished
    //if (pCodSpc->ucType == SWEEP)
    for (i = (uint32)pCodGen->ucPStart; i <= (uint32)pCodGen->ucPEnd; i++)
    {
        AnimMaRamp_aucPxlIntTgt[i] = 0u;
    }

    nStartPos = (sint32)AnimMa_aActiveBlocksRun10[ulBlkCtxIdx].ucMovePos - (sint32)pCodSpc->ucPatternSize + 1;
    (void)AnimMa_copyKernel(nStartPos, pCodSpc->ucPatternSize, pCodSpc->aucPattern, pCodGen->ucPStart, pCodGen->ucPEnd);

    for (sint32 iPos = (sint32)pCodGen->ucPStart; iPos < (sint32)nStartPos; iPos++)
    {
        AnimMaRamp_aucPxlIntTgt[iPos] = nFillValue;
    }

    for (sint32 iPos = (sint32)pCodGen->ucPStart; iPos <= (sint32)pCodGen->ucPEnd; iPos++)
    {
        AnimMaRamp_aucPxlIntInc[iPos] = pCodSpc->ucDimUp;
        AnimMaRamp_aucPxlIntDec[iPos] = pCodSpc->ucDimDn;
    }
} // PRQA S 5310 code is maintainable, testable and well structured.


//-----------------------------------------------------------------------------
/// Shift bytes of LFSR register and perform feedback XORs.
/// reg[0] >>= 1, fill highest bit with lowest bit of reg[1]
/// reg[1] >>= 1, fill highest bit with lowest bit of reg[2]
/// ...
/// reg[n] >>= 1, fill highest bit with XOR of feedback bits
///
/// Feedback bit is calculated like this:
/// bit = (reg >> fdbk1) ^ (reg >> fdbk2) ^ ... ^ (reg >> fdbk_k)
/// reg = (reg >> 1) | (bit << nrbits-1)
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_LfsrShift(const uint32 ulBlkCtxIdx, const tBlockSpecificSparkleLfsr * pCodSpc, const sint32 nBits)
{
    uint8 ucBit = 0;
    uint8 ucLowBit;
    uint8 ucByte;
    uint8 ucFdbk;
    sint32 nByte;
    sint32 nBit;
    bool bBitInit = false;
    sint32 nBytes = (nBits + 7) / 8;

    if (nBytes > ANIMMA_BLOCK_LFSR_NR_REG_BYTES)
    {
        nBytes = ANIMMA_BLOCK_LFSR_NR_REG_BYTES;
    }

    for (nByte = 0; nByte < nBytes; nByte++)
    {
        ucByte = AnimMa_aActiveBlocksSparkleLfsr[ulBlkCtxIdx].ucReg[nByte];
        ucFdbk = pCodSpc->aucFeedback[nByte];

        for (nBit = 0; (nBit < 8) && (ucFdbk != 0U); nBit++)
        {
            if ((ucFdbk & 0x01u) != 0U)
            {
                if (!bBitInit)
                {
                    ucBit = ucByte & 0x01u;
                    bBitInit = true;
                }
                else
                {
                    ucBit ^= ucByte;
                }
            }
            ucByte >>= 1u;
            ucFdbk >>= 1u;
        }
    }

    for (nByte = nBytes - 1; nByte >= 0; nByte--)
    {
        ucLowBit = AnimMa_aActiveBlocksSparkleLfsr[ulBlkCtxIdx].ucReg[nByte] & 0x01u;
        AnimMa_aActiveBlocksSparkleLfsr[ulBlkCtxIdx].ucReg[nByte] >>= 1u;
        AnimMa_aActiveBlocksSparkleLfsr[ulBlkCtxIdx].ucReg[nByte] |= (uint8)(ucBit << 7u);
        ucBit = ucLowBit;
    }
}

///-----------------------------------------------------------------------------
/// Block execution for SparkleLfsr block
///-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockSparkleLfsr(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric             * pCodGen = (const tBlockGeneric             *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificSparkleLfsr * pCodSpc = (const tBlockSpecificSparkleLfsr *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;

    sint32 i;

    // TBD handle this globally
    if (unBlkCtxIdx >= AnimMa_unActiveBlocksSparkleLfsrCnt)
    {
        return;
    }

    if (ulTime >= AnimMa_aActiveBlocksSparkleLfsr[unBlkCtxIdx].unNextTime)
    {
        AnimMa_LfsrShift(unBlkCtxIdx, pCodSpc, ((sint32)pCodGen->ucPEnd - (sint32)pCodGen->ucPStart));
        AnimMa_aActiveBlocksSparkleLfsr[unBlkCtxIdx].unNextTime += AnimMa_Cod_Param2Ms(pCodSpc->ucUpdateInterval);
    }

    for (i = (sint32)pCodGen->ucPStart; i <= (sint32)pCodGen->ucPEnd; i++)
    {
        uint32 ulByte = ((uint32)i) / 8u;
        uint32 ulBit = ((uint32)i) % 8u;
        if ((((uint32)AnimMa_aActiveBlocksSparkleLfsr[unBlkCtxIdx].ucReg[ulByte] >> ulBit) & 0x1UL) != 0UL)
        {
            AnimMaRamp_aucPxlIntTgt[i] = ANIMMA_PATTERN_MAX_VALUE;
        }
        else
        {
            AnimMaRamp_aucPxlIntTgt[i] = 0;
        }

        AnimMaRamp_aucPxlIntInc[i] = pCodSpc->ucDimUp;
        AnimMaRamp_aucPxlIntDec[i] = pCodSpc->ucDimDn;
    }
}

//-----------------------------------------------------------------------------
/// XOR shift of a 64 bit value with feedback
//-----------------------------------------------------------------------------
STATIC_AL uint64 xorshift64(uint64 ulBits, const uint8 * aucShift)
{
    ulBits ^= ulBits << aucShift[0];
    ulBits ^= ulBits >> aucShift[1];
    ulBits ^= ulBits << aucShift[2];
    return ulBits;
}

//-----------------------------------------------------------------------------
/// Block execution for SPARKLE_XOR64 block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockSparkleXor64(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric              * pCodGen = (const tBlockGeneric              *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificSparkleXor64 * pCodSpc = (const tBlockSpecificSparkleXor64 *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;

    uint32 i;

    // TBD handle this globally
    if (unBlkCtxIdx >= AnimMa_unActiveBlocksSparkleXor64Cnt)
    {
        return;
    }

    if (ulTime >= AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].unNextTime)
    {
        AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg = xorshift64(AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg, pCodSpc->aucShift);
        AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].unNextTime += AnimMa_Cod_Param2Ms(pCodSpc->ucUpdateInterval);
    }

    // Update RINT (AnimMaRamp_aucPxlIntTgt) in each call (because RINT is cleared for each call)
    for (i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
    {
        if (((AnimMa_aActiveBlocksSparkleXor64[unBlkCtxIdx].ulReg >> i) & 0x1UL) != 0UL)
        {
            AnimMaRamp_aucPxlIntTgt[i] = ANIMMA_PATTERN_MAX_VALUE;
        }
        else
        {
            AnimMaRamp_aucPxlIntTgt[i] = 0;
        }

        AnimMaRamp_aucPxlIntInc[i] = pCodSpc->ucDimUp;
        AnimMaRamp_aucPxlIntDec[i] = pCodSpc->ucDimDn;

    }

}

//-----------------------------------------------------------------------------
/// Intensity interpolation between points for DIM block
//-----------------------------------------------------------------------------
STATIC_AL uint8 interpolateDim(uint16 * T, uint16 * I, uint32 unTime)
{
    uint8 countOfDataPts = ANIMMA_DIMBLOCK_POINT_NUMBER;
    uint8 dimIntensity = 0U;

    uint8 upper = 0u;

    uint32 ulValue = unTime / ANIMMA_CYCLE_TIME;

    while (countOfDataPts > 0U)
    {
        uint8 iteratorDataPt = upper;
        uint8 dataPtsInStepForSorting = countOfDataPts / 2U;

        iteratorDataPt = iteratorDataPt + dataPtsInStepForSorting;

        if (!(ulValue < T[iteratorDataPt]))
        {
            upper = ++iteratorDataPt;
            countOfDataPts -= dataPtsInStepForSorting + 1U;
        }
        else
        {
            countOfDataPts = dataPtsInStepForSorting;
        }
    }


    if (upper == ANIMMA_DIMBLOCK_POINT_NUMBER)
    {
        dimIntensity = (uint8)I[(sint32)(ANIMMA_DIMBLOCK_POINT_NUMBER - 1U)];
    }
    else if (upper == 0U)
    {
        dimIntensity = (uint8)I[0];
    }

    else
    {
        // leap between the two points
        // lower = upper - 1;
        uint8 lower = upper - 1U;

        const uint32 ulTlo100 = ((uint32)T[lower]) * ANIMMA_PATTERN_MAX_VALUE;
        const uint32 ulThi100 = ((uint32)T[upper]) * ANIMMA_PATTERN_MAX_VALUE;
        const uint32 ulIlo100 = ((uint32)I[lower]) * ANIMMA_PATTERN_MAX_VALUE;
        const uint32 ulIhi100 = ((uint32)I[upper]) * ANIMMA_PATTERN_MAX_VALUE;
        const uint32 ulValue100 = ((uint32)ulValue) * ANIMMA_PATTERN_MAX_VALUE;

        if (ulIhi100 >= ulIlo100) // Rising DIM Curve
        {
            const uint32 ulLinear100 = (ulValue100 - ulTlo100) * (ulIhi100 - ulIlo100) / (ulThi100 - ulTlo100);

            const uint8  ucLinear = (uint8)(ulLinear100 / ANIMMA_PATTERN_MAX_VALUE);

            dimIntensity = (uint8)(I[lower] + ucLinear);
        }
        else  // falling Dim Curve
        {
            const uint32 ulLinear100 = (ulThi100 - ulValue100) * (ulIlo100 - ulIhi100) / (ulThi100 - ulTlo100);

            const uint8  ucLinear = (uint8)(ulLinear100 / ANIMMA_PATTERN_MAX_VALUE);

            dimIntensity = (uint8)(I[upper] + ucLinear);
        }
    }


    return dimIntensity;
}

//-----------------------------------------------------------------------------
/// Block execution for CLAMP/DIM block
//-----------------------------------------------------------------------------
// PRQA S 5310 ++
// QAC(Prio2) Msg: 5310(HIS metrics violation: 'AnimMa_rcBlockClamp() : STPTH = 216' exceeds threshold 80 for Number of paths (STPTH).) Depth: 0 Ref: 
// Rationale: code is well structured, maintainable, testable, and consists of independent code segments.
STATIC_AL void AnimMa_rcBlockClamp(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric              * pCodGen = (const tBlockGeneric       *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificClamp        * pCodSpc = (const tBlockSpecificClamp *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;
    /// Remember state if normal-sequence DIM block such that the state can be used by a end-sequence DIM block, see FLMT-7071
    static struct
    {
        bool isInTimeInterval;   ///< true if DIM block is part of normal-sequence and is still within its time interval (unT is less than T4); false otherwise
        uint8 ucLastUpperLimit;  ///< [%] if DIM block is part of normal-sequence: last calculated upper limit
        uint8 ucLastLowerLimit;  ///< [%] if DIM block is part of normal-sequence: last calculated lower limit
    } sAbortedSeq = { false, 0, 0 };

    uint32 i;
    uint32 ulT; // [ms] local time (since block was started)

    uint8 lowerLimit;
    uint8 upperLimit;

    // TBD handle this globally
    if (unBlkCtxIdx >= AnimMa_unActiveBlocksClampCnt)
    {
        return;
    }
    uint16 T[4];
    uint16 I[4];

    // time stamps of DIM use local time, so 0 sec is start of DIM block
    if (ulTime >= AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(pCodGen->ucTStart)))
    {
        ulT = ulTime - AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(pCodGen->ucTStart));
    }
    else
    {
        ulT = 0u;
    }

    T[0] = (uint16)pCodSpc->aucLowerLimit[0];
    T[1] = (uint16)pCodSpc->aucLowerLimit[2];
    T[2] = (uint16)pCodSpc->aucLowerLimit[4];
    T[3] = (uint16)pCodSpc->aucLowerLimit[6];

    I[0] = (uint16)pCodSpc->aucLowerLimit[1];
    I[1] = (uint16)pCodSpc->aucLowerLimit[3];
    I[2] = (uint16)pCodSpc->aucLowerLimit[5];
    I[3] = (uint16)pCodSpc->aucLowerLimit[7];

    lowerLimit = interpolateDim(T, I, ulT);

    T[0] = (uint16)pCodSpc->aucUpperLimit[0];
    T[1] = (uint16)pCodSpc->aucUpperLimit[2];
    T[2] = (uint16)pCodSpc->aucUpperLimit[4];
    T[3] = (uint16)pCodSpc->aucUpperLimit[6];

    I[0] = (uint16)pCodSpc->aucUpperLimit[1];
    I[1] = (uint16)pCodSpc->aucUpperLimit[3];
    I[2] = (uint16)pCodSpc->aucUpperLimit[5];
    I[3] = (uint16)pCodSpc->aucUpperLimit[7];

    upperLimit = interpolateDim(T, I, ulT);

    // Handle aborted sequence (soft stop), part one
    if (AnimMa_GetGenericFlagStop(pCodGen))
    {
        if (sAbortedSeq.isInTimeInterval)
        {
            if ((sAbortedSeq.ucLastLowerLimit < lowerLimit)
                && ((sAbortedSeq.ucLastLowerLimit > (uint32)pCodSpc->aucLowerLimit[0])
                    || (sAbortedSeq.ucLastLowerLimit > (uint32)pCodSpc->aucLowerLimit[2])
                    || (sAbortedSeq.ucLastLowerLimit > (uint32)pCodSpc->aucLowerLimit[4])
                    || (sAbortedSeq.ucLastLowerLimit > (uint32)pCodSpc->aucLowerLimit[6])
                    )
                )
            {
                lowerLimit = sAbortedSeq.ucLastLowerLimit;
            }

            if ((sAbortedSeq.ucLastUpperLimit < upperLimit)
                && ((sAbortedSeq.ucLastUpperLimit > (uint32)pCodSpc->aucUpperLimit[0])
                    || (sAbortedSeq.ucLastUpperLimit > (uint32)pCodSpc->aucUpperLimit[2])
                    || (sAbortedSeq.ucLastUpperLimit > (uint32)pCodSpc->aucUpperLimit[4])
                    || (sAbortedSeq.ucLastUpperLimit > (uint32)pCodSpc->aucUpperLimit[6])
                    )
                )
            {
                upperLimit = sAbortedSeq.ucLastUpperLimit;
            }
        }
    }

    // Clamp the function
    for (i = (uint32)pCodGen->ucPStart; i <= (uint32)pCodGen->ucPEnd; i++)
    {
        if (upperLimit >= lowerLimit)
        {
            uint8 a = AnimMaRamp_aucPxlIntTgt[i];
            uint8 b = a > upperLimit ? upperLimit : a;
            AnimMaRamp_aucPxlIntTgt[i] = b < lowerLimit ? lowerLimit : b;
        }
        else
        {
            // do nothing, don't change the intensity 
        }
    }

    // Handle aborted sequence (soft stop)
    if (!AnimMa_GetGenericFlagStop(pCodGen))
    {
        sAbortedSeq.isInTimeInterval = false;
        // PRQA S 3415 1 // design: no side effect from AnimMa_Cod_Param2Ms 
        if ((ulT < AnimMa_Cod_Param2Ms(pCodSpc->aucLowerLimit[6])) || (ulT < AnimMa_Cod_Param2Ms(pCodSpc->aucUpperLimit[6])))
        {
            // time is less than parameterized time
            sAbortedSeq.isInTimeInterval = true;
        }

        sAbortedSeq.ucLastUpperLimit = upperLimit;
        sAbortedSeq.ucLastLowerLimit = lowerLimit;
    }
}
// PRQA S 5310 1 // design:code is maintainable, testable and well structured.


//-----------------------------------------------------------------------------
/// Block execution for Invert block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockInvert(uint32 ulActiveBlkId, uint32 ulTime)
{

    const tBlockGeneric * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    uint8 ucTemp;
    uint32 i;
    uint32 nStop;

    (void)ulTime;

    if (pCodGen->ucPEnd > pCodGen->ucPStart)
    {
        nStop = ((uint32)pCodGen->ucPEnd - (uint32)pCodGen->ucPStart) / 2U;

        for (i = 0; i <= nStop; i++)
        {
            ucTemp = AnimMaRamp_aucPxlIntTgt[(uint32)pCodGen->ucPEnd - i];
            AnimMaRamp_aucPxlIntTgt[(uint32)pCodGen->ucPEnd - i] = AnimMaRamp_aucPxlIntTgt[(uint32)pCodGen->ucPStart + i];
            AnimMaRamp_aucPxlIntTgt[(uint32)pCodGen->ucPStart + i] = ucTemp;
        }
    }
}

//-----------------------------------------------------------------------------
/// Block execution for Blink block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockBlink(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric       * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificBlink * pCodSpc = (const tBlockSpecificBlink *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);

    // Output intensity
    uint8 ucIntensity;

    // The period before the Blink is deactived
    uint8 unBlinkEndPhase = pCodSpc->ucTPhase + pCodSpc->ucTOn;

    // Plausible check
    if (unBlinkEndPhase > pCodSpc->ucTPeriod)
    {
        unBlinkEndPhase = pCodSpc->ucTPeriod;
    }
    else
    {
        // Do nothing
    }

    // TPhase+TPeriod
    uint32 unCodTime = AnimMa_Cod_Param2Ms(pCodSpc->ucTPeriod);

    // Difference between the real time and start time
    uint32 unTempTime = ulTime - AnimMa_TimeWarp(AnimMa_Cod_Param2Ms(pCodGen->ucTStart));

    if (unTempTime < AnimMa_Cod_Param2Ms(pCodSpc->ucTDelay))
    {
        // During the Tdelay phase, intensity is ucIoff
        ucIntensity = pCodSpc->ucIOff;
    }
    else
    {
        uint32 unDeltaTime = (unTempTime - AnimMa_Cod_Param2Ms(pCodSpc->ucTDelay)) % ((uint32)unCodTime);

        if ((ulTime != 0U) && (unDeltaTime == 0U))
        {
            unDeltaTime = unCodTime;
        }
        // PRQA S 3415 1 // design: no side effects on AnimMa_Cod_Param2Ms
        if ((unDeltaTime >= AnimMa_Cod_Param2Ms(pCodSpc->ucTPhase)) && (unDeltaTime <= AnimMa_Cod_Param2Ms(unBlinkEndPhase)))
        {
            ucIntensity = pCodSpc->ucIOn;
        }
        else
        {
            ucIntensity = pCodSpc->ucIOff;
        }
    }

    for (uint8 i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
    {
        uint8 unByte = ((uint8)i) / 8u;
        uint8 unBit = ((uint8)i) % 8u;

        if (((pCodSpc->ucPixelMask[unByte] >> unBit) & 0x1U) != 0U)
        {
            AnimMaRamp_aucPxlIntTgt[i] = ucIntensity;
        }
        else
        {
            AnimMaRamp_aucPxlIntTgt[i] = 0u;
        }

        AnimMaRamp_aucPxlIntInc[i] = pCodSpc->ucDimUp;
        AnimMaRamp_aucPxlIntDec[i] = pCodSpc->ucDimDn;
    }
}

//-----------------------------------------------------------------------------
/// Returns the value of the bit at the position unBitPos in array pBytes.
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE bool AnimMa_BitTest(const uint8 * pBytes, const uint32 ulBitPos)
{
    return ((pBytes[ulBitPos / 8u] >> (ulBitPos % 8u)) & 0x01u) != 0u;
}

//-----------------------------------------------------------------------------
/// Block execution for Flex block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockFlex(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric      * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificFlex * pCodSpc = (const tBlockSpecificFlex *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;
    uint8 i;
    const uint8 * pBytes = &(pCodSpc->ucByte0);
    uint32 unBitPos;
    uint32 unBytePos;

    // TBD handle this globally
    if ((unBlkCtxIdx < AnimMa_unActiveBlocksFlexCnt)
        && (pCodSpc->ucT > (uint8) 0))
    {
        if (ulTime >= AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulNextTime)
        {
            unBytePos = AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulPos;
            unBitPos = 0;
            for (i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
            {
                if (AnimMa_BitTest(&(pBytes[unBytePos]), unBitPos))
                {
                    AnimMaRamp_aucPxlIntTgt[i] = ANIMMA_PATTERN_MAX_VALUE;
                }
                else
                {
                    AnimMaRamp_aucPxlIntTgt[i] = 0;
                }
                unBitPos++;
            }
            AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulNextTime += ANIMMA_CYCLE_TIME;
            // switch to next byte position: increment with the number of bytes (round to smallest number that is greater than or equal to ucN and is a multiple of 8)
            if (AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulPos < ((uint32)pCodSpc->ucT - 1u) * (((uint32)pCodSpc->ucN + 7u) / 8u))
            {
                AnimMa_aActiveBlocksFlex[unBlkCtxIdx].ulPos += ((uint32)pCodSpc->ucN + 7u) / 8u;
            }
        }

        for (i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
        {
            AnimMaRamp_aucPxlIntInc[i] = pCodSpc->ucDimUp;
            AnimMaRamp_aucPxlIntDec[i] = pCodSpc->ucDimDn;
        }
    }
}

//-----------------------------------------------------------------------------
/// Block execution for SpeedAssign block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockSpeedAssign(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric      * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificSpeedAssign * pCodSpc = (const tBlockSpecificSpeedAssign *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    uint8 i;
    uint8 ucIdx;
    uint32 ulTmp;
    const uint8 ucNrBytes = AnimMa_CeilU8(pCodSpc->ucN, 4u);
    const uint8 * pBytesDimUpIdx = &(pCodSpc->ucByte0);
    const uint8 * pBytesDimDnIdx = &(pBytesDimUpIdx[ucNrBytes]);
    const uint8 ucLastByteIdx = ucNrBytes - (uint8)1u;

    (void)ulTime;

    for (i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
    {
        ulTmp = (uint32)i - (uint32)pCodGen->ucPStart;
        // LSB of DimUpIdx byte stream contains index of first pixel, so MSB is in pBytesDimUpIdx[0], LSB is in pBytesDimUpIdx[ucNrBytes-1].
        ucIdx = (uint8)((pBytesDimUpIdx[ucLastByteIdx - (ulTmp / 4u)] >> (2u * (ulTmp % 4u))) & 0x03u);
        AnimMaRamp_aucPxlIntInc[i] = pCodSpc->ucDimUpInc[ucIdx];
    }
    for (i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
    {
        ulTmp = (uint32)i - (uint32)pCodGen->ucPStart;
        // LSB of DimUpIdx byte stream contains index of first pixel, so MSB is in pBytesDimUpIdx[0], LSB is in pBytesDimUpIdx[ucNrBytes-1].
        ucIdx = (uint8)((pBytesDimDnIdx[ucLastByteIdx - (ulTmp / 4u)] >> (2u * (ulTmp % 4u))) & 0x03u);
        AnimMaRamp_aucPxlIntDec[i] = pCodSpc->ucDimDnDec[ucIdx];
    }
}

//-----------------------------------------------------------------------------
/// Block execution for PiecewiseLinear block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockPiecewiseLinear(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric                 * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificPiecewiseLinear * pCodSpc = (const tBlockSpecificPiecewiseLinear *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;

    // [%] Output intensity
    uint8 ucIntensity;

    if (ulTime == AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ulNextTime)
    {
        if ((uint32)AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ucIdx + 1u < (uint32)pCodSpc->ucN)
        {
            AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ucIdx++;
            AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ulNextTime += AnimMa_Cod_Param2Ms(AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Time(pCodSpc, AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ucIdx));
            AnimMa_PiecewiseLinear_InitRamp(AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ucIdx, pCodSpc, &AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ramp);
        }
    }

    ucIntensity = Ramp_HighRes2Param(AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ramp.ulCur);

    AnimMa_Ramp_Step(&AnimMa_aActiveBlocksPiecewiseLinear[unBlkCtxIdx].ramp);

    for (uint8 i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
    {
        AnimMaRamp_aucPxlIntTgt[i] = ucIntensity;

        AnimMaRamp_aucPxlIntInc[i] = pCodSpc->ucDimUpInc;
        AnimMaRamp_aucPxlIntDec[i] = pCodSpc->ucDimDnDec;
    }
}

//-----------------------------------------------------------------------------
/// Block execution for InvertIntensity block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockInvertIntensity(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    uint32 i;

    (void)ulTime;

    for (i = pCodGen->ucPStart; i <= pCodGen->ucPEnd; i++)
    {
        AnimMaRamp_aucPxlIntTgt[i] = ANIMMA_PATTERN_MAX_VALUE - AnimMaRamp_aucPxlIntTgt[i];
    }
}

//-----------------------------------------------------------------------------
/// Block execution for TimeOffset block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockTimeOffset(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric * pCodGen = (const tBlockGeneric *)(const void *)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);

    sTimeWarp.ulTimeOffset = AnimMa_Cod_Param2Ms(AnimMa_Cod_MakeUInt16(pCodGen->ucTStart, pCodGen->ucTEnd));

    if (ulTime == sTimeWarp.ulTimeOffset)
    {
        AnimMa_EnableInitContext(255U);
    }
}

//-----------------------------------------------------------------------------
/// Block execution for Repetition block
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockRepetition(uint32 ulActiveBlkId, uint32 ulTime)
{
    const tBlockGeneric* pCodGen = (const tBlockGeneric*)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx);
    const tBlockSpecificRepetition* pCodSpc = (const tBlockSpecificRepetition*)(const void*)AnimMa_Cod_GetBlockSpecific(AnimMa_aActiveBlocks[ulActiveBlkId].unSpcParamCodIdx);
    const uint32 unBlkCtxIdx = AnimMa_aActiveBlocks[ulActiveBlkId].ucBlkCtxIdx;

    // do not use TimeWarp function because TimeWarp considers both offset of TimeOffset block and offset of Repetition block
    if (ulTime >= AnimMa_Cod_Param2Ms(pCodGen->ucTStart) + (uint32)sTimeWarp.ulTimeOffset)
    {
        if ((uint32)AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ucRepCntDn > 0U)
        {
            // ucRepCntDn is a count down but TimeOffsetRepetition shall increase -> (ucNrRepetitions - ucRepCntDn) is the factor for repetition time to calculate the offset
            AnimMa_RepetitionStack_Push(
                ((uint32)pCodSpc->ucNrRepetitions - (uint32)AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ucRepCntDn) * AnimMa_Cod_Param2Ms(pCodSpc->ucRepetitionTime),
                pCodSpc->ucNrBlocks);

            if (ulTime == AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ulNextTime)
            {
                AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ucRepCntDn--;
                if ((uint32)AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ucRepCntDn > 0U)
                {
                    // Update TimeOffset again because ucCnt has been manipulated and subsequent blocks need to be triggered immediately (during this run on rcSequence)
                    AnimMa_RepetitionStack_Pop();
                    AnimMa_RepetitionStack_Push(
                        ((uint32)pCodSpc->ucNrRepetitions - (uint32)AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ucRepCntDn) * AnimMa_Cod_Param2Ms(pCodSpc->ucRepetitionTime),
                        pCodSpc->ucNrBlocks);
                    AnimMa_EnableInitContext(pCodSpc->ucNrBlocks);
                    AnimMa_aActiveBlocksRepetition[unBlkCtxIdx].ulNextTime += AnimMa_Cod_Param2Ms(pCodSpc->ucRepetitionTime);
                }
                else
                {
                    // Remove TimeOffset because the repetition is finished
                    AnimMa_RepetitionStack_Pop();
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
/// Empty function (used for blocks that are not implemented yet / are not available)
//-----------------------------------------------------------------------------
STATIC_AL void AnimMa_rcBlockNA(uint32 ulActiveBlkId, uint32 ulTime)
{
    //doing nothing
    (void)ulActiveBlkId;
    (void)ulTime;
}

//-----------------------------------------------------------------------------
/// Return true of the block type uses timestart and timeend
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE bool AnimMa_HasTime(uint8 ucBlockType)
{
    return (ucBlockType != (uint8)TIMEOFFSET) && (ucBlockType != (uint8)REPETITION);
}

//-----------------------------------------------------------------------------
/// Return true if the block shall be executed tue to unTime (and its block type)
//-----------------------------------------------------------------------------
STATIC_AL AM_INLINE bool AnimMa_TimeCond(uint32 ulActiveBlkId, uint32 ulTime)
{
    bool bRet;

    const uint8 blocktype = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucType;

    const uint8 stopTime = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucTEnd;
    const uint8 startTime = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucTStart;

    uint32 unStopTime = AnimMa_Cod_Param2Ms(stopTime);
    uint32 unStartTime = AnimMa_Cod_Param2Ms(startTime);

    unStopTime = AnimMa_TimeWarp(unStopTime);
    unStartTime = AnimMa_TimeWarp(unStartTime);

    if (AnimMa_HasTime(blocktype))
    {
        bRet =
            ((ulTime <= unStopTime) || (stopTime == (uint8)ANIMMA_ENDLESSRUN_TIME))
            && (ulTime >= unStartTime);
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

//-----------------------------------------------------------------------------
/// Cyclic block execution
/// param unActiveBlkId: Index of block that is to be executed, index in AnimMa_aActiveBlocks 
/// param unTime: [ms] Current time 
/// param ucMountingSide: mounting side [ANIMMA_MOUNTINGSIDE_LEFT, _RIGHT]
//-----------------------------------------------------------------------------
void AnimMa_rcBlock(uint32 ulActiveBlkId, uint32 ulTime, uint8 ucMountingSide)
{
    static const tAnimMa_rcFuncType AnimMa_arcFunc[] =
    {
      AnimMa_rcBlockRun10,          // Index = block type RUN10 (0)
      AnimMa_rcBlockSparkleLfsr,    // Index = block type SPARKLE_LFSR (1)
      AnimMa_rcBlockSparkleXor64,   // Index = block type SPARKLE_XOR64 (2)
      AnimMa_rcBlockClamp,          // Index = block type DIM (3)
      AnimMa_rcBlockNA,             // Index = block type MASK (4)
      AnimMa_rcBlockFlex,           // Index = block type FLEX (5)
      AnimMa_rcBlockInvert,         // Index = block type INVERT (6)
      AnimMa_rcBlockBlink,          // Index = block type BLINK  (7)
      AnimMa_rcBlockSpeedAssign,    // Index = block type SPEEDASSIGN  (8)
      AnimMa_rcBlockPiecewiseLinear,// Index = block type PIECEWISELINEAR  (9)
      AnimMa_rcBlockInvertIntensity,// Index = block type INVERTINTENSITY  (10)
      AnimMa_rcBlockNA,             // Index = block type RUNN  (11)
      AnimMa_rcBlockTimeOffset,     // Index = block type TIMEOFFSET  (12)
      AnimMa_rcBlockRepetition      // Index = block type REPETITION  (13)
    };

    const uint8 blocktype = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucType;
    const uint8 bFlagType = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucFlags;

    // initialize block context if needed, update repetition counter, ...
    AnimMa_InitContext(ulActiveBlkId);

    // Update the time offset in case a repetition is active
    AnimMa_UpdateRepetition();

    // true if it is time for the block to be executed
    const bool bTime = AnimMa_TimeCond(ulActiveBlkId, ulTime);

    // Running flag based on the Mounting side
    bool bRunSideFlag = false;

    // Check the mounting side and the bit 1&2 of the bFlagType
    if ((ucMountingSide == ANIMMA_MOUNTINGSIDE_LEFT)
        && ((bFlagType & ANIMMA_BLOCK_RIGHTONLY) != 0U))
    {
        bRunSideFlag = false;
    }
    else if ((ucMountingSide == ANIMMA_MOUNTINGSIDE_RIGHT)
        && ((bFlagType & ANIMMA_BLOCK_LEFTONLY) != 0U))
    {
        bRunSideFlag = false;
    }
    else
    {
        bRunSideFlag = true;
    }

    if (0U == (bFlagType & ANIMMA_BLOCK_STOPFLAG))
    {
        if ((uint32)blocktype < (sizeof(AnimMa_arcFunc) / sizeof(tAnimMa_rcFuncType))
            && (bRunSideFlag != false)
            && (bTime))
        {
            AnimMa_arcFunc[(sint32)blocktype](ulActiveBlkId, ulTime);
        }
    }
}

//-----------------------------------------------------------------------------
/// Return true if the block shall be executed tue to unTime (and its block type)
//-----------------------------------------------------------------------------
STATIC_AL bool AnimMa_TimeCondEndSeq(uint32 ulActiveBlkId, uint32 ulTime, uint32 * pulStopTime)
{
    bool bRet;

    const uint8 blocktype = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucType;

    const uint8 stopTime = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucTEnd;
    const uint8 startTime = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucTStart;

    uint32 unStopTime = AnimMa_Cod_Param2Ms(stopTime);
    uint32 unStartTime = AnimMa_Cod_Param2Ms(startTime);

    unStopTime = AnimMa_TimeWarp(unStopTime);
    unStartTime = AnimMa_TimeWarp(unStartTime);

    *pulStopTime = unStopTime;

    if (AnimMa_HasTime(blocktype))
    {
        bRet = (ulTime <= unStopTime) && (ulTime >= unStartTime);
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

//-----------------------------------------------------------------------------
/// All the stop blocks for the sequnces are called
//-----------------------------------------------------------------------------
bool AnimMa_rcStopBlock(uint32 ulActiveBlkId, uint32 ulTime, uint8 ucMountingSide)
{
    bool ret = false;

    static const tAnimMa_rcFuncType AnimMa_arcFunc[] =
    {
      AnimMa_rcBlockRun10,          // Index = block type RUN10 (0)
      AnimMa_rcBlockSparkleLfsr,    // Index = block type SPARKLE_LFSR (1)
      AnimMa_rcBlockSparkleXor64,   // Index = block type SPARKLE_XOR64 (2)
      AnimMa_rcBlockClamp,          // Index = block type DIM (3)
      AnimMa_rcBlockNA,             // Index = block type MASK (4)
      AnimMa_rcBlockFlex,           // Index = block type FLEX (5)
      AnimMa_rcBlockInvert,         // Index = block type INVERT (6)
      AnimMa_rcBlockBlink,          // Index = block type BLINK (7)
      AnimMa_rcBlockSpeedAssign,    // Index = block type SPEEDASSIGN (8)
      AnimMa_rcBlockPiecewiseLinear,// Index = block type PIECEWISELINEAR  (9)
      AnimMa_rcBlockInvertIntensity,// Index = block type INVERTINTENSITY  (10)
      AnimMa_rcBlockNA,           // Index = block type RUNN  (11)
      AnimMa_rcBlockTimeOffset,     // Index = block type TIMEOFFSET  (12)
      AnimMa_rcBlockRepetition      // Index = block type REPETITION  (13)
    };

    uint8 blocktype = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucType;
    uint8 bFlagType = AnimMa_Cod_GetBlockGenericBlkGenIdx(AnimMa_aActiveBlocks[ulActiveBlkId].unGenParamCodIdx)->ucFlags;
    uint32 unStopTime;

    // initialize block context if needed, update repetition counter, ...
    AnimMa_InitContext(ulActiveBlkId);

    /// true if it is time for the block to be executed
    const bool bTime = AnimMa_TimeCondEndSeq(ulActiveBlkId, ulTime, &unStopTime);

    // Running flag based on the Mounting side
    bool bRunSideFlag = false;

    // Check the mounting side and the bit 1&2 of the bFlagType
    if ((ucMountingSide == ANIMMA_MOUNTINGSIDE_LEFT)
        && ((bFlagType & ANIMMA_BLOCK_RIGHTONLY) != 0U))
    {
        bRunSideFlag = false;
    }
    else if ((ucMountingSide == ANIMMA_MOUNTINGSIDE_RIGHT)
        && ((bFlagType & ANIMMA_BLOCK_LEFTONLY) != 0U))
    {
        bRunSideFlag = false;
    }
    else
    {
        bRunSideFlag = true;
    }

    // Each block run only once, the bit 0 is reflecting the stop or non-stop block
    if (0U != (ANIMMA_BLOCK_STOPFLAG & bFlagType))
    {
        if ((uint32)blocktype < (sizeof(AnimMa_arcFunc) / sizeof(tAnimMa_rcFuncType))
            && (bTime)
            && (bRunSideFlag != false))
        {
            AnimMa_arcFunc[(sint32)blocktype](ulActiveBlkId, ulTime);
        }
        else if (ulTime == unStopTime) // For the applicable side
        {
            ret = true;
        }
        else if ((ulTime == (uint32)0U) && (bRunSideFlag == false))//For the non applicable side, does not execute 
        {
            ret = true;
        }
        else
        {
            // do nothing
        }
    }

    return ret;
}
//

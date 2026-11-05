//-----------------------------------------------------------------------------
/// Animation Master block interface
//-----------------------------------------------------------------------------

#ifndef ANIMMA_BLOCKS_H
#define ANIMMA_BLOCKS_H

#include <stdbool.h> // C99
#include <Std_Types.h>

#include "AnimMa.h"
#include "AnimMa_Types.h"


typedef enum
{
    RUN10 = 0,
    SPARKLE_LFSR = 1,
    SPARKLE_XOR64 = 2,
    CLAMP = 3,
    MASK = 4,
    FLEX = 5,
    INVERT = 6,
    BLINK = 7,
    SPEEDASSIGN = 8,
    PIECEWISELINEAR = 9,
    INVERTINTENSITY = 10,
    RUNN = 11,
    TIMEOFFSET = 12,
    REPETITION = 13,
    INVALID_BLOCK_TYPE = 255
} tAnimMaBlockType;

typedef enum
{
    NonStopBlock = 0, // the first bit of the flag is zero
    StopBlock = 1  //the first bit of the flag is zero
} tAnimMaFlagType;

/// Initializes all data structures (for example, at start up)
void AnimMa_Blocks_Init(void);

/// initializes internal data before the first block of a sequence is executed
void AnimMa_InitAtSequenceStart(void);

/// Allocate the blocks of the given sequence. unSeqCodIdx is the index into coding parameters.
uint8 AnimMa_AllocateBlocks(uint32 ulSeqCodIdx);
uint8 AnimMa_StopBlocksNr(uint32 ulSeqCodIdx);
void  AnimMa_DeleteBlocks(uint32 ulBlkFstIdx, uint32 ulSeqCodIdx);
// Init the content of all the block in one sequence
void AnimMa_InitBlocksContent(uint32 ulBlkFstIdx, uint32 ulSeqCodIdx);

/// Cyclic block execution
void AnimMa_rcBlock(uint32 ulActiveBlkId, uint32 ulTime, uint8 ucMountingSide);
bool AnimMa_rcStopBlock(uint32 ulActiveBlkId, uint32 ulTime, uint8 ucMountingSide);


/// [%] Array of target intensities
extern uint8 AnimMaRamp_aucPxlIntTgt[ANIMMA_NR_PIXELS];
/// [%] Array of target increments
extern uint8 AnimMaRamp_aucPxlIntInc[ANIMMA_NR_PIXELS];
/// [%] Array of target decrements
extern uint8 AnimMaRamp_aucPxlIntDec[ANIMMA_NR_PIXELS];
extern tActiveBlockRunN AnimMa_aActiveBlocksRunN[ANIMMA_NR_BLOCKS_RUNN];


#endif // ANIMMA_BLOCKS_H

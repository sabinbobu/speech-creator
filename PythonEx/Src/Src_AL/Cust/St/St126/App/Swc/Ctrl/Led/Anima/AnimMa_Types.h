//-----------------------------------------------------------------------------
/// Animation Master type definitions
//-----------------------------------------------------------------------------
#ifndef ANIMMA_TYPES_H
#define ANIMMA_TYPES_H

//=============================================================================
// includes
//=============================================================================

#include "AnimMa.h"
#include "RteCommonTypes.h"

//=============================================================================
// defines
//=============================================================================

//#define STATIC_AL static
#define AM_INLINE inline

/// Number of sequences that can be active at the same time
#define ANIMMA_NR_SEQUENCES                4U
/// Number of blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS                   90U
/// Number of RUN10 blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_RUN10             30U
/// Number of RUNN blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_RUNN              10U
/// Number of SPARKLELFSR blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_SPARKLE_LFSR      2U
/// Number of SPARKLELFSR blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_SPARKLE_XOR64     6U
/// Number of Blink blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_BLINK             8U
/// Number of Flex blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_FLEX              8U
/// Number of PiecewiseLinear blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_PIECEWISELINEAR   8U
/// Number of InvertIntensity blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_INVERTINTENSITY   8U
/// Number of TimeOffset blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_TIMEOFFSET        4U
/// Number of Repetition blocks that can be active at the same time
#define ANIMMA_NR_BLOCKS_REPETITION        4U

//Number for the interpolation
#define ANIMMA_DIMBLOCK_POINT_NUMBER       4U

/// Invalid BlkFstIdx
#define ANIMMA_INVALID_BLOCK_IDX           255U

#define ANIMMA_ENDLESSRUN_TIME             255U

#define ANIMMA_BLOCK_STOPFLAG              0x8U
#define ANIMMA_BLOCK_LEFTONLY              0x2U
#define ANIMMA_BLOCK_RIGHTONLY             0x4U
                                         
#define ANIMMA_MOUNTINGSIDE_INIT           0x0U
#define ANIMMA_MOUNTINGSIDE_LEFT           0x1U
#define ANIMMA_MOUNTINGSIDE_RIGHT          0x2U
#define ANIMMA_MOUNTINGSIDE_UNKNOWN        0x3U

/// Type for index into AnimMa_pCodingData (short type)
typedef uint16 tCodIdxS;
/// Type for index into AnimMa_pCodingData (natural type)
typedef uint32   tCodIdxL;

//=============================================================================
// structures
//=============================================================================
/// a type for dim ramp calculation
typedef struct
{
    uint32 ulCur;    ///< [high res] current value
    uint32 ulTgt;    ///< [high res] target value
    uint32 ulDelta;  ///< [high res] delta, current value is incremented or decremented with each call
} tStepRamp;

/// context of an active sequence
typedef struct
{
    uint32                        ulTime;// [cyclic ticks, e.g. 50 ms] Elapsed time since animation start
    //uint32  unStopTime;           ///< [cyclic ticks, e.g. 50 ms] Elapsed time since animation stop
    tCodIdxS                      unSeqCodIdx;///< Index for AnimMa_pCodingData, reference is first byte in coding data stream
    tSequenceStatus               unSeqStatus;  // Is sequence running active 
    teRte_ExtLightingAnimationReq ucSeqId;  ///< Sequence ID (from coding parameters)
    uint8                         ucBlkFstIdx;//< Index to the generic context of the first block of the sequence (index to AnimMa_aActiveBlocks)
    uint8                         unStopBlocks;// number of stop blocks in the sequence
} tActiveSequence;

/// generic context of an active block
typedef struct
{
    tCodIdxS unGenParamCodIdx;    ///< Index for AnimMa_pCodingData, reference is first byte in coding data stream, points to block generic parameters
    tCodIdxS unSpcParamCodIdx;    ///< Index for AnimMa_pCodingData, reference is first byte in coding data stream, points to block specific parameters
    uint8    ucBlkCtxIdx;    ///< Block-type specific index into a block context array
} tActiveBlock;

/// number of bytes for LFSR register; contains ANIMMA_NR_PIXELS bits at least
#define ANIMMA_BLOCK_LFSR_NR_REG_BYTES    ((ANIMMA_NR_PIXELS + 7) / 8)

/// specific context of a SPARKLELFSR  block
typedef struct
{
    uint32 unNextTime;    ///< time for next shift
    uint8  ucReg[ANIMMA_BLOCK_LFSR_NR_REG_BYTES];    ///< shift register
} tActiveBlockSparkleLfsr;

/// specific context of a SPARKLEXOR64  block
typedef struct
{
    uint32 unNextTime;      ///< time for next shift
    uint64 ulReg;             ///< 64 bit shift register
} tActiveBlockSparkleXor64;

/// specific context of a RUN10 block
typedef struct
{
    uint8 ucMovePos;      ///< current position of the pattern
} tActiveBlockRun10;

/// specific context of a RUNN block
typedef struct
{
    uint8 ucMovePos;      ///< current position of the pattern
} tActiveBlockRunN;

/// specific context of a FLEX block
typedef struct
{
    uint32 ulNextTime;      ///< time for next step
    uint32 ulPos;           ///< byte position of current row, that is, ucN * current row
} tActiveBlockFlex;

/// specific context of a PIECEWISELINEAR block
typedef struct
{
    uint32    ulNextTime;      ///< time for next step
    tStepRamp ramp;         ///< dim ramp data
    uint8     ucIdx;            ///< current position in array of function points (0 ... N-1)
} tActiveBlockPiecewiseLinear;

/// specific context of a REPETITION block
typedef struct
{
    uint32 ulNextTime;      ///< time for next step
    uint8  ucRepCntDn;       ///< count down for number of repetitions
} tActiveBlockRepetition;

extern tActiveSequence             AnimMa_aActiveSeq[ANIMMA_NR_SEQUENCES];
extern tActiveBlock                AnimMa_aActiveBlocks[ANIMMA_NR_BLOCKS];
extern tActiveBlockRun10           AnimMa_aActiveBlocksRun10[ANIMMA_NR_BLOCKS_RUN10];
extern tActiveBlockSparkleLfsr     AnimMa_aActiveBlocksSparkleLfsr[ANIMMA_NR_BLOCKS_SPARKLE_LFSR];
extern tActiveBlockSparkleXor64    AnimMa_aActiveBlocksSparkleXor64[ANIMMA_NR_BLOCKS_SPARKLE_XOR64];
extern tActiveBlockFlex            AnimMa_aActiveBlocksFlex[ANIMMA_NR_BLOCKS_FLEX];
extern tActiveBlockPiecewiseLinear AnimMa_aActiveBlocksPiecewiseLinear[ANIMMA_NR_BLOCKS_PIECEWISELINEAR];
extern tActiveBlockRepetition      AnimMa_aActiveBlocksRepetition[ANIMMA_NR_BLOCKS_REPETITION];

typedef struct
{
    uint8  bLB : 1;
    uint8  bF2P : 1;
    uint8  bEtat : 1;
    uint8  bGFHBAvailability : 1;
    uint8  bHB : 1;
    uint8  bDRL : 1;
    uint8  bFP : 1;
    uint8  bTI : 1;
}tsInputsCheck;

typedef union
{
    tsInputsCheck  bBit;
    uint8          unRaw;

}uInputsCheck;

typedef enum
{
    eAnima_ModeConfigVehicle_Montage     = 0U,
    eAnima_ModeConfigVehicle_Usine       = 1U,
    eAnima_ModeConfigVehicle_Controle    = 2U,
    eAnima_ModeConfigVehicle_Stockage    = 3U,
    eAnima_ModeConfigVehicle_Client      = 4U,
    eAnima_ModeConfigVehicle_Showroom    = 5U,
    eAnima_ModeConfigVehicle_AfterMarket = 6U,
    eAnima_ModeConfigVehicle_Invalid     = 7U,
    eAnima_ModeConfigVehicle_Invalid2    = 15U
}teAnima_ModeConfigVehicle;

// Glare Free HighBeam command
typedef enum
{
    Anima_eGfHb_Off,
    Anima_eCurtain_Activation,
    Anima_eGfHb_On,
    Anima_eCurtain_Deactivation
}teAnima_GfHbCmd;

#endif // ANIMMA_TYPES_H

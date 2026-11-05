//-----------------------------------------------------------------------------
/// Animation Master type definitions:access to coding data
//-----------------------------------------------------------------------------
#ifndef ANIMMA_COD_H
#define ANIMMA_COD_H

#include <stdbool.h> 
#include <Std_Types.h>
#include "AnimMa_Types.h"

/// Number of bytes for a dictionary entry (id: 1 byte, size: 2 bytes)
#define ANIMMA_COD_BYTES_SEQ_ENTRY      3u

/// Pointer to the coding data
extern CONST_AL tNvmPara_CodingArea * AnimMa_pCodingData;

/// defines how coding data for a sequence start
typedef struct
{
  uint8 ucID;   ///< Sequence ID
  uint8 ucN;    ///< Number of blocks
} tSequence;

/// defines coding data for generic block parameters
typedef struct
{
  uint8 ucType;     ///< Block Type (tAnimMaBlockType)
  uint8 ucIdxMSB;   ///< Use this index to locate block specific data in AnimMa_pCodingData, index is relative to start of sequence. 
  uint8 ucIdxLSB;   ///< Use this index to locate block specific data in AnimMa_pCodingData, index is relative to start of sequence. 
  uint8 ucFlags;    ///< Flags
  uint8 ucTStart;   ///< [50 ms] Start time
  uint8 ucTEnd;     ///< [50 ms] End time
  uint8 ucPStart;   ///< [0...ANIMMA_NR_PIXELS-1] First pixel
  uint8 ucPEnd;     ///< [0...ANIMMA_NR_PIXELS-1] Last pixel
} tBlockGeneric;

/// access flags: stop flag
AM_INLINE bool AnimMa_GetGenericFlagStop(const tBlockGeneric * pBG) { return (pBG->ucFlags & ANIMMA_BLOCK_STOPFLAG) != 0u; }

/// Run type for run blocks (e.g. Run10)
typedef enum
{
  RUN = 0U,
  SWEEP = 1U,
  DISAPPEAR = 2U
} tBlockSpecificRun10Type;

/// defines coding data for specific Run10 block parameters
typedef struct
{
  uint8 ucDimUp;
  uint8 ucDimDn;
  uint8 aucPattern[10];
  uint8 ucPatternSize;
  uint8 ucSpeed;
  ///< [50 ms] time until pattern appears after pattern disappears
  uint8 ucWaitTime;  
  /// [tBlockSpecificRun10Type] run type
  uint8 ucType;       
} tBlockSpecificRun10;

/// defines coding data for specific RunN block parameters
typedef struct
{
    uint8 ucDimUp;
    uint8 ucDimDn;
    uint8 ucSpeed;
    uint8 ucWaitTime;   ///< [50 ms] time until pattern appears after pattern disappears

    //uint8 aucPattern[20];       ///pattern size meant to be N for this block type, in this case, upto a maximum of 20 currently

    ///Size of pattern vector [0 ... 255]
    uint8 ucPatternSize;
    /// [tBlockSpecificRunNType] run type
    uint8 ucType;     
    ///< First byte of 1x N bytes (an array of singles (I only))
    uint8 ucByte0;      
} tBlockSpecificRunN;

/// defines coding data for specific SparkleLfsr block parameters
typedef struct
{
  uint8 ucDimUp;
  uint8 ucDimDn;
  uint8 aucStartValue[ANIMMA_BLOCK_LFSR_NR_REG_BYTES];  ///< Start value
  uint8 aucFeedback[ANIMMA_BLOCK_LFSR_NR_REG_BYTES];    ///< Feedback 
  uint8 ucUpdateInterval;                     ///< [50 ms] interval for shift operations
} tBlockSpecificSparkleLfsr;


/// defines coding data for specific Clamp/Dim block parameters
typedef struct
{
  uint8 aucLowerLimit[8];              ///< 64 bit lower limit of intensity
  uint8 aucUpperLimit[8];              ///< 64 bit upper limit of intensity
} tBlockSpecificClamp;


/// defines coding data for specific SparkleXor64 block parameters
typedef struct
{
  uint8 ucDimUp;
  uint8 ucDimDn;
  uint8 aucStartValue[8];                   ///< 64 bit start value
  uint8 aucShift[3];                        ///< 3 shift values
  uint8 ucUpdateInterval;                   ///< [50 ms] interval for shift operations
} tBlockSpecificSparkleXor64;


/// defines coding data for specific blink block parameters
typedef struct
{
  uint8 ucDimUp;
  uint8 ucDimDn;
  uint8 ucPixelMask[12];
  uint8 ucTDelay;
  uint8 ucTPeriod;
  uint8 ucTPhase;
  uint8 ucTOn;
  uint8 ucIOn;
  uint8 ucIOff;
} tBlockSpecificBlink;

/// defines coding data for specific Flex block parameters
typedef struct
{
  uint8 ucDimUp;    ///< [%/10 ms] Dim Up Increment
  uint8 ucDimDn;    ///< [%/10 ms] Dim Down Decrement
  uint8 ucN;        ///< Number of pixels that are controlled by this block, must be a multiple of 8
  uint8 ucT;        ///< [50 ms] Time of the Flex block, that is, number of rows
  uint8 ucByte0;    ///< First byte of ucT * (ucN / 8) bytes
} tBlockSpecificFlex;

#define ANIMMA_COD_SPEEDASSIGN_NR_OF_INCREMENTS   4

/// defines coding data for specific SpeedAssign block parameters
typedef struct
{
  uint8 ucDimUpInc[ANIMMA_COD_SPEEDASSIGN_NR_OF_INCREMENTS];    ///< [%/10 ms] Dim Up Increment
  uint8 ucDimDnDec[ANIMMA_COD_SPEEDASSIGN_NR_OF_INCREMENTS];    ///< [%/10 ms] Dim Down Decrement
  //uint8 ucStartIntensity;  ///< [%] Intensity at start time
  uint8 ucN;        ///< Number of pixels that are controlled by this block
  uint8 ucByte0;    ///< First byte of 2x (ucN / 4) bytes (for each pixel an index into ucDimUpInc and an index into ucDimDnDec)
} tBlockSpecificSpeedAssign;

/// defines coding data for specific PiecewiseLinear block parameters
typedef struct
{
  uint8 ucDimUpInc;   ///< [%/10 ms] Dim Up Increment
  uint8 ucDimDnDec;   ///< [%/10 ms] Dim Down Decrement
  uint8 ucInitI;      ///< [%] Initial intensity
  uint8 ucN;          ///< Number of function points [0 ... 255]
  uint8 ucByte0;      ///< First byte of 2x N bytes (an array of tuples (dT, I))
} tBlockSpecificPiecewiseLinear;

/// defines coding data for specific Repetition block parameters
typedef struct
{
  uint8 ucNrBlocks;       ///< Number of blocks after the Repetition block that are to be repeated
  uint8 ucNrRepetitions;  ///< Number of repetitions
  uint8 ucRepetitionTime; ///< [50 ms] A repetition is started after this time
} tBlockSpecificRepetition;

//-----------------------------------------------------------------------------
/// Combine MSB (first byte) and LSB (second byte) to a tCodIdxL
//-----------------------------------------------------------------------------
AM_INLINE tCodIdxL AnimMa_Cod_MakeIdx(uint8 ucFirstByte, uint8 ucSecondByte)
{
  return (((tCodIdxL)ucFirstByte) << 8u) | ((tCodIdxL)ucSecondByte);
}

//-----------------------------------------------------------------------------
/// Combine MSB and LSB into an uint16
//-----------------------------------------------------------------------------
AM_INLINE uint16 AnimMa_Cod_MakeUInt16(uint8 ucMSB, uint8 ucLSB)
{
  return (((uint16)ucMSB) << 8u) | ((uint16)ucLSB);
}

//-----------------------------------------------------------------------------
/// Returns the coding parameter value in [ms]
//-----------------------------------------------------------------------------
AM_INLINE uint32 AnimMa_Cod_Param2Ms(uint32 unTime)
{
  return ANIMMA_CYCLE_TIME * unTime;
}

//-----------------------------------------------------------------------------
/// Return the pointer to the parameter vector containing the Patterns in RunN block
//-----------------------------------------------------------------------------
AM_INLINE const uint8* AnimMa_Cod_Get_BlockSpecificRunN_Patterns(const tBlockSpecificRunN* pCodSpc)
{
  return &(pCodSpc->ucByte0);
}

//-----------------------------------------------------------------------------
/// Return the intensity raw value for each Pattern element of RunN block with index unIdx.
/// Index unIdx is not checked for range.
//-----------------------------------------------------------------------------
AM_INLINE uint8 AnimMa_Cod_Get_BlockSpecificRunN_Pattern_Intensity(const tBlockSpecificRunN* pCodSpc, uint32 ulIdx)
{
  const uint8* p = AnimMa_Cod_Get_BlockSpecificRunN_Patterns(pCodSpc);
  return p[1u * ulIdx];
}

//-----------------------------------------------------------------------------
/// Return the pointer to the parameter array of function time..
//-----------------------------------------------------------------------------
AM_INLINE const uint8 * AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoints(const tBlockSpecificPiecewiseLinear * pCodSpc)
{
  return &(pCodSpc->ucByte0);
}

//-----------------------------------------------------------------------------
/// Return the time raw value for function point with index unIdx.
/// Index unIdx is not checked for range.
//-----------------------------------------------------------------------------
AM_INLINE uint8 AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Time(const tBlockSpecificPiecewiseLinear * pCodSpc, uint32 ulIdx)
{
  const uint8 * p = AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoints(pCodSpc);
  return p[2u*ulIdx];
}

//-----------------------------------------------------------------------------
/// Return the intensity raw value for function point with index unIdx.
/// Index unIdx is not checked for range.
//-----------------------------------------------------------------------------
AM_INLINE uint8 AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Intensity(const tBlockSpecificPiecewiseLinear * pCodSpc, uint32 ulIdx)
{
  const uint8 * p = AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoints(pCodSpc);
  return p[2u*ulIdx + 1u];
}

/// Return the coding data pointer
AM_INLINE const uint8 *         AnimMa_Cod_GetCodingData(void) { return &AnimMa_pCodingData->Animation.AnimationByteStream.aucByteStream[0]; }
AM_INLINE char                  AnimMa_Cod_GetStreamVersion(void) { return AnimMa_Cod_GetCodingData()[0]; }
AM_INLINE uint32                AnimMa_Cod_GetNumberOfSequences(void) { return (uint32)(AnimMa_Cod_GetCodingData()[1]); }
AM_INLINE tCodIdxL              AnimMa_Cod_GetDictFirstEntryIdx() { return 2u; }
AM_INLINE tCodIdxL              AnimMa_Cod_GetFirstSequenceIdx(void) { return AnimMa_Cod_GetDictFirstEntryIdx() + ANIMMA_COD_BYTES_SEQ_ENTRY * AnimMa_Cod_GetNumberOfSequences(); }
 tCodIdxL              AnimMa_Cod_GetSequenceIdx(teRte_ExtLightingAnimationReq eSeqId);
AM_INLINE const tSequence *     AnimMa_Cod_GetSequence(tCodIdxL ulSeqIdx)                           { return (const tSequence *)(const void *) &(AnimMa_Cod_GetCodingData()[ulSeqIdx]); }
AM_INLINE uint32                AnimMa_Cod_GetNrBlocks(tCodIdxL ulSeqIdx)                           { return (uint32)(AnimMa_Cod_GetSequence(ulSeqIdx)->ucN); }
AM_INLINE tCodIdxS              AnimMa_Cod_GetBlockGenIdx(tCodIdxL ulSeqIdx, uint32 ulBlkNr)        { return (uint16)(ulSeqIdx + sizeof(tSequence) + ulBlkNr * sizeof(tBlockGeneric)); }
AM_INLINE tCodIdxL              AnimMa_Cod_GetBlockGenSize(tCodIdxL ulSeqIdx)                       { return AnimMa_Cod_GetNrBlocks(ulSeqIdx) * sizeof(tBlockGeneric); }
AM_INLINE const tBlockGeneric * AnimMa_Cod_GetBlockGeneric(tCodIdxL ulSeqIdx, uint32 ulBlkNr)       { return (const tBlockGeneric *)(const void *) &(AnimMa_Cod_GetCodingData()[AnimMa_Cod_GetBlockGenIdx(ulSeqIdx, ulBlkNr)]); }
AM_INLINE CONST_AL tBlockGeneric * AnimMa_Cod_GetBlockGenericBlkGenIdx(tCodIdxS ulBlkGenIdx)           { return (const tBlockGeneric *)(const void *) &(AnimMa_Cod_GetCodingData()[ulBlkGenIdx]); }
AM_INLINE tCodIdxS              AnimMa_Cod_GetBlockSpcIdx(tCodIdxL ulSeqIdx, uint32 ulBlkNr)
{
  const tBlockGeneric * pBG = AnimMa_Cod_GetBlockGeneric(ulSeqIdx, ulBlkNr);
  return (uint16)( ulSeqIdx + AnimMa_Cod_MakeIdx(pBG->ucIdxMSB, pBG->ucIdxLSB));
}
AM_INLINE uint16                AnimMa_Cod_GetDelayTiNotRequested(void)                             { return AnimMa_pCodingData->Led1.BasicFunctions.unDELAY_TI_NOT_REQUESTED; }

#endif // ANIMMA_COD_H

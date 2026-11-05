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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include "Swc/Ctrl/Led/Anima/AnimMa_Blocks.h"
#include "Swc/Ctrl/Led/Anima/AnimMa_Types.h"
#include <ALUnitTest_UserInterface.h>
#include "Swc/Ctrl/Led/Anima/AnimMa_Cod.h"
#include <UtilDebounce.h>

//=============================================================================
// Defines
//=============================================================================

/// 0 = disabled, 1 = enabled
#define CFG_ENABLE_LOGGING                          0
/// Priority if an animation is running
#define PRIORITY_ANIMATION_RUNNING                  TRUE
/// Priority if animations are not running
#define PRIORITY_ANIMATION_NONE                     FALSE
#define T2P(t)                                      (t/ANIMMA_CYCLE_TIME)
/// Number of Repetition blocks that can be running concurrently (defines stack size)
#define ANIMMA_MAX_NR_NESTED_REPETITIONS            ANIMMA_NR_BLOCKS_REPETITION

///output txt files used for testing and checking behavior
#if CFG_ENABLE_LOGGING == 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#endif
#if CFG_ENABLE_LOGGING == 1
STATIC_AL FILE * Anima_Test_fp = NULL;
#endif

//=============================================================================
// Typedefs
//=============================================================================

/// Elements of the Repetition block stack
typedef struct
{
    uint32 ulTimeOffset; ///< [ms] time offset for the Repetition block
    uint8  ucRepBlkCntDn;   ///< Number of blocks that the Repetition block works on (modifies), count down value
} tAnimMa_Repetition;

/// Stack for concurrent Repetition blocks
typedef struct
{
    tAnimMa_Repetition aValues[ANIMMA_MAX_NR_NESTED_REPETITIONS];
    uint8              ucCnt; ///< Next free index into aValues = number of concurrent Repetition blocks; 0 <= ucCnt <= ANIMMA_MAX_NR_NESTED_REPETITIONS
} tAnimMa_RepetitionStack;

/// store state of time modifications (modified by e.g. TimeOffset block)
STATIC_AL struct
{
    uint32                  ulTimeOffset;    ///< [ms] time offset that is applied to Tstart and Tend.
    uint32                  ulTimeOffsetRepetition; ///< [ms] time offset that is applied to Tstart and Tend.
    tAnimMa_RepetitionStack RepetitionStack; ///< Stack for concurrent repetitions
    bool                    bInitContext;      ///< true = initialize context of blocks
    uint8                   ucInitContextCnt; ///< count down: number of block context initializations
} sTimeWarp;

///used for animations- total of 27 pixels
typedef struct
{
    uint16 unTime;     // [ms]
    uint16 aunHopt[27]; // [%]
} tResultsAnimaC;

///Used for blocks checking- no more than 10 pixels
typedef struct
{
    uint16 unTime;     // [ms]
    uint16  aunHopt[10]; // [%]
} tResultsBlocks;

///Struct used to test animas with TI SCR
typedef struct
{
    uint16 unTime;     // [ms]
    uint16 aunHopt[28]; // [%]
} tResultsScr;

//=============================================================================
// Module global variables
//=============================================================================

extern tActiveSequence             AnimMa_aActiveSeq[ANIMMA_NR_SEQUENCES];
extern uint32                      AnimMa_unActiveBlocksCnt;
extern tActiveBlock                AnimMa_aActiveBlocks[ANIMMA_NR_BLOCKS];
extern uint32                      AnimMa_unActiveBlocksRun10Cnt;
extern uint32                      AnimMa_unDeactivateBlocksRun10Cnt;
extern tActiveBlockRun10           AnimMa_aActiveBlocksRun10[ANIMMA_NR_BLOCKS_RUN10];
extern uint32                      AnimMa_unActiveBlocksRunNCnt;
extern uint32                      AnimMa_unDeactivateBlocksRunNCnt;
extern tActiveBlockRunN            AnimMa_aActiveBlocksRunN[ANIMMA_NR_BLOCKS_RUNN];
extern uint32                      AnimMa_unActiveBlocksSparkleLfsrCnt;
extern uint32                      AnimMa_unDeactivateBlocksSparkleLfsrCnt;
extern tActiveBlockSparkleLfsr     AnimMa_aActiveBlocksSparkleLfsr[ANIMMA_NR_BLOCKS_SPARKLE_LFSR];
extern uint32                      AnimMa_unActiveBlocksSparkleXor64Cnt;
extern uint32                      AnimMa_unDeactivateBlocksSparkleXor64Cnt;
extern tActiveBlockSparkleXor64    AnimMa_aActiveBlocksSparkleXor64[ANIMMA_NR_BLOCKS_SPARKLE_XOR64];
extern uint32                      AnimMa_unActiveBlocksBlinkCnt;
extern uint32                      AnimMa_unDeactivateBlocksBlinkCnt;
extern uint32                      AnimMa_unActiveBlocksClampCnt;
extern uint32                      AnimMa_unDeactivateBlocksClampCnt;
extern uint32                      AnimMa_unActiveBlocksInvertCnt;
extern uint32                      AnimMa_unDeactivateBlocksInvertCnt;
extern uint32                      AnimMa_unActiveBlocksFlexCnt;
extern uint32                      AnimMa_unDeactivateBlocksFlexCnt;
extern tActiveBlockFlex            AnimMa_aActiveBlocksFlex[ANIMMA_NR_BLOCKS_FLEX];
extern uint32                      AnimMa_unActiveBlocksSpeedAssignCnt;
extern uint32                      AnimMa_unDeactivateBlocksSpeedAssignCnt;
extern uint32                      AnimMa_unActiveBlocksPiecewiseLinearCnt;
extern uint32                      AnimMa_unDeactivateBlocksPiecewiseLinearCnt;
extern tActiveBlockPiecewiseLinear AnimMa_aActiveBlocksPiecewiseLinear[ANIMMA_NR_BLOCKS_PIECEWISELINEAR];
extern uint32                      AnimMa_unActiveBlocksInvertIntensityCnt;
extern uint32                      AnimMa_unDeactivateBlocksInvertIntensityCnt;
extern uint32                      AnimMa_unActiveBlocksRepetitionCnt;
extern uint32                      AnimMa_unDeactivateBlocksRepetitionCnt;
extern uint8                       AnimMaRamp_aucPxlIntTgt[ANIMMA_NR_PIXELS];
extern uint8                       AnimMaRamp_aucPxlIntInc[ANIMMA_NR_PIXELS];
extern uint8                       AnimMaRamp_aucPxlIntDec[ANIMMA_NR_PIXELS];
extern tUtilDebounceControl        Anima_TgtPrep_TiDelayTimer;
extern uint8                       AnimMa_ucActiveSeqCnt;
extern uint8                       AnimMa_ucMountingSide;
extern tsRte_TgtAniArr             Anima_TgtAniArr;
extern tsRte_TgtAniArrScr          Anima_Scrolling;

//=============================================================================
// Module function declarations
//=============================================================================

//AnimMa_Blocks.c
extern uint8            interpolateDim(uint16 * T, uint16 * I, uint32 unTime);
extern uint8            AnimMa_AllocateBlockContext(uint8 blocktype);
extern void             AnimMa_InitBlockContext(uint32 ulActiveBlkId);
extern void             AnimMa_DeleteBlockContext(uint32 unBlkCtxIdx, uint8 blocktype);
extern void             AnimMa_RepetitionStack_Push(const uint32 unTime, const uint8 ucBlockCnt);
extern void             AnimMa_RepetitionStack_Pop(void);
extern void             AnimMa_UpdateRepetition(void);
extern void             AnimMa_rcBlockRun10(uint32 ulActiveBlkId, uint32 ulTime);
extern void             AnimMa_EnableInitContext(uint8 ucNr);
extern tBlockGeneric *  AnimMa_Cod_GetBlockGenericBlkGenIdx(tCodIdxS ulBlkGenIdx);
extern  void            AnimMa_rcBlockSparkleXor64(uint32 ulActiveBlkId, uint32 ulTime);
extern void             AnimMa_LfsrShift(const uint32 ulBlkCtxIdx, const tBlockSpecificSparkleLfsr * pCodSpc, const sint32 nBits);
extern  void            AnimMa_Ramp_UpdateDelta(const uint32 dt, const uint32 y1, const uint32 y2, const uint32 timestep, tStepRamp * pRamp);
extern void             AnimMa_Ramp_Step(tStepRamp * pRamp);
extern uint32           AnimMa_TimeWarp(uint32 unTime);
extern void             AnimMa_PiecewiseLinear_InitRamp(uint32 ulIdx, const tBlockSpecificPiecewiseLinear * pCodSpc, tStepRamp * pRamp);
extern uint32           muldiv32_ceil(uint32 dividend1, uint32 dividend2, uint32 divisor);

//AnimMa.c
extern uint32           AnimMa_FindSequence(teRte_ExtLightingAnimationReq ucSeqId);
extern void             AnimMa_rcSequence(uint32 nSeq);
extern void             AnimMa_clearSequence(uint32 nSeq);
extern  bool            AnimMa_IsIdxValid(uint32 ulIdx);
extern void             Anima_DoRamps(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
//Anima_CodPrj.c
tNvmPara_CodingArea                           AnimaCodingAreaC = { 0u };
tNvmPara_CodingArea                           AnimaCodingAreaDim;
tNvmPara_CodingArea                           AnimaCodingAreaRun;
tNvmPara_CodingArea                           AnimaCodingAreaFlex;
tNvmPara_CodingArea                           AnimaCodingAreaBlink;
tNvmPara_CodingArea                           AnimaCodingAreaLFSR_XOR;
tNvmPara_CodingArea                           AnimaCodingAreaWelcomeDayNight;
tNvmPara_CodingArea                           AnimaCodingAreaUnlockDayNightExt;
tNvmPara_CodingArea                           AnimaCodingAreaUnlockDayNight;
tNvmPara_CodingArea                           AnimaCodingAreaUndefinedAnima;
tNvmPara_CodingArea                           AnimaCodingAreaShowroomEvent;
tNvmPara_CodingArea                           AnimaCodingAreaLockDayNight;
tNvmPara_CodingArea                           AnimaCodingAreaBye;
tNvmPara_CodingArea                           AnimaCodingAreaFMH;
tNvmPara_CodingArea                           AnimaCodingAreaFMH30;
tNvmPara_CodingArea                           AnimaCodingAreaFMH60;

//AnimMa_Blocks.c
uint32                                        muldiv32_ceil_Param1;
uint32                                        muldiv32_ceil_Param2;
uint32                                        muldiv32_ceil_Param3;
uint64                                        muldiv32_ceil_RetVal;


//AnimMa_Blocks.c
uint32                                        AnimMa_RepetitionStack_Push_Param1;
uint8                                         AnimMa_RepetitionStack_Push_Param2;
uint32                                        AnimMa_TimeWarp_Param;
uint32                                        AnimMa_DeleteBlockContext_BlkIdx;
uint8                                         AnimMa_AllocateBlockContext_Param;
uint32                                        AnimMa_BlockContext_BkType;
uint8                                         AnimMa_EnableInitContext_Param;
uint32                                        AnimMa_rcBlockRun10_Param1;
uint32                                        AnimMa_rcBlockRun10_Param2;
uint32                                        AnimMa_LfsrShift_Param1;
tBlockSpecificSparkleLfsr                   * AnimMa_LfsrShift_Param2;
sint32                                        AnimMa_LfsrShift_Param3;
uint32                                        AnimMa_rcBlockSparkleLfsr_Param1;
uint32                                        AnimMa_rcBlockSparkleLfsr_Param2;

//AnimMa.c
teRte_ExtLightingAnimationReq                 AnimMa_Cod_GetSequenceIdx_Param;
teRte_ExtLightingAnimationReq                 AnimMa_FindSequence_Param;
teRte_ExtLightingAnimationReq                 AnimMa_isSequenceActive_Param;
teRte_ExtLightingAnimationReq                 AnimMa_isStopSequenceActive_Param;
teRte_ExtLightingAnimationReq                 AnimMa_isSeqActivePhase_WithNoRunningIDs_Param;
teRte_ExtLightingAnimationReq                 AnimMa_getElapsedTime_Param;
teRte_ExtLightingAnimationReq                 AnimMa_stopSequence_Param;
teRte_ExtLightingAnimationReq                 AnimMa_startSequence_Param;
teRte_ExtLightingAnimationReq                 AnimMa_softStopSequence_Param;
uint32                                        AnimMa_rcSequence_Param1;
const tNvmPara_CodingArea                   * pData_Param;

//ctaaAnima.c
tParaFct0_Cmd                                 roAnima_ParaFct0_Param1;
tNvmPara_CodingArea*                          roAnima_ParaFct0_Param2;
uint32                                        AnimMa_AllocateBlocks_Param;

//=============================================================================
// Module function return value stubs
//=============================================================================

//Anima.c
boolean                 Anima_ReadFrontTurnIndicatorCmd_RetVal;

//AnimMa.c
tCodIdxL                AnimMa_Cod_GetSequenceIdx_RetVal;
uint32                  AnimMa_FindSequence_RetVal;
uint32                  AnimMa_isStopSequenceActive_RetVal;
uint32                  AnimMa_isSeqActivePhase_WithNoRunningIDs_RetVal;
uint32                  AnimMa_getElapsedTime_RetVal;
boolean                 AnimMa_isSequenceActive_RetVal;
uint8                   AnimMa_ActiveSeqNr_RetVal;
uint32                  AnimMa_AllocateBlocks_RetVal;

//////output txt files used for testing and checking behavior
//-----------------------------------------------------------------------------
/// If needed: open a file to save results
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_Log_Start(const char * filename);

//-----------------------------------------------------------------------------
/// If needed: close the logging file
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_Log_Stop(void);

//-----------------------------------------------------------------------------
/// Write a message to output file Anima_Test_fp
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_Log(const char *format, ...);

//-----------------------------------------------------------------------------
/// Initialize stubs and globals
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_PreTest(void);

#if CFG_ENABLE_LOGGING == 1
//-----------------------------------------------------------------------------
/// Open a file for logging results
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_Log_Start(const char * filename)
{
    Anima_Test_fp = fopen(filename, "w+");
}

//-----------------------------------------------------------------------------
/// Open a file for logging results
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_Log_Stop(void)
{
    if (Anima_Test_fp != NULL)
    {
        fclose(Anima_Test_fp);
        Anima_Test_fp = NULL;
    }
}

//-----------------------------------------------------------------------------
/// Write a message to output file Anima_Test_fp
//-----------------------------------------------------------------------------
void  Mt_CtrlLed_Log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(Anima_Test_fp, format, args);
    va_end(args);
}
#endif

#endif // TEST_2023_08_25_H_
